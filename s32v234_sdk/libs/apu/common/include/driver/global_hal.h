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

// Include files.
#ifndef GLOBAL_HAL_HPP___
#define GLOBAL_HAL_HPP___

#include "global_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
   apu2_rst       8
   apu1_rst       7
   dmem2_rst      6
   dmem1_rst      5
   sequencer_rst  4
   stream_rst     3
   MCdma_rst      2
   multi_dma_rst  1
   cmem_if_rst    0
*/

#define RESET_CMEM_IF               0
#define RESET_DMA                   1
#define RESET_MCE                   2
#define RESET_CMEM_DMA              3
#define RESET_SEQUENCER             4
#define RESET_DMEM_0                5
#define RESET_DMEM_1                6
#define RESET_APU_0                 7
#define RESET_APU_1                 8

typedef enum {

   APEX2_INTERRUPT_MULTI_DMA = 0,
   APEX2_INTERRUPT_MOT_COMP_DMA,
   APEX2_INTERRUPT_SEQUENCER,
   APEX2_INTERRUPT_STREAM_IN_0,
   APEX2_INTERRUPT_STREAM_IN_1,
   APEX2_INTERRUPT_STREAM_IN_2,
   APEX2_INTERRUPT_STREAM_IN_3,
   APEX2_INTERRUPT_STREAM_OUT_0,
   APEX2_INTERRUPT_STREAM_OUT_1,
   APEX2_INTERRUPT_HRSZ_0,
   APEX2_INTERRUPT_HRSZ_1,
   APEX2_INTERRUPT_MAX
   
} APEX2_INTERRUPT_BITS;

typedef enum {

   APEX2_INTERRUPT_DISABLE = 1,
   APEX2_INTERRUPT_ENABLE  = 1

} APEX2_INTERRUPT_MASK;


typedef enum {

   APEX2_APU_DISABLED= 0,
   APEX2_APU_ENBABLED

} APEX2_APU_STATE;

int global_hal_AllReset(void);
int global_hal_uSequencerReset(void);
int global_hal_MotCmpDmaReset(void);
int global_hal_CmemDmaReset(void);
int global_hal_cmemIFReset(void);
int global_hal_DmaReset(void);
int global_hal_Apu0Reset(void);
int global_hal_Apu1Reset(void);
int global_hal_Vu0Reset(void);
int global_hal_Vu1Reset(void);
int global_hal_HrszReset(void);
int global_hal_Dmem0Reset(void);
int global_hal_Dmem1Reset(void);
int global_hal_Apu0Enable(void);
int global_hal_Apu1Enable(void);
int global_hal_Apu0Disable(void);
int global_hal_Apu1Disable(void);
int global_hal_Apex2GlobalInterruptDisable(APEX2_INTERRUPT_BITS intBit);
int global_hal_Apex2GlobalInterruptEnable(APEX2_INTERRUPT_BITS intBit);
bool global_hal_isApex2GlobalInterruptEnabled(APEX2_INTERRUPT_BITS intBit);
int global_hal_Apex2GlobalInterruptStatus(APEX2_INTERRUPT_BITS intBit);
LIB_RESULT global_hal_Apex2GlobalInterruptPolling(APEX2_INTERRUPT_BITS intBit);

int global_hal_RetHwVersion();
int global_hal_RetSwVersion();

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_HAL_HPP___
