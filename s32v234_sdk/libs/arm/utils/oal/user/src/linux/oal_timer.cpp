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
#include <linux/oal_linux.h>
#include <ctime>
#include <cerrno>
#include <csignal>

/*****************************************************************************
* types
*****************************************************************************/

/****************************************************************************/
/** Linux-specific timer type hidden by the OAL_SEMAPHORE
*****************************************************************************/
struct stimer
{
  timer_t ttimer;
  timespec interval;
  timespec lastValue;
  unsigned int userCallBackParam;
  bool state;
};

/*****************************************************************************
* local functions
*****************************************************************************/

/****************************************************************************/
/** Translates the errno to OAL timer error.
*
* \return OAL timer error
*
* \todo may be not complete
*****************************************************************************/
static LIB_RESULT TimerErrorTranslate()
{
  LIB_RESULT ret = LIB_FAILURE;

  switch(errno)
  {
    case ENOMEM:
      ret = OAL_ERR_MEMORY_OUT_OF_MEMORY;
      break;
    case EINVAL:
      ret = OAL_ERR_INVALID_TIMER_ID;
      break;
    default:
      break;
  }

  return ret;
}

/****************************************************************************/
/** Gets timer_t from OAL_TIMER.
*
* \param aOT OAL_TIMER
*
* \return timer_t
*****************************************************************************/
static inline timer_t TGetFromOT(OAL_TIMER aOT)
{
  return ((stimer*)aOT)->ttimer;
}

/*****************************************************************************
* functions
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

LIB_RESULT OAL_ControlTimer(OAL_TIMER timerId, unsigned int state)
{
  LIB_RESULT ret = LIB_SUCCESS;

  stimer* st = (stimer*)timerId;
  //TODO: let fail if wrong timer?
  if (st->state != bool(state))
  {
    itimerspec its;
    if (timer_gettime(TGetFromOT(timerId), &its))
    {
      ret = TimerErrorTranslate();
    }
    else
    {
      its.it_interval = st->interval;
      if (!state)
      {
        st->lastValue = its.it_value;
        its.it_value.tv_sec = its.it_value.tv_nsec = 0;
      }
      else
      {
        its.it_value = st->lastValue;
      }

      if (timer_settime(TGetFromOT(timerId), 0, &its, NULL))
      {
        ret = TimerErrorTranslate();
      }
      else
      {
        st->state = (bool)state;
      }
    }
  }
  return ret;
}

//TODO: OS contexts & stuff?
LIB_RESULT OAL_CreateTimer(OAL_TIMER *pTimerId,
                           const char *,
                           OAL_TimerCallBackFunc userCallBack,
                           unsigned int userCallBackParam,
                           unsigned int initial_time,
                           unsigned int reschedule_time,
                           unsigned int startState)
{
  LIB_RESULT ret = LIB_SUCCESS;

  sigevent sev;
  sev.sigev_notify = SIGEV_THREAD;
  //sev.sigev_notify = SIGEV_NONE;
  //TODO: types ok??
  void(*snf)(sigval_t) = (void(*)(sigval_t))userCallBack;
  sev._sigev_un._sigev_thread._function = snf;
  sev._sigev_un._sigev_thread._attribute = NULL;
  sev.sigev_value.sival_ptr = (void*)(unsigned long)userCallBackParam;

  timer_t tt;
  if (timer_create(CLOCK_MONOTONIC, &sev, &tt))
  {
    ret = TimerErrorTranslate();
  }
  else
  {
    stimer* st = new stimer;
    st->ttimer = tt;
    st->userCallBackParam = userCallBackParam;
    *pTimerId = st;

    itimerspec its;
    if (startState)
    {
      its.it_value = MicrosecondsToTimeSpec(initial_time);
    }
    else
    {
      its.it_value.tv_sec = its.it_value.tv_nsec = 0;
    }
    its.it_interval = MicrosecondsToTimeSpec(reschedule_time);
    if (timer_settime(tt, 0, &its, NULL))
    {
      ret = TimerErrorTranslate();
    }
    else
    {
      st->interval = its.it_interval;
      st->lastValue = MicrosecondsToTimeSpec(initial_time);
      st->state = bool(startState);
    }
  }

  return ret;
}

/*
 * TODO: probably not implemented correctly... e.g. see callback argument
 * (but usercallback can change... strange)
 */
LIB_RESULT OAL_ResetTimer(OAL_TIMER *pTimerId,
                          OAL_TimerCallBackFunc UserCallBack,
                          unsigned int initial_time,
                          unsigned int reschedule_time,
                          unsigned int startState)
{
  stimer* st = (stimer*)*pTimerId;
  unsigned int userCallBackParam = st->userCallBackParam;
  LIB_RESULT ret = OAL_DeleteTimer(*pTimerId);
  if (ret == LIB_SUCCESS)
  {
    ret = OAL_CreateTimer(pTimerId, "", UserCallBack, userCallBackParam,
        initial_time, reschedule_time, startState);
  }

  return ret;
}

LIB_RESULT OAL_DeleteTimer(OAL_TIMER timerId)
{
  LIB_RESULT res = LIB_SUCCESS;

  if (timer_delete(TGetFromOT(timerId)))
  {
    res = TimerErrorTranslate();
  }
  else
  {
    delete (stimer*)timerId;
  }

  return res;
}

unsigned int OAL_GetTickCountInMS(void)
{
  timespec ts;
  (void)clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

#ifdef __cplusplus
}
#endif
