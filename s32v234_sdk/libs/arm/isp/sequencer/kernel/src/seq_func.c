/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2016 Freescale Semiconductor;
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
 * \file     seq_func.c
 * \brief    functionality of Sequencer driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     12.6.2014
 * \note
 ****************************************************************************/

//#define VDB_LOG_NOTE_OFF

#ifndef __STANDALONE__
  #include <linux/kernel.h>     // We're doing kernel work
  #include <linux/module.h>     // Specifically, a module 
  #include <asm/uaccess.h>  // for get_user and put_user 
  #include <linux/sched.h>
  #include <linux/spinlock_types.h>
  #include <linux/spinlock.h>
  #include <linux/wait.h>
  #include <linux/slab.h>	// for malloc and free
  #include <linux/types.h>
  #include <linux/delay.h>	// for msleep
  #include <asm/io.h>   // for ioremap
  
  #include "csi_types.h"
  uint32_t SONY_DRV_ExpControl(enum CSI_IDX aCsiIdx, uint32_t *apHist);
  
#else // #ifndef __STANDALONE__
  //#include "s32vs234.h"
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <stdint.h>
  #include <string.h>
  #include <oal.h>
  
  #include "seq_sa_kernel_api.h"
  
  #include "csi.h"
  #include "sony_func.h"

  extern void SeqSigHandler(int aSigNum, int aValue); 
#endif // else from #ifndef __STANDALONE__

#include "seq.h"
#include "seq_func.h"
#include "fdma.h"
#include "vdb_log.h"
#include "vdlist.h"

//*****************************************************************************
// constants
//*****************************************************************************
//#define IRQ_DEBUG

#define SEQ_ISP0_TDT_IDX    0     ///< index of ISP 0 transfer descriptor table
#define SEQ_ISP1_TDT_IDX    1     ///< index of ISP 1 transfer descriptor table
#define SEQ_USER_TDT_IDX    2     ///< index of USER  transfer descriptor table

//*****************************************************************************
// local types
//*****************************************************************************

typedef void(*MsgInstantService_t)(void);

//*****************************************************************************
// global data
//*****************************************************************************
float	gFPS		= 0.0f;
jiffy_t	gTimeDeltaStart	= 0;
jiffy_t	gTimeDeltaEnd	= 0;

//*****************************************************************************
// global functions
//*****************************************************************************

//*****************************************************************************
// local functions
//*****************************************************************************

/****************************************************************************/
/** Initializes Sequencer driver internal data.
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SeqDrvDataInit(void);

/****************************************************************************/
/** Registers Sequencer IRQs.
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SeqIrqsRequest(void);

/****************************************************************************/
/** Releases Sequencer IRQs.
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
void SeqIrqsFree(void);

/****************************************************************************/
/** Puts Sequencer HW into reset.
* 
*****************************************************************************/
void SeqHWreset(void);

/****************************************************************************/
/** Maps Sequencer register space, PRAM, CRAM and KRAM.
*  
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SeqMap(void);

/****************************************************************************/
/** UnMaps Sequencer register space, PRAM, CRAM and KRAM.
*  
*****************************************************************************/
void SeqUnmap(void);

/****************************************************************************/
/** Maps IPUS0..7 and IPUV0..3 register banks.
*  
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE otherwise 
*****************************************************************************/
int32_t IpuMap(void);

/****************************************************************************/
/** Unmaps all mapped IPUS/Vs
*  
*****************************************************************************/
void IpuUnmap(void);

/****************************************************************************/
/** Sequencer "Outbound message" IRQ handler.
*  
* \param aIrq	IRQ number invoking the handler
* \param apDev_id	pointer to device specific data (ignored) 
* 
* \return IRQ_HANDLED
*
*****************************************************************************/
irqreturn_t SEQ_MsgIrqHandler(int32_t aIrq, void *apDev_id);

/***************************************************************************/
/** Prints out the memory content by bytes, 4 bytes to one row.
 *
 * \param apMem base memory address to be printed
 * \param aSize number of bytes to print
 * \param apCation string caption to be printed before the memory print
 *
 * \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
 ***************************************************************************/
void MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption);

/****************************************************************************/
/** Instant FrameDone message response.
* 
* \note Does only the time critical part. The rest left to the tasklet.
* 
*
*****************************************************************************/
static inline void MsgFrameDoneInstant(void);

/****************************************************************************/
/** FrameDone message handler.
* 
*****************************************************************************/
static inline void MsgFrameDone_Handler(void);

/****************************************************************************/
/** Sequencer Done message handler.
* 
*****************************************************************************/
static inline void MsgSeqDone_Handler(void);

/***************************************************************************/
/** Downloads sequencer firmware to CRAM.
 *
 * \param apSeqFw Sequencer firmware structure.
 *
 * \return SEQ_DRV_SUCCESS if all OK, otherwise SEQ_DRV_FAILURE
 ***************************************************************************/
uint32_t FwDownload(struct SeqFw *apSeqFw);

/***************************************************************************/
/** Incomming MSG IRQ handler.
 *
 ***************************************************************************/
void SEQ_DRV_IrqMsgProcess(void);

/***************************************************************************/
/** Outgoing MSG ACK IRQ handler.
 *
 ***************************************************************************/
void SEQ_DRV_IrqMsgAckProcess(void);

/****************************************************************************/
/** Handler for Sequencer message IRQ.
* 
* \param aIrq     irq number
* \param apDev_id identification of the device
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
irqreturn_t SEQ_MsgIrqHandler(int32_t aIrq, void *apDev_id);

#ifndef __STANDALONE__
  /****************************************************************************/
  /** Handler for HOST message acknowledge IRQ in Linux.
  * 
  * \param aIrq     irq number
  * \param apDev_id identification of the device
  * 
  * \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
  *
  *****************************************************************************/
  irqreturn_t SEQ_MsgAckIrqHandler(int32_t aIrq, void *apDev_id);
#else
  /****************************************************************************/
  /** Handler for HOST message acknowledge IRQ on STANDALONE.
  *
  *****************************************************************************/
  void SEQ_MsgAckIrqHandler(void);
#endif // #ifndef __STANDALONE__

/****************************************************************************/
/** Does Message related deffered work.
* 
* \param aArg not used
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
void SEQ_S2hMsgTasklet(unsigned long aArg);

/****************************************************************************/
/** Sets up and schedules a timer.
* \note Fixed behavior as watch dog for Sequencer's in-time-response check.
* \TODO: make it configurable.
*****************************************************************************/
void SEQ_WDTSchedule(void);

/****************************************************************************/
/** Removes a previously scheduled timer.
* \note Fixed behavior as watch dog for Sequencer's in-time-response check.
* \TODO: make it configurable.
*****************************************************************************/
void SEQ_WDTRemove(void);

/****************************************************************************/
/** Initializes specified messaging pool message pool.
*
* Computes wrapparound if needed.
* 
* \param apMsgPool pointer to messaging pool
* \param apMsgBase pointer to first message in the pool
* \param aMsgCnt   number of messages in the pool
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
void SEQ_MsgPoolInit(SEQ_MessagePool_t *apMsgPool, uint8_t* apMsgBase, uint32_t aMsgCnt);

/****************************************************************************/
/** Shifts write pointer in message pool.
*
* Computes wrapparound if needed. In case of an owerflow the write pointer is
* set to NULL and SEQ_DRV_FAILURE is returned.
* 
* \param apMsgPool pointer to messaging pool
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_MsgPoolWriteShift(SEQ_MessagePool_t *apMsgPool);

/****************************************************************************/
/** Shifts read pointer in message pool.
* 
* Computes wrapparound if needed. If the pool is empty already, SEQ_DRV_FAILURE  
* is returned.
* 
* \param apMsgPool pointer to messaging pool
* 
* \return SEQ_DRV_SUCCESS if all ok, SEQ_DRV_FAILURE if pool empty already
*
*****************************************************************************/
int32_t SEQ_MsgPoolReadShift(SEQ_MessagePool_t *apMsgPool);


void SEQ_DRV_IrqIpusdoneProcess(void);
void SEQ_DRV_IrqIpuvdoneProcess(void);
void SEQ_DRV_IrqOtherdoneProcess(void);
void SEQ_DRV_IrqSwEventProcess(void);
static void SEQ_DRV_IpuHistRead(SEQ_IpuHist_t *apHist);

/****************************************************************************/
/** Sends a signal to registered user process.
* 
* \param aPid   process PID
* \param aValue value to be passed with the signal
* 
* \return SEQ_DRV_SUCCESS if all ok, SEQ_DRV_FAILURE if pool empty already
*
*****************************************************************************/
int32_t Sig2UsrSend(pid_t aPid, int32_t aValue);

#ifdef __ARMV8

///< not optimized byte-wise memset is required
#define memset MemSet32

void MemSet32(void* apDst, uint8_t aVal, size_t aSize)
{
  size_t i;
  uint8_t *lpDst = (uint8_t*)apDst;
  for(i = 0; i < aSize; i++)
  {
    lpDst[i] = aVal;
  } // for all data
} // MemSet32()

#endif

//*****************************************************************************
// global data
//*****************************************************************************

extern struct SeqFw gSeqFw;

#ifdef __KERNEL__
  char     gSeqMode   = SEQ_MODE; // exported to inform other Linux modules
#endif //#ifdef __KERNEL__

uint32_t gSeqStatus = SEQ_STATUS_OFF;

// pointer to fdma driver event handler
int32_t (*gpSEQ_FdmaEventHandler)(uint32_t aTdIdx, uint32_t aEventType);

// tasklet for message defered processing
DECLARE_TASKLET(gSeqMsg_tasklet, SEQ_S2hMsgTasklet, 0);

// Ready after boot message received (0 = NO, YES > 0)
// initially set to 1 - reset required
char gSeqRab = 1;

typedef volatile struct IPUS_tag SEQ_IpusRegs_t;

unsigned long gSeqStartTick = 0UL;
unsigned long gLastFrmDone  = 0UL;
unsigned long gFrmDoneAvg = 0UL;
unsigned long gFrmDoneCnt = 0UL;

//*****************************************************************************
// local data
//*****************************************************************************

///< array of IPUx physical addresses
static volatile void* sppIpuPtrs[IPUS_CNT + IPUV_CNT] = { 
  (volatile void*)&IPUS_0, (volatile void*)&IPUS_1, (volatile void*)&IPUS_2, 
  (volatile void*)&IPUS_3, (volatile void*)&IPUS_4, (volatile void*)&IPUS_5,
  (volatile void*)&IPUS_6, (volatile void*)&IPUS_7, (volatile void*)&IPUV_0, 
  (volatile void*)&IPUV_1, (volatile void*)&IPUV_2, (volatile void*)&IPUV_3};

///< IPUS/V addresses after mapping                            
static SEQ_IpusRegs_t *sppIpusRegs[8] = {NULL};
static SEQ_IpuvRegs_t *sppIpuvRegs[4] = {NULL};

// tasklet info
static uint32_t sTaskletCnt   = 0;
static uint32_t sTaskletWork  = 0;

static uint32_t sH2SmsgCnt    = 0;


// PRAM pointer
static uint8_t* spPram    = NULL;
// DBG PRAM pointer
static uint8_t* spDbgPram = NULL;
// CRAM pointer
static uint8_t* spCram    = NULL;
// KRAM pointer
static uint8_t* spKram    = NULL;

// FDMA TDT pointers
static FDMA_Td_t* sppTdt[3] = {NULL};
// FDMA TDT physical addresses
static uint32_t spPhysTdt[3] = {0};

// SEQ_CtrlBlock registers
static SEQ_CtrlBlkRegs_t *spSeqCBregs = NULL;

// SEQ_EvtCtrl registers
static SEQ_EvtCtrlRegs_t *spSeqECregs = NULL;

// *** graph slots ***
static uint8_t *spGraphSlots[3];

// sequencer messaging pools
static SEQ_MessagePool_t sS2hMsg, sH2sMsg; 

// wait queue for Sequencer Ready after boot
static wait_queue_head_t sSeqRabQueue;

// wait queue for messaging to Sequencer
static wait_queue_head_t sSeqMsgQueue;

// wait queue for Sequencer message acknowledge signal
static wait_queue_head_t sSeqAckQueue;

// pointer to sender process message structure - valid only if waiting for reply
static SEQ_Message_t *spSeqInbMsg = NULL;

// simulates the flag in messaging interface HOST->Seq
volatile uint32_t sSeqMsgReady  = 1;

// equales 1 if someone waits for Sequencer to ack message
volatile uint8_t sSeqAckWait    = 0;

// spinlock for access to outbound message
// used to synchronize between different host threads trying to send a message
static spinlock_t sSeqMsgLock;

// guards global variable access if needed
static spinlock_t sSeqGlobalLock;

// Buffer stream access lock
static spinlock_t sStreamLock;

#ifndef __STANDALONE__
  //watch dog timer
  static struct timer_list sWDTimer;
#endif

static pid_t sSeqUserPid = 0;

// buffer list management
static SEQ_FrmStream_t *spFrmStreams[FDMA_CHNL_CNT];

// index of current ISP TDT
static uint32_t sTdtIdx = 0;

