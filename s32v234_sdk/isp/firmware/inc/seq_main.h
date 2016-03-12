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
 * \file    isp_main.h
 * \brief   ISP runtime firmware definitions
 * \author
 * \author
 * \version 0.1
 * \date    15-10-2013
 * \note    initial version
 ****************************************************************************/

#ifndef	SEQ_MAIN_H_
#define	SEQ_MAIN_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "config.h"
#include "seq_graph.h"

/*****************************************************************************
* code configuration
*****************************************************************************/

//#define				SEQ_DEBUG
//#define				SEQ_LOG
//#define				EVENT_LOGS		1024
//#define				ENA_SW_EVNT_LOG
//#define				IPU_REG_REPLAY

/*****************************************************************************
* consts
*****************************************************************************/

#define	SEQ_ENGIX_DYN		0xffff

#define	STATE_MSK		0xff00
#define	COUNT_MSK		0x00ff
#define	STATE_UPD_CONS		0x0100
#define	STATE_UPD_PROD		0x0200
#define	STATE_FDMA_DONE		0x0400

#ifdef IPU_REG_REPLAY
#define	IPU_BUF_ADDR_SAMP_SZ	0x400
#endif // IPU_REG_REPLAY

/*****************************************************************************
* macros
*****************************************************************************/

#ifdef USE_ASM_FUNC
#define	SUBST_FUNC	extern
#else
#define	SUBST_FUNC	static
#endif

#define	SEQ_FATAL(_m,_s)	fatalError(__FILE__, __LINE__, _m, _s);

#ifdef SEQ_LOG
  #define	DBG_CHKPT	{ dbgAppendStr(__FILE__); dbgAppendStr("#"); dbgPrintNum(0, 0, __LINE__); dbgAppendStr("\n"); }
#else
  #define	DBG_CHKPT
#endif

#define	waitClock(_c)
#define	writeRAM(_a,_d)		{ *(volatile Mem_t*)(_a)=(_d); }
#define	readRAM(_a,_d)		{ (*_d) = *(volatile Mem_t*)(_a); }
#define	writeREG_NC(_a,_d)	{ *(volatile Mem_t*)(_a)=(_d); }
#define	readREG(_a,_d)		{ (*_d) = *(volatile Mem_t*)(_a); }
#define	writeREG(_a,_d,_m)	writeREG_NC(_a,_d)

#if defined(__ghs__)
#define	ENA_IRQ			{ EVENT_LOG(EVENT_IRQ_ENA); asm("cpsie.n i"); }
#define	DIS_IRQ			{ asm("cpsid.n i"); EVENT_LOG(EVENT_IRQ_DISA); }
#else
#define	ENA_IRQ			{ EVENT_LOG(EVENT_IRQ_ENA); asm("cpsie i"); }
#define	DIS_IRQ			{ asm("cpsid i"); EVENT_LOG(EVENT_IRQ_DISA); }
#endif

#ifdef EVENT_LOGS
#define	EVENT_LOG(_e)		{ sEvent[sEventIx++]=(_e); if(sEventIx > EVENT_LOGS) { sEventIx=0; } }
#else
#define	EVENT_LOG(_e)
#endif

#define	BUF_FREE(_b)		(0 < ((_b)->mStatus & COUNT_MSK))
#define	BUF_FDMA_DONE(_b)	(STATE_FDMA_DONE == ((_b)->mStatus & STATE_FDMA_DONE))
#define	CONS_FDMA_DONE(_c)	(STATE_FDMA_DONE == ((_c)->mReady & STATE_FDMA_DONE))
#define	GET_CONS(_p)		((0 != (_p)->mpInBuf) ? &(((SEQ_Buf_t*)((_p)->mpInBuf))->mConsumer[(_p)->mcConsIx]):NULL)

/*****************************************************************************
* types
*****************************************************************************/

