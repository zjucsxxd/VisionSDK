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
 * \file    maxim_func.hpp
 * \brief   Maxim SER/DES related functionality declaration.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    8-July-2015
 ****************************************************************************/

#ifndef MAXIM_FUNC_HPP_
#define MAXIM_FUNC_HPP_

#ifdef __cplusplus 
extern "C" { 
#endif

//****************************************************************************
// contant definitions
//****************************************************************************
#define MAXIM_CAM_SLOTS 4
#define MAXIM_FAILURE 1
#define MAXIM_SUCCESS 0  

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Configures Maxim SER/DES setup.
 * 
 * \param acCamCnt   number of attached cameras
 * 
 ****************************************************************************/
int32_t MAXIM_DRV_Init(enum CSI_IDX aCsiIdx, const uint32_t acCamCnt);

/****************************************************************************/
/** Configures Maxim SER/DES setup.
 * 
 * New guide.
 * 
 * \param acCamCnt   number of attached cameras
 * 
 ****************************************************************************/
int32_t MAXIM_DRV_Init2(const uint32_t acCamCnt);

/****************************************************************************/
/** Enables CSI output from deserializer.
 * 
 ****************************************************************************/
void MAXIM_DRV_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI output from deserializer.
 * 
 ****************************************************************************/
void MAXIM_DRV_CsiDisable(enum CSI_IDX aCsiIdx);

#ifdef __cplusplus 
} //extern "C" 
#endif

#endif // MAXIM_FUNC_HPP_ 