// array of instant message handling routines
static MsgInstantService_t sMsgInstant[SEQ_MSG_TYPE_S2H_MAX - SEQ_MSG_TYPE_RAB];

// set to 1 if IPU profiling has finished
static uint32_t sIpuProfileDone = 0;

// which IPU provides histogram data
static uint8_t       sIpuAeIdx = 1;    // by default set to one
static uint32_t      sCSINumLines = 0; // # of lines from csi per frame

// automatic exposure ON > 1, OFF = 0
static uint8_t sAeOn = 0;

// ISP event log
static SEQ_EventRecord_t  sEventRecords[ISP_EVT_LOG_LEN];
static SEQ_EventLog_t     sEventLog = {sEventRecords, 0};
static uint8_t            sEventLogOn = 0; // by default event loggin OFF
static uint8_t            sGraphOn = 0; // by default graph is OFF

// Histograms

static SEQ_IpuHist_t *spIpuHists[IPU_HIST_CNT];
static uint32_t       spIpuHistLocks[IPU_HIST_CNT] = {0};

//*****************************************************************************

int32_t SEQ_Setup(void)
{  
  // TODO: set up driver 
  int32_t lRet = SEQ_DRV_SUCCESS;
 
  // *** initialize internal data ***
  // initialize driver data
  if(SeqDrvDataInit() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_DRV_FAILURE;
    goto data_init_failed;
  } // if driver data init failed                 

  // *** register IRQs ***
  if(SeqIrqsRequest() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_DRV_FAILURE;
    goto irq_request_failed;
  }

  //MemPrint((uint8_t*)spSeqCBregs, 0x28, "CB regs before IRQ enable\n");  
  
#ifdef SEQ_LOAD_BOOT
  // *** boot Sequencer  ***
  if(SeqBoot() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_DRV_FAILURE;
    goto seq_boot_failed;
  }
#endif // ifdef SEQ_LOAD_BOOT
  // *** Error handling ***
  if(lRet != SEQ_DRV_SUCCESS)
  {
#ifdef SEQ_LOAD_BOOT    
    seq_boot_failed:
#endif // ifdef SEQ_LOAD_BOOT    
      SeqIrqsFree();
    irq_request_failed:
      SeqUnmap();
    data_init_failed:
      ;
    lRet = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Canceling Sequencer driver insmod.\n");
  } // if error detected;
  else
  {
    
    printk("Sequencer driver ready.\n");
  } // else from if error detected
  
  return lRet;
} // SeqSetup(void)

//*****************************************************************************

int32_t SEQ_Close(void)
{  
  uint32_t i = 0;
  //write 1b to CM0p_RESET bit to reset CM0+ core
  spSeqCBregs->CLKRST.B.CM0p_RESET = 1;
  
  // assert Sequencer module reset  
  spSeqCBregs->CLKRST.B.SEQ_INT_RESET = 0;
  spSeqCBregs->CLKRST.B.CM0p_CLK_EN = 0;
  
  // cleanup driver
  SeqIrqsFree();
  SeqUnmap();
  SEQ_DRV_FrmStreamsReset();
  
  for(i = 0; i < IPU_HIST_CNT; i++)
  {
    if(spIpuHists[i] != NULL)
    {
      SEQ_DRV_IpuHistogramDisable((SEQ_IpuEngine_t)i);
    } // if enabled
  } // for all IPU hist engines
  
  return SEQ_DRV_SUCCESS;
} // SeqClose(void)

//****************************************************************************

int32_t SeqDrvDataInit()
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  uint32_t i = 0;

  // map Sequencer related blocks
  if(SeqMap() != SEQ_DRV_SUCCESS)
  {
    lRet = SEQ_DRV_FAILURE;
  } // if Sequencer mapping failed
  else
  {  
    SEQ_pram_map_t *lpCommInfo;  
    
    // ***  reset Sequencer ***
    SeqHWreset();
    
    // initialize utilities
    spin_lock_init(&sSeqMsgLock);
    spin_lock_init(&sSeqGlobalLock);
    spin_lock_init(&sStreamLock);
    init_waitqueue_head(&sSeqRabQueue);
    init_waitqueue_head(&sSeqMsgQueue);
    init_waitqueue_head(&sSeqAckQueue);
    
#ifndef __STANDALONE__
    init_timer(&sWDTimer);
#else
    sSeqUserPid = 1;
#endif //__STANDALONE__
    
    // set all Instant message handlers to null
    for(i = 0; i < (SEQ_MSG_TYPE_S2H_MAX - SEQ_MSG_TYPE_RAB); i++)
    {
      sMsgInstant[i] = NULL;
    } // for all message types
    
    // set available Instant message handlers
    sMsgInstant[SEQ_MSG_TYPE_FRAMEDONE - SEQ_MSG_TYPE_RAB]		= MsgFrameDoneInstant;
    sMsgInstant[SEQ_MSG_TYPE_IPU_PROFILE_DONE - SEQ_MSG_TYPE_RAB]	= MsgFrameDoneInstant;	// *** both are sharing the same ***

    // *** prepare messaging ***
      
    // set up message pools
    SEQ_MsgPoolInit(&sS2hMsg, 
                    &spPram[PRAM_OUT_MSG_OFF], 
                    SEQ2HOST_MESSAGE_CNT);
    SEQ_MsgPoolInit(&sH2sMsg, 
                    &spPram[PRAM_IN_MSG_OFF], 
                    HOST2SEQ_MESSAGE_CNT );
    
    // set initial message addresses
    spSeqCBregs->INMSG_ADDR.R   = (uint32_t)((uintptr_t)sH2sMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase + SEQ_PRAM_OFFSET);
    spSeqCBregs->OUTMSG_ADDR.R  = (uint32_t)((uintptr_t)sS2hMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase) + SEQ_PRAM_BASE;
    
    // fill in communication info
    lpCommInfo                  = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]);
    lpCommInfo->mOutMsgAddrOff  = (uint32_t) (SEQ_PRAM_BASE + PRAM_OUT_MSG_OFF);
    lpCommInfo->mAuxDataOff     = (uint32_t) (SEQ_PRAM_BASE + PRAM_AUX_DATA_OFF);     
    lpCommInfo->mGraphOff       = (uint32_t) (CRAM_BASE_M0  + SEQ_GRAPH_CRAM_OFFSET);    
    
    
    VDB_LOG_NOTE("PRAM map content:\nmOutMsgAddrOff: 0x%x\nmAuxDataOff: 0x%x\nmGraphOff 0x%x\n", 
                 (unsigned) lpCommInfo->mOutMsgAddrOff, 
                 (unsigned) lpCommInfo->mAuxDataOff, 
                 (unsigned) lpCommInfo->mGraphOff);
    
    // *** assign graph slots ***
    spGraphSlots[0] = spPram + PRAM_GRAPH_OFF;
    
    
    VDB_LOG_NOTE("Message pools initialized. S2h base: %p, H2s base: %p, pram base: %p\n", 
                 (void*) sS2hMsg.mpBase, 
                 (void*) sH2sMsg.mpBase, 
                 (void*) &spPram[0]
                 );
    
    // *** init Frame buffer stream pointers ***
    for(i = 0; i < FDMA_CHNL_CNT; i++)
    {
      spFrmStreams[i] = NULL;
    } // for all FDMA channels
    
    // *** reset IPUS histograms ***
    for(i = 0; i < 3/*IPUS_CNT*/; i++)
    {
      sppIpusRegs[i]->HOST_HISTCLEAR.B.HISTCLEAR = 1; // Histogram Clear Register
    } // for all IPUS
    
  } // else from if Sequencer mapping failed
  return lRet;
} // SeqDrvDataInit()

//*****************************************************************************
  
int32_t SeqMap()
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  // map CTRL BLK registers  
  spSeqCBregs = (SEQ_CtrlBlkRegs_t*) ioremap((uintptr_t)&VSEQ_CTRL_BLK, SEQ_SIZE);
  
  if(spSeqCBregs == NULL)
  {
    VDB_LOG_ERROR("Failed to map SEQ registers.\n");
    lRet = SEQ_DRV_FAILURE;
  } // if Sequencer registers not mapped
  else
  {
    // map EVT CTRL registers  
    spSeqECregs = (SEQ_EvtCtrlRegs_t*) ioremap((uintptr_t)&VSEQ_EVT_CTRL, sizeof(struct VSEQ_EVT_CTRL_tag));
    if(spSeqECregs == NULL)
    {
      VDB_LOG_ERROR("Failed to map SEQ event control registers.\n");
      lRet = SEQ_DRV_FAILURE;
    } // if Sequencer event registers not mapped
    else
    {
      // map PRAM
      spDbgPram = (uint8_t*) ioremap(DBG_PRAM_BASE, DBG_PRAM_SIZE);
      spPram    = (uint8_t*) ioremap(PRAM_BASE, PRAM_SIZE);  

      *spDbgPram = 0xfa;
      memset(spDbgPram, 0, DBG_PRAM_SIZE);
      
      if(spPram == NULL)
      {
        VDB_LOG_ERROR("Failed to map PRAM.\n"); 
        iounmap(spSeqCBregs);
        spSeqCBregs = NULL;
        lRet = SEQ_DRV_FAILURE;
      } // if PRAM not mapped
      else
      {
        // map CRAM
        spCram  = (uint8_t*) ioremap(CRAM_BASE, CRAM_SIZE);
        if(spCram == NULL)
        {
          VDB_LOG_ERROR("Failed to map CRAM.\n");    
          iounmap(spPram);
          iounmap(spDbgPram);
          iounmap(spSeqCBregs);

          spPram      = NULL;
          spDbgPram   = NULL;
          spSeqCBregs = NULL;
          lRet = SEQ_DRV_FAILURE;
        } // if CRAM registers not mapped
        else
        {
          // map KRAM
          spKram = (uint8_t*) ioremap(KRAM_BASE, KRAM_SIZE);
          if(IpuMap() != SEQ_DRV_SUCCESS)
          {
            iounmap(spKram);
            spKram = NULL;
          }

          if(spKram == NULL)
          {
            VDB_LOG_ERROR("Failed to map KRAM.\n");        
            iounmap(spPram);
            iounmap(spDbgPram);
            iounmap(spSeqCBregs);
            iounmap(spCram);

            spPram      = NULL;
            spDbgPram   = NULL;
            spSeqCBregs = NULL;
            spCram      = NULL;
            lRet = SEQ_DRV_FAILURE;
          } // if KRAM registers not mapped
          else
          {
            memset(spPram, 0, PRAM_SIZE);
            memset(spCram, 0, CRAM_SIZE);           
          } // else from if KRAM registers not mapped
        } // else from if CRAM registers not mapped
      } // else from if Pram not mapped
    } // else from if Event Ctrl registers not mapped
  } // else from if CTRL BLK not mapped
  
  return lRet;
} // SeqMap()

//*****************************************************************************

void SeqUnmap()
{  
  IpuUnmap();
  iounmap(spSeqCBregs);
  iounmap(spSeqECregs);
  iounmap(spPram);
  iounmap(spDbgPram);
  iounmap(spCram);
  iounmap(spKram);
  
  spSeqCBregs = NULL;
  spSeqECregs = NULL;
  spPram      = NULL;
  spDbgPram   = NULL;
  spCram      = NULL;
  spKram      = NULL;
} // SeqUnmap()

//*****************************************************************************

int32_t IpuMap()
{
  int32_t lRet  = SEQ_DRV_SUCCESS;
  uint32_t i    = 0;
  
  // map IPUSs registers  
  for(i = 0; i < IPUS_CNT; i ++)
  {   
    sppIpusRegs[i] = (SEQ_IpusRegs_t*) ioremap((uintptr_t)sppIpuPtrs[i], sizeof(SEQ_IpusRegs_t));
    if(sppIpusRegs[i] == NULL)
    {
      VDB_LOG_ERROR("Failed to map IPUS%u registers.\n", i);
      lRet = SEQ_DRV_FAILURE;
      break;
    } // if Sequencer registers not mapped
  } // for all IPUSs
  
  if(lRet == SEQ_DRV_SUCCESS)
  {
    // map IPUVs registers  
    for(i = 0; i < IPUV_CNT; i ++)
    {   
      sppIpuvRegs[i] = (SEQ_IpuvRegs_t*) ioremap((uintptr_t)sppIpuPtrs[i + IPUS_CNT], sizeof(SEQ_IpuvRegs_t));
      if(sppIpuvRegs[i] == NULL)
      {
        VDB_LOG_ERROR("Failed to map IPUS%u registers.\n", i);
        lRet = SEQ_DRV_FAILURE;
        break;
      } // if Sequencer registers not mapped
    } // for all IPUSs
  } // if still all ok
  
  if(lRet != SEQ_DRV_SUCCESS)
  {
    IpuUnmap();
  } // if sth failed
  
  return lRet;
} // IpuMap()

//*****************************************************************************

