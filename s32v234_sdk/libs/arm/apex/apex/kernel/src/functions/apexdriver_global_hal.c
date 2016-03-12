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

// Include files.
#include "global_errors.h"
#include "apexdriver_global_hal.h"
#include "apexdriver_hw_reg_user.h"

typedef unsigned int REG32;
#include <apex_642cl_global_map.h>

#define TRUE 1
#define FALSE 0

/****************************************************************************
 * Function:      global_hal_AllReset
 * Description:   Resets all APEX blocks
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_AllReset(int apexID)
{
   apexdriver_global_hal_cmemIFReset(apexID);
   apexdriver_global_hal_CmemDmaReset(apexID);
   apexdriver_global_hal_uSequencerReset(apexID);
   apexdriver_global_hal_DmaReset(apexID);
   apexdriver_global_hal_MotCmpDmaReset(apexID);
   apexdriver_global_hal_Apu0Reset(apexID);
   apexdriver_global_hal_Apu1Reset(apexID);
   apexdriver_global_hal_Vu0Reset(apexID);
   apexdriver_global_hal_Vu1Reset(apexID);
   apexdriver_global_hal_Dmem0Reset(apexID);
   apexdriver_global_hal_Dmem1Reset(apexID);
   apexdriver_global_hal_HrszReset(apexID);
   return 0;
}

/****************************************************************************
 * Function:      global_hal_CmemDmaReset
 * Description:   Resets the CmemDmaReset block
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_CmemDmaReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Stream = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Stream = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_uSequencerReset
 * Description:   Resets the uSequencer
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_uSequencerReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Sequencer = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Sequencer = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_DmaReset
 * Description:   Resets the Dma block
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_DmaReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.MultiDma = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.MultiDma = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_MotCmpDmaReset
 * Description:   Resets the Motion Comp Dma block
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_MotCmpDmaReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.MotionComp = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.MotionComp = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_cmemIFReset
 * Description:
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_cmemIFReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.CmemIf = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.CmemIf = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apu0Reset
 * Description:   Resets the APU0
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu0Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Apu0 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Apu0 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apu1Reset
 * Description:   Resets the APU1
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu1Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Apu1 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Apu1 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Vu0Reset
 * Description:   Resets Vu0
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Vu0Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Vu0 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Vu0 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Vu1Reset
 * Description:   Resets Vu1
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Vu1Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Vu1 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Vu1 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_HrszReset
 * Description:   Resets Horizontal Resizer
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_HrszReset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.HrzScaler = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.HrzScaler = TRUE;
   return 0;
}


/****************************************************************************
 * Function:      global_hal_Dmem0Reset
 * Description:
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Dmem0Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Dmem0 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Dmem0 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Dmem1Reset
 * Description:
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Dmem1Reset(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->RstSet.asBitField.Dmem1 = TRUE;
   lpApex2GlobalReg->RstClear.asBitField.Dmem1 = TRUE;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apu0Enable
 * Description:   Enable APU0
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu0Enable(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->Misc.asBitField.ApuEnable0 = APEX2_APU_ENBABLED;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apu1Enable
 * Description:   Enable APU1
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu1Enable(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->Misc.asBitField.ApuEnable1 = APEX2_APU_ENBABLED;
   return 0;
}

   /****************************************************************************
 * Function:      global_hal_Apu0Disable
 * Description:   Disable APU0
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu0Disable(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->Misc.asBitField.ApuEnable0 = APEX2_APU_DISABLED;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apu1Disable
 * Description:   Disable APU1
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apu1Disable(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   lpApex2GlobalReg->Misc.asBitField.ApuEnable1 = APEX2_APU_DISABLED;
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apex2GlobalInterruptDisable
 * Description:   Musk specified interrupt bit to disable the INT
 * Parameters:    intBit : spcified Interrupt bit
 *                maskVal: value
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);

   switch (intBit)
   {
      case APEX2_INTERRUPT_MULTI_DMA:
         lpApex2GlobalReg->IntMaskSet.asBitField.MultiDma = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_MOT_COMP_DMA:
         lpApex2GlobalReg->IntMaskSet.asBitField.MotionComp = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_SEQUENCER:
         lpApex2GlobalReg->IntMaskSet.asBitField.Sequencer = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_STREAM_IN_0:
         lpApex2GlobalReg->IntMaskSet.asBitField.StreamIn0 = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_STREAM_IN_1:
         lpApex2GlobalReg->IntMaskSet.asBitField.StreamIn1 = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_0:
         lpApex2GlobalReg->IntMaskSet.asBitField.StreamOut0 = APEX2_INTERRUPT_DISABLE;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_1:
         lpApex2GlobalReg->IntMaskSet.asBitField.StreamOut1 = APEX2_INTERRUPT_DISABLE;
         break;
		 
	  default:
	     break;

   }
   return 0;
}

/****************************************************************************
 * Function:      global_hal_Apex2GlobalInterruptEnable
 * Description:   Unmask specified interrupt bit to enable the INT
 * Parameters:    intBit : spcified Interrupt bit
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);

   switch (intBit)
   {
      case APEX2_INTERRUPT_MULTI_DMA:
         lpApex2GlobalReg->IntMaskClear.asBitField.MultiDma = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_MOT_COMP_DMA:
         lpApex2GlobalReg->IntMaskClear.asBitField.MotionComp = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_SEQUENCER:
         lpApex2GlobalReg->IntMaskClear.asBitField.Sequencer = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_STREAM_IN_0:
         lpApex2GlobalReg->IntMaskClear.asBitField.StreamIn0 = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_STREAM_IN_1:
         lpApex2GlobalReg->IntMaskClear.asBitField.StreamIn1 = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_0:
         lpApex2GlobalReg->IntMaskClear.asBitField.StreamOut0 = APEX2_INTERRUPT_ENABLE;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_1:
         lpApex2GlobalReg->IntMaskClear.asBitField.StreamOut1 = APEX2_INTERRUPT_ENABLE;
         break;

	  default:
	     break;
   }
   return 0;
}

/****************************************************************************
 * Function:      global_hal_isApex2GlobalInterruptEnabled
 * Description:    returns the mask status of an interrupt
 * Parameters:    intBit : spcified Interrupt bit
 * Return Value/Updated Parameters:
 *                      TRUE = interrupt is enable
 *                      FALSE = interrupt is disabled
 ****************************************************************************/
