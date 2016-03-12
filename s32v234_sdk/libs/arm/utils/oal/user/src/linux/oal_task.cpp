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
* \file OAL_Task.cpp
* \brief OAL task implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <oal_task.hpp>
#include <linux/oal_linux.h>
#include <pthread.h>
#include <cerrno>

/*****************************************************************************
* const
*****************************************************************************/

const uint32_t DEFAULT_TASK_PRIORITY = 127;
const uint32_t MAX_TASK_PRIORITY = 255;

/*****************************************************************************
* functions
*****************************************************************************/

/****************************************************************************/
/** Translates the errno to OAL task error.
*
* \return OAL task error
*
* \todo may be not complete
*****************************************************************************/
static LIB_RESULT TaskErrorTranslate()
{
  LIB_RESULT ret = LIB_FAILURE;

  switch(errno)
  {
    case EINVAL:
    case EPERM:
      ret = OAL_ERR_LOG_EINVALIDPARAM;
      break;
    default:
      break;
  }

  return ret;
}

/****************************************************************************/
/** Gets a pointer to pthread_t from a pointer to OAL_TCB.
*
* \param apTcb pointer to OAL_TCB
*
* \return pointer to pthread_t
*****************************************************************************/
static inline pthread_t* ThreadPGetFromTCBP(OAL_TCB* apTcb)
{
  return (pthread_t*)apTcb;
}

/****************************************************************************/
/** Gets a pthread_t from OAL_TCB.
*
* \param apTcb OAL_TCB
*
* \return pthread_t
*****************************************************************************/
static inline pthread_t ThreadGetFromTCB(OAL_TCB aTcb)
{
  return (pthread_t)aTcb;
}

/****************************************************************************/
/** Maps the OAL priority to pthread priority.
*
* \param apTcb pointer to OAL_TCB
*
* \return pointer to pthread_t
*****************************************************************************/
static int MapPriority(uint32_t aOALpriority)
{
  int pmax = sched_get_priority_max( SCHED_FIFO );
  int pmin = sched_get_priority_min( SCHED_FIFO );
  int range = abs((pmax - pmin)  +1);

  /*
  * Calculate the number of bins to map the OAL priorities into (large range
  * to small range).
  */
  int nBins = int(MAX_TASK_PRIORITY)/range;

  //Add one bin if more than half a range is left.
  if ((int)MAX_TASK_PRIORITY % range > range/2)
  {
    ++nBins;
  }

  //revert the priority (descending vs ascending)
  int pReverted = int(MAX_TASK_PRIORITY) - aOALpriority;
  int offset = pReverted / nBins ;

  return pmin + offset;
}

//TODO: use the semaphore?
OAL_Task::OAL_Task():
 mMessageQueueId(0),
 mTaskControlBlock(0),
 mStackSizeInBytes(0),
 mPriority(DEFAULT_TASK_PRIORITY),
 mSemaphoreThreadSafety(0),
 mIsSemaphoreThreadSafetyCreated(false),
 mIsTaskInitialized(false),
 mIsTaskActivated(false),
 mIsTaskSuspended(false),
 mIsTaskFinished(false)
{
   mName[0] = 0;
}

OAL_Task::~OAL_Task()
{
  mTaskControlBlock = 0;
  mSemaphoreThreadSafety = 0;
}

LIB_RESULT OAL_Task::Spawn(const uint32_t cStackSizeInBytes,
                const uint32_t cTaskPriority,
                const char   cTaskName[])
{
  LIB_RESULT res = Init(cStackSizeInBytes, cTaskPriority, cTaskName);
  if (res == LIB_SUCCESS)
  {
    res = Activate();
  }
  return res;
}

void* OAL_Task::TaskEntryRoutine(void* pVoid)
{
  OAL_Task* o = (OAL_Task*) pVoid;
  //TODO: not like that... e.g. TaskClose should react to external closing?
  o->TaskOpen();
  o->TaskService();
  o->TaskClose();
  return NULL;
}