void IpuUnmap()
{
  uint32_t i = 0;
  
  // unmap IPUSs registers  
  for(i = 0; i < IPUS_CNT; i ++)
  {
    if(sppIpusRegs[i] != NULL)
    {
      iounmap(sppIpusRegs[i]);
    } // if mapped
  } // for all IPUSs
  
  // unmap IPUVs registers  
  for(i = 0; i < IPUV_CNT; i ++)
  {
    if(sppIpuvRegs[i] != NULL)
    {
      iounmap(sppIpuvRegs[i]);
    } // if mapped
  } // for all IPUVs
} // IpuUnmap()

//*****************************************************************************
 
int32_t SeqIrqsRequest()
{
  int32_t lRet = SEQ_DRV_SUCCESS;
#ifndef __STANDALONE__ 
  
  if (request_irq(SEQ_IRQ_MSG, &SEQ_MsgIrqHandler, IRQF_TRIGGER_RISING, SEQ_DEVICE_NAME, NULL))
  {
    lRet = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request IRQ for incomming message signal.\n");
  } // if request for MSG IRQ failed
  else
  {
    if (request_irq(SEQ_IRQ_MSG_ACK, &SEQ_MsgAckIrqHandler, IRQF_TRIGGER_RISING, SEQ_DEVICE_NAME, NULL))
    {
      lRet = SEQ_DRV_FAILURE;
      free_irq(SEQ_IRQ_MSG, NULL);
      VDB_LOG_ERROR("Failed to request IRQ for outbound message acknowlodge signal.\n");
    } // if request for MSG_ACK IRQ failed
  } // else from if request DONE IRQ failed
#else // 
  OAL_IRQInit(SEQ_DRV_IrqMsgProcess, SEQ_IRQ_MSG, 0xA0, IRQ_EDGE);
  OAL_IRQEnable(SEQ_IRQ_MSG);
  
  OAL_IRQInit(SEQ_MsgAckIrqHandler, SEQ_IRQ_MSG_ACK, 0xA0, IRQ_EDGE);
  OAL_IRQEnable(SEQ_IRQ_MSG_ACK);

#if (ISP_EVT_LOG_LEN > 0)
  OAL_IRQInit(SEQ_DRV_IrqIpusdoneProcess, SEQ_IRQ_IPUS_DONE, 0xA0, IRQ_EDGE);
  OAL_IRQEnable(SEQ_IRQ_IPUS_DONE);
  OAL_IRQInit(SEQ_DRV_IrqIpuvdoneProcess, SEQ_IRQ_IPUV_DONE, 0xA0, IRQ_EDGE);
  OAL_IRQEnable(SEQ_IRQ_IPUV_DONE);
  OAL_IRQInit(SEQ_DRV_IrqOtherdoneProcess, SEQ_IRQ_OTHER_DONE, 0xA0, IRQ_EDGE);
  OAL_IRQEnable(SEQ_IRQ_OTHER_DONE);
  
  for(i = SEQ_IRQ_SW_EVT_0; i <= SEQ_IRQ_SW_EVT_7; i++)
  {
    OAL_IRQInit(SEQ_DRV_IrqSwEventProcess, i, 0xA0, IRQ_EDGE);
    OAL_IRQEnable(i);
  } // for all SW_EVT IRQs
#endif // #if (ISP_EVT_LOG_LEN > 0)
  
#endif // eles from #ifndef __STANDALONE__ 
  return lRet;
} // SeqIrqsRequest()

//*****************************************************************************

void SeqIrqsFree()
{
#ifndef __STANDALONE__   
  free_irq(SEQ_IRQ_MSG, NULL);
  free_irq(SEQ_IRQ_MSG_ACK, NULL); 
#endif // #ifndef __STANDALONE__ 
} // SeqIrqsFree()

//*****************************************************************************

void SeqHWreset()
{
  // *** make sure Sequencer HW is in reset ***

  /*spSeqCBregs->MSGCTRL.R = 0x10001;
  spSeqCBregs->MSGCTRL.R = 0x10001;
  spSeqCBregs->MSGCTRL.R = 0x20002;*/
  spSeqCBregs->CLKRST.R = 0x3; // cm0 clock off, cm0 reset, seq int logig reset
  //spSeqCBregs->CLKRST.B.CM0p_RESET = 0;
  
  // disable IRQs to host
  spSeqCBregs->HOST_IRQ_EN.R = 0;
  
  // reset ERROR status
  spSeqCBregs->ERRSTAT.R = spSeqCBregs->ERRSTAT.R;
  
  /*spSeqCBregs->CLKRST.B.CM0p_RESET = 1;
  
  // disable IRQs to host
  spSeqCBregs->HOST_IRQ_EN.R = 0;
  
  // reset ERROR status
  spSeqCBregs->ERRSTAT.R = spSeqCBregs->ERRSTAT.R;
  
  // clear possible MSG flags 
  spSeqCBregs->MSGCTRL.R = 0x10001;
  spSeqCBregs->MSGCTRL.R = 0x20002;
  
  spSeqCBregs->CLKRST.B.SEQ_INT_RESET = 1;
  spSeqCBregs->CLKRST.B.CM0p_CLK_EN = 0;*/
} // SeqHWreset()

//*****************************************************************************

void SEQ_DRV_Reset()
{
  spin_lock(&sSeqGlobalLock);
  if((gSeqStatus == SEQ_STATUS_RESET) || (gSeqStatus == SEQ_STATUS_OFF))
  {
    spin_unlock(&sSeqGlobalLock);
    SeqHWreset();
    VDB_LOG_WARNING("SEQ NOT ON.\n");
  } // if in reset already
  else
  {
    gSeqStatus = SEQ_STATUS_RESET;
    spin_unlock(&sSeqGlobalLock);
  
    // *** make sure Sequencer HW is reseted ***
    SeqHWreset();
    
    // clean up streams
    SEQ_DRV_FrmStreamsReset();
    
    // wake up RAB queue - can time-out on its own
    gSeqRab = 0;

    wake_up(&sSeqRabQueue);
    
    // wake up MsgQueue
    spin_lock(&sSeqMsgLock);

    sSeqMsgReady = 1;
    spin_unlock(&sSeqMsgLock);
    wake_up(&sSeqMsgQueue);
    
    // wake up possible ACK queue
    spin_lock(&sSeqMsgLock);    
    SEQ_WDTRemove();

    if(spSeqInbMsg)
    {	  
      // assert condition
      sSeqAckWait = 1;
      spin_unlock(&sSeqMsgLock);
    
      VDB_LOG_NOTE("Wake up the sender.\n");
      
      // wake up sender
      wake_up(&sSeqAckQueue);
    } // if the sender is waiting
    else
    {
      spin_unlock(&sSeqMsgLock);
    }
    
    spin_lock(&sSeqGlobalLock);
    gSeqStatus = SEQ_STATUS_OFF;
    spin_unlock(&sSeqGlobalLock);  
  } // else from if in reset already  
  //MemPrint((uint8_t*)spSeqCBregs, 0x28, "CB regs after SEQ_Reset:\n");
} // SEQ_DRV_Reset()

//*****************************************************************************

uint32_t SEQ_DRV_Boot()
{  
  uint32_t lRet = SEQ_DRV_SUCCESS;
  uint32_t lRetTmp = 0;
  
  spin_lock(&sSeqGlobalLock);
  if((gSeqStatus == SEQ_STATUS_OFF) && (spSeqCBregs->CLKRST.B.CM0p_RESET == 1))
  {
    //uint32_t lTdtAddr = 0;
    
    gSeqStatus = SEQ_STATUS_BOOT;
    spin_unlock(&sSeqGlobalLock);
    
    //TDT addresses have to be assigned already by fmda module
    if(sppTdt[SEQ_ISP0_TDT_IDX] != NULL)
    {
      // enable Sequencer clock
      spSeqCBregs->CLKRST.B.CM0p_CLK_EN = 1;
      // deassert Sequencer module reset (CM0+ stays in RESET) 
      spSeqCBregs->CLKRST.B.SEQ_INT_RESET = 0;  
      // reset the Error flags just to be sure
      spSeqCBregs->ERRSTAT.R = spSeqCBregs->ERRSTAT.R;

      // enable IRQs
      if( sEventLogOn > 0)
      {
        spSeqCBregs->HOST_IRQ_EN.R = 0xff007c;
      }
      else
      {
        spSeqCBregs->HOST_IRQ_EN.R = 0xc;
      }

#if 0
      // download firmware into CRAM
      if(FwDownload(&gSeqFw) == SEQ_DRV_SUCCESS)
      {  
        // TODO:
        // download decrypted/unencrypted code into KRAM
#endif
      
        //write 0b to CM0p_RESET bit to BOOT Sequencer
        spSeqCBregs->CLKRST.B.CM0p_RESET = 0;
        
        // wait for Sequencer "Ready after boot" message
        VDB_LOG_NOTE("Waiting for Sequencer to Boot.\n");
        lRetTmp = wait_event_timeout(sSeqRabQueue, gSeqRab, SEQ_RAB_TIMEOUT);
        VDB_LOG_NOTE("Wait ended with %u\n", lRetTmp);
        
        if( lRetTmp < 2)
        {
          VDB_LOG_NOTE("Wait for Sequencer to boot timed out.\n");
          lRet = SEQ_DRV_FAILURE;
          SEQ_DRV_Reset();
        } // RAB wait timedout
        else
        {
          spin_lock(&sSeqGlobalLock);
          
          if(gSeqStatus == SEQ_STATUS_BOOT)
          {
            gSeqStatus = SEQ_STATUS_ON;
            spin_unlock(&sSeqGlobalLock);
            VDB_LOG_NOTE("Sequencer \"Ready after boot\" message received.\n");
          } // if message received
          else
          {
            spin_unlock(&sSeqGlobalLock);
            lRet = SEQ_DRV_FAILURE;
            SEQ_DRV_Reset();
            VDB_LOG_NOTE("RAB message not received. Sequencer boot failed.\n");
          } // else from if message received
        } // else from if RAB timedout
        
        gSeqRab = 0;  
#if 0
      } // if FWDownload() ok
      else
      {
        lRet = SEQ_DRV_FAILURE;
      } // else from if FWDownload() ok    
#endif
    } // if TDT found
    else
    {
      sppTdt[SEQ_USER_TDT_IDX] = NULL;
      sppTdt[SEQ_ISP0_TDT_IDX] = NULL;
      sppTdt[SEQ_ISP1_TDT_IDX] = NULL;
      VDB_LOG_ERROR("FDMA TDT not found.\n Aborting boot.\n");
      lRet = SEQ_DRV_FAILURE;
    } // else from if TDT found
  } // if Sequencer in reset
  else
  {
    spin_unlock(&sSeqGlobalLock);
    VDB_LOG_ERROR("Sequencer is not OFF. Aborting boot.\n");
    lRet = SEQ_DRV_FAILURE;
  } // else form if Sequencer in reset
  
  return lRet;
} // SEQ_DRV_Boot()
  
//*****************************************************************************

void SEQ_DRV_IrqsProcess()
{
  
  SEQ_MsgIrqHandler(111, NULL);
  //SEQ_MsgAckIrqHandler();
} // SEQ_IrqsProcess(int32_t aIrq, void *apDev_id)

//*****************************************************************************

irqreturn_t SEQ_MsgIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t ret = IRQ_HANDLED;
  SEQ_pram_map_t *lpCommInfo = NULL;
  uint8_t lChannelRelease = 1;  
  
  // remember there's work
  sTaskletWork++;
    
  if(SEQ_MsgPoolWriteShift(&sS2hMsg) != SEQ_DRV_SUCCESS)
  { 
    lChannelRelease = 0; // remember the channel cannot be released
    
    VDB_LOG_ERROR("Seq2Host message queue full.\n");
  } // if write message shift failed == pool is full
  
  
  if((sS2hMsg.mpRead->mType < SEQ_MSG_TYPE_S2H_MAX) && (sS2hMsg.mpRead->mType > SEQ_MSG_TYPE_H2S_MAX))
  {
    //invoke instant handler
    if( sMsgInstant[sS2hMsg.mpRead->mType - SEQ_MSG_TYPE_RAB] != NULL)
    {
      sMsgInstant[sS2hMsg.mpRead->mType - SEQ_MSG_TYPE_RAB]();
    } // if instant service set
    
  } // if a valid message number
  else
  {
    VDB_LOG_ERROR("Invalid Seq -> Host message type %u.\n", 
                  (unsigned) sS2hMsg.mpRead->mType);
  } // else from if a valid message number

  if(lChannelRelease == 1)
  {
    // set next message address to comm info
    lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]);
    lpCommInfo->mOutMsgAddrOff = (uint32_t)((uintptr_t)sS2hMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase + PRAM_OUT_MSG_OFF + SEQ_PRAM_BASE);
      
    // reset the message bit in CTRL_BLK_MSGCTRL register
    spSeqCBregs->MSGCTRL.R = 0x1;
  }// if msg channel should be released    
   
  // schedule deffered work
  tasklet_schedule(&gSeqMsg_tasklet);
  
  return ret;
} // SeqMsgIrqHandler()    

//*****************************************************************************

