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

class ldws_graph : public ACF_Graph
{
public:

   void Create()
   {
      //set identifier for graph
      SetIdentifier("ldws_remap_sobel_median");

      //add kernels
      AddKernel("myRemap",  "remap_bilinear_grayscale"); // yuv once implemented
      AddKernel("mySobel",  "sobel_3x3_8bpp");
      AddKernel("myMedian", "median_3x3_8bpp");

      //add graph ports
      AddInputPort("SRC_IMG");
      AddInputPort("LOCAL_OFFSET");
      AddInputPort("DELTA");
      AddOutputPort("DST_IMG");

      //specify connections
      Connect(GraphPort("SRC_IMG"), KernelPort("myRemap", "SRC"));
      Connect(GraphPort("LOCAL_OFFSET"), KernelPort("myRemap", "OFFSET"));
      Connect(GraphPort("DELTA"), KernelPort("myRemap", "DELTA"));
      Connect(KernelPort("myRemap", "DST"), KernelPort("mySobel", "SRC"));
      Connect(KernelPort("mySobel", "DST"), KernelPort("myMedian", "SRC"));
      Connect(KernelPort("myMedian", "DST"), GraphPort("DST_IMG"));
   }
};
