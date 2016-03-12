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
#ifndef ACF_APU_HISTOGRAM_APU_PROCESS_DESC_HPP
#define ACF_APU_HISTOGRAM_APU_PROCESS_DESC_HPP

#ifndef APEX2_EMULATE // This is needed only for the Target Compiler 
#include <acf_process_desc_apu.hpp>
#endif

#include "apu_histogram_graph.hpp"
const int HIST_TILE_SIZE_X = 8;
const int HIST_TILE_SIZE_Y = 8;


class apu_histogram_apu_process_desc : public ACF_Process_Desc_APU
{
public:

   void Create()
   {
      Initialize(mGraph, HISTOGRAM_GN);

	  SetInputChunkSize(HISTOGRAM_GRAPH_IN, HIST_TILE_SIZE_X, HIST_TILE_SIZE_Y);
   }

   apu_histogram_graph mGraph;
};



#endif