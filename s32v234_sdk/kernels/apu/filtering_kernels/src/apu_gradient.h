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

#ifndef APU_GRADIENT_H
#define  APU_GRADIENT_H

#include "stringify_macros.h"

#define	GRADIENT_K			apu_gradient
#define GRADIENT_KN			XSTR(GRADIENT_K)

#define	GRADIENT_ABS_K		apu_gradient_abs
#define GRADIENT_ABS_KN		XSTR(GRADIENT_ABS_K)

#define GR_ABS_K			apu_gr_abs
#define GR_ABS_KN			XSTR(GR_ABS_K)

#define GRADIENT_KN_IN		"INPUT_0"
#define GRADIENT_KN_OUTX	"OUT_GX"
#define GRADIENT_KN_OUTY	"OUT_GY"
#define GRADIENT_KN_ABSSUM  "OUT_ABSSUM"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(GRADIENT_K);
void GRADIENT_K(kernel_io_desc lIn0, kernel_io_desc lgradX, kernel_io_desc lgradY);

extKernelInfoDecl(GRADIENT_ABS_K);
void GRADIENT_ABS_K(kernel_io_desc lIn0, kernel_io_desc lgradX, kernel_io_desc lgradY, kernel_io_desc labsSum);

extKernelInfoDecl(GR_ABS_K);
void GR_ABS_K(kernel_io_desc lIn0, kernel_io_desc labsSum);

#endif

#endif 



