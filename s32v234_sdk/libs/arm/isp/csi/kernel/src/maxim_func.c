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
 * \file    maxim_func.c
 * \brief   Maxim SER/DES config functionality implementation.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    8-July-2015
 ****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "i2c.h"
#include "oal.h"
#include "csi.h"
#include "maxim_func.h"
#include "vdb_log.h"
#include "ov10640_config.h"
 
//****************************************************************************
// constsf
//****************************************************************************

#define OV10640_CHIP_ID_HIGH_BYTE 0x300A
#define OV10640_CHIP_ID_LOW_BYTE  0x300B

//****************************************************************************
// macros
//****************************************************************************

#define INIT_DELAY 20 // delay before i2c config is attempted
#define PRINT_ON      // commnet this out to disable printing in this module

#ifdef PRINT_ON
  #define PRINT printf 
#else 
  #define PRINT VDB_LOG_NOTE
#endif

#define msleep(_val) (sleep((double)(_val/1000.0)))

//****************************************************************************
// static global variables
//****************************************************************************
#ifdef OLD_EVB
static uint8_t sI2cBus[]  = {I2C0, I2C2};
#else
static uint8_t sI2cBus[]  = {I2C0, I2C1};
#endif // else from ifdef OLD_EVB

static uint8_t sMaxSerAddr[] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45};
static uint8_t sOv10640Addr[] = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65,0x30};

//****************************************************************************
// functions declarations
//****************************************************************************

static inline void DesRegWrite(uint8_t aRegAddr, uint8_t aVal);
static inline uint8_t DesRegRead(uint8_t aRegAddr, uint8_t *apVal);
static inline void SerRegWrite(uint8_t aIdx, uint8_t aRegAddr, uint8_t aVal);
static inline uint8_t SerRegRead(uint8_t aIdx, uint8_t aRegAddr, uint8_t *apVal);
static inline void Ov10640RegWrite(uint8_t aIdx, uint16_t aRegAddr, uint8_t aVal);
static inline uint8_t Ov10640RegRead(uint8_t aIdx, uint16_t aRegAddr, uint8_t *apVal);
static void DeserDump(uint8_t* apDump);
static void OvDump(uint32_t aIdx, uint8_t* apDump);

static void sleep(double aSec);

//****************************************************************************

