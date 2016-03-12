// --------------------------------------------------------------------------
// COPYRIGHT (c) Freescale 2009
// Freescale Confidential Proprietary
//  All Rights Reserved
// --------------------------------------------------------------------------
//!\file    common.h
//!\brief   This file includes the various common header files
//
// TYPE: Header File
// DEPARTMENT: MSG-IDC
// CREATED BY: Pankaj Gupta  (B34391)
// --------------------------------------------------------------------------
// PURPOSE:  To generate a single file which includes all common header file
// --------------------------------------------------------------------------
// $Log: common.h.rca $
// 
//  Revision: 1.3 Fri May 30 16:04:50 2014 B34391
//  *** empty comment string ***
// 
//  Revision: 1.2 Thu May 29 13:49:39 2014 B20570
//  Initial Check-in...
// 
//  Revision: 1.1 
//  Initial Check In
// --------------------------------------------------------------------------

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

/* 
 * Include the specific CPU header file 
 */
//#define THIRDEYE
//#define RAINIER_1_0
//#define CALYPSO6M_1_0
#define HALO_1_0

#define DEBUG_PRINTS

#include "typedefs.h"
#include "typedefs_UINT8.h"
#if defined RAINIER_1_0
#include "MPC5746R.h"
#elif defined CALYPSO6M_1_0
#include "MPC5748G.h"
#elif defined HALO_1_0
#include "MAC57D54H.h"
//#include "halo.h"
//#include "CM4.h"

#endif
#include "thirdeye.h"
#include "printf.h"
//#include "stdlib.h"
//#include "typedefs_UINT8.h"
#include "user_module.h"
#include "cgm_api.h"
#include "serial.h"
//#include "intc_soc_config.h"
//#include "swt_soc_config.h"
//#include "pit_soc_config.h"
//#include "cgm_soc_config.h"
//#include "edma_soc_config.h"
//#include "smpu_soc_config.h"
//#include "mc_me_soc_config.h"
//#include "io.h"
//#define TRACE_MEMORY_OPERATION 1
/********************************************************************/

#endif /* _COMMON_H_ */
