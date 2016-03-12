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

#ifndef APU_SAT_NONZERO_H
#define  APU_SAT_NONZERO_H

#include "stringify_macros.h"

#define	SAT_NONZERO_K	apu_saturate_nonzero
#define SAT_NONZERO_KN	XSTR(SAT_NONZERO_K)

#define	BINARIZE_K		apu_binarize
#define BINARIZE_KN		XSTR(BINARIZE_K)

#define	MASK_K			apu_mask
#define MASK_KN			XSTR(MASK_K)


#define SAT_NONZERO_IN	"INPUT_0"
#define SAT_NONZERO_OUT	"OUTPUT_0"

#define BINARIZE_IN		"BIN_IN"
#define BINARIZE_OUT	"BIN_OUT"

#define MASK_INFLAGS	"MASK_INFL"
#define MASK_INX		"MASK_INX"
#define MASK_INY		"MASK_INY"
#define MASK_OUTX		"MASK_OUTX"
#define MASK_OUTY		"MASK_OUTY"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(SAT_NONZERO_K);
void SAT_NONZERO_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(BINAIRZE_K);
void BINAIRZE_K(kernel_io_desc lIn0, kernel_io_desc lOut0);


extKernelInfoDecl(MASK_K);
void MASK_K(kernel_io_desc lInFlags, kernel_io_desc lInX, kernel_io_desc lInY, kernel_io_desc lOutX, kernel_io_desc lOutY);

#endif

#endif 