int32_t MAXIM_DRV_Init(enum CSI_IDX aCsiIdx, uint32_t acCamCnt)
{ 
  uint8_t lVal = 0;
  uint8_t lVal2 = 0;
  uint8_t lVal3 = 0;
  int32_t lRet = MAXIM_SUCCESS;
  uint32_t i = 0;
  
  uint8_t lpDeserRegs[256] = {0};
  uint8_t lpOvRegs[5*256] = {0};
  
  if(acCamCnt > MAXIM_CAM_SLOTS)
  {
    acCamCnt = MAXIM_CAM_SLOTS;
  }
  
  // introduce i2c initialization delay if desired
  uint32_t lCnt = INIT_DELAY;
  for(;lCnt > 0; lCnt--)
  {
    PRINT("%u \n", lCnt);
    msleep(10000);
  }
  
  PRINT("Initialize the I2C\n"); 
  I2C_Init_Config(aCsiIdx,I2C_MAXIM_DES_ADDR);

     
  // *** A ***
  PRINT("=== Section A ===\n");
  msleep(20);
  DesRegRead(0x1e, &lVal);
  if(lVal != 0x40)
  {
    // deserializer not recognized
    PRINT("Deserializer not recognized 0x%x.\n", lVal);
    lRet = MAXIM_FAILURE;
    return lRet;
  }
  
  PRINT("Deserializer recognized.\n");
  //added
//  DesRegRead(0x34, &lVal);
//  PRINT("DesReg addr 0x34 val = %x \n", lVal);

  //DesRegWrite(0x0A, 0xF1); // enable only the first link control channel (FWD+REV)
  // Jason ADD - begin
  
  
  //Updated to current procedure 1-14-16 Blaine Ashley
  msleep(200);
  DesRegWrite(0x3F,0x4F);//BA 1-14-16
  msleep(200);//BA 1-14-16
  DesRegWrite(0x3B,0x1E);//BA 1-14-16
  msleep(200);//BA 1-14-16
  SerRegWrite(0,0x04, 0x43);//BA 1-14-16
  msleep(200);//BA 1-14-16
  SerRegWrite(0,0x08, 0x01);//BA 1-14-16
  msleep(200);//BA 1-14-16
  DesRegWrite(0x3B,0x19);//BA 1-14-16
  msleep(200); //BA 1-14-16


  PRINT("Please run initialization\n"); 
  lCnt = INIT_DELAY;	
  for(;lCnt > 0; lCnt--)
  {
    PRINT("%u \n", lCnt);
    msleep(10000);
  }
  PRINT("Cnt down finished\n");
  
  //change the SER I2C speed
  SerRegWrite(0,0x0D,0xAE); 
  msleep(2); //YW 1-20-16
  
  // SerRegWrite(0,0x08, 0x09);//BA 1-14-16
  // DesRegWrite(0x3B, 0x2B);//BA 1-14-16
  // DesRegWrite(0x3F, 0x62);//BA 1-14-16

  //SerRegWrite(0, 0x4, 0x43);  // Enable configuration link, use I2C link as local control channel
  //SerRegWrite(0, 0xD, 0xAE);  //TB edit: set 100kHz I2C clock on the serializer
  // Jason ADD - end
  
  DesRegWrite(0x0A, 0xF1); // enable only the first link control channel (FWD+REV)
  
  DesRegRead(0x15, &lVal);
  DesRegWrite(0x15, lVal&0xF7); // Disable CSI output Bits[3]=0b0
  DesRegRead(0x15, &lVal2);
  
  if(lVal2 != (lVal&0xF7))
  {
    PRINT("I2c check failed (disable CSI output).\n");
  }
  
  DesRegRead(0x12, &lVal); // debug only check
  DesRegRead(0x0A, &lVal); // debug only check
  
  DesRegRead(0x0, &lVal);
  
  PRINT("%u cameras attached.\n", acCamCnt);
  
  lVal3 = 0;
  for(i = 0; i < acCamCnt; i++)
  {
    lVal3 = (lVal3 << 1) + 1;
  } // for all cameras
  lVal3 += 0x80;
  DesRegWrite(0x0, (lVal&0x00)|lVal3); // Auto detect csi clock source, disable VSYNC gen (will come from camera), enable input links from used cameras
  
  DesRegRead(0x0, &lVal2);
  if(lVal2 != ((lVal&0x00)|lVal3))
  {
    PRINT("I2c check failed (autodetect csi clock).\n");
  }
  
  // set MIPI-CSI-2 data type
  DesRegRead(0x12, &lVal);
  DesRegWrite(0x12, (lVal&0xC0)|0x07);  // RAW12. single input mode, csidbl = 0
  DesRegRead(0x12, &lVal2);
  
  if(lVal2 != ((lVal&0xC0)|0x07))
  {
    PRINT("I2c check failed (RAW12).\n");
  }

  DesRegRead(0x01, &lVal);
  DesRegWrite(0x01, (lVal&0x01)|0x01); // enable Frame Sync
  DesRegRead(0x01, &lVal2);
  if(lVal2 != (lVal&0x01)|0x01)
  {
    PRINT("I2c check failed (Framce sync).\n");
  }  

  // *** B ***
  PRINT("=== Section B ===\n");
  lVal3 = 0;
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    msleep(10000);
    lVal3 = (lVal3 << 1) + 0x11;
    DesRegRead(0xA, &lVal);
    DesRegWrite(0xA, (lVal&0xF0)|lVal3); // Enable link 0 reverse control channel to serializer (sending)
    DesRegRead(0xA, &lVal2);
    if(lVal2 != ((lVal&0xF0)|lVal3))
    {
      PRINT("I2c check failed (Enable link 0).\n");
    }
    
    //Configuration of MAX9271 - serializer
    //SerRegWrite(0,0x08, 0x09);	//BA 1-14-16
    //SerRegWrite(0, 0x4, 0x43);  // Enable configuration link, use I2C link as local control channel //BA 1-14-16

   // SerRegWrite(0, 0xD, 0xAE);  //TB edit: set 100kHz I2C clock on the serializer

    msleep(30); // Wait 3 ms min
    
    SerRegRead(0, 0x4, &lVal2);
    if(lVal2 != 0x43)
    {
      PRINT("I2c check failed (serializer config link enable).\n");
    }

    SerRegWrite(0, 0x0, sMaxSerAddr[i] << 1);  // Change I2C slave ID of MAX9271 to 0x82
    msleep(20);  
    
    SerRegRead(i, 0x0, &lVal2);
    if(lVal2 != sMaxSerAddr[i] << 1)
    {
      PRINT("I2c check failed (serializer change I2C slave ID).\n");
    }

    SerRegWrite(i, 0x9, sOv10640Addr[i] << 1);  // Create unique camera ID = 0x62
    SerRegRead(i, 0x9, &lVal2);
    if(lVal2 != sOv10640Addr[i] << 1)
    {
      PRINT("I2c check failed (serializer create unique camera ID).\n");
    }
    SerRegWrite(i, 0xA, I2C_OV10640_CAM_ADDR << 1);  // Program original camera address = 0x60
    SerRegRead(i, 0xA, &lVal2);
    if(lVal2 != I2C_OV10640_CAM_ADDR << 1)
    {
      PRINT("I2c check failed (serializer program original camera address).\n");
    }
    SerRegWrite(i, 0xB, sMaxSerAddr[5] << 1);  // Create a MAX9271 broadcast I2C slave address 0x8A
    SerRegRead(i, 0xB, &lVal2);
    if(lVal2 != sMaxSerAddr[5] << 1)
    {
      PRINT("I2c check failed (serializer create broadcast addr).\n");
    }

    SerRegWrite(i, 0xC, sMaxSerAddr[i] << 1);  // Program original address of MAX9271 = 0x82
    SerRegRead(i, 0xC, &lVal2);
    if(lVal2 != sMaxSerAddr[i] << 1)
    {
      PRINT("I2c check failed (serializer original address).\n");
    }

    SerRegRead(i, 0x7, &lVal);

    PRINT("Register 0x07 of Serial[%u] contains 0x%x\n", i, lVal);
    SerRegWrite(i, 0x7, (lVal&0x6F)|0x04);  // Enable single mode, PCLK latched on Rising edge, Enable HS/VS encoding
	msleep(3);	//BA 1-14-16
    SerRegRead(i, 0x7, &lVal);
    

    PRINT("Register 0x07 of Serial[%u] contains 0x%x\n", i, lVal);
    
    msleep(300); // Wait 3 ms min

    SerRegRead(i, 0x7, &lVal2);
    if(lVal2 != (lVal|0x04))
    {
      PRINT("I2c check failed (serializer enable double mode) 0x%x.\n", lVal2);
    }

    lVal = 0xde;
    Ov10640RegRead(i, 0x300D, &lVal);
    PRINT("Camera revision is 0x%x\n", lVal);
  } // for all attached cameras

  ////////////////////////////////////////////////////////////////

  //DeserDump(lpDeserRegs);
  msleep(10000);
  lVal3 = 0;
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    
    uint8_t lRetVal = Ov10640RegRead(i, OV10640_CHIP_ID_HIGH_BYTE, &lVal3);
    if (lVal3 != 0xA6) {
      PRINT("camera ov10640_mipi was not found (high_byte) lRetVal %d id %x\n", lRetVal, lVal3);
      return MAXIM_FAILURE;
    }
    lRetVal = Ov10640RegRead(i, OV10640_CHIP_ID_LOW_BYTE,&lVal3);
    if (lVal3 != 0x40) {
      PRINT("camera ov10640_mipi was not found (low_byte)\n");
      return MAXIM_FAILURE;
    }
  } // for all attached cameras

  PRINT("All attached cameras ov10640_mipi were found\n");

  // *** F ***
  PRINT("=== Section F ===\n");
  DesRegRead(0x34, &lVal);
  DesRegWrite( 0x34, lVal&0x7F); // Disable Local Auto I2C ACK
  msleep(100);
  DesRegRead(0x34, &lVal2);
  if(lVal2 != (lVal&0x7F))
  {
    PRINT("I2c check failed (Disable local auto i2c ack) 0x%x.\n", lVal2);
  }

  // *** Camera reset ***
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    // reset the camera
    Ov10640RegWrite(i, 0x3013, 0x01);
    
    msleep(100);
     // make sure in standby
    Ov10640RegWrite(i, 0x3012, 0x00);
  } // for all attached cameras
  
  msleep(10000);
  // *** Camera config ***
  {
    uint8_t *lpCamConfig = Ov10640_Table3;
    uint32_t lConfigSize = sizeof(Ov10640_Table3);
    uint32_t j = 0;
    for(j = 0; j < lConfigSize; j += 3) // Configure omnivision cameras
    {
      uint16_t lAddr = ((uint16_t)lpCamConfig[j] << 8) + lpCamConfig[j + 1];
      //for (i = 1; i < (acCamCnt + 1); i++)//BA 1-14-16
      //{        //BA 1-14-16
        Ov10640RegWrite(6, lAddr, lpCamConfig[j+2]);
        msleep(20);
      //} // for all attached cameras//BA 1-14-16
    } // for all configurations
    PRINT("Configured camera registers.\n");
  
    for(j = 0; j < sizeof(Ov10640_FsinTable); j += 3)  //   Enable External Frame Syncs 
    {
      uint16_t lAddr = ((uint16_t)Ov10640_FsinTable[j] << 8) + Ov10640_FsinTable[j + 1];
      //for (i = 1; i < (acCamCnt + 1); i++)//BA 1-14-16
      //{        //BA 1-14-16
        Ov10640RegWrite(6, lAddr, Ov10640_FsinTable[j+2]);
        msleep(20);
      //} // for all configurations//BA 1-14-16
    } // for all attached cameras
  } // Camera config
  
  //OvDump(1, lpOvRegs);
  msleep(10000);  
  PRINT("Enabled external frame syncs.\n");
  DesRegRead(0x34, &lVal);
  DesRegWrite( 0x34, lVal|0x80); // Enable Local Auto I2C ACK
  msleep(100);
  DesRegRead(0x34, &lVal2);  
  if(lVal2 != (lVal|0x80))
  {
    PRINT("I2c check failed (Enable local auto i2c ack) 0x%x.\n", lVal2);
  }

  PRINT("=== Section H ===\n");
  lVal = 0;
  msleep(100);
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    SerRegRead(i, 0x04, &lVal);
    SerRegWrite(i, 0x04, (lVal&0xBF)|0x80); // try to enable serial links
    msleep(100);
    SerRegRead(i, 0x04, &lVal2);
    if(lVal2 != ((lVal&0xBF)|0x80))
    {
      PRINT("I2c config error (deserializer try to enable serial links [%u]): 0x%x\n", i, lVal2);
    }
    PRINT("Ser%u done.\n", i);
  } // for all attached cameras
  
  msleep(10000);  // Wait 10 ms min
  
  
  DesRegRead(0x12, &lVal);
  DesRegWrite(0x12, (lVal&0x4F)|0x40); // Enable CSI data lanes D0, D1 , BIT[7:6]=01 // DBL OFF, CSI_DBL OFF
  
  msleep(100);
  DesRegRead(0x12, &lVal2);
  if(lVal2 != ((lVal&0x4F)|0x40))
  {
    PRINT("I2c config error (deserializer enable CSI lanes): 0x%x\n", lVal2);
  }
  PRINT("== Deserial register 0x12: 0x%x\n", lVal2);
  
  DesRegRead(0x0C, &lVal2);
  PRINT("== Deserial register 0x0c: 0x%x\n", lVal2);
  PRINT("Dump deserializer:\n");
  
  MAXIM_DRV_CsiDisable(aCsiIdx);
  
  //DeserDump(lpDeserRegs);

  return lRet;
} // MAXIM_Init()

