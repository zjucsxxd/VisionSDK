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

#include <linux/oal_linux.h>
#include <sys/mman.h>
#include <unistd.h>
#include <oal_cont_alloc.h>
#include <vector>
#include <pthread.h>

#include <stdio.h>
/*****************************************************************************
* forward declarations
*****************************************************************************/

enum ContiguousMemoryFreeResult {
  OAL_CM_SUCCESS,
  OAL_CM_FAILURE,
  OAL_CM_NOT_CONTIGUOUS,
};

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
static void* AllocateContiguousMemory(uint32_t aSize, OAL_MEMORY_FLAG aFlags);
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
static const size_t CACHELINE_SIZE =
    (size_t)sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
static const size_t PAGE_SIZE = (size_t)sysconf(_SC_PAGESIZE);

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
//don't use contiguous memory on desktop
#ifndef ARM
  flags &= ~OAL_MEMORY_FLAG_CONTIGUOUS;
#endif
  void* ptr = NULL;

  if (flags & OAL_MEMORY_FLAG_CONTIGUOUS_CMA)
  {
    ptr = AllocateContiguousMemory(size, flags);
  }
  else if (flags & OAL_MEMORY_FLAG_CONTIGUOUS)
  {
    ptr = AllocateContiguousMemory(size, flags);
  }
  else
  {
    //TODO: handle the size = 0 case?

    //TODO: handle conflicting flags?
    //TODO: restrictions on POSIX_memalign?
    size_t alignment = AlignmentGet(flags);
    if (alignment)
    {
      if (posix_memalign(&ptr, alignment, size))
      {
        ptr = NULL;
      }
    }
    else
    {
      ptr = malloc(size);
    }

    if (ptr != NULL)
    {
      if (flags & OAL_MEMORY_FLAG_NONSWAPABLE)
      {
        //TODO: ignore/fail?
        if (mlock(ptr, size) < 0)
        {
          free(ptr);
          ptr = NULL;
        }
      }
    }
  }

  if ((ptr != NULL) && (flags & OAL_MEMORY_FLAG_ZERO))
  {
    (void)memset(ptr, 0, size);
  }

  return ptr;
}

void* OAL_MemoryAlloc(uint32_t size)
{
  return OAL_MemoryAllocFlag(size, 0);
}

void OAL_MemoryFree(void *pBuffer)
{
	if (pBuffer)
  if (TryFreeContiguousMemory(pBuffer) == OAL_CM_NOT_CONTIGUOUS)
  {
    free(pBuffer);
  }
}

#ifdef __cplusplus
}
#endif

/*****************************************************************************
* contiguous memory
*****************************************************************************/

typedef enum {MEMORY_CMA, MEMORY_DDR} CONT_MEMORY_TYPE;
struct ContiguousMemoryBlock
{
  unsigned long mBasePhysicalAddress;
  unsigned long mAlignedPhysicalAddress;
  void* mpBaseVirtualPointer;
  void* mAlignedVirtualPointer;
  //from base, not from aligned
  unsigned long mActualSize;
  CONT_MEMORY_TYPE mType;

  void Invalidate()
  {
    mBasePhysicalAddress = NULL_ADDRESS;
  }

  bool IsValid()
  {
    return mBasePhysicalAddress != NULL_ADDRESS;
  }
};

struct CMBRegister
{
  //TODO: use map/unordered map instead? They have worse memory patterns...
  std::vector<ContiguousMemoryBlock> mRegister;
  pthread_mutex_t mMutex;

  CMBRegister();
  ~CMBRegister()
  {
    pthread_mutex_destroy(&mMutex);
  }
};

CMBRegister::CMBRegister()
{
  pthread_mutexattr_t attr;
  bool ok = true;
  ok = ok && (pthread_mutexattr_init(&attr) == 0);
  ok = ok &&
    (pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST) == 0);
  if (ok && pthread_mutex_init(&mMutex, &attr))
  {
    //TODO: how to handle the error?
  }
  (void)pthread_mutexattr_destroy(&attr);
}

static CMBRegister gCMBRegister;

/****************************************************************************/
/** Registers a contiguous memory block.
*
* \param acrBlock block to register
*****************************************************************************/