//TODO: should create the thread in some form already? as detached maybe?
LIB_RESULT OAL_Task::Init(const uint32_t cStackSizeInBytes,
               const uint32_t cTaskPriority,
               const char cTaskName[])
{
  mStackSizeInBytes = cStackSizeInBytes;
  mPriority = cTaskPriority;
  (void)strcpy(mName, cTaskName);

  mIsTaskInitialized = true;
  //TODO: suspended?

  return LIB_SUCCESS;
}

LIB_RESULT OAL_Task::Activate()
{
  LIB_RESULT ret = LIB_SUCCESS;

  pthread_attr_t attr;
  if (pthread_attr_init(&attr))
  {
    ret = LIB_FAILURE;
  }
  //stack
  else if (pthread_attr_setstacksize(&attr, (size_t)mStackSizeInBytes))
  {
    ret = LIB_FAILURE;
  }
  else
  {
    sched_param sp;
    //int schedulePolicy = 0;
    //pthread_attr_getschedpolicy(&attr, &schedulePolicy);
    uint32_t priority = (uint32_t)mPriority;
    priority = MapPriority(priority);
    sp.__sched_priority = priority;
    if (pthread_attr_setschedpolicy(&attr, SCHED_RR))
    {
      ret = LIB_FAILURE;
    }
    else if (pthread_attr_setschedparam(&attr, &sp))
    {
      ret = LIB_FAILURE;
    }
    else if (
        pthread_create(ThreadPGetFromTCBP(&mTaskControlBlock), &attr,
            OAL_Task::TaskEntryRoutine, (void*)this))
    {
      //return TaskErrorTranslate();
      ret = LIB_FAILURE;
    }
    else
    {
      (void)pthread_attr_destroy(&attr);

      mIsTaskActivated = true;
    }
  }
  return ret;
}

 LIB_RESULT OAL_Task::Delete()
 {
   LIB_RESULT ret = LIB_SUCCESS;

   pthread_t t = ThreadGetFromTCB(mTaskControlBlock);
   mIsTaskFinished = true;
   if (pthread_cancel(t))
   {
     //task has ended already
     ret = LIB_SUCCESS;
   }
   else
   {
     mIsTaskActivated = false;
     mIsTaskSuspended = false;

     //TODO: necessary?
     if (pthread_join(t, NULL))
     {
       ret = LIB_FAILURE;
     }
   }

   return ret;
 }

 LIB_RESULT OAL_Task::Join()
 {
   pthread_t t = ThreadGetFromTCB(mTaskControlBlock);
   return pthread_join(t, NULL);
 }

LIB_RESULT OAL_Task::Suspend()
{

  mIsTaskSuspended = true;

  return LIB_SUCCESS;
}

LIB_RESULT OAL_Task::Resume()
{

  mIsTaskSuspended = false;

  return LIB_SUCCESS;
}

LIB_RESULT OAL_Task::Reset()
{
  //TODO: nothing to do?
  return LIB_SUCCESS;
}

LIB_RESULT OAL_Task::PrioritySet(const uint32_t cPriority)
{
  LIB_RESULT ret = LIB_SUCCESS;

  mPriority = MapPriority(cPriority);

  pthread_t t = ThreadGetFromTCB(mTaskControlBlock);
  if (mTaskControlBlock)
  {
    if (pthread_setschedprio(t, mPriority))
    {
      ret = TaskErrorTranslate();
    }
  }

  return ret;
}

LIB_RESULT OAL_Task::PriorityGet(uint32_t& rReturnedPriority)
{
  rReturnedPriority = mPriority;

  return LIB_SUCCESS;
}

LIB_RESULT OAL_Task::MessageQueueGet(uint32_t&)
{
  return LIB_FAILURE;
}

#ifdef __cplusplus
extern "C" {
#endif

void OAL_TaskSleep(unsigned int time)
{
  timespec ts = MicrosecondsToTimeSpec(time);
  nanosleep(&ts, NULL);
}

void OAL_TaskRelinquish(void)
{
  pthread_yield();
}

#ifdef __cplusplus
}
#endif


