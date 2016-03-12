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


#ifndef APU_SAT_INDIRECT_BOX_FILTER_H
#define APU_SAT_INDIRECT_BOX_FILTER_H

#ifdef APEX2_EMULATE
#include "apu_cond.hpp"
#else
#include <common.h> // needed for the definition of APU_VSIZE
#endif

#include "stringify_macros.h"
//#define SAT_BOX_FILTER_64u_K	apu_sat_box_filter_indirect_64u_selected_points // same name as the kernel function
//#define SAT_BOX_FILTER_64u_KN	XSTR(SAT_BOX_FILTER_64u_K) 

#define SAT_BOX_FILTER_INDIR_64s_K	apu_sat_box_filter_indirect_64s_selected_points // same name as the kernel function
#define SAT_BOX_FILTER_INDIR_64s_KN	XSTR(SAT_BOX_FILTER_INDIR_64s_K) 

#define SAT_BOX_FILTER_INPUT			"INPUT"
#define SAT_BOX_FILTER_OUTPUT			"OUTPUT"

#define SAT_BOX_FILTER_KERNEL_64_INPUT_HIGH	"SatBoxFlt64_InH"
#define SAT_BOX_FILTER_KERNEL_64_INPUT_LOW	"SatBoxFlt64_InL"
#define SAT_BOX_FILTER_KERNEL_64_OUTPUT_HIGH "SatBoxFlt64_OutH"
#define SAT_BOX_FILTER_KERNEL_64_OUTPUT_LOW	"SatBoxFlt64_OutL"
#define SAT_BOX_FILTER_KERNEL_64_OFFS_X		"SatBoxFlt64_OffsX"
#define SAT_BOX_FILTER_KERNEL_64_OFFS_Y		"SatBoxFlt64_OffsY"
#define SAT_BOX_FILTER_KERNEL_64_NRPTS		"SatBoxFlt64_NrPts"
#define SAT_BOX_FILTER_KERNEL_64_TMPVECT	"SatBoxFlt64_TmpVect"

#define SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH	 (APU_VSIZE * 2) // *VECT_TILE_WIDTH
#define SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT	  1 // VECT_TILE_HEIGHT

#define SAT_BOX_FILTER_64_OUTPUT_WIDTH			APU_VSIZE
#define SAT_BOX_FILTER_64_OUTPUT_HEIGHT			(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH/SAT_BOX_FILTER_64_OUTPUT_WIDTH + 1) 

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

#include "stringify_macros.h"

//extKernelInfoDecl(SAT_BOX_FILTER_64u_K);
//void SAT_BOX_FILTER_64u_K(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow);

extKernelInfoDecl(SAT_BOX_FILTER_INDIR_64s_K);
void SAT_BOX_FILTER_INDIR_64s_K(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lTmpDone);

#endif
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
