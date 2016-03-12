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
*  @file bilateral_5x5_proc_desc.hpp
*  @brief Process description for bilateral 5x5 filter
***********************************************************************************/
#ifndef BILATERAL_5X5_APU_PROCESS_DESC_HPP
#define BILATERAL_5X5_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "bilateral_5x5_graph.hpp"
#include "filter_chunk_size_definitions.h"


class bilateral_5x5_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "BILATERAL_5X5");
      //SetInputChunkSize(INPUT_0, FILTER_CHUNK_WIDTH, FILTER_CHUNK_HEIGHT);
   }
   
   bilateral_5x5_graph mGraph;
};

#endif
