/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2015 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#include <acf_common.h>
#include <acf_process.h>
#include <acf_process_apu.h>
#include <acf_process_portinfo.h>
#include <acf_process_portinfo_apu.h>
#include <acf_apu_program_params.h>
#include <resource_manager_protected.h>
#include <resource_manager_apex.h>
#include <apex_seq_hal.h>
#include <apex_apu_hal.h>
#include <apex_apu_microkernel_hal.h>
#include <apex_cmem_if_hal.h>
#include <kernel_manager.h>

//these currently required to allow ACF to query the APU configuration and to set the desired default configuration
#include <apex_global_hal.h>
#include <apex_cmem_if_hal.h>

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string.h> //for memcpy

using namespace std;

#define ACF_ENABLE_HW_PROFILING   0

#if (ACF_ENABLE_HW_PROFILING == 1)
#include <apex_mcdma_hal.h> //for use of 'performance' profiling registers
#endif

int RetLocalMemDescSizeInBytes(ACF_LocalMemDesc* lpLM)
{
   return lpLM->chunkE0Span*(lpLM->chunkHeight*lpLM->numBuffers + lpLM->padding.n + lpLM->padding.s);
}

//function declaration (TODO: should this be a class member instead??)
acf_scenario* SelectOptimalScenario(std::vector<ACF_Process_PortInfo> &lPortInfoVec,
                                    int32_t lRoiInfoL, int32_t lRoiInfoR,
                                    int32_t lCuArrayWidth, int32_t lAvailableCmem, int32_t lAvailableDmem,
                                    acf_scenario_list* lpScenarioList,
                                    std::string lUserSelPort,
                                    int32_t     lUserSelChunkWidth,
                                    int32_t     lUserSelChunkHeight);

//translate ACF_APU_CFG to CMEM_IF_APU_CFG (don't want to expose CMEM_IF_APU_CFG through interface)
CMEM_IF_APU_CFG Translate_AcfApuCfg_CmemIfApuCfg(ACF_APU_CFG lApuConfig, int32_t lHwVersion)
{
   CMEM_IF_APU_CFG lRetVal = CFG_UNKNOWN_CONFIGURATION;

   switch (lApuConfig)
   {
   case ACF_APU_CFG__DEFAULT:
      if      (0x321 == lHwVersion) lRetVal = CFG_321__APU_0_CU_0_31_SMEM_0_1;
      else if (0x642 == lHwVersion) lRetVal = CFG_642__APU_0_CU_0_63_SMEM_0_3;
      break;
   case ACF_APU_CFG__APU_0_CU_0_63_SMEM_0_3:
      lRetVal = CFG_642__APU_0_CU_0_63_SMEM_0_3;
      break;
   case ACF_APU_CFG__APU_0_CU_0_31_SMEM_0_1:
      if      (0x321 == lHwVersion) lRetVal = CFG_321__APU_0_CU_0_31_SMEM_0_1;
      else if (0x642 == lHwVersion) lRetVal = CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3;
      break;
   case ACF_APU_CFG__APU_1_CU_32_63_SMEM_2_3:
      lRetVal = CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3;
      break;
   }

   return lRetVal;
}

void CfgResSet_321_ALL(acf_res_info* lpAcfResInfo);
void CfgResSet_642_ALL(acf_res_info* lpAcfResInfo);
void CfgResSet_642_HALF_APU0(acf_res_info* lpAcfResInfo);
void CfgResSet_642_HALF_APU1(acf_res_info* lpAcfResInfo);

ACF_Process_APU *instance_apex1 = NULL;
ACF_Process_APU *instance_apex2 = NULL;
void (*function_apex0)(void)  = NULL;
void (*function_apex1)(void)  = NULL;
void IRQ_Handler1();
void IRQ_Handler2();
#define APEX_APEX0_IRQ			(141)
#define APEX_APEX1_IRQ			(142)

int32_t ACF_Process_APU::InitDoneInterrupt(void (*pCustomHandler) (void))
{
  mUseIRQ[mApexId] = true;     
  switch(mApexId)
  {
	case 0:
	  if (instance_apex1 != NULL)
		return 1;
	  instance_apex1 = this;
	  	  
	  OAL_IRQInit(IRQ_Handler1, APEX_APEX0_IRQ, 0xA0, IRQ_EDGE);
	  OAL_IRQEnable(APEX_APEX0_IRQ); 
		
	  function_apex0 = pCustomHandler;
	  break;
	case 1:
	  if (instance_apex2 != NULL)
		return 1;
	  instance_apex2 = this;
	  	  
	  OAL_IRQInit(IRQ_Handler2, APEX_APEX1_IRQ, 0xA0, IRQ_EDGE);
	  OAL_IRQEnable(APEX_APEX1_IRQ); 
		
	  function_apex1 = pCustomHandler;
	  break;
	default:
	  return 2;
  }
  return 0;
}

void IRQ_Handler1()
{
   OAL_IRQDisable(APEX_APEX0_IRQ);
   OAL_IRQDelete(APEX_APEX0_IRQ);
   
   uint32_t isrval = seq_hal_query_interrupts(0);
   seq_hal_clear_interrupts(0, isrval);
   instance_apex1->Wait();
   instance_apex1 = NULL;
   //release HW resources
   function_apex0();  
}
	
void IRQ_Handler2()
{
   OAL_IRQDisable(APEX_APEX1_IRQ);
   OAL_IRQDelete(APEX_APEX1_IRQ);
   
   uint32_t isrval = seq_hal_query_interrupts(0);
   seq_hal_clear_interrupts(0, isrval);
   
   instance_apex2->Wait();
   instance_apex2 = NULL;
   //release HW resources
   function_apex1();  
}

//-------------------------------------------------------------------------------
//***********************ACF_Process_APU*****************************************
//-------------------------------------------------------------------------------

#define MAX_PARAM_LIST_SIZE_IN_WORDS 255

ACF_Process_APU::ACF_Process_APU(int apexID)
{
   mApexId                 = apexID;
   mApuCfg                 = ACF_APU_CFG__DEFAULT;
   mUseIRQ[apexID]         = false;
   mApuId                  = 0;
   mCuArrayWidth           = 32;
   mHwVersion              = 0;
   mDmemHeapBaseAddrOffset = 0;
   mDmemHeapSizeInBytes    = 0;
   mCmemHeapBaseAddrOffset = 0;
   mCmemHeapSizeInBytes    = 0;
   mPmemBaseAddrOffset     = 0;
   mSmemBaseAddrOffset     = 0;
   mPmemSizeInBytes        = 0;
   mpScenarioList          = 0;
   mpSelectedScenario      = 0;

   mpPmemLoadOal       = 0;
   mpDmemLoadOal       = 0;
   mpCmemLoadOal       = 0;
   mpLoadSegmentsLLOal = 0;

   mProcessApuLoadFlag = 1; //process the load once then set flag to 0
   mProcessStartedFlag = 0;
}

extern void apu_hal_FreeSegments(void** loadOalMemoryPtr_PMEM, void** loadOalMemoryPtr_DMEM, void** loadOalMemoryPtr_CMEM, void **dma_list);

ACF_Process_APU::~ACF_Process_APU()
{
   //apu_hal_FreeSegments(&mpPmemLoadOal, &mpDmemLoadOal, &mpCmemLoadOal, &mpLoadSegmentsLLOal);
   if (mpPmemLoadOal)       OAL_MemoryFree(mpPmemLoadOal);
   if (mpDmemLoadOal)       OAL_MemoryFree(mpDmemLoadOal);
   if (mpCmemLoadOal)       OAL_MemoryFree(mpCmemLoadOal);
   if (mpLoadSegmentsLLOal) OAL_MemoryFree(mpLoadSegmentsLLOal);
}