//*****************************************************************************

void GmslLinkSetup(uint32_t aLinkIdx)
{
  if(aLinkIdx < 4)
  {
    uint8_t lVal = 0;
    DesRegWrite(0x0A, (0xF0|(1<<aLinkIdx)));        // Enable Link Idx Reverse Channel
    aLinkIdx++;
    SerRegWrite(0,0x04, 0x43);                      // Optional - Enable configuration link
    msleep(5);
    SerRegRead(0, 0x04, &lVal);
    if(lVal != 0x43)
    {
      lVal = 0;
    }
    // TB
    //SerRegWrite(0,0x08, 0x01);                      // Enable high threshold for reverse channel input buffer.  This increases immunity to power supply noise when the coaxial link is used for power as well as signal.
    //msleep(2);
    SerRegWrite(0, 0x00, sMaxSerAddr[aLinkIdx] << 1/*0x80 + aLinkIdx*2*/);        // Change serializer slave address
    msleep(5);
    SerRegRead(aLinkIdx, 0x00, &lVal);
    if(lVal != sMaxSerAddr[aLinkIdx] << 1/*0x80 + aLinkIdx*2*/)
    {
      lVal = 0;
    }
    //SerRegWrite(aLinkIdx, 0x07, 0x84);              // Enable DBL; Set Edge Select 1=Rise / 0=Fall; Enable HS/VS encoding
    SerRegWrite(aLinkIdx, 0x07, 0x04);              // Disable DBL; Low data rate mode, BWS = 0, Set Edge Select 0=Fall; Enable HS/VS encoding
    msleep(5);
    SerRegRead(aLinkIdx, 0x07, &lVal);
    if(lVal != 0x04)
    {
      lVal = 0;
    }
    SerRegWrite(aLinkIdx, 0x09, sOv10640Addr[aLinkIdx] << 1/*0x60 + aLinkIdx*2*/); // Unique Link Idx image sensor slave address
    msleep(5);
    SerRegRead(aLinkIdx, 0x09, &lVal);
    if(lVal != sOv10640Addr[aLinkIdx] << 1/*0x60 + aLinkIdx*2*/)
    {
      lVal = 0;
    }
    SerRegWrite(aLinkIdx, 0x0A, I2C_OV10640_CAM_ADDR << 1);              // Link Idx image sensor slave address
    msleep(5);
    SerRegRead(aLinkIdx, 0x0A, &lVal);
    if(lVal != I2C_OV10640_CAM_ADDR << 1)
    {
      lVal = 0;
    }
    SerRegWrite(aLinkIdx, 0x0B, sMaxSerAddr[5] << 1/*0x8A*/);              // Serializer broadcast address  
    msleep(5);
    SerRegRead(aLinkIdx, 0x0B, &lVal);
    if(lVal != sMaxSerAddr[5] << 1/*0x8A*/)
    {
      lVal = 0;
    }
    SerRegWrite(aLinkIdx, 0x0C, sMaxSerAddr[aLinkIdx] << 1/*0x8A*/);              // Serializer broadcast address  
    msleep(5);
    SerRegRead(aLinkIdx, 0x0C, &lVal);
    if(lVal != sMaxSerAddr[aLinkIdx] << 1/*0x8A*/)
    {
      lVal = 0;
    }
  } // if link index in bounds
} // GmslLinkSetup(uint32_t aLinkIdx)

