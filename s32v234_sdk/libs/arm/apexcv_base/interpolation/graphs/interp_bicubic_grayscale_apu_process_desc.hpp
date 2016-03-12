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
*  @file bicubic_proc_desc.hpp
*  @brief Process description for bicubic interpolation
***********************************************************************************/
 
#include <acf_process_desc_apu.hpp>
#include "interp_bicubic_grayscale_graph.hpp"

class interp_bicubic_grayscale_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "INTERP_BICUBIC_GRAYSCALE");
   }
   
   interp_bicubic_grayscale_graph mGraph;
};