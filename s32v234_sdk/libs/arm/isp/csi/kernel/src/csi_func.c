/******************************************************************************
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
 * (INCLUDING, BUT NOT LIMITEDl TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * \file    csi_func.c
 * \brief   Mipi csi receiver interface functionality implementation.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    18-September-2015
 ****************************************************************************/

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
  #include <stddef.h>
  #include <math.h>
  #include "oal.h"
  #include "i2c.h"
  
  #include "seq_sa_kernel_api.h"
#endif // else from if !defined(__STANDALONE__)

#include "config.h"
#include "csi.h"
#include "csi_func.h"
#include "sony_func.h"
#include "vdb_log.h"
#include "ov10640_config_mipi.h"

//****************************************************************************
// consts
//****************************************************************************
#define CSI_LANES     2   ///< number of CSI lanes used
//#define CSI_DATA_FREQ (594/CSI_LANES) ///< data frequency per lane [MHz] - SONY
#define CSI_DATA_FREQ (369/CSI_LANES) ///< data frequency per lane [MHz] - OV
#ifdef CAM_MAXIM
  #define CAM_CNT CAM_MAXIM
#else
  #define CAM_CNT 1
#endif // #ifdef CAM_MAXIM
#define OV10640_CAM_ADDR 0x60  ///< i2c ov10640 camera address
#define BITS_PER_PIXEL   12
#define BYTES_PER_PIXEL   2
#define FPS              30

//****************************************************************************
// macros
//****************************************************************************
#define CSI_UI(_freq) (1000.0/(_freq))
#define CSI_HSSETL_MIN(_freq) (85 + 6*CSI_UI(_freq))
#define CSI_HSSETL_MAX(_freq) (145 + 10*CSI_UI(_freq))
#define HSSETL_COMPUTE(_freq) ((uint32_t)(((CSI_HSSETL_MIN(_freq) + CSI_HSSETL_MAX(_freq))/30) - 1))

//****************************************************************************
// static global variables
//****************************************************************************
static CSI_Regs_t *spCsi[] = {0, 0};
#ifdef __STANDALONE__
  #ifdef OLD_EVB
    static uint8_t sI2cBus[]  = {I2C0, I2C2};
  #else
    static uint8_t sI2cBus[]  = {I2C0, I2C1};
  #endif // else from ifdef OLD_EVB
#endif // #ifdef __STANDALONE__
static uintptr_t sSramBuffAddr[] = {0, 0};
static void(*spIrqHandler[2])(void) = {NULL, NULL};

//****************************************************************************
// global variables
//****************************************************************************

#if !defined(__STANDALONE__)
// Csi locking mutex
mutex_t gCsiMutex;
#endif //#if !defined(__STANDALONE__)

//****************************************************************************
// functions declarations
//****************************************************************************
static int32_t CsiRegsMap(void);
static void CsiRegsUnmap(void);
static int32_t Siul2Init(enum CSI_IDX aCsiIdx);
int32_t CSI_DRV_IrqsRequest(void);

#ifdef __STANDALONE__
  static void CSI0_IrqHandler(void);
  static void CSI1_IrqHandler(void);
#else // #ifdef __STANDALONE__
  void CSI_DRV_IrqsFree(void);
  irqreturn_t CSI0_IrqHandler(int32_t aIrq, void *apDev_id);
  irqreturn_t CSI1_IrqHandler(int32_t aIrq, void *apDev_id);
#endif // else from #ifdef __STANDALONE__

//****************************************************************************

#if defined(__KERNEL__) || defined(__STANDALONE__)

int32_t CSI_DRV_Setup()
{
  int32_t lRet = CSI_DRV_SUCCESS;
  
  // turn on both CSI interfaces
  Siul2Init(CSI_IDX_0);
  Siul2Init(CSI_IDX_1);
  
  // initialize pin config
  if(CsiRegsMap() != CSI_DRV_SUCCESS)
  {
    lRet = CSI_DRV_FAILURE;
    goto csi_regmap_failed;
  } // if driver data init failed  
  
  // request irqs
  CSI_DRV_IrqsRequest();
  
  csi_regmap_failed:
  
  return lRet;
} // CSI_Setup()

