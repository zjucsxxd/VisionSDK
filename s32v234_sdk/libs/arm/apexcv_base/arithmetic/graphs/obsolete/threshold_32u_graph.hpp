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
*  @file threshold_32u_graph.hpp
*  @brief ACF graph for thresholding (unsigned 32 bit)
***********************************************************************************/
#ifndef THRESHOLD_32U_GRAPH_HPP
#define THRESHOLD_32U_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"
class threshold_32u_graph : public ACF_Graph
{
public:
	threshold_32u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(THRESH_32u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("threshold_32u_graph");
      
      //add kernels
      AddKernel("_threshold_32u", THRESH_32u_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_IN_1);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_threshold_32u", GR_IN_0));
      Connect(GraphPort(GR_IN_1),   KernelPort("_threshold_32u", GR_IN_1));
      Connect(KernelPort("_threshold_32u", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
