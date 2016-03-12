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
*  \file apexcv_arithmetic.cpp
*  \brief Host-ACF interface for arithmetic operations.
***********************************************************************************/


#include "apexcv_arithmetic.h"
//#include "cgv_report.h"
#include "all_arithmetic_graph_registrations.h"
#include "graph_templates.h"

// report tool
#include <typeinfo>
#include <sstream>
/*!*********************************************************************************
*  \brief Templated arithmetic class functions
***********************************************************************************/
template <class A>
int apexcv_arithmetic<A>::Initialize( DataDescriptor& lInput0,
                                      DataDescriptor& lInput1,
                                      DataDescriptor& lAlpha,
                                      DataDescriptor& lOutput0 ) {
   int lRetVal = 0;

   //
   //std::stringstream fName;
   //fName << "APEX_APEXCV_" << typeid(A).name() << "_0";
   //CGV_REPORT_LOG(fName.str().c_str());
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_IN_1, lInput1);
   lRetVal |= mProcess.ConnectIO(GR_ALPHA,   lAlpha);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_arithmetic<A>::Initialize( DataDescriptor& lInput0,
                                      DataDescriptor& lInput1,
                                      DataDescriptor& lOutput0 ) {
   int lRetVal = 0;
   
   //
   //std::stringstream fName;
   //fName << "APEX_APEXCV_" << typeid(A).name() << "_0";
   //CGV_REPORT_LOG(fName.str().c_str());
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_IN_1, lInput1);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_arithmetic<A>::Initialize( DataDescriptor& lInput0,
                                      DataDescriptor& lOutput0 ) {
   int lRetVal = 0;
   //
   //std::stringstream fName;
   //fName << "APEX_APEXCV_" << typeid(A).name() << "_0";
   //CGV_REPORT_LOG(fName.str().c_str());
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}
		  
template <class A>
int apexcv_arithmetic<A>::Release() {
   return 0;
}
  
template <class A>
int apexcv_arithmetic<A>::Process() {
   int lRetVal = 0;
   lRetVal |= mProcess.Start();
   
   lRetVal |= mProcess.Wait();
   return lRetVal;
}

template int apexcv_arithmetic<ABS_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<ABS_08U>::Release();
template int apexcv_arithmetic<ABS_08U>::Process();

template int apexcv_arithmetic<ABSDIFF_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<ABSDIFF_08U>::Release();
template int apexcv_arithmetic<ABSDIFF_08U>::Process();

template int apexcv_arithmetic<ACCUMULATE_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                   
template int apexcv_arithmetic<ACCUMULATE_16S>::Release();
template int apexcv_arithmetic<ACCUMULATE_16S>::Process();

template int apexcv_arithmetic<ACCUMULATE_SQUARED_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, 
                                                                     DataDescriptor& lScale,  DataDescriptor& lOutput0 );                                   
template int apexcv_arithmetic<ACCUMULATE_SQUARED_16S>::Release();
template int apexcv_arithmetic<ACCUMULATE_SQUARED_16S>::Process();

template int apexcv_arithmetic<ACCUMULATE_WEIGHTED_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, 
                                                                     DataDescriptor& lAlpha,  DataDescriptor& lOutput0 );                                   
template int apexcv_arithmetic<ACCUMULATE_WEIGHTED_08U>::Release();
template int apexcv_arithmetic<ACCUMULATE_WEIGHTED_08U>::Process();

template int apexcv_arithmetic<ADD_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<ADD_08U>::Release();
template int apexcv_arithmetic<ADD_08U>::Process();

template int apexcv_arithmetic<ADD_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<ADD_16S>::Release();
template int apexcv_arithmetic<ADD_16S>::Process();

template int apexcv_arithmetic<AND_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<AND_08U>::Release();
template int apexcv_arithmetic<AND_08U>::Process();

template int apexcv_arithmetic<AND_16U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<AND_16U>::Release();
template int apexcv_arithmetic<AND_16U>::Process();

template int apexcv_arithmetic<AND_32U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<AND_32U>::Release();
template int apexcv_arithmetic<AND_32U>::Process();

template int apexcv_arithmetic<CLZ_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<CLZ_08U>::Release();
template int apexcv_arithmetic<CLZ_08U>::Process();

template int apexcv_arithmetic<CLZ_08S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<CLZ_08S>::Release();
template int apexcv_arithmetic<CLZ_08S>::Process();

template int apexcv_arithmetic<CLZ_16U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<CLZ_16U>::Release();
template int apexcv_arithmetic<CLZ_16U>::Process();

template int apexcv_arithmetic<CLZ_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<CLZ_16S>::Release();
template int apexcv_arithmetic<CLZ_16S>::Process();

template int apexcv_arithmetic<MAGNITUDE_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<MAGNITUDE_16S>::Release();
template int apexcv_arithmetic<MAGNITUDE_16S>::Process();

template int apexcv_arithmetic<NOT_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lOutput0 );		                                    
template int apexcv_arithmetic<NOT_08U>::Release();
template int apexcv_arithmetic<NOT_08U>::Process();

template int apexcv_arithmetic<OR_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<OR_08U>::Release();
template int apexcv_arithmetic<OR_08U>::Process();

template int apexcv_arithmetic<OR_16U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );		                                    
template int apexcv_arithmetic<OR_16U>::Release();
template int apexcv_arithmetic<OR_16U>::Process();

template int apexcv_arithmetic<OR_32U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<OR_32U>::Release();
template int apexcv_arithmetic<OR_32U>::Process();

template int apexcv_arithmetic<SUB_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );		                                    
template int apexcv_arithmetic<SUB_08U>::Release();
template int apexcv_arithmetic<SUB_08U>::Process();

template int apexcv_arithmetic<SUB_16S>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );	                                    
template int apexcv_arithmetic<SUB_16S>::Release();
template int apexcv_arithmetic<SUB_16S>::Process();

template int apexcv_arithmetic<THRESHOLD_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<THRESHOLD_08U>::Release();
template int apexcv_arithmetic<THRESHOLD_08U>::Process();

template int apexcv_arithmetic<THRESHOLD_16U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<THRESHOLD_16U>::Release();
template int apexcv_arithmetic<THRESHOLD_16U>::Process();

template int apexcv_arithmetic<THRESHOLD_32U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<THRESHOLD_32U>::Release();
template int apexcv_arithmetic<THRESHOLD_32U>::Process();

template int apexcv_arithmetic<XOR_08U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<XOR_08U>::Release();
template int apexcv_arithmetic<XOR_08U>::Process();

template int apexcv_arithmetic<XOR_16U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<XOR_16U>::Release();
template int apexcv_arithmetic<XOR_16U>::Process();

template int apexcv_arithmetic<XOR_32U>::Initialize( DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0 );                                    
template int apexcv_arithmetic<XOR_32U>::Release();
template int apexcv_arithmetic<XOR_32U>::Process();
