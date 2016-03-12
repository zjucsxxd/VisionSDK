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
 * \file     fdma_user.c
 * \brief    User space access functions to fdma driver.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     10.11.2014
 * \note
 ****************************************************************************/

#include "s32vs234.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>		// memset
#include <unistd.h>		// exit 
#include <stdint.h>

#ifndef __STANDALONE__ 
// only for LINUX
#include <fcntl.h>		// open 
#include <sys/types.h>
#include <sys/ioctl.h>	// ioctl */
#else 
#include "fdma_func.h"

#endif // else from ifndef __STANDALONE__

#include "fdma_public.h"

//****************************************************************************
// global variables
//****************************************************************************

#ifndef __STANDALONE__

///< array of pointers to user registerred event handlers (one for each TD)
static FDMA_EventHandler_t sEventHandlers[FDMA_TD_CNT];

static uint8_t sInitialized = 0;

static int32_t sFileDesc = -1;		///< driver file descriptor

//****************************************************************************
// local function declarations
//****************************************************************************
void FdmaSigHandler(int n, siginfo_t *info, void *unused);
#endif // #ifndef __STANDALONE__

//****************************************************************************
// function definitions
//****************************************************************************

FDMA_LIB_RESULT FdmaOpen()
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;
  
#ifndef __STANDALONE__  
  if(sFileDesc < 0)
  {
    sFileDesc = open("/dev/" FDMA_DEVICE_NAME, 0);
    if (sFileDesc < 0) {
      VDB_LOG_ERROR("Can't open device file: %s\n", FDMA_DEVICE_NAME);
      lRet = FDMA_LIB_FAILURE;
    } // if open failed
  } // not openned yet
  else 
  {
    VDB_LOG_WARNING("Fdma already openned.\n");
  } // else from if not openned yet
#else // #ifndef __STANDALONE__ 

  // *** Setup the driver ***    
  if(FDMA_Setup() != FDMA_DRV_SUCCESS)
  {
    lRet = FDMA_LIB_FAILURE;
    VDB_LOG_ERROR("FDMA setup failed.\n");
  } // if driver setup failed
  
#endif //__STANDALONE__
  
  return lRet;
} // Open()

//****************************************************************************

FDMA_LIB_RESULT FdmaClose()
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;
#ifndef __STANDALONE__  
  if(sFileDesc < 0)
  {
    close(sFileDesc);
    if (close(sFileDesc) < 0) {
      VDB_LOG_ERROR("Failed to close device file %s.\n", FDMA_DEVICE_NAME);
      lRet = FDMA_LIB_FAILURE;
    } // if open failed
    else
    {
      sFileDesc = -1;
    } // else if open failed
  } // not openned yet
  else 
  {
    VDB_LOG_WARNING("Fdma already closed.\n");
  } // else from if not openned yet
#else // #ifndef __STANDALONE__ 

  // relase resources
  FDMA_Close();
  
#endif // else from #ifndef __STANDALONE__ 
  
  return lRet;
} // Close()


//****************************************************************************

