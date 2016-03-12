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
 
#include <apexcv_base_integral_image.h>
#include <stdint.h>

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include <apexcv_integral_image.h>

namespace apexcv{

IntegralImage::IntegralImage()
{
}

IntegralImage::~IntegralImage()
{
}

int IntegralImage::exec( DataDescriptor&        src /*!< Source memory buffer. */,
						 DataDescriptor&        dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
	if( src.GetElementDataType() == DATATYPE_08U && 
		dst.GetElementDataType() == DATATYPE_32U) {
      
      apexcv_integral_image i; 
      
      result |= i.Initialize(src, dst);
      result |= i.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
	}
	
	return result;
}					 
                              
}  /* namespace apexcv */
