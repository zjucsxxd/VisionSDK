/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2015 Freescale Semiconductor;
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
 * \file     fdma_func.c
 * \brief    functionality of fDMA driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     4. September 2015
 * \note
 ****************************************************************************/
#define VDB_LOG_NOTE_OFF

#if !defined(__STANDALONE__)
  #include <linux/kernel.h>     // We're doing kernel work
  #include <linux/module.h>     // Specifically, a module 
  #include <linux/interrupt.h>  // For interrupts
  #include <asm/siginfo.h>      // siginfo
  #include <linux/sched.h>      // send_sig_info
  #include <linux/types.h>
  #include <linux/delay.h>      // for msleep
  #include <asm/io.h>           // for ioremap
#else
  #include <stdio.h>
  #include <unistd.h>
  #include <stdint.h>
  #include <string.h>
  #define printk //printf
#endif // else from if !defined(__STANDALONE__)

#include "fdma.h"
#include "fdma_func.h"
#include "vdb_log.h"

//****************************************************************************
// consts
//****************************************************************************
#define TDT_ISP0 0 ///< index of TDT for IPS transfer (array 0)
#define TDT_ISP1 1 ///< index of TDT for IPS transfer (array 1)
#define TDT_USER 2 ///< index of TDT for user transfers

//#define VDB_LOG_NOTE printk

//****************************************************************************
// macros
//****************************************************************************

#define SRAM_V2P(_VirtAddr, _Offset) ((uintptr_t)(((uintptr_t)_VirtAddr) + _Offset))
#define SRAM_P2V(_PhysAddr, _Offset) ((uintptr_t)(_PhysAddr - _Offset))

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// global data
//****************************************************************************

#define X  1
#pragma push_macro("X")
#undef X
#define X -1
#pragma pop_macro("X")
int x [X];

// FDMA HW registers
static FDMA_Regs_t *spFdmaRegs = NULL;

// transaction descriptors table in SRAM
static FDMA_Tdt_t spTdt[3];

// Array of available TDMs (one for each TD in SRAM TDT)
static FDMA_Tdm_t sTdmArr[FDMA_TD_CNT];

// list of unused TDMs
static FDMA_TdmList_t sFreeTdmList;

#if !defined(__STANDALONE__)
// fDMA locking mutex
mutex_t gFdmaMutex;
#endif //#if !defined(__STANDALONE__)

// Array of TC events (one for each TD in SRAM TDT)
static FDMA_TcEvent_t sTcEventArr[FDMA_TD_CNT];

// offset from virtual 2 physical SRAM address imported from sram manager
extern ptrdiff_t gSRAM_V2pOffset;

static uintptr_t sTdtBasePhy = 0;

// available sequencer mode (1 = Sequencer-based, 0 = Sequencer-less);
// extern char gSeqMode; // exported by Sequencer module
char gSequencerOn = SEQ_LESS_MODE; // fdma module internal variable

//*****************************************************************************
// global functions
//*****************************************************************************

// declaration of functions imported from SRAM module
uintptr_t SRAM_SingleMalloc(uint32_t);
void SRAM_Free(uintptr_t);

#ifdef __STANDALONE__
extern int32_t SEQ_DRV_TdtAddressesSet(const FDMA_Td_t *apUserTdt, 
                                       uint32_t aPhys);
#endif // __STANDALONE__

//****************************************************************************
// local data
//****************************************************************************
// declaration of gSeqMode variable
static char gSeqMode;

#ifndef __STANDALONE__
// templates for symbol_get()s from Sequencer kernel module
static int32_t (*gpSEQ_FdmaEventHandler)(uint32_t aTdIdx, uint32_t aEventType);
int32_t SEQ_FdmaTdSchedule(uint32_t aTdIdx);
int32_t SEQ_DRV_TdtAddressesSet(const FDMA_Td_t *apUserTdt, uint32_t aPhys);

// fdma pointers to imported Sequencer symbols
int32_t (**gppSEQ_FdmaEventHandler)(uint32_t aTdIdx, uint32_t aEventType);
int32_t (*gpSEQ_FdmaTdSchedule)(uint32_t aTdIdx);
int32_t (*gpSEQ_DRV_TdtAddressesSet)(const FDMA_Td_t *apUserTdt, uint32_t aPhys);
#endif //__STANDALONE__

//*****************************************************************************
// local function declarations
//*****************************************************************************

// Initialize TDMs
static int32_t FDMA_TdmsInit(void);

// SeqUp FDMA registers to be ready for first TX scheduling
static int32_t FdmaHwInit(void);

#if !defined(__STANDALONE__)
// Connects FDMA module to SEQUENCER module
static int32_t SequencerConnect(void);

// Disconnects FDMA module to SEQUENCER module
static void SequencerDisconnect(void);

#else
void msleep(uint32_t);
#endif // #if !defined(__STANDALONE__)

// Register IRQs for FDMA module
static int32_t FdmaIrqRegister(void);

// Releses FDMA IRQs
void FdmaIrqFree(void);

// Releases TDT memory in SRAM
void FDMA_TdtFree(FDMA_Tdt_t *apTdt);

// Print out memory
void FDMA_MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption);

// set IO remapped memory content
void* IoMemSet(void* apAddr, uint8_t aValue, size_t aSize);
 
//*****************************************************************************
// function definitions
//*****************************************************************************

