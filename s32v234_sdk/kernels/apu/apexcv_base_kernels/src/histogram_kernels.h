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

#ifndef _APU_APEXCV_BASE_HISTOGRAM_H_
#define _APU_APEXCV_BASE_HISTOGRAM_H_

#include "stringify_macros.h"

#define HISTOGRAM_K			histogram
#define HISTOGRAM_KN	XSTR(HISTOGRAM_K)


#define INPUT_0		"INPUT_0"
#define OUTPUT_0	"OUTPUT_0"
#define L_HIST		"L_HIST"

#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(HISTOGRAM_K);
void HISTOGRAM_K(kernel_io_desc lIn0, kernel_io_desc llhist, kernel_io_desc lOut0);
	 
#endif //#ifdef APEX2_EMULATE
#endif
