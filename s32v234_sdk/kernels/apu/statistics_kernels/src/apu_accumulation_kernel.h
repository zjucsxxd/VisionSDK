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
#ifndef APU_ACCUM_KN_H
#define APU_ACCUM_KN_H

#include "stringify_macros.h"
//#define ACCUM_KID accumulation
#define ACCUM_K		apu_accumulation
#define ACCUM_KN	XSTR(ACCUM_K)

#define ACCUM_WEIGHTED_K	apu_accumulation_weighted
#define ACCUM_WEIGHTED_KN	XSTR(ACCUM_WEIGHTED_K)

#define ACCUM_UWEIGHTED_K	apu_u_accumulation_weighted
#define ACCUM_UWEIGHTED_KN	XSTR(ACCUM_UWEIGHTED_K)

#define ACCUM_IN "INPUT_Img"
#define ACCUM_OUT "Output_Img"
#define	ACCUM_XOFFS "ACCUM_XOFFS"
#define	ACCUM_YOFFS "ACCUM_YOFFS"
#define	ACCUM_XWIDTH "ACCUM_XWIDTH"
#define	ACCUM_YHEIGHT "ACCUM_YHEIGHT"

#ifdef APEX2_EMULATE
extKernelInfoDecl(ACCUM_K);
void ACCUM_K(kernel_io_desc lImgInA, kernel_io_desc lValOut, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lxWidth, kernel_io_desc lyHeight);

extKernelInfoDecl(ACCUM_WEIGHTED_K);
void ACCUM_WEIGHTED_K(kernel_io_desc lImgInA, kernel_io_desc lValOut, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lxWidth, kernel_io_desc lyHeight);

extKernelInfoDecl(ACCUM_UWEIGHTED_K);
void ACCUM_UWEIGHTED_K(kernel_io_desc lImgInA, kernel_io_desc lValOut, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lxWidth, kernel_io_desc lyHeight);

#endif

#endif