//*****************************************************************************

int32_t MAXIM_DRV_Init2(uint32_t acCamCnt)
{ 
  uint8_t lVal = 0;
  uint8_t lVal2 = 0;
  uint8_t lVal3 = 0;
  int32_t lRet = MAXIM_SUCCESS;
  uint32_t i = 0;
  uint32_t lConfigChannels = 0;
  
  uint8_t lpDeserRegs[256] = {0};
  uint8_t lpOvRegs[5*256] = {0};
  
  if(acCamCnt > MAXIM_CAM_SLOTS)
  {
    acCamCnt = MAXIM_CAM_SLOTS;
  }
  
  I2C_Init_Config(I2C0,I2C_MAXIM_DES_ADDR << 1);
  
  // *** Check Deserializer connected ***
  DesRegRead(0x1e, &lVal);
  if(lVal != 0x40)
  {
    // deserializer not recognized
    PRINT("Deserializer not recognized 0x%x.\n", lVal);
    lRet = MAXIM_FAILURE;
    return lRet;
  }
  PRINT("Deserializer recognized.\n");
  
  // *** Reverse channel setup ***
#if 0
  DesRegWrite(0x3F, 0x4F);  // Enable Custom Reverse Channel & First Pulse Length
  msleep(2);  
  DesRegWrite(0x3B, 0x1E);  // First pulse length rise time changed from 300ns to 200ns
  msleep(2); 
  SerRegWrite(0,0x04, 0x43); // Optional - Enable configuration link
  msleep(5);
  SerRegWrite(0,0x08, 0x01); // Enable high threshold for reverse channel input buffer.  This increases immunity to power supply noise when the coaxial link is used for power as well as signal.
  msleep(2);
  DesRegWrite(0x3B, 0x19);  // Increase reverse amplitude from 100mV to 170mV.  This compensates for the higher threshold of step 5.
  msleep(2);
#else
  SerRegWrite(0,0x08, 0x09); // Enable high threshold for reverse channel input buffer.  This increases immunity to power supply noise when the coaxial link is used for power as well as signal.
  DesRegWrite(0x3B, 0x2B);
  DesRegWrite(0x3F, 0x62);
  
  SerRegWrite(0, 0x4, 0x43);  // Enable configuration link, use I2C link as local control channel
#endif 
  
  // *** MAX9286 Initial Setup ***
  DesRegWrite(0x15, 0x03); // Disable CSI output
  //DesRegWrite(0x12, 0x75); // Enable CSI-2 Lanes D0, D1; Enable CSI-2 DBL; Enable GMSL DBL for RAWx2; Enable RAW 8  data type
  DesRegWrite(0x12, 0x47); // Enable CSI-2 Lanes D0, D1; disable CSI-2 DBL; disable GMSL DBL for RAWx2; Enable RAW 12RAW  data type
  DesRegWrite(0x01, 0x01); // Enable frame sync; Enable semi-auto frame sync. Use semi-auto for row reset on frame sync sensors; Use auto for row/column reset on frame sync sensors
  DesRegWrite(0x00, 0xEF); // Force master link or select auto. First GMSL link to lock will be master link with auto select; Disable internal VSYNC generation. Use free running VSYNC from image sensor;Enable input links from all cameras 

  // *** GMSL Link Setup ***
  for(i = 0; i < acCamCnt; i++)
  {
    GmslLinkSetup(i);
    lConfigChannels = (lConfigChannels << 1) + 0x1;
  } // for all possible links
  lConfigChannels += 0xF0;
  
  DesRegWrite(0x0A, lConfigChannels); // Enable all I2C reverse channels
  
  // check the cameras are attached
  lVal3 = 0;
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    
    uint8_t lRetVal = Ov10640RegRead(i, OV10640_CHIP_ID_HIGH_BYTE, &lVal3);
    if (lVal3 != 0xA6) {
      PRINT("camera ov10640_mipi was not found (high_byte) lRetVal %d id %x\n", lRetVal, lVal3);
      return MAXIM_FAILURE;
    }
    lRetVal = Ov10640RegRead(i, OV10640_CHIP_ID_LOW_BYTE,&lVal3);
    if (lVal3 != 0x40) {
      PRINT("camera ov10640_mipi was not found (low_byte)\n");
      return MAXIM_FAILURE;
    }
  } // for all attached cameras
  
  // *** image sensor initialization ***
  DesRegWrite(0x34, 0x36); // Disable auto acknowledge
  
  // camera reset
  for (i = 1; i < (acCamCnt + 1); i++)
  {
    // reset the camera
    Ov10640RegWrite(i, 0x3013, 0x01);
    
    msleep(100);
     // make sure in standby
    Ov10640RegWrite(i, 0x3012, 0x00);
  } // for all attached cameras
  
  // camera config
  {
    uint8_t *lpCamConfig = Ov10640_Table3;
    uint32_t lConfigSize = sizeof(Ov10640_Table3);
    uint32_t j = 0;
    for(j = 0; j < lConfigSize; j += 3) // Configure omnivision cameras
    {
      uint16_t lAddr = ((uint16_t)lpCamConfig[j] << 8) + lpCamConfig[j + 1];
      for (i = 1; i < (acCamCnt + 1); i++)
      {        
        Ov10640RegWrite(i, lAddr, lpCamConfig[j+2]);
      } // for all attached cameras
    } // for all configurations
    PRINT("Configured camera registers.\n");
  
    for(j = 0; j < sizeof(Ov10640_FsinTable); j += 3)  //   Enable External Frame Syncs 
    {
      uint16_t lAddr = ((uint16_t)Ov10640_FsinTable[j] << 8) + Ov10640_FsinTable[j + 1];
      for (i = 1; i < (acCamCnt + 1); i++)
      {        
        Ov10640RegWrite(i, lAddr, Ov10640_FsinTable[j+2]);
      } // for all configurations
    } // for all attached cameras
  } // Camera config
  
  DesRegWrite(0x34, 0xB6); // Enable auto ack -optional-
  for(i = 1; i < (acCamCnt + 1); i++)
  {
    SerRegRead(i,0x15, &lVal);
    if((lVal & 0x1) == 0)
    {
      break; //Valid PCLKIN not detected
    } // if no valid PCLKIN
  } // for all cameras read status
  
  // *** Enable GMSL & CSI-2 ***
  //SerRegWrite(4,0x06, 0xAx); // Set all devices Preemphasis settings (if needed)
  msleep(5);
  //DesRegWrite(0x32, 0xXX); // Set Deserializer Equalizer settings (if needed)
  //DesRegWrite(0x33, 0xXX); // Set Deserializer Equalizer settings (if needed)
  //DesRegWrite(0x1B, 0x0F); // Enable EQs (if needed)
  msleep(5);
  SerRegWrite(5,0x04, 0x83); // Enable all serial links
  msleep(5);
  do
  {
    DesRegRead(0x31, &lVal); // Poll frame synchronization bit
  }while((lVal&0x40) == 0);
  
  //DesRegWrite(0x15, 0x0B);   // Enable CSI-2 output
  
  return lRet;
} // MAXIM_Init2()

