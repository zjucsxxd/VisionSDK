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
#ifndef APU_MATCH_DESCRIPTORS_HPP
#define APU_MATCH_DESCRIPTORS_HPP

#include <acf_graph.hpp>

#ifdef APEX2_EMULATE
using namespace APEX2;
#endif

#include "apu_match_descriptors_graph.h"
#include "apu_match_descriptors.h"

class apu_match_descriptors_graph : public ACF_Graph
{
public:
	apu_match_descriptors_graph()
		: ACF_Graph()
	{
#ifdef APEX2_EMULATE
		XREGISTER_ACF_KERNEL(MATCH_DESCRIPTORS_K);
#endif
	}

  void Create()
  {
    //set identifier for graph
    SetIdentifier("apu_match_descriptors_graph");

    //add kernels
	AddKernel("match_descriptors_0", MATCH_DESCRIPTORS_KN);

    //add graph ports
    AddInputPort(MATCH_DESCR_GR_IN0);
    AddInputPort(MATCH_DESCR_GR_IN1);
    AddInputPort(MATCH_DESCR_GR_CFG);
    AddOutputPort(MATCH_DESCR_GR_OUT0);
    AddOutputPort(MATCH_DESCR_GR_OUT1);

    //specify connections
    Connect(GraphPort(MATCH_DESCR_GR_IN0), KernelPort("match_descriptors_0", MATCH_DESCR_KN_IN0));
	Connect(GraphPort(MATCH_DESCR_GR_IN1), KernelPort("match_descriptors_0", MATCH_DESCR_KN_IN1));
	Connect(GraphPort(MATCH_DESCR_GR_CFG), KernelPort("match_descriptors_0", MATCH_DESCR_KN_CFG));
	Connect(KernelPort("match_descriptors_0", MATCH_DESCR_KN_OUT0), GraphPort(MATCH_DESCR_GR_OUT0));
	Connect(KernelPort("match_descriptors_0", MATCH_DESCR_KN_OUT1), GraphPort(MATCH_DESCR_GR_OUT1));
  }
};

#endif