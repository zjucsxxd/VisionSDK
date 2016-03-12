/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
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
*  @file interp_linear_proc_desc.hpp
*  @brief Process description for linear grayscale interpolation
***********************************************************************************/
#ifndef INTERP_LINEAR_GRAYSCALE_APU_PROCESS_DESC_HPP
#define INTERP_LINEAR_GRAYSCALE_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "interp_linear_grayscale_graph.hpp"
#include "interpol_chunk_size_definitions.h"

class interp_linear_grayscale_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "INTERP_LINEAR_GRAYSCALE");
	  SetInputChunkSize("INPUT_0", INTERPOL_CHUNK_WIDTH, INTERPOL_CHUNK_HEIGHT);
	  SetInputChunkSize("DELTA_X", INTERPOL_CHUNK_WIDTH, INTERPOL_CHUNK_HEIGHT);
   }
   
   interp_linear_grayscale_graph mGraph;
};

#endif
