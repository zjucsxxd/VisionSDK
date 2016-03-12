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
/**
 * \file     seq_user.cpp
 * \brief    User-space library calls to access Sequencer driver functionality.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     09-November-2014
 * \note
 ****************************************************************************/

#include "s32vs234.h"

//#define CA53 // to make sure IPU addresses are from A53 perspective

#include <stdint.h>
#include <errno.h>
#ifndef __STANDALONE__
  #include <string.h>
  #include <signal.h>
  #include <fcntl.h>		// open 
  #include <unistd.h>		// exit 
  #include <sys/ioctl.h>	// ioctl 
  #include <sys/mman.h>	// mmap
#else
  #include "seq_func.h"
#endif // else from #ifndef __STANDALONE__

#define VDB_LOG_NOTE_OFF
#include "vdb_log.h"
#include "seq_public.h"

//#include "seq_hw.h"

//****************************************************************************
// types
//****************************************************************************

typedef struct seq_fw_arr
{
  const char  *mpFwData;
  uint32_t    mIndex;
} SEQ_FwArr_t;

//****************************************************************************
// global variables
//****************************************************************************


//*****************************************************************************
// local data
//*****************************************************************************

static SEQ_EventHandler_t sEventHandler = NULL; ///< user registerred event handler
static SEQ_EventHandlerClass *spEventHandlerClass = NULL; ///< user registerred event handler
static uint8_t sInitialized = 0;	///< >0 if initialized

#ifndef __STANDALONE__
static int32_t sSeqFD = -1;		///< Sequencer driver file descriptor

//****************************************************************************
// local function declarations
//****************************************************************************
void SeqSigHandler(int aSigNum, siginfo_t *info, void *unused);
#else //#ifndef __STANDALONE__
extern "C" {
  void SeqSigHandler(int aSigNum, int aValue);
}
#endif //else from #ifndef __STANDALONE__

static uint32_t checkIpuRange(uint16_t aIsIPUS, uint16_t aEng);

//*****************************************************************************
// functions definitions
//*****************************************************************************

SEQ_LIB_RESULT SEQ_Reserve()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if(sSeqFD < 0)
  {  
    sSeqFD = open("/dev/seq", 0);
    if (sSeqFD < 0) 
    {
      VDB_LOG_ERROR("Can't open device file: %s\n", SEQ_DEVICE_NAME);
      lRet = SEQ_LIB_FAILURE;
    } // if open failed
  } // if not opened yet
  else 
  {
    VDB_LOG_WARNING("Device file: %s opened already.\n", SEQ_DEVICE_NAME);
  } // else from if not opened yet
#else
  // *** Setup the driver ***    
  if(SEQ_Setup() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
    VDB_LOG_ERROR("SEQ setup failed.\n");
  } // if driver setup failed
#endif // #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_Reserve()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_Release()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;
#ifndef __STANDALONE__  
  if(sSeqFD < 0)
  {
    close(sSeqFD);
    if (close(sSeqFD) < 0) 
    {
      VDB_LOG_ERROR("Failed to close device file %s.\n", SEQ_DEVICE_NAME);
      lRet = SEQ_LIB_FAILURE;
    } // if open failed
    else
    {
      sSeqFD = -1;
    } // else if open failed
  } // not openned yet
  else 
  {
    VDB_LOG_WARNING("Sequencer already closed.\n");
  } // else from if not openned yet
#else // #ifndef __STANDALONE__ 

  // relase resources
  if(SEQ_Close() != SEQ_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to close Sequecer device.\n");
    lRet = SEQ_LIB_FAILURE;
  }
  
#endif // else from #ifndef __STANDALONE__ 
  return lRet;
} // SEQ_Release()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_Boot()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__    
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_BOOT)) < 0) 
  {
    VDB_LOG_ERROR("Failed to BOOT the Sequencer.\n");
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__  
  if(SEQ_DRV_Boot() == SEQ_DRV_SUCCESS)
  {
    VDB_LOG_NOTE("Sequencer booted.\n");
  }
  else
  {
    VDB_LOG_ERROR("Sequencer boot failed.\n");
  }
#endif // else from #ifndef __STANDALONE__  
     
  return lRet;
} // SEQ_Boot()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_Reset()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__   
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_RESET)) < 0) 
  {
    VDB_LOG_ERROR("Failed to RESET the Sequencer.\n");
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  SEQ_DRV_Reset();
#endif // else from #ifndef __STANDALONE__ 
     
  return lRet;
} // SEQ_Reset()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_MessageSend(SEQ_Message_t *apMessage, uint8_t aWait)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if(apMessage != NULL)
  {
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, (aWait == 0)?IOCTL_SEQ_MSG_SEND:IOCTL_SEQ_MSG_SEND_WAIT, apMessage)) < 0) 
    {
      VDB_LOG_ERROR("Failed to send the message: %d, %u\n", lRetVal, IOCTL_SEQ_MSG_SEND);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
  }
  else
  {
    VDB_LOG_ERROR("Message was a NULL pointer.\n");
    lRet = SEQ_LIB_FAILURE;
  }
#else // #ifndef __STANDALONE__
  
  VDB_LOG_NOTE("Sending a message.\n");
  if(SEQ_DRV_MsgSend(apMessage, aWait) == SEQ_DRV_SUCCESS)
  {
    VDB_LOG_NOTE("The message was sent\n");
  }
  else
  {
    lRet = SEQ_LIB_FAILURE;
    VDB_LOG_NOTE("Failed to send the message.\n");
  }

#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_MessageSend()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_GraphAddressGet(uintptr_t *apGraphAddress)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;
  
  *apGraphAddress = SEQ_GRAPH_ADDR;
  
  return lRet;
} // SEQ_GraphAddressGet()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_MsgAuxDataGet(void* apData, uint32_t aSize)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if((apData != NULL) && (aSize > 0))
  {
    if(sSeqFD < 0)
    {
      VDB_LOG_ERROR("Sequencer device file not opened.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if Sequencer not opened
    else
    {
      int32_t lRetVal = 0;
      SEQ_AuxData_t lAuxData = {apData, aSize};
      
      if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_AUX_DATA_GET, &lAuxData)) < 0) 
      {
        VDB_LOG_ERROR("Auxiliary data get failed: %d\n", lRetVal);
        lRet = SEQ_LIB_FAILURE;
      } // if ioctl returned failure
    } // else from if Sequencer not opened
  }// if the Graph package exists
  else
  {
    VDB_LOG_WARNING("Invalid pointer or size.\n");
  }
