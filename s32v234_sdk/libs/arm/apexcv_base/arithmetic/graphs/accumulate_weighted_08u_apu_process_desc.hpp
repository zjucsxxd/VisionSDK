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
*  @file accumulate_weighted_08u_proc_desc.hpp
*  @brief Process description for accumulate weighted (unsigned 8 bit)
***********************************************************************************/
#ifndef ACCUMULATE_16S_WEIGHTED_APU_PROCESS_DESC_HPP
#define ACCUMULATE_16S_WEIGHTED_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "accumulate_weighted_08u_graph.hpp"
#include "arithm_chunk_size_definitions.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
#include "arithmetic_kernels.h"

GRAPH_CLASS_DEF_2In_1Alpha_1Out(ACCUM_WGTD_08u_K);

#define ACCUMWGTD_PI	ACCUMULATE_WEIGHTED_08U
#define ACCUMWGTD_PIN	XSTR(ACCUMWGTD_PI)

class accumulate_weighted_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, ACCUMWGTD_PIN);
      SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
      SetInputChunkSize(GR_IN_1, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
   }
   
   //accumulate_weighted_08u_graph mGraph;
   graphClassName(ACCUM_WGTD_08u_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(ACCUMWGTD_PI, accumulate_weighted_08u_apu_process_desc)
#endif


#endif
