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
#include <oal_cont_alloc.h>

#include <oal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>
#include <struct_defs.h>
#include <ioctl_defs.h>
#include <ioctl_cmd.h>

#define MSPACES 1
#include <linux/oal_mspace.h>

bool 	ddr_init = false;
void *	ddr_base_virt = NULL;
mspace 	ddr_space;


unsigned long OAL_ContAllocDDRGetBaseVirt()
{
  return (unsigned long) ddr_base_virt;
}

LIB_RESULT OAL_MemoryAllocInit()
//void OAL_ContAllocDDRInit(unsigned long base, unsigned long size)
{
  //printf("Init OAL Start\n");
   int fd = open("/dev/oal", O_RDWR);
   if (fd < 0)
     return LIB_FAILURE;
   ddr_base_virt = mmap(0, OAL_DDR_PHYSICAL_POOL_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, OAL_DDR_PHYSICAL_POOL_BASE);
   
  //printf("DDR Space base virtual %X -> %p\n", OAL_DDR_PHYSICAL_POOL_BASE, ddr_base_virt);
   ddr_space = create_mspace_with_base(ddr_base_virt, OAL_DDR_PHYSICAL_POOL_SIZE, 0);
  
   ddr_init = true;
   
   close(fd);
   //printf("MSPACE created\n");
   return LIB_SUCCESS;
}


//CPU cache function
void CleanAndInvalidateDCache(void *pointer, int size)
{
	CMD_FLUSH_TYPE aux;
	aux.phys_ptr = pointer;
	aux.virt_base = ddr_base_virt;
	aux.size = size;
	
  int fd;
  fd = open("/dev/oal", O_RDWR);
   
  if (fd < 0) return;
  
  else if(ioctl(fd, CMD_FLUSH, &aux) < 0)
  {
    close(fd);
    return;
  }
  
  close(fd);
  return;
}

void *OAL_ContAllocDDRAlloc(unsigned long size)
{
  if (!ddr_init) return NULL;
  void *ptr = mspace_malloc(ddr_space, size);
  //printf ("Malloc of %d size on address %p\n", size, ptr);
  return ptr;
}

void OAL_ContAllocDDRFree(void * addr)
{
  if (!ddr_init) return;
  //printf ("Free on address %p\n", addr);
  mspace_free(ddr_space, addr);
}

///////////////////////////////////////////////////////////////////////////////////////
// Allocates physically contiguous region of specified size. 
// Returns HW address of the allocated memory or 0 if error.
// HW address works like identification.
///////////////////////////////////////////////////////////////////////////////////////
unsigned long OAL_ContAllocAllocPhysical(unsigned long size)
{
  /*int fd;
  fd = open("/dev/oal", O_RDWR);
   
  if (fd < 0)
    return NULL_ADDRESS;
  
  else if(ioctl(fd, CMD_ALLOC, &size) < 0)
  {
    close(fd);
    return NULL_ADDRESS;
  }
  
  close(fd);
  return size;*/
  
  if (!ddr_init) return 0;
  void *ptr = mspace_malloc(ddr_space, size);
  //printf ("Malloc of %d size on address %p (%X)\n", size, ptr, (unsigned long)ptr - (unsigned long)ddr_base_virt + OAL_DDR_PHYSICAL_POOL_BASE);
  return (unsigned long)ptr - (unsigned long)ddr_base_virt + OAL_DDR_PHYSICAL_POOL_BASE;
}

///////////////////////////////////////////////////////////////////////////////////////
// Frees physically contiguous region of specified size.
// Returns true on success, false otherwise.
// If mapping into user space exists, free function will fail. 
// The unmap function must preceede.
 ///////////////////////////////////////////////////////////////////////////////////////