void SEQ_DRV_IrqMsgProcess()
{
  uint32_t i = 0;
  
  sTaskletWork++;
    
  if(SEQ_MsgPoolWriteShift(&sS2hMsg) != SEQ_DRV_SUCCESS)
  { 
    // mpWrite was set to NULL to remember full state
    // bit has to be reset when one message is freed
    if((sS2hMsg.mpRead->mType < SEQ_MSG_TYPE_S2H_MAX) && (sS2hMsg.mpRead->mType > SEQ_MSG_TYPE_H2S_MAX))
    {
      uint32_t lHandlerIdx = sS2hMsg.mpRead->mType - SEQ_MSG_TYPE_RAB;
      //invoke instant handler
      if( sMsgInstant[lHandlerIdx] != NULL)
      {
        //VDB_LOG_NOTE("Invoking instant handler\n");
        sMsgInstant[lHandlerIdx]();
      } // if instant service set
    } // if a valid message number
    else
    {
      VDB_LOG_ERROR("Invalid Seq -> Host message type.\n");
    } // else from if a valid message number
    
    VDB_LOG_ERROR("Seq2Host message overflow.\n");
  } // if write message shift failed == pool is full
  else
  {
    SEQ_pram_map_t *lpCommInfo = NULL;
    if((sS2hMsg.mpRead->mType < SEQ_MSG_TYPE_S2H_MAX) && (sS2hMsg.mpRead->mType > SEQ_MSG_TYPE_H2S_MAX))
    {
      uint32_t lHandlerIdx = sS2hMsg.mpRead->mType - SEQ_MSG_TYPE_RAB;
      //invoke instant handler
      if( sMsgInstant[lHandlerIdx] != NULL)
      {
        //VDB_LOG_NOTE("Invoking instant handler\n");
        sMsgInstant[lHandlerIdx]();
      } // if instant service set
      
      // len is known from the message type
    } // if a valid message number
    else
    {
      VDB_LOG_ERROR("Invalid Seq -> Host message type %u.\n", 
                    (unsigned) sS2hMsg.mpRead->mType);
    } // else from if a valid message number

    // set next message address to comm info
    lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]);
    lpCommInfo->mOutMsgAddrOff = (uint32_t)((uintptr_t)sS2hMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase + PRAM_OUT_MSG_OFF + SEQ_PRAM_BASE);
    
    // *** schedule deffered work ***
    //tasklet_schedule(&gSeqMsg_tasklet);
  
    // *** process the message
    sTaskletCnt++;
    
    // if there is any work left?
    while(sS2hMsg.mpWrite != sS2hMsg.mpRead)
    {    
      // TODO: return back to mpRead
      // remember oldest message pointer
      SEQ_Message_t *pMsg = sS2hMsg.mpRead;
      //SEQ_Message_t *pMsg = sS2hMsg.mpBase;
      
      // TODO: process the oldest message    
      switch(pMsg->mType)
      {
        //case 0x1234:
        case SEQ_MSG_TYPE_RAB: 
        {
          // remember Ready after boot message was received and wake up
          gSeqRab = 1;
          wake_up(&sSeqRabQueue);
          
        } // case SEQ_MSG_TYPE_RAB
        break;
        
        case SEQ_MSG_TYPE_SEQDONE:
        {
          // lock WORK and DONE queues

          MsgSeqDone_Handler();
          
          // unlock WORK and DONE queues
        } // case SEQ_MSG_TYPE_SEQDONE
        break;
        case SEQ_MSG_TYPE_IPU_PROFILE_DONE:
        {
          sIpuProfileDone = 1; // remember profiling has finished
        } // case SEQ_MSG_TYPE_IPU_PROFILE_DONE
        // *** fall through is intended ***
        case SEQ_MSG_TYPE_FRAMEDONE:
        {      
          // lock WORK and DONE queues
          gFrmDoneCnt++;
#ifdef ISP_FRAME_RATE_MEASURE_NUM
          unsigned long now = jiffies;
          if(gLastFrmDone)
          {
            gFrmDoneAvg += (now-gLastFrmDone);
            
            if(ISP_FRAME_RATE_MEASURE_NUM == gFrmDoneCnt)
            {
              gFPS = 1.0e6/((float)gFrmDoneAvg/ISP_FRAME_RATE_MEASURE_NUM);
            } // if all frames captured
          } // if gLastFrmDone not zero
          gLastFrmDone = now;
#endif // ISP_FRAME_RATE_MEASURE_NUM
          MsgFrameDone_Handler();

          // unlock WORK and DONE queues
	  
        } // SEQ_MSG_TYPE_FRAMEDONE
        break;
        case SEQ_MSG_TYPE_FDMADONE:
        {
          if(gpSEQ_FdmaEventHandler)
          {
            SEQM_fdma_event_t *lpEvent = (SEQM_fdma_event_t*) pMsg->mData;
            gpSEQ_FdmaEventHandler(lpEvent->mTdIdx, FDMA_DONE_EVENT);
          }
        } // case SEQ_MSG_TYPE_FDMADONE
        break;
        case SEQ_MSG_TYPE_FDMAERROR:
        {
          if(gpSEQ_FdmaEventHandler)
          {
            SEQM_fdma_event_t *lpEvent = (SEQM_fdma_event_t*) pMsg->mData;
            gpSEQ_FdmaEventHandler(lpEvent->mTdIdx, FDMA_ERR_EVENT);
          }
        } // case SEQ_MSG_TYPE_FDMAERROR
        break;
        case SEQ_MSG_TYPE_FDMACRCERROR:
        {
          if(gpSEQ_FdmaEventHandler)
          {
            SEQM_fdma_event_t *lpEvent = (SEQM_fdma_event_t*) pMsg->mData;
            gpSEQ_FdmaEventHandler(lpEvent->mTdIdx, FDMA_ERR_EVENT);
          }
        } // case SEQ_MSG_TYPE_FDMACRCERROR
        break;
        case SEQ_MSG_TYPE_BUFFOVF:
        {
          ;
        } // case SEQ_MSG_TYPE_BUFFOVF
        break;
        case SEQ_MSG_TYPE_OTHERERROR:
        {
          gLastFrmDone = 8846;
        } // case SEQ_MSG_TYPE_OTHERERROR
        break;
        case SEQ_MSG_TYPE_GET_IDLE_CNT:
        {
//	  for(volatile uint32_t w=0; w<100000; w++);
        } // case SEQ_MSG_TYPE_GET_IDLE_CNT
        break;
        case SEQ_MSG_TYPE_DELTA_START:
        {
          gTimeDeltaStart = jiffies;
        } // case SEQ_MSG_TYPE_DELTA_START
        break;
        case SEQ_MSG_TYPE_DELTA_END:
        {
#ifdef __STANDALONE__  
          SEQM_delta_t*   pDelta    = (SEQM_delta_t*)pMsg->mData;
        
          volatile jiffy_t  delta   = gTimeDeltaEnd - gTimeDeltaStart;  // *** delta in uSec ***
          volatile float  tDeltaSec = ((float)delta)*1.0e-6;
          volatile float  tSeqCyc   = 1.0f/175.0e6; //250.0e6;
          volatile float  nCycle    = tDeltaSec/tSeqCyc;
          volatile float  tSingle   = nCycle/pDelta->mDelta;
          volatile float  tNetto    = tSingle - 5.0f;
          volatile float  fCore   = (8.0f * (float)pDelta->mDelta*1.0e6)/(float)delta;
          
          for(;;);  // *** you can break here ***
#endif // ifdef __STANDALONE__
          gTimeDeltaEnd = jiffies;

        } // case SEQ_MSG_TYPE_DELTA_STOP
        break;
        default:
        {
          ;
        } // default
        break;
      }; // switch message type
    
      // shift read pointer
      if(SEQ_MsgPoolReadShift(&sS2hMsg) != SEQ_DRV_SUCCESS)
      {
        VDB_LOG_ERROR("Message pool read shift failed.\n");
        //break;
      } // if read shift failed
      else
      {
        i++;
        // reenable S2H messaging if pool was full  
        if( sS2hMsg.mpWrite == NULL)
        {
          SEQ_pram_map_t *lpCommInfo = NULL;
          // set next message address to comm info
          lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]);
          lpCommInfo->mOutMsgAddrOff = (uint32_t)((uintptr_t)sS2hMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase + PRAM_OUT_MSG_OFF + SEQ_PRAM_BASE);

                // reset the message bit in CTRL_BLK_MSGCTRL register
          spSeqCBregs->MSGCTRL.B.OUTBOUND_MSG_RDY = 1;
        } // if pool was full
      } // else from if read shift failed
      
      // send message to user app
      Sig2UsrSend(sSeqUserPid, pMsg->mType);
    } // while there is a message pending 
  
    // reset the message bit in CTRL_BLK_MSGCTRL register
    spSeqCBregs->MSGCTRL.R = 0x1;
        
  } // else from if write message shift failed

  
} // SEQ_DRV_IrqMsgProcess(int32_t aIrq, void *apDev_id)

//*****************************************************************************

#ifndef __STANDALONE__
irqreturn_t SEQ_MsgAckIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t ret = IRQ_HANDLED;
  
  // remove watch dog timer
  SEQ_WDTRemove();  
#else
void SEQ_MsgAckIrqHandler()
{
#endif //#ifndef __STANDALONE__  

  // reset the message bit in CTRL_BLK_MSGCTRL register
  spSeqCBregs->MSGCTRL.R = 0x20000;
  
  // *** if required wake up the sender ****
  if(spSeqInbMsg)
  {
    // copy message content
    *spSeqInbMsg = *sH2sMsg.mpBase;
        
    // assert condition
    sSeqAckWait = 1;
    
    // wake up sender
    wake_up(&sSeqAckQueue);
  } // if the sender is waiting
  
  //TODO: move WAKEING UP to tasklet !!!
  // reenable channel
  sSeqMsgReady = 1;     

  // wake up other possible senders
  wake_up_interruptible(&sSeqMsgQueue);

#ifndef __STANDALONE__
  return ret;
#endif // ifndef __STANDALONE__
} // SeqMsgAckIrqHandler()

//*****************************************************************************

void SEQ_DRV_IrqMsgAckProcess()
{  
  // reset the message bit in CTRL_BLK_MSGCTRL register
  spSeqCBregs->MSGCTRL.R = 0x20000;
    
  // *** if required wake up the sender ****
  if(spSeqInbMsg)
  {
    // copy message content
    *spSeqInbMsg = *sH2sMsg.mpBase;
        
    // assert condition
    sSeqAckWait = 1;
    
    // wake up sender
    wake_up(&sSeqAckQueue);
  } // if the sender is waiting
  
  VDB_LOG_NOTE("Wake up next sender.\n");
  
  //TODO: move WAKEING UP to tasklet !!!
  // reenable channel
  sSeqMsgReady = 1;     

  // wake up other possible senders
  wake_up_interruptible(&sSeqMsgQueue);
} // SEQ_DRV_IrqMsgAckProcess(int32_t aIrq, void *apDev_id)

//*****************************************************************************

void SEQ_DRV_IrqIpusdoneProcess()
{
#if (ISP_EVT_LOG_LEN > 0)
  SEQ_EventRecord_t *lpEvent = &(sEventLog.mpRecords[sEventLog.mNextRecIdx++]);
  if(sEventLog.mNextRecIdx > (ISP_EVT_LOG_LEN - 1)) 
  {
    sEventLog.mNextRecIdx = ISP_EVT_LOG_LEN - 1;
  }
  lpEvent->mEvent.R = (ISP_LOGEVT_IPUS << 26)|(spSeqECregs->IPUS_CNTR_ALLEVT.R & 0x000000ff);
  lpEvent->mTime  = jiffies();
#endif // #if (ISP_EVT_LOG_LEN > 0)
} // SEQ_DRV_IrqIpusdoneProcess

//*****************************************************************************

void SEQ_DRV_IrqIpuvdoneProcess()
{
#if (ISP_EVT_LOG_LEN > 0)
  SEQ_EventRecord_t *lpEvent = &(sEventLog.mpRecords[sEventLog.mNextRecIdx++]);
  if(sEventLog.mNextRecIdx > (ISP_EVT_LOG_LEN - 1)) 
  {
    sEventLog.mNextRecIdx = ISP_EVT_LOG_LEN - 1;
  }
  lpEvent->mEvent.R = (ISP_LOGEVT_IPUV << 26)|(spSeqECregs->IPUV_CNTR_ALLEVT.R & 0x0000000f);
  lpEvent->mTime  = jiffies();
#endif // #if (ISP_EVT_LOG_LEN > 0)
} // SEQ_DRV_IrqIpuvdoneProcess

//*****************************************************************************

void SEQ_DRV_IrqOtherdoneProcess()
{
#if (ISP_EVT_LOG_LEN > 0)
  SEQ_EventRecord_t *lpEvent = &(sEventLog.mpRecords[sEventLog.mNextRecIdx++]);
  if(sEventLog.mNextRecIdx > (ISP_EVT_LOG_LEN - 1)) 
  {
    sEventLog.mNextRecIdx = ISP_EVT_LOG_LEN - 1;
  }
  lpEvent->mEvent.R = (ISP_LOGEVT_OTHER << 26)|(spSeqECregs->OTHR_CNTR_ALLEVT.R & 0x03ffffff);
  
  lpEvent->mTime  = jiffies();
#endif // #if (ISP_EVT_LOG_LEN > 0)
} // SEQ_DRV_IrqOthedoneProcess

