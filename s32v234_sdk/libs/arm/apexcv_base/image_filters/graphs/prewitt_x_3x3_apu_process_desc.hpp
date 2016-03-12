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
*  @file prewitt_x_3x3_proc_desc.hpp
*  @brief Process description for prewitt x 3x3 filter 
***********************************************************************************/
 
#ifndef PREWITT_X_3X3_APU_PROCESS_DESC_HPP
#define PREWITT_X_3X3_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "prewitt_x_3x3_graph.hpp"
#include "filter_chunk_size_definitions.h"


class prewitt_x_3x3_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "PREWITT_X_3X3");
      //SetInputChunkSize(INPUT_0, FILTER_CHUNK_WIDTH, FILTER_CHUNK_HEIGHT);
   }
   
   prewitt_x_3x3_graph mGraph;
};
#endif
