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
 * @file apexdriver_ioctl.h
 *
 * \\author Rostislav Hulik (Freescale Semiconductor)
 * \date 28. 11. 2013
 *
 */
#ifndef APEXDRIVER_IOCTL__H
#define APEXDRIVER_IOCTL__H

#include <linux/fs.h>
#include "apexdriver_cmem_if_hal.h"
#include "apexdriver_apu_hal.h"
#include "apexdriver_apu_microkernel_hal.h"
#include "apexdriver_seq_hal.h"
#include "apexdriver_global_hal.h"
#include "apexdriver_mcdma_hal.h"
#include "apexdriver_hw_reg_user.h"
/*==============================================================================*/
/* IOCTL code prefix 								                            */
#define APEXDRIVER_CODE_CMEMIF		'C'
#define APEXDRIVER_CODE_APU		    'I'
#define APEXDRIVER_CODE_APUMK		'M'
#define APEXDRIVER_CODE_SEQ			'S'
#define APEXDRIVER_CODE_GLOBAL		'G'
#define APEXDRIVER_CODE_MCDMA		'A'


/*==============================================================================*/
#define APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG	              _IOW(APEXDRIVER_CODE_CMEMIF,  0, int32_t)
typedef struct
{
  int 			            lApexID;
  CMEM_IF_APU_CFG           lApuCfg;
} APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE;

#define APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START	      _IOW(APEXDRIVER_CODE_CMEMIF,  1, int32_t)
typedef struct
{
  int                       lApexID;
  int32_t                   apuid;
  uint32_t                  address;
} APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE;

#define APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START	      _IOW(APEXDRIVER_CODE_CMEMIF,  2, int32_t)
typedef struct
{
  int                       lApexID;
  int32_t                   apuid;
  uint32_t                  address;
} APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE;

/*==============================================================================*/
#define APEXDRIVER_APU_HAL_LOADSEGMENT   	      _IOW(APEXDRIVER_CODE_APU,  0, int32_t)
typedef struct
{
  int                       apexID;             
  int32_t                   apuid;
  const LOAD_SEGMENT_t*     seg_addr;
  int32_t                   ret;
} APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE;

#define APEXDRIVER_APU_HAL_ENABLE	              _IOW(APEXDRIVER_CODE_APU,  1, int32_t)
typedef struct
{
  int                       apexID;
  unsigned int              APUID;
  unsigned int              isEnable;
} APEXDRIVER_APU_HAL_ENABLE_TYPE;

#define APEXDRIVER_APU_HAL_RESET	              _IOW(APEXDRIVER_CODE_APU,  4, int32_t)
typedef struct
{
  int                       apexID;
  unsigned int              APUID;
} APEXDRIVER_APU_HAL_RESET_TYPE;

#define APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ	  _IOW(APEXDRIVER_CODE_APU,  2, int32_t)
typedef struct
{
  int                       apexID;
  const LOAD_SEGMENT_t*     seg_addr;
  int32_t*                  pCmemReq;
  int32_t*                  pDmemReq;
  int32_t*                  pPmemReq;
} APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE;

#define APEXDRIVER_APU_HAL_RETMEMSIZES	          _IOW(APEXDRIVER_CODE_APU,  3, int32_t)
typedef struct
{
  int                       apexID;
  CMEM_IF_APU_CFG           apuconfig;
  int32_t*                  pSmemSize;
  int32_t*                  pCmemSize;
  int32_t                   ret;
} APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE;

/*==============================================================================*/
#define APEXDRIVER_APUMK_HAL_HOST_COM_RX	          _IOW(APEXDRIVER_CODE_APUMK,  0, int32_t)
typedef struct
{
  int                       apexID;
  int                       apuid;
  int32_t*                  msg;
  int32_t                   ret;
} APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE;

#define APEXDRIVER_APUMK_HAL_HOST_COM_TX	          _IOW(APEXDRIVER_CODE_APUMK,  1, int32_t)
typedef struct
{
  int                       apexID;
  int                       apuid;
  int32_t                   msg;
  int32_t                   ret;
} APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE;

