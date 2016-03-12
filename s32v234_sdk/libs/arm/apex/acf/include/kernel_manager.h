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


#ifndef _KERNEL_MANAGER_H_
#define _KERNEL_MANAGER_H_

#include <apu_microkernel.h>
#include <apex_apu_hal.h>


class KernelManager
{
public:
   KernelManager();
   ~KernelManager();
   int InitLoadKernelDB ( int apuid, const LOAD_SEGMENT_t* seg_addr);
   int ReturnKernelID   ( int* kernelID, const char* kernelName);
private:
   KERNEL_INFO*   mkernel_list;
   int            mkernel_num;
};




#endif /* _KERNEL_MANAGER_H_ */
