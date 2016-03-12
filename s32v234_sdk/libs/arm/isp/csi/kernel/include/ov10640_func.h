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
 * \file    sony_func.hpp
 * \brief   Omnivision 10640 MIPI/CSI camera functionality declaration.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    14-December-2015
 ****************************************************************************/

#ifndef OV10640_FUNC_HPP_
#define OV10640_FUNC_HPP_

#include "csi_types.h"
//#include "ov10640_types.h"

#ifdef __cplusplus 
extern "C" { 
#endif

//****************************************************************************
// contant definitions
//****************************************************************************

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Configures Sony camera driver.
 * 
 * 
 ****************************************************************************/
int32_t OV10640_DRV_Setup(void);

/****************************************************************************/
/** Configures Sony camera register.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void OV10640_DRV_RegConfig(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Enables CSI output from Sony camera.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void OV10640_DRV_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI output from Sony camera.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void OV10640_DRV_CsiDisable(enum CSI_IDX aCsiIdx);

#ifdef __cplusplus 
} //extern "C" 
#endif

#endif // OV10640_FUNC_HPP_ 
