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

#ifndef APU_HARRIS_H
#define  APU_HARRIS_H

#include "stringify_macros.h"

#define	HARRIS_K		apu_harris
#define HARRIS_KN		XSTR(HARRIS_K)

#define HARRIS_KN_IN_GX			"INPUT_GX"
#define HARRIS_KN_IN_GY			"INPUT_GY"
#define HARRIS_KN_IN_K_RBS_WIN	"INPUT_K_RBS_WINDOW"

#define HARRIS_KN_OUT_RESP		"OUTPUT_RESPONSE"
#define HARRIS_KN_OUT_TEMP_BUF	"OUTPUT_TEMP_BUFFER"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(HARRIS_K);
void HARRIS_K(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lIn2, kernel_io_desc lOut0, kernel_io_desc lOut1);

#endif

#endif 