#else // #ifndef __STANDALONE__
  SEQ_AuxData_t lTmpData = {apData, aSize};
  
  SEQ_DRV_PramAuxDataGet(&lTmpData);
  memcpy(apData, lTmpData.mpData, lTmpData.mSize);
  aSize = lTmpData.mSize;
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_GraphAddressGet()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_GraphDownload(SEQ_GraphPackage_t *apGraphPackage)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if(apGraphPackage != NULL)
  {
    if(sSeqFD < 0)
    {
      VDB_LOG_ERROR("Sequencer device file not opened.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if Sequencer not opened
    else
    {
      int32_t lRetVal = 0;
      if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_GRAPH_DOWNLOAD, apGraphPackage)) < 0) 
      {
        VDB_LOG_ERROR("Graph download failed: %d\n", lRetVal);
        lRet = SEQ_LIB_FAILURE;
      } // if ioctl returned failure
    } // else from if Sequencer not opened
  }// if the Graph package exists
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_GraphDownload(apGraphPackage) != SEQ_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Graph download failed.\n");
    lRet = SEQ_LIB_FAILURE;
  }
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_GraphDownload(SEQ_GraphPackage_t *apGraphPackage)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_GraphFetch(SEQ_GraphPackage_t *apGraphPackage)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__
  if(apGraphPackage != NULL)
  {
    if(sSeqFD < 0)
    {
      VDB_LOG_ERROR("Sequencer device file not opened.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if Sequencer not opened
    else
    {
      int32_t lRetVal = 0;
      if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_GRAPH_FETCH, apGraphPackage)) < 0) 
      {
        VDB_LOG_ERROR("Graph fetch failed: %d\n", lRetVal);
        lRet = SEQ_LIB_FAILURE;
      } // if ioctl returned failure
    } // else from if Sequencer not opened
  }// if the Graph package exists
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_GraphFetch(apGraphPackage) != SEQ_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Graph download failed.\n");
  }
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_GraphFetch(SEQ_GraphPackage_t *apGraphPackage)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_FrmBuffersRequest(SEQ_BufferRequest_t *apRequest)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

  if(apRequest != NULL)
  { 
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_BUF_REQ, apRequest)) < 0) 
    {
      VDB_LOG_ERROR("Frame buffers' requset failed: %d\n", lRetVal);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    if(SEQ_DRV_FrmBuffersRequest(apRequest) != SEQ_DRV_SUCCESS)
    {
        VDB_LOG_ERROR("Frame buffers' request failed.\n");
        lRet = SEQ_LIB_FAILURE;
    } // if request failed
#endif // else #ifndef __STANDALONE__
  }// if Request structure exists
  
  return lRet;
} // SEQ_FrmBuffersRequest(SEQ_BufferList_t *apBuffsList)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_FrmBufferQuery(SEQ_FrmBufferInfo_t *apBuffInfo)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

  if(apBuffInfo != NULL)
  { 
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_BUF_QRY, apBuffInfo)) < 0) 
    {
      VDB_LOG_ERROR("Frame buffer query failed: %d\n", lRetVal);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    if(SEQ_DRV_FrmBufferQuery(apBuffInfo) != SEQ_DRV_SUCCESS)
    {
        VDB_LOG_ERROR("Frame buffer query failed.\n");
        lRet = SEQ_LIB_FAILURE;
    } // if query failed
#endif // else #ifndef __STANDALONE__
  }// if Info structure exists
  
  return lRet;
} // SEQ_FrmBufferQuery(SEQ_FrmBufferInfo_t *apBuffInfo)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_FrmBufferPush(SEQ_FrmBufferInfo_t *apBuffInfo)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

  if(apBuffInfo != NULL)
  {  
#ifndef __STANDALONE__  
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_BUF_PSH, apBuffInfo)) < 0) 
    {
      VDB_LOG_ERROR("Push failed: %d\n", lRetVal);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
#else // #ifndef __STANDALONE__
    if(SEQ_DRV_FrmBufferPush(apBuffInfo) != SEQ_DRV_SUCCESS)
    {
        VDB_LOG_ERROR("Push failed.\n");
        lRet = SEQ_LIB_FAILURE;
    } // if Push failed
#endif // else #ifndef __STANDALONE__
  }// if Info structure exists 
  
  return lRet;
} // SEQ_FrmBufferPush(SEQ_FrmBufferInfo_t *apBuffInfo)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_FrmBufferPop(SEQ_FrmBufferInfo_t *apBuffInfo)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

  if(apBuffInfo != NULL)
  {  
#ifndef __STANDALONE__  
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_BUF_POP, apBuffInfo)) < 0) 
    {
      //VDB_LOG_ERROR("Pop failed: %d\n", lRetVal);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
#else // #ifndef __STANDALONE__
    if(SEQ_DRV_FrmBufferPop(apBuffInfo) != SEQ_DRV_SUCCESS)
    {
      //VDB_LOG_ERROR("Pop failed.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if Pop failed
#endif // else #ifndef __STANDALONE__
  }// if Info structure exists 
  
  return lRet;
} // SEQ_FrmBufferPop(SEQ_FrmBufferInfo_t *apBuffInfo)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_GraphStart(uint32_t aFrameCnt, uint32_t aInputLines)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  SEQ_StartCfg_t lStartCfg = {aFrameCnt, aInputLines};
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_START, &lStartCfg)) < 0) 
  {
    VDB_LOG_ERROR("Graph START failed: %d\n", lRetVal);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  SEQ_DRV_GraphStart(aFrameCnt, aInputLines);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SEQ_GraphStart(uint32_t aFrameCnt)

//*****************************************************************************

SEQ_LIB_RESULT SEQ_GraphStop(uint8_t aWait)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, (aWait == 0)?IOCTL_SEQ_STOP:IOCTL_SEQ_STOP_WAIT)) < 0) 
  {
    VDB_LOG_ERROR("Graph STOP failed: %d\n", lRetVal);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  SEQ_DRV_GraphStop();
  
  if(aWait == 1)
  {
    while(SEQ_DRV_GraphStateGet() == 0)
    {
    }; // while not stopped
  } // if wait required
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_GraphStop()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_IpuPerformanceInfoRequest(uint32_t aFrmCnt)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_IPU_PROFILE_REQ, aFrmCnt)) < 0) 
  {
    VDB_LOG_ERROR("IPU profiling info request failed: %d\n", lRetVal);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_IpuPerformanceInfoRequest(aFrmCnt) != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_IpuPerformanceInfoRequest()

//*****************************************************************************

SEQ_LIB_RESULT SEQ_IpuPerformanceInfoGet(SEQ_IpuPerformanceRegs_t *apIpuRegs)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_IPU_PROFILE_GET, apIpuRegs)) < 0) 
  {
    VDB_LOG_ERROR("IPU profiling info fetch failed: %d\n", lRetVal);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_IpuPerformanceInfoGet(apIpuRegs) != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_IpuPerformanceInfoGet()

//****************************************************************************

SEQ_LIB_RESULT SEQ_EventLogEnable()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  lRet = SEQ_LIB_FAILURE;
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_EventLogEnable() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_EventLogEnable()

//****************************************************************************

SEQ_LIB_RESULT SEQ_EventLogDisable()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  lRet = SEQ_LIB_FAILURE;
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_EventLogDisable() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_EventLogDisable()

//****************************************************************************

SEQ_LIB_RESULT SEQ_AutoExpEnable()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  lRet = SEQ_LIB_FAILURE;
#else // #ifndef __STANDALONE__
  SEQ_DRV_AutoExpEnable();
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_AutoExpEnable()

//****************************************************************************

SEQ_LIB_RESULT SEQ_AutoExpDisable()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  lRet = SEQ_LIB_FAILURE;
#else // #ifndef __STANDALONE__
  SEQ_DRV_AutoExpDisable();  
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_AutoExpDisable()

//****************************************************************************

SEQ_LIB_RESULT SEQ_EventLogGet(SEQ_EventLog_t **appEventLog)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  appEventLog[0][0].mNextRecIdx = 0;
  lRet = SEQ_LIB_FAILURE;
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_EventLogGet(appEventLog) != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_EventLogGet()

//****************************************************************************

SEQ_LIB_RESULT SEQ_HistogramEnable(SEQ_IpuEngine_t aIpuIdx)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_HIST_ENABLE, aIpuIdx)) < 0) 
  {
    VDB_LOG_ERROR("Histogram enable for IPU %d failed.\n", (uint32_t) aIpuIdx);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  if(SEQ_DRV_IpuHistogramEnable(aIpuIdx) != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_LIB_FAILURE;
  } // if failed
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_HistogramEnable()

//****************************************************************************

SEQ_LIB_RESULT SEQ_HistogramGet(SEQ_IpuHist_t *apHist)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;
  
  if(apHist != NULL)
  {
#ifndef __STANDALONE__  
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_HIST_GET, apHist)) < 0) 
    {
      VDB_LOG_ERROR("Histogram enable for IPU %d failed.\n", (uint32_t) apHist->mIpuIdx);
      lRet = SEQ_LIB_FAILURE;
    } // if ioctl returned failure
