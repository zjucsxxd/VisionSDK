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
*  @file or_32u_proc_desc.hpp
*  @brief Process description for bitwise or (unsigned 32 bit)
***********************************************************************************/
#ifndef OR_32U_APU_PROCESS_DESC_HPP
#define OR_32U_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "or_32u_graph.hpp"
#include "arithm_chunk_size_definitions.h"
#include "arithmetic_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"

GRAPH_CLASS_DEF_2In_1Out(OR_32u_K);

#define OR_32U_PI		OR_32U
#define OR_32U_PIN	XSTR(OR_32U_PI)

class or_32u_apu_process_desc : public ACF_Process_Desc_APU
{
public:

	void Create()
	{
		Initialize(mGraph, OR_32U_PIN);
		SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
		SetInputChunkSize(GR_IN_1, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
	}
	graphClassName(OR_32u_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(OR_32U_PI, or_32u_apu_process_desc)
#endif

#endif
