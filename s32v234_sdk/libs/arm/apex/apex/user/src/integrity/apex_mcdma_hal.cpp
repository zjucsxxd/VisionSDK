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

void mcdma_hal_set_memory_fill_words(int apexID, unsigned int FillWord0, unsigned int FillWord1, unsigned int FillWord2, unsigned int FillWord3)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_ENABLE;
  params.apexID = apexID;
  params.FillWord0 = FillWord0;
  params.FillWord1 = FillWord1;
  params.FillWord2 = FillWord2;
  params.FillWord3 = FillWord3;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_set_memory_fill_words). Operation not executed.\n");
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

void mcdma_hal_program_seq_linkedlist (int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE params;
  params.io_id = APEXDRIVER_MCDMA_HAL_SEQ_LL;
  params.apexID = apexID;
  params.ChannelN = ChannelN;
  params.LinkedListAddr = LinkedListAddr;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_program_seq_linkedlist). Operation not executed.\n");
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

void mcdma_hal_start(int apexID, unsigned int ChannelN)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_MCDMA_HAL_START_TYPE params;
  params.io_id = APEXDRIVER_MCDMA_HAL_START;
  params.apexID = apexID;
  params.ChannelN = ChannelN;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_start). Operation not executed.\n");
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

void mcdma_hal_wait(int apexID, unsigned int ChannelN)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_MCDMA_HAL_WAIT_TYPE params;
  params.io_id = APEXDRIVER_MCDMA_HAL_WAIT;
  params.apexID = apexID;
  params.ChannelN = ChannelN;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_wait). Operation not executed.\n");
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

void mcdma_hal_interruptclear_ch_done(int apexID, unsigned int ChannelN)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE params;
  params.io_id = APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE;
  params.apexID = apexID;
  params.ChannelN = ChannelN;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_interruptclear_ch_done). Operation not executed.\n");
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

