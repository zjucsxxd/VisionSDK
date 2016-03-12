/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 ******************************************************************************/
#ifndef _APU_APEXCV_BASE_FILTER_H_
#define _APU_APEXCV_BASE_FILTER_H_


#include "stringify_macros.h"


#define BILATERAL_5X5_K			bilateral_5x5
#define BILATERAL_5X5_KN		XSTR(BILATERAL_5X5_K) 

#define BOX_1X3_16S_K			box_1x3_16s
#define BOX_1X3_16S_KN			XSTR(BOX_1X3_16S_K) 
#define BOX_3X1_16S_K			box_3x1_16s
#define BOX_3X1_16S_KN			XSTR(BOX_3X1_16S_K) 
#define BOX_3X3_08U_K			box_3x3_08u
#define BOX_3X3_08U_KN			XSTR(BOX_3X3_08U_K) 
#define BOX_3X3_16S_K			box_3x3_16s
#define BOX_3X3_16S_KN			XSTR(BOX_3X3_16S_K) 
#define BOX_5X5_16S_K           box_5x5_16s
#define BOX_5X5_16S_KN		    XSTR(BOX_5X5_16S_K) 

#define DILATE_3X3_08U_K	    dilate_3x3_08u
#define DILATE_3X3_08U_KN		XSTR(DILATE_3X3_08U_K) 
#define DILATE_3X3_16S_K		dilate_3x3_16s
#define DILATE_3X3_16S_KN		XSTR(DILATE_3X3_16S_K) 

#define ERODE_3X3_08U_K			erode_3x3_08u
#define ERODE_3X3_08U_KN		XSTR(ERODE_3X3_08U_K) 

#define GAUSSIAN_3X3_08U_K		gaussian_3x3_08u
#define GAUSSIAN_3X3_08U_KN		XSTR(GAUSSIAN_3X3_08U_K) 
#define GAUSSIAN_5X5_08U_K		gaussian_5x5_08u
#define GAUSSIAN_5X5_08U_KN		XSTR(GAUSSIAN_5X5_08U_K)

#define MEDIAN_3X3_08U_K		median_3x3_08u
#define MEDIAN_3X3_08U_KN		XSTR(MEDIAN_3X3_08U_K) 
#define MEDIAN_5X5_08U_K		median_5x5_08u
#define MEDIAN_5X5_08U_KN		XSTR(MEDIAN_5X5_08U_K) 

#define HT_SOBEL_3X3_16S_K		ht_sobel_3x3_16s
#define HT_SOBEL_3X3_16S_KN		 XSTR(HT_SOBEL_3X3_16S_K)
#define HT_SOBEL_X_3X3_08S_K	 ht_sobel_x_3x3_08s
#define HT_SOBEL_X_3X3_08S_KN	 XSTR(HT_SOBEL_X_3X3_08S_K)
#define HT_SOBEL_Y_3X3_08S_K	 ht_sobel_y_3x3_08s
#define HT_SOBEL_Y_3X3_08S_KN	 XSTR(HT_SOBEL_Y_3X3_08S_K)
#define HT_SOBEL_X_3X3_16S_K	 ht_sobel_x_3x3_16s
#define HT_SOBEL_X_3X3_16S_KN	 XSTR(HT_SOBEL_X_3X3_16S_K)
#define HT_SOBEL_Y_3X3_16S_K	 ht_sobel_y_3x3_16s
#define HT_SOBEL_Y_3X3_16S_KN	 XSTR(HT_SOBEL_Y_3X3_16S_K)
#define HT_SOBEL_X_5X5_16S_K	 ht_sobel_x_5x5_16s
#define HT_SOBEL_X_5X5_16S_KN	 XSTR(HT_SOBEL_X_5X5_16S_K)
#define HT_SOBEL_Y_5X5_16S_K	 ht_sobel_y_5x5_16s
#define HT_SOBEL_Y_5X5_16S_KN	 XSTR(HT_SOBEL_Y_5X5_16S_K)

