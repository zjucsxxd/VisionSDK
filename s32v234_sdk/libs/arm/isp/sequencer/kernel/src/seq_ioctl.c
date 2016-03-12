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
 * \file     seq_ioctl.c
 * \brief    IOCTL functionality of Sequencer driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     30.5.2014
 * \note
 ****************************************************************************/

#include <asm/uaccess.h>	// for get_user and put_user 
#include "s32vs234.h"
#include <linux/mutex.h>	// for semaphore/mutex
#include <linux/string.h>	// for memset
#include <linux/sched.h>	// for current->pid
#include <linux/slab.h>		// for malloc and free


#include "seq.h"
#include "seq_types.h"
#include "seq_ioctl.h"
#include "seq_func.h"
#include "fdma.h"
#include "vdb_log.h"

//*****************************************************************************
// external declarations
//*****************************************************************************

// pointer to fdma driver event handler
extern int32_t (*gpSEQ_FdmaEventHandler)(uint32_t aTdIdx, uint32_t aEventType);

//*****************************************************************************
// global data
//*****************************************************************************
// to remember if a particular graph slot is being used and by whom
//pid_t gGraphSlotUsage[2] = {0,0};

//*****************************************************************************
// local function declarations
//*****************************************************************************

/****************************************************************************/
/** Sends message to Sequencer.
* 
* \param aIoctlParam the IOCT parameter.
* \param aWait       0 if wait for ACK not required, > 0 otherwise
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t MsgSend(unsigned long aIoctlParam, uint8_t aWait);

/****************************************************************************/
/** Requests buffers
* 
* \param aIoctlParam the IOCT parameter.
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t BuffersRequest(unsigned long aIoctlParam);

/****************************************************************************/
/** Queries buffer status.
* 
* \param aIoctlParam the IOCT parameter.
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t BufferQuery(unsigned long aIoctlParam);

/****************************************************************************/
/** Push the buffer.
* 
* \param aIoctlParam the IOCT parameter.
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t BufferPush(unsigned long aIoctlParam);

/****************************************************************************/
/** Pop the buffer
* 
* \param aIoctlParam the IOCT parameter.
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t BufferPop(unsigned long aIoctlParam);

/****************************************************************************/
/** Copies the aux data to user space buffer.
* 
* \param aIoctlParam the IOCT parameter.
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t AuxDataGet(unsigned long aIoctlParam);

/****************************************************************************/
/** Requests the graph execution to be started
* 
* \return SEQ_DRV_SUCCESS if all ok
*     SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t GraphStart(unsigned long aIoctlParam);

/****************************************************************************/
/** Requests the graph execution to be stopped
* 
* \return SEQ_DRV_SUCCESS if all ok
* 	  SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t GraphStop(void);

/****************************************************************************/
/** Get histogram
* 
* \return SEQ_DRV_SUCCESS if all ok
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t HistogramGet(unsigned long aIoctlParam);

//*****************************************************************************
//*****************************************************************************

long SeqIoctl(struct file *apFile,	/* ditto */
		 unsigned int aIoctlNum,	/* number and param for ioctl */
		 unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  uint8_t lWait = 0;
  
  switch (aIoctlNum) {
   
    // *** send message ***
    case IOCTL_SEQ_MSG_SEND_WAIT:
      lWait = 1;
    case IOCTL_SEQ_MSG_SEND:
    {
      MsgSend(aIoctlParam, lWait);
    } // case IOCTL_SEQ_MSG_SEND
      break;
    
    // *** send status message ***
    case IOCTL_SEQ_MSG_STATUS_SEND:
    {
      SEQ_Message_t msg;
      msg.mType = SEQ_MSG_TYPE_STATUS;

      VDB_LOG_NOTE("Sending Status message to Sequencer and waiting for response\n");
      // wait for acknowledgement
      lRet = SEQ_DRV_MsgSend(&msg, 1);
    } // case IOCTL_SEQ_MSG_SEND
      break;
      
    // *** download graph to PRAM ***
    case IOCTL_SEQ_GRAPH_DOWNLOAD:
    {
      lRet = SEQ_DRV_GraphDownload((SEQ_GraphPackage_t*)aIoctlParam);      
    } // case IOCTL_SEQ_GRAPH_DOWNLOAD
      break;
      
    // *** Request framebuffer stream to be created ***
    case IOCTL_SEQ_BUF_REQ:
    {
      lRet = BuffersRequest(aIoctlParam);      
    } // case IOCTL_SEQ_BUF_REQ
      break;
      
    // *** Query buffer state ***
    case IOCTL_SEQ_BUF_QRY:
    {
      lRet = BufferQuery(aIoctlParam);
    } // case IOCTL_SEQ_BUF_QRY
      break;
      
    case IOCTL_SEQ_BUF_PSH:
    {
      lRet = BufferPush(aIoctlParam);
    } // case IOCTL_SEQ_BUF_PSH
      break;
      
    case IOCTL_SEQ_BUF_POP:
    {
      lRet = BufferPop(aIoctlParam);
    } // case IOCTL_SEQ_BUF_POP
      break;
      
    // *** starts the graph execution ***
    case IOCTL_SEQ_START:
    {
      // send start message
      lRet = GraphStart(aIoctlParam);    
      
    } // case IOCTL_SEQ_START
      break;
      
    // *** copies aux data to userspace buffer ***
    case IOCTL_SEQ_AUX_DATA_GET:
    {
      // send start message
      lRet = AuxDataGet(aIoctlParam);      
      
    } // case IOCTL_SEQ_STARTl
      break;
      
    // *** request the sequencer to stop ***
    case IOCTL_SEQ_STOP_WAIT:
      lWait = 1;
    case IOCTL_SEQ_STOP:
    {  
      // send stop message
      lRet = GraphStop();      
      VDB_LOG_NOTE("Stop message sent.\n");
    } // case IOCTL_SEQ_STOP
      break;
      
    // *** resets the SEQ HW and driver ***
    case IOCTL_SEQ_RESET:
    {  
      SEQ_DRV_Reset();      
      VDB_LOG_NOTE("Reset done.\n");
    } // case IOCTL_SEQ_STOP
      break;
    
    // *** boots up the SEQ HW ***
    case IOCTL_SEQ_BOOT:
    {  
      lRet = SEQ_DRV_Boot();
      if(lRet == SEQ_DRV_SUCCESS)
      {
        VDB_LOG_NOTE("Sequencer booted.\n");
      }
      else
      {
        VDB_LOG_ERROR("Sequencer boot failed.\n");
      }
    } // case IOCTL_SEQ_STOP
      break;
    
    case IOCTL_SEQ_HIST_ENABLE:
    { 
      SEQ_IpuEngine_t lIpuIdx = (SEQ_IpuEngine_t)aIoctlParam;
      lRet = SEQ_DRV_IpuHistogramEnable(lIpuIdx);
    } // case IOCTL_SEQ_HIST_ENABLE
      break;
      
    case IOCTL_SEQ_HIST_GET:
    { 
      lRet = HistogramGet(aIoctlParam);
    } // case IOCTL_SEQ_HIST_GET
      break;

    // *** serves SEQ IRQs if any ***
    case IOCTL_SEQ_IRQ_SRV:
    {  
      SEQ_DRV_IrqsProcess();
    } // case IOCTL_SEQ_STOP
      break;
    
    // *** unknown message ***
    default:
    {     
      VDB_LOG_WARNING("Unknown ioctl command %u.\n", aIoctlNum);
      lRet = SEQ_DRV_FAILURE;
    } // default
      break;
  } // switch ioctl command
  
  return lRet;
} // SeqIoctl()

