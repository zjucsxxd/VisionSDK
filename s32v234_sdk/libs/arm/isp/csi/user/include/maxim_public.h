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
* \file     maxim_public.h
* \brief    public declarations for maxim user space library
* \author   Tomas Babinec
* \version  0.1
* \date     14-December-2014
* \note
****************************************************************************/

#ifndef MAXIM_PUBLIC_H
#define MAXIM_PUBLIC_H

#include "csi.h"
#include "csi_public.h"
#include "sony_types.h"
#include "seq_types.h"

//*****************************************************************************
// constants
//*****************************************************************************

//*****************************************************************************
// types
//*****************************************************************************

//*****************************************************************************
// public functionality declarations
//*****************************************************************************

/****************************************************************************/
/** Configures Sony camera registers.
* 
* \param apMessage[in] message to be sent
* 
* \return CSI_LIB_SUCCESS if all ok
*         CSI_LIB_FAILURE otherwise
*****************************************************************************/
CSI_LIB_RESULT MAXIM_Init(enum CSI_IDX aCsiIdx, const uint32_t acCamCnt);

/****************************************************************************/
/** Enables CSI transmission from Sony camera.
 * 
 * \param apGraphPackage packed graph structure
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT MAXIM_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI transmission from Sony camera.
* 
* \return CSI_LIB_SUCCESS if all ok, 
*         CSI_LIB_FAILURE otherwise
*****************************************************************************/
CSI_LIB_RESULT MAXIM_CsiDisable(enum CSI_IDX aCsiIdx);

#endif // MAXIM_PUBLIC_H

/* EOF */