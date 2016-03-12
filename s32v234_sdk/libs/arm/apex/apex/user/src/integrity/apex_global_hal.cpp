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

#include <INTEGRITY.h>
#include "../../../kernel/include/integrity/apexdriver_iodev.h"

#include <stdio.h>

int global_hal_RetHwVersion(int apexID)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE params;
  params.io_id = APEXDRIVER_GLOBAL_HAL_RETHWVERSION;
  params.apexID = apexID;

  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (global_hal_RetHwVersion). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  
  return params.ret;
}

int global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE params;
  params.io_id = APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE;
  params.apexID = apexID;
  params.intBit = intBit;

  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (global_hal_Apex2GlobalInterruptDisable). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  
  return params.ret;
}

int global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE params;
  params.io_id = APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE;
  params.apexID = apexID;
  params.intBit = intBit;

  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (global_hal_Apex2GlobalInterruptEnable). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  
  return params.ret;
}

