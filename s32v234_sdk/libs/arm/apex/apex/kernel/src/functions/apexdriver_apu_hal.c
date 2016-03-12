/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2012 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

// Include files.
// Power Up and Reset
#include <apexdriver_global_hal.h>
#include <apexdriver_apu_hal.h>
#include <cmem_array_map.h>
#include <apexdriver_cmem_hal.h>
#include <apexdriver_cmem_if_hal.h>
#include <apexdriver_hw_reg_user.h>
#ifdef __KERNEL_MODULE
	#include <linux/module.h>
	#include <linux/string.h>
#else
	#include <string.h> //memcpy	
#endif


volatile unsigned int DMEM_APU_OFFSET[APU_MAX_NUMBER_OF_APUS] = {APU_0_DMEM_OFFSET,
                                                                 APU_1_DMEM_OFFSET,
                                                                 APU_2_DMEM_OFFSET,
                                                                 APU_3_DMEM_OFFSET};

volatile unsigned int IMEM_APU_OFFSET[APU_MAX_NUMBER_OF_APUS] = {APU_0_IMEM_OFFSET,
                                                                 APU_1_IMEM_OFFSET,
                                                                 APU_2_IMEM_OFFSET,
                                                                 APU_3_IMEM_OFFSET};

volatile unsigned int VMEM_APU_OFFSET[APU_MAX_NUMBER_OF_APUS] = {APU_0_VMEM_OFFSET,
                                                                 APU_1_VMEM_OFFSET,
                                                                 APU_2_VMEM_OFFSET,
                                                                 APU_3_VMEM_OFFSET};
                                                   
volatile APU_COMM *apu_com[APU_MAX_NUMBER_OF_APUS] = { (volatile APU_COMM *)0 };

void apexdriver_RetApuInfoFromCmemIf (int apexID, int32_t    lApuId,
                           HW_REG_ID* lpCmemBroadcastReg,
                           uint32_t*   lpPmemOffsetInBytes,
                           uint32_t*   lpDmemOffsetInBytes,
                           uint32_t*   lpDmemSizeInBytes)
{
   CMEM_IF_APU_CFG lCmemIfCfg = apexdriver_cmem_if_hal_query_apu_cfg(apexID);
   uint32_t lPmemOffset = apexdriver_cmem_if_hal_query_apu_pmem_start(apexID, lApuId);
   uint32_t lDmemOffset = apexdriver_cmem_if_hal_query_apu_dmem_start(apexID, lApuId);

   *lpPmemOffsetInBytes = lPmemOffset;
   *lpDmemOffsetInBytes = lDmemOffset;

   switch(lCmemIfCfg)
   {
   case CFG_321__APU_0_CU_0_31_SMEM_0_1:
      *lpCmemBroadcastReg = HW_REG_CMEM_BOC_31_00;
      *lpDmemSizeInBytes = (lPmemOffset >= lDmemOffset) ? lPmemOffset-lDmemOffset : (1024*64)-lDmemOffset;
      break;
   case CFG_642__APU_0_CU_0_63_SMEM_0_3:
      *lpCmemBroadcastReg = HW_REG_CMEM_BOC_63_00;
      *lpDmemSizeInBytes = (lPmemOffset >= lDmemOffset) ? lPmemOffset-lDmemOffset : (1024*128)-lDmemOffset;
      break;
   case CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3:
      if (0 == lApuId)
      {
         *lpCmemBroadcastReg = HW_REG_CMEM_BOC_31_00;
         *lpDmemSizeInBytes = (lPmemOffset >= lDmemOffset) ? lPmemOffset-lDmemOffset : (1024*64)-lDmemOffset;
      }
      else if (1 == lApuId)
      {
         *lpCmemBroadcastReg = HW_REG_CMEM_BOC_63_32;
         *lpDmemSizeInBytes = (lPmemOffset >= lDmemOffset) ? lPmemOffset-lDmemOffset : (1024*128)-lDmemOffset;
      }
      break;
	  
	  default:
	     break;
   }
}