static inline void
  RegisterContiguousMemoryBlock(const ContiguousMemoryBlock& acrBlock)
{
  pthread_mutex_lock(&gCMBRegister.mMutex);

  bool done = false;
  for (unsigned int i = 0; i < gCMBRegister.mRegister.size(); ++i)
  {
    if (!gCMBRegister.mRegister[i].IsValid())
    {
      gCMBRegister.mRegister[i] = acrBlock;
      done = true;
      break;
    }
  }
  if (!done)
  {
    gCMBRegister.mRegister.push_back(acrBlock);
  }

  pthread_mutex_unlock(&gCMBRegister.mMutex);
}

/****************************************************************************/
/** Finds and unregisters a contiguous memory block.
*
* \param arOut unregistered block
* \param p virtual pointer to search for
*
* \return false if and only if the block was not registered
*****************************************************************************/
static inline bool
  FindAndUnregisterContiguousMemoryBlockByPointer(
      ContiguousMemoryBlock &arOut, void* ap)
{
  pthread_mutex_lock(&gCMBRegister.mMutex);

  bool ret = false;
  for (unsigned int i = 0; i < gCMBRegister.mRegister.size(); ++i)
  {
    if (gCMBRegister.mRegister[i].IsValid() &&
      gCMBRegister.mRegister[i].mAlignedVirtualPointer == ap)
    {
      arOut = gCMBRegister.mRegister[i];
      gCMBRegister.mRegister[i].Invalidate();
      ret = true;
      break;
    }
  }

  pthread_mutex_unlock(&gCMBRegister.mMutex);

  return ret;
}

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
  pthread_mutex_lock(&gCMBRegister.mMutex);

  unsigned long ret = NULL_ADDRESS;
  unsigned long iP = (unsigned long)ap;
  for (unsigned int i = 0; i < gCMBRegister.mRegister.size(); ++i)
  {
    if (gCMBRegister.mRegister[i].IsValid())
    {
      unsigned long start =
          (unsigned long) gCMBRegister.mRegister[i].mpBaseVirtualPointer;
      unsigned long end = start +
                (unsigned long) gCMBRegister.mRegister[i].mActualSize;
      if (iP >= start && iP < end)
      {
        ret = gCMBRegister.mRegister[i].mBasePhysicalAddress + (iP - start);
        break;
      }
    }
  }

  pthread_mutex_unlock(&gCMBRegister.mMutex);

  return ret;
}

static inline void *
  GetVirtualAddress(unsigned long aPhysical)
{
  pthread_mutex_lock(&gCMBRegister.mMutex);

  void* lpRet = NULL;
  
  for (unsigned int i = 0; i < gCMBRegister.mRegister.size(); ++i)
  {
    if (gCMBRegister.mRegister[i].IsValid())
    {
      unsigned long start =
          (unsigned long) gCMBRegister.mRegister[i].mBasePhysicalAddress;
      unsigned long end = start +
                (unsigned long) gCMBRegister.mRegister[i].mActualSize;
      if (aPhysical >= start && aPhysical < end)
      {
        lpRet = (void*)((uintptr_t)(gCMBRegister.mRegister[i].mpBaseVirtualPointer)\
               + (aPhysical - start));
        break;
      }
    }
  }

  pthread_mutex_unlock(&gCMBRegister.mMutex);

  return lpRet;
}

