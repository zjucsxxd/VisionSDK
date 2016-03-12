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

#ifndef APU_LUCAS_KANADE_KERNEL_H
#define APU_LUCAS_KANADE_KERNEL_H

#include "stringify_macros.h"

#include "stringify_macros.h"

#define LUCAS_KANADE_MISMATCH_K			apu_lucas_kanade_mismatch
#define LUCAS_KANADE_MISMATCH_KN		XSTR(LUCAS_KANADE_MISMATCH_K)

#define LUCAS_KANADE_ACCUM_K			apu_lucas_kanade_accum
#define LUCAS_KANADE_ACCUM_KN			XSTR(LUCAS_KANADE_ACCUM_K)

#define LUCAS_KANADE_ACCUM_SIMPLE_K		apu_lucas_kanade_accum_simple
#define LUCAS_KANADE_ACCUM_SIMPLE_KN	XSTR(LUCAS_KANADE_ACCUM_SIMPLE_K)


#define LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_K		apu_lucas_kanade_accum_simple_at_offs
#define LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_KN	XSTR(LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_K)


/*
#define LUCAS_KANADE_OFFSET_K			apu_lucas_kanade_offset
#define LUCAS_KANADE_OFFSET_KN			XSTR(LUCAS_KANADE_OFFSET_K)
*/
#define LUCAS_KANADE_OFFSET_XorY_K				apu_lucas_kanade_offset_xOry
#define LUCAS_KANADE_OFFSET_XorY_KN				XSTR(LUCAS_KANADE_OFFSET_XorY_K)

#define LUCAS_KANADE_OFFSET_XorY_unsigned_K		apu_lucas_kanade_offset_xOry_unsigned
#define LUCAS_KANADE_OFFSET_XorY_unsigned_KN	XSTR(LUCAS_KANADE_OFFSET_XorY_unsigned_K)

#define LUCAS_KANADE_KN_IMG_A					"INPUT_IMG_A"
#define LUCAS_KANADE_KN_IMG_B					"INPUT_IMG_B"
#define LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_HIGH	"OUT_OFFS_G_X_VECT_HIGH"
#define LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_HIGH	"OUT_OFFS_G_Y_VECT_HIGH"
#define LUCAS_KANADE_KN_OFFS_G_OUT_X_VECT_LOW	"OUT_OFFS_G_X_VECT_LOW"
#define LUCAS_KANADE_KN_OFFS_G_OUT_Y_VECT_LOW	"OUT_OFFS_G_Y_VECT_LOW"

#define LUCAS_KANADE_KN_OFFS_G_OUT_VECT			"OUT_OFFS_G_VECT"
#define LUCAS_KANADE_KN_OFFS_G_OUT_OFFS_VECT	"OUT_OFFS_G_OFFS_VECT"
#define LUCAS_KANADE_KN_OUT_ETA_NORM			"OUT_OFFS_ETA_NORM"


#define LUCAS_KANADE_KN_OFFS_G_IN_X_VECT	"IN_OFFS_G_X_VECTOR"
#define LUCAS_KANADE_KN_OFFS_G_IN_Y_VECT	"IN_OFFS_G_Y_VECTOR"
#define LUCAS_KANADE_KN_OFFS_ETA_X_VECT		"IN_OFFS_ETA_X_VECTOR"
#define LUCAS_KANADE_KN_OFFS_ETA_Y_VECT		"IN_OFFS_ETA_Y_VECTOR"

#define LUCAS_KANADE_KN_DELTAK_IMG			"IN_DELTA_K_IMG"
#define LUCAS_KANADE_KN_DELTAK_GRADX_IMG	"OUT_DELTAK_GRADX_IM"
#define LUCAS_KANADE_KN_DELTAK_GRADY_IMG	"OUT_DELTAK_GRADY_IM"

/*
// for the process without indirect inputs
#define LUCAS_KANADE_KN_XPTS				"LK_KN_IN_X"
#define LUCAS_KANADE_KN_YPTS				"LK_KN_IN_Y"
#define LUCAS_KANADE_KN_NRPTS				"LK_KN_IN_NRPTS"
*/

#define LUCAS_KANADE_KN_GRAD_X				"IN_GRAD_X"
#define LUCAS_KANADE_KN_GRAD_Y				"IN_GRAD_Y"
#define LUCAS_KANADE_KN_ACC_GRAD_X_SQR		"IN_ACC_GRAD_X_SQR"
#define LUCAS_KANADE_KN_ACC_GRAD_Y_SQR		"IN_ACC_GRAD_Y_SQR"
#define LUCAS_KANADE_KN_ACC_GRAD_XorY_SQR	"IN_ACC_GRAD_XorY_SQR"
#define LUCAS_KANADE_KN_ACC_GRAD_XY			"IN_ACC_GRAD_XY"
#define LUCAS_KANADE_KN_ACC_DETG_INV		"IN_ACC_DET_G_INV"
#define LUCAS_KANADE_KN_VALID_POINTS		"IN_VALID_POINTS"
#define LUCAS_KANADE_KN_OUT_VALID_POINTS	"OUT_VALID_POINTS"

