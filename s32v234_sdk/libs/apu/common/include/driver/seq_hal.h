/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
 
/**
 *  \file   seq_hal.h
 *  \brief  Sequencer HAL Driver.
 *
 */

#ifndef _SEQ_HAL_H_
#define _SEQ_HAL_H_

void seq_hal_set_rsc_counter(int lRsc, int lVal);
int  seq_hal_ret_rsc_counter(int lRsc);
void seq_hal_proc_inc_rscmask(int lProcId, int lRscMask);
void seq_hal_proc_dec_rscmask(int lProcId, int lRscMask);
void seq_hal_enable_seq(int lProcId);
void seq_hal_disable_seq(int lProcId);
int  seq_hal_query_interrupt(int lProcId);
void seq_hal_clear_interrupt(int lProcId);
void seq_hal_scb_enable(int lScbWord);
void seq_hal_scb_disable(int lScbWord);
void seq_hal_set_hrsz_inc(int lCh, int lVal);
void seq_hal_set_hrsz_dec(int lCh, int lVal);
void seq_hal_set_dma_inc(int lCh, int lVal);
void seq_hal_set_dma_dec(int lCh, int lVal);
void seq_hal_set_motioncomp_inc(int lCh, int lVal);
void seq_hal_set_motioncomp_dec(int lCh, int lVal);
void seq_hal_mask_interrupts(int lMask);
void seq_hal_mask_interrupts_apu(int lApuId, int lMask);
void seq_hal_clear_interrupts(int lMask);
int  seq_hal_query_interrupts();

int RetMceScbId(int lIdx);

#if 0
int   useq_hal_reset();
int   useq_hal_config();
int   useq_hal_inc(int tid, int rset);

// OLD
/*
int   USeqReset();
int   USeqConfig();
*/

#endif //0

#endif //_SEQ_HAL_H_
