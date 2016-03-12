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

#ifndef APU_SAT_KN_H
#define APU_SAT_KN_H

#include "stringify_macros.h"

#define SAT_K					apu_sat
#define SAT_KN					XSTR(SAT_K)


#define SAT_SGN_K					apu_sat_sgn
#define SAT_SGN_KN					XSTR(SAT_SGN_K)


#define SAT_PLUS_SQRD_K			apu_sat_plus_squared
#define SAT_PLUS_SQRD_KN		XSTR(SAT_PLUS_SQRD_K) 

/*
#define SAT_in32u_out64u_K		apu_sat_in32u_out64u
#define SAT_in32u_out64u_KN		XSTR(SAT_in32u_out64u_K) 
*/
#define SAT_in32s_out64s_K		apu_sat_in32s_out64s
#define SAT_in32s_out64s_KN		XSTR(SAT_in32s_out64s_K) 

#define SAT_KN_IN					"INPUT"
#define SAT_KN_OUT					"OUTPUT"
#define SAT_KN_OUT_ROW				"OUTPUT_ROW"
#define SAT_KN_ABS_OUT				"ABS_OUT"
#define SAT_KN_OUT_ABS_ROW			"OUT_ABS_ROW"

#define SATSQRD_KN_IN				"INPUT"
#define SATSQRD_KN_OUT				"OUTPUT"
#define SATSQRD_KN_OUT_ROW			"OUTPUT_ROW"
#define SATSQRD_KN_OUT_SQUARED		"OUTPUT_SQUARED"
#define SATSQRD_KN_OUT_ROW_SQUARED	"OUTPUT_ROW_SQUARED"


#define SAT_in32u_out64u_K_IN			"Sat64uK_In"
#define SAT_in32u_out64u_K_OUT_HIGH			"Sat64uK_Out_High"
#define SAT_in32u_out64u_K_OUT_LOW			"Sat64uK_Out_Low"
#define SAT_in32u_out64u_K_ROW_OUT_HIGH		"Sat64uK_RowOut_High"
#define SAT_in32u_out64u_K_ROW_OUT_LOW		"Sat64uK_RowOut_Low"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(SAT_K);
void SAT_K(kernel_io_desc lIn, kernel_io_desc lOut, kernel_io_desc lRow);

extKernelInfoDecl(SAT_SGN_K);
void SAT_SGN_K(kernel_io_desc lIn, kernel_io_desc lOut, kernel_io_desc lAbsOut, kernel_io_desc lRow, kernel_io_desc lAbsRow);

/*
extKernelInfoDecl(SAT_in32u_out64u_K);
void SAT_in32u_out64u_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);
*/

extKernelInfoDecl(SAT_in32s_out64s_K);
void SAT_in32s_out64s_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);


extKernelInfoDecl(SAT_PLUS_SQRD_K);
void SAT_PLUS_SQRD_K(kernel_io_desc lIn, kernel_io_desc lOut,
	kernel_io_desc lOutSquared,	kernel_io_desc lRow,kernel_io_desc lRowSquared);

/*
extKernelInfoDecl(SAT_in32u_out64u_K);
void SAT_in32u_out64u_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);
*/

extKernelInfoDecl(SAT_in32s_out64s_K);
void SAT_in32s_out64s_K(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow);


#endif //APEX2_EMULATE

#endif //#ifndef APU_SAT_KN_H

