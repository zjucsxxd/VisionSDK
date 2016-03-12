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
*  @file ht_generic_3x3_08u_proc_desc.hpp
*  @brief Process description for hand-tuned generic 3x3 filter
***********************************************************************************/
 
#ifndef HT_GENERIC_3X3_08U_APU_PROCESS_DESC_HPP
#define HT_GENERIC_3X3_08U_APU_PROCESS_DESC_HPP 
 
#include <acf_process_desc_apu.hpp>
#include "ht_generic_3x3_08u_graph.hpp"
#include "filter_chunk_size_definitions.h"


class ht_generic_3x3_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "HT_GENERIC_3X3_08U");
   }
   
   ht_generic_3x3_08u_graph mGraph;
};
#endif
