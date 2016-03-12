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
*  \file apexcv_histogram_ref.cpp
*  \brief Reference code for histogram kernels
***********************************************************************************/

#include <stdint.h>

#include <apexcv_histogram_ref.h>

void histogram_ref(uint32_t* hst, const uint8_t* src, int ss, int sw, int sh)
{
   // Initialize Histogram
   
   for (int y=0; y<sh; ++y)
   {
      for (int x=0; x<sw; ++x)
      {
         ++hst[src[y*ss+x]];
      }
   }
}