//****************************************************************************

void CSI_DRV_Close()
{
  CsiRegsUnmap();
} // CSI_Close()

//****************************************************************************

static int32_t CsiRegsMap()
{
  int32_t lRet = CSI_DRV_SUCCESS;
      
  spCsi[0] = (CSI_Regs_t*) ioremap((uintptr_t)CSI0_BASE, sizeof(CSI_Regs_t));
  if(spCsi[0] == NULL)
  {
    VDB_LOG_ERROR("Failed to map CSI0 registers.\n");
    lRet = CSI_DRV_FAILURE;
  } // if CSI0 registers not mapped
  else
  {   
    spCsi[1] = (CSI_Regs_t*) ioremap((uintptr_t)CSI1_BASE, sizeof(CSI_Regs_t));
    if(spCsi[1] == NULL)
    {
      VDB_LOG_ERROR("Failed to map CSI1 registers.\n");
      lRet = CSI_DRV_FAILURE;
    } // if CS1 registers not mapped
       
  } // if SUIL2 registers not mapped
  return lRet;
} //CsiRegsMap()

//****************************************************************************

static void CsiRegsUnmap()
{    
  if(spCsi[0])
  {
    iounmap(spCsi[0]);
//     spCsi[0] = NULL;
  }
  if(spCsi[1])
  {
    iounmap(spCsi[1]);
    spCsi[1] = NULL;
  }
} //CsiRegsMap()

//****************************************************************************

static int32_t Siul2Init(enum CSI_IDX aCsiIdx)
{
  int32_t lRet = CSI_DRV_SUCCESS;
  CSI_Siul2Regs_t *lpSiul2Regs = NULL;
    
  lpSiul2Regs = (CSI_Siul2Regs_t*) ioremap((uintptr_t)&SIUL2, sizeof(CSI_Siul2Regs_t));
  if(lpSiul2Regs == NULL)
  {
    VDB_LOG_ERROR("Failed to map SUIL2 registers.\n");
    lRet = CSI_DRV_FAILURE;
  } // if SUIL2 registers not mapped
  else
  {   
    // *** turn on Sony cam ***
    if(aCsiIdx == CSI_IDX_0)
    {
      // wake up camera
      lpSiul2Regs->MSCR[38].B.MUX_MODE = 0;  // GPIO mux mode selected
      lpSiul2Regs->MSCR[38].B.OBE = 1;   // output buffer enabled
      lpSiul2Regs->MSCR[38].B.DSE = 7;   // Drive Strenght

      lpSiul2Regs->GPDO[9].B.PDO_4n2 = 1;
    } // if CSI_IDX_0
    else if(aCsiIdx == CSI_IDX_1)
    {
      lpSiul2Regs->MSCR[31].B.MUX_MODE = 0;  // GPIO mux mode selected
      lpSiul2Regs->MSCR[31].B.OBE = 1;   // output buffer enabled
      lpSiul2Regs->MSCR[31].B.DSE = 7;   // Drive Strenght

      lpSiul2Regs->GPDO[7].B.PDO_4n3 = 1;
    } // if CSI_IDX_1
   
    iounmap(lpSiul2Regs);
  } // if SUIL2 registers not mapped
  return lRet;
} // Siul2Init(enum CSI_IDX aIdx)

//****************************************************************************

