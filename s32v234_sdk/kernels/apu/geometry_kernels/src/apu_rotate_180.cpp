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
* \file apu_rotate_180.cpp
* \addtogroup geometry
* \addtogroup rotation Rotate image by 180 deg
* \ingroup geometry
* @{
* \brief Image rotation
*/
#ifdef APEX2_EMULATE
//#include "apu_lib.hpp"
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA

#include "apu_rotate_180.h"

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
   180-degree rotation kernel metadata.
   
   \param ROTATE_KN				Define for Kernel name
   \param 2                     Number of ports
   \param "Port ROTATE_KN_IN"   Define for name of input image (unsigned 8bit)
   \param "Port ROTATE_KN_OUT"  Define for name of output image (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(ROTATE_K)//_kernel_info_rotate_180
(
	ROTATE_KN,
   2,
   __port(__index(0),
          __identifier(ROTATE_KN_IN),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(1),
   __identifier(ROTATE_KN_OUT),
          __attributes(ACF_ATTR_VEC_OUT),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#include "apu_rotate_180_impl.h"

void apu_rotate_180(kernel_io_desc lIn, kernel_io_desc lOut)
{
   vec08u*        lpvIn   = (vec08u*) lIn.pMem;
   vec08u*        lpvOut  = (vec08u*)  lOut.pMem;

   rotate_180(lpvOut, lpvIn, lIn.chunkWidth, lIn.chunkHeight, lIn.chunkSpan);
}
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
