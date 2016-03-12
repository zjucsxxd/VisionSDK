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

#include "../../../kernel/include/linux/apexdriver_ioctl.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int apumk_hal_host_com_rx(int apexID, int apuid, int32_t* msg)
{
  return apexdriver_apumk_hal_host_com_rx(apexID, apuid, msg);
}

int apumk_hal_host_com_tx(int apexID, int apuid, int32_t  msg)
{
   return apexdriver_apumk_hal_host_com_tx(apexID, apuid, msg);
}

int apumk_hal_send_cmd(int apexID, int32_t apu_id, int32_t kernel_id, int32_t num_params, const int32_t* param_list)
{
    return apexdriver_apumk_hal_send_cmd(apexID, apu_id, kernel_id, num_params, param_list);
}


