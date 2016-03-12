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
#ifndef APU_CONVOLUTION_GRAPH_HPP
#define APU_CONVOLUTION_GRAPH_HPP

#include <acf_graph.hpp>

#ifdef APEX2_EMULATE
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include "apu_correlation_kernel.h"
#include "apu_convolution_graph.h"

class apu_convolution_graph : public ACF_Graph
{
public:
	const char* m_graphName;
public:
	apu_convolution_graph()
		: ACF_Graph()
		, m_graphName(CONVOLUTION_GN)
	{
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(CORR_K);
#endif
	}
	
   virtual void Create()
   {
      //set identifier for graph
      SetIdentifier("apu_convolution_graph");

	  std::string Conv_Inst_Name("convolution_0");

      //add kernels
	  AddKernel(Conv_Inst_Name, CORR_KN);

      //add graph ports
      AddInputPort(CONVOLUTION_GRAPH_IN);
	  AddInputPort(CONVOLUTION_GRAPH_IN_FILTER);
	  AddOutputPort(CONVOLUTION_GRAPH_OUT);

	  //AddInputPort(CONVOLUTION_GRAPH_FILTER_WIDTH);
	  //AddInputPort(CONVOLUTION_GRAPH_FILTER_HEIGHT);
	  AddInputPort(CONVOLUTION_GRAPH_FILTER_SCALE);
	  AddInputPort(CONVOLUTION_GRAPH_FILTER_SYMMFLG);
      
      //specify connections
	  Connect(GraphPort(CONVOLUTION_GRAPH_IN), KernelPort(Conv_Inst_Name, CORR_Kernel_Input));
	  //output connection
	  Connect(KernelPort(Conv_Inst_Name, CORR_Kernel_Output), GraphPort(CONVOLUTION_GRAPH_OUT));
	  Connect(GraphPort(CONVOLUTION_GRAPH_IN_FILTER), KernelPort(Conv_Inst_Name, CORR_Kernel_Filter));
	  //Connect(GraphPort(CONVOLUTION_GRAPH_FILTER_WIDTH), KernelPort(Conv_Inst_Name, CORR_Kernel_FilterWidth));
	  //Connect(GraphPort(CONVOLUTION_GRAPH_FILTER_HEIGHT), KernelPort(Conv_Inst_Name, CORR_Kernel_FilterHeight));
	  Connect(GraphPort(CONVOLUTION_GRAPH_FILTER_SCALE), KernelPort(Conv_Inst_Name, CORR_Kernel_FilterScale));
	  Connect(GraphPort(CONVOLUTION_GRAPH_FILTER_SYMMFLG), KernelPort(Conv_Inst_Name, CORR_Kernel_FiltSymmFl));
   }
};

#endif