int32_t ACF_Process_APU::Start()
{


   int32_t lRetVal = ACF_SUCCESS;
   
   //TODO: implement the idea of a 'dirty' flag that indicates whether or not SelectScenario and DetWorstCaseRoiInfo
   //      need to be re-run or not.  The flag could be raised whenever a new IO is connected (although it should be
   //      even more intelligent than that in theory ... if only the address changes many things don't need to be
   //      recalculated, but if the ROI location changes (for example) they do).  This could actually get pretty
   //      complicated ... until this is implemented properly some things may be called redundantly or unnecessarily.

   //if any state errors have occurred prior to invocation of Start(), exit immediately
   if (mErrorState != 0)
   {
      printf("ACF_Process_APU::Start() -> internal state error detected; not starting\n");
      lRetVal = ACF_ERROR;
      return lRetVal;
   }

   if (mRoiInfoManualFlag != 1)
   {
      if (DetWorstCaseRoiInfo() != 0) //check applicable inputs for ROI information
      {
         lRetVal = ACF_ERROR;
         return lRetVal;
      }
   }

   //**************************************************************
   //SCENARIO SELECTION

   //if a scenario has not already been selected
   if (mpSelectedScenario == 0)
   {
      SelectScenario("", 0, 0); //select optimal scenario
   }

   if (mpSelectedScenario != 0)
   {
      //update chunk information associated with input/output ports based on the selected scenario
      //(done like this to eliminate need to change GenApuProgramParams ... should probably be cleaned up
      for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
      {
         mPortInfoVec[i].mChunkWidth = mpSelectedScenario->pBufferData[mPortInfoVec[i].mLmIndex].chunkWidth;
         mPortInfoVec[i].mChunkHeight = mpSelectedScenario->pBufferData[mPortInfoVec[i].mLmIndex].chunkHeight;
      }
   }
   else
   {
      lRetVal = ACF_SCENARIO_DETECTION_ERROR;
      return lRetVal; //<<<<<<<<<<
   }
   //***********************************************************************

   //based on the selected scenario, determine if a 1D processing pipeline should be utilized
   //if the graph has any spatial dependencies it will be treated as 2D, regardless of input dimensions
   int32_t lFlag1D = 0;
   if (mSpatialDepFlag == 0)
   {
      lFlag1D = CheckIf1D_pipeline(mPortInfoVec);;
   }

   int32_t lProgramParams[MAX_PARAM_LIST_SIZE_IN_WORDS] = {0}; //TODO: choose this size more carefully based on some global limits
   int32_t lProgramParamSizeInWords = MAX_PARAM_LIST_SIZE_IN_WORDS; //init with 'max' for now - it will be overridden with 'actual' size

   
   if (0 == GenApuProgramParams(mPortInfoVec, mPortInfoApuVec, mRoiInfoL, mRoiInfoR, mRoiInfoT, mRoiInfoB,
                                lFlag1D, mCuArrayWidth, lProgramParams, &lProgramParamSizeInWords,
                                mpSelectedScenario, 0, mApexId))
   {
     
      //*************************
      //acquire HW resources
      //*************************

      if (ACF_SUCCESS == AllocateHwResources())
      {   //----------------------------------------------------------------------------
		 switch (mApexId)
		 {
			 case 0:
				lProgramParams[8] = 0x74000000 + mSmemBaseAddrOffset;
			    break;
		     case 1:
				lProgramParams[8] = 0x78000000 + mSmemBaseAddrOffset;
			    break;
		 }
         
         lProgramParams[9] = mCmemHeapBaseAddrOffset;
         lProgramParams[10] = mCmemHeapSizeInBytes;
         lProgramParams[11] = mDmemHeapBaseAddrOffset;
         lProgramParams[12] = mDmemHeapSizeInBytes;
         memcpy((void*)&lProgramParams[13], (void*)&mAcfResInfo, sizeof(acf_res_info));
		 
		 //for (int i = 0; i < lProgramParamSizeInWords; ++i)
		 //	printf("Param %X\n", lProgramParams[i]);
         //----------------------------------------------------------------------------

         //****************************
         //APU setup and program launch
         //****************************

         int32_t lMsg = 0;

         //NOTE: cmem_if MUST be configured prior to invoking the apu loader (apu loader will query cmem_if for relevant information)
         cmem_if_hal_set_apu_cfg(mApexId, Translate_AcfApuCfg_CmemIfApuCfg(mApuCfg, mHwVersion));
         cmem_if_hal_set_apu_pmem_start(mApexId, mApuId, mSmemBaseAddrOffset + mPmemBaseAddrOffset);
         cmem_if_hal_set_apu_dmem_start(mApexId, mApuId, mSmemBaseAddrOffset);

#if 1 //use DMA-based segment loading (faster)

         if (mProcessApuLoadFlag)
         {

            apu_hal_CopyLoadToOalMemory(mpLoadPmem, mLoadPmemSize,
                                        mpLoadDmem, mLoadDmemSize,
                                        mpLoadCmem, mLoadCmemSize,
                                        &mpPmemLoadOal,
                                        &mpDmemLoadOal,
                                        &mpCmemLoadOal);

            apu_hal_GenLoadLL(mApexId, 
			                   mApuId, mLoadSegments, mpLoadPmem, mpLoadDmem, mpLoadCmem,
                              (mpPmemLoadOal != 0) ? (uint32_t)(uint64_t)OAL_MemoryReturnAddress(mpPmemLoadOal, ACCESS_PHY) : 0,
                              (mpDmemLoadOal != 0) ? (uint32_t)(uint64_t)OAL_MemoryReturnAddress(mpDmemLoadOal, ACCESS_PHY) : 0,
                              (mpCmemLoadOal != 0) ? (uint32_t)(uint64_t)OAL_MemoryReturnAddress(mpCmemLoadOal, ACCESS_PHY) : 0,
                              &mpLoadSegmentsLLOal);

            //only need to do this once for each load
            mProcessApuLoadFlag = 0;
         }

         apu_hal_LoadSegments_DMA(mApexId, mApuId, mAcfResInfo.dmaChIn[0], mpLoadSegmentsLLOal);

#else //use memcpy based segment loading (better for debugging)

         apu_hal_LoadSegment(mApexId, mApuId, mLoadSegments);
#endif
         apu_hal_Enable(mApexId, mApuId, 1);

         apumk_hal_host_com_rx(mApexId, (int)mApuId, &lMsg);

		 for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
		 {
			 //int32_t a = (int32_t)(int64_t)mPortInfoVec[i].mContigDataDesc.GetDataPtrPhys();
			 //int32_t b = a & 0xFFFFFF00;
			 
			 //if (a == b)
				OAL_MemoryFlushAndInvalidate((void *)((int64_t)mPortInfoVec[i].mContigDataDesc.GetDataPtrPhys() & 0x00000000FFFFFFFF), mPortInfoVec[i].mContigDataDesc.GetSpan() * mPortInfoVec[i].mContigDataDesc.GetHeight() * mPortInfoVec[i].mContigDataDesc.GetDimensions());
			if (mPortInfoVec[i].IsIndirect())
			{
				//a = (int32_t)(int64_t)mPortInfoVec[i].mOffsetArray.GetDataPtrPhys();
				//b = a & 0xFFFFFF00;
			 
				//if (a == b)
					OAL_MemoryFlushAndInvalidate((void *)((int64_t)mPortInfoVec[i].mOffsetArray.GetDataPtrPhys() & 0x00000000FFFFFFFF), mPortInfoVec[i].mOffsetArray.GetSpan() * mPortInfoVec[i].mOffsetArray.GetHeight() * mPortInfoVec[i].mOffsetArray.GetDimensions());
			}
		 }
         int32_t lApuProgFuncPtr = 0;
         KernelManager lKernelManager;
         lKernelManager.InitLoadKernelDB((int)mApuId, mLoadSegments);

         //the name of the apu program is the same as the process identifier
         if (lKernelManager.ReturnKernelID((int*)&lApuProgFuncPtr, RetProcessIdentifier().c_str()) != -1)
         {

            //**************************
            //EVERYTHING IS READY TO GO
            //**************************

            //ensure sequencer interrupts are properly configured
			if (mUseIRQ[mApexId]) 
			{
				seq_hal_mask_interrupts(mApexId, 0xFFFFFFFF);
				seq_hal_clear_interrupts(mApexId, 0xFFFFFFFF);
				global_hal_Apex2GlobalInterruptDisable(mApexId, APEX2_INTERRUPT_SEQUENCER);
				global_hal_Apex2GlobalInterruptEnable(mApexId, APEX2_INTERRUPT_SEQUENCER);
				
				seq_hal_mask_interrupts(mApexId, ~(1ul << mAcfResInfo.zeroSeqRes_Done));
			}
            apumk_hal_send_cmd(mApexId, mApuId, (int)lApuProgFuncPtr, lProgramParamSizeInWords, (const int32_t*)lProgramParams);
            //*(( unsigned int volatile*)(0x3009000c)) = 0xBEEF1111;//****TYCHEDEBUG
   #if (ACF_ENABLE_HW_PROFILING == 1)
            mcdma_hal_enable_perf_counter(mApexId);
   #endif
            apumk_hal_host_com_tx(mApexId, (int)mApuId, HOST_MSG_SENDCMD);
	    //for (int i = 0; i < 1000000; ++i);
            mProcessStartedFlag = 1;
         }
         else
         {
            printf("ACF_Process_APU::Start() -> '%s' could not be found in the APU load\n", RetProcessIdentifier().c_str());
            lRetVal = ACF_ERROR;
         }
      }
      else
      {
         printf("ACF_Process_APU::Start() -> HW resources could not be acquired\n");
         lRetVal = ACF_HW_RESOURCE_ERROR;
      }
   }
   else //GenApuProgramParams failed
   {
      lRetVal = ACF_ERROR;
   }
   

   return lRetVal;
}