#ifdef EVENT_LOGS
typedef enum {
  EVENT_NONE		= 0,
  
  EVENT_IPUS0_START	= 0x10,
  EVENT_IPUS1_START,
  EVENT_IPUS2_START,
  EVENT_IPUS3_START,
  EVENT_IPUS4_START,
  EVENT_IPUS5_START,
  EVENT_IPUS6_START,
  EVENT_IPUS7_START,
  
  EVENT_IPUS0_DONE	= 0x20,
  EVENT_IPUS1_DONE,
  EVENT_IPUS2_DONE,
  EVENT_IPUS3_DONE,
  EVENT_IPUS4_DONE,
  EVENT_IPUS5_DONE,
  EVENT_IPUS6_DONE,
  EVENT_IPUS7_DONE,

  EVENT_IPUV0_START	= 0x30,
  EVENT_IPUV1_START,
  EVENT_IPUV2_START,
  EVENT_IPUV3_START,
  
  EVENT_IPUV0_DONE	= 0x40,
  EVENT_IPUV1_DONE,
  EVENT_IPUV2_DONE,
  EVENT_IPUV3_DONE,

  EVENT_MIPI0_DONE	= 0x50,
  EVENT_MIPI1_DONE,
  
  EVENT_FDMA_START0	= 0x60,
  EVENT_FDMA_START1,
  EVENT_FDMA_START2,
  EVENT_FDMA_START3,
  EVENT_FDMA_START4,
  EVENT_FDMA_START5,
  EVENT_FDMA_START6,
  EVENT_FDMA_START7,
  EVENT_FDMA_START8,
  EVENT_FDMA_START9,
  EVENT_FDMA_STARTa,
  EVENT_FDMA_STARTb,
  EVENT_FDMA_STARTc,
  EVENT_FDMA_STARTd,
  EVENT_FDMA_STARTe,
  EVENT_FDMA_STARTf,
  
  EVENT_FDMA_DONE0	= 0x70,
  EVENT_FDMA_DONE1,
  EVENT_FDMA_DONE2,
  EVENT_FDMA_DONE3,
  EVENT_FDMA_DONE4,
  EVENT_FDMA_DONE5,
  EVENT_FDMA_DONE6,
  EVENT_FDMA_DONE7,
  EVENT_FDMA_DONE8,
  EVENT_FDMA_DONE9,
  EVENT_FDMA_DONEa,
  EVENT_FDMA_DONEb,
  EVENT_FDMA_DONEc,
  EVENT_FDMA_DONEd,
  EVENT_FDMA_DONEe,
  EVENT_FDMA_DONEf,
  
  EVENT_HOST_MSG_INT	= 0x80,
  
  EVENT_HOST_ACK_INT	= 0x90,

  EVENT_SEQ_INIT	= 0xa0,
  EVENT_END_FRAME,
  EVENT_IRQ_DISA,
  EVENT_IRQ_ENA,

} event_log_t;
#endif

#ifndef __ASSEMBLER__
typedef struct RegPair_t
{
  uint32_t	mAddr0;		// *** 00
  uint32_t	mData0;		// *** 04
  uint32_t	mAddr1;		// *** 08
  uint32_t	mData1;		// *** 0c
				// *** 10 (total) ***
} RegPair_t
#ifdef __GNUC__
__attribute__ ((aligned (4)))
#endif
;

/*****************************************************************************
* exported data
*****************************************************************************/

extern const Addr_t		gcEvntCtrlAddr;
extern const Addr_t		gcClkCtrlAddr;
extern const Addr_t		gcIntDmaAddr;
extern volatile uint16_t	gOutMsgFree;
extern uint32_t			gOTHRdoneMsk;
extern uint32_t			gIPUSdoneMsk;
extern uint32_t			gIPUVdoneMsk;

#ifdef EVENT_LOGS
extern event_log_t		sEvent[EVENT_LOGS];
extern uint16_t			sEventIx;
#endif

extern uint16_t			gNumCamLines;
extern uint16_t			gMIPIlines;
#ifdef IPU_REG_REPLAY
extern RegPair_t		gIPUbuf[IPU_BUF_ADDR_SAMP_SZ];
#endif // IPU_REG_REPLAY

extern uint16_t			gNumIpusRun[ISP_NUM_IPUS];
extern uint16_t			gNumIpuvRun[ISP_NUM_IPUV];
extern uint16_t			gNumFdmaRun[FDMA_CHANNELS];

/*****************************************************************************
* imported functions
*****************************************************************************/

#if defined(STATIC_SEQUENCE_MIPI) || defined(STATIC_SEQUENCE_FDMA) 
extern void	staticSequenceInit(void);
extern void	staticSequence(void);
#endif

/*****************************************************************************
* exported functions
*****************************************************************************/

extern void	processMessage(Addr_t aAddr, Addr_t aLen);
extern void	processEvent(SEQ_Head_t* apNodeCfg, uint16_t aCnt);
extern void	checkUpdatedDev(void);
extern void	exception(void);
extern void	updateProdStat(SEQ_Buf_t* apBuf);
extern void	updateConsRdy(const SEQ_Buf_t* apcBuf, SEQ_Cons_t* apCons);
extern void	startDev(SEQ_Head_t* pHead, uint16_t aChan);

extern void	fatalError(const char* apcFile, int aLine, const char* apcMsg, uint16_t aSeverity);
#ifdef SEQ_LOG
  extern void	printRegAddr(const char* apcName, uint32_t aAddr, const char* apPre, const char* apPost);
  extern void	printRegVal(const char* apcName, uint32_t aVal, const char* apPre, const char* apPost);
  extern void	dbgPrintNum(uint8_t aIsHex, uint8_t aLeadZero, uint32_t aNum);
  extern void	dbgAppendStr(const char* apStr);
#else
  #define	printRegAddr(_a, _b, _c, _d)
  #define	printRegVal(_a, _b, _c, _d)
  #define	dbgPrintNum(_a, _b, _c)
  #define	dbgAppendStr(_a)
#endif

// *** from ASM ***
extern uint32_t	getIPSR(void);
extern uint32_t	getPRIMASK(void);
extern uint32_t	getCONTROL(void);
#endif // __ASSEMBLER__

#ifdef  __cplusplus
}
#endif

#endif // SEQ_MAIN_H_
/*EOF*/
