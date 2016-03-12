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
*  @file interp_bilinear_grayscale_graph.hpp
*  @brief ACF graph for bilinear grayscale 08u interpolation
***********************************************************************************/

#ifndef INTERP_BILINEAR_GRAYSCALE_GRAPH_HPP
#define INTERP_BILINEAR_GRAYSCALE_GRAPH_HPP

#include <acf_graph.hpp>
#include "interpolation_kernels.h"
#include "graph_templates.h"

class interp_bilinear_grayscale_graph : public ACF_Graph
{
public:
	interp_bilinear_grayscale_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(INTERP_BILIN_GRAYSC_K);
#endif
	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("bilinear_grayscale_graph");
      
      //add kernels
	  AddKernel("_interp_bilinear_grayscale", INTERP_BILIN_GRAYSC_KN);

      //add graph ports
      AddInputPort(GR_IN_0);
      AddInputPort("DELTA_XY");
      AddOutputPort(GR_OUT_0);

      //specify connections
      Connect(GraphPort(GR_IN_0),    KernelPort("_interp_bilinear_grayscale", INPUT_0));
      Connect(GraphPort("DELTA_XY"),   KernelPort("_interp_bilinear_grayscale", DELTA_XY));
      Connect(KernelPort("_interp_bilinear_grayscale", OUTPUT_0), GraphPort(GR_OUT_0));
   }
};

#endif
