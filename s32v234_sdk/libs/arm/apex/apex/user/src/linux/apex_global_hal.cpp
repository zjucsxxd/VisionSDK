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

int global_hal_RetHwVersion(int apexID)
{
    return apexdriver_global_hal_RetHwVersion(apexID);
}

int global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
    return apexdriver_global_hal_Apex2GlobalInterruptDisable(apexID, intBit);
}

int global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
    return apexdriver_global_hal_Apex2GlobalInterruptEnable(apexID, intBit);
}

