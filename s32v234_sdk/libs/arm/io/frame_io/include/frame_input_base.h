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

#ifndef __FRAME_INPUT_BASE__H__
#define __FRAME_INPUT_BASE__H__

#include <frame_io_types.h>

namespace io
{
  class FrameInputBase
  {
    public:
      FrameInputBase() {}
      virtual ~FrameInputBase() {}
    
      virtual void *           GetFrame()=0;
      virtual IO_STATUS        GetStatus()=0; 
      
      virtual uint32_t         GetWidth()=0;
      virtual uint32_t         GetHeight()=0;
      virtual IO_DATA_DEPTH    GetDepth()=0;
      virtual IO_DATA_CHANNELS GetChannels()=0;
  };
}

#endif //__FRAME_INPUT_BASE__H__