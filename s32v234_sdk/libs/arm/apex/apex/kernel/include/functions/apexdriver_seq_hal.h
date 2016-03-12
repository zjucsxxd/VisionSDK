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

#ifndef _SEQ_HAL_H_
#define _SEQ_HAL_H_

#include "apex_seq_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void apexdriver_seq_hal_set_rsc_counter(int apexID, int lRsc, int lVal);
int  apexdriver_seq_hal_ret_rsc_counter(int apexID, int lRsc);
void apexdriver_seq_hal_proc_inc_rscmask(int apexID, int lProcId, int lRscMask);
void apexdriver_seq_hal_proc_dec_rscmask(int apexID, int lProcId, int lRscMask);
void apexdriver_seq_hal_enable_seq(int apexID, int lProcId);
void apexdriver_seq_hal_disable_seq(int apexID, int lProcId);
int  apexdriver_seq_hal_query_interrupt(int apexID, int lProcId);
void apexdriver_seq_hal_clear_interrupt(int apexID, int lProcId);
void apexdriver_seq_hal_scb_enable(int apexID, int lScbWord);
void apexdriver_seq_hal_scb_disable(int apexID, int lScbWord);
void apexdriver_seq_hal_set_hrsz_inc(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_set_hrsz_dec(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_set_dma_inc(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_set_dma_dec(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_set_motioncomp_inc(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_set_motioncomp_dec(int apexID, int lCh, int lVal);
void apexdriver_seq_hal_mask_interrupts(int apexID, int lMask);
void apexdriver_seq_hal_mask_interrupts_apu(int apexID, int lApuId, int lMask);
void apexdriver_seq_hal_clear_interrupts(int apexID, int lMask);
int  apexdriver_seq_hal_query_interrupts(int apexID);

int apexdriver_RetMceScbId(int lIdx);

#ifdef __cplusplus
}
#endif

#endif //_SEQ_HAL_H_
