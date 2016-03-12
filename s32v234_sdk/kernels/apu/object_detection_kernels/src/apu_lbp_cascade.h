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

#ifndef APU_LBP_CASC_H
#define  APU_LBP_CASC_H

#include "stringify_macros.h"

#define	LBP_CASC_K		apu_lbp_cascade
#define LBP_CASC_KN		XSTR(LBP_CASC_K)

#define LBP_CASC_IN_INTEGR_IMG 	"INPUT_INTEGRAL_IMAGE"
#define LBP_CASC_LINE_IDX 			"LINE_INDEX"
#define LBP_CASC_WND_BUF			"WINDOW_BUFFER"

#define LBP_CASC_IN_CASC_SZ_AND_SKIP "INPUT_CASCADE_SIZES_AND_SKIP"
#define LBP_CASC_IN_CASC_FEAT 		"INPUT_CASCADE_FEATURES"
#define LBP_CASC_IN_CASC_STAGES 	"INPUT_CASCADE_STAGES"
#define LBP_CASC_IN_PIX_SHFT 		"INPUT_PIXEL_SHIFTS"
#define LBP_CASC_IN_PIX_OFFS 		"INPUT_PIXEL_OFFSETS"
#define LBP_CASC_OUT				"OUTPUT"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(LBP_CASC_K);
void LBP_CASC_K(
	kernel_io_desc lInII,
	kernel_io_desc lLineIndex,
	kernel_io_desc lWindowBuffer,
	kernel_io_desc lInCSizesAndSkip,
	kernel_io_desc lInCFeatures,
	kernel_io_desc lInCstages,
	kernel_io_desc lInPixelShifts,
	kernel_io_desc lInPixelOffsets,
	kernel_io_desc lOut);

#endif

#endif 



