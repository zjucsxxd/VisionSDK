/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONCSIUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file     csi_public.h
* \brief    public declarations for MIPI-CSI user space library
* \author   Tomas Babinec
* \version  0.1
* \date     03-November-2014
* \note
****************************************************************************/

#ifndef CSI_PUBLIC_H
#define CSI_PUBLIC_H

#include "csi.h"

//*****************************************************************************
// constants
//*****************************************************************************

#define EVTLOG_STRING_SIZE   (10*10*750) // 10 col * 10 char/col * 750 line/frame 

//*****************************************************************************
// types
//*****************************************************************************

/****************************************************************************/
/** Sequencer user space library return values.
 * 
 ****************************************************************************/
enum CSI_LIB_RESULT
{
  CSI_LIB_SUCCESS = 0,
  CSI_LIB_FAILURE = 1
}; // CSI_LIB_RESULT

/****************************************************************************/
///< Pointer to a user function handling CSI events
typedef void(*CSI_EventHandler_t)(uint32_t aEventType);

/****************************************************************************/
/** Sequencer even handler class
 * 
 ****************************************************************************/
class CSI_EventHandlerClass
{
public:
  virtual void CsiEventHandler(uint32_t aEventType) = 0;
}; // CSI_EventHandlerClass

//*****************************************************************************
// public functionality declarations
//*****************************************************************************

/****************************************************************************/
/** Prepares the CSI driver to be used.
 *
 * In Linux the csi special device file is opened.
 * In standalone environment the CSI_SetUp() function is called directly to
 * initialize the internal driver structures and CSI HW.
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if opening of the device file fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_Open(void);

/****************************************************************************/
/** Deinitializes the CSI driver use.
 * 
 * In Linux the csi special device file is closed.
 * In standalone environment the CSI_Close() function is called directly to
 * release internal driver resources and disconnect from the HW.
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if the close fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_Close(void);

/****************************************************************************/
/** Configures CSI registers.
 * 
 * \param apcCsiCfg structure describing the configuration
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Config(CSI_Cfg_t *apcCsiCfg);

/****************************************************************************/
/** Enables CSI receiver.
 * 
 * \param aCsiIdKey[in] Identifies CSI interface channels to Configures
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Start(CSI_IdKey_t aCsiIdKey);

/****************************************************************************/
/** Disables CSI receiver.
 * 
 * \param aCsiIdKey[in] Identifies CSI interface channels to Configures
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Stop(CSI_IdKey_t aCsiIdKey);

/****************************************************************************/
/** Enables CSI transmission from Sony camera.
 * 
 * \param apGraphPackage packed graph structure
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI transmission from Sony camera.
* 
* \return CSI_LIB_SUCCESS if all ok, 
*         CSI_LIB_FAILURE otherwise
*****************************************************************************/
CSI_LIB_RESULT SONY_CsiDisable(enum CSI_IDX aCsiIdx);

#ifdef __STANDALONE__
void CSI_IrqHandlerSet(enum CSI_IDX aCsiIdx, void (*apIrqHandler)(void));
#endif // ifdef __STANDALONE__

#endif // CSI_PUBLIC_H

#include "sony_public.h"
#include "ov10640_public.h"
#include "maxim_public.h"

//****************************************************************************
/* EOF */