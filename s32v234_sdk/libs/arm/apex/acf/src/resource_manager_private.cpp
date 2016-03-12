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
#include "resource_manager_types.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LIB_ERROR_INVALID_USER_ID
  #define LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE           0xB5000 ///< The allocation request is valid but the not all resources were available presently
  #define LIB_ERROR_ATTEMPT_DEALLOC_UNOWNED_RESOURCE      0xB5001 ///< User attempted to deallocate a resource which did no belong to him/her
  #define LIB_ERROR_USER_STILL_OWNS_RESOURCES             0xB5002 ///< User attempted to deallocate a user who still has resources that need to be deallocated
  #define LIB_ERROR_USER_WAITING_ON_RESOURCES             0xB5003 ///< User attempted to deallocate a user who is still waiting on resources to be allocated
  #define LIB_ERROR_INITIALIZATION_VALUE_TOO_SMALL        0xB5004 ///< User attempted passed a value larger than what is supported by the values passed to ResMgr_Initialize
  #define LIB_ERROR_INVALID_USER_ID                       0xB5005 ///< User attempted to reuse a user id which is no longer valid or provide a wrong value
  #define LIB_ERROR_OUTPUT_ARRAY_SIZE_TOO_LARGE           0xB5006 ///< User passed a value larger than what is supported by the values passed to ResMgr_Initialize
  #define LIB_ERROR_USER_INDEX_TOO_LARGE                  0xB5007 ///< User passed a value larger than what is supported by the values passed to ResMgr_Initialize
  #define LIB_ERROR_SESSION_ID_MISMATCH                   0xB5008 ///< User session id does not match with current session for that user index
  #define LIB_ERROR_USER_STILL_HAS_RESOURCES              0xB5009 ///< User attempted to allocate resources before freeing those he currently owns
  #define LIB_NO_USER_WAITING_FOR_RESOURCES               0xB500A ///< There are no users waiting for resources, meaning the queue is empty
  #define LIB_USER_OBTAINED_RESOURCES                     0xB500B ///< A user was allocated resources in the returning function, if he was blocked he should be unblocked
  #define LIB_USER_WAITING_FOR_RESOURCES                  0xB500C
#endif
static const uint32_t gscNumberOfObjects = 3; /* Should be three: {Set, Resource, User} */

static bool gsIsResourceManagerInitialized[2] = {false}; /* Need this variable to protect against multiple initializations, would not be necessary if this were written in C++ */

static const bool gscAreTracesEnabled[2] = {false};


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
 
#define SHOW_ERROR(expr) if(!(expr)) { printf("%s : %s [%d]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__); }

