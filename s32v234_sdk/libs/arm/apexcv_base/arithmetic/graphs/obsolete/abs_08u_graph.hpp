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
*  @file abs_08u_graph.hpp
*  @brief ACF graph for absolute difference
***********************************************************************************/

#ifndef ABS_08u_GRAPH_HPP
#define ABS_08u_GRAPH_HPP

#include <acf_graph.hpp>
#include "arithmetic_kernels.h"

class abs_08u_graph : public ACF_Graph
{
public:
	abs_08u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ABS_08u_K);
#endif

	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("abs_graph");
      
      //add kernels
	  AddKernel("_abs_08u", ABS_08u_KN);

      //add graph ports
      AddInputPort(GR_IN_0);

      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_abs_08u", GR_IN_0));
      Connect(KernelPort("_abs_08u", GR_OUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