int32_t ACF_Process_APU::Wait()
{
   int32_t lRetVal = 0;

   if (mProcessStartedFlag) //if the process was successfully started
   {
	  if (mUseIRQ)
	  {
		  global_hal_Apex2GlobalInterruptDisable(mApexId, APEX2_INTERRUPT_SEQUENCER);
		  seq_hal_mask_interrupts(mApexId, 0xFFFFFFFF);
		  seq_hal_clear_interrupts(mApexId, 0xFFFFFFFF);
	  }
	  else
	  {
		uint32_t lSeqIsrVal = 0;
		uint32_t lMask = (1ul<<mAcfResInfo.zeroSeqRes_Done);
		while ((lSeqIsrVal & lMask) != lMask)
		{
			lSeqIsrVal = seq_hal_query_interrupts(mApexId);
		}

		seq_hal_clear_interrupts(mApexId, lMask);
	  }
	  
      //make sure method execution has completed and disable the APU
      int32_t lMsg = 0;
      apumk_hal_host_com_rx(mApexId, (int)mApuId, &lMsg);
      apu_hal_Enable(mApexId, mApuId, 0);

      //retrieve runtime apu program return value
      int32_t lProgramRetVal = RET_VAL(lMsg);

      switch (lProgramRetVal)
      {
         case ACF_SUCCESS:
            //apu program execution completed without error
            break;
         case ACF_HW_RESOURCE_ERROR:
            printf("ACF_Process_APU::Wait() -> apu program runtime error (hardware resource)\n");
            lRetVal = ACF_HW_RESOURCE_ERROR;
            break;
         case ACF_MEMORY_ALLOCATION_ERROR:
            printf("ACF_Process_APU::Wait() -> apu program runtime error (memory allocation)\n");
            lRetVal = ACF_MEMORY_ALLOCATION_ERROR;
            break;
         default:
            printf("ACF_Process_APU::Wait() -> apu program runtime error (unknown error code)\n");
            lRetVal = ACF_ERROR;
            break;
      }

#if (ACF_ENABLE_HW_PROFILING == 1)
      mcdma_hal_disable_perf_counter(mApexId);
      printf("PRF(total,busrd,buswr) = (%d, %d, %d)\n", mcdma_hal_read_perf_counter_total(mApexId), mcdma_hal_read_perf_counter_busrd(mApexId), mcdma_hal_read_perf_counter_buswr(mApexId));
#endif

      //int32_t* lpSmem = (int32_t*)ReturnVirtualHwPtr(HW_REG_SMEM);
      //printf("APU Program Execution Cycles = %d\n", (int)(lpSmem[0xE1C/4]));

      //release HW resources
      if (DeallocateHwResources() != 0)
      {
         printf("ACF_Process_APU::Wait() -> HW resource deallocation failed\n");
         lRetVal = ACF_ERROR;
      }

      mProcessStartedFlag = 0;
   }
   else //program execution never started
   {
      printf("ACF_Process_APU::Wait() -> process was never started (i.e. nothing to wait for)\n");
      lRetVal = ACF_ERROR;
   }

   return lRetVal;
}

void ACF_Process_APU::SetApuLoadInfo(const LOAD_SEGMENT_t* lLoadSegments,
                                     const SEG_MEM_TYPE* lpLoadPmem, const int32_t lLoadPmemSize,
                                     const SEG_MEM_TYPE* lpLoadDmem, const int32_t lLoadDmemSize,
                                     const SEG_MEM_TYPE* lpLoadCmem, const int32_t lLoadCmemSize)
{
   mLoadSegments = lLoadSegments;
   mpLoadPmem    = lpLoadPmem;
   mLoadPmemSize = lLoadPmemSize;
   mpLoadDmem    = lpLoadDmem;
   mLoadDmemSize = lLoadDmemSize;
   mpLoadCmem    = lpLoadCmem;
   mLoadCmemSize = lLoadCmemSize;
}

void ACF_Process_APU::AddPort(std::string lPortIdentifier,
                              icp::DATATYPE lE0DataType,
                              int32_t lE0x, int32_t lE0y,
                              int32_t lChunkWidth, int32_t lChunkHeight,
                              int32_t lInputOutput,
                              int32_t lCmemDmem,
                              int32_t lNonstaticStatic,
                              int32_t lDirectIndirect,
                              int32_t lNonfixedFixed,
                              int32_t lRegFifo,
                              int32_t lLmIndex,
                              int32_t lRoiDepInfo)
{
   ACF_Process::AddPort(lPortIdentifier, lE0DataType, lE0x, lE0y,
                        lChunkWidth, lChunkHeight,
                        lInputOutput,
                        lNonstaticStatic,
                        lDirectIndirect,
                        lNonfixedFixed,
                        lRegFifo,
                        lLmIndex,
                        lRoiDepInfo);

   ACF_Process_PortInfo_APU lPortInfoApu;
   lPortInfoApu.mPortIdentifier = lPortIdentifier;
   lPortInfoApu.mCmemDmem = lCmemDmem;
   mPortInfoApuVec.push_back(lPortInfoApu);
}

int32_t ACF_Process_APU::DetectHwVersion()
{
   int32_t lRetVal = 0;

   mHwVersion = global_hal_RetHwVersion(mApexId);
   if (mHwVersion != 0x321 && mHwVersion != 0x642)
   {
      printf("ACF_Process_APU::DetectHwResources() -> unknown HW version detected (%d)\n", mHwVersion);
      lRetVal = 1;
   }

   return lRetVal;
}

