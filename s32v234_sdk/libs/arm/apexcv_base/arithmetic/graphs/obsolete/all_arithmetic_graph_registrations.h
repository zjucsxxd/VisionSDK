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
#ifndef ALL_ARITHMETIC_GRAPH_REGISTRATIONS_H
#define ALL_ARITHMETIC_GRAPH_REGISTRATILONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;

#include <ABS_08U.hpp>
#include <ABSDIFF_08U.hpp>
#include <ACCUMULATE_16S.hpp>
#include <ACCUMULATE_SQUARED_16S.hpp>
#include <ACCUMULATE_WEIGHTED_08U.hpp>
#include <ADD_08U.hpp>
#include <ADD_16S.hpp>
#include <AND_08U.hpp>
#include <AND_16U.hpp>
#include <AND_32U.hpp>
#include <CLZ_08U.hpp>
#include <CLZ_08S.hpp>
#include <CLZ_16U.hpp>
#include <CLZ_16S.hpp>
#include <MAGNITUDE_16S.hpp>
#include <NOT_08U.hpp>
#include <OR_08U.hpp>
#include <OR_16U.hpp>
#include <OR_32U.hpp>
#include <SUB_08U.hpp>
#include <SUB_16S.hpp>
#include <THRESHOLD_08U.hpp>
#include <THRESHOLD_16U.hpp>
#include <THRESHOLD_32U.hpp>
#include <XOR_08U.hpp>
#include <XOR_16U.hpp>
#include <XOR_32U.hpp>
#else
#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#include "abs_08u_apu_process_desc.hpp"
#include "abs_08u_apu_process_desc.hpp"
#include "absdiff_08u_apu_process_desc.hpp"
#include "accumulate_16s_apu_process_desc.hpp"
#include "accumulate_squared_16s_apu_process_desc.hpp"
#include "accumulate_weighted_08u_apu_process_desc.hpp"
#include "add_08u_apu_process_desc.hpp"
#include "add_16s_apu_process_desc.hpp"
#include "and_08u_apu_process_desc.hpp"
#include "and_16u_apu_process_desc.hpp"
#include "and_32u_apu_process_desc.hpp"
#include "clz_08u_apu_process_desc.hpp"
#include "clz_08s_apu_process_desc.hpp"
#include "clz_16u_apu_process_desc.hpp"
#include "clz_16s_apu_process_desc.hpp"
#include "magnitude_16s_apu_process_desc.hpp"
#include "not_08u_apu_process_desc.hpp"
#include "or_08u_apu_process_desc.hpp"
#include "or_16u_apu_process_desc.hpp"
#include "or_32u_apu_process_desc.hpp"
#include "sub_08u_apu_process_desc.hpp"
#include "sub_16s_apu_process_desc.hpp"
#include "threshold_08u_apu_process_desc.hpp"
#include "threshold_16u_apu_process_desc.hpp"
#include "threshold_32u_apu_process_desc.hpp"
#include "xor_08u_apu_process_desc.hpp"
#include "xor_16u_apu_process_desc.hpp"
#include "xor_32u_apu_process_desc.hpp"

/*REGISTER_PROCESS_TYPE(ABS_08U, abs_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(ABSDIFF_08U, absdiff_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(ACCUMULATE_16S, accumulate_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(ACCUMULATE_SQUARED_16S, accumulate_squared_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(ACCUMULATE_WEIGHTED_08U, accumulate_weighted_08u_apu_process_desc)
//REGISTER_PROCESS_TYPE(ADD_08U, add_08u_apu_process_desc)
//REGISTER_PROCESS_TYPE(ADD_16S, add_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(AND_08U, and_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(AND_16U, and_16u_apu_process_desc)
REGISTER_PROCESS_TYPE(AND_32U, and_32u_apu_process_desc)
REGISTER_PROCESS_TYPE(CLZ_08U, clz_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(CLZ_08S, clz_08s_apu_process_desc)
REGISTER_PROCESS_TYPE(CLZ_16U, clz_16u_apu_process_desc)
REGISTER_PROCESS_TYPE(CLZ_16S, clz_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(MAGNITUDE_16S, magnitude_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(NOT_08U, not_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(OR_08U, or_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(OR_16U, or_16u_apu_process_desc)
REGISTER_PROCESS_TYPE(OR_32U, or_32u_apu_process_desc)*/
REGISTER_PROCESS_TYPE(SUB_08U, sub_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(SUB_16S, sub_16s_apu_process_desc)
REGISTER_PROCESS_TYPE(THRESHOLD_08U, threshold_08u_apu_process_desc)
REGISTER_PROCESS_TYPE(THRESHOLD_16U, threshold_16u_apu_process_desc)
REGISTER_PROCESS_TYPE(THRESHOLD_32U, threshold_32u_apu_process_desc)
REGISTER_PROCESS_TYPE(XOR_08U, xor_08u_apu_process_desc)
//REGISTER_PROCESS_TYPE(XOR_16U, xor_16u_apu_process_desc)
REGISTER_PROCESS_TYPE(XOR_32U, xor_32u_apu_process_desc)
#endif


#endif