#else // #ifndef __STANDALONE__
    SEQ_IpuHistHead_t lHist;
    lHist.mIpuIdx = apHist->mIpuIdx;
    lHist.mpData  = &(apHist->mpData[0]);
    if(SEQ_DRV_IpuHistogramGet(&lHist) != SEQ_DRV_SUCCESS)
    {
      lRet = SEQ_LIB_FAILURE;
    } // if failed
    apHist->mPeak     = lHist.mPeak;
    apHist->mPeakAddr = lHist.mPeakAddr;
#endif // else #ifndef __STANDALONE__
  } // if apHist exists
  
  return lRet;
} // SEQ_HistogramGit()

//***************************************************************************
//DATA.SAVE.BINARY c:\isp_log.csv var.address(*spLogFile)++var.value(lLogSize)
uint32_t SEQ_EventLogProccess(SEQ_EventLog_t &arEventLog,
                              uint32_t aMaxFrames,
                              char* apString, 
                              size_t aStringSize)
{
#if (ISP_EVT_LOG_LEN > 0)
  unsigned long lStartTime = arEventLog.mpRecords[0].mTime;
  sprintf(apString, "IPUS,IPUV,OTHER,SEQ_FD,CSI_FE,SW_EVT,CSI_Line,FDMA_Line,REG,Time\r\n");
  //                   0     1    2      3      4     5       6         7      8    9
  //                   A     B    C      D      E     F       G         H      I    J
  char *lpLogFile = apString + strlen(apString);
  uint32_t lEventCounters[8] = {0};
  uint32_t lUnprocFrames = 0;
  uint32_t i = 0;
  
  if(aMaxFrames > (aStringSize / EVTLOG_STRING_SIZE))
  {
    aMaxFrames = (aStringSize / EVTLOG_STRING_SIZE);
  } // if too many frames requested
  
  for(i = 0; i < ISP_EVT_LOG_LEN; i++)
  {
    SEQ_EventRecord_t &lEventRec = arEventLog.mpRecords[i];
    
    if(lEventRec.mEvent.B.mType != ISP_LOGEVT_CSI_FE)
    {
      break;
    }    
        
    lEventCounters[lEventRec.mEvent.B.mType] ++;
    
    sprintf(lpLogFile, "0,0,0,0,%u,0,0,0,%08x,%lu\r\n",
            lEventCounters[ISP_LOGEVT_CSI_FE],
            lEventRec.mEvent.B.mRegister,
            lEventRec.mTime - lStartTime
            );
    
    // shift file pointer
    lpLogFile += strlen(lpLogFile);
  } // for all unprocessed frames
  
  lUnprocFrames = i;
  lStartTime = arEventLog.mpRecords[i].mTime;
  
  for(1; i < ISP_EVT_LOG_LEN;i++)
  {
    uint32_t lEventFlags[8] = {0};
    SEQ_EventRecord_t &lEventRec = arEventLog.mpRecords[i];
    
    if(lEventRec.mEvent.B.mType == ISP_LOGEVT_OTHER)
    {
      if((lEventRec.mEvent.B.mRegister & 0x00000400) > 0)
      { 
        lEventCounters[ISP_LOGEVT_CSI_LINE]++;
        lEventFlags[ISP_LOGEVT_CSI_LINE] = lEventCounters[ISP_LOGEVT_CSI_LINE];
      } // if CSI line done event
      
      if((lEventRec.mEvent.B.mRegister & 0x00000001) > 0)
      { 
        lEventCounters[ISP_LOGEVT_FDMA_LINE]++;
        lEventFlags[ISP_LOGEVT_FDMA_LINE] = lEventCounters[ISP_LOGEVT_FDMA_LINE];
      } // if FDMA done event
    } // if OTHER event
      
    lEventCounters[lEventRec.mEvent.B.mType] ++;
    lEventFlags[lEventRec.mEvent.B.mType] = lEventCounters[lEventRec.mEvent.B.mType];
    
    
    // *** print the event ***
    sprintf(lpLogFile, "%u,%u,%u,%u,%u,%u,%u,%u,%08x,%lu\r\n",
            lEventFlags[ISP_LOGEVT_IPUS],
            lEventFlags[ISP_LOGEVT_IPUV],
            lEventFlags[ISP_LOGEVT_OTHER],
            lEventFlags[ISP_LOGEVT_SEQ_FD],
            lEventFlags[ISP_LOGEVT_CSI_FE],
            lEventFlags[ISP_LOGEVT_SW_EVT],
            lEventFlags[ISP_LOGEVT_CSI_LINE],
            lEventFlags[ISP_LOGEVT_FDMA_LINE],
            lEventRec.mEvent.B.mRegister,
            lEventRec.mTime - lStartTime
            );
    
    // shift file pointer
    lpLogFile += strlen(lpLogFile);
    
    if(lEventCounters[ISP_LOGEVT_SEQ_FD] >= (aMaxFrames - 1 + lUnprocFrames))
    {
      break;
    } // if Maximum frames reached

  } // for all possible event
  return (lpLogFile - apString);
#else // #if (ISP_EVT_LOG_LEN > 0)
  arEventLog.mNextRecIdx = 0;
  aStringSize = aMaxFrames;
  if((apString != NULL) && (aStringSize != 0))
  {
    apString[0] = '\0';    
  }
  
  return 0;
#endif // else from #if (ISP_EVT_LOG_LEN > 0)
} // SEQ_EventLogProcess()

