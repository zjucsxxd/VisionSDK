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
 * \file    isp_graph.h
 * \brief   ISP runtime firmware (M0+)
 * \author
 * \author
 * \version 0.1
 * \date    15-10-2013
 * \note    initial version
 ****************************************************************************/

#ifndef	SEQ_GRAPH_H_
#define	SEQ_GRAPH_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "seq_hw.h"

/*****************************************************************************
* consts
*****************************************************************************/

#define	MAX_CONSUMER		8

#define	SEQ_NUM_SDMA_OUT	4
#define	SEQ_NUM_SDMA_IN		9
#define	SEQ_NUM_DEV		20
#define	FDMA_CHANNELS		0x10
#define	MIPI_VIRT_CHN_NUM	4

#if (SEQ_NUM_SDMA_OUT<MIPI_VIRT_CHN_NUM) || (SEQ_NUM_SDMA_IN<MIPI_VIRT_CHN_NUM)
  #error "Can't handle full number of MIPI channels"
#endif

/*****************************************************************************
* macros
*****************************************************************************/

#define	BUF_ALIGNMENT	0x10
#define	BUF_ALIGN(_v)	(((_v) + (BUF_ALIGNMENT-1)) & ~(BUF_ALIGNMENT-1))
#define	NUM_PARA_EL(_a)	sizeof(_a)/sizeof(SEQ_CfgPara_t)

/*****************************************************************************
* types
*****************************************************************************/
#ifndef __ASSEMBLER__
typedef uint32_t	Mem_t;
typedef uint32_t	Addr_t;

typedef uint32_t	SEQ_Head_Ptr_t;
typedef uint32_t	SEQ_Buf_Ptr_t;
typedef uint32_t	SEQ_Mem_Ptr_t;
typedef uint32_t	SEQ_Char_CPtr_t;
typedef uint32_t	SEQ_CfgPara_CPtr_t;

#undef  __GNUC__

typedef enum {

  SEQ_NODE_SCALAR	=0,
  SEQ_NODE_VECTOR	=1,
  SEQ_NODE_OTHER	=2,
  SEQ_NODE_FWLOAD,
  SEQ_NODE_VERSION,

  SEQ_NODE_LAST,
  SEQ_NODE_SIZE = 0x7fffffff	// *** force enum to be 32bit ***

} SEQ_Node_t;

typedef enum {

  SEQ_OTHRIX_FDMA	=0,
  SEQ_OTHRIX_H264ENC	=1,
  SEQ_OTHRIX_H264DEC	=2,
  SEQ_OTHRIX_JPEGDEC	=3,
  SEQ_OTHRIX_MIPICSI0	=4,
  SEQ_OTHRIX_MIPICSI1	=5,

  SEQ_OTHRIX_LAST,
  SEQ_OTHRIX_SIZE = 0x7fffffff	// *** force enum to be 32bit ***

} SEQ_Othr_ix_t;

typedef uint32_t pixel_t;

// *** graph data structures ******************************
#pragma pack(push, 2)