FDMA_LIB_RESULT FdmaTcReserve(FDMA_Tc_t *apTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if(apTc != NULL)
  {
    if (ioctl(sFileDesc, IOCTL_FDMA_TD_RESERVE, &(apTc->mTdm)) != FDMA_DRV_SUCCESS) 
    {
      VDB_LOG_ERROR("TcReserve failed:%d\n", (int) lRet);
      // reset the TC
      memset(apTc, 0, sizeof(FDMA_Tc_t));
      lRet = FDMA_LIB_FAILURE;
    } // if ioctl returned failure
  } // if TC exists
  else
  {
    VDB_LOG_ERROR("TC pointer is NULL.\n");
    lRet = FDMA_LIB_FAILURE;
  } // else from if TC exists
#else // #ifndef __STANDALONE__ 
  FDMA_Tdm_t *lpFreeTdm = NULL;
          
  //try to pop free TD
  //lpFreeTdm = FDMA_TdmListPopFront(&gFreeTdmList);
  lpFreeTdm = FDMA_TdmFreePop();
  if( lpFreeTdm )
  {
    // set the TDM
    lpFreeTdm->mReserved = 1;
    lpFreeTdm->mOwnerProcId = 777;
      
    // copy TDM back to user
    apTc->mTdm = *lpFreeTdm;
  } // if pop succeeded
  else
  {
    // return failure (leave TC reset to user space)
    lRet = FDMA_LIB_FAILURE;
  } // if pop failed    
#endif // else from #ifndef __STANDALONE__
  
  return lRet;
} // FdmaTcReserve()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcConfig(const FDMA_Tc_t *acpTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if (ioctl(sFileDesc, IOCTL_FDMA_TD_CONFIG, acpTc) != FDMA_DRV_SUCCESS) 
  {
	  VDB_LOG_ERROR("TcConfig failed:%d\n", (int)lRet);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  // set the new TD values       
  if(FDMA_TdConfig(acpTc) != FDMA_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("TD config failed.\n");
    lRet = FDMA_LIB_FAILURE;
  }
#endif // else from #ifndef __STANDALONE__ 

  return lRet;
} // FdmaTcConfig()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcIspConfig(const FDMA_Tc_t *acpTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if (ioctl(sFileDesc, IOCTL_FDMA_TD_ISP_CONFIG, acpTc) != FDMA_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("ISP TC Config failed:%d\n", (int)lRet);
    lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  // set the new TD values       
  if(FDMA_TdIspConfig(acpTc) != FDMA_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("ISP TC config failed.\n");
    lRet = FDMA_LIB_FAILURE;
  }
#endif // else from #ifndef __STANDALONE__ 

  return lRet;
} // FdmaTcConfig()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcSchedule(const FDMA_Tc_t *acpTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_TD_SCHEDULE, acpTc) != FDMA_DRV_SUCCESS) 
  {
	  VDB_LOG_ERROR("TcSchedule failed:%d\n", (int) lRet);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  FDMA_TcSchedule(acpTc);
#endif // else from #ifndef __STANDALONE__ 

  return lRet;
} // FdmaTcSchedule()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcRelease( FDMA_Tc_t *apTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_TD_RELEASE, &(apTc->mTdm)) != FDMA_DRV_SUCCESS) 
  {
    VDB_LOG_ERROR("TcRelease failed:%d\n", (int) lRet);
    lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
  else
  {
    apTc->mTdm.mReserved = 0;
  } // else from if ioctl returned failure
#else // #ifndef __STANDALONE__ 

  //try to push free TDM
  if( FDMA_TdRelease(&(apTc->mTdm)) != FDMA_DRV_SUCCESS )
  {
    VDB_LOG_ERROR("Tdm release failed.\n");
    lRet = FDMA_LIB_FAILURE;
  } // if push failed
#endif // else from #ifndef __STANDALONE__ 
  
  return lRet;
} // FdmaTcRelease()

//****************************************************************************

int32_t FdmaSeqModeGet()
{
#ifndef __STANDALONE__
  return ioctl(sFileDesc, IOCTL_FDMA_SEQ_MODE_GET);
#else // #ifndef __STANDALONE__ 
  return 1;
#endif // else from #ifndef __STANDALONE__ 
} // FdmaSeqModeGet()

//****************************************************************************

FDMA_LIB_RESULT FdmaStatusGet(FDMA_Regs_t *apFdmaRegs)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_STATUS_GET, apFdmaRegs) != FDMA_DRV_SUCCESS) 
  {
	  VDB_LOG_ERROR("StatusGet failed:%d\n", (int) lRet);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  FDMA_Regs_t *lpFdmaRegs = FDMA_RegsGet();
        
  if(lpFdmaRegs != NULL)
  {
    // copy fdma registers back to user
    memcpy((void*)apFdmaRegs,(const void*) lpFdmaRegs, sizeof(FDMA_Regs_t));
    //*apFdmaRegs = *lpFdmaRegs;
  }else
  {
    VDB_LOG_ERROR("FDMA registers not mapped.\n");
    lRet = FDMA_LIB_FAILURE;
  }
  
#endif // else from #ifndef __STANDALONE__ 
  return lRet;
} // FdmaStatusGet()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcGet(FDMA_Tc_t *apTc)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_TC_GET, apTc) != FDMA_DRV_SUCCESS) 
  {
	  VDB_LOG_ERROR("TcGet failed:%d\n", (int) lRet);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__    
  // read the TD  
  if(FDMA_TcGet(apTc) != FDMA_DRV_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to get the TC.\n");
    lRet = FDMA_LIB_FAILURE;
  }  
#endif // else from #ifndef __STANDALONE__ 
  return lRet;
} // FdmaTcGet()

