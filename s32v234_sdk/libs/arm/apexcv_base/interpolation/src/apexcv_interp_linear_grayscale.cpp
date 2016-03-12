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
*  \file apexcv_interp_linear_grayscale.cpp
*  \brief Host-ACF interface for linear grayscale interpolation
***********************************************************************************/

#include <apexcv_interp_linear_grayscale.h>

#include "all_interpol_graph_registrations.h"
#include "graph_templates.h"

int apexcv_interp_linear_grayscale::Initialize( DataDescriptor& lInput0,
                                                DataDescriptor& lOutput0,
                                                DataDescriptor& delta ) {
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO("INPUT_0", lInput0);
   lRetVal |= mProcess.ConnectIO("DELTA_X", delta);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);
  
   return lRetVal;
}

int apexcv_interp_linear_grayscale::Release() {
   return 0;
}
  

int apexcv_interp_linear_grayscale::Process() {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Start();
   lRetVal |= mProcess.Wait();
   
   return lRetVal;
}
