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
*  @file ht_8UC3_to_y_graph.hpp
*  @brief ACF graph for ht_8UC3 to y
***********************************************************************************/

#include <acf_graph.hpp>
#include "color_conversion_kernels.h"

class ht_8UC3_to_y_graph : public ACF_Graph
{
public:
	ht_8UC3_to_y_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(HT_8UC3_TO_Y_K);
#endif

	}
   void Create()
   {
      //set identifier for graph
      SetIdentifier("ht_8UC3_to_y_graph");

      //add kernels
      AddKernel("_ht_8UC3_to_y", HT_8UC3_TO_Y_KN);

      //add graph ports
      AddInputPort("INPUT_0");
      AddInputPort("KA");
      AddInputPort("KB");
      AddInputPort("KC");
      AddInputPort("KR");
      AddOutputPort("OUTPUT_0");

      //specify connections
      Connect(GraphPort("INPUT_0"),   KernelPort("_ht_8UC3_to_y", "INPUT_0"));
      Connect(GraphPort("KA"),        KernelPort("_ht_8UC3_to_y", "KA"));
      Connect(GraphPort("KB"),        KernelPort("_ht_8UC3_to_y", "KB"));
      Connect(GraphPort("KC"),        KernelPort("_ht_8UC3_to_y", "KC"));
      Connect(GraphPort("KR"),        KernelPort("_ht_8UC3_to_y", "KR"));
      Connect(KernelPort("_ht_8UC3_to_y", "OUTPUT_0"), GraphPort("OUTPUT_0"));
   }
};