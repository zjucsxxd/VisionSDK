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

#include <apexdriver_seq_hal.h>
#include <apexdriver_hw_reg_user.h>

typedef unsigned int REG32;
#include <apex_642cl_seq_map.h>

void apexdriver_seq_hal_set_rsc_counter(int apexID, int lRsc, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   volatile REG32* lCntArray = (volatile REG32*)&(lpSeqRegisters->ResourceFix[0]);
   lCntArray[lRsc] = lVal;
}

int apexdriver_seq_hal_ret_rsc_counter(int apexID, int lRsc)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   volatile REG32* lCntArray = (volatile REG32*)&(lpSeqRegisters->ResourceFix[0]);
#ifdef HAL_DUMMY_NO_HW
   return lCntArray[lRsc] + 1; //resource always 'available'
#else
   return lCntArray[lRsc];
#endif
}

void apexdriver_seq_hal_proc_inc_rscmask(int apexID, int lProcId, int lRscMask)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->ProcInc[lProcId].as32BitValue = lRscMask;
}

void apexdriver_seq_hal_proc_dec_rscmask(int apexID, int lProcId, int lRscMask)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->ProcDec[lProcId].as32BitValue = lRscMask;
}

void apexdriver_seq_hal_enable_seq(int apexID, int lProcId)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->Enable.as32BitValue = 1<<lProcId;
}

void apexdriver_seq_hal_disable_seq(int apexID, int lProcId)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->SeqDisable.as32BitValue = 1<<lProcId;
}

int apexdriver_seq_hal_query_interrupt(int apexID, int lProcId)
{
   int lRetVal = 0;
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   if (lpSeqRegisters->Isr.as32BitValue & (1<<lProcId))
      lRetVal = 1;
#ifdef HAL_DUMMY_NO_HW
   lRetVal = 1; //interrupt always available
#endif
   return lRetVal;
}

void apexdriver_seq_hal_clear_interrupt(int apexID, int lProcId)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->Icr.as32BitValue = (1<<lProcId);
}

void apexdriver_seq_hal_scb_enable(int apexID, int lScbWord)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->ScbEnable.as32BitValue = lScbWord;
}

void apexdriver_seq_hal_scb_disable(int apexID, int lScbWord)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->ScbDisable.as32BitValue = lScbWord;
}

void apexdriver_seq_hal_set_hrsz_inc(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->HorizResizerInc[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_set_hrsz_dec(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->HorizResizerDec[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_set_dma_inc(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->DmaInc[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_set_dma_dec(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->DmaDec[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_set_motioncomp_inc(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->MotionCompInc[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_set_motioncomp_dec(int apexID, int lCh, int lVal)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->MotionCompDec[lCh].as32BitValue = lVal;
}

void apexdriver_seq_hal_mask_interrupts(int apexID, int lMask)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->Imr.as32BitValue = lMask;
}

void apexdriver_seq_hal_mask_interrupts_apu(int apexID, int lApuId, int lMask)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   if (0 == lApuId)
   {
      lpSeqRegisters->Imr2.as32BitValue = lMask;
   }
   else //1 == lApuId
   {
      lpSeqRegisters->Imr3.as32BitValue = lMask;
   }
}

void apexdriver_seq_hal_clear_interrupts(int apexID, int lMask)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
   lpSeqRegisters->Icr.as32BitValue = lMask;
}

int apexdriver_seq_hal_query_interrupts(int apexID)
{
   volatile APEX_642CL_SEQ_DCR *const lpSeqRegisters = (APEX_642CL_SEQ_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_USEQ);
#ifdef HAL_DUMMY_NO_HW
   return lpSeqRegisters->Isr.as32BitValue | 0xFFFFFFFF; //interrupts always available
#else
   return lpSeqRegisters->Isr.as32BitValue;
#endif
}

int apexdriver_RetMceScbId(int lIdx)
{
   int lScbId = 0;
   switch(lIdx)
   {
   case 0: lScbId = 24; break;
   case 1: lScbId = 25; break;
   }
   return lScbId;
}