/****************************************************************************
 * Function:      APU Enable
 * Description:   This function enables the APU
 * Parameters:
 *    Sequence    
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
void apexdriver_apu_hal_Enable(int apexID, unsigned int APUID, unsigned int isEnable)
{
   switch (APUID)
   {
   case 0:
      if (isEnable) { apexdriver_global_hal_Apu0Enable(apexID); } else { apexdriver_global_hal_Apu0Disable(apexID); }
      break;
   case 1:
      if (isEnable) { apexdriver_global_hal_Apu1Enable(apexID); } else { apexdriver_global_hal_Apu1Disable(apexID); }
      break;
   }
}


/****************************************************************************
 * Function:      APU Reset
 * Description:   This function resets the APU
 * Parameters:
 *    Sequence
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
void apexdriver_apu_hal_Reset(int apexID, unsigned int APUID)
{
   switch (APUID)
   {
   case 0:
      apexdriver_global_hal_Apu0Reset(apexID);
      break;
   case 1:
      apexdriver_global_hal_Apu1Reset(apexID);
      break;
   case 2:
      //Apu2Reset();
      break;
   case 3:
      //Apu3Reset();
      break;    
   }
}


/****************************************************************************
 * Function:      Get address
 * Description:
 * Parameters:
 *    Sequence
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
volatile unsigned int *apexdriver_apu_hal_GetDMEMAddress(int apexID, unsigned int APUID)
{
   volatile unsigned int* dmem = (volatile unsigned int*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_SMEM) + DMEM_APU_OFFSET[APUID]);
   return dmem;
}

volatile unsigned int *apexdriver_apu_hal_GetIMEMAddress(int apexID, unsigned int APUID)
{
   volatile unsigned int* imem = (volatile unsigned int*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_SMEM) + IMEM_APU_OFFSET[APUID]);
   return imem;
}

volatile unsigned int *apexdriver_apu_hal_GetVMEMAddress(int apexID, unsigned int APUID)
{
   volatile unsigned int* vmem = (volatile unsigned int*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_CMEM_GOC) + VMEM_APU_OFFSET[APUID]);
   return vmem;
}

volatile unsigned int *apexdriver_apu_hal_GetDMEMAddressPhys(int apexID, unsigned int APUID)
{
   volatile unsigned int* dmem = (volatile unsigned int*)((int64_t)ReturnPhysicalHwPtr(apexID, HW_REG_SMEM) + DMEM_APU_OFFSET[APUID]);
   return dmem;
}

volatile unsigned int *apexdriver_apu_hal_GetIMEMAddressPhys(int apexID, unsigned int APUID)
{
   volatile unsigned int* imem = (volatile unsigned int*)((int64_t)ReturnPhysicalHwPtr(apexID, HW_REG_SMEM) + IMEM_APU_OFFSET[APUID]);
   return imem;
}

volatile unsigned int *apexdriver_apu_hal_GetVMEMAddressPhys(int apexID, unsigned int APUID)
{
   volatile unsigned int* vmem = (volatile unsigned int*)((int64_t)ReturnPhysicalHwPtr(apexID, HW_REG_CMEM_GOC) + VMEM_APU_OFFSET[APUID]);
   return vmem;
}

/****************************************************************************
 * Function:      APU Loader
 * Description:
 * Parameters:
 *    Sequence
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int
apexdriver_apu_load_IMEM(int apexID, int apuid, int size, const int* addr, const int* data)
{
   int rval = 0;

   volatile int* imem = (volatile int*)apexdriver_apu_hal_GetIMEMAddress(apexID, apuid);

   // INITIALIZE ALL IMEM
#if (1 == IMEM_INIT)
   {
	  int i;
      for (i=0; i<IMEM_SIZE_MAX; ++i)
         imem[i] = 0;
   }
#endif

   {
	  int i;
      for (i=0; i<size; ++i)
         imem[addr[i]] = data[i];
   }

   return rval;
}

int
apexdriver_apu_load_DMEM(int apexID, int apuid, int size, const int* addr, const int* data)
{
   int rval = 0;

#if (1 == DMEM_INIT)
   {
	  int i;
      volatile int* dmem = (volatile int*)apexdriver_apu_hal_GetDMEMAddress(apexID, apuid);
      for (i=0; i<DMEM_SIZE_MAX; ++i)
         dmem[i] = 0;
   }
#endif

   {
	  int i;
      volatile int* dmem = (volatile int*)apexdriver_apu_hal_GetDMEMAddress(apexID, apuid);
      for (i=0; i<size; ++i)
         dmem[addr[i]] = data[i];
   }

   return rval;
}

int
apexdriver_apu_load_VMEM(int apexID, int apuid, int size, const int* addr, const int* data)
{
   int rval  =  0;

#if (1 == VMEM_INIT)
   {
      // BROADCAST
	  int i;
      volatile int* cmem = (volatile int*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_CMEM_GOC) + 0x00380000);
      for (i=0; i<VMEM_SIZE_MAX; ++i)
      {
         // 128-bit write
         cmem[4*i+0] = 0;
         cmem[4*i+1] = 0;
         cmem[4*i+2] = 0;
         cmem[4*i+3] = 0;
      }
   }
#endif

   {
      volatile int* cmem = (volatile int*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_SMEM) + 0x00080000);
      int i;
      int ka =     0;
      int kc =     0;
      int kp = -1024;

      for (i=0; i<size; ++i)
      {
         ka  = addr[i];
         if ((ka-kp)>1)
         {
            // new beginning!
            kc = ((ka >> 4) << 3) + (ka & 0x0F);
            //printf(" VM BEG: %06X (%06X)\n", kc, ka);
         }
         else
            ++kc;

         kp = ka;
         ka = kc ^ 0x0F;     // MALCOLM MEMORY ORDER (INVERSE CU ORDER? ENDIANNESS AS WELL?)

         cmem[ka] = data[i];
      }
   }

   return rval;
}

/****************************************************************************
 * Function:      apu_hal_Load
 * Parameters:
 *    Sequence             
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
void apexdriver_apu_hal_Load(int apexID, int apuid,
                  int im_size, const int* im_addr, const int* im_data,
                  int dm_size, const int* dm_addr, const int* dm_data,
                  int vm_size, const int* vm_addr, const int* vm_data)
{
   // Disable APU
   apexdriver_apu_hal_Enable(apexID, apuid, 0);
   apexdriver_apu_hal_Reset(apexID, apuid);
   
   // Load the APU with HARD CODED outputs from
   // dart/bridge
   // --------------------------------------------------------------
   // Load program and data memory
   apexdriver_apu_load_IMEM(apexID, apuid, im_size, im_addr, im_data);
   apexdriver_apu_load_DMEM(apexID, apuid, dm_size, dm_addr, dm_data);
   apexdriver_apu_load_VMEM(apexID, apuid, vm_size, vm_addr, vm_data);

   // Initialize the communication address
   //apu_com[apuid] = (APU_COMM *)(((unsigned int)apu_hal_GetDMEMAddress(apuid)) + 0x00000800);

} // End of the APULoadProgram function.


/****************************************************************************
 * Function:      apu_hal_Load one single load
 * Parameters:
 *    Sequence
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
int32_t apexdriver_apu_hal_LoadSegment(int apexID, int32_t apuid,
                            const LOAD_SEGMENT_t* seg_addr)
{
   int32_t lRetVal = 0;
   int n;

   HW_REG_ID lCmemBroadcastReg;
   uint32_t lPmemOffsetInBytes = 0;
   uint32_t lDmemOffsetInBytes = 0;
   uint32_t lDmemSizeInBytes = 0;
   volatile SEG_MEM_TYPE* dmem;
   volatile SEG_MEM_TYPE* base_addr[3];
   volatile SEG_MEM_TYPE* cmem;
   SEG_HOST_TYPE memory_type;
   
   //Disable and reset APU 'apuid'
   apexdriver_apu_hal_Enable(apexID, apuid, 0);
   apexdriver_apu_hal_Reset(apexID, apuid);
   
   apexdriver_RetApuInfoFromCmemIf (apexID, apuid, &lCmemBroadcastReg, &lPmemOffsetInBytes, &lDmemOffsetInBytes, &lDmemSizeInBytes);

   base_addr[0] = (SEG_MEM_TYPE*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_SMEM)     + lPmemOffsetInBytes);
   base_addr[1] = (SEG_MEM_TYPE*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_SMEM)     + lDmemOffsetInBytes);
   base_addr[2] = (SEG_MEM_TYPE*)((int64_t)ReturnVirtualHwPtr(apexID, HW_REG_CMEM_GOC) + 0);

#if (1 == VMEM_INIT) // clear VMEM (use cmem broadcast functionality)
   cmem = (volatile SEG_MEM_TYPE*)ReturnVirtualHwPtr(apexID, lCmemBroadcastReg);
   /*{
	   int i;
	   for (i=0; i<VMEM_SIZE_MAX*2*8; ++i)
			((char *)cmem)[i] = 0;
   }*/
   #ifdef __KERNEL_MODULE
   memset_io((void*)cmem, 0, VMEM_SIZE_MAX*2*8);
   #else
   memset((void*)cmem, 0, VMEM_SIZE_MAX*2*8);
   #endif
