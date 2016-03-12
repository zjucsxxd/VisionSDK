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
 
#include <apexdriver_cmem_if_hal.h>
#include <apexdriver_hw_reg_user.h>

typedef unsigned int REG32;
#include "apex_642cl_cmem_if_map.h"                                                             //SmemTdm   | SmemCtrl | VecCtrl  | Vec6332Master | Vec310Master
#define VECCFGREG__CFG_321__APU_0_CU_0_31_SMEM_0_1                          (0xf << 12 | 0x0 << 8 | 0x2 << 4 | 0x0 << 1      | 0x0 << 0)
#define VECCFGREG__CFG_642__APU_0_CU_0_63_SMEM_0_3                          (0xf << 12 | 0x0 << 8 | 0x0 << 4 | 0x0 << 1      | 0x0 << 0)
#define VECCFGREG__CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3 (0xf << 12 | 0xc << 8 | 0x2 << 4 | 0x1 << 1      | 0x0 << 0)

void apexdriver_cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg)
{
   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);

   switch (lApuCfg)
   {
   case CFG_321__APU_0_CU_0_31_SMEM_0_1:
      lpCmemifRegisters->ApuVecConfig.as32BitValue = VECCFGREG__CFG_321__APU_0_CU_0_31_SMEM_0_1;
      break;
   case CFG_642__APU_0_CU_0_63_SMEM_0_3:
      lpCmemifRegisters->ApuVecConfig.as32BitValue = VECCFGREG__CFG_642__APU_0_CU_0_63_SMEM_0_3;
      break;
   case CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3:
      lpCmemifRegisters->ApuVecConfig.as32BitValue = VECCFGREG__CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3;
      break;
	  
   default:
	  break;
   }
}

CMEM_IF_APU_CFG apexdriver_cmem_if_hal_query_apu_cfg(int lApexID)
{
   CMEM_IF_APU_CFG lApuCfg = CFG_UNKNOWN_CONFIGURATION;

   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);

   switch(lpCmemifRegisters->ApuVecConfig.as32BitValue)
   {
   case VECCFGREG__CFG_321__APU_0_CU_0_31_SMEM_0_1:
      lApuCfg = CFG_321__APU_0_CU_0_31_SMEM_0_1;
      break;
   case VECCFGREG__CFG_642__APU_0_CU_0_63_SMEM_0_3:
      lApuCfg = CFG_642__APU_0_CU_0_63_SMEM_0_3;
      break;
   case VECCFGREG__CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3:
      lApuCfg = CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3;
      break;
   }

   return lApuCfg;
}

void apexdriver_cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address)
{
  
   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);
   switch (apuid)
   {
   case 0:
      lpCmemifRegisters->Apu0PmStart.asBitField.Addr = address;
      break;
   case 1:
      lpCmemifRegisters->Apu1PmStart.asBitField.Addr = address;
      break;
   }
}

void apexdriver_cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address)
{
  
   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);
   switch (apuid)
   {
   case 0:
      lpCmemifRegisters->Apu0DmStart.asBitField.Addr = address;
      break;
   case 1:
      lpCmemifRegisters->Apu1DmStart.asBitField.Addr = address;
      break;
   }
}

uint32_t apexdriver_cmem_if_hal_query_apu_pmem_start(int lApexID, int32_t apuid)
{
   uint32_t lAddr = 0;

   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);
   switch (apuid)
   {
   case 0:
      lAddr = lpCmemifRegisters->Apu0PmStart.asBitField.Addr;
      break;
   case 1:
      lAddr = lpCmemifRegisters->Apu1PmStart.asBitField.Addr;
      break;
   }

   return lAddr;
}

uint32_t apexdriver_cmem_if_hal_query_apu_dmem_start(int lApexID, int32_t apuid)
{
   uint32_t lAddr = 0;

   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);
   switch (apuid)
   {
   case 0:
      lAddr = lpCmemifRegisters->Apu0DmStart.asBitField.Addr;
      break;
   case 1:
      lAddr = lpCmemifRegisters->Apu1DmStart.asBitField.Addr;
      break;
   }

   return lAddr;
}

uint32_t apexdriver_cmem_if_hal_query_cu_array_width(int lApexID, int32_t apuid)
{
   //NOTE: apuid currently not used but it will likely be required in the future

   uint32_t lArrayWidth = 32; //default

   volatile APEX_642CL_CMEM_IF_DCR *const lpCmemifRegisters = (APEX_642CL_CMEM_IF_DCR*)ReturnVirtualHwPtr(lApexID, HW_REG_CMEM_IF);

   if (VECCFGREG__CFG_642__APU_0_CU_0_63_SMEM_0_3 == lpCmemifRegisters->ApuVecConfig.as32BitValue)
      lArrayWidth = 64;

   return lArrayWidth;
}


//#endif // ATD_HWSIM_DATA_GEN

