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

#ifndef _MCDMA_HAL_H_
#define _MCDMA_HAL_H_

#include "apex_mcdma_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

void apexdriver_mcdma_hal_program_seq_linkedlist (int apexID, unsigned int ChannelN, unsigned int LinkedListAddr);
void apexdriver_mcdma_hal_program_nonseq_linkedlist(int apexID, unsigned int ChannelN, unsigned int LinkedListAddr);
void apexdriver_mcdma_hal_interruptclear_ch_done(int apexID, unsigned int ChannelN);
void apexdriver_mcdma_hal_start(int apexID, unsigned int ChannelN);
void apexdriver_mcdma_hal_wait(int apexID, unsigned int ChannelN);
void apexdriver_mcdma_hal_ch_clear(int apexID, unsigned int ChannelN);
void apexdriver_mcdma_hal_set_memory_fill_words(int apexID, unsigned int FillWord0,
                                     unsigned int FillWord1,
                                     unsigned int FillWord2,
                                     unsigned int FillWord3);

void apexdriver_mcdma_hal_enable_perf_counter(int apexID);
void apexdriver_mcdma_hal_disable_perf_counter(int apexID);
unsigned int apexdriver_mcdma_hal_read_perf_counter_total(int apexID);
unsigned int apexdriver_mcdma_hal_read_perf_counter_busrd(int apexID); //bus read
unsigned int apexdriver_mcdma_hal_read_perf_counter_buswr(int apexID); //bus write

int apexdriver_RetStreamInPeriphId(int lIdx);
int apexdriver_RetStreamOutPeriphId(int lIdx);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_MCDMA_HAL_H_
