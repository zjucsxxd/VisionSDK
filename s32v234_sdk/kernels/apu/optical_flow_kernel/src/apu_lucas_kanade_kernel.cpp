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
* \addtogroup of_lucas_kanade Lucas-Kanade
* \ingroup optical_flow
* @{
* \brief Lucas-Kanade method
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#
#ifdef ACF_KERNEL_METADATA

#include "apu_lucas_kanade_kernel.h"


#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
#else
//extern 
const int ACCUM_TILE_SIZE_X = 10; // have to be defined here, otherwise g++ linker complains
//extern 
const int ACCUM_TILE_SIZE_Y = 10;
#endif

#ifndef APEX2_EMULATE
static  
#endif

/****************************************************************************/
/*!
\brief Lucas-Kanade mismatch kernel metadata. 

Calculate the mismatch vector of the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image (Eq. 30).
Ouputs the images of dot products of DeltaK.*GradX and DeltaK.*GradY. 

\param  LUCAS_KANADE_MISMATCH_KN				Define for Kernel name
\param 5										Number of ports
\param "Port LUCAS_KANADE_KN_DELTAK_GRADX_IMG"	Define for name of signed 32bit output image of DeltaK*GradX values, i.e. dot product btw DeltaK and GradX matrices
\param "Port LUCAS_KANADE_KN_DELTAK_GRADY_IMG"	Define for name of signed 32bit output imageof accumulated DeltaK*GradY, i.e. dot product btw DeltaK and GradY matrices
\param "Port LUCAS_KANADE_KN_DELTAK_IMG" 		Define for name of input image (signed 32bit) of the difference between this and the previous images signed 
\param "Port GRADIENT_MATRIX_KN_GRAD_X"			Define for name of Gradient X input image (signed 16bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_Y"			Define for name of Gradient Y input image (signed 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_MISMATCH_K) //_kernel_info_apu_lucas_kanade_mismatch
(
	LUCAS_KANADE_MISMATCH_KN,
    5,

  __port(__index(0),
		  __identifier(LUCAS_KANADE_KN_DELTAK_GRADX_IMG),
		  __attributes(ACF_ATTR_VEC_OUT),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

  __port(__index(1),
		  __identifier(LUCAS_KANADE_KN_DELTAK_GRADY_IMG),
		  __attributes(ACF_ATTR_VEC_OUT),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

  __port(__index(2),
		  __identifier(LUCAS_KANADE_KN_DELTAK_IMG),
		  __attributes(ACF_ATTR_VEC_IN),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

  __port(__index(3),
		  __identifier(LUCAS_KANADE_KN_GRAD_X),
		  __attributes(ACF_ATTR_VEC_IN),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d16s),
		  __e0_size(1, 1),
		  __ek_size(1, 1)),

  __port(__index(4),
		  __identifier(LUCAS_KANADE_KN_GRAD_Y),
		  __attributes(ACF_ATTR_VEC_IN),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d16s),
		  __e0_size(1, 1),
		  __ek_size(1, 1))
);

/*
#ifndef APEX2_EMULATE
static
#endif


KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_ACCUM_K) //_kernel_info_apu_lucas_kanade_accum
(
LUCAS_KANADE_ACCUM_KN,
11,
__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADX_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(3),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADY_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(4),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(7),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(8),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(9),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(10),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))

);
*/

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Lucas-Kanade accumulated mismatch kernel metadata.  
Accumultated etaX = Sum_neigh(deltaKGradX), etaY = Sum_neigh(deltaKGradY) are computed. Neighborhoods are the chunks

\param  LUCAS_KANADE_ACCUM_SIMPLE_KN			Define for Kernel name
\param 10										Number of ports
\param "Port LUCAS_KANADE_KN_DELTAK_GRADX_IMG"	Define for name of output vector of accumulated DeltaK*GradX values, i.e. dot product btw DeltaK and GradX matrices (signed 32bit)
\param "Port LUCAS_KANADE_KN_DELTAK_GRADY_IMG"	Define for name of output vector of accumulated DeltaK*GradY, i.e. dot product btw DeltaK and GradY matrices (signed 32bit)
\param "Port LUCAS_KANADE_KN_DELTAK_IMG"		Define for name of input image of the difference between this and the previous images (signed 32bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_X"			Define for name of Gradient X input image (signed 16bit)
\param "Port GRADIENT_MATRIX_KN_GRAD_Y"			Define for name of Gradient Y input image (signed 16bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_ACCUM_SIMPLE_K)
(
LUCAS_KANADE_ACCUM_SIMPLE_KN,
4,
__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADX_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(3),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADY_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y))


);


