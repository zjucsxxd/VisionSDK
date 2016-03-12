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
#include <linux/device.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/cdev.h>


#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/kernel.h> 

#include <oal_alloc.h>
//#include <uapi/linux/fb.h>
//#include <asm/io.h> 
//#include <linux/stat.h>
//#include <ioctl_cmd.h>


#include <ioctl_cmd.h>
#include <ioctl_func.h>

#include <asm/tlbflush.h>
extern void flush_dcache_range(void *pMemory, unsigned int size);
///////////////////////////////////////////////////////////////////////////////////
// Module character device definitions
///////////////////////////////////////////////////////////////////////////////////
static struct class *oal_mem_cl;
static dev_t oal_mem_dev_main;
static struct cdev oal_mem_c_dev_main;
static struct vm_area_struct *oal_cma_vma;
///////////////////////////////////////////////////////////////////////////////////
// Main IOCTL function
///////////////////////////////////////////////////////////////////////////////////
static long oal_mem_device_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
  switch (cmd)
  {
    // Allocate a new contiguous region
    case CMD_ALLOC:
    {
      unsigned long size;
      unsigned long addr;
    
      if (copy_from_user(&size, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
      addr = oal_alloc(size);
    
      if (copy_to_user((unsigned long *)arg, &addr, sizeof(unsigned long)) != 0)
	return -EIO;
      return 0;
    }
    
    // Free unused contiguous region
    case CMD_FREE:
    {
      unsigned long addr;
    
      if (copy_from_user(&addr, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
    
      addr = oal_free(addr);
      if (copy_to_user((unsigned long *)arg, &addr, sizeof(unsigned long)) != 0)
	return -EIO;
      return 0;
    }
    
    // Get size of a region
    case CMD_SIZE:
    {
      unsigned long addr;
      unsigned long size;
    
      if (copy_from_user(&addr, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
    
      size = oal_getsize(addr);
      if (copy_to_user((unsigned long *)arg, &size, sizeof(unsigned long)) != 0)
	return -EIO;
    
      return 0;
    }
    
    // Return virtual mapping for this process
    case CMD_VIRTUAL:
    {
      unsigned long addr;
      if (copy_from_user(&addr, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
    
      addr = oal_getvirtual(addr);
      if (copy_to_user((unsigned long *)arg, &addr, sizeof(unsigned long)) != 0)
	return -EIO;
    
      return 0;
    }
    
    // Add virtual mapping to the management for this process
    case CMD_MAP:
    {
      t_MapStruct addr;
      unsigned long ret;
      if (copy_from_user(&addr, (t_MapStruct *)arg, sizeof(t_MapStruct)) != 0)
	return -EIO;
    
      ret = oal_map(addr);
    
      if (ret == 0)
      {
	addr.user_virtual = 0;
	addr.kernel_physical = 0;
	if (copy_to_user((t_MapStruct *)arg, &addr, sizeof(t_MapStruct)) != 0)
	  return -EIO;
      }
      return 0;
    }
    
    // Unmap virtual mapping from this process
    case CMD_UNMAP:
    {
      unsigned long addr;
      if (copy_from_user(&addr, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
    
      addr = oal_unmap(addr);
      if (copy_to_user((unsigned long *)arg, &addr, sizeof(unsigned long)) != 0)
	return -EIO;
        
      return 0;
    }
    
    // Return physical address based on the virtual one
    case CMD_PHYSICAL:
    {
      unsigned long addr;
      if (copy_from_user(&addr, (unsigned long *)arg, sizeof(unsigned long)) != 0)
	return -EIO;
      
      addr = oal_getphysical(addr);
      if (copy_to_user((unsigned long *)arg, &addr, sizeof(unsigned long)) != 0)
	return -EIO;
      return 0;
    }
    
    case CMD_RESET:
    {
      oal_reset();
      OAL_ContAllocDDRReset();
      return 0;
    }
    
    case CMD_FLUSH:
    {
      void * addr;
      CMD_FLUSH_TYPE aux;
      
      
      if (copy_from_user(&aux, (CMD_FLUSH_TYPE *)arg, sizeof(CMD_FLUSH_TYPE)) != 0)
	return -EIO;
      
      //addr = oal_getvirtual(aux.phys_ptr);
 
      addr = (void *)((unsigned long)aux.phys_ptr - OAL_DDR_PHYSICAL_POOL_BASE) + (unsigned long)aux.virt_base;
      //flush_cache_all();
      //flush_dcache_all();
      //printk("Flushing %p %p\n", OAL_ContAllocDDRGetBaseVirt(), OAL_ContAllocDDRGetBaseVirt()+0x5000000);
      //flush_cache_range(oal_cma_vma, OAL_ContAllocDDRGetBaseVirt(), OAL_ContAllocDDRGetBaseVirt()+0x5000000); 
      //flush_cache_range(oal_cma_vma, addr, aux.size);
      flush_dcache_range(addr, aux.size);
      //flush_tlb_all();
      //flush_cache_all();
      //printk("Flush cache on %p\n", addr);
      return 0;
    }  
    
    // NOOP
    default:
    {
      return -1;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// Memmap function
////////////////////////////////////////////////////////////////////////////////
static int oal_mem_mmap(struct file *filp, struct vm_area_struct *vma)
{  
  oal_cma_vma = vma;
  //vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
  if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
                vma->vm_end - vma->vm_start,
                vma->vm_page_prot))
        return -EAGAIN;

    return 0;

}

///////////////////////////////////////////////////////////////////////////////////
// FOPS definitions
///////////////////////////////////////////////////////////////////////////////////
static const struct file_operations oal_fops = {
	.owner =    THIS_MODULE,
	.unlocked_ioctl = oal_mem_device_ioctl,
	.mmap= 		  oal_mem_mmap,
};

///////////////////////////////////////////////////////////////////////////////////
// Init function - registers a char device
///////////////////////////////////////////////////////////////////////////////////
static int __init cma_test_init(void)
{
  if (alloc_chrdev_region(&oal_mem_dev_main, 0, 1, "oal_main") < 0)
	  goto fail_alloc_region_main;

  if ((oal_mem_cl = class_create(THIS_MODULE, "oal_chardrv")) == NULL)
	  goto fail_class_create_main;

  if (device_create(oal_mem_cl, NULL, oal_mem_dev_main, NULL, "oal") == NULL)
	  goto fail_device_create_main;

  cdev_init(&oal_mem_c_dev_main, &oal_fops);
  if (cdev_add(&oal_mem_c_dev_main, oal_mem_dev_main, 1) == -1)
	  goto fail_cdev_add_main;

	
  //OAL_ContAllocDDRInit();
  //printk("OAL Memory for allocation initialized on: %p.\n", (void *)OAL_ContAllocDDRGetBaseVirt());
	return 0;
	
  fail_cdev_add_main:
  device_destroy(oal_mem_cl, 0);
  fail_device_create_main:
  class_destroy(oal_mem_cl);
  fail_class_create_main:
  unregister_chrdev_region(0, 1);
  fail_alloc_region_main:
  return -1;
	
}
module_init(cma_test_init);

///////////////////////////////////////////////////////////////////////////////////
// Destructor function - frees all resources
///////////////////////////////////////////////////////////////////////////////////
static void __exit cma_exit(void)
{
  device_destroy(oal_mem_cl, 0);
  unregister_chrdev_region(0, 1);
  class_destroy(oal_mem_cl);
}

module_exit(cma_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rostislav Hulik <rostislav.hulik <at> freescale.com>");
MODULE_DESCRIPTION("OAL kernel module for contiguous memory allocations and its management.");
MODULE_ALIAS("oal");