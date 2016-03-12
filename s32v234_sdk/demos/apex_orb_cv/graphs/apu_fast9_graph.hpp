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
#ifndef APU_FAST9_GRAPH_HPP
#define APU_FAST9_GRAPH_HPP

#include <acf_graph.hpp>

#ifdef APEX2_EMULATE
using namespace APEX2;
#endif

#include "apu_fast9.h"
#include "apu_gauss_3x3.h"
#include "apu_nms.h"
#include "apu_fast9_graph.h"

class apu_fast9_graph : public ACF_Graph
{
public:
	apu_fast9_graph()
		: ACF_Graph()
	{

#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(FAST9_K);
		XREGISTER_ACF_KERNEL(NMS_K);
		XREGISTER_ACF_KERNEL(GAUSS_3x3_K)
#endif
	}

   void Create()
   {
      //set identifier for graph
      SetIdentifier("apu_fast9_graph");

      //add kernels
	  AddKernel("gauss_3x3_0", GAUSS_3x3_KN);
	  AddKernel("fast9_0", FAST9_KN);
	  AddKernel("nms_0", NMS_KN);

      //add graph ports
	  AddInputPort(FAST9_GR_IN0);
	  AddInputPort(FAST9_GR_IN1);
	  AddOutputPort(FAST9_GR_OUT0);
	  AddOutputPort(FAST9_GR_OUT1);

      //specify connections
	  Connect(GraphPort(FAST9_GR_IN0), KernelPort("gauss_3x3_0", GAUSS_3x3_KN_IN));
	  Connect(GraphPort(FAST9_GR_IN1), KernelPort("fast9_0", FAST9_KN_IN1));
      Connect(KernelPort("gauss_3x3_0", GAUSS_3x3_KN_OUT), KernelPort("fast9_0", FAST9_KN_IN0));
      Connect(KernelPort("fast9_0", FAST9_KN_OUT), KernelPort("nms_0", NMS16_KN_IN));
	  Connect(KernelPort("nms_0", NMS16_KN_OUT), GraphPort(FAST9_GR_OUT0));
	  Connect(KernelPort("gauss_3x3_0", GAUSS_3x3_KN_OUT), GraphPort(FAST9_GR_OUT1));
   }
};

#endif