//****************************************************************************
//   Firmware handling
//****************************************************************************

static int FwArrGetc(SEQ_FwArr_t *apFwArr)
{
  int lRet = EOF;
  if( (apFwArr != NULL) && (apFwArr->mpFwData[apFwArr->mIndex] != '\0'))
  {
    lRet = apFwArr->mpFwData[apFwArr->mIndex++];
  } // if something to get
  return lRet;
} // FwArrGetc(SEQ_FwArr_t *apFwArr)

//****************************************************************************

static void ArrLineSkip(SEQ_FwArr_t *apFwArr, int32_t *apChar) 
{
  do
  { 
    *apChar = FwArrGetc(apFwArr); 
  } while((*apChar != 'S') && (*apChar != EOF));
  
  if(*apChar == 'S')
  {
    apFwArr->mIndex--;
    *apChar = '\n';
  }
} // LineSkip()

//****************************************************************************

static uint32_t ArrHexScan(SEQ_FwArr_t *apFwArr, uint8_t aBytes)
{
  int32_t lData;
  uint32_t lVal = 0;
  
  for(int i= 0; i< aBytes * 2; i++)
  {
    lVal <<= 4;
    lData = FwArrGetc(apFwArr);
    if(lData < 'A') 
    {
      lVal += lData - '0';
    }
    else
    {
      lVal += lData - 'A' + 10;
    }  
  } // for all bytes
    
  return lVal;
} // HexScan()

//****************************************************************************

SEQ_LIB_RESULT SEQ_FwArrDownload(const char *apcFwArr, off_t aMapBase, size_t aMapBytes, bool aW32)
{
  SEQ_LIB_RESULT aRes = SEQ_LIB_SUCCESS;
  
  if(apcFwArr == NULL)
  {
    VDB_LOG_ERROR("FW data.\n");
    aRes = SEQ_LIB_FAILURE;
  } // if file open failed
  else
  {
    SEQ_FwArr_t lFwArr = {apcFwArr, 0};
    // open and map memory
    uint8_t *lpMap = NULL;
    
#ifndef __STANDALONE__
    int32_t lFd = 0;

    lFd = open("/dev/mem", O_RDWR);

    if(lFd < 0)
    {
      VDB_LOG_ERROR("Failed to open /dev/mem\n");
      aRes = SEQ_LIB_FAILURE;
    } //if failed to open /dev/mem
    else
    {
      if(aMapBytes)
      {
        lpMap = (uint8_t*)mmap(NULL, aMapBytes, PROT_READ | PROT_WRITE, MAP_SHARED, lFd, aMapBase);
      } // if aMapBytes = 0
      else
      {
        // if aMapBytes is 0, aMapBase is expected to contain previous mapping
        lpMap = (uint8_t*)aMapBase;
      } // else if aMapBytes = 0

      if (lpMap == NULL) 
      {
        VDB_LOG_ERROR("Can't map memory: %s\n", strerror(errno));
      } // if mapping failed
      close(lFd);
    } // else from if failed to open /dev/mem
#else // #ifndef __STANDALONE__
    lpMap = (uint8_t*)aMapBase;
#endif // else from l#ifndef __STANDALONE__    
    
    if(lpMap != NULL)
    {
      // process and download the firmware
      int32_t   lChar = 0;
      uint32_t  lAddr = 0;
      uint32_t  j     = 0;
      uint32_t  lSize = 0;
      uint32_t* lpW32 = NULL;
      uint8_t   lBA[4];
      
      while(1)
      {
        j ++;
        lChar = FwArrGetc(&lFwArr);
        if(lChar != 'S')
        {
          // skip the rest of the line
          ArrLineSkip(&lFwArr, &lChar);
          VDB_LOG_NOTE("Not S at the beginning\n");
        } // if not starting with S
        else
        {
          // check srec line type (address size)
          lChar = FwArrGetc(&lFwArr);
          size_t lAddrWidth=0;
          switch(lChar)
          {
            // 16bit address
            case '1': lAddrWidth = 2;
              break;
            // 24bit address
            case '2': lAddrWidth = 3;
              break;
            // 32bit address
            case '3': lAddrWidth = 4;
              break;
            default:  lAddrWidth = 0;
              break;
          } // switch address type
          
          if(0 == lAddrWidth)
          {
            // skip the rest of the line
            ArrLineSkip(&lFwArr, &lChar);
            VDB_LOG_NOTE("Not supported Srecored line type.\n");
          } // if not supported line type
          else
          {
            // read the num. of bytes
            lSize = ArrHexScan(&lFwArr, 1);
      
            // read the address
            lAddr = ArrHexScan(&lFwArr, lAddrWidth);
#ifdef FW_DL_PRINTS
            VDB_LOG_NOTE("address is: %x, %u\n", 
                         (unsigned) lAddr, 
                         (unsigned) lSize);
#endif
            // copy the data to mapped memory
            uint32_t  i = 0;
            uint32_t  ci  = 0;
            bool  run;
            uint8_t byte;
            
            lpW32 = (uint32_t*)((uintptr_t)lpMap + lAddr);
      
            do
            {
              byte = (uint8_t)ArrHexScan(&lFwArr, 1);
        
              if(!aW32) // 8 bit accesses
              {
                      lpMap[lAddr+i] = byte;
              } // if 8 bit accesses 
              
              run  = (++i < (lSize - (lAddrWidth+1)));
              
              if(aW32)  // 32 bit accesses
              {
                lBA[ci++] = byte;
              
                if(!run || (sizeof(lBA) == ci))
                {
                  *lpW32++ =  (uint32_t)lBA[0]  | \
                              (uint32_t)lBA[1] << 8 | \
                              (uint32_t)lBA[2] << 16  | \
                              (uint32_t)lBA[3] << 24;

                  ci = 0;
                } // if ready to write
              } // if 32 bit accesses
            }while(run);
      
//            putchar('\n');
            ArrLineSkip(&lFwArr, &lChar);
          } // else from if not supported line type
        } // else from if not starting with S
#ifdef FW_DL_PRINTS
        printf("line no: %u processed\n", (unsigned) j);
#endif
        if(lChar == EOF)
        {
          VDB_LOG_NOTE("Copied %d lines\n", (int) j);
          break;
        } // if done
      } // for all lines    
#ifndef __STANDALONE__      
      // unmap the memory
      if(aMapBytes)
      {
        munmap(lpMap, aMapBytes);
      } // if mapped      
#endif // #ifndef __STANDALONE__    
      lpMap = NULL;
    } // if memory mapped
  } // else from if file open failed
  
  return aRes;  
} // sdi::SeqFwArrDownload()

