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
 
#include <apexcv_base_histogram.h>
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

#include <apexcv_histogram.h>

namespace apexcv{

Histogram::Histogram()
{
}

Histogram::~Histogram()
{
}

int Histogram::exec( DataDescriptor&        src /*!< Source memory buffer. */,
                     DataDescriptor&        dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
	if(src.GetElementDataType() == DATATYPE_08U && 
			dst.GetElementDataType() == DATATYPE_32U) {
      
      apexcv_histogram h; 
      
      result |= h.Initialize(src, dst);
      result |= h.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
	}
	
	return result;
}					 
                              
}  /* namespace apex */
