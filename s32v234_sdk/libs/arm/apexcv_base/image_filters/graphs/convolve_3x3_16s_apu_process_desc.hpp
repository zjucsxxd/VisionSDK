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
*  @file convolve_3x3_16s_proc_desc.hpp
*  @brief Process description for convolve filter (signed 16 bit)
***********************************************************************************/
#ifndef CONVOLVE_3X3_16S_APU_PROCESS_DESC_HPP
#define CONVOLVE_3X3_16S_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "convolve_3x3_16s_graph.hpp"
#include "filter_chunk_size_definitions.h"


class convolve_3x3_16s_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "CONVOLVE_3X3_16S");
      //SetInputChunkSize(INPUT_0, FILTER_CHUNK_WIDTH, FILTER_CHUNK_HEIGHT);
   }
   
   convolve_3x3_16s_graph mGraph;
};
#endif