//****************************************************************************
//     Event handling
//****************************************************************************

SEQ_LIB_RESULT SEQ_IrqsProcess()
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__  
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(sSeqFD, IOCTL_SEQ_IRQ_SRV)) < 0) 
  {
    VDB_LOG_ERROR("Graph STOP failed: %d\n", lRetVal);
    lRet = SEQ_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__
  SEQ_DRV_IrqsProcess(); 
#endif // else #ifndef __STANDALONE__
    
  return lRet;
} // SEQ_LIB_RESULT SEQ_IrqServe()

//****************************************************************************
//   Firmware handling
//****************************************************************************

SEQ_LIB_RESULT SEQ_FwArrDownload(const char *apcFwArr, SEQ_FwType_t aFwType)
{
  SEQ_LIB_RESULT aRes = SEQ_LIB_SUCCESS; 
  uint8_t *lpMap = NULL;
  uintptr_t lMapBase = 0;
  size_t    lMapBytes = 0;
  bool lW32;
  SEQ_FwArr_t lFwArr = {apcFwArr, 0};
  
  if(aFwType == SEQ_FW_CM0)
  {
    lMapBase = CRAM_BASE;
    lMapBytes = CRAM_SIZE;
    lW32     = false;
  } // if SEQ_FW_CM0
  else if(aFwType == SEQ_FW_KERNEL)
  {
    lMapBase = KRAM_BASE;
    lMapBytes = KRAM_SIZE;
    lW32     = true;
  } // else if SEQ_FW_KERNEL
  else
  {
    aRes = SEQ_LIB_FAILURE;
    VDB_LOG_ERROR("Unknown firmware type specified.\n");
  } // else from if SEQ_FW_KERNEL
  
  if(aRes == SEQ_LIB_SUCCESS)
  {    
    if(apcFwArr == NULL)
    {
      VDB_LOG_ERROR("No FW data.\n");
      aRes = SEQ_LIB_FAILURE;
    } // if file open failed
    else
    {
      // open and map memory
      
#ifndef __STANDALONE__
      int32_t lFd = 0;

      lFd = open("/dev/mem", O_RDWR);

      if(lFd < 0)
      {
        VDB_LOG_ERROR("Failed to open /dev/mem\n");
        aRes = SEQ_LIB_FAILURE;
      } //if failed to open /dev/mem
      else
      {
        lpMap = (uint8_t*)mmap(NULL, lMapBytes, PROT_READ | PROT_WRITE, MAP_SHARED, lFd, lMapBase);

        if (lpMap == NULL) 
        {
          aRes = SEQ_LIB_FAILURE;
          VDB_LOG_ERROR("Can't map memory: %s\n", strerror(errno));
        }
        close(lFd);
      } // else from if failed to open /dev/mem
#else // #ifndef __STANDALONE__
      (void) lMapBytes; // to get rid of a compiler warning
      lpMap = (uint8_t*)lMapBase;
#endif // else from #ifndef __STANDALONE__     
    } // else from if no FW data
    
    if(lpMap != NULL)
    {
      // process the file and download the data
      int32_t	lChar = 0;
      uint32_t	lAddr = 0;
      uint32_t	j = 0;
      uint32_t	lSize = 0;
      uint32_t*	lpW32 = NULL;
      uint32_t lBA;
      uint8_t	*lpBA = (uint8_t*) &lBA;
      
      while(1)
      {
        j ++;
        lChar = FwArrGetc(&lFwArr);
        if(lChar != 'S')
        {
          // skip the rest of the line
          ArrLineSkip(&lFwArr, &lChar);
          VDB_LOG_NOTE("Not S at the beginning\n");
        } // if not starting with S
        else
        {
          // look for only 32 bits at the moment
          lChar = FwArrGetc(&lFwArr);
          size_t lAddrWidth=0;
          switch(lChar)
          {
                  case '1':	lAddrWidth = 2;
            break;
                  case '2':	lAddrWidth = 3;
            break;
                  case '3':	lAddrWidth = 4;
            break;
            default:	lAddrWidth = 0;
          } // switch address width
          
          if(0 == lAddrWidth)
          {
            // skip the rest of the line
            ArrLineSkip(&lFwArr, &lChar);
            VDB_LOG_NOTE("Not supported\n");
          } // if address width 0
          else
          {
            // read the num. of bytes
            lSize = ArrHexScan(&lFwArr, 1);

            // read the address
            lAddr = ArrHexScan(&lFwArr, lAddrWidth);
#ifdef FW_DL_PRINTS
            VDB_LOG_NOTE("address is: %x, %u\n", 
                         (unsigned) lAddr, 
                         (unsigned) lSize);
#endif
            // copy the data to SRAM
            uint32_t	i	= 0;
            uint32_t	ci	= 0;
            bool	run;
            uint8_t	byte;
            
            lpW32 = (uint32_t*)((uintptr_t)lpMap + lAddr);
            
            do
            {
              byte = (uint8_t)ArrHexScan(&lFwArr, 1);
              
              if(!lW32)	// 8 bit accesses
              {
                lpMap[lAddr+i] = byte;
              }
              
              run  = (++i < (lSize - (lAddrWidth+1)));
              
              if(lW32)	// 32 bit accesses
              {
                lpBA[ci++] = byte;
              
                if(!run || (sizeof(lBA) == ci))
                {
                  // if not full 4bytes fill with 0
                  /*if((!run) && (sizeof(lBA) != ci))
                  {
                    do
                    {
                      lBA[ci++] = 0;
                    }while(ci != sizeof(lBA));
                  }*/
                  *lpW32++ =	lBA; 
#if 0                  
                  // went for direct uint32_t solution because:
                  // bit shift generates neg operations which don't add up right
                  // why??
                  ((uint32_t)lBA[0])	|	\
-                  ((uint32_t)lBA[1] << 8)	|	\
-                  ((uint32_t)lBA[2] << 16)	|	\
-                  ((uint32_t)lBA[3] << 24);                 
#endif 

                  ci = 0;
                }
              }
            }while(run);
            
      //    putchar('\n');
            ArrLineSkip(&lFwArr, &lChar);
          } // else from if 
        } // else from if not starting with S
#ifdef FW_DL_PRINTS
        printf("line no: %u processed\n", (unsigned) j);
#endif
        if(lChar == EOF)
        {
          VDB_LOG_NOTE("Copied %d lines\n", (int) j);
          break;
        }
      } // for all lines     
#ifndef __STANDALONE__
      // unmap the memory
      munmap(lpMap, lMapBytes);
#endif //#ifndef __STANDALONE__
      lpMap = NULL;
    } // if memory mapped
  } // if all ok so far
  
  return aRes;  
} // SeqFwArrDownload(const char*, SEQ_FwType_t)

