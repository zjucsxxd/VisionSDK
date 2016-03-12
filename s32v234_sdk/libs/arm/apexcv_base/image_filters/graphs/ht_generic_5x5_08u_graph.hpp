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
*  @file ht_generic_5x5_08u_graph.hpp
*  @brief ACF graph for hand-tuned generic 5x5 filter
***********************************************************************************/
 
#ifndef HT_GENERIC_5X5_08U_GRAPH_HPP
#define HT_GENERIC_5X5_08U_GRAPH_HPP

#include <acf_graph.hpp>
#include "filter_kernels.h"
#include "graph_templates.h"

class ht_generic_5x5_08u_graph : public ACF_Graph
{
public:
	ht_generic_5x5_08u_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(HT_GENERIC_5X5_08U_K);
#endif

	}
   void Create()
   {
      //set identifier for graph
      SetIdentifier("ht_generic_5x5_08u_graph");
      
      //add kernels
      AddKernel("_ht_generic_5x5_08u", HT_GENERIC_5X5_08U_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_F_COEFF);
      AddInputPort(GR_F_SCALE);
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_ht_generic_5x5_08u", INPUT_0));
      Connect(GraphPort(GR_F_COEFF),   KernelPort("_ht_generic_5x5_08u", "F_COEFF"));
      Connect(GraphPort(GR_F_SCALE),   KernelPort("_ht_generic_5x5_08u", "F_SCALE"));
      Connect(KernelPort("_ht_generic_5x5_08u", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};
#endif
