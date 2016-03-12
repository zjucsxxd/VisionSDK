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


#ifndef _APU_MICROKERNEL_HAL_H_
#define _APU_MICROKERNEL_HAL_H_

#include "apex_apu_microkernel_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void  apexdriver_apumk_hal_com_wait(int c, int rta);
int   apexdriver_apumk_hal_host_com_rx(int apexID, int apuid, int32_t* msg);
int   apexdriver_apumk_hal_host_com_tx(int apexID, int apuid, int32_t  msg);

#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////
//            APU MK HAL COMMAND QUEUE GENERATION
//////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// APU MK HAL  COMMAND
// APU LIB
// pre-compile a command list
void  apexdriver_apumk_hal_dmem_init     ( int apexID, int apuid, const int que_mode);
int   apexdriver_apumk_hal_push_cmd      ( int32_t* list, int kernel_id, int num_params, const int32_t* param_list);
int   apexdriver_apumk_hal_seq_push_wait ( int32_t* list, int res_set, int processor_id);
int   apexdriver_apumk_hal_seq_push_done ( int32_t* list, int res_set, int processor_id);
int   apexdriver_apumk_hal_push_align(int32_t* list);

// push the pre-compiled list into apu command queue (not start yet)
// Host write list
int   apexdriver_apumk_hal_send_list(int apexID, int32_t apu_id,
                          int32_t* list);
// Host write one single command
int   apexdriver_apumk_hal_send_cmd(int apexID, int32_t apu_id,
                         int32_t kernel_id,
                         int32_t num_params,
                         const int32_t* param_list);

#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////
//            APU MK HAL DMEM FIFO COMMAND QUEUE
//////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif


int   apexdriver_apumk_hal_config_dmemfifo_config(int apexID, int ch, int xmem_addr,
                                       int transfer_mode);
int   apexdriver_apumk_hal_config_dmemfifo_dmaconfig(int apexID, int ch, int xmem_addr,
                                          int transfer_size,
                                          int transfer_mode);
// Host transfer list through DMA
int   apexdriver_apumk_hal_transfer_list (int apexID, int ch);
void  apexdriver_apumk_hal_wait_list     (int apexID, int ch);
void  apexdriver_apumk_hal_disable       (int apexID, int ch);

#ifdef __cplusplus
}
#endif

#endif /* _APU_MICROKERNEL_HAL_H_ */
