/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2011 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#include <INTEGRITY.h>
#include "../../../kernel/include/integrity/apexdriver_iodev.h"

#include <stdio.h>

#include "oal.h"
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "linked_list_utilities.h"
#include <fcntl.h>
#include <unistd.h>
#include "apexdriver_hw_reg_user.h"
#include "cmem_array_map.h"
#include "apex_mcdma_hal.h"
#include "apexdriver_cmem_if_hal.h"

void apu_hal_Enable(int apexID, unsigned int APUID, unsigned int isEnable)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APU_HAL_ENABLE_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_ENABLE;
  params.apexID = apexID;
  params.APUID = APUID;
  params.isEnable = isEnable;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apu_hal_Enable). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
    
}

void apu_hal_Reset(int apexID, unsigned int APUID)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APU_HAL_RESET_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_RESET;
  params.apexID = apexID;
  params.APUID = APUID;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apu_hal_Reset). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

void apu_hal_FreeSegments(void** loadOalMemoryPtr_PMEM, void** loadOalMemoryPtr_DMEM, void** loadOalMemoryPtr_CMEM, void **dma_list)
{
	if (*loadOalMemoryPtr_PMEM) OAL_MemoryFree(*loadOalMemoryPtr_PMEM);
	if (*loadOalMemoryPtr_DMEM) OAL_MemoryFree(*loadOalMemoryPtr_DMEM);
	if (*loadOalMemoryPtr_CMEM) OAL_MemoryFree(*loadOalMemoryPtr_CMEM);
	if (*dma_list) OAL_MemoryFree(*dma_list);
}

int32_t apu_hal_LoadSegment(int apexID, int32_t apuid, const LOAD_SEGMENT_t* seg_addr)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APU_HAL_LOADSEGMENT_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_LOADSEGMENT;
  params.apexID = apexID;
  params.apuid = apuid;
  params.seg_addr = seg_addr;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apu_hal_LoadSegment). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  return params.ret;
}

void apu_hal_QueryLoad_MEM_REQ(int apexID, const LOAD_SEGMENT_t* seg_addr, int32_t* pCmemReq, int32_t* pDmemReq, int32_t* pPmemReq)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_QUERYLOAD_MEM_REQ;
  params.apexID = apexID;
  params.seg_addr = seg_addr;
  params.pCmemReq = pCmemReq;
  params.pDmemReq = pDmemReq;
  params.pPmemReq = pPmemReq;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apu_hal_QueryLoad_MEM_REQ). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

int32_t apu_hal_RetMemSizes (int apexID, CMEM_IF_APU_CFG apuconfig, int32_t* pSmemSize, int32_t* pCmemSize)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_APU_HAL_RETMEMSIZES_TYPE params;
  params.io_id = APEXDRIVER_APU_HAL_RETMEMSIZES;
  params.apexID = apexID;
  params.apuconfig = apuconfig;
  params.pSmemSize = pSmemSize;
  params.pCmemSize = pCmemSize;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (apu_hal_RetMemSizes). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  return params.ret;
}

void RetApuInfoFromCmemIf (int apexID, int32_t    lApuId,
                           HW_REG_ID* lpCmemBroadcastReg,
                           uint32_t*   lpPmemOffsetInBytes,
                           uint32_t*   lpDmemOffsetInBytes,
                           uint32_t*   lpDmemSizeInBytes)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF_TYPE params;
  params.io_id = APEXDRIVER_RET_APU_INFO_FROM_CMEM_IF;
  params.apexID = apexID;
  params.lApuId = lApuId;
  params.lpCmemBroadcastReg = lpCmemBroadcastReg;
  params.lpPmemOffsetInBytes = lpPmemOffsetInBytes;
  params.lpDmemOffsetInBytes = lpDmemOffsetInBytes;
  params.lpDmemSizeInBytes = lpDmemSizeInBytes;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (mcdma_hal_interruptclear_ch_done). Operation not executed.\n");
    return;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return;
  }
  return;
}

