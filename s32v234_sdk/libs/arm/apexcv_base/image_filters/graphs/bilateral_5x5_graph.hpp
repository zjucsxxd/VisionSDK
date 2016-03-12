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
*  @file bilateral_5x5_graph.hpp
*  @brief ACF graph for bilateral 5x5 filter
***********************************************************************************/
#ifndef BILATERAL_5X5_GRAPH_HPP
#define BILATERAL_5X5_GRAPH_HPP

#include <acf_graph.hpp>
#include "filter_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"

class  bilateral_5x5_graph: public ACF_Graph
{
public:
	bilateral_5x5_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(BILATERAL_5X5_K);
#endif

	}
   void Create()
   {
      //set identifier for graph
      SetIdentifier("bilateral_5x5_graph");
      
      //add kernels
      AddKernel("_bilateral_5x5", BILATERAL_5X5_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort("SIGMA_R");
      AddInputPort("SIGMA_D");
	  //AddOutputPort("R_LUT");
	  //AddOutputPort("D_LUT");
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),	KernelPort("_bilateral_5x5", INPUT_0));
	  Connect(GraphPort("SIGMA_D"), KernelPort("_bilateral_5x5", SIGMA_D));
      Connect(GraphPort("SIGMA_R"), KernelPort("_bilateral_5x5", SIGMA_R));

	  //Connect(KernelPort("_bilateral_5x5", R_LUT),		GraphPort("R_LUT"));
	  //Connect(KernelPort("_bilateral_5x5", D_LUT),		GraphPort("D_LUT"));
      Connect(KernelPort("_bilateral_5x5", OUTPUT_0),	GraphPort(GR_OUT_0));
   }
};
#endif

