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
 * @file apexdriver_dev.c
 *
 * \\author Rostislav Hulik (Freescale Semiconductor)
 * \date 17. 12. 2013
 *
 */
#include <bsp.h>
#include <INTEGRITY.h>
#include <memoryspace.h>
#include <buildmemtable.h>

#include <devtree_bus_utils.h>

#include <apexdriver_iodev.h>
#include <apexdriver_hw_reg_user.h>

/*======================================================================================*/
/* IODevice vector for APEX 								*/
struct IODeviceVectorStruct apex_iodevice_vector;
struct IORequestStruct apex_requests[16];

/*======================================================================================*/
/* Write register IODevice function							*/
static Error apexdriver_writeregister(IODeviceVector io, Value id, Value val)
{
  switch (id)
  {
    /*case APEXDRIVER_REGW_RESET_ALL:
      apexdriver_reset_all((unsigned int)val);
      break;*/
    
    default:
      return Failure;
  }
  return Success;
}

/*======================================================================================*/
/* Write transfer IODevice function							*/
static Error apexdriver_writetransfer(IODeviceVector io, IORequest iorequest, Value count, const volatile Value *data)
{
  unsigned int *ptr = (unsigned int *)*data;
  unsigned int id = (unsigned int)*ptr;
  switch (id)
  {
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE *data_struct = (APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE *)ptr;
      apexdriver_cmem_if_hal_set_apu_cfg(data_struct->lApexID, data_struct->lApuCfg);
      break;
    }
    
    case APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE *data_struct = (APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE *)ptr;
      apexdriver_cmem_if_hal_set_apu_pmem_start(data_struct->lApexID, data_struct->apuid, data_struct->address);
      break;
    }

    case APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE *data_struct = (APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE *)ptr;
      apexdriver_cmem_if_hal_set_apu_dmem_start(data_struct->lApexID, data_struct->apuid, data_struct->address);
      break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_LOADSEGMENT:
    {
      APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE *data_struct = (APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE *)ptr;
      data_struct->ret = apexdriver_apu_hal_LoadSegment(data_struct->apexID, data_struct->apuid, data_struct->seg_addr);
      break;
    }	
    
    case APEXDRIVER_APU_HAL_ENABLE:
    {
      APEXDRIVER_APU_HAL_ENABLE_TYPE *data_struct = (APEXDRIVER_APU_HAL_ENABLE_TYPE *)ptr;
      apexdriver_apu_hal_Enable(data_struct->apexID, data_struct->APUID, data_struct->isEnable);
      break;
    }
    
    case APEXDRIVER_APU_HAL_RESET:
    {
      APEXDRIVER_APU_HAL_RESET_TYPE *data_struct = (APEXDRIVER_APU_HAL_RESET_TYPE *)ptr;
      apexdriver_apu_hal_Reset(data_struct->apexID, data_struct->APUID);
      break;
    }
    
    case APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ:
    {
      APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE *data_struct = (APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE *)ptr;
      apexdriver_apu_hal_QueryLoad_MEM_REQ(data_struct->apexID, data_struct->seg_addr, data_struct->pCmemReq, data_struct->pDmemReq, data_struct->pPmemReq);
      break;
    }
    
    case APEXDRIVER_APU_HAL_RETMEMSIZES:
    {
      APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE *data_struct = (APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE *)ptr;
      data_struct->ret = apexdriver_apu_hal_RetMemSizes(data_struct->apexID, data_struct->apuconfig, data_struct->pSmemSize, data_struct->pCmemSize);
      break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_APUMK_HAL_HOST_COM_RX:
    {
      APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE *data_struct = (APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE *)ptr;
      data_struct->ret = apexdriver_apumk_hal_host_com_rx(data_struct->apexID, data_struct->apuid, data_struct->msg);
      break;
    }
    
    case APEXDRIVER_APUMK_HAL_HOST_COM_TX:
    {
      APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE *data_struct = (APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE *)ptr;
      data_struct->ret = apexdriver_apumk_hal_host_com_tx(data_struct->apexID, data_struct->apuid, data_struct->msg);
      break;
    }
    
    case APEXDRIVER_APUMK_HAL_SEND_CMD:
    {
      APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE *data_struct = (APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE *)ptr;
      data_struct->ret = apexdriver_apumk_hal_send_cmd(data_struct->apexID, data_struct->apu_id, data_struct->kernel_id, data_struct->num_params, data_struct->param_list);
      break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE *data_struct = (APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE *)ptr;
      apexdriver_seq_hal_clear_interrupts(data_struct->apexID, data_struct->lMask);
      break;
    }
    
    case APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE *data_struct = (APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE *)ptr;
      data_struct->ret = apexdriver_seq_hal_query_interrupts(data_struct->apexID);
      break;
    }
    
    case APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE *data_struct = (APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE *)ptr;
      apexdriver_seq_hal_mask_interrupts(data_struct->apexID, data_struct->lMask);
      break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_GLOBAL_HAL_RETHWVERSION:
    {
      APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE *data_struct = (APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE *)ptr;
      data_struct->ret = apexdriver_global_hal_RetHwVersion(data_struct->apexID);
      break;
    }
    
    case APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE:
    {
      APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE *data_struct = (APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE *)ptr;
      data_struct->ret = apexdriver_global_hal_Apex2GlobalInterruptDisable(data_struct->apexID, data_struct->intBit);
      break;
    }
    
    case APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE:
    {
      APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE *data_struct = (APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE *)ptr;
      data_struct->ret = apexdriver_global_hal_Apex2GlobalInterruptEnable(data_struct->apexID, data_struct->intBit);
      break;
    }
    
    case APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR:
    {
      APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE *data_struct = (APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE *)ptr;
      data_struct->ret = ReturnPhysicalHwPtr(data_struct->apexID, data_struct->lHwRegId);
      break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_SET_MEM_FILL:
    {
      APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE *data_struct = (APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE *)ptr;
      apexdriver_mcdma_hal_set_memory_fill_words( data_struct->apexID, data_struct->FillWord0, data_struct->FillWord1, data_struct->FillWord2, data_struct->FillWord3);
      break;
    }
    
    case APEXDRIVER_MCDMA_HAL_SEQ_LL:
    {
      APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE *data_struct = (APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE *)ptr;
      apexdriver_mcdma_hal_program_seq_linkedlist(data_struct->apexID, data_struct->ChannelN, data_struct->LinkedListAddr);
      break;
    }
    
    case APEXDRIVER_MCDMA_HAL_START:
    {
      APEXDRIVER_MCDMA_HAL_START_TYPE *data_struct = (APEXDRIVER_MCDMA_HAL_START_TYPE *)ptr;
      apexdriver_mcdma_hal_start(data_struct->apexID, data_struct->ChannelN);
      break;
    }
    
    case APEXDRIVER_MCDMA_HAL_WAIT:
    {
      APEXDRIVER_MCDMA_HAL_WAIT_TYPE *data_struct = (APEXDRIVER_MCDMA_HAL_WAIT_TYPE *)ptr;
      apexdriver_mcdma_hal_wait(data_struct->apexID, data_struct->ChannelN);
      break;
    }
    
    case APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE:
    {
      APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE *data_struct = (APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE *)ptr;
      apexdriver_mcdma_hal_interruptclear_ch_done(data_struct->apexID, data_struct->ChannelN);
      break;
    }
    
    case APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF:
    {
      APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE *data_struct = (APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE *)ptr;
      apexdriver_RetApuInfoFromCmemIf (data_struct->apexID, data_struct->lApuId, data_struct->lpCmemBroadcastReg, data_struct->lpPmemOffsetInBytes, data_struct->lpDmemOffsetInBytes, data_struct->lpDmemSizeInBytes);
      break;
    }
    
    default:
      return Failure;
  }
  return Success;
}

