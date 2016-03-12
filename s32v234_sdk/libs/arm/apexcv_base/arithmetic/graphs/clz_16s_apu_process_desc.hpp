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
*  @file clz_16s_proc_desc.hpp
*  @brief Process description for count leading zeros (signed 16-bit)
***********************************************************************************/
#ifndef CLZ_16S_APU_PROCESS_DESC_HPP
#define CLZ_16S_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "clz_16s_graph.hpp"
#include "arithm_chunk_size_definitions.h"

#include<acf_graph.hpp>
#include "graph_templates.h"
#include "arithmetic_kernels.h"

GRAPH_CLASS_DEF_1In_1Out(CLZ_16s_K)

#define CLZ_16S_PI	CLZ_16S
#define CLZ_16S_PIN	XSTR(CLZ_16S_PI)

class clz_16s_apu_process_desc : public ACF_Process_Desc_APU
{
public:
	void Create()
	{
		Initialize(mGraph, CLZ_16S_PIN);
		//SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
	}

	//clz_16s_graph mGraph;
	graphClassName(CLZ_16s_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(CLZ_16S_PI, clz_16s_apu_process_desc)
#endif


#endif