/*

#ifndef APEX2_EMULATE
static
#endif
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_K) //_kernel_info_apu_lucas_kanade_accum_simple
(
LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_KN,
6,
__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADX_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(3),
__identifier(LUCAS_KANADE_KN_DELTAK_GRADY_IMG),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(ACCUM_TILE_SIZE_X, ACCUM_TILE_SIZE_Y)),

__port(__index(4),
__identifier(LUCAS_KANADE_KN_XPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KN_YPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KN_NRPTS),
__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))


);
*/


#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
\brief Lucas-Kanade offset for X and Y kernel metadata.  

Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.
[nuEtaX		 =	(1/detG)* [accGradYSqr		-accGradXY]	*	[nuEtaX
nuEtaY]					  -accGradXY		accGradXSqr]	nuEtaY]

Calculate actually either:
nuEtaX = (accGradYSqr*nuEtaX - accGradXY*nuEtaY)/detG
or
nuEtaY = (accGradXSqr*nuEtaY - accGradXY*nuEtaX)/detG


\param  LUCAS_KANADE_OFFSET_XorY_KN				Define for Kernel name
\param 10										Number of ports
\param "Port LUCAS_KANADE_KN_OFFS_G_OUT_VECT"		Define for name of integer part of output offset vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_G_OUT_OFFS_VECT"	Define for name of fractional part of output offset vector in Q3.28 fixed point format (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_ETA_X_VECT" 		Define for name of accumulated X component of mismatch vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_ETA_Y_VECT"		Define for name of accumulated Y component of mismatch vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_ACC_GRAD_XorY_SQR"		Define for name of accumulated either gradX*gradX or gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood  (unsigned 32bit)
\param "Port LUCAS_KANADE_KN_ACC_GRAD_XY"			Define for name of accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood (signed 32bit)
\param "Port LUCAS_KANADE_KN_ACC_DETG_INV"			Define for name of inverse of determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood (unsigned 16bit)
\param "Port LUCAS_KANADE_KN_VALID_POINTS"			Define for name of input boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high) (unsigned 16bit).
\param "Port LUCAS_KANADE_KN_OUT_VALID_POINTS"		Define for name of output boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high). Is AND-ed with input valid points (unsigned 32bit)
\param "Port LUCAS_KANADE_KN_OUT_ETA_NORM"			Define for name of etaNorm vector containing the sum of 16*(gOut+gOutOffs)^2 over the whole vector
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_OFFSET_XorY_K) 
(
	LUCAS_KANADE_OFFSET_XorY_KN,
	10,
	__port(__index(0),
			__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_VECT),
			__attributes(ACF_ATTR_VEC_OUT),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(1),
			__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_OFFS_VECT),
			__attributes(ACF_ATTR_VEC_OUT),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(2),
			__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(3),
			__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(4),
			__identifier(LUCAS_KANADE_KN_ACC_GRAD_XorY_SQR),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(5),
			__identifier(LUCAS_KANADE_KN_ACC_GRAD_XY),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32s),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(6),
			__identifier(LUCAS_KANADE_KN_ACC_DETG_INV),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d32u),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(7),
		__identifier(LUCAS_KANADE_KN_VALID_POINTS),
			__attributes(ACF_ATTR_VEC_IN),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16u),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(8),
		__identifier(LUCAS_KANADE_KN_OUT_VALID_POINTS),
			__attributes(ACF_ATTR_VEC_OUT),
			__spatial_dep(0, 0, 0, 0),
			__e0_data_type(d16u),
			__e0_size(1, 1),
			__ek_size(1, 1)),

	__port(__index(9),
			__identifier(LUCAS_KANADE_KN_OUT_ETA_NORM),
			__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
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
\brief Lucas-Kanade offset for either X or Y with unsigned inputs kernel metadata. 

Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.
[nuEtaX		 =	(1/detG)* [accGradYSqr		-accGradXY]	*	[nuEtaX
nuEtaY]					  -accGradXY		accGradXSqr]	nuEtaY]