//*****************************************************************************

void SEQ_DRV_IrqSwEventProcess()
{
#if (ISP_EVT_LOG_LEN > 0)
  SEQ_EventRecord_t *lpEvent = &(sEventLog.mpRecords[sEventLog.mNextRecIdx++]);
  if(sEventLog.mNextRecIdx > (ISP_EVT_LOG_LEN - 1)) 
  {
    sEventLog.mNextRecIdx = ISP_EVT_LOG_LEN - 1;
  }
  lpEvent->mEvent.R = (ISP_LOGEVT_SW_EVT << 26)|(spSeqECregs->SW_EVT_TRIG.R & 0x000000ff);
  
  lpEvent->mTime  = jiffies();  
  spSeqECregs->SW_EVT_CLR_DONE.R = (spSeqECregs->SW_EVT_TRIG.R & 0x000000ff);
#endif // #if (ISP_EVT_LOG_LEN > 0)
} // SEQ_DRV_IrqSwEventProcess()

//*****************************************************************************

int32_t Sig2UsrSend(pid_t aPid, int32_t aValue)
{
  int32_t ret = IRQ_HANDLED;
#ifndef __STANDALONE__
  struct siginfo info;
  struct pid *pid_struct;
  struct task_struct *t;
    
  // send the signal to user space
  memset(&info, 0, sizeof(struct siginfo));
  info.si_signo = SEQ_EVENT_SIGNAL;
  info.si_code = SI_QUEUE;
  info.si_int = (aValue);
  rcu_read_lock();
  pid_struct = find_get_pid(aPid);
  t = pid_task(pid_struct,PIDTYPE_PID);
  if(t == NULL){
    VDB_LOG_ERROR("No such pid %u. Signal not sent.\n", (unsigned) aPid);
    rcu_read_unlock();
    ret = -1;
  } // if no such pidRegisterred
  else
  {
    rcu_read_unlock();
    ret = send_sig_info(SEQ_EVENT_SIGNAL, &info, t);    //send the signal
    if (ret < 0) {
      VDB_LOG_ERROR("Error sending signal to user space.\n");
    } // if sending signal failed
  } // else if no such pid
#else // #ifndef __STANDALONE__
  SeqSigHandler((int)SEQ_EVENT_SIGNAL, (int)aValue);
#endif // else from #ifndef __STANDALONE__
  return ret;
} // Sig2UsrSend()
 
//*****************************************************************************

void SEQ_S2hMsgTasklet(unsigned long aArg)
{ 
  uint32_t lTaskletCnt = ++sTaskletCnt;
  
  VDB_LOG_NOTE("I'm the tasklet running for the %d. time, there is %u of work\n", 
               (int) sTaskletCnt, 
               (unsigned) sTaskletWork);
  
  //printk("tasklet\n");
  
  // if there is any work left?
  while(sS2hMsg.mpWrite != sS2hMsg.mpRead)
  {    
    // remember oldest message pointer
    SEQ_Message_t *pMsg = sS2hMsg.mpRead;
        
    VDB_LOG_NOTE("S2h MSG pointer: %p \n", (void*) sS2hMsg.mpRead);
    //printk("  work\n");
    // process the oldest message    
    switch(pMsg->mType)
    {
      //case 0x1234:
      case SEQ_MSG_TYPE_RAB: 
      {
        // remember Ready after boot message was received and wake up
        gSeqRab = 1;
        wake_up(&sSeqRabQueue);
        VDB_LOG_NOTE("Sequencer \"Ready after boot\" message received.\n");
        //printk("  RAB\n");
      } // case SEQ_MSG_TYPE_RAB
      break;
      
      case SEQ_MSG_TYPE_SEQDONE:
      {
        VDB_LOG_NOTE("SEQDONE message received.\n");
      } // default
      break;
      case SEQ_MSG_TYPE_IPU_PROFILE_DONE:
      {
        sIpuProfileDone = 1; // remember profiling has finished
      } // case SEQ_MSG_TYPE_IPU_PROFILE_DONE
      case SEQ_MSG_TYPE_FRAMEDONE:
      {
        VDB_LOG_NOTE("FRAMEDONE message received.\n");
        gFrmDoneCnt++;
        #ifdef ISP_FRAME_RATE_MEASURE_NUM
          unsigned long now = jiffies;
          if(gLastFrmDone)
          {
            gFrmDoneAvg += (now-gLastFrmDone);
            
            if(ISP_FRAME_RATE_MEASURE_NUM == gFrmDoneCnt)
            {
              volatile float timePerFrameMS = ((float)gFrmDoneAvg/ISP_FRAME_RATE_MEASURE_NUM);
              volatile float fps = 1.0e6/timePerFrameMS;
              for(;;);
            } // if all frames captured
          } // if gLastFrmDone not zero
          gLastFrmDone = now;
        #endif // ISP_FRAME_RATE_MEASURE_NUM
        MsgFrameDone_Handler();
      } // default
      break;
      case SEQ_MSG_TYPE_FDMADONE:
      {
        VDB_LOG_NOTE("FDMADONE message received.\n");
      } // default
      break;
      case SEQ_MSG_TYPE_FDMAERROR:
      {
        VDB_LOG_NOTE("FDMAERROR message received.\n");
      } // default
      break;
      case SEQ_MSG_TYPE_FDMACRCERROR:
      {
        VDB_LOG_NOTE("FDMACRCERROR message received.\n");
      } // default
      break;
      case SEQ_MSG_TYPE_BUFFOVF:
      {
        VDB_LOG_NOTE("BUFFOVF message received.\n");
      } // default
      break;
      case SEQ_MSG_TYPE_OTHERERROR:
      {
        VDB_LOG_NOTE("OTHERERROR message received.\n");
        VDB_LOG_NOTE("Message: %s\n",&spPram[PRAM_AUX_DATA_OFF]);
      } // default
      break;
      case SEQ_MSG_TYPE_ECHO:
      {
        VDB_LOG_NOTE("ECHO message received.\n");
      } // default
      break; 
      
      default:
      {
        VDB_LOG_WARNING("Unknow Sequencer message type (%u) received.\n", (unsigned) pMsg->mType);
      } // default
      break;
    }; // switch message type
    
    // *** send message ***
    if(sSeqUserPid != 0)
    {
      VDB_LOG_NOTE("Sending signal to %u.\n", sSeqUserPid);
      if(Sig2UsrSend(sSeqUserPid, pMsg->mType) != IRQ_HANDLED)
      {
        VDB_LOG_ERROR("*** FAILED to send message to user-space process %u ***\n", 
                      (unsigned) sSeqUserPid);
      } // if signal not send
      else
      {
        VDB_LOG_NOTE("*** SUCCEEDED to send message to user-space process %u ***\n", 
                      (unsigned) sSeqUserPid);
      } // else from if signal not send
    } // if there is a user
    
    // *** shift read pointer ***
    if(SEQ_MsgPoolReadShift(&sS2hMsg) != SEQ_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Message pool read shift failed.\n");
      break;
    } // if read shift failed
    else
    {
      // reenable S2H messaging if pool was full  
      if( sS2hMsg.mpWrite == NULL)
      {
        SEQ_pram_map_t *lpCommInfo = NULL;
        // set next message address to comm info
        lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]);
        lpCommInfo->mOutMsgAddrOff = (uint32_t)((uintptr_t)sS2hMsg.mpWrite - (uintptr_t)sS2hMsg.mpBase + PRAM_OUT_MSG_OFF + SEQ_PRAM_BASE);

        // reset the message bit in CTRL_BLK_MSGCTRL register
        spSeqCBregs->MSGCTRL.R = 0x1;
        VDB_LOG_NOTE("Released messaging channel after overflow.");
      } // if pool was full
    } // else from if read shift failed
    
    sTaskletWork--;
  } // while there is a message pending 
  
  VDB_LOG_NOTE("Tasklet processed %u messages %p %p.\n", 
               (unsigned) lTaskletCnt - sTaskletCnt, 
               (void*) sS2hMsg.mpRead, 
               (void*) sS2hMsg.mpWrite);
}// SEQ_S2hMsgTasklet

//*****************************************************************************

void SEQ_WDTRun(unsigned long aData)
{
  VDB_LOG_ERROR("Sequencer watch dog timer timed out. Jiffies start: %lu, now: %lu\n", (unsigned long) aData, (unsigned long) jiffies);
  // *** if the sender is waiting ****
  if(spSeqInbMsg)
  { 
    // set message type to ACK timed out
    spSeqInbMsg->mType = SEQ_MSG_TYPE_ACKTO;
    // assert acknowledged condition
    sSeqAckWait = 1;
    
    VDB_LOG_NOTE("Wakeing up sender.\n");
    // wake up sender
    wake_up(&sSeqAckQueue);
  } // if the sender is waiting
  
  // wake up other possible senders
  VDB_LOG_NOTE("Releasing outbound message channel.\n");
  sSeqMsgReady = 1;
  wake_up_interruptible(&sSeqMsgQueue);  
  
  VDB_LOG_NOTE("======== leaving WDTRun() =============\n");
} // SEQ_WDTRun()

//*****************************************************************************

void SEQ_WDTSchedule()
{
  // TODO: in case of Host->Seq MSG queue add synchronization
  // register the timer
#ifndef __STANDALONE__    
  sWDTimer.data = (unsigned long)jiffies;
  sWDTimer.function = SEQ_WDTRun;
  sWDTimer.expires = jiffies + SEQ_WDT_TIMEOUT; // parameter

  add_timer(&sWDTimer);    
  VDB_LOG_NOTE("\n**************** Timer scheduled (jiffies %lu)\n", (unsigned long) sWDTimer.data);
#endif // #ifndef __STANDALONE__  
} // SEQ_WDTSchedule()

//*****************************************************************************

void SEQ_WDTRemove()
{
  // TODO: in case of Host->Seq MSG queue add synchronization
  // remove the timer
#ifndef __STANDALONE__  
  del_timer(&sWDTimer);
#endif // #ifndef __STANDALONE__  
  VDB_LOG_NOTE("\n********************** Timer removed (jiffies %lu)\n", (unsigned long)jiffies);
} // SEQ_WDTRemove()

//*****************************************************************************

int32_t SEQ_FdmaTdSchedule(uint32_t aTdIdx)
{
  int32_t ret = SEQ_DRV_SUCCESS;
  
  VDB_LOG_NOTE("Invoking fDMA TD scheduling.\n");
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  gpSEQ_FdmaEventHandler(aTdIdx, FDMA_DONE_EVENT);
  
  return ret;
} // SEQ_FdmaTdSchedule(uint32_t aTdIdx);

//*****************************************************************************

int32_t SEQ_DRV_MsgSend(SEQ_Message_t *apMsg, uint8_t aWait)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  
  // get Sequencer message spinlock
  spin_lock(&sSeqMsgLock);
 
  // remember who's sending the message
#ifndef __STANDALONE__
  sSeqUserPid = current->pid;
#else
  sSeqUserPid = 1;
#endif 
  
  // while channel in use
  while(sSeqMsgReady == 0)
  {
    int32_t wait_ret = 0;
    // release spinlock
    spin_unlock( &sSeqMsgLock);
    //MemPrint((uint8_t*) spSeqCBregs, 0x28, "Seq regs:\n");
    wait_ret = wait_event_interruptible(sSeqMsgQueue, sSeqMsgReady);
    if(wait_ret == -ERESTARTSYS)
    {
      //MemPrint((uint8_t*)spSeqCBregs, 0x28, "SEQ regs of wait interrupted:\n");
      lRet = -ERESTARTSYS;
      break;
    } // if interrupted
    // get spinlock to synchronize bettween possible more threads
    spin_lock( &sSeqMsgLock);
  } // while message in use
  
  if(lRet == SEQ_DRV_SUCCESS)
  {
    spin_lock(&sSeqGlobalLock);
    if(gSeqStatus == SEQ_STATUS_ON)
    {
      uint32_t lMsgOffset = 0;
      spin_unlock(&sSeqGlobalLock);
     
      // set message content
      *sH2sMsg.mpBase = *apMsg;
	
      // remember wait state
      spSeqInbMsg = (aWait > 0) ? apMsg : NULL;
      sSeqAckWait = 0;
      
      if(aWait)
      {
        VDB_LOG_NOTE("Wait required.");
      }
      
      // print seq regs before generating a message
      //MemPrint((uint8_t*)spSeqCBregs, 0x28, "Seq CBregs before sending a msg:\n");
      
      // prepare message
      lMsgOffset = (uint32_t)((uintptr_t)sH2sMsg.mpBase - (uintptr_t)spPram + SEQ_PRAM_OFFSET);
      spSeqCBregs->INMSG_ADDR.R = lMsgOffset;
	
      // set channel to "in use"
      sSeqMsgReady = 0;
      sH2SmsgCnt++;
      VDB_LOG_NOTE("Message to Sequencer #%u was sent (msg offset 0x%x).\n", 
                   (unsigned) sH2SmsgCnt, 
                   (unsigned) lMsgOffset);
      
      // schedule the watch dog timer
      //SEQ_WDTSchedule();
      
      // release spinlock
      spin_unlock(&sSeqMsgLock);
      
      // send the message
      spSeqCBregs->INMSG_LEN.B.INBOUND_MSG_LEN = sizeof(SEQ_Message_t);
      
      // if required, wait for Sequencer to acknowledge
      if(aWait)
      {
        VDB_LOG_NOTE("Waiting for Sequencer to replay.\n");
        // wait for acknowledge event - cannot be interruptible 
        wait_event(sSeqAckQueue, sSeqAckWait);
        
        *apMsg = *sH2sMsg.mpBase;  // read back the message
        
        VDB_LOG_NOTE("ACK wait finished.\n");
      } // if we should wait for the acknowledge
    } // if SEQ is on
    else
    {
      spin_unlock(&sSeqGlobalLock);
      VDB_LOG_WARNING("SEQ is not ON. Aborting MSG.\n");
      MemPrint((uint8_t*)spSeqCBregs, 0x28, "SEQ regs of wait interrupted:\n");
      lRet = SEQ_DRV_FAILURE;
    } // else from if SEQ on   
  } // if all ok so far
  else
  {
//    VDB_LOG_ERROR("FAILED to send the message.");
    // release spinlock
    spin_unlock(&sSeqMsgLock);
  } // else from if all ok so far
  // print seq regs before generating a message
  //MemPrint((uint8_t*)spSeqCBregs, 0x28, "Seq CBregs after sending a msg:\n");
  return lRet;
} // SEQ_DRV_MsgSend()

