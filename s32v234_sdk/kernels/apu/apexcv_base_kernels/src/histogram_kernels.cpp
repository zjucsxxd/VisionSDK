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
* \file histogram.cpp
* \addtogroup apexcv-histogram
* \addtogroup histogram
* \ingroup histogram
* @{
* \brief histogram operations mimicking opencv
*/

/*!*********************************************************************************
*  @file histogram.c
*  @brief ACF metadata and wrapper function for histogram kernels
***********************************************************************************/

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA
#include "histogram_kernels.h"

/*!*********************************************************************************
*  \brief ACF metadata for histogram
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(HISTOGRAM_K)
(
   HISTOGRAM_KN,
   3,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),     
   __port(__index(1),
          __identifier(L_HIST),
          __attributes(ACF_ATTR_VEC_OUT_STATIC_FIXED), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d16u),
          __e0_size(1, 1),
          __ek_size(256, 1)),					
   __port(__index(2),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(256, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_histogram_impl.h"

/*!*********************************************************************************
*  \brief ACF wrapper function for histogram
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void histogram(kernel_io_desc lIn0, kernel_io_desc llhist, kernel_io_desc lOut0)
{
   vec08u*   lpvIn0  = (vec08u*)lIn0.pMem;
   vec16u*	 lplhist = (vec16u*)llhist.pMem;
   uint32_t* lpvOut0 = (uint32_t*)lOut0.pMem;
	
   int16_t lBeginCU = ACF_RET_VAR(ACF_VAR_FIRST_CUID);
   int16_t lEndCU = lBeginCU + ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
	
   if(ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG)) {
      apu_hist_init_l(lplhist);
      apu_hist_init_g(lpvOut0);
   }

   apu_hist1_l(lplhist, lpvIn0, lIn0.chunkSpan, lIn0.chunkWidth, lIn0.chunkHeight);
	
   if(ACF_RET_VAR(ACF_VAR_LAST_TILE_FLAG)) {
      apu_hist1_gn(lpvOut0, lplhist, lBeginCU, lEndCU);
   }
}
	 
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
/*! @} */
