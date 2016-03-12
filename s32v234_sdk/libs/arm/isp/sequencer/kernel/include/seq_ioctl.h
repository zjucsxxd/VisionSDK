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
* \file     fdma_ioctl.h
* \brief    ioctl related declarations for Sequencer driver
* \author   Tomas Babinec
* \version  0.1
* \date     30.5.2014
* \note
****************************************************************************/

#ifndef SEQ_IOCTL_H
#define SEQ_IOCTL_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include <linux/fs.h>		// required for the struct file declaration

///////////////////////////////////////////
//
// IOCTL command codes numbers allocation
//

// *** DEBUG ONES ***

// IOCTL: transaction descriptor reservation
#define IOCTL_UNKNOWN _IO(SEQ_IOC_MAGIC, 0)

// IOCTL: simulate Sequencer message IRQ
#define IOCTL_SEQ_MSG_IRQ_SIM _IOW(SEQ_IOC_MAGIC, 1, uint32_t)

// IOCTL: schedule message processing tasklet
#define IOCTL_SEQ_MSG_IRQ_PROCESS _IO(SEQ_IOC_MAGIC, 2) 
  
// IOCTL: simulate message acknowlegment IRQ from Sequencer
#define IOCTL_SEQ_MSG_ACK_IRQ_SIM _IO(SEQ_IOC_MAGIC, 4)
  
// IOCTL: send status message
#define IOCTL_SEQ_MSG_STATUS_SEND _IO(SEQ_IOC_MAGIC, 5) 

// *** REAL ONES ***
  
// IOCTL: graph download
#define IOCTL_SEQ_GRAPH_DOWNLOAD _IOW(SEQ_IOC_MAGIC, 6, SEQ_GraphPackage_t*)
  
// IOCTL: DDR buffer lists setup
#define IOCTL_SEQ_DDRBUF_SET _IOW(SEQ_IOC_MAGIC, 7, void*)

// IOCTL: graph start
#define IOCTL_SEQ_START _IOW(SEQ_IOC_MAGIC, 8, SEQ_StartCfg_t*)
  
// IOCTL: graph start
#define IOCTL_SEQ_AUX_DATA_GET _IOR(SEQ_IOC_MAGIC, 9, void*)
  
// IOCTL: graph stop
#define IOCTL_SEQ_STOP _IO(SEQ_IOC_MAGIC, 10)
  
// IOCTL: graph stop wait
#define IOCTL_SEQ_STOP_WAIT _IO(SEQ_IOC_MAGIC, 11)
  
// IOCTL: SEQ HW & driver reset
#define IOCTL_SEQ_RESET _IO(SEQ_IOC_MAGIC, 12)
  
// IOCTL: SEQ boot
#define IOCTL_SEQ_BOOT _IO(SEQ_IOC_MAGIC, 13)

// IOCTL: Irq serve
#define IOCTL_SEQ_IRQ_SRV _IO(SEQ_IOC_MAGIC, 14)
  
// IOCTL: send message
#define IOCTL_SEQ_MSG_SEND _IOW(SEQ_IOC_MAGIC, 15, void*) 

// IOCTL: send message wait
#define IOCTL_SEQ_MSG_SEND_WAIT _IOW(SEQ_IOC_MAGIC, 16, void*) 
  
// IOCTL: request buffers
#define IOCTL_SEQ_BUF_REQ _IOW(SEQ_IOC_MAGIC, 17, void*) 
  
// IOCTL: queries buffer
#define IOCTL_SEQ_BUF_QRY _IOWR(SEQ_IOC_MAGIC, 18, void*) 

// IOCTL: removes buffers in all streams
#define IOCTL_SEQ_STR_RES _IOW(SEQ_IOC_MAGIC, 19, void*) 
  
// IOCTL: removes buffers in all streams
#define IOCTL_SEQ_BUF_PSH _IOW(SEQ_IOC_MAGIC, 20, void*) 
  
// IOCTL: removes buffers in all streams
#define IOCTL_SEQ_BUF_POP _IOWR(SEQ_IOC_MAGIC, 21, void*) 
  
// IOCTL: requests performance data for IPUs
#define IOCTL_SEQ_IPU_PROFILE_REQ _IOR(SEQ_IOC_MAGIC, 22, uint32_t)
  
// IOCTL: gets performance data for IPUs
#define IOCTL_SEQ_IPU_PROFILE_GET _IOR(SEQ_IOC_MAGIC, 23, void*)

// IOCTL: gets Event log data
#define IOCTL_SEQ_IPU_EVENT_LOG _IOR(SEQ_IOC_MAGIC, 24, void*)  
  
// IOCTL: enables Event logging
#define IOCTL_SEQ_IPU_EVENT_LOG_ENABLE _IO(SEQ_IOC_MAGIC, 25) 

// IOCTL: disables Event logging
#define IOCTL_SEQ_IPU_EVENT_LOG_DISABLE _IO(SEQ_IOC_MAGIC, 26) 
  
// IOCTL: gets graph structure from PRAM
#define IOCTL_SEQ_GRAPH_FETCH _IOR(SEQ_IOC_MAGIC, 27, void*) 
  
// IOCTL: enables histogram readout for IPU engine
#define IOCTL_SEQ_HIST_ENABLE _IOW(SEQ_IOC_MAGIC, 28, SEQ_IpuEngine_t) 
  
// IOCTL: gets latest histogram data for particular IPU engine
#define IOCTL_SEQ_HIST_GET _IOWR(SEQ_IOC_MAGIC, 28, SEQ_IpuHist_t*) 

///////////////////////////////////////////
//
// IOCTL cmds processing code
//

// only for kernel space
#if defined(__KERNEL__) || defined(ISP_SIM)

long SeqIoctl(struct file *apFile,	/* ditto */
		 unsigned int aIoctlNum,	/* number and param for ioctl */
		 unsigned long aIoctlParam);

#endif // if defined(__KERNEL__) || defined(ISP_SIM)

#ifdef __cplusplus 
} 
#endif 

#endif