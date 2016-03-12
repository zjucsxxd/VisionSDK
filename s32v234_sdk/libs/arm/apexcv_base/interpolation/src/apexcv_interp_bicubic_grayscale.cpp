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
*  \file apexcv_bicubic.cpp
*  \brief Host-ACF interface for bicubic
***********************************************************************************/

#include <apexcv_interp_bicubic_grayscale.h>
#include "all_interpol_graph_registrations.h"
#include "graph_templates.h"

int apexcv_interp_bicubic_grayscale::Initialize(       DataDescriptor& lInput0,
                                                       DataDescriptor& lOutput0,
                                                       DataDescriptor& x_offset, DataDescriptor& y_offset ) {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO("INPUT_0", lInput0);
   lRetVal |= mProcess.ConnectIO("X_OFFSET", x_offset);
   lRetVal |= mProcess.ConnectIO("Y_OFFSET", y_offset);
   lRetVal |= mProcess.ConnectIO("OUTPUT_0", lOutput0);
  
   return lRetVal;
}

int apexcv_interp_bicubic_grayscale::Release() {
   return 0;
}
  

int apexcv_interp_bicubic_grayscale::Process() {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Start();
   lRetVal |= mProcess.Wait();
   
   return lRetVal;
}
