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
*  \file apexcv_rgb565_to_rgb888.cpp
*  \brief Host-ACF interface for rgb565 to rgb888 
***********************************************************************************/

#include "graph_templates.h"
#include <apexcv_rgb565_to_rgb888.h>

int apexcv_rgb565_to_rgb888::Initialize( DataDescriptor& lInput0,
                                         DataDescriptor& lOutput0 ) {
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO("INPUT_0", lInput0);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}
		  
int apexcv_rgb565_to_rgb888::Release() {
   return 0;
}
  

int apexcv_rgb565_to_rgb888::Process() {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Start();
   lRetVal |= mProcess.Wait();
   
   return lRetVal;
}