int32_t FDMA_Setup()
{
  uint32_t lRet = FDMA_DRV_SUCCESS;
  
  VDB_LOG_NOTE("v2p: %llx\n", gSRAM_V2pOffset);
  
#if !defined(__STANDALONE__)  
  // *** attempt to connect to Sequencer moduel if available ***
  if(symbol_get(gSeqMode) != NULL)
  {
    VDB_LOG_NOTE("Sequencer-based mode %d.\n", (int) gSeqMode);
    // TODO: return back sequencer conection
    if(SequencerConnect() != FDMA_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Failed to connect to Sequencer.\n");
      gSequencerOn = 0;
      // return;
      lRet = FDMA_DRV_FAILURE;
      //goto tdt_init_failed;
    } // if connecting to Sequencer module failed
    else
    {
      gSequencerOn = 1;
    } // else from if connecting to Sequencer module failed
    VDB_LOG_NOTE("Acting as Sequencer driver is not there.\n");
    gSequencerOn = 0;
  } // if gSeqMode symbol found
  else
  {
    VDB_LOG_NOTE("Sequencer-less mode.\n");
    gSequencerOn = 0;
  } // else from if gSeqMode symbol found
#else
  gSequencerOn = 0;
#endif //#if !defined(__STANDALONE__)
  
  // *** initialize TDT area in SRAM ***
  if(FDMA_TdtInit(spTdt))
  {
    lRet = FDMA_DRV_FAILURE;
    VDB_LOG_ERROR("TDT init failed\n");
#if !defined(__STANDALONE__)    
    goto tdt_init_failed;
#endif // #if !defined(__STANDALONE__)
  } // if tdt init failed
  
  // *** init list of unused TDMs and TC envents ***
  if(FDMA_TdmsInit() != FDMA_DRV_SUCCESS)
  {
    lRet = FDMA_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to initialize TDMs.\n");
    goto tdms_init_failed;
  } // if TDM init failed  
  
  VDB_LOG_NOTE(" There are %u TDM ready to be used by user space.\n",(unsigned) sFreeTdmList.mLength);  
  
#if !defined(__STANDALONE__)  
  // *** initialize FastDMA mutex ***
  mutex_init(&gFdmaMutex);
#endif // #if !defined(__STANDALONE__)

  // *** register IRQs ***
  if(FdmaIrqRegister() != FDMA_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to register IRQs.\n");
    lRet = FDMA_DRV_FAILURE;
    goto irq_request_failed;
  } // if IRQ registering failed
  
  // *** initialize FastDMA ***  
  if( FdmaHwInit() != FDMA_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("FDMA HW init failed.\n");
    lRet = FDMA_DRV_FAILURE; 
  }
  
  // *** error processing ***    
  if(lRet != FDMA_DRV_SUCCESS)
  {
    FdmaIrqFree();
    irq_request_failed:  
      FDMA_TdmListInit(&sFreeTdmList);
    tdms_init_failed:
      FDMA_TdtFree(spTdt);
#if !defined(__STANDALONE__)
    tdt_init_failed:  
      SequencerDisconnect(); 
#endif //#if !defined(__STANDALONE__)    
      VDB_LOG_ERROR("Canceling FDMA insmod.\n");
  } // if error detected;
  else
  {
    printk("FDMA driver ready.\n");
  } // else from if error detected
  
  return lRet;
} // FDMA_Setup()

//****************************************************************************

void FDMA_Close()
{  
  // reset
  spFdmaRegs->CTRL.B.SOFT_RST = 1;
  msleep(50);

#if !defined(__STANDALONE__)  
  // unmap registers
  iounmap(spFdmaRegs);
#else 
  spFdmaRegs = NULL;
#endif // #if !defined(__STANDALONE__)
  
  // release IRQ channels
  FdmaIrqFree();
  
  // reset TDM list
  FDMA_TdmListInit(&sFreeTdmList);
  
  // *** free the SRAM TDT memory in SRAM ***
  FDMA_TdtFree(spTdt);

#if !defined(__STANDALONE__)  
  // *** disconnect from Sequencer module ***
  if(gSequencerOn)
  {
    gSequencerOn = 0;
    SequencerDisconnect(); 
  } // if Sequencer on 
#endif // #if !defined(__STANDALONE__)
} // FDMA_Close()

//****************************************************************************

int32_t FDMA_TdmsInit()
{  
  int32_t lRet = FDMA_DRV_SUCCESS;
  uint32_t i = 0;
  
  // init the free list
  FDMA_TdmListInit(&sFreeTdmList);
  
  // push all available TDMs as free
  for( i = 0; i < FDMA_TD_CNT; ++i)
  {
    sTdmArr[i].mTdIdx = i; // TDM init
    if(FDMA_TdmListPushBack(&sFreeTdmList, &sTdmArr[i]) != FDMA_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Tdm number %d already in the list.\n",(int) i);
      lRet = FDMA_DRV_FAILURE;
      break;
    } // if tdm list push back failed
    
    // reset TC event
    sTcEventArr[i].mXfrStat = 0;
    sTcEventArr[i].mXfrCalcCrcVal = 0;
    sTcEventArr[i].mXfrCurrDdrPtr = 0;	
    sTcEventArr[i].mXfrCurrSramPtr = 0;  
    sTcEventArr[i].mXfrRecNum = 0;  	// not needed defined by the index
    sTcEventArr[i].mSramNextLine = 0;  
  } // for all list nodes
  
  return lRet;
} // FDMA_TdmsInit()