Calculate actually either:
nuEtaX = (accGradYSqr*nuEtaX - accGradXY*nuEtaY)/detG
or
nuEtaY = (accGradXSqr*nuEtaY - accGradXY*nuEtaX)/detG

\param  LUCAS_KANADE_OFFSET_XorY_KN					Define for Kernel name
\param 10											Number of ports
\param "Port LUCAS_KANADE_KN_OFFS_G_OUT_VECT"		Define for name of integer part of output offset vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_G_OUT_OFFS_VECT"	Define for name of fractional part of output offset vector in Q3.28 fixed point format (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_ETA_X_VECT" 		Define for name of accumulated X component of mismatch vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_OFFS_ETA_Y_VECT"		Define for name of accumulated Y component of mismatch vector (signed 32bit)
\param "Port LUCAS_KANADE_KN_ACC_GRAD_XorY_SQR"		Define for name of accumulated either gradX*gradX or gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood  (unsigned 32bit)
\param "Port LUCAS_KANADE_KN_ACC_GRAD_XY"			Define for name of accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood (signed 32bit)
\param "Port LUCAS_KANADE_KN_ACC_DETG_INV"			Define for name of inverse of determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood (signed 32bit)
\param "Port LUCAS_KANADE_KN_VALID_POINTS"			Define for name of input boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high) (unsigned 16bit).
\param "Port LUCAS_KANADE_KN_OUT_VALID_POINTS"		Define for name of output boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high). Is AND-ed with input valid points (unsigned 16bit)
\param "Port LUCAS_KANADE_KN_OUT_ETA_NORM"			Define for name of etaNorm vector containing the sum of 16*(gOut+gOutOffs)^2 over the whole vector  (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_OFFSET_XorY_unsigned_K)
(
LUCAS_KANADE_OFFSET_XorY_unsigned_KN,
10,
__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_OFFS_VECT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_XorY_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KN_ACC_DETG_INV),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(7),
__identifier(LUCAS_KANADE_KN_VALID_POINTS),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d16u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(8),
__identifier(LUCAS_KANADE_KN_OUT_VALID_POINTS),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d16u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(9),
__identifier(LUCAS_KANADE_KN_OUT_ETA_NORM),
__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1))
);

#ifndef APEX2_EMULATE
static
#endif

