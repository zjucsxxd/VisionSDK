/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2012 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

// Include files.
#ifndef apex_GLOBAL_HAL_HPP___
#define apex_GLOBAL_HAL_HPP___

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

int global_hal_AllReset(int apexID);
int global_hal_uSequencerReset(int apexID);
int global_hal_MotCmpDmaReset(int apexID);
int global_hal_CmemDmaReset(int apexID);
int global_hal_cmemIFReset(int apexID);
int global_hal_DmaReset(int apexID);
int global_hal_Apu0Reset(int apexID);
int global_hal_Apu1Reset(int apexID);
int global_hal_Vu0Reset(int apexID);
int global_hal_Vu1Reset(int apexID);
int global_hal_HrszReset(int apexID);
int global_hal_Dmem0Reset(int apexID);
int global_hal_Dmem1Reset(int apexID);
int global_hal_Apu0Enable(int apexID);
int global_hal_Apu1Enable(int apexID);
int global_hal_Apu0Disable(int apexID);
int global_hal_Apu1Disable(int apexID);
int global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit);
int global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit);
int global_hal_isApex2GlobalInterruptEnabled(int apexID, APEX2_INTERRUPT_BITS intBit);
int global_hal_Apex2GlobalInterruptStatus(int apexID, APEX2_INTERRUPT_BITS intBit);
LIB_RESULT global_hal_Apex2GlobalInterruptPolling(int apexID, APEX2_INTERRUPT_BITS intBit);

int global_hal_RetHwVersion(int apexID);
int global_hal_RetSwVersion(int apexID);

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_HAL_HPP___
