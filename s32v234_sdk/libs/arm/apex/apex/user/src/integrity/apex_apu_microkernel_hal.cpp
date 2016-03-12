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

int apumk_hal_host_com_rx(int apexID, int apuid, int32_t* msg)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE params;
  params.io_id = APEXDRIVER_APUMK_HAL_HOST_COM_RX;
  params.apexID = apexID;
  params.apuid = apuid;
  params.msg = msg;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apumk_hal_host_com_rx). Operation not executed.\n");
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

int apumk_hal_host_com_tx(int apexID, int apuid, int32_t  msg)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE params;
  params.io_id = APEXDRIVER_APUMK_HAL_HOST_COM_TX;
  params.apexID = apexID;
  params.apuid = apuid;
  params.msg = msg;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apumk_hal_host_com_tx). Operation not executed.\n");
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

int apumk_hal_send_cmd(int apexID, int32_t apu_id, int32_t kernel_id, int32_t num_params, const int32_t* param_list)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE params;
  params.io_id = APEXDRIVER_APUMK_HAL_SEND_CMD;
  params.apexID = apexID;
  params.apu_id = apu_id;
  params.kernel_id = kernel_id;
  params.num_params = num_params;
  params.param_list = param_list;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apumk_hal_send_cmd). Operation not executed.\n");
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


