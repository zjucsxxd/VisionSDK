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
*  @file histogram_proc_desc.hpp
*  @brief Process description for histogram
***********************************************************************************/
#ifndef HISTOGRAM_APU_PROCESS_DESC_HPP
#define HISTOGRAM_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "histogram_graph.hpp"
#include "histogram_chunk_size_definitions.h"

class histogram_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "HISTOGRAM");
	  SetInputChunkSize("INPUT_0", HISTO_CHUNK_WIDTH, HISTO_CHUNK_HEIGHT);
   }
   
   histogram_graph mGraph;
};

#endif