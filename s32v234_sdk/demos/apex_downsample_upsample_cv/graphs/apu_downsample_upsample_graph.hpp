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
#include <acf_graph.hpp>

class apu_downsample_upsample_graph : public ACF_Graph
{
public:

   void Create()
   {
      //set identifier for graph
      SetIdentifier("apu_downsample_upsample_graph");

      //add kernels
      AddKernel("downsample_0", "apu_downsample");
      AddKernel("upsample_0", "apu_upsample");

      //add graph ports
      AddInputPort("INPUT");
      AddOutputPort("OUTPUT_DOWN");
      AddOutputPort("OUTPUT_UP");

      //specify connections
      Connect(GraphPort("INPUT"), KernelPort("downsample_0", "INPUT_0"));
      Connect(KernelPort("downsample_0", "OUTPUT_0"), GraphPort("OUTPUT_DOWN"));
      Connect(GraphPort("INPUT"), KernelPort("upsample_0", "INPUT_0"));
      Connect(KernelPort("upsample_0", "OUTPUT_0"), GraphPort("OUTPUT_UP"));
   }
};
