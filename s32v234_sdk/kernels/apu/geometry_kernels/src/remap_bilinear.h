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

#ifndef APU_REMAP_BILIN_H
#define  APU_REMAP_BILIN_H

#include "stringify_macros.h"

#define	REMAP_BILIN_RGB_K		remap_bilinear_rgb
#define REMAP_BILIN_RGB_KN		XSTR(REMAP_BILIN_RGB_K)

#define	REMAP_BILIN_GRAY_K		remap_bilinear_grayscale
#define REMAP_BILIN_GRAY_KN		XSTR(REMAP_BILIN_GRAY_K)


#define REMAP_BILIN_KN_SRC		"SRC"
#define REMAP_BILIN_KN_DST		"DST"
#define REMAP_BILIN_KN_OFFS 	"OFFSET"
#define REMAP_BILIN_KN_DELTA 	"DELTA"

#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(REMAP_BILIN_GRAY_K);
void REMAP_BILIN_GRAY_K(kernel_io_desc dst_param,
                    kernel_io_desc src_param,
                    kernel_io_desc offset_param, 
                    kernel_io_desc delta_param);

extKernelInfoDecl(REMAP_BILIN_RGB_K);
void REMAP_BILIN_RGB_K(kernel_io_desc dst_param,
	kernel_io_desc src_param,
	kernel_io_desc offset_param,
	kernel_io_desc delta_param);

#endif

#endif 



