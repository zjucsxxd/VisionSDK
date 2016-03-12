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

#include "../../../kernel/include/linux/apexdriver_ioctl.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>


void mcdma_hal_set_memory_fill_words(int apexID, unsigned int FillWord0, unsigned int FillWord1, unsigned int FillWord2, unsigned int FillWord3)
{
    apexdriver_mcdma_hal_set_memory_fill_words(apexID, FillWord0, FillWord1, FillWord2, FillWord3);
}

void mcdma_hal_program_seq_linkedlist (int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
    apexdriver_mcdma_hal_program_seq_linkedlist (apexID, ChannelN, LinkedListAddr);
}

void mcdma_hal_start(int apexID, unsigned int ChannelN)
{
    apexdriver_mcdma_hal_start(apexID, ChannelN);
}

void mcdma_hal_wait(int apexID, unsigned int ChannelN)
{
    apexdriver_mcdma_hal_wait(apexID, ChannelN);
}

void mcdma_hal_interruptclear_ch_done(int apexID, unsigned int ChannelN)
{
    apexdriver_mcdma_hal_interruptclear_ch_done(apexID, ChannelN);
}

