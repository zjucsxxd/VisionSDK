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
#ifndef APU_DOT_SQR_KERNEL_H
#define APU_DOT_SQR_KERNEL_H

#include "stringify_macros.h"

#define SQR_In16s_Out32u_K		apu_dot_sqr_in16s_out32u
#define SQR_In16s_Out32u_KN		XSTR(SQR_In16s_Out32u_K)

#define SQR_In32s_Out32u_K		apu_dot_sqr_in32s_out32u
#define SQR_In32s_Out32u_KN		XSTR(SQR_In32s_Out32u_K)

#define SQR_In32s_Out64u_K		apu_dot_sqr_in32s_out64u
#define SQR_In32s_Out64u_KN		XSTR(SQR_In32s_Out64u_K)

#define SQR_KN_IN		"INPUT"
#define SQR_KN_OUT		"OUTPUT"
#define SQR_KN_OUT_HIGH	"OUTPUT_High"
#define SQR_KN_OUT_LOW	"OUTPUT_Low"


#ifdef APEX2_EMULATE
extKernelInfoDecl(SQR_In16s_Out32u_K);
void SQR_In16s_Out32u_K(kernel_io_desc lImgInA, kernel_io_desc lImgOut);

extKernelInfoDecl(SQR_In32s_Out32u_K);
void SQR_In32s_Out32u_K(kernel_io_desc lImgInA, kernel_io_desc lImgOut);

extKernelInfoDecl(SQR_In32s_Out64u_K);
void SQR_In32s_Out64u_K(kernel_io_desc lImgInA, kernel_io_desc lImgOut_high, kernel_io_desc lImgOut_low);

#endif // APEX2_EMULATE

#endif //APU_DOT_SQR_KERNEL_H

