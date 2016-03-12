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
* \file     fdma_func.h
* \brief    declaration of fDMA driver internal functionality
* \author   Tomas Babinec
* \version  0.1
* \date     27.5.2014
* \note
****************************************************************************/

#ifndef FDMA_FUNC_H
#define FDMA_FUNC_H

#ifdef __cplusplus 
extern "C" { 
#endif

#if !defined(__STANDALONE__)
#include <linux/interrupt.h>    // For interrupts
#else  // if !defined(__STANDALONE__)
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define IRQ_HANDLED 0

typedef uint32_t irqreturn_t;
#endif // else from if !defined(__STANDALONE__)

#include "fdma.h"

#include "fdma_types.h"

#if defined(__KERNEL__) || defined(__STANDALONE__)

/*****************************************************************************
* functions (prototypes)
*****************************************************************************/

/****************************************************************************/
/** Sets up the internal functionality of the fdma kernel module. Initializes
 * fdma related resources.
* 
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*
*****************************************************************************/
int32_t FDMA_Setup(void);

/****************************************************************************/
/** Releases all fdma related resources.
* 
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*
*****************************************************************************/
void FDMA_Close(void);

/****************************************************************************/
/** FDMA DONE IRQ handler.
* 
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return IRQ_HANDLED when done
*
*****************************************************************************/
irqreturn_t FdmaDoneIrqHandler(int32_t aIrq, void *apDev_id);

/****************************************************************************/
/** FDMA Error IRW handler.
*
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return IRQ_HANDLED when done
*
*****************************************************************************/
irqreturn_t FdmaErrIrqHandler(int32_t aIrq, void *apDev_id);

/****************************************************************************/
/** FDMA CRC Error IRQ handler.
* 
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return IRQ_HANDLED when done
*
*****************************************************************************/
irqreturn_t FdmaCrcErrIrqHandler(int32_t aIrq, void *apDev_id);

// TODO: comment
int32_t FDMA_SeqEventHandler(uint32_t aTdIdx, uint32_t aEventType);

/****************************************************************************/
/** Simple allocation/free call sequence to test SRAM Manager functionality.
* 
* Intended for debug.
* 
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*
*****************************************************************************/
int32_t FdmaSramMallocTest(void);

/****************************************************************************/
/** Attempts to fill/empty a TDM list.
* 
* Intended for debug.
* 
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*
*****************************************************************************/
int32_t FdmaTdmListTest(void);

/****************************************************************************/
/** Initializes the Tdt structure.
* 
* Allocates also the TD array in SRAM.  
* 
* \param apTdt pointer to the TDT to be .
* 
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*
*****************************************************************************/
int32_t FDMA_TdtInit(FDMA_Tdt_t *apTdt);

/****************************************************************************/
/** Initializes the double linked list for TDMs.
*
* Has to be called before the list is used. Sets the list as empty and resets
* all nodes in the node pool. 
* 
* \param apTdmList pointer to a list structure to be initialized.
*****************************************************************************/
void FDMA_TdmListInit(FDMA_TdmList_t *apTdmList);

/****************************************************************************/
/** Pushes TDM structure to the begining of the list.
*
* \param apTdmList pointer to a list structure to push the TDM to.
* \param acpTdm pointer to TDM structure to be pushed.
*
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*****************************************************************************/
int32_t FDMA_TdmListPushFront(FDMA_TdmList_t *apTdmList, FDMA_Tdm_t *acpTdm);

/****************************************************************************/
/** Pushes TDM structure to the end of the list..
*
* \param apTdmList pointer to a list structure to push the TDM to.
* \param acpTdm pointer to TDM structure to be pushed.
*
* \return FDMA_DRV_SUCCESS if all ok, otherwise FDMA_DRV_FAILURE
*****************************************************************************/
int32_t FDMA_TdmListPushBack(FDMA_TdmList_t *apTdmList, FDMA_Tdm_t *acpTdm);

/****************************************************************************/
/** Removes the a TDM from the beginning of the list.
* 
* \param apTdmList pointer to a list structure to be initialized.
* 
* \return pointer to the poped TDM structure, NULL if list was empty
*
*****************************************************************************/
FDMA_Tdm_t* FDMA_TdmListPopFront(FDMA_TdmList_t *apTdmList);

/****************************************************************************/
/** Removes the a TDM from the end of the list.
* 
* \param apTdmList pointer to a list structure to be initialized.
*
* \return pointer to the poped TDM structure, NULL if list was empty
*****************************************************************************/
FDMA_Tdm_t* FDMA_TdmListPopBack(FDMA_TdmList_t *apTdmList);

/****************************************************************************/
/** Pops a TDM out of the free TDM list if available.
*
* \return pointer to the poped TDM structure, NULL if list was empty
*****************************************************************************/
FDMA_Tdm_t* FDMA_TdmFreePop(void);

/****************************************************************************/
/** Returns a TDM back to the free TDM list.
*
* \return FDMA_DRV_SUCCESS if all ok
*         FDMA_DRV_FAILURE if failed
*****************************************************************************/
int32_t FDMA_TdRelease(FDMA_Tdm_t* apTdm);

/****************************************************************************/
/** Returns number of TDMs in the free TDM list.
*
* \return number of available TDMs
*****************************************************************************/
uint32_t FDMA_TdmFreeCntGet(void);

/****************************************************************************/
/** Applies the TD setup to SRAM USER TDT.
* 
* \param apcTc pointer to a TC with the TD configuration. 
*
* \return FDMA_DRV_SUCCESS
*****************************************************************************/
int32_t FDMA_TdConfig( const FDMA_Tc_t* apcTc);

/****************************************************************************/
/** Applies the TD setup to SRAM ISP TDT.
* 
* \param apcTc pointer to a TC with the TD configuration. 
*
* \return FDMA_DRV_SUCCESS
*****************************************************************************/
int32_t FDMA_TdIspConfig( const FDMA_Tc_t* apcTc);

/****************************************************************************/
/** Schedules the given TC.
* 
* \param apcTc pointer to a TC. 
*
* \return FDMA_DRV_SUCCESS
*****************************************************************************/
int32_t FDMA_TcSchedule( const FDMA_Tc_t* apcTc);

/****************************************************************************/
/** Gets pointer to FDMA registers mapping.
* 
* \return pointer to FDMA registers mapping
*         NULL if not mapped
*****************************************************************************/
FDMA_Regs_t* FDMA_RegsGet(void);

/****************************************************************************/
/** Gets current status of a transfer channel.
* 
* \return FDMA_DRV_SUCCESS if all ok
*         FDMA_DRV_FAILURE if failed
*****************************************************************************/
int32_t FDMA_TcGet(FDMA_Tc_t* apTc);

/****************************************************************************/
/** Gets the physical address of the USER TDT in SRAM.
* 
* \return physical address of the USER TDT
*         0 if not mapped
*****************************************************************************/
uint32_t FDMA_TdtPhysAddrGet(void);

/****************************************************************************/
/** Gets the physical address of the ISP0 TDT in SRAM.
* 
* \return physical address of the ISP0 TDT
*         0 if not mapped
*****************************************************************************/
uint32_t FDMA_IspTdtPhysAddrGet(void);

#endif // if defined(__KERNEL__) || defined(__STANDALONE__)

#ifdef __cplusplus 
} // extern "C" { 
#endif

#endif // FDMA_FUNC_H