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
*  @file ht_separable_3x3_16s_graph.hpp
*  @brief ACF graph for hand-tuned separable 3x3 filter
***********************************************************************************/
 
#ifndef HT_SEPARABLE_3X3_16S_GRAPH_HPP
#define HT_SEPARABLE_3X3_16S_GRAPH_HPP

#include <acf_graph.hpp>
#include "filter_kernels.h"
#include "graph_templates.h"

class ht_separable_3x3_16s_graph : public ACF_Graph
{
public:
	ht_separable_3x3_16s_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(HT_SEPARABLE_3X3_16S_K);
#endif

	}
   void Create()
   {
      //set identifier for graph
      SetIdentifier("ht_separable_3x3_16s_graph");
      
      //add kernels
      AddKernel("_ht_separable_3x3_16s", HT_SEPARABLE_3X3_16S_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort(GR_F_ROW);
      AddInputPort(GR_F_COL);
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),   KernelPort("_ht_separable_3x3_16s", INPUT_0));
      Connect(GraphPort(GR_F_ROW),     KernelPort("_ht_separable_3x3_16s", F_ROW));
      Connect(GraphPort(GR_F_COL),     KernelPort("_ht_separable_3x3_16s", F_COL));
      Connect(KernelPort("_ht_separable_3x3_16s", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};
#endif