#endif

#if (1 == DMEM_INIT) //clear DMEM
   dmem = base_addr[1];
   #ifdef __KERNEL_MODULE
   memset_io((void*)dmem, 0, lDmemSizeInBytes);
   #else
   memset((void*)dmem, 0, lDmemSizeInBytes);
   #endif
   /*{
	   int i;
	   for (i=0; i<lDmemSizeInBytes; ++i)
			((char *)dmem)[i] = 0;
   }*/
#endif
   // Load the APU with HARD CODED outputs from
   // dart/bridge
   // --------------------------------------------------------------
   // Load program and data memory
   n = 0;
   memory_type = (SEG_HOST_TYPE)seg_addr[n][0];
   while (memory_type != -1)
   {
      //values directly from APU LOAD file
      SEG_MEM_TYPE* src_ptr = (SEG_MEM_TYPE*)seg_addr[n][1];
      SEG_HOST_TYPE dst_offset_in_bytes    = seg_addr[n][2];
      SEG_HOST_TYPE data_size_in_bytes     = seg_addr[n][3];

      //'adjusted' values
      SEG_HOST_TYPE dst_offset_32 = (dst_offset_in_bytes)>>2;
      SEG_HOST_TYPE data_size_32 = ((dst_offset_in_bytes + data_size_in_bytes)>>2) - (dst_offset_in_bytes>>2);

      // points to dst memory
      // 32-bit write
      volatile SEG_MEM_TYPE* dst_addr  = (volatile SEG_MEM_TYPE*)(base_addr[memory_type] + dst_offset_32);

      if (src_ptr == 0)
      {
         //for (int32_t i=0; i<dat_siz32; ++i)
         //   dst_addr[i] = 0;
      }
      else if  (((dst_offset_in_bytes < APU_0_DMEM_SIZE) && (memory_type == 1)) ||
                 (memory_type == 0)                                             ||
                 (memory_type == 2)
               )
      {
         memcpy((void*)dst_addr, (void*)src_ptr, data_size_32*4);
      }

      memory_type = seg_addr[++n][0];
   }

   // Initialize the communication address
   //apu_com[apuid] = (APU_COMM *)(((unsigned int)apu_hal_GetDMEMAddress(apuid)) + 0x00000800);

   return lRetVal;
   
} // End of the APULoadProgram function.

