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

#ifndef apu_hal_H
#define apu_hal_H

#include "apex_apu_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif 

// APU HAL
// --------------------------------------------------------------------------
void apexdriver_apu_hal_Enable(int apexID, unsigned int APUID, unsigned int isEnable);
void apexdriver_apu_hal_Reset(int apexID, unsigned int APUID);

volatile unsigned int *apexdriver_apu_hal_GetDMEMAddress(int apexID, unsigned int APUID);
volatile unsigned int *apexdriver_apu_hal_GetIMEMAddress(int apexID, unsigned int APUID);

// APU Code
// Loader                       
// --------------------------------------------------------------------------
void apexdriver_apu_hal_Load(int apexID, int apuid,
                  int im_size, const int* im_addr, const int* im_data,
                  int dm_size, const int* dm_addr, const int* dm_data,
                  int vm_size, const int* vm_addr, const int* vm_data);


#ifndef SEG_HOST_TYPE
typedef int64_t  SEG_HOST_TYPE;
typedef uint32_t SEG_MEM_TYPE;
#endif
typedef SEG_HOST_TYPE LOAD_SEGMENT_t[4];
int32_t apexdriver_apu_hal_LoadSegment(int apexID, int32_t apuid,
                            const LOAD_SEGMENT_t* seg_addr);
void apexdriver_apu_hal_QueryLoad_MEM_REQ(int apexID, const LOAD_SEGMENT_t* seg_addr,
                               int32_t* pCmemReq,
                               int32_t* pDmemReq,
                               int32_t* pPmemReq);
int32_t apexdriver_apu_hal_RetMemSizes (int apexID, CMEM_IF_APU_CFG apuconfig,
                              int32_t* pSmemSize,
                              int32_t* pCmemSize);

// IRQ related functions.
void apexdriver_apu_hal_DisableAllIRQs (int apexID);
void apexdriver_apu_hal_ClearAllIRQs(int apexID);


// --------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif 

//***************************************************************************
#endif  // apu_hal_H