LIB_RESULT ResMgr_Initialize_Private(int apexID, struct ResourceManager* const cpThis,
                                     void* const cpBuffer,
                                     uint32_t const cBufferSizeInBytes,
                                     uint32_t const cInputArray[][3],    /* See function description for details */
                                     uint32_t const cSizeOfInputArray,   /* Expects 3, see function description for details */
                                     uint32_t const cMaxNumberOfResourcesInAllocation,
                                     uint32_t* const cpReturnedSizeInBytes)
{
  
   LIB_RESULT libResult = LIB_FAILURE;
   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == false);

   if(cpThis != 0 &&
      cpReturnedSizeInBytes != 0)
   {
      SHOW_ERROR(gscNumberOfObjects == 3);
      (*cpReturnedSizeInBytes) = 0;


      if(cSizeOfInputArray == gscNumberOfObjects)
      {
         uint32_t neededSizeInBytes      = 0;
         uint32_t queueNeededSizeInBytes = 0;

         bool areValuesInInputArrayValid = true;

         /* Add extra entries for the ResMgr user */
         const uint32_t cAdjustedMaxNumberOfUserTypes = (cInputArray[2][1] < gcResMgr_MaxNumberOfUsrTypes) ?
                                                        (cInputArray[2][1] + 1) : gcResMgr_MaxNumberOfUsrTypes;

         const uint32_t cAdjustedMaxNumberOfUsers     = (cInputArray[2][2] < (gcResMgr_MaxNumberOfUsrTypes * gcResMgr_MaxNumberOfUsrInstances)) ?
                                                        (cInputArray[2][2] + 1) : (gcResMgr_MaxNumberOfUsrTypes * gcResMgr_MaxNumberOfUsrInstances);

         if(cInputArray[0][0] > 0 &&  /* Max Set Name Length, does not include null termination byte */
            cInputArray[0][1] > 0 &&  /* Max Number of Set Types */
            cInputArray[0][2] > 0 &&  /* Max Number of Set */
            cInputArray[0][1] <= gcResMgr_MaxNumberOfSetTypes &&
            cInputArray[0][2] <= (gcResMgr_MaxNumberOfSetTypes * gcResMgr_MaxNumberOfSetInstances) &&

            cInputArray[1][0] > 0 &&  /* Max Res Name Length, does not include null termination byte */
            cInputArray[1][1] > 0 &&  /* Max Number of Res Types */
            cInputArray[1][2] > 0 &&  /* Max Number of Res */
            cInputArray[1][1] <= (gcResMgr_MaxNumberOfSetTypes * gcResMgr_MaxNumberOfSetInstances * gcResMgr_MaxNumberOfResTypes) &&

            cInputArray[2][0] > 0 &&  /* Max User Name Length, does not include null termination byte */
            cInputArray[2][1] > 0 &&  /* Max Number of User Types */
            cInputArray[2][2] > 0 &&  /* Max Number of User */
            cInputArray[2][1] <  gcResMgr_MaxNumberOfUsrTypes &&
            cInputArray[2][2] <= (gcResMgr_MaxNumberOfUsrTypes * gcResMgr_MaxNumberOfUsrInstances) )
         {
            neededSizeInBytes += cInputArray[0][1] * sizeof(struct ResMgr_SetType); /* ResourceManager::ResMgr_SetTypes::mpSetTypes */
            neededSizeInBytes += sizeof(uintptr_t);                                 /* For alignments */

            neededSizeInBytes += cInputArray[0][1] * (cInputArray[0][0] + 1);       /* ResourceManager::ResMgr_SetTypes::mpSetTypeName */
            neededSizeInBytes += cInputArray[1][1] * (cInputArray[1][0] + 1);       /* ResourceManager::ResMgr_SetTypes::mpSetTypes::mpResourceTypeNames */
            neededSizeInBytes += cInputArray[0][1] * gcResMgr_MaxNumberOfResTypes;  /* ResourceManager::ResMgr_SetTypes::mpSetTypes::mpNumberOfResourcePerType */
            neededSizeInBytes += cInputArray[0][1] * sizeof(uintptr_t);             /* For alignments */
            neededSizeInBytes += cInputArray[0][2] * sizeof(struct ResMgr_Set);     /* ResourceManager::ResMgr_SetTypes::mpSets */
            neededSizeInBytes += cInputArray[0][1] * sizeof(uintptr_t);             /* For alignments */
            neededSizeInBytes += cInputArray[0][2] * gcResMgr_MaxNumberOfResTypes * sizeof(struct ResMgr_Resource*);
            neededSizeInBytes += cInputArray[0][2] * sizeof(uintptr_t);             /* For alignments */
            neededSizeInBytes += cInputArray[0][2] * gcResMgr_MaxNumberOfResTypes * sizeof(struct ResMgr_Resource);
            neededSizeInBytes += cInputArray[0][2] * gcResMgr_MaxNumberOfResTypes * sizeof(uintptr_t);  /* For alignments */


            neededSizeInBytes += cAdjustedMaxNumberOfUserTypes * (cInputArray[2][0] + 1);                                  /* ResourceManager::ResMgr_Users::mpUserTypeNames */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers * sizeof(struct ResMgr_User);                                   /* ResourceManager::ResMgr_Users::mpUsers */
            neededSizeInBytes += sizeof(uintptr_t);                                                                        /* For alignments */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers * cMaxNumberOfResourcesInAllocation * sizeof(cpThis->mUsers.mpUsers[0].mpInputArray[0]); /* ResourceManager::ResMgr_Users::ResMgr_User::mpInputArray */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers * cAdjustedMaxNumberOfUsers* sizeof(uintptr_t);                                             /* For alignments */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers * cMaxNumberOfResourcesInAllocation * sizeof(cpThis->mUsers.mpUsers[0].mpOutputArray[0]); /* ResourceManager::ResMgr_Users::ResMgr_User::mpOutputArray */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers* sizeof(uintptr_t);                                             /* For alignments */
            neededSizeInBytes += cAdjustedMaxNumberOfUsers * sizeof(cpThis->mUsers.mpFreeIndexes[0]);                   /* ResourceManager::ResMgr_Users::mpFreeIndexes */

            neededSizeInBytes += gcResMgr_MaxNumberOfResTypes * sizeof(uint32_t) * 4;  /* ResourceManager::mpScratchPad */   /* SASHBY: *4 is magic Number representing the maximum dimension for input arrays, need to do this better!!! */
         }
         else
         {
            areValuesInInputArrayValid = false;
         }

         libResult = ResMgr_Queue_Initialize(&(cpThis->mQueue),
                                             0,
                                             0,
                                             cAdjustedMaxNumberOfUsers,
                                             &queueNeededSizeInBytes);

         if(libResult == LIB_SUCCESS)
         {
            neededSizeInBytes += queueNeededSizeInBytes;

            if(cpThis->mIsInitialized == false &&
               areValuesInInputArrayValid == true)
            {
               SHOW_ERROR(neededSizeInBytes > 0);

               *(cpReturnedSizeInBytes) = neededSizeInBytes;

               libResult = LIB_SUCCESS;

               if(cpBuffer != 0 &&
                  cBufferSizeInBytes >= neededSizeInBytes)
               {
                  memset(cpThis, 0, sizeof(*cpThis));

                  libResult = LIB_SUCCESS;
                                          
                  if(libResult == LIB_SUCCESS)
                  {
		     libResult = LIB_SUCCESS;
                     if(libResult == LIB_SUCCESS)
                     {
                        cpThis->mScratchPadSizeInBytes = gcResMgr_MaxNumberOfResTypes * sizeof(uint32_t) * 4; /* SASHBY: *4 is magic Number representing the maximum dimension for input arrays, need to do this better!!! */

                        cpThis->mIsInitialized = false;

                        memset(cpBuffer, 0, cBufferSizeInBytes);

                        cpThis->mInits.mSet.mMaxNameLength     = cInputArray[0][0];
                        cpThis->mInits.mSet.mMaxNumberOfTypes  = cInputArray[0][1];
                        cpThis->mInits.mSet.mMaxNumberOfObject = cInputArray[0][2];

                        cpThis->mInits.mResource.mMaxNameLength     = cInputArray[1][0];
                        cpThis->mInits.mResource.mMaxNumberOfTypes  = cInputArray[1][1];
                        cpThis->mInits.mResource.mMaxNumberOfObject = cInputArray[1][2];

                        cpThis->mInits.mUser.mMaxNameLength     = cInputArray[2][0];
                        cpThis->mInits.mUser.mMaxNumberOfTypes  = cAdjustedMaxNumberOfUserTypes;
                        cpThis->mInits.mUser.mMaxNumberOfObject = cAdjustedMaxNumberOfUsers;

                        cpThis->mInits.mMaxNumberOfResourcesInAllocation = cMaxNumberOfResourcesInAllocation;


                        cpThis->mpBufferBegin = (uintptr_t)cpBuffer;
                        cpThis->mpBufferNext  = (uintptr_t)cpBuffer;
                        cpThis->mpBufferEnd   = (((uintptr_t)cpBuffer) + cBufferSizeInBytes);

                        cpThis->mUsers.mNumberOfUserTypes = 0;
                        cpThis->mUsers.mpUserTypeNames    = (char*)(cpThis->mpBufferNext);
                        cpThis->mpBufferNext += cpThis->mInits.mUser.mMaxNumberOfTypes * (cpThis->mInits.mUser.mMaxNameLength + 1); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                        cpThis->mUsers.mNumberOfUsers = cpThis->mInits.mUser.mMaxNumberOfObject;
                        cpThis->mpBufferNext          = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                        cpThis->mUsers.mpUsers        = (struct ResMgr_User*)(cpThis->mpBufferNext);
                        cpThis->mpBufferNext         += cpThis->mInits.mUser.mMaxNumberOfObject * sizeof(struct ResMgr_User); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                        cpThis->mUsers.mNumberOfFreeIndexes = cpThis->mInits.mUser.mMaxNumberOfObject;
                        cpThis->mpBufferNext                   = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                        cpThis->mUsers.mpFreeIndexes        = (uint32_t*)(cpThis->mpBufferNext);
                        cpThis->mpBufferNext                  += cpThis->mInits.mUser.mMaxNumberOfObject * sizeof(cpThis->mUsers.mpFreeIndexes[0]); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                        cpThis->mSetTypes.mNumberOfSetTypes = 0;
                        cpThis->mpBufferNext                = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                        cpThis->mSetTypes.mpSetTypes        = (struct ResMgr_SetType*)(cpThis->mpBufferNext);
                        cpThis->mpBufferNext               += cpThis->mInits.mResource.mMaxNumberOfTypes * sizeof(struct ResMgr_SetType); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                        cpThis->mpBufferNext  = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                        cpThis->mpScratchPad  = (uint32_t*)(cpThis->mpBufferNext);
                        cpThis->mpBufferNext += cpThis->mScratchPadSizeInBytes;

                        /*
                         * mQueue
                         */
                        libResult = ResMgr_Queue_Initialize(&(cpThis->mQueue),
                                                            (void*)cpThis->mpBufferNext,
                                                            queueNeededSizeInBytes,
                                                            cpThis->mInits.mUser.mMaxNumberOfObject,
                                                            &queueNeededSizeInBytes);

                        cpThis->mpBufferNext += queueNeededSizeInBytes;

                        if(libResult != LIB_SUCCESS ||
                           cpThis->mpBufferNext > cpThis->mpBufferEnd)
                        {
                           SHOW_ERROR(false);
                           libResult = LIB_FAILURE;
                        }
                        else
                        {
                           const uint32_t cNumberOfResMgrPotentialNames = 4;
                           const char cResMgrPotentialNames[][32] = { "Resource Manager",
                                                                      "ResMgr",
                                                                      "RM",
                                                                      "0"}; /* Worst case since minimum allocate name size is 1 during initialization */

                           const uint32_t cNumberOfUserNames = 1;

                           uint32_t userOutputArray[1];

                           const char* pcResMgr = 0;
                           uint32_t resMgrNameLength = 0;

                           uint32_t i = 0;
                           uint32_t j = 0;

                           j = (cpThis->mUsers.mNumberOfUsers) - 1;
                           for(i = 0; i < cpThis->mUsers.mNumberOfUsers; ++i, --j)
                           {
                              struct ResMgr_User* const cpUser = &(cpThis->mUsers.mpUsers[j]);

                              cpThis->mpBufferNext                = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                              cpUser->mpInputArray                = (uint32_t (*)[3])(cpThis->mpBufferNext);
                              cpThis->mpBufferNext               += cMaxNumberOfResourcesInAllocation * sizeof(cpThis->mUsers.mpUsers[0].mpInputArray[0]);

                              cpThis->mpBufferNext                = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                              cpUser->mpOutputArray               = (uint32_t (*)[5])(cpThis->mpBufferNext);
                              cpThis->mpBufferNext               += cMaxNumberOfResourcesInAllocation * sizeof(cpThis->mUsers.mpUsers[0].mpOutputArray[0]);

                              cpUser->mSizeOfInputArray           = 0;
                              cpUser->mSessionId                  = 0;
                              cpUser->mNumberOfAllocatedResources = 0;
                              cpUser->mIsWaitingOnResources       = false;
                              cpUser->mIsFree                     = true;
                              cpThis->mUsers.mpFreeIndexes[i] = j;
                           }
                           for(i = 0; i < cNumberOfResMgrPotentialNames; ++i)
                           {
                              resMgrNameLength = strlen(cResMgrPotentialNames[i]);

                              if(cpThis->mInits.mUser.mMaxNameLength >= resMgrNameLength)
                              {
                                 pcResMgr = cResMgrPotentialNames[i];
                                 break;
                              }
                           }

                           cpThis->mIsInitialized = true;
                           gsIsResourceManagerInitialized[apexID] = true;

                           libResult = ResMgr_User_Type_Register_Private(apexID, cpThis,
                                                                         pcResMgr,
                                                                         resMgrNameLength,
                                                                         userOutputArray,
                                                                         cNumberOfUserNames);
                           if(libResult == LIB_SUCCESS)
                           {
                              cpThis->mResMgr_UserTypeIndex = userOutputArray[0];

                              libResult = ResMgr_User_Allocate_Private(apexID, 0x9,
                                                                       cpThis,
                                                                       cpThis->mResMgr_UserTypeIndex,
                                                                       &(cpThis->mResMgr_UserId));
                           }

                           if(libResult != LIB_SUCCESS)
                           {
                              cpThis->mIsInitialized = false;
                              gsIsResourceManagerInitialized[apexID] = false;
                           }
                        }
                     }
                  }    /* Semaphore creation succeeded */
               }
               else if(cpBuffer != 0 &&
                       cBufferSizeInBytes < neededSizeInBytes)
               {
                  SHOW_ERROR(false);
                  libResult = LIB_FAILURE;
               }
            }       /* ResMgr has not yet been initialized and input values are valid */
         }          /* input values are valid */
      }             /* Queue initialization succeeded */
   }                /* input values are valid */

   return libResult;
}



