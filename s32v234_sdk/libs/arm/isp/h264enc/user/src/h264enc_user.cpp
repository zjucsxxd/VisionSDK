/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2015 Freescale Semiconductor;
 * All Rights Reserved
 *
 *****************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONH264ENCUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * \file     h264enc_user.c
 * \brief    User space interface for H264 Encoder driver.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     2.12.2014
 * \note
 ****************************************************************************/

/* 
 * device specifics, such as ioctl numbers and the
 * major device file. 
 */
#include "s32vs234.h"
#include <stdint.h>
#include <signal.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */

#include "h264enc_public.h"
#include "vdb_log.h"

//****************************************************************************
// global data
//****************************************************************************
static H264ENC_EventHandler_t sEventHandler = NULL; ///< user registerred event handler
static H264ENC_EventHandlerClass *spEventHandlerClass = NULL; ///< user registerred event handler
static uint8_t sInitialized = 0;	///< >0 if initialized
static int32_t sFileDesc = -1;		///< H264Enc driver file descriptor

//****************************************************************************
// local function declarations
//****************************************************************************
void H264EncSigHandler(int, siginfo_t *info, void *);

//*****************************************************************************
// functions definitions
//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_Reserve()
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if(sFileDesc < 0)
  {  
    //sFileDesc = open("/dev/" H264ENC_DEVICE_NAME, 0);
    sFileDesc = open("/dev/h264enc", 0);
    if (sFileDesc < 0) 
    {
      VDB_LOG_ERROR("Can't open device file: %s\n", H264ENC_DEVICE_NAME);
      lRet = H264ENC_LIB_FAILURE;
    } // if open failed
  } // if not opened yet
  else 
  {
    VDB_LOG_WARNING("Device file: %s opened already.\n", H264ENC_DEVICE_NAME);
  } // else from if not opened yet
  
  return lRet;
} // H264ENC_Reserve()

//*****************************************************************************

void H264ENC_Release()
{
  close(sFileDesc);
} // H264ENC_Release()

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_Configure(const H264ENC_Config_t &arcConfig)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if (ioctl(sFileDesc, IOCTL_H264_ENC_CONFIG_SET, &arcConfig) != H264ENC_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("Encoder HW config failed:%d\n", lRet);
    lRet = H264ENC_LIB_FAILURE;
  } // if ioctl returned failure
  
  return lRet;
}

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_BuffersSet(const H264ENC_Buffers_t &arcBuffers)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if (ioctl(sFileDesc, IOCTL_H264_ENC_BUFFERS_SET, &arcBuffers) != H264ENC_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("Buffer setup failed:%d\n", lRet);
    lRet = H264ENC_LIB_FAILURE;
  } // if ioctl returned failure
  
  return lRet;
}

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_LinesFetch(uint32_t aMoreLines)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if(aMoreLines)
  {
    if (ioctl(sFileDesc, IOCTL_H264_ENC_FETCH, aMoreLines) != H264ENC_DRV_SUCCESS) 
    {
      VDB_LOG_ERROR("Fetch %u lines failed:%d\n", aMoreLines, lRet);
      lRet = H264ENC_LIB_FAILURE;
    } // if ioctl returned failure
  } // if there are more lines
  else
  {
    VDB_LOG_WARNING("No lines to be fetched.\n");
    lRet = H264ENC_LIB_FAILURE;
  } // else from if there are more lines
  
  return lRet;
}

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_AlarmShift(uint32_t aAlarmShift)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if(aAlarmShift)
  {
    if (ioctl(sFileDesc, IOCTL_H264_ENC_BS_ALARM_SHIFT, aAlarmShift) != H264ENC_DRV_SUCCESS) 
    {
      VDB_LOG_ERROR("Faled to shift alarm addres by %u bytes:%d\n", aAlarmShift, lRet);
      lRet = H264ENC_LIB_FAILURE;
    } // if ioctl returned failure
  } // if there are more lines
  else
  {
    VDB_LOG_WARNING("No shift.\n");
    lRet = H264ENC_LIB_FAILURE;
  } // else from if there are more lines
  
  return lRet;
}

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_StatusGet(H264ENC_Status_t &arStatus)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS; 
 
  if (ioctl(sFileDesc, IOCTL_H264_ENC_STATUS_GET, &arStatus) != H264ENC_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("Failed to get current encoder status:%d\n", lRet);
    lRet = H264ENC_LIB_FAILURE;
  } // if ioctl returned failure
  
  return lRet;
}

