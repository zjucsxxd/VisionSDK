/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
#include <ioctl_func.h>

#include <linux/spinlock.h>
#include <linux/dma-mapping.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/slab.h>

#include <cma_list.h>
#include <ioctl_cmd.h>
#include <oal_alloc.h>
// Spin lock for mutual exclusive access to the management list
static DEFINE_SPINLOCK(oal_lock);

//////////////////////////////////////////////////////////////////////////////////
// Function allocates a contiguous memory block and add an item into management list.
// Returns allocated HW address if success, 0 otherwise.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_alloc(unsigned long size)
{
  void * virt;
  void * phys;
  int ret;
  t_MemArea *area = (t_MemArea *)vmalloc(sizeof(t_MemArea));
  
  // if size is 0, return error
  if (!size)
    return 0;
  
  // Allocate coherent cont. physical block
  virt = OAL_ContAllocDDRAlloc(size);
  phys = OAL_DDR_PHYSICAL_POOL_BASE + (virt - OAL_ContAllocDDRGetBaseVirt());
  //printk("Allocated memory on: %p\n", virt);
  //printk("                     %p\n", phys);
  //virt = kmalloc(size, GFP_KERNEL | GFP_USER | GFP_DMA);
  //struct page *p = alloc_pages(GFP_KERNEL | GFP_USER | GFP_DMA, 2);
  //virt = page_address(p);
  //phys = dma_map_single(0, virt, size, DMA_BIDIRECTIONAL);
  //virt = dma_alloc_noncoherent(0, size, &phys, GFP_KERNEL | GFP_USER);
  //printk("Allocated memory: %i 0x%x 0x%x\n", size, (unsigned long)virt, phys);
  
  // If allocation succeeded
  if (virt)
  {
    // Create an allocation structure
    area->kernel_physical = (unsigned long)phys;
    area->kernel_virtual = (unsigned long)virt;
    area->size = size;
    area->user_addresses = NULL;
    
    // Push it into the list of allocations
    spin_lock(&oal_lock);
    ret = cma_list_area_push_back(area);
    spin_unlock(&oal_lock);
    
    if (ret < 0)
      return 0;
    else
      return (unsigned long)phys;
  }
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Function removes a contiguous memory block and removes an entry from the management list.
// Returns 0 if success and ULONG_MAX if fail.
// Does not free virtual mappings.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_free (unsigned long kernel_physical)
{
  t_MemArea *area;
  int ret;
  
  //printk("Freeing memory on: %x\n", kernel_physical);
  // Get area from list and try to remove it
  spin_lock(&oal_lock);
  area = cma_list_area_find(kernel_physical);
  ret = cma_list_area_remove(area);
  spin_unlock(&oal_lock); 
  
  // If successfully removed
  if (ret > 0)
  {
    // Free allocated memory and free the structure
    //dma_unmap_single(0, area->kernel_physical, area->size, DMA_BIDIRECTIONAL);
    //kfree((void *)area->kernel_virtual);
    OAL_ContAllocDDRFree((void *)area->kernel_virtual);
    //dma_free_noncoherent(0, area->size, (void *)area->kernel_virtual, area->kernel_physical);
    vfree(area);
    return 0;
  }
  else
    return ULONG_MAX;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns a size of allocated memory block.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_getsize(unsigned long kernel_physical)
{
  t_MemArea *area;
  
  spin_lock(&oal_lock);
  area = cma_list_area_find(kernel_physical);
  spin_unlock(&oal_lock);
  
  if (area)
    return area->size;
  else 
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns a current process virtual memory mapping.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_getvirtual(unsigned long kernel_physical)
{
  t_MemArea *area;
  
  spin_lock(&oal_lock);
  area = cma_list_area_find(kernel_physical);
  spin_unlock(&oal_lock);
  
  // if found appropriate area, try to find an vaddress
  if (area)
  {
    t_UserAddress *user;
    
    spin_lock(&oal_lock);
    user = cma_list_user_find(area, current->pid);
    spin_unlock(&oal_lock);
    
    if (user)
      return user->user_virtual;
    else
      return 0;
      
  }
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns a current process physical memory mapping.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_getphysical(unsigned long user_virtual)
{
  t_MemArea *area;
  
   spin_lock(&oal_lock);
   area = cma_list_user_find_physical(current->pid, user_virtual);
   spin_unlock(&oal_lock);
   
   // if found appropriate area, try to find an kernel physical address
   if (area)
    return area->kernel_physical;
   else
     return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Function adds a new memory mapping into the management list (current process).
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_map(t_MapStruct address)
{
  t_MemArea *area;
  int ret; 
  t_UserAddress *user = (t_UserAddress *)vmalloc(sizeof(t_UserAddress));
  
  spin_lock(&oal_lock);
  area = cma_list_area_find(address.kernel_physical);
  spin_unlock(&oal_lock);
  
  user->pid = current->pid;
  user->user_virtual = address.user_virtual;
    
  spin_lock(&oal_lock);
  ret = cma_list_user_push_back(area, user);
  spin_unlock(&oal_lock);
    
  if (ret < 0)
    return 0;
  else return user->user_virtual;
}

//////////////////////////////////////////////////////////////////////////////////
// Function removes a memory mapping for current process.
//////////////////////////////////////////////////////////////////////////////////
unsigned long oal_unmap(unsigned long kernel_physical)
{
  t_MemArea *area;
  t_UserAddress *addr;
  int ret;
  
  spin_lock(&oal_lock);
  area = cma_list_area_find(kernel_physical);
  
  ret = cma_list_user_remove(area, current->pid, &addr);
  vfree(addr);
  spin_unlock(&oal_lock);
  
  return ret;
}

void oal_reset()
{
  spin_lock(&oal_lock);
  cma_list_reset();
  spin_unlock(&oal_lock);
}