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
* \file     h264enc_ioctl.h
* \brief    ioctl related declarations for H264 Encoder driver
* \author   Tomas Babinec
* \version  0.1
* \date     4.4.2014
* \note
****************************************************************************/

#ifndef H264_ENC_IOCTL_H
#define H264_ENC_IOCTL_H

#include <linux/fs.h>		// required for the struct file declaration

#include "h264enc.h"

///////////////////////////////////////////
//
// IOCTL command codes numbers allocation
//

// IOCTL: encodig configuration setup
#define IOCTL_H264_ENC_CONFIG_SET _IOW(H264ENC_IOC_MAGIC, 0, char *)

// IOCTL: set memory buffers
#define IOCTL_H264_ENC_BUFFERS_SET _IOW(H264ENC_IOC_MAGIC, 1, char *)

// IOCTL: how many more lines are available in input buffer
#define IOCTL_H264_ENC_FETCH _IOW(H264ENC_IOC_MAGIC, 2, uint32_t)

// IOCTL: invokes bistream alarm address shift
#define IOCTL_H264_ENC_BS_ALARM_SHIFT _IOW(H264ENC_IOC_MAGIC, 3, uint32_t)

// IOCTL: get current HW status
#define IOCTL_H264_ENC_STATUS_GET _IOR(H264ENC_IOC_MAGIC, 4, char*)

// IOCTL: stops the encoding sequence
#define IOCTL_H264_ENC_STOP _IO(H264ENC_IOC_MAGIC, 5)

///////////////////////////////////////////
//
// IOCTL cmds processing code
//

// only for kernel space
#ifdef __KERNEL__

long H264EncIoctl(struct file *apFile,	/* ditto */
		 unsigned int aIoctlNum,	/* number and param for ioctl */
		 unsigned long aIoctlParam);

#endif // ifdef __KERNEL__

#endif // ifndef H264_ENC_IOCTL_H