//****************************************************************************

void MAXIM_DRV_CsiEnable(enum CSI_IDX aCsiIdx)
{
  uint8_t lVal = 0;
  uint8_t lVal2 = 0;
  
  DesRegRead(0x15, &lVal);
  DesRegWrite( 0x15, lVal|0x08); // Enable CSI output , BIT[3] = 1
  msleep(100);
  DesRegRead(0x15, &lVal2);
  if(lVal2 != (lVal|0x08))
  {
    PRINT("I2c config error (deserializer enable CSI output):  0x%x\n", (uint32_t)lVal2);
  }
} // MAXIM_CsiEnable()

//****************************************************************************

void MAXIM_DRV_CsiDisable(enum CSI_IDX aCsiIdx)
{
  uint8_t lVal = 0;
  
  DesRegRead(0x15, &lVal);
  DesRegWrite( 0x15, lVal&0xF7); // Disable CSI output , BIT[3] = 1
  msleep(100);
} // MAXIM_CsiDisable()

//****************************************************************************

static inline void DesRegWrite(uint8_t aRegAddr, uint8_t aVal)
{
  I2C8_DevTx(I2C0, I2C_MAXIM_DES_ADDR, aRegAddr, aVal);
} // DesRegWrite()

//*****************************************************************************

static inline uint8_t DesRegRead(uint8_t aRegAddr, uint8_t *apVal)
{
  *apVal = I2C8_DevRx(I2C0, I2C_MAXIM_DES_ADDR, aRegAddr);
  return *apVal;
} //DesRegRead()

