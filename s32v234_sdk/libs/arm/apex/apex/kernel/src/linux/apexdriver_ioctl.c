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
 * @file apexdriver_ioctl.c
 *
 * \\author Rostislav Hulik (Freescale Semiconductor)
 * \date 28. 11. 2013
 *
 */
#include <apexdriver_ioctl.h>
 
#include <asm/uaccess.h>

 
/*======================================================================================*/
/* Function processes CMEM IF calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_cmemif_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG
    //////////////////////////////////////////////////////
    case APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE *)arg, sizeof(APEXDRIVER_CMEM_IF_HAL_SET_APU_CFG_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_cmem_if_hal_set_apu_cfg(aux.lApexID, aux.lApuCfg);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START
    //////////////////////////////////////////////////////
    case APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE *)arg, sizeof(APEXDRIVER_CMEM_IF_HAL_SET_APU_PMEM_START_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_cmem_if_hal_set_apu_pmem_start(aux.lApexID, aux.apuid, aux.address);
    }
    break;
	
	//////////////////////////////////////////////////////
    // APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START
    //////////////////////////////////////////////////////
    case APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START:
    {
      APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE *)arg, sizeof(APEXDRIVER_CMEM_IF_HAL_SET_APU_DMEM_START_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_cmem_if_hal_set_apu_dmem_start(aux.lApexID, aux.apuid, aux.address);
    }
    break;
    
    //////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}

/*======================================================================================*/
/* Function processes APU calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_apu_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_APU_HAL_LOADSEGMENT
    //////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_LOADSEGMENT:
    {
      APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE *)arg, sizeof(APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_apu_hal_LoadSegment(aux.apexID, aux.apuid, aux.seg_addr);
	  
	  if (copy_to_user((APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE *)arg, &aux, sizeof(APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
	//////////////////////////////////////////////////////
    // APEXDRIVER_APU_HAL_ENABLE
    //////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_ENABLE:
    {
      APEXDRIVER_APU_HAL_ENABLE_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APU_HAL_ENABLE_TYPE *)arg, sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_apu_hal_Enable(aux.apexID, aux.APUID, aux.isEnable);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_APU_HAL_RESET
    //////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_RESET:
    {
      APEXDRIVER_APU_HAL_ENABLE_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APU_HAL_RESET_TYPE *)arg, sizeof(APEXDRIVER_APU_HAL_RESET_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_apu_hal_Reset(aux.apexID, aux.APUID);
    }
    break;
	
	//////////////////////////////////////////////////////
    // APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ
    //////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ:
    {
      APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE *)arg, sizeof(APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE)) != 0) 
	return -EIO;
      
      apexdriver_apu_hal_QueryLoad_MEM_REQ(aux.apexID, aux.seg_addr, aux.pCmemReq, aux.pDmemReq, aux.pPmemReq);
    }
    break;
	
	//////////////////////////////////////////////////////
    // APEXDRIVER_APU_HAL_RETMEMSIZES
    //////////////////////////////////////////////////////
    case APEXDRIVER_APU_HAL_RETMEMSIZES:
    {
      APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE *)arg, sizeof(APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_apu_hal_RetMemSizes(aux.apexID, aux.apuconfig, aux.pSmemSize, aux.pCmemSize);
	  
	  if (copy_to_user((APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE *)arg, &aux, sizeof(APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE)) != 0) 
		return -EIO;
    }
    break;

    //////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}

/*======================================================================================*/
/* Function processes APU Microkernel calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_apumk_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_APUMK_HAL_HOST_COM_RX
    //////////////////////////////////////////////////////
    case APEXDRIVER_APUMK_HAL_HOST_COM_RX:
    {
      APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE *)arg, sizeof(APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_apumk_hal_host_com_rx(aux.apexID, aux.apuid, aux.msg);
	  
	  if (copy_to_user((APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE *)arg, &aux, sizeof(APEXDRIVER_APUMK_HAL_HOST_COM_RX_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
	//////////////////////////////////////////////////////
    // APEXDRIVER_APUMK_HAL_HOST_COM_TX
    //////////////////////////////////////////////////////
    case APEXDRIVER_APUMK_HAL_HOST_COM_TX:
    {
      APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE *)arg, sizeof(APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_apumk_hal_host_com_tx(aux.apexID, aux.apuid, aux.msg);
	  
	  if (copy_to_user((APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE *)arg, &aux, sizeof(APEXDRIVER_APUMK_HAL_HOST_COM_TX_TYPE)) != 0) 
		return -EIO;
    }
    break;
	
	//////////////////////////////////////////////////////
    // APEXDRIVER_APUMK_HAL_SEND_CMD
    //////////////////////////////////////////////////////
    case APEXDRIVER_APUMK_HAL_SEND_CMD:
    {
      APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE *)arg, sizeof(APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_apumk_hal_send_cmd(aux.apexID, aux.apu_id, aux.kernel_id, aux.num_params, aux.param_list);
	  
	  if (copy_to_user((APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE *)arg, &aux, sizeof(APEXDRIVER_APUMK_HAL_SEND_CMD_TYPE)) != 0) 
		return -EIO;
    }
    break;

	//////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}

/*======================================================================================*/
/* Function processes Sequencer calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_seq_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS
    //////////////////////////////////////////////////////
    case APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE *)arg, sizeof(APEXDRIVER_SEQ_HAL_CLEAR_INTERRUPTS_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_seq_hal_clear_interrupts(aux.apexID, aux.lMask);
    }
    break;
    
	//////////////////////////////////////////////////////
    // APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS
    //////////////////////////////////////////////////////
    case APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE *)arg, sizeof(APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_seq_hal_query_interrupts(aux.apexID);
	  
	  if (copy_to_user((APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE *)arg, &aux, sizeof(APEXDRIVER_SEQ_HAL_QUERY_INTERRUPTS_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
	//////////////////////////////////////////////////////
    // APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS
    //////////////////////////////////////////////////////
    case APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS:
    {
      APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE *)arg, sizeof(APEXDRIVER_SEQ_HAL_MASK_INTERRUPTS_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_seq_hal_mask_interrupts(aux.apexID, aux.lMask);
	  
    }
    break;
	
	
	//////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}

/*======================================================================================*/
/* Function processes Global calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_global_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_GLOBAL_HAL_RETHWVERSION
    //////////////////////////////////////////////////////
    case APEXDRIVER_GLOBAL_HAL_RETHWVERSION:
    {
      APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE *)arg, sizeof(APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_global_hal_RetHwVersion(aux.apexID);
	  
	  if (copy_to_user((APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE *)arg, &aux, sizeof(APEXDRIVER_GLOBAL_HAL_RETHWVERSION_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE
    //////////////////////////////////////////////////////
    case APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE:
    {
      APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE *)arg, sizeof(APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_global_hal_Apex2GlobalInterruptDisable(aux.apexID, aux.intBit);
	  
	  if (copy_to_user((APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE *)arg, &aux, sizeof(APEXDRIVER_GLOBAL_HAL_IRQ_DISABLE_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE
    //////////////////////////////////////////////////////
    case APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE:
    {
      APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE *)arg, sizeof(APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = apexdriver_global_hal_Apex2GlobalInterruptEnable(aux.apexID, aux.intBit);
	  
	  if (copy_to_user((APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE *)arg, &aux, sizeof(APEXDRIVER_GLOBAL_HAL_IRQ_ENABLE_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR
    //////////////////////////////////////////////////////
    case APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR:
    {
      APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE *)arg, sizeof(APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE)) != 0) 
		return -EIO;
      
      aux.ret = ReturnPhysicalHwPtr(aux.apexID, aux.lHwRegId);
	  
	  if (copy_to_user((APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE *)arg, &aux, sizeof(APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE)) != 0) 
		return -EIO;
    }
    break;
    
	//////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}

extern void apexdriver_RetApuInfoFromCmemIf (int apexID, int32_t    lApuId,
                           HW_REG_ID* lpCmemBroadcastReg,
                           uint32_t*   lpPmemOffsetInBytes,
                           uint32_t*   lpDmemOffsetInBytes,
                           uint32_t*   lpDmemSizeInBytes);

/*======================================================================================*/
/* Function processes MCDMA calls (called from IOCTL function)			*/
/*======================================================================================*/
int64_t process_mcdma_calls(unsigned int cmd, unsigned long arg)
{
  switch(cmd) 
  {
    //////////////////////////////////////////////////////
    // APEXDRIVER_MCDMA_HAL_SET_MEM_FILL
    //////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_SET_MEM_FILL:
    {
      APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE *)arg, sizeof(APEXDRIVER_MCDMA_HAL_SET_MEM_FILL_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_mcdma_hal_set_memory_fill_words( aux.apexID, aux.FillWord0, aux.FillWord1, aux.FillWord2, aux.FillWord3);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_MCDMA_HAL_SEQ_LL
    //////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_SEQ_LL:
    {
      APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE *)arg, sizeof(APEXDRIVER_MCDMA_HAL_SEQ_LL_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_mcdma_hal_program_seq_linkedlist(aux.apexID, aux.ChannelN, aux.LinkedListAddr);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_MCDMA_HAL_START
    //////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_START:
    {
      APEXDRIVER_MCDMA_HAL_START_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_MCDMA_HAL_START_TYPE *)arg, sizeof(APEXDRIVER_MCDMA_HAL_START_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_mcdma_hal_start(aux.apexID, aux.ChannelN);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_MCDMA_HAL_WAIT
    //////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_WAIT:
    {
      APEXDRIVER_MCDMA_HAL_WAIT_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_MCDMA_HAL_WAIT_TYPE *)arg, sizeof(APEXDRIVER_MCDMA_HAL_WAIT_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_mcdma_hal_wait(aux.apexID, aux.ChannelN);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE
    //////////////////////////////////////////////////////
    case APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE:
    {
      APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE *)arg, sizeof(APEXDRIVER_MCDMA_HAL_INTERRUPTCLEAR_CH_DONE_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_mcdma_hal_interruptclear_ch_done(aux.apexID, aux.ChannelN);
    }
    break;
    
    //////////////////////////////////////////////////////
    // APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF
    //////////////////////////////////////////////////////
    case APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF:
    {
      APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE aux;
      
      if (copy_from_user(&aux, (APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE *)arg, sizeof(APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE)) != 0) 
		return -EIO;
      
      apexdriver_RetApuInfoFromCmemIf (aux.apexID, aux.lApuId, aux.lpCmemBroadcastReg, aux.lpPmemOffsetInBytes, aux.lpDmemOffsetInBytes, aux.lpDmemSizeInBytes);
    }
    break;

	//////////////////////////////////////////////////////
    // Default - no command
    //////////////////////////////////////////////////////
    default:
      return -ENOTTY;
      break;
  }
  return 0;
}


long apexdriver_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
  int64_t status;
  
  status = process_cmemif_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
  status = process_apu_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
  status = process_apumk_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
  status = process_seq_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
  status = process_global_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
  status = process_mcdma_calls(cmd, arg);
  if (status == 0 || status == -EIO) return status;
  
   
  return status;
}