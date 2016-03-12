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
*  \file apexcv_interpolation_test.cpp
*  \brief Run and validate interpolation kernels
***********************************************************************************/

#include <stdio.h>
#include <string>

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

#include "apexcv_base_interpolation.h"
#include "apexcv_interpolation_ref.h"
#include "apexcv_interpolation_test_image.h"
#include "string.h"

using namespace apexcv;

namespace apexcv{
	
int test_interp_linear_grayscale(uint8_t* src, uint8_t* srcPad, int w, int h, uint8_t* delta) 
{
   int lRetVal = 0;
   apexcv::Interpolation i;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor deltaImg;
   	     deltaImg.InitManual(w, h, delta, (void *)OAL_MemoryReturnAddress((void *)delta, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
				
   if(srcImg.IsOK() && deltaImg.IsOK() && dstImg.IsOK() && dstRefImg.IsOK()) {
      //run implementation
      lRetVal |= i.linearGrayscale(srcImg, dstImg, deltaImg);
  
      //obtain dst data pointers
      uint8_t* pDst    = (uint8_t*) dstImg.GetDataPtr();
      uint8_t* pDstRef = (uint8_t*) dstRefImg.GetDataPtr();
      uint8_t* pDelta  = (uint8_t*) deltaImg.GetDataPtr();
      
      //run reference
      interp_linear_grayscale_ref(pDstRef, w, srcPad+(w+2*SRC_PAD)*SRC_PAD+SRC_PAD, w+2*SRC_PAD, w, h, pDelta);

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

int test_interp_bilinear_grayscale(uint8_t* src, uint8_t* srcPad, int w, int h, uint8_t* delta) 
{
   int lRetVal = 0;
   apexcv::Interpolation i;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor deltaImg;
   	     deltaImg.InitManual(w, h, delta, (void *)OAL_MemoryReturnAddress((void *)delta, ACCESS_PHY), DATATYPE_08U, 2, 1);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   
   if(srcImg.IsOK() != 0 && deltaImg.IsOK() != 0 && dstImg.IsOK() != 0 && dstRefImg.IsOK() != 0) {
      //run implementation
      lRetVal |= i.bilinearGrayscale(srcImg, dstImg, deltaImg);
  
      //obtain dst data pointers
      uint8_t* pDst    = (uint8_t*) dstImg.GetDataPtr();
      uint8_t* pDstRef = (uint8_t*) dstRefImg.GetDataPtr();
      uint8_t* pSrc    = (uint8_t*) srcImg.GetDataPtr();
      uint8_t* pDelta  = (uint8_t*) deltaImg.GetDataPtr();
      
      //run reference
      interp_bilinear_grayscale_ref(pDstRef, w, srcPad+(w+2*SRC_PAD)*SRC_PAD+SRC_PAD, w+2*SRC_PAD, w, h, pDelta);

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

int test_interp_bicubic_grayscale(uint8_t* src, uint8_t* srcPad, int w, int h, uint8_t* x_offset, uint8_t* y_offset)
{
   int lRetVal = 0;
   apexcv::Interpolation i;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_08U);
   DataDescriptor xImg;
         xImg.InitManual(1, 1, x_offset, (void *)OAL_MemoryReturnAddress((void *)x_offset, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor yImg;
         yImg.InitManual(1, 1, y_offset, (void *)OAL_MemoryReturnAddress((void *)y_offset, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstRefImg(w, h, DATATYPE_08U);
   

  if(srcImg.IsOK() != 0 && dstImg.IsOK() != 0 && xImg.IsOK() != 0 && yImg.IsOK() != 0 && dstRefImg.IsOK() != 0) {
      //run implementation
      lRetVal |= i.bicubicGrayscale(srcImg, dstImg, xImg, yImg);
  
      //obtain dst data pointers
      uint8_t* pDst    = (uint8_t*) dstImg.GetDataPtr();
      uint8_t* pDstRef = (uint8_t*) dstRefImg.GetDataPtr();
      uint8_t* pSrc    = (uint8_t*) srcImg.GetDataPtr();
      uint8_t* px_offset  = (uint8_t*) xImg.GetDataPtr();
      uint8_t* py_offset  = (uint8_t*) yImg.GetDataPtr();
      
      //run reference
      interp_bicubic_grayscale_ref(pDstRef, w, srcPad+(w+2*2)*2+2, w+2*2, w, h, px_offset[0], py_offset[0]);

      if (dstImg == dstRefImg)
			 lRetVal |= 0;
		 else
			 lRetVal |= 1;

    // char fn[128];
    // sprintf(fn, "C:/Michael/apex2_cloud/ref_bicubic.raw");
    // FILE* fp = fopen(fn, "wb");
    // fwrite(pDstRef, sizeof(uint8_t)*w*h, 1, fp);
    // fclose(fp);

    // char afn[128];
    // sprintf(afn, "C:/Michael/apex2_cloud/kernel_bicubic.raw");
    // FILE* afp = fopen(afn, "wb");
    // fwrite(pDst, sizeof(uint8_t)*w*h, 1, afp);
    // fclose(afp);

   } else {
      lRetVal |= 1;
   }

   //free buffers
   dstImg.SetFreeOnExit(true);
   dstRefImg.SetFreeOnExit(true);
   
   return lRetVal;

}

void test_apexcv_interpolation()
{
   int e = 0;

   uint8_t  *test_image08u_pad_oal  = (uint8_t *)OAL_MemoryAllocFlag(8772, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   uint8_t  *test_image08u_2pad_oal = (uint8_t *)OAL_MemoryAllocFlag(9360, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   uint8_t  *test_image08u_oal      = (uint8_t *)OAL_MemoryAllocFlag(8192, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   uint8_t  *delta_x_oal            = (uint8_t *)OAL_MemoryAllocFlag(8192, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   uint8_t  *delta_xy_oal           = (uint8_t *)OAL_MemoryAllocFlag(16384, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   uint8_t  *bicubic_xy_oal         = (uint8_t *)OAL_MemoryAllocFlag(1, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   
   memcpy(test_image08u_pad_oal, test_image08u_pad, 8772);
   memcpy(test_image08u_2pad_oal, test_image08u_2pad, 9360);
   memcpy(test_image08u_oal, test_image08u, 8192);
   memcpy(delta_x_oal, delta_x, 8192);
   memcpy(delta_xy_oal, delta_xy, 16384);
   memcpy(bicubic_xy_oal, bicubic_xy, 1);

   
   //interpolation test
   printf("Test ApexCV interpolation start\n");

   //linear grayscale test
   {
	  printf("  Test ApexCV linear grayscale interpolation start\n");

      e = test_interp_linear_grayscale(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, &delta_x_oal[0]);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");
   
      printf("  Test ApexCV linear grayscale interpolation end\n");
   }
   
   //bilinear grayscale test
   {
	  printf("  Test ApexCV bilinear grayscale interpolation start\n");
      
      e = test_interp_bilinear_grayscale(test_image08u_oal, test_image08u_pad_oal, SRC_WIDTH, SRC_HEIGHT, &delta_xy_oal[0]);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");
   
      printf("  Test ApexCV bilinear grayscale interpolation end\n");
   }
   
   //bicubic grayscale test
   {
	  printf("  Test ApexCV bicubic grayscale interpolation start\n");
   
      e = test_interp_bicubic_grayscale(test_image08u_oal, test_image08u_2pad_oal, SRC_WIDTH, SRC_HEIGHT, &bicubic_xy_oal[0], &bicubic_xy_oal[0]);
      if (e)   printf("    08u Done                                     FAIL\n");
      else     printf("    08u Done                                     PASS\n");
   
      printf("  Test ApexCV bicubic grayscale interpolation end\n");
   }
   
   OAL_MemoryFree(test_image08u_pad_oal);
   OAL_MemoryFree(test_image08u_2pad_oal);
   OAL_MemoryFree(test_image08u_oal);
   OAL_MemoryFree(delta_x_oal);
   OAL_MemoryFree(delta_xy_oal);
   OAL_MemoryFree(bicubic_xy_oal);
   
   //interpolation done
   printf("Test ApexCV interpolation end\n");
}

} // namespace apexcv