#define SOBEL_X_3X3_08U_K    sobel_x_3x3_08u
#define SOBEL_X_3X3_08U_KN   XSTR(SOBEL_X_3X3_08U_K) 
#define SOBEL_X_3X3_08S_K    sobel_x_3x3_08s
#define SOBEL_X_3X3_08S_KN   XSTR(SOBEL_X_3X3_08S_K) 
#define SOBEL_Y_3X3_08U_K    sobel_y_3x3_08u
#define SOBEL_Y_3X3_08U_KN   XSTR(SOBEL_Y_3X3_08U_K) 
#define SOBEL_Y_3X3_08S_K    sobel_y_3x3_08s
#define SOBEL_Y_3X3_08S_KN   XSTR(SOBEL_Y_3X3_08S_K)
#define SOBEL_XY_3X3_08U_K	 sobel_xy_3x3_08u
#define SOBEL_XY_3X3_08U_KN	 XSTR(SOBEL_XY_3X3_08U_K)

#define SOBEL_3X3_08U_K		 sobel_3x3_08u
#define SOBEL_3X3_08U_KN	 XSTR(SOBEL_3X3_08U_K) 
#define SOBEL_X_5X5_08U_K    sobel_x_5x5_08u
#define SOBEL_X_5X5_08U_KN   XSTR(SOBEL_X_5X5_08U_K) 
#define SOBEL_X_5X5_08S_K    sobel_x_5x5_08s
#define SOBEL_X_5X5_08S_KN   XSTR(SOBEL_X_5X5_08S_K)
#define SOBEL_Y_5X5_08U_K    sobel_y_5x5_08u
#define SOBEL_Y_5X5_08U_KN   XSTR(SOBEL_Y_5X5_08U_K)
#define SOBEL_Y_5X5_08S_K    sobel_y_5x5_08s
#define SOBEL_Y_5X5_08S_KN   XSTR(SOBEL_Y_5X5_08S_K) 
#define SOBEL_5X5_08U_K		 sobel_5x5_08u
#define SOBEL_5X5_08U_KN	 XSTR(SOBEL_5X5_08U_K) 

#define HT_BOX_3X3_08U_K		ht_box_3x3_08u
#define HT_BOX_3X3_08U_KN		XSTR(HT_BOX_3X3_08U_K)	
#define HT_GENERIC_3X3_08U_K	ht_generic_3x3_08u
#define HT_GENERIC_3X3_08U_KN	XSTR(HT_GENERIC_3X3_08U_K)
#define HT_GENERIC_5X5_08U_K	ht_generic_5x5_08u
#define HT_GENERIC_5X5_08U_KN	XSTR(HT_GENERIC_5X5_08U_K)

#define HT_CENTRALDX_3X3_16S_K		ht_centraldx_3x3_16s
#define HT_CENTRALDX_3X3_16S_KN		XSTR(HT_CENTRALDX_3X3_16S_K)	
#define HT_CENTRALDY_3X3_16S_K		ht_centraldy_3x3_16s
#define HT_CENTRALDY_3X3_16S_KN		XSTR(HT_CENTRALDY_3X3_16S_K)	

#define CONVOLVE_3X3_08U_K			convolve_3x3_08u
#define CONVOLVE_3X3_08U_KN			XSTR(CONVOLVE_3X3_08U_K) 
#define CONVOLVE_SCALE_3X3_08U_K    convolve_scale_3x3_08u
#define CONVOLVE_SCALE_3X3_08U_KN   XSTR(CONVOLVE_SCALE_3X3_08U_K)
#define CONVOLVE_3X3_16S_K			convolve_3x3_16s
#define CONVOLVE_3X3_16S_KN			XSTR(CONVOLVE_3X3_16S_K)
#define CONVOLVE_SCALE_3X3_16S_K    convolve_scale_3x3_16s
#define CONVOLVE_SCALE_3X3_16S_KN   XSTR(CONVOLVE_SCALE_3X3_16S_K)
#define CONVOLVE_5X5_08U_K			convolve_5x5_08u
#define CONVOLVE_5X5_08U_KN			XSTR(CONVOLVE_5X5_08U_K)
#define CONVOLVE_SCALE_5X5_08U_K    convolve_scale_5x5_08u
#define CONVOLVE_SCALE_5X5_08U_KN   XSTR(CONVOLVE_SCALE_5X5_08U_K)
#define CONVOLVE_5X5_16S_K			convolve_5x5_16s
#define CONVOLVE_5X5_16S_KN			XSTR(CONVOLVE_5X5_16S_K) 
#define CONVOLVE_SCALE_5X5_16S_K    convolve_scale_5x5_16s
#define CONVOLVE_SCALE_5X5_16S_KN   XSTR(CONVOLVE_SCALE_5X5_16S_K)

