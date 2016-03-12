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
 
/**
 *  \file   seq_hal.h
 *  \brief  Sequencer HAL Driver.
 *
 */

#include "../../../kernel/include/linux/apexdriver_ioctl.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int  seq_hal_query_interrupts(int apexID)
{
    return apexdriver_seq_hal_query_interrupts(apexID);
}

void seq_hal_clear_interrupts(int apexID, int lMask)
{
    apexdriver_seq_hal_clear_interrupts(apexID, lMask);
}

void seq_hal_mask_interrupts(int apexID, int lMask)
{
    apexdriver_seq_hal_mask_interrupts(apexID, lMask);
}


