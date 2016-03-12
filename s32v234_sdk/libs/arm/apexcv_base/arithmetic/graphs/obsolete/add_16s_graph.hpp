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
*  @file add16s_graph.hpp
*  @brief ACF graph for add (signed 16 bit)
***********************************************************************************/
#ifndef ADD_16S_GRAPH_HPP
#define ADD_16S_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"

class add_16s_graph : public ACF_Graph
{
public:
	add_16s_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ADD_16s_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("add_16s_graph");
      
      //add kernels
      AddKernel("_add_16s", ADD_16s_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort("INPUT_1");

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_add_16s", INPUT_0));
      Connect(GraphPort("INPUT_1"),   KernelPort("_add_16s", INPUT_1));
      Connect(KernelPort("_add_16s", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
