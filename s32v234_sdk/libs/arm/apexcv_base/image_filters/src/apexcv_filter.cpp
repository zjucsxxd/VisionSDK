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
*  \file apexcv_filter.cpp
*  \brief Host-ACF interface for filter operations.
***********************************************************************************/

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include <apexcv_filter.h>
#include "graph_templates.h"

#include <typeinfo>
#include <sstream>

/*!*********************************************************************************
*  \brief Templated filter class functions
***********************************************************************************/
template <class A>
int apexcv_filter<A>::Initialize( DataDescriptor& lInput0,
                                  DataDescriptor& lOutput0,
                                  DataDescriptor& sigmaR,
                                  DataDescriptor& sigmaD//,
								  //DataDescriptor& r_lut,
								  //DataDescriptor& d_lut
								  ) 
{
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO("SIGMA_R", sigmaR);
   lRetVal |= mProcess.ConnectIO("SIGMA_D", sigmaD);
   //lRetVal |= mProcess.ConnectIO("R_LUT", r_lut);
   //lRetVal |= mProcess.ConnectIO("D_LUT", d_lut);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_filter<A>::Initialize_Scale( DataDescriptor& lInput0,
                                        DataDescriptor& lOutput0,
                                        DataDescriptor& lFilterCoeff,
                                        DataDescriptor& lFilterScale) {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_F_COEFF, lFilterCoeff);
   lRetVal |= mProcess.ConnectIO(GR_F_SCALE, lFilterScale);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_filter<A>::Initialize( DataDescriptor& lInput0,
                                  DataDescriptor& lOutput0,
                                  DataDescriptor& lFilterCoeff ) {
   int lRetVal = 0;

   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_F_COEFF, lFilterCoeff);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_filter<A>::Initialize( DataDescriptor& lInput0,
                                  DataDescriptor& lOutput0 ) {
   int lRetVal = 0;
   
   lRetVal |= mProcess.Initialize();
   lRetVal |= mProcess.ConnectIO(GR_IN_0, lInput0);
   lRetVal |= mProcess.ConnectIO(GR_OUT_0, lOutput0);

   return lRetVal;
}

template <class A>
int apexcv_filter<A>::Release() {
   return 0;
}

template <class A>
int apexcv_filter<A>::Process() {
   int lRetVal = 0;
   lRetVal |= mProcess.Start();

   lRetVal |= mProcess.Wait();
   return lRetVal;
}

template int apexcv_filter<BILATERAL_5X5>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& sigmaR, DataDescriptor& sigmaD);
template int apexcv_filter<BILATERAL_5X5>::Release();
template int apexcv_filter<BILATERAL_5X5>::Process();

template int apexcv_filter<BOX_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<BOX_3X3_08U>::Release();
template int apexcv_filter<BOX_3X3_08U>::Process();

template int apexcv_filter<BOX_3X3_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<BOX_3X3_16S>::Release();
template int apexcv_filter<BOX_3X3_16S>::Process();

template int apexcv_filter<BOX_5X5_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<BOX_5X5_16S>::Release();
template int apexcv_filter<BOX_5X5_16S>::Process();

template int apexcv_filter<CONVOLVE_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff);
template int apexcv_filter<CONVOLVE_3X3_08U>::Release();
template int apexcv_filter<CONVOLVE_3X3_08U>::Process();

template int apexcv_filter<CONVOLVE_3X3_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff);
template int apexcv_filter<CONVOLVE_3X3_16S>::Release();
template int apexcv_filter<CONVOLVE_3X3_16S>::Process();

template int apexcv_filter<CONVOLVE_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff);
template int apexcv_filter<CONVOLVE_5X5_08U>::Release();
template int apexcv_filter<CONVOLVE_5X5_08U>::Process();

template int apexcv_filter<CONVOLVE_5X5_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff);
template int apexcv_filter<CONVOLVE_5X5_16S>::Release();
template int apexcv_filter<CONVOLVE_5X5_16S>::Process();

template int apexcv_filter<CONVOLVE_SCALE_3X3_08U>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<CONVOLVE_SCALE_3X3_08U>::Release();
template int apexcv_filter<CONVOLVE_SCALE_3X3_08U>::Process();

template int apexcv_filter<CONVOLVE_SCALE_3X3_16S>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<CONVOLVE_SCALE_3X3_16S>::Release();
template int apexcv_filter<CONVOLVE_SCALE_3X3_16S>::Process();

template int apexcv_filter<CONVOLVE_SCALE_5X5_08U>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<CONVOLVE_SCALE_5X5_08U>::Release();
template int apexcv_filter<CONVOLVE_SCALE_5X5_08U>::Process();

template int apexcv_filter<CONVOLVE_SCALE_5X5_16S>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<CONVOLVE_SCALE_5X5_16S>::Release();
template int apexcv_filter<CONVOLVE_SCALE_5X5_16S>::Process();