#define PREWITT_X_3X3_K		prewitt_x_3x3
#define PREWITT_X_3X3_KN	XSTR(PREWITT_X_3X3_K) 
#define PREWITT_Y_3X3_K		prewitt_y_3x3
#define PREWITT_Y_3X3_KN	XSTR(PREWITT_Y_3X3_K) 

#define HT_SATURATE_08S_K	ht_saturate_08s
#define HT_SATURATE_08S_KN	XSTR(HT_SATURATE_08S_K)

#define HT_SEPARABLE_3X3_16S_K	ht_separable_3x3_16s
#define HT_SEPARABLE_3X3_16S_KN XSTR(HT_SEPARABLE_3X3_16S_K)

#define HT_SEPARABLE_5X5_16S_K  ht_separable_5x5_16s
#define HT_SEPARABLE_5X5_16S_KN XSTR(HT_SEPARABLE_5X5_16S_K)

#define INPUT_0		"INPUT_0"
#define INPUT_1		"INPUT_1"
#define OUTPUT_0	"OUTPUT_0"
#define OUTPUT_1	"OUTPUT_1"
#define R_LUT		"R_LUT"
#define D_LUT		"D_LUT"
#define SIGMA_R		"SIGMA_R"
#define SIGMA_D		"SIGMA_D"
#define F_COEFF		"F_COEFF"
#define F_SCALE		"F_SCALE"
#define F_ROW		"F_ROW"
#define F_COL		"F_COL"
#define BUFFER_0	"BUFFER_0"



#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(BILATERAL_5X5_K);
void BILATERAL_5X5_K(kernel_io_desc lIn0, kernel_io_desc lRLut, kernel_io_desc lDLut, kernel_io_desc lSigmaR, kernel_io_desc lSigmaD, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SATURATE_08S_K);
void HT_SATURATE_08S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SEPARABLE_5X5_16S_K);
void HT_SEPARABLE_5X5_16S_K(kernel_io_desc lIn0, kernel_io_desc row, kernel_io_desc col, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SEPARABLE_3X3_16S_K);
void HT_SEPARABLE_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc f_row, kernel_io_desc f_col, kernel_io_desc lOut0);

extKernelInfoDecl(HT_BOX_3X3_08U_K);
void HT_BOX_3X3_08U_K(kernel_io_desc lIn0,  kernel_io_desc lOut0);

extKernelInfoDecl(HT_GENERIC_3X3_08U_K);
void HT_GENERIC_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc fcoef, kernel_io_desc fscale, kernel_io_desc lOut0);

extKernelInfoDecl(HT_GENERIC_5X5_08U_K);
void HT_GENERIC_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc fcoef, kernel_io_desc fscale, kernel_io_desc lOut0);

extKernelInfoDecl(HT_CENTRALDX_3X3_16S_K);
void HT_CENTRALDX_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc k0, kernel_io_desc k1, kernel_io_desc k2, kernel_io_desc lOut0);

extKernelInfoDecl(HT_CENTRALDY_3X3_16S_K);
void HT_CENTRALDY_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc k0, kernel_io_desc k1, kernel_io_desc k2, kernel_io_desc lOut0);

extKernelInfoDecl(BOX_1X3_16S_K);
void BOX_1X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(BOX_3X1_16S_K);
void BOX_3X1_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);


