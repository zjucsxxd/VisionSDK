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
#ifndef APU_COPY_INPUT_KERNEL_H
#define APU_COPY_INPUT_KERNEL_H

#include "stringify_macros.h"

#define COPY_IN_IN08u_K			apu_copy_input_in08u_out08u
#define COPY_IN_IN08u_KN			XSTR(COPY_IN_IN08u_K)

#define COPY_IN_IN08u_OUT16u_K	apu_copy_input_in08u_out16u
#define COPY_IN_IN08u_OUT16u_KN	XSTR(COPY_IN_IN08u_OUT16u_K)

#define COPY_IN_IN16u_OUT16s_K	apu_copy_input_in16u_out16s
#define COPY_IN_IN16u_OUT16s_KN	XSTR(COPY_IN_IN16u_OUT16s_K)

#define COPY_IN_IN16s_K			apu_copy_input_in16s_out16s
#define COPY_IN_IN16s_KN			XSTR(COPY_IN_IN16s_K)

#define COPY_IN_IN32s_K			apu_copy_input_in32s_out32s
#define COPY_IN_IN32s_KN			XSTR(COPY_IN_IN32s_K)

#define COPY_IN_IN32u_K			apu_copy_input_in32u_out32u
#define COPY_IN_IN32u_KN			XSTR(COPY_IN_IN32u_K)

#define COPY_IN_IN32u_OUT32s_K			apu_copy_input_in32u_out32s
#define COPY_IN_IN32u_OUT32s_KN			XSTR(COPY_IN_IN32u_OUT32s_KN)

#define COPY_IN_KN_IMG		"INPUT_IMG"
#define COPY_IN_KN_OUT_IMG	"OUTPUT_IMG"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;

extKernelInfoDecl(COPY_IN_IN08u_K);
void COPY_IN_IN08u_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN08u_OUT16u_K);
void COPY_IN_IN08u_OUT16u_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN16s_K);
void COPY_IN_IN16s_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN16u_OUT16s_K);
void COPY_IN_IN16u_OUT16s_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN32s_K);
void COPY_IN_IN32s_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN32s_K);
void COPY_IN_IN32s_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN32u_K);
void COPY_IN_IN32u_K(kernel_io_desc input, kernel_io_desc output);

extKernelInfoDecl(COPY_IN_IN32u_OUT32s_K);
void COPY_IN_IN32u_OUT32s_K(kernel_io_desc input, kernel_io_desc output);
#endif //APEX2_EMULATE

#endif //#ifndef APU_COPY_INPUT_KERNEL_H