#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_K apu_transformCoordsToPointOffs
#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_KN XSTR(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_K)

#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutOffsets	"Out_Offsets"
#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_OutValidPts	"Out_ValidPts"

#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_XCoords		"In_XCoords"
#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_YCoords		"In_YCoords"
#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_InValidPts	"In_ValidPts"
#define LUCAS_KANADE_OFFSET_TransfCoordsToOffs_StaticData	"InImgWH_TileWH_DataSz"


#ifndef OFFS_SELECT_KN_MAX_VECTOR_SIZE
#define OFFS_SELECT_KN_MAX_VECTOR_SIZE		128
#endif


#ifdef APEX2_EMULATE
#include "acf_lib.hpp"

extKernelInfoDecl(LUCAS_KANADE_MISMATCH_K);
void LUCAS_KANADE_MISMATCH_K(/*kernel_io_desc lImgA, kernel_io_desc lImgB, */
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img, kernel_io_desc lImgDeltaK,
	kernel_io_desc inGradXImg, kernel_io_desc inGradYImg);

extKernelInfoDecl(LUCAS_KANADE_ACCUM_SIMPLE_K);
void LUCAS_KANADE_ACCUM_SIMPLE_K(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img);

/*
extKernelInfoDecl(LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_K);
void LUCAS_KANADE_ACCUM_SIMPLE_AT_OFFS_K(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img, kernel_io_desc lXpts, kernel_io_desc lYpts, kernel_io_desc lNrpts);
*/


extKernelInfoDecl(LUCAS_KANADE_ACCUM_K);
void LUCAS_KANADE_ACCUM_K(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img,
		kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg
	);

/*
extKernelInfoDecl(LUCAS_KANADE_OFFSET_K);
void LUCAS_KANADE_OFFSET_K(	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg);
*/

extKernelInfoDecl(LUCAS_KANADE_ACCUM_SIMPLE_K);
void LUCAS_KANADE_ACCUM_SIMPLE_K(kernel_io_desc lOutOffsetEtaXVect, kernel_io_desc lOutOffsetEtaYVect,
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img);

extKernelInfoDecl(LUCAS_KANADE_MISMATCH_K);
void LUCAS_KANADE_MISMATCH_K(/*kernel_io_desc lImgA, kernel_io_desc lImgB, */
	kernel_io_desc outDeltaK_GradX_Img, kernel_io_desc outDeltaK_GradY_Img, kernel_io_desc lImgDeltaK,
	kernel_io_desc inGradXImg, kernel_io_desc inGradYImg);


extKernelInfoDecl(LUCAS_KANADE_OFFSET_XorY_K);
void LUCAS_KANADE_OFFSET_XorY_K(kernel_io_desc lOutGVect, kernel_io_desc lOutGOffsetVect,
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc inGradXorYSqrImg, kernel_io_desc inGradXGradYImg,
	kernel_io_desc inDetGImg_low, kernel_io_desc linValidPts, kernel_io_desc loutValidPts,
	kernel_io_desc lEtaNormOut);

extKernelInfoDecl(LUCAS_KANADE_OFFSET_XorY_unsigned_K);
void LUCAS_KANADE_OFFSET_XorY_unsigned_K(kernel_io_desc lOutGVect, kernel_io_desc lOutGOffsetVect,
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc inGradXorYSqrImg, kernel_io_desc inGradXGradYImg,
	kernel_io_desc inDetGImg_low, kernel_io_desc linValidPts, kernel_io_desc loutValidPts,
	kernel_io_desc lEtaNormOut);


extKernelInfoDecl(LUCAS_KANADE_OFFSET_TransfCoordsToOffs_K);
void LUCAS_KANADE_OFFSET_TransfCoordsToOffs_K(kernel_io_desc l_PointOffsets, kernel_io_desc l_newValidPts,
	kernel_io_desc l_xCoords, kernel_io_desc l_yCoords, kernel_io_desc l_validPoints,
	kernel_io_desc l_imgWidthHeight_tileWidthHeight_DataSz);

#endif //APEX2_EMULATE

#endif //#ifndef APU_LUCAS_KANADE_KERNEL_H

