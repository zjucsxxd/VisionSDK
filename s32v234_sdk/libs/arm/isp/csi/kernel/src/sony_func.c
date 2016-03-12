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
 * \file    sony_func.c
 * \brief   Sony IMX224MQV MIPI/CSI camera functionality.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    31-August-2015
 ****************************************************************************/
#include "config.h"

#if !defined(__STANDALONE__)
  #include <linux/kernel.h>     // We're doing kernel work
  #include <linux/module.h>     // Specifically, a module 
  #include <linux/interrupt.h>  // For interrupts
  #include <asm/siginfo.h>      // siginfo
  #include <linux/sched.h>      // send_sig_info
  #include <linux/types.h>
  #include <linux/delay.h>      // for msleep
  #include <linux/i2c.h>
  #include <asm/io.h>           // for ioremap
  
#else
  #include <stdint.h>
  #include <stddef.h>
  #include "i2c.h"
  #include "oal.h"
  #include "seq_sa_kernel_api.h"
#endif // #if !defined(__STANDALONE__)

#include "s32vs234.h"
#include "csi.h"
#include "csi_types.h"

#ifdef CAM_SONY_SE
  #include "sony_config.h"
#else
//#ifdef CAM_SONY_DOL
  #include "sony_config_DOL2.h"
#endif 
  
#include "sony_func.h"
#include "sony_types.h"
#include "vdb_log.h"
 
//****************************************************************************
// consts
//****************************************************************************

#define STH_CTL
//#define TB_CTL

#define SONY_DRV_SUCCESS CSI_DRV_SUCCESS
#define SONY_DRV_FAILURE CSI_DRV_FAILURE
#define SONY_MODEL_ID_REG_ADDR 0x3399



#define SONY_REG_BEG 0x3000  ///< first register address
#define SONY_REG_END 0x33EF  ///< last register address

//****************************************************************************
// macros
//****************************************************************************
#ifdef __STANDALONE__
#define msleep(_val) (sleep((double)(_val/1000.0)))
#endif

static int32_t sExposure = 32;
static int8_t  sConv = 1;
static int32_t sGain = 0;
static int32_t sExposureSkipFrames = -1; // disabled
//#define DEFINE_PARS

#ifdef DEFINE_PARS
//static uint32_t sPixCnt = 729*1280/4;
#define PIXCNT (729*1280/4)
#define PIXOE  (PIXCNT>>2)   // 25% overexposed pxiels
#define HIST_START_IDX (127)
#define HIST_STOP_IDX  (64)
#define HIST_OE_LEV (HIST_START_IDX-40)
#else
uint32_t  PIXCNT=(729*1280/4);
uint32_t  PIXOE=((729*1280/4)>>2);   // 25% overexposed pxiels
uint32_t  HIST_START_IDX=(127);
uint32_t  HIST_STOP_IDX=(64);
uint32_t  HIST_OE_LEV=(127-40);
#endif


static uint32_t sExpRange = 990;

#define SONY_HIST_RIDX  0
#define SONY_HIST_GRIDX 1
#define SONY_HIST_GBIDX 2
#define SONY_HIST_BIDX  3

//****************************************************************************
// static global variables
//****************************************************************************
#ifdef __STANDALONE__
  #ifdef OLD_EVB
  static uint8_t sI2cBus[]  = {I2C0, I2C2};
  #else
  static uint8_t sI2cBus[]  = {I2C0, I2C1};
  #endif // else from ifdef OLD_EVB
#endif // #ifdef __STANDALONE__
  
// defines the state of the exposure update
static SONY_ExpState_t sExpState[2] = {SONY_EXP_APPLIED, SONY_EXP_APPLIED};

#define DEBUG_EXP 0  
#if (DEBUG_EXP > 0)  
  static uint32_t         sExposureCnt = 0;
  static uint32_t         sExpRec[200][3];
#endif // #if (DEBUG_EXP > 0)  
#ifdef __KERNEL__

static int SonyI2c_Probe(struct i2c_client *client,
                          const struct i2c_device_id *id);
static int SonyI2c_Remove(struct i2c_client *client);
static int32_t I2c_RegWrite16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t aVal);
static int32_t I2c_RegRead16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t *apVal);

// *** Sony I2C ***
struct i2c_client *spSonyI2cCli[2] = {NULL};

static struct i2c_board_info spSonyI2cInfo[2] = {
  {
    I2C_BOARD_INFO("imx224mqv", I2C_SONY_CAM_ADDR)
  },
  {
    I2C_BOARD_INFO("imx224mqv", I2C_SONY_CAM_ADDR)
  },
};

static const struct i2c_device_id sSonyId[] = {
  {"imx224mqv", 0},
  {"imx224mqv", 1},
  {},
};

static struct i2c_driver sSonyI2cDriver = {
  .driver = {
      .owner = THIS_MODULE,
      .name  = "imx224mqv",
      },
  .probe  = SonyI2c_Probe,
  .remove = SonyI2c_Remove,
  .id_table = sSonyId,
};

#endif // #ifdef __KERNEL__

//****************************************************************************
// functions declarations
//****************************************************************************

static int32_t Siul2Init(enum CSI_IDX aIdx);
int32_t SONY_DRV_I2cClientAdd(enum CSI_IDX aCsiIdx);
static int32_t SonyRegWrite(enum CSI_IDX aCsiIdx, 
                                uint16_t aRegAddr, 
                                uint8_t aVal);
static int32_t SonyRegRead(enum CSI_IDX aCsiIdx,
                                  uint16_t aRegAddr, 
                                  uint8_t *apVal);

//****************************************************************************

int32_t SONY_DRV_Setup(enum CSI_IDX aCsiIdx)
{ 
  int32_t lRet = SONY_SUCCESS;
#ifndef __STANDALONE__
  // initialize pin config
  if(Siul2Init(aCsiIdx) != SONY_DRV_SUCCESS)
  {
    lRet = SONY_DRV_FAILURE;
    goto i2c_init_failed;
  } // if driver data init failed                 
  
  msleep(100);
  
  SONY_DRV_I2cClientAdd(aCsiIdx);
#endif
  
  i2c_init_failed:
  
  return lRet;
} // SONY_DRV_Setup()

//****************************************************************************

static int32_t Siul2Init(enum CSI_IDX aCsiIdx)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  CSI_Siul2Regs_t *lpSiul2Regs = NULL;
    
  lpSiul2Regs = (CSI_Siul2Regs_t*) ioremap((uintptr_t)&SIUL2, sizeof(CSI_Siul2Regs_t));
  if(lpSiul2Regs == NULL)
  {
    VDB_LOG_ERROR("Failed to map SUIL2 registers.\n");
    lRet = SONY_DRV_FAILURE;
  } // if SUIL2 registers not mapped
  else
  {
    // *** turn on I2C bus ***
    switch(aCsiIdx)
    {
#ifdef OLD_EVB
      case CSI_IDX_0:
      {
          ///////////////// I2C_0 - MIPI camera ////////////////////////////////////////

          // SDA    
        lpSiul2Regs->MSCR[15].B.MUX_MODE = 1;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[15].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[15].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[15].B.ODE = 1;   // open drain enabled
        lpSiul2Regs->MSCR[15].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[269].B.DAISY = 2;  // PA15 selected as input*/

          // SCL
        lpSiul2Regs->MSCR[16].B.MUX_MODE = 1;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[16].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[16].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[16].B.ODE = 1;   // open drain enabled*/
        lpSiul2Regs->MSCR[16].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[268].B.DAISY = 2;  // PB0 selected as input*/
      } // case CSI_IDX_0:
      break;

      case CSI_IDX_1:
      {       
        // SDA
        lpSiul2Regs->MSCR[17].B.MUX_MODE = 0;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[17].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[17].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[17].B.ODE = 1;   // open drain enabled

        lpSiul2Regs->IMCR[271].B.DAISY = 2;      // PB1 selected as input

        // SCL
        lpSiul2Regs->MSCR[18].B.MUX_MODE = 0;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[18].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[18].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[18].B.ODE = 1;   // open drain enabled
        
        lpSiul2Regs->IMCR[271].B.DAISY = 2;      // PB2 selected as input
      } // case CSI_IDX_1:
      break;
#else
      case CSI_IDX_0:
      {
        ///////////////// I2C_0 - MIPI camera ////////////////////////////////////////

        // SDA    
        lpSiul2Regs->MSCR[99].B.MUX_MODE = 2;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[99].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[99].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[99].B.ODE = 1;   // open drain enabled
        lpSiul2Regs->MSCR[99].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[269].B.DAISY = 3;  // PA15 selected as input*/

        // SCL
        lpSiul2Regs->MSCR[100].B.MUX_MODE = 2;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[100].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[100].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[100].B.ODE = 1;   // open drain enabled*/
        lpSiul2Regs->MSCR[100].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[268].B.DAISY = 3;  // PB0 selected as input*/
      } // case CSI_IDX_0:
      break;

      case CSI_IDX_1:
      {
        ///////////////// I2C_1 - MIPI camera ////////////////////////////////////////

        // SDA    
        lpSiul2Regs->MSCR[101].B.MUX_MODE = 2;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[101].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[101].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[101].B.ODE = 1;   // open drain enabled
        lpSiul2Regs->MSCR[101].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[271].B.DAISY = 3;  // PA15 selected as input*/

        // SCL
        lpSiul2Regs->MSCR[102].B.MUX_MODE = 2;  // GPIO mux mode selected
        lpSiul2Regs->MSCR[102].B.OBE = 1;   // output buffer enabled
        lpSiul2Regs->MSCR[102].B.IBE = 1;   // input buffer enabled
        lpSiul2Regs->MSCR[102].B.ODE = 1;   // open drain enabled*/
        lpSiul2Regs->MSCR[102].B.DSE = 7; // maximum drive strenght

        lpSiul2Regs->IMCR[270].B.DAISY = 3;  // PB0 selected as input*/
      } // case CSI_IDX_1:
      break;
#endif // ifdef OLD_EVB      

      default:
      {
        lRet = SONY_DRV_FAILURE;
      } // default
      break;      
    } // switch(aIdx)
    
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

void SONY_DRV_RegConfig(enum CSI_IDX aCsiIdx)
{
  uint32_t i = 0;
  uint8_t tmp = 0;
  
#ifdef __STANDALONE__  
  I2C_Init_Config(sI2cBus[aCsiIdx],SONY_CAM_ADDR);  
#endif //#ifdef __STANDALONE__ 
  
  //put camera to standby mode
  SonyRegWrite(aCsiIdx, 0x03, 1);
  tmp = SonyRegRead(aCsiIdx, 0x03, &tmp);

  SonyRegWrite(aCsiIdx, 0x0, 1);
  tmp = SonyRegRead(aCsiIdx, 0x00, &tmp);
  
  for(i=0;i<sizeof(Sony_Table);i=i+3)
  {
    SonyRegWrite(aCsiIdx, (Sony_Table[i]<<8)|Sony_Table[i+1], Sony_Table[i+2]);
  }
  
  //I2C_Tx(sI2cBus[aCsiIdx], 0x33, 0x83, thsprepare);
  //I2C_Tx(sI2cBus[aCsiIdx], 0x33, 0x84, thspzero);
  
  SONY_DRV_VmaxGet(aCsiIdx, &sExpRange);
#ifdef CAM_SONY_DOL
  sExpRange<<=1;
#endif
  SONY_DRV_ExpLinesGet(aCsiIdx, &sExposure);
  SONY_DRV_ConvGet(aCsiIdx, &sConv);
  SONY_DRV_GainGet(aCsiIdx, &sGain);
  sExposure = sExpRange-sExposure-1;
  
  SonyRegRead(aCsiIdx, SONY_MODEL_ID_REG_ADDR, &tmp);
} // SONY_DRV_RegConfig(enum CSI_IDX aCsiIdx)

//****************************************************************************

void SONY_DRV_CsiEnable(enum CSI_IDX aCsiIdx)
{
  // bring camera out of standby
  SonyRegWrite(aCsiIdx, 0x3000, 0);
} // MAXIM_CsiEnable()

//****************************************************************************

void SONY_DRV_CsiDisable(enum CSI_IDX aCsiIdx)
{
   // bring camera to standby
  SonyRegWrite(aCsiIdx, 0x3000, 1); 
} // MAXIM_CsiDisable()

//*****************************************************************************

static int32_t SonyRegWrite(enum CSI_IDX aCsiIdx, uint16_t aRegAddr, uint8_t aVal)
{
  int32_t lRet = SONY_DRV_SUCCESS;
#ifdef __STANDALONE__   
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;
  
  I2C_DevTx(sI2cBus[aCsiIdx], SONY_CAM_ADDR >> 1, lpAddr[1], lpAddr[0], aVal);
#else
  lRet = I2c_RegWrite16(spSonyI2cCli[aCsiIdx], aRegAddr, aVal);
#endif // #ifdef __STANDALONE__ 
  return lRet;
} // SonyRegWrite()

//*****************************************************************************

static int32_t SonyRegRead(enum CSI_IDX aCsiIdx, uint16_t aRegAddr, uint8_t *apVal)
{
  int32_t lRet = SONY_DRV_SUCCESS;
#ifdef __STANDALONE__   
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;
  *apVal = I2C_DevRx(sI2cBus[aCsiIdx], SONY_CAM_ADDR >> 1, lpAddr[1], lpAddr[0]);
#else
  lRet = I2c_RegRead16(spSonyI2cCli[aCsiIdx], aRegAddr, apVal);
#endif // #ifdef __STANDALONE__ 
  return lRet;
} //SonyRegRead()

//*****************************************************************************

#ifdef __STANDALONE__
static void sleep(double aSec)
{
  volatile uint64_t i = 0;
  uint64_t stop = aSec * 1000 * 1000 * 2;
  while(i < stop)
  {
    i++;
  } // while(i < stop)
  
  stop = 0;
} //sleep()
#endif 

//*****************************************************************************
#if 0
static int32_t SonyDump(enum CSI_IDX aCsiIdx, uint8_t* apDump, uint16_t aStart, uint16_t aStop)
{
  uint32_t i    = 0;
  int32_t  lRet = SONY_DRV_SUCCESS;
  
  if(aStart < SONY_REG_BEG) 
  {
    aStart = SONY_REG_BEG;
  } // if start too low
  
  if(aStop > SONY_REG_END) 
  {
    aStop = SONY_REG_END;
  } // if stop to high

  for( i = aStart; i <= aStop; i++)
  {
    uint8_t lVal = 0;
    if(SonyRegRead(aCsiIdx, i, &lVal) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
      break;
    }
    apDump[i] = lVal;
  } // for the regs in address span
  
  return lRet;
} // SonyDump()
#endif

//*****************************************************************************

//< winmode registers
#define SONY_WINMODE_ADDR 0x3007
#define SONY_WINMODE_VR   0x1
#define SONY_WINMODE_HR   0x2
#define SONY_WINMODE_QVGA 0x0
#define SONY_WINMODE_720P 0x10
#define SONY_WINMODE_CROP 0x40

//< max frame height registers
#define SONY_VMAXL_ADDR 0x3018
#define SONY_VMAXH_ADDR 0x3019
#define SONY_VMAX_MASK  0x1fff

//< max frame widht registers
#define SONY_HMAXL_ADDR 0x301b
#define SONY_HMAXH_ADDR 0x301c
#define SONY_HMAX_MASK  0x3fff

//< cropping window optical blanking height registers
#define SONY_WINWV_OB_ADDR 0x3036 
#define SONY_WINWV_OB_MASK  0x1f

//< cropping window height registers
#define SONY_WINWVL_ADDR 0x303a 
#define SONY_WINWVH_ADDR 0x303b
#define SONY_WINWV_MASK  0x3ff

//< cropping window width registers
#define SONY_WINWHL_ADDR 0x303e
#define SONY_WINWHH_ADDR 0x303f
#define SONY_WINWH_MASK  0x7ff

//< cropping window offset y registers
#define SONY_WINPVL_ADDR 0x303c 
#define SONY_WINPVH_ADDR 0x303d
#define SONY_WINPV_MASK  0x3ff

//< cropping window offset x registers
#define SONY_WINPHL_ADDR 0x303e
#define SONY_WINPHH_ADDR 0x303f
#define SONY_WINPH_MASK  0x7ff

//< conversion registers
#define SONY_CONV_HIGH  0x1
#define SONY_CONV_LOW   0x0
#define SONY_CONV_MASK  0x10
#define SONY_CONV_ADDR  0x3009  //< address of the conversion gain register

//< number of exposure lines registers
#define SONY_SHS1L_ADDR 0x3020  //< address of number of exposure lines
#define SONY_SHS1H_ADDR 0x3021  //< address of number of exposure lines
#define SONY_SHS1_MASK  0x1fff  //< SHS1[12:0] bitmask //sth 17 bit ??

#define SONY_SHS2L_ADDR 0x3023  //< address of number of exposure lines
#define SONY_SHS2H_ADDR 0x3024  //< address of number of exposure lines
#define SONY_SHS2_MASK  0xffff  //< SHS2[12:0] bitmask

#ifdef CAM_SONY_SE
  #define SONY_LSHSL_ADDR 0x3020  //< address of number of exposure lines
  #define SONY_LSHSH_ADDR 0x3021  //< address of number of exposure lines
  #define SONY_LSHS_MASK  0x1fff  //< SHS1[12:0] bitmask //sth 17 bit ??
#else
  #define SONY_LSHSL_ADDR 0x3023  //< address of number of exposure lines
  #define SONY_LSHSH_ADDR 0x3024  //< address of number of exposure lines
  #define SONY_LSHS_MASK  0xffff  //< SHS1[12:0] bitmask
  #define SONY_SSHSL_ADDR 0x3020  //< address of number of exposure lines
  #define SONY_SSHSH_ADDR 0x3021  //< address of number of exposure lines
  #define SONY_SSHS_MASK  0xffff  //< SHS1[12:0] bitmask
#endif

//< analog gain registers
#define SONY_GAINL_ADDR 0x3014
#define SONY_GAINH_ADDR 0x3015
#define SONY_GAIN_MASK  0x3ff
#define SONY_GAIN_MAX  720

//< max allowed values
#define SONY_WIDTH_MAX   1304
#define SONY_HEIGHT_MAX  976
#define SONY_WWIDTH_MIN  368
#define SONY_WHEIGHT_MIN 304
#define SONY_OB_MAX      16

//*****************************************************************************

int32_t SONY_DRV_ConvGet(enum CSI_IDX aCsiIdx, uint8_t* apConv)
{
  uint8_t lRet = 0;
  lRet = SonyRegRead(aCsiIdx, SONY_CONV_ADDR, apConv);
  
  *apConv = (((*apConv) & SONY_CONV_MASK)?SONY_CONV_HIGH:SONY_CONV_LOW);
  
  return lRet;
} // SONY_DRV_ConvGet()

//*****************************************************************************

int32_t SONY_DRV_ConvHighSet(enum CSI_IDX aCsiIdx)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp = 0;
  if(SonyRegRead(aCsiIdx, SONY_CONV_ADDR, &lTmp) == SONY_DRV_SUCCESS)
  {
    lRet = SonyRegWrite(aCsiIdx, SONY_CONV_ADDR, lTmp|SONY_CONV_MASK);  
  }
  else
  {
    lRet = SONY_DRV_FAILURE;
  }
  
  return lRet;
} // SONY_DRV_ConvHighSet()