//*****************************************************************************

void SEQ_MsgPoolInit(SEQ_MessagePool_t *apMsgPool, uint8_t* apMsgBase, uint32_t mMsgCnt)
{
  apMsgPool->mpWrite =  apMsgPool->mpRead = apMsgPool->mpBase = 
                        (SEQ_Message_t*) apMsgBase;
  apMsgPool->mpLast = (SEQ_Message_t*)((uintptr_t)(apMsgPool->mpBase) + \
                      sizeof(SEQ_Message_t) * (mMsgCnt - 1));
} // SEQ_MsgPoolInit(SEQ_MessagePool_t *apMsgPool, char* apMsgBase)

//*****************************************************************************

int32_t SEQ_MsgPoolWriteShift(SEQ_MessagePool_t *apMsgPool)
{
  int32_t ret = SEQ_DRV_SUCCESS;
    
  if( apMsgPool->mpWrite )
  {  
    SEQ_Message_t *pNext = (apMsgPool->mpWrite + 1);
    if( pNext > apMsgPool->mpLast)
    {
      pNext = apMsgPool->mpBase;
    } // if wrapparound
    if(pNext == apMsgPool->mpRead)
    {
      // remember overflow
      ret = SEQ_DRV_FAILURE;
      pNext = NULL;
    } // if message pool overflow 
    apMsgPool->mpWrite = pNext;
  } // if no unresolved overflow
  else
  {
    ret = SEQ_DRV_SUCCESS;
  } // else from if no unresolved overflow
    
  return ret;
} // SEQ_MsgPoolWriteShift(SEQ_MessagePool_t *apMsgPool)

//*****************************************************************************

int32_t SEQ_MsgPoolReadShift(SEQ_MessagePool_t *apMsgPool)
{
  int32_t ret = SEQ_DRV_SUCCESS;

  if(apMsgPool->mpWrite == apMsgPool->mpRead)
  {
    ret = SEQ_DRV_FAILURE;
  } // if no message to shift to
  else
  {
    SEQ_Message_t *pNext = (apMsgPool->mpRead + 1);
    if( pNext > apMsgPool->mpLast)
    {
      pNext = apMsgPool->mpBase;
    } // if wrapparound    

    apMsgPool->mpRead = pNext;
  } // else from if no message to shift to  
  
  return ret;
} // SEQ_MsgPoolReadShift(SEQ_MessagePool_t *apMsgPool)

//*****************************************************************************

static inline void MsgFrameDoneInstant()
{
#ifdef ISP_FRAME_DONE_LOG
  SEQ_EventRecord_t *lpEvent = NULL;
  lpEvent = &(sEventLog.mpRecords[sEventLog.mNextRecIdx++]);
  if(sEventLog.mNextRecIdx > (ISP_EVT_LOG_LEN - 1)) 
  {
    sEventLog.mNextRecIdx = ISP_EVT_LOG_LEN - 1;
  }
  lpEvent->mEvent.R = (ISP_LOGEVT_SEQ_FD << 26);
  lpEvent->mTime  = jiffies();
#endif // ifdef ISP_FRAME_DONE_LOG
} // MsgFrameDoneInstant()

//*****************************************************************************

static inline void MsgFrameDone_Handler()
{
  uint32_t i = 0;
  //VDB_LOG_NOTE("FrameDone instant message handler invoked.\n");
  
  // *** update transfer descriptores ***
  
  for(i = 0; i < FDMA_CHNL_CNT; i++)
  {
    SEQ_FrmStream_t *lpStream = spFrmStreams[i];
    // find ddr buffer lists
    if(lpStream != NULL)
    {
      unsigned long lFlags;
      spin_lock_irqsave(&sStreamLock, lFlags); // save the state, if locked already it is saved in flags
     
      //*** shift buffers and queues ***
      if((SEQ_FrmBuffer_t*)lpStream->mWorkQueue.mpHead->mpData != lpStream->mpNextBuffer)
      {   
        // update queues
        VDList_TailPush(&(lpStream->mDoneQueue), VDList_HeadPop(&(lpStream->mWorkQueue)));
      } // if next is different from head
      
      if(lpStream->mWorkQueue.mLength > 1)
      {   
        lpStream->mpNextBuffer = (SEQ_FrmBuffer_t*)lpStream->mWorkQueue.mpHead->mpNext->mpData;
      } // if more then one left in work queue
      
      //*** update TDT ***
      sppTdt[sTdtIdx][i].mDdrImgStartAddr = lpStream->mpNextBuffer->mPhyAddr;
      sppTdt[sTdtIdx][i].mDdrCurrLine     = 0;
      sppTdt[sTdtIdx][i].mSramCurrLine    = 0;   
      
      spin_unlock_irqrestore(&sStreamLock, lFlags); // return to the formally state specified in flags   
    } // if stream setup
  } // for all possible channels
  
  sTdtIdx = (sTdtIdx + 1)%2; 
  
  // *** fetch IPU histograms ***
  for(i = 0; i < IPU_HIST_CNT; i++)
  {
    SEQ_DRV_IpuHistRead(spIpuHists[i]);
  } // for all histogram capable IPUs
  
  // *** run auto exposure algorithm ***
#ifdef SEQ_AE_ON
  if(sAeOn)
  {
    //SONY_DRV_ExpControl(CSI_IDX_0, spIpuHists[sIpuAeIdx]->mpData);
  } // if sAeOn
#endif // if SEQ_AE_ON
} // MsgFrameDone_Handler()

//*****************************************************************************

static inline void MsgSeqDone_Handler()
{
  uint32_t i = 0;
  //VDB_LOG_NOTE("FrameDone instant message handler invoked.\n");
  
  for(i = 0; i < FDMA_CHNL_CNT; i++)
  {
    SEQ_FrmStream_t *lpStream = spFrmStreams[i];
    // find ddr buffer lists
    if(lpStream != NULL)
    {
      //*** pop clean work queue ***
      while(lpStream->mWorkQueue.mLength > 0)
      {
        ((SEQ_FrmBuffer_t*)VDList_HeadPop(&(lpStream->mWorkQueue))->mpData)->mState =  SEQ_FRM_BUFFER_STATE_USER;
      }
      
      lpStream->mpNextBuffer = NULL;
    } // if stream setup
  } // for all possible channels
  
  sTdtIdx = 0;  
  sGraphOn = 0;
} // MsgSeqDone_Handler()

//*****************************************************************************

void MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption)
{
  uint32_t i = 0;
  if( apCaption != NULL)
  {
    printk("%s", apCaption);
  } // if caption set
  
  for(i = 0; i < aSize; i++)
  {
    if((i % 4) == 0)
    {
      printk("\n%2u:\t", (unsigned) (i / 4));
    }
    printk("%2x ", (unsigned) apMem[i]);    
  }
  
  printk("\n");
} // MemPrint

//*****************************************************************************

uint32_t FwDownload(struct SeqFw *apSeqFw)
{
  uint32_t lRes = SEQ_DRV_SUCCESS;
  
  if(spCram != NULL)
  {
    uint32_t i = 0;
    
    // erase current CRAM content
    memset(spCram, 0, CRAM_SIZE);
    
    // download the data    
    for(i = 0; i < apSeqFw->mLineCnt; ++i)
    {
      // copy the firmware
      memcpy(&(spCram[apSeqFw->mpLines[i].mAddr]), apSeqFw->mpLines[i].mpData, apSeqFw->mpLines[i].mSize);
    } // for all lines
  } // if CRAM mapped  
  else
  {
    lRes = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("CRAM not mapped.\n");
  } // else if SRAM not mapped
  
  return lRes;  
} // FwDownload()

//*****************************************************************************

int32_t SEQ_DRV_GraphDownload(SEQ_GraphPackage_t *apGraph)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_GraphPackage_t lGraph;
  if (copy_from_user( &lGraph, 
                      apGraph, 
                      sizeof(SEQ_GraphPackage_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  {   
    // remember graph limits
    sCSINumLines = lGraph.mCSINumLines;
    if((lGraph.mGraphSize + lGraph.mBufferListSize) > SEQ_GRAPH_SIZE_MAX)
    {
      VDB_LOG_ERROR("Graph + Buffer list too big (0x%x bytes; max allowed 0x%x bytes).\n", 
                    (unsigned) (lGraph.mGraphSize + lGraph.mBufferListSize), 
                    (unsigned) SEQ_GRAPH_SIZE_MAX);
      lRet = -EIO;
    } // if graph too big
    else
    {
      SEQ_pram_map_t *lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]); 
      void *lpM0Graph = (void*)&spCram[lpCommInfo->mGraphOff];
      // TODO: manage the slots
      // copy the graph to apropriate slot
      if (copy_from_user(lpM0Graph, (uint8_t *)lGraph.mpGraphData, 
          lGraph.mGraphSize) != 0)
      {
        VDB_LOG_ERROR("Graph data download failed.\n");
        lRet = SEQ_DRV_FAILURE;
      } // if graph data download failed
      else 
      {
        uint16_t lBuffListOff = (uint16_t)ALIGN64(lpCommInfo->mGraphOff + lGraph.mGraphSize);
        VDB_LOG_NOTE("Graph downloaded successfully at %p.\n", 
                     (void*)  lpM0Graph);
        lpCommInfo->mBufferListOff = lBuffListOff;
        //lpCommWords[1] = (lpCommWords[1] & 0xff00) || lBuffListOff;
        if(lGraph.mpBufferList != NULL)
        {
          void *lpBufferList = (void*)((uintptr_t)spCram + lpCommInfo->mBufferListOff);
          if (copy_from_user( lpBufferList, 
                              (uint8_t *)lGraph.mpBufferList, 
                              lGraph.mBufferListSize) != 0)
          {
            uint16_t lBuffListOff = (uint16_t)0x1000;
            VDB_LOG_ERROR("Graph BufferList download failed.\n");
            lpCommInfo->mBufferListOff = lBuffListOff;
            lRet = SEQ_DRV_FAILURE;
          } // if graph data download failed
          else 
          {
            VDB_LOG_NOTE("Graph BufferList downloaded successfully at %p.\n", 
                         (void*) lpBufferList);
          } // else from if graph download failed
        } // if there is a buffer list
        else
        {
          uint16_t lBuffListOff = (uint16_t)0x1000;
          lpCommInfo->mBufferListOff = lBuffListOff;
          VDB_LOG_NOTE("No graph BufferList in the package.\n");
        } // else from if there is a buffer list
        
      } // else form if graph data download failed
    } // else from if graph too big
    
  } // else from if copy from user failed
  return lRet;
} // SEQ_DRV_GraphDownload(SEQ_GraphPackage_t *apGraph)

//*****************************************************************************

int32_t SEQ_DRV_GraphFetch(SEQ_GraphPackage_t *apGraph)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_GraphPackage_t lGraph;
  if (copy_from_user( &lGraph, 
                      apGraph, 
                      sizeof(SEQ_GraphPackage_t)) != 0)
  {
    VDB_LOG_ERROR("Copy from user failed.\n");
    lRet = -EIO;
  } // if copy from user failed
  else
  {   
    if((lGraph.mGraphSize + lGraph.mBufferListSize) > SEQ_GRAPH_SIZE_MAX)
    {
      VDB_LOG_ERROR("Graph + Buffer list too big (0x%x bytes; max allowed 0x%x bytes).\n", 
                    (unsigned) (lGraph.mGraphSize + lGraph.mBufferListSize), 
                    (unsigned) SEQ_GRAPH_SIZE_MAX);
      lRet = -EIO;
    } // if graph too big
    else
    {
      SEQ_pram_map_t *lpCommInfo = (SEQ_pram_map_t*) &(spPram[SEQ_PRAM_MAP_OFF]); 
      void *lpM0Graph = (void*)&spCram[lpCommInfo->mGraphOff];
      // copy the graph to user
      if (copy_to_user((uint8_t *)lGraph.mpGraphData, lpM0Graph, 
          lGraph.mGraphSize) != 0)
      {
        VDB_LOG_ERROR("Graph data fetch failed.\n");
        lRet = SEQ_DRV_FAILURE;
      } // if graph data fetch failed
    } // else from if graph too big
    
  } // else from if copy from user failed
  return lRet;
} // SEQ_DRV_GraphFetch(SEQ_GraphPackage_t *apGraph)