template int apexcv_filter<DILATE_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<DILATE_3X3_08U>::Release();
template int apexcv_filter<DILATE_3X3_08U>::Process();

template int apexcv_filter<DILATE_3X3_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<DILATE_3X3_16S>::Release();
template int apexcv_filter<DILATE_3X3_16S>::Process();

template int apexcv_filter<ERODE_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<ERODE_3X3_08U>::Release();
template int apexcv_filter<ERODE_3X3_08U>::Process();

template int apexcv_filter<GAUSSIAN_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<GAUSSIAN_3X3_08U>::Release();
template int apexcv_filter<GAUSSIAN_3X3_08U>::Process();

template int apexcv_filter<GAUSSIAN_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<GAUSSIAN_5X5_08U>::Release();
template int apexcv_filter<GAUSSIAN_5X5_08U>::Process();

template int apexcv_filter<HT_BOX_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<HT_BOX_3X3_08U>::Release();
template int apexcv_filter<HT_BOX_3X3_08U>::Process();

template int apexcv_filter<HT_GENERIC_3X3_08U>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<HT_GENERIC_3X3_08U>::Release();
template int apexcv_filter<HT_GENERIC_3X3_08U>::Process();

template int apexcv_filter<HT_GENERIC_5X5_08U>::Initialize_Scale(DataDescriptor& lInput0, DataDescriptor& lOutput0, DataDescriptor& lFilterCoeff, DataDescriptor& lFilterScale);
template int apexcv_filter<HT_GENERIC_5X5_08U>::Release();
template int apexcv_filter<HT_GENERIC_5X5_08U>::Process();

template int apexcv_filter<HT_SATURATE_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<HT_SATURATE_08S>::Release();
template int apexcv_filter<HT_SATURATE_08S>::Process();

template int apexcv_filter<HT_SOBEL_3X3_16S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<HT_SOBEL_3X3_16S>::Release();
template int apexcv_filter<HT_SOBEL_3X3_16S>::Process();

template int apexcv_filter<HT_SOBEL_X_3X3_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<HT_SOBEL_X_3X3_08S>::Release();
template int apexcv_filter<HT_SOBEL_X_3X3_08S>::Process();

template int apexcv_filter<HT_SOBEL_Y_3X3_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<HT_SOBEL_Y_3X3_08S>::Release();
template int apexcv_filter<HT_SOBEL_Y_3X3_08S>::Process();

template int apexcv_filter<MEDIAN_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<MEDIAN_3X3_08U>::Release();
template int apexcv_filter<MEDIAN_3X3_08U>::Process();

template int apexcv_filter<MEDIAN_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<MEDIAN_5X5_08U>::Release();
template int apexcv_filter<MEDIAN_5X5_08U>::Process();

template int apexcv_filter<PREWITT_X_3X3>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<PREWITT_X_3X3>::Release();
template int apexcv_filter<PREWITT_X_3X3>::Process();

template int apexcv_filter<PREWITT_Y_3X3>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<PREWITT_Y_3X3>::Release();
template int apexcv_filter<PREWITT_Y_3X3>::Process();

template int apexcv_filter<SOBEL_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_3X3_08U>::Release();
template int apexcv_filter<SOBEL_3X3_08U>::Process();

template int apexcv_filter<SOBEL_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_5X5_08U>::Release();
template int apexcv_filter<SOBEL_5X5_08U>::Process();

template int apexcv_filter<SOBEL_X_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_X_3X3_08U>::Release();
template int apexcv_filter<SOBEL_X_3X3_08U>::Process();

template int apexcv_filter<SOBEL_X_3X3_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_X_3X3_08S>::Release();
template int apexcv_filter<SOBEL_X_3X3_08S>::Process();

template int apexcv_filter<SOBEL_X_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_X_5X5_08U>::Release();
template int apexcv_filter<SOBEL_X_5X5_08U>::Process();

template int apexcv_filter<SOBEL_X_5X5_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_X_5X5_08S>::Release();
template int apexcv_filter<SOBEL_X_5X5_08S>::Process();

template int apexcv_filter<SOBEL_Y_3X3_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_Y_3X3_08U>::Release();
template int apexcv_filter<SOBEL_Y_3X3_08U>::Process();

template int apexcv_filter<SOBEL_Y_3X3_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_Y_3X3_08S>::Release();
template int apexcv_filter<SOBEL_Y_3X3_08S>::Process();

template int apexcv_filter<SOBEL_Y_5X5_08U>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_Y_5X5_08U>::Release();
template int apexcv_filter<SOBEL_Y_5X5_08U>::Process();

template int apexcv_filter<SOBEL_Y_5X5_08S>::Initialize(DataDescriptor& lInput0, DataDescriptor& lOutput0);
template int apexcv_filter<SOBEL_Y_5X5_08S>::Release();
template int apexcv_filter<SOBEL_Y_5X5_08S>::Process();