//****************************************************************************

int32_t FdmaHwInit()
{         
  int32_t lRet = FDMA_DRV_SUCCESS; 
  
#if !defined(__STANDALONE__)  
  spFdmaRegs = ioremap((uintptr_t)&FDMA, FDMA_SIZE);
#else 
  spFdmaRegs = (FDMA_Regs_t*)&FDMA;
#endif //#if !defined(__STANDALONE__)
  if(spFdmaRegs == NULL)
  {
    VDB_LOG_ERROR("Failed to map FDMA registers.\n");
    lRet = FDMA_DRV_FAILURE;
  } // if FDMA registers not mapped
  else
  {
    // do SW reset just to be sure
    spFdmaRegs->CTRL.B.SOFT_RST = 1;

    // wait a bit
    msleep(50);  
  
    // set address of transaction descriptor table
    spFdmaRegs->XFR_REC_LIST_PTR.R = (uint32_t)(uintptr_t) SRAM_V2P(spTdt[TDT_ISP0].mpBase, gSRAM_V2pOffset) ;
    
    // set count of available TDs
    spFdmaRegs->XFR_REC_CNT.R = (uint32_t) FDMA_TD_CNT;
  
    // !!! all IRQ flags are expected to be deaserted at the moment !!!
  
    // enable all IRQs
    spFdmaRegs->IRQ_EN.R = 0;//0xF;

  } // else from if fdma registers not mapped
  
  return lRet;
} // FdmaHwInit()

//****************************************************************************
#if !defined(__STANDALONE__)  
int32_t SequencerConnect()
{
  int32_t lRet = FDMA_DRV_SUCCESS;
  
  // *** get FdmaEventHandler pointer from Sequencer module ***
  if( (gppSEQ_FdmaEventHandler = symbol_get(gpSEQ_FdmaEventHandler)) != NULL)
  {
    VDB_LOG_NOTE("FDMA event handler pointer from Sequencer found\n");
    // assign the correct handler function from FDMA module
    *gppSEQ_FdmaEventHandler = &FDMA_SeqEventHandler;
    
    // *** get Sequencer exported TD scheduling function
    if( (gpSEQ_FdmaTdSchedule = symbol_get(SEQ_FdmaTdSchedule)) != NULL)
    {
      VDB_LOG_NOTE("Transaction scheduling function from Sequencer found\n");
      if( (gpSEQ_DRV_TdtAddressesSet = symbol_get(SEQ_DRV_TdtAddressesSet)) != NULL)
      {
        VDB_LOG_NOTE("TDT setup function from Sequencer found\n");
        gSequencerOn = 1;
      } // if SEQ_DRV_TdtAddressesSet symbol found
      else
      {
        VDB_LOG_WARNING("TDT setup function from Sequencer not found\n");
        // put so far gotten symbols
        symbol_put(gpSEQ_FdmaTdSchedule);
        // put so far gotten symbols
        symbol_put(gpSEQ_FdmaEventHandler);
        
        lRet = FDMA_DRV_FAILURE;
      } // else from if SEQ_DRV_TdtAddressesSet symbol found
    } // if SEQ_FdmaTdSchedule symbol found
    else
    {
      VDB_LOG_WARNING("Transaction scheduling function from Sequencer not found\n");
      // put so far gotten symbols
      symbol_put(gpSEQ_FdmaEventHandler);
      
      lRet = FDMA_DRV_FAILURE;
    } // else from if SEQ_FdmaTdSchedule symbol found
  } // if gpSEQ_FdmaEventHandler symbol found
  else
  {
    VDB_LOG_WARNING("FDMA event handler pointer from Sequencer not found\n");
    lRet = FDMA_DRV_FAILURE;
  } // else from if gpSEQ_FdmaEventHandler symbol found
  
  return lRet;
} // SequencerConnect()
#endif // #if !defined(__STANDALONE__)  

//****************************************************************************

#if !defined(__STANDALONE__)  
void SequencerDisconnect()
{
  if(gSequencerOn)
  {
    // cancel FDMA event handler TODO: put default handler back
    *gppSEQ_FdmaEventHandler = NULL;
    gppSEQ_FdmaEventHandler = NULL;
    symbol_put(gpSEQ_FdmaEventHandler);
    
    // release TD scheduling function
    symbol_put(SEQ_FdmaTdSchedule);
    
    // release SeqMode symbol
    symbol_put(gSeqMode);
  } // if Sequencer on
} // SequencerDisconnect()
#endif // #if !defined(__STANDALONE__)  

//****************************************************************************

#if !defined(__STANDALONE__)  
int32_t Sig2UserSend(uint32_t aTdIdx, uint32_t aEvent)
{
  struct siginfo info;
  int32_t ret = IRQ_HANDLED;
  struct pid *pid_struct;
  struct task_struct *t;
    
  // send the signal to user space
  memset(&info, 0, sizeof(struct siginfo));
  info.si_signo = FDMA_EVENT_SIGNAL;
  info.si_code = SI_QUEUE;
  info.si_int = ((aEvent<<8) | aTdIdx);
  rcu_read_lock();
  pid_struct = find_get_pid(sTdmArr[aTdIdx].mOwnerProcId);
  t = pid_task(pid_struct,PIDTYPE_PID);
  if(t == NULL){
    VDB_LOG_ERROR("FDMA Done IRQ handler - No such pid %u.\n", (unsigned) sTdmArr[aTdIdx].mOwnerProcId);
    rcu_read_unlock();
      ret = -1;
  } // if no such pid
  else
  {
    rcu_read_unlock();
    ret = send_sig_info(FDMA_EVENT_SIGNAL, &info, t);    //send the signal
    if (ret < 0) {
      VDB_LOG_ERROR("FDMA IRQ handler - Error sending signal for DONE event.\n");
    } // if sending signal failed
  } // else if no such pid
  return ret;
} // Sig2UserSend()
#else // #if !defined(__STANDALONE__)  