extKernelInfoDecl(BOX_3X3_08U_K);
void BOX_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(BOX_3X3_16S_K);
void BOX_3X3_16S_K(kernel_io_desc lIn          /*!< The padded source image.*/,
                 kernel_io_desc lOut         /*!< The destination image.*/
				 );

extKernelInfoDecl(BOX_5X5_16S_K);
void BOX_5X5_16S_K(kernel_io_desc lIn          /*!< The padded source image.*/,
                 kernel_io_desc lOut         /*!< The destination image.*/
				 );

extKernelInfoDecl(DILATE_3X3_08U_K);
void DILATE_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(DILATE_3X3_16S_K);
void DILATE_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(ERODE_3X3_08U_K);
void ERODE_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(GAUSSIAN_3X3_08U_K);
void GAUSSIAN_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(GAUSSIAN_5X5_08U_K);
void GAUSSIAN_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(MEDIAN_3X3_08U_K);
void MEDIAN_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(MEDIAN_5X5_08U_K);
void MEDIAN_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_3X3_16S_K);
void HT_SOBEL_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_X_3X3_08S_K);
void HT_SOBEL_X_3X3_08S_K(kernel_io_desc lIn0, kernel_io_desc buffer,  kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_Y_3X3_08S_K);
void HT_SOBEL_Y_3X3_08S_K(kernel_io_desc lIn0, kernel_io_desc buffer, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_X_3X3_16S_K);
void HT_SOBEL_X_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_Y_3X3_16S_K);
void HT_SOBEL_Y_3X3_16S_K(kernel_io_desc lIn0,  kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_X_5X5_16S_K);
void HT_SOBEL_X_5X5_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(HT_SOBEL_Y_5X5_16S_K);
void HT_SOBEL_Y_5X5_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);


extKernelInfoDecl(SOBEL_X_3X3_08U_K);
void SOBEL_X_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_Y_3X3_08U_K);
void SOBEL_Y_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_X_3X3_08S_K);
void SOBEL_X_3X3_08S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_Y_3X3_08S_K);
void SOBEL_Y_3X3_08S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_XY_3X3_08U_K);
void SOBEL_XY_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lOut1);

extKernelInfoDecl(SOBEL_3X3_08U_K);
void SOBEL_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_X_5X5_08U_K);
void SOBEL_X_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_X_5X5_08S_K);
void SOBEL_X_5X5_08S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_Y_5X5_08U_K);
void SOBEL_Y_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_Y_5X5_08S_K);
void SOBEL_Y_5X5_08S_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(SOBEL_5X5_08U_K);
void SOBEL_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(CONVOLVE_3X3_08U_K);
void CONVOLVE_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff);

extKernelInfoDecl(CONVOLVE_SCALE_3X3_08U_K);
void CONVOLVE_SCALE_3X3_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff, kernel_io_desc lFilterScale);

extKernelInfoDecl(CONVOLVE_3X3_16S_K);
void CONVOLVE_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff);

extKernelInfoDecl(CONVOLVE_SCALE_3X3_16S_K);
void CONVOLVE_SCALE_3X3_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff, kernel_io_desc lFilterScale);

extKernelInfoDecl(CONVOLVE_5X5_08U_K);
void CONVOLVE_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff);

extKernelInfoDecl(CONVOLVE_SCALE_5X5_08U_K);
void CONVOLVE_SCALE_5X5_08U_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff, kernel_io_desc lFilterScale);

extKernelInfoDecl(CONVOLVE_5X5_16S_K);
void CONVOLVE_5X5_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff);

extKernelInfoDecl(CONVOLVE_SCALE_5X5_16S_K);
void CONVOLVE_SCALE_5X5_16S_K(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lFilterCoeff, kernel_io_desc lFilterScale);

extKernelInfoDecl(PREWITT_X_3X3_K);
void PREWITT_X_3X3_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(PREWITT_Y_3X3_K);
void PREWITT_Y_3X3_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION


#endif
