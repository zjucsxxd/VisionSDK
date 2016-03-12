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
* \file     csi_ioctl.h
* \brief    ioctl related declarations for CSI driver
* \author   Tomas Babinec
* \version  0.1
* \date     21. September 2015
* \note
****************************************************************************/

#ifndef CSI_IOCTL_H
#define CSI_IOCTL_H

#include <linux/fs.h>		// required for the struct file declaration

///////////////////////////////////////////
//
// IOCTL command codes numbers allocation
//

// IOCTL: reserve CSI interface
#define IOCTL_CSI_CONFIG _IOW(CSI_IOC_MAGIC, 0, char *)
#define IOCTL_SONY_REG_CONFIG _IOR(CSI_IOC_MAGIC, 3, uint32_t)
#define IOCTL_CSI_START _IOW(CSI_IOC_MAGIC, 4, uint32_t)
#define IOCTL_CSI_STOP _IOW(CSI_IOC_MAGIC, 5, uint32_t)
#define IOCTL_SONY_START _IOW(CSI_IOC_MAGIC, 6, uint32_t)
#define IOCTL_SONY_STOP _IOW(CSI_IOC_MAGIC, 7, uint32_t)
#define IOCTL_SONY_EXP_STATUS_GET _IOW(CSI_IOC_MAGIC, 8,uint32_t)
#define IOCTL_SONY_EXP_GET _IOWR(CSI_IOC_MAGIC, 9, SONY_Exposure_t*)
#define IOCTL_SONY_EXP_SET _IOWR(CSI_IOC_MAGIC, 10, SONY_Exposure_t*)
#define IOCTL_SONY_GEO_GET _IOWR(CSI_IOC_MAGIC, 11, SONY_Geometry_t*)
#define IOCTL_SONY_GEO_SET _IOWR(CSI_IOC_MAGIC, 12, SONY_Geometry_t*)
#define IOCTL_OV10640_REG_CONFIG _IOR(CSI_IOC_MAGIC, 13, uint32_t)
#define IOCTL_OV10640_START _IOW(CSI_IOC_MAGIC, 14, uint32_t)
#define IOCTL_OV10640_STOP _IOW(CSI_IOC_MAGIC, 15, uint32_t)
#define IOCTL_MAXIM_INIT _IOR(CSI_IOC_MAGIC, 16, uint32_t)
#define IOCTL_MAXIM_START _IOW(CSI_IOC_MAGIC, 17, uint32_t)
#define IOCTL_MAXIM_STOP _IOW(CSI_IOC_MAGIC, 18, uint32_t)

#if 0
// IOCTL: transaction configuration
#define IOCTL_FDMA_TD_CONFIG _IOW(FDMA_IOC_MAGIC, 1, char *)

// IOCTL: get copy of current fDMA registers
#define IOCTL_FDMA_SEQ_MODE_GET _IO(FDMA_IOC_MAGIC, 2)
#endif 
///////////////////////////////////////////
//
// IOCTL cmds processing code
//

// only for kernel space
#ifdef __KERNEL__

long CsiIoctl(struct file *apFile,	/* ditto */
    unsigned int aIoctlNum,	/* number and param for ioctl */
    unsigned long aIoctlParam);

#endif

#endif // #ifndef CSI_IOCTL_H

/* EOF */