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


#ifndef _APU_APEXCV_INTERPOLATION_H_
#define _APU_APEXCV_INTERPOLATION_H_


#include "stringify_macros.h"

#define INTERP_LIN_GRAYSC_K		interp_linear_grayscale
#define INTERP_LIN_GRAYSC_KN	XSTR(INTERP_LIN_GRAYSC_K )

#define INTERP_BILIN_GRAYSC_K	interp_bilinear_grayscale
#define INTERP_BILIN_GRAYSC_KN	XSTR(INTERP_BILIN_GRAYSC_K)

#define INTERP_BICUBIC_GRAYSC_K		interp_bicubic_grayscale
#define INTERP_BICUBIC_GRAYSC_KN	XSTR(INTERP_BICUBIC_GRAYSC_K)

#define INPUT_0		"INPUT_0"
#define OUTPUT_0	"OUTPUT_0"

#define DELTA_X		"DELTA_X"
#define DELTA_XY	"DELTA_XY"

#define X_OFFSET	"X_OFFSET"
#define Y_OFFSET	"Y_OFFSET"

#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(INTERP_LIN_GRAYSC_K);
void INTERP_LIN_GRAYSC_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lDelta0);

extKernelInfoDecl(INTERP_BILIN_GRAYSC_K);
void INTERP_BILIN_GRAYSC_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lDelta0);


extKernelInfoDecl(INTERP_BICUBIC_GRAYSC_K);
void INTERP_BICUBIC_GRAYSC_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lXOffs, kernel_io_desc lYOffs);

#endif 

#endif

