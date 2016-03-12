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
* \file     h264enc_func.h
* \brief    declaration of H264 Encoder driver internal functionality
* \author   Tomas Babinec
* \version  0.1
* \date     20.6.2014
* \note
****************************************************************************/

#ifndef H264ENC_FUNC_H
#define H264ENC_FUNC_H

#include <linux/interrupt.h>    // For interrupts
#include "h264enc.h"

// for simple access to registers' fields

#define REG_FIELD_READ(_reg, _field)\
  (((_reg) & _reg ## _ ## _field) >> (_reg ## _ ## _field ## _LSB))
  
#define REG_FIELD_WRITE(_reg, _field, _value)\
  (_reg = (_reg & (! _reg ## _ ## _field)) | (_reg ## _ ## _field) & (_value << (_reg ## _ ## _field ## _LSB)))

#include "h264enc_types.h"

#ifdef __KERNEL__
/*****************************************************************************
* functions (prototypes)
*****************************************************************************/

/****************************************************************************/
/** Sets up the internal functionality of the H264 Encodera kernel module. Initializes
* H264 Encoder related resources.
* 
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
int32_t H264ENC_Setup(void);


/****************************************************************************/
/** Releases all H264 Encoder related resources.
* 
* \return H264ENC_DRV_SUCCESS if all ok, otherwise H264ENC_DRV_FAILURE
*
*****************************************************************************/
void H264ENC_Close(void);


/****************************************************************************/
/** H264ENC DONE IRQ handler.
* 
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return IRQ_HANDLED when done
*
*****************************************************************************/
irqreturn_t H264ENC_DoneIrqHandler(int32_t aIrq, void *apDev_id);

/****************************************************************************/
/** Applies given configuration to the encoder HW.
* 
* \param apcConfig configuration parameter values
*
*****************************************************************************/
void H264ENC_Config(const H264ENC_Config_t *apConfig);

/****************************************************************************/
/** Sets specified buffer addresses to the register values.
*   Sets up the input (Y, U, V) and output (bitstream data) buffers.
* 
* \param apcBuffers pointer to buffer defining structure
*
*****************************************************************************/
void H264ENC_BuffersSet(const H264ENC_Buffers_t *apBuffers);

/****************************************************************************/
/** Assigns callback function to specific events.
* 
* \param apcClbck   pointer structure with calback pointers filled in. NULL
*                   values are replaced by driver default callbacks.
*
*****************************************************************************/
void H264ENC_CallbackSet(const H264ENC_Callbacks_t *apClbck);

/****************************************************************************/
/** Provides current encoding status description.
* 
* \param apcStatus   pointer to status describing structure
*
*****************************************************************************/
void H264ENC_StatusGet(H264ENC_Status_t *apStatus);

/****************************************************************************/
/** Remembers more lines are ready in the input buffer.
* 
* \param aMoreLines number of new lines in input buffer
*
*****************************************************************************/
void H264ENC_LinesFetch(uint32_t aMoreLines);

/****************************************************************************/
/** Shifts bitstream buffer alarm address.
*  Should be used after the old data have been poped and can be overwritten.
* 
* \param aMoreLines number of new lines in input buffer
*
*****************************************************************************/
void H264ENC_BitstreamAlarmShift(uint32_t aAlarmShift);


#endif // ifdef __KERNEL__

#endif // H264ENC_FUNC_H