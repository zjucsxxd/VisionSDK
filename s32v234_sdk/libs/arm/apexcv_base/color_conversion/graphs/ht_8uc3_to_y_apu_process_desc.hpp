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
*  @file ht_8UC3_to_y_proc_desc.hpp
*  @brief Process description for ht_8UC3 to y
***********************************************************************************/
 
#include <acf_process_desc_apu.hpp>
#include "ht_8uc3_to_y_graph.hpp"

class ht_8uc3_to_y_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "HT_8UC3_TO_Y");
   }
   
   ht_8UC3_to_y_graph mGraph;
};