int apexdriver_global_hal_isApex2GlobalInterruptEnabled(int apexID, APEX2_INTERRUPT_BITS intBit)
{
   unsigned int maskbit=1;

   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);

   switch (intBit)
   {
      case APEX2_INTERRUPT_MULTI_DMA:
         maskbit = lpApex2GlobalReg->IntMaskStatus.asBitField.MultiDma;
         break;

      case APEX2_INTERRUPT_MOT_COMP_DMA:
         maskbit =  lpApex2GlobalReg->IntMaskStatus.asBitField.MotionComp;
         break;

      case APEX2_INTERRUPT_SEQUENCER:
         maskbit =  lpApex2GlobalReg->IntMaskStatus.asBitField.Sequencer;
         break;

      case APEX2_INTERRUPT_STREAM_IN_0:
         maskbit =  lpApex2GlobalReg->IntMaskStatus.asBitField.StreamIn0;
         break;

      case APEX2_INTERRUPT_STREAM_IN_1:
         maskbit =  lpApex2GlobalReg->IntMaskStatus.asBitField.StreamIn1;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_0:
         maskbit =  lpApex2GlobalReg->IntMaskStatus.asBitField.StreamOut0;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_1:
         maskbit = lpApex2GlobalReg->IntMaskStatus.asBitField.StreamOut1;
         break;

      default:
         maskbit =  0;
         break;
   }

   if( maskbit == 0 )   // IRQ is enabled
      return TRUE;

   return FALSE;
}

/****************************************************************************
 * Function:      global_hal_Apex2GlobalInterruptStatus
 * Description:   Check status of specified interrupt bit
 * Parameters:    intBit : spcified Interrupt bit
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int apexdriver_global_hal_Apex2GlobalInterruptStatus(int apexID, APEX2_INTERRUPT_BITS intBit)
{
   int intStatus = FALSE;

   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);

   switch (intBit)
   {
      case APEX2_INTERRUPT_MULTI_DMA:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.MultiDma ;
         break;

      case APEX2_INTERRUPT_MOT_COMP_DMA:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.MotionComp;
         break;

      case APEX2_INTERRUPT_SEQUENCER:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.Sequencer ;
         break;

      case APEX2_INTERRUPT_STREAM_IN_0:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.StreamIn0;
         break;

      case APEX2_INTERRUPT_STREAM_IN_1:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.StreamIn1;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_0:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.StreamOut0;
         break;

      case APEX2_INTERRUPT_STREAM_OUT_1:
         intStatus = lpApex2GlobalReg->IntStatus.asBitField.StreamOut1;
         break;
	  
	  default:
	     break;
   }

   return intStatus;
}


/****************************************************************************
 * Function:      global_hal_Apex2GlobalInterruptPolling
 * Description:   Poll specified interrupt bit
 * Parameters:    intBit : spcified Interrupt bit
 * Return Value/Updated Parameters:
 *    Success or Failed
 ****************************************************************************/
LIB_RESULT apexdriver_global_hal_Apex2GlobalInterruptPolling(int apexID, APEX2_INTERRUPT_BITS intBit)
{
   int rtc = LIB_SUCCESS;
   int intStatus = FALSE;
   unsigned int  loopCount = 0xfffff;

   do
   {
      intStatus = apexdriver_global_hal_Apex2GlobalInterruptStatus(apexID, intBit);
      if ( intStatus == TRUE)
      {
         break;
      }

      loopCount--;
   } while ( intStatus != TRUE && loopCount != 0);

   if (loopCount == 0)
   {
      rtc = LIB_FAILURE;
   }

   return rtc;
}


int apexdriver_global_hal_RetHwVersion(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   return lpApex2GlobalReg->Version.asBitField.Hw;
}

int apexdriver_global_hal_RetSwVersion(int apexID)
{
   volatile APEX_642CL_GLOBAL_DCR *const lpApex2GlobalReg = (APEX_642CL_GLOBAL_DCR*)ReturnVirtualHwPtr(apexID, HW_REG_GLOBAL);
   return lpApex2GlobalReg->Version.asBitField.Sw;
}