/*!
\brief Transform Coordinates kernel metainfo. 

Helper kernel. Computes from x,y image coordinates the byte offset in the image. 
Outputs a vector of offsets. This is needed for indirect inputs.

\param  LUCAS_KANADE_OFFSET_TransfCoordsToOffs_KN				Define for Kernel name
\param 6														Number of paramaters
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutOffsets"	Define for name of output byte indices (unsigned 32bit)
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutValidPts" Define for name of output flag array containing the valid points & points inside the array boundaries. It is an AND-ed with the input valid points (unsigned 16bit).
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_XCoords"	Define for name of array containing the x-Coordinates of the points (signed 32bit)
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_YCoords"	Define for name of array containing the y-Coordinates of the points (signed 32bit)
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_InValidPts" Define for name of input flag array containing the valid points & points inside the array boundaries (unsigned 16bit).
\param "Port LUCAS_KANADE_OFFSET_TransfCoordsToOffs_StaticData"	Define for name of input array of five elements containing imgWidth/Height, tileWidth/Height, overall data size (signed 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_K) 
(
LUCAS_KANADE_OFFSET_TransfCoordsToOffs_KN,
6,
	__port(__index(0),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutOffsets),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(1),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutValidPts),
		__attributes(ACF_ATTR_VEC_OUT),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(2),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_XCoords),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(1, 1)),


	__port(__index(3),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_YCoords),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(4),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_InValidPts),
		__attributes(ACF_ATTR_VEC_IN),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d16u),
		__e0_size(1, 1),
		__ek_size(1, 1)),

	__port(__index(5),
		__identifier(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_StaticData),
		__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
		__spatial_dep(0, 0, 0, 0),
		__e0_data_type(d32s),
		__e0_size(1, 1),
		__ek_size(8, 1))

);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION
#include "apu_lucas_kanade_kernel_impl.h"
#include "apu_gradient_matrix_kernel_impl.h" // needed for the accDownScale definition



void apu_lucas_kanade_mismatch(kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img
							  , kernel_io_desc lImgDeltaK,   kernel_io_desc inGradXImg, kernel_io_desc inGradYImg)
{
	//vec08u* imgA = (vec08u*) lImgA.pMem;
	//vec08u* imgB = (vec08u*) lImgB.pMem;
	vec32s* imgDeltaK = (vec32s*)lImgDeltaK.pMem;
	const int16s inDataSz = sizeof(int32s);

	// these two are needed only for intermediate results
	vec32s* deltaK_GradX = (vec32s*) outDeltaK_GradX_Img.pMem;
	vec32s* deltaK_GradY = (vec32s*) outDeltaK_GradY_Img.pMem;
	const int16s outDataSz = sizeof(int32s);

	vec16s*	gradX = (vec16s*) inGradXImg.pMem;
	vec16s*	gradY = (vec16s*) inGradYImg.pMem; 
	int16s nrInEls = lImgDeltaK.chunkSpan / inDataSz;

	lucas_kanade_mismatch_filter(/*imgA, imgB, */deltaK_GradX, deltaK_GradY, imgDeltaK, nrInEls, lImgDeltaK.chunkWidth, lImgDeltaK.chunkHeight, outDeltaK_GradX_Img.chunkSpan/outDataSz, gradX, gradY);
}




void apu_lucas_kanade_accum_simple(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc deltaK_GradX_Img, kernel_io_desc deltaK_GradY_Img
	)
{
	vec32s*	etaOutX = (vec32s*)lOutOffsetEtaXVect.pMem;
	vec32s*	etaOutY = (vec32s*)lOutOffsetEtaYVect.pMem;

	// these two are needed only for intermediate results
	vec32s* deltaK_GradX = (vec32s*)deltaK_GradX_Img.pMem;
	vec32s* deltaK_GradY = (vec32s*)deltaK_GradY_Img.pMem;
	const int32s dataSz = sizeof(int32s);
	int16s nrInEls = deltaK_GradX_Img.chunkSpan / dataSz;

	lucas_kanade_accum_filter(etaOutX, etaOutY, nrInEls, deltaK_GradX_Img.chunkWidth, deltaK_GradX_Img.chunkHeight, deltaK_GradX, deltaK_GradY);
	*etaOutX >>= accDownScale; // (1<<6) == (bw-2)*(bh-2)
	*etaOutY >>= accDownScale;

}