//****************************************************************************

SEQ_LIB_RESULT SEQ_FwArrDownload(const char *apcFwArr)
{
  return SEQ_FwArrDownload(apcFwArr, SEQ_FW_CM0);  
} // sdi::SeqFwArrDownload()

//****************************************************************************

SEQ_LIB_RESULT SEQ_FwFileDownload(const char *apFwPath, SEQ_FwType_t aFwType)
{
  SEQ_LIB_RESULT aRes = SEQ_LIB_SUCCESS;
  
  FILE *lpFr = fopen(apFwPath, "r");
  if(lpFr == 0)
  {
    VDB_LOG_ERROR("Unable to open the sequencer FW file.\n");
    aRes = SEQ_LIB_FAILURE;
  } // if file open failed
  else
  {
    // Determine file size
    fseek(lpFr, 0, SEEK_END);
    size_t lSize = ftell(lpFr);

    // get the fw data
    char* lpFwArr = new char[lSize];
    rewind(lpFr);
    fread(lpFwArr, sizeof(char), lSize, lpFr);
    fclose(lpFr);

    // download data
    aRes = SEQ_FwArrDownload(lpFwArr, aFwType);
    delete[] lpFwArr;
  } // else from if file open failed
  
  return aRes;  
} // sdi::SeqFwFileDownload(const char*, SEQ_FwType_t)

//****************************************************************************
//     Event handling
//****************************************************************************

SEQ_LIB_RESULT SEQ_EventHandlerSet(SEQ_EventHandler_t aHandler)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;

