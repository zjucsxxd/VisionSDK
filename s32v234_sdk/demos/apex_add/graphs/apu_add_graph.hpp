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
#ifndef APU_ADD_GRAPPH_HPP
#define APU_ADD_GRAPPH_HPP


#ifdef APEX2_EMULATE
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include "apu_add_graph.h"
#include "apu_add.h"

#include "acf_graph.hpp"

class apu_add_graph : public ACF_Graph
{
public:
	const char* m_graphName;
public:
	apu_add_graph()
		: ACF_Graph()
		, m_graphName(ADD_GN)
	{
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(ADD_K); // this works only if the corresponding KERNEL_INFO structure has been defined with: extKernelInfoDecl(ADD_K);
#endif
	}
	
	void Create()
    {
      //set identifier for graph
      SetIdentifier("apu_add_graph");
      
      //add kernels
	  std::string add_kernel_instance("Add_kernel_0");
	  AddKernel(add_kernel_instance, ADD_KN);

      //add graph ports

      AddInputPort(ADD_GRAPH_INA);
      AddInputPort(ADD_GRAPH_INB);
      AddOutputPort(ADD_GRAPH_OUT);

      //specify connections
	  Connect(GraphPort(ADD_GRAPH_INA), KernelPort(add_kernel_instance, ADD_KN_INA));
	  Connect(GraphPort(ADD_GRAPH_INB), KernelPort(add_kernel_instance, ADD_KN_INB));
	  Connect(KernelPort(add_kernel_instance, ADD_KN_OUT), GraphPort(ADD_GRAPH_OUT));	       
   }
};


#endif