//*****************************************************************************

H264ENC_LIB_RESULT H264ENC_Stop()
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS; 
 
  if (ioctl(sFileDesc, IOCTL_H264_ENC_STOP) != H264ENC_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("Failed to stop the encoding:%d\n", lRet);
    lRet = H264ENC_LIB_FAILURE;
  } // if ioctl returned failure
  
  return lRet;
}

//****************************************************************************

H264ENC_LIB_RESULT H264ENC_EventHandlerSet(H264ENC_EventHandler_t aHandler)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if(sInitialized == 0)
  {      
    // prepare internal signal handler
    struct sigaction sig;
    sig.sa_sigaction = H264EncSigHandler;
    sig.sa_flags = SA_SIGINFO;
    
    if( sigaction(H264ENC_FRAME_DONE_SIGNAL, &sig, NULL) != 0)
    {
      VDB_LOG_ERROR("Failed to register Frame done signal handler.\n");
      lRet = H264ENC_LIB_FAILURE;
    } // if signal not registered
    else
    {
      sInitialized = 1;
    } // else from if signal not registered
  } // if not initialized yet
  
  if(lRet == H264ENC_LIB_SUCCESS)
  {
    // set the new handler
    sEventHandler = aHandler;
    VDB_LOG_NOTE("Event handler set.\n");
  } // if all ok so far

  return lRet;
} // H264EncEventHandlerSet()

//****************************************************************************

H264ENC_LIB_RESULT H264ENC_EventHandlerSet(H264ENC_EventHandlerClass *apHandler)
{
  H264ENC_LIB_RESULT lRet = H264ENC_LIB_SUCCESS;
  
  if(sInitialized == 0)
  {      
    // prepare internal signal handler
    struct sigaction sig;
    sig.sa_sigaction = H264EncSigHandler;
    sig.sa_flags = SA_SIGINFO;
    
    if( sigaction(H264ENC_FRAME_DONE_SIGNAL, &sig, NULL) != 0)
    {
      VDB_LOG_ERROR("Failed to register signal handler.\n");
      lRet = H264ENC_LIB_FAILURE;
    } // if signal not registered
    else
    {
      sInitialized = 1;
    } // else from if signal not registered
  } // if not initialized yet
  
  if(lRet == H264ENC_LIB_SUCCESS)
  {
    // set the new handler
    spEventHandlerClass = apHandler;
    VDB_LOG_NOTE("Event handler class set.\n");
  } // if all ok so far

  return lRet;
} // H264ENC_EventHandlerSet();

//****************************************************************************

void H264EncSigHandler(int, siginfo_t *apSigInfo, void *) 
{
  VDB_LOG_NOTE("Received event %u\n", apSigInfo->si_int);
  uint8_t lHandlerAssigned = 0;
  
  // *** call apropriate handler ***
  if(sEventHandler != NULL)
  {
    // call the handler
    sEventHandler(apSigInfo->si_int);
    lHandlerAssigned = 1;
  } // if handler assigned
  
  if(spEventHandlerClass != NULL)
  {
    // call the handler
    spEventHandlerClass->H264EncEventHandler(apSigInfo->si_int);
    lHandlerAssigned = 1;
  } // if handler assigned
  
  if(lHandlerAssigned == 0)
  {
    VDB_LOG_WARNING("Event handler Object unassigned.\n");
  } // if handler unassigned
  
} //H264EncSigHandler()

//****************************************************************************
