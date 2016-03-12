/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 ******************************************************************************/

/*!
* \file integral_image.cpp
* \addtogroup apexcv-integral_image
* \addtogroup integral_image
* \ingroup integral_image
* @{
* \brief integral_image operations mimicking opencv
*/

/*!*********************************************************************************
*  @file integral_image.c
*  @brief ACF metadata and wrapper function for integral image kernel
***********************************************************************************/

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA
#include "integral_image_kernels.h"

/*!*********************************************************************************
*  \brief ACF metadata for integral image
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(INTEGRAL_IMAGE_K)
(
   INTEGRAL_IMAGE_KN,
   3,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),     
   __port(__index(1),
          __identifier(T_LST),
          __attributes(ACF_ATTR_VEC_OUT_STATIC_FIXED), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(16, 1)),					
   __port(__index(2),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_integral_image_impl.h"

/*!*********************************************************************************
*  \brief ACF wrapper function for histogram
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void integral_image(kernel_io_desc lIn0, kernel_io_desc ltlst, kernel_io_desc lOut0)
{
	vec08u*   lpvIn0  = (vec08u*)lIn0.pMem;
	vec32u*		lptlst  = (vec32u*)ltlst.pMem;
	vec32u*   lpvOut0 = (vec32u*)lOut0.pMem;
	
	int16_t lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	
	if(ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG)) {
		apu_integral_init(lptlst, lIn0.chunkWidth);
	}

	apu_integral_image(lpvOut0, lOut0.chunkSpan / 4, lpvIn0, lptlst, lIn0.chunkSpan, lIn0.chunkWidth, lIn0.chunkHeight, lTileWidthInChunks);
}

	 
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
/*! @} */
