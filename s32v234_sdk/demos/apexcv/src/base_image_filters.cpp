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
 ******************************************************************************/
/*!*********************************************************************************
*  \file apexcv_filter_test.cpp
*  \brief Run and validate filter kernels
***********************************************************************************/

#include <stdio.h>
#include <cstring>


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include <oal.h>

#include <apexcv_base_image_filters.h>
#include <apexcv_filter_ref.h>
#include <apexcv_filter_test_image.h>

using namespace apexcv;

namespace apexcv{
	
int test_dilate(const unsigned char *src, const unsigned char *srcPad, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.dilateFilter(srcImg, dstImg);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      dilate_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_dilate_16s(const short *src, const short *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_16S);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);

   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.dilateFilter(srcImg, dstImg);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      dilate_3x3_16s_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }

   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_erode(const unsigned char *src, const unsigned char *srcPad, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
	  //run implementation
      lRetVal |= f.erodeFilter(srcImg, dstImg);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      erode_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_bilateral_5x5(const unsigned char *src, const unsigned char *srcPad, int w, int h, int sigmaR, int sigmaD) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      bilateral_5x5_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h, sigmaR, sigmaD);
  
	  //run implementation
      lRetVal |= f.bilateralFilter(srcImg, dstImg, sigmaR, sigmaD);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}


