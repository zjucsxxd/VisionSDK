#ifndef APU_SAT_INDIRECT_KERNEL_H
#define APU_SAT_INDIRECT_KERNEL_H

#include "stringify_macros.h"

/*
#define SAT_in32u_out64u_K		apu_sat_indirect_in32u_out64u
#define SAT_in32u_out64u_KN		XSTR(SAT_in32u_out64u_K) 
*/
#define SAT_indirect_in32s_out64s_K		apu_sat_indirect_in32s_out64s
#define SAT_indirect_in32s_out64s_KN	XSTR(SAT_indirect_in32s_out64s_K) 


#define SAT_KERNEL_INPUT					"INPUT"
#define SAT_KERNEL_OUTPUT					"OUTPUT"
#define SAT_KERNEL_OUTPUT_ROW				"OUTPUT_ROW"

#define SATSQRD_KERNEL_INPUT				"INPUT"
#define SATSQRD_KERNEL_OUTPUT				"OUTPUT"
#define SATSQRD_KERNEL_OUTPUT_ROW			"OUTPUT_ROW"
#define SATSQRD_KERNEL_OUTPUT_SQUARED		"OUTPUT_SQUARED"
#define SATSQRD_KERNEL_OUTPUT_ROW_SQUARED	"OUTPUT_ROW_SQUARED"


#define SAT_in32u_out64u_K_INPUT			"Sat64uK_In"
#define SAT_in32u_out64u_K_OUT_HIGH			"Sat64uK_Out_High"
#define SAT_in32u_out64u_K_OUT_LOW			"Sat64uK_Out_Low"
#define SAT_in32u_out64u_K_ROW_OUT_HIGH		"Sat64uK_RowOut_High"
#define SAT_in32u_out64u_K_ROW_OUT_LOW		"Sat64uK_RowOut_Low"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

/*
extKernelInfoDecl(SAT_in32u_out64u_K);
void SAT_in32u_out64u_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);
*/

extKernelInfoDecl(SAT_in32s_out64s_K);
void SAT_in32s_out64s_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);


#endif

#endif 