typedef struct SEQ_Head_t
{
  // *** engine ***
  const SEQ_Node_t		mcNodeType;				// *** 00 type of node ***
  const Addr_t			mcDevAddr;				// *** 04 address of hardware device ***
  const uint16_t		mcEngIndex;				// *** 08 index of requested engine (-1 for auto) ***
  uint16_t			mActive;				// *** 0a engine is running ***
  uint16_t			mDone;					// *** 0c engine is done for this frame ***
  uint16_t			mUpdate;				// *** 0e engine got some update ***
									// *** 10 (total) ***
} SEQ_Head_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** sequencer consumer ***
typedef struct SEQ_Cons_t
{
  // *** consumer ***
  SEQ_Head_Ptr_t		mpCons;					// *** 00 pointer to consumers (node) configuration header ***
  const uint16_t		mcChann;				// *** 04 the devices channel used ***
  const uint16_t		mcSkipLines;				// *** 06 number of lines to skip at frame begin ***
  const uint16_t		mcLines;				// *** 08 number of lines required for processing ***
  const uint16_t		mcLineBytes;				// *** 0a number of bytes per line to read ***

  // *** read ***
  uint16_t			mCurrRdIndex;				// *** 0c current relative index into source buffer (read) ***
  const uint16_t		mcIncRdIndex;				// *** 0e increment of current relative index ***
  uint16_t			mLinesRead;				// *** 10 total lines read from buffer ***
  uint16_t			mReady;					// *** 12 buffer is ready to be read by this consumer ***
  uint16_t			mHighWater;				// *** 14 maximum difference between read and write ***
  uint16_t			mPad0;					// *** 16 pad aligment ***
									// *** 18 (total) ***
} SEQ_Cons_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** sequencer buffer ***
typedef struct SEQ_Buf_t
{
  // *** buffer ***
  SEQ_Mem_Ptr_t			mpBuf;					// *** 00 pointer to output buffer ***
  const uint16_t		mcLineMax;				// *** 04 number of lines fitting into output buffer (wrap) ***
  const uint16_t		mcLineBytes;				// *** 06 number of bytes per line ***
  const uint16_t		mcLineStride;				// *** 08 number of bytes to next line begin ***

  // *** write ***
  uint16_t			mStatus;				// *** 0a buffers status ***
  SEQ_Head_Ptr_t		mpProd;					// *** 0c pointer to producers (node) configuration header ***
  uint16_t			mCurrWrIndex;				// *** 10 current relative index into output buffer (write) ***
  const uint16_t		mcIncWrIndex;				// *** 12 increment of current relative index ***
  uint16_t			mLinesWritten;				// *** 14 total lines written to buffer ***
  uint16_t			mPad0;					// *** 16 pad aligment ***

  // *** read ***
  SEQ_Cons_t			mConsumer[MAX_CONSUMER];		// *** 18 consumer nodes ***
									// *** 78 (total) ***
} SEQ_Buf_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** configuration (register) parameter ***
typedef struct SEQ_CfgPara_t
{
  const uint32_t		mcIndex;				// *** 00 configuration parameter index ***
  const uint32_t		mcValue;				// *** 04 configuration parameter ***
									// *** 08 (total) ***
} SEQ_CfgPara_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** DMA transfer ***
typedef struct SEQ_Xfer_t
{
  // *** DMA ***
  const uint16_t		mcRegOffs;				// *** 00 offset to SDMA's register ***
  const uint16_t		mcStartLine;				// *** 02 number of first line to be used ***
  const uint16_t		mcStartOffsBytes;			// *** 04 number of bytes to first pixel in line ***
  const uint16_t		mcNumPixel;				// *** 06 number of pixels to transfer ***
									// *** 08 (total) ***
} SEQ_Xfer_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** IPU ***
typedef struct SEQ_IpuDst_t
{
  SEQ_Buf_Ptr_t			mpOutBuf;				// *** 00 output buffer ***
  const SEQ_Xfer_t		mcOutXfer;				// *** 04 output transfer struct ***
									// *** 0c (total) ***
} SEQ_IpuDst_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_IpuSrc_t
{
  SEQ_Buf_Ptr_t			mpInBuf;				// *** 00 input buffer ***
  const SEQ_Xfer_t		mcInXfer;				// *** 04 input transfer struct ***
  const uint16_t		mcConsIx;				// *** 0c our index in buffers consumer array ***
  uint16_t			mPad0;					// *** 0e pad aligment ***
									// *** 10 (total) ***
} SEQ_IpuSrc_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_IpuCfg_t
{
  SEQ_Head_t			mHead;					// *** 00 configuration header ***

  const Addr_t			mcCodeOff;				// *** 10 code entry address ***

  // *** current status ***
  uint16_t			mCurrProcStep;				// *** 14 current processing steps ***
  const uint16_t		mcNumProcSteps;				// *** 16 number of processing steps per frame ***

  // *** output buffers ***
  SEQ_IpuDst_t			mOutBuf[SEQ_NUM_SDMA_OUT];		// *** 18 output buffers ***

  // *** input data ***
  SEQ_IpuSrc_t			mInBuf[SEQ_NUM_SDMA_IN];		// *** 48 input buffers ***

  // *** configuration parameters ***
  SEQ_CfgPara_CPtr_t		mpcCfgPara;				// *** d8 pointer to configuration parameters ***
  const uint16_t		mcNumCfgPara;				// *** dc number of configuration parameters ***
  uint16_t			mPad0;					// *** de pad aligment ***
									// *** e0 (total) ***
} SEQ_IpuCfg_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

// *** MIPI ***
typedef struct SEQ_MipiCfg_t
{
  SEQ_Head_t			mHead;					// *** 00 configuration header ***

  // *** output buffers ***
  SEQ_Buf_Ptr_t			mpOutBuf[MIPI_VIRT_CHN_NUM];		// *** 10 output buffer pointer array ***
  const uint16_t		mcNumInputLines;				// *** 20 number of input image lines ***
  uint16_t			mPad0;					// *** 22 pad aligment ***
									// *** 24 (total) ***
} SEQ_MipiCfg_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_FdmaSrc_t
{
  SEQ_Buf_Ptr_t			mpInBuf;				// *** 00 input buffer ***
  const uint16_t		mcConsIx;				// *** 04 our index in buffers consumer array ***
  uint16_t			mPad0;					// *** 06 pad aligment ***
									// *** 08 (total) ***
} SEQ_FdmaSrc_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_FdmaDst_t
{
  SEQ_Buf_Ptr_t			mpOutBuf;				// *** 00 output buffer ***
									// *** 04 (total) ***
} SEQ_FdmaDst_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_FdmaCfg_t
{
  SEQ_Head_t			mHead;					// *** 00 configuration header ***

  // *** output buffers ***
  SEQ_FdmaDst_t			mOutBuf[FDMA_CHANNELS];			// *** 10 destination buffers ***

  // *** input data ***
  SEQ_FdmaSrc_t			mInBuf[FDMA_CHANNELS];			// *** 40 source buffers ***
									// *** c0 (total) ***
} SEQ_FdmaCfg_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

typedef struct SEQ_Load_t
{
  SEQ_Head_t			mHead;					// *** 00 configuration header ***
  
  uint16_t			mKMEM;					// *** 10 Kernel address in KMEM ***
  uint16_t			mLength;				// *** 12 Kernel length in bytes ***
  uint16_t			mInst;					// *** 14 Kernel address in IPU instruction mem ***
  uint16_t			mPad0;					// *** 16 pad aligment ***
  SEQ_Head_Ptr_t		mpStart;				// *** 18 pointer to IPU node to start ***
									// *** 1c (total) ***
} SEQ_Load_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

#pragma pack(pop)

#ifdef  __cplusplus
}
#endif

#define __GNUC__

#else	// __ASSEMBLER__
#define	SEQ_OTHRIX_FDMA		0
#define	SEQ_OTHRIX_H264ENC	1
#define	SEQ_OTHRIX_H264DEC	2
#define	SEQ_OTHRIX_JPEGDEC	3
#define	SEQ_OTHRIX_MIPICSI0	4
#define	SEQ_OTHRIX_MIPICSI1	5
#endif

#endif // SEQ_GRAPH_H_
/*EOF*/