bool OAL_ContAllocFreePhysical(unsigned long kernel_physical)
{
  /*int fd;
  fd = open("/dev/oal", O_RDWR);
  
  if (fd < 0)
    return false;
  else if(ioctl(fd, CMD_FREE, &kernel_physical) < 0)
  {
    close(fd);
    return false;
  }
  
  close(fd);
  
  if (kernel_physical == 0)
    return true;  
  else
    return false;*/
  if (!ddr_init) return false;
  //printf ("Free on address %X (%p)\n", kernel_physical, (void*)(kernel_physical - OAL_DDR_PHYSICAL_POOL_BASE + (unsigned long)ddr_base_virt));
  mspace_free(ddr_space, (void*)(kernel_physical - OAL_DDR_PHYSICAL_POOL_BASE + (unsigned long)ddr_base_virt));
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////
// Returns HW addresses mapping into user space (i.e. user virtual address).
// If mapping does not exist, it's created. returns address on success, NULL otherwise.
 ///////////////////////////////////////////////////////////////////////////////////////
void *OAL_ContAllocGetVirtual(unsigned long kernel_physical)
{
  return (void *)(kernel_physical - OAL_DDR_PHYSICAL_POOL_BASE + (unsigned long)ddr_base_virt);
  /*int fd;
  unsigned long aux = kernel_physical;
  fd = open("/dev/oal", O_RDWR);
   
  // Get existing virtual address
  if (fd < 0)
    return NULL;
  else if(ioctl(fd, CMD_VIRTUAL, &aux) < 0)
  {
    close(fd);
    return NULL;
  }
 	
  // If there is no existing address, create new mapping
  if (aux == 0)
  {
    // Get size for mmap
    aux = kernel_physical;
    
    if(ioctl(fd, CMD_SIZE, &aux) < 0)
    {
      close(fd);
      return NULL;
    }
    
    // If ok
    if (kernel_physical > 0)
    {
      void *vadr = mmap(0, aux, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, kernel_physical);

    
      // If successfully mapped, we need add it to the map list
      if (vadr)
      {
	// Create an input structure and open file
	t_MapStruct map;
	map.kernel_physical = kernel_physical;
	map.user_virtual = (unsigned long) vadr;
	
	// Test insert
	if(ioctl(fd, CMD_MAP, &map) < 0)
	{
	  munmap(vadr, aux);
	  close(fd);
	  return NULL;
	}
      
	// If all ok, we return virtual address
	if (map.user_virtual)
	{
	  close(fd);
	  return (void *)map.user_virtual;
	}
	else
	{
	  munmap(vadr, aux);
	}
	close(fd);
	return vadr;
      } // if vaddr
      else 
      {
	close(fd);
	return NULL;
      }
    } // if size > 0
    else
    {
      close(fd);
      return NULL;
    }
  } // if virtual exists
  else
  {
    close(fd);
    return (void *)aux;
  }
  */
}

///////////////////////////////////////////////////////////////////////////////////////
// Returns HW address from user space virtual address
// If mapping does not exist, function returns NULL_ADDRESS.
///////////////////////////////////////////////////////////////////////////////////////
unsigned long OAL_ContAllocGetPhysical(void * user_virtual)
{
  return (unsigned long)user_virtual - (unsigned long)ddr_base_virt + OAL_DDR_PHYSICAL_POOL_BASE;
  /*int fd;
  fd = open("/dev/oal", O_RDWR);
  
  unsigned long address = (unsigned long)user_virtual;
  if (fd < 0)
    return false;
  else if(ioctl(fd, CMD_PHYSICAL, &address) < 0)
  {
    close(fd);
    return false;
  }
      
  close(fd);
  
  if (address == 0)
    return NULL_ADDRESS;  
  else
    return address;*/
}

void OAL_MemoryAllocReset()
{
  int fd;
  fd = open("/dev/oal", O_RDWR);
  
  if (fd >= 0)
  {  
    if(ioctl(fd, CMD_RESET, NULL) < 0)
    {
      close(fd);
    }
  } 
  close(fd);
}

///////////////////////////////////////////////////////////////////////////////////////
// Unmaps use space mapping of specified HW address for current process. 
// Unmapping is possible only for current process. If other mapping exists, owner processes must free it.
// Returns true on success, false otherwise.
///////////////////////////////////////////////////////////////////////////////////////
bool OAL_ContAllocUnmapVirtual(unsigned long kernel_physical)
{
  /*int fd;
  unsigned long aux = kernel_physical;
  fd = open("/dev/oal", O_RDWR);

  if (fd < 0)
    return false;

  // Get mapped size
  unsigned long size = kernel_physical;
  if(ioctl(fd, CMD_SIZE, &size) < 0)
  {
    close(fd);
    return false;
  }
  
  // Get virtual address
  if(ioctl(fd, CMD_VIRTUAL, &aux) < 0)
  {
    close(fd);
    return false;
  }
 
  // Do unmapping
  if (aux > 0) munmap((void *)aux, size);
    
  if(ioctl(fd, CMD_UNMAP, &kernel_physical) < 0)
  {
    close(fd);
    return false;
  }
  
  close(fd);*/
  return true;
}
