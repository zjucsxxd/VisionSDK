/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2013 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 ******************************************************************************/
  
/*!*********************************************************************************
*  @file abs_08u_graph.hpp
*  @brief ACF graph for absolute difference
***********************************************************************************/
#ifndef ALL_INTEGR_IMG_GRAPH_REGISTRATIONS_H
#define ALL_INTEGR_IMG_GRAPH_REGISTRATILONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;

#include <INTEGRAL_IMAGE.hpp>

#else
#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#include "integral_image_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(INTEGRAL_IMAGE, integral_image_apu_process_desc)

#endif


#endif
