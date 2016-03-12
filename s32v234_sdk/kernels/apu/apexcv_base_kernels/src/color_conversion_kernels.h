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
  
/*!*********************************************************************************
*  @file color_conversion.c
*  @brief ACF metadata and wrapper function for color conversion kernels
***********************************************************************************/


#ifndef _APU_APEXCV_BASE_COLOR_CONVERSION_H_
#define _APU_APEXCV_BASE_COLOR_CONVERSION_H_


#include "stringify_macros.h"

#define RGB565_TO_RGB888_K		rgb565_to_rgb888	
#define RGB565_TO_RGB888_KN		XSTR(RGB565_TO_RGB888_K)

#define RGB888_TO_RGB565_K		rgb888_to_rgb565
#define RGB888_TO_RGB565_KN		XSTR(RGB888_TO_RGB565_K)

#define RGB888_TO_Y_K			rgb888_to_y
#define RGB888_TO_Y_KN			XSTR(RGB888_TO_Y_K)	


#define RGB888_TO_YUV_K			rgb888_to_yuv
#define RGB888_TO_YUV_KN		XSTR(RGB888_TO_YUV_K)

#define HT_8UC3_TO_Y_K			ht_8UC3_to_y
#define HT_8UC3_TO_Y_KN			XSTR(HT_8UC3_TO_Y_K)


#define INPUT_0		"INPUT_0"
#define OUTPUT_0	"OUTPUT_0"
#define R2Y			"R2Y"
#define G2Y			"G2Y"
#define B2Y			"B2Y"
#define KA			"KA"
#define KB			"KB"
#define KC			"KC"
#define KR			"KR"

#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(RGB565_TO_RGB888_K);
void RGB565_TO_RGB888_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(RGB888_TO_RGB565_K);
void RGB888_TO_RGB565_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(RGB888_TO_Y_K);
void RGB888_TO_Y_K(kernel_io_desc lIn0, kernel_io_desc lR2Y, kernel_io_desc lG2Y, kernel_io_desc lB2Y, kernel_io_desc lOut0);

extKernelInfoDecl(RGB888_TO_YUV_K);
void RGB888_TO_YUV_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_8UC3_TO_Y_K);
void HT_8UC3_TO_Y_K(kernel_io_desc lIn0, kernel_io_desc lKA, kernel_io_desc lKB, kernel_io_desc lKC, kernel_io_desc lKR, kernel_io_desc lOut0);

#endif //#ifdef APEX2_EMULATE

#endif
