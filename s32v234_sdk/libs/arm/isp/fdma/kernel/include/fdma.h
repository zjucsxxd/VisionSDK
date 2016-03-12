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
* \file     fdma.h
* \brief    declarations for fDMA driver
* \author   Tomas Babinec
* \version  0.1
* \date     2.4.2014
* \note
****************************************************************************/

#ifndef FDMA_H
#define FDMA_H

#ifdef __cplusplus 
extern "C" { 
#endif

// will be built run on desktop
//#define FDMA_DESK 

#if !defined(__STANDALONE__)
#include <linux/ioctl.h>
# endif // !defined(__STANDALONE__)

#include "isp_hw.h"

/*****************************************************************************
* MACRO definitions
*****************************************************************************/

#define FDMA_IRQ_DONE    115
#define FDMA_IRQ_ERR     116

#define FDMA_EVENT_SIGNAL   44
#define FDMA_DONE_EVENT     0
#define FDMA_ERR_EVENT      1

#define FDMA_DRV_SUCCESS  0
#define FDMA_DRV_FAILURE -1

#define FDMA_DRV_ERR_QUEUE_FULL -2

#define FDMA_MEM_BUF_LEN 256

// name of the device file
#define FDMA_DEVICE_NAME "fdma"

// magic number for fDMA driver
#define FDMA_IOC_MAGIC 'f'

///< number of transaction descriptors in SRAM table (TDT)
#define FDMA_TD_CNT 16

///< possible Sequencer mode states
#define SEQ_BASED_MODE 1
#define SEQ_LESS_MODE 0

#if !defined(__STANDALONE__)
#include "fdma_ioctl.h"
# endif // !defined(__STANDALONE__)

#ifdef __cplusplus 
} //extern "C" 
#endif

#endif