int test_box_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.boxFilter(srcImg, dstImg);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      box_3x3_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_box_3x3_16s(const short *src, const short *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_16S);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.boxFilter(srcImg, dstImg, 3);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      box_3x3_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_box_5x5_16s(const short *src, const short *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_16S);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.boxFilter(srcImg, dstImg, 5);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      box_5x5_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_box_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.boxFilter(srcImg, dstImg, 3);

      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();

      //run reference
      // The ht veresion does not round up
      box_3x3_nr_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_centraldx(const unsigned char *src, const unsigned char *srcPad, int w, int h, int k0, int k1, int k2)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run reference
      short* pDstRef = (short*) dstRefImg.GetDataPtr();
      derivative_x_3x3_16s_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h, k0, k1, k2);

      //run implementation for sobel x
      lRetVal |= f.derivativeFilter(srcImg, dstImg, apexcv::OPT::ImageFilter::DERIVATIVE_X, k0, k1, k2);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_centraldy(const unsigned char *src, const unsigned char *srcPad, int w, int h, int k0, int k1, int k2)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation for sobel x
      lRetVal |= f.derivativeFilter(srcImg, dstImg, apexcv::OPT::ImageFilter::DERIVATIVE_Y, k0, k1, k2);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      derivative_y_3x3_16s_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h, k0, k1, k2);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_convolve_08u(const unsigned char *src, const unsigned char *srcPad, int w, int h, const signed char* fCoeff, int windowSize, int fScale)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.convolveFilter(srcImg, dstImg, fCoeff, windowSize, fScale);

      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();

      //run reference
      if(fScale > 0)
      {
         convolve_scale_08u_nr_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize, fScale);
      } else {
         convolve_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize);
      }

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_saturate_08s(const short *src, int w, int h)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_16S);
   DataDescriptor dstImg(w, h, DATATYPE_08S);
   DataDescriptor dstRefImg(w, h, DATATYPE_08S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.saturateFilter(srcImg, dstImg);

      //obtain dst data pointers
      int8_t* pDst    = (int8_t*) dstImg.GetDataPtr();
      int8_t* pDstRef = (int8_t*) dstRefImg.GetDataPtr();

      //run reference
      saturate_08s_ref(pDstRef, w, src, w, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_separable_16s(const unsigned char *src, const unsigned char *srcPad, int w, int h, signed char* fCoeffRow, signed char* fCoeffCol, int windowSize)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      if (windowSize == 3)
         separable_3x3_16s_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, fCoeffRow, fCoeffCol);
      else
         separable_5x5_16s_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, fCoeffRow, fCoeffCol);

	  lRetVal |= f.separableFilter(srcImg, dstImg, fCoeffRow, fCoeffCol, windowSize);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_sobel_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.sobelFilter(srcImg, dstImg, 3, apexcv::OPT::ImageFilter::SOBEL_BOTH);

      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();

      //run reference
      sobel_3x3_16s_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_sobel_x_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08S);
   DataDescriptor dstRefImg(w, h, DATATYPE_08S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.sobelFilter(srcImg, dstImg, 3, apexcv::OPT::ImageFilter::SOBEL_X);

      //obtain dst data pointers
      int8_t* pDst    = (int8_t*) dstImg.GetDataPtr();
      int8_t* pDstRef = (int8_t*) dstRefImg.GetDataPtr();

      //run reference
      sobel_x_3x3_08s_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_ht_sobel_y_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::OPT::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08S);
   DataDescriptor dstRefImg(w, h, DATATYPE_08S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.sobelFilter(srcImg, dstImg, 3, apexcv::OPT::ImageFilter::SOBEL_Y);

      //obtain dst data pointers
      int8_t* pDst    = (int8_t*) dstImg.GetDataPtr();
      int8_t* pDstRef = (int8_t*) dstRefImg.GetDataPtr();

      //run reference
      sobel_y_3x3_08s_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_median(const unsigned char *src, const unsigned char *srcPad, int w, int h, int windowSize) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.medianFilter(srcImg, dstImg, windowSize);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
			switch(windowSize)
			{
				case 3:
					median_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
					break;
					
				case 5:
					median_5x5_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
					break;
				
				default:
					lRetVal |= 1;
					break;
			}

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_gaussian_3x3(const unsigned char *src, const unsigned char *srcPad, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.gaussianFilter(srcImg, dstImg);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      gaussian_3x3_08u_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_gaussian_5x5(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.gaussianFilter(srcImg, dstImg, 5);

      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();

      //run reference
      gaussian_5x5_08u_ref(pDstRef, w, srcPad+2*(w+4)+2, w+4, w, h);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);

   return lRetVal;
}

int test_sobel(const unsigned char *src, const unsigned char *srcPad, int w, int h, int windowSize, apexcv::ImageFilter::SobelType st) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.sobelFilter(srcImg, dstImg, windowSize, st);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
			if(st == apexcv::ImageFilter::SOBEL_X) {
				switch(windowSize)
				{
					case 3:
						sobel_x_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
						
					case 5:
						sobel_x_5x5_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
					
					default:
						lRetVal |= 1;
						break;
				}
			} else if(st == apexcv::ImageFilter::SOBEL_Y) {
				switch(windowSize)
				{
					case 3:
						sobel_y_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
						
					case 5:
						sobel_y_5x5_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
					
					default:
						lRetVal |= 1;
						break;
				}
			} else {
				switch(windowSize)
				{
					case 3:
						sobel_3x3_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
						
					case 5:
						sobel_5x5_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
						break;
					
					default:
						lRetVal |= 1;
						break;
				}
			}

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_sobel_xy_08u(const unsigned char *src, const unsigned char *srcPad, int w, int h)
{
   int lRetVal = 0;
   apexcv::ImageFilter f;

   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstXImg(w, h, DATATYPE_08U);
   DataDescriptor dstYImg(w, h, DATATYPE_08U);
   DataDescriptor dstXRefImg(w, h, DATATYPE_08U);
   DataDescriptor dstYRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() && dstXImg.IsOK() && dstYImg.IsOK() && dstXRefImg.IsOK() && dstYRefImg.IsOK()) {
	   
      //run implementation
      lRetVal |= f.sobelFilter(srcImg, dstXImg, dstYImg);

      //obtain dst data pointers
      unsigned char* pDstX    = (unsigned char*) dstXImg.GetDataPtr();
      unsigned char* pDstY    = (unsigned char*) dstYImg.GetDataPtr();
      unsigned char* pDstXRef = (unsigned char*) dstXRefImg.GetDataPtr();
      unsigned char* pDstYRef = (unsigned char*) dstYRefImg.GetDataPtr();
      
      //run reference implementation
      sobel_x_3x3_08u_ref(pDstXRef, w, srcPad+(w+4)*2+2, w+4, w, h);
      sobel_y_3x3_08u_ref(pDstYRef, w, srcPad+(w+4)*2+2, w+4, w, h);
      
      //run reference implementation
      if (dstXImg == dstXRefImg && dstYImg == dstYRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstXImg.SetFreeOnExit(true);
   dstYImg.SetFreeOnExit(true);
   dstXRefImg.SetFreeOnExit(true);
   dstYRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_convolve_08u(const unsigned char *src, const unsigned char *srcPad, int w, int h, const signed char* fCoeff, int windowSize, int fScale) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.convolveFilter(srcImg, dstImg, (signed char* )fCoeff, windowSize, fScale);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
			if(fScale > 0)
			{
				convolve_scale_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize, fScale);
			} else {
				convolve_08u_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize);
			}
			
      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_convolve_16s(const unsigned char *src, const unsigned char *srcPad, int w, int h, const signed char* fCoeff, int windowSize, int fScale) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.convolveFilter(srcImg, dstImg, (signed char* )fCoeff, windowSize, fScale);
  
      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();
      
      //run reference
			if(fScale > 0)
			{
				convolve_scale_16s_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize, fScale);
			} else {
				convolve_16s_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h, (const int8_t *)fCoeff, windowSize, windowSize);
			}
			
      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}

