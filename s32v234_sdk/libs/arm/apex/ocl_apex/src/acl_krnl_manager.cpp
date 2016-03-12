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

#include <string>
#include <string.h>
#include <oal.h>

#include "apex/acl_krnl_manager.h"



acl_krnl_manager::acl_krnl_manager()
{
   mkernel_list = 0;
   mkernel_num  = 0;
   mkernel_db   = 0;
   mseg_addr    = 0;
}

acl_krnl_manager::~acl_krnl_manager()
{
   if (mkernel_db != 0)
   {
      OAL_MemoryFree(mkernel_db);

      mkernel_num  = 0;
   }
   if (mkernel_list != 0)
   {
      OAL_MemoryFree(mkernel_list);
      mkernel_list = 0;
   }
}


int acl_krnl_manager::init( int /*apuid*/, const LOAD_SEGMENT_t* seg_addr)
{

   int rval = 0;

   // cl program loading
   int n = 0;

   // if not loaded already
   if (mseg_addr != seg_addr)
   {
      // free previously allocated memory
      if (mkernel_db != 0)
      {
         OAL_MemoryFree(mkernel_db);

         mkernel_num  = 0;
      }
      if (mkernel_list != 0)
      {
         OAL_MemoryFree(mkernel_list);
         mkernel_list = 0;
      }

      // allocate new memory
      int32_t memory_type = (int32_t)seg_addr[n][0];
      while (memory_type != -1)
      {
         // dst: 32-bit system
         // src: 32/64-bit system
         uint32_t dst_offset   = seg_addr[n][2];
         unsigned int* src_ptr = (unsigned int*)seg_addr[n][1];

         int kn = 0;
         if ((dst_offset == DMEM_CL_DB_OFFSET) && (memory_type == APU_LOAD_ID_DMEM))
         {

            kn = src_ptr[0];

            if (kn != 0)
            {
               mkernel_num  = kn;
               mkernel_db = (CL_KRNL_DB_ENTRY*)OAL_MemoryAllocFlag(
                                          (sizeof(CL_KRNL_DB_ENTRY)* kn),
                                          OAL_MEMORY_FLAG_CONTIGUOUS |
                                          OAL_MEMORY_FLAG_ZERO);

               memcpy(mkernel_db, (CL_KRNL_DB_ENTRY*)(&(src_ptr[1])), sizeof(CL_KRNL_DB_ENTRY)* kn);

            }
         }
         else if  ((dst_offset == DMEM_CL_MD_OFFSET) && (memory_type == APU_LOAD_ID_DMEM))
         {
            if (mkernel_num!=0)
            {
               CL_KRNL_MD* tptr = (CL_KRNL_MD*)src_ptr;
               mkernel_list = (acl_kernel*)OAL_MemoryAllocFlag(
                                          (sizeof(acl_kernel)* mkernel_num),
                                          OAL_MEMORY_FLAG_CONTIGUOUS |
                                          OAL_MEMORY_FLAG_ZERO);
               for (int i=0; i<mkernel_num; i++)
               {
                  CL_KRNL_MD* dptr = &(mkernel_list[i].krnl_md);
                  memcpy(dptr,
                         (CL_KRNL_MD*)(tptr),
                         sizeof(CL_KRNL_MD));
                  tptr++;
               }

            }
         }

         memory_type = (int32_t)seg_addr[++n][0];
      }
   }

   return rval;

} // End of the APULoadProgram function.

#if 1
int acl_krnl_manager::ret_id( int* kernelID, const char* kernelName)
{
   int rval    = 0;
   int kid     = 0;
   int found   = 0;
   std::string *s1;
	s1 = new std::string(kernelName);
	
   do
   {
      std::string *s2;
      s2 = new std::string((char*)mkernel_db[kid].krnl_nm);

      if (*s1 == *s2)
      {
         found = 1;
         kernelID[0] = kid;   //mkernel_list[kid].krnl_md;
         delete s2;
         break;
      }
      else kid++;

      delete s2;
		
   } while (kid <mkernel_num);

   delete s1;
	
   if (found == 0) rval = -1;

   return rval;
}
#else
int acl_krnl_manager::ret_id( int* kernelID, const char* kernelName)
{
   int rval    = 0;
   int kid     = 0;
   int found   = 0;
   std::string s1(kernelName);
   do
   {
      std::string s2((char*)mkernel_db[kid].krnl_nm);

      if (s1 == s2)
      {
         found = 1;
         kernelID[0] = kid;   //mkernel_list[kid].krnl_md;
         break;
      }
      else kid++;
   } while (kid <mkernel_num);

   if (found == 0) rval = -1;

   return rval;
}
#endif
int acl_krnl_manager::ret_nargs(int kernelID)
{
   int rval = 0;
   rval = mkernel_list[kernelID].krnl_md.num_args;
   return rval;
}