//****************************************************************************

FDMA_LIB_RESULT FdmaTcUsed(uint32_t &arTcUsedCnt)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_TD_USED, &arTcUsedCnt) < 0) 
  {
	  VDB_LOG_ERROR("TcUsed failed: %u\n", arTcUsedCnt);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  int32_t lTdFree = FDMA_TdmFreeCntGet();
  arTcUsedCnt = FDMA_TD_CNT - lTdFree;
  VDB_LOG_NOTE("TD_CNT: %u, Free: %u, Used: %u\n", (unsigned) FDMA_TD_CNT, (unsigned) lTdFree, (unsigned) arTcUsedCnt);
#endif // else from #ifndef __STANDALONE__ 
  
  return lRet;
} // FdmaTcUsed()

//****************************************************************************

FDMA_LIB_RESULT FdmaTdtAddrGet(uint64_t &arTdtAddr)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;

#ifndef __STANDALONE__
  if (ioctl(sFileDesc, IOCTL_FDMA_TDT_GET, &arTdtAddr) < 0) 
  {
	  VDB_LOG_ERROR("TdtAddrGet failed:%d\n", (int) arTdtAddr);
	  lRet = FDMA_LIB_FAILURE;
  } // if ioctl returned failure
#else // #ifndef __STANDALONE__ 
  arTdtAddr = FDMA_TdtPhysAddrGet();
#endif // else from #ifndef __STANDALONE__ 
  return lRet;
} // FdmaTdtAddrGet()

//****************************************************************************

FDMA_LIB_RESULT FdmaEventHandlerSet(FDMA_Tc_t *apTc, FDMA_EventHandler_t aHandler)
{
  FDMA_LIB_RESULT lRet = FDMA_LIB_SUCCESS;
#ifndef __STANDALONE__
  if(apTc != NULL)
  {
    if(sInitialized == 0)
    {
      // initialize all handler pointers if first assignment
      for(uint32_t i = 0; i < FDMA_TD_CNT; i++)
      {
        sEventHandlers[i] = NULL;
      } // for all possible TDs
      
      // prepare internal signal handler
      struct sigaction sig;
      sig.sa_sigaction = FdmaSigHandler;
      sig.sa_flags = SA_SIGINFO;
      if( sigaction(FDMA_EVENT_SIGNAL, &sig, NULL) != 0)
      {
        VDB_LOG_ERROR("Failed to register signal handler.\n");
        lRet = FDMA_LIB_FAILURE;
      } // if signal not registered
      else 
      {
        sInitialized = 1;
      } // else from if signal not registered
    } // if not initialized yet
    
    if(lRet == FDMA_LIB_SUCCESS)
    {
      // set the new handler
      sEventHandlers[apTc->mTdm.mTdIdx] = aHandler;
    } // if all ok so far
  } // if not a bad TC pointer
#else // #ifndef __STANDALONE__
  // TODO: in case interrupts available
  lRet = FDMA_LIB_FAILURE;
#endif // else from #ifndef __STANDALONE__
  
  return lRet;
} // FdmaEventHandlerSet()

//****************************************************************************

#ifndef __STANDALONE__
void FdmaSigHandler(int aSigNum, siginfo_t *apSigInfo, void *aUnused) 
{
  uint32_t lTdIdx = apSigInfo->si_int & 0xff;
  uint32_t lEventType = apSigInfo->si_int >> 8;
  
  if(aUnused == NULL)
  {
    printf("received signal %d\n", aSigNum);
  }
  
  VDB_LOG_NOTE("received event %u from TD %u\n",(unsigned) lEventType, (unsigned) lTdIdx);
  
  // *** call apropriate handler ***
  if(sEventHandlers[lTdIdx] != NULL)
  {
    // call the handler
    sEventHandlers[lTdIdx](lTdIdx, lEventType);
  } // if handler assigned
  else
  {
    VDB_LOG_WARNING("Event handler unassigned for TD %u.\n", lTdIdx);
  } // else from if handler assigned
  
} //FdmaSigHandler()
#endif //#ifndef __STANDALONE__

//****************************************************************************
