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
*  \file apexcv_integral_image_test.cpp
*  \brief Run and validate histogram kernels
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

#include <apexcv_base_integral_image.h>
#include <apexcv_integral_image_ref.h>
#include <apexcv_integral_image_test_image.h>

using namespace apexcv;

namespace apexcv{
	
int test_integral_image(const unsigned char *src, int w, int h) 
{
   int lRetVal = 0;
   apexcv::IntegralImage i;
   
   DataDescriptor srcImg;
	     srcImg.InitManual(w, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(w, h, DATATYPE_32U);
   DataDescriptor dstRefImg(w, h, DATATYPE_32U);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
	   
      //run implementation
      lRetVal |= i.exec(srcImg, dstImg);
  
      //obtain dst data pointers
      unsigned int* pDst    = (unsigned int*) dstImg.GetDataPtr();
      unsigned int* pDstRef = (unsigned int*) dstRefImg.GetDataPtr();
      
      //run reference
      integral_image_ref(pDstRef, src, w, w, h);

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

void test_apexcv_integral_image()
{
   int e = 0;

   uint8_t  *test_image08u_oal         = (uint8_t *)OAL_MemoryAllocFlag(1024, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   memcpy(test_image08u_oal, test_image08u, 1024);
   
   //integral image test
   {
	  printf("Test ApexCV integral image start\n");
      
	  e = test_integral_image(test_image08u_oal, SRC_WIDTH, SRC_HEIGHT);
      if (e)   printf("  08u Done                                       FAIL\n");
      else     printf("  08u Done                                       PASS\n");

      printf("Test ApexCV integral image end\n");
   }
   
   OAL_MemoryFree(test_image08u_oal);
}

} // namespace apexcv
