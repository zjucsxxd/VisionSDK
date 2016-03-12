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
*  @file absdiff_08u_proc_desc.hpp
*  @brief Process description for absolute difference
***********************************************************************************/
#ifndef ABSDIFF_08u_APU_PROCESS_DESC_HPP
#define ABSDIFF_08u_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "absdiff_08u_graph.hpp"
#include "arithm_chunk_size_definitions.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
#include "arithmetic_kernels.h"

GRAPH_CLASS_DEF_2In_1Out(ABSDIFF_08u_K)

#define ABSDIFF_08U_PI	ABSDIFF_08U
#define ABSDIFF_08U_PIN	XSTR(ABSDIFF_08U_PI)

class absdiff_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, ABSDIFF_08U_PIN);
	  SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
	  SetInputChunkSize(GR_IN_1, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
   }
   
   //absdiff_08u_graph mGraph;
   graphClassName(ABSDIFF_08u_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(ABSDIFF_08U_PI, absdiff_08u_apu_process_desc)
#endif


#endif