int32_t ACF_Process_APU::SelectApuConfiguration(ACF_APU_CFG lApuConfig, int32_t lApexId)
{
   int lRetVal = ACF_SUCCESS;

   mApexId = lApexId;  //will be used once multiple APEX support is implemented

   if (lApuConfig != mApuCfg)
   {
      mApuCfg = lApuConfig;

      //if the apu configuration changes, scenario and apu load processing must be revisited
      mProcessApuLoadFlag = 1; //regenerate APU load linked list when start is called
      mpSelectedScenario = 0;  //if a scenario has already been chosen, it may no longer be valid
   }

   memset((void*)&mAcfResInfo, 0, sizeof(acf_res_info));

   if (0 == DetectHwVersion())
   {
      if (0x321 == mHwVersion)
      {
         switch (lApuConfig)
         {
         case ACF_APU_CFG__DEFAULT:
         case ACF_APU_CFG__APU_0_CU_0_31_SMEM_0_1:
            mApuId = 0;
            mCuArrayWidth = 32;
            mSmemBaseAddrOffset = 0;
            CfgResSet_321_ALL(&mAcfResInfo);

            InitApexResReq(mApexId, mResReqArray[0], RES__APEX__APU,   0);
            InitApexResReq(mApexId, mResReqArray[1], RES__APEX__CU_32, 0);
            InitApexResReq(mApexId, mResReqArray[2], RES__SMEM_64K,    0);
            mNumResReq = 3;

            break;
         default:
            printf("ACF_Process_APU::SelectApuConfiguration() -> unknown 321 APU configuration detected\n");
            lRetVal = ACF_ERROR;
            break;
         }
      }
      else if (0x642 == mHwVersion)
      {
         switch (lApuConfig)
         {
         case ACF_APU_CFG__DEFAULT:
         case ACF_APU_CFG__APU_0_CU_0_63_SMEM_0_3:
            mApuId = 0;
            mCuArrayWidth = 64;
            mSmemBaseAddrOffset = 0;
            CfgResSet_642_ALL(&mAcfResInfo);

            InitApexResReq(mApexId, mResReqArray[0], RES__APEX__APU,   0);
            InitApexResReq(mApexId, mResReqArray[1], RES__APEX__CU_32, 0);
            InitApexResReq(mApexId, mResReqArray[2], RES__APEX__CU_32, 1);
            InitApexResReq(mApexId, mResReqArray[3], RES__SMEM_64K,    0);
            InitApexResReq(mApexId, mResReqArray[4], RES__SMEM_64K,    1);
            mNumResReq = 5;

            break;
         case ACF_APU_CFG__APU_0_CU_0_31_SMEM_0_1:
            mApuId = 0;
            mCuArrayWidth = 32;
            mSmemBaseAddrOffset = 0;
            CfgResSet_642_HALF_APU0(&mAcfResInfo);

            InitApexResReq(mApexId, mResReqArray[0], RES__APEX__APU,   0);
            InitApexResReq(mApexId, mResReqArray[1], RES__APEX__CU_32, 0);
            InitApexResReq(mApexId, mResReqArray[2], RES__SMEM_64K,    0);
            mNumResReq = 3;

      break;
         case ACF_APU_CFG__APU_1_CU_32_63_SMEM_2_3:
            mApuId = 1;
            mCuArrayWidth = 32;
            mSmemBaseAddrOffset = (1024*64);
            CfgResSet_642_HALF_APU1(&mAcfResInfo);

            InitApexResReq(mApexId, mResReqArray[0], RES__APEX__APU,   1);
            InitApexResReq(mApexId, mResReqArray[1], RES__APEX__CU_32, 1);
            InitApexResReq(mApexId, mResReqArray[2], RES__SMEM_64K,    1);
            mNumResReq = 3;

            break;
         default:
            printf("ACF_Process_APU::SelectApuConfiguration() -> unknown 642 APU configuration detected\n");
            lRetVal = ACF_ERROR;
            break;
         }
      }

      DetectAvailApexMemory();
   }
   else
   {
      lRetVal = ACF_HW_DETECTION_ERROR;
   }

   return lRetVal;
}

int32_t ACF_Process_APU::DetectAvailApexMemory()
{
   int lRetVal = 0;

   //Based on the load determine CMEM/DMEM available to the scenario (for 'dynamic' ACF heap)
   //Note that memory size calculations (specifically related to SMEM) depend on the APU configuration

   int32_t lCmemReq  = 0;
   int32_t lDmemReq  = 0;
   int32_t lPmemReq  = 0;
   int32_t lSmemSize = 0;
   int32_t lCmemSize = 0;
   int32_t lTmp      = 0;

   if (0 == apu_hal_RetMemSizes(mApexId, Translate_AcfApuCfg_CmemIfApuCfg(mApuCfg, mHwVersion), &lSmemSize, &lCmemSize))
   {
      apu_hal_QueryLoad_MEM_REQ(mApexId, mLoadSegments, &lCmemReq, &lDmemReq, &lPmemReq);

      //PMEM offset/size calculation (PMEM will reside at the end of the contiguous SMEM region and the calculated offset
      //is relative to the start of the contiguous SMEM region)

#if 1    //WORKAROUND FOR CLOVER-386
      //for the purpose of this calculation, assume PMEM will occupy 'entire' SMEM banks to ensure there is no overlap between
      //the SMEM bank used for DMEM and the SMEM bank used for PMEM; round up required PMEM to multiple of SMEM_BANK_SIZE
      const int32_t SMEM_BANK_SIZE = (1024*32); //32K
      mPmemSizeInBytes = lPmemReq;
      if (mPmemSizeInBytes%SMEM_BANK_SIZE != 0)
         mPmemSizeInBytes = ((lPmemReq/SMEM_BANK_SIZE)+1)*SMEM_BANK_SIZE;
#else
      //ensure 16-byte alignment of PMEM region in SMEM
      lTmp = ((lPmemReq&0xF) == 0) ? 0 : (16-(lPmemReq&0xF));
      mPmemSizeInBytes = lPmemReq + lTmp;
#endif

      mPmemBaseAddrOffset = lSmemSize - mPmemSizeInBytes;

      if (mPmemSizeInBytes <= (lSmemSize - lDmemReq))
      {
         //create dmem/cmem heaps with remainder of SMEM region (between linked mapped DMEM at the top and PMEM at the bottom)

         //DMEM HEAP
         lTmp = ((lDmemReq&0x3) == 0) ? 0 : (4-(lDmemReq&0x3));
         mDmemHeapBaseAddrOffset = lDmemReq + lTmp; //assume DMEM heap follows 'blob' of DMEM reserved by the linker
         mDmemHeapSizeInBytes += lSmemSize - (lDmemReq + lTmp) - mPmemSizeInBytes;

         //CMEM HEAP
         lTmp = ((lCmemReq&0x3) == 0) ? 0 : (4-(lCmemReq&0x3));
         mCmemHeapBaseAddrOffset = lCmemReq + lTmp; //assume CMEM heap follows 'blob' of CMEM reserved by the linker
         mCmemHeapSizeInBytes = lCmemSize - (lCmemReq + lTmp);
      }
      else
      {
         printf("ACF_Process_APU::DetectAvailApexMemory() -> insufficient program memory space for %s (%d bytes required).\n", RetProcessIdentifier().c_str(), lPmemReq);
         lRetVal = 1;
      }

   #if 0
         printf("CMEM HEAP OFFSET = 0x%08X | CMEM HEAP SIZE = %d\n", mCmemHeapBaseAddrOffset, mCmemHeapSizeInBytes);
         printf("SMEM SIZE = %d (first %d bytes reserved by linker)\n", lSmemSize, lDmemReq);
         printf("   DMEM HEAP OFFSET = 0x%08X | DMEM HEAP SIZE = %d\n", mDmemHeapBaseAddrOffset, mDmemHeapSizeInBytes);
         printf("   PMEM OFFSET      = 0x%08X | PMEM SIZE = %d\n", mPmemBaseAddrOffset, mPmemSizeInBytes);
   #endif

   }
   else
   {
      printf("ACF_Process_APU::DetectAvailApexMemory() -> apu_hal_RetMemSizes(...) failed\n");
      lRetVal = 1;
   }

   return lRetVal;
}