void* AllocateContiguousMemory(uint32_t aSize, OAL_MEMORY_FLAG aFlags)
{
  ContiguousMemoryBlock block;

  void* ret = NULL;

  //alignment
  size_t alignment = AlignmentGet(aFlags);
  //always page-aligned
  if (alignment == 1 || alignment == PAGE_SIZE)
  {
    alignment = 0;
  }

  block.mActualSize = alignment == 0 ? aSize : aSize + alignment - 1;
  block.mBasePhysicalAddress = OAL_ContAllocAllocPhysical(block.mActualSize);
  if (block.mBasePhysicalAddress != NULL_ADDRESS)
  {
    block.mpBaseVirtualPointer = OAL_ContAllocGetVirtual(block.mBasePhysicalAddress);
    
    size_t alignment_pad = alignment == 0 ? 0 : (alignment - (block.mBasePhysicalAddress % alignment)) % alignment;

    block.mAlignedPhysicalAddress = block.mBasePhysicalAddress + alignment_pad;
    
    block.mAlignedVirtualPointer = (void*)((unsigned long)block.mpBaseVirtualPointer + alignment_pad);

    block.mType = MEMORY_CMA;
    RegisterContiguousMemoryBlock(block);

    ret = block.mAlignedVirtualPointer;
  }

  return ret;
}
#include <iostream>
void* AllocateContiguousMemoryDDR(uint32_t aSize, OAL_MEMORY_FLAG aFlags)
{
  ContiguousMemoryBlock block;

  void* ret = NULL;

  //alignment
  size_t alignment = AlignmentGet(aFlags);
  //always page-aligned
  if (alignment == 1 || alignment == PAGE_SIZE)
  {
    alignment = 0;
  }

  block.mActualSize = alignment == 0 ? aSize : aSize + alignment - 1;
  block.mpBaseVirtualPointer = OAL_ContAllocDDRAlloc(block.mActualSize);
  if (block.mpBaseVirtualPointer != NULL)
  {
    block.mBasePhysicalAddress = OAL_DDR_PHYSICAL_POOL_BASE + (unsigned long)block.mpBaseVirtualPointer - OAL_ContAllocDDRGetBaseVirt();
    
    size_t alignment_pad = alignment == 0 ? 0 : (alignment - (block.mBasePhysicalAddress % alignment)) % alignment;
    

    block.mAlignedPhysicalAddress = block.mBasePhysicalAddress + alignment_pad;
    
    block.mAlignedVirtualPointer = (void*)((unsigned long)block.mpBaseVirtualPointer + alignment_pad);

    block.mType = MEMORY_DDR;
    
    RegisterContiguousMemoryBlock(block);

    ret = block.mAlignedVirtualPointer;
  }
  return ret;
}

ContiguousMemoryFreeResult TryFreeContiguousMemory(void* aPtr)
{
  //TODO: should use a semaphore!
  ContiguousMemoryFreeResult ret = OAL_CM_NOT_CONTIGUOUS;

  ContiguousMemoryBlock block;
  if (FindAndUnregisterContiguousMemoryBlockByPointer(block, aPtr))
  {
    ret = OAL_CM_SUCCESS;
    if (block.mType == MEMORY_CMA)
    {
      if (!OAL_ContAllocUnmapVirtual(block.mBasePhysicalAddress))
      {
	ret = OAL_CM_FAILURE;
      }
      if (!OAL_ContAllocFreePhysical(block.mBasePhysicalAddress))
      {
	ret = OAL_CM_FAILURE;
      }
    }
    else if (block.mType == MEMORY_DDR)
    {
      if (!OAL_ContAllocUnmapVirtual(block.mBasePhysicalAddress))
      {
	ret = OAL_CM_FAILURE;
      }
      if (!OAL_ContAllocFreePhysical(block.mBasePhysicalAddress))
      {
	ret = OAL_CM_FAILURE;
      }
    }
    else 
      ret = OAL_CM_FAILURE;
  }

  return ret;
}

//CPU cache function
void CleanAndInvalidateDCacheByAddress(char *, char *)
{
	//CleanAndInvalidateDCacheAll();
}

//CPU cache function
void InvalidateDCacheByAddress(char *, char *)
{
	//CleanAndInvalidateDCacheAll();
}

//CPU cache function
void OAL_MemoryFlush(void *, uint32_t)
{
	//CleanAndInvalidateDCacheAll();
}

//CPU cache function
void OAL_MemoryFlushAndInvalidate(void * addr, uint32_t size)
{
	CleanAndInvalidateDCache(addr, size);
}

//CPU cache function
void OAL_MemoryInvalidate(void *, uint32_t)
{
	//CleanAndInvalidateDCacheAll();
}

//CPU cache function
void OAL_MemoryFlushAndInvalidateAll (void)
{
	//CleanAndInvalidateDCacheAll();
}


#ifdef __cplusplus
extern "C" {
#endif

//works only for physical addresses allocated by contiguous allocator
void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access)
{
  void* ret = NULL;

  if (access == ACCESS_PHY)
  {
    ret = (void*)OAL_ContAllocGetPhysical(pBuffer);
  }
  else 
  {
    ret = OAL_ContAllocGetVirtual((unsigned long) pBuffer);
    
  }

  return ret;
}


#ifdef __cplusplus
}
#endif
