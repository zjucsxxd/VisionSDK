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

#ifndef __FRAME_OUTPUT_V234FB__H__
#define __FRAME_OUTPUT_V234FB__H__

#include <frame_output_base.h>
#include <stddef.h>
#include <fcntl.h>            
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "linux/fb.h"
#include "video/fsl_dcu_ioctl.h"

// comment in case of arbittrary geometry support
#define DCU_FIXED
#define DCU_FRM_WIDTH  1920
#define DCU_FRM_HEIGHT 1080
#define DCU_FRM_SIZE   (DCU_FRM_WIDTH*DCU_FRM_HEIGHT*3)
#define DCU_FRM_CNT    2

namespace io
{
  class FrameOutputV234Fb : public FrameOutputBase
  {
    public:
      FrameOutputV234Fb(uint32_t aWidth, 
                        uint32_t aHeight, 
                        IO_DATA_DEPTH aDepth, 
                        IO_DATA_CHANNELS aChannels, 
                        uint32_t aFormat=0);
      ~FrameOutputV234Fb();
    
      void             PutFrame(void *frame, bool aFlushCache=true);
      void             PutFrameAlpha(void *frame, bool aFlushCache=true);
      IO_STATUS        GetStatus(); 
      
    private:
      struct fb_var_screeninfo mScreenInfo; ///< screen info from ioctl
      uint8_t *             mpFrameBuffer;
      uint8_t *             mppScreens[DCU_FRM_CNT];
      uint32_t              mScreenIdx;
      
      uint32_t              mWidth;
      uint32_t              mHeight;
      IO_DATA_DEPTH         mDepth;
      IO_DATA_CHANNELS      mChannels;
      uint32_t              mFormat;
      size_t                mSize;
      
      IO_STATUS             mStatus;        ///< status of the frame_o interface
      
      int32_t               mFbFd;
      int32_t               mDcuFd;
  };
}


#endif //__FRAME_OUTPUT_V234FB__H__