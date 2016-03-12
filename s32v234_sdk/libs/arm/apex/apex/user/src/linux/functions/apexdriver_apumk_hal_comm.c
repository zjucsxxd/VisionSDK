/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2015 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

//
#include "apexdriver_apu_microkernel_hal.h"
#include "apexdriver_cmem_if_hal.h"
#include <apexdriver_hw_reg_user.h>

#define APU_COM_WAIT_CC          100

#ifdef __cplusplus
extern "C" {
#endif

// cxu: SHARED DMEM divided into message queue and command queue
// size: in WORDs
// entire shared memory:            2048  32-bit
// message queue size:              8     32-bit
// command queue counter size:      8     32-bit
// command queue size:              2032  32-bit
/*
#define APU_COM_DMEM_SIZE        8
#define APU_DMEM_CMD_CNT_SIZE    8
#define APU_DMEM_CMD_QUE_SIZE    2032
*/

/***********************************************************************
// COM IMPLEMENTATION
***********************************************************************/
//
void
apexdriver_apumk_hal_com_wait(int c, int rta)
{
   static int wait_ctr[4] = { 0, 0, 0, 0 };
   static int l = 0;
   // wait(PDD_COM_WAIT_CC);
   for (; c>0; --c) { ++l;}

   ++wait_ctr[rta];
}

// HOST APIs ONLY
int
apexdriver_apumk_hal_host_com_rx(int apexID, int apuid, int32_t* msg)
{
   volatile int* APU0_DMEM_SHARED = (volatile int*)((long)ReturnVirtualHwPtr(apexID, HW_REG_SMEM) + apexdriver_cmem_if_hal_query_apu_dmem_start(apexID, apuid) + DMEM_SHARED_OFFSET);

   // WAIT FOR A MESSAGE
   while (!(APU0_DMEM_SHARED[4] > APU0_DMEM_SHARED[5]))
      apexdriver_apumk_hal_com_wait(1000, 0);

   if (msg)
      *msg = APU0_DMEM_SHARED[6];
   // SEND ACKNOWLEDGE
   ++APU0_DMEM_SHARED[5];
   
   return 0;
}

int
apexdriver_apumk_hal_host_com_tx(int apexID, int apuid, int32_t msg)
{
   volatile int* APU0_DMEM_SHARED = (volatile int*)((long)ReturnVirtualHwPtr(apexID, HW_REG_SMEM) + apexdriver_cmem_if_hal_query_apu_dmem_start(apexID, apuid) + DMEM_SHARED_OFFSET);

   APU0_DMEM_SHARED[2] = msg;
   // SEND A MESSAGE
   ++APU0_DMEM_SHARED[0];
   // WAIT ACKNOWLEDGE
   while (APU0_DMEM_SHARED[0]  > APU0_DMEM_SHARED[1]);
      //apumk_hal_com_wait(1000, 0);

   return 0;
}

#ifdef __cplusplus
}
#endif
