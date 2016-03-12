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
*  @file rgb888_to_yuv_proc_desc.hpp
*  @brief Process description for rgb888 to yuv
***********************************************************************************/
#ifndef RGB888_TO_YUV_APU_PROCESS_DESC_HPP
#define RGB888_TO_YUV_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "rgb888_to_yuv_graph.hpp"
#include "color_conversion_chunk_size_definitions.h"

class rgb888_to_yuv_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "RGB888_TO_YUV");
	  //SetInputChunkSize("INPUT_0", COLCONV_CHUNK_WIDTH, COLCONV_CHUNK_HEIGHT);
   }
   
   rgb888_to_yuv_graph mGraph;
};

#endif
