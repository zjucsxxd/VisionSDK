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
 * \file     fdma_ioctl.c
 * \brief    IOCTL functionality of fDMA driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     21. September 2015
 * \note
 ****************************************************************************/

#include <asm/uaccess.h>	// for get_user and put_user 
#include <linux/mutex.h>	// for semaphore/mutex
#include <linux/string.h>	// for memset
#include <linux/sched.h>	// for current->pid

#include "csi.h"
#include "csi_ioctl.h"
#include "csi_func.h"
#include "sony_func.h"

#include "vdb_log.h"

// CSI locking mutex
extern mutex_t gCsiMutex;

long CsiIoctl( struct file *apFile,	/* ditto */
                unsigned int aIoctlNum,	/* number and param for ioctl */
                unsigned long aIoctlParam)
{
  int lRet = CSI_DRV_SUCCESS;
#if 0  
  // only one IOCTL can be processed at the time
  if(mutex_lock_interruptible(&gCsiMutex) > 0)
  {
    VDB_LOG_WARNING("CSI mutex down interrupted.\n");
    lRet = -ERESTARTSYS;
  } // if CSI mutex interrupted
  else
  {
    VDB_LOG_NOTE("CSI mutex locked.\n");
#endif //0
    // switch the ioctl command
    switch (aIoctlNum) {

      case IOCTL_CSI_CONFIG:
      {
        CSI_Cfg_t lCfg;
        if (copy_from_user( &lCfg, (CSI_Cfg_t *)aIoctlParam, 
            sizeof(CSI_Cfg_t)) != 0)
        {
          VDB_LOG_ERROR("Copy from user failed.\n");
          lRet = -EIO;
        } // if copy from user failed
        else
        {   
          CSI_DRV_Config(&lCfg);
        } // else from if copy from user failed
      } // case IOCTL_CSI_INIT
      break;
      
      case IOCTL_SONY_REG_CONFIG:
      {
        enum CSI_IDX lCsiIdx = (enum CSI_IDX)aIoctlParam;
        
        SONY_DRV_RegConfig(lCsiIdx);     
      } // case IOCTL_SONY_REG_CONFIG
      break;

      case IOCTL_CSI_STOP:
      {
        CSI_IdKey_t lCsiIdKey;
        lCsiIdKey.mKey = (uint32_t)aIoctlParam;
        
        CSI_DRV_Stop(lCsiIdKey);       
      } // case IOCTL_CSI_STOP
      break;
      
      case IOCTL_CSI_START:
      {
        CSI_IdKey_t lCsiIdKey;
        lCsiIdKey.mKey = (uint32_t)aIoctlParam;
                
        CSI_DRV_Start(lCsiIdKey);       
      } // case IOCTL_CSI_START
      break;
      
      case IOCTL_SONY_START:
      {
        enum CSI_IDX lCsiIdx = (enum CSI_IDX)aIoctlParam;
        
        SONY_DRV_CsiEnable(lCsiIdx);    
      } // case IOCTL_SONY_START
      break;
      
      case IOCTL_SONY_EXP_GET:
      {
        SONY_Exposure_t lExp;
        if (copy_from_user( &lExp, (SONY_Exposure_t *)aIoctlParam, 
                            sizeof(SONY_Exposure_t)) != 0)
        {
          VDB_LOG_ERROR("Copy from user failed.\n");
          lRet = -EIO;
        } // if copy from user failed
        else
        {   
          lRet = SONY_DRV_ExposureGet(lExp.mCsiIdx, &lExp);
          if (copy_to_user((SONY_Exposure_t *)aIoctlParam, &lExp, 
                            sizeof(SONY_Exposure_t)) != 0)
          {
            VDB_LOG_ERROR("Copy to user failed.\n");
            lRet = -EIO;
          } // if copy from user failed
        } // else from if copy from user failed
      } // case IOCTL_SONY_EXP_GET
      break;
      
      case IOCTL_SONY_EXP_SET:
      {
        SONY_Exposure_t lExp;
        if (copy_from_user( &lExp, (SONY_Exposure_t *)aIoctlParam, 
                            sizeof(SONY_Exposure_t)) != 0)
        {
          VDB_LOG_ERROR("Copy from user failed.\n");
          lRet = -EIO;
        } // if copy from user failed
        else
        {   
          //printk("ioctl EXP_SET\n");
          lRet = SONY_DRV_ExposureSet(lExp.mCsiIdx, &lExp);
          if (copy_to_user((SONY_Exposure_t *)aIoctlParam, &lExp, 
                            sizeof(SONY_Exposure_t)) != 0)
          {
            VDB_LOG_ERROR("Copy to user failed.\n");
            lRet = -EIO;
          } // if copy from user failed
        } // else from if copy from user failed
      } // case IOCTL_SONY_EXP_SET
      break;
      case IOCTL_SONY_EXP_STATUS_GET:
      {
        lRet = (int32_t)SONY_DRV_ExpStateGet((enum CSI_IDX)aIoctlParam);
      } // case IOCTL_SONY_EXP_STATUS_GET
      break;
      
      case IOCTL_SONY_GEO_GET:
      {
        SONY_Geometry_t lGeo;
        if (copy_from_user( &lGeo, (SONY_Geometry_t *)aIoctlParam, 
                            sizeof(SONY_Geometry_t)) != 0)
        {
          VDB_LOG_ERROR("Copy from user failed.\n");
          lRet = -EIO;
        } // if copy from user failed
        else
        {   
          lRet = SONY_DRV_GeometryGet(lGeo.mCsiIdx, &lGeo);
          if (copy_to_user((SONY_Geometry_t *)aIoctlParam, &lGeo, 
                            sizeof(SONY_Geometry_t)) != 0)
          {
            VDB_LOG_ERROR("Copy to user failed.\n");
            lRet = -EIO;
          } // if copy from user failed
        } // else from if copy from user failed
      } // case IOCTL_SONY_GEO_GET
      break;
      
      case IOCTL_SONY_GEO_SET:
      {
        SONY_Geometry_t lGeo;
        if (copy_from_user( &lGeo, (SONY_Geometry_t *)aIoctlParam, 
                            sizeof(SONY_Geometry_t)) != 0)
        {
          VDB_LOG_ERROR("Copy from user failed.\n");
          lRet = -EIO;
        } // if copy from user failed
        else
        {   
          lRet = SONY_DRV_GeometrySet(lGeo.mCsiIdx, &lGeo);
          if (copy_to_user((SONY_Geometry_t *)aIoctlParam, &lGeo, 
                            sizeof(SONY_Geometry_t)) != 0)
          {
            VDB_LOG_ERROR("Copy to user failed.\n");
            lRet = -EIO;
          } // if copy from user failed
        } // else from if copy from user failed
      } // case IOCTL_SONY_GEO_SET
      break;
      
      default:
      {
        VDB_LOG_WARNING("Unknown ioctl command.\n");
        lRet = -ENOTTY;
      } // default
        break;
    } // switch ioctl command
#if 0  
    // relase the CSI mutex
    mutex_unlock(&gCsiMutex);
    VDB_LOG_NOTE("Csi mutex released.\n");
  }// else from if mutex down interrupted
#endif // 0
  return lRet;
} // CsiIoctl()