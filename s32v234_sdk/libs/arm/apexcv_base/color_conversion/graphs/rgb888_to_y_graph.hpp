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
*  @file rgb888_to_y_graph.hpp
*  @brief ACF graph for rgb888 to y
***********************************************************************************/

#ifndef RGB888_TO_Y_GRAPH_HPP
#define RGB888_TO_Y_GRAPH_HPP

#include <acf_graph.hpp>
#include "color_conversion_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
class rgb888_to_y_graph : public ACF_Graph
{
public:
	rgb888_to_y_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(RGB888_TO_Y_K);
#endif
	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("rgb888_to_y_graph");
      
      //add kernels
      AddKernel("_rgb888_to_y", RGB888_TO_Y_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort("R2Y");
      AddInputPort("G2Y");
      AddInputPort("B2Y");			
	
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_rgb888_to_y", "INPUT_0"));
      Connect(GraphPort("R2Y"),           KernelPort("_rgb888_to_y", "R2Y"));
      Connect(GraphPort("G2Y"),           KernelPort("_rgb888_to_y", "G2Y"));
      Connect(GraphPort("B2Y"),           KernelPort("_rgb888_to_y", "B2Y"));			
      Connect(KernelPort("_rgb888_to_y", GR_OUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