//*****************************************************************************

int32_t SEQ_DRV_GraphStart(uint32_t aFrmCnt, uint32_t aInputLines)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  
  uint32_t i = 0;
  
  // check/prepare streams
  // clean up streams
  for(i = 0; i < FDMA_CHNL_CNT; i++)
  {
    SEQ_FrmStream_t *lpStream = spFrmStreams[i];
    if(lpStream != NULL)
    {
      if(lpStream->mWorkQueue.mLength == 1)
      {
        // init FDMA transfer descriptors
        SEQ_FrmBuffer_t *lpBuffer = (SEQ_FrmBuffer_t*)lpStream->mWorkQueue.mpHead->mpData;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mDdrImgStartAddr = lpBuffer->mPhyAddr;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mDdrCurrLine     = 0;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mSramCurrLine    = 0;

        // next buffer is the same one
        lpStream->mpNextBuffer        = lpBuffer;
        
        // copy the same setup to second TDT
        sppTdt[SEQ_ISP1_TDT_IDX][i] = sppTdt[SEQ_ISP0_TDT_IDX][i];
      } // if there is exactly one buffer in WORK queue  
      else if(lpStream->mWorkQueue.mLength > 1)
      {
        // init FDMA transfer descriptor in first TDT
        SEQ_FrmBuffer_t *lpBuffer = (SEQ_FrmBuffer_t*)lpStream->mWorkQueue.mpHead->mpData;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mDdrImgStartAddr = lpBuffer->mPhyAddr;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mDdrCurrLine     = 0;
        sppTdt[SEQ_ISP0_TDT_IDX][i].mSramCurrLine    = 0;
        
        // init FDMA transfer descriptor in second TDT
        lpBuffer = (SEQ_FrmBuffer_t*)lpStream->mWorkQueue.mpHead->mpNext->mpData;
        sppTdt[SEQ_ISP1_TDT_IDX][i].mDdrImgStartAddr = lpBuffer->mPhyAddr;
        sppTdt[SEQ_ISP1_TDT_IDX][i].mDdrCurrLine     = 0;
        sppTdt[SEQ_ISP1_TDT_IDX][i].mSramCurrLine    = 0;
        
        // next buffer is the second one in workqueue
        lpStream->mpNextBuffer        = lpBuffer;
      } // if more than one buffer set in WORK queue  
      else
      {
        VDB_LOG_ERROR("Work queue for stream %u is empty. Unable to start graph.\n", i);
        lRet = SEQ_DRV_FAILURE;
      } // if ther is no buffer in work queue
    } // if stream exists
  } // for all possible streams
  
  
  // send START message to Sequencer
  if(lRet == SEQ_DRV_SUCCESS)
  {
    SEQ_Message_t   msg;
    SEQM_start_t*   pSt = (SEQM_start_t*)&msg.mData;
    
    msg.mType   = SEQ_MSG_TYPE_START;
    msg.mStatus = SEQ_MSG_STAT_READY;
    
    pSt->mNumCamLines   = (aInputLines>0)?aInputLines:sCSINumLines; ///*0x60E;*/729;
    pSt->mFDMAlistBase0 = spPhysTdt[SEQ_ISP0_TDT_IDX];
    pSt->mFDMAlistBase1 = spPhysTdt[SEQ_ISP1_TDT_IDX];
    pSt->mFrames2Grab   = aFrmCnt;

    sGraphOn = 1;
    lRet = SEQ_DRV_MsgSend(&msg, 1);
    
    gSeqStartTick = jiffies;
    
  } // if all ok so far
  
  return lRet;
} // SEQ_DRV_GraphStart()

//*****************************************************************************

int32_t SEQ_DRV_GraphStop()
{
  int32_t lRet = SEQ_DRV_SUCCESS;
   
  // send STOP message to Sequencer
  {
    SEQ_Message_t   msg;
      
    msg.mType   = SEQ_MSG_TYPE_STOP;
    msg.mStatus = SEQ_MSG_STAT_READY;

    lRet = SEQ_DRV_MsgSend(&msg, 0);
  } // send STOP message to Sequencer
  
  // check/reset streams
  
  return lRet;
} // SEQ_DRV_GraphStop()

//*****************************************************************************

int32_t SEQ_DRV_GraphStateGet()
{
  return sGraphOn;
} // SEQ_DRV_GraphStateGet()

//*****************************************************************************

int32_t SEQ_DRV_FrmBuffersRequest(SEQ_BufferRequest_t *apRequest)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  uint32_t i = 0;
  SEQ_FrmStream_t *lpStream = spFrmStreams[apRequest->mStreamIdx];
  
  // check input structure
  if((apRequest == NULL) || (apRequest->mStreamIdx >= FDMA_CHNL_CNT))
  {
    VDB_LOG_ERROR("Bad input structure.\n");
    goto final_return;
  } // if bad input structure
  
  //TODO: lock the driver
  
  //TODO: check for STREAM is OFF
  
  // if 0 buffers requested => deallocate last
  if(apRequest->mCnt == 0)
  {
    // check if stream exists
    if( lpStream != NULL)
    {
      kfree(lpStream);
      spFrmStreams[apRequest->mStreamIdx] = NULL;
    } // if srteam exists
    
    goto final_return;
  } // if mCnt == 0
  // check if stream not set already
  if(lpStream != NULL)
  {
    lRet = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Stream exists already. No action taken.\n");
    goto final_return;
  } // if stream exists already
  
  // check input structure
  if(apRequest->mpBuffers == NULL)
  {
    VDB_LOG_ERROR("Bad input structure.\n");
    goto final_return;
  } // if bad input structure

  // allocate new stream structure
  lpStream = (SEQ_FrmStream_t*) kmalloc(sizeof(SEQ_FrmStream_t), GFP_KERNEL);
  if(lpStream == NULL)
  {
    VDB_LOG_ERROR("Stream mem allocation failed.\n");
    lRet = SEQ_DRV_FAILURE;
    goto final_return;
  } // if mem alloc failed
  
  lpStream->mpBufferTable = (SEQ_FrmBuffer_t*) kmalloc(sizeof(SEQ_FrmBuffer_t)*apRequest->mCnt, GFP_KERNEL);
  if(lpStream == NULL)
  {
    kfree(lpStream);
    VDB_LOG_ERROR("Frm buffer table mem allocation failed.\n");
    lRet = SEQ_DRV_FAILURE;
    goto final_return;
  } // if mem alloc failed
  
  // init stream
  lpStream->mCnt         = apRequest->mCnt;
  lpStream->mBufferSize  = apRequest->mBufferSize;
  lpStream->mpNextBuffer = NULL;
  VDList_Init(&(lpStream->mWorkQueue));
  VDList_Init(&(lpStream->mDoneQueue));
  
  // init buffers
  for(i = 0; i < lpStream->mCnt; i++)
  {
    lpStream->mpBufferTable[i].mBufferIdx  = i;
    lpStream->mpBufferTable[i].mPhyAddr    = apRequest->mpBuffers[i] + apRequest->mBaseShift;
    lpStream->mpBufferTable[i].mState      = SEQ_FRM_BUFFER_STATE_USER;
    lpStream->mpBufferTable[i].mStreamIdx  = apRequest->mStreamIdx;
    
    VDList_NodeInit(&(lpStream->mpBufferTable[i].mVDListNode), (void*)&(lpStream->mpBufferTable[i]));
  } // for all buffers
  
  spFrmStreams[apRequest->mStreamIdx] = lpStream;      
  
  // TODO: unlock the driver
  
final_return:
  return lRet;
} // SEQ_DRV_FrmBuffersRequest()
  
//*****************************************************************************

void SEQ_DRV_FrmStreamsReset()
{
  uint32_t i = 0;
  
  // clean up streams
  for(i = 0; i < FDMA_CHNL_CNT; i++)
  {
    SEQ_FrmStream_t *lpStream = spFrmStreams[i];
    if(lpStream != NULL)
    {
      if(lpStream->mpBufferTable != 0)
      {
        kfree(lpStream->mpBufferTable);
      } // if buffer table exists
      kfree(lpStream);
      spFrmStreams[i] = NULL;
    } // if stream exists
  } // for all possible streams
} // FrmStreamsReset()

//*****************************************************************************
  
int32_t SEQ_DRV_FrmBufferQuery(SEQ_FrmBufferInfo_t *apBufferInfo)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  
  // check if buffer exists
  if((spFrmStreams[apBufferInfo->mStreamIdx] != NULL) && 
     (spFrmStreams[apBufferInfo->mStreamIdx]->mCnt > apBufferInfo->mBufferIdx))
  {
    apBufferInfo->mState = spFrmStreams[apBufferInfo->mStreamIdx]->mpBufferTable[apBufferInfo->mBufferIdx].mState;
    apBufferInfo->mSize  = spFrmStreams[apBufferInfo->mStreamIdx]->mBufferSize;
  } // if buffer exists
  else
  {
    VDB_LOG_ERROR("No such buffer\n");
    lRet = SEQ_DRV_FAILURE;
  } // if no such buffer
  
  return lRet;
} // SEQ_DRV_FrmBuffersRequest()

//*****************************************************************************

int32_t SEQ_DRV_FrmBufferPush(SEQ_FrmBufferInfo_t *apBufferInfo)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_FrmStream_t *lpStream = NULL;
  
  // check input structure
  if(apBufferInfo == NULL)
  {
    lRet = SEQ_DRV_FAILURE;
  } // if input structure NULL
  else if(apBufferInfo->mStreamIdx >= FDMA_CHNL_CNT)
  {
    lRet = SEQ_DRV_FAILURE;
  } // if Stream index out of range
  else
  {
    lpStream = spFrmStreams[apBufferInfo->mStreamIdx];
  } // else input ok
  
  // check if buffer exists
  if((lpStream != NULL) && 
     (lpStream->mCnt > apBufferInfo->mBufferIdx))
  { 
    SEQ_FrmBuffer_t * lpFrmBuffer = &(lpStream->mpBufferTable[apBufferInfo->mBufferIdx]);
    
    if(lpFrmBuffer->mState == SEQ_FRM_BUFFER_STATE_USER)
    {
      unsigned long lFlags;
      // *** push the buffer to WORK queue *** 
      lpFrmBuffer->mState = SEQ_FRM_BUFFER_STATE_WORK;
      // TODO: lock the WORK queue
      spin_lock_irqsave(&sStreamLock, lFlags); // save the state, if locked already it is saved in flags
      VDList_TailPush(&(lpStream->mWorkQueue), &(lpFrmBuffer->mVDListNode));
      spin_unlock_irqrestore(&sStreamLock, lFlags); // return to the formally state specified in flags   
      // TODO: unlock the WORK queue
    }// if buffer in user state
    else
    {
      VDB_LOG_ERROR("Buffer not in user state. Push aborted.\n");
      lRet = SEQ_DRV_FAILURE;
    }// else from if buffer in user state
  } // if buffer exists
  else
  {
    VDB_LOG_ERROR("No such buffer\n");
    lRet = SEQ_DRV_FAILURE;
  } // if no such buffer
  
  return lRet;
} // SEQ_DRV_FrmBufferPush(SEQ_FrmBufferInfo_t *apBuffInfo)

//*****************************************************************************

int32_t SEQ_DRV_FrmBufferPop(SEQ_FrmBufferInfo_t *apBufferInfo)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  SEQ_FrmStream_t *lpStream = NULL;
  uint32_t cnt, index;
  
  // check input structure
  if(apBufferInfo == NULL)
  {
    lRet = SEQ_DRV_FAILURE;
  } // if input structure NULL
  else if(apBufferInfo->mStreamIdx >= FDMA_CHNL_CNT)
  {
    lRet = SEQ_DRV_FAILURE;
  } // if Stream index out of range
  else
  {
    lpStream = spFrmStreams[apBufferInfo->mStreamIdx];
  } // input OK
  
  cnt = (uint8_t)(lpStream->mCnt);
  index = apBufferInfo->mStreamIdx;
  //printk("Start cnt %u, bidx %u\n", lpStream->mCnt, apBufferInfo->mBufferIdx);
  // check if stream exists
  if(lpStream != NULL)
  {    
    if(!VDList_Empty(&(lpStream->mDoneQueue)))
    {
      // *** pop a buffer from DONE queue ***
      unsigned long lFlags;
      SEQ_FrmBuffer_t * lpFrmBuffer = NULL;
      //printk("Mid\n");
      spin_lock_irqsave(&sStreamLock, lFlags); // save the state, if locked already it is saved in flags
      // TODO: lock the DONE queue
      lpFrmBuffer = (SEQ_FrmBuffer_t*)(VDList_HeadPop(&(lpStream->mDoneQueue))->mpData);
      // TODO: unlock the DONE queue
      spin_unlock_irqrestore(&sStreamLock, lFlags); // return to the formally state specified in flags      
      
      //printk("FrmBuffer %p\n",lpFrmBuffer);
      lpFrmBuffer->mState = SEQ_FRM_BUFFER_STATE_USER;     
        
      apBufferInfo->mBufferIdx = lpFrmBuffer->mBufferIdx; 
      apBufferInfo->mState     = SEQ_FRM_BUFFER_STATE_USER;      
      apBufferInfo->mSize      = lpStream->mBufferSize;
    }// if done queue not empty
    else
    {
      VDB_LOG_NOTE("Done queue empty. Pop aborted.\n");
      lRet = SEQ_DRV_FAILURE;
    } // else from if done queue not empty
  } // if buffer exists
  else
  {
    VDB_LOG_ERROR("No such stream\n");
    lRet = SEQ_DRV_FAILURE;
  } // if no such buffer
  
  return lRet;
} // SEQ_DRV_FrmBufferPush(SEQ_FrmBufferInfo_t *apBuffInfo)

