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
* \file OAL_Process.cpp
* \brief OAL process and inter-process communication implementation
* \author Tomas Babinec
* \version
* \date 09-January-2014
****************************************************************************/

#include "oal_integrity.h"
#include <oal_process.h>
#include <unistd.h>
#include <sys/stat.h>
//#include <sys/statvfs.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

/*****************************************************************************
* constants
*****************************************************************************/

//mode used when creating shared memory
const int SHMEM_CREATION_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

/*****************************************************************************
* types
*****************************************************************************/

/****************************************************************************/
/** Linux-specific shared memory type hidden by the OAL_SHARED_MEM
*****************************************************************************/
struct sharedMem_s
{
  int mFD;
  void* mpPointer;
  uint32_t mSize;
  char mName[8];
  //Linux name always starts with /
  char mLinuxName[9];
  //only the process who created the shmem can delete it
  bool mOwnership;

  /************************************************************************/
  /** Simple constructor.
  *************************************************************************/
  sharedMem_s():
    mFD(-1),
    mpPointer(NULL),
    mSize(0),
    mOwnership(false)
  {
    (void)memset(mName, 0, 8);
    (void)memset(mLinuxName, 0, 9);
  }

  /************************************************************************/
  /** Simple destructor.
  *************************************************************************/
  ~sharedMem_s()
  {
    mpPointer = NULL;
  }
};

/*****************************************************************************
* functions
*****************************************************************************/

LIB_RESULT OAL_ProcessSpawn(const char* apFileName, int aArgC,
    char** appArgV, int (*pFailureFunction)(void*), void* pFFarg)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (aArgC >= 0)
  {
    int fRes = fork();

    if (fRes == 0)
    {
      char** args = new char*[aArgC + 2];
      //const char problem
      unsigned int sl = (unsigned int)strlen(apFileName);
      args[0] = new char[sl+1];
      (void)strcpy(args[0], apFileName);
      args[0][sl] = 0;
      for (int i = 0; i < aArgC; ++i)
      {
        args[i + 1] = appArgV[i];
      }
      args[aArgC + 1] = 0;
      (void)execvp(apFileName, args);
      delete[] args[0];
      delete[] args;
      if (pFailureFunction)
      {
        exit(pFailureFunction(pFFarg));
      }
      else
      {
        exit(EXIT_FAILURE);
      }
    }
    else if (fRes < 0)
    {
      ret = LIB_FAILURE;
    }
  }
  else
  {
    ret = LIB_FAILURE;
  }

  return ret;
}

LIB_RESULT OAL_SharedMemoryCreate(OAL_SHARED_MEM* apSharedMem,
  const char* apName, uint32_t aSize)
{
  LIB_RESULT ret = LIB_SUCCESS;

  sharedMem_s* sms = new sharedMem_s();

  LinuxNameTruncate7(sms->mName, sms->mLinuxName, apName);

  sms->mFD = shm_open(sms->mLinuxName, O_RDWR | O_CREAT,
      SHMEM_CREATION_MODE);
  if (sms->mFD < 0)
  {
    delete sms;
    ret = LIB_FAILURE;
  }
  else if (ftruncate(sms->mFD, aSize))
  {
    (void)close(sms->mFD);
    (void)shm_unlink(sms->mLinuxName);
    delete sms;
    ret = LIB_FAILURE;
  }
  else
  {
    sms->mpPointer =
      mmap(NULL, aSize, PROT_READ | PROT_WRITE, MAP_SHARED, sms->mFD, 0);

    if (sms->mpPointer == MAP_FAILED)
    {
      (void)close(sms->mFD);
      (void)shm_unlink(sms->mLinuxName);
      delete sms;
      ret = LIB_FAILURE;
    }
    else
    {
      sms->mOwnership = true;
      sms->mSize = aSize;
      *apSharedMem = sms;
    }
  }

  return ret;
}