int32_t VerifyROI(int32_t lWorstCaseDataComingFromSource,
                  int32_t lDataAvailFromSource,
                  int32_t lDepInfo)
{
   //the purpose of this function is to flag unsupported ROIs given the already calculated 'lWorstCaseDataComingFromSource' values
   //(i.e. trying to identify the unsupported 'crop' use case)

   int32_t lRetVal = 0;
   int32_t lDataComingFromSource = 0;

   if (lDepInfo >= lDataAvailFromSource)
      lDataComingFromSource = lDataAvailFromSource;
   else //(lDepInfo < lDataAvailFromSource)
      lDataComingFromSource = lDepInfo;

   if (lDataComingFromSource != lWorstCaseDataComingFromSource)
   {
      if (lDataComingFromSource > lWorstCaseDataComingFromSource)
         lRetVal = 1;
      else if (lDataComingFromSource != lDepInfo)
         lRetVal = 1;
   }

   return lRetVal;
}

//determine worst case additional 'from source' transfer requirements for each direction (for ROI)
//TODO: should probably be in ACF_Process - requires some cleanup related to CMEM/DMEM attribute info first
int32_t ACF_Process_APU::DetWorstCaseRoiInfo()
{
   int32_t lRetVal = 0;

   mRoiInfoL = 0;
   mRoiInfoR = 0;
   mRoiInfoT = 0;
   mRoiInfoB = 0;

   int32_t lTmp, lDepDataAvailFromSource, lDepInfo;

   for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
   {
      if (mPortInfoVec[i].IsNonStatic() && mPortInfoVec[i].IsInput() && mPortInfoApuVec[i].IsCmem())
      {
         //TOP
         lDepDataAvailFromSource = mPortInfoVec[i].mContigDataDesc.GetRoiInfoT();
         lDepInfo = mPortInfoVec[i].mRoiDepInfoN;
         lTmp = lDepDataAvailFromSource;
         if (lDepDataAvailFromSource >= lDepInfo)
            lTmp = lDepInfo;
         if (lTmp > mRoiInfoT)
            mRoiInfoT = lTmp;

         //BOTTOM
         lDepDataAvailFromSource = mPortInfoVec[i].mContigDataDesc.GetRoiInfoB();
         lDepInfo = mPortInfoVec[i].mRoiDepInfoS;
         lTmp = lDepDataAvailFromSource;
         if (lDepDataAvailFromSource >= lDepInfo)
            lTmp = lDepInfo;
         if (lTmp > mRoiInfoB)
            mRoiInfoB = lTmp;

         //LEFT
         lDepDataAvailFromSource = mPortInfoVec[i].mContigDataDesc.GetRoiInfoL();
         lDepInfo = mPortInfoVec[i].mRoiDepInfoW;
         lTmp = lDepDataAvailFromSource;
         if (lDepDataAvailFromSource >= lDepInfo)
            lTmp = lDepInfo;
         if (lTmp > mRoiInfoL)
            mRoiInfoL = lTmp;

         //RIGHT
         lDepDataAvailFromSource = mPortInfoVec[i].mContigDataDesc.GetRoiInfoR();
         lDepInfo = mPortInfoVec[i].mRoiDepInfoE;
         lTmp = lDepDataAvailFromSource;
         if (lDepDataAvailFromSource >= lDepInfo)
            lTmp = lDepInfo;
         if (lTmp > mRoiInfoR)
            mRoiInfoR = lTmp;
      }
   }

   //VERIFY THAT ROI SCENARIO IS SUPPORTED

   for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
   {
      if (mPortInfoVec[i].IsNonStatic() && mPortInfoVec[i].IsInput() && mPortInfoApuVec[i].IsCmem())
      {
         lRetVal |= VerifyROI(mRoiInfoT, mPortInfoVec[i].mContigDataDesc.GetRoiInfoT(), mPortInfoVec[i].mRoiDepInfoN);
         lRetVal |= VerifyROI(mRoiInfoB, mPortInfoVec[i].mContigDataDesc.GetRoiInfoB(), mPortInfoVec[i].mRoiDepInfoS);
         lRetVal |= VerifyROI(mRoiInfoL, mPortInfoVec[i].mContigDataDesc.GetRoiInfoL(), mPortInfoVec[i].mRoiDepInfoW);
         lRetVal |= VerifyROI(mRoiInfoR, mPortInfoVec[i].mContigDataDesc.GetRoiInfoR(), mPortInfoVec[i].mRoiDepInfoE);

         if (lRetVal)
         {
            printf("ACF_Process_APU::DetWorstCaseRoiInfo() -> multiple ROIs have been specified that are not compatible\n");
            break;
         }
      }
   }

   return lRetVal;
}

//********************************************************************
//METHODS RELATED TO SCENARIO SELECTION
//********************************************************************

/*
Select optimal scenario based on IO configuration.
lUserSelPort, lUserSelChunkWidth, and lUserSelChunkHeight are for advanced use
where the user wants to choose a scenario based on a specific width/height/both for a specific port
*/

