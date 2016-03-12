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
* \file     seq.h
* \brief    declarations for Sequencer driver
* \author   Tomas Babinec
* \version  0.1
* \date     30.5.2014
* \note
****************************************************************************/

#ifndef SEQ_H
#define SEQ_H

#ifndef __STANDALONE__
#include <linux/ioctl.h>
#endif // #ifndef __STANDALONE__

#include "config.h"
#include "seq_comm.h"
#include "isp_hw.h"

// *** DEBUG testing ***
// uncomment to enable debug testing
//#define SEQ_DEBUG
//#define SEQ_LOAD_BOOT

#define ALIGN32(_val) ((_val + 3) & 0xfffffffc)
#define ALIGN64(_val) ((_val + 7) & 0xfffffff8)

// *** PRAM map offsets ***
#define PRAM_OUT_MSG_OFF (SEQ_PRAM_MAP_OFF + ALIGN32(sizeof(SEQ_pram_map_t)))
#define PRAM_IN_MSG_OFF (PRAM_OUT_MSG_OFF + ALIGN32(sizeof(SEQ_Message_t))*SEQ2HOST_MESSAGE_CNT)
#define PRAM_AUX_DATA_OFF (PRAM_IN_MSG_OFF + ALIGN32(sizeof(SEQ_Message_t))*HOST2SEQ_MESSAGE_CNT) ///< aux data location (offset from PRAM_BASE);
#define PRAM_GRAPH_OFF (PRAM_AUX_DATA_OFF + ALIGN32(SEQ_PRAM_AUX_DATA_SIZE)) ///< graph location (offset from PRAM_BASE);

// *** Graph ***
#define SEQ_GRAPH_SIZE_MAX     0x4000 //< maximum allowed size of the graph
#define SEQ_GRAPH_CRAM_OFFSET  (CRAM_SIZE - SEQ_GRAPH_SIZE_MAX)
#define SEQ_GRAPH_ADDR         (CRAM_BASE + SEQ_GRAPH_CRAM_OFFSET)
//#define SEQ_GRAPH_ADDR         (PRAM_BASE + PRAM_GRAPH_OFFSET)

#define SEQ_EVENT_SIGNAL  45
// *** Sequencer IRQ numbers ***
#define SEQ_IRQ_FPGA      91
#define SEQ_IRQ_MSG       145
#define SEQ_IRQ_MSG_ACK   146

// *** IPU IRQ numbers ***
#define SEQ_IRQ_IPUS_DONE    149
#define SEQ_IRQ_IPUV_DONE    150
#define SEQ_IRQ_OTHER_DONE   151
#define SEQ_IRQ_SW_EVT_0     152
#define SEQ_IRQ_SW_EVT_1     153
#define SEQ_IRQ_SW_EVT_2     154
#define SEQ_IRQ_SW_EVT_3     155
#define SEQ_IRQ_SW_EVT_4     156
#define SEQ_IRQ_SW_EVT_5     157
#define SEQ_IRQ_SW_EVT_6     158
#define SEQ_IRQ_SW_EVT_7     159

// uncomment to turn on auto exposure control
#define SEQ_AE_ON

// Sequencer driver return values
#define SEQ_DRV_SUCCESS   0
#define SEQ_DRV_FAILURE   -1

// name of the device file
#define SEQ_DEVICE_NAME   "seq"

// magic number for Sequencer driver
#define SEQ_IOC_MAGIC     's'

// TODO: should be at some common location for SEQ and FDMA
// number of fDMA channels
#define FDMA_CHNL_CNT     16

// maximum size of the Sequencer graph
#define SEQ_GRAPH_SLOT_SIZE 	(PRAM_SIZE - PRAM_GRAPH_OFF)	///< max allowed size of the graph

// *** Sequencer status ***
#define SEQ_STATUS_OFF    0
#define SEQ_STATUS_ON     1
#define SEQ_STATUS_BOOT   2
#define SEQ_STATUS_RESET  3

#if 0
// *** Event logging ***
#define SEQ_IPUS_EVENT          1
#define SEQ_IPUV_EVENT          2
#define SEQ_OTHER_EVENT         3
#define SEQ_FRAMEDONE_EVENT     4
#define SEQ_CSI_FRAMEEND_EVENT  5
#define SEQ_SW_EVENT            6
#define SEQ_EVENT_LOG_LEN       500000
#endif

// Sequencer mode ("1" = ON, "0" = OFF)
#define SEQ_MODE 1

//**************************************************************************** 
// includes
//****************************************************************************

#include "seq_types.h"

#ifndef __STANDALONE__
#include "seq_ioctl.h"
#endif //#ifndef __STANDALONE__

//*****************************************************************************
// public data
//*****************************************************************************

extern float gFPS;

#endif // SEQ_H