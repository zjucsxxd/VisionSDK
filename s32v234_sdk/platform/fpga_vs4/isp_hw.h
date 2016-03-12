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
 * \brief 		definitions of common ISP HW values
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
#define DDR_BASE    0x80000000

#define SRAM_BASE 0x7e800000
#define SRAM_BASE_PRO 0x3e800000
#define SRAM_SIZE   (4*1024*1024)

// *** Code & Data RAM ***
#define CRAM_BASE   0x60000000
#define CRAM_SIZE   (64 * 1024)

// *** Parameter RAM ***
#define PRAM_BASE   0x60019000
#define PRAM_BASE_PRO   0x20000000
#define PRAM_SIZE   (4 * 1024)

// *** Debug Parameter RAM ***
#define DBG_PRAM_BASE   0x60018000
#define DBG_PRAM_SIZE   (4 * 1024)

// *** Kernel RAM ***
#define KRAM_BASE   0x6001A000
#define KRAM_SIZE   (4 * 1024)

#define CSI0_BASE 0x4002E000
#define CSI1_BASE 0x4002F000
#define CSI_SIZE  0x140

#define FDMA_BASE	0x60040000
#define FDMA_BASE_PRO	0x40020000
#define FDMA_SIZE	0x38

// final silicon add only for CSI
#define CSI_IF_CNT        2   ///< number of available CSI interfaces
#define CSI0_BASE 0x4002E000
#define CSI1_BASE 0x4002F000
#define CSI_SIZE  0x140

#ifdef __ARMV8
#define SRAM_BASE	0x3e800000
#else // #ifdef __ARMV8
#define SRAM_BASE	0x7e800000
#endif // else from #ifdef __ARMV8
#define SRAM_BASE_PRO	0x3e800000
#define SRAM_SIZE 	(4*1024*1024)

#ifdef __cplusplus 
extern "C" { 
#endif



#ifdef __cplusplus 
} 
#endif 

#endif // ISP_HW_H_


