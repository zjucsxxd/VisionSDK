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
#ifndef APU_GRADIENT_MATRIX_KERNEL_H
#define APU_GRADIENT_MATRIX_KERNEL_H

#include "stringify_macros.h"

#define GRADIENT_MATRIX_K					apu_gradient_matrix
#define GRADIENT_MATRIX_KN					XSTR(GRADIENT_MATRIX_K)

#define ACCUM_GRADIENT_MATRIX_K				apu_accum_gradient_matrix
#define ACCUM_GRADIENT_MATRIX_KN			XSTR(ACCUM_GRADIENT_MATRIX_K)

//#define GRADIENT_MATRIX_COPY_IN_KN			"apu_copy_input"

#define INVERSE_DETERMINANT_K				apu_inverse_determinant
#define INVERSE_DETERMINANT_KN				XSTR( INVERSE_DETERMINANT_K)


#define INVERSE_DETERMINANT_SIMPLE_K		apu_inverse_det_simple
#define INVERSE_DETERMINANT_SIMPLE_KN		XSTR( INVERSE_DETERMINANT_SIMPLE_K)

#define GRADIENT_MATRIX_KN_IMG				"INPUT_IMG"
#define GRADIENT_MATRIX_KN_OUT_IMG			"OUTPUT_IMG"

#define GRADIENT_MATRIX_KN_GRAD_X			"GRAD_X"
#define GRADIENT_MATRIX_KN_GRAD_Y			"GRAD_Y"
#define GRADIENT_MATRIX_KN_GRAD_X_SQR		"GRAD_X_SQR"
#define GRADIENT_MATRIX_KN_GRAD_Y_SQR		"GRAD_Y_SQR"
#define GRADIENT_MATRIX_KN_GRAD_XY			"GRAD_XY"


#define GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR_H	"OUT_ACC_GRAD_X_SQR_H"
#define GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR_H	"OUT_ACC_GRAD_Y_SQR_H"
#define GRADIENT_MATRIX_KN_ACC_GRAD_XY_H	"OUT_ACC_GRAD_XY_H"
#define GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR_L	"OUT_ACC_GRAD_X_SQR_L"
#define GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR_L	"OUT_ACC_GRAD_Y_SQR_L"
#define GRADIENT_MATRIX_KN_ACC_GRAD_XY_L	"OUT_ACC_GRAD_XY_L"


#define GRADIENT_MATRIX_KN_ACC_GRAD_X_SQR	"OUT_ACC_GRAD_X_SQR"
#define GRADIENT_MATRIX_KN_ACC_GRAD_Y_SQR	"OUT_ACC_GRAD_Y_SQR"
#define GRADIENT_MATRIX_KN_ACC_GRAD_XY		"OUT_ACC_GRAD_XY"

#define GRADIENT_MATRIX_KN_ACC_DET_G_INV	"OUT_ACC_DET_G_INV"
#define GRADIENT_MATRIX_KN_VALIDPTS			"OUT_VALID_PTS"


#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;


extKernelInfoDecl(GRADIENT_MATRIX_K);
void GRADIENT_MATRIX_K(kernel_io_desc gradientX, kernel_io_desc gradientY, kernel_io_desc gradientXSqr, kernel_io_desc gradientYSqr, kernel_io_desc gradXgradY);

extKernelInfoDecl(GRADIENT_MATRIX_K);
void GRADIENT_MATRIX_K(kernel_io_desc gradientX, kernel_io_desc gradientY, kernel_io_desc gradientXSqr, kernel_io_desc gradientYSqr, kernel_io_desc gradXgradY);


extKernelInfoDecl(ACCUM_GRADIENT_MATRIX_K);
void ACCUM_GRADIENT_MATRIX_K(kernel_io_desc gradientXSqr, kernel_io_desc gradientYSqr, kernel_io_desc gradXgradY, kernel_io_desc accGradXSqr, kernel_io_desc accGradYSqr, kernel_io_desc accGradXY, kernel_io_desc validPts, kernel_io_desc accDetG_inv);

extKernelInfoDecl(INVERSE_DETERMINANT_K);
void INVERSE_DETERMINANT_K(kernel_io_desc laccGradXSqrH, kernel_io_desc laccGradXSqrL,
	kernel_io_desc laccGradYSqrH, kernel_io_desc laccGradYSqrL, kernel_io_desc laccGradXYH, kernel_io_desc laccGradXYL,
	kernel_io_desc loutAccGradXSqr, kernel_io_desc loutAccGradYSqr, kernel_io_desc loutAccGradXY,
	kernel_io_desc laccDetG_inv, kernel_io_desc lvalidPts);

extKernelInfoDecl(INVERSE_DETERMINANT_SIMPLE_K);
void INVERSE_DETERMINANT_SIMPLE_K(kernel_io_desc laccGradXSqr, kernel_io_desc laccGradYSqr,
	kernel_io_desc laccGradXY, kernel_io_desc laccDetG_inv, kernel_io_desc lvalidPts);

#endif //APEX2_EMULATE

#endif //#ifndef APU_GRADIENT_MATRIX_KN_H

