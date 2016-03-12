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

#ifndef __FRAME_OUTPUT_DCU__H__
#define __FRAME_OUTPUT_DCU__H__

#include <frame_output_base.h>
#include <stddef.h>
#include "dcu.h"

#define DCU_FRAME_BUFFER_CNT 2

// comment in case of arbittrary geometry support
#define DCU_FIXED
#define DCU_FRM_WIDTH 1920
#define DCU_FRM_HEIGHT 1080

namespace io
{
  class FrameOutputDCU : public FrameOutputBase
  {
    public:
      FrameOutputDCU();
      FrameOutputDCU(uint32_t aWidth, uint32_t aHeight, IO_DATA_DEPTH aDepth, IO_DATA_CHANNELS aChannels, Dcu_BPP_t aFormat=DCU_BPP_24);
      
      ~FrameOutputDCU();
    
      void             Init(uint32_t aWidth, uint32_t aHeight, IO_DATA_DEPTH aDepth, IO_DATA_CHANNELS aChannels, Dcu_BPP_t aFormat=DCU_BPP_24);
      void             Reset();
      void             Disable();
      void             PutFrame(void *frame, bool aFlushCache=true);
      IO_STATUS        GetStatus(); 
      
    private:
      void             BaseInit();
      
      uint8_t *             mppFrameBuffers[DCU_FRAME_BUFFER_CNT]; ///< buffer pointers
      void*                 mppFbsVirtual[DCU_FRAME_BUFFER_CNT]; ///< virtual buffer pointers
      uintptr_t             mpFbsPhysical[DCU_FRAME_BUFFER_CNT]; ///< physical buffer adresses
      
      uint32_t              mWidth;
      uint32_t              mHeight;
      IO_DATA_DEPTH         mDepth;
      IO_DATA_CHANNELS      mChannels;
      size_t                mSize;
      
      IO_STATUS             mStatus;        ///< status of the frame_o interface
      Dcu_LCD_Para_t        mLcdPara;       ///< LCD parameters
      uint32_t              mDcuClk;        ///< DCU clock
      Dcu_LCD_Connection_t  mLcdConnection; ///< LCD connection type
      Dcu_LayerParams_t     mDcuLayerParams;///< DCU layer setup
      uint32_t              mNextBuff;      ///< next DCU buffer
  };
}


#endif //__FRAME_OUTPUT_DCU__H__