#ifndef __STANDALONE__   
  if(sInitialized == 0)
  {      
    // prepare internal signal handler
    struct sigaction sig;
    sig.sa_sigaction = SeqSigHandler;
    sig.sa_flags = SA_SIGINFO;
    
    if( sigaction(SEQ_EVENT_SIGNAL, &sig, NULL) != 0)
    {
      VDB_LOG_ERROR("Failed to register signal handler.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if signal not registered
    else
    {
      sInitialized = 1;
    } // else from if signal not registered
  } // if not initialized yet
#else // #ifndef __STANDALONE__ 
  sInitialized = 1;
#endif // else #ifndef __STANDALONE__ 
  
  if(lRet == SEQ_LIB_SUCCESS)
  {
    // set the new handler
    sEventHandler = aHandler;
    VDB_LOG_NOTE("Event handler set.\n");
  } // if all ok so far


  return lRet;
} // FdmaEventHandlerSet()

//****************************************************************************

SEQ_LIB_RESULT SEQ_EventHandlerSet(SEQ_EventHandlerClass *apHandler)
{
  SEQ_LIB_RESULT lRet = SEQ_LIB_SUCCESS;
#ifndef __STANDALONE__  
  if(sInitialized == 0)
  {      
    // prepare internal signal handler
    struct sigaction sig;
    sig.sa_sigaction = SeqSigHandler;
    sig.sa_flags = SA_SIGINFO;
    
    if( sigaction(SEQ_EVENT_SIGNAL, &sig, NULL) != 0)
    {
      VDB_LOG_ERROR("Failed to register signal handler.\n");
      lRet = SEQ_LIB_FAILURE;
    } // if signal not registered
    else
    {
      sInitialized = 1;
    } // else from if signal not registered
  } // if not initialized yet
#else // #ifndef __STANDALONE__
  sInitialized = 1;
#endif // else #ifndef __STANDALONE__  
  
  if(lRet == SEQ_LIB_SUCCESS)
  {
    // set the new handler
    spEventHandlerClass = apHandler;
    VDB_LOG_NOTE("Event handler class set.\n");
  } // if all ok so far


  return lRet;
} // SEQ_EventHandlerSet();

//****************************************************************************
#define UNUSED(_a) ((void*) aUnused)

#ifndef __STANDALONE__
void SeqSigHandler(int aSigNum, siginfo_t *apSigInfo, void *aUnused) 
{
  int *lpVal = &(apSigInfo->si_int);
  VDB_LOG_NOTE("Received event %u through signal %d\n", *lpVal, aSigNum);
  (void)aSigNum;	// *** avoid warning ***
  (void)aUnused;	// *** avoid warning ***
  UNUSED(aUnused);
#else // #ifndef __STANDALONE__
void SeqSigHandler(int aSigNumn, int aValue)
{	
	int *lpVal = &aValue;
#endif //else #ifndef __STANDALONE__

  uint8_t lHandlerAssigned = 0;
  
  // *** call apropriate handler ***
  if(sEventHandler != NULL)
  {
    // call the handler
    sEventHandler(*lpVal);
    lHandlerAssigned = 1;
  } // if handler assigned
  
  if(spEventHandlerClass != NULL)
  {
    // call the handler
    spEventHandlerClass->SeqEventHandler(*lpVal);
    lHandlerAssigned = 1;
  } // if handler assigned
  
  if(lHandlerAssigned == 0)
  {
    VDB_LOG_WARNING("Event handler Object unassigned.\n");
  } // if handler unassigned
  
} //SeqSigHandler()

//****************************************************************************

#define	CPY2MDATA(_s)	memcpy(&msg.mData, &_s, sizeof(_s));
#define	READ_REG_WAIT	1000000UL

/****************************************************************************/

SEQ_LIB_RESULT seq_swreset(SEQ_reset_t aReset)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_SUCCESS;
  SEQM_swreset_t	swr;
  SEQ_Message_t		msg;

  swr.mReset	= aReset;
  
  CPY2MDATA(swr);
  msg.mType	= SEQ_MSG_TYPE_SWRESET;
  msg.mStatus	= SEQ_MSG_STAT_READY;
 
  lRet = SEQ_MessageSend(&msg, 0);

  return(lRet);

} // seq_swreset()

/****************************************************************************/

SEQ_LIB_RESULT seq_startNode(SEQM_start_node_para_t* apSN, uint16_t aNumNodes)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_FAILURE;
  SEQ_Message_t		msg;
  SEQM_start_node_t *lpSn = (SEQM_start_node_t*)msg.mData;
  SEQM_start_node_para_t *lpSnp = &(lpSn->mNodes);
  size_t		sz = sizeof(SEQM_start_node_para_t)*aNumNodes;
  
  if((sizeof(uint16_t)+sz) < sizeof(msg.mData))
  {
    lpSn->mNum = aNumNodes;
    for(uint32_t i = 0; i < aNumNodes; i++)
    {
      lpSnp[i] = apSN[i];
    }   
    
    msg.mType	= SEQ_MSG_TYPE_START_NODE;
    msg.mStatus	= SEQ_MSG_STAT_READY;
    lRet	= SEQ_MessageSend(&msg);
  }
  
  return(lRet);

} // seq_startNode()

/****************************************************************************/

SEQ_LIB_RESULT seq_checkNode(uint16_t aNode)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_SUCCESS;
  SEQ_Message_t		msg;
  SEQM_check_node_t	chk;
  
  chk.mNode	= aNode;
  
  CPY2MDATA(chk);
  msg.mType	= SEQ_MSG_TYPE_CHECK_NODE;
  msg.mStatus	= SEQ_MSG_STAT_READY;
  
  lRet = SEQ_MessageSend(&msg);

  return(lRet);

} // seq_checkNode()

/****************************************************************************/

SEQ_LIB_RESULT seq_setReg(uint16_t aIsIPUS, uint16_t aEng, uint16_t aDirect, uint32_t aOffset, uint32_t aValue)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_FAILURE;
  SEQ_Message_t		msg;
  SEQM_ipu_reg_t	set;
  uint32_t		addr;
  
  if(0 != (addr = checkIpuRange(aIsIPUS, aEng)))
  {
    set.mEngBase= addr + ISP_IO_DEV_SPACE*aEng;
    set.mDirect	= aDirect;
    set.mIndex	= aOffset;
    set.mData	= aValue;
  
    CPY2MDATA(set);
    msg.mType	= SEQ_MSG_TYPE_SET_REG;
    msg.mStatus	= SEQ_MSG_STAT_READY;
  
    lRet = SEQ_MessageSend(&msg);
  }
  
  return(lRet);

} // seq_setReg()

/****************************************************************************/

SEQ_LIB_RESULT seq_getReg(uint16_t aIsIPUS, uint16_t aEng, uint16_t aDirect, uint32_t aOffset, uint32_t* apValue)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_FAILURE;
  SEQ_Message_t		msg;
  SEQM_ipu_reg_t	get;
  uint32_t		addr;
  volatile size_t	w;
  
  if(0 != (addr = checkIpuRange(aIsIPUS, aEng)))
  {
    get.mEngBase= addr + ISP_IO_DEV_SPACE*aEng;
    get.mDirect	= aDirect;
    get.mIndex	= aOffset;
  
    CPY2MDATA(get);
    msg.mType	= SEQ_MSG_TYPE_GET_REG;
    msg.mStatus	= SEQ_MSG_STAT_READY;
  
    lRet = SEQ_MessageSend(&msg);
    
    // *** wait for result ***
    for(w=0; (SEQ_MSG_STAT_RESULT != msg.mStatus) && (w<READ_REG_WAIT); w++);
    
    if(w<READ_REG_WAIT)
    {
      *apValue = get.mData;
      lRet = SEQ_LIB_SUCCESS;
    }
  }
  
  return(lRet);

} // seq_getReg()

/****************************************************************************/

SEQ_LIB_RESULT seq_echo(uint32_t aDelay)
{
  SEQ_LIB_RESULT	lRet = SEQ_LIB_SUCCESS;
  SEQ_Message_t		msg;
  SEQM_echo_t		ech;
  
  ech.mReplayDly= aDelay;
  
  CPY2MDATA(ech);
  msg.mType	= SEQ_MSG_TYPE_ECHO;
  msg.mStatus	= SEQ_MSG_STAT_READY;
  
  lRet = SEQ_MessageSend(&msg);

  return(lRet);

} // seq_checkNode()

/****************************************************************************/

static uint32_t checkIpuRange(uint16_t aIsIPUS, uint16_t aEng)
{
  uint32_t addr=0;
  
  if(aIsIPUS)
  {
    if(aEng < ISP_NUM_IPUS)
    {
      addr = (uint32_t)((uintptr_t)&IPUS_0);
    }
  }
  else
  {
    if(aEng < ISP_NUM_IPUV)
    {
      addr = (uint32_t)((uintptr_t)&IPUV_0);
    }
  }
  
  return(addr);

} // checkIpuRange()

