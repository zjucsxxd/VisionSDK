/******************************************************************************
 *  (C) Copyright CogniVue Corp. 2006 All right reserved.
 *    Confidential Information
 *  
 *  All parts of the MtekVision Program Source are protected by copyright law 
 *  and all rights are reserved. 
 *  This documentation may not, in whole or in part, be copied, photocopied, 
 *  reproduced, translated, or reduced to any electronic medium or machine 
 *  readable form without prior consent, in writing, from MtekVision. 
 ******************************************************************************/

#include <apexdriver_mcdma_hal.h>
#include <apexdriver_hw_reg_user.h>

typedef unsigned int REG32;
#include "apex_642cl_mcdma_map.h"

void apexdriver_mcdma_hal_program_seq_linkedlist(int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   
   //configure linked list address and enable (mode will be 0 indicating sequential)
   lpDmaRegisters->Ch[ChannelN].LinkedList.as32BitValue = (LinkedListAddr | 0x01);
}

void apexdriver_mcdma_hal_program_nonseq_linkedlist(int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);

   //configure linked list address and enable (mode will be 1 indicating non-sequential)
   lpDmaRegisters->Ch[ChannelN].LinkedList.as32BitValue = (LinkedListAddr | 0x03);
}

void apexdriver_mcdma_hal_interruptclear_ch_done(int apexID, unsigned int ChannelN)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->Icr.as32BitValue = (int)(1ul << ChannelN);
}

void apexdriver_mcdma_hal_start(int apexID, unsigned int ChannelN)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->ChEnable.as32BitValue |= (1 << (ChannelN));
}

void apexdriver_mcdma_hal_wait(int apexID, unsigned int ChannelN)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);

   while ( lpDmaRegisters->ChEnable.as32BitValue & (1 << (ChannelN)) )
   {
#ifdef HAL_DUMMY_NO_HW
      break; //return immediately
#endif
   }

   lpDmaRegisters->Icr.as32BitValue = (int)(1ul << ChannelN);
}

void apexdriver_mcdma_hal_ch_clear(int apexID, unsigned int ChannelN)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->ChClear.as32BitValue |= (1 << ChannelN);
}

void apexdriver_mcdma_hal_set_memory_fill_words(int apexID, 
									 unsigned int FillWord0,
                                     unsigned int FillWord1,
                                     unsigned int FillWord2,
                                     unsigned int FillWord3)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->MemoryFill[0].Word[0].as32BitValue = FillWord0;
   lpDmaRegisters->MemoryFill[0].Word[1].as32BitValue = FillWord1;
   lpDmaRegisters->MemoryFill[0].Word[2].as32BitValue = FillWord2;
   lpDmaRegisters->MemoryFill[0].Word[3].as32BitValue = FillWord3;
}

void apexdriver_mcdma_hal_enable_perf_counter(int apexID)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->Perf.Control.asBitField.Enable = 1;
}

void apexdriver_mcdma_hal_disable_perf_counter(int apexID)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   lpDmaRegisters->Perf.Control.asBitField.Enable = 0;
}

unsigned int apexdriver_mcdma_hal_read_perf_counter_total(int apexID)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   return lpDmaRegisters->Perf.Total.asBitField.Count;
}

unsigned int apexdriver_mcdma_hal_read_perf_counter_busrd(int apexID)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   return lpDmaRegisters->Perf.Busrd.asBitField.Count;
}

unsigned int apexdriver_mcdma_hal_read_perf_counter_buswr(int apexID)
{
   volatile APEX_642CL_MCDMA_DCR *const lpDmaRegisters = (APEX_642CL_MCDMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_MCDMA);
   return lpDmaRegisters->Perf.Buswr.asBitField.Count;
}

int apexdriver_RetStreamInPeriphId(int lIdx)
{
   int lPeriphId = 0;
   switch(lIdx)
   {
   case 0: lPeriphId = DST_CMEM_DMA_STREAM_IN0; break;
   case 1: lPeriphId = DST_CMEM_DMA_STREAM_IN1; break;
   case 2: lPeriphId = DST_CMEM_DMA_STREAM_IN2; break;
   case 3: lPeriphId = DST_CMEM_DMA_STREAM_IN3; break;
   }
   return lPeriphId;
}

int apexdriver_RetStreamOutPeriphId(int lIdx)
{
   int lPeriphId = 0;
   switch(lIdx)
   {
   case 0: lPeriphId = SRC_CMEM_DMA_STREAM_OUT0; break;
   case 1: lPeriphId = SRC_CMEM_DMA_STREAM_OUT1; break;
   }
   return lPeriphId;
}