int32_t apu_hal_CopyLoadToOalMemory(const SEG_MEM_TYPE* pLoadPmem,
                                    int32_t loadPmemSize,
                                    const SEG_MEM_TYPE* pLoadDmem,
                                    int32_t loadDmemSize,
                                    const SEG_MEM_TYPE* pLoadCmem,
                                    int32_t loadCmemSize,
                                    void** loadOalMemoryPtr_PMEM,
                                    void** loadOalMemoryPtr_DMEM,
                                    void** loadOalMemoryPtr_CMEM)
{
   int lRetVal = 0;
   uint32_t* lpDst = 0;

   //*loadOalMemoryPtr_PMEM = 0;
   //*loadOalMemoryPtr_DMEM = 0;
   //*loadOalMemoryPtr_CMEM = 0;

   //PMEM
   if (loadPmemSize > 0)
   {
      if (*loadOalMemoryPtr_PMEM==0) *loadOalMemoryPtr_PMEM = OAL_MemoryAllocFlag(loadPmemSize*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
      if (*loadOalMemoryPtr_PMEM != 0)
      {
         lpDst = (uint32_t*)*loadOalMemoryPtr_PMEM;
         memcpy((void*)lpDst, (void*)pLoadPmem, loadPmemSize*4);
	 
		 OAL_MemoryFlushAndInvalidate(OAL_MemoryReturnAddress(*loadOalMemoryPtr_PMEM, ACCESS_PHY), loadPmemSize*4);
      }
      else //failed to allocate memory
      {
         lRetVal = 1;
      }
   }

   //DMEM
   if (loadDmemSize > 0)
   {
     
      if (*loadOalMemoryPtr_DMEM==0) *loadOalMemoryPtr_DMEM = OAL_MemoryAllocFlag(loadDmemSize*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
      if (*loadOalMemoryPtr_DMEM != 0)
      {
         lpDst = (uint32_t*)*loadOalMemoryPtr_DMEM;
         memcpy((void*)lpDst, (void*)pLoadDmem, loadDmemSize*4);
		 OAL_MemoryFlushAndInvalidate(OAL_MemoryReturnAddress(*loadOalMemoryPtr_DMEM, ACCESS_PHY), loadDmemSize*4);
		 
      }
      else //failed to allocate memory
      {
         lRetVal = 1;
      }
   }

   //CMEM
   if (loadCmemSize > 0)
   {
      if (*loadOalMemoryPtr_CMEM==0) *loadOalMemoryPtr_CMEM = OAL_MemoryAllocFlag(loadCmemSize*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
      if (*loadOalMemoryPtr_CMEM != 0)
      {
         lpDst = (uint32_t*)*loadOalMemoryPtr_CMEM;
         memcpy((void*)lpDst, (void*)pLoadCmem, loadCmemSize*4);
		 OAL_MemoryFlushAndInvalidate(OAL_MemoryReturnAddress(*loadOalMemoryPtr_CMEM, ACCESS_PHY), loadCmemSize*4);
      }
      else //failed to allocate memory
      {
         lRetVal = 1;
      }
   }

   if (lRetVal != 0)
   {
      if (*loadOalMemoryPtr_PMEM) OAL_MemoryFree(*loadOalMemoryPtr_PMEM);
      if (*loadOalMemoryPtr_DMEM) OAL_MemoryFree(*loadOalMemoryPtr_DMEM);
      if (*loadOalMemoryPtr_CMEM) OAL_MemoryFree(*loadOalMemoryPtr_CMEM);
   }

   return lRetVal;
}

int32_t CalcOptimalWordSize(int32_t lPhysAddr, int32_t lSpan, int32_t lBytesPerLine)
{
   //0: 8-bit
   //1: 16-bit
   //2: 32-bit
   //3: 64-bit
   //4: 128-bit

   int32_t lWordSize = 0;
   int lTemp = (lPhysAddr|lSpan|lBytesPerLine) & 0xF;

   if (lTemp & 1)
      lWordSize = 0;
   else if (lTemp & 2)
      lWordSize = 1;
   else if (lTemp & 4)
      lWordSize = 2;
   else if (lTemp & 8)
      lWordSize = 3;
   else
      lWordSize = 4;

   return lWordSize;
}

void LLE_1D_Fill (uint32_t* llBuffer,  //size must be >=8 words
                  uint32_t dstAddr,    //physical destination address DMA will write to
                  int32_t fillSizeInBytes)
{
   int32_t lWordSize = CalcOptimalWordSize(dstAddr, 0, fillSizeInBytes);

   //ENTRY_0     periph enable | sideband cfg | src periph port (memfill0)
   llBuffer[0] = 1 << 31       | 0 << 4       | 7 << 0;

   //ENTRY_1         dst addr
   llBuffer[1] = dstAddr;

   //ENTRY_2     pause   | int enable | loop on last | last    | burst size | word size      | src xfer type | src addr mode | src data format | dst xfer type | dst addr mode | dst data format
   llBuffer[2] = 0 << 31 | 0 << 30    | 0 << 29      | 0 << 28 | 15 << 11   | lWordSize << 8 | 1 << 7        | 0 << 6        | 0 << 4          | 0 << 3        | 0 << 2        | 0 << 0;
   //                                                            16_BEAT      <depends>        periph based    direct addr     1D                mem based       direct addr     1D

   //ENTRY_3     frame size (in bytes)
   llBuffer[3] = fillSizeInBytes;

   //ENTRY_4 (not used in 1D configuration)
   llBuffer[4] = 0;

   //ENTRY_5 (not used in 1D configuration)
   llBuffer[5] = 0;

   //ENTRY_6 (not used in 1D configuration)
   llBuffer[6] = 0;

   //NXT_LL
   llBuffer[7] = 8*4;
}

void LLE_1D_MEM_MEM (uint32_t* llBuffer,  //size must be >=8 words
                     uint32_t srcAddr,    //physical source address DMA will read from
                     uint32_t dstAddr,    //physical destination address DMA will write to
                     int32_t transferSizeInBytes)
{
   int32_t lWordSize = CalcOptimalWordSize(srcAddr|dstAddr, 0, transferSizeInBytes);

   //******************************************
   //START POPULATING LINKED LIST ENTRY
   //******************************************

   //ENTRY_0     src addr
   llBuffer[0] = srcAddr;

   //ENTRY_1     dst addr
   llBuffer[1] = dstAddr;

   //ENTRY_2     pause   | int enable | loop on last | last    | burst size | word size      | src xfer type | src addr mode | src data format | dst xfer type | dst addr mode | dst data format
   llBuffer[2] = 0 << 31 | 0 << 30    | 0 << 29      | 0 << 28 | 15 << 11   | lWordSize << 8 | 0 << 7        | 0 << 6        | 0 << 4          | 0 << 3        | 0 << 2        | 0 << 0;
   //                                                            16_BEAT      <depends>        mem based       direct addr     1D                mem based       direct addr     1D

   //ENTRY_3     frame size (in bytes)
   llBuffer[3] = transferSizeInBytes;

   //ENTRY_4 (not used in 1D configuration)
   llBuffer[4] = 0;

   //ENTRY_5 (not used in 1D configuration)
   llBuffer[5] = 0;

   //ENTRY_6 (not used in 1D configuration)
   llBuffer[6] = 0;

   //NXT_LL
   llBuffer[7] = 8*4;
}

void LLE_DMA_Finalize(uint32_t* llEntry)
{
   llEntry[2] |= 0xD0000000; //set 'pause', 'interrupt enable', and 'last' bits
}

void* ReturnPhysicalHwPtr (int lApexID, HW_REG_ID lHwRegId)
{
  IODevice apex;
  Error flag;
  Value args[4];
  Buffer buffer[1];
  APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR_TYPE params;
  params.io_id = APEXDRIVER_GLOBAL_HAL_RET_PHYS_PTR;
  params.apexID = lApexID;
  params.lHwRegId = lHwRegId;
  
  
  if (RequestResource((Object *) &apex, "APEXIODevice", "!systempassword") != Success)
  {
    fprintf(stderr, "Apex 2 - Error opening APU device (ReturnPhysicalHwPtr). Operation not executed.\n");
    return 0;    
  }

  args[0] = 0;
  buffer[0].BufferType = 	BufferType_DataWrite | BufferFlag_LastBuffer;
  buffer[0].TheAddress = (Address)&params;
  buffer[0].Length = sizeof(APEXDRIVER_APU_HAL_ENABLE_TYPE);

  flag = SynchronousSendIORequest(apex, 0, args, buffer);
  if (flag != Success)
  {
    fprintf(stderr, "Apex 2 - APU Load program IOCTL failed.\n");
    return 0;
  }
  return params.ret;
}

int32_t apu_hal_GenLoadLL(int apexID, int32_t apuid,
                          const LOAD_SEGMENT_t* seg_addr,
                          const SEG_MEM_TYPE* pPmemLoadBase, //base address of *_LOAD_PMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          const SEG_MEM_TYPE* pDmemLoadBase, //base address of *_LOAD_DMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          const SEG_MEM_TYPE* pCmemLoadBase, //base address of *_LOAD_CMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          uint32_t loadPhysPtr_PMEM,         //base address (physical) of *_LOAD_PMEM
                          uint32_t loadPhysPtr_DMEM,         //base address (physical) of *_LOAD_DMEM
                          uint32_t loadPhysPtr_CMEM,         //base address (physical) of *_LOAD_CMEM
                          void** llOalMemoryPtr)
{
   int32_t lRetVal = 0;

   HW_REG_ID lCmemBroadcastReg;
   uint32_t lPmemOffsetInBytes = 0;
   uint32_t lDmemOffsetInBytes = 0;
   uint32_t lDmemSizeInBytes = 0;
   RetApuInfoFromCmemIf (apexID, apuid, &lCmemBroadcastReg, &lPmemOffsetInBytes, &lDmemOffsetInBytes, &lDmemSizeInBytes);

   
   volatile SEG_MEM_TYPE* base_addr[3] = {(SEG_MEM_TYPE*)((uint64_t)ReturnPhysicalHwPtr(apexID, HW_REG_SMEM)     + lPmemOffsetInBytes),
                                          (SEG_MEM_TYPE*)((uint64_t)ReturnPhysicalHwPtr(apexID, HW_REG_SMEM)     + lDmemOffsetInBytes),
                                          (SEG_MEM_TYPE*)((uint64_t)ReturnPhysicalHwPtr(apexID, HW_REG_CMEM_GOC) + 0)};

   //determine number of load segments
   int lNumSegments = 0;
   SEG_HOST_TYPE memory_type = (SEG_HOST_TYPE)seg_addr[lNumSegments][0];
   while ((int)memory_type != -1)
   {
      memory_type = seg_addr[++lNumSegments][0];
   }

   //allocate memory for the linked list
   if (*llOalMemoryPtr==0) *llOalMemoryPtr = OAL_MemoryAllocFlag(LLE_SIZE_1D_MEM_MEM*4*lNumSegments, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);

   if (*llOalMemoryPtr != 0)
   {
      uint32_t* lpLinkedList = (uint32_t*)*llOalMemoryPtr;
      uint32_t* lpLLE = lpLinkedList; //pointer to the 'current' linked list entry

      // Load program and data memory
      int n = 0;
      SEG_HOST_TYPE memory_type = (SEG_HOST_TYPE)seg_addr[n][0];
      while ((int)memory_type != -1)
      {
         //values directly from APU LOAD file
         SEG_MEM_TYPE* src_ptr = (SEG_MEM_TYPE*)seg_addr[n][1];
         SEG_HOST_TYPE dst_offset_in_bytes    = seg_addr[n][2];
         SEG_HOST_TYPE data_size_in_bytes     = seg_addr[n][3];

         //'adjusted' values
         SEG_HOST_TYPE dst_offset_32 = (dst_offset_in_bytes)>>2;
         SEG_HOST_TYPE data_size_32 = ((dst_offset_in_bytes + data_size_in_bytes)>>2) - (dst_offset_in_bytes>>2);

         // points to dst memory
         // 32-bit writeio
         volatile SEG_MEM_TYPE* dst_addr  = (volatile SEG_MEM_TYPE*)(base_addr[memory_type] + dst_offset_32);

         //NOTE: ignoring CMEM memory_type (shouldn't be used)
         if (src_ptr == 0)
         {
            //do nothing
         }
         else if  ( ((dst_offset_in_bytes < APU_0_DMEM_SIZE) && (memory_type == 1))  ||
                    (memory_type == 0))
         {
            SEG_MEM_TYPE* srcPtrTmp = 0;
            if (0 == memory_type) //LOAD_PMEM
               srcPtrTmp = (SEG_MEM_TYPE*)(uint64_t)loadPhysPtr_PMEM + (src_ptr-pPmemLoadBase);
            else if (1 == memory_type) //LOAD_DMEM
               srcPtrTmp = (SEG_MEM_TYPE*)(uint64_t)loadPhysPtr_DMEM + (src_ptr-pDmemLoadBase);
            //else if (2 == memory_type) //LOAD_CMEM
            //   srcPtrTmp = (SEG_MEM_TYPE*)loadPhysPtr_CMEM + (src_ptr-pCmemLoadBase);

            LLE_1D_MEM_MEM(lpLLE, (uint32_t)(uint64_t)srcPtrTmp, (uint32_t)(uint64_t)dst_addr, data_size_32*4);
            lpLLE += LLE_SIZE_1D_MEM_MEM;
         }

         memory_type = seg_addr[++n][0];
      }

      LLE_DMA_Finalize(lpLLE-LLE_SIZE_1D_MEM_MEM);
   }
   else //failed to allocate memory for linked list
   {
      lRetVal = 1;
   }

   OAL_MemoryFlushAndInvalidate(OAL_MemoryReturnAddress(*llOalMemoryPtr, ACCESS_PHY), LLE_SIZE_1D_MEM_MEM*4*lNumSegments);
   return  lRetVal;
}

int32_t apu_hal_LoadSegments_DMA(int apexID, int32_t apuid,
                                 int32_t dmaCh,
                                 void* pLoadSegmentsLLBufferOal)
{
   int32_t lRetVal = 0;

   //Disable and reset APU 'apuid'
   apu_hal_Enable(apexID, apuid, 0);
   apu_hal_Reset(apexID, apuid);

#if 1 //clear VMEM/DMEM w/ DMA fill

   HW_REG_ID lCmemBroadcastReg;
   uint32_t lPmemOffsetInBytes = 0;
   uint32_t lDmemOffsetInBytes = 0;
   uint32_t lDmemSizeInBytes = 0;
   RetApuInfoFromCmemIf (apexID, apuid, &lCmemBroadcastReg, &lPmemOffsetInBytes, &lDmemOffsetInBytes, &lDmemSizeInBytes);
   
   

   void* lpLinkListBufferOal;
   const int32_t lNumLLE = 2;
   lpLinkListBufferOal = OAL_MemoryAllocFlag(LLE_SIZE_1D_FILL*4*lNumLLE, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);

   if (lpLinkListBufferOal != 0)
   {
      uint32_t* lpLinkedList = (uint32_t*)lpLinkListBufferOal;
      uint32_t* lpLLE = lpLinkedList; //pointer to the 'current' linked list entry
      //clear VMEM
      LLE_1D_Fill(lpLLE, (uint64_t)ReturnPhysicalHwPtr(apexID, lCmemBroadcastReg), VMEM_SIZE_MAX*2*8);
      lpLLE += LLE_SIZE_1D_FILL;
      //clear DMEM
      LLE_1D_Fill(lpLLE, (uint32_t)((uint64_t)ReturnPhysicalHwPtr(apexID, HW_REG_SMEM) + lDmemOffsetInBytes), lDmemSizeInBytes);
      lpLLE += LLE_SIZE_1D_FILL;
      LLE_DMA_Finalize(lpLLE-LLE_SIZE_1D_FILL);
	  OAL_MemoryFlushAndInvalidate(OAL_MemoryReturnAddress(lpLinkListBufferOal, ACCESS_PHY), LLE_SIZE_1D_FILL*4*lNumLLE);
	  
      mcdma_hal_set_memory_fill_words(apexID, 0, 0, 0, 0);
      mcdma_hal_program_seq_linkedlist(apexID, dmaCh, (int64_t)OAL_MemoryReturnAddress(lpLinkListBufferOal, ACCESS_PHY));
      mcdma_hal_start(apexID, dmaCh);
      mcdma_hal_wait(apexID, dmaCh);
      mcdma_hal_interruptclear_ch_done(apexID, dmaCh);
      OAL_MemoryFree(lpLinkListBufferOal);
      
      
      
   }
   else //could not allocate linked list buffer
   {
      lRetVal = 1;
   }

#endif
   //load segments
   mcdma_hal_program_seq_linkedlist(apexID, dmaCh, (int64_t)OAL_MemoryReturnAddress(pLoadSegmentsLLBufferOal, ACCESS_PHY));
   mcdma_hal_start(apexID, dmaCh);
   mcdma_hal_wait(apexID, dmaCh);
   mcdma_hal_interruptclear_ch_done(apexID, dmaCh);

   return lRetVal;
}