void CSI_DRV_Config(const CSI_Cfg_t *apcCsiCfg)
{  
  if(apcCsiCfg != NULL)
  {
    uint8_t  lCsiIdx  = CSI_IDX_GET(apcCsiCfg->mIdKey);
    uint32_t i        = 0;
    uint32_t lCsiIrqs = 0;
    uint32_t lMbps    = 0; 
  
    Siul2Init(lCsiIdx);

#ifndef __STANDALONE__  
    msleep(10);
#endif //#ifndef __STANDALONE__

    // start csi config
    spCsi[lCsiIdx]->CONC.B.NULANE = CSI_LANES - 1; //Two Lanes to Receive MIPI Data
    spCsi[lCsiIdx]->PHYC.B.PDRX   = 0x0; //Power down disabled
    //spCsi[lCsiIdx]->PHYC.B.ENPDES = 0x0; //DPHY clock and data lane 1Gbps

// Camera data rate for 2 MIPI CSI lanes coming from datasheet = 297Mbps = SONY
// UI = 3.367ns
// -------------------------------------------------
//         |Minimum   |Typical  | Maximum
// -------------------------------------------------
// THS_SETL|85+6xUI   | 142     | 145+10xUI=179
// -------------------------------------------------
// HSSETL  |(THS_SETL/15)-1| 9    | (THS_SETL/15)-1
// -------------------------------------------------

  
// Camera data rate for 2 MIPI CSI lanes coming from datasheet = 297Mbps = SONY
// UI = 3.367ns
// -------------------------------------------------
//         |Minimum   |Typical  | Maximum
// -------------------------------------------------
// THS_SETL|85+20=105 | 142     | 145+34=179
// -------------------------------------------------
// HSSETL  |(105/15)-1=6 | 9       | (179/15)-1=11
// -------------------------------------------------

// Camera data rate for 2 MIPI CSI lanes coming from datasheet = 185Mbps = OV
// UI = 5.405ns
// -------------------------------------------------
//         |Minimum   |Typical  | Maximum
// -------------------------------------------------
// THS_SETL|85+20=117 | 158     | 199
// -------------------------------------------------
// HSSETL  |(117/15)-1=7 | 9       | (199/15)-1=12
// -------------------------------------------------

    lMbps = (apcCsiCfg->mpVc[i].mLineBytes / BYTES_PER_PIXEL * BITS_PER_PIXEL *\
            apcCsiCfg->mpVc[i].mFrameHeight * FPS)>>20;
    lMbps = CSI_DATA_FREQ * CAM_CNT;
    lMbps = HSSETL_COMPUTE(lMbps );
    spCsi[lCsiIdx]->CLKCS.B.HSSETL  = lMbps;
    spCsi[lCsiIdx]->LAN0CS.B.D0HSET = lMbps;
    spCsi[lCsiIdx]->LAN1CS.B.D1HSET = lMbps;
    
    sSramBuffAddr[lCsiIdx] = apcCsiCfg->mpVc[0].mBufAddr;
    for(i = 0; i < CSI_CHNL_CNT; i++)
    {
      if(CSI_VC_IDX_USED(apcCsiCfg->mIdKey, i))
      {
        spCsi[lCsiIdx]->CH[i].SRTPTR.R           = apcCsiCfg->mpVc[i].mBufAddr;
        // length of buffer line in bytes (1312 pix, 2bytes/pix => 2624bytes)
        // 8bytes aligned - includes the padding
        spCsi[lCsiIdx]->CH[i].BUFLLEN.B.BUFLLEN  = apcCsiCfg->mpVc[i].mLineStride;
        // length of buffer line in bytes (1312 pix, 2bytes/pix => 2624bytes)
        // without the padding
        spCsi[lCsiIdx]->CH[i].LINLEN.B.LINLEN    = apcCsiCfg->mpVc[i].mLineBytes;
        // number of lines to generate DONE signal to Sequencer
        spCsi[lCsiIdx]->CH[i].LPDI.B.LPDI        = apcCsiCfg->mpVc[i].mDoneLineCnt;
        // number of lines available in SRAM
        spCsi[lCsiIdx]->CH[i].NUMLINE.B.NULINE   = apcCsiCfg->mpVc[i].mLineCnt;
        // number of lines expected per frame
        spCsi[lCsiIdx]->CH[i].EXPCTDL.B.EXPLINES = apcCsiCfg->mpVc[i].mFrameHeight;
        
        lCsiIrqs |= (0x2 << (i*4)); // set Frame end interrupt
        //spCsi[lCsiIdx]->INTRENVC.B.FE0IE = 1; // interrupt enabled
        lCsiIrqs |= (0x1 << (i*4)); // set Frame start interrupt
        //spCsi[lCsiIdx]->INTRENVC.B.FS0IE = 1; // interrupt enabled
      } // if VC used
    } // for all possible VCs
  
    spCsi[lCsiIdx]->INTRENVC.R  = lCsiIrqs; // apply CSI setup
    spCsi[lCsiIdx]->ERPPINTEN.R = 0x7F; //Protocol Packet Error Interrupt Enable
    spCsi[lCsiIdx]->ERPHYIE.R   = 0xF; //Phy Error Interrupt Enable Register 
  } // if config not NULL
  else
  {
    VDB_LOG_ERROR("Config structure is NULL.\n");
  } // else from if config not NULL
} // CSI_Config()

