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
 * \brief   Omnivision 10640 MIPI/CSI camera functionality.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    14-December-2015
 ****************************************************************************/
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
  #include "config.h"
  #include "i2c.h"
  #include "oal.h"
  #include "seq_sa_kernel_api.h"
#endif // #if !defined(__STANDALONE__)

#include "s32vs234.h"
#include "csi.h"
#include "csi_types.h"
#include "ov10640_config_mipi.h"
#include "ov10640_func.h"
//#include "ov10640_types.h"
#include "vdb_log.h"
 
//****************************************************************************
// consts
//****************************************************************************

#define OV10640_DRV_SUCCESS CSI_DRV_SUCCESS
#define OV10640_DRV_FAILURE CSI_DRV_FAILURE
#define OV10640_MODEL_ID_REG_ADDR 0x3399

//****************************************************************************
// macros
//****************************************************************************
#ifdef __STANDALONE__
#define msleep(_val) (sleep((double)(_val/1000.0)))
#endif

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
  
#ifdef __KERNEL__

static int Ov10640I2c_Probe(struct i2c_client *client,
                          const struct i2c_device_id *id);
static int Ov10640I2c_Remove(struct i2c_client *client);
static int32_t I2c_RegWrite16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t aVal);
static int32_t I2c_RegRead16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t *apVal);

// *** Ov10640 I2C ***
struct i2c_client *spOv10640I2cCli[2] = {NULL};

static struct i2c_board_info spOv10640I2cInfo[1] = {
  {
    I2C_BOARD_INFO("ov10640", I2C_OV10640_CAM_ADDR)
  },
};

static const struct i2c_device_id sOv10640Id[] = {
  {"ov10640", 0},
  {},
};

static struct i2c_driver sOv10640I2cDriver = {
  .driver = {
      .owner = THIS_MODULE,
      .name  = "ov10640",
      },
  .probe  = Ov10640I2c_Probe,
  .remove = Ov10640I2c_Remove,
  .id_table = sOv10640Id,
};

#endif // #ifdef __KERNEL__

//****************************************************************************
// functions declarations
//****************************************************************************

static int32_t Siul2Init(enum CSI_IDX aIdx);
int32_t OV10640_DRV_I2cClientAdd(void);
static int32_t Ov10640RegWrite(enum CSI_IDX aCsiIdx, 
                                uint16_t aRegAddr, 
                                uint8_t aVal);
static int32_t Ov10640RegRead(enum CSI_IDX aCsiIdx,
                                  uint16_t aRegAddr, 
                                  uint8_t *apVal);

//****************************************************************************

int32_t OV10640_DRV_Setup()
{ 
  int32_t lRet = OV10640_DRV_SUCCESS;
#ifndef __STANDALONE__
  // initialize pin config
  if(Siul2Init(CSI_IDX_0) != OV10640_DRV_SUCCESS)
  {
    lRet = OV10640_DRV_FAILURE;
    goto i2c_init_failed;
  } // if driver data init failed                 
  
  msleep(100);
  
  OV10640_DRV_I2cClientAdd();
#endif
  
  i2c_init_failed:
  
  return lRet;
} // OV10640_DRV_Setup()

//****************************************************************************

static int32_t Siul2Init(enum CSI_IDX aCsiIdx)
{
  int32_t lRet = OV10640_DRV_SUCCESS;
  CSI_Siul2Regs_t *lpSiul2Regs = NULL;
    
  lpSiul2Regs = (CSI_Siul2Regs_t*) ioremap((uintptr_t)&SIUL2, sizeof(CSI_Siul2Regs_t));
  if(lpSiul2Regs == NULL)
  {
    VDB_LOG_ERROR("Failed to map SUIL2 registers.\n");
    lRet = OV10640_DRV_FAILURE;
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
        lRet = OV10640_DRV_FAILURE;
      } // default
      break;      
    } // switch(aIdx)
    
    // *** turn on Ov10640 cam ***
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