#define APEXDRIVER_APUMK_HAL_SEND_CMD	          _IOW(APEXDRIVER_CODE_APUMK,  2, int32_t)
typedef struct
{
  int                       apexID;
  int32_t                   apu_id;
  int32_t                   kernel_id;
  int32_t                   num_params;
  const int32_t*            param_list;
  int32_t                   ret;
} APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE;

/*==============================================================================*/
#define APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS	          _IOW(APEXDRIVER_CODE_SEQ, 0, int32_t)
typedef struct
{
  int                       apexID;
  int                       lMask;
} APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE;

#define APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS	          _IOW(APEXDRIVER_CODE_SEQ, 1, int32_t)
typedef struct
{
  int                       apexID;
  int32_t                   ret;
} APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE;

#define APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS	          _IOW(APEXDRIVER_CODE_SEQ, 2, int32_t)
typedef struct
{
  int                       apexID;
  int                       lMask;
} APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE;

/*==============================================================================*/
#define APEXDRIVER_GLOBAL_HAL_RETHWVERSION	          _IOW(APEXDRIVER_CODE_GLOBAL, 0, int32_t)
typedef struct
{
  int                       apexID;
  int                       ret;
} APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE;

#define APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE	          _IOW(APEXDRIVER_CODE_GLOBAL, 1, int32_t)
typedef struct
{
  int                       apexID;
  APEX2_INTERRUPT_BITS      intBit;
  int                       ret;
} APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE;

#define APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE	          _IOW(APEXDRIVER_CODE_GLOBAL, 2, int32_t)
typedef struct
{
  int                       apexID;
  APEX2_INTERRUPT_BITS      intBit;
  int                       ret;
} APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE;

#define APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR	          _IOW(APEXDRIVER_CODE_GLOBAL, 3, int32_t)
typedef struct
{
  int                       apexID;
  HW_REG_ID                 lHwRegId;
  void *                    ret;
} APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE;


/*==============================================================================*/
#define APEXDRIVER_MCDMA_HAL_SET_MEM_FILL	          _IOW(APEXDRIVER_CODE_MCDMA, 0, int32_t)
typedef struct
{
  int apexID;
  unsigned int FillWord0;
  unsigned int FillWord1;
  unsigned int FillWord2;
  unsigned int FillWord3;
} APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE;

#define APEXDRIVER_MCDMA_HAL_SEQ_LL	                  _IOW(APEXDRIVER_CODE_MCDMA, 1, int32_t)
typedef struct
{
  int apexID;
  unsigned int ChannelN;
  unsigned int LinkedListAddr;
} APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE;

#define APEXDRIVER_MCDMA_HAL_START       	          _IOW(APEXDRIVER_CODE_MCDMA, 2, int32_t)
typedef struct
{
  int apexID;
  unsigned int ChannelN;
} APEXDRIVER_MCDMA_HAL_START_TYPE;

#define APEXDRIVER_MCDMA_HAL_WAIT	                  _IOW(APEXDRIVER_CODE_MCDMA, 3, int32_t)
typedef struct
{
  int apexID;
  unsigned int ChannelN;
} APEXDRIVER_MCDMA_HAL_WAIT_TYPE;

#define APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE	  _IOW(APEXDRIVER_CODE_MCDMA, 4, int32_t)
typedef struct
{
  int apexID;
  unsigned int ChannelN;
} APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE;

#define APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF     	  _IOW(APEXDRIVER_CODE_MCDMA, 5, int32_t)
typedef struct
{
  int apexID;
  int32_t    lApuId;
  HW_REG_ID* lpCmemBroadcastReg;
  uint32_t*   lpPmemOffsetInBytes;
  uint32_t*   lpDmemOffsetInBytes;
  uint32_t*   lpDmemSizeInBytes;
} APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE;



/**
 * APEX driver ioctl function header
 * @param filep File descriptor
 * @param cmd   Command ID 
 * @param arg   Passed argument
 * @return 0 on success, error code otherwise
 */
long apexdriver_ioctl(struct file *filep, unsigned int cmd, unsigned long arg);

#endif