int test_prewitt(const unsigned char *src, const unsigned char *srcPad, int w, int h, apexcv::ImageFilter::PrewittType pt) 
{
   int lRetVal = 0;
   apexcv::ImageFilter f;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w, h, DATATYPE_16S);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= f.prewittFilter(srcImg, dstImg, pt);
  
      //obtain dst data pointers
      short* pDst    = (short*) dstImg.GetDataPtr();
      short* pDstRef = (short*) dstRefImg.GetDataPtr();
      
      //run reference
      if(pt == apexcv::ImageFilter::PREWITT_Y) {
         prewitt_y_3x3_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
      } else {
         prewitt_x_3x3_ref(pDstRef, w, srcPad+(w+4)*2+2, w+4, w, h);
      }

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;
   } else {
      lRetVal |= 1;
   }
   
   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;
}


void test_apexcv_filter()
{
   int e = 0;

   //filter test
   printf("Test ApexCV image filters start\n");

   unsigned char * test_image08u_pad_oal = (unsigned char * )OAL_MemoryAllocFlag(9360, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   unsigned char * test_image08u_oal     = (unsigned char * )OAL_MemoryAllocFlag(8192, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   short *test_image16s_pad_oal          = (short *)OAL_MemoryAllocFlag(9360*2, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   short *test_image16s_oal              = (short *)OAL_MemoryAllocFlag(8192*2, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_3x3_oal      = (signed char *)OAL_MemoryAllocFlag(9, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_5x5_oal      = (signed char *)OAL_MemoryAllocFlag(25, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_3x1_oal      = (signed char *)OAL_MemoryAllocFlag(3, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_1x3_oal      = (signed char *)OAL_MemoryAllocFlag(3, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_5x1_oal      = (signed char *)OAL_MemoryAllocFlag(5, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   signed char *test_filter_1x5_oal      = (signed char *)OAL_MemoryAllocFlag(5, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   
   memcpy(test_image08u_pad_oal, test_image08u_pad, 9360);
   memcpy(test_image08u_oal, test_image08u, 8192);
   memcpy(test_image16s_pad_oal, test_image16s_pad, 9360*2);
   memcpy(test_image16s_oal, test_image16s, 8192*2);
   memcpy(test_filter_3x3_oal, test_filter_3x3, 9);
   memcpy(test_filter_5x5_oal, test_filter_5x5, 25);
   memcpy(test_filter_3x1_oal, test_filter_3x1, 3);
   memcpy(test_filter_1x3_oal, test_filter_1x3, 3);
   memcpy(test_filter_5x1_oal, test_filter_5x1, 5);
   memcpy(test_filter_1x5_oal, test_filter_1x5, 5);


   /*unsigned char * test_image08u_pad_oal = (unsigned char * )test_image08u_pad;
   unsigned char * test_image08u_oal     = (unsigned char * )test_image08u;
   short *test_image16s_pad_oal          = (short *)test_image16s_pad;
   short *test_image16s_oal              = (short *)test_image16s;
   signed char *test_filter_3x3_oal      = (signed char *)test_filter_3x3;
   signed char *test_filter_5x5_oal      = (signed char *)test_filter_5x5;
   signed char *test_filter_3x1_oal      = (signed char *)test_filter_3x1;
   signed char *test_filter_1x3_oal      = (signed char *)test_filter_1x3;
   signed char *test_filter_5x1_oal      = (signed char *)test_filter_5x1;
   signed char *test_filter_1x5_oal      = (signed char *)test_filter_1x5;*/
   
   //bilateral 5x5 test
   {
	   printf("  Test ApexCV bilateral 5x5 start\n");

	   e = test_bilateral_5x5(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 50, 2);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

	   printf("  Test ApexCV bilateral 5x5 end\n");
   }

   //dilate 3x3 test
   {
      printf("  Test ApexCV dilate 3x3 start\n");

      e = test_dilate(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    08u Done                                     FAIL\n");
	  else     printf("    08u Done                                     PASS\n");

      printf("  Test ApexCV dilate 3x3 end\n");
   }

   //dilate 3x3 16s test
   {
      printf("  Test ApexCV dilate 3x3 16s start\n");

      e = test_dilate_16s(test_image16s_oal, test_image16s_pad_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    08u Done                                     FAIL\n");
	  else     printf("    08u Done                                     PASS\n");

      printf("  Test ApexCV dilate 3x3 16s end\n");
   }

   //erode 3x3 test
   {
      printf("  Test ApexCV erode 3x3 start\n");

      e = test_erode(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    08u Done                                     FAIL\n");
	  else     printf("    08u Done                                     PASS\n");

      printf("  Test ApexCV erode 3x3 end\n");
   }
   


   //box 3x3 test
   {
	  printf("  Test ApexCV box 3x3 start\n");

      e = test_box_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV box 3x3 end\n");
   }


   //box 3x3 16s test
   {
	  printf("  Test ApexCV box 3x3 16s start\n");

      e = test_box_3x3_16s(test_image16s_oal, test_image16s_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV box 3x3 16s end\n");
   }


   //box 5x5 test
   {
	  printf("  Test ApexCV box 5x5 start\n");

      e = test_box_5x5_16s(test_image16s_oal, test_image16s_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV box 5x5 end\n");
   }


   //ht box 3x3 test
   {
	  printf("  Test ApexCV HT box 3x3 start\n");

      e = test_ht_box_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT box 3x3 end\n");
   }


   //ht derivative x 3x3 test
   {
	  printf("  Test ApexCV HT centraldx 3x3 start\n");

      e = test_ht_centraldx(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 1, 2, 1);
	   if (e) {  
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

	   printf("  Test ApexCV HT centraldx 3x3 end\n");
   }


   //ht derivative y 3x3 test
   {
	  printf("  Test ApexCV HT centraldy 3x3 start\n");

      e = test_ht_centraldy(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 1, 2, 1);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT centraldy 3x3 end\n");
   }


   //ht convolve 3x3 08u test
   {
	  printf("  Test ApexCV HT convolve 3x3 08u start\n");

      e = test_ht_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 0);
	   if (e) {  
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT convolve 3x3 08u end\n");
   }


   //ht convolve 5x5 08u test
   {
	  printf("  Test ApexCV HT convolve 5x5 08u start\n");

      e = test_ht_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 0);
	   if (e) {  
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT convolve 5x5 08u end\n");
   }


   //ht convolve scale 3x3 08u test
   {
	  printf("  Test ApexCV HT convolve scale 3x3 08u start\n");

      e = test_ht_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 3);
	   if (e) {
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT convolve scale 3x3 08u end\n");
   }


   //ht convolve scale 5x5 08u test
   {
	  printf("  Test ApexCV HT convolve scale 5x5 08u start\n");

      e = test_ht_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 3);
	   if (e) {  
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT convolve scale 5x5 08u end\n");
   }

   //ht saturate 08s test
   {
	  printf("  Test ApexCV HT saturate 08s start\n");

      e = test_ht_saturate_08s(test_image16s_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT saturate 08s end\n");
   }

   //ht separable 3x3 16s test
   {
	  printf("  Test ApexCV HT separable 3x3 16s start\n");

      e = test_ht_separable_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, (signed char*)test_filter_3x1_oal, (signed char*)test_filter_1x3_oal, 3);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT separable 3x3 16s end\n");
   }


   //ht separable 5x5 16s test
   {
	  printf("  Test ApexCV HT separable 5x5 16s start\n");

      e = test_ht_separable_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, (signed char*)test_filter_5x1_oal, (signed char*)test_filter_1x5_oal, 5);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT separable 5x5 16s end\n");
   }


   //ht sobel 3x3 test
   {
	  printf("  Test ApexCV HT sobel 3x3 start\n");

      e = test_ht_sobel_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e) { 
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT sobel 3x3 end\n");
   }


   //ht sobel x 3x3 test
   {
	  printf("  Test ApexCV HT sobel x 3x3 start\n");

      e = test_ht_sobel_x_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e){
		   printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		   printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	   } else
		   printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT sobel x 3x3 end\n");
   }


   //ht sobel y 3x3 test
   {
	  printf("  Test ApexCV HT sobel y 3x3 start\n");

      e = test_ht_sobel_y_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

      printf("  Test ApexCV HT sobel y 3x3 end\n");
   }
   
   //median 3x3 test
   {
	   printf("  Test ApexCV median 3x3 start\n");

	   e = test_median(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 3);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV median 3x3 end\n");
   }


   //median 5x5 test
   {
	   printf("  Test ApexCV median 5x5 start\n");

	   e = test_median(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 5);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV median 5x5 end\n");
   }
   
   //gaussian 3x3 test
   {
	   printf("  Test ApexCV gaussian 3x3 start\n");

	   e = test_gaussian_3x3(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

	   printf("  Test ApexCV gaussian 3x3 end\n");
   }
   
   //gaussian 5x5 test
   {
	   printf("  Test ApexCV gaussian 5x5 start\n");

	   e = test_gaussian_5x5(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    Done                                         FAIL\n");
	   else     printf("    Done                                         PASS\n");

	   printf("  Test ApexCV gaussian 5x5 end\n");
   }

   //sobel x 3x3 test
   {
	   printf("  Test ApexCV sobel x 3x3 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 3, apexcv::ImageFilter::SOBEL_X);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel x 3x3 end\n");
   }

   //sobel y 3x3 test
   {
	   printf("  Test ApexCV sobel y 3x3 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 3, apexcv::ImageFilter::SOBEL_Y);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel y 3x3 end\n");
   }

   //sobel xy 3x3 test
   {
      printf("  Test ApexCV sobel xy 3x3 start\n");
	  
      e = test_sobel_xy_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    08u Done                                     FAIL\n");
	  else     printf("    08u Done                                     PASS\n");

      printf("  Test ApexCV sobel xy 3x3 end\n");
   }
   
   //sobel 3x3 test
   {
	   printf("  Test ApexCV sobel 3x3 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 3, apexcv::ImageFilter::SOBEL_BOTH);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel 3x3 end\n");
   }

   //sobel x 5x5 test
   {
	   printf("  Test ApexCV sobel x 5x5 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 5, apexcv::ImageFilter::SOBEL_X);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel x 5x5 end\n");
   }

   //sobel y 5x5 test
   {
	   printf("  Test ApexCV sobel y 5x5 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 5, apexcv::ImageFilter::SOBEL_Y);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel y 5x5 end\n");
   }

   //sobel 5x5 test
   {
	   printf("  Test ApexCV sobel 5x5 start\n");

	   e = test_sobel(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, 5, apexcv::ImageFilter::SOBEL_BOTH);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV sobel 5x5 end\n");
   }
   
   //convolve 3x3 test
   {
	   printf("  Test ApexCV convolve 3x3 start\n");

	   e = test_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 0);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");


	   e = test_convolve_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 0);
	   if (e)   printf("    16s Done                                     FAIL\n");
	   else     printf("    16s Done                                     PASS\n");

	   printf("  Test ApexCV convolve 3x3 end\n");
   }
 
   //convolve scale 3x3 test
   {
	  printf("  Test ApexCV convolve with scale 3x3 start\n");

      e = test_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 3);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");

      e = test_convolve_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_3x3_oal, 3, 3);
      if (e)   printf("    16s Done                                     FAIL\n");
      else     printf("    16s Done                                     PASS\n");
			
      printf("  Test ApexCV convolve with scale 3x3 end\n");
   }
	 
   //convolve 5x5 test
   {
      printf("  Test ApexCV convolve 5x5 start\n");
   
      e = test_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 0);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");
      
      e = test_convolve_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 0);
      if (e)   printf("    16s Done                                     FAIL\n");
      else     printf("    16s Done                                     PASS\n");
			
      printf("  Test ApexCV convolve 5x5 end\n");
   }
	 
	//convolve scale 5x5 test
   {
      printf("  Test ApexCV convolve with scale 5x5 start\n");
      
      e = test_convolve_08u(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 3);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");
      
      e = test_convolve_16s(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, test_filter_5x5_oal, 5, 3);
      if (e)   printf("    16s Done                                     FAIL\n");
      else     printf("    16s Done                                     PASS\n");
			
      printf("  Test ApexCV convolve with scale 5x5 end\n");
   }

   //prewitt x 3x3 test
   {
	  printf("  Test ApexCV prewitt x 3x3 start\n");
      
	  e = test_prewitt(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, apexcv::ImageFilter::PREWITT_X);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV prewitt x 3x3 end\n");
   }

	//prewitt y 3x3 test
   {
      printf("  Test ApexCV prewitt y 3x3 start\n");
	  
      e = test_prewitt(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, apexcv::ImageFilter::PREWITT_Y);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV prewitt y 3x3 end\n");
   }

   OAL_MemoryFree(test_image08u_pad_oal);
   OAL_MemoryFree(test_image08u_oal);
   OAL_MemoryFree(test_image16s_pad_oal);
   OAL_MemoryFree(test_image16s_oal);
   OAL_MemoryFree(test_filter_3x3_oal);
   OAL_MemoryFree(test_filter_5x5_oal);
   OAL_MemoryFree(test_filter_3x1_oal);
   OAL_MemoryFree(test_filter_1x3_oal);
   OAL_MemoryFree(test_filter_5x1_oal);
   OAL_MemoryFree(test_filter_1x5_oal);
   
   //filter done
   printf("Test ApexCV image filters end\n");
}

} // namespace apexcv
