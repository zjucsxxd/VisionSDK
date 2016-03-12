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
*  @file add_08u_graph.hpp
*  @brief ACF graph for add (unsigned 8 bit)
***********************************************************************************/
#ifndef ADD_08U_GRAPH_HPP
#define ADD_08U_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic.h"

class add_08u_graph : public ACF_Graph
{
public:
	add_08u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ADD_08u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("add_08u_graph");
      
      //add kernels
      AddKernel("_add_08u", ADD_08u_KN);

      //add graph ports
      AddInputPort("INPUT_0");
      AddInputPort("INPUT_1");

      AddOutputPort("OUTPUT_0");

      //specify connections
      Connect(GraphPort("INPUT_0"),   KernelPort("_add_08u", "INPUT_0"));
      Connect(GraphPort("INPUT_1"),   KernelPort("_add_08u", "INPUT_1"));
      Connect(KernelPort("_add_08u", "OUTPUT_0"), GraphPort("OUTPUT_0"));
   }
};

#endif