acf_scenario* SelectOptimalScenario(std::vector<ACF_Process_PortInfo> &lPortInfoVec,
                                    int32_t lRoiInfoL, int32_t lRoiInfoR,
                                    int32_t lCuArrayWidth, int32_t lAvailableCmem, int32_t lAvailableDmem,
                                    acf_scenario_list* lpScenarioList,
                                    std::string lUserSelPort,
                                    int32_t     lUserSelChunkWidth,
                                    int32_t     lUserSelChunkHeight)
{
   ACF_Process_PortInfo* lpPortInfo = 0;
   acf_scenario* lpSelectedScenario = 0;
   int32_t lChunkWidth = 0;
   int32_t lChunkHeight = 0;
   int32_t lFlagNotEnoughMemory = 0;

   if (lpScenarioList->numScenarios == 1) //there is only a single scenario available
   {
      if (lUserSelPort != "") //user has singled out a specific port so find it
      {
         for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
         {
            if (lPortInfoVec[i].mPortIdentifier == lUserSelPort)
            {
               lpPortInfo = &lPortInfoVec[i];
               break;
            }
         }

         if (lpPortInfo)
         {
            int32_t lTmpChunkWidth = lpScenarioList->pScenarioList[0].pBufferData[lpPortInfo->mLmIndex].chunkWidth;
            int32_t lTmpChunkHeight = lpScenarioList->pScenarioList[0].pBufferData[lpPortInfo->mLmIndex].chunkHeight;

            if ((lUserSelChunkWidth == 0) || (lUserSelChunkWidth != 0 && lUserSelChunkWidth == lTmpChunkWidth))
            {
               if ((lUserSelChunkHeight == 0) || (lUserSelChunkHeight != 0 && lUserSelChunkHeight == lTmpChunkHeight))
               {
                  if (lpScenarioList->pScenarioList[0].cmemReq <= lAvailableCmem &&
                      lpScenarioList->pScenarioList[0].dmemReq <= lAvailableDmem)
                  {
                     lpSelectedScenario = &lpScenarioList->pScenarioList[0];
                  }
                  else
                  {
                     lFlagNotEnoughMemory = 1;
                  }
               }
               else
               {
                  printf("SelectOptimalScenario() -> no scenario exists where port '%s' has a chunk height of %d.\n",
                       lUserSelPort.c_str(), lUserSelChunkHeight);
               }
            }
            else
            {
				printf("SelectOptimalScenario() -> no scenario exists where port '%s' has a chunk width of %d.\n",
                       lUserSelPort.c_str(), lUserSelChunkWidth);
            }
         }
         else
         {
            printf("SelectOptimalScenario() -> port '%s' cannot be found\n", lUserSelPort.c_str());
         }
      }
      else if (lUserSelPort == "") //no specific port has been singled out
      {
         if (lpScenarioList->pScenarioList[0].cmemReq <= lAvailableCmem &&
             lpScenarioList->pScenarioList[0].dmemReq <= lAvailableDmem)
         {
            lpSelectedScenario = &lpScenarioList->pScenarioList[0];
         }
         else
         {
            lFlagNotEnoughMemory = 1;
         }
      }

      if (lFlagNotEnoughMemory)
      {
         printf("SelectOptimalScenario() -> The single available scenario overflows available APEX memory resources (CMEM: %d/%d DMEM: %d/%d)\n",
			  lpScenarioList->pScenarioList[0].cmemReq, lAvailableCmem, lpScenarioList->pScenarioList[0].dmemReq, lAvailableDmem);
      }
   }
   else //multiple scenarios available
   {
      //Decision Critiera (2D case):
      //1) choose a chunk width that divides nicely into the input width and uses as many CUs as possible
      //2) using the width chosen in 1), find the scenario with the largest chunk height that divides
      //   nicely into the input height and deosn't exceed available APEX memory resources

      //if it is indicated that specific port should be used then use it to make the decision
      //else use the first direct non-fixed port encountered
      for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
      {
         if (lUserSelPort == "")
         {
            //an 'indirect' port cannot be used for scenario selection since the framework has no way of choosing
            //a meaningful chunk size based on an offset array
            if (lPortInfoVec[i].IsNonFixed() && lPortInfoVec[i].IsDirect())
            {
               lpPortInfo = &lPortInfoVec[i];
               break;
            }
         }
         else //lUserSelPort != ""
         {
            if (lPortInfoVec[i].IsNonFixed() && lPortInfoVec[i].IsDirect() && lPortInfoVec[i].mPortIdentifier == lUserSelPort)
            {
               lpPortInfo = &lPortInfoVec[i];
               break;
            }
         }
      }

      if (lpPortInfo)
      {
         //---------------------------------
         //select an appropriate chunk width
         //---------------------------------

         icp::DataDescriptor* lpCDD = &lpPortInfo->mContigDataDesc;

         //choose a suitable width assuming the most important chunk size selection criteria is to use as many CUs as possible
         //(the chosen width must be such that it fits into the SIMD array AND it exists in the scenario table)
         if (lUserSelChunkWidth != 0) //user wants a specific chunk width
         {
            lChunkWidth = lUserSelChunkWidth;
         }
         else //pick the 'optimal' width given the array size
         {
            for (int32_t j=lCuArrayWidth; j>=1; j--)
            {
               if (lpCDD->GetWidth()%j == 0)
               {
                  int32_t lCandidateChunkWidth = lpCDD->GetWidth()/j;

                  //ROI STUFF:
                  //assuming 'lCandidateChunkWidth, determine the number of additional CUs required to accommodate
                  //padding data from source (i.e. data beyond core data); currently ROUNDED UP to lCandidateChunkWidth
                  //since ACF is still only processing chunks

                  int32_t lAdditionalCusReq = ((lRoiInfoL+lCandidateChunkWidth-1)/lCandidateChunkWidth) +
                                              ((lRoiInfoR+lCandidateChunkWidth-1)/lCandidateChunkWidth);

                  if (lAdditionalCusReq <= (lCuArrayWidth - j))
                  {
                     for (int32_t k=0; k<lpScenarioList->numScenarios; k++)
                     {
                        if (lpCDD->GetWidth()/j == lpScenarioList->pScenarioList[k].pBufferData[lpPortInfo->mLmIndex].chunkWidth)
                        {
                           lChunkWidth = lpCDD->GetWidth()/j;
                           break;
                        }
                     }
                  }
               }
               if (lChunkWidth != 0)
                  break;
            }
         }

         //----------------------------------
         //select an appropriate chunk height
         //----------------------------------

         for (int32_t k=0; k<lpScenarioList->numScenarios; k++)
         {
            int32_t lTmpChunkWidth = lpScenarioList->pScenarioList[k].pBufferData[lpPortInfo->mLmIndex].chunkWidth;
            int32_t lTmpChunkHeight = lpScenarioList->pScenarioList[k].pBufferData[lpPortInfo->mLmIndex].chunkHeight;

            if (lTmpChunkWidth == lChunkWidth)
            {
               if (lUserSelChunkHeight != 0) //user wants a specific chunk height
               {
                  if (lTmpChunkHeight == lUserSelChunkHeight &&
                      (lpScenarioList->pScenarioList[k].cmemReq <= lAvailableCmem) &&
                      (lpScenarioList->pScenarioList[k].dmemReq <= lAvailableDmem))
                  {
                     lpSelectedScenario = &lpScenarioList->pScenarioList[k];
                     break;
                  }
               }
               else //acf is choosing the chunk height
               {
                  if ((lTmpChunkHeight > lChunkHeight) &&
                      (lpCDD->GetHeight()%lTmpChunkHeight == 0) &&
                      (lpScenarioList->pScenarioList[k].cmemReq <= lAvailableCmem) &&
                      (lpScenarioList->pScenarioList[k].dmemReq <= lAvailableDmem))
                  {
                     lChunkHeight = lTmpChunkHeight;
                     lpSelectedScenario = &lpScenarioList->pScenarioList[k];
                  }
               }
            }
         }
      }
      else //valid port was not found
      {
         if (lUserSelPort == "") //a specific port was not specified
         {
            printf("SelectOptimalScenario() -> A valid scenario selection port cannot be found (must be a non-fixed direct port)\n");
         }
         else //a specific port was specified
         {
            printf("SelectOptimalScenario() -> port '%s' cannot be found or cannot be used for scenario selection (must be a non-fixed direct port)\n", lUserSelPort.c_str());
         }
      }
   }

   return lpSelectedScenario;
}

int32_t ACF_Process_APU::SelectScenario(std::string lPortIdentifier, int32_t lChunkWidth, int32_t lChunkHeight)
{
   int lRetVal = ACF_SUCCESS;

   //Consider this scenario: a graph has  a single input, no spatial dep, input data region = 1024x32, and NUMCUs = 32
   //Should ACF consider this a 2D processing pipeline with eight tiles of 32x4 chunks (for example) or should it consider it
   //a 1D processing pipeline with eight tiles of 4x32 chunks (for example)?
   //***For now, ACF will perform scenario selection assuming that a 2D processing pipeline will be established.  If the user wants
   //the processing pipeline to be treated as 1D, they will have to call SelectScenario with a suitable chunk width and a chunk height that is equal
   //to the height of the data region they are processing.

   if (mRoiInfoManualFlag != 1)
   {
      if (DetWorstCaseRoiInfo() != 0) //check applicable inputs for ROI information
      {
         lRetVal = ACF_ERROR;
         return lRetVal;
      }
   }

   acf_scenario* lpScenario = SelectOptimalScenario(mPortInfoVec, mRoiInfoL, mRoiInfoR,
         mCuArrayWidth, mCmemHeapSizeInBytes, mDmemHeapSizeInBytes, mpScenarioList,
         lPortIdentifier, lChunkWidth, lChunkHeight);

   if (lpScenario != 0)
   {
      mpSelectedScenario = lpScenario;
   }
   else
   {
      if (lPortIdentifier != "" && lChunkWidth != 0 && lChunkHeight != 0)
      {
         printf("ACF_Process_APU::SelectScenario() -> The user-specified scenario (port %s = [%d,%d]) could not be found, or there is not enough available memory\n",
			   lPortIdentifier.c_str(), lChunkWidth, lChunkHeight);
      }
      else
      {
         printf("ACF_Process_APU::SelectScenario() -> A suitable scenario could not be found\n");
      }
      lRetVal = ACF_SCENARIO_DETECTION_ERROR;
   }

   return lRetVal;
}

