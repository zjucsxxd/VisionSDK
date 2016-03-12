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


#include "resource_manager_private.h"

static struct ResourceManager gsResMgr[2];

/*
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
                             uint32_t* const cpReturnedSizeInBytes)
{
   return ResMgr_Initialize_Private(apexID, &gsResMgr[apexID],
                                    cpBuffer,
                                    cBufferSizeInBytes,
                                    cInputArray,
                                    cSizeOfInputArray,
                                    cMaxNumberOfResourcesInAllocation,
                                    cpReturnedSizeInBytes);
}



/*
 * Free all the resources owned by the resource manager
 */
LIB_RESULT ResMgr_Deinitialize(int apexID)
{
   return ResMgr_Deinitialize_Private(apexID, &gsResMgr[apexID]);
}



/* Register <Set>
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
                               uint32_t const cSizeOfArrays)
{
   return ResMgr_Set_Register_Private(apexID, &gsResMgr[apexID],
                                      cpcNameInputArray,
                                      cMaxNameLength,
                                      cInputArray,
                                      outputArray,
                                      cSizeOfArrays);
}



/*
 * Register User Type
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
                                     uint32_t const cSizeOfArrays)
{
   return ResMgr_User_Type_Register_Private(apexID, &gsResMgr[apexID],
                                            cpcTypeNameInputArray,
                                            cMaxNameLength,
                                            outputArray,
                                            cSizeOfArrays);
}



/*
 * Allocate <User>
 *
 * Input
 *    cUserTypeId_Index
 *
 * Output
 *    cpReturnedUserId
 */
LIB_RESULT ResMgr_User_Allocate(int apexID, uint32_t const cUserTypeId_Index,
                                uint32_t* const cpReturnedUserId)
{
   return ResMgr_User_Allocate_Private(apexID, 0,
                                       &gsResMgr[apexID],
                                       cUserTypeId_Index,
                                       cpReturnedUserId);
}



/*
 * Deallocate <Resource>
 *
 * Input
 *    cUserId
 *
 *    cInputArray[L]
 *
 *       [L], where {0 <= L < cSizeOfInputArray}
 *            is value of <ResourceId_Index> which matches values from ResMgr_Resource_Allocate
 */
LIB_RESULT ResMgr_User_Deallocate(int apexID, uint32_t const cUserId)
{
   return ResMgr_User_Deallocate_Private(apexID, 0,
                                         &gsResMgr[apexID],
                                         cUserId);
}



/*
 * Allocate <Resource>
 *
 * Input
 *    cUserId_Index
 *
 *    cInputArray[L][M]
 *
 *       [L], where {0 <= L < cSizeOfInputArray}
 *       [M], where M = 3
 *            when 0 is value of <SetTypeId_Index>
 *            when 1 is value of <ResourceTypeId_Index>
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
LIB_RESULT ResMgr_Resource_Allocate_TT(int apexID, uint32_t const cUserId,
                                       uint32_t       inputArray[][3],
                                       uint32_t const cSizeOfInputArray,
                                       uint32_t       outputArray[][5],
                                       uint32_t const cSizeOfOutputArray)
{
   return ResMgr_Resource_Allocate_TT_Private(apexID, 0,
                                              &gsResMgr[apexID],
                                              cUserId,
                                              inputArray,
                                              cSizeOfInputArray,
                                              outputArray,
                                              cSizeOfOutputArray);
}



/*
 * Allocate <Resource>
 *
 * Input
 *    cUserId_Index
 *
 *    cInputArray[L][M]
 *
 *       [L], where {0 <= L < cSizeOfInputArray}
 *       [M], where M = 3
 *            when 0 is value of <SetTypeId_Index>
 *            when 1 is value of <ResourceTypeId_Index>
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
LIB_RESULT ResMgr_Resource_Allocate_TI(int apexID, uint32_t const cUserId,
                                       uint32_t       inputArray[][3],
                                       uint32_t const cSizeOfInputArray,
                                       uint32_t       outputArray[][5],
                                       uint32_t const cSizeOfOutputArray)
{
   return ResMgr_Resource_Allocate_TI_Private(apexID, 0,
                                              &gsResMgr[apexID],
                                              cUserId,
                                              inputArray,
                                              cSizeOfInputArray,
                                              outputArray,
                                              cSizeOfOutputArray);
}



/*
 * Deallocate <Resource>
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
                                      uint32_t       inputArray[][5],
                                      uint32_t const cSizeOfInputArray)
{
   return ResMgr_Resource_Deallocate_Private(apexID, 0,
                                             &gsResMgr[apexID],
                                             cUserId,
                                             inputArray,
                                             cSizeOfInputArray);
}





