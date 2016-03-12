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

#ifndef _APU_APEXCV_BASE_INTEGRAL_IMAGE_H_
#define _APU_APEXCV_BASE_INTEGRAL_IMAGE_H_

#include "stringify_macros.h"

#define INTEGRAL_IMAGE_K	integral_image
#define INTEGRAL_IMAGE_KN	XSTR(INTEGRAL_IMAGE_K)


#define INPUT_0		"INPUT_0"
#define OUTPUT_0	"OUTPUT_0"
#define T_LST		"T_LST"


#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(INTEGRAL_IMAGE_K);
void INTEGRAL_IMAGE_K(kernel_io_desc lIn0, kernel_io_desc ltlst, kernel_io_desc lOut0);

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

#endif
