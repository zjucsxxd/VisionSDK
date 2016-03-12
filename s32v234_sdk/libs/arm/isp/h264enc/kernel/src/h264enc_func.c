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
 * \file     h264enc_ioctl.c
 * \brief    IOCTL functionality of H264 Encoder driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     20.6.2014
 * \note
 ****************************************************************************/

#include <linux/kernel.h>	// We're doing kernel work
#include <linux/module.h>	// Specifically, a module 
#include "s32vs234.h"
#include <linux/interrupt.h>    // For interrupts
#include <asm/siginfo.h>	// siginfo
#include <linux/sched.h>	// send_sig_info
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>	// for malloc and free
#include <linux/delay.h>	// for msleep
#include <asm/io.h>		// for ioremap
#include "h264enc.h"
#include "h264enc_func.h"
#include "vdb_log.h"

//*****************************************************************************
// types
//*****************************************************************************

//*****************************************************************************
// constants
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

// current user process PID
pid_t gH264EncUserPid;

// H264 Encoder locking mutex
extern struct mutex gH264EncMutex;

spinlock_t gDataLock;

// Encoder registers
H264ENC_Regs_t *gpH264EncRegs = NULL;
int32_t gIrqNum = 0;
uint32_t gPixLinesReady = 0; ///< number of lines ready to be fetched

// Callback function pointers
H264ENC_Callbacks_t gCallbacks = {0};

//*****************************************************************************
// local functions
//*****************************************************************************

/****************************************************************************/
/** Initializes H264Enc driver internal data.
* 
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
int32_t H264EncDrvDataInit(void);

/****************************************************************************/
/** Registers H264Enc IRQs.
* 
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
int32_t H264EncIrqsRequest(void);

/****************************************************************************/
/** Releases H264Enc IRQs.
* 
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
void H264EncIrqsFree(void);

/****************************************************************************/
/** Maps H264Enc register space.
*  
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
int32_t H264EncMap(void);

/****************************************************************************/
/** UnMaps H264Enc register space, PRAM, CRAM and KRAM.
*  
*****************************************************************************/
void H264EncUnmap(void);

//*****************************************************************************
// exported functions
//*****************************************************************************

/****************************************************************************/
/** Resets the H264Enc HW and driver data.
*  
*****************************************************************************/
void H264ENC_Reset(void);

/****************************************************************************/
/** Informs the encoder how many new MBRW lines have been added to the input 
*   buffer and are ready to be fetched.
*  
*****************************************************************************/
void H264ENC_FrameDone(void);

/****************************************************************************/
/** H264Enc IRQ handler for the FPGA version.
* All H264Enc IRQs are orred to just one interrupt signal on FPGA. Based on 
* what bits are set in registers it calls the MsgIrq or MsgAckIrq handlers. 
* 
* \param aIrq	IRQ number invoking the handler
* \param apDev_id	pointer to device specific data (ignored) 
* 
* \return IRQ_HANDLED
*
*****************************************************************************/
irqreturn_t H264ENC_FpgaIrqHandler(int32_t aIrq, void *apDev_id);

irqreturn_t H264ENC_InpFrameDoneIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_BStrNewRowIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_OutBufAlarmIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_InpLineThreshIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_InpLcountAlarmIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_EncOutOfSyncIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_MRowReadIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_MRowFetchOvfIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_OutBuffOvfIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_BStrFrameDoneIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_BrateTooHighIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_OutBufAlmostFullIrqHandler(int32_t aIrq, void *apDev_id);
irqreturn_t H264ENC_OutBufFullIrqHandler(int32_t aIrq, void *apDev_id);

void FrameDoneDefClbck(void);
void PixLowDefClbck(void);
void BitAlarmDefClbck(H264ENC_BsAlarmType_t aType);
void ErrorDefClbck(H264ENC_ErrType_t aType);

/***************************************************************************/
/** Sends a signal to userspace.
 *
 * \param aPid PID of the user process
 * \param aValue uint32 value to be passed with the signal
 *
 * \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
 ***************************************************************************/
uint32_t Sig2UsrSend(pid_t aPid, int32_t aValue);

/***************************************************************************/
/** Prints out the memory content by bytes, 4 bytes to one row.
 *
 * \param apMem base memory address to be printed
 * \param aSize number of bytes to print
 * \param apCation string caption to be printed before the memory print
 *
 * \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
 ***************************************************************************/
void MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption);

/***************************************************************************/
/** Prints out the h264 encoder registers
 *
 * \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
 ***************************************************************************/
void H264EncRegPrint(void);

//*****************************************************************************

int32_t H264ENC_Setup()
{
  uint32_t lRet = H264ENC_DRV_SUCCESS;
  
  // symbols to get from
  //

  // prepare global data
  //
  
  // *** initialize internal data ***   
  if(H264EncDrvDataInit() != H264ENC_DRV_SUCCESS)
  {
    lRet = H264ENC_DRV_FAILURE;
    goto data_init_failed;
  } // if driver data init failed                 
  
  // *** register IRQs ***
  if(H264EncIrqsRequest() != H264ENC_DRV_SUCCESS)
  {
    lRet = H264ENC_DRV_FAILURE;
    goto irq_request_failed;
  }
  
  H264EncRegPrint();
  
  // *** Error handling ***
  if(lRet != H264ENC_DRV_SUCCESS)
  {
    VDB_LOG_NOTE("In error handling.\n");
      H264EncIrqsFree();
    irq_request_failed:
      H264EncUnmap();
    data_init_failed:
      ;
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Canceling H264Enc driver insmod.\n");
  } // if error detected;
  
  VDB_LOG_NOTE("Leaving Setup\n");
       
  return lRet;
} // H264ENC_Setup()

//****************************************************************************

int32_t H264EncDrvDataInit()
{
  int32_t lRet = H264ENC_DRV_SUCCESS;
  // map H264Enc related blocks
  if(H264EncMap() != H264ENC_DRV_SUCCESS)
  {
    lRet = H264ENC_DRV_FAILURE;
  } // if H264Enc mapping failed
  else
  { 
    // TODO: init in future
    // reset callback pointers
    gCallbacks.mFrameDone 	= NULL;
    gCallbacks.mPixDataLow 	= NULL;
    gCallbacks.mBitstreamAlarm	= NULL;
    gCallbacks.mError		= NULL;
    gCallbacks.mFunc2Set = H264ENC_CLB_FRM_DONE | H264ENC_CLB_PIX_LOW | H264ENC_CLB_BIT_ALARM | H264ENC_CLB_ERR;
    H264ENC_CallbackSet(&gCallbacks);
    
    // initialize utilities
    mutex_init(&gH264EncMutex);
    spin_lock_init(&gDataLock);
    gPixLinesReady = 0;
    
    VDB_LOG_NOTE("getting lock\n");
    spin_lock(&gDataLock);
    VDB_LOG_NOTE("got lock\n");
    spin_unlock(&gDataLock);
    VDB_LOG_NOTE("unlocked again\n");
    
    // *** put H264Enc registers to default ***
    gpH264EncRegs->MCR.B.SW_RESET = 1;
    msleep(100);
    gpH264EncRegs->MCR.B.SW_RESET = 0;
    
    //spin_unlock(&gDataLock);
    
  } // else from if H264Enc mapping failed
  
  return lRet;
} // H264EncDrvDataInit()

//*****************************************************************************
  
int32_t H264EncMap()
{
  int32_t lRet = H264ENC_DRV_SUCCESS;
  // map CTRL BLK registers
  gpH264EncRegs = (H264ENC_Regs_t*)ioremap(H264ENC_BASE, H264ENC_SIZE);
  if(gpH264EncRegs == NULL)
  {
    VDB_LOG_ERROR("Failed to map H264ENC registers.\n");
    lRet = H264ENC_DRV_FAILURE;
  } // if H264Enc registers not mapped
  else
  {
    VDB_LOG_NOTE("H264 Encoder registers mapped OK.\n");
  } // else from if registers not mapped
  
  return lRet;
} // H264EncMap()

//*****************************************************************************

void H264EncUnmap()
{
  iounmap(gpH264EncRegs);
  
  gpH264EncRegs = NULL;
} // H264EncUnmap()

//*****************************************************************************

