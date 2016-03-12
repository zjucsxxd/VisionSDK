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
*  @file accumulate_squared_16s_graph.hpp
*  @brief ACF graph for accumulate squared (unsigned 16 bit)
***********************************************************************************/
#ifndef ACCUMULATE_16S_SQUARED_GRAPH_HPP
#define ACCUMULATE_16S_SQUARED_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"

class accumulate_squared_16s_graph : public ACF_Graph
{
public:
	accumulate_squared_16s_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ACCUM_SQRD_16s_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("accumulate_squared_16s_graph");
      
      //add kernels
      AddKernel("_accumulate_squared_16s", ACCUM_SQRD_16s_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_IN_1);
      AddInputPort(GR_ALPHA);
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_accumulate_squared_16s", GR_IN_0));
      Connect(GraphPort(GR_IN_1),   KernelPort("_accumulate_squared_16s", GR_IN_1));
      Connect(GraphPort(GR_ALPHA),     KernelPort("_accumulate_squared_16s", GR_ALPHA));
      Connect(KernelPort("_accumulate_squared_16s", GR_OUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
