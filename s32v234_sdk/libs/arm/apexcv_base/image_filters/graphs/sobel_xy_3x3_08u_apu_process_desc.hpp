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
*  @file sobel_xy_3x3_08u_proc_desc.hpp
*  @brief Process description for sobel xy 3x3 filter (unsigned 8 bit)
***********************************************************************************/
 
#ifndef SOBEL_XY_3X3_08U_APU_PROCESS_DESC_HPP
#define SOBEL_XY_3X3_08U_APU_PROCESS_DESC_HPP

#include <acf_process_desc_apu.hpp>
#include "sobel_xy_3x3_08u_graph.hpp"
#include "filter_chunk_size_definitions.h"

class sobel_xy_3x3_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "SOBEL_XY_3X3_08U");
   }
   
   sobel_xy_3x3_08u_graph mGraph;
};
#endif
