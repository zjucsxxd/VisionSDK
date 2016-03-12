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
* \file Oal_memorypool.cpp
* \brief OAL memory pool implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <linux/oal_linux.h>
#include <vector>
#include <pthread.h>

/*****************************************************************************
* types
*****************************************************************************/

//type of the free map elements
//unsigned int should be the most "natural" size
typedef unsigned int memPool_FMt;
//fully occupied element
const memPool_FMt fully_occupied = 0xffffffff;
const size_t MEMPOOL_FMT_BITCOUNT = sizeof(memPool_FMt) * 8;

/****************************************************************************/
/** Linux-specific memory pool type hidden by the OAL_MEM_POOL
*****************************************************************************/
struct memPool_s
{
  private:
    void* mpMem;
    uint32_t mSize;
    //for alignment
    uint32_t mRealSize;
    uint32_t mCount;

    //map of the free blocks, works on a bit basis... 0 free, 1 not free
    memPool_FMt* mFreeMap;
    unsigned int mFreeMapSize;
    bool mDeleteWhenFree;

    memPool_s( const memPool_s& );            // Do not implement
    memPool_s& operator=( const memPool_s& ); // Do not implement

    /************************************************************************/
    /** Gets the index of a free block.
    *
    * \return index of the free block, -1 if no block is free
    *************************************************************************/
    int GetFreeIndex() const;

    /************************************************************************/
    /** Marks the block as free / occupied.
    *
    * \param index index of the block
    * \param value false if occupied, true if free
    *
    * \note the index is not checked against the freeMap range
    *************************************************************************/
    void SetIndex(int aIndex, bool aValue);
  public:
    /************************************************************************/
    /** Constructs the memory pool.
    *
    * \param apMem pointer to allocated memory
    * \param aSize block size
    * \param aRealSize "real" block size (for alignment purposes)
    * \param aCount number of blocks
    *
    * \note from now on the object manages the pMem! ugly but needed...
    *************************************************************************/
    memPool_s(
      void* apMem, uint32_t aSize, uint32_t aRealSize,uint32_t aCount);

    /************************************************************************/
    /** Destructs the memory pool.
    *************************************************************************/
    ~memPool_s();

    /************************************************************************/
    /** Translates the errno to OAL file error.
    *
    * \return true if all blocks free, false otherwise
    *************************************************************************/
    bool IsCompletelyFree() const;

    /************************************************************************/
    /** Sets whether the pool should be automatically deleted when free.
    *************************************************************************/
    void DeleteWhenFree()
    {
      mDeleteWhenFree = true;
    }

    bool ShouldBeDeletedWhenFree() const
    {
      return mDeleteWhenFree;
    }

    /************************************************************************/
    /** Allocates one block, returns NULL if no free space is left.
    *************************************************************************/
    void* MemoryAllocate();

    /************************************************************************/
    /** Frees one block.
    *
    * \param p pointer to the block
    *************************************************************************/
    void MemoryFree(void* ap);

    /************************************************************************/
    /** Is the address in this pool's range?
    *
    * \param p address to check
    *************************************************************************/
    bool IsAddressInRange(const void* ap) const
    {
      return ((unsigned long)ap >= (unsigned long)mpMem) &&
          ((unsigned long)ap < ((unsigned long)mpMem + mCount * mRealSize));
    }
};

/*****************************************************************************
* local functions
*****************************************************************************/

memPool_s::memPool_s(void* apMem, uint32_t aSize, uint32_t aRealSize,
uint32_t aCount):
    mpMem(apMem),
    mSize(aSize),
    mRealSize(aRealSize),
    mCount(aCount),
    mFreeMap(0),
    mFreeMapSize(0),
    mDeleteWhenFree(false)
{
  //prepare the map of the free blocks
  mFreeMapSize = aCount / MEMPOOL_FMT_BITCOUNT;
  if (aCount % MEMPOOL_FMT_BITCOUNT)
  {
    ++mFreeMapSize;
  }
  mFreeMap = new memPool_FMt[mFreeMapSize];
  for (unsigned int i = 0; i < mFreeMapSize; ++i)
  {
    mFreeMap[i] = 0;
  }
}

memPool_s::~memPool_s()
{
  delete[] mFreeMap;
  OAL_MemoryFree(mpMem);
  mpMem = NULL;
}

bool memPool_s::IsCompletelyFree() const
{
  bool ret = true;

  for (unsigned int i = 0; i < mFreeMapSize; ++i)
  {
    if(mFreeMap[i])
    {
      ret = false;
      break;
    }
  }

  return ret;
}

/************************************************************************/
/** Integer minimum.
*
* \param aA
* \param aB
*
* \return min(a, b)
*************************************************************************/
static inline int MinInt(int aA, int aB)
{
  return aA < aB ? aA : aB;
}

int memPool_s::GetFreeIndex() const
{
  int ret = -1;

  for (unsigned int i = 0; i < mFreeMapSize; ++i)
  {
    if (mFreeMap[i] == fully_occupied) continue;
    int limit = MinInt(int(MEMPOOL_FMT_BITCOUNT),
        int(mCount - (i * MEMPOOL_FMT_BITCOUNT)));
    for (unsigned int j = 0; j < (unsigned int)limit; ++j)
    {
      if (!(mFreeMap[i] & ((memPool_FMt)0x1 << (memPool_FMt)j)))
      {
        ret = int(i * MEMPOOL_FMT_BITCOUNT + j);
        break;
      }
    }
  }

  return ret;
}

void memPool_s::SetIndex(int aIndex, bool aValue)
{
  int fmi = aIndex / int(MEMPOOL_FMT_BITCOUNT);
  int bi = aIndex - (fmi * int(MEMPOOL_FMT_BITCOUNT));

  if (aValue)
  {
    mFreeMap[fmi] |= (memPool_FMt)0x1 << (memPool_FMt)bi;
  }
  else
  {
    mFreeMap[fmi] &= ~((memPool_FMt)0x1 << (memPool_FMt)bi);
  }
}

