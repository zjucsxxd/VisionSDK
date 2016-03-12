/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2013 Freescale Semiconductor;
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
 * \file    isp_int.h
 * \brief   ISP runtime firmware (M0+)
 * \author
 * \author
 * \version 0.1
 * \date    15-10-2013
 * \note    initial version
 ****************************************************************************/

#ifndef	SEQ_INT_H_
#define	SEQ_INT_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
* consts
*****************************************************************************/

/*****************************************************************************
* macros
*****************************************************************************/

/*****************************************************************************
* types
*****************************************************************************/

typedef struct devEvent_t
{
  SEQ_Head_t*	mpHead;	// *** 00 pointer to nodes header ***
  uint16_t	mCnt;	// *** 04 event counter ***
  uint16_t	mPad0;	// *** 06 pad aligment ***
			// *** 08 (total) ***
} devEvent_t
#ifdef __GNUC__
__attribute__ ((aligned (2)))
#endif
;

/*****************************************************************************
* exported data
*****************************************************************************/

extern SEQ_Head_t*	gpIntDevCfg[SEQ_NUM_DEV];
extern uint16_t		gIntDevCnt;
extern devEvent_t	spIPUS[ISP_NUM_IPUS];
extern devEvent_t	spIPUV[ISP_NUM_IPUV];
extern devEvent_t	spOTHR[SEQ_OTHRIX_LAST];

/*****************************************************************************
* exported functions
*****************************************************************************/

extern void	SEQ_EvntInit(SEQ_Othr_ix_t aMIPIix);
extern void	SEQ_EvntHndl(void);
extern void	SEQ_EvntRegIntDev(SEQ_Head_t* apHead);
extern void	SEQ_HostOutAckHndl(void);
extern void	SEQ_ExecuteEvents(void);

/*****************************************************************************
* imports
*****************************************************************************/

#ifdef  __cplusplus
}
#endif

#endif // SEQ_INT_H_
/*EOF*/
