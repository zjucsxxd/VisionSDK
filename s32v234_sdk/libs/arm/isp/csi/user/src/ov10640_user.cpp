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
 * \file     ov10640_user.cpp
 * \brief    User-space library calls to access Ov10640 functionality.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     12-December-2015
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
  #include "ov10640_func.h"
#endif // else from #ifndef __STANDALONE__

#define VDB_LOG_NOTE_OFF

#include "ov10640_public.h"
#include "vdb_log.h"

//****************************************************************************
// consts
//****************************************************************************

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// global variables
//****************************************************************************
#ifndef __STANDALONE__
  extern int32_t gCsiFD;   ///< csi driver file descriptor
#endif //ifndef __STANDALONE__

//*****************************************************************************
// local data
//*****************************************************************************

//static CSI_EventHandler_t sEventHandler = NULL; ///< user registerred event handler
//static CSI_EventHandlerClass *spEventHandlerClass = NULL; ///< user registerred event handler
//static uint8_t sInitialized = 0;	///< >0 if initialized

//*****************************************************************************
// functions definitions
//*****************************************************************************

CSI_LIB_RESULT OV10640_RegConfig(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(gCsiFD, IOCTL_OV10640_REG_CONFIG, aCsiIdx)) < 0) 
  {
    VDB_LOG_ERROR("Failed to configure camera registers.\n");
    lRet = CSI_LIB_FAILURE;
  } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
  OV10640_DRV_RegConfig(aCsiIdx);
    
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // CSI_RegConfig(CSI_BufferList_t *apBuffsList)

//*****************************************************************************

CSI_LIB_RESULT OV10640_CsiEnable(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_OV10640_START, aCsiIdx)) < 0) 
    {
      VDB_LOG_ERROR("Failed to start Ov10640 camera CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    OV10640_DRV_CsiEnable(aCsiIdx);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // OV10640_CsiEnable(enum CSI_IDX aCsiIdx)

//*****************************************************************************

CSI_LIB_RESULT OV10640_CsiDisable(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_OV10640_STOP, aCsiIdx)) < 0) 
    {
      VDB_LOG_ERROR("Failed to stop Ov10640 camera CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    OV10640_DRV_CsiDisable(aCsiIdx);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // OV10640_CsiDisable(enum CSI_IDX aCsiIdx)

//***************************************************************************

/*EOF*/
