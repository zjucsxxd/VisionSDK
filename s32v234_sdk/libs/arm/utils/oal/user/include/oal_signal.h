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
* \file OAL_Signal.h
* \brief OAL signals
* \author Igor Aleksandrowicz
* \version
* \date 30-August-2013
****************************************************************************/

#ifndef OAL_SIGNAL_H_
#define OAL_SIGNAL_H_

#include <oal.h>

/*****************************************************************************
* constants
*****************************************************************************/

///< Timeout waiting on Signal
static const LIB_RESULT OAL_ERR_SIG_ETIMEOUT = 0x91001;

/*****************************************************************************
* prototypes
*****************************************************************************/

/// opaque handle for OAL Signal
typedef struct signal_s *OAL_SIGNAL;

/*****************************************************************************
* prototypes
*****************************************************************************/

/****************************************************************************/
/** Creates a signal.
*
* \param apSignal pointer to signal handle
* \param aSignalID size of the shared memory
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalCreate(OAL_SIGNAL* apSignal, int aSignalID);

/****************************************************************************/
/** Waits for a signal.
*
* \param aSignal signal handle
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalWait(OAL_SIGNAL aSignal);

/****************************************************************************/
/** Waits for a signal with timeout.
*
* \param aSignal signal handle
* \param aTime maximal wait time in microseconds
*
* \return LIB_SUCCESS on success, OAL_ERR_SIG_ETIMEOUT on timeout,
*         LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalTimedWait(OAL_SIGNAL aSignal, unsigned int aTime);

/****************************************************************************/
/** Waits for any of the signals.
*
* \param apWhichSignal output, which signal was caught,
*                      can be NULL if we're not interested in that
* \param aSignals signal handles
* \param aSignalCount signal handles count
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalWaitAny(OAL_SIGNAL* apWhichSignal,
    OAL_SIGNAL aSignals[], unsigned int aSignalCount);

/****************************************************************************/
/** Waits for a signal with timeout.
*
* \param apWhichSignal output, which signal was caught,
*                      can be NULL if we're not interested in that
* \param aSignals signal handles
* \param aSignalCount signal handles count
* \param aTime maximal wait time in microseconds
*
* \return LIB_SUCCESS on success, OAL_ERR_SIG_ETIMEOUT on timeout,
*         LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalTimedWaitAny(OAL_SIGNAL* apWhichSignal,
  OAL_SIGNAL aSignals[], unsigned int aSignalCount, unsigned int aTime);

/****************************************************************************/
/** Sets a signal hanler.
*
* \param aSignal signal to set the handler to
* \param apHandler handler function to set
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalSetHandler(OAL_SIGNAL aSignal, void (*apHandler)(int));

/****************************************************************************/
/** Destroys shared memory.
*
* \param aSignal signal to destroy
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*****************************************************************************/
LIB_RESULT OAL_SignalDestroy(OAL_SIGNAL aSignal);

#endif /* OAL_SIGNAL_H_ */