/*
 * Free all the resources owned by the resource manager
 */
LIB_RESULT ResMgr_Deinitialize_Private(int apexID, struct ResourceManager* const cpThis)
{
   LIB_RESULT libResult = LIB_FAILURE;

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true)
   {
      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         cpThis->mIsInitialized = false;
         gsIsResourceManagerInitialized[apexID] = false;

         libResult = LIB_SUCCESS;

         if(libResult == LIB_SUCCESS)
         {
            uint32_t i = 0;

            /* I need to free all the user semaphores */
            for(i = 0; i < cpThis->mUsers.mNumberOfUsers; ++i)
            {
               if(cpThis->mUsers.mpUsers[i].mIsFree == false)
               {
                  libResult = LIB_SUCCESS;

                  if(libResult != LIB_SUCCESS)
                  {
                     break;
                  }
               }
            }
         }
      }
   }

   return libResult;
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
LIB_RESULT ResMgr_Set_Register_Private(int apexID, struct ResourceManager* const cpThis,
                                       const char* const cpcNameInputArray,
                                       uint32_t const cMaxNameLength,
                                       uint32_t const cInputArray[],
                                       uint32_t  outputArray[],
                                       uint32_t const cSizeOfArrays)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      cpcNameInputArray != 0 &&
      cMaxNameLength > 0 &&
      cInputArray != 0 &&
      outputArray != 0 &&
      cSizeOfArrays > 1) /* At least one entry for the set type and one resource type */
   {
      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         libResult = LIB_FAILURE;

         if(cMaxNameLength <= cpThis->mInits.mResource.mMaxNameLength &&
            (cSizeOfArrays - 1) <= gcResMgr_MaxNumberOfResTypes &&         /* -1 because first entry is always the set type */
            (cSizeOfArrays - 1) <= cpThis->mInits.mResource.mMaxNumberOfTypes &&
            cInputArray[0]      <= gcResMgr_MaxNumberOfSetInstances &&
            cInputArray[0]      <= cpThis->mInits.mSet.mMaxNumberOfObject &&
            (cpThis->mInits.mSet.mMaxNumberOfTypes - cpThis->mSetTypes.mNumberOfSetTypes) > 0)  /* No more room for set types */
         {
            struct ResMgr_SetType* const cpSetType = &(cpThis->mSetTypes.mpSetTypes[cpThis->mSetTypes.mNumberOfSetTypes]);

            outputArray[0] = cpThis->mSetTypes.mNumberOfSetTypes;

            ++(cpThis->mSetTypes.mNumberOfSetTypes);

            cpSetType->mMaxNameLength = cMaxNameLength;
            cpSetType->mpSetTypeName = (char*)(cpThis->mpBufferNext);
            cpThis->mpBufferNext    += (cMaxNameLength + 1); /* +1 for null termination byte */  SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

            cpSetType->mNumberOfResourceTypes = cSizeOfArrays - 1;  /* -1 because first entry is always the set type */
            cpSetType->mpResourceTypeNames    = (char*)(cpThis->mpBufferNext);
            cpThis->mpBufferNext             += cpSetType->mNumberOfResourceTypes * (cMaxNameLength + 1); /* +1 for null termination byte */  SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

            cpThis->mpBufferNext                 = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
            cpSetType->mpNumberOfResourcePerType = (uint32_t*)(cpThis->mpBufferNext);
            cpThis->mpBufferNext                += cpSetType->mNumberOfResourceTypes * sizeof(cpSetType->mpNumberOfResourcePerType[0]); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

            cpSetType->mNumberOfSets = cInputArray[0];
            cpThis->mpBufferNext     = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
            cpSetType->mpSets        = (struct ResMgr_Set*)(cpThis->mpBufferNext);
            cpThis->mpBufferNext    += cpSetType->mNumberOfSets * sizeof(struct ResMgr_Set); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

            if(cpThis->mpBufferNext <= cpThis->mpBufferEnd)
            {
               bool areInputValuesValid = true;

               uint32_t i = 0;

               const char*    pcCurrentInputName    = cpcNameInputArray;
               char*          pCurrentResName       = cpSetType->mpResourceTypeNames;
               const uint32_t cInputNameSpanInBytes = cMaxNameLength + 1; /* +1 For null terminating byte. */
               const uint32_t cResNameSpanInBytes   = cpSetType->mMaxNameLength + 1; /* +1 For null terminating byte. */

               strncpy(cpSetType->mpSetTypeName, pcCurrentInputName, cpSetType->mMaxNameLength);
               cpSetType->mpSetTypeName[cpSetType->mMaxNameLength] = 0;
               pcCurrentInputName += cInputNameSpanInBytes;

               for(i = 1; i <= cpSetType->mNumberOfResourceTypes; i++)
               {
                  strncpy(pCurrentResName, pcCurrentInputName, cpSetType->mMaxNameLength);
                  pCurrentResName[cpSetType->mMaxNameLength] = 0;
                  pcCurrentInputName += cInputNameSpanInBytes;
                  pCurrentResName    += cResNameSpanInBytes;
               }

               cpSetType->mNumberOfResources = 0;

               for(i = 0; i < cpSetType->mNumberOfResourceTypes; ++i)
               {
                  if(cInputArray[i+1] <= gcResMgr_MaxNumberOfResInstances)
                  {
                     cpSetType->mpNumberOfResourcePerType[i] = cInputArray[i+1];
                     cpSetType->mNumberOfResources += cInputArray[i+1];
                  }
                  else
                  {
                     areInputValuesValid = false;
                     libResult = LIB_FAILURE;
                     SHOW_ERROR(false); /* Bad!!! */
                     break;
                  }
               }

               if(areInputValuesValid == true)
               {
                  for(i = 0; i < cpSetType->mNumberOfSets; ++i)
                  {
                     struct ResMgr_Set* const cpSet = &(cpSetType->mpSets[i]);

                     uint32_t j = 0;
                     uint32_t k = 0;
                     uint32_t l = 0;

                     cpThis->mpBufferNext  = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                     cpSet->mppResources   = (struct ResMgr_Resource**)(cpThis->mpBufferNext);
                     cpThis->mpBufferNext += (cpSetType->mNumberOfResourceTypes * sizeof(struct ResMgr_Resource*)); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                     cpThis->mpBufferNext           = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                     cpSet->mpNumberOfFreeResources = (uint32_t*)(cpThis->mpBufferNext);
                     cpThis->mpBufferNext          += (cpSetType->mNumberOfResourceTypes * sizeof(cpSet->mpNumberOfFreeResources[0])); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                     cpThis->mpBufferNext             = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                     cpSet->mppFreeResourceIndexes = (uint32_t**)(cpThis->mpBufferNext);
                     cpThis->mpBufferNext            += (cpSetType->mNumberOfResourceTypes * sizeof(cpSet->mppFreeResourceIndexes[0])); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);


                     if(cpThis->mpBufferNext <= cpThis->mpBufferEnd)
                     {
                        for(j = 0; j < cpSetType->mNumberOfResourceTypes; ++j)
                        {
                           cpSet->mpNumberOfFreeResources[j] = cpSetType->mpNumberOfResourcePerType[j];

                           cpThis->mpBufferNext   = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                           cpSet->mppResources[j] = (struct ResMgr_Resource*)(cpThis->mpBufferNext);
                           cpThis->mpBufferNext  += (cpSetType->mpNumberOfResourcePerType[j] * sizeof(struct ResMgr_Resource)); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);

                           cpThis->mpBufferNext                = (cpThis->mpBufferNext + (sizeof(uintptr_t) - 1)) & ~(sizeof(uintptr_t) - 1); /* Start aligned */
                           cpSet->mppFreeResourceIndexes[j] = (uint32_t*)(cpThis->mpBufferNext);
                           cpThis->mpBufferNext               += (cpSetType->mpNumberOfResourcePerType[j] * sizeof(cpSet->mppFreeResourceIndexes[0][0])); SHOW_ERROR(cpThis->mpBufferNext <= cpThis->mpBufferEnd);


                           if(cpThis->mpBufferNext <= cpThis->mpBufferEnd)
                           {
                              l = cpSetType->mpNumberOfResourcePerType[j] - 1;
                              for(k = 0; k < cpSetType->mpNumberOfResourcePerType[j]; ++k, --l)
                              {
                                 cpSet->mppResources[j][k].mUserId = cpThis->mResMgr_UserId;
                                 cpSet->mppFreeResourceIndexes[j][k] = l;
                              }
                           }
                        }
                     }
                     else
                     {
                        libResult = LIB_FAILURE;
                        SHOW_ERROR(false); /* Bad!!! */
                        break;
                     }
                  }

                  if(cpThis->mpBufferNext <= cpThis->mpBufferEnd)
                  {
                     for(i = 0; i < cpSetType->mNumberOfResourceTypes; ++i)
                     {
                        outputArray[i+1] = i;
                     }

                     libResult = LIB_SUCCESS;
                  }
               }
            }
         }

      }
   }

   return libResult;
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
LIB_RESULT ResMgr_User_Type_Register_Private(int apexID, struct ResourceManager* const cpThis,
                                             const char* const cpcTypeNameInputArray,
                                             uint32_t const cMaxNameLength,
                                             uint32_t outputArray[],
                                             uint32_t const cSizeOfArrays)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      cpcTypeNameInputArray != 0 &&
      cMaxNameLength > 0 &&
      outputArray != 0 &&
      cSizeOfArrays > 0)
   {
      memset(outputArray, 0, cSizeOfArrays * sizeof(outputArray[0]));

      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         uint32_t i = 0;

         const char*    pcCurrentInputName    = cpcTypeNameInputArray;
         const uint32_t cInputNameSpanInBytes = cMaxNameLength + 1; /* +1 For null terminating byte. */

         uint32_t typeNameIndex = ~(0U); /* 0xFFFFFFFF is invalid index; */

         for (i = 0; i < cSizeOfArrays; ++i) /* Verification/Creation of each type name */
         {
            libResult = ResMgr_Helper_TypeName_Find(pcCurrentInputName,
                                                    cpThis->mUsers.mpUserTypeNames,
                                                    cpThis->mInits.mUser.mMaxNameLength,
                                                    cpThis->mUsers.mNumberOfUserTypes,
                                                    &typeNameIndex);
            if(libResult == LIB_SUCCESS)
            {
               if(typeNameIndex == ~(0U)) /* Name does not exist */
               {
                  if((cpThis->mInits.mUser.mMaxNumberOfTypes - cpThis->mUsers.mNumberOfUserTypes) > 0) /* There is free space for a new type name */
                  {
                     char* pCurrentName = 0;

                     typeNameIndex = cpThis->mUsers.mNumberOfUserTypes;
                     ++(cpThis->mUsers.mNumberOfUserTypes);
                     pCurrentName = cpThis->mUsers.mpUserTypeNames + (typeNameIndex * (cpThis->mInits.mUser.mMaxNameLength + 1));
                     strncpy(pCurrentName, pcCurrentInputName, cpThis->mInits.mUser.mMaxNameLength);
                     pCurrentName[cpThis->mInits.mUser.mMaxNameLength] = 0;
                  }
                  else
                  {
                     SHOW_ERROR(false); /* No more room, should reconsider initialization values */
                     libResult = LIB_FAILURE;
                     break;
                  }
               }

               outputArray[i] = typeNameIndex;

               /* */
               /* Prepare for next iteration */
               /* */
               pcCurrentInputName += cInputNameSpanInBytes;
            }
            else
            {
               SHOW_ERROR(false); /* Something bad happened in TypeName_Find */
               break;
            }
         }

      }
   }

   return libResult;
}

