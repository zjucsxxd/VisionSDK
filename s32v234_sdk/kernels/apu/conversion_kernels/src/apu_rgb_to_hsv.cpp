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
* \file apu_rgb_to_hsv.cpp
* \addtogroup conversion
* \addtogroup color_conversion Color conversion
* \ingroup conversion
* @{
* \brief Color conversion
*/

#ifdef APEX2_EMULATE
#include "apu_lib.hpp"
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA

#include "apu_rgb_to_hsv.h"

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
   RGB to HSV conversion kernel metadata. 
   
   \param RGB_HSV_KN			Define for Kernel name
   \param 2						Number of ports
   \param "Port RGB_HSV_KN_IN"  Define for name of input RGB image (unsigned 3x8bit)
   \param "Port RGB_HSV_KN_SAT" Define for name of output SATURATION image (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(RGB_HSV_K)
(
   RGB_HSV_KN,
   2,
   __port(__index(0),
		  __identifier(RGB_HSV_KN_IN),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(3, 1),
          __ek_size(1, 1)),
   __port(__index(1),
		  __identifier(RGB_HSV_KN_SAT),
          __attributes(ACF_ATTR_VEC_OUT),
          __spatial_dep(0,0,0,0),
		  __e0_data_type(d08u),
		  __e0_size(1, 1),
		  __ek_size(1, 1))
);


#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
RGB to HSV conversion kernel metadata.

\param RGB_HSV_KN			Define for Kernel name
\param 3						Number of ports
\param "Port RGB_HSV_KN_IN"  Define for name of input RGB image (unsigned 3x8bit)
\param "Port RGB_HSV_KN_SAT" Define for name of output SATURATION image (unsigned 8bit)
\param "Port RGB_HSV_KN_HUE" Define for name of output HUE image (unsigned 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(RGB_HSV_HS_K)
(
RGB_HSV_HS_KN,
3,
__port(__index(0),
	__identifier(RGB_HSV_KN_IN),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(3, 1),
	__ek_size(1, 1)),
__port(__index(1),
	__identifier(RGB_HSV_KN_SAT),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(2),
	__identifier(RGB_HSV_KN_HUE),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16u),
	__e0_size(1, 1),
	__ek_size(1, 1))
);

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
RGB to HSV conversion kernel metadata.

\param RGB_HSV_KN			Define for Kernel name
\param 4						Number of ports
\param "Port RGB_HSV_KN_IN"  Define for name of input RGB image (unsigned 3x8bit)
\param "Port RGB_HSV_KN_SAT" Define for name of output SATURATION image (unsigned 8bit)
\param "Port RGB_HSV_KN_VAL" Define for name of output VALUE image (unsigned 8bit)
\param "Port RGB_HSV_KN_RED" Define for name of output Red channel of the input image (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(RGB_HSV_SVR_K)
(
RGB_HSV_SVR_KN,
4,
__port(__index(0),
	__identifier(RGB_HSV_KN_IN),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(3, 1),
	__ek_size(1, 1)),
__port(__index(1),
	__identifier(RGB_HSV_KN_SAT),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(2),
	__identifier(RGB_HSV_KN_VAL),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(3),
	__identifier(RGB_HSV_KN_RED),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1))

);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

//#ifdef APEX2_EMULATE
//#include "acf_kernel.hpp" // if using the ACF emulation library
//using namespace APEX2;
//#endif

#include "apu_rgb_to_hsv.h"
#include "apu_rgb_to_hsv_impl.h"

void apu_rgb_to_hsv_sat(kernel_io_desc lIn0, kernel_io_desc lOutSat)
{
   vec08u* lpvIn0  = (vec08u*)lIn0.pMem;
   vec08u* lpvOutSat = (vec08u*)lOutSat.pMem;

   rgb_to_hsv_sat(lpvOutSat, lpvIn0, lIn0.chunkWidth, lIn0.chunkHeight, lOutSat.chunkSpan, lIn0.chunkSpan);
   
}

void apu_rgb_to_hsv_hue_sat(kernel_io_desc lIn0, kernel_io_desc lOutSat, kernel_io_desc lOutHue)
{
	vec08u* lpvIn0 = (vec08u*)lIn0.pMem;
	vec08u* lpvOutSat = (vec08u*)lOutSat.pMem;
	vec16u* lpvOutHue = (vec16u*)lOutHue.pMem;

	rgb_to_hsv_hue_sat(lpvOutHue, lpvOutSat, lpvIn0, lIn0.chunkWidth, lIn0.chunkHeight, lOutSat.chunkSpan, lIn0.chunkSpan);
}

void apu_rgb_to_hsv_svr(kernel_io_desc lIn0, kernel_io_desc lOutSat, kernel_io_desc lOutVal, kernel_io_desc lOutRed)
{
	vec08u* lpvIn0 = (vec08u*)lIn0.pMem;
	vec08u* lpvOutSat = (vec08u*)lOutSat.pMem;
	vec08u* lpvOutVal = (vec08u*)lOutVal.pMem;
	vec08u* lpvOutRed = (vec08u*)lOutRed.pMem;

	rgb_to_hsv_svr(lpvOutSat, lpvOutVal, lpvOutRed, lpvIn0, lIn0.chunkWidth, lIn0.chunkHeight, lOutSat.chunkSpan, lIn0.chunkSpan);

}
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */

