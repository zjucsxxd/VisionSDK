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

#include "apexdriver_apu_microkernel_hal.h"

void apumk_hal_com_wait(int c, int rta)
{
	apexdriver_apumk_hal_com_wait(c, rta);
}

int apumk_hal_host_com_rx(int apexID, int apuid, int32_t* msg)
{
	return apexdriver_apumk_hal_host_com_rx(apexID, apuid, msg);
}

int apumk_hal_host_com_tx(int apexID, int apuid, int32_t  msg)
{
	return apexdriver_apumk_hal_host_com_tx(apexID, apuid, msg);
}

int apumk_hal_push_cmd( int32_t* list, int kernel_id, int num_params, const int32_t* param_list)
{
	return apexdriver_apumk_hal_push_cmd( list, kernel_id, num_params, param_list);
}

int apumk_hal_seq_push_wait( int32_t* list, int res_set, int processor_id)
{
	return apexdriver_apumk_hal_seq_push_wait( list, res_set, processor_id);
}

int apumk_hal_seq_push_done( int32_t* list, int res_set, int processor_id)
{
	return apexdriver_apumk_hal_seq_push_done( list, res_set, processor_id);
}

int apumk_hal_push_align(int32_t* list)
{
	return apexdriver_apumk_hal_push_align(list);
}

int apumk_hal_send_list(int apexID, int32_t apu_id, int32_t* list)
{
	return apexdriver_apumk_hal_send_list(apexID, apu_id, list);
}

int apumk_hal_send_cmd(int apexID, int32_t apu_id, int32_t kernel_id, int32_t num_params, const int32_t* param_list)
{
	return apexdriver_apumk_hal_send_cmd(apexID, apu_id, kernel_id, num_params, param_list);
}


