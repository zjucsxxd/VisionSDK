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
#ifndef APU_apexcv_GRAPPH_HPP
#define APU_apexcv_GRAPPH_HPP


#ifdef APEX2_EMULATE
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include "apu_apexcv_graph.h"
#include "arithmetic.h"

#include "acf_graph.hpp"

class apu_apexcv_graph : public ACF_Graph
{
public:
	const char* m_graphName;
public:
	apu_apexcv_graph()
		: ACF_Graph()
		, m_graphName(apexcv_GN)
	{
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ADD_08u_K); // this works only if the corresponding KERNEL_INFO structure has been defined with: extKernelInfoDecl(apexcv_K);
#endif
	}
	
	void Create()
    {
      //set identifier for graph
      SetIdentifier("apu_apexcv_graph");
      
      //apexcv kernels
	  std::string apexcv_kernel_instance("apexcv_kernel_0");
	  AddKernel(apexcv_kernel_instance, ADD_08u_KN);

      //apexcv graph ports

      AddInputPort(apexcv_GRAPH_INA);
      AddInputPort(apexcv_GRAPH_INB);
      AddOutputPort(apexcv_GRAPH_OUT);

      //specify connections
	  Connect(GraphPort(apexcv_GRAPH_INA), KernelPort(apexcv_kernel_instance, INPUT_0));
	  Connect(GraphPort(apexcv_GRAPH_INB), KernelPort(apexcv_kernel_instance, INPUT_1));
	  Connect(KernelPort(apexcv_kernel_instance, OUTPUT_0), GraphPort(apexcv_GRAPH_OUT));	       
   }
};


#endif