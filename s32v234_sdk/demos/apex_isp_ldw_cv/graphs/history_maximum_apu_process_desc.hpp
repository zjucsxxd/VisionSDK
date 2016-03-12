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
#include <acf_process_desc_apu.hpp>
#include "history_maximum_graph.hpp"

class history_maximum_process_desc : public ACF_Process_Desc_APU
{
public:

   void Create()
   {
      Initialize(m_history_maximum_ldws_graph, "HISTORY_MAXIMUM");
      SetInputChunkSize("SRC_0", 6, 8);
      SetInputChunkSize("SRC_1", 6, 8);
      SetInputChunkSize("SRC_2", 6, 8);
      SetInputChunkSize("SRC_3", 6, 8);
      SetInputChunkSize("SRC_4", 6, 8);
      SetInputChunkSize("SRC_5", 6, 8);
      SetInputChunkSize("SRC_6", 6, 8);
      SetInputChunkSize("SRC_7", 6, 8);
      SetInputChunkSize("SRC_8", 6, 8);
      SetInputChunkSize("SRC_9", 6, 8);
      SetInputChunkSize("SRC_10", 6, 8);
      SetInputChunkSize("SRC_11", 6, 8);
      SetInputChunkSize("SRC_12", 6, 8);
      SetInputChunkSize("SRC_13", 6, 8);
      SetInputChunkSize("SRC_14", 6, 8);
      
      
   }

   history_maximum_ldws_graph m_history_maximum_ldws_graph;
};
