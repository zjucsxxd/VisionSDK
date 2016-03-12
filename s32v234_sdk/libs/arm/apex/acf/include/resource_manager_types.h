/******************************************************************************
 *  (C) Copyright CogniVue Corp. 2015 All right reserved.
 *    Confidential Information
 *
 *  All parts of the CogniVue Corp. Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from Cognivue.
 ******************************************************************************/

/* Information for doxygen */
/**
 *  \file   <<FileName>>
 *  \brief  <<One line Description>>
 *
 *  <<Replace this with Multiline description. This should describe the
 *  file in general.>>
 */

#ifndef RESOURCE_MANAGER_TYPES_HPP
#define RESOURCE_MANAGER_TYPES_HPP

/***************************************************************************/
/* Include files. */
#include "resource_manager_private.h"
#include "oal.h"
#include "global_errors.h"
#include "global_types.h"
#include <stdint.h>
#include <stdio.h>


#if defined __INTEGRITY
#if defined __cplusplus
  extern "C" {
#endif
#endif

/****************************************************************************/
/* Literals & definitions */


/****************************************************************************/
/* Class declaration. */
/**
 * \brief This class is responsible for ...
 *
 *
 */
LIB_RESULT ResMgr_Helper_TypeName_Find(const char* const cpcTypeNameToFind,
                                       const char* const cpcTypeNames,
                                       uint32_t const cMaxNameLength,
                                       uint32_t const cNumberOfTypes,
                                       uint32_t* const pReturnedIndex);

int ResMgr_Helper_qsort_compare_uint32_t_x3_2_1(const void* a,
                                                const void* b);


int ResMgr_Helper_qsort_compare_uint32_t_x3_2_1_0(const void* a,
                                                  const void* b);






LIB_RESULT ResMgr_Queue_Initialize(struct ResMgr_Queue* const cpThis,
                                   void* const cpBuffer,
                                   uint32_t const cBufferSizeInBytes,
                                   uint32_t const cCapacity,
                                   uint32_t* const cpReturnedSizeInBytes);

LIB_RESULT ResMgr_Queue_PushBack(struct ResMgr_Queue* const cpThis,
                                 uint32_t const cItem);

LIB_RESULT ResMgr_Queue_PeekFront(struct ResMgr_Queue* const cpThis,
                                  uint32_t* const cpItem);

LIB_RESULT ResMgr_Queue_PopFront(struct ResMgr_Queue* const cpThis,
                                 uint32_t* const cpItem);


#if defined __INTEGRITY
#if defined __cplusplus
  }
#endif
#endif


#endif /* RESOURCE_MANAGER_TYPES_HPP */
