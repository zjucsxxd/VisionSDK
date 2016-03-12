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
* \file     seq_types.h
* \brief    declaration of Sequencer driver internal types
* \author   Tomas Babinec
* \version  0.1
* \date     16.6.2014
* \note
****************************************************************************/

#ifndef SEQ_TYPES_H
#define SEQ_TYPES_H

#include "seq.h"
#include "s32vs234.h"
#include "seq_comm.h"
#include "seq_graph_meta.h"
#include "vdlist.h"

#define SEQ2HOST_MESSAGE_CNT  	3	///< number of messages from Sequencer to Host 
#define HOST2SEQ_MESSAGE_CNT  	1	///< number of messages from Host to Sequencer

#ifdef __cplusplus 
extern "C" { 
#endif

  
#define IPU_HIST_SIZE 256         ///< number of bins in histogram
#define IPU_HIST_CNT  4           ///< number of IPUs capable to do histogram  

//****************************************************************************
// types
//****************************************************************************

///< new name for Sequencer control blcok register structure
typedef volatile struct VSEQ_CTRL_BLK_tag SEQ_CtrlBlkRegs_t;

///< new name for Sequencer event control register structure
typedef volatile struct VSEQ_EVT_CTRL_tag SEQ_EvtCtrlRegs_t;

///< new name for IPUS block register structure
typedef volatile struct IPUS_tag SEQ_IpusRegs_t;

///< new name for IPUV block register structure
typedef volatile struct IPUV_tag SEQ_IpuvRegs_t;

/*** host communication ***/

/****************************************************************************/
/** Defines pool for Sequencer messages.
*
* The messages are distributed from a virtually contiguous memory block which 
* has to be specified during init call.
*****************************************************************************/
typedef struct SEQ_MessagePool
{
  struct SEQ_Message *mpRead;
  struct SEQ_Message *mpWrite;
  struct SEQ_Message *mpBase;
  struct SEQ_Message *mpLast;
} SEQ_MessagePool_t;

// *** for both KERNEL and USER space ***

/****************************************************************************/
/** Defines possible states of Sequencer frame buffer
*
*****************************************************************************/
typedef enum SEQ_FrmBufferState
{
  SEQ_FRM_BUFFER_STATE_WORK = 0,  ///< in the work queue
  SEQ_FRM_BUFFER_STATE_DONE,      ///< in the done queue 
  SEQ_FRM_BUFFER_STATE_USER,      ///< available for user
} SEQ_FrmBufferState_t; // enum SEQ_FrmBufferState

/****************************************************************************/
/** Defines frame buffer info structure.
*
*****************************************************************************/
typedef struct SEQ_FrmBufferInfo
{
  uint32_t                mBufferIdx; ///< index of the buffer
  enum SEQ_FrmBufferState mState;     ///< current state of the buffer
  uint32_t                mStreamIdx; ///< index of buffer stream
  uint32_t                mSize;      ///< size of the buffer
} SEQ_FrmBufferInfo_t;

/****************************************************************************/
/** Defines one frame buffer.
*
*****************************************************************************/
typedef struct SEQ_FrmBuffer
{
  uint32_t                mBufferIdx; ///< index of the buffer
  uintptr_t               mOffset;    ///< offset of the buffer/or user pointer
  uint32_t                mPhyAddr;   ///< physical address of the buffer
  enum SEQ_FrmBufferState mState;     ///< current state of the buffer
  uint32_t                mStreamIdx; ///< index of buffer stream
  
  struct VDList_Node      mVDListNode;///< list node
    
} SEQ_FrmBuffer_t;

/****************************************************************************/
/** Defines one frame buffer.
*
*****************************************************************************/
typedef struct SEQ_FrmStream
{
  uint32_t                mCnt;          ///< number of available buffers
  SEQ_FrmBuffer_t*        mpBufferTable; ///< table of buffers
  size_t                  mBufferSize;   ///< size of one buffer in bytes
  
  SEQ_FrmBuffer_t*        mpNextBuffer;  ///< pointer to buffer that is sheduled
  struct VDList           mWorkQueue;    ///< queue of frames to be captured
  struct VDList           mDoneQueue;    ///< queue of done frames
} SEQ_FrmStream_t;

//****************************************************************************

static inline void SEQ_FrmStreamInit(struct SEQ_FrmStream *apStream)
{
  apStream->mCnt          = 0;
  apStream->mpBufferTable = NULL;
  apStream->mBufferSize   = 0;
  VDList_Init(&(apStream->mWorkQueue));
  VDList_Init(&(apStream->mDoneQueue));
} // VDList_Init()

/****************************************************************************/
/** Structure to request sequencer frame buffers.
*
*****************************************************************************/
typedef struct SEQ_BufferRequest
{
  uint32_t    mStreamIdx;  ///< index of a frame stream
  uint32_t    mCnt;        ///< number of requested buffers
  uint32_t    mBaseShift;  ///< shift from base address to valid pixel data
  size_t      mBufferSize; ///< size of one buffer in bytes
  
  uint32_t*   mpBuffers;   ///< pointer to array of HW addresses in uint32_t fromat
} SEQ_BufferRequest_t;

/****************************************************************************/
/** Structure to keep packed graph data.
*
*****************************************************************************/
typedef struct SEQ_GraphPackage
{
  uint32_t      mGraphSize;       ///< overall size of the packed graph
  void*         mpGraphData;      ///< pointer to packed graph data
  uint32_t      mBufferListSize;  ///< size of the buffer list in bytes
  void*         mpBufferList;     ///< pointer to list of buffers
  uint32_t      mCSINumLines;     ///< # of lines expected from csi per frame
} SEQ_GraphPackage_t;

/****************************************************************************/
/** Structure to keep packed graph data.
*
*****************************************************************************/
typedef struct SEQ_StartCfg
{
  uint32_t      mFrames2Grab;    ///< # of frames to grab
  uint32_t      mInputLines;     ///< # of lines expected per input frame
} SEQ_StartCfg_t;

/****************************************************************************/
/** Defines one preprocessed Sequencer firmware line from S-record file.
*
* Used by SEQ_Fw_t to describe the whole firmware package.
*****************************************************************************/
typedef struct SeqFwLine
{
  uint32_t mAddr;
  uint32_t mSize;
  uint8_t *mpData;
} SEQ_FwLine_t; 

/****************************************************************************/
/** Collects all lines of a Sequencer firmware.
*
*****************************************************************************/
typedef struct SeqFw
{
  uint32_t      mLineCnt;
  SEQ_FwLine_t *mpLines;
} SEQ_Fw_t; 

/****************************************************************************/
/** To pass message auxiliary data from kernel- to user-space.
*
*****************************************************************************/
typedef struct SeqAuxData
{
  void *mpData;
  uint32_t mSize;
} SEQ_AuxData_t; // struct SeqAuxData

/****************************************************************************/
/** IPUx performacnce registers.
*
*****************************************************************************/
typedef struct SeqIpuPerformanceRegs
{
  uint32_t mStallStreamIn;
  uint32_t mStallStreamOut;
  uint32_t mStallStreamInOut;
  uint32_t mStallDataHazard;
  uint32_t mExecCounter;
} SEQ_IpuPerformanceRegs_t;

/****************************************************************************/
/** Define possible IPU engines.
*
*****************************************************************************/
typedef enum SEQ_IpuEngine
{
  SEQ_IPUS0 = 0,
  SEQ_IPUS1 = 1,
  SEQ_IPUS2 = 2,
  SEQ_IPUS3 = 3,
  SEQ_IPUS4 = 4,
  SEQ_IPUS5 = 5,
  SEQ_IPUS6 = 6,
  SEQ_IPUS7 = 7,
  SEQ_IPUV0 = 8,
  SEQ_IPUV1 = 9,
  SEQ_IPUV2 = 10,
  SEQ_IPUV3 = 11,
} SEQ_IpuEngine_t; 

/****************************************************************************/
/** Seqencer Event description.
*
*****************************************************************************/
typedef union SEQ_EventDesc
{
  uint32_t R;
  struct 
  {
    uint32_t mRegister:26;
    uint32_t mType:6;
  } B;
} SEQ_EventDesc_t;

/****************************************************************************/
/** Seqencer Event time record.
*
*****************************************************************************/
typedef struct SEQ_EventRecord
{
  SEQ_EventDesc_t mEvent; ///< event description
  unsigned long   mTime;  ///< time the event ocured
} SEQ_EventRecord_t; 

/****************************************************************************/
/** Series of Seqencer Event records.
*
*****************************************************************************/
typedef struct SEQ_EventLog
{
  SEQ_EventRecord_t *mpRecords;   ///< event record array pointer
  uint32_t           mNextRecIdx; ///< index of the next event record
} SEQ_EventLog_t; 

/****************************************************************************/
/** Ipu histogram.
*
*****************************************************************************/
typedef struct SEQ_IpuHist
{
  uint32_t        mPeak;     ///< peak value of the histogram
  uint32_t        mPeakAddr; ///< bin index of the peak value
  SEQ_IpuEngine_t mIpuIdx;   ///< IPU engines  
  uint32_t        mpData[IPU_HIST_SIZE];  ///< pointer to histogram data
} SEQ_IpuHist_t; 

#if defined(__KERNEL__) || defined(__STANDALONE__)
/****************************************************************************/
/** Ipu histogram.
*
*****************************************************************************/
  typedef struct SEQ_IpuHistHead
  {
    uint32_t        mPeak;     ///< peak value of the histogram
    uint32_t        mPeakAddr; ///< bin index of the peak value
    SEQ_IpuEngine_t mIpuIdx;   ///< IPU engines  
    uint32_t       *mpData;    ///< pointer to histogram data
  } SEQ_IpuHistHead_t; 
#endif //defined(__KERNEL__) || defined(__STANDALONE__)


#ifndef __STANDALONE__  
  typedef unsigned long jiffy_t;
#endif // ifndef SEQ_SA_KERNEL_API_H

#ifdef __cplusplus 
} 
#endif 

#endif // SEQ_TYPES_H

/*EOF*/