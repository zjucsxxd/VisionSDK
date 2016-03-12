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

#ifndef RESOURCE_MANAGER_PRIVATE_H
#define RESOURCE_MANAGER_PRIVATE_H

/***************************************************************************/
/* Include files. */
#include "oal.h"
#include "global_errors.h"
#include "global_types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#if defined __INTEGRITY
#if defined __cplusplus
  extern "C" {
#endif
#endif

/****************************************************************************/
/* Literals & definitions */
#define gcResMgr_MaxNumberOfSetTypes     0x100  /* const uint32_t gcResMgr_MaxNumberOfSetTypes     = 0x100 */
#define gcResMgr_MaxNumberOfSetInstances 0x100  /* const uint32_t gcResMgr_MaxNumberOfSetInstances = 0x100 */
#define gcResMgr_MaxNumberOfResTypes     0x100  /* const uint32_t gcResMgr_MaxNumberOfResTypes     = 0x100 */
#define gcResMgr_MaxNumberOfResInstances 0x100  /* const uint32_t gcResMgr_MaxNumberOfResInstances = 0x100 */
#define gcResMgr_MaxNumberOfUsrTypes     0x100  /* const uint32_t gcResMgr_MaxNumberOfUsrTypes     = 0x100 */
#define gcResMgr_MaxNumberOfUsrInstances 0x100  /* const uint32_t gcResMgr_MaxNumberOfUsrInstances = 0x100 */

#define gcResMgr_MaxNumberOfUsrSessions  0x10000  /* const uint32_t gcResMgr_MaxNumberOfUsrSessions = 0x10000 */


/****************************************************************************/
/* Class declaration. */
/**
 * \brief This class is responsible for ...
 *
 *
 */
struct ResMgr_Init
{
   uint32_t mMaxNameLength;     /* Maximum name length in mp<Object>TypeNames, where <Object> is in {Set, Resource, User}. DOES NOT INCLUDE THE TERMINATING NULL BYTE!!! */
   uint32_t mMaxNumberOfTypes;  /* Maximum number of entries in mp<Object>TypeNames and mp<Object>TypeNames_OrderedLookup, where <Object> is in {Set, Resource, User}. */
   uint32_t mMaxNumberOfObject; /* Maximum number of entries in mp<Object>s, where <Object> is in {Set, Resource, User}. */
};


struct ResMgr_Inits
{
   struct ResMgr_Init mSet;
   struct ResMgr_Init mResource;
   struct ResMgr_Init mUser;
   uint32_t           mMaxNumberOfResourcesInAllocation; /* Largest value supported for parameter cSizeOfOutputArray of function ResMgr_Resource_Allocate */
};


struct ResMgr_Resource
{
   uint32_t mUserId;     /* high 16 bits is session id, low 16 bits is user index */
};



struct ResMgr_Set
{
   struct ResMgr_Resource** mppResources;              /* [X][Y], where {0 <= X < ResMgr_SetType::mNumberOfResourceTypes} and {0 <= Y < ResMgr_SetType::mpNumberOfResourcePerType[X]} */
   uint32_t*                mpNumberOfFreeResources;   /* [X],    where {0 <= X < ResMgr_SetType::mNumberOfResourceTypes} */
   uint32_t**               mppFreeResourceIndexes;    /* [X][Y], where {0 <= X < ResMgr_SetType::mNumberOfResourceTypes} and {0 <= Y < ResMgr_SetType::mpNumberOfResourcePerType[X]} */
};



struct ResMgr_SetType
{
   uint32_t           mMaxNameLength;            /* Does NOT include the null termination byte */
   char*              mpSetTypeName;             /* [X],    where {0 <= X <= mMaxNameLength} */
   uint32_t           mNumberOfResourceTypes;    /*  X ,    where {0 <  X < gcResMgr_MaxNumberOfResTypes */
   char*              mpResourceTypeNames;       /* [X][Y], where {0 <= X <  mNumberOfResourceTypes} and {0 <= Y <= mMaxNameLength} */
   uint32_t*          mpNumberOfResourcePerType; /* [X]   , where {0 <= X <  mNumberOfResourceTypes} */
   uint32_t           mNumberOfResources;
   uint32_t           mNumberOfSets;
   struct ResMgr_Set* mpSets;                    /* [X]   , where {0 <= X <  mNumberOfSets} */
};



struct ResMgr_SetTypes
{
   uint32_t               mNumberOfSetTypes;
   struct ResMgr_SetType* mpSetTypes;
};



struct ResMgr_User
{
   OAL_SEMAPHORE mOalSemaphore;                /* Semaphore blocks ResMgr_Resource_Allocate until all resources are available. */
   uint32_t    (*mpInputArray)[3];             /* Copy of cInputArray        of last call to ResMgr_Resource_Allocate which blocked */
   uint32_t      mSizeOfInputArray;            /* Copy of cSizeOfInputArray  of last call to ResMgr_Resource_Allocate which blocked */
   uint32_t    (*mpOutputArray)[5];            /* Result of alloc returned   to last call to ResMgr_Resource_Allocate which blocked */
   uint32_t      mSizeOfOutputArray;           /* Copy of cSizeOfOutputArray of last call to ResMgr_Resource_Allocate which blocked */

   uint32_t      mNumberOfAllocatedResources;  /* User should only allocate if he has no outstanding allocated resources */
   uint16_t      mSessionId;                   /* Storing this value in the high 16 bits of the user id give to users */
   bool          mIsWaitingOnResources;
   bool          mIsAllocatingInstances;       /* true means that user called ResMgr_Resource_Allocate_TI, false means that user called ResMgr_Resource_Allocate_TT  */
   bool          mIsFree;                      /* If true, this user is not allocated, its Id_Index can be found in mpFreeUserId_Indexes */
};



struct ResMgr_Users
{
   OAL_SEMAPHORE       mOalSemaphore;            /* Semaphore blocks ResMgr_User_Allocate until a user slot opens up, bound by ResourceManager::ResMgr_Inits::mUser.mMaxNumberOfObject */
   uint32_t            mNumberOfUserTypes;       /*  X,  where {0 <  X <= gcResMgr_MaxNumberOfUsrTypes}     */
   char*               mpUserTypeNames;          /* [X], where {0 <= X <  gcResMgr_MaxNumberOfUsrTypes}     */
   uint32_t            mNumberOfUsers;           /*  X,  where {0 <  X <= gcResMgr_MaxNumberOfUsrInstances} */
   struct ResMgr_User* mpUsers;                  /* [X], where {0 <= X <  gcResMgr_MaxNumberOfUsrInstances} */
   uint32_t            mNumberOfFreeIndexes;     /*  X,  where {0 <  X <= gcResMgr_MaxNumberOfUsrInstances} */
   uint32_t*           mpFreeIndexes;            /* [X], where {0 <= X <  gcResMgr_MaxNumberOfUsrInstances} */
};



struct ResMgr_Queue
{
    uint32_t* mpBuffer;     /* data buffer */
    uint32_t* mpBufferEnd;  /* end of data buffer */
    uint32_t  mCapacity;    /* maximum number of items in the buffer */
    uint32_t  mCount;       /* number of items in the queue */
    uint32_t* mpHead;       /* pointer to head */
    uint32_t* mpTail;       /* pointer to tail */
};



struct ResourceManager
{
   OAL_SEMAPHORE mThreadSafetySemaphore;        /* Semaphore to prevent concurrent access to the ResourceManager data */

   struct ResMgr_Inits mInits;

   uintptr_t mpBufferBegin;    /* Address of buffer provided by caller of initialize function */
   uintptr_t mpBufferNext;     /* Address of next range to be allocated internally by ResMgr */
   uintptr_t mpBufferEnd;      /* Address of byte that follows the last valid address */

   struct ResMgr_Users mUsers;

   struct ResMgr_SetTypes mSetTypes;

   struct ResMgr_Queue mQueue;

   uint32_t mResMgr_UserTypeIndex;            /* User Type Id/Index of the resource manager User instance */
   uint32_t mResMgr_UserId;                   /* User Id/Index which is reserved for the resource manager itself. */

   uint32_t* mpScratchPad;
   uint32_t  mScratchPadSizeInBytes;

   bool      mIsInitialized;
};



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
LIB_RESULT ResMgr_Initialize_Private(int apexID, struct ResourceManager* const cpThis,
                                     void* const cpBuffer,
                                     uint32_t const cBufferSizeInBytes,
                                     uint32_t const cInputArray[][3],    /* See function description for details */
                                     uint32_t const cSizeOfInputArray,   /* Expects 3, see function description for details */
                                     uint32_t const cMaxNumberOfResourcesInAllocation,
                                     uint32_t* const cpReturnedSizeInBytes);

LIB_RESULT ResMgr_Deinitialize_Private(int apexID, struct ResourceManager* const cpThis);



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
LIB_RESULT ResMgr_Set_Register_Private(int apexID, struct ResourceManager* const cpThis,
                                       const char* const cpcNameInputArray,
                                       uint32_t const cMaxNameLength,
                                       uint32_t const cInputArray[],
                                       uint32_t  outputArray[],
                                       uint32_t const cSizeOfArrays);



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
LIB_RESULT ResMgr_User_Type_Register_Private(int apexID, struct ResourceManager* const cpThis,
                                             const char* const cpcTypeNameInputArray,
                                             uint32_t const cMaxNameLength,
                                             uint32_t outputArray[],
                                             uint32_t const cSizeOfArrays);



/*
 * Allocate <User>
 *
 * Input
 *    cUserTypeId_Index
 *
 * Output
 *    cpReturnedUserId_Index
 */
LIB_RESULT ResMgr_User_Allocate_Private(int apexID, const uint32_t cThreadId,
                                        struct ResourceManager* const cpThis,
                                        uint32_t const cUserTypeId_Index,
                                        uint32_t* const cpReturnedUserId);

LIB_RESULT ResMgr_User_Deallocate_Private(int apexID, const uint32_t cThreadId,
                                          struct ResourceManager* const cpThis,
                                          uint32_t const cUserId);



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
LIB_RESULT ResMgr_Resource_Allocate_TT_Private(int apexID, const uint32_t cThreadId,
                                               struct ResourceManager* const cpThis,
                                               uint32_t const cUserId,
                                               uint32_t       inputArray[][3],
                                               uint32_t const cSizeOfInputArray,
                                               uint32_t       outputArray[][5],
                                               uint32_t const cSizeOfOutputArray);



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
LIB_RESULT ResMgr_Resource_Allocate_TI_Private(int apexID, const uint32_t cThreadId,
                                               struct ResourceManager* const cpThis,
                                               uint32_t const cUserId,
                                               uint32_t       inputArray[][3],
                                               uint32_t const cSizeOfInputArray,
                                               uint32_t       outputArray[][5],
                                               uint32_t const cSizeOfOutputArray);



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
LIB_RESULT ResMgr_Resource_Deallocate_Private(int apexID, const uint32_t cThreadId,
                                              struct ResourceManager* const cpThis,
                                              uint32_t const cUserId,
                                              uint32_t       inputArray[][5],
                                              uint32_t const cSizeOfInputArray);

#if defined __INTEGRITY
#if defined __cplusplus
  }
#endif
#endif

#endif /* RESOURCE_MANAGER_PRIVATE_H */
