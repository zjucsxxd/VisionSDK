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
*  \file apexcv_color_conversion_test.cpp
*  \brief Run and validate color conversion kernels
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

#include <apexcv_base_color_conversion.h>
#include <apexcv_color_conversion_ref.h>
#include <apexcv_color_conversion_test_image.h>

using namespace apexcv;

namespace apexcv{
	
int test_rgb888_to_rgb565(const unsigned int *src, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ColorConverter rgb;
   
   DataDescriptor srcImg;
		srcImg.InitManual(w, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_32U);
   DataDescriptor dstImg(w, h, DATATYPE_16U);
   DataDescriptor dstRefImg(w, h, DATATYPE_16U);
      
   if(srcImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= rgb.convert(srcImg, dstImg, apexcv::ColorConverter::RGB888_TO_RGB565);
  
      //obtain dst data pointers
      unsigned short* pDst    = (unsigned short*) dstImg.GetDataPtr();
      unsigned short* pDstRef = (unsigned short*) dstRefImg.GetDataPtr();
      
      //run reference
      rgb888_to_rgb565_ref(pDstRef, w, src, w, w, h);

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

int test_rgb565_to_rgb888(const unsigned short *src, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ColorConverter rgb;
   
   DataDescriptor srcImg;
		srcImg.InitManual(w, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_16U);
   DataDescriptor dstImg(w, h, DATATYPE_32U);
   DataDescriptor dstRefImg(w, h, DATATYPE_32U);
      
   if(srcImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= rgb.convert(srcImg, dstImg, apexcv::ColorConverter::RGB565_TO_RGB888);
  
      //obtain dst data pointers
      unsigned int* pDst    = (unsigned int*) dstImg.GetDataPtr();
      unsigned int* pDstRef = (unsigned int*) dstRefImg.GetDataPtr();
      
      //run reference
      rgb565_to_rgb888_ref(pDstRef, w, src, w, w, h);

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

int test_rgb888_to_y(const unsigned char *src, int w, int h, int R2Y, int G2Y, int B2Y) 
{
   int lRetVal = 0;
   apexcv::ColorConverter rgb;
   
   DataDescriptor srcImg;
		srcImg.InitManual(w/*/4*/, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U, 4, 1);
   DataDescriptor dstImg(w/*/4*/, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w/*/4*/, h, DATATYPE_08U);
      
   if(srcImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
	  //run implementation
      lRetVal |= rgb.convert(srcImg, dstImg, ColorConverter::RGB888_TO_Y, R2Y, G2Y, B2Y);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      rgb888_to_y_ref((uint8_t*)pDstRef, w, (uint8_t*)src, w*4, w*4, h, R2Y, G2Y, B2Y);

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

int test_rgb888_to_yuv(const unsigned char *src, int w, int h) 
{
   int lRetVal = 0;
   apexcv::ColorConverter rgb;
   
   DataDescriptor srcImg;
		srcImg.InitManual(w/*/4*/, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U, 4, 1);
   DataDescriptor dstImg(w/*/4*/, h, DATATYPE_08U, 4, 1);
   DataDescriptor dstRefImg(w/*/4*/, h, DATATYPE_08U, 4, 1);
      
   if(srcImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= rgb.convert(srcImg, dstImg, ColorConverter::RGB888_TO_YUV);
  
      //obtain dst data pointers
      unsigned char* pDst    = (unsigned char*) dstImg.GetDataPtr();
      unsigned char* pDstRef = (unsigned char*) dstRefImg.GetDataPtr();
      
      //run reference
      rgb888_to_yuv_ref((uint8_t*)pDstRef, w*4, (uint8_t*)src, w*4, w, h);

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

int test_ht_8UC3_to_y(const uint8_t *src, int w, int h, uint8_t KA, uint8_t KB, uint8_t KC, uint16_t KR)
{
   int lRetVal = 0;
   apexcv::OPT::ColorConverter rgb;

   DataDescriptor srcImg;
		srcImg.InitManual(w/*/4*/, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U, 4, 1);
   DataDescriptor dstImg(w/*/4*/, h, DATATYPE_16S);
   DataDescriptor dstRefImg(w/*/4*/, h, DATATYPE_16S);


   if(srcImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= rgb.convert(srcImg, dstImg, OPT::ColorConverter::HT_8UC3_TO_Y, KA, KB, KC, KR);

      //obtain dst data pointers
      int16_t* pDst    = (int16_t*) dstImg.GetDataPtr();
      int16_t* pDstRef = (int16_t*) dstRefImg.GetDataPtr();

      //run reference
      csc_8UC3_to_y_ref((int16_t*)pDstRef, w, (uint8_t*)src, w*4, w, h, KA, KB, KC, KR);

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

void test_apexcv_color_conversion()
{
   int e = 0;
 
   unsigned int   *test_image888_oal      = (unsigned int *)OAL_MemoryAllocFlag(8192*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   unsigned short *test_image565_oal      = (unsigned short *)OAL_MemoryAllocFlag(8192*2, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   unsigned char  *test_image08u_oal      = (unsigned char *)OAL_MemoryAllocFlag(8192, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   
   memcpy(test_image888_oal, test_image888, 8192*4);
   memcpy(test_image565_oal, test_image565, 8192*2);
   memcpy(test_image08u_oal, test_image08u, 8192);


   //Color conversion test
   printf("Test ApexCV color conversion start\n");
   
   //rgb888 to rgb565 test
   {
	  printf("  Test ApexCV RGB888 to RGB565 start\n");
      
      e = test_rgb888_to_rgb565(test_image888_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV RGB888 to RGB565 end\n");
   }
   
   //rgb565 to rgb888 test
   {
	  printf("  Test ApexCV RGB565 to RGB888 start\n");
      
      e = test_rgb565_to_rgb888(test_image565_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV RGB565 to RGB888 end\n");
   }
	 
	 //rgb888 to y test
   {
	  printf("  Test ApexCV RGB888 to Y start\n");
	  
      e = test_rgb888_to_y((uint8_t*)test_image888_oal, SRC_WIDTH, SRC_HEIGHT, 16, 32, 64);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV RGB888 to Y end\n");
   }
	 
	 //rgb888 to yuv test
   {
	  printf("  Test ApexCV RGB888 to YUV start\n");
	  
      e = test_rgb888_to_yuv((uint8_t*)test_image888_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("    Done                                         FAIL\n");
      else     printf("    Done                                         PASS\n");
   
      printf("  Test ApexCV RGB888 to YUV end\n");
   }
   
   //ht 8UC3 to y test
   { // ERRATA: not working under emulation due to different memory model
	  printf("  Test ApexCV HT 8UC3 to Y start\n");
      e = test_ht_8UC3_to_y((uint8_t*)test_image888_oal, SRC_WIDTH, SRC_HEIGHT, 16, 32, 64, 128);
	  if (e){
		  printf("    Done                                         FAIL\n");
#ifdef APEX2_EMULATE
		  printf("    REMARK: not working under emulation due to different memory model\n");
#endif
	  } else     printf("    Done                                         PASS\n");
	  printf("  Test ApexCV HT 8UC3 to Y end\n");
   }
   
   //Color conversion done
   printf("Test ApexCV color conversion end\n");
   
   OAL_MemoryFree(test_image888_oal);
   OAL_MemoryFree(test_image565_oal);
   OAL_MemoryFree(test_image08u_oal);
   
}

} // namespace apexcv


