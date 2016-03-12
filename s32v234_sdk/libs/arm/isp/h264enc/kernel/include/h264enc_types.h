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
* \file     h264enc_types.h
* \brief    types declarations for H264 Encoder driver
* \author   Tomas Babinec
* \version  0.1
* \date     20.6.2014
* \note
****************************************************************************/
#ifndef H264_TYPES_H

#include "s32vs234.h"
#include "h264enc.h"
/*****************************************************************************
* struct definitions
*****************************************************************************/

typedef struct H264_ENC_tag H264ENC_Regs_t;

#ifdef __KERNEL__
//struct h264_enc_regs;

#endif // ifdef __KERNEL__

/****************************************************************************/
/** Describes one memomry buffer.
*
*****************************************************************************/
typedef struct vision_mem_buf
{
  uint32_t mPhysAddr;
  uint32_t mSize;
} VISION_MemBuf_t;

/****************************************************************************/
/** Defines encoding parameter values.
*
*****************************************************************************/

typedef struct h264_enc_buffers
{
  // input pixel data
  VISION_MemBuf_t mY;
  VISION_MemBuf_t mU;
  VISION_MemBuf_t mV;
  
  uint32_t mLineNum;
  
  uint8_t  mBankStride;		// 0-7 (>7 => disabled)
  
  // output bitstream data
  VISION_MemBuf_t mBitstream;  
} H264ENC_Buffers_t; 

/****************************************************************************/
/** Defines encoding parameter values.
*
*****************************************************************************/

typedef struct h264_enc_config
{
  uint8_t  mDataModeChroma; 	// Binary offset (0), Two's complement (1)
  uint8_t  mFetchTrig;  		// Host (1) or Sequencer (0) will trigger
  uint8_t  mColorFormat;		// YUV420 (0), Gray (1)
  uint8_t  mBitWidth; 		// 8 bpp (0), 10 bpp (1), 12 bpp (2)
  
  uint32_t mFrameWidth;		// ceiled to multiple of 16
  uint32_t mFrameHeight;	// ceiled to multiple of 16
  
  // probably should be elswhere
  uint32_t mInputAlarm;		// number of MBRW between VI_LINE_INT IRQ
  uint32_t mNumOutAlarm;	// number of MBRW without CB_ALARM_INT IRQ to signal VI_LCOUNT_ALARM_INT
    
  uint8_t  mFrameRate;		// in fps
  uint8_t  mQpInit;
  uint8_t  mQpMin;
  uint8_t  mQpMax;
  uint8_t  mQpFallback;
  
  uint32_t mBitsPerMbrw;
  
  uint8_t  mQpIncDiff0;
  uint8_t  mQpIncDiff1;
  uint8_t  mQpIncDiff2;
  uint8_t  mQpIncOffset;
  uint32_t mQpIncThld0; 
  uint32_t mQpIncThld1;
  uint32_t mQpIncThld2;
  
  uint8_t  mQpDecDiff0;
  uint8_t  mQpDecDiff1;
  uint8_t  mQpDecDiff2;
  uint8_t  mQpDecOffset;
  uint32_t mQpDecThld0; 
  uint32_t mQpDecThld1;
  uint32_t mQpDecThld2;
  
  uint8_t  mWaitFrames;
  
  uint8_t  mDisableDbf; 
  
  // TODO: add test line config
} H264ENC_Config_t; 

/****************************************************************************/
/** Defines encoding parameter values.
*
*****************************************************************************/

typedef struct h264_enc_status
{
  uint32_t mOutCurrentAddress;
  uint32_t mLastFrmEndAddress;
  uint32_t mOutLineCounter;
  uint32_t mInLineCounter;
  uint32_t mInterruptStatus;
   
} H264ENC_Status_t; 

/****************************************************************************/
/** Defines callback function pointers.
*
*****************************************************************************/

// Error types
typedef enum 
{
  H264ENC_ERR_ENC_OOS       = 1,
  H264ENC_ERR_CBUF_OVF      = 2,
  H264ENC_ERR_BR_TOO_HIGH   = 4,
  H264ENC_ERR_BS_FIFO_FULL  = 8,
  
  H264ENC_ERR_LAST
} H264ENC_ErrType_t;

// Bitstream alarm types
typedef enum 
{
  H264ENC_BSA_ADDR  = 1,  //< alarm address has been reached
  H264ENC_BSA_RATE  = 2,  //< for n input MBrows no out Alarm
  
  H264ENC_BSA_LAST
} H264ENC_BsAlarmType_t;

// Callback types
typedef enum 
{
  H264ENC_CLB_FRM_DONE  = 1,
  H264ENC_CLB_PIX_LOW   = 2,
  H264ENC_CLB_BIT_ALARM = 4,
  H264ENC_CLB_ERR       = 8,
  
  H264_ENC_CLB_LAST
} H264ENC_ClbType_t;

// Callback pointer types
typedef void (*H264ENC_FrameDoneCalbck_t)(void);
typedef void (*H264ENC_PixDataLowCalbck_t)(void);
typedef void (*H264ENC_BitstreamAlarmCalbck_t)(H264ENC_BsAlarmType_t aType);
typedef void (*H264ENC_ErrorCalbck_t)(H264ENC_ErrType_t aType);

typedef struct h264_enc_callbacks
{
  uint32_t mFunc2Set;
  
  H264ENC_FrameDoneCalbck_t      mFrameDone;
  H264ENC_PixDataLowCalbck_t     mPixDataLow;
  uint8_t                        mMbrwInterval;
  H264ENC_BitstreamAlarmCalbck_t mBitstreamAlarm;
  uint8_t                        mMaxMbrwOut;
  uint32_t                       mOutAlarmAddr;
  H264ENC_ErrorCalbck_t          mError;
} H264ENC_Callbacks_t; 




#endif //ifndef H264_TYPES_H