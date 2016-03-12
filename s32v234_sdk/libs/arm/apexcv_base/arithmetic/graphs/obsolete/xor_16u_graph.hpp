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
*  @file xor_16u_graph.hpp
*  @brief ACF graph for bitwise xor (unsigned 16 bit)
***********************************************************************************/
#ifndef XOR_16U_GRAPH_HPP
#define XOR_16U_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"
#include<acf_graph.hpp>
#include "graph_templates.h"

class xor_16u_graph : public ACF_Graph
{
public:
	xor_16u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(XOR_16u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("xor_16u_graph");
      
      //add kernels
      AddKernel("_xor_16u", XOR_16u_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_IN_1);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_xor_16u", INPUT_0));
	  Connect(GraphPort(GR_IN_1), KernelPort("_xor_16u", INPUT_1));
      Connect(KernelPort("_xor_16u", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};
#endif