#ifndef __STANDALONE__
#include <sstream>
#endif

/*
 * Allocate <User>
 *
 * Input
 *    cUserTypeId_Index
 *
 * Output
 *    cpReturnedUserId
 */
LIB_RESULT ResMgr_User_Allocate_Private(int apexID, const uint32_t cThreadId,
                                        struct ResourceManager* const cpThis,
                                        uint32_t const cUserTypeId_Index,
                                        uint32_t* const cpReturnedUserId)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);
   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      cpReturnedUserId != 0)
   {
      (*cpReturnedUserId) = ~(0U);

      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         libResult = LIB_SUCCESS;

         if(libResult == LIB_SUCCESS)
         {
            libResult = LIB_FAILURE;

            if(cUserTypeId_Index < cpThis->mUsers.mNumberOfUserTypes)
            {
               if(cpThis->mUsers.mNumberOfFreeIndexes > 0)
               {
                  uint32_t userIndex = 0;

                  struct ResMgr_User* pUser = 0;

                  --(cpThis->mUsers.mNumberOfFreeIndexes);

                  userIndex = cpThis->mUsers.mpFreeIndexes[cpThis->mUsers.mNumberOfFreeIndexes];

                  cpThis->mUsers.mpFreeIndexes[cpThis->mUsers.mNumberOfFreeIndexes] = ~(0U);

                  SHOW_ERROR(userIndex < (gcResMgr_MaxNumberOfUsrTypes*gcResMgr_MaxNumberOfUsrInstances)); /* User Indexes should stay below  65536 or fit in 16 bits */

                  pUser = &(cpThis->mUsers.mpUsers[userIndex]);

                  *(cpReturnedUserId) = userIndex + (((uint32_t)pUser->mSessionId) << 16);  /* Storing session id in the high 16 bits of user id */

                  SHOW_ERROR(pUser->mIsFree == true); /* Would imply corruption? Regardless its bad! */

                  pUser->mIsFree = false;
		  
		  libResult = LIB_SUCCESS;
		  
		  
		    
               }
               else
               {
                  SHOW_ERROR(false); /* Semaphore count and mNumberOfFreeIndexes should always be in sync!!! */
               }
            }
	    
         }
      }
   }

   return libResult;
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
LIB_RESULT ResMgr_User_Deallocate_Private(int apexID, const uint32_t cThreadId,
                                          struct ResourceManager* const cpThis,
                                          uint32_t const cUserId)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true)
   {
      bool weFreedUser = false;

      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */
         const uint32_t cUserSession = cUserId >> 16;     /* SASHBY: Magic Number Bad!!! */

         struct ResMgr_User* const cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

         libResult = LIB_FAILURE;

         if(cUserIndex != cpThis->mResMgr_UserId &&
            cUserIndex < cpThis->mInits.mUser.mMaxNumberOfObject &&
            cpUser->mSessionId == cUserSession &&
            cpUser->mNumberOfAllocatedResources == 0 &&
            cpUser->mIsWaitingOnResources == false &&
            cpUser->mIsFree == false &&
            cpThis->mUsers.mNumberOfFreeIndexes < cpThis->mInits.mUser.mMaxNumberOfObject)
         {
            cpThis->mUsers.mpFreeIndexes[cpThis->mUsers.mNumberOfFreeIndexes] = cUserIndex;

            ++(cpThis->mUsers.mNumberOfFreeIndexes);

            ++(cpUser->mSessionId);

            cpUser->mIsFree = true;

            weFreedUser = true;

            libResult = LIB_SUCCESS;
         }
         else if(cpUser->mSessionId != cUserSession)
         {
            libResult = LIB_ERROR_INVALID_USER_ID;
         }
         else if(cpUser->mNumberOfAllocatedResources > 0)
         {
            libResult = LIB_ERROR_USER_STILL_OWNS_RESOURCES;
         }
         else if(cpUser->mIsWaitingOnResources == true)
         {
            libResult = LIB_ERROR_USER_WAITING_ON_RESOURCES;
         }
         else
         {
            SHOW_ERROR(false);
            libResult = LIB_FAILURE;
         }

         SHOW_ERROR(libResult != LIB_SUCCESS ||
                    cpUser->mIsFree == true);

      }

      if(weFreedUser == true)
      {
         libResult = LIB_SUCCESS;
      }
   }

   return libResult;
}



