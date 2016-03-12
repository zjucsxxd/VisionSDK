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
#ifndef ALL_FILTER_GRAPH_REGISTRATIONS_H
#define ALL_FILTER_GRAPH_REGISTRATILONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
//filter kernel headers
#include <BILATERAL_5X5.hpp>
#include <BOX_3X3_08U.hpp>
#include <BOX_3X3_16S.hpp>
#include <BOX_5X5_16S.hpp>
#include <CONVOLVE_3X3_08U.hpp>
#include <CONVOLVE_3X3_16S.hpp>
#include <CONVOLVE_5X5_08U.hpp>
#include <CONVOLVE_5X5_16S.hpp>
#include <CONVOLVE_SCALE_3X3_08U.hpp>
#include <CONVOLVE_SCALE_3X3_16S.hpp>
#include <CONVOLVE_SCALE_5X5_08U.hpp>
#include <CONVOLVE_SCALE_5X5_16S.hpp>
#include <DILATE_3X3_08U.hpp>
#include <DILATE_3X3_16S.hpp>
#include <ERODE_3X3_08U.hpp>
#include <GAUSSIAN_3X3_08U.hpp>
#include <GAUSSIAN_5X5_08U.hpp>
#include <HT_BOX_3X3_08U.hpp>
#include <HT_CENTRALDX_3X3_16S.hpp>
#include <HT_CENTRALDY_3X3_16S.hpp>
#include <HT_GENERIC_3X3_08U.hpp>
#include <HT_GENERIC_5X5_08U.hpp>
#include <HT_SATURATE_08S.hpp>
#include <HT_SEPARABLE_3X3_16S.hpp>
#include <HT_SEPARABLE_5X5_16S.hpp>
#include <HT_SOBEL_3X3_16S.hpp>
#include <HT_SOBEL_X_3X3_08S.hpp>
#include <HT_SOBEL_Y_3X3_08S.hpp>
#include <MEDIAN_3X3_08U.hpp>
#include <MEDIAN_5X5_08U.hpp>
#include <PREWITT_X_3X3.hpp>
#include <PREWITT_Y_3X3.hpp>
#include <SOBEL_3X3_08U.hpp>
#include <SOBEL_5X5_08U.hpp>
#include <SOBEL_X_3X3_08S.hpp>
#include <SOBEL_X_3X3_08U.hpp>
#include <SOBEL_X_5X5_08S.hpp>
#include <SOBEL_X_5X5_08U.hpp>
#include <SOBEL_XY_3X3_08U.hpp>
#include <SOBEL_Y_3X3_08S.hpp>
#include <SOBEL_Y_3X3_08U.hpp>
#include <SOBEL_Y_5X5_08S.hpp>
#include <SOBEL_Y_5X5_08U.hpp>
#else
#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;
//filter kernel headers
#include <bilateral_5x5_apu_process_desc.hpp>
#include <box_3x3_08u_apu_process_desc.hpp>
#include <box_3x3_16s_apu_process_desc.hpp>
#include <box_5x5_16s_apu_process_desc.hpp>
#include <convolve_3x3_08u_apu_process_desc.hpp>
#include <convolve_3x3_16s_apu_process_desc.hpp>
#include <convolve_5x5_08u_apu_process_desc.hpp>
#include <convolve_5x5_16s_apu_process_desc.hpp>
#include <convolve_scale_3x3_08u_apu_process_desc.hpp>
#include <convolve_scale_3x3_16s_apu_process_desc.hpp>
#include <convolve_scale_5x5_08u_apu_process_desc.hpp>
#include <convolve_scale_5x5_16s_apu_process_desc.hpp>
#include <dilate_3x3_08u_apu_process_desc.hpp>
#include <dilate_3x3_16s_apu_process_desc.hpp>
#include <erode_3x3_08u_apu_process_desc.hpp>
#include <gaussian_3x3_08u_apu_process_desc.hpp>
#include <gaussian_5x5_08u_apu_process_desc.hpp>
#include <ht_box_3x3_08u_apu_process_desc.hpp>
#include <ht_centraldx_3x3_16s_apu_process_desc.hpp>
#include <ht_centraldy_3x3_16s_apu_process_desc.hpp>
#include <ht_generic_3x3_08u_apu_process_desc.hpp>
#include <ht_generic_5x5_08u_apu_process_desc.hpp>
#include <ht_saturate_08s_apu_process_desc.hpp>
#include <ht_separable_3x3_16s_apu_process_desc.hpp>
#include <ht_separable_5x5_16s_apu_process_desc.hpp>
#include <ht_sobel_3x3_16s_apu_process_desc.hpp>
#include <ht_sobel_x_3x3_08s_apu_process_desc.hpp>
#include <ht_sobel_y_3x3_08s_apu_process_desc.hpp>
#include <median_3x3_08u_apu_process_desc.hpp>
#include <median_5x5_08u_apu_process_desc.hpp>
#include <prewitt_x_3x3_apu_process_desc.hpp>
#include <prewitt_y_3x3_apu_process_desc.hpp>
#include <sobel_3x3_08u_apu_process_desc.hpp>
#include <sobel_5x5_08u_apu_process_desc.hpp>
#include <sobel_x_3x3_08s_apu_process_desc.hpp>
#include <sobel_x_3x3_08u_apu_process_desc.hpp>
#include <sobel_x_5x5_08s_apu_process_desc.hpp>
#include <sobel_x_5x5_08u_apu_process_desc.hpp>
#include <sobel_xy_3x3_08u_apu_process_desc.hpp>
#include <sobel_y_3x3_08s_apu_process_desc.hpp>
#include <sobel_y_3x3_08u_apu_process_desc.hpp>
#include <sobel_y_5x5_08s_apu_process_desc.hpp>
#include <sobel_y_5x5_08u_apu_process_desc.hpp>


