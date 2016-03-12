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

#include <INTEGRITY.h>
#include "../../../kernel/include/integrity/apexdriver_iodev.h"

#include <stdio.h>

void cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE params;
  params.io_id = APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG;
  params.lApexID = lApexID;
  params.lApuCfg = lApuCfg;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (cmem_if_hal_set_apu_cfg). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

void cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  
  APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE params;
  params.io_id = APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START;
  params.lApexID = lApexID;
  params.apuid = apuid;
  params.address = address;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (cmem_if_hal_set_apu_pmem_start). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

void cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  
  APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE params;
  params.io_id = APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START;
  params.lApexID = lApexID;
  params.apuid = apuid;
  params.address = address;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (cmem_if_hal_set_apu_dmem_start). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

