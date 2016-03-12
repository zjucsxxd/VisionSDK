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
*  @file integral_image_graph.hpp
*  @brief ACF graph for integral image
***********************************************************************************/
#ifndef INTEGRAL_IMAGE_GRAPH_HPP
#define INTEGRAL_IMAGE_GRAPH_HPP

#include <acf_graph.hpp>
#include "integral_image_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
class integral_image_graph : public ACF_Graph
{
public:
	integral_image_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(INTEGRAL_IMAGE_K);
#endif

	}   void Create()
   {
      //set identifier for graph
      SetIdentifier("integral_image_graph");
      
      //add kernels
      AddKernel("_integral_image", INTEGRAL_IMAGE_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_integral_image", INPUT_0));
      Connect(KernelPort("_integral_image", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif