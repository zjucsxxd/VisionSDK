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

#ifndef APU_NMS_H
#define  APU_NMS_H

#include "stringify_macros.h"

#define	NMS_K		apu_nms
#define NMS_KN		XSTR(NMS_K)

#define	NMS16_K		apu_nms16
#define NMS16_KN	XSTR(NMS16_K)

#define NMS_KN_IN		"INPUT_0"
#define NMS_KN_OUT		"OUTPUT_0"



#define NMS16_KN_IN		"INPUT_0"
#define NMS16_KN_OUT	"OUTPUT_0"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(NMS_K);
void NMS_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(NMS16_K);
void NMS16_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

#endif

#endif 