void* memPool_s::MemoryAllocate()
{
  int freeIndex = GetFreeIndex();

  void* ret = NULL;
  if (freeIndex >= 0)
  {
    SetIndex(freeIndex, true);
    ret = (void*)((unsigned long)mpMem + freeIndex * mRealSize);
  }

  return ret;
}

void memPool_s::MemoryFree(void* ap)
{
  unsigned long uipMem = (unsigned long)mpMem;
  unsigned long uip = (unsigned long)ap;
  if (uip >= uipMem)
  {
    unsigned long offset = uip - uipMem;
    if ((offset % mRealSize) == 0)
    {
      int indexToSet = offset / mRealSize;

      SetIndex(indexToSet, false);
    }
  }
}

/****************************************************************************/
/** Vector of all pools. Needed for freeing the blocks without specifying
* the pool. Guarded by mutex.
*****************************************************************************/
struct MemoryPoolRegister
{
  std::vector<OAL_MEM_POOL> mRegister;
  pthread_mutex_t mMutex;

  MemoryPoolRegister();
  ~MemoryPoolRegister()
  {
    pthread_mutex_destroy(&mMutex);
  }
};

MemoryPoolRegister::MemoryPoolRegister()
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

static MemoryPoolRegister gMemoryPools;

/****************************************************************************/
/** Registers the pool (into the vector).
*
* \param mp aPool the pool to be registered
*****************************************************************************/
static inline void MemoryPoolRegisterFunc(const OAL_MEM_POOL aPool)
{
  pthread_mutex_lock(&gMemoryPools.mMutex);

  bool addNewPool = true;

  for (unsigned int i = 0; i < gMemoryPools.mRegister.size(); ++i)
  {
    if (!gMemoryPools.mRegister[i])
    {
      gMemoryPools.mRegister[i] = aPool;
      addNewPool = false;
      break;
    }
  }

  if (addNewPool)
  {
    gMemoryPools.mRegister.push_back(aPool);
  }

  pthread_mutex_unlock(&gMemoryPools.mMutex);
}

/****************************************************************************/
/** Unregisters the pool (from the vector).
*
* \param aPool the pool to be registered
*****************************************************************************/
static inline void MemoryPoolUnregister(const OAL_MEM_POOL aPool)
{
  pthread_mutex_lock(&gMemoryPools.mMutex);

  for (unsigned int i = 0; i < gMemoryPools.mRegister.size(); ++i)
  {
    if (gMemoryPools.mRegister[i] == aPool)
    {
      gMemoryPools.mRegister[i] = 0;
    }
  }

  pthread_mutex_unlock(&gMemoryPools.mMutex);
}

/****************************************************************************/
/** Returns the memory pool whose range contains the pointer
* (using the vector).
*
* \param ap a pointer to search for
*
* \return the pool containing the pointer or NULL when no such pool found
*****************************************************************************/
static inline OAL_MEM_POOL MemoryPoolFindByPointer(const void* ap)
{
  pthread_mutex_lock(&gMemoryPools.mMutex);

  OAL_MEM_POOL ret = NULL;

  for (unsigned int i = 0; i < gMemoryPools.mRegister.size(); ++i)
  {
    if (gMemoryPools.mRegister[i] &&
      gMemoryPools.mRegister[i]->IsAddressInRange(ap))
    {
      ret = gMemoryPools.mRegister[i];
      break;
    }
  }

  pthread_mutex_unlock(&gMemoryPools.mMutex);

  return ret;
}

/****************************************************************************/
/** Deletes and unregisters the pool.
*
* \param aPool a pool to unregister and delete
*****************************************************************************/
static inline void MemoryPoolDeleteAndUnregister(OAL_MEM_POOL aPool)
{
  MemoryPoolUnregister(aPool);
  delete aPool;
}

#ifdef __cplusplus
extern "C" {
#endif

OAL_MEM_POOL OAL_MemoryPoolCreate (uint32_t size,
                                   uint32_t count,
                                   OAL_MEMORY_FLAG flags)
{
  uint32_t realSize = size;
  size_t alignment = AlignmentGet(flags);
  //TODO: should be implemented this way? makes sense...
  if (alignment && (size % alignment))
  {
    realSize += alignment - size % alignment;
  }

  OAL_MEM_POOL mp = NULL;

  void* pMem = OAL_MemoryAllocFlag(realSize * count, flags);
  if (pMem)
  {
    mp = new memPool_s(pMem, size, realSize, count);
    MemoryPoolRegisterFunc(mp);
  }
  return mp;
}

void OAL_MemoryPoolDestroy (OAL_MEM_POOL pool)
{
  if (pool->IsCompletelyFree())
  {
    MemoryPoolDeleteAndUnregister(pool);
  }
  else
  {
    pool->DeleteWhenFree();
  }
}

void* OAL_MemoryPoolAlloc (OAL_MEM_POOL pool)
{
  void* ret = NULL;
  if (!pool->ShouldBeDeletedWhenFree())
  {
    ret = pool->MemoryAllocate();
  }
  return ret;
}

void OAL_MemoryPoolFree(void *pMem)
{
  OAL_MEM_POOL pool = MemoryPoolFindByPointer(pMem);
  if (pool)
  {
    pool->MemoryFree(pMem);
    //delete if should be deleted and is free already
    if (pool->ShouldBeDeletedWhenFree() && pool->IsCompletelyFree())
    {
      MemoryPoolDeleteAndUnregister(pool);
    }
  }
}

#ifdef __cplusplus
}
#endif

