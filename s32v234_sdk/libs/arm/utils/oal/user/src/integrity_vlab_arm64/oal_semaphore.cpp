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
* \file Oal_semaphore.cpp
* \brief OAL semaphore implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include "oal_integrity.h"
#include <oal_extras.h>
#include <ctime>
#include <semaphore.h>
#include <cerrno>
#include <fcntl.h>
#include <pthread.h>
#include <new>

/*****************************************************************************
* types
*****************************************************************************/

/****************************************************************************/
/** Linux-specific semaphore type hidden by the OAL_SEMAPHORE
*****************************************************************************/
struct tOalSemaphore
{
  char mName[8];
  //with the slash
  char mLinuxName[9];
  bool mIsMutex;
  //POSIX semaphore
  sem_t* mSemaphore;
  //POSIX mutex
  pthread_mutex_t mMutex;
  //POSIX indirect mutex (e.g. in shared memory)
  pthread_mutex_t* mIndirectMutex;
  // is this process responsible for unlink?
  bool mOwnership;
  // semaphores created by placement new should NOT be deleted
  bool mIsIndirect;

  /************************************************************************/
  /** Simple constructor.
  *************************************************************************/
  tOalSemaphore():
    mIsMutex(false),
    mSemaphore(NULL),
    mIndirectMutex(NULL),
    mOwnership(false),
    mIsIndirect(false)
  {
    (void)memset(mName, 0, 8);
    (void)memset(mLinuxName, 0, 9);
  }
};

const size_t SEMAPHORE_STRUCT_SIZE = sizeof(pthread_mutex_t);

/*****************************************************************************
* local functions
*****************************************************************************/

/****************************************************************************/
/** Translates the errno to OAL semaphore error.
*
* \return OAL semaphore error
*
* \todo may be not complete
*****************************************************************************/
static LIB_RESULT SemaphoreErrorTranslate()
{
  LIB_RESULT ret = LIB_FAILURE;

  switch(errno)
  {
    //TODO: ENFILE + EMFILE?
    case ENOMEM:
      ret = OAL_ERR_SEM_ENOMEM;
      break;
    case EINVAL:
    case ENOENT:
      ret = OAL_ERR_SEM_EBADSEM;
      break;
    case EBUSY:
    case EAGAIN:
      ret = OAL_ERR_SEM_ESEMLOCKED;
      break;
    case ETIMEDOUT:
      ret = OAL_ERR_SEM_ETIMEOUT;
      break;
    default:
      break;
  }

  return ret;
}

/****************************************************************************/
/** Gets a pointer to sem_t from OAL_SEMAPHORE.
*
* \param aOS OAL_SEMAPHORE
*
* \return pointer to sem_t*
*****************************************************************************/
static inline sem_t* PSGetFromOALS(const OAL_SEMAPHORE aOS)
{
  return aOS->mSemaphore;
}

/****************************************************************************/
/** Gets a pointer to pthread_mutex_t from OAL_SEMAPHORE.
*
* \param aOS OAL_SEMAPHORE
*
* \return pointer to pthread_mutex_t*
*****************************************************************************/
static inline pthread_mutex_t* PMGetFromOALS(const OAL_SEMAPHORE aOS)
{
  return aOS->mIsIndirect ? aOS->mIndirectMutex : &aOS->mMutex;
}

/****************************************************************************/
/** Is the OAL_SEMAPHORE a mutex?
*
* \param aOS OAL_SEMAPHORE
*
* \return true iff OAL_SEMAPHORE is a mutex
*****************************************************************************/
static inline bool IsMutex(const OAL_SEMAPHORE aOS)
{
  return aOS->mIsMutex;
}

/*****************************************************************************
* functions
*****************************************************************************/

void LinuxNameTruncate7(char* apOutName, char *apOutLinuxName,
    const char* apcInName)
{
  (void)memset((void*) apOutName, 0, 8);
  (void)memset((void*) apOutLinuxName, 0, 9);
  apOutLinuxName[0] = '/';
  (void)strncpy(&(apOutLinuxName[1]), apcInName, 7);
  (void)strncpy(apOutName, apcInName, 7);
}