//****************************************************************************

int32_t Sig2UserSend(uint32_t aTdIdx, uint32_t aEvent)
{
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return 0;
} // Sig2UserSend(uint32_t aTdIdx)
#endif //#if !defined(__STANDALONE__)  

//****************************************************************************

int32_t FdmaIrqRegister()
{
  int32_t lRet = FDMA_DRV_SUCCESS;
  if(gSequencerOn == 0)
  {
#if 0 //!defined(__STANDALONE__)
    if (request_irq(FDMA_IRQ_DONE, &FdmaDoneIrqHandler, IRQF_TRIGGER_RISING, FDMA_DEVICE_NAME, NULL))
    {
      lRet = FDMA_DRV_FAILURE;
      VDB_LOG_ERROR("Failed to request IRQ for DONE signal.\n");
    } // if request for DONE IRQ failed
    else 
    {
      if (request_irq(FDMA_IRQ_ERR, &FdmaErrIrqHandler, IRQF_TRIGGER_RISING, FDMA_DEVICE_NAME, NULL))
      {
        lRet = FDMA_DRV_FAILURE;
        VDB_LOG_ERROR("Failed to request IRQ for ERROR signal.\n");
        free_irq(FDMA_IRQ_DONE, NULL);
      } // if request for DONE IRQ failed
    } // else from if IRQ_DONE registration failed
#endif // #if !defined(__STANDALONE__)
  } // if Sequencer is not enabled
  return lRet;
} // FdmaIrqRegister()

//****************************************************************************

void FdmaIrqFree()
{    
#if !defined(__STANDALONE__)  
  free_irq(FDMA_IRQ_DONE, NULL);
  free_irq(FDMA_IRQ_ERR, NULL);
#endif // #if !defined(__STANDALONE__)
} // FdmaIrqRegister()

//****************************************************************************

irqreturn_t FdmaDoneIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t lRet = IRQ_HANDLED;  
  // read registers - remeber event
  uint32_t tdIdx = spFdmaRegs->XFR_REC_NUM_DONE.R;
  FDMA_TcEvent_t *pEvent = &(sTcEventArr[tdIdx]);
  
  //FDMA_MemPrint((uint8_t*)spFdmaRegs, 0x38, "FDMA registers:\n");

  pEvent->mXfrStat = spFdmaRegs->XFR_STAT.R;
  pEvent->mXfrCalcCrcVal = spFdmaRegs->CALC_CRC_VAL.R;
  pEvent->mXfrCurrDdrPtr = spFdmaRegs->CURR_DDR_PTR.R;
  pEvent->mXfrCurrSramPtr = spFdmaRegs->CURR_SRAM_PTR.R;
  pEvent->mSramNextLine = spFdmaRegs->NEXT_LINE.B.SRAM_NEXT_LINE_NUM;
  
  lRet = Sig2UserSend(tdIdx, FDMA_DONE_EVENT);  
  
  // reset the done bit in STAT register
  spFdmaRegs->XFR_STAT.R = 0x10000;
  
  VDB_LOG_NOTE("FDMA DONE IRQ handled.\n");
  return lRet;
} // FdmaDoneIrqHandler()

//****************************************************************************

irqreturn_t FdmaErrIrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t ret = IRQ_HANDLED;
  uint32_t statErrMask = 0x7f8;
  
  // read registers
  uint32_t tdIdx = spFdmaRegs->ERR_XFR_REC_NUM.R;
  FDMA_TcEvent_t *pEvent = &(sTcEventArr[tdIdx]);
  
  //FDMA_MemPrint((uint8_t*)spFdmaRegs, 0x38, "FDMA registers:\n");
  
  pEvent->mXfrStat        = spFdmaRegs->XFR_STAT.R;
  pEvent->mXfrCalcCrcVal  = spFdmaRegs->CALC_CRC_VAL.R;
  pEvent->mXfrCurrDdrPtr  = spFdmaRegs->CURR_DDR_PTR.R;
  pEvent->mXfrCurrSramPtr = spFdmaRegs->CURR_SRAM_PTR.R;
  pEvent->mSramNextLine   = spFdmaRegs->NEXT_LINE.B.SRAM_NEXT_LINE_NUM;

  /* send the signal */
  ret = Sig2UserSend(tdIdx, FDMA_ERR_EVENT); 
  
  // TODO: reset appropriate err bits
  //statErrMask = (FDMA_XFR_STAT_XFR_ERR_SRAM | FDMA_XFR_STAT_XFR_ERR_DDR | 
  //FDMA_XFR_STAT_XFR_CFG_ERR | FDMA_XFR_STAT_XFR_STP_ERR_CT |
  //FDMA_XFR_STAT_XFR_STP_ERR_TR | FDMA_XFR_STAT_CMD_CFG_ERR);
  
  spFdmaRegs->XFR_STAT.R = (pEvent->mXfrStat | statErrMask);
  
  VDB_LOG_NOTE("FDMA ERR IRQ handled.\n");
  return ret;
} // FdmaDoneIrqHandler()

