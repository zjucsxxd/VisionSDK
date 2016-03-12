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
* \file apu_copy_input_kernel.c
* \addtogroup optical_flow Optical flow
* \addtogroup of_copy_input Copy input
* \ingroup optical_flow
* @{
* \brief Input to output copying
*/
#ifdef ACF_KERNEL_METADATA
#include "apu_copy_input_kernel.h"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy unsigned 8bit input to output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs unsigned 8bit copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN08u_KN			Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of first input image (unsigned 8bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (unsigned 8bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN08u_K)
(
	COPY_IN_IN08u_KN,
	2,
	__port(__index(0),
			  __identifier(COPY_IN_KN_IMG),
			  __attributes(ACF_ATTR_VEC_IN),
			  __spatial_dep(0, 0, 0, 0),
			  __e0_data_type(d08u),
			  __e0_size(1, 1),
			  __ek_size(1, 1)),

	 __port(__index(1),
			  __identifier(COPY_IN_KN_OUT_IMG),
			  __attributes(ACF_ATTR_VEC_OUT),
			  __spatial_dep(0, 0, 0, 0),
			  __e0_data_type(d08u),
			  __e0_size(1, 1),
			  __ek_size(1, 1))
);

#ifndef APEX2_EMULATE
static
#endif
/*!
\brief Copy unsigned 8bit input to unsigned 16bit output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs a unsigned 16bit type conversion of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN08u_OUT16u_KN		Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (unsigned 8bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (unsigned 16bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN08u_OUT16u_K)
(
COPY_IN_IN08u_OUT16u_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16u),
	__e0_size(1, 1),
	__ek_size(1, 1))
);



#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy signed 16bit input to output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs signed 16bit copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN16s_KN			Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (signed 16bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (signed 16bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN16s_K)
(
COPY_IN_IN16s_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16s),
	__e0_size(1, 1),
	__ek_size(1, 1))
);



#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy unsigned 16bit input to output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs unsigned 16bit  copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN16u_OUT16s_KN		Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (unsigned 16bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (unsigned 16bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN16u_OUT16s_K)
(
COPY_IN_IN16u_OUT16s_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16s),
	__e0_size(1, 1),
	__ek_size(1, 1))
);

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy signed 32bit input to output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs a signed 32bit  copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN32s_KN			Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (signed 32bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (signed 32bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN32s_K)
(
COPY_IN_IN32s_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1))
);



#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy unsigned 32bit input to output kernel metadata. 

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs a unsigned 32bit  copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN32u_KN			Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (unsigned 32bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (unsigned 32bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN32u_K)
(
COPY_IN_IN32u_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1))
);





#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Copy unsigned 32bit input to signed 32bit output kernel metadata.

This kernel can be used for indirect input graphs, to output the selected patch-image .
Outputs a signed 32bit copy of input image (i.e. the result image size is adapted to the offset vector of the indirect input graph).

\param  COPY_IN_IN32u_KN			Define for Kernel name
\param 2							Number of ports
\param "Port COPY_IN_KN_IMG"		Define for name of input image (unsigned 32bit)
\param "Port COPY_IN_KN_OUT_IMG"	Define for name of copy of the input image (unsigned 32bit).
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(COPY_IN_IN32u_OUT32s_K)
(
COPY_IN_IN32u_OUT32s_KN,
2,
__port(__index(0),
	__identifier(COPY_IN_KN_IMG),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(COPY_IN_KN_OUT_IMG),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#include "apu_copy_input_kernel_impl.h"


void apu_copy_input_in08u_out08u(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec08u* lpvInputImg = (vec08u*) inputImg.pMem;
	vec08u* lpvcpyOutImg = (vec08u*)cpyOutImg.pMem;

	copy_input_in08u_out08u(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan, cpyOutImg.chunkSpan);
}


void apu_copy_input_in08u_out16u(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec08u* lpvInputImg = (vec08u*)inputImg.pMem;
	vec16u* lpvcpyOutImg = (vec16u*)cpyOutImg.pMem;

	copy_input_in08u_out16u(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan, cpyOutImg.chunkSpan/sizeof(int16u));
}

void apu_copy_input_in16s_out16s(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec16s* lpvInputImg = (vec16s*)inputImg.pMem;
	vec16s* lpvcpyOutImg = (vec16s*)cpyOutImg.pMem;

	copy_input_in16s_out16s(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan / sizeof(int16s), cpyOutImg.chunkSpan / sizeof(int16s));
}



void apu_copy_input_in16u_out16s(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec16u* lpvInputImg = (vec16u*)inputImg.pMem;
	vec16s* lpvcpyOutImg = (vec16s*)cpyOutImg.pMem;
	int16s inImgStrideLen = inputImg.chunkSpan / sizeof(int16u);
	int16s outImgStrideLen = cpyOutImg.chunkSpan / sizeof(int16s);

	copy_input_in16u_out16s(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inImgStrideLen, outImgStrideLen);
}


void apu_copy_input_in32s_out32s(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec32s* lpvInputImg = (vec32s*)inputImg.pMem;
	vec32s* lpvcpyOutImg = (vec32s*)cpyOutImg.pMem;

	copy_input_in32s_out32s(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan / sizeof(int32s), cpyOutImg.chunkSpan / sizeof(int32s));
}


void apu_copy_input_in32u_out32u(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec32u* lpvInputImg = (vec32u*)inputImg.pMem;
	vec32u* lpvcpyOutImg = (vec32u*)cpyOutImg.pMem;

	copy_input_in32u_out32u(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan / sizeof(int32u), cpyOutImg.chunkSpan / sizeof(int32u));
}


void apu_copy_input_in32u_out32s(kernel_io_desc inputImg, kernel_io_desc cpyOutImg)
{
	vec32u* lpvInputImg = (vec32u*)inputImg.pMem;
	vec32s* lpvcpyOutImg = (vec32s*)cpyOutImg.pMem;

	copy_input_in32u_out32s(lpvInputImg, lpvcpyOutImg, inputImg.chunkWidth, inputImg.chunkHeight, inputImg.chunkSpan / sizeof(int32u), cpyOutImg.chunkSpan / sizeof(int32u));
}



#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