int32_t ACF_Process_APU::QueryPortChunkSize(std::string lPortIdentifier, int32_t& lChunkWidth, int32_t& lChunkHeight)
{
   int32_t lRetVal = 0;
   int32_t lPortIdentifierFound = 0;

   if (mpSelectedScenario != 0)
   {
      for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
      {
         if(lPortIdentifier == mPortInfoVec[i].mPortIdentifier)
         {
            lPortIdentifierFound = 1;
            lChunkWidth  = mpSelectedScenario->pBufferData[mPortInfoVec[i].mLmIndex].chunkWidth;
            lChunkHeight = mpSelectedScenario->pBufferData[mPortInfoVec[i].mLmIndex].chunkHeight;
            break;
         }
      }

      if (!lPortIdentifierFound)
      {
         printf("ACF_Process_APU::QueryPortChunkSize -> Port '%s' could not be found\n", lPortIdentifier.c_str());
         lRetVal = 1;
      }
   }
   else
   {
      printf("ACF_Process_APU::QueryPortChunkSize -> No scenario has been selected\n");
      lRetVal = 1;
   }

   return lRetVal;
}

//Override the chunk size of a port for the currently 'selected' scenario (must be used in tandem with 'SelectScenario')
int32_t ACF_Process_APU::OverridePortChunkSize(std::string lPortIdentifier, int32_t lChunkWidth, int32_t lChunkHeight)
{
   int32_t lRetVal = 1;
   int32_t lPortFoundFlag = 0;

   //only proceed if a specific scenario has already been selected
   if (mpSelectedScenario != 0)
   {
      for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
      {
         ACF_Process_PortInfo* lpPortInfo = &mPortInfoVec[i];
         ACF_Process_PortInfo_APU* lpPortInfoApu = &mPortInfoApuVec[i];
         if (lpPortInfo->mPortIdentifier == lPortIdentifier)
         {
            lPortFoundFlag = 1;

            /*
            Existing CMEM/DMEM req for the scenario is known.  Calculate and subtract the 'original' cost of this
            buffer and add the cost of the updated size.  Make sure the new 'total'
            doesn't exceed the available CMEM/DMEM!  Update the scenario description accordingly.
            */

            int32_t lLmIndex = lpPortInfo->mLmIndex;

            ACF_LocalMemDesc lLmDescOrig;
            lLmDescOrig.e0 = lpPortInfo->mE0;
            lLmDescOrig.chunkWidth = mpSelectedScenario->pBufferData[lLmIndex].chunkWidth;
            lLmDescOrig.chunkHeight = mpSelectedScenario->pBufferData[lLmIndex].chunkHeight;
            lLmDescOrig.numBuffers = mpSelectedScenario->pBufferData[lLmIndex].numBuffers;
            lLmDescOrig.padding.w = ((mpSelectedScenario->pBufferData[lLmIndex].padding>>12)&0xF);
            lLmDescOrig.padding.e = ((mpSelectedScenario->pBufferData[lLmIndex].padding>>8)&0xF);
            lLmDescOrig.padding.n = ((mpSelectedScenario->pBufferData[lLmIndex].padding>>4)&0xF);
            lLmDescOrig.padding.s = ((mpSelectedScenario->pBufferData[lLmIndex].padding>>0)&0xF);
            lLmDescOrig.chunkE0Span = (lLmDescOrig.chunkWidth + lLmDescOrig.padding.e + lLmDescOrig.padding.w)*RetE0SizeInBytes(&lLmDescOrig.e0);

            ACF_LocalMemDesc lLmDescNew = lLmDescOrig;
            lLmDescNew.chunkWidth = lChunkWidth;
            lLmDescNew.chunkHeight = lChunkHeight;
            lLmDescNew.chunkE0Span = (lLmDescNew.chunkWidth + lLmDescNew.padding.e + lLmDescNew.padding.w)*RetE0SizeInBytes(&lLmDescNew.e0);

            if (lpPortInfoApu->IsCmem())
            {
               int32_t lCmemReq = mpSelectedScenario->cmemReq - RetLocalMemDescSizeInBytes(&lLmDescOrig) + RetLocalMemDescSizeInBytes(&lLmDescNew);
               if (lCmemReq <= mCmemHeapSizeInBytes)
               {
                  mpSelectedScenario->pBufferData[lLmIndex].chunkWidth = lChunkWidth;
                  mpSelectedScenario->pBufferData[lLmIndex].chunkHeight = lChunkHeight;
                  mpSelectedScenario->cmemReq = lCmemReq;
                  lRetVal = 0;
               }
               else
               {
                  printf("ACF_Process_APU::OverridePortChunkSize -> Given the selected scenario, changing the chunk size of port %s to %d x %d exceeds available CMEM by %d bytes\n",
					   lPortIdentifier.c_str(), lChunkWidth, lChunkHeight, lCmemReq-mCmemHeapSizeInBytes);
               }
            }
            else //DMEM
            {
               int32_t lDmemReq = mpSelectedScenario->dmemReq - RetLocalMemDescSizeInBytes(&lLmDescOrig) + RetLocalMemDescSizeInBytes(&lLmDescNew);
               if (lDmemReq <= mDmemHeapSizeInBytes)
               {
                  mpSelectedScenario->pBufferData[lLmIndex].chunkWidth = lChunkWidth;
                  mpSelectedScenario->pBufferData[lLmIndex].chunkHeight = lChunkHeight;
                  mpSelectedScenario->dmemReq = lDmemReq;
                  lRetVal = 0;
               }
               else
               {
                  printf("ACF_Process_APU::OverridePortChunkSize -> Given the selected scenario, changing the chunk size of port %s to %d x %d exceeds available DMEM by %d bytes\n",
					   lPortIdentifier.c_str(), lChunkWidth, lChunkHeight, lDmemReq-mDmemHeapSizeInBytes);
               }
            }

            break;
         }
      }

      if (0 == lPortFoundFlag)
      {
         printf("ACF_Process_APU::OverridePortChunkSize -> Couldn't find a port with the identifier %s\n");
      }
   }

   return lRetVal;
}

void ACF_Process_APU::CfgScenarios(acf_scenario_list* lpScenarioList)
{
   mpScenarioList = lpScenarioList;
}

int32_t ACF_Process_APU::RetCuArrayWidth()
{
   return mCuArrayWidth;
}

int32_t ACF_Process_APU::RetCmemHeapSizeInBytes()
{
   return mCmemHeapSizeInBytes;
}

acf_scenario* ACF_Process_APU::RetSelectedScenario()
{
   return mpSelectedScenario;
}

int32_t ACF_Process_APU::AllocateHwResources()
{
   int32_t lRetVal = ACF_SUCCESS;

   if(LIB_SUCCESS == ResMgr_User_Allocate(mApexId, UserTypeId(mApexId, USER__ACF), &mUserId))
   {
      if(LIB_SUCCESS == ResMgr_Resource_Allocate_TI(mApexId, mUserId, mResReqArray, mNumResReq, mResAcqArray, mNumResReq))
      {
         //allocations successful
      }
      else //resource allocation failed
      {
         ResMgr_User_Deallocate(mApexId, mUserId); //decallocate user
         lRetVal = ACF_HW_RESOURCE_ERROR;
      }
   }
   else //failed to allocate a user slot
   {
      lRetVal = ACF_HW_RESOURCE_ERROR;
   }

   return lRetVal;
}