//****************************************************************************

// called by Sequencer to handle the FDMA events
int32_t FDMA_SeqEventHandler(uint32_t aTdIdx, uint32_t aEventType)
{
  int32_t ret = FDMA_DRV_SUCCESS;

  FDMA_TcEvent_t *pEvent = &(sTcEventArr[aTdIdx]);
  
  //FDMA_MemPrint((uint8_t*)spFdmaRegs, 0x38, "FDMA registers:\n");
  
  pEvent->mXfrStat        = spFdmaRegs->XFR_STAT.R;
  pEvent->mXfrCalcCrcVal  = spFdmaRegs->CALC_CRC_VAL.R;
  pEvent->mXfrCurrDdrPtr  = spFdmaRegs->CURR_DDR_PTR.R;
  pEvent->mXfrCurrSramPtr = spFdmaRegs->CURR_SRAM_PTR.R;
  pEvent->mSramNextLine   = spFdmaRegs->NEXT_LINE.B.SRAM_NEXT_LINE_NUM;
  
  /* send the signal */
  ret = Sig2UserSend(aTdIdx, aEventType); 
  
  VDB_LOG_NOTE("SEQ -> FDMA Event handler called.\n");
  return ret;
} // FdmaSeqEventHandler(uint32_t aTdIdx)

//****************************************************************************

int32_t FdmaSramMallocTest()
{
  int32_t lRet = FDMA_DRV_SUCCESS;
  // test the malloc & free interface from SRAM module
  uintptr_t sramAddr = SRAM_SingleMalloc(4096);	
  if(sramAddr == 0)
  {
    VDB_LOG_ERROR("SRAM alloc failed.\n");    
    lRet = FDMA_DRV_SUCCESS;    
  } // if sram failed
  else
  {
    VDB_LOG_NOTE("SRAM alloc Ok.\n");
  } // else if sram failed
  SRAM_Free(sramAddr);
  return lRet;
} // FdmaSramMallocTest()

//****************************************************************************

int32_t FdmaTdmListTest()
{ 
  uint32_t lRet = FDMA_DRV_SUCCESS;
  uint32_t i = 0;
  // init list of unused TDMs
  FDMA_TdmList_t tdmList;
  FDMA_Tdm_t tdmArr[FDMA_TD_CNT];
  FDMA_TdmListInit(&tdmList);
  for( i = 0; i < FDMA_TD_CNT; ++i)
  {
    tdmArr[i].mTdIdx = i; 
    if(FDMA_TdmListPushBack(&tdmList, &tdmArr[i]) != FDMA_DRV_SUCCESS)
    {
      VDB_LOG_ERROR("Tdm number %d already in the list.\n",(int) i);
      lRet = FDMA_DRV_FAILURE;
      break;
    } // if push-back failed
  } // for all list nodes
  
  VDB_LOG_NOTE("There are %u TDM ready to be used\n",(unsigned) tdmList.mLength);
  
  // empty the list
  for( i = 0; i < FDMA_TD_CNT/2; ++i)
  {
    if(!FDMA_TdmListPopBack(&tdmList))
    {
      VDB_LOG_ERROR("Pop Back failed \n");
      lRet = FDMA_DRV_FAILURE;
    } // if popBack failed
    if(!FDMA_TdmListPopFront(&tdmList))
    {
      VDB_LOG_ERROR("Pop Front failed \n");
      lRet = FDMA_DRV_FAILURE;
    } // if popFront failed
    VDB_LOG_NOTE("Number of free TDMs in list: %u\n",(unsigned) tdmList.mLength);
  } // for all list nodes
  return lRet;
} // FdmaTdmListTest()

//****************************************************************************

int32_t FDMA_TdtInit(FDMA_Tdt_t *apTdt)
{
  int32_t ret = FDMA_DRV_SUCCESS;
  // set number of TDs
  apTdt[TDT_USER].mTdCnt = FDMA_TD_CNT;
  apTdt[TDT_ISP0].mTdCnt = FDMA_TD_CNT;
  apTdt[TDT_ISP1].mTdCnt = FDMA_TD_CNT;
  
  // allocate SRAM for TDT
  // FDMA_TD_CNT + 1 to achieve alignemnt
  sTdtBasePhy  = SRAM_SingleMalloc((FDMA_TD_CNT * 3 + 1) * sizeof(FDMA_Td_t));
  if(sTdtBasePhy != 0)
  {
    uintptr_t lTdtBase = 0;
    lTdtBase = (sTdtBasePhy + 0x1F) & 0xFFFFFFE0; // make sure it is alligned to 32bits
    
    // setup the TDT structures TDT_USER
    apTdt[TDT_ISP0].mpBase = (struct fdma_td*) SRAM_P2V(lTdtBase, gSRAM_V2pOffset);
    apTdt[TDT_ISP1].mpBase = &(apTdt[TDT_ISP0].mpBase[FDMA_TD_CNT]);
    apTdt[TDT_USER].mpBase = &(apTdt[TDT_ISP0].mpBase[FDMA_TD_CNT * 2]);
    
    // clear the TDs
    IoMemSet((void*)apTdt[TDT_ISP0].mpBase, 0, sizeof(FDMA_Td_t) * (FDMA_TD_CNT*3 +1));

#ifndef __STANDALONE__    
    // set TDTs to  Sequencer
    if(gpSEQ_DRV_TdtAddressesSet != NULL)
    {
      gpSEQ_DRV_TdtAddressesSet(apTdt[TDT_ISP0].mpBase, sTdtBasePhy);
    } // if there is something to be set
    //SEQ_DRV_TdtAddressesSet(apTdt[TDT_ISP0].mpBase);
#else
    SEQ_DRV_TdtAddressesSet(apTdt[TDT_ISP0].mpBase, sTdtBasePhy);
#endif 
    
    VDB_LOG_NOTE("V2P offset: 0x%llx\n", gSRAM_V2pOffset);
    VDB_LOG_NOTE("addr allocated: 0x%x\n", (unsigned) sTdtBasePhy);
    VDB_LOG_NOTE("TDT at virtual address 0x%p\n", (void*) apTdt->mpBase);
  } // if SRAM alloc succeeded
  else
  {
    VDB_LOG_ERROR("Failed to allocate TDTs in SRAM.\n");
    ret = FDMA_DRV_FAILURE;
  } // if SRAM allocation succeeded
  
  return ret;
} // FDMA_TdtInit()

