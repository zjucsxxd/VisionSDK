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
#include "oal.h"
#include "oal_process.h"


/*==============================================================================*/
/* OAL Semaphore type								*/
/*==============================================================================*/
struct tOalSemaphore
{
   void * sm;
   OAL_SEMAPHORE_TYPE type;
};

typedef struct
{
  struct tOalSemaphore semaphore;          //This must be first always
  //Semaphore            integritySemaphore; //Integrity semaphore
  //LocalMutex           integrityMutex;     //Integrity mutex
} OAL_SEMAPHORE_LOCAL;

/*==============================================================================*/
/* Create the semaphore								*/
/*==============================================================================*/
LIB_RESULT OAL_SemaphoreCreate(OAL_SEMAPHORE* pSem,
                               const char *pName,
                               OAL_SEMAPHORE_TYPE type,
                               unsigned int count)
{
  return LIB_SUCCESS;
}

/*==============================================================================*/
/* Delete the semaphore								*/
/*==============================================================================*/
LIB_RESULT OAL_SemaphoreDelete(OAL_SEMAPHORE sem)
{
  return LIB_SUCCESS;
}

/*==============================================================================*/
/* Obtain the semaphore								*/
/*==============================================================================*/
LIB_RESULT OAL_SemaphoreObtain(OAL_SEMAPHORE sem)
{
  return LIB_SUCCESS;
}

/*==============================================================================*/
/* Timed wait for the semaphore							*/
/*==============================================================================*/
LIB_RESULT OAL_SemaphoreTimedWait(OAL_SEMAPHORE sem, unsigned int time)
{
  return LIB_SUCCESS;
}

/*==============================================================================*/
/* Release the semaphore							*/
/*==============================================================================*/
LIB_RESULT OAL_SemaphoreRelease(OAL_SEMAPHORE sem)
{
  return LIB_SUCCESS;
}


LIB_RESULT OAL_SharedMemoryDestroy(OAL_SHARED_MEM aSharedMem)
{
  return LIB_SUCCESS;
}

LIB_RESULT OAL_SharedMemoryOwnershipSet(OAL_SHARED_MEM aSharedMem, 
                                        bool aOwnership)
{
  return LIB_SUCCESS;
}


#ifdef __cplusplus
extern "C" {
#endif

LIB_RESULT OAL_SemaphoreOwnershipSet(OAL_SEMAPHORE aSem, bool aOwner)
{
  return LIB_SUCCESS;
}

LIB_RESULT OAL_SemaphoreGetByName(OAL_SEMAPHORE *apSem, const char *apName)
{
  return LIB_SUCCESS;
}


#ifdef __cplusplus
}
#endif


//HW interrupts
void OAL_InterruptLock(void)
{
}

//HW interrupts
void OAL_InterruptFree(void)
{
}
