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
*  @file rgb565_to_rgb888_graph.hpp
*  @brief ACF graph for rgb565 to rgb888
***********************************************************************************/
#ifndef RGB565_TO_RGB888_GRAPH_HPP
#define RGB565_TO_RGB888_GRAPH_HPP

#include <acf_graph.hpp>
#include "color_conversion_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"


class rgb565_to_rgb888_graph : public ACF_Graph
{
public:
	rgb565_to_rgb888_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(RGB565_TO_RGB888_K);
#endif
	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("rgb565_to_rgb888_graph");
      
      //add kernels
      AddKernel("_rgb565_to_rgb888", RGB565_TO_RGB888_KN);

      //add graph ports
      AddInputPort(GR_IN_0);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_rgb565_to_rgb888", INPUT_0));
      Connect(KernelPort("_rgb565_to_rgb888", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
