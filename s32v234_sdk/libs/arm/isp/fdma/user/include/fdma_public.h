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
 * \file     fdma_public.h
 * \brief    Declarations of user space access functions to fdma driver.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     10.11.2014
 * \note
 ****************************************************************************/

#ifndef __FDMA_PUBLIC__H__
#define __FDMA_PUBLIC__H__

#include "fdma.h"
#include "fdma_types.h"

#include "vdb_log.h"

#ifdef __cplusplus 
extern "C" { 
#endif

//*****************************************************************************
// types
//*****************************************************************************

enum FDMA_LIB_RESULT
{
  FDMA_LIB_SUCCESS = 0,
  FDMA_LIB_FAILURE = 1
}; // FDMA_LIB_RESULT

// user function pointer to handle fdma event
typedef void(*FDMA_EventHandler_t)(uint32_t aTdIdx, uint32_t aEventType);

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Enables FDMA operation for this program.
 * 
 * In Linux the fdma special device file is opened.
 * In standalone environment the FDMA_SetUp() function is called directly to
 * initialize the internal driver structures and HW registers.
 *  
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaOpen(void);

/****************************************************************************/
/** Disables FDMA operation for this program.
 * 
 * In Linux the fdma special device file is closed.
 * In standalone environment the FDMA_Close() function is called directly to
 * release internal driver resources and disconnect from the HW.
 *
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaClose(void);

/****************************************************************************/
/** Reserves one FDMA TranferChannel (TC).
 * 
 * \param  apTc  pointerto a TC structure to be filled with the reserved TC 
 *               metadata and setup
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcReserve(FDMA_Tc_t *apTc);

/****************************************************************************/
/** Applies the given TC setup to the USER TransferDescriptorTable (TDT) in SRAM.
 * 
 * \param  acpTc pointer to the TC to be configured
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcConfig(const FDMA_Tc_t *apTc);

/****************************************************************************/
/** Applies the given TC setup to the ISP TransferDescriptorTable (TDT) in SRAM.
 * 
 * \param  acpTc pointer to the TC to be configured
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcIspConfig(const FDMA_Tc_t *acpTc);

/****************************************************************************/
/** Schedules one FDMA transfer described by the given TC.
 * 
 * Schedule only. No TC configuration done internally. Has to be preceeded by 
 * call to FdmaTcConfig().
 * 
 * \param  acpTc pointer to the TC to be scheduled
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcSchedule(const FDMA_Tc_t *apTc);

/****************************************************************************/
/** Releases the specified TC.
 * 
 * \param  apTc reference to the TC to be released
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcRelease(FDMA_Tc_t *apTc);

/****************************************************************************/
/** Finds out if the Sequencer is ON.
 * 
 * \note For debug only at the moment.
 * 
 * \return 1 if Sequencer ON
 *         0 otherwise
 ****************************************************************************/
int32_t FdmaSeqModeGet(void);
        
/****************************************************************************/
/** Gets current content of FDMA registers.
 * 
 * \param  apFdmaRegs pointer to FDMA register structure to be filled in
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaStatusGet(FDMA_Regs_t *apFdmaRegs);

/****************************************************************************/
/** Gets latest state of the given TC.
 * 
 * Reads the most resent TD setup directly from SRAM TD table.
 * 
 * \param  apTc pointer to a TC
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcGet(FDMA_Tc_t *apTc);

/****************************************************************************/
/** Gets the current number of reserved TCs.
 * 
 * \param  arTcUsedCnt reference to the "used count" output variable
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTcUsed(uint32_t &arTcUsedCnt);

/****************************************************************************/
/** Sets FDMA event handler to a specific transfer channel (TC).
 * 
 * \param apTc     pointer to the Transfer channel the handler will be bind to
 * \param aHandler pointer to a function to handle the event
 * 
 * \return IRQ_HANDLED when done
 *
 ****************************************************************************/
FDMA_LIB_RESULT FdmaEventHandlerSet(FDMA_Tc_t *apTc, FDMA_EventHandler_t aHandler);

/****************************************************************************/
/** Gets the physical address of the TDT in SRAM.
 * 
 * \note For debug only at the moment.
 * 
 * \param  arTdtAddr reference to the address output variable
 * 
 * \return FDMA_LIB_SUCCESS if all ok
 *         FDMA_LIB_FAILURE if failed
 ****************************************************************************/
FDMA_LIB_RESULT FdmaTdtAddrGet(uint64_t &arTdtAddr);

//****************************************************************************

#ifdef __cplusplus 
} // extern "C" { 
#endif

#endif // __FDMA_PUBLIC__H__