int32_t H264EncIrqsRequest()
{
  int32_t lRet = H264ENC_DRV_SUCCESS;

  if (request_irq(H264ENC_IRQ_FPGA, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  else
  {
    VDB_LOG_ERROR("H264 Encoder FPGA IRQ requested successfully.\n");
  }
  
  // enable all IRQs
  gpH264EncRegs->IER.R = 0xffffffff;

#if 0
  if (request_irq(89, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  
  if (request_irq(90, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  
  if (request_irq(91, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  
  if (request_irq(92, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  
  if (request_irq(93, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
  
  if (request_irq(94, &H264ENC_FpgaIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request H264 Encoder FPGA IRQ.\n");
  } // if request for IRQ failed
#endif // if 0

  printk("Irqs requested.\n");
  
/*  
  if (request_irq(H264ENC_IRQ_MSG, &H264ENC_MsgIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
  {
    lRet = H264ENC_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request IRQ for incomming message signal.\n");
  } // if request for MSG IRQ failed
  else
  {
    if (request_irq(H264ENC_IRQ_MSG_ACK, &H264ENC_MsgAckIrqHandler, IRQF_TRIGGER_RISING, H264ENC_DEVICE_NAME, NULL))
    {
      lRet = H264ENC_DRV_FAILURE;
      free_irq(H264ENC_IRQ_MSG, NULL);
      VDB_LOG_ERROR("Failed to request IRQ for outbound message acknowlodge signal.\n");
    } // if request for MSG_ACK IRQ failed
  } // else from if request DONE IRQ failed
*/
  return lRet;
} // H264EncIrqsRequest()

//*****************************************************************************

void H264EncIrqsFree()
{
  free_irq(H264ENC_IRQ_FPGA, NULL);
/*
  free_irq(H264ENC_IRQ_MSG, NULL);
  free_irq(H264ENC_IRQ_MSG_ACK, NULL); 
*/
} // H264EncIrqsFree()

//*****************************************************************************

void H264ENC_Close()
{  
  
  H264EncIrqsFree();
  H264EncUnmap();
  
  // TODO: reset
  
} // H264ENC_Close()

uint32_t gIrqCounter = 0;

//*****************************************************************************

irqreturn_t H264ENC_FpgaIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  uint32_t lIsrReg = gpH264EncRegs->ISR.R;
  
  VDB_LOG_NOTE("=========== FPGA H264 ENC Irq received %d 0x%x #%u===========\n", aIrq, lIsrReg, gIrqCounter);
  gIrqCounter ++;
  gIrqNum = aIrq;
  
  while(gpH264EncRegs->ISR.R > 0)
  {
    // check the IRQ bits in register & call appropriate function
    if(gpH264EncRegs->ISR.B.VI_FRAME_DONE_INT == 1)
    {
      lRet = H264ENC_InpFrameDoneIrqHandler(aIrq, apDev_id); 
    } // if Input frame done
    
    if(gpH264EncRegs->ISR.B.BS_NEW_ROW_INT == 1)
    {
      lRet = H264ENC_BStrNewRowIrqHandler(aIrq, apDev_id);
    } // if bistream new row
    
    //VDB_LOG_NOTE("Afrer bs newrow 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.CB_ALARM_INT == 1)
    {
      lRet = H264ENC_OutBufAlarmIrqHandler(aIrq, apDev_id);
    } // if circular buffer alarm address reached
    
    //VDB_LOG_NOTE("before vi_line_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.VI_LINE_INT == 1)
    {
      lRet = H264ENC_InpLineThreshIrqHandler(aIrq, apDev_id);
    } // if Input lines threshold reached
    
    //VDB_LOG_NOTE("before vi_lcount_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.VI_LCOUNT_ALARM_INT == 1)
    {
      lRet = H264ENC_InpLcountAlarmIrqHandler(aIrq, apDev_id);
    } // if Input line alarm reached
    
    //VDB_LOG_NOTE("before enc_oos_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.ENC_OOS_INT == 1)
    {
      lRet = H264ENC_EncOutOfSyncIrqHandler(aIrq, apDev_id);
    } // if encoder out of sync
    
    //VDB_LOG_NOTE("before mbrw_done_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.MBRW_DONE_INT == 1)
    {
      lRet = H264ENC_MRowReadIrqHandler(aIrq, apDev_id);
    } // if Macroblock read from SRAM
    
    //VDB_LOG_NOTE("before mbrw_ff_ovf_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.MBRW_FF_OVF_INT == 1)
    {
      lRet = H264ENC_MRowFetchOvfIrqHandler(aIrq, apDev_id);
    } // if Macroblock fetch fifo overflow
    
    //VDB_LOG_NOTE("before out_cbuf_ovf 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.OUT_CBUF_OVF_INT == 1)
    {
      lRet = H264ENC_OutBuffOvfIrqHandler(aIrq, apDev_id);
    } // if circular buffer overflow
    
    //VDB_LOG_NOTE("before bs_frame_done_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.BS_FRAME_DONE_INT == 1)
    {
      lRet = H264ENC_BStrFrameDoneIrqHandler(aIrq, apDev_id);
    } // if frame bistream done
    
    //VDB_LOG_NOTE("before br_too_high_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.BR_TOO_HIGH_INT == 1)
    {
      lRet = H264ENC_BrateTooHighIrqHandler(aIrq, apDev_id);
    } // if bit rate too high
    
    //VDB_LOG_NOTE("before bs_fifo_almost_full_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.BS_FIFO_ALMOST_FULL_INT == 1)
    {
      lRet = H264ENC_OutBufAlmostFullIrqHandler(aIrq, apDev_id);
    } // if bit rate too high
    
    //VDB_LOG_NOTE("before bs_fifo_full_int 0x%x\n",gpH264EncRegs->ISR.B);
    
    if(gpH264EncRegs->ISR.B.BS_FIFO_FULL_INT == 1)
    {
      lRet = H264ENC_OutBufFullIrqHandler(aIrq, apDev_id);
    } // if bit rate too high
  } // while there is some ISR
  
  printk("ISR status: 0x%x\n", gpH264EncRegs->ISR.R);
  //gpH264EncRegs->ISR.R = gpH264EncRegs->ISR.R;
  printk("ISR status 2: 0x%x\n", gpH264EncRegs->ISR.R);
  return lRet;  
} //H264ENC_FpgaIrqHandler()

//*****************************************************************************

irqreturn_t H264ENC_InpFrameDoneIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x1;
  
  gCallbacks.mFrameDone();
  printk("Input frame done\n");
  
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_BStrNewRowIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x2;
  printk("Bit stream new row %x\n", gpH264EncRegs->OUT_CBUF_CURR_ADDR.R);
  
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_OutBufAlarmIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  // reprogram alarm address - should be done after data were fetched
  // gpH264EncRegs->OUT_CBUF_ALARM_ADDR.R += 0x400;
  
  VDB_LOG_NOTE("Beginning handler.\n");
  
  gpH264EncRegs->ISR.R = 0x4;
  
  // run BitstreamAlarm Clbck,
  gCallbacks.mBitstreamAlarm(H264ENC_BSA_ADDR);
 
  printk("Output buffer alarm. Curr address: %x\n", gpH264EncRegs->OUT_CBUF_CURR_ADDR.R);
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_InpLineThreshIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x8;
  
  printk("Input line threshold\n");
  
  gCallbacks.mPixDataLow();
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_InpLcountAlarmIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x10;
  
  gCallbacks.mBitstreamAlarm(H264ENC_BSA_RATE);
  
  printk("Lcount alarm %x\n", gpH264EncRegs->OUT_CBUF_CURR_ADDR.R);
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_EncOutOfSyncIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  // TODO: run proper reset
  gpH264EncRegs->MCR.B.SW_RESET = 1;
  
  gpH264EncRegs->MCR.B.SW_RESET = 0;
  
  gpH264EncRegs->ISR.R = 0x20;
  
  gCallbacks.mError(H264ENC_ERR_ENC_OOS);

  printk("Encoder out of sync\n");
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_MRowReadIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  VDB_LOG_NOTE("Beginning with %u.\n", gpH264EncRegs->LINE_CNTR_STAT.R);
  
  
  gpH264EncRegs->ISR.R = 0x40;
  
  //spin_lock(&gDataLock);
  VDB_LOG_NOTE("Spin lock obtained.\n");
  if(gPixLinesReady)
  {
    // fetch next row
    gPixLinesReady-= 32;
    gpH264EncRegs->FETCH_MBRW.R = 1;
    gpH264EncRegs->FETCH_MBRW.R = 1;
    gpH264EncRegs->FETCH_MBRW.R = 1;
    VDB_LOG_NOTE("Fetch sent.\n");
  }   
  //spin_unlock(&gDataLock);
  
  printk("MB row read %x\n", gpH264EncRegs->OUT_CBUF_CURR_ADDR.R);
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_MRowFetchOvfIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x80;
  
  //spin_lock(&gDataLock);
  if(gPixLinesReady)
  {
    // remember one line was not fetched
    gPixLinesReady+=16;
  }   
  //spin_unlock(&gDataLock);
  
  printk("Fetch OVF\n");
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_BStrFrameDoneIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  gpH264EncRegs->ISR.R = 0x100;
  
  printk("Output frame done %x\n", gpH264EncRegs->OUT_CBUF_VEND_ADDR.R);
  VDB_LOG_NOTE("Line cnt status\n", gpH264EncRegs->LINE_CNTR_STAT.R);
  
  // reset encoding after one frame done
  gpH264EncRegs->MCR.B.SW_RESET = 1;
  
  gCallbacks.mFrameDone();
  
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_OutBuffOvfIrqHandler(int32_t aIrq, void *apDev_id)
{ 
  int32_t lRet = IRQ_HANDLED;
  
  // reset
  gpH264EncRegs->MCR.B.SW_RESET = 1;
  
  gpH264EncRegs->ISR.R = 0x200;
  
  printk("Output buffer OVF\n");
  gCallbacks.mError(H264ENC_ERR_CBUF_OVF);
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_BrateTooHighIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  // reset
  gpH264EncRegs->MCR.B.SW_RESET = 1;
  
  gpH264EncRegs->ISR.R = 0x400;
 
  gCallbacks.mError(H264ENC_ERR_BR_TOO_HIGH);
  printk("Bitrate too high\n");
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_OutBufAlmostFullIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;  
  
  gpH264EncRegs->ISR.R = 0x800;
  
  printk("Output buffer almost full\n");
  return lRet;
}

//*****************************************************************************

irqreturn_t H264ENC_OutBufFullIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;
  
  // reset
  gpH264EncRegs->MCR.B.SW_RESET = 1;
  
  gpH264EncRegs->ISR.R = 0x1000;
  
  gCallbacks.mError(H264ENC_ERR_BS_FIFO_FULL);
  
  printk("Output buffer full\n");
    
  return lRet;
}

//*****************************************************************************

/*irqreturn_t H264ENC_DoneIrqHandler(int32_t aIrq, void *apDev_id)
{
  struct siginfo info;
  int32_t ret = IRQ_HANDLED;
  struct pid *pid_struct;
  struct task_struct *t;
  
  // read registers - remeber event
    
  // send the signal to user space
  memset(&info, 0, sizeof(struct siginfo));
  info.si_signo = H264ENC_EVENT_SIGNAL;
  info.si_code = SI_QUEUE;
  //info.si_int = ((H264ENC_DONE_EVENT<<8) | tdIdx);

  rcu_read_lock();
  //pid_struct = find_get_pid(gTdmArr[tdIdx].mOwnerProcId);
  t = pid_task(pid_struct,PIDTYPE_PID);
  if(t == NULL){
    //VDB_LOG_ERROR("H264ENC Done IRQ handler - No such pid %u.\n", gTdmArr[tdIdx].mOwnerProcId);
    rcu_read_unlock();
      ret = -1;
  } // if no such pid
  else
  {
    rcu_read_unlock();
    ret = send_sig_info(H264ENC_EVENT_SIGNAL, &info, t);    //send the signal
    if (ret < 0) {
      VDB_LOG_ERROR("H264ENC IRQ handler - Error sending signal for DONE event.\n");
    } // if sending signal failed
  } // else if no such pid
  
  // reset the done bit in STAT register
  //REG_FIELD_WRITE(H264ENC_XFR_STAT, XFR_DONE, 0x1);
  
  VDB_LOG_NOTE("H264ENC DONE IRQ handled.\n");
  return ret;
} // H264ENCDoneIrqHandler()*/

//*****************************************************************************

void H264ENC_Config(const H264ENC_Config_t *apcConfig)
{
  // TODO: add spinlock
  
  gpH264EncRegs->MCR.B.DATA_MODE_CHR    = apcConfig->mDataModeChroma;	
  gpH264EncRegs->MCR.B.FETCH_TRIG       = apcConfig->mFetchTrig;  		
  gpH264EncRegs->MCR.B.VI_COLOR_FMT     = apcConfig->mColorFormat;		
  gpH264EncRegs->MCR.B.VI_BIT_WIDTH     = apcConfig->mBitWidth;		
  
  gpH264EncRegs->VCR.B.FR_WIDTH         = apcConfig->mFrameWidth >> 1;  	
  gpH264EncRegs->VCR.B.FR_HEIGHT        = apcConfig->mFrameHeight >> 1;	    
  
  gpH264EncRegs->ULLVC_FRAME_RATE.R        = apcConfig->mFrameRate;
  gpH264EncRegs->ULLVC_QP_INIT.R           = apcConfig->mQpInit;
  gpH264EncRegs->ULLVC_QP_RANGE.B.MIN      = apcConfig->mQpMin;
  gpH264EncRegs->ULLVC_QP_RANGE.B.MAX      = apcConfig->mQpMax;
  gpH264EncRegs->ULLVC_QP_FALLBACK_LIMIT.R = apcConfig->mQpFallback;
  
  gpH264EncRegs->ULLVC_BITS_PER_MB_ROW.R = apcConfig->mBitsPerMbrw;
  gpH264EncRegs->ULLVC_QP_INC.B.DIFF_0   = apcConfig->mQpIncDiff0;
  gpH264EncRegs->ULLVC_QP_INC.B.DIFF_1   = apcConfig->mQpIncDiff1;
  gpH264EncRegs->ULLVC_QP_INC.B.DIFF_2   = apcConfig->mQpIncDiff2;
  gpH264EncRegs->ULLVC_QP_INC.B.OFFSET   = apcConfig->mQpIncOffset;
  gpH264EncRegs->ULLVC_QP_INC_THLD[0].R  = apcConfig->mQpIncThld0; 
  gpH264EncRegs->ULLVC_QP_INC_THLD[1].R  = apcConfig->mQpIncThld1; 
  gpH264EncRegs->ULLVC_QP_INC_THLD[2].R  = apcConfig->mQpIncThld2; 
  
  gpH264EncRegs->ULLVC_QP_DEC.B.DIFF_0   = apcConfig->mQpDecDiff0;
  gpH264EncRegs->ULLVC_QP_DEC.B.DIFF_1   = apcConfig->mQpDecDiff1;
  gpH264EncRegs->ULLVC_QP_DEC.B.DIFF_2   = apcConfig->mQpDecDiff2;
  gpH264EncRegs->ULLVC_QP_DEC.B.OFFSET   = apcConfig->mQpDecOffset;
  gpH264EncRegs->ULLVC_QP_DEC_THLD[0].R  = apcConfig->mQpDecThld0; 
  gpH264EncRegs->ULLVC_QP_DEC_THLD[1].R  = apcConfig->mQpDecThld1; 
  gpH264EncRegs->ULLVC_QP_DEC_THLD[2].R  = apcConfig->mQpDecThld2; 
  
  gpH264EncRegs->ULLVC_WAIT_FRAMES.R     = apcConfig->mWaitFrames;
  
  gpH264EncRegs->ULLVC_DISABLE_DBF.R     = apcConfig->mDisableDbf;
};

//*****************************************************************************

void H264ENC_BuffersSet(const H264ENC_Buffers_t *apcBuffers)
{
  //spin_lock(&gDataLock);
  // Input
  gpH264EncRegs->VI_CBUF_Y_ADDR.R       = apcBuffers->mY.mPhysAddr;
  gpH264EncRegs->VI_CBUF_CB_ADDR.R      = apcBuffers->mU.mPhysAddr;
  gpH264EncRegs->VI_CBUF_CR_ADDR.R      = apcBuffers->mV.mPhysAddr;
  gpH264EncRegs->VI_NRLINES.B.Y_LINES   = apcBuffers->mLineNum;
  
  // Output
  gpH264EncRegs->OUT_CBUF_START_ADDR.R  = apcBuffers->mBitstream.mPhysAddr;
  gpH264EncRegs->OUT_CBUF_END_ADDR.R    = apcBuffers->mBitstream.mPhysAddr + apcBuffers->mBitstream.mSize - 8;
  
  // Rateflow control
  if(apcBuffers->mBankStride < 8)
  {
    gpH264EncRegs->RATE_FLOW_CTRL.B.EN    = 1;
  
    gpH264EncRegs->RATE_FLOW_CTRL.B.BANK_STRIDE_LTH = apcBuffers->mBankStride;
  } // if rate flow control on
  else
  {
    gpH264EncRegs->RATE_FLOW_CTRL.B.EN    = 0;
  }  // if rate flow control off
  
  //spin_unlock(&gDataLock);
};

//*****************************************************************************
//*** Callback handling *******************************************************
//*****************************************************************************

void FrameDoneDefClbck(void)
{
  if(Sig2UsrSend(gH264EncUserPid, H264ENC_FRAME_DONE_SIGNAL) != H264ENC_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to send the FRAME_DONE signal to userspace.\n");
  }
};

//*****************************************************************************

void PixLowDefClbck(void)
{
  if(Sig2UsrSend(gH264EncUserPid, H264ENC_PIX_DATA_LOW_SIGNAL) != H264ENC_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to send the PIX_DATA_LOW signal to userspace.\n");
  }
};

//*****************************************************************************

void BitAlarmDefClbck(H264ENC_BsAlarmType_t aType)
{
  if(Sig2UsrSend(gH264EncUserPid, H264ENC_BIT_ALARM_SIGNAL) != H264ENC_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to send the BIT_ALARM signal to userspace.\n");
  }
};

//*****************************************************************************

void ErrorDefClbck(H264ENC_ErrType_t aType)
{
  if(Sig2UsrSend(gH264EncUserPid, H264ENC_ERROR_SIGNAL) != H264ENC_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to send the ERROR signal to userspace.\n");
  }
};

//*****************************************************************************

void H264ENC_CallbackSet(const H264ENC_Callbacks_t *apcClbck)
{
  //spin_lock(&gDataLock);
  
  VDB_LOG_NOTE("Callbacks setup\n");
  
  // *** Frame done ***
  if(apcClbck->mFunc2Set & H264ENC_CLB_FRM_DONE)
  {
    if(apcClbck->mFrameDone == NULL)
    {
      VDB_LOG_NOTE("FRM_DONE default\n");
      gCallbacks.mFrameDone = &FrameDoneDefClbck;
    } // if fun is NULL
    else
    {
      gCallbacks.mFrameDone = apcClbck->mFrameDone;
    } // else from if fun is NULL
  } // if Frame done to be set
  
  // *** Pixel data low ***
  if(apcClbck->mFunc2Set & H264ENC_CLB_PIX_LOW)
  {
    if(apcClbck->mPixDataLow == NULL)
    {
      VDB_LOG_NOTE("PIX_LOW default\n");
      gCallbacks.mPixDataLow = &PixLowDefClbck;
      gpH264EncRegs->VI_ALARM.B.MBRW_THLD = 2;
      
    } // if fun is NULL
    else
    {
      gCallbacks.mPixDataLow              = apcClbck->mPixDataLow; 
      gpH264EncRegs->VI_ALARM.B.MBRW_THLD = apcClbck->mMbrwInterval;
    } // else from if fun is NULL
  } // if Frame done to be set
  
  // *** Output buffer alarm ***
  if(apcClbck->mFunc2Set & H264ENC_CLB_BIT_ALARM)
  {
    if(apcClbck->mBitstreamAlarm == NULL)
    {
      VDB_LOG_NOTE("BIT_ALARM default\n");
      gCallbacks.mBitstreamAlarm                = &BitAlarmDefClbck;
      gpH264EncRegs->VI_ALARM.B.MBRW_ALARM_THLD = 2;
      gpH264EncRegs->OUT_CBUF_ALARM_ADDR.R      = 0xff00; 
    } // if fun is NULL
    else
    {
      gCallbacks.mBitstreamAlarm                = apcClbck->mBitstreamAlarm; 
      gpH264EncRegs->VI_ALARM.B.MBRW_ALARM_THLD = apcClbck->mMaxMbrwOut;
      gpH264EncRegs->OUT_CBUF_ALARM_ADDR.R      = apcClbck->mOutAlarmAddr; 
    } // else from if fun is NULL
  } // if Frame done to be set
  
  // *** Error ***
  if(apcClbck->mFunc2Set & H264ENC_CLB_ERR)
  {
    if(apcClbck->mError == NULL)
    {
      VDB_LOG_NOTE("FRM_ERR default\n");
      gCallbacks.mError = &ErrorDefClbck;
    } // if fun is NULL
    else
    {
      gCallbacks.mError = apcClbck->mError; 
    } // else from if fun is NULL
  } // if Frame done to be set
  
  //spin_unlock(&gDataLock);
}

//*****************************************************************************

void H264ENC_StatusGet(H264ENC_Status_t *apcStatus)
{
  VDB_LOG_ERROR("%s: \n", __func__);
  //spin_lock(&gDataLock);
  
  apcStatus->mOutCurrentAddress    = gpH264EncRegs->OUT_CBUF_CURR_ADDR.R;
  apcStatus->mLastFrmEndAddress    = gpH264EncRegs->OUT_CBUF_VEND_ADDR.R;
  apcStatus->mInterruptStatus      = gpH264EncRegs->ISR.R;
  apcStatus->mOutLineCounter       = gpH264EncRegs->LINE_CNTR_STAT.R;
  apcStatus->mInLineCounter        = gPixLinesReady;  
  
  //spin_unlock(&gDataLock);
}

//*****************************************************************************

void H264ENC_LinesFetch(uint32_t aMoreLines)
{
  VDB_LOG_ERROR("%s:\n", __func__);
  //spin_lock(&gDataLock);
  
  // invoke fetch if 0 before
  if(gPixLinesReady == 0)
  {
    // fetch next row
    gpH264EncRegs->FETCH_MBRW.R = 1;
    gpH264EncRegs->FETCH_MBRW.R = 1;
    gPixLinesReady += aMoreLines - 2;
    VDB_LOG_ERROR("%s:\n", __func__);
  }
  else
  {
    gPixLinesReady += aMoreLines;
  }  
  
  //spin_unlock(&gDataLock);
}

//*****************************************************************************

void H264ENC_BitstreamAlarmShift(uint32_t aAlarmShift)
{
  VDB_LOG_ERROR("%s:\n", __func__);
  //spin_lock(&gDataLock);
  
  // reprogram alarm address - should be done after data were fetched
  gpH264EncRegs->OUT_CBUF_ALARM_ADDR.R += aAlarmShift;
  
  //spin_unlock(&gDataLock);
}

//*****************************************************************************

void MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption)
{
  uint32_t i = 0;
  if( apCaption != NULL)
  {
    printk("%s", apCaption);
  } // if caption set
  
  for(i = 0; i < aSize; i++)
  {
    if((i % 4) == 0)
    {
      printk("\n%2u:\t", i / 4);
    }
    printk("%2x ", apMem[i]);    
  }
  
  printk("\n");
} // MemPrint

//*****************************************************************************

uint32_t Sig2UsrSend(pid_t aPid, int32_t aValue)
{
  struct siginfo info;
  uint32_t lRet = H264ENC_DRV_SUCCESS;
  struct pid *pid_struct;
  struct task_struct *t;
    
  // send the signal to user space
  memset(&info, 0, sizeof(struct siginfo));
  info.si_signo = H264ENC_FRAME_DONE_SIGNAL;
  info.si_code = SI_QUEUE;
  info.si_int = (aValue);
  rcu_read_lock();
  pid_struct = find_get_pid(aPid);
  t = pid_task(pid_struct,PIDTYPE_PID);
  if(t == NULL)
  {
    VDB_LOG_ERROR("No such pid %u. Signal not sent.\n", aPid);
    rcu_read_unlock();
    lRet = H264ENC_DRV_FAILURE;
  } // if no such pidRegisterred s
  else
  {
    rcu_read_unlock();
    //send the signal
    if (send_sig_info(H264ENC_FRAME_DONE_SIGNAL, &info, t) < 0) 
    {
      lRet = H264ENC_DRV_FAILURE;
      VDB_LOG_ERROR("Error sending signal to user space.\n");
    } // if sending signal failed
  } // else if no such pid
  return lRet;
} // Sig2UsrSend()

//*****************************************************************************

#define REG_CNT 38 

void H264EncRegPrint()
{
  uint32_t i = 0;
  uint32_t lRegOffsets[REG_CNT] = 
	{0x0, 0x10, 0x14, 0x18, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x80, 0x84, 0x88, 
	 0x90, 0x94, 0x104, 0x11c, 0x120, 0x140, 0x144, 0x148, 0x14c, 0x150, 
	 0x200, 0x204, 0x208, 0x20c, 0x210, 0x214, 0x218, 0x21c, 0x220, 0x224, 
	 0x228, 0x22c, 0x230, 0x234, 0x238, 0x284};
  
  printk("H264 Encoder registers\n");
    
  for(i = 0; i < REG_CNT; i++)
  {
    
    printk("\n0x%2x:\t", lRegOffsets[i]);
    
    printk("%2x ", *((uint32_t*)(((uint8_t*)gpH264EncRegs) + lRegOffsets[i])));    
  }
  
  printk("\n");
} // MemPrint

//*****************************************************************************