void OV10640_DRV_RegConfig(enum CSI_IDX aCsiIdx)
{ 
#ifdef __STANDALONE__ 
  uint32_t i = 0;
  uint8_t tmp = 0;
  uint8_t *lpOvTable = Ov10640_MIPI_basic_configuration_2MIPI_lane_12bcombined;
  
  I2C_Init_Config(sI2cBus[aCsiIdx],I2C_OV10640_CAM_ADDR << 1);
  
  OV10640_DRV_CsiDisable(aCsiIdx); // Camera in the standby mode
 
  // *** basic configuration ***
  for(i=0;i<sizeof(Ov10640_MIPI_basic_configuration_2MIPI_lane_12bcombined);i=i+3)
  {
    Ov10640RegWrite(aCsiIdx, (lpOvTable[i]<<8)|lpOvTable[i+1], lpOvTable[i+2]);
  }
 
  // *** long exposure only ***
/*   for(i=0;i<sizeof(OV10640_change_to_long_exposure);i=i+3)
  {
    Ov10640RegWrite(aCsiIdx, (OV10640_change_to_long_exposure[i]<<8)|OV10640_change_to_long_exposure[i+1], OV10640_change_to_long_exposure[i+2]);
  } 
  
  // *** Auto exposure control on ***
   for(i=0;i<sizeof(Ov10640_AEC_ON);i=i+3)
  {
    Ov10640RegWrite(aCsiIdx, (Ov10640_AEC_ON[i]<<8)|Ov10640_AEC_ON[i+1], Ov10640_AEC_ON[i+2]);
  }   
*/
  // *** 3x12 enable ***
  for(i=0;i<sizeof(OV10640_3x12);i=i+3)
  {
    Ov10640RegWrite(aCsiIdx, (OV10640_3x12[i]<<8)|OV10640_3x12[i+1], OV10640_3x12[i+2]);
  }

#else // ifdef __STANDALONE__

#endif // else from ifdef __STANDALONE__
} // CSI_CamRegConfig()

//****************************************************************************

void OV10640_DRV_CsiEnable(enum CSI_IDX aCsiIdx)
{
  uint8_t lVal = 0;
  // bring camera out of standby
  Ov10640RegWrite(aCsiIdx, 0x3012, 1);
  while(lVal != 1)
  {
    Ov10640RegRead(aCsiIdx, 0x3012, &lVal);
  }
} // MAXIM_CsiEnable()

//****************************************************************************

void OV10640_DRV_CsiDisable(enum CSI_IDX aCsiIdx)
{
  uint8_t lVal = 1;
  // bring camera to standby
  Ov10640RegWrite(aCsiIdx, 0x3012, 0); 
  while(lVal != 0)
  {
    Ov10640RegRead(aCsiIdx, 0x3012, &lVal);
  }
} // MAXIM_CsiDisable()

//*****************************************************************************

static int32_t Ov10640RegWrite(enum CSI_IDX aCsiIdx, uint16_t aRegAddr, uint8_t aVal)
{
  int32_t lRet = OV10640_DRV_SUCCESS;
#ifdef __STANDALONE__   
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;
  
  I2C_DevTx(sI2cBus[aCsiIdx], I2C_OV10640_CAM_ADDR, lpAddr[1], lpAddr[0], aVal);
#else
  lRet = I2c_RegWrite16(spOv10640I2cCli[aCsiIdx], aRegAddr, aVal);
#endif // #ifdef __STANDALONE__ 
  return lRet;
} // Ov10640RegWrite()

//*****************************************************************************

static int32_t Ov10640RegRead(enum CSI_IDX aCsiIdx, uint16_t aRegAddr, uint8_t *apVal)
{
  int32_t lRet = OV10640_DRV_SUCCESS;
#ifdef __STANDALONE__   
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;
  *apVal = I2C_DevRx(sI2cBus[aCsiIdx], I2C_OV10640_CAM_ADDR, lpAddr[1], lpAddr[0]);
#else
  lRet = I2c_RegRead16(spOv10640I2cCli[aCsiIdx], aRegAddr, apVal);
#endif // #ifdef __STANDALONE__ 
  return lRet;
} //Ov10640RegRead()

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

