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
* \file apu_gradient_matrix_kernel.c
* \addtogroup optical_flow
* \addtogroup of_gradient_matrix Gradient matrix
* \ingroup optical_flow
* @{
* \brief Gradient matrix
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA
#include "apu_gradient_matrix_kernel.h"


#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Gradient matrix kernel metadata. 

Calculate the square gradients and gradX*gradY, i.e the elements of the spatial gradient matrix for the Lucas-Kanade algorithm
\param  GRADIENT_MATRIX_KN					Define for Kernel name
\param 5									Number of ports
\param "Port GRADIENT_MATRIX_KN_GRAD_X"		Define for name of Gradient X input image (signed 16bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_Y"		Define for name of Gradient Y input image (signed 16bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_X_SQR"	Define for name of Square of GradX matrix (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_Y_SQR"	Define for name of Square of GradY matrix (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_XY"	Define for name of GradX*GradY, i.e. dot product btw GradX and GradY matrices (signed 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(GRADIENT_MATRIX_K)
(
   GRADIENT_MATRIX_KN,
   5,
  
	__port(__index(0),
		  __identifier(GRADIENT_MATRIX_KN_GRAD_X),
		  __attributes(ACF_ATTR_VEC_IN),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d16s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

    __port(__index(1),
		  __identifier(GRADIENT_MATRIX_KN_GRAD_Y),
		  __attributes(ACF_ATTR_VEC_IN),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d16s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

    __port(__index(2),
		  __identifier(GRADIENT_MATRIX_KN_GRAD_X_SQR),
		  __attributes(ACF_ATTR_VEC_OUT),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32u),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

	__port(__index(3),
		  __identifier(GRADIENT_MATRIX_KN_GRAD_Y_SQR),
		  __attributes(ACF_ATTR_VEC_OUT),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32u),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

	 __port(__index(4),
		  __identifier(GRADIENT_MATRIX_KN_GRAD_XY),
		  __attributes(ACF_ATTR_VEC_OUT),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32s),
		  __e0_size(1, 1),
		  __ek_size(1, 1))
);


#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;// = 8;
extern const int ACCUM_TILE_SIZE_Y;// = 8;
#else
const int ACCUM_TILE_SIZE_X = 10; // have to be defined here, otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 10;
#endif

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*! \brief Accumulate the elements of the gradient matrix kernel metadata. 

Calculate the sum of the chunk elements of each of the Lucas-Kanade Gradient Matrix elements over a defined neighborhood specified by (ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_X)
Outputs the three vectors of accumulated GradX^2, GradY^2, GradX*GradY and the vector of dot inverse of the determinant of previous three(i.e. detG = accGradXSqr*accGradYSqr - accGradXY^2, invDetG = 1/detG)

\param  ACCUM_GRADIENT_MATRIX_KN				Define for Kernel name
\param 5										Number of ports
\param "Port GRADIENT_MATRIX_KN_GRAD_X_SQR"		Define for name of Square of GradX matrix input image (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_GRAD_Y_SQR"		Define for name of Square of GradY matrix input image (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_XY"		Define for name of GradX*GradY matrix input image (signed 32bit), 
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR"	Define for name of accumulated Square of GradX output vector (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR"	Define for name of accumlated Square of GradY output vector (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_XY"	Define for name of accumulated GradX*GradY output vector (signed 32bit),
\param "GRADIENT_MATRIX_KN_VALIDPTS"			Define for name of flags for the vector elements which have a valid determinant (according to Lucas-Kanade validation conditions) (unsigned 16bit)
\param "Port GRADIENT_MATRIX_KN_ACC_DET_G_INV"  Define for name of inverse determinant output vector (signed 32bit),
*****************************************************************************/

KERNEL_INFO kernelInfoConcat(ACCUM_GRADIENT_MATRIX_K)
(
	ACCUM_GRADIENT_MATRIX_KN,
	8,
	__port(__index(0),
	__identifier(GRADIENT_MATRIX_KN_GRAD_X_SQR),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_X)),

	__port(__index(1),
	__identifier(GRADIENT_MATRIX_KN_GRAD_Y_SQR),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_X)),

	__port(__index(2),
		__identifier(GRADIENT_MATRIX_KN_GRAD_XY),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_X)),

	__port(__index(3),
		__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR),
		__attributes(ACF_ATTR_VEC_OUT), 
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(4),
		__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR),
		__attributes(ACF_ATTR_VEC_OUT), 
		__spatial_dep(0, 0, 0, 0), 
		__e0_data_type(d32u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(5),
		__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_XY),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(6),
		__identifier(GRADIENT_MATRIX_KN_VALIDPTS),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(7),
		__identifier(GRADIENT_MATRIX_KN_ACC_DET_G_INV),
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
/*! \brief Compute the inverse determinant from the 64bit gradient matrix kernel metadata.

The input 64bit gradient matrix components are also automatically scaled down to 32bits and written out
Outputs the vector of dot inverse of the determinant of previous three(i.e. detG = accGradXSqr*accGradYSqr - accGradXY^2, invDetG = 1/detG)

\param  INVERSE_DETERMINANT_KN					Define for Kernel name
\param 11										Number of ports
\param "Port GRADIENT_MATRIX_KN_GRAD_X_SQR_H"	Define for name of word of square of GradX matrix input image (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_GRAD_X_SQR_L"	Define for name of low word of square of GradX matrix input image (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_GRAD_Y_SQR_H"	Define for name of high word of square of GradY matrix input image (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_Y_SQR_L"	Define for name of low word of square of GradY matrix input image (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_XY_H"		Define for name of high word of GradX*GradY matrix input image (signed 32bit),
\param "Port GRADIENT_MATRIX_KN_GRAD_XY_L"		Define for name of low word of GradX*GradY matrix input image (signed 32bit),
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR"	Define for name of accumulated Square of GradX output vector (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR"	Define for name of accumlated Square of GradY output vector(unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_ACC_GRAD_XY"	Define for name of accumulated GradX*GradY output vector (signed 32bit),
\param "Port GRADIENT_MATRIX_KN_ACC_DET_G_INV"	Define for name of inverse determinant output vector (signed 32bit),
\param "GRADIENT_MATRIX_KN_VALIDPTS"			Define for name of flags for the vector elements which have a valid determinant (according to Lucas-Kanade validation conditions) (unsigned 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(INVERSE_DETERMINANT_K)
(
INVERSE_DETERMINANT_KN,
11,
__port(__index(0),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR_H ),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR_L),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(2),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR_H),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(3),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR_L),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),


__port(__index(4),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_XY_H),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(5),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_XY_L),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(6),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(7),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(8),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_XY),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(9),
__identifier(GRADIENT_MATRIX_KN_ACC_DET_G_INV),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(10),
__identifier(GRADIENT_MATRIX_KN_VALIDPTS),
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
/*! \brief Compute the inverse determinant from the 32bit gradient matrix kernel metadata.

Outputs the vector of dot inverse of the determinant of previous three(i.e. detG = accGradXSqr*accGradYSqr - accGradXY^2, invDetG = 1/detG)

\param  INVERSE_DETERMINANT_SIMPLE_KN				Define for Kernel name
\param 5							Number of ports
\param "Port GRADIENT_MATRIX_KN_GRAD_X_SQR"		Define for name of square of GradX matrix input image (unsigned 32bit).
\param "Port GRADIENT_MATRIX_KN_GRAD_Y_SQR"		Define for name of square of GradY matrix input image (unsigned 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_XY"		Define for name of GradX*GradY matrix input image (signed 32bit), 
\param "Port GRADIENT_MATRIX_KN_ACC_DET_G_INV"	Define for name of inverse determinant output vector (signed 32bit),
\param "GRADIENT_MATRIX_KN_VALIDPTS"			Define for name of flags for the vector elements which have a valid determinant (according to Lucas-Kanade validation conditions) (unsigned 16bit)
*****************************************************************************/

KERNEL_INFO kernelInfoConcat(INVERSE_DETERMINANT_SIMPLE_K)
(
INVERSE_DETERMINANT_SIMPLE_KN,
5,
__port(__index(0),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),


__port(__index(2),
__identifier(GRADIENT_MATRIX_KN_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(GRADIENT_MATRIX_KN_ACC_DET_G_INV),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(GRADIENT_MATRIX_KN_VALIDPTS),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d16u),
__e0_size(1, 1),
__ek_size(1, 1))
);
#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION



#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
#else
//extern 
const int ACCUM_TILE_SIZE_X = 10; // have to be defined here, otherwise g++ linker complains
//extern 
const int ACCUM_TILE_SIZE_Y = 10;
#endif

#include "apu_gradient_matrix_kernel_impl.h"

void apu_gradient_matrix(kernel_io_desc gradientX, kernel_io_desc gradientY, kernel_io_desc gradientXSqr, kernel_io_desc gradientYSqr, kernel_io_desc gradXgradY)
{
   vec16s* lpvGradX		=	(vec16s*)	gradientX.pMem;
   vec16s* lpvGradY		=	(vec16s*)	gradientY.pMem;
   vec32u* lpvGradXSqr	=	(vec32u*)	gradientXSqr.pMem;
   vec32u* lpvGradYSqr	=	(vec32u*)	gradientYSqr.pMem;
   vec32s* lpvGradXGradY=	(vec32s*)	gradXgradY.pMem;
   int16s inDataSz = sizeof(int16s); //sizeof(vec16s)
   int16s outDataSz = sizeof(int32s); //sizeof(vec32s)
   int16s inStrideLen = gradientX.chunkSpan / inDataSz ;
   int16s outStrideLen = gradientXSqr.chunkSpan / outDataSz;
   gradient_matrix_filter(lpvGradX, lpvGradY,
	   lpvGradXSqr, lpvGradYSqr, lpvGradXGradY,gradientX.chunkWidth, gradientX.chunkHeight, inStrideLen, outStrideLen);
}

void apu_inverse_determinant(kernel_io_desc laccGradXSqrH, kernel_io_desc laccGradXSqrL,
	kernel_io_desc laccGradYSqrH, kernel_io_desc laccGradYSqrL, kernel_io_desc laccGradXYH, kernel_io_desc laccGradXYL,
	kernel_io_desc loutAccGradXSqr, kernel_io_desc loutAccGradYSqr, kernel_io_desc loutAccGradXY,
	kernel_io_desc laccDetG_inv, kernel_io_desc lvalidPts)
{
	vec32s* accGradXSqrH	= (vec32s*) laccGradXSqrH.pMem;
	vec32u* accGradXSqrL	= (vec32u*) laccGradXSqrL.pMem;
	vec32s* accGradYSqrH	= (vec32s*) laccGradYSqrH.pMem;
	vec32u* accGradYSqrL	= (vec32u*) laccGradYSqrL.pMem;
	vec32s* accGradXYH		= (vec32s*) laccGradXYH.pMem;
	vec32u* accGradXYL		= (vec32u*) laccGradXYL.pMem;
	vec32s* outAccGradXSqr	= (vec32s*) loutAccGradXSqr.pMem;
	vec32s* outAccGradYSqr	= (vec32s*) loutAccGradYSqr.pMem;
	vec32s* outAccGradXY	= (vec32s*) loutAccGradXY.pMem;
	vec32u* accDetG_inv		= (vec32u*) laccDetG_inv.pMem;
	vec16u* validPts		= (vec16u*) lvalidPts.pMem;
	int16s inStrideLen		= (int16s) laccGradXSqrH.chunkSpan / sizeof(int32u);
	int16s outStrideLen		= (int16s) loutAccGradXSqr.chunkSpan / sizeof(int32u);
		
	inverse_determinant_filter(accGradXSqrH, accGradXSqrL, accGradYSqrH, accGradYSqrL, accGradXYH, accGradXYL,
		outAccGradXSqr, outAccGradYSqr, outAccGradXY, accDetG_inv, validPts,
		(int16s)laccGradXSqrH.chunkWidth, (int16s) laccGradXSqrH.chunkHeight, inStrideLen, outStrideLen);
}

void apu_inverse_det_simple(kernel_io_desc laccGradXSqr, kernel_io_desc laccGradYSqr,
	kernel_io_desc laccGradXY, kernel_io_desc laccDetG_inv, kernel_io_desc lvalidPts)
{
	vec32u* accGradXSqr	= (vec32u*) laccGradXSqr.pMem;
	vec32u* accGradYSqr	= (vec32u*) laccGradYSqr.pMem;
	vec32s* accGradXY		= (vec32s*) laccGradXY.pMem;
	vec32u* accDetG_inv		= (vec32u*) laccDetG_inv.pMem;
	vec16u* validPts		= (vec16u*) lvalidPts.pMem;
	int16s inStrideLen		= (int16s) laccGradXSqr.chunkSpan / sizeof(int32u);
	int16s outStrideLen		= (int16s) laccDetG_inv.chunkSpan / sizeof(int32u);
		
	inverse_det_simple_filter(accGradXSqr, accGradYSqr, accGradXY,
		 accDetG_inv, validPts, ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y,
		(int16s)laccGradXSqr.chunkWidth, (int16s) laccGradXSqr.chunkHeight, inStrideLen, outStrideLen);
}

void apu_accum_gradient_matrix(kernel_io_desc gradientXSqr, kernel_io_desc gradientYSqr, kernel_io_desc gradXgradY, kernel_io_desc accGradXSqr, kernel_io_desc accGradYSqr, kernel_io_desc accGradXY, kernel_io_desc validPts, /*kernel_io_desc accDetG_high, */kernel_io_desc accDetG_inv)
{
	vec32u* lpvGradXSqr = (vec32u*)gradientXSqr.pMem;
	vec32u* lpvGradYSqr = (vec32u*)gradientYSqr.pMem;
	vec32s* lpvGradXGradY = (vec32s*)gradXgradY.pMem;
	vec32u* lpvAccGradXSqr = (vec32u*)accGradXSqr.pMem;
	vec32u* lpvAccGradYSqr = (vec32u*)accGradYSqr.pMem;
	vec32s* lpvAccGradXY = (vec32s*)accGradXY.pMem;
	vec32u* lpvAccDetG_inv = (vec32u*)accDetG_inv.pMem;
	vec16u* lpvValidPts = (vec16u*)validPts.pMem;

	int16s inDataSz = sizeof(int32u); //sizeof(vec16s)
	int16s outDataSz = sizeof(int32s);
	int16s inStrideLen = gradXgradY.chunkSpan / inDataSz;
	int16s outStrideLen = accGradXSqr.chunkSpan/outDataSz;

	accum_gradient_matrix_filter(lpvGradXSqr, lpvGradYSqr, lpvGradXGradY, 
								  lpvAccGradXSqr, lpvAccGradYSqr, lpvAccGradXY,/* lpvAccDetG_high, */lpvAccDetG_inv, lpvValidPts,
								  gradXgradY.chunkWidth, gradXgradY.chunkHeight, inStrideLen, outStrideLen);
}




#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
