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
* \file color_conversion.cpp
* \addtogroup apexcv-color_conversion
* \addtogroup color_conversion
* \ingroup color_conversion
* @{
* \brief color_conversion operations mimicking opencv
*/

/*!*********************************************************************************
*  @file color_conversion.c
*  @brief ACF metadata and wrapper function for color conversion kernels
***********************************************************************************/

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA
#include "color_conversion_kernels.h"

/*!*********************************************************************************
*  \brief ACF metadata for rgb565 to rgb888x
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(RGB565_TO_RGB888_K)
(
   RGB565_TO_RGB888_KN,
   2,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d16u),
          __e0_size(1, 1),
          __ek_size(1, 1)),    
   __port(__index(1),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

/*!*********************************************************************************
*  \brief ACF metadata for rgb888x to rgb565
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(RGB888_TO_RGB565_K)
(
   RGB888_TO_RGB565_KN,
   2,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(1, 1)),    
   __port(__index(1),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d16u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

/*!*********************************************************************************
*  \brief ACF metadata for rgb888x to y
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(RGB888_TO_Y_K)
(
   RGB888_TO_Y_KN,
   5,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(4, 1),
          __ek_size(1, 1)), 
	 __port(__index(1),
          __identifier(R2Y),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32s),
          __e0_size(1, 1),
          __ek_size(1, 1)),    		
	 __port(__index(2),
          __identifier(G2Y),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32s),
          __e0_size(1, 1),
          __ek_size(1, 1)), 
	 __port(__index(3),
          __identifier(B2Y),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32s),
          __e0_size(1, 1),
          __ek_size(1, 1)),  					
   __port(__index(4),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

/*!*********************************************************************************
*  \brief ACF metadata for rgb888x to y
*  \see UG-10267-03 ACF User Guide, Section 3.2.2
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO  kernelInfoConcat(RGB888_TO_YUV_K)
(
   RGB888_TO_YUV_KN,
   2,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(4, 1),
          __ek_size(1, 1)), 				
   __port(__index(1),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT), 
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(4, 1),
          __ek_size(1, 1))
);

/*!*********************************************************************************
*  \brief ACF metadata for Hand-Tuned 3 Channel to Grayscale Conversion
***********************************************************************************/
#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO kernelInfoConcat(HT_8UC3_TO_Y_K)
(
   HT_8UC3_TO_Y_KN,
   6,
   __port(__index(0),
          __identifier(INPUT_0),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(4, 1),
          __ek_size(1, 1)),
   __port(__index(1),
          __identifier(KA),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(2),
          __identifier(KB),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(3),
          __identifier(KC),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(4),
          __identifier(KR),
          __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d16u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(5),
          __identifier(OUTPUT_0),
          __attributes(ACF_ATTR_VEC_OUT),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d16s),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_color_conversion_impl.h"

/*!*********************************************************************************
*  \brief ACF wrapper function for rgb565 to rgb888
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void rgb565_to_rgb888(kernel_io_desc lIn0, kernel_io_desc lOut0)
{
   vec16u* lpvIn0  = (vec16u*)lIn0.pMem;
   vec32u* lpvOut0 = (vec32u*)lOut0.pMem;
   
   apu_csc_rgb565_to_rgb888(lpvOut0, lOut0.chunkSpan / 4,
                             lpvIn0, lIn0.chunkSpan / 2,
                    lIn0.chunkWidth, lIn0.chunkHeight);
}

/*!*********************************************************************************
*  \brief ACF wrapper function for rgb888 to rgb565
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void rgb888_to_rgb565(kernel_io_desc lIn0, kernel_io_desc lOut0)
{
   vec32u* lpvIn0  = (vec32u*)lIn0.pMem;
   vec16u* lpvOut0 = (vec16u*)lOut0.pMem;
   
   apu_csc_rgb888_to_rgb565(lpvOut0, lOut0.chunkSpan / 2,
                             lpvIn0, lIn0.chunkSpan / 4,
                    lIn0.chunkWidth, lIn0.chunkHeight);
}

/*!*********************************************************************************
*  \brief ACF wrapper function for rgb888x to y
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void rgb888_to_y(kernel_io_desc lIn0, kernel_io_desc lR2Y, kernel_io_desc lG2Y, kernel_io_desc lB2Y, kernel_io_desc lOut0)
{
  vec08u* lpvIn0  = (vec08u*)lIn0.pMem;
  int32_t* lpR2Y = (int32_t*)lR2Y.pMem;
  int32_t* lpG2Y = (int32_t*)lG2Y.pMem;
  int32_t* lpB2Y = (int32_t*)lB2Y.pMem;
  vec08u* lpvOut0 = (vec08u*)lOut0.pMem;
   
  apu_csc_rgb2y(lpvOut0, lOut0.chunkSpan,
                 lpvIn0, lIn0.chunkSpan,
        lIn0.chunkWidth, lIn0.chunkHeight,
               lpR2Y[0], lpG2Y[0], lpB2Y[0]);
}

/*!*********************************************************************************
*  \brief ACF wrapper function for rgb888x to yuv
*  \see UG-10267-03 ACF User Guide, Section 3.2.3
***********************************************************************************/                                 
void rgb888_to_yuv(kernel_io_desc lIn0, kernel_io_desc lOut0)
{
  vec08u* lpvIn0  = (vec08u*)lIn0.pMem;
  vec08u* lpvOut0 = (vec08u*)lOut0.pMem;
   
  apu_csc_rgb2yuv(lpvOut0, lOut0.chunkSpan,
                   lpvIn0, lIn0.chunkSpan,
          lIn0.chunkWidth, lIn0.chunkHeight );
}

/*!*********************************************************************************
*  \brief ACF wrapper function for Hand-Tuned 3 Channel to Grayscale Conversion
***********************************************************************************/
void ht_8UC3_to_y(kernel_io_desc lIn0, kernel_io_desc lKA, kernel_io_desc lKB, kernel_io_desc lKC, kernel_io_desc lKR, kernel_io_desc lOut0)
{
  vec08u* lpvIn0  = (vec08u*)lIn0.pMem;
  uint8_t* lpKA = (uint8_t*)lKA.pMem;
  uint8_t* lpKB = (uint8_t*)lKB.pMem;
  uint8_t* lpKC = (uint8_t*)lKC.pMem;
  uint16_t* lpKR = (uint16_t*)lKR.pMem;
  vec16s* lpvOut0 = (vec16s*)lOut0.pMem;

   ht::apu_csc_8UC3_Y(lpvOut0, lOut0.chunkSpan>>1,
                       lpvIn0, lIn0.chunkSpan,
              lIn0.chunkWidth, lIn0.chunkHeight,
                      lpKA[0], lpKB[0], lpKC[0], lpKR[0]);
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
/*! @} */
