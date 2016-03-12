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
*  @file and_16u_graph.hpp
*  @brief ACF graph for bitwise and (unsigned 16 bit)
***********************************************************************************/
#ifndef AND_16U_GRAPH_HPP
#define AND_16U_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"

class and_16u_graph : public ACF_Graph
{
public:
	and_16u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(AND_16u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("and_16u_graph");
      
      //add kernels
      AddKernel("_and_16u", AND_16u_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_IN_1);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_and_16u", GR_IN_0));
      Connect(GraphPort(GR_IN_1),   KernelPort("_and_16u", GR_IN_1));
      Connect(KernelPort("_and_16u", GR_OUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
