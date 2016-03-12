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

#ifndef apex_CMEMARRAY_HAL_H_CV230X
#define apex_CMEMARRAY_HAL_H_CV230X

// Include files
#include <cmem_array_map.h>

#ifdef __KERNEL_MODULE
	
#else
	#include <stdint.h>
#endif

// Local Literals and Definitions

// These functions came from Simd.c.
// Most of them are unused, but have been made macros just in case.
// TODO: They should be REMOVED in the future.
#define GetNumCus(void)       (NUMBER_CUS_VERT * NUMBER_CUS_HORIZ)
#define GetArrayWidth(void)   (NUMBER_CUS_HORIZ)
#define GetArrayHeight(void)  (NUMBER_CUS_VERT)
#define GetMemPerCUSize(void) (MEMORY_PER_CU)
#define InitSIMD(void)        (CmemInit(void))

#endif // CMEMARRAY_HAL_H_CV230X