//****************************************************************************

void CSI_DRV_Stop(CSI_IdKey_t aCsiIdKey)
{
  uint8_t  lCsiIdx     = CSI_IDX_GET(aCsiIdKey);
  uint32_t i           = 0;
  uint32_t lChnlEnable = 0;
  
  // stop CSI receiver
  spCsi[lCsiIdx]->RXEN.B.RXEN = 0; // Receive disable
  spCsi[lCsiIdx]->ENABLECH.B.CHOEN = 0;	// Disable Virtual Channel Zero

  for(i = 0; i < CSI_CHNL_CNT; i++)
  {
    if(CSI_VC_IDX_USED(aCsiIdKey, i))
    {
      lChnlEnable |= (1 << i);
    } // if VC used
  } // for all possible VCs
  
  spCsi[lCsiIdx]->ENABLECH.R = (~lChnlEnable); // Enable Virtual Channel Zero
  
  //SONY_DRV_CsiDisable(lCsiIdx);

#ifdef __STANDALONE__  
  // disable IRQs
  OAL_IRQDisable(CSI0_ERR_IRQ);
  OAL_IRQDisable(CSI0_FRM_IRQ);
  OAL_IRQDisable(CSI1_ERR_IRQ);
  OAL_IRQDisable(CSI1_FRM_IRQ);
  
#else // ifdef __STANDALONE__

#endif // else from ifdef __STANDALONE__
  
} // CSI_Stop();

//****************************************************************************

void CSI_DRV_Start(CSI_IdKey_t aCsiIdKey)
{
  uint8_t  lCsiIdx     = CSI_IDX_GET(aCsiIdKey);
  uint32_t i           = 0;
  uint32_t lChnlEnable = 0;
  //spCsi[lCsiIdx]->ERPHYIE.R = 0x0000ffff;
  //spCsi[lCsiIdx]->ERPPINTEN.R = 0x0000ffff;
  spCsi[lCsiIdx]->RXEN.B.RXEN = 1; // Receive enable
  
  while(!spCsi[lCsiIdx]->RESCS.B.CALCOM)
  {
  } // while not ready
  
  for(i = 0; i < CSI_CHNL_CNT; i++)
  {
    if(CSI_VC_IDX_USED(aCsiIdKey, i))
    {
      lChnlEnable |= (1 << i);
    } // if VC used
  } // for all possible VCs
  
  spCsi[lCsiIdx]->ENABLECH.R = lChnlEnable;	// Enable Virtual Channel Zero
  
} // CSI_Start()

//****************************************************************************

