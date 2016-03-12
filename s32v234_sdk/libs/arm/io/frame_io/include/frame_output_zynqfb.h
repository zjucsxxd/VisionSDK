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

#ifndef __FRAME_OUTPUT_ZYNQFB__H__
#define __FRAME_OUTPUT_ZYNQFB__H__

#include <frame_output_base.h>
#include <string>
#include <opencv2/opencv.hpp>

namespace io
{  
  class FrameOutputZynqFB : public FrameOutputBase
  {
    public:
      FrameOutputZynqFB(uint32_t width, uint32_t height, IO_DATA_DEPTH depth, IO_DATA_CHANNELS channels);
      ~FrameOutputZynqFB();
    
      void             PutFrame(void *frame);
      IO_STATUS        GetStatus(); 
      
    private:
      IO_STATUS        m_status;
      
      uint32_t         m_width;
      uint32_t         m_height;
      IO_DATA_DEPTH    m_depth;
      IO_DATA_CHANNELS m_channels;
      
      uint8_t *        m_buffers;
      uint8_t *        m_buffer[2];
      uint8_t          m_back_id;
      int32_t          m_fd;
      int32_t          m_cvtcode;
      cv::Mat          m_rgb_disp;
      cv::Mat          m_in_frame;
  };
}


#endif //__FRAME_OUTPUT_MEMORY__H__