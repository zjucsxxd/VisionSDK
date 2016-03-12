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
* \file     sram_func.h
* \brief    function declarations for SRAM manager driver
* \author   Tomas Babinec
* \version  0.1
* \date     22.4.2014
* \note
****************************************************************************/

#ifndef SRAM_FUNC_H
#define SRAM_FUNC_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include "sram.h"

//*****************************************************************************
// types
//*****************************************************************************
#if !defined(__STANDALONE__) && defined(__KERNEL__)
typedef struct mutex mutex_t;
#endif // #if !defined(__STANDALONE__) && defined(__KERNEL__)

//*****************************************************************************
// function prototypes
//*****************************************************************************

/****************************************************************************/
/** Sets up the SRAM Manager.
* 
* \return SRAM_DRV_SUCCESS if all ok, otherwise SRAM_DRV_FAILURE     
*****************************************************************************/
int32_t SRAM_SetUp(void);

/****************************************************************************/
/** Releases all SRAM related resources.
* 
* \return SRAM_DRV_SUCCESS if all ok, otherwise SRAM_DRV_FAILURE     
*****************************************************************************/
void SRAM_Close(void);

/****************************************************************************/
/** Allocates region of specified size in SRAM single-banked area.
* 
* \note The actual memory used is higher than requested size.(includes padding
* and metadata)
*
* \param size   requested region size
* 
* \return       Physical address of the allocated region, 0 in case of an error.     
*****************************************************************************/
uintptr_t SRAM_SingleMalloc(uintptr_t aSize);

/****************************************************************************/
/** Allocates region of specified size in SRAM multi-banked area.
* 
* \note The actual memory used is higher than requested size.(includes padding
* and metadata)
*
* \param aSize   requested region size
* 
* \return       Physical alddress of the allocated region, 0 in case of an error.     
*****************************************************************************/
uintptr_t SRAM_MultiMalloc(uintptr_t aSize);

/****************************************************************************/
/** Releases the specified SRAM memory region.
* 
* \note Common for single- and multi-banked SRAM areas.
*
* \param aAddr   address of the region (acquired from sram_multi/single_alloc)
*      
*****************************************************************************/
void SRAM_Free(uintptr_t aAddr);

#ifdef __cplusplus 
} // extern "C" 
#endif

#endif // SRAM_FUNC_H