//****************************************************************************

void FDMA_TdtFree(FDMA_Tdt_t *apTdt)
{
  if(sTdtBasePhy != 0)
  {
    VDB_LOG_NOTE("SRAM addr to free: %p\n", (void*) apTdt);
    // free tdt in SRAM
    SRAM_Free(sTdtBasePhy); 
  } // if tdt allocated
  
  // reset number of TDs
  apTdt[TDT_USER].mTdCnt = 0;
  apTdt[TDT_ISP0].mTdCnt = 0;
  apTdt[TDT_ISP1].mTdCnt = 0;
  // reset tdt address
  apTdt[TDT_USER].mpBase = NULL;
  apTdt[TDT_ISP0].mpBase = NULL;
  apTdt[TDT_ISP1].mpBase = NULL;
} // FDMA_TdtFree()

//****************************************************************************

// initializes given tdm list
void FDMA_TdmListInit(FDMA_TdmList_t *apTdmList)
{
  int32_t i;
  apTdmList->mpHead = NULL;
  apTdmList->mpTail = NULL;
  
  apTdmList->mLength = 0;  
  
  // reset all nodes in the pool
  for(i = 0; i < FDMA_TD_CNT; ++i)
  {
    apTdmList->mNodePool[i].mpPrev = NULL;
    apTdmList->mNodePool[i].mpNext = NULL;
    apTdmList->mNodePool[i].mpTdm = NULL;
  } // for all nodesl
} // FDMA_TdmListInit()

//****************************************************************************

// pushes TDM to the front of the list
int32_t FDMA_TdmListPushFront(FDMA_TdmList_t *apTdmList, FDMA_Tdm_t *acpTdm)
{
  FDMA_TdmListNode_t *pCurrentNode = &(apTdmList->mNodePool[acpTdm->mTdIdx]);
  int32_t retVal = FDMA_DRV_FAILURE;
  
  if(!pCurrentNode->mpTdm)
  {
    if(apTdmList->mpHead != NULL)
    {
      apTdmList->mpHead->mpPrev = pCurrentNode;
    } // if not empty
    else
    {
      apTdmList->mpTail = pCurrentNode;
    } // else from if not empty
    
    pCurrentNode->mpNext = apTdmList->mpHead;  
    ++apTdmList->mLength;
    
    apTdmList->mpHead = pCurrentNode;
    
    pCurrentNode->mpPrev = NULL;
    pCurrentNode->mpTdm = acpTdm;  
    
    retVal = FDMA_DRV_SUCCESS;
  } // if TDM not in the list yet
  
  return retVal;
} // FDMA_TdmListPushFront()

//****************************************************************************

// pushes TDM to the back of the list
int32_t FDMA_TdmListPushBack(FDMA_TdmList_t *apTdmList, FDMA_Tdm_t *acpTdm)
{
  FDMA_TdmListNode_t *pCurrentNode = &(apTdmList->mNodePool[acpTdm->mTdIdx]);
  int32_t retVal = FDMA_DRV_FAILURE;
  
  if(!pCurrentNode->mpTdm)
  {
    if(apTdmList->mpTail != NULL)
    {
      apTdmList->mpTail->mpNext = pCurrentNode;
    } // if not empty
    else
    {
      apTdmList->mpHead = pCurrentNode;
    } // else from if not empty
    
    pCurrentNode->mpPrev = apTdmList->mpTail;  
    
    apTdmList->mpTail = pCurrentNode;
    ++apTdmList->mLength;
    
    pCurrentNode->mpNext = NULL;
    pCurrentNode->mpTdm = acpTdm;  
    
    retVal = FDMA_DRV_SUCCESS;
  } // if TDM not in the list yet
  
  return retVal;
} // FDMA_TdmListPushBack()

//****************************************************************************

FDMA_Tdm_t* FDMA_TdmListPopFront(FDMA_TdmList_t *apTdmList)
{
  FDMA_TdmListNode_t *pCurrentNode = apTdmList->mpHead;
  FDMA_Tdm_t *pRet = NULL;
  
  if( pCurrentNode != NULL)
  {
     pRet = pCurrentNode->mpTdm;
     
     if(pCurrentNode->mpNext != NULL)
     {
       pCurrentNode->mpNext->mpPrev = NULL;
       apTdmList->mpHead = pCurrentNode->mpNext;
     } // if not last node
     else 
     {
       apTdmList->mpHead = NULL;
       apTdmList->mpTail = NULL;
     } // else from if not last node
     
     --apTdmList->mLength;     
     
     // reset the node
     pCurrentNode->mpPrev = NULL;
     pCurrentNode->mpNext = NULL;
     pCurrentNode->mpTdm = NULL;
  } // if list not empty
  
  return pRet;  
} // FDMA_TdmListPopFront()

