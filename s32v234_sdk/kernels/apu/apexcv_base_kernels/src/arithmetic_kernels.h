/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2013 All right reserved.
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


#ifndef _APU_APEXCV_BASE_ARITHMETIC_H_
#define _APU_APEXCV_BASE_ARITHMETIC_H_


#include "stringify_macros.h"

#define ABS_08u_K			abs_08u	
#define ABS_08u_KN			XSTR(ABS_08u_K)

#define ABSDIFF_08u_K		absdiff_08u
#define ABSDIFF_08u_KN		XSTR(ABSDIFF_08u_K)

#define ACCUM_16s_K			accumulate_16s
#define ACCUM_16s_KN		XSTR(ACCUM_16s_K)

#define ACCUM_SQRD_16s_K	accumulate_squared_16s
#define ACCUM_SQRD_16s_KN	XSTR(ACCUM_SQRD_16s_K)

#define ACCUM_WGTD_08u_K	accumulate_weighted_08u
#define ACCUM_WGTD_08u_KN	XSTR(ACCUM_WGTD_08u_K)

#define ADD_08u_K			add_08u
#define ADD_08u_KN			XSTR(ADD_08u_K)

#define ADD_16s_K			add_16s
#define ADD_16s_KN			XSTR(ADD_16s_K)

#define AND_08u_K			and_08u
#define AND_08u_KN			XSTR(AND_08u_K)

#define AND_16u_K			and_16u
#define AND_16u_KN			XSTR(AND_16u_K)

#define AND_32u_K			and_32u
#define AND_32u_KN			XSTR(AND_32u_K)

#define CLZ_08u_K			clz_08u
#define CLZ_08u_KN			XSTR(CLZ_08u_K)

#define CLZ_08s_K			clz_08s
#define CLZ_08s_KN			XSTR(CLZ_08s_K)

#define CLZ_16u_K			clz_16u
#define CLZ_16u_KN			XSTR(CLZ_16u_K)

#define CLZ_16s_K			clz_16s
#define CLZ_16s_KN			XSTR(CLZ_16s_K)

#define MAGNITUDE_16s_K		magnitude_16s
#define MAGNITUDE_16s_KN	XSTR(MAGNITUDE_16s_K)

#define NOT_08u_K			not_08u
#define NOT_08u_KN			XSTR(NOT_08u_K)

#define OR_08u_K			or_08u
#define OR_08u_KN			XSTR(OR_08u_K)

#define OR_16u_K			or_16u
#define OR_16u_KN			XSTR(OR_16u_K)

#define OR_32u_K			or_32u
#define OR_32u_KN			XSTR(OR_32u_K)

#define SUB_08u_K			sub_08u
#define SUB_08u_KN			XSTR(SUB_08u_K)

#define SUB_16s_K			sub_16s
#define SUB_16s_KN			XSTR(SUB_16s_K)

#define THRESH_08u_K		threshold_08u
#define THRESH_08u_KN		XSTR(THRESH_08u_K)

#define THRESH_16u_K		threshold_16u
#define THRESH_16u_KN		XSTR(THRESH_16u_K)

#define THRESH_32u_K		threshold_32u
#define THRESH_32u_KN		XSTR(THRESH_32u_K)

#define XOR_08u_K			xor_08u
#define XOR_08u_KN			XSTR(XOR_08u_K)

#define XOR_16u_K			xor_16u
#define XOR_16u_KN			XSTR(XOR_16u_K)

#define XOR_32u_K			xor_32u
#define XOR_32u_KN			XSTR(XOR_32u_K)



#define INPUT_0		"INPUT_0"
#define INPUT_1		"INPUT_1"
#define OUTPUT_0	"OUTPUT_0"
#define OUTPUT_1	"OUTPUT_1"
#define ALPHA		"ALPHA"



#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(ABS_08u_K);
void ABS_08u_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(ABSDIFF_08u_K);
void ABSDIFF_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(ACCUM_16s_K);
void ACCUM_16s_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(ACCUM_SQRD_16s_K);
void ACCUM_SQRD_16s_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lAlpha, kernel_io_desc lOut0);

extKernelInfoDecl(ACCUM_WGTD_08u_K);
void ACCUM_WGTD_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lAlpha, kernel_io_desc lOut0);

extKernelInfoDecl(ADD_08u_K);
void ADD_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(ADD_16s_K);
void ADD_16s_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(AND_08u_K);
void AND_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(AND_16u_K);
void AND_16u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(AND_32u_K);
void AND_32u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(CLZ_08u_K);
void CLZ_08u_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(CLZ_08s_K);
void CLZ_08s_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(CLZ_16u_K);
void CLZ_16u_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(CLZ_16s_K);
void CLZ_16s_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(MAGNITUDE_16s_K);
void MAGNITUDE_16s_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(NOT_08u_K);
void NOT_08u_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(OR_08u_K);
void OR_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(OR_16u_K);
void OR_16u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(OR_32u_K);
void OR_32u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(SUB_08u_K);
void SUB_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(SUB_16s_K);
void SUB_16s_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(THRESH_08u_K);
void THRESH_08u_K(kernel_io_desc lIn0, kernel_io_desc lThreshold, kernel_io_desc lOut0);

extKernelInfoDecl(THRESH_16u_K);
void THRESH_16u_K(kernel_io_desc lIn0, kernel_io_desc lThreshold, kernel_io_desc lOut0);

extKernelInfoDecl(THRESH_32u_K);
void THRESH_32u_K(kernel_io_desc lIn0, kernel_io_desc lThreshold, kernel_io_desc lOut0);

extKernelInfoDecl(XOR_08u_K);
void XOR_08u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(XOR_16u_K);
void XOR_16u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

extKernelInfoDecl(XOR_32u_K);
void XOR_32u_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lOut0);

#endif //APEX2_EMULATE

#endif 