/*
 * Allocate <Resource>
 *
 * Input
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
static LIB_RESULT ResMgr_Helper_Output_Array_Validate(int apexID, struct ResourceManager* const cpThis,
                                                      uint32_t outputArray[][5],
                                                      uint32_t const cSizeOfOutputArray)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      outputArray != 0 &&
      cSizeOfOutputArray <= cpThis->mInits.mMaxNumberOfResourcesInAllocation)
   {
      uint32_t (*pEntry)[5] = &(outputArray[cSizeOfOutputArray-1]);

      if((*pEntry)[0] < cSizeOfOutputArray &&
         (*pEntry)[1] < cpThis->mSetTypes.mNumberOfSetTypes &&
         (*pEntry)[2] < cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mNumberOfSets &&
         (*pEntry)[3] < cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mNumberOfResourceTypes &&
         (*pEntry)[4] < cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mpNumberOfResourcePerType[(*pEntry)[3]])
      {
         uint32_t i = 0;
         uint32_t (*pEntryNext)[5] = 0;

         libResult = LIB_SUCCESS; /* Value are fine unless we find a problem */

         for(i = 0; i < (cSizeOfOutputArray-1); ++i)
         {
            pEntry     = &(outputArray[i]);
            pEntryNext = &(outputArray[i+1]);

            if((*pEntry)[0] >= cSizeOfOutputArray ||
               (*pEntry)[1] >= cpThis->mSetTypes.mNumberOfSetTypes ||
               (*pEntry)[2] >= cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mNumberOfSets ||
               (*pEntry)[3] >= cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mNumberOfResourceTypes ||
               (*pEntry)[4] >= cpThis->mSetTypes.mpSetTypes[(*pEntry)[1]].mpNumberOfResourcePerType[(*pEntry)[3]] ||
               (*pEntry)[0] > (*pEntryNext)[0])
            {
               libResult = LIB_FAILURE;
               break;
            }
         }
      }
   }

   return libResult;
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
static LIB_RESULT ResMgr_Helper_Resource_Allocate_TT(int apexID, struct ResourceManager* const cpThis,
                                                     uint32_t const cUserId,
                                                     uint32_t cInputArray[][3],
                                                     uint32_t const cSizeOfInputArray,
                                                     uint32_t outputArray[][5],
                                                     uint32_t const cSizeOfOutputArray)
{
   LIB_RESULT libResult = LIB_FAILURE;

   const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */
   const uint32_t cUserSession = cUserId >> 16;     /* SASHBY: Magic Number Bad!!! */

   struct ResMgr_User* cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

   if(cUserId != cpThis->mResMgr_UserId &&
      cSizeOfOutputArray <= cpThis->mInits.mMaxNumberOfResourcesInAllocation &&
      cUserIndex < cpThis->mInits.mUser.mMaxNumberOfObject &&
      cpUser->mSessionId == cUserSession &&
      cpUser->mIsFree == false &&
      cpUser->mNumberOfAllocatedResources == 0 &&      /* User should only allocate if he has no outstanding allocated resources */
      cpThis->mScratchPadSizeInBytes >= (cSizeOfInputArray * sizeof(cInputArray[0])) + (gcResMgr_MaxNumberOfSetTypes * sizeof(cInputArray[0][0])))
   {
      bool areInputValuesValid = false;
      uint32_t totalNumberOfResources = 0;

      uint32_t (*pSortedInputArray)[3]    = (uint32_t(*)[3])cpThis->mpScratchPad;       /* *3 is the number of element in each entry of cInputArray */
      uint32_t* const cpSetTypeToSetIdMap = cpThis->mpScratchPad + (cSizeOfInputArray * sizeof(cInputArray[0]) / sizeof(cInputArray[0][0]));

      memcpy(cpThis->mpScratchPad, cInputArray, cSizeOfInputArray*sizeof(cInputArray[0]));

      /*
       * pSortedInputArray is sorted according to:
       *
       *    1. Set Type Id
       *    2. Res Type Id
       *
       * See details of what qsort does: http://www.cplusplus.com/reference/cstdlib/qsort/
       */
      qsort (cpThis->mpScratchPad,
             cSizeOfInputArray,
             sizeof(cInputArray[0]),
             ResMgr_Helper_qsort_compare_uint32_t_x3_2_1);

      if(pSortedInputArray[cSizeOfInputArray-1][0] <  cpThis->mSetTypes.mNumberOfSetTypes &&  /* Check validity of values */
         pSortedInputArray[cSizeOfInputArray-1][1] <  cpThis->mSetTypes.mpSetTypes[pSortedInputArray[cSizeOfInputArray-1][0]].mNumberOfResourceTypes &&
         pSortedInputArray[cSizeOfInputArray-1][2] <= cpThis->mSetTypes.mpSetTypes[pSortedInputArray[cSizeOfInputArray-1][0]].mpNumberOfResourcePerType[pSortedInputArray[cSizeOfInputArray-1][1]])
      {
         uint32_t i = 0;

         areInputValuesValid = true;
         totalNumberOfResources = pSortedInputArray[cSizeOfInputArray-1][2];

         for(i = 0; i < (cSizeOfInputArray-1); ++i)
         {
            totalNumberOfResources += pSortedInputArray[i][2];

            if(pSortedInputArray[i][0] >=  cpThis->mSetTypes.mNumberOfSetTypes ||  /* Check validity of values */
               pSortedInputArray[i][1] >=  cpThis->mSetTypes.mpSetTypes[pSortedInputArray[i][0]].mNumberOfResourceTypes ||
               pSortedInputArray[i][2] >   cpThis->mSetTypes.mpSetTypes[pSortedInputArray[i][0]].mpNumberOfResourcePerType[pSortedInputArray[i][1]] ||
               (pSortedInputArray[i][0] == pSortedInputArray[i+1][0] &&
                pSortedInputArray[i][1] == pSortedInputArray[i+1][1])) /* Check for duplicates */
            {
               areInputValuesValid = false;
               break;
            }
         }

         if(cSizeOfOutputArray < totalNumberOfResources)
         {
            areInputValuesValid = false;
         }
      }

      if(areInputValuesValid == true)
      {
         bool areAllResourcesAvailable = true;

         uint32_t i = 0;
         uint32_t j = 0;
         uint32_t setTypeBegin = 0;

         uint32_t setType = pSortedInputArray[setTypeBegin][0];

         struct ResMgr_SetType* pSetType = &(cpThis->mSetTypes.mpSetTypes[setType]);

         /* While there are more set types in the input array*/
         while(pSetType != 0)
         {
            bool weFoundASetWithEnoughResources = false;

            /* Look for a Set instance which has all the resources requested by the caller for the current Set Type */
            for(i = 0; i < pSetType->mNumberOfSets; ++i)
            {
               const struct ResMgr_Set* pcSet = &(pSetType->mpSets[i]);

               /* Check that this set instance has all the resources requested by the caller for the current Set Type */
               for(j = setTypeBegin; j < cSizeOfInputArray; ++j)
               {
                  if(pSortedInputArray[j][0] != setType)
                  {
                     weFoundASetWithEnoughResources = true;
                     break; /* This set instance has enough of this resource type */
                  }

                  if(pSortedInputArray[j][2] > pcSet->mpNumberOfFreeResources[pSortedInputArray[j][1]])
                  {
                     areAllResourcesAvailable = false;
                     break; /* This set instance is missing resources */
                  }
                  else if(j == (cSizeOfInputArray - 1))
                  {
                     weFoundASetWithEnoughResources = true;
                  }
               }

               if(weFoundASetWithEnoughResources == true)
               {
                  cpSetTypeToSetIdMap[setType] = i;  /* "i" would be the Set Id */
                  break;                             /* Move on to the next Set Type */
               }
            }

            if(weFoundASetWithEnoughResources == true &&
               j < cSizeOfInputArray)
            {
               setTypeBegin = j;
               setType  = pSortedInputArray[setTypeBegin][0];
               pSetType = &(cpThis->mSetTypes.mpSetTypes[setType]);
            }
            else
            {
               if(weFoundASetWithEnoughResources == true)
               {
                  areAllResourcesAvailable = true;
               }

               pSetType = 0; /* Should get us out of the loop */
            }
         }

         if(areAllResourcesAvailable == true) /* Go ahead and allocate them */
         {
            uint32_t k = 0; /* Index in the output arrays */

            for(i = 0; i < cSizeOfInputArray; ++i)
            {
               struct ResMgr_Set* const cpSet = &(cpThis->mSetTypes.mpSetTypes[cInputArray[i][0]].mpSets[cpSetTypeToSetIdMap[cInputArray[i][0]]]);

               SHOW_ERROR(cpSetTypeToSetIdMap[cInputArray[i][0]] < cpThis->mSetTypes.mpSetTypes[cInputArray[i][0]].mNumberOfSets);

               for(j = 0; j < cInputArray[i][2]; ++j)
               {
                  outputArray[k][0] = i;
                  outputArray[k][1] = cInputArray[i][0];
                  outputArray[k][2] = cpSetTypeToSetIdMap[cInputArray[i][0]];
                  outputArray[k][3] = cInputArray[i][1];

                  --(cpSet->mpNumberOfFreeResources[cInputArray[i][1]]);

                  outputArray[k][4] = cpSet->mppFreeResourceIndexes[cInputArray[i][1]][cpSet->mpNumberOfFreeResources[cInputArray[i][1]]];
                  cpSet->mppFreeResourceIndexes[cInputArray[i][1]][cpSet->mpNumberOfFreeResources[cInputArray[i][1]]] = ~(0U);

                  SHOW_ERROR(cpSet->mppResources[cInputArray[i][1]][outputArray[k][4]].mUserId == cpThis->mResMgr_UserId);

                  cpSet->mppResources[cInputArray[i][1]][outputArray[k][4]].mUserId = cUserId;
                  ++k;
               }
            }
            cpUser->mNumberOfAllocatedResources = totalNumberOfResources;

            SHOW_ERROR(LIB_SUCCESS == ResMgr_Helper_Output_Array_Validate(apexID, cpThis,
                                                                               outputArray,
                                                                               cSizeOfOutputArray));

            libResult = LIB_SUCCESS;
         }
         else
         {
            libResult = LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE;
         }
      }
   }
   else if(cUserId == cpThis->mResMgr_UserId ||
           cpUser->mIsFree == true)
   {
      libResult = LIB_ERROR_INVALID_USER_ID;
   }
   else if(cSizeOfOutputArray > cpThis->mInits.mMaxNumberOfResourcesInAllocation)
   {
      libResult = LIB_ERROR_OUTPUT_ARRAY_SIZE_TOO_LARGE;
   }
   else if(cUserIndex >= cpThis->mInits.mUser.mMaxNumberOfObject)
   {
      libResult = LIB_ERROR_USER_INDEX_TOO_LARGE;
   }
   else if(cpUser->mSessionId != cUserSession)
   {
      libResult = LIB_ERROR_SESSION_ID_MISMATCH;
   }
   else if(cpUser->mNumberOfAllocatedResources > 0)
   {
      libResult = LIB_ERROR_USER_STILL_HAS_RESOURCES;
   }
   else
   {
      SHOW_ERROR(false);
   }

   return libResult;
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
static LIB_RESULT ResMgr_Helper_Resource_Allocate_TI(int apexID, struct ResourceManager* const cpThis,
                                                     uint32_t const cUserId,
                                                     uint32_t cInputArray[][3],
                                                     uint32_t const cSizeOfInputArray,
                                                     uint32_t outputArray[][5],
                                                     uint32_t const cSizeOfOutputArray)
{
   LIB_RESULT libResult = LIB_FAILURE;

   const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */
   const uint32_t cUserSession = cUserId >> 16;     /* SASHBY: Magic Number Bad!!! */

   struct ResMgr_User* cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

   if(cUserId != cpThis->mResMgr_UserId &&
      cSizeOfOutputArray <= cpThis->mInits.mMaxNumberOfResourcesInAllocation &&
      cUserIndex < cpThis->mInits.mUser.mMaxNumberOfObject &&
      cpUser->mSessionId == cUserSession &&
      cpUser->mIsFree == false &&
      cpUser->mNumberOfAllocatedResources == 0 &&      /* User should only allocate if he has no outstanding allocated resources */
      cpThis->mScratchPadSizeInBytes >= (cSizeOfInputArray * sizeof(cInputArray[0])) + (gcResMgr_MaxNumberOfSetTypes * sizeof(cInputArray[0][0])))
   {
      bool areInputValuesValid = false;
      uint32_t totalNumberOfResources = 0;

      uint32_t (*pSortedInputArray)[3]    = (uint32_t(*)[3])cpThis->mpScratchPad;       /* *3 is the number of element in each entry of cInputArray */
      uint32_t* const cpSetTypeToSetIdMap = cpThis->mpScratchPad + (cSizeOfInputArray * sizeof(cInputArray[0]) / sizeof(cInputArray[0][0]));

      memcpy(cpThis->mpScratchPad, cInputArray, cSizeOfInputArray*sizeof(cInputArray[0]));

      /*
       * pSortedInputArray is sorted according to:
       *
       *    1. Set Type Id
       *    2. Res Type Id
       *
       * See details of what qsort does: http://www.cplusplus.com/reference/cstdlib/qsort/
       */
      qsort (cpThis->mpScratchPad,
             cSizeOfInputArray,
             sizeof(cInputArray[0]),
             ResMgr_Helper_qsort_compare_uint32_t_x3_2_1_0);

      if(pSortedInputArray[cSizeOfInputArray-1][0] < cpThis->mSetTypes.mNumberOfSetTypes &&  /* Check validity of values */
         pSortedInputArray[cSizeOfInputArray-1][1] < cpThis->mSetTypes.mpSetTypes[pSortedInputArray[cSizeOfInputArray-1][0]].mNumberOfResourceTypes &&
         pSortedInputArray[cSizeOfInputArray-1][2] < cpThis->mSetTypes.mpSetTypes[pSortedInputArray[cSizeOfInputArray-1][0]].mpNumberOfResourcePerType[pSortedInputArray[cSizeOfInputArray-1][1]])
      {
         uint32_t i = 0;

         areInputValuesValid = true;
         ++totalNumberOfResources;

         for(i = 0; i < (cSizeOfInputArray-1); ++i)
         {
            ++totalNumberOfResources;

            if(pSortedInputArray[i][0] >=  cpThis->mSetTypes.mNumberOfSetTypes ||  /* Check validity of values */
               pSortedInputArray[i][1] >=  cpThis->mSetTypes.mpSetTypes[pSortedInputArray[i][0]].mNumberOfResourceTypes ||
               pSortedInputArray[i][2] >=  cpThis->mSetTypes.mpSetTypes[pSortedInputArray[i][0]].mpNumberOfResourcePerType[pSortedInputArray[i][1]] ||
               (pSortedInputArray[i][0] == pSortedInputArray[i+1][0] &&
                pSortedInputArray[i][1] == pSortedInputArray[i+1][1] &&
                pSortedInputArray[i][2] == pSortedInputArray[i+1][2])) /* Check for duplicates */
            {
               areInputValuesValid = false;
               break;
            }
         }

         if(cSizeOfOutputArray < totalNumberOfResources)
         {
            areInputValuesValid = false;
         }
      }

      if(areInputValuesValid == true)
      {
         bool areAllResourcesAvailable = true;

         uint32_t i = 0;
         uint32_t j = 0;
         uint32_t setTypeBegin = 0;

         uint32_t setType = pSortedInputArray[setTypeBegin][0];

         struct ResMgr_SetType* pSetType = &(cpThis->mSetTypes.mpSetTypes[setType]);

         /* While there are more set types in the input array*/
         while(pSetType != 0)
         {
            bool weFoundASetWithEnoughResources = false;

            /* Look for a Set instance which has all the resources requested by the caller for the current Set Type */
            for(i = 0; i < pSetType->mNumberOfSets; ++i)
            {
               const struct ResMgr_Set* pcSet = &(pSetType->mpSets[i]);

               /* Check that this set instance has all the resources requested by the caller for the current Set Type */
               for(j = setTypeBegin; j < cSizeOfInputArray; ++j)
               {
                  if(pSortedInputArray[j][0] != setType)
                  {
                     weFoundASetWithEnoughResources = true;
                     break; /* This set instance has enough of this resource type */
                  }

                  if(pcSet->mppResources[pSortedInputArray[j][1]][pSortedInputArray[j][2]].mUserId != cpThis->mResMgr_UserTypeIndex) /* Means this instance is allocated/not free */
                  {
                     areAllResourcesAvailable = false;
                     break; /* This set instance is missing resources */
                  }
                  else if(j == (cSizeOfInputArray - 1))
                  {
                     weFoundASetWithEnoughResources = true;
                  }
               }

               if(weFoundASetWithEnoughResources == true)
               {
                  cpSetTypeToSetIdMap[setType] = i;  /* "i" would be the Set Id */
                  break;                             /* Move on to the next Set Type */
               }
            }

            if(weFoundASetWithEnoughResources == true &&
               j < cSizeOfInputArray)
            {
               setTypeBegin = j;
               setType  = pSortedInputArray[setTypeBegin][0];
               pSetType = &(cpThis->mSetTypes.mpSetTypes[setType]);
            }
            else
            {
               if(weFoundASetWithEnoughResources == true)
               {
                  areAllResourcesAvailable = true;
               }

               pSetType = 0; /* Should get us out of the loop */
            }
         }

         if(areAllResourcesAvailable == true) /* Go ahead and allocate them */
         {
            uint32_t k = 0; /* Index in the output arrays */
            bool weStartCompacting = false;

            for(i = 0; i < cSizeOfInputArray; ++i)
            {
               struct ResMgr_Set* const cpSet = &(cpThis->mSetTypes.mpSetTypes[cInputArray[i][0]].mpSets[cpSetTypeToSetIdMap[cInputArray[i][0]]]);

               SHOW_ERROR(cpSetTypeToSetIdMap[cInputArray[i][0]] < cpThis->mSetTypes.mpSetTypes[cInputArray[i][0]].mNumberOfSets);

               outputArray[k][0] = i;
               outputArray[k][1] = cInputArray[i][0];
               outputArray[k][2] = cpSetTypeToSetIdMap[cInputArray[i][0]];
               outputArray[k][3] = cInputArray[i][1];
               outputArray[k][4] = cInputArray[i][2];

               SHOW_ERROR(cpSet->mppResources[cInputArray[i][1]][outputArray[k][4]].mUserId == cpThis->mResMgr_UserId);

               cpSet->mppResources[cInputArray[i][1]][outputArray[k][4]].mUserId = cUserId;

               /* Need remove the instance from the free list and compact it */
               weStartCompacting = false;

               for(j = 0; j < (cpSet->mpNumberOfFreeResources[cInputArray[i][1]] - 1); ++j)
               {
                  if(cpSet->mppFreeResourceIndexes[cInputArray[i][1]][j] == outputArray[k][4])
                  {
                     weStartCompacting = true;
                  }

                  if(weStartCompacting == true)
                  {
                     cpSet->mppFreeResourceIndexes[cInputArray[i][1]][j] = cpSet->mppFreeResourceIndexes[cInputArray[i][1]][j+1];
                  }
               }

               --(cpSet->mpNumberOfFreeResources[cInputArray[i][1]]);

               cpSet->mppFreeResourceIndexes[cInputArray[i][1]][cpSet->mpNumberOfFreeResources[cInputArray[i][1]]] = ~(0U);

               ++k;
            }
            cpUser->mNumberOfAllocatedResources = totalNumberOfResources;

            SHOW_ERROR(LIB_SUCCESS == ResMgr_Helper_Output_Array_Validate(apexID, cpThis,
                                                                               outputArray,
                                                                               cSizeOfOutputArray));
            libResult = LIB_SUCCESS;
         }
         else
         {
            libResult = LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE;
         }
      }
   }
   else if(cUserId == cpThis->mResMgr_UserId ||
           cpUser->mIsFree == true)
   {
      libResult = LIB_ERROR_INVALID_USER_ID;
   }
   else if(cSizeOfOutputArray > cpThis->mInits.mMaxNumberOfResourcesInAllocation)
   {
      libResult = LIB_ERROR_OUTPUT_ARRAY_SIZE_TOO_LARGE;
   }
   else if(cUserIndex >= cpThis->mInits.mUser.mMaxNumberOfObject)
   {
      libResult = LIB_ERROR_USER_INDEX_TOO_LARGE;
   }
   else if(cpUser->mSessionId != cUserSession)
   {
      libResult = LIB_ERROR_SESSION_ID_MISMATCH;
   }
   else if(cpUser->mNumberOfAllocatedResources > 0)
   {
      libResult = LIB_ERROR_USER_STILL_HAS_RESOURCES;
   }
   else
   {
      SHOW_ERROR(false);
   }

   return libResult;
}



/*
 * Hmm
 */
static LIB_RESULT ResMgr_Helper_ScanWaitingUserQueue(int apexID, const uint32_t cThreadId,
                                                     struct ResourceManager* const cpThis)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      cpThis->mQueue.mCount > 0)
   {
      uint32_t peekedUserId = 0;

      do
      {
         libResult = ResMgr_Queue_PeekFront(&(cpThis->mQueue),
                                            &peekedUserId); SHOW_ERROR(libResult == LIB_SUCCESS &&
                                                                       peekedUserId != cpThis->mResMgr_UserId);
         if(libResult == LIB_SUCCESS)
         {
            const uint32_t cQueuedUserIndex = peekedUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */

            struct ResMgr_User* const cpQueuedUser = &(cpThis->mUsers.mpUsers[cQueuedUserIndex]);

            if(cpQueuedUser->mIsAllocatingInstances == true)
            {
               libResult = ResMgr_Helper_Resource_Allocate_TI(apexID, cpThis,
                                                              peekedUserId,
                                                              cpQueuedUser->mpInputArray,
                                                              cpQueuedUser->mSizeOfInputArray,
                                                              cpQueuedUser->mpOutputArray,
                                                              cpQueuedUser->mSizeOfOutputArray);
            }
            else
            {
               libResult = ResMgr_Helper_Resource_Allocate_TT(apexID, cpThis,
                                                              peekedUserId,
                                                              cpQueuedUser->mpInputArray,
                                                              cpQueuedUser->mSizeOfInputArray,
                                                              cpQueuedUser->mpOutputArray,
                                                              cpQueuedUser->mSizeOfOutputArray);
            }

            if(libResult == LIB_SUCCESS)
            {
               uint32_t poppedUserId = 0;

               libResult = ResMgr_Queue_PopFront(&(cpThis->mQueue),
                                                 &poppedUserId); SHOW_ERROR(libResult == LIB_SUCCESS &&
                                                                            peekedUserId == poppedUserId);
               if(libResult == LIB_SUCCESS)
               {
                  if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X UNBLOCKED\n", cThreadId, peekedUserId); }

                  libResult = LIB_SUCCESS;

                  if(libResult == LIB_SUCCESS)
                  {
                     libResult = LIB_USER_OBTAINED_RESOURCES;
                  }
               }
            }
         }
      }
      while(libResult == LIB_USER_OBTAINED_RESOURCES &&
            cpThis->mQueue.mCount > 0);


      if(libResult == LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE ||
         libResult == LIB_USER_OBTAINED_RESOURCES)
      {
         libResult = LIB_SUCCESS;
      }
   }
   else if(cpThis != 0)
   {
      libResult = LIB_SUCCESS;
   }

   return libResult;
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
LIB_RESULT ResMgr_Resource_Allocate_TT_Private(int apexID, const uint32_t cThreadId,
                                               struct ResourceManager* const cpThis,
                                               uint32_t const cUserId,
                                               uint32_t       inputArray[][3],
                                               uint32_t const cSizeOfInputArray,
                                               uint32_t       outputArray[][5],
                                               uint32_t const cSizeOfOutputArray)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */

   struct ResMgr_User* cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      inputArray != 0 &&
      cSizeOfInputArray > 0 &&
      outputArray != 0 &&
      cSizeOfOutputArray >= cSizeOfInputArray)
   {
      bool weWaitForResources = false;

      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         libResult = ResMgr_Helper_ScanWaitingUserQueue(apexID, cThreadId,
                                                        cpThis);
         if(libResult == LIB_SUCCESS)
         {
            libResult = ResMgr_Helper_Resource_Allocate_TT(apexID, cpThis,
                                                             cUserId,
                                                             inputArray,
                                                             cSizeOfInputArray,
                                                             outputArray,
                                                             cSizeOfOutputArray);

            if(libResult == LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE)
            {
               memcpy(cpUser->mpInputArray, inputArray, cSizeOfInputArray*sizeof(inputArray[0]));

               cpUser->mSizeOfInputArray  = cSizeOfInputArray;
               cpUser->mSizeOfOutputArray = cSizeOfOutputArray;

               cpUser->mIsAllocatingInstances = false;
               cpUser->mIsWaitingOnResources  = true;

               libResult = ResMgr_Queue_PushBack(&(cpThis->mQueue),
                                                 cUserId); SHOW_ERROR(libResult == LIB_SUCCESS);
               if(libResult == LIB_SUCCESS)
               {
                  weWaitForResources = true;
               }
            }
            else if(libResult == LIB_SUCCESS)
            {
               if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X NOWAIT\n", cThreadId, cUserId); }
            }
         }

      }

      if(weWaitForResources == true)
      {
         if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X WAIT\n", cThreadId, cUserId); }

         libResult = LIB_SUCCESS;

         if(libResult == LIB_SUCCESS)
         {
            libResult = LIB_SUCCESS;

            if(libResult == LIB_SUCCESS)
            {
               if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X OBTAINED\n", cThreadId, cUserId); }
               SHOW_ERROR(cSizeOfOutputArray == cpUser->mSizeOfOutputArray);

               /* Copy the results over */
               memcpy(outputArray, cpUser->mpOutputArray, cpUser->mSizeOfOutputArray*sizeof(cpUser->mpOutputArray[0]));

               cpUser->mIsWaitingOnResources  = false;

               SHOW_ERROR(LIB_SUCCESS == ResMgr_Helper_Output_Array_Validate(apexID, cpThis,
                                                                                  outputArray,
                                                                                  cSizeOfOutputArray));

            }
         }
      }
   }

   return libResult;
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
LIB_RESULT ResMgr_Resource_Allocate_TI_Private(int apexID, const uint32_t cThreadId,
                                               struct ResourceManager* const cpThis,
                                               uint32_t const cUserId,
                                               uint32_t       inputArray[][3],
                                               uint32_t const cSizeOfInputArray,
                                               uint32_t       outputArray[][5],
                                               uint32_t const cSizeOfOutputArray)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */

   struct ResMgr_User* cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      inputArray != 0 &&
      cSizeOfInputArray > 0 &&
      outputArray != 0 &&
      cSizeOfOutputArray >= cSizeOfInputArray)
   {
      bool weWaitForResources = false;

      libResult = LIB_SUCCESS;

      if(libResult == LIB_SUCCESS)
      {
         libResult = ResMgr_Helper_ScanWaitingUserQueue(apexID, cThreadId,
                                                        cpThis);
         if(libResult == LIB_SUCCESS)
         {
            libResult = ResMgr_Helper_Resource_Allocate_TI(apexID, cpThis,
                                                           cUserId,
                                                           inputArray,
                                                           cSizeOfInputArray,
                                                           outputArray,
                                                           cSizeOfOutputArray);

            if(libResult == LIB_RESOURCES_NOT_CURRENTLY_AVAILABLE)
            {
               memcpy(cpUser->mpInputArray, inputArray, cSizeOfInputArray*sizeof(inputArray[0]));

               cpUser->mSizeOfInputArray  = cSizeOfInputArray;
               cpUser->mSizeOfOutputArray = cSizeOfOutputArray;

               cpUser->mIsAllocatingInstances = true;
               cpUser->mIsWaitingOnResources  = true;

               libResult = ResMgr_Queue_PushBack(&(cpThis->mQueue),
                                                 cUserId); SHOW_ERROR(libResult == LIB_SUCCESS);
               if(libResult == LIB_SUCCESS)
               {
                  weWaitForResources = true;
               }
            }
            else if(libResult == LIB_SUCCESS)
            {
               if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X NOWAIT\n", cThreadId, cUserId); }
            }
         }

      }

      if(weWaitForResources == true)
      {
         if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X WAIT\n", cThreadId, cUserId); }

         libResult = LIB_SUCCESS;

         if(libResult == LIB_SUCCESS)
         {
            libResult = LIB_SUCCESS;

            if(libResult == LIB_SUCCESS)
            {
               if(gscAreTracesEnabled[apexID] == true) { printf("            %d %6X OBTAINED\n", cThreadId, cUserId); }
               SHOW_ERROR(cSizeOfOutputArray == cpUser->mSizeOfOutputArray);

               /* Copy the results over */
               memcpy(outputArray, cpUser->mpOutputArray, cpUser->mSizeOfOutputArray*sizeof(cpUser->mpOutputArray[0]));

               cpUser->mIsWaitingOnResources  = false;

               SHOW_ERROR(LIB_SUCCESS == ResMgr_Helper_Output_Array_Validate(apexID, cpThis,
                                                                                  outputArray,
                                                                                  cSizeOfOutputArray));

            }
         }
      }
   }

   return libResult;
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
LIB_RESULT ResMgr_Resource_Deallocate_Private(int apexID, const uint32_t cThreadId,
                                              struct ResourceManager* const cpThis,
                                              uint32_t const cUserId,
                                              uint32_t       inputArray[][5],
                                              uint32_t const cSizeOfInputArray)
{
   LIB_RESULT libResult    = LIB_FAILURE;

   const uint32_t cUserIndex   = cUserId & 0xFFFF; /* SASHBY: Magic Number Bad!!! */
   const uint32_t cUserSession = cUserId >> 16;     /* SASHBY: Magic Number Bad!!! */

   struct ResMgr_User* cpUser = &(cpThis->mUsers.mpUsers[cUserIndex]);

   SHOW_ERROR(gsIsResourceManagerInitialized[apexID] == true);

   if(cpThis != 0 &&
      cpThis->mIsInitialized == true &&
      inputArray != 0 &&
      cSizeOfInputArray > 0)
   {
      libResult = LIB_SUCCESS;

      SHOW_ERROR(LIB_SUCCESS == ResMgr_Helper_Output_Array_Validate(apexID, cpThis,
                                                                         inputArray,
                                                                         cSizeOfInputArray));
      if(libResult == LIB_SUCCESS)
      {
         libResult = LIB_FAILURE;

         if(cUserId != cpThis->mResMgr_UserId &&
            cUserIndex < cpThis->mInits.mUser.mMaxNumberOfObject &&
            cpUser->mSessionId == cUserSession &&
            cpUser->mNumberOfAllocatedResources > 0 &&
            cpUser->mIsWaitingOnResources == false &&
            cpUser->mIsFree == false)
         {
            uint32_t i = 0;
            uint32_t j = cSizeOfInputArray-1; /* Index in the input arrays */

            libResult = LIB_SUCCESS;

            for(i = 0; i < cSizeOfInputArray; ++i)
            {
               struct ResMgr_Set* const cpSet = &(cpThis->mSetTypes.mpSetTypes[inputArray[j][1]].mpSets[inputArray[j][2]]);

               if(cpSet->mppResources[inputArray[j][3]][inputArray[j][4]].mUserId == cUserId)
               {
                  cpSet->mppResources[inputArray[j][3]][inputArray[j][4]].mUserId = cpThis->mResMgr_UserId;

                  cpSet->mppFreeResourceIndexes[inputArray[j][3]][cpSet->mpNumberOfFreeResources[inputArray[j][3]]] = inputArray[j][4];

                  ++(cpSet->mpNumberOfFreeResources[inputArray[j][3]]);
               }
               else
               {
                  libResult = LIB_ERROR_ATTEMPT_DEALLOC_UNOWNED_RESOURCE;
                  break;
               }
               /* Going backwards so that I can reintroduce the resources in the reverse order
                * I may get rid of it, but it allows to restore the ResMgr data structures to their original state
                * Could be pointless because in complex cases things get jumbled anyways.
                * Mostly useful in debugging because ResMgr reallocates the same resources in the same order.
                */
               --j;
            }

            cpUser->mNumberOfAllocatedResources -= i;

            SHOW_ERROR(cpUser->mNumberOfAllocatedResources == 0);

            if(libResult == LIB_SUCCESS)
            {
               libResult = ResMgr_Helper_ScanWaitingUserQueue(apexID, cThreadId,
                                                              cpThis);
            }
         }

      }
   }

   return libResult;
}





