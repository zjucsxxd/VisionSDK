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
*  @file bicubic.hpp
*  @brief ACF graph for bicubic 08u interpolation
***********************************************************************************/
 
#include <acf_graph.hpp>
#include "interpolation_kernels.h"
class interp_bicubic_grayscale_graph : public ACF_Graph
{
public:
	interp_bicubic_grayscale_graph() : ACF_Graph() {
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(INTERP_BICUBIC_GRAYSC_K);
#endif
	}
   void Create()
   {
      //set identifier for graph
      SetIdentifier("interp_bicubic_grayscale_graph");

      //add kernels      
	  AddKernel("_interp_bicubic_grayscale", INTERP_BICUBIC_GRAYSC_KN);

      //add graph ports
      AddInputPort("INPUT_0");
      AddInputPort("Y_OFFSET");
      AddInputPort("X_OFFSET");
      AddOutputPort("OUTPUT_0");

      //specify connections
      Connect(GraphPort("INPUT_0"),    KernelPort("_interp_bicubic_grayscale", "INPUT_0"));
      Connect(GraphPort("Y_OFFSET"),   KernelPort("_interp_bicubic_grayscale", "X_OFFSET"));
      Connect(GraphPort("X_OFFSET"),   KernelPort("_interp_bicubic_grayscale", "Y_OFFSET"));
      Connect(KernelPort("_interp_bicubic_grayscale", "OUTPUT_0"), GraphPort("OUTPUT_0"));
   }
};