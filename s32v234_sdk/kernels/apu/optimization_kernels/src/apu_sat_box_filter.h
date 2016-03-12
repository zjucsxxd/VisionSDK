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

#ifndef APU_SAT_BOX_FILTER_H
#define APU_SAT_BOX_FILTER_H

#ifdef APEX2_EMULATE
#include "apu_cond.hpp"
#else
#define APU_VSIZE 32
#endif

#include "stringify_macros.h"

#define SAT_BOX_FILTER_K		apu_sat_box_filter // same name as the kernel function
#define SAT_BOX_FILTER_KN		XSTR(SAT_BOX_FILTER_K) 

//#define SAT_BOX_FILTER_64u_K	apu_sat_box_filter_64u_selected_points // same name as the kernel function
//#define SAT_BOX_FILTER_64u_KN	XSTR(SAT_BOX_FILTER_64u_K) 

#define SAT_BOX_FILTER_64s_K	apu_sat_box_filter_64s_selected_points // same name as the kernel function
#define SAT_BOX_FILTER_64s_KN	XSTR(SAT_BOX_FILTER_64s_K) 

#define SAT_BOX_FILTER_IN			"INPUT"
#define SAT_BOX_FILTER_OUT			"OUTPUT"

#define SAT_BOX_FILTER_KN_64_IN_HIGH	"SatBoxFlt64_InH"
#define SAT_BOX_FILTER_KN_64_IN_LOW	"SatBoxFlt64_InL"
#define SAT_BOX_FILTER_KN_64_OUT_HIGH "SatBoxFlt64_OutH"
#define SAT_BOX_FILTER_KN_64_OUT_LOW	"SatBoxFlt64_OutL"
#define SAT_BOX_FILTER_KN_64_OFFS_X		"SatBoxFlt64_OffsX"
#define SAT_BOX_FILTER_KN_64_OFFS_Y		"SatBoxFlt64_OffsY"
#define SAT_BOX_FILTER_KN_64_NRPTS		"SatBoxFlt64_NrPts"
#define SAT_BOX_FILTER_KN_64_TMPVECT	"SatBoxFlt64_TmpVect"

#define SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH	 (APU_VSIZE * 2) // *VECT_TILE_WIDTH
#define SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT	  1 // VECT_TILE_HEIGHT

#define SAT_BOX_FILTER_64_OUT_WIDTH			APU_VSIZE
#define SAT_BOX_FILTER_64_OUT_HEIGHT			(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH/SAT_BOX_FILTER_64_OUT_WIDTH + 1) 

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

#include "stringify_macros.h"

extKernelInfoDecl(SAT_BOX_FILTER_K);
void SAT_BOX_FILTER_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SAT_BOX_FILTER_64s_K);
void SAT_BOX_FILTER_64s_K(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lTmpDone);

#endif //APEX2_EMULATE

#endif //#ifndef APU_SAT_BOX_FILTER_H


