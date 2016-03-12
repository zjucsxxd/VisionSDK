/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
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
/**
* \file Oal_memory.cpp
* \brief OAL memory allocation implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <standalone/oal_mspace.h>
#include <oal_cont_alloc.h>
#include <oal.h>

//#include <stdio.h>
/*****************************************************************************
* forward declarations
*****************************************************************************/

enum ContiguousMemoryFreeResult {
  OAL_CM_SUCCESS,
  OAL_CM_FAILURE,
  OAL_CM_NOT_CONTIGUOUS,
};

//#define uint32_t unsigned int
/****************************************************************************/
/** Allocates a physically contiguous memory.
*
* \param aSize size of the block to allocate
* \param aFlags OAL flags
*
* \return address of a successfully allocated data, NULL if not successfull
*
* \note physically contiguous memory in aFlags is not checked
*****************************************************************************/
static void* AllocateContiguousMemoryDDR(uint32_t aSize, OAL_MEMORY_FLAG aFlags);

/****************************************************************************/
/** Frees a memory allocated by AllocateContiguousMemory.
*
* \param aPtr pointer of a memory to be freed
*
* \return SUCCESS, FAILURE or NOT_CONTIGUOUS if the mmeory wasn't allocated
*         by AllocateContiguousMemory
*****************************************************************************/
static ContiguousMemoryFreeResult TryFreeContiguousMemory(void* aPtr);

/*****************************************************************************
* const
*****************************************************************************/

//TODO: really level 1 cache?
static const size_t CACHELINE_SIZE = 1;
static const size_t PAGE_SIZE = 1;

/*****************************************************************************
* functions
*****************************************************************************/

size_t AlignmentGet(OAL_MEMORY_FLAG aFlags)
{
  size_t ret = 0;

  if ((aFlags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)) ==
        OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE))
  {
    ret = CACHELINE_SIZE;
  }
  else if ((aFlags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE)) ==
      OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE))
  {
    ret = PAGE_SIZE;
  }
  else if ((aFlags & OAL_MEMORY_FLAG_ALIGN(BYTE_N)) ==
      OAL_MEMORY_FLAG_ALIGN(BYTE_N))
  {
    size_t alignment = (size_t)((aFlags & 0x00FF0000) >> 16);
    ret = alignment;
  }

  return ret;
}

#ifdef __cplusplus
extern "C" {
#endif

void *OAL_MemoryAllocFlag(uint32_t size, OAL_MEMORY_FLAG flags)
{
  void* ptr = AllocateContiguousMemoryDDR(size, flags);

  if ((ptr != 0) && (flags & OAL_MEMORY_FLAG_ZERO))
  {
    (void)memset(ptr, 0, size);
  }

  //printf("Allocated %x\n", ptr);
  return ptr;
}

void* OAL_MemoryAlloc(uint32_t size)
{
  return OAL_MemoryAllocFlag(size, 0);
}

void OAL_MemoryFree(void *pBuffer)
{
	//printf("Free %x\n", pBuffer);
  TryFreeContiguousMemory(pBuffer);
}

#ifdef __cplusplus
}
#endif

/*****************************************************************************
* contiguous memory
*****************************************************************************/


/****************************************************************************/
/** Returns a physical address corresponding to virtual address.
*
* \param p virtual pointer to search for
*
* \return physical address or NULL_ADDRESS if virtual pointer is not in range of
* the contiguous blocks
*****************************************************************************/
static inline unsigned long
  GetPhysicalAddress(void* ap)
{
  return (unsigned long)ap;
}

void* AllocateContiguousMemoryDDR(uint32_t aSize, OAL_MEMORY_FLAG aFlags)
{
   //alignment
  size_t alignment = AlignmentGet(aFlags);
  //always page-aligned
  if (alignment == 1 || alignment == PAGE_SIZE)
  {
    alignment = 0;
  }

  unsigned int mActualSize = alignment == 0 ? aSize : aSize + alignment - 1;
 
  return OAL_ContAllocDDRAlloc(mActualSize);
}

ContiguousMemoryFreeResult TryFreeContiguousMemory(void* aPtr)
{
  OAL_ContAllocDDRFree(aPtr);
  return OAL_CM_SUCCESS;
}

extern "C"
	{
     void flush_dcache_range(void *, unsigned int);	
	}
	
//CPU cache function
void CleanAndInvalidateDCacheByAddress(char *start, char *end)
{
	flush_dcache_range((void *)start, end - start);
}

//CPU cache function
void InvalidateDCacheByAddress(char *start, char *end)
{
	flush_dcache_range((void *)start, end - start);
}

//CPU cache function
void OAL_MemoryFlush(void *start, uint32_t size)
{
	flush_dcache_range((void *)start, size);
}

//CPU cache function
void OAL_MemoryFlushAndInvalidate(void *start, uint32_t size)
{
	flush_dcache_range((void *)start, size);
}

//CPU cache function
void OAL_MemoryInvalidate(void *start, uint32_t size)
{
	flush_dcache_range((void *)start, size);
}

//CPU cache function
void OAL_MemoryFlushAndInvalidateAll (void)
{
	flush_dcache_range((void *)0x80000000, 0x80000000);
}

#ifdef __cplusplus
extern "C" {
#endif

//works only for physical addresses allocated by contiguous allocator
void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access)
{
  return pBuffer;
}

void OAL_MemoryAllocReset()
{
}

#ifdef __cplusplus
}
#endif
