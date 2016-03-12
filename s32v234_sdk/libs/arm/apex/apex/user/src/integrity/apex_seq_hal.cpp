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
 
/**
 *  \file   seq_hal.h
 *  \brief  Sequencer HAL Driver.
 *
 */

#include <INTEGRITY.h>
#include "../../../kernel/include/integrity/apexdriver_iodev.h"

#include <stdio.h>

int  seq_hal_query_interrupts(int apexID)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE params;
  params.io_id = APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS;
  params.apexID = apexID;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (seq_hal_query_interrupts). Operation not executed.\n");
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

void seq_hal_clear_interrupts(int apexID, int lMask)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE params;
  params.io_id = APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS;
  params.apexID = apexID;
  params.lMask = lMask;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (seq_hal_clear_interrupts). Operation not executed.\n");
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

void seq_hal_mask_interrupts(int apexID, int lMask)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE params;
  params.io_id = APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS;
  params.apexID = apexID;
  params.lMask = lMask;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (seq_hal_mask_interrupts). Operation not executed.\n");
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


