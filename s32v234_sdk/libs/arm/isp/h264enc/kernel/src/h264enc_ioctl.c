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
 * \file     h264enc_ioctl.c
 * \brief    IOCTL functionality of H264 Encoder driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     20.6.2014
 * \note
 ****************************************************************************/

#include <asm/uaccess.h>	// for get_user and put_user 
#include "s32vs234.h"
#include <linux/mutex.h>	// for semaphore/mutex
#include <linux/string.h>	// for memset
#include <linux/sched.h>	// for current->pid
#include "h264enc.h"
#include "h264enc_ioctl.h"
#include "h264enc_func.h"
#include "vdb_log.h"

// H264 Encoder locking mutex
extern struct mutex gH264EncMutex;

// H264 Encoder HW registers placeholder
extern H264ENC_Regs_t gH264EncRegs;

long H264EncIoctl(struct file *apFile,	/* ditto */
		 unsigned int aIoctlNum,	/* number and param for ioctl */
		 unsigned long aIoctlParam)
{
	int lRet = H264ENC_DRV_SUCCESS;
	
	// switch the ioctl command
	switch (aIoctlNum) {
        
          case IOCTL_H264_ENC_CONFIG_SET:
          {
            H264ENC_Config_t lConfig;
            if (copy_from_user( &lConfig, (H264ENC_Config_t *)aIoctlParam, 
                      sizeof(H264ENC_Config_t)) != 0)
            {
              VDB_LOG_ERROR("Copy from user failed.\n");
              lRet = -EIO;
            } // if copy from user failed
            else
            {
              H264ENC_Config(&lConfig);
              VDB_LOG_NOTE("Config done.\n");
            } // else from if copy from user failed            
          }
            break;
            
          case IOCTL_H264_ENC_BUFFERS_SET:
          {
            H264ENC_Buffers_t lBuffers;
            if (copy_from_user( &lBuffers, (H264ENC_Buffers_t *)aIoctlParam, 
                      sizeof(H264ENC_Buffers_t)) != 0)
            {
              VDB_LOG_ERROR("Copy from user failed.\n");
              lRet = -EIO;
            } // if copy from user failed
            else
            {
              H264ENC_BuffersSet(&lBuffers);
              VDB_LOG_NOTE("Buffers set.\n");
            } // else from if copy from user failed       
          }
            break;
            
          case IOCTL_H264_ENC_FETCH:
          {
            H264ENC_LinesFetch((uint32_t)aIoctlParam);
            VDB_LOG_NOTE("Fetch invoked.\n");
          }
            break;
            
          case IOCTL_H264_ENC_BS_ALARM_SHIFT:
          {
            H264ENC_BitstreamAlarmShift((uint32_t)aIoctlParam);
          }
            break;
            
          case IOCTL_H264_ENC_STATUS_GET:
          {
            H264ENC_Status_t lStatus;
            
            H264ENC_StatusGet(&lStatus);
            if (copy_to_user((H264ENC_Status_t *)aIoctlParam, &lStatus, sizeof(H264ENC_Status_t)) != 0)
            {
              VDB_LOG_ERROR("Copy to user failed.\n");
              lRet = -EIO;
            } // if copy to user failed
            else
            {
              VDB_LOG_NOTE("Status fetched.\n");
            }
          }
            break;
            
          case IOCTL_H264_ENC_STOP:
          {
           // TODO: implement
            
            VDB_LOG_FCN_NOT_IMPLEMENTED();
            
          }
            break;
            
          default:
            VDB_LOG_WARNING("Unknown ioctl command.\n");
            lRet = -ENOTTY;
            break;
	} // switch ioctl command
	  	
	return lRet;
} // H264EncIoctl()