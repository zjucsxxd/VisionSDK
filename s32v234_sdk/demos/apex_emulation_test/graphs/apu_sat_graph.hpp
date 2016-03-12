/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
#ifndef APU_SAT_GRAPH_HPP
#define APU_SAT_GRAPH_HPP

#include <acf_graph.hpp>

#ifdef APEX2_EMULATE
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include "apu_sat_graph.h"
#include "apu_sat_box_filter.h"
#include "apu_sat.h"

class apu_sat_graph : public ACF_Graph
{
public:
	const char* m_graphName;
	
public:
	apu_sat_graph() 
	: ACF_Graph() 
	, m_graphName(SAT_GN)
	{ 
#ifdef APEX2_EMULATE
		// tbd in future with XREGISTER_ACF_KERNEL(KernelName) REGISTER_ACF_KERNEL(kernelInfoConcat(KernelName), KernelName)
		//REGISTER_ACF_KERNEL(_kernel_info_sat, SAT_K);
		//REGISTER_ACF_KERNEL(_kernel_info_sat_box_filter, SAT_BOX_FILTER_K);
		XREGISTER_ACF_KERNEL(SAT_K);
		XREGISTER_ACF_KERNEL(SAT_BOX_FILTER_K);
#endif
	}
	
   virtual void Create()
   {
      //set identifier for graph
      SetIdentifier("apu_sat_graph");

      //add kernels
	  std::string satInst("apu_sat_0");
      AddKernel(satInst, SAT_KN);

	  std::string satBoxFiltInst("apu_sat_box_filter_0");
	  AddKernel(satBoxFiltInst, SAT_BOX_FILTER_KN);

      //add graph ports
      AddInputPort(SAT_GRAPH_IN);
	  AddOutputPort(SAT_GRAPH_OUT);
	  AddOutputPort(SAT_GRAPH_OUT_FILTER);

      //specify connections
      Connect(GraphPort(SAT_GRAPH_IN), KernelPort(satInst, SAT_KN_IN));
	  Connect(KernelPort(satInst, SAT_KN_OUT), KernelPort(satBoxFiltInst, SAT_BOX_FILTER_IN));
	  Connect(KernelPort(satInst, SAT_KN_OUT), GraphPort(SAT_GRAPH_OUT));
	  //Connect(KernelPort(satInst, SAT_KN_OUT_ROW), KernelPort(satBoxFiltInst, "DUMMY_ROW"));
	  Connect(KernelPort(satBoxFiltInst, SAT_BOX_FILTER_OUT ), GraphPort(SAT_GRAPH_OUT_FILTER));
   }
};

#endif
