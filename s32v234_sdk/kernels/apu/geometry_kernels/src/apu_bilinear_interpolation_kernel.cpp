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
* \file apu_bilinear_interpolation_kernel.c
* \addtogroup geometry
* \addtogroup bilinear_interpolation Bilinear interpolation
* \ingroup geometry
* @{
* \brief Bilinear interpolation
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA

#include "apu_bilinear_interpolation_kernel.h"


#ifdef APEX2_EMULATE
///The chunk width for ACCUMULATION/BILINEAR INTERPOLATION
extern const int ACCUM_TILE_SIZE_X;// = 8; // defined in apu_gradient_matrix_kernel.c
///The chunk Height for accumulation/bilinear interpolation
extern const int ACCUM_TILE_SIZE_Y;// = 8;
#else
const int ACCUM_TILE_SIZE_X = 10; // otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 10;
#endif


#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif // ifndef APEX2_EMULATE
/****************************************************************************/
/*!
Bilinear interpolation kernel metadata with indirect inputs. Interpolates the pixels in one chunk of unsigned 8bit image according to the chunk related xoffs and yoffs
Outputs 16bit signed interpolation image of same size as the input image. Out(x,y) = [(quotx-xOffs)(quoty-yOffs)In(x,y) + xOffs(quoty-yOffs)In(x+1, y) + yOffs*(quotx-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)

\param  BILIN_INTERPOL_IN16u_OUT16s_KN	Define for Kernel name
\param 6							Number of ports
\param "Port BILIN_INTERPOL_IN"		Define for name of first input image (unsigned 8bit)
\param "ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)" This is the size of the image chunk (has to be defined by the user). It has to comply with the chunk size of the graph using this kernel.
\param "Port BILIN_INTERPOL_OUT"	Define for name of interpolation result of the input image (unsigned 16bit).
\param "Port BILIN_INTERPOL_XOFFS"	Define for name of x offset vector (has one element for each chunk of the image) (signed 16bit)
\param "Port BILIN_INTERPOL_QUOTX"	Define for name of (unsigned 16bit quotient for the x offset (i.e. fractional value is alpha = xOffs/quotX) (unsigned 16bit)
\param "Port BILIN_INTERPOL_YOFFS"	Define for name of (signed 16bit y offset vector (has one element for each chunk of the image)  (signed 16bit)
\param "Port BILIN_INTERPOL_QUOTY"	Define for name of quotient for the y offset (i.e. fractional value is alpha = yOffs/quotY)  (unsigned 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(BILIN_INTERPOL_IN08u_OUT16s_K)
(
   BILIN_INTERPOL_IN08u_OUT16s_KN,
   6,
	__port(__index(0),
			__identifier(BILIN_INTERPOL_IN),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0 , 1, 0, 1), 
			__e0_data_type(d08u),
			__e0_size(1, 1),
			__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(1),
			__identifier(BILIN_INTERPOL_OUT),
			__attributes(ACF_ATTR_VEC_OUT),
			__spatial_dep(0,0,0,0),
			__e0_data_type(d16s),
			__e0_size(1, 1),
			__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(2),
			__identifier(BILIN_INTERPOL_XOFFS),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16s),
			__e0_size(1, 1),
			__ek_size(1, 1)),
		  
	__port(__index(3),
			__identifier(BILIN_INTERPOL_QUOTX),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16u),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(4),
			__identifier(BILIN_INTERPOL_YOFFS),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(5),
			__identifier(BILIN_INTERPOL_QUOTY),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16u),
			__e0_size(1, 1),
			__ek_size(1, 1))

);

/*
KERNEL_INFO kernelInfoConcat(BILIN_INTERPOL_IN16u_OUT16s_K)//_kernel_info_apu_bilinear_interpolation_in16u_out16s
(
	BILIN_INTERPOL_IN16u_OUT16s_KN,
		6,
	__port(__index(0),
		__identifier(BILIN_INTERPOL_IN),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(1, 1, 1, 1),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(1),
		__identifier(BILIN_INTERPOL_OUT),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16s),
		__e0_size(1, 1),
		__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(2),
		__identifier(BILIN_INTERPOL_XOFFS),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(3),
		__identifier(BILIN_INTERPOL_QUOTX),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(4),
		__identifier(BILIN_INTERPOL_YOFFS),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(5),
		__identifier(BILIN_INTERPOL_QUOTY),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(1, 1))

	);

	*/


#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
Bilinear interpolation kernel metadata with indirect inputs. Interpolates the pixels in one chunk of unsigned 16bit image according to the chunk related xoffs and yoffs
Outputs 16bit signed interpolation image of same size as the input image. Out(x,y) = [(quotx-xOffs)(quoty-yOffs)In(x,y) + xOffs(quoty-yOffs)In(x+1, y) + yOffs*(quotx-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)

\param  BILIN_INTERPOL_IN16u_OUT16s_KN	Define for Kernel name
\param 6								Number of ports
\param "Port BILIN_INTERPOL_IN"		Define for name of first input image (unsigned 8bit)
\param "ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)" This is the size of the image chunk (has to be defined by the user). It has to comply with the chunk size of the graph using this kernel.
\param "Port BILIN_INTERPOL_OUT"	Define for name of interpolation result of the input image.  (unsigned 16bit)
\param "Port BILIN_INTERPOL_XOFFS"	Define for name of x offset vector (has one element for each chunk of the image)  (signed 16bit)
\param "Port BILIN_INTERPOL_QUOTX"	Define for name of quotient for the x offset (i.e. fractional value is alpha = xOffs/quotX)  (unsigned 16bit)
\param "Port BILIN_INTERPOL_YOFFS"	Define for name of y offset vector (has one element for each chunk of the image)  (signed 16bit)
\param "Port BILIN_INTERPOL_QUOTY"	Define for name of quotient for the y offset (i.e. fractional value is alpha = yOffs/quotY)  (unsigned 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(BILIN_INTERPOL_IN16u_OUT16s_K)
(
	BILIN_INTERPOL_IN16u_OUT16s_KN,
		6,
	__port(__index(0),
		__identifier(BILIN_INTERPOL_IN),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 1, 0, 1),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(1),
		__identifier(BILIN_INTERPOL_OUT),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16s),
		__e0_size(1, 1),
		__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

	__port(__index(2),
		__identifier(BILIN_INTERPOL_XOFFS),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(3),
		__identifier(BILIN_INTERPOL_QUOTX),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(4),
		__identifier(BILIN_INTERPOL_YOFFS),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(5),
		__identifier(BILIN_INTERPOL_QUOTY),
		__attributes(ACF_ATTR_VEC_IN),
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
Bilinear interpolation kernel metadata with indirect inputs. Interpolates the pixels in one chunk of unsigned 16bit image according to the chunk related xoffs and yoffs given in fixed point Q3.28 format
Outputs 16bit signed interpolation image of same size as the input image. Out(x,y) = [(1-xOffs)(1-yOffs)In(x,y) + xOffs(1-yOffs)In(x+1, y) + yOffs*(1-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)

\param  BILIN_INTERPOL_IN16u_OUT16s_KN	Define for Kernel name
\param 4								Number of ports
\param "Port BILIN_INTERPOL_IN"		Define for name of first input image (unsigned 8bit)
\param "ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)" This is the size of the image chunk (has to be defined by the user). It has to comply with the chunk size of the graph using this kernel.
\param "Port BILIN_INTERPOL_OUT"	Define for name of interpolation result of the input image.  (unsigned 16bit)
\param "Port BILIN_INTERPOL_XOFFS"	Define for name of x offset vector in fixed point Q3.28 format (has one element for each chunk of the image) (signed 32bit)
\param "Port BILIN_INTERPOL_YOFFS"	Define for name of y offset vector in fixed point Q3.28 format (has one element for each chunk of the image) (signed 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(BILIN_INTERPOL_IN16u_OUT16s_Q3_28_K)
(
BILIN_INTERPOL_IN16u_OUT16s_Q3_28_KN,
4,
__port(__index(0),
	__identifier(BILIN_INTERPOL_IN),
	__attributes(ACF_ATTR_VEC_IN),
	//__spatial_dep(0, 1, 0, 1), //this does not work with indirect inputs
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16u),
	__e0_size(1, 1),
	__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(1),
	__identifier(BILIN_INTERPOL_OUT),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d16s),
	__e0_size(1, 1),
	__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(2),
	__identifier(BILIN_INTERPOL_XOFFS),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(3),
	__identifier(BILIN_INTERPOL_YOFFS),
	__attributes(ACF_ATTR_VEC_IN),
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
Bilinear interpolation kernel metadata with direct inputs and simulated indirect chunks. Interpolates the pixels in one chunk of unsigned 16bit image according to the chunk related xoffs and yoffs
Outputs 16bit signed interpolation image of same size as the input image. Out(x,y) = [(1-xOffs)(1-yOffs)In(x,y) + xOffs(1-yOffs)In(x+1, y) + yOffs*(1-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)

\param  BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_KN Define for Kernel name
\param 12								Number of ports
\param "Port BILIN_INTERPOL_IN"			Define for name of first input image (unsigned 8bit)
\param "Port BILIN_INTERPOL_OUT"		Define for name of interpolation result of the input image. (unsigned 16bit)
\param "Port BILIN_INTERPOL_TMP_DIV"	Define for name of result containing the count of overlapping interpolation regions. (unsigned 8bit)
\param "Port BILIN_INTERPOL_XPTS"		Define for name of x vector of the points where to start interpolation (has one element for each chunk of the image) (signed 32bit)
\param "Port BILIN_INTERPOL_YPTS"		Define for name of y vector of the points where to start interpolation (has one element for each chunk of the image) (signed 32bit)
\param "Port BILIN_INTERPOL_XOFFS"		Define for name of x offset vector in fixed point Q3.28 format (has one element for each chunk of the image) (signed 32bit)
\param "Port BILIN_INTERPOL_YOFFS"		Define for name of y offset vector in fixed point Q3.28 format (has one element for each chunk of the image) (signed 32bit)
\param "Port BILIN_INTERPOL_NrPts"		Define for name of scalar value defining the number of elements contained in each of the above four vectors  (unsigned 32bit)
\param "Port BILIN_INTERPOL_ALPHA1"		Define for name of temporary memory needed for transfer of the accumulated values between consecutive slices (signed 32bit)
\param "Port BILIN_INTERPOL_ALPHA2"		Define for name of temporary memory needed for transfer of the accumulated values between consecutive slices (signed 32bit)
\param "Port BILIN_INTERPOL_BETA1"		Define for name of temporary memory needed for transfer of the accumulated values between consecutive slices (signed 32bit)
\param "Port BILIN_INTERPOL_BETA2"		Define for name of temporary memory needed for transfer of the accumulated values between consecutive slices (signed 32bit)

*****************************************************************************/
KERNEL_INFO kernelInfoConcat(BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K)
(
BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_KN,
12,
__port(__index(0),
__identifier(BILIN_INTERPOL_IN),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 1, 0, 1), //this does not work with indirect inputs!
__e0_data_type(d16u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(BILIN_INTERPOL_OUT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d16s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(BILIN_INTERPOL_TMP_DIV), // this allows a maximal chunk size of 16x16 pixels
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d08u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(BILIN_INTERPOL_XPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(4),
__identifier(BILIN_INTERPOL_YPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(5),
__identifier(BILIN_INTERPOL_XOFFS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(6),
__identifier(BILIN_INTERPOL_YOFFS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(7),
__identifier(BILIN_INTERPOL_NRPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(8),
__identifier(BILIN_INTERPOL_ALPHA1),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),


__port(__index(9),
__identifier(BILIN_INTERPOL_ALPHA2),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),


__port(__index(10),
__identifier(BILIN_INTERPOL_BETA1),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(11),
__identifier(BILIN_INTERPOL_BETA2),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1))
);
/*
,
__port(__index(12),
__identifier(BILIN_INTERPOL_TMPDONE),
__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d08u),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1))
*/

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION
#include "apu_bilinear_interpolation_kernel.h"
#include "apu_bilinear_interpolation_kernel_impl.h"
#include <string.h>
#ifdef APEX2_EMULATE
#include <assert.h>
#endif


void apu_bilinear_interpolation_in08u_out16s(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lquotx, kernel_io_desc lyOffs, kernel_io_desc lquoty)
{
   vec08u*  lpvImgIn	= (vec08u*) lImgIn.pMem;
   int32s inDataSz = sizeof(int08u);
   int16s inChunkWidth = lImgIn.chunkSpan / inDataSz;

   vec16s* lpvImgOut = (vec16s*) lImgOut.pMem;
   int32s outDataSz = sizeof(int16s);
   int16s outChunkWidth = lImgOut.chunkSpan / outDataSz;

   vec16s* xOffs = (vec16s*)lxOffs.pMem;
   vec16u* quotx = (vec16u*)lquotx.pMem;
  
   vec16s* yOffs = (vec16s*)lyOffs.pMem;
   vec16u* quoty = (vec16u*)lquoty.pMem;

   bilinear_interpolation_filter_in08u_out16s(lpvImgOut, lpvImgIn, xOffs, quotx, yOffs, quoty, lImgIn.chunkWidth, lImgIn.chunkHeight, inChunkWidth, outChunkWidth);
}



void apu_bilinear_interpolation_in16u_out16s(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lquotx, kernel_io_desc lyOffs, kernel_io_desc lquoty)
{
	vec16u*  lpvImgIn = (vec16u*)lImgIn.pMem;
	int32s inDataSz = sizeof(int16u);
	int16s inChunkWidth = lImgIn.chunkSpan / inDataSz;

	vec16s* lpvImgOut = (vec16s*)lImgOut.pMem;
	int32s outDataSz = sizeof(int16s);
	int16s outChunkWidth = lImgOut.chunkSpan / outDataSz;

	vec32s* xOffs = (vec32s*)lxOffs.pMem;
	vec32u* quotx = (vec32u*)lquotx.pMem;

	vec32s* yOffs = (vec32s*)lyOffs.pMem;
	vec32u* quoty = (vec32u*)lquoty.pMem;

	bilinear_interpolation_filter_in16u_out16s(lpvImgOut, lpvImgIn, xOffs, quotx, yOffs, quoty, lImgIn.chunkWidth, lImgIn.chunkHeight, inChunkWidth, outChunkWidth);
}


void apu_bilinear_interpolation_filter_in16u_out16s_Q3_28(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lyOffs)
{
	vec16u*  lpvImgIn = (vec16u*)lImgIn.pMem;
	int32s inDataSz = sizeof(int16u);
	int16s inChunkWidth = lImgIn.chunkSpan / inDataSz;

	vec16s* lpvImgOut = (vec16s*)lImgOut.pMem;
	int32s outDataSz = sizeof(int16s);
	int16s outChunkWidth = lImgOut.chunkSpan / outDataSz;

	vec32s* xOffs = (vec32s*)lxOffs.pMem;
	vec32s* yOffs = (vec32s*)lyOffs.pMem;
	 
	bilinear_interpolation_filter_in16u_out16s_Q3_28(lpvImgOut, lpvImgIn, xOffs,  yOffs, lImgIn.chunkWidth, lImgIn.chunkHeight, inChunkWidth, outChunkWidth);
}


#ifdef APEX2_EMULATE
//extern const int ACCUM_TILE_SIZE_X;// = 8; // defined in apu_gradient_matrix_kernel.c
//extern const int ACCUM_TILE_SIZE_Y;// = 8;
#else
const int ACCUM_TILE_SIZE_X = 10; // otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 10;
#endif



void apu_bilinear_interp_withOffsPar_filter_in16u_out16s_Q3_28(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc ltmpDiv, kernel_io_desc lxPts, kernel_io_desc lyPts, kernel_io_desc lxOffs, kernel_io_desc lyOffs
								, kernel_io_desc lnrPts
								, kernel_io_desc laccum_a1b1L, kernel_io_desc laccum_a1b2L,kernel_io_desc laccum_a2b1L, kernel_io_desc laccum_a2b2L
								/*, kernel_io_desc lTmpDone*/)
{
	vec16u*  lpvImgIn = (vec16u*)lImgIn.pMem;
	int32s inDataSz = sizeof(int16u);
	int16s inChunkWidth = lImgIn.chunkSpan / inDataSz;

	vec16s* lpvImgOut = (vec16s*)lImgOut.pMem;
	int32s outDataSz = sizeof(int16s);
	int16s outChunkWidth = lImgOut.chunkSpan / outDataSz;

	vec08u* lpvTmpDiv = (vec08u*)ltmpDiv.pMem;

	int32s* xPts = (int32s*)lxPts.pMem;
	int32s* yPts = (int32s*)lyPts.pMem;

	int32s* xOffs = (int32s*)lxOffs.pMem;
	int32s* yOffs = (int32s*)lyOffs.pMem;

	int32u nrPts = *(int32u*)lnrPts.pMem;
	//int08u* tmpDone = (int08u*)lTmpDone.pMem;


	static int16u startRow, idxFirstCell;

	int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
	int16u lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	int16u imgWidth = lTileWidthInChunks * lImgIn.chunkWidth;
	static vec16s vIndicesWillBeDone;
	if (lFirstTileFl) {
		startRow = 0;
		idxFirstCell = 0;
		vIndicesWillBeDone = -1;
	}
	memset(lpvImgOut, '\0', lImgOut.chunkHeight*lImgOut.chunkSpan * APU_VSIZE);
	memset(lpvTmpDiv, '\0', ltmpDiv.chunkHeight*ltmpDiv.chunkSpan * APU_VSIZE);

	vec32u *accum_a1b1L = (vec32u *) laccum_a1b1L.pMem;
	vec32u *accum_a1b2L = (vec32u *) laccum_a1b2L.pMem;
	vec32u *accum_a2b1L = (vec32u *) laccum_a2b1L.pMem;
	vec32u *accum_a2b2L = (vec32u *) laccum_a2b2L.pMem;

	int chunkSZ = laccum_a1b1L.chunkHeight*laccum_a1b1L.chunkSpan * APU_VSIZE;
	memset(accum_a1b1L, '\0', chunkSZ);
	memset(accum_a1b2L, '\0', chunkSZ);
	memset(accum_a2b1L, '\0', chunkSZ);
	memset(accum_a2b2L, '\0', chunkSZ);

	//memset(tmpDone, '\0', lTmpDone.chunkSpan*lTmpDone.chunkHeight);

	bilinear_interpolation_withOffsPar_filter_in16u_out16s_Q3_28(lpvImgOut, lpvImgIn, lpvTmpDiv, xPts, yPts, xOffs, yOffs, nrPts, startRow, idxFirstCell, vIndicesWillBeDone,
		accum_a1b1L, accum_a1b2L, accum_a2b1L, accum_a2b2L, //tmpDone,
		imgWidth, lImgIn.chunkWidth, lImgIn.chunkHeight, ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y, inChunkWidth, outChunkWidth);

	startRow += lImgIn.chunkHeight;
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
