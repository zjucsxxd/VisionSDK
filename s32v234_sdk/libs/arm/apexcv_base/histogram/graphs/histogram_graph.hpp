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
*  @file histogram_graph.hpp
*  @brief ACF graph for histogram
***********************************************************************************/
#ifndef HISTOGRAM_GRAPH_HPP
#define HISTOGRAM_GRAPH_HPP

#include <acf_graph.hpp>
#include "histogram_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"

class histogram_graph : public ACF_Graph
{
public:
	histogram_graph()
		: ACF_Graph()
	{
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(HISTOGRAM_K)
#endif
	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("histogram_graph");
      
      //add kernels
      AddKernel("_histogram", HISTOGRAM_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_histogram", INPUT_0));
      Connect(KernelPort("_histogram", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