#ifdef __KERNEL__
int32_t OV10640_DRV_I2cClientAdd()
{
  struct i2c_adapter *lpI2cAdap = NULL;
  uint32_t lRet = OV10640_DRV_SUCCESS;

  lpI2cAdap = i2c_get_adapter(0);
  if(lpI2cAdap != NULL)
  {
    spOv10640I2cCli[0] = i2c_new_device(lpI2cAdap, &spOv10640I2cInfo[0]);
    i2c_put_adapter(lpI2cAdap);
    if(spOv10640I2cCli[0] == NULL)
    {
      pr_err("Error: Ov10640 i2c client is NULL.\n");
      lRet = OV10640_DRV_FAILURE;
    }
    else
    { 
      if(0 != i2c_add_driver(&sOv10640I2cDriver))
      {
        pr_err("Error: Ov10640 i2c driver not added.\n");
        lRet = OV10640_DRV_FAILURE;
      } // if add Ov10640 i2c client driver failed
      else
      {
        pr_info("Ov10640 I2c client added successfully.\n");
      } // else from if add Ov10640 i2c client driver failed
    } // else from if no i2c client
  } // if I2C addapter not NULL
  else
  {
    pr_err("Error: I2C adapter 0 is NULL.\n");
    lRet = OV10640_DRV_FAILURE;
  } // else from if I2C addapter not NULL
  
  return lRet;
} // OV10640_DRV_I2cClientAdd()

//*****************************************************************************

static int Ov10640I2c_Probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
  uint8_t lModelId = 0;
  Ov10640RegRead(CSI_IDX_0, OV10640_MODEL_ID_REG_ADDR, &lModelId);
  pr_info("Ov10640 model ID 0x%x\n",lModelId);
  Ov10640RegRead(CSI_IDX_0, OV10640_MODEL_ID_REG_ADDR, &lModelId);
  return 0;
}

//*****************************************************************************

static int Ov10640I2c_Remove(struct i2c_client *client)
{
  pr_info("Ov10640 I2c Remove.\n");
  return 0;
}

//*****************************************************************************

static int32_t I2c_RegWrite16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t aVal)
{
  uint8_t lBuf[3] = {0};
  uint32_t lNumBytes = 0;
  uint32_t lRetVal = OV10640_DRV_SUCCESS;

  lBuf[0] = aRegAddr >> 8;
  lBuf[1] = aRegAddr & 0xff;
  lBuf[2] = aVal;
  
  //msleep(3);
  lNumBytes = i2c_master_send(apI2cClient, lBuf, 3);
  
  if (lNumBytes < 0) 
  {
    pr_err("%s:write reg error:reg=%x,val=%x\n",
      __func__, aRegAddr, aVal);
    lRetVal = OV10640_DRV_FAILURE;
  }
  //msleep(3);
  //pr_err("Written %d bytes.\n", lNumBytes);

  return lRetVal;
} // RegWrite16()

//*****************************************************************************

static int32_t I2c_RegRead16(struct i2c_client *apI2cClient, uint16_t aRegAddr, uint8_t *apVal)
{
  uint32_t lRetVal = OV10640_DRV_SUCCESS;
  uint8_t lBuf[2] = {0};

  lBuf[0] = aRegAddr >> 8;
  lBuf[1] = aRegAddr & 0xff;

  *apVal = 0;
  if (2 != i2c_master_send(apI2cClient, lBuf, 2)) 
  {
    pr_err("%s:write reg error:reg=%x\n",
        __func__, aRegAddr);
    lRetVal = OV10640_DRV_FAILURE;
  }
  else if (1 != i2c_master_recv(apI2cClient, apVal, 1)) {
    pr_err("%s:read reg error:reg=%x,val=%x\n",
        __func__, aRegAddr, *apVal);
    lRetVal = OV10640_DRV_FAILURE;
  }

  return lRetVal;
} //RegRead16()

//*****************************************************************************

#endif // #ifdef __KERNEL__

/* EOF */