#define APEX_0_BASE 0x74000000
#define APEX_1_BASE 0x78000000

/*======================================================================================*/
/* Transfer start IODevice function							*/
static Error apexdriver_transferstart(IODeviceVector TheIODeviceVector, Value flags, const volatile Value arguments[4])
{
  StartIORequest(&apex_requests[0]);
  return Success;
}

/*======================================================================================*/
/* IODevice initialization								*/
void apexdriver_iodevice_init(void)
{
  int i;
  #ifndef __S32V234
  // Map the memory
  ATAGS_KernelMap((APEX_0_BASE), (APEX_0_BASE), 0x10000000, MEMORY_RW | MEMORY_VOLATILE, Other_MemoryType);
  ATAGS_KernelMap((APEX_1_BASE), (APEX_1_BASE), 0x10000000, MEMORY_RW | MEMORY_VOLATILE, Other_MemoryType);
  #endif
  
  // IODevice functions
  apex_iodevice_vector.WriteRegister = apexdriver_writeregister;
  apex_iodevice_vector.TransferStart = apexdriver_transferstart;
  apex_iodevice_vector.TransferWrite = apexdriver_writetransfer;

  RegisterIODeviceVector(&apex_iodevice_vector, "APEXIODevice");

  for (i=0; i < 16; ++i)
	  InitializeIORequest(&apex_iodevice_vector, &apex_requests[i], IOREQUEST_STANDARD);

  // Init registers
  InitVirtualHwPtrArray();
  consolestring("APEX Driver loaded.\n");
}
 
typedef void (*voidfunc)();
voidfunc __ghsentry_bspuserinit_apex_regmap = apexdriver_iodevice_init;

#pragma ghs alias __ghsautoimport_apex_regmap __ghsentry_bspuserinit_apex_regmap


