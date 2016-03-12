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

#ifndef APU_BILIN_INTERPOL_KERNEL_H
#define APU_BILIN_INTERPOL_KERNEL_H


#include "stringify_macros.h"

#define BILIN_INTERPOL_IN08u_OUT16s_K	apu_bilinear_interpolation_in08u_out16s
#define BILIN_INTERPOL_IN08u_OUT16s_KN	XSTR(BILIN_INTERPOL_IN08u_OUT16s_K)

#define BILIN_INTERPOL_IN16u_OUT16s_K	apu_bilinear_interpolation_in16u_out16s
#define BILIN_INTERPOL_IN16u_OUT16s_KN	XSTR(BILIN_INTERPOL_IN16u_OUT16s_K)

#define BILIN_INTERPOL_IN16u_OUT16s_Q3_28_K apu_bilinear_interpolation_filter_in16u_out16s_Q3_28
#define BILIN_INTERPOL_IN16u_OUT16s_Q3_28_KN	XSTR(BILIN_INTERPOL_IN16u_OUT16s_Q3_28_K)


#define BILIN_INTERPOL_withOffsets_IN16u_OUT16s_Q3_28_K apu_bilinear_interp_withOffs_filter_in16u_out16s_Q3_28
#define BILIN_INTERPOL_withOffsets_IN16u_OUT16s_Q3_28_KN	XSTR(BILIN_INTERPOL_withOffsets_IN16u_OUT16s_Q3_28_K)

#define BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K apu_bilinear_interp_withOffsPar_filter_in16u_out16s_Q3_28
#define BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_KN	XSTR(BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K)

#define BILIN_INTERPOL_IN	"BilinInterpolKern_InImg"
#define BILIN_INTERPOL_OUT	"BilinInterpolKern_OutImg"

#define BILIN_INTERPOL_TMP_DIV	"BilinInterpolKern_TMPDIV"
#define	BILIN_INTERPOL_XOFFS	"BilinInterpolKern_XOFFS"
#define	BILIN_INTERPOL_YOFFS	"BilinInterpolKern_YOFFS"
#define	BILIN_INTERPOL_XPTS		"BilinInterpolKern_XPTS"
#define	BILIN_INTERPOL_YPTS		"BilinInterpolKern_YPTS"
#define BILIN_INTERPOL_NRPTS	"BilinInterpolKern_NRPTS"

#define BILIN_INTERPOL_ALPHA1	"BilinInterpolKern_ALPHA1"
#define BILIN_INTERPOL_ALPHA2	"BilinInterpolKern_ALPHA2"
#define BILIN_INTERPOL_BETA1	"BilinInterpolKern_BETA1"
#define BILIN_INTERPOL_BETA2	"BilinInterpolKern_BETA2"
#define BILIN_INTERPOL_TMPDONE	"BilinInterpolKern_TmpDone"

#define	BILIN_INTERPOL_QUOTX	"BILIN_INTERPOL_QUOTX"
#define	BILIN_INTERPOL_QUOTY	"BILIN_INTERPOL_QUOTY"


#ifndef OFFS_SELECT_KN_MAX_VECTOR_SIZE
#define OFFS_SELECT_KN_MAX_VECTOR_SIZE		128
#endif


#ifdef APEX2_EMULATE

extKernelInfoDecl(BILIN_INTERPOL_IN08u_OUT16s_K);
void BILIN_INTERPOL_IN08u_OUT16s_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lquotx, kernel_io_desc lyOffs, kernel_io_desc lquoty);

extKernelInfoDecl(BILIN_INTERPOL_IN16u_OUT16s_K);
void BILIN_INTERPOL_IN16u_OUT16s_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lquotx, kernel_io_desc lyOffs, kernel_io_desc lquoty);

extKernelInfoDecl(BILIN_INTERPOL_IN16u_OUT16s_Q3_28_K);
void BILIN_INTERPOL_IN16u_OUT16s_Q3_28_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc lxOffs, kernel_io_desc lyOffs);


extKernelInfoDecl(BILIN_INTERPOL_withOffsets_IN16u_OUT16s_Q3_28_K);
void BILIN_INTERPOL_withOffsets_IN16u_OUT16s_Q3_28_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc ltmpDiv, kernel_io_desc lxPts, kernel_io_desc lyPts, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lnrPts);

extKernelInfoDecl(BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K);
//void BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc ltmpDiv, kernel_io_desc lxPts, kernel_io_desc lyPts, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lnrPts);

void BILIN_INTERPOL_withOffsetsPar_IN16u_OUT16s_Q3_28_K(kernel_io_desc lImgIn, kernel_io_desc lImgOut, kernel_io_desc ltmpDiv, kernel_io_desc lxPts, kernel_io_desc lyPts, kernel_io_desc lxOffs, kernel_io_desc lyOffs, kernel_io_desc lnrPts,
	kernel_io_desc laccum_a1b1L, kernel_io_desc laccum_a1b2L, kernel_io_desc laccum_a2b1L, kernel_io_desc laccum_a2b2L/*, kernel_io_desc ltmpDone*/);

#endif

#endif