void apexdriver_apu_hal_QueryLoad_MEM_REQ(int apexID, const LOAD_SEGMENT_t* seg_addr, int32_t* pCmemReq, int32_t* pDmemReq, int32_t* pPmemReq)
{
   //this function basically takes the 'last' of each type encountered in the segment array and assumes it is the
   //end of memory of that type!!!

   const int32_t binNumCu = 128;
   const int32_t cmem_end = 0x1000;

   int32_t lIndex = 0;
   SEG_HOST_TYPE memory_type = (SEG_HOST_TYPE)seg_addr[lIndex][0];

   while (memory_type != -1)
   {
      SEG_HOST_TYPE dst_offset  = seg_addr[lIndex][2];
      SEG_HOST_TYPE dst_size    = seg_addr[lIndex][3];

      if (memory_type == 0) //PMEM
      {
         *pPmemReq = dst_offset + dst_size; //SHOULD ONLY BE ONE OF THESE
      }

      if (memory_type == 1) //DMEM
      {
         if (dst_offset == 0x10800 || dst_offset == 0x10804)
         {
            //ignore (some virtual *.bcf thing Christina can explain)
         }
         else
         {
            *pDmemReq = dst_offset + dst_size;
         }
      }

      if (memory_type == 2) //CMEM
      {
         if (dst_offset == cmem_end)
         {
            //ignore (related to CMEM_RESERVED stuff)
         }
         else
         {
            *pCmemReq = dst_offset + dst_size/binNumCu;
         }
      }

      memory_type = seg_addr[++lIndex][0];
   }
   }

int32_t apexdriver_apu_hal_RetMemSizes (int apexID, CMEM_IF_APU_CFG apuconfig,
                             int32_t* pSmemSize,
                             int32_t* pCmemSize)
{
   int32_t lRetVal = 0;

   *pCmemSize = (1024*4); //always 4K right now
   
   switch(apuconfig)
   {
   case CFG_321__APU_0_CU_0_31_SMEM_0_1:
      *pSmemSize = (1024*64);
      break;
   case CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3:
      *pSmemSize = (1024*64);
      break;
   case CFG_642__APU_0_CU_0_63_SMEM_0_3:
      *pSmemSize = (1024*128);
      break;
   default:
      lRetVal = 1; //ERROR - unexpected APU configuration
      break;
}

   return lRetVal;
}

/****************************************************************************
 * Function:      ACDisableAllIRQs
 * Description:   Disable all the AC IRQs.
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
void apexdriver_apu_hal_DisableAllIRQs (int apexID)
{

} // End of the ACDisableAllIRQs function.

/****************************************************************************
 * Function:      ACClearAllIRQ
 * Description:   Clear the all the AC IRQs.
 * Parameters:    None
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/
void apexdriver_apu_hal_ClearAllIRQs (int apexID)
{

} // End of the ACClearAllIRQs function


