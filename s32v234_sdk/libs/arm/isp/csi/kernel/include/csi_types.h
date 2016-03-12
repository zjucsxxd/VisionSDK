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
* \file     csi_types.h
* \brief    types declarations for MIPI CSI receiver driver
* \author   Tomas Babinec
* \version  0.1
* \date     29.5.2015
* \note
****************************************************************************/
#ifndef CSI_TYPES_H
#define CSI_TYPES_H

#ifdef __cplusplus 
extern "C" { 
#endif

#if !defined(__KERNEL__) && !defined(__STANDALONE__)
#include <stdint.h>

#endif // if !defined(__KERNEL__) && !defined(__STANDALONE__)

//*****************************************************************************
// const
//***************************************************************************** 
  
#define CSI_CHNL_CNT 4  
  
//*****************************************************************************
// macros
//*****************************************************************************  

#define CSI_IDX_GET(_aCsiIdKey)((uint8_t)_aCsiIdKey.mId.mCsi)
#define CSI_IDX_SET(_aCsiIdKey, _aIdx)(_aCsiIdKey.mKey |= (0xffffff00 + _aIdx))
  
#define CSI_IDX2VCID(_aCsiIdx, _aVcIdx)((uint16_t)(1 << (_aVcIdx + 8*_aCsiIdx)))  
  
#define CSI_VC_IDX_USED(_aCsiIdKey, _aVcIdx)\
                       ((_aCsiIdKey.mId.mVc & \
                        CSI_IDX2VCID(_aCsiIdKey.mId.mCsi,_aVcIdx)) \
                        > 0 ? true : false)
                      
#define CSI_VC_IDX_ADD(_aCsiIdKey, _aVcIdx)\
                        (_aCsiIdKey.mId.mVc |= (uint16_t)(1 << \
                        (_aVcIdx + 8*_aCsiIdKey.mId.mCsi)))
#define CSI_VC_IDX_REM(_aCsiIdKey, _aVcIdx)\
                      (_aCsiIdKey.mId.mVc &= (~((uint16_t)_aVcIdx)))                       
  
//*****************************************************************************
// types
//*****************************************************************************  
  
///< new name for CSI register structure
typedef volatile struct CSI_tag CSI_Regs_t;  
  
///< new name for SIUL2 register structure
typedef volatile struct SIUL2_tag CSI_Siul2Regs_t;

//*****************************************************************************

enum CSI_IDX
{
  CSI_IDX_0 = 0,
  CSI_IDX_1 = 1,
  CSI_IDX_INVALID = 2,
}; // CSI index definition  

//*****************************************************************************

enum CSI_VCID
{
  CSI_VCID_00 = 0x1,
  CSI_VCID_01 = 0x2,
  CSI_VCID_02 = 0x4,
  CSI_VCID_03 = 0x8,
  
  CSI_VCID_10 = 0x10,
  CSI_VCID_11 = 0x20,
  CSI_VCID_12 = 0x40,
  CSI_VCID_13 = 0x80,
}; // CSI VC ID definition  

//*****************************************************************************

///< 32 bits to define what CSI VCs are used
typedef union CSI_IdKey {    
  uint32_t mKey;                 ///< CSI ID key
  struct 
  {
    uint8_t mCsi:8;               ///< Csi interface index
    uint16_t mVc:16;              ///< Csi id
  } mId;                          ///< Included IDs
} CSI_IdKey_t;

//*****************************************************************************

enum CSI_SENSORS
{
  CSI_SONY = 0,
  CSI_OV10640,
  CSI_MAX_OV10640,  
  CSI_MAX_SONY
}; // CSI index definition

//*****************************************************************************

enum CSI_IRQ_TYPE
{
  CSI_IRQ_TYPE_SOF = 0x1,  ///< start of frame interrupt
  CSI_IRQ_TYPE_EOF = 0x2,  ///< end of frame interrupt
  CSI_IRQ_TYPE_LLE = 0x4,  ///< line length error interrupt
  CSI_IRQ_TYPE_LCE = 0x8,  ///< line count error interrupt
}; // CSI IRQ TYPE definition  

/*****************************************************************************
* struct definitions
*****************************************************************************/

typedef struct CSI_VcCfg
{
  uint32_t mBufAddr;          ///< SRAM buffer address
  uint32_t mLineCnt;          ///< number of lines fitting into buffer
  uint32_t mLineBytes;        ///< number of bytes per line
  uint32_t mLineStride;       ///< number of bytes to next line begin
  uint32_t mFrameHeight;      ///< expected frame height
  uint32_t mDoneLineCnt;      ///< number of lines after which the done signal is generated
} CSI_VcCfg_t; // CSI VC configuration

//*****************************************************************************

typedef struct CSI_Cfg
{
  union CSI_IdKey mIdKey;      ///< Mipi CSI id;
  enum CSI_SENSORS  mSensor;   ///< sensor type;
  struct CSI_VcCfg  mpVc[4];   ///< VC config
} CSI_Cfg_t; // CSI configuration

//*****************************************************************************

#if defined(__KERNEL__) || defined(__STANDALONE__)
#include "s32vs234.h"

typedef struct mutex mutex_t;


#endif // #if defined(__KERNEL__) || defined(__STANDALONE__)

#ifdef __cplusplus 
} //extern "C" { 
#endif

#endif // CSI_TYPES_H