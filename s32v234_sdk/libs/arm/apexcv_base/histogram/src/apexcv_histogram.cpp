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
*  \file apexcv_histogram.cpp
*  \brief Host-ACF interface for histogram
***********************************************************************************/

#include <apexcv_histogram.h>

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

#include "graph_templates.h"

int apexcv_histogram::Initialize( DataDescriptor& lInput0,
                                  DataDescriptor& lOutput0 ) {
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO("INPUT_0", lInput0);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);
  
   return lRetVal;
}
		  
int apexcv_histogram::Release() {
   return 0;
}
  

int apexcv_histogram::Process() {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Start();
   lRetVal |= mProcess.Wait();
   
   return lRetVal;
}