#ifdef __cplusplus
extern "C" {
#endif

LIB_RESULT OAL_SemaphoreCreate(OAL_SEMAPHORE *pSem,
    const char *pName, OAL_SEMAPHORE_TYPE type, unsigned int count)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if ((!pSem) || (type == OAL_SEMAPHORE_INVALID))
  {
    ret = OAL_ERR_SEM_EBADTYPE;
  }
  else
  {
    *pSem = 0;
    tOalSemaphore* tos = new tOalSemaphore();

    LinuxNameTruncate7(tos->mName, tos->mLinuxName, pName);

    if (type == OAL_SEMAPHORE_BINARY || type == OAL_SEMAPHORE_MUTEX)
    {
      count = 1;
    }

    if (type == OAL_SEMAPHORE_MUTEX)
    {
      tos->mIsMutex = true;
      pthread_mutexattr_t attr;
      bool ok = true;
      ok = ok && (pthread_mutexattr_init(&attr) == 0);
      
      if (ok && pthread_mutex_init(&tos->mMutex, &attr))
      {
        delete tos;
        tos = NULL;
        ret = SemaphoreErrorTranslate();
      }

      (void)pthread_mutexattr_destroy(&attr);
    }
    else
    {
      tos->mIsMutex = false;
      int oflag = O_RDWR | O_CREAT | O_EXCL;
      int mode = 6+6+6;//S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
      sem_t* sem = sem_open(tos->mLinuxName, oflag, mode, count);
      if (!sem)
      {
        delete tos;
        tos = NULL;
        ret = SemaphoreErrorTranslate();
      }
      else
      {
        tos->mSemaphore = sem;
      }
    }

    if (ret == LIB_SUCCESS && tos)
    {
      tos->mOwnership = true;
      *pSem = tos;
    }
  }

  return ret;
}

LIB_RESULT OAL_SemaphoreGetByName(OAL_SEMAPHORE *apSem, const char *apName)
{
  LIB_RESULT ret = LIB_SUCCESS;

  tOalSemaphore* tos = new tOalSemaphore();

  LinuxNameTruncate7(tos->mName, tos->mLinuxName, apName);

  tos->mIsMutex = false;
  int oflag = O_RDWR;
  sem_t* sem = sem_open(tos->mLinuxName, oflag, 0, 0);
  if (!sem)
  {
    delete tos;
    ret =  SemaphoreErrorTranslate();
  }
  else
  {
    tos->mSemaphore = sem;

    tos->mOwnership = false;
    *apSem = tos;
  }

  return ret;
}

LIB_RESULT OAL_SemaphoreObtain(OAL_SEMAPHORE sem)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (!sem)
  {
    ret = OAL_ERR_SEM_EBADSEM;
  }
  else if (IsMutex(sem))
  {
    if (pthread_mutex_lock(PMGetFromOALS(sem)))
    {
      ret = SemaphoreErrorTranslate();
    }
  }
  else
  {
    if (sem_wait(PSGetFromOALS(sem)))
    {
      ret = SemaphoreErrorTranslate();
    }
  }

  return ret;
}

LIB_RESULT OAL_SemaphoreTryObtain(OAL_SEMAPHORE sem)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (!sem)
  {
    ret = OAL_ERR_SEM_EBADSEM;
  }
  else if (IsMutex(sem))
  {
    if (pthread_mutex_trylock(PMGetFromOALS(sem)))
    {
      //TODO: Linux mutex returns timeout error here... weird
      //return SemaphoreErrorTranslate();
      ret = OAL_ERR_SEM_ESEMLOCKED;
    }
  }
  else
  {
    if (sem_trywait(PSGetFromOALS(sem)))
    {
      ret = SemaphoreErrorTranslate();
    }
  }

  return ret;
}

LIB_RESULT OAL_SemaphoreTimedWait(OAL_SEMAPHORE sem, unsigned int time)
{
  LIB_RESULT ret = LIB_SUCCESS;
  timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  timespec ts = MicrosecondsToTimeSpec(time);
  //absolute time needed
  ts.tv_sec += now.tv_sec;
  ts.tv_nsec += now.tv_nsec;
  ts.tv_sec += ts.tv_nsec / 1000000000;
  ts.tv_nsec %= 1000000000;

  if (!sem)
  {
    ret = OAL_ERR_SEM_EBADSEM;
  }
  //TODO: reset error?
  else if (IsMutex(sem))
  {
    if (pthread_mutex_timedlock(PMGetFromOALS(sem), &ts))
    {
      ret = SemaphoreErrorTranslate();
    }
  }
  else
  {
    if (sem_timedwait(PSGetFromOALS(sem), &ts))
    {
      ret = SemaphoreErrorTranslate();
    }
  }

  return ret;
}