REGISTER_PROCESS_TYPE(BILATERAL_5X5, bilateral_5x5_apu_process_desc)
REGISTER_PROCESS_TYPE(BOX_3X3_08U, box_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(BOX_3X3_16S, box_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(BOX_5X5_16S, box_5x5_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_3X3_08U, convolve_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_3X3_16S, convolve_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_5X5_08U, convolve_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_5X5_16S, convolve_5x5_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_SCALE_3X3_08U, convolve_scale_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_SCALE_3X3_16S, convolve_scale_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_SCALE_5X5_08U, convolve_scale_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(CONVOLVE_SCALE_5X5_16S, convolve_scale_5x5_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(DILATE_3X3_08U, dilate_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(DILATE_3X3_16S, dilate_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(ERODE_3X3_08U, erode_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(GAUSSIAN_3X3_08U, gaussian_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(GAUSSIAN_5X5_08U, gaussian_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_BOX_3X3_08U, ht_box_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_CENTRALDX_3X3_16S, ht_centraldx_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_CENTRALDY_3X3_16S, ht_centraldy_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_GENERIC_3X3_08U, ht_generic_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_GENERIC_5X5_08U, ht_generic_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SATURATE_08S, ht_saturate_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SEPARABLE_3X3_16S, ht_separable_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SEPARABLE_5X5_16S, ht_separable_5x5_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SOBEL_3X3_16S, ht_sobel_3x3_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SOBEL_X_3X3_08S, ht_sobel_x_3x3_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(HT_SOBEL_Y_3X3_08S, ht_sobel_y_3x3_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(MEDIAN_3X3_08U, median_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(MEDIAN_5X5_08U, median_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(PREWITT_X_3X3, prewitt_x_3x3_apu_process_desc)
REGISTER_PROCESS_TYPE(PREWITT_Y_3X3, prewitt_y_3x3_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_3X3_08U, sobel_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_5X5_08U, sobel_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_X_3X3_08U, sobel_x_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_X_3X3_08S, sobel_x_3x3_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_X_5X5_08U, sobel_x_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_X_5X5_08S, sobel_x_5x5_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_XY_3X3_08U, sobel_xy_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_Y_3X3_08U, sobel_y_3x3_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_Y_3X3_08S, sobel_y_3x3_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_Y_5X5_08U, sobel_y_5x5_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SOBEL_Y_5X5_08S, sobel_y_5x5_08s_apu_process_desc)

#endif


#endif