/*
void apu_lucas_kanade_accum_simple_at_offs(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img, kernel_io_desc lXpts, kernel_io_desc lYpts, kernel_io_desc lNrPts)
{
	int32s*	etaOutX = (int32s*)lOutOffsetEtaXVect.pMem;
	int32s*	etaOutY = (int32s*)lOutOffsetEtaYVect.pMem;

	int32s*	xPts = (int32s*)lXpts.pMem;
	int32s*	yPts = (int32s*)lYpts.pMem;

	int32s nrPts = *((int32s*)lNrPts.pMem;

	// these two are needed only for intermediate results
	vec32s* deltaK_GradX = (vec32s*)deltaK_GradX_Img.pMem;
	vec32s* deltaK_GradY = (vec32s*)deltaK_GradY_Img.pMem;
	const int32s dataSz = sizeof(int32s);
	int16s nrInEls = deltaK_GradX_Img.chunkSpan / dataSz;

	int16u nrTiles = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	int16u firstCUIdx = ACF_RET_VAR(ACF_VAR_FIRST_CUID);
	int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);

	static int16u startRow, idxFirstCell;
	if (lFirstTileFl) {
		startRow = 0;
		idxFirstCell = 0;
		memset(etaOutX, '\0', lOutOffsetEtaXVect.chunkHeight*lOutOffsetEtaXVect.chunkSpan);
		memset(etaOutY, '\0', lOutOffsetEtaYVect.chunkHeight*lOutOffsetEtaYVect.chunkSpan);
	}

	lucas_kanade_accum_filter_at_offs(etaOutX, etaOutY, nrInEls, deltaK_GradX_Img.chunkWidth, deltaK_GradX_Img.chunkHeight, deltaK_GradX, deltaK_GradY, xPts, yPts, nrPts, startRow, idxFirstCell);

	// to do it separately 
	*etaOutX >>= accDownScale; // (1<<6) == (bw-2)*(bh-2)
	*etaOutY >>= accDownScale;

}

*/

void apu_lucas_kanade_accum(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
					kernel_io_desc deltaK_GradX_Img, kernel_io_desc deltaK_GradY_Img,					
					kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
					kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
					kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
					kernel_io_desc inGradXGradYImg
					)
{
	vec32s*	etaOutX = (vec32s*)lOutOffsetEtaXVect.pMem;
	vec32s*	etaOutY = (vec32s*)lOutOffsetEtaYVect.pMem;

	// these two are needed only for intermediate results
	vec32s* deltaK_GradX = (vec32s*)deltaK_GradX_Img.pMem;
	vec32s* deltaK_GradY = (vec32s*)deltaK_GradY_Img.pMem;
	const int32s dataSz = sizeof(int32s);

	lucas_kanade_accum_filter(etaOutX, etaOutY, deltaK_GradX_Img.chunkSpan/dataSz, deltaK_GradX_Img.chunkWidth, deltaK_GradX_Img.chunkHeight, deltaK_GradX, deltaK_GradY);
	/*
	vec32s*	gOutX_high = (vec32s*)lOutOffsetGXVect_high.pMem;
	vec32s*	gOutY_high = (vec32s*)lOutOffsetGYVect_high.pMem;
	vec32u*	gOutX_low = (vec32u*)lOutOffsetGXVect_low.pMem;
	vec32u*	gOutY_low = (vec32u*)lOutOffsetGYVect_low.pMem;
	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutOffsetGXVect_high.chunkSpan / outDataSz;



	vec32u*	gradXSqr = (vec32u*)inGradXSqrImg.pMem;
	vec32u*	gradYSqr = (vec32u*)inGradYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	//vec32s*	detG = (vec32s*)inDetGImg.pMem;


	//vec32u	vEtaNorm = 0;
	//int32u& etaNorm = *((int32u*)lEtaNorm.pMem);
	static int32s nrPointsToProcess = 0;
	int16s offsOutStrideLen = lOutOffsetGXVect_high.chunkSpan / outDataSz;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lOutOffsetEtaXVect.chunkSpan / inDataSz;
*/
	// The input chunks are reduced to one value per chunk, thus etaX and etaY contain only one value per CU and can be downsampled directly
	*etaOutX >>= accDownScale; // (1<<6) == (bw-2)*(bh-2)
	*etaOutY >>= accDownScale;
	//lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaOutX, etaOutX, inStrideLen, lOutOffsetEtaXVect.chunkWidth, lOutOffsetEtaXVect.chunkHeight, offsOutStrideLen, gradXSqr, gradYSqr, gradXgradY);
}