//****************************************************************************

FDMA_Tdm_t* FDMA_TdmListPopBack(FDMA_TdmList_t *apTdmList)
{
  FDMA_TdmListNode_t *pCurrentNode = apTdmList->mpTail;
  FDMA_Tdm_t *pRet = NULL;
  
  if( pCurrentNode != NULL)
  {
     pRet = pCurrentNode->mpTdm;
     
     if(pCurrentNode->mpPrev != NULL)
     {
       pCurrentNode->mpPrev->mpNext = NULL;
       apTdmList->mpTail = pCurrentNode->mpPrev;
     } // if not last node
     else 
     {
       apTdmList->mpHead = NULL;
       apTdmList->mpTail = NULL;
     } // else from if not last node
     
     --apTdmList->mLength;     
     
     // reset the node
     pCurrentNode->mpPrev = NULL;
     pCurrentNode->mpNext = NULL;
     pCurrentNode->mpTdm = NULL;
  } // if list not empty
  
  return pRet;  
} // FDMA_TdmListPopBack()

//****************************************************************************

FDMA_Tdm_t* FDMA_TdmFreePop()
{
  FDMA_Tdm_t *lpFreeTdm = NULL;
          
  //try to pop free TD
  lpFreeTdm = FDMA_TdmListPopFront(&sFreeTdmList);
  
  return lpFreeTdm;
} // FDMA_Td_t* FDMA_TdFreePop()

//****************************************************************************

int32_t FDMA_TdRelease(FDMA_Tdm_t* apTdm)
{
  int32_t lRet = FDMA_DRV_SUCCESS;
  FDMA_Tdm_t *lpFreeTdm = NULL;
    
  if(apTdm->mTdIdx < FDMA_TD_CNT)
  {
    // remember pointer to the TDM to be freed
    lpFreeTdm = &sTdmArr[apTdm->mTdIdx];
    
    // reset the TD      
    memset(&(spTdt[TDT_ISP0].mpBase[apTdm->mTdIdx]), 0, sizeof(FDMA_Td_t));
      
    //set TDM as free
    lpFreeTdm->mReserved = 0;
    lpFreeTdm->mOwnerProcId = 0;
    
    //try to push free TDM
    if( FDMA_TdmListPushFront(&sFreeTdmList, lpFreeTdm) != FDMA_DRV_SUCCESS )
    {
      VDB_LOG_ERROR("Push free failed.\n");
      lRet = FDMA_DRV_FAILURE;
    } // if push failed
  }else
  {
    VDB_LOG_WARNING("No such TD index (%u). No action taken.\n", (unsigned) apTdm->mTdIdx);
    lRet = FDMA_DRV_FAILURE;
  }
  
  return lRet;
} // int32_t FDMA_TdRelease(FDMA_Tdm_t* apTdm)

//****************************************************************************

uint32_t FDMA_TdmFreeCntGet()
{   
  return sFreeTdmList.mLength;
} // uint32_t FDMA_TdFreeCntGet()

//****************************************************************************

int32_t FDMA_TdConfig( const FDMA_Tc_t* apcTc)
{  
  int32_t lRet = FDMA_DRV_SUCCESS;
  if(apcTc != NULL)
  {
    if(apcTc->mTdm.mTdIdx < FDMA_TD_CNT)
    {
      spTdt[TDT_USER].mpBase[apcTc->mTdm.mTdIdx] = apcTc->mTd;
    }else
    {
      VDB_LOG_WARNING("No such TD index (%u). No action taken.\n", (unsigned) apcTc->mTdm.mTdIdx);
      lRet = FDMA_DRV_FAILURE;
    }
  }else
  {
    VDB_LOG_ERROR("Tc is NULL.\n");
    lRet = FDMA_DRV_FAILURE;
  }
  return lRet;
} // uint32_t FDMA_TdConfig( const FDMA_Tc_t* apcTc)

//****************************************************************************

int32_t FDMA_TdIspConfig( const FDMA_Tc_t* apcTc)
{  
  int32_t lRet = FDMA_DRV_SUCCESS;
  if(apcTc != NULL)
  {
    if(apcTc->mTdm.mTdIdx < FDMA_TD_CNT)
    {
      // set both ping-pong TDs
      spTdt[TDT_ISP0].mpBase[apcTc->mTdm.mTdIdx] = apcTc->mTd;
      spTdt[TDT_ISP1].mpBase[apcTc->mTdm.mTdIdx] = apcTc->mTd;
    }else
    {
      VDB_LOG_WARNING("No such TD index (%u). No action taken.\n", (unsigned) apcTc->mTdm.mTdIdx);
      lRet = FDMA_DRV_FAILURE;
    }
  }else
  {
    VDB_LOG_ERROR("Tc is NULL.\n");
    lRet = FDMA_DRV_FAILURE;
  }
  return lRet;
} // uint32_t FDMA_TdIspConfig( const FDMA_Tc_t* apcTc)

