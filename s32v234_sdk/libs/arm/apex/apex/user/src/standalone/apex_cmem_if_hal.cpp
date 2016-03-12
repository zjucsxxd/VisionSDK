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

#include "apexdriver_cmem_if_hal.h"

void cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg)
{
	apexdriver_cmem_if_hal_set_apu_cfg(lApexID, lApuCfg);
}

CMEM_IF_APU_CFG cmem_if_hal_query_apu_cfg(int lApexID)
{
	return apexdriver_cmem_if_hal_query_apu_cfg(lApexID);
}

void cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address)
{
	apexdriver_cmem_if_hal_set_apu_pmem_start(lApexID, apuid, address);
}

void cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address)
{
	apexdriver_cmem_if_hal_set_apu_dmem_start(lApexID, apuid, address);
}

uint32_t cmem_if_hal_query_apu_pmem_start(int lApexID, int32_t apuid)
{
	return apexdriver_cmem_if_hal_query_apu_pmem_start(lApexID, apuid);
}

uint32_t cmem_if_hal_query_apu_dmem_start(int lApexID, int32_t apuid)
{
	return apexdriver_cmem_if_hal_query_apu_dmem_start(lApexID, apuid);
}

uint32_t cmem_if_hal_query_cu_array_width(int lApexID, int32_t apuid)
{
	return apexdriver_cmem_if_hal_query_cu_array_width(lApexID, apuid);
}

