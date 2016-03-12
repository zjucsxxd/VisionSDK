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
*  \file apexcv_histogram_test.cpp
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

#include <apexcv_base_histogram.h>
#include <apexcv_histogram_ref.h>
#include <apexcv_histogram_test_image.h>

using namespace apexcv;

namespace apexcv{
	
int test_histogram(const unsigned char *src, int w, int h) 
{
   int lRetVal = 0;
   apexcv::Histogram hg;
   
   DataDescriptor srcImg;
   srcImg.InitManual(w, h, (void *)src, (void *)OAL_MemoryReturnAddress((void *)src, ACCESS_PHY), DATATYPE_08U);
   DataDescriptor dstImg(256, 1, DATATYPE_32U);
   DataDescriptor dstRefImg(256, 1, DATATYPE_32U);
   
   memset(dstImg.GetDataPtr(), 0, 256 * 4);
   memset(dstRefImg.GetDataPtr(), 0, 256 * 4);
   
   if(srcImg.IsOK() &&dstImg.IsOK() && dstRefImg.IsOK()) {
	   
      //run implementation
      lRetVal |= hg.exec(srcImg, dstImg);
  
      //obtain dst data pointers
      uint32_t* pDst    = (uint32_t*) dstImg.GetDataPtr();
      uint32_t* pDstRef = (uint32_t*) dstRefImg.GetDataPtr();
      
      //run reference
      histogram_ref(pDstRef, src, w, w, h);

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

void test_apexcv_histogram()
{
   int e = 0;
   uint8_t  *test_image08u_oal         = (uint8_t *)OAL_MemoryAllocFlag(1024, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
   memcpy(test_image08u_oal, test_image08u, 1024);

   
   //histogram test
   {
	  printf("Test ApexCV histogram start\n");
      
	  e = test_histogram(test_image08u_oal, SRC_WIDTH, SRC_HEIGHT);
	  if (e)   printf("  08u Done                                       FAIL\n");
      else     printf("  08u Done                                       PASS\n");
	  
      //histogram done
      printf("Test ApexCV histogram end\n");
   }
   
   OAL_MemoryFree(test_image08u_oal);
}

} // namespace apexcv
