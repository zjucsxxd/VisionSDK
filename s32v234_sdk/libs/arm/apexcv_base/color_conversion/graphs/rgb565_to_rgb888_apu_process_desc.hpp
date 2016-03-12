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
*  @file rgb565_to_rgb888_proc_desc.hpp
*  @brief Process description for rgb565 to rgb888
***********************************************************************************/
#ifndef RGB565_TO_RGB888_APU_PROCESS_DESC_HPP
#define RGB565_TO_RGB888_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "rgb565_to_rgb888_graph.hpp"
#include "color_conversion_chunk_size_definitions.h"

class rgb565_to_rgb888_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "RGB565_TO_RGB888");
	  //SetInputChunkSize("INPUT_0", COLCONV_CHUNK_WIDTH, COLCONV_CHUNK_HEIGHT);
   }
   
   rgb565_to_rgb888_graph mGraph;
};

#endif
