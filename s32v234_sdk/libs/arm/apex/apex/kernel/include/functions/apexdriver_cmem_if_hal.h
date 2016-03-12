/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2011 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#ifndef _CMEM_IF_HAL_H_
#define _CMEM_IF_HAL_H_

#include "apex_cmem_if_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void            apexdriver_cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg);
CMEM_IF_APU_CFG apexdriver_cmem_if_hal_query_apu_cfg(int lApexID);
void            apexdriver_cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address);
void            apexdriver_cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address);
uint32_t        apexdriver_cmem_if_hal_query_apu_pmem_start(int lApexID, int32_t apuid);
uint32_t        apexdriver_cmem_if_hal_query_apu_dmem_start(int lApexID, int32_t apuid);
uint32_t        apexdriver_cmem_if_hal_query_cu_array_width(int lApexID, int32_t apuid);

#ifdef __cplusplus
}
#endif

#endif //_CMEM_IF_HAL_H_
