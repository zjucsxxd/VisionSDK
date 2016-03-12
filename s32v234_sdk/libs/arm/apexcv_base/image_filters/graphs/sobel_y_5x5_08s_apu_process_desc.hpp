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
*  @file sobel_y_5x5_08s_proc_desc.hpp
*  @brief Process description for sobel y 5x5 filter (unsigned 8 bit to signed 8 bit)
***********************************************************************************/
 
#ifndef SOBEL_Y_5X5_08S_APU_PROCESS_DESC_HPP
#define SOBEL_Y_5X5_08S_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "sobel_y_5x5_08s_graph.hpp"
#include "filter_chunk_size_definitions.h"


class sobel_y_5x5_08s_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "SOBEL_Y_5X5_08S");
      //SetInputChunkSize(INPUT_0, FILTER_CHUNK_WIDTH, FILTER_CHUNK_HEIGHT);
   }
   
   sobel_y_5x5_08s_graph mGraph;
};

#endif
