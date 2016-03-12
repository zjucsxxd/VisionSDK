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

#include "../../../kernel/include/linux/apexdriver_ioctl.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

void cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg)
{
    apexdriver_cmem_if_hal_set_apu_cfg(lApexID, lApuCfg);
}

void cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address)
{
    apexdriver_cmem_if_hal_set_apu_pmem_start(lApexID, apuid, address);
}

void cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address)
{
    apexdriver_cmem_if_hal_set_apu_dmem_start(lApexID, apuid, address);
}

