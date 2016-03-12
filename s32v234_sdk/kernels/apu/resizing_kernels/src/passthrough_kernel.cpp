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
/*!
* \file passthrough_kernel.cpp
* \addtogroup resizing
* \addtogroup copying Copy input image to output Image
* \ingroup resizing
* @{
* \brief Image downsampling
*/

#ifdef ACF_KERNEL_METADATA
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#include "apu_resize_definitions.h"
#include "passthrough_kernel.h"

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
Image copying kernel metadata.

\param PASS_THROUGH_KN			Define for Kernel name
\param 2						Number of ports
\param "Port PASS_THROUGH_IN"	Define for name of input image (unsigned 8bit)
\param "Port PASS_THROUGH_OUT"	Define for name of output image (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(PASS_THROUGH_K)//_kernel_info_passthrough_kernel
(
   PASS_THROUGH_KN,
   2,
   __port(__index(0),
   __identifier(PASS_THROUGH_IN),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0), //{left, right, top, bottom}
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(1),
   __identifier(PASS_THROUGH_OUT),
          __attributes(ACF_ATTR_VEC_OUT),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION


#ifdef APEX2_EMULATE
#include "apu_vec.hpp"
using namespace APEX2;
#endif
#include "passthrough_kernel_impl.h"

void passthrough_kernel (kernel_io_desc lIn0, kernel_io_desc lOut0)
{
   vec08u* lpvIn0  = (vec08u*)lIn0.pMem;
   vec08u* lpvOut0 = (vec08u*)lOut0.pMem;

   int lChunkWidth  = lIn0.chunkWidth;
   int lChunkHeight = lIn0.chunkHeight;
   int lStrideIn0   = lIn0.chunkSpan;   // 8bbp
   int lStrideOut0  = lOut0.chunkSpan;  // 8bpp
   pass_through(lpvOut0, lpvIn0, lStrideOut0, lStrideIn0, lChunkWidth, lChunkHeight);

   //KERNEL IMPLEMENTATION - copy
   /*for (int y=0; y<lChunkHeight; y++) {
      for (int x=0; x<lChunkWidth; x++) {
         lpvOut0[x] = lpvIn0[x];
      }
      
      lpvIn0 += lStrideIn0;
      lpvOut0 += lStrideOut0;
   }
   */
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
