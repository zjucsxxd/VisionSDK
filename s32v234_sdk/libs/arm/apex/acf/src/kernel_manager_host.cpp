/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#include <apex_apu_hal.h>
#include <apu_microkernel.h>
#include <apex_apu_microkernel_hal.h>
#include <string>
#include <string.h>
#include <oal.h>

#include "kernel_manager.h"


//--------------------------------------------------------------------
// !!!!!! IMPORTANT: HAS TO MATCH WITH WHAT'S BUILT IN THE LOAD !!!!!!
// ONLY USED BY HOST
// IDEALLY THIS LIST SHOULD BE GENERATED FROM THE LOAD
//--------------------------------------------------------------------


KernelManager::KernelManager()
{
   mkernel_list = 0;
   mkernel_num  = 0;
}
KernelManager::~KernelManager()
{
   if (mkernel_list != 0)
   {
      OAL_MemoryFree(mkernel_list);
      mkernel_list = 0;
      mkernel_num  = 0;
   }
}

int KernelManager::InitLoadKernelDB( int apuid, const LOAD_SEGMENT_t* seg_addr)
{

   int rval = 0;
   // Load the APU with HARD CODED outputs from
   // dart/bridge
   // --------------------------------------------------------------
   // Load kernel database
   int n = 0;
   int32_t memory_type = (int32_t)seg_addr[n][0];
   while (memory_type != -1)
   {

      uint32_t dst_offset  = seg_addr[n][2];

      int kn = 0;
      if ((dst_offset == DMEM_KERNEL_DB_OFFSET) && (memory_type == APU_LOAD_ID_DMEM))
      {
         uint32_t* src_ptr    = (uint32_t*)seg_addr[n][1];
         kn = src_ptr[0];

         if (kn != 0)
         {
            mkernel_num  = kn;
            mkernel_list = (KERNEL_INFO*)OAL_MemoryAllocFlag(
                                       (sizeof(KERNEL_INFO)* kn),
                                       OAL_MEMORY_FLAG_CONTIGUOUS |
                                       OAL_MEMORY_FLAG_ZERO);

            memcpy(mkernel_list, (KERNEL_INFO*)(&(src_ptr[1])), sizeof(KERNEL_INFO)* kn);

         }
         break;
      }

      memory_type = (int32_t)seg_addr[++n][0];
   }

   return rval;

} // End of the APULoadProgram function.

int KernelManager::ReturnKernelID( int* kernelID, const char* kernelName)
{
   int rval    = 0;
   int kid     = 0;
   int found   = 0;
   std::string s1(kernelName);
   do
   {
      std::string s2(mkernel_list[kid].kernel_name);

      if (s1 == s2)
      {
         found = 1;
         kernelID[0] = mkernel_list[kid].kernel_addr;
         break;
      }
      else kid++;
   } while (kid <mkernel_num);

   if (found == 0) rval = -1;

   return rval;
}
