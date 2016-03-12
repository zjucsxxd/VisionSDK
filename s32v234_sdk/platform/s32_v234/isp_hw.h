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
 * \file 		  isp_hw.h
 * \brief 		definitions of Sequencer memories for the silicon
 * \author 		Tomas Babinec
 * \version 	0.1
 * \date 		Oct 23, 2014
 ****************************************************************************/

#ifndef ISP_HW_H_
#define ISP_HW_H_

/*****************************************************************************
* constants
*****************************************************************************/

// *** DDR RAM ***
#define DDR_BASE          0x80000000

// *** SRAM RAM ***
#define SRAM_BASE         0x3e800000
#define SRAM_SIZE         (4*1024*1024)
#define SRAM_SINGLE_SIZE  (3 * 1024 * 1024)
#define SRAM_MULTI_SIZE   (1024 * 1024)

// *** Code & Data RAM ***
#ifdef CRAM_BASE
  #undef CRAM_BASE
#endif
#define CRAM_BASE         0x7C000000
#define CRAM_BASE_M0      0x0
#define CRAM_SIZE         (64 * 1024)

// *** Parameter RAM ***
#ifdef PRAM_BASE
  #undef PRAM_BASE
#endif
#define PRAM_BASE         0x7C019000
#define PRAM_SIZE         (4 * 1024)

// Sequencer view of PRAM
#define SEQ_PRAM_OFFSET   0x00019000   ///< A53 view
#define SEQ_PRAM_BASE     0x20000000   ///< M0 view

// *** Debug Parameter RAM ***
#define DBG_PRAM_BASE     0x7C018000
#define DBG_PRAM_SIZE     (4 * 1024)

// *** Kernel RAM ***
#ifdef KRAM_BASE
  #undef KRAM_BASE
#endif
#define KRAM_BASE         0x7C01A000
#define KRAM_SIZE         (4 * 1024)

//****************************************************************************
#define SEQ_SIZE             0x28
#define FDMA_SIZE            0x38

#define CSI_IF_CNT           2   ///< number of available CSI interfaces
#define CSI0_BASE            0x40030000
#define CSI1_BASE            0x400A0000
#define CSI_SIZE             0x140

#define I2C_OV10640_CAM_ADDR 0x30
#define I2C_SONY_CAM_ADDR    0x1A
#define I2C_MAXIM_DES_ADDR   0x6A
#define I2C_HDMI_ADDR        0x39  

#define IPUS_CNT             8 ///< number of available IPUs engines
#define IPUV_CNT             4 ///< number of available IPUv engines

/****************************************************************************/
/** Defines possible ISP LOG events.
*
*****************************************************************************/
typedef enum ISP_LogEvent
{
  ISP_LOGEVT_IPUS      = 0,
  ISP_LOGEVT_IPUV      = 1,
  ISP_LOGEVT_OTHER     = 2,
  ISP_LOGEVT_SEQ_FD    = 3,
  ISP_LOGEVT_CSI_FE    = 4,
  ISP_LOGEVT_SW_EVT    = 5,
  ISP_LOGEVT_CSI_LINE  = 6,
  ISP_LOGEVT_FDMA_LINE = 7,
  ISP_LOGEVT_MAX
} ISP_LogEvent_t;

typedef volatile uint32_t vuint32_t;
typedef volatile uint16_t vuint16_t;
typedef volatile uint8_t vuint8_t;

#ifdef __cplusplus 
extern "C" { 
#endif



#ifdef __cplusplus 
} 
#endif 

#endif /* ISP_HW_H_ */