int32_t ACF_Process_APU::DeallocateHwResources()
{
   int lRetVal = ACF_ERROR;
   
   if (LIB_SUCCESS == ResMgr_Resource_Deallocate(mApexId, mUserId, mResAcqArray, mNumResReq))
   {
      if (LIB_SUCCESS == ResMgr_User_Deallocate(mApexId, mUserId))
      {
         lRetVal = ACF_SUCCESS;
      }
   }

   return lRetVal;
}

//For now, ACF will take ownership of as many resources as it can for a given configuration
//(even if it cannot necessarily utilize them all).  For example, if a process is executing with the
//ACF_APU_CFG__APEX0_APU_0_CU_0_63_SMEM_0_3 configuration ACF will take everything (all DMAs, STREAMS, MCE, etc.).
//In more advanced cases the decision about which resources to give a specific process will depend on a number of
//factors and may require user intervention to get the optimal resource allocation.
void CfgResSet_321_ALL(acf_res_info* lpAcfResInfo)
{
   lpAcfResInfo->numDmaChIn = 2;
      lpAcfResInfo->dmaChIn[0] = 0;
      lpAcfResInfo->dmaChIn[1] = 1;

   lpAcfResInfo->numStreamInChForDma = 1;
      lpAcfResInfo->streamInChForDma[0] = 1;

   lpAcfResInfo->numDmaChOut = 2;
      lpAcfResInfo->dmaChOut[0] = 2;
      lpAcfResInfo->dmaChOut[1] = 3;

   lpAcfResInfo->numStreamOutChForDma = 1;
      lpAcfResInfo->streamOutChForDma[0] = 0;

   lpAcfResInfo->numMceChIn = 1;
      lpAcfResInfo->mceChIn[0] = 0;

   lpAcfResInfo->numStreamInForMce = 1;
      lpAcfResInfo->streamInChForMce[0] = 0;

   lpAcfResInfo->numFixedSeqRes = 20;
      for (int i=0; i<20; i++)
         lpAcfResInfo->fixedSeqRes[i] = i;

   lpAcfResInfo->numProcIntSeqRes = 3;
      lpAcfResInfo->procIntSeqRes[0] = 1;
      lpAcfResInfo->procIntSeqRes[1] = 2;
      lpAcfResInfo->procIntSeqRes[2] = 3;

   lpAcfResInfo->zeroSeqRes_Done = 30;
   lpAcfResInfo->procIdSeqRes = 0;
   lpAcfResInfo->apuId = 0;
}

void CfgResSet_642_ALL(acf_res_info* lpAcfResInfo)
{
   lpAcfResInfo->numDmaChIn = 4;
      lpAcfResInfo->dmaChIn[0] = 0;
      lpAcfResInfo->dmaChIn[1] = 1;
      lpAcfResInfo->dmaChIn[2] = 2;
      lpAcfResInfo->dmaChIn[3] = 3;

   lpAcfResInfo->numStreamInChForDma = 2;
      lpAcfResInfo->streamInChForDma[0] = 2;
      lpAcfResInfo->streamInChForDma[1] = 3;

   lpAcfResInfo->numDmaChOut = 4;
      lpAcfResInfo->dmaChOut[0] = 4;
      lpAcfResInfo->dmaChOut[1] = 5;
      lpAcfResInfo->dmaChOut[2] = 6;
      lpAcfResInfo->dmaChOut[3] = 7;

   lpAcfResInfo->numStreamOutChForDma = 2;
      lpAcfResInfo->streamOutChForDma[0] = 0;
      lpAcfResInfo->streamOutChForDma[1] = 1;

   lpAcfResInfo->numMceChIn = 2;
      lpAcfResInfo->mceChIn[0] = 0;
      lpAcfResInfo->mceChIn[1] = 1;

   lpAcfResInfo->numStreamInForMce = 2;
      lpAcfResInfo->streamInChForMce[0] = 0;
      lpAcfResInfo->streamInChForMce[1] = 1;

   lpAcfResInfo->numFixedSeqRes = 20;
      for (int i=0; i<20; i++)
         lpAcfResInfo->fixedSeqRes[i] = i;

   lpAcfResInfo->numProcIntSeqRes = 3;
      lpAcfResInfo->procIntSeqRes[0] = 1;
      lpAcfResInfo->procIntSeqRes[1] = 2;
      lpAcfResInfo->procIntSeqRes[2] = 3;

   lpAcfResInfo->zeroSeqRes_Done = 30;
   lpAcfResInfo->procIdSeqRes = 0;
   lpAcfResInfo->apuId = 0;
}

void CfgResSet_642_HALF_APU0(acf_res_info* lpAcfResInfo)
{
   lpAcfResInfo->numDmaChIn = 2;
      lpAcfResInfo->dmaChIn[0] = 0;
      lpAcfResInfo->dmaChIn[1] = 1;

   lpAcfResInfo->numStreamInChForDma = 1;
      lpAcfResInfo->streamInChForDma[0] = 2;

   lpAcfResInfo->numDmaChOut = 2;
      lpAcfResInfo->dmaChOut[0] = 2;
      lpAcfResInfo->dmaChOut[1] = 3;

   lpAcfResInfo->numStreamOutChForDma = 1;
      lpAcfResInfo->streamOutChForDma[0] = 0;

   lpAcfResInfo->numMceChIn = 1;
      lpAcfResInfo->mceChIn[0] = 0;

   lpAcfResInfo->numStreamInForMce = 1;
      lpAcfResInfo->streamInChForMce[0] = 0;

   lpAcfResInfo->numFixedSeqRes = 10;
      for (int i=0; i<10; i++)
         lpAcfResInfo->fixedSeqRes[i] = i;

   lpAcfResInfo->numProcIntSeqRes = 3;
      lpAcfResInfo->procIntSeqRes[0] = 1;
      lpAcfResInfo->procIntSeqRes[1] = 2;
      lpAcfResInfo->procIntSeqRes[2] = 3;

   lpAcfResInfo->zeroSeqRes_Done = 30;
   lpAcfResInfo->procIdSeqRes = 0;
   lpAcfResInfo->apuId = 0;
}

void CfgResSet_642_HALF_APU1(acf_res_info* lpAcfResInfo)
{
   lpAcfResInfo->numDmaChIn = 2;
      lpAcfResInfo->dmaChIn[0] = 4;
      lpAcfResInfo->dmaChIn[1] = 5;

   lpAcfResInfo->numStreamInChForDma = 1;
      lpAcfResInfo->streamInChForDma[0] = 3;

   lpAcfResInfo->numDmaChOut = 2;
      lpAcfResInfo->dmaChOut[0] = 6;
      lpAcfResInfo->dmaChOut[1] = 7;

   lpAcfResInfo->numStreamOutChForDma = 1;
      lpAcfResInfo->streamOutChForDma[0] = 1;

   lpAcfResInfo->numMceChIn = 1;
      lpAcfResInfo->mceChIn[0] = 1;

   lpAcfResInfo->numStreamInForMce = 1;
      lpAcfResInfo->streamInChForMce[0] = 1;

   lpAcfResInfo->numFixedSeqRes = 10;
      for (int i=0; i<10; i++)
         lpAcfResInfo->fixedSeqRes[i] = 10+i;

   lpAcfResInfo->numProcIntSeqRes = 3;
      lpAcfResInfo->procIntSeqRes[0] = 4;
      lpAcfResInfo->procIntSeqRes[1] = 5;
      lpAcfResInfo->procIntSeqRes[2] = 6;

   lpAcfResInfo->zeroSeqRes_Done = 31;
   lpAcfResInfo->procIdSeqRes = 1;
   lpAcfResInfo->apuId = 1;
}
