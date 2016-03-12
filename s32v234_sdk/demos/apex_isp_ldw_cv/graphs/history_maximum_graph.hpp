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

class history_maximum_ldws_graph : public ACF_Graph
{
public:

   void Create()
   {
      //set identifier for graph
      SetIdentifier("history_maximum");

      //add kernels
      AddKernel("max1",  "apu_max");
      AddKernel("max2",  "apu_max");
      AddKernel("max3",  "apu_max");
      AddKernel("max4",  "apu_max");
      AddKernel("max5",  "apu_max");
      AddKernel("max6",  "apu_max");
      AddKernel("max7",  "apu_max");
      AddKernel("max8",  "apu_max");
      AddKernel("max9",  "apu_max");
      AddKernel("max10", "apu_max");
      AddKernel("max11", "apu_max");
      AddKernel("max12", "apu_max");
      AddKernel("max13", "apu_max");
      AddKernel("max14", "apu_max");

      //add graph ports
      AddInputPort("SRC_0");
      AddInputPort("SRC_1");
      AddInputPort("SRC_2");
      AddInputPort("SRC_3");
      AddInputPort("SRC_4");
      AddInputPort("SRC_5");
      AddInputPort("SRC_6");
      AddInputPort("SRC_7");
      AddInputPort("SRC_8");
      AddInputPort("SRC_9");
      AddInputPort("SRC_10");
      AddInputPort("SRC_11");
      AddInputPort("SRC_12");
      AddInputPort("SRC_13");
      AddInputPort("SRC_14");
      AddOutputPort("DST_IMG");

      //specify connections
      Connect(GraphPort("SRC_1"),  KernelPort("max1",  "INPUT_1"));
      Connect(GraphPort("SRC_2"),  KernelPort("max2",  "INPUT_1"));
      Connect(GraphPort("SRC_3"),  KernelPort("max3",  "INPUT_1"));
      Connect(GraphPort("SRC_4"),  KernelPort("max4",  "INPUT_1"));
      Connect(GraphPort("SRC_5"),  KernelPort("max5",  "INPUT_1"));
      Connect(GraphPort("SRC_6"),  KernelPort("max6",  "INPUT_1"));
      Connect(GraphPort("SRC_7"),  KernelPort("max7",  "INPUT_1"));
      Connect(GraphPort("SRC_8"),  KernelPort("max8",  "INPUT_1"));
      Connect(GraphPort("SRC_9"),  KernelPort("max9",  "INPUT_1"));
      Connect(GraphPort("SRC_10"), KernelPort("max10", "INPUT_1"));
      Connect(GraphPort("SRC_11"), KernelPort("max11", "INPUT_1"));
      Connect(GraphPort("SRC_12"), KernelPort("max12", "INPUT_1"));
      Connect(GraphPort("SRC_13"), KernelPort("max13", "INPUT_1"));
      Connect(GraphPort("SRC_14"), KernelPort("max14", "INPUT_1"));
      Connect(GraphPort("SRC_0"),  KernelPort("max1",  "INPUT_0"));
      
      Connect(KernelPort("max1",  "OUTPUT_0"), KernelPort("max2",  "INPUT_0"));
      Connect(KernelPort("max2",  "OUTPUT_0"), KernelPort("max3",  "INPUT_0"));
      Connect(KernelPort("max3",  "OUTPUT_0"), KernelPort("max4",  "INPUT_0"));
      Connect(KernelPort("max4",  "OUTPUT_0"), KernelPort("max5",  "INPUT_0"));
      Connect(KernelPort("max5",  "OUTPUT_0"), KernelPort("max6",  "INPUT_0"));
      Connect(KernelPort("max6",  "OUTPUT_0"), KernelPort("max7",  "INPUT_0"));
      Connect(KernelPort("max7",  "OUTPUT_0"), KernelPort("max8",  "INPUT_0"));
      Connect(KernelPort("max8",  "OUTPUT_0"), KernelPort("max9",  "INPUT_0"));
      Connect(KernelPort("max9",  "OUTPUT_0"), KernelPort("max10", "INPUT_0"));
      Connect(KernelPort("max10", "OUTPUT_0"), KernelPort("max11", "INPUT_0"));
      Connect(KernelPort("max11", "OUTPUT_0"), KernelPort("max12", "INPUT_0"));
      Connect(KernelPort("max12", "OUTPUT_0"), KernelPort("max13", "INPUT_0"));
      Connect(KernelPort("max13", "OUTPUT_0"), KernelPort("max14", "INPUT_0"));
      Connect(KernelPort("max14", "OUTPUT_0"), GraphPort("DST_IMG"));
   }
};
