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
 * \file     csi_user.cpp
 * \brief    User-space library calls to access CSI driver functionality.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     18-September-2015
 * \note
 ****************************************************************************/

#include "s32vs234.h"
#include <stdint.h>
#include <errno.h>
#include <string.h>

#ifndef __STANDALONE__
  #include <signal.h>
  #include <fcntl.h>		// open 
  #include <unistd.h>		// exit 
  #include <sys/ioctl.h>	// ioctl 
  #include <sys/mman.h>	// mmap
#else
  #include "csi_func.h"
  #include "sony_func.h"
#endif // else from #ifndef __STANDALONE__

#define VDB_LOG_NOTE_OFF

#include "csi_public.h"
#include "vdb_log.h"
#include "isp_hw.h"

//****************************************************************************
// consts
//****************************************************************************


//****************************************************************************
// types
//****************************************************************************


//****************************************************************************
// global variables
//****************************************************************************


//*****************************************************************************
// local data
//*****************************************************************************

//static CSI_EventHandler_t sEventHandler = NULL; ///< user registerred event handler
//static CSI_EventHandlerClass *spEventHandlerClass = NULL; ///< user registerred event handler
//static uint8_t sInitialized = 0;	///< >0 if initialized

// chip geometry settings
static SONY_Geometry_t sGeometry;
//static SONY_Exposure_t sExposure;

#ifndef __STANDALONE__
  int32_t gCsiFD = -1;    ///< csi driver file descriptor

//****************************************************************************
// local function declarations
//****************************************************************************
  void CsiSigHandler(int aSigNum, siginfo_t *info, void *unused);
#else //#ifndef __STANDALONE__
extern "C" {
  void CsiSigHandler(int aSigNum, int aValue);
}
#endif //else from #ifndef __STANDALONE__

//*****************************************************************************
// functions definitions
//*****************************************************************************

CSI_LIB_RESULT CSI_Open()
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;
  memset(&sGeometry, 0, sizeof(SONY_Geometry_t));
  memset(&sGeometry, 0, sizeof(SONY_Exposure_t));

#ifndef __STANDALONE__  
  if(gCsiFD < 0)
  {  
    gCsiFD = open("/dev/csi", 0);
    if (gCsiFD < 0) 
    {
      VDB_LOG_ERROR("Can't open device file: %s\n", CSI_DEVICE_NAME);
      lRet = CSI_LIB_FAILURE;
    } // if open failed
  } // if not opened yet
  else 
  {
    VDB_LOG_WARNING("Device file: %s opened already.\n", CSI_DEVICE_NAME);
  } // else from if not opened yet
#else // from ifndef __STANDALONE__
  if(CSI_DRV_Setup() != CSI_DRV_SUCCESS)
  {
    lRet = CSI_LIB_FAILURE;
  }
#endif // #ifndef __STANDALONE__
  
  return lRet;
} // CSI_Reserve()

//*****************************************************************************

CSI_LIB_RESULT CSI_Close()
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;
#ifndef __STANDALONE__  
  if(gCsiFD < 0)
  {
    close(gCsiFD);
    if (close(gCsiFD) < 0) 
    {
      VDB_LOG_ERROR("Failed to close device file %s.\n", CSI_DEVICE_NAME);
      lRet = CSI_LIB_FAILURE;
    } // if open failed
    else
    {
      gCsiFD = -1;
    } // else if open failed
  } // not openned yet
  else 
  {
    VDB_LOG_WARNING("Csi already closed.\n");
  } // else from if not openned yet
#endif // else from #ifndef __STANDALONE__ 
  return lRet;
} // CSI_Release()

//*****************************************************************************

CSI_LIB_RESULT CSI_Config(CSI_Cfg_t *apcCsiCfg)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__  
  if(apcCsiCfg != NULL)
  {
    if(gCsiFD < 0)
    {
      VDB_LOG_ERROR("Csi device file not opened.\n");
      lRet = CSI_LIB_FAILURE;
    } // if Csi not opened
    else
    {
      int32_t lRetVal = 0;
      if ((lRetVal = ioctl(gCsiFD, IOCTL_CSI_CONFIG, apcCsiCfg)) < 0) 
      {
        VDB_LOG_ERROR("Csi init failed: %d\n", lRetVal);
        lRet = CSI_LIB_FAILURE;
      } // if ioctl returned failure
    } // else from if Csi not opened
  }// if apcCsiCfg exists
#else // #ifndef __STANDALONE__
  CSI_DRV_Config(apcCsiCfg);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // CSI_Config(const CSI_Cfg_t *apcCsiCfg)

//*****************************************************************************

CSI_LIB_RESULT CSI_Start(CSI_IdKey_t aCsiIdKey)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_CSI_START, aCsiIdKey)) < 0) 
    {
      VDB_LOG_ERROR("Failed to start CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    CSI_DRV_Start(aCsiIdKey);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // CSI_Start(CSI_IdKey_t aCsiIdKey)

//*****************************************************************************

CSI_LIB_RESULT CSI_Stop(CSI_IdKey_t aCsiIdKey)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_CSI_STOP, aCsiIdKey)) < 0) 
    {
      VDB_LOG_ERROR("Failed to stop CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    CSI_DRV_Stop(aCsiIdKey);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // CSI_Stop(CSI_IdKey_t aCsiIdKey)

//****************************************************************************
//     Event handling
//****************************************************************************

#ifdef __STANDALONE__
void CSI_IrqHandlerSet(enum CSI_IDX aCsiIdx, void (*apIrqHandler)(void))
{
  CSI_DRV_IrqHandlerSet(aCsiIdx, apIrqHandler);
}
#endif // ifdef __STANDALONE__

//*****************************************************************************

/*EOF*/
