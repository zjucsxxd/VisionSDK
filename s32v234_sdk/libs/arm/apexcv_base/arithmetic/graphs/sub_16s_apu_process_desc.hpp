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
*  @file sub_16s_proc_desc.hpp
*  @brief Process description for arithmetic subtraction (signed 16 bit)
***********************************************************************************/
#ifndef SUB_16S_APU_PROCESS_DESC_HPP
#define SUB_16S_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "sub_16s_graph.hpp"
#include "arithm_chunk_size_definitions.h"

#include "arithmetic_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"

GRAPH_CLASS_DEF_2In_1Out(SUB_16s_K);

#define SUB_16S_PI		SUB_16S
#define SUB_16S_PIN	XSTR(SUB_16S_PI)

class sub_16s_apu_process_desc : public ACF_Process_Desc_APU
{
public:

	void Create()
	{
		Initialize(mGraph, SUB_16S_PIN);
		SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
		SetInputChunkSize(GR_IN_1, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
	}
	graphClassName(SUB_16s_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(SUB_16S_PI, sub_16s_apu_process_desc)
#endif
#endif