//***************************************************************************

void ISP_DumpPerfCounters(uint16_t aFramecount)
{
#ifdef __STANDALONE__  
  uint8_t i;
  unsigned long exec_ipu[12];
  unsigned long stall_ipu[12];
  float exec_mcpf;
  char engine_name[12][3]= {
    "s0","s1","s2","s3","s4","s5","s6","s7",
    "v0","v1","v2","v3"
  };
  
  //IPUS_0.PMONITOR_SAMPLE.R=IPU_PROF_SAMPLE  
  volatile struct IPUS_tag *lpIpus = (volatile struct IPUS_tag *)(0x7C042000UL);
  
  
  exec_ipu[0]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[0] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[1]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[1] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[2]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[2] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[3]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[3] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[4]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[4] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[5]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[5] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[6]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[6] = lpIpus->STALL_DATAHAZARD.R;
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  exec_ipu[7]  = lpIpus->EXEC_COUNTER.R;
  stall_ipu[7] = lpIpus->STALL_DATAHAZARD.R;
  
  volatile struct IPUV_tag *lpIpuv = (volatile struct IPUV_tag *)(0x7C062000UL);

  exec_ipu[8]  = lpIpuv->EXEC_COUNTER.R;
  stall_ipu[8] = lpIpuv->STALL_DATAHAZARD.R;
  lpIpuv       = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  exec_ipu[9]  = lpIpuv->EXEC_COUNTER.R;
  stall_ipu[9] = lpIpuv->STALL_DATAHAZARD.R;
  lpIpuv       = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  exec_ipu[10]  = lpIpuv->EXEC_COUNTER.R;
  stall_ipu[10] = lpIpuv->STALL_DATAHAZARD.R;
  lpIpuv        = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  exec_ipu[11]  = lpIpuv->EXEC_COUNTER.R;
  stall_ipu[11] = lpIpuv->STALL_DATAHAZARD.R;
  
  //#define PRINTSTALL  

  for (i=0; i<12; i++) 
  {
    if (exec_ipu[i]) 
    {
      exec_mcpf=exec_ipu[i]/aFramecount/1000000.0;
      printf("ipu%s took %9.f Mcylces/frame;"
#ifdef PRINTSTALL
       " %4.1f%% stalls;"
#endif
       " %6.2ffps\n",
       engine_name[i],exec_mcpf,
#ifdef PRINTSTALL
       stall_ipu[i]*100.0/exec_ipu[i],
#endif
       500.0/(float)exec_mcpf);
    } // if exec_ipu not 0
  } // for all possible IPUs
#else
  printf("ISP_DumpPerfCounters() NOT IMPLEMENTED\n");
#endif // #ifdef __STANDALONE__  
} // ISP_DumpPerfCounters()

//***************************************************************************

void ISP_DumpIpuState()
{
#ifdef __STANDALONE__
  uint32_t lines_total=0;
  uint32_t pos;
  volatile struct IPUS_tag *lpIpus = (volatile struct IPUS_tag *)(0x7C042000UL);
  
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus0 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus1 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus2 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus3 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus4 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus5 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus6 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpus       = (struct IPUS_tag *)((uintptr_t)lpIpus + 0x1000);
  if ((pos=lpIpus->HOST_POS.R)) {
    printf("final possition ipus7 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  
  volatile struct IPUV_tag *lpIpuv = (volatile struct IPUV_tag *)(0x7C062000UL);

  if ((pos=lpIpuv->HOST_POS.R)) {
    printf("final possition ipuv0 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpuv        = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  if ((pos=lpIpuv->HOST_POS.R)) {
    printf("final possition ipuv1 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpuv        = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  if ((pos=lpIpuv->HOST_POS.R)) {
    printf("final possition ipuv2 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  lpIpuv        = (struct IPUV_tag *)((uintptr_t)lpIpuv + 0x1000);
  
  if ((pos=lpIpuv->HOST_POS.R)) {
    printf("final possition ipuv3 (%4d,%4d)\n",pos>>16,pos&0xffff);
    lines_total+=pos&0xffff;
  }
  
  if (!lines_total) {
    printf("\nNo lines started. Is the Start Trigger correct?\n");
  }
#else
    printf("ISP_DumpIpuState() NOT IMPLEMENTED.\n");
#endif // #ifdef __STANDALONE__
} // ISP_DumpIpuState()

//***************************************************************************

void ISP_PrintGraphStat(SEQ_Buf_t** appFetchedBufferList)
{
#ifdef __STANDALONE__  
  for(volatile uint32_t w=0; w<100000; w++);
  
  printf("FPS: %f\n", gFPS);

  //SEQ_Head_Ptr_t* lpFetchedGraph = NULL;
  //SEQ_Buf_t**   lppFetchedBufferList = arIsp.GraphFetch(&lpFetchedGraph);
  SEQ_Buf_t*    pBuf;
  uint32_t    i=0;
  
  while(NULL != (pBuf=appFetchedBufferList[i]))
  {
    if(pBuf->mpBuf > 1)
    {
      printf("Buf[%d].size: %d ----------\n", i, pBuf->mcLineMax);
      for(uint32_t j=0; j<MAX_CONSUMER; j++)
      {
        if(pBuf->mConsumer[j].mpCons)
        {
          printf("Cons[%d].max: %d\n", j, pBuf->mConsumer[j].mHighWater);
        } // if consumer exists
      } // for all possible consumers
    } // if SRAM buffer allocated
    i++;
  } // while any buffers left

  // *** Seq Msg ***
  SEQ_Message_t lMsg;
  lMsg.mStatus      = SEQ_MSG_STAT_READY;
  lMsg.mType      = SEQ_MSG_TYPE_GET_IDLE_CNT;
  SEQM_idle_cnt_t* lpIdle = (SEQM_idle_cnt_t*)lMsg.mData;
  
  if(SEQ_MessageSend(&lMsg) != SEQ_LIB_SUCCESS)
  {
    VDB_LOG_NOTE("Failed to send a message.\n");
  } // if message send failed

  printf("Idle-L: 0x%08x\n", lpIdle->mIdleL);
  printf("Idle-H: 0x%08x\n", lpIdle->mIdleH);
  
#else
    printf("ISP_PrintGraphStat() NOT IMPLEMENTED.\n");
#endif // #ifdef __STANDALONE__

} // ISP_PrintGraphStat()

//***************************************************************************

/*EOF*/