LIB_RESULT OAL_SharedMemoryGetByName(OAL_SHARED_MEM* apSharedMem,
  const char* apName)
{
  LIB_RESULT ret = LIB_SUCCESS;

  sharedMem_s* sms = new sharedMem_s();

  LinuxNameTruncate7(sms->mName, sms->mLinuxName, apName);

  sms->mFD = shm_open(sms->mLinuxName, O_RDWR ,
      SHMEM_CREATION_MODE);
  if (sms->mFD < 0)
  {
    (void)close(sms->mFD);
    delete sms;
    ret = LIB_FAILURE;
  }
  else
  {
    struct stat buf;
    if (fstat(sms->mFD, &buf))
    {
			switch(errno)
			{
				case 	EACCES: break; 
			  case EBADF: break;
				case EFAULT: break;
				case EIO : break;
				case ELOOP: break;
				case ENAMETOOLONG: break;
				case ENOENT: break;
				case ENOSYS: break;
				case ENOTDIR: break;
				default: break;
			}
			
      ret = LIB_FAILURE;
    }
    else
    {
      sms->mSize = (uint32_t)buf.st_size;
      sms->mpPointer =
        mmap(NULL, sms->mSize, PROT_READ | PROT_WRITE, MAP_SHARED, sms->mFD, 0);

      if (sms->mpPointer == MAP_FAILED)
      {
        (void)close(sms->mFD);
        delete sms;
        ret = LIB_FAILURE;
      }
      else
      {
        sms->mOwnership = false;
        *apSharedMem = sms;
      }
    }
  }

  return ret;
}

LIB_RESULT OAL_SharedMemoryGetByName(OAL_SHARED_MEM* apSharedMem,
  const char* apName, uint32_t aSize)
{
  LIB_RESULT ret = LIB_SUCCESS;

  sharedMem_s* sms = new sharedMem_s();

  LinuxNameTruncate7(sms->mName, sms->mLinuxName, apName);

  sms->mFD = shm_open(sms->mLinuxName, O_RDWR ,
      SHMEM_CREATION_MODE);
  if (sms->mFD < 0)
  {
    (void)close(sms->mFD);
    delete sms;
    ret = LIB_FAILURE;
  }
  else
  {
		sms->mSize = aSize;
		sms->mpPointer =
			mmap(NULL, sms->mSize, PROT_READ | PROT_WRITE, MAP_SHARED, sms->mFD, 0);

		if (sms->mpPointer == MAP_FAILED)
		{
			(void)close(sms->mFD);
			delete sms;
			ret = LIB_FAILURE;
		}
		else
		{
			sms->mOwnership = false;
			*apSharedMem = sms;
		}
	}
  return ret;
}

LIB_RESULT OAL_SharedMemoryGetPointer(void** apPointer,
    OAL_SHARED_MEM aSharedMem)
{
  *apPointer = aSharedMem->mpPointer;
  return LIB_SUCCESS;
}

LIB_RESULT OAL_SharedMemoryGetPointer(void** apPointer,
    OAL_SHARED_MEM aSharedMem, uint32_t aSize)
{
	LIB_RESULT res = LIB_SUCCESS;
  if (munmap(aSharedMem->mpPointer, aSharedMem->mSize))
  {
    res = LIB_FAILURE;
  } // if unmap old mapping failed
	else
	{
		aSharedMem->mSize = aSize;
		aSharedMem->mpPointer =
			mmap(NULL, aSharedMem->mSize, PROT_READ | PROT_WRITE, MAP_SHARED, aSharedMem->mFD, 0);
		if (aSharedMem->mpPointer == MAP_FAILED)
		{
			res = LIB_FAILURE;
		} // if new mapping failed
		else
		{
			*apPointer = aSharedMem->mpPointer;
		} // else from if mapping failed
		
	} // else from if unmap old mapping failed
  return res;
}

uint32_t OAL_SharedMemorySizeGet(OAL_SHARED_MEM aSharedMem)
{
	return aSharedMem->mSize;
} // OAL_SharedMemorySizeGet(OAL_SHARED_MEM aSharedMem)

LIB_RESULT OAL_SharedMemoryDestroy(OAL_SHARED_MEM aSharedMem)
{
  LIB_RESULT res = LIB_SUCCESS;
  if (munmap(aSharedMem->mpPointer, aSharedMem->mSize))
  {
    res = LIB_FAILURE;
  }
  if (close(aSharedMem->mFD))
  {
    res = LIB_FAILURE;
  }
  if (aSharedMem->mOwnership &&
      shm_unlink(aSharedMem->mLinuxName))
  {
    res = LIB_FAILURE;
  }

  delete aSharedMem;

  return res;
}

LIB_RESULT OAL_SharedMemoryOwnershipSet(OAL_SHARED_MEM aSharedMem, bool aOwnership)
{
  LIB_RESULT ret = LIB_SUCCESS;
  if(aSharedMem)
  {
    aSharedMem->mOwnership = aOwnership;
  }
  else
  {
    ret = LIB_FAILURE;
  }
  return ret;
}

