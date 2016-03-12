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
*  @file integral_image_proc_desc.hpp
*  @brief Process description for histogram
***********************************************************************************/
#ifndef  INTEGRAL_IMAGE_APU_PROCESS_DESC_HPP
#define INTEGRAL_IMAGE_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "integral_image_graph.hpp"
#include "integral_img_chunk_size_definitions.h"

class integral_image_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "INTEGRAL_IMAGE");
      SetInputChunkSize("INPUT_0", INTEGR_IMG_CHUNK_WIDTH, INTEGR_IMG_CHUNK_HEIGHT);
   }
   
   integral_image_graph mGraph;
};

#endif