/*
void apu_lucas_kanade_offset(
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg)
{
	vec32s*	gOutX_high = (vec32s*)lOutOffsetGXVect_high.pMem;
	vec32s*	gOutY_high = (vec32s*)lOutOffsetGYVect_high.pMem;
	vec32u*	gOutX_low = (vec32u*)lOutOffsetGXVect_low.pMem;
	vec32u*	gOutY_low = (vec32u*)lOutOffsetGYVect_low.pMem;
	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutOffsetGXVect_high.chunkSpan / outDataSz;


	vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
	vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;
	int32s etaInXSz = sizeof(etaInX);

	vec32u*	gradXSqr = (vec32u*)inGradXSqrImg.pMem;
	vec32u*	gradYSqr = (vec32u*)inGradYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	//vec32s*	detG = (vec32s*)inDetGImg.pMem;
	

	//vec32u	vEtaNorm = 0;
	//int32u& etaNorm = *((int32u*)lEtaNorm.pMem);
	//static int32s nrPointsToProcess = 0;
		
	////lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen, gradXSqr, gradYSqr, gradXgradY);
	lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY , gradXSqr, gradYSqr, gradXgradY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen);
	
	/*
	for (int i = 0; i < nrTiles; ++i) {
		etaNorm += vget(vEtaNorm, firstCUIdx + i);
	}
* /
	/*
	for (int i = 0; i < nrTiles; ++i) {
		int32s crtEtaValX = vget((*etaInX), firstCUIdx + i);
		int32s crtEtaValY = vget((*etaInY), firstCUIdx + i);

		int32u absX = (int32u) (crtEtaValX > 0 ? crtEtaValX : -crtEtaValX);
		int32u absY = (int32u) (crtEtaValY > 0 ? crtEtaValY : -crtEtaValY);
		etaNorm += absX + absY;
	}* /
}
*/

void apu_lucas_kanade_offset_xOry(kernel_io_desc lOutGVect, kernel_io_desc lOutGOffsetVect,
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc inGradXorYSqrImg, kernel_io_desc inGradXGradYImg, 
	kernel_io_desc inDetGImg_low, kernel_io_desc linValidPts, kernel_io_desc loutValidPts, 
	kernel_io_desc lEtaNormOut)
{
	vec32s*	gOut= (vec32s*)lOutGVect.pMem;
	vec32s*	gOutOffs = (vec32s*)lOutGOffsetVect.pMem;

	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutGVect.chunkSpan / outDataSz;

	vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
	vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;
	
	int32s etaInXSz = sizeof(etaInX);
	vec32s*	gradXorYSqr = (vec32s*)inGradXorYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	vec32u*	detG_low = (vec32u*)inDetGImg_low.pMem;

	vec16u* inValidPts = (vec16u*) linValidPts.pMem;
	vec16u* outValidPts = (vec16u*) loutValidPts.pMem;

	int32u& etaNormOut = *((int32u*)lEtaNormOut.pMem);

	vec32u vEtaNorm;
	lucas_kanade_offset_filter_xOry(gOut, gOutOffs, etaInX, etaInY, gradXorYSqr, gradXgradY, detG_low, inValidPts, outValidPts,&vEtaNorm, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, inStrideLen, outStrideLen);
	
	int nrTiles = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	int firstCUIdx = ACF_RET_VAR(ACF_VAR_FIRST_CUID);

	if (ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG)) {
		etaNormOut = 0;
	}

	for (int i = 0; i < nrTiles; ++i) {
		etaNormOut += vget(vEtaNorm, firstCUIdx + i);
	}
}

