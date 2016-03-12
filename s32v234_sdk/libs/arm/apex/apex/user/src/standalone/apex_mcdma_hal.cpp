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

#include "apexdriver_mcdma_hal.h"

void mcdma_hal_program_seq_linkedlist (int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
	apexdriver_mcdma_hal_program_seq_linkedlist (apexID, ChannelN, LinkedListAddr);
}

void mcdma_hal_program_nonseq_linkedlist(int apexID, unsigned int ChannelN, unsigned int LinkedListAddr)
{
	apexdriver_mcdma_hal_program_nonseq_linkedlist(apexID, ChannelN, LinkedListAddr);
}

void mcdma_hal_interruptclear_ch_done(int apexID, unsigned int ChannelN)
{
	apexdriver_mcdma_hal_interruptclear_ch_done(apexID, ChannelN);
}

void mcdma_hal_start(int apexID, unsigned int ChannelN)
{
	apexdriver_mcdma_hal_start(apexID, ChannelN);
}

void mcdma_hal_wait(int apexID, unsigned int ChannelN)
{
	apexdriver_mcdma_hal_wait(apexID, ChannelN);
}

void mcdma_hal_ch_clear(int apexID, unsigned int ChannelN)
{
	apexdriver_mcdma_hal_ch_clear(apexID, ChannelN);
}

void mcdma_hal_set_memory_fill_words(int apexID, unsigned int FillWord0, unsigned int FillWord1, unsigned int FillWord2, unsigned int FillWord3)
{
	apexdriver_mcdma_hal_set_memory_fill_words(apexID, FillWord0, FillWord1, FillWord2, FillWord3);
}

void mcdma_hal_enable_perf_counter(int apexID)
{
	apexdriver_mcdma_hal_enable_perf_counter(apexID);
}

void mcdma_hal_disable_perf_counter(int apexID)
{
	apexdriver_mcdma_hal_disable_perf_counter(apexID);
}

unsigned int mcdma_hal_read_perf_counter_total(int apexID)
{
	return apexdriver_mcdma_hal_read_perf_counter_total(apexID);
}

unsigned int mcdma_hal_read_perf_counter_busrd(int apexID)
{
	return apexdriver_mcdma_hal_read_perf_counter_busrd(apexID);
}

unsigned int mcdma_hal_read_perf_counter_buswr(int apexID)
{
	return apexdriver_mcdma_hal_read_perf_counter_buswr(apexID);
}

int RetStreamInPeriphId(int lIdx)
{
	return apexdriver_RetStreamInPeriphId(lIdx);
}

int RetStreamOutPeriphId(int lIdx)
{
	return apexdriver_RetStreamOutPeriphId(lIdx);
}