void CSI_DRV_IrqHandlerSet(enum CSI_IDX aCsiIdx, void (*apIrqHandler)(void))
{
  if( aCsiIdx == CSI_IDX_0)
  {
#ifdef __STANDALONE__      
    //OAL_IRQInit(CSI0_IrqHandler, CSI0_ERR_IRQ, 0xA0, IRQ_EDGE);
    OAL_IRQInit(CSI0_IrqHandler, CSI0_FRM_IRQ, 0xA0, IRQ_EDGE);
    //OAL_IRQInit(CSI0_IrqHandler, CSI0_ERR_IRQ, 0xA0, IRQ_EDGE);
    //OAL_IRQInit(CSI0_IrqHandler, CSI0_FRM_IRQ, 0xA0, IRQ_EDGE);
    
    //OAL_IRQEnable(CSI0_ERR_IRQ);
    OAL_IRQEnable(CSI0_FRM_IRQ);
    //OAL_IRQEnable(CSI0_ERR_IRQ);
    //OAL_IRQEnable(CSI0_FRM_IRQ);
#else // ifdef __STANDALONE__

#endif // else from ifdef __STANDALONE__
  } // if CSI idx == 0
  else if( aCsiIdx == CSI_IDX_1)
  {
#ifdef __STANDALONE__      
    //OAL_IRQInit(CSI1_IrqHandler, CSI1_ERR_IRQ, 0xA0, IRQ_EDGE);
    OAL_IRQInit(CSI1_IrqHandler, CSI1_FRM_IRQ, 0xA0, IRQ_EDGE);
    //OAL_IRQInit(CSI1_IrqHandler, CSI1_ERR_IRQ, 0xA0, IRQ_EDGE);
    //OAL_IRQInit(CSI1_IrqHandler, CSI1_FRM_IRQ, 0xA0, IRQ_EDGE);
    
    //OAL_IRQEnable(CSI1_ERR_IRQ);
    OAL_IRQEnable(CSI1_FRM_IRQ);
    //OAL_IRQEnable(CSI1_ERR_IRQ);
    //OAL_IRQEnable(CSI1_FRM_IRQ);
#else // ifdef __STANDALONE__

#endif // else from ifdef __STANDALONE__
    
  } // if CSI idx == 1
  
  spIrqHandler[aCsiIdx] = apIrqHandler;
} // CSI_DRV_IrqHandlerSet()

//****************************************************************************

int32_t CSI_DRV_IrqsRequest()
{
  int32_t lRet = CSI_DRV_SUCCESS;
#ifndef __STANDALONE__ 
  if (request_irq(CSI0_FRM_IRQ, &CSI0_IrqHandler, IRQF_TRIGGER_RISING, CSI_DEVICE_NAME, NULL))
  {
    lRet = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request IRQ for CSI0.\n");
    printk("CSI0 failed \n");
  } // if request for MSG IRQ failed
  
  if (request_irq(CSI1_FRM_IRQ, &CSI1_IrqHandler, IRQF_TRIGGER_RISING, CSI_DEVICE_NAME, NULL))
  {
    lRet = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("Failed to request IRQ for CSI1.\n");
    printk("CSI1 failed \n");
  } // if request for MSG_ACK IRQ failed
  
#endif // from #ifndef __STANDALONE__ 
  return lRet;
} // CSI_DRV_IrqsRequest()

//*****************************************************************************

void CSI_DRV_IrqsFree()
{
#ifndef __STANDALONE__   
  free_irq(CSI0_FRM_IRQ, NULL);
  free_irq(CSI1_FRM_IRQ, NULL); 
#endif // #ifndef __STANDALONE__ 
} // CSI_DRV_IrqsFree()

//****************************************************************************
#if 0
void CSI_StatusPrint(enum CSI_IDX aCsiIdx)
{
	printf("Embed next prt: 0x%08x\n", spCsi[aCsiIdx]->EMBEDNP.R);  //B.NXTPTR;
	printf("Ch[0] next line: 0x%x\n", spCsi[aCsiIdx]->CH[0].NXTLIN.R);  //B.NXTLINE 
	printf("Ch[0] err line: 0x%x\n", spCsi[aCsiIdx]->CH[0].ERRLINE.R); //B.LINNUM
	printf("Ch[0] err len: 0x%x\n", spCsi[aCsiIdx]->CH[0].ERRLEN.R);  //B.ERRLEN
	printf("Ch[0] IRQ status: 0x%x\n", spCsi[aCsiIdx]->INTRSVC.R);
} // CSI_StatusPrint()
#endif // 0

//****************************************************************************

// *** frame end interrupt ***
#define FRM_RST_CNT 0
static int32_t lFrmCnt = 0;

