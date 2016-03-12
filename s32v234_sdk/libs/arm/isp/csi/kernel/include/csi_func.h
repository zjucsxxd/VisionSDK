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
 * \file 		csi_func.hpp
 * \brief 	Mipi csi receiver and camera related functionality declaration.
 * \author 	Tomas Babinec
 * \version 0.1
 * \date 		21-September-2015
 ****************************************************************************/

#ifndef CSI_FUNC_HPP_
#define CSI_FUNC_HPP_

#ifdef __cplusplus 
extern "C" { 
#endif

#include "csi_types.h"

//****************************************************************************
// contant definitions
//****************************************************************************

#if defined(__KERNEL__) || defined(__STANDALONE__)

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Initializes CSI driver to use the HW.
 * 
 ****************************************************************************/
int32_t CSI_DRV_Setup(void);

/****************************************************************************/
/** Deinitialize the driver.
 * 
 ****************************************************************************/
void CSI_DRV_Close(void);
  
/****************************************************************************/
/** Configures MIPI-CSI2 receiver registers.
 *
 * CSI0, One VC, 2 lanes
 * 
 * \param apcCsiCfg Mipi Csi-2 config structure
 * 
 ****************************************************************************/
void CSI_DRV_Config(const CSI_Cfg_t *apcCsiCfg);

/****************************************************************************/
/** Disables MIPI-CSI2 receiver operation.
 * 
 * \param aCsiIdKey Identifies CSI interface channels to Configures
 ****************************************************************************/
void CSI_DRV_Stop(CSI_IdKey_t aCsiIdKey);

/****************************************************************************/
/** Turns on the MIPI receiver functionality.
 * 
 * \param aCsiIdKey Identifies CSI interface channels to Configures
 *
 * MIPI CSI receiver should be enabled before the cam starts to generate data.
 ****************************************************************************/
void CSI_DRV_Start(CSI_IdKey_t aCsiIdKey);

/****************************************************************************/
/** Configures Camera registers over i2c.
 * 
 * \param aCsiIdx   index of CSI interface (valid 0 & 1)
 * \param pIrqHandler pointer to user defined IRQ handler function
 ****************************************************************************/
void CSI_DRV_IrqHandlerSet(enum CSI_IDX aCsiIdx, void (*apIrqHandler)(void));

/****************************************************************************/
/** Prints content of CSI status registers.
 * 
 * \param aCsiIdx   index of CSI interface (valid 0 & 1)
 ****************************************************************************/
void CSI_DRV_StatusPrint(enum CSI_IDX aCsiIdx);
#endif

#ifdef __cplusplus 
} //extern "C" 
#endif

#endif // CSI_FUNC_HPP_ 