//*****************************************************************************

void SEQ_DRV_PramAuxDataGet(SEQ_AuxData_t* apAuxData)
{
  if(apAuxData != NULL)
  {
    apAuxData->mSize  = ((uint32_t)SEQ_PRAM_AUX_DATA_SIZE < apAuxData->mSize)?
                        (uint32_t)SEQ_PRAM_AUX_DATA_SIZE: apAuxData->mSize;
    apAuxData->mpData = &spPram[PRAM_AUX_DATA_OFF];
  }
  else
  {
    VDB_LOG_WARNING("AuxData structure pointer is NULL. No action taken.\n");
  }
} // void SEQ_DRV_PramAuxDataGet(SEQ_AuxData_t* apAuxData);

//*****************************************************************************

void SEQ_UserPidSet(pid_t aUsrPid)
{
  sSeqUserPid = aUsrPid;
} // SEQ_UserPidSet(pid_t aUsrPid)

//*****************************************************************************

int32_t SEQ_DRV_IpuPerformanceInfoRequest(uint32_t aFrmCnt)
{
  SEQ_Message_t   lMsg;
  SEQM_profile_t  *lpProfileMsg = (SEQM_profile_t*)lMsg.mData;
  
  lpProfileMsg->mFrmCnt = aFrmCnt;
  
  lMsg.mType   = SEQ_MSG_TYPE_IPU_PROFILE;
  lMsg.mStatus = SEQ_MSG_STAT_READY;
  
  // TODO: lock
  sIpuProfileDone = 0; // forget last profiling if any
  // TODO: unlock  
  
  return (SEQ_DRV_MsgSend(&lMsg, 0));
} // SEQ_IpuPerformanceInfoRequest(uint32_t aFrmCnt)

//*****************************************************************************

int32_t SEQ_DRV_IpuPerformanceInfoGet(SEQ_IpuPerformanceRegs_t *apIpuRegs)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  if((apIpuRegs == NULL) || (sIpuProfileDone == 0))
  {
    lRet = SEQ_DRV_FAILURE;
  } // if output pointer not valid or no data ready yet
  else
  {
    uint32_t i = 0;
    
    // get IPUS regs
    for(i = 0; i < IPUS_CNT; i++)
    {
      apIpuRegs[i].mStallStreamIn     = sppIpusRegs[i]->STALL_STREAMIN.R;
      apIpuRegs[i].mStallStreamOut    = sppIpusRegs[i]->STALL_STREAMOUT.R;
      apIpuRegs[i].mStallStreamInOut  = sppIpusRegs[i]->STALL_STREAMINOUT.R;
      apIpuRegs[i].mStallDataHazard   = sppIpusRegs[i]->STALL_DATAHAZARD.R;
      apIpuRegs[i].mExecCounter       = sppIpusRegs[i]->EXEC_COUNTER.R;
    } // for all IPUS
    
    // get IPUV regs
    for(i = IPUS_CNT; i < (IPUS_CNT + IPUV_CNT); i++)
    {
      apIpuRegs[i].mStallStreamIn     = sppIpuvRegs[i - IPUS_CNT]->STALL_STREAMIN.R;
      apIpuRegs[i].mStallStreamOut    = sppIpuvRegs[i - IPUS_CNT]->STALL_STREAMOUT.R;
      apIpuRegs[i].mStallStreamInOut  = sppIpuvRegs[i - IPUS_CNT]->STALL_STREAMINOUT.R;
      apIpuRegs[i].mStallDataHazard   = sppIpuvRegs[i - IPUS_CNT]->STALL_DATAHAZARD.R;
      apIpuRegs[i].mExecCounter       = sppIpuvRegs[i - IPUS_CNT]->EXEC_COUNTER.R;
    } // for all IPUv
  } // else from if output pointer not valid
  
  return lRet;
} // SEQ_UserPidSet(pid_t aUsrPid)

//*****************************************************************************

void SEQ_DRV_AutoExpEnable()
{     
  spin_lock(&sSeqGlobalLock);
  
  sAeOn = 1;
  
  spin_unlock(&sSeqGlobalLock);
} // SEQ_DRV_EventLogEnable()

//*****************************************************************************

void SEQ_DRV_AutoExpDisable()
{     
  spin_lock(&sSeqGlobalLock);
  
  sAeOn = 0;
  
  spin_unlock(&sSeqGlobalLock);
} // SEQ_DRV_EventLogEnable()

//*****************************************************************************

uint32_t SEQ_DRV_EventLogEnable()
{  
  uint32_t lRet = SEQ_DRV_SUCCESS;
#if (ISP_EVT_LOG_LEN > 0)
  uint32_t lRetTmp = 0;
   
  spin_lock(&sSeqGlobalLock);
  
  sEventLogOn = 1;
  
  // enable all IRQs 
  spSeqCBregs->HOST_IRQ_EN.R |= 0xff007f; //0xff007c;
  
  spin_unlock(&sSeqMsgLock);
#endif  
  return lRet;
} // SEQ_DRV_EventLogEnable()

//*****************************************************************************

uint32_t SEQ_DRV_EventLogDisable()
{  
  uint32_t lRet = SEQ_DRV_SUCCESS;
  
  spin_lock(&sSeqGlobalLock);
  
  sEventLogOn = 0;
  
  // enable MSG IRQs only
  spSeqCBregs->HOST_IRQ_EN.R = 0xc;
  
  spin_unlock(&sSeqMsgLock);
  
  return lRet;
} // SEQ_DRV_EventLogDisable()

//*****************************************************************************

int32_t SEQ_DRV_EventLogGet(SEQ_EventLog_t **appEventLog)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  if(appEventLog != NULL)
  {
    *appEventLog = &sEventLog;
  }
  else
  {
    lRet = SEQ_DRV_FAILURE;
  }
  
  return lRet;
} // SEQ_DRV_EventLogGet()

//*****************************************************************************

int32_t SEQ_DRV_TdtAddressesSet(FDMA_Td_t *apIsp0Tdt, uint32_t aPhys)
{
   sppTdt[SEQ_ISP0_TDT_IDX]     = apIsp0Tdt;
   spPhysTdt[SEQ_ISP0_TDT_IDX]  = aPhys;
   sppTdt[SEQ_ISP1_TDT_IDX]     = apIsp0Tdt + FDMA_CHNL_CNT;
   spPhysTdt[SEQ_ISP1_TDT_IDX]  = aPhys + FDMA_CHNL_CNT * sizeof(FDMA_Td_t);
   sppTdt[SEQ_USER_TDT_IDX]     = apIsp0Tdt + FDMA_CHNL_CNT * 2;
   spPhysTdt[SEQ_USER_TDT_IDX]  = aPhys + 2 * FDMA_CHNL_CNT * sizeof(FDMA_Td_t);
   
   return 0;
} // SEQ_DRV_TdtAddressesSet()

//*****************************************************************************

void SEQ_DRV_IpuHistRead(SEQ_IpuHist_t *apHist)
{
  uint32_t i = 0;
  if(apHist != NULL)
  {
    if(apHist->mIpuIdx < IPU_HIST_CNT)
    {
      uint32_t *lpHist = apHist->mpData;
      uint32_t lIpuIdx = apHist->mIpuIdx;
      sppIpusRegs[lIpuIdx]->HOST_HISTA.B.HISTA = 0;         // Histogram Memory Address Register
      for(i = 0; i < IPU_HIST_SIZE; i++)
      {
        //sppIpusRegs[lIpuIdx]->HOST_HISTA.B.HISTA = i;         // Histogram Memory Address Register
        lpHist[i] = sppIpusRegs[lIpuIdx]->HOST_HISTD.B.HISTD; // Histogram Memory Data Register
      } // for all bins
      
      apHist->mPeak     = sppIpusRegs[lIpuIdx]->HOST_HISTPEAK.B.HISTPEAK; // Histogram Peak Value Register
      apHist->mPeakAddr = sppIpusRegs[lIpuIdx]->HOST_HISTAMAX.B.HISTAMAX; // Histogram Maximum Value Address Register
      
      sppIpusRegs[lIpuIdx]->HOST_HISTCLEAR.B.HISTCLEAR = 1; // Histogram Clear Register
    } // if valid index
  }
} // void SeqHistGet()

//*****************************************************************************

int32_t SEQ_DRV_IpuHistogramEnable(SEQ_IpuEngine_t aIpuIdx)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  if(aIpuIdx < IPU_HIST_CNT)
  {
    if(spIpuHists[aIpuIdx] == NULL)
    {
      SEQ_IpuHist_t *lpHist = kmalloc(sizeof(SEQ_IpuHist_t), GFP_KERNEL);
      if(lpHist == NULL)
      {
        VDB_LOG_ERROR("Failed to allocate histogram memory.\n");
        lRet = SEQ_DRV_FAILURE;
      } // if alloc failed
      else
      {
        memset(lpHist, 0, sizeof(SEQ_IpuHist_t));
        lpHist->mIpuIdx     = aIpuIdx;
        spIpuHists[aIpuIdx] = lpHist;
      } // else from if alloc failed
    } // if hist not enabled yet
  } // if IPU index in range
  else
  {
    VDB_LOG_ERROR("Wrong Ipu index.\n");
    lRet = SEQ_DRV_FAILURE;
  } // else from if IPU index in range
  return lRet;
} // void SeqHistEnable(uint8_t aIpuIdx)

//*****************************************************************************

void SEQ_DRV_IpuHistogramDisable(SEQ_IpuEngine_t aIpuIdx)
{
  if(aIpuIdx < IPU_HIST_CNT)
  {
    SEQ_IpuHist_t *lpHist = spIpuHists[aIpuIdx];
    spIpuHists[aIpuIdx] = NULL;
    if(lpHist != NULL)
    {
      kfree(lpHist);
    } // if hist not enabled yet
  } // if IPU index in range
} // void SeqHistEnable(uint8_t aIpuIdx)

//*****************************************************************************

int32_t SEQ_DRV_IpuHistogramGet(SEQ_IpuHistHead_t *apHist)
{
  int32_t lRet = SEQ_DRV_SUCCESS;
  if(apHist != NULL)
  {
    if(apHist->mIpuIdx < IPU_HIST_CNT)
    {
      if(spIpuHists[apHist->mIpuIdx] != NULL)
      {
        uint32_t lLock = spIpuHistLocks[apHist->mIpuIdx];
        do
        {
          if (copy_to_user((uint8_t *)apHist->mpData, 
                            spIpuHists[apHist->mIpuIdx]->mpData, 
                            sizeof(uint32_t) * IPU_HIST_SIZE) != 0)
          {
            VDB_LOG_ERROR("Histogram data copy failed.\n");
            lRet = SEQ_DRV_FAILURE;
          } // if graph data fetch failed
          apHist->mPeak     = spIpuHists[apHist->mIpuIdx]->mPeak;
          apHist->mPeakAddr = spIpuHists[apHist->mIpuIdx]->mPeakAddr;
          // make sure no update in between
        }while(lLock != spIpuHistLocks[apHist->mIpuIdx]);
      }
      else
      {
        lRet = SEQ_DRV_FAILURE;
      }
    } // if valid index
    else
    {
      VDB_LOG_ERROR("Wrong Ipu index.\n");
      lRet = SEQ_DRV_FAILURE;
    }
  }
  else
  {
    VDB_LOG_ERROR("Histogram pointer is NULL.\n");
    lRet = SEQ_DRV_FAILURE;
  }
  
  return lRet;
} // void SeqHistGet(uint8_t aIpuIdx)

//*****************************************************************************

#ifndef __STANDALONE__
EXPORT_SYMBOL(gpSEQ_FdmaEventHandler);
EXPORT_SYMBOL(SEQ_FdmaTdSchedule);
EXPORT_SYMBOL(gSeqMode);
EXPORT_SYMBOL(SEQ_DRV_TdtAddressesSet);
#endif // #ifndef __STANDALONE__