LIB_RESULT OAL_SemaphoreRelease(OAL_SEMAPHORE sem)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (!sem)
  {
    ret = LIB_FAILURE;
  }
  else if (IsMutex(sem))
  {
    if (pthread_mutex_unlock(PMGetFromOALS(sem)))
    {
      ret = SemaphoreErrorTranslate();
    }
  }
  else
  {
    if (sem_post(PSGetFromOALS(sem)))
    {
      ret = SemaphoreErrorTranslate();
    }
  }

  return ret;
}

//TODO: not implemented (yet?)
LIB_RESULT OAL_SemaphoreReset(OAL_SEMAPHORE sem, unsigned int count)
{
  return LIB_FAILURE;
}

LIB_RESULT OAL_SemaphoreDelete(OAL_SEMAPHORE sem)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (sem->mIsIndirect && sem->mOwnership)
  {
    pthread_mutex_destroy(PMGetFromOALS(sem));
    PMGetFromOALS(sem)->~pthread_mutex_t();
  }
  else if (!sem->mIsIndirect)
  {
    if (!sem)
    {
      ret = OAL_ERR_SEM_EBADSEM;
    }
    else if (IsMutex(sem))
    {
      if (pthread_mutex_destroy(PMGetFromOALS(sem)))
      {
        ret = SemaphoreErrorTranslate();
      }
    }
    else
    {
      if (sem_close(PSGetFromOALS(sem)))
      {
        ret = SemaphoreErrorTranslate();
      }
      else if (sem->mOwnership)
      {
        // only owner can unlink semaphore
        if (sem_unlink(sem->mLinuxName))
        {
          ret = SemaphoreErrorTranslate();
        }
      }
    }
  }

  delete sem;

  return ret;
}

LIB_RESULT OAL_SemaphoreOwnershipSet(OAL_SEMAPHORE aSem, bool aOwner)
{
  LIB_RESULT ret = LIB_SUCCESS;
  if (!aSem)
  {
    ret = OAL_ERR_SEM_EBADSEM;
  }
  else
  {
    aSem->mOwnership = aOwner;
  }
  return ret;
}

// not supported in Integrity
/*LIB_RESULT OAL_SemaphoreCreateInterprocessMutexOnAddress
  (OAL_SEMAPHORE *apSem, const char *apName, void *ap)
{
  LIB_RESULT ret = LIB_SUCCESS;

  tOalSemaphore* tos = new tOalSemaphore();

  tos->mIndirectMutex = new(ap) pthread_mutex_t();

  LinuxNameTruncate7(tos->mName, tos->mLinuxName, apName);

  tos->mIsIndirect = true;
  tos->mIsMutex = true;
  pthread_mutexattr_t attr;
  bool ok = true;
  ok = ok && (pthread_mutexattr_init(&attr) == 0);
  ok = ok &&
    (pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST) == 0);
  ok = ok &&
    (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) == 0);
  if (ok && pthread_mutex_init(tos->mIndirectMutex, &attr))
  {
    delete tos;
    tos = NULL;
    ret = SemaphoreErrorTranslate();
  }
  else
  {
    (void)pthread_mutexattr_destroy(&attr);
  }

  if (ret == LIB_SUCCESS && tos)
  {
    tos->mOwnership = true;
    *apSem = tos;
  }

  return ret;
}*/

LIB_RESULT
OAL_SemaphoreGetFromMutexAddress(OAL_SEMAPHORE *apSem, const char *apName,
    void *ap)
{
  LIB_RESULT ret = LIB_SUCCESS;

  tOalSemaphore* tos = new tOalSemaphore();
  tos->mIndirectMutex = (pthread_mutex_t*)ap;
  tos->mIsMutex = true;
  tos->mIsIndirect = true;
  tos->mOwnership = false;

  LinuxNameTruncate7(tos->mName, tos->mLinuxName, apName);

  *apSem = tos;

  return ret;
}

#ifdef __cplusplus
}
#endif