//*****************************************************************************

static inline void SerRegWrite(uint8_t aIdx, uint8_t aRegAddr, uint8_t aVal)
{
  I2C8_DevTx(I2C0, sMaxSerAddr[aIdx], aRegAddr, aVal);
} // SerRegWrite()

//*****************************************************************************

static inline uint8_t SerRegRead(uint8_t aIdx, uint8_t aRegAddr, uint8_t *apVal)
{
  *apVal = I2C8_DevRx(I2C0, sMaxSerAddr[aIdx], aRegAddr);
  return *apVal;
} //SerRegRead()

//*****************************************************************************

static inline void Ov10640RegWrite(uint8_t aIdx, uint16_t aRegAddr, uint8_t aVal)
{
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;

  I2C_DevTx(I2C0, sOv10640Addr[aIdx], lpAddr[1], lpAddr[0], aVal);
} // Ov10640RegWrite()

//*****************************************************************************

static inline uint8_t Ov10640RegRead(uint8_t aIdx, uint16_t aRegAddr, uint8_t *apVal)
{
  uint8_t* lpAddr = (uint8_t*) &aRegAddr;

  *apVal = I2C_DevRx(I2C0, sOv10640Addr[aIdx], lpAddr[1], lpAddr[0]);
  return *apVal;
} //Ov10640RegRead()

//*****************************************************************************

static void sleep(double aSec)
{
  volatile uint64_t i = 0;
  uint64_t stop = aSec * 1000 * 1000 * 2;
  while(i < stop)
  {
    i++;
  }
  
  stop = 0;
} //sleep()

//*****************************************************************************

static void DeserDump(uint8_t* apDump)
{
  uint32_t i = 0;
  uint8_t lVal = 0;

  for( i = 0x4e; i < (0x4e + 16); i++)
  {
    DesRegRead(i, &lVal);
    apDump[i] = lVal;
    sleep(3);
  }
} // DeserDump()

//*****************************************************************************

static void OvDump(uint32_t aIdx, uint8_t* apDump)
{
  uint32_t i = 0;
  uint8_t lVal = 0;

  for( i = 0x0; i < 0x49D; i++)
  {
    Ov10640RegRead(aIdx, 0x3000+i, &lVal);
    apDump[i] = lVal;
    sleep(3);
    lVal = 0;
  }
} // OvDump()

//*****************************************************************************