//*****************************************************************************

int32_t SONY_DRV_ConvLowSet(enum CSI_IDX aCsiIdx)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp = 0;
  if(SonyRegRead(aCsiIdx, SONY_CONV_ADDR, &lTmp) == SONY_DRV_SUCCESS)
  {
    lRet = SonyRegWrite(aCsiIdx, SONY_CONV_ADDR, lTmp&(~SONY_CONV_MASK));
  }
  else
  {
    lRet = SONY_DRV_FAILURE;
  }
  
  return lRet;  
} // SONY_DRV_ConvLowSet()

//*****************************************************************************

int32_t SONY_DRV_ExpLinesGet(enum CSI_IDX aCsiIdx, uint32_t* apExpLines)
{
  int32_t lRet   = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apExpLines;
  
  if(SonyRegRead(aCsiIdx, SONY_LSHSL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_LSHSH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apExpLines &= SONY_LSHS_MASK;
  
  return lRet;
} // SONY_DRV_ExpLineGet

//*****************************************************************************

#ifdef CAM_SONY_DOL
int32_t SONY_DRV_ExpLinesSGet(enum CSI_IDX aCsiIdx, uint32_t* apExpLines)
{
  int32_t lRet   = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apExpLines;
  
  if(SonyRegRead(aCsiIdx, SONY_SSHSL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_SSHSH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apExpLines &= SONY_SSHS_MASK;
  
  return lRet;
} // SONY_DRV_ExpLinesSGet
#endif // #ifdef CAM_SONY_DOL

//*****************************************************************************

int32_t SONY_DRV_ExpLinesSet(enum CSI_IDX aCsiIdx, uint32_t aLineCnt)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  int32_t lShortLineCnt;
  
  if(aLineCnt > (sExpRange - 3))
  {
    aLineCnt = sExpRange - 3;
  } // correct line count if needed
  
  lTmp = aLineCnt&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_LSHSL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aLineCnt >> 8)&(SONY_LSHS_MASK >> 8);  
    if(SonyRegWrite(aCsiIdx, SONY_LSHSH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }

#ifdef CAM_SONY_DOL
    // short exposure
    lShortLineCnt = +sExpRange - (aLineCnt+1); // to time
    lShortLineCnt >>= 4;  // 1:16 exposure ratio
    lShortLineCnt = 0x31 /*RSH1*/ - lShortLineCnt -1;
    if (lShortLineCnt < 3) lShortLineCnt=3;
    if (lShortLineCnt > 0x2F /*RSH-2*/) lShortLineCnt=0x2F;
    lTmp = lShortLineCnt&0xff;
    if(SonyRegWrite(aCsiIdx, SONY_SSHSL_ADDR, lTmp) == SONY_DRV_SUCCESS)
    {
      lTmp = (lShortLineCnt >> 8)&(SONY_SSHS_MASK >> 8);  
      if(SonyRegWrite(aCsiIdx, SONY_SSHSH_ADDR, lTmp) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      }
    } // if write successfully
    else
    {
      lRet = SONY_DRV_FAILURE;
    } // else from if write successfully
#endif
  } // if write successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_ExpLineSet()

//*****************************************************************************

int32_t SONY_DRV_GainGet(enum CSI_IDX aCsiIdx, uint32_t* apGain)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apGain;
  
  if(SonyRegRead(aCsiIdx, SONY_GAINL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_GAINH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apGain &= SONY_GAIN_MASK;
  
  return lRet;
} // SONY_DRV_GainGet()

//*****************************************************************************

int32_t SONY_DRV_GainSet(enum CSI_IDX aCsiIdx, uint32_t aGain)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  if(aGain > SONY_GAIN_MAX)
  {
    aGain = SONY_GAIN_MAX;
  }

  lTmp = aGain&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_GAINL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aGain >> 8)&(SONY_GAIN_MASK >> 8);
    if(SonyRegWrite(aCsiIdx, SONY_GAINH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_GainSet()

//*****************************************************************************

int32_t SONY_DRV_ExposureEnable(enum CSI_IDX aCsiIdx,int32_t anUpdateRate)
{  
  sExposureSkipFrames=anUpdateRate;
  
  return (sExposureSkipFrames);
} // SONY_DRV_ExposureEnable

//*****************************************************************************

void SONY_DRV_IrqHandler(enum CSI_IDX aCsiIdx, uint32_t aIrqType)
{
  if(aCsiIdx == CSI_IDX_0)
  {
    if(aIrqType && CSI_IRQ_TYPE_EOF)
    {
      if(sExpState[0] == SONY_EXP_SENT)
      {
        sExpState[0] = SONY_EXP_APPLIED; ///< move to updated state
      } // if SENT
      else if(sExpState[0] == SONY_EXP_APPLIED)
      {
        sExpState[0] = SONY_EXP_USED; ///< move to used state
        return;
      } // if APPLIED
    } // if EOF
    
    if(aIrqType && CSI_IRQ_TYPE_SOF)
    {
      if(sExpState[0] == SONY_EXP_USED)
      {
        sExpState[0] = SONY_EXP_READY; ///< move to ready state
      } // if USED
    } // if SOF
  } // if CSI0
  
  if(aCsiIdx == CSI_IDX_1)
  {
    if(aIrqType && CSI_IRQ_TYPE_EOF)
    {
      if(sExpState[1] == SONY_EXP_SENT)
      {
        sExpState[1] = SONY_EXP_APPLIED; ///< move to updated state
      } // if SENT
      else if(sExpState[1] == SONY_EXP_APPLIED)
      {
        sExpState[1] = SONY_EXP_USED; ///< move to used state
        return;
      } // if APPLIED
    } // if EOF
    
    if(aIrqType && CSI_IRQ_TYPE_SOF)
    {
      if(sExpState[1] == SONY_EXP_USED)
      {
        sExpState[1] = SONY_EXP_READY; ///< move to ready state
      } // if USED
    } // if SOF
  } // if CSI1
} // SONY_DRV_IrqHandler()

//*****************************************************************************

SONY_ExpState_t SONY_DRV_ExpStateGet(enum CSI_IDX aCsiIdx)
{    
  return sExpState[aCsiIdx];
} // SONY_DRV_ExpStateGet()

//*****************************************************************************

int32_t SONY_DRV_ExposureSet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  
  if((sExpState[aCsiIdx] == SONY_EXP_READY) && (apExpo != NULL))
  {         
    // hold register values and make synchronously valid
    SonyRegWrite(aCsiIdx, 0x3001, 1); // set to 1 to hold
      
#if (DEBUG_EXP > 0)     
    SONY_DRV_ExpLinesGet(aCsiIdx, &(sExpRecOld[sExposureCnt][0]));
    SONY_DRV_ConvGet(aCsiIdx, &(sExpRecOld[sExposureCnt][1]));
    SONY_DRV_GainGet(aCsiIdx, &(sExpRecOld[sExposureCnt][2]));
    
    sExpRec[sExposureCnt][0] = apExpo->mExposureLines;
    sExpRec[sExposureCnt][1] = apExpo->mConversionGain;
    sExpRec[sExposureCnt][2] = apExpo->mAnalogGain;
    
    sExposureCnt++;
#endif // #if (DEBUG_EXP > 0) 
    
    // flags for all?
    if(apExpo->mConfigFlags == 0)
    {
      apExpo->mConfigFlags = 0xff;
    } // if flags == 0
  
    // analog gain
    if(apExpo->mConfigFlags|SONY_EXP_AG)
    {
      if(SONY_DRV_GainSet(aCsiIdx, apExpo->mAnalogGain) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      } // if not success
    } // if AG

    // exposure lines
    if(apExpo->mConfigFlags|SONY_EXP_EL)
    {
      if(SONY_DRV_ExpLinesSet(aCsiIdx, sExpRange - apExpo->mExposureLines - 1) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      } // if not success
    } // if EL
    
    // conversion gain
    if(apExpo->mConfigFlags|SONY_EXP_CG)
    {
      if(apExpo->mConversionGain == SONY_CONV_LOW)
      {
        if(SONY_DRV_ConvLowSet(aCsiIdx) != SONY_DRV_SUCCESS)
        {
          lRet = SONY_DRV_FAILURE;
        } // if not success
      } // if low
      else
      {
        
        if(SONY_DRV_ConvHighSet(aCsiIdx) != SONY_DRV_SUCCESS)
        {
          lRet = SONY_DRV_FAILURE;
        } // if not success
      } // else from if low
    } // if CG      
    
    SonyRegWrite(aCsiIdx, 0x3001, 0);
    sExpState[aCsiIdx] = SONY_EXP_SENT;
  } // if ready to update the exposure

  return lRet;
} // SONY_DRV_ExposureSet()

//*****************************************************************************

int32_t SONY_DRV_ExposureGet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  if(apExpo != NULL)
  {
    if(apExpo->mConfigFlags == 0)
    {
      apExpo->mConfigFlags = 0xff;
    }
    
    // analog gain
    if(apExpo->mConfigFlags|SONY_EXP_AG)
    {
       if(SONY_DRV_GainGet(aCsiIdx, &(apExpo->mAnalogGain)) != SONY_DRV_SUCCESS)
       {
         lRet = SONY_DRV_FAILURE;
       } // if not success
    } // if AG
    
    // exposure lines
    if(apExpo->mConfigFlags|SONY_EXP_EL)
    {
      if(SONY_DRV_ExpLinesGet(aCsiIdx, &(apExpo->mExposureLines)) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      } //if not success
      else
      {
        apExpo->mExposureLines = sExpRange - apExpo->mExposureLines - 1;
      }
#ifdef CAM_SONY_DOL
      if(SONY_DRV_ExpLinesSGet(aCsiIdx, &(apExpo->mExposureLinesShort)) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      } //if not success
      else
      {
        apExpo->mExposureLinesShort = 0x31 - apExpo->mExposureLinesShort - 1;
      }
#endif // #ifdef CAM_SONY_DOL
    } // if EL
    
    // conversion gain
    if(apExpo->mConfigFlags|SONY_EXP_CG)
    {
      if(SONY_DRV_ConvGet(aCsiIdx, &(apExpo->mConversionGain)) != SONY_DRV_SUCCESS)
      {
        lRet = SONY_DRV_FAILURE;
      } // if not success
    }  // if CG
  } // if apExpo not NULL
  return lRet;
} // SONY_DRV_ExposureGet()

//*****************************************************************************

int32_t SONY_DRV_VmaxGet(enum CSI_IDX aCsiIdx, uint32_t* apVmax)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apVmax;
    
  if(SonyRegRead(aCsiIdx, SONY_VMAXL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_VMAXH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apVmax &= SONY_VMAX_MASK;
  
  return lRet;
} // SONY_DRV_VmaxGet

//*****************************************************************************

int32_t SONY_DRV_VmaxSet(enum CSI_IDX aCsiIdx, uint32_t aLineCnt)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  aLineCnt &= SONY_VMAX_MASK;
  
  lTmp = aLineCnt&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_VMAXL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aLineCnt >> 8)&(SONY_VMAX_MASK >> 8);  
    if(SonyRegWrite(aCsiIdx, SONY_VMAXH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return aLineCnt;
} // SONY_DRV_VmaxSet()

//*****************************************************************************

int32_t SONY_DRV_HmaxGet(enum CSI_IDX aCsiIdx, uint32_t* apHmax)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apHmax;
  
  if(SonyRegRead(aCsiIdx, SONY_HMAXL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_HMAXH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apHmax &= SONY_HMAX_MASK;
  
  return lRet;
} // SONY_DRV_HmaxGet

//*****************************************************************************

int32_t SONY_DRV_HmaxSet(enum CSI_IDX aCsiIdx, uint32_t aColCnt)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  aColCnt &= SONY_HMAX_MASK;
  
  lTmp = aColCnt&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_HMAXL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aColCnt >> 8)&(SONY_HMAX_MASK >> 8);  
    if(SonyRegWrite(aCsiIdx, SONY_HMAXH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_HmaxSet()

//*****************************************************************************

int32_t SONY_DRV_ObWvGet(enum CSI_IDX aCsiIdx, uint8_t* apLineCnt)
{
  uint8_t lRet = 0;
  
  lRet = SonyRegRead(aCsiIdx, SONY_WINWV_OB_ADDR, apLineCnt);
  *apLineCnt &= SONY_WINWV_OB_MASK;
  
  return lRet;
} // SONY_DRV_CropObWvGet()

//*****************************************************************************

int32_t SONY_DRV_ObWvSet(enum CSI_IDX aCsiIdx, uint8_t aLineCnt)
{    
  aLineCnt &= SONY_WINWV_OB_MASK;
  
  return SonyRegWrite(aCsiIdx, SONY_WINWV_OB_ADDR, aLineCnt);
} // SONY_DRV_ObWvSet()

//*****************************************************************************

int32_t SONY_DRV_CropWvSet(enum CSI_IDX aCsiIdx, uint32_t aHeight)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  aHeight &= SONY_WINWV_MASK;
  
  lTmp = aHeight&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_WINWVL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aHeight >> 8)&(SONY_WINWV_MASK >> 8);
    if(SonyRegWrite(aCsiIdx, SONY_WINWVH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_CropWvSet()

//*****************************************************************************

int32_t SONY_DRV_CropWvGet(enum CSI_IDX aCsiIdx, uint32_t* apHeight)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apHeight;
  
  if(SonyRegRead(aCsiIdx, SONY_WINWVL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_WINWVH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apHeight &= SONY_WINWV_MASK;
  
  return lRet;
} // SONY_DRV_CropWvGet()

//*****************************************************************************

int32_t SONY_DRV_CropWhSet(enum CSI_IDX aCsiIdx, uint32_t aWidth)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  aWidth &= SONY_WINWH_MASK;
  
  lTmp = aWidth&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_WINWHL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aWidth >> 8)&(SONY_WINWH_MASK >> 8);
    if(SonyRegWrite(aCsiIdx, SONY_WINWHH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_CropWhSet()

//*****************************************************************************

int32_t SONY_DRV_CropWhGet(enum CSI_IDX aCsiIdx, uint32_t* apWidth)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apWidth;
  
  if(SonyRegRead(aCsiIdx, SONY_WINWHL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_WINWHH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apWidth &= SONY_WINWH_MASK;
  
  return (lRet & SONY_WINWH_MASK);
} // SONY_DRV_CropWhGet()


//*****************************************************************************

int32_t SONY_DRV_CropPvGet(enum CSI_IDX aCsiIdx, uint32_t* apYoff)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apYoff;
  
  if(SonyRegRead(aCsiIdx, SONY_WINPVL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_WINPVH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apYoff &= SONY_WINPV_MASK;
  
  return (lRet & SONY_WINPV_MASK);
} // SONY_DRV_CropPvGet()

//*****************************************************************************

int32_t SONY_DRV_CropPvSet(enum CSI_IDX aCsiIdx, uint32_t aLineCnt)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  aLineCnt &= SONY_WINPV_MASK;
  
  lTmp = aLineCnt&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_WINPVL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aLineCnt >> 8)&(SONY_WINPV_MASK >> 8);  
    if(SonyRegWrite(aCsiIdx, SONY_WINPVH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return aLineCnt;
} // SONY_DRV_CropPvSet()

//*****************************************************************************

int32_t SONY_DRV_CropPhGet(enum CSI_IDX aCsiIdx, uint32_t* apXoff)
{ 
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t *lpTmp = (uint8_t*)apXoff;
  
  if(SonyRegRead(aCsiIdx, SONY_WINPHL_ADDR, &lpTmp[0]) == SONY_DRV_SUCCESS)
  {
    if(SonyRegRead(aCsiIdx, SONY_WINPHH_ADDR, &lpTmp[1]) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if not read successfully
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
  
  *apXoff &= SONY_WINPV_MASK;
  
  return lRet;
} // SONY_DRV_CropPhGet()

//*****************************************************************************

int32_t SONY_DRV_CropPhSet(enum CSI_IDX aCsiIdx, uint32_t aXoff)
{  
  int32_t lRet = SONY_DRV_SUCCESS;
  uint8_t lTmp;
  
  lTmp = aXoff&0xff;
  if(SonyRegWrite(aCsiIdx, SONY_WINPHL_ADDR, lTmp) == SONY_DRV_SUCCESS)
  {
    lTmp = (aXoff >> 8)&(SONY_WINPH_MASK >> 8);  
    if(SonyRegWrite(aCsiIdx, SONY_WINPHH_ADDR, lTmp) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if read successfully
  else
  {
    lRet = SONY_DRV_FAILURE;
  } // else from if read successfully
    
  return lRet;
} // SONY_DRV_CropPhSet()

//*****************************************************************************

int32_t SONY_DRV_WinmodeGet(enum CSI_IDX aCsiIdx, uint8_t* apWinmode)
{  
  return SonyRegRead(aCsiIdx, SONY_WINMODE_ADDR, apWinmode); 
} // SONY_DRV_CropPhSet()

//*****************************************************************************

int32_t SONY_DRV_WinmodeSet(enum CSI_IDX aCsiIdx, uint8_t aWinmode)
{  
  return SonyRegWrite(aCsiIdx, SONY_WINMODE_ADDR, aWinmode); 
} // SONY_DRV_CropPhSet()

//*****************************************************************************

int32_t SONY_DRV_GeometrySet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  if(apGeom != NULL)
  { 
    uint8_t lWinmode = 0;
    
    if(apGeom->mWinMode == SONY_CROP)
    {
      // check values
      apGeom->mVmax     &= SONY_VMAX_MASK;
      apGeom->mWidth    &= 0xfffffffc; // force multiple of 4
      apGeom->mXoff     &= 0xfffffffc; // force multiple of 4
      
      if(apGeom->mOb > SONY_OB_MAX)
      {
        apGeom->mOb = SONY_OB_MAX;
      } 
      // don't enforce low OB limit to 6
      
      if(apGeom->mVmax < (SONY_WHEIGHT_MIN + apGeom->mOb + 13)) // why 13?
      {
        apGeom->mVmax = (SONY_WHEIGHT_MIN + apGeom->mOb + 13);
      }
      
      if(apGeom->mWidth < SONY_WWIDTH_MIN)
      {
        apGeom->mWidth = SONY_WWIDTH_MIN;
      }
      else if(apGeom->mWidth > SONY_WIDTH_MAX)
      {
        apGeom->mWidth = SONY_WIDTH_MAX;
      }
      
      if((apGeom->mWidth + apGeom->mXoff) > SONY_WIDTH_MAX)
      {
        apGeom->mXoff = SONY_WIDTH_MAX - apGeom->mWidth;
      }
      
      if(apGeom->mHeight < SONY_WHEIGHT_MIN)
      {
        apGeom->mWidth = SONY_WHEIGHT_MIN;
      }
      else if(apGeom->mHeight > SONY_HEIGHT_MAX)
      {
        apGeom->mHeight = SONY_HEIGHT_MAX;
      }
      
      if(apGeom->mHeight > (apGeom->mVmax - 16))
      {
        apGeom->mHeight = (apGeom->mVmax - 16);
      }
      
      if((apGeom->mHeight + apGeom->mYoff) > SONY_HEIGHT_MAX)
      {
        apGeom->mYoff = SONY_HEIGHT_MAX - apGeom->mHeight;
      }
      
      if((apGeom->mHeight + apGeom->mYoff) > apGeom->mVmax)
      {
        apGeom->mYoff = apGeom->mVmax - apGeom->mHeight - 9 - 16;
      }
      
      // compute HMAX to fit required fps
      apGeom->mHmax = (30*4500*1100/apGeom->mVmax/apGeom->mFps);
    
      // set values
      if(SONY_DRV_VmaxSet(aCsiIdx, apGeom->mVmax) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      if(SONY_DRV_HmaxSet(aCsiIdx, apGeom->mHmax) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      if(SONY_DRV_CropPhSet(aCsiIdx, apGeom->mXoff) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      if(SONY_DRV_CropPvSet(aCsiIdx, apGeom->mYoff) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      if(SONY_DRV_CropWhSet(aCsiIdx, apGeom->mWidth) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      if(SONY_DRV_CropWvSet(aCsiIdx, apGeom->mHeight) == SONY_DRV_FAILURE)
      {
        lRet = SONY_DRV_FAILURE;
      }
      
      lWinmode = SONY_WINMODE_CROP;
    }
    else if(apGeom->mWinMode == SONY_720P)
    {
      lWinmode = SONY_WINMODE_720P;
    }
    else
    {
      lWinmode = SONY_WINMODE_QVGA;
    }
    
    // set winmode and flip mode
    if(apGeom->mVerFlip)
    {
      lWinmode |= SONY_WINMODE_VR;
    }
    if(apGeom->mHorFlip)
    {
      lWinmode |= SONY_WINMODE_HR;
    }
    if(SONY_DRV_WinmodeSet(aCsiIdx, lWinmode) == SONY_DRV_FAILURE)
    {
      lRet = SONY_DRV_FAILURE;
    }
    
    // set optical black lines
    if(SONY_DRV_ObWvSet(aCsiIdx, apGeom->mOb) == SONY_DRV_FAILURE)
    {
      lRet = SONY_DRV_FAILURE;
    }
  } // if apGeom not NULL
  else
  {
    lRet = SONY_DRV_FAILURE;
  }
  
  return lRet;
} // SONY_DRV_GeometrySet()

//*****************************************************************************

int32_t SONY_DRV_GeometryGet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom)
{
  int32_t lRet = SONY_DRV_SUCCESS;
  if(apGeom != NULL)
  { 
    uint8_t lWinmode = 0;
  
    // *** Get values ***
    if(SONY_DRV_VmaxGet(aCsiIdx,   &(apGeom->mVmax)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_HmaxGet(aCsiIdx,   &(apGeom->mHmax)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_CropPhGet(aCsiIdx, &(apGeom->mXoff)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_CropPvGet(aCsiIdx, &(apGeom->mYoff)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_CropWhGet(aCsiIdx, &(apGeom->mWidth)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_CropWvGet(aCsiIdx, &(apGeom->mHeight)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    if(SONY_DRV_ObWvGet(aCsiIdx,   &(apGeom->mOb)) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    
    apGeom->mExpMode = SONY_SINGLE_EXP; // TODO: check for
    
    if(SONY_DRV_WinmodeGet(aCsiIdx, &lWinmode) != SONY_DRV_SUCCESS)
    {
      lRet = SONY_DRV_FAILURE;
    } // if failed
    
    // *** Eval win mode ***
    if(((lWinmode & SONY_WINMODE_CROP) == SONY_WINMODE_CROP))
    {
      apGeom->mWinMode = SONY_CROP;
    }
    else if(((lWinmode & SONY_WINMODE_720P) == SONY_WINMODE_720P))
    {
      apGeom->mWinMode = SONY_720P;
    }
    else if(((lWinmode & SONY_WINMODE_QVGA) == SONY_WINMODE_QVGA))
    {
      apGeom->mWinMode = SONY_QVGA;
    }
    
    // *** Eval flop mode ***
    apGeom->mVerFlip = (lWinmode & SONY_WINMODE_VR)? 1: 0;
    apGeom->mHorFlip = (lWinmode & SONY_WINMODE_HR)? 1: 0;
    
    // *** Compute aprox FPS ***
    apGeom->mFps     = (30*4500*1100)/(apGeom->mVmax * apGeom->mHmax);
  } // if apGeom not NULL
  
  return lRet;
} // SONY_DRV_GeometryGet()

//*****************************************************************************

#define CONV_ON
#define AGAIN_ON
#define DIFF_HISTORY_LENGTH 10

#ifdef STH_CTL
//#define PIXCNT (729*1280/4)
//#define PIXOE  (PIXCNT>>2)   // 25% overexposed pxiels
//#define HIST_START_IDX (127)
//#define HIST_STOP_IDX  (64)
//#define HIST_OE_LEV (HIST_START_IDX-4)

uint32_t SONY_DRV_ExpControl(enum CSI_IDX aCsiIdx, uint32_t *apHist)
{
  //find position in Histogram
  {
    uint16_t index=HIST_START_IDX;
    uint16_t index_stop = 0;
    uint32_t sum=0;
    uint32_t sum_lev=0;
    static uint8_t limgcnt=0;


    if (limgcnt == sExposureSkipFrames) {
      limgcnt++;
      return sExposure;
    }
    else limgcnt=0;
    
    while (index >= HIST_OE_LEV) {  // sum_lev is computed
      
      if (sum <  PIXOE) {
        sum+=apHist[index];
        index_stop=index;
      }
      sum_lev+=apHist[index--];
    }

    while ((index >= HIST_STOP_IDX) && // overexposed level is reached
           (sum < PIXOE)) {

      sum+=apHist[index--];
      index_stop=index;
    }

    index_stop-=HIST_STOP_IDX;
    if (index_stop<1) index_stop=1;
    // too many overexposed pixels
    if (index_stop >= (HIST_OE_LEV-HIST_STOP_IDX)) {
      if (sum_lev > 2*PIXOE) {         // 2x too muany
        sExposure=(sExposure*96)>>7;   // (x 3/4)
      }
      else if (sum_lev > ((3*PIXOE)>>1)) {  // 1,5x too many
        sExposure=(sExposure*112)>>7;   // (x 7/8)
      }
      else if (sum_lev > ((5*PIXOE)>>2)) {  // 1,25 too many
        sExposure=(sExposure*120)>>7;   // (x 15/16)
      }
      else if (sum_lev > ((9*PIXOE)>>3)) {  // 1,125 too many
        sExposure=(sExposure*124)>>7;   // (x 15/16)
      }
    }
    else {
      sExposure+=((sExposure<<10)*(HIST_OE_LEV-HIST_STOP_IDX-index_stop)/index_stop)>>13;
      //sExposure+=((sExposure<<1)*(HIST_OE_LEV-HIST_STOP_IDX-index_stop))>>2;
    }
  }

#ifdef AGAIN_ON
  // dimm down analgog gain (by one step = 6dB = 60 x 0.1dB)
  if (sGain) {
    if ((sExposure) < ((3*sExpRange)>>3)) {
      sGain--;
      sExposure<<=1;
      SONY_DRV_GainSet(aCsiIdx, sGain*60);
    }
  }
#endif

#ifdef CONV_ON
  // move up conversion gain
  if (!sConv && (sExposure > 6*32)) {
    sConv=1;
    SONY_DRV_ConvHighSet(aCsiIdx);
    sExposure>>=1;
  }
  
  // move down conversion gain
  if (sConv && (sExposure < 32)) {
    sConv=0;
    SONY_DRV_ConvLowSet(aCsiIdx);
    sExposure<<=1;
  }
#endif

#ifdef AGAIN_ON
  // move up analog gain
  if (sExposure > sExpRange) {
    if (sGain < 12) {
      sGain++;
      sExposure>>=1;
      SONY_DRV_GainSet(aCsiIdx, sGain*60);
    }
  }
#endif
  
  if (sExposure < 32) sExposure=32;
  if (sExposure >= sExpRange) sExposure=sExpRange-1;
  SONY_DRV_ExpLinesSet(aCsiIdx, sExpRange-sExposure-1);

  return sExposure;

}  
#endif

//*****************************************************************************
#ifdef TB_CTL

//#define FRM_MSR 1000
#define FRM_MSR 0
#define DIFF_NEXT_IDX(_idx) ((_idx + 1)%DIFF_HISTORY_LENGTH)


static float sDiffMomentum = 0.0;
static float sDiffHistory[DIFF_HISTORY_LENGTH] = {0.0};
static uint32_t sDiffHistoryIdx = 0;

#if (FRM_MSR > 0)
  static uint32_t sppExposures[FRM_MSR][6] = {0};
  static float    spMomentum[FRM_MSR]      = {0.0};
  static uint8_t  spConv[FRM_MSR]          = {0};
  static uint32_t sFrmMsrIdx = 0;
#endif

uint32_t SONY_DRV_ExpControl(enum CSI_IDX aCsiIdx, uint32_t *apHist)
{
  uint32_t lOeIdx[4]={63,124,188,255};
  uint32_t lUeIdx[4]={0,64,128,192};
  int64_t lOe  = 0;
  int64_t lUe = 0;
  float lDiff = 0.0;
  int32_t lExpStep = 0;
  int64_t lNewExp = 0;
  
  
  lOe = /*apHist[lOeIdx[SONY_HIST_GRIDX]] +*/ apHist[lOeIdx[SONY_HIST_GBIDX]];
  lUe = /*apHist[lUeIdx[SONY_HIST_GRIDX]] +*/ apHist[lUeIdx[SONY_HIST_GBIDX]];
  
  lDiff = (lOe - lUe) / (float)(PIXCNT);
  
  sDiffMomentum = sDiffMomentum - sDiffHistory[sDiffHistoryIdx] + lDiff;
  sDiffHistory[sDiffHistoryIdx] = lDiff;
  
  sDiffHistoryIdx = DIFF_NEXT_IDX(sDiffHistoryIdx);
  
  lExpStep = (lDiff/DIFF_HISTORY_LENGTH) * (sExpRange/2)*10;  
  
  lNewExp = (int64_t)sExposure + lExpStep;
  sExposure = (lNewExp < 0)?0:(uint32_t)lNewExp;

#ifdef CONV_ON
  // short exposure bright image
  if((sExposure > ((sExpRange * 6)/10)) &&
     (sDiffMomentum > 0) && (sConv == 1))
  {
    SONY_DRV_ConvLowSet(aCsiIdx);
    sExposure = sExposure / 2;
    sConv = 0;
  }
  // long exposure dark image
  else if((sExposure <= 0) && (sDiffMomentum < 0) && (sConv == 0))
  {
    SONY_DRV_ConvHighSet(aCsiIdx);
    sExposure = sExpRange>>1; //0x100;
    sConv = 1;
  }
#endif // ifdef CONV_ON 

#ifdef AGAIN_ON  
  if((sConv == 1) && (sExposure == 0) && (lDiff < 0.0))
  {
    sGain -= (lDiff/DIFF_HISTORY_LENGTH) * (SONY_GAIN_MAX / 2); 
  }
  else if(sGain > 0)
  {
    int32_t lGainStep = (int32_t)sGain - (lDiff/DIFF_HISTORY_LENGTH) * (SONY_GAIN_MAX / 2);
    sGain = (lGainStep < 0)?0:lGainStep;
    sExposure = 0;
  }
  SONY_DRV_GainSet(aCsiIdx, sGain);
#endif // ifdef AGAIN_ON 
    
  SONY_DRV_ExpLinesSet(aCsiIdx, sExposure);
  
#if (FRM_MSR > 0)  
  sppExposures[sFrmMsrIdx][1] = apHist[64];
  sppExposures[sFrmMsrIdx][2] = apHist[124];
  sppExposures[sFrmMsrIdx][3] = apHist[128];
  sppExposures[sFrmMsrIdx][4] = apHist[188];
  sppExposures[sFrmMsrIdx][5] = sGain;
  sppExposures[sFrmMsrIdx][0] = sExposure;
  spMomentum[sFrmMsrIdx] = sDiffMomentum;
  spConv[sFrmMsrIdx] = sConv;
  if(sFrmMsrIdx >= (FRM_MSR - 1))
  {
    while(1);
  }
  
  sFrmMsrIdx++;
#endif // #if (FRM_MSR > 0)  
  
  return sExposure;
} // SONY_DRV_ExpControl()
#endif
//*****************************************************************************

static uint32_t sCsiIdx = CSI_IDX_INVALID;
#ifdef __KERNEL__
int32_t SONY_DRV_I2cClientAdd(enum CSI_IDX aCsiIdx)
{
  struct i2c_adapter *lpI2cAdap = NULL;
  uint32_t lRet = SONY_DRV_SUCCESS;

  pr_info("Probing Sony I2c client on CSI %u.\n", aCsiIdx);
  lpI2cAdap = i2c_get_adapter(aCsiIdx);
  if(lpI2cAdap != NULL)
  {
    spSonyI2cCli[aCsiIdx] = i2c_new_device(lpI2cAdap, &spSonyI2cInfo[aCsiIdx]);
    i2c_put_adapter(lpI2cAdap);
    if(spSonyI2cCli[aCsiIdx] == NULL)
    {
      pr_err("Error: Sony i2c client is NULL.\n");
      lRet = SONY_DRV_FAILURE;
    }
    else
    { 
      if((aCsiIdx == CSI_IDX_0) || (spSonyI2cCli[CSI_IDX_0] == NULL))
      {
        if(0 != i2c_add_driver(&sSonyI2cDriver))
        {
          pr_err("Error: Sony i2c driver not added.\n");
          lRet = SONY_DRV_FAILURE;
        } // if add Sony i2c client driver failed
        else
        {
          pr_info("Sony I2c client added successfully.\n");
        } // else from if add Sony i2c client driver failed
      } // if driver not registerred already for CSI 0
    } // else from if no i2c client
  } // if I2C addapter not NULL
  else
  {
    pr_err("Error: I2C adapter 0 is NULL.\n");
    lRet = SONY_DRV_FAILURE;
  } // else from if I2C addapter not NULL
  
  return lRet;
} // SONY_DRV_I2cClientAdd()

//*****************************************************************************

static int SonyI2c_Probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
  uint8_t lModelId  = 0;
  int     lRet      = -1;
  
  lRet = I2c_RegRead16(client, SONY_MODEL_ID_REG_ADDR, &lModelId);
  //SonyRegRead(sCsiIdx, SONY_MODEL_ID_REG_ADDR, &lModelId);
  pr_info("Sony model ID 0x%x\n",lModelId, sCsiIdx);
  
  return lRet;
} // SonyI2c_Probe()

//*****************************************************************************

static int SonyI2c_Remove(struct i2c_client *client)
{
  pr_info("Sony I2c Remove.\n");
  return 0;
}  // SonyI2c_Remove()

//*****************************************************************************

static int32_t I2c_RegWrite16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t aVal)
{
  uint8_t lBuf[3] = {0};
  uint32_t lNumBytes = 0;
  uint32_t lRetVal = SONY_DRV_SUCCESS;

  lBuf[0] = aRegAddr >> 8;
  lBuf[1] = aRegAddr & 0xff;
  lBuf[2] = aVal;
  
  //msleep(3);
  lNumBytes = i2c_master_send(apI2cClient, lBuf, 3);
  
  if (lNumBytes < 0) 
  {
    pr_err("%s:write reg error:reg=%x,val=%x\n",
      __func__, aRegAddr, aVal);
    lRetVal = SONY_DRV_FAILURE;
  }
  //msleep(3);
  //pr_err("Written %d bytes.\n", lNumBytes);

  return lRetVal;
} // RegWrite16()

//*****************************************************************************

static int32_t I2c_RegRead16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t *apVal)
{
  uint32_t lRetVal = SONY_DRV_SUCCESS;
  uint8_t lBuf[2] = {0};

  lBuf[0] = aRegAddr >> 8;
  lBuf[1] = aRegAddr & 0xff;

  *apVal = 0;
  if (2 != i2c_master_send(apI2cClient, lBuf, 2)) 
  {
    pr_err("%s:write reg error:reg=%x\n",
        __func__, aRegAddr);
    lRetVal = SONY_DRV_FAILURE;
  }
  else if (1 != i2c_master_recv(apI2cClient, apVal, 1)) {
    pr_err("%s:read reg error:reg=%x,val=%x\n",
        __func__, aRegAddr, *apVal);
    lRetVal = SONY_DRV_FAILURE;
  }

  return lRetVal;
} //RegRead16()

//*****************************************************************************


#endif // #ifdef __KERNEL__

#ifndef __STANDALONE__
EXPORT_SYMBOL(SONY_DRV_ExpControl);
#endif // #ifndef __STANDALONE__

/* EOF */
