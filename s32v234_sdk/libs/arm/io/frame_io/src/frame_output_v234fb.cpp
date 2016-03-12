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
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "linux/fb.h"
#include "video/fsl_dcu_ioctl.h"
#include <frame_output_v234fb.h>
#include "oal.h"
#include "vdb_log.h"
#include <sys/ioctl.h>  



namespace io
{

FrameOutputV234Fb::FrameOutputV234Fb(uint32_t aWidth, 
                                     uint32_t aHeight, 
                                     IO_DATA_DEPTH aDepth, 
                                     IO_DATA_CHANNELS aChannels, 
                                     uint32_t aFormat):
  mScreenIdx(0), mWidth(aWidth), mHeight(aHeight), mDepth(aDepth), 
  mChannels(aChannels), mFormat(aFormat), mStatus(IO_OK)
{  
  
  mFbFd = open("/dev/fb0", O_RDWR);
  mDcuFd = open("/dev/dcu", O_RDWR);
  
  if (mFbFd < 1)
    mStatus = IO_ERROR;
  else
    mStatus = IO_OK;
  
  struct fb_fix_screeninfo mFixedInfo;  ///< fixed frame buffer info from ioctl
  
  if (!ioctl(mFbFd,
               FBIOGET_VSCREENINFO,
               &mScreenInfo) && !ioctl(mFbFd,
                                       FBIOGET_FSCREENINFO,
                                       &mFixedInfo))
  {      
    // *** change resolution (to double buffered) ***
    // TODO
    //mScreenInfo.yres_virtual = 1080*2;
    
    // *** change number of channels ***
    if(mChannels == 3)
    {
      mScreenInfo.bits_per_pixel = 24;
      mScreenInfo.transp.offset = 0;
      mScreenInfo.transp.length = 0;
      mScreenInfo.transp.msb_right = 0;
    }
    else if(mChannels == 4)
    {
      mScreenInfo.bits_per_pixel = 32;
      mScreenInfo.transp.offset = 24;
      mScreenInfo.transp.length = 8;
      mScreenInfo.transp.msb_right = 0;
    }
    else
    {
      printf("Unknown config required. Keeping default settings:\n");
      printf("v_heigth == %u, v_width == %u\n",
                  mScreenInfo.yres_virtual, mScreenInfo.xres_virtual);
      printf("height == %u, width == %u\n",
                    mScreenInfo.yres, mScreenInfo.xres);
      printf("bpp == %u\n",
                    mScreenInfo.bits_per_pixel);
    }
    
    mScreenInfo.yres_virtual = mHeight * DCU_FRM_CNT;
    mScreenInfo.xres_virtual = mWidth;
    mScreenInfo.yres         = mHeight;
    mScreenInfo.xres         = mWidth;
    
    // set screeninfo
    ioctl(mFbFd,
          FBIOPUT_VSCREENINFO,
          &mScreenInfo);
  }
  
  mSize = mWidth * mHeight * mChannels;
  
  // map the whole frambuffer
  mpFrameBuffer = (uint8_t *)mmap(0, 
                                  mSize * DCU_FRM_CNT, // double buffered
                                  PROT_READ | PROT_WRITE | PROT_EXEC, 
                                  MAP_SHARED, 
                                  mFbFd, 
                                  0x0);
  // setup screen pointers
  for(uint32_t i = 0; i < DCU_FRM_CNT; i++)
  {
    mppScreens[i] = mpFrameBuffer + i * mSize;
  } // for all screens
} // FrameOutputV234Fb::FrameOutputV234Fb()

//***************************************************************************

FrameOutputV234Fb::~FrameOutputV234Fb()
{
  if(mpFrameBuffer)
  {
    munmap(mpFrameBuffer, mSize);
  }
  
  close(mDcuFd);
  close(mFbFd);
} // FrameOutputV234Fb::~FrameOutputV234Fb()

//***************************************************************************

void FrameOutputV234Fb::PutFrame(void *frame, bool aFlushCache)
{
  uint32_t lScreenIdx = (mScreenIdx + 1) % DCU_FRM_CNT;
  memcpy(mppScreens[lScreenIdx], frame, mSize);    
  
  if(aFlushCache)
  {
    CleanAndInvalidateDCache(mppScreens[lScreenIdx], mSize);
  } // if cache to be flushed
  
  mScreenInfo.yoffset = lScreenIdx * mHeight;  
  // set screeninfo
  ioctl(mFbFd,
        FBIOPAN_DISPLAY,
        &mScreenInfo);
  mScreenIdx = lScreenIdx;
} // FrameOutputV234Fb::PutFrame(

//***************************************************************************

void FrameOutputV234Fb::PutFrameAlpha(void *frame, bool aFlushCache)
{
  uint8_t *lpLineSrc = (uint8_t*)frame;
  uint8_t *lpLineDst = (uint8_t*)mpFrameBuffer;
  
  ioctl(mFbFd, FBIO_WAITFORVSYNC, 0);
  for(uint32_t y = 0; y < mHeight; y++)
  {
    uint8_t *lpSrc = lpLineSrc;
    uint8_t *lpDst = lpLineDst;
    
    for(uint32_t x = 0; x < mWidth; x++)
    {
      lpDst[0] = lpSrc[0];
      lpDst[1] = lpSrc[1];
      lpDst[2] = lpSrc[2];
      lpDst[3] = 255;
      lpDst += 4;
      lpSrc += 3;
    }
    lpLineSrc += mWidth * 4;
    lpLineDst += mWidth * 4;
  }
  
  if(aFlushCache)
  {
    CleanAndInvalidateDCache(lpLineDst, mSize);
  } // if cache to be flushed
} // FrameOutputV234Fb::PutFrameAlpha(

//***************************************************************************

IO_STATUS FrameOutputV234Fb::GetStatus()
{
  return mStatus;
} // FrameOutputV234Fb::GetStatus()

} // namespace io

//***************************************************************************