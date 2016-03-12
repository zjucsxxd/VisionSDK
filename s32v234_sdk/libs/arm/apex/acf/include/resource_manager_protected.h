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

#ifndef RESOURCE_MANAGER_PROTECTED_H
#define RESOURCE_MANAGER_PROTECTED_H

/***************************************************************************/
/* Include files. */
#include "oal.h"
#include "global_errors.h"
#include "global_types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>



//**************************************************************************/
// Module Function Prototypes

/**
 *  \file ResourceManagerPublic.h
 *  \brief Interface for resource manager
 *  \addtogroup ResMgr Resource Manager
 *  @{
 *  \details
 * This interface contains functions used for mutual exclusion of shared resources.
 * Resources can be registered at run-time
 * Resources are grouped into sets
 * Multiple resources can be allocated atomically
 *
 * Mandatory Function Call Ordering Sequence:
 * <ol><li>#ResMgr_Initialize to get the required size in bytes of the buffer
 * </li><li>#ResMgr_Initialize to initialize this module
 * </li><li>#ResMgr_Set_Register to register a set and its resources
 * </li><li>#ResMgr_User_Type_Register to register a user type
 * </li><li>#ResMgr_User_Allocate to allocate a user
 * </li><li>#ResMgr_Resource_Allocate to allocate resource(s)
 * </li><li>#ResMgr_Resource_Deallocate to deallocate resource(s)
 * </li><li>#ResMgr_User_Deallocate to deallocate user
 * </li><li>#ResMgr_Deinitialize to deinitialize this module
 * </li></ol>
 *
*/


/*
 * \details
 * The ResMgr_Initialize() function initializes the ResMgr module.
 *
 *
 * Input
 *    cpBuffer[J]
 *
 *       [J], where J = cBufferSizeInBytes, if distance between two array elements is a byte.
 *
 *    cInputArray[K][L]
 *
 *       [K], where K = 3
 *            when 0 <Object> is <Set>
 *            when 1 <Object> is <Resource>
 *            when 2 <Object> is <User>
 *       [L], where L = 3
 *            when 0 is Max <Object> Name Length
 *            when 1 is Max Number of <Object> Types
 *            when 2 is Max Number of <Object>
 *
 *    cSizeOfInputArray = value of K
 *
 *    cMaxNumberOfResourcesInAllocation = Largest value supported for parameter cSizeOfOutputArray of function ResMgr_Resource_Allocate
 */
LIB_RESULT ResMgr_Initialize(int apexID, void* const cpBuffer,
                             uint32_t const cBufferSizeInBytes,
                             uint32_t const cInputArray[][3],    /* See function description for details */
                             uint32_t const cSizeOfInputArray,   /* Expects 3, see function description for details */
                             uint32_t const cMaxNumberOfResourcesInAllocation,
                             uint32_t* const cpReturnedSizeInBytes);

/*
 * \details
 * The ResMgr_Deinitialize() function deinitializes the ResMgr module.
 *
 */
LIB_RESULT ResMgr_Deinitialize(int apexID);



/*
 * \details
 * The ResMgr_Set_Register() function registers set(s) of resource(s).
 *
 * The number of available set types is determined during the call to ResMgr_Initialize in the parameter cInputArray[0][1]
 * The maximum supported set/resource name length is determined during the call to ResMgr_Initialize in the parameter cInputArray[1][0]
 * The number of available resource types is determined during the call to ResMgr_Initialize in the parameter cInputArray[1][1]
 * The number of available resource is determined during the call to ResMgr_Initialize in the parameter cInputArray[1][2]
 *
 * Input
 *    cpcTypeNameInputArray[J][K]
 *
 *       [J], where J = cSizeOfArrays
 *            when 0 is name of the Set type
 *            when {1 <= J < cSizeOfInputArrays} is name of Resource types
 *       [K], where K = cMaxNameLength + 1
 *
 *    cInputArray[L]
 *
 *       [L], where L = cSizeOfArrays
 *            when 0 is number of Set instances
 *            when {1 <= J < cSizeOfInputArrays} is number of Resource instances
 *
 * Output
 *    cOutputArray[P]
 *
 *       [P], where P = cSizeOfArrays
 *            when 0 is Set Type Id
 *            when {1 <= J < cSizeOfArrays} is Resource Type Id
 *
 *    rSizeOfOutputArray = to the sum of all cInputArray[L][1]
 *
 */
LIB_RESULT ResMgr_Set_Register(int apexID, const char* const cpcNameInputArray,
                               uint32_t const cMaxNameLength,
                               uint32_t const cInputArray[],
                               uint32_t  outputArray[],
                               uint32_t const cSizeOfArrays);



/*
 * \details
 * The ResMgr_User_Type_Register() function registers user type(s).
 *
 * The maximum supported user type id name length is determined during the call to ResMgr_Initialize in the parameter cInputArray[2][0]
 * The number of available user type id is determined during the call to ResMgr_Initialize in the parameter cInputArray[2][1]
 *
 * Input
 *    cpcTypeNameInputArray[J][K]
 *
 *       [J], where J = cSizeOfArrays
 *       [K], where K = cMaxNameLength + 1
 *
 * Output
 *    cOutputArray[P]
 *
 *       [P], where P = cSizeOfArrays
 *            all values are User Type Id
 *
 *
 */
LIB_RESULT ResMgr_User_Type_Register(int apexID, const char* const cpcTypeNameInputArray,
                                     uint32_t const cMaxNameLength,
                                     uint32_t outputArray[],
                                     uint32_t const cSizeOfArrays);



/*
 * \details
 * The ResMgr_User_Allocate() function allocates a userId.
 *
 * This function will block if there are no more userId available.
 * The number of available userId is determined during the call to ResMgr_Initialize in the parameter cInputArray[2][2]
 *
 *
 * Input
 *    cUserTypeId
 *
 * Output
 *    cpReturnedUserId
 */
LIB_RESULT ResMgr_User_Allocate(int apexID, uint32_t const cUserTypeId,
                                uint32_t* const cpReturnedUserId);


/*
 * \details
 * The ResMgr_User_Deallocate() function deallocates a userId.
 *
 * This function will unblock the oldest blocked call to ResMgr_User_Allocate.
 *
 */
LIB_RESULT ResMgr_User_Deallocate(int apexID, uint32_t const cUserId); /* Same as *cpReturnedUserId returned by ResMgr_User_Allocate*/



/*
 * \details
 * The ResMgr_Resource_Allocate() function allocates resource(s) to a user
 *
 * This function will block if the requested resources are not currently available.
 *
 * Input
 *    cUserId
 *
 *    inputArray[L][M]
 *
 *       [L], where {0 <= L < cSizeOfInputArray}
 *       [M], where M = 3
 *            when 0 is value of <SetTypeId>
 *            when 1 is value of <ResourceTypeId>
 *            when 2 is value of <NumberOf>

 *
 * Output
 *    outputArray[R][S]
 *
 *       [R], where {0 <= R < cSizeOfOutputArray}
 *       [S], where S = 5
 *            when 0 is input array index which generated this entry
 *            when 1 is <Set Type Id>
 *            when 2 is <Set Instance number>
 *            when 3 is <Resource Type Id>
 *            when 4 is <Resource instance number>
 */
LIB_RESULT ResMgr_Resource_Allocate_TT(int apexID, uint32_t const cUserId,            /* Same as *cpReturnedUserId returned by ResMgr_User_Allocate*/
                                       uint32_t       inputArray[][3],
                                       uint32_t const cSizeOfInputArray,
                                       uint32_t       outputArray[][5],
                                       uint32_t const cSizeOfOutputArray);



/*
 * \details
 * The ResMgr_Resource_Allocate() function allocates resource(s) to a user
 *
 * This function will block if the requested resources are not currently available.
 *
 * Input
 *    cUserId
 *
 *    inputArray[L][M]
 *
 *       [L], where {0 <= L < cSizeOfInputArray}
 *       [M], where M = 3
 *            when 0 is value of <SetTypeId>
 *            when 1 is value of <ResourceTypeId>
 *            when 2 is value of <Instance>

 *
 * Output
 *    outputArray[R][S]
 *
 *       [R], where {0 <= R < cSizeOfOutputArray}
 *       [S], where S = 5
 *            when 0 is input array index which generated this entry
 *            when 1 is <Set Type Id>
 *            when 2 is <Set Instance number>
 *            when 3 is <Resource Type Id>
 *            when 4 is <Resource instance number>
 */
LIB_RESULT ResMgr_Resource_Allocate_TI(int apexID, uint32_t const cUserId,            /* Same as *cpReturnedUserId returned by ResMgr_User_Allocate*/
                                       uint32_t       inputArray[][3],
                                       uint32_t const cSizeOfInputArray,
                                       uint32_t       outputArray[][5],
                                       uint32_t const cSizeOfOutputArray);



/*
 * \details
 * The ResMgr_Resource_Deallocate() function deallocates resource(s) from a user
 *
 * This function will unblock the oldest blocked call to ResMgr_Resource_Allocate, if its requested resources are become available.
 *
 * Input
 *    cUserId_Index
 *
 *    cInputArray[X][Y]
 *
 *       [X], where {0 <= X < cSizeOfInputArray}
 *       [Y], where Y = 5
 *            when 0 is unused value
 *            when 1 is <Set Type Id>
 *            when 2 is <Set Instance number>
 *            when 3 is <Resource Type Id>
 *            when 4 is <Resource instance number>
 */
LIB_RESULT ResMgr_Resource_Deallocate(int apexID, uint32_t const cUserId,
                                      uint32_t       inputArray[][5],   /* Same as outputArray returned by ResMgr_Resource_Allocate*/
                                      uint32_t const cSizeOfInputArray);

#endif /* RESOURCE_MANAGER_PROTECTED_H */
