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

#ifndef apex_CMEM_IF_HAL_H_
#define apex_CMEM_IF_HAL_H_

#ifdef __KERNEL_MODULE
	#include <linux/string.h>
#else
	#include <stdint.h>
#endif


//this enumeration is used to define logical resource sets
typedef enum
{
   //------------------
   //321 configurations
   //------------------

   //APU0 has ownership of CUs 0-31 and SMEM blocks 0-1 (64K)
   CFG_321__APU_0_CU_0_31_SMEM_0_1,

   //------------------
   //642 configurations
   //------------------

   //APU0 has ownership of CUs 0-63 and SMEM blocks 0-3 (128K)
   CFG_642__APU_0_CU_0_63_SMEM_0_3,

   //APU0 has ownership of CUs 0-31  and SMEM blocks 0-1 (64K)
   //APU1 has ownership of CUs 32-63 and SMEM blocks 2-3 (64K)
   CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3,

   //----------------------------------
   //error (i.e. unknown configuration)
   //----------------------------------
   CFG_UNKNOWN_CONFIGURATION

} CMEM_IF_APU_CFG;

void            cmem_if_hal_set_apu_cfg(int lApexID, CMEM_IF_APU_CFG lApuCfg);
CMEM_IF_APU_CFG cmem_if_hal_query_apu_cfg(int lApexID);
void            cmem_if_hal_set_apu_pmem_start(int lApexID, int32_t apuid, uint32_t address);
void            cmem_if_hal_set_apu_dmem_start(int lApexID, int32_t apuid, uint32_t address);
uint32_t        cmem_if_hal_query_apu_pmem_start(int lApexID, int32_t apuid);
uint32_t        cmem_if_hal_query_apu_dmem_start(int lApexID, int32_t apuid);
uint32_t        cmem_if_hal_query_cu_array_width(int lApexID, int32_t apuid);

#endif //_CMEM_IF_HAL_H_
