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

 #include "apexdriver_seq_hal.h"
 
void seq_hal_set_rsc_counter(int apexID, int lRsc, int lVal)
{
	apexdriver_seq_hal_set_rsc_counter(apexID, lRsc, lVal);
}

int seq_hal_ret_rsc_counter(int apexID, int lRsc)
{
	return apexdriver_seq_hal_ret_rsc_counter(apexID, lRsc);
}

void seq_hal_proc_inc_rscmask(int apexID, int lProcId, int lRscMask)
{
	apexdriver_seq_hal_proc_inc_rscmask(apexID, lProcId, lRscMask);
}

void seq_hal_proc_dec_rscmask(int apexID, int lProcId, int lRscMask)
{
	apexdriver_seq_hal_proc_dec_rscmask(apexID, lProcId, lRscMask);
}

void seq_hal_enable_seq(int apexID, int lProcId)
{
	apexdriver_seq_hal_enable_seq(apexID, lProcId);
}

void seq_hal_disable_seq(int apexID, int lProcId)
{
	apexdriver_seq_hal_disable_seq(apexID, lProcId);
}

int seq_hal_query_interrupt(int apexID, int lProcId)
{
	return apexdriver_seq_hal_query_interrupt(apexID, lProcId);
}

void seq_hal_clear_interrupt(int apexID, int lProcId)
{
	apexdriver_seq_hal_clear_interrupt(apexID, lProcId);
}

void seq_hal_scb_enable(int apexID, int lScbWord)
{
	apexdriver_seq_hal_scb_enable(apexID, lScbWord);
}

void seq_hal_scb_disable(int apexID, int lScbWord)
{
	apexdriver_seq_hal_scb_disable(apexID, lScbWord);
}

void seq_hal_set_hrsz_inc(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_hrsz_inc(apexID, lCh, lVal);
}

void seq_hal_set_hrsz_dec(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_hrsz_dec(apexID, lCh, lVal);
}

void seq_hal_set_dma_inc(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_dma_inc(apexID, lCh, lVal);
}

void seq_hal_set_dma_dec(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_dma_dec(apexID, lCh, lVal);
}

void seq_hal_set_motioncomp_inc(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_motioncomp_inc(apexID, lCh, lVal);
}

void seq_hal_set_motioncomp_dec(int apexID, int lCh, int lVal)
{
	apexdriver_seq_hal_set_motioncomp_dec(apexID, lCh, lVal);
}

void seq_hal_mask_interrupts(int apexID, int lMask)
{
	apexdriver_seq_hal_mask_interrupts(apexID, lMask);
}

void seq_hal_mask_interrupts_apu(int apexID, int lApuId, int lMask)
{
	apexdriver_seq_hal_mask_interrupts_apu(apexID, lApuId, lMask);
}

void seq_hal_clear_interrupts(int apexID, int lMask)
{
	apexdriver_seq_hal_clear_interrupts(apexID, lMask);
}

int seq_hal_query_interrupts(int apexID)
{
	return apexdriver_seq_hal_query_interrupts(apexID);
}

int RetMceScbId(int lIdx)
{
	return apexdriver_RetMceScbId(lIdx);
}