//*****************************************************************************

int32_t MsgSend(unsigned long aIoctlParam, uint8_t aWait)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_Message_t lMsg;
  if (copy_from_user( &lMsg, (SEQ_Message_t *)aIoctlParam, 
      sizeof(SEQ_Message_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  {   
    VDB_LOG_NOTE("Sending a message.\n");

    if(SEQ_DRV_MsgSend(&lMsg, aWait) == SEQ_DRV_SUCCESS)
    {
      VDB_LOG_NOTE("The message was sent\n");
    }
    else
    {
      VDB_LOG_NOTE("Failed to send the message.\n");
      lRet = SEQ_DRV_FAILURE;
    }
  } // else from if copy from user failed
  
  return lRet;
} // MsgSend()

//*****************************************************************************

int32_t AuxDataGet(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_AuxData_t lAuxData;
  
  // copy the aux data destination descriptor
  if (copy_from_user(&lAuxData, (uint8_t *)aIoctlParam, 
      sizeof(SEQ_AuxData_t)) != 0)
  {
    VDB_LOG_ERROR("Failed to read aux data paramateres.\n");
  } // if graph data download failed
  else 
  {
    SEQ_AuxData_t lTmpData;
    lTmpData.mSize  = lAuxData.mSize;
    lTmpData.mpData = lAuxData.mpData;
    SEQ_DRV_PramAuxDataGet(&lTmpData);
  
    // copy PRAM back to user
    if (copy_to_user(lAuxData.mpData, lTmpData.mpData, lTmpData.mSize) != 0)
    {
      VDB_LOG_ERROR("Failed to copy the aux data to user space.\n");
      lRet = -EIO;
    } // if copy to user failed
    else
    {
      if (copy_to_user( (uint8_t *)aIoctlParam, 
                        (uint8_t*)&lAuxData, 
                        sizeof(SEQ_AuxData_t)) != 0)
      {
        VDB_LOG_ERROR("Failed to copy the aux data structure to user space.\n");
        lRet = -EIO;
      } // if copy to user failed
    }
    
    VDB_LOG_NOTE("AuxDataPushed to user-space.\n");    
  } // else form if graph data download failed
  
  return lRet;
} // AuxDataGet(SEQ_AuxData_t *apData)

//*****************************************************************************

int32_t BuffersRequest(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_BufferRequest_t lRequest;
  
  if (copy_from_user( &lRequest, (SEQ_BufferRequest_t *)aIoctlParam, 
      sizeof(SEQ_BufferRequest_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  {
    size_t lBufferListSz = lRequest.mCnt * sizeof(uint32_t);
    uint32_t *lpBufferArr = kmalloc(lBufferListSz, GFP_KERNEL);
    if( lpBufferArr != NULL)
    {
      if (copy_from_user( lpBufferArr, (uint32_t*)lRequest.mpBuffers, 
          lBufferListSz) != 0)
      {
        VDB_LOG_ERROR("Copy from user failed.\n");
        lRet = -EIO;
      } // if copy from user failed
      else
      { 
        lRequest.mpBuffers = lpBufferArr;
        if(SEQ_DRV_FrmBuffersRequest(&lRequest) != SEQ_DRV_SUCCESS)
        {
          VDB_LOG_ERROR("Frame buffers request failed.\n");
          lRet = SEQ_DRV_FAILURE;
        } // if request failed
        kfree(lpBufferArr);
      } // else from if copy from user failed
    } // if buffer array allocated
    else
    {
      VDB_LOG_ERROR("Failed to allocate buffer array.\n");
      lRet = SEQ_DRV_FAILURE;
    } // else from if buffer array allocated
  } // else from if copy from user failed
  
  return lRet;
} // BuffersRequest()

//*****************************************************************************

int32_t BufferQuery(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_FrmBufferInfo_t lBuffInfo;
      
  if (copy_from_user( &lBuffInfo, (SEQ_FrmBufferInfo_t *)aIoctlParam, 
      sizeof(SEQ_FrmBufferInfo_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  { 
    // query the buffer
    if(SEQ_DRV_FrmBufferQuery(&lBuffInfo) != SEQ_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Frame buffers query failed.\n");
      lRet = SEQ_DRV_FAILURE;
    }
    
    // copy BufferInfo back to user
    if (copy_to_user((SEQ_FrmBufferInfo_t *)aIoctlParam, &lBuffInfo, 
        sizeof(SEQ_FrmBufferInfo_t)) != 0)
    {
      VDB_LOG_ERROR("Failed to copy the buffer info to user space.\n");
      lRet = -EIO;
    } // if copy to user failed
  } // else from if copy from user failed
  
  return lRet;
} // BufferQuery()

//*****************************************************************************

int32_t BufferPush(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_FrmBufferInfo_t lBuffInfo;
      
  if (copy_from_user( &lBuffInfo, (SEQ_FrmBufferInfo_t *)aIoctlParam, 
      sizeof(SEQ_FrmBufferInfo_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  { 
    // Push the buffer
    if(SEQ_DRV_FrmBufferPush(&lBuffInfo) != SEQ_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Frame buffers query failed.\n");
      lRet = SEQ_DRV_FAILURE;
    }
  } // else from if copy from user failed
  
  return lRet;
} // BufferPush()

//*****************************************************************************

int32_t BufferPop(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_FrmBufferInfo_t lBuffInfo;
      
  if (copy_from_user( &lBuffInfo, (SEQ_FrmBufferInfo_t *)aIoctlParam, 
      sizeof(SEQ_FrmBufferInfo_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  { 
    // Pop the buffer
    if(SEQ_DRV_FrmBufferPop(&lBuffInfo) != SEQ_DRV_SUCCESS)
    {
      VDB_LOG_NOTE("Frame buffers query failed.\n");
      lRet = SEQ_DRV_FAILURE;
    }
    
    // copy BufferInfo back to user
    if (copy_to_user((SEQ_FrmBufferInfo_t *)aIoctlParam, &lBuffInfo, 
        sizeof(SEQ_FrmBufferInfo_t)) != 0)
    {
      VDB_LOG_ERROR("Failed to copy the buffer info to user space.\n");
      lRet = -EIO;
    } // if copy to user failed
  } // else from if copy from user failed
  
  return lRet;
} // BufferPush()

//*****************************************************************************

int32_t GraphStart(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_StartCfg_t lStartCfg = {0};
  
  if (copy_from_user( &lStartCfg, (SEQ_StartCfg_t *)aIoctlParam, 
      sizeof(SEQ_StartCfg_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  {
    lRet = SEQ_DRV_GraphStart(lStartCfg.mFrames2Grab, lStartCfg.mInputLines);
    if( lRet != SEQ_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Frame buffers request failed.\n");
    } // if start failed
  } // else from if copy from user failed
  
  return lRet;
} // GraphStart()

//*****************************************************************************

int32_t GraphStop()
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_Message_t lMsg;
  lMsg.mType = SEQ_MSG_TYPE_STOP;

  SEQ_DRV_MsgSend(&lMsg, 0);
  
  VDB_LOG_NOTE("Stop message sent.\n");
  
  return lRet;
} // GraphStop()

//*****************************************************************************

int32_t HistogramGet(unsigned long aIoctlParam)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_IpuHistHead_t lHist;
  SEQ_IpuHist_t *lpHist = (SEQ_IpuHist_t*)0;
  
  if (copy_from_user( &lHist, (uint8_t*)aIoctlParam, 
      sizeof(SEQ_IpuHistHead_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  { 
    // get address of the histogram data
    lHist.mpData = (uint32_t*)(aIoctlParam + (uintptr_t)&(lpHist->mpData[0]));
    
    lRet = SEQ_DRV_IpuHistogramGet(&lHist);
    
    // copy peak & peak address to user
    if (copy_to_user((uint8_t*)aIoctlParam, &lHist, 
        sizeof(uint32_t) * 2) != 0)
    {
      VDB_LOG_ERROR("Failed to copy hidtogram peak info to user.\n");
      lRet = -EIO;
    } // if copy to user failed        
  } // else from if copy from user failed
  return lRet;
} // HistogramGet()

//*****************************************************************************