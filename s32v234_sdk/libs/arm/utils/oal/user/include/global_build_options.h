/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2010 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

 
 /******************************************************************************
 *  Description: Global include which defines the compile configuration
 *               for a specific platform.
 *
 ******************************************************************************
 */

/* Information for doxygen */
/**
 *  \file   GlobalBuildOptions.h
 *  \brief  Global include which defines the compile configuration for a specific platform.
 *
 *  Global include which defines the compile configuration for a specific platform.
 */

#ifndef GLOBAL_BUILD_OPTIONS_ALL_H
#define GLOBAL_BUILD_OPTIONS_ALL_H

//***************************************************************************
// Include files.

// Select (comment/uncomment) only one of these for the PLATFORM/APP/CHIP
// combination being built.

//TODO: next line was uncommented originally
//#include GBO_FILE // Let the build system figure it out.
//#include "./GBOpts_EVB_ICP_SDK_CV2201.h"
//#include "./GBOpts_RDK_ICP_SDK_CV2202.h"
//#include "./GBOpts_RDK_ICP_SDK_CV2202_SN20001.h"
//#include "./GBOpts_EVB_Slave_CV2201_Arm2.h"
//#include "./GBOpts_RDK_Slave_CV2202_Arm2.h"

#ifndef ATD_HW_PLATFORM
//TODO: next line was uncommented originally
//#error "Must select target in 'GlobalBuildOptions.h'"
#endif

#endif

