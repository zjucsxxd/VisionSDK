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
* \file     h264enc.h
* \brief    declarations for H264 Encoder driver
* \author   Tomas Babinec
* \version  0.1
* \date     20.6.2014
* \note
****************************************************************************/

#ifndef H264ENC_H
#define H264ENC_H

#include <linux/ioctl.h>

/*****************************************************************************
* MACRO definitions
*****************************************************************************/

#define H264ENC_IRQ_FPGA 	 88

#define H264ENC_ERROR_SIGNAL            42
#define H264ENC_BIT_ALARM_SIGNAL        43
#define H264ENC_PIX_DATA_LOW_SIGNAL     44
#define H264ENC_FRAME_DONE_SIGNAL       45

#define H264ENC_DRV_SUCCESS 0
#define H264ENC_DRV_FAILURE -1

// name of the device file
#define H264ENC_DEVICE_NAME "h264enc"

// magic number for fDMA driver
#define H264ENC_IOC_MAGIC 'h' + 'e'

// *** H264ENC registers ***
#define H264ENC_BASE		0x6004B000
#define H264ENC_BASE_PRO	0x4002B000
#define H264ENC_SIZE 		0x288

#include "h264enc_ioctl.h"

#endif