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
#ifndef ALL_COLCONV_GRAPH_REGISTRATIONS_H
#define ALL_COLCONV_GRAPH_REGISTRATILONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;

#include <RGB565_TO_RGB888.hpp>
#include <RGB888_TO_Y.hpp>
#include <RGB888_TO_RGB565.hpp>
#include <RGB888_TO_YUV.hpp>

#else
#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#include "rgb565_to_rgb888_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(RGB565_TO_RGB888, rgb565_to_rgb888_apu_process_desc)

#include "rgb888_to_rgb565_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(RGB888_TO_RGB565, rgb888_to_rgb565_apu_process_desc)

#include "rgb888_to_y_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(RGB888_TO_Y, rgb888_to_y_apu_process_desc)

#include "rgb888_to_yuv_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(RGB888_TO_YUV, rgb888_to_yuv_apu_process_desc)

#endif


#endif
