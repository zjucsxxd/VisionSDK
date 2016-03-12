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
#include <apexdriver_stio_hal.h>

typedef unsigned int REG32;
#include <apex_642cl_stream_dma_map.h>

#include <apexdriver_hw_reg_user.h>

/*
void stio_hal_config(APEX_642CL_STREAM_DMA_STREAM_DCR *r, unsigned int i)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(HW_REG_STIO);
   memcpy((void *)&(stio_reg->sioRegisters[i]), (void *)r, sizeof(APEX_642CL_STREAM_DMA_DCR));
}
*/

void apexdriver_stio_hal_pollwait_sti0_done(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   while (0 == stio_reg->Isr.asBitField.In0);
}

void apexdriver_stio_hal_interruptclear_sti0_done(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   stio_reg->Icr.asBitField.In0 = 1;
}

void apexdriver_stio_hal_interruptclear_sti1_done(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   stio_reg->Icr.asBitField.In1 = 1;
}

void apexdriver_stio_hal_interruptclear_sti0_framestart(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   stio_reg->Icr.asBitField.Start0 = 1;
}

void apexdriver_stio_hal_interruptclear_sti1_framestart(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   stio_reg->Icr.asBitField.Start1 = 1;
}

void apexdriver_stio_hal_interruptclear_sto0_done(int apexID)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   stio_reg->Icr.asBitField.Out0 = 1;
}

void apexdriver_stio_hal_interruptclear_sti_done(int apexID, int channel)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   switch (channel)
   {
      case 0: stio_reg->Icr.asBitField.In0 = 1; break;
      case 1: stio_reg->Icr.asBitField.In1 = 1; break;
      case 2: stio_reg->Icr.asBitField.In2 = 1; break;
      case 3: stio_reg->Icr.asBitField.In3 = 1; break;
   }
}

void apexdriver_stio_hal_interruptclear_sto_done(int apexID, int channel)
{
   volatile APEX_642CL_STREAM_DMA_DCR *const stio_reg = (volatile APEX_642CL_STREAM_DMA_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_STIO);
   switch (channel)
   {
      case 0: stio_reg->Icr.asBitField.Out0 = 1; break;
      case 1: stio_reg->Icr.asBitField.Out1 = 1; break;
   }
}

