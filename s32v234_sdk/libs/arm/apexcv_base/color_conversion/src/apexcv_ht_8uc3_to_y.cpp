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
*  \file apexcv_ht_8uc3_to_y.cpp
*  \brief Host-ACF interface for rgb565 to rgb888 
***********************************************************************************/

#include "graph_templates.h"
#include <apexcv_ht_8uc3_to_y.h>

int apexcv_ht_8uc3_to_y::Initialize( DataDescriptor&  lInput0, 
                                     DataDescriptor& lOutput0, 
									 DataDescriptor&       ka, 
									 DataDescriptor&       kb, 
									 DataDescriptor&       kc, 
									 DataDescriptor&       kr ) {
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO("INPUT_0", lInput0);
   lRetVal |= mProcess.ConnectIO("KA", ka);
   lRetVal |= mProcess.ConnectIO("KB", kb);
   lRetVal |= mProcess.ConnectIO("KC", kc);
   lRetVal |= mProcess.ConnectIO("KR", kr);
   lRetVal |= mProcess.ConnectIO("OUTPUT_0", lOutput0);

   return lRetVal;
}
		  
int apexcv_ht_8uc3_to_y::Release() {
   return 0;
}
  

int apexcv_ht_8uc3_to_y::Process() {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Start();
   lRetVal |= mProcess.Wait();
   
   return lRetVal;
}
