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
* \file OAL_Signal.cpp
* \brief OAL signal implementation
* \author Igor Aleksandrowicz
* \version
* \date 30-August-2013
****************************************************************************/

#include <oal_signal.h>
#include <linux/oal_linux.h>
#include <csignal>
#include <cerrno>

/*****************************************************************************
* types
*****************************************************************************/

/****************************************************************************/
/** Linux-specific signal type hidden by the OAL_SIGNAL
*****************************************************************************/
struct signal_s
{
  int mSig;
  //remember current handler
  void (*mpHandler)(int);
  //old action... for avoiding further dynamic allocations
  struct sigaction* mpOldAction;
};

/*****************************************************************************
* functions
*****************************************************************************/

/****************************************************************************/
/** Translates the errno to OAL signal error.
*
* \return OAL signal error
*
* \todo may be not complete
*****************************************************************************/
static LIB_RESULT SignalErrorTranslate()
{
  LIB_RESULT ret = LIB_FAILURE;

  switch(errno)
  {
    case EAGAIN:
      ret = OAL_ERR_SIG_ETIMEOUT;
      break;
  }

  return ret;
}

LIB_RESULT OAL_SignalCreate(OAL_SIGNAL* apSignal, int aSignalID)
{
  signal_s* ss = new signal_s();
  ss->mSig = aSignalID;
  ss->mpHandler = NULL;

  *apSignal= ss;

  return LIB_SUCCESS;
}

void emptySigHandler(int){}

/****************************************************************************/
/** Common function for both non-timed and timed wait.
*
* \param apWhichSignal output, which signal was caught,
*                      can be NULL if we're not interested in that
* \param aSignals signal handles
* \param aSignalCount signal handles count
* \param aTime maximal wait time in microseconds
* \param timed is the wait timed?
*
* \return LIB_SUCCESS on success, OAL_ERR_SIG_ETIMEOUT on timeout,
*         LIB_FAILURE otherwise
*****************************************************************************/
//TODO: combination handler + wait doesn't really work on linux level..
static inline LIB_RESULT OAL_SignalWaitCommon(OAL_SIGNAL* apWhichSignal,
    OAL_SIGNAL aSignals[], unsigned int aSignalCount, unsigned int aTime,
    int)
{
  //create a signal set
    sigset_t sigSet;
    sigemptyset(&sigSet);
    //for disabling the default signal behavior
    struct sigaction sact;
    sact.sa_handler = emptySigHandler;
    sigemptyset(&(sact.sa_mask));
    sact.sa_flags = 0;
    for (unsigned int i = 0; i < aSignalCount; ++i)
    {
      int iSig = aSignals[i]->mSig;
      //skip if handler set already
      if ((aSignals[i]->mpHandler == NULL) &&
          sigaction(iSig, &sact, aSignals[i]->mpOldAction) < 0)
      {
        return SignalErrorTranslate();
      }
      sigaddset(&sigSet, iSig);
    }

    timespec timeS = MicrosecondsToTimeSpec(aTime);
    siginfo_t sigInf;
    int sig = aTime ?
        sigtimedwait(&sigSet, &sigInf, &timeS) :
        sigwaitinfo(&sigSet, &sigInf);
    if (sig < 0)
    {
      return SignalErrorTranslate();
    }

    //reenable the signal actions, find which signal was caught
    if (apWhichSignal)
    {
      for (unsigned int i = 0; i < aSignalCount; ++i)
      {
        int iSig = aSignals[i]->mSig;
        //was tested for errors already
        if (aSignals[i]->mpHandler == NULL)
        {
          sigaction(iSig, aSignals[i]->mpOldAction, NULL);
        }
        if (apWhichSignal && (aSignals[i]->mSig == sig))
        {
          *apWhichSignal = aSignals[i];
        }
      }
    }

    return LIB_SUCCESS;
}

LIB_RESULT OAL_SignalWait(OAL_SIGNAL aSignal)
{
  return OAL_SignalWaitCommon(NULL, &aSignal, 1, 0, 0);
}

LIB_RESULT OAL_SignalTimedWait(OAL_SIGNAL aSignal, unsigned int aTime)
{
  return OAL_SignalWaitCommon(NULL, &aSignal, 1, aTime, 1);
}

LIB_RESULT OAL_SignalWaitAny(OAL_SIGNAL* apWhichSignal,
    OAL_SIGNAL aSignals[], unsigned int aSignalCount)
{
  return OAL_SignalWaitCommon(apWhichSignal, aSignals, aSignalCount, 0, 1);
}

LIB_RESULT OAL_SignalTimedWaitAny(OAL_SIGNAL* apWhichSignal,
  OAL_SIGNAL aSignals[], unsigned int aSignalCount, unsigned int aTime)
{
  return OAL_SignalWaitCommon(apWhichSignal, aSignals, aSignalCount, aTime, 1);
}

LIB_RESULT OAL_SignalSetHandler(OAL_SIGNAL aSignal, void (*apHandler)(int))
{
  struct sigaction sact;
  sact.sa_handler = apHandler;
  sact.sa_flags = 0;

  if (sigaction(aSignal->mSig, &sact, NULL) < 0)
  {
    return SignalErrorTranslate();
  }

  aSignal->mpHandler = apHandler;

  return LIB_SUCCESS;
}

LIB_RESULT OAL_SignalDestroy(OAL_SIGNAL aSignal)
{
  delete aSignal;
  return LIB_SUCCESS;
}
