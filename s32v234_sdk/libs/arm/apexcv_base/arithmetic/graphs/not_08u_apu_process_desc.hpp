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
*  @file not_08u_proc_desc.hpp
*  @brief Process description for bitwise not (unsigned 8 bit)
***********************************************************************************/
#ifndef NOT_08U_APU_PROCESS_DESC_HPP
#define NOT_08U_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
//#include "not_08u_graph.hpp"
#include "arithm_chunk_size_definitions.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
#include "arithmetic_kernels.h"

GRAPH_CLASS_DEF_1In_1Out(NOT_08u_K)

#define NOT_08U_PI	NOT_08U
#define NOT_08U_PIN	XSTR(NOT_08U_PI)

class not_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
	void Create()
	{
		Initialize(mGraph, NOT_08U_PIN);
		SetInputChunkSize(GR_IN_0, ARITHM_CHUNK_WIDTH, ARITHM_CHUNK_HEIGHT);
	}

	//not_08u_graph mGraph;
	graphClassName(NOT_08u_K) mGraph;
};


#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(NOT_08U_PI, not_08u_apu_process_desc)
#endif

#endif