#ifndef __STANDALONE__
irqreturn_t CSI0_IrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t ret = IRQ_HANDLED;
#else // #ifndef __STANDALONE__
static void CSI0_IrqHandler()
{      
#endif // else from #ifndef __STANDALONE__
  
  uint32_t lIrqReset = 0;

#ifdef	RESET_CSI_INTERFACE  
  if(lFrmCnt >= FRM_RST_CNT)
  {
    spCsi[0]->ENABLECH.B.CHOEN = 0; // Disable Virtual Channel Zero
  } // if reset count reached
#endif

  if(spCsi[0]->INTRSVC.B.FS0)
  {
    lIrqReset += CSI_IRQ_TYPE_SOF; // reset frame start
  } // if frame start signaled
  
  if(spCsi[0]->INTRSVC.B.FE0)
  {
    lIrqReset += CSI_IRQ_TYPE_EOF; // reset frame end
  } // if frame end signaled
  
  if(spCsi[0]->INTRSVC.B.LLENE0)
  {
    // reset disabled to see it in LTB
    //lIrqReset += CSI_IRQ_TYPE_LLE; // reset line length error
  } // if line length error signaled
  
  if(spCsi[0]->INTRSVC.B.LCNTE0)
  {
    // reset disabled to see it in LTB
    //lIrqReset += CSI_IRQ_TYPE_LCE; // reset line count error
  } // if line count error signaled
  
  spCsi[0]->INTRSVC.R = lIrqReset; // reset all signaled interrupts
  
#if defined(CAM_SONY_SE) || defined(CAM_SONY_DOL)
  SONY_DRV_IrqHandler(CSI_IDX_0, lIrqReset);
#endif // #ifdef CAM_SONY_SE    
  
  if(spIrqHandler[0] != NULL)
  {
    spIrqHandler[0]();
  }
  
#ifdef RESET_CSI_INTERFACE
  spCsi[0]->ENABLECH.B.CHOEN = 1;	// Enable Virtual Channel Zero
#endif
  lFrmCnt++;
  
#ifndef __STANDALONE__
  return IRQ_HANDLED;
#endif // #ifndef __STANDALONE__
} // CSI0_IrqHandler()

//****************************************************************************

#ifndef __STANDALONE__
irqreturn_t CSI1_IrqHandler(int32_t aIrq, void *apDev_id)
{
  int32_t ret = IRQ_HANDLED;
#else // #ifndef __STANDALONE__
static void CSI1_IrqHandler()
{      
#endif // else from #ifndef __STANDALONE__

  uint32_t lIrqReset = 0;

#ifdef  RESET_CSI_INTERFACE   
  if(lFrmCnt >= FRM_RST_CNT)
  {
    spCsi[1]->ENABLECH.B.CHOEN = 0; // Disable Virtual Channel Zero
  } // if reset count reached
#endif

  if(spCsi[1]->INTRSVC.B.FS0)
  {
    lIrqReset += CSI_IRQ_TYPE_SOF; // reset frame start
  } // if frame start signaled
  
  if(spCsi[1]->INTRSVC.B.FE0)
  {
    lIrqReset += CSI_IRQ_TYPE_EOF; // reset frame end
  } // if frame end signaled
  
  if(spCsi[1]->INTRSVC.B.LLENE0)
  {
    // reset disabled to see it in LTB
    //lIrqReset += CSI_IRQ_TYPE_LLE; // reset line length error
  } // if line length error signaled
  
  if(spCsi[1]->INTRSVC.B.LCNTE0)
  {
    // reset disabled to see it in LTB
    //lIrqReset += CSI_IRQ_TYPE_LCE; // reset line count error
  } // if line count error signaled
  
  spCsi[1]->INTRSVC.R = lIrqReset; // reset all signaled interrupts
  
#if defined(CAM_SONY_SE) || defined(CAM_SONY_DOL)
  SONY_DRV_IrqHandler(CSI_IDX_1, lIrqReset);
#endif // #ifdef CAM_SONY_SE    

  if(spIrqHandler[1] != NULL)
  {
    spIrqHandler[1]();
  }
  
#ifdef  RESET_CSI_INTERFACE   
  spCsi[1]->ENABLECH.B.CHOEN = 1;	// Enable Virtual Channel Zero
#endif

#ifndef __STANDALONE__
  return IRQ_HANDLED;
#endif // #ifndef __STANDALONE__
} // CSI1_IrqHandler()

//****************************************************************************

#endif // #if defined(__KERNEL__) || defined(__STANDALONE__)

/*EOF*/