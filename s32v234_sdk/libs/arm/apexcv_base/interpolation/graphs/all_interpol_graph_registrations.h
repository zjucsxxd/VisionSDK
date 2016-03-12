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
#ifndef ALL_INTERPOL_GRAPH_REGISTRATIONS_H
#define ALL_INTERPOL_GRAPH_REGISTRATIONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#include <INTERP_BILINEAR_GRAYSCALE.hpp>
#include <INTERP_LINEAR_GRAYSCALE.hpp>
#include <INTERP_BICUBIC_GRAYSCALE.hpp>

#else
#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#include "interp_bilinear_grayscale_apu_process_desc.hpp"
#include "interp_linear_grayscale_apu_process_desc.hpp"
#include "interp_bicubic_grayscale_apu_process_desc.hpp"


REGISTER_PROCESS_TYPE(INTERP_LINEAR_GRAYSCALE, interp_linear_grayscale_apu_process_desc)
REGISTER_PROCESS_TYPE(INTERP_BILINEAR_GRAYSCALE, interp_bilinear_grayscale_apu_process_desc)
REGISTER_PROCESS_TYPE(INTERP_BICUBIC_GRAYSCALE, interp_bicubic_grayscale_apu_process_desc)

#endif


#endif