void apu_lucas_kanade_offset_xOry_unsigned(kernel_io_desc lOutGVect, kernel_io_desc lOutGOffsetVect,
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc inGradXorYSqrImg, kernel_io_desc inGradXGradYImg,
	kernel_io_desc inDetGImg_low, kernel_io_desc linValidPts, kernel_io_desc loutValidPts,
	kernel_io_desc lEtaNormOut)
{
	vec32s*	gOut = (vec32s*)lOutGVect.pMem;
	vec32s*	gOutOffs = (vec32s*)lOutGOffsetVect.pMem;

	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutGVect.chunkSpan / outDataSz;

	vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
	vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;

	int32s etaInXSz = sizeof(etaInX);
	vec32u*	gradXorYSqr = (vec32u*)inGradXorYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	vec32u*	detG_low = (vec32u*)inDetGImg_low.pMem;

	vec16u* inValidPts = (vec16u*)linValidPts.pMem;
	vec16u* outValidPts = (vec16u*)loutValidPts.pMem;

	int32u& etaNormOut = *((int32u*)lEtaNormOut.pMem);

	vec32u vEtaNorm;
	lucas_kanade_offset_filter_xOry_unsigned(gOut, gOutOffs, etaInX, etaInY, gradXorYSqr, gradXgradY, detG_low, inValidPts, outValidPts, &vEtaNorm, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, inStrideLen, outStrideLen);

	int nrTiles = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	int firstCUIdx = ACF_RET_VAR(ACF_VAR_FIRST_CUID);

	if (ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG)) {
		etaNormOut = 0;
	}

	for (int i = 0; i < nrTiles; ++i) {
		etaNormOut += vget(vEtaNorm, firstCUIdx + i);
	}
}



void apu_transformCoordsToPointOffs(kernel_io_desc l_PointOffsets, kernel_io_desc l_newValidPts,
	kernel_io_desc l_xCoords, kernel_io_desc l_yCoords, kernel_io_desc l_validPoints,
	kernel_io_desc l_imgWidthHeight_tileWidthHeight_DataSz)
{


	vec32u* lPointOffsets = (vec32u*)l_PointOffsets.pMem;
	vec16u* newValidPts = (vec16u*)l_newValidPts.pMem; 
	vec32s* xCoords = (vec32s*)l_xCoords.pMem;
	vec32s* yCoords = (vec32s*)l_yCoords.pMem;
	vec16u* validPoints = (vec16u*) l_validPoints.pMem;
	int32s imgWidth = ((int32s*)l_imgWidthHeight_tileWidthHeight_DataSz.pMem)[0];
	int32s imgHeight = ((int32s*)l_imgWidthHeight_tileWidthHeight_DataSz.pMem)[1];
	int32s tWidth = ((int32s*)l_imgWidthHeight_tileWidthHeight_DataSz.pMem)[2];
	int32s tHeight = ((int32s*)l_imgWidthHeight_tileWidthHeight_DataSz.pMem)[3];
	int32s dSz = ((int32s*)l_imgWidthHeight_tileWidthHeight_DataSz.pMem)[4];

	int16s bw = l_xCoords.chunkWidth;
	int16s bh = l_xCoords.chunkHeight;
	int16s inputStrideWidth = l_xCoords.chunkSpan/ sizeof(int32s);
	int16s outputStrideWidth = l_PointOffsets.chunkSpan / sizeof(int32u);

	transformCoordsToPointOffsets(lPointOffsets, newValidPts, xCoords, yCoords, validPoints,
								  imgWidth, imgHeight, tWidth, tHeight,
								  dSz, bw, bh, inputStrideWidth, outputStrideWidth);

}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION


/*
#ifndef APEX2_EMULATE
static
#endif
KERNEL_INFO kernelInfoConcat(LUCAS_KANADE_OFFSET_K) //_kernel_info_apu_lucas_kanade_offset
(
LUCAS_KANADE_OFFSET_KN,
9,
__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(7),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(8),
__identifier(LUCAS_KANADE_KN_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))
);


__port(__index(0),
__identifier(LUCAS_KANADE_KN_OFFS_G_IN_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KN_OFFS_G_IN_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

,
__port(__index(10),
__identifier(LUCAS_KANADE_KN_ETA_NORM),
__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1))
*/

/*! @} */
