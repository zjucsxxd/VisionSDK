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


#ifndef _ACL_KRNL_MANAGER_H_
#define _ACL_KRNL_MANAGER_H_

#include <apex_apu_microkernel_hal.h>
#include <apex_apu_hal.h>
#include "apu_ocl_struct.h"


class acl_krnl_manager
{
public:
   acl_krnl_manager();
   ~acl_krnl_manager();
   int init  ( int apuid, const LOAD_SEGMENT_t* seg_addr);
   int ret_id( int* kernelID, const char* kernelName);
   int ret_nargs(int kernelID);

   acl_kernel*       mkernel_list;
private:
   CL_KRNL_DB_ENTRY* mkernel_db;
   int               mkernel_num;
   LOAD_SEGMENT_t*   mseg_addr;
};




#endif /* _KERNEL_MANAGER_H_ */
