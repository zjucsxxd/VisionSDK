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
#ifndef GLOBAL_HAL_HPP___
#define GLOBAL_HAL_HPP___

#include "apex_global_hal.h"

#ifdef __cplusplus
extern "C" {
#endif


int apexdriver_global_hal_AllReset(int apexID);
int apexdriver_global_hal_uSequencerReset(int apexID);
int apexdriver_global_hal_MotCmpDmaReset(int apexID);
int apexdriver_global_hal_CmemDmaReset(int apexID);
int apexdriver_global_hal_cmemIFReset(int apexID);
int apexdriver_global_hal_DmaReset(int apexID);
int apexdriver_global_hal_Apu0Reset(int apexID);
int apexdriver_global_hal_Apu1Reset(int apexID);
int apexdriver_global_hal_Vu0Reset(int apexID);
int apexdriver_global_hal_Vu1Reset(int apexID);
int apexdriver_global_hal_HrszReset(int apexID);
int apexdriver_global_hal_Dmem0Reset(int apexID);
int apexdriver_global_hal_Dmem1Reset(int apexID);
int apexdriver_global_hal_Apu0Enable(int apexID);
int apexdriver_global_hal_Apu1Enable(int apexID);
int apexdriver_global_hal_Apu0Disable(int apexID);
int apexdriver_global_hal_Apu1Disable(int apexID);
int apexdriver_global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit);
int apexdriver_global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit);
int apexdriver_global_hal_isApex2GlobalInterruptEnabled(int apexID, APEX2_INTERRUPT_BITS intBit);
int apexdriver_global_hal_Apex2GlobalInterruptStatus(int apexID, APEX2_INTERRUPT_BITS intBit);
LIB_RESULT apexdriver_global_hal_Apex2GlobalInterruptPolling(int apexID, APEX2_INTERRUPT_BITS intBit);

int apexdriver_global_hal_RetHwVersion(int apexID);
int apexdriver_global_hal_RetSwVersion(int apexID);

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_HAL_HPP___