//****************************************************************************

int32_t FDMA_TcSchedule( const FDMA_Tc_t* apcTc)
{  
  int32_t lRet = FDMA_DRV_SUCCESS;
  if(apcTc != NULL)
  {
    if(apcTc->mTdm.mTdIdx < FDMA_TD_CNT)
    {
      // find out queue status
      if( spFdmaRegs->XFR_STAT.R & 0x2 )
      {
        lRet = FDMA_DRV_ERR_QUEUE_FULL;
        VDB_LOG_WARNING("FDMA transaction queue full.\n");
      } // if queue full
      else
      {
        uint32_t lLineNums = 0;
        // Set DDR current line - 0x3FFF = use value from TD in SRAM
        //line_nums = 0x3FFFFFFF;//usrTc.mTd.mDdrCurrLine << 16;
        
        lLineNums = apcTc->mTd.mSramCurrLine << 16;
        lLineNums |= apcTc->mTd.mDdrCurrLine;  
          
        spFdmaRegs->XFR_LINE_NUM.R = lLineNums;
        
        VDB_LOG_NOTE("LINE_NUM.R = 0x%x\n", (unsigned) lLineNums);
        
        // schedule the transaction
        spFdmaRegs->XFR_REC_NUM.R = FDMA_TD_CNT*TDT_USER + apcTc->mTdm.mTdIdx;
      } //else from if queue full   
    }else
    {
      VDB_LOG_WARNING("No such TD index (%u). No action taken.\n", (unsigned) apcTc->mTdm.mTdIdx);
      lRet = FDMA_DRV_FAILURE;
    }
  }else
  {
    VDB_LOG_ERROR("Tc is NULL.\n");
    lRet = FDMA_DRV_FAILURE;
  }
  return lRet;
} // int32_t FDMA_TcSchedule( const FDMA_Tc_t* apcTc)

//****************************************************************************

FDMA_Regs_t* FDMA_RegsGet()
{  
  return spFdmaRegs;
} // FDMA_Regs_t* FDMA_RegsGet()

//****************************************************************************

int32_t FDMA_TcGet(FDMA_Tc_t* apTc)
{  
  int32_t lRet = FDMA_DRV_SUCCESS;
  
  if(apTc != NULL)
  {
    if(apTc->mTdm.mTdIdx < FDMA_TD_CNT)
    {
      // read the TD  
      apTc->mTd = spTdt[TDT_USER].mpBase[apTc->mTdm.mTdIdx];
      apTc->mTdm = sTdmArr[apTc->mTdm.mTdIdx];
    }else
    {
      VDB_LOG_WARNING("No such TD index (%u). No action taken.\n", (unsigned) apTc->mTdm.mTdIdx);
      lRet = FDMA_DRV_FAILURE;
    }    
  }else
  {
    VDB_LOG_ERROR("Supplied TC is NULL. No action taken.\n");
    lRet = FDMA_DRV_FAILURE;
  }
  
  return lRet;
} // int32_t FDMA_TcGet(FDMA_Tc_t* apTc)

//****************************************************************************

uint32_t FDMA_TdtPhysAddrGet()
{   
  return (uint32_t)SRAM_V2P(spTdt[TDT_USER].mpBase, gSRAM_V2pOffset);
} // int32_t FDMA_TdtPhysAddrGet()

//****************************************************************************

uint32_t FDMA_IspTdtPhysAddrGet()
{   
  return (uint32_t)SRAM_V2P(spTdt[TDT_ISP0].mpBase, gSRAM_V2pOffset);
} // int32_t FDMA_IspTdtPhysAddrGet()

//****************************************************************************

void FDMA_MemPrint(uint8_t *apMem, uint32_t aSize, char* apCaption)
{
  uint32_t i = 0;
#if !defined(__STANDALONE__)   
  if( apCaption != NULL)
  {    
    printk("%s", apCaption);
  } // if caption set
  
  for(i = 0; i < aSize; i++)
  {
    if((i % 4) == 0)
    {
      printk("\n%2u:\t", i / 4);
    }
    printk("%2x ", apMem[i]); 
  }
  printk("\n");
#else
  if( apCaption != NULL)
  {    
    printf("%s", apCaption);
  } // if caption set
  
  for(i = 0; i < aSize; i++)
  {
    if((i % 4) == 0)
    {
      printf("\n%2u:\t", (unsigned)(i / 4));
    }
    printf("%2x ", apMem[i]); 
  }
  printf("\n");
#endif

} // MemPrint

//*****************************************************************************

void* IoMemSet(void* apAddr, uint8_t aValue, size_t aSize)
{
  size_t i = 0;
  uint8_t *lpDst = (uint8_t*)apAddr;
  for(i = 0; i < aSize; i++)
  {
    *lpDst++ = aValue;
  } // for all bytes
  return lpDst;
} // IoMemSet

//*****************************************************************************
#ifdef __STANDALONE__
void msleep(uint32_t aMsec)
{
  //usleep(aMsec * 1000);
  volatile uint64_t i = 0;
  uint64_t stop = aMsec * 2000;
  while(i < stop)
	i++;
	
  stop = 0;
}
#endif // __STANDALONE__
//*****************************************************************************

#if !defined(__STANDALONE__) && defined(__KERNEL__)
EXPORT_SYMBOL(FDMA_IspTdtPhysAddrGet);
#endif // #if !defined(__STANDALONE__) && defined(__KERNEL__)
