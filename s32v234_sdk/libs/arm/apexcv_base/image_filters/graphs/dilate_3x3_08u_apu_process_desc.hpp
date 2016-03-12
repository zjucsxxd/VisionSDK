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
*  @file dilate_3x3_08u_proc_desc.hpp
*  @brief Process description for dilate 3x3 filter (unsigned 8 bit)
***********************************************************************************/
#ifndef DILATE_3X3_08U_APU_PROCESS_DESC_HPP
#define DILATE_3X3_08U_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "dilate_3x3_08u_graph.hpp"
#include "filter_chunk_size_definitions.h"


class dilate_3x3_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "DILATE_3X3_08U");
      //SetInputChunkSize(INPUT_0, FILTER_CHUNK_WIDTH, FILTER_CHUNK_HEIGHT);
   }
   
   dilate_3x3_08u_graph mGraph;
};
#endif

