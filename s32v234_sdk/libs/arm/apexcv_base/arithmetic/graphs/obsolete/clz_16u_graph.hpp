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
*  @file clz_16u_graph.hpp
*  @brief ACF graph for count leading zeros (unsigned 16-bit)
***********************************************************************************/
#ifndef CLZ_16U_GRAPH_HPP
#define CLZ_16U_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"

class clz_16u_graph : public ACF_Graph
{
public:
	clz_16u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(CLZ_16u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("clz_16u_graph");
      
      //add kernels
      AddKernel("_clz_16u", CLZ_16u_KN);

      //add graph ports
      AddInputPort(GR_IN_0);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_clz_16u", GR_IN_0));
      Connect(KernelPort("_clz_16u", GR_OUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
