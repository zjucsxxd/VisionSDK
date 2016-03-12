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


#include "resource_manager_types.h"
#include <string.h>


LIB_RESULT ResMgr_Helper_TypeName_Find(const char* const cpcTypeNameToFind,
                                       const char* const cpcTypeNames,
                                       uint32_t const cMaxNameLength,
                                       uint32_t const cNumberOfTypes,
                                       uint32_t* const cpReturnedIndex)
{
   /* */
   /* Could optimize if I used OrderedLookup and did a binary search */
   /* */
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpcTypeNameToFind != 0 &&
      cpcTypeNameToFind[0] != 0 &&  /* Don't want empty string */
      cpcTypeNames != 0 &&
      cMaxNameLength > 0 &&
      cpReturnedIndex != 0)
   {
      uint32_t i = 0;

      const char* pcCurrentName = cpcTypeNames;
      const uint32_t cNameSpanInBytes = cMaxNameLength + 1; /* +1 For null terminating byte. */

      *cpReturnedIndex = ~(0U);

      for (i = 0; i < cNumberOfTypes; ++i)
      {
         if(strncmp(cpcTypeNameToFind, pcCurrentName, cMaxNameLength) == 0)
         {
            *cpReturnedIndex = i;
            break;
         }
         pcCurrentName += cNameSpanInBytes;
      }

      libResult = LIB_SUCCESS;
   }

   return libResult;
}



int ResMgr_Helper_qsort_compare_uint32_t_x3_2_1 (const void * a, const void * b)
{
   int intResult = 0;

   const uint32_t* const cpcA = (uint32_t*)a;
   const uint32_t* const cpcB = (uint32_t*)b;

   intResult = (cpcA[2] > cpcB[2]) - (cpcB[2] > cpcA[2]);

   if(intResult == 0)
   {
      intResult = (cpcA[1] > cpcB[1]) - (cpcB[1] > cpcA[1]);
   }

   return intResult;
}



int ResMgr_Helper_qsort_compare_uint32_t_x3_2_1_0(const void * a, const void * b)
{
   int intResult = 0;

   const uint32_t* const cpcA = (uint32_t*)a;
   const uint32_t* const cpcB = (uint32_t*)b;

   intResult = (cpcA[2] > cpcB[2]) - (cpcB[2] > cpcA[2]);

   if(intResult == 0)
   {
      intResult = (cpcA[1] > cpcB[1]) - (cpcB[1] > cpcA[1]);

      if(intResult == 0)
      {
         intResult = (cpcA[0] > cpcB[0]) - (cpcB[0] > cpcA[0]);
      }
   }

   return intResult;
}






/* */
/* http://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c */
/* */
/* struct ResMgr_Queue */
/* { */
/*     uint32_t* mpBuffer;     // data buffer */
/*     uint32_t* mpBufferEnd;  // end of data buffer */
/*     uint32_t  mCapacity;    // maximum number of items in the buffer */
/*     uint32_t  mCount;       // number of items in the queue */
/*     uint32_t* mpHead;       // pointer to head */
/*     uint32_t* mpTail;       // pointer to tail */
/* }; */
/* */
/* */
LIB_RESULT ResMgr_Queue_Initialize(struct ResMgr_Queue* const cpThis,
                                   void* const cpBuffer,
                                   uint32_t const cBufferSizeInBytes,
                                   uint32_t const cCapacity,
                                   uint32_t* const cpReturnedSizeInBytes)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      cpReturnedSizeInBytes != 0 &&
      cCapacity > 0)
   {
      uint32_t const cNeededSizeInBytes = cCapacity * sizeof(cpThis->mpHead[0]);

      *cpReturnedSizeInBytes = cNeededSizeInBytes;

      libResult = LIB_SUCCESS;

      if(cpBuffer != 0)
      {
         if(cBufferSizeInBytes >= cNeededSizeInBytes)
         {
            cpThis->mpBuffer    = (uint32_t*)cpBuffer;
            cpThis->mpBufferEnd = cpThis->mpBuffer + cCapacity;
            cpThis->mCapacity   = cCapacity;
            cpThis->mCount      = 0;
            cpThis->mpHead      = cpThis->mpBuffer;
            cpThis->mpTail      = cpThis->mpBuffer;

            libResult = LIB_SUCCESS;
         }
         else
         {
            libResult = LIB_FAILURE;
         }
      }
   }

   return libResult;
}



LIB_RESULT ResMgr_Queue_PushBack(struct ResMgr_Queue* const cpThis,
                                 uint32_t const cItem)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      cpThis->mCount < cpThis->mCapacity)
   {
      *(cpThis->mpHead) = cItem;
      ++(cpThis->mpHead);

      if(cpThis->mpHead == cpThis->mpBufferEnd)    /* Could do some fancy operator& stuff here ? */
      {
         cpThis->mpHead = cpThis->mpBuffer;
      }
      ++(cpThis->mCount);

      libResult = LIB_SUCCESS;
   }

   return libResult;
}



LIB_RESULT ResMgr_Queue_PeekFront(struct ResMgr_Queue* const cpThis,
                                  uint32_t* const cpItem)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      cpItem != 0 &&
      cpThis->mCount > 0)
   {
      *cpItem = *(cpThis->mpTail);

      libResult = LIB_SUCCESS;
   }

   return libResult;
}



LIB_RESULT ResMgr_Queue_PopFront(struct ResMgr_Queue* const cpThis,
                                 uint32_t* const cpItem)
{
   LIB_RESULT libResult = LIB_FAILURE;

   if(cpThis != 0 &&
      cpItem != 0 &&
      cpThis->mCount > 0 &&
      cpThis->mCount <= cpThis->mCapacity)
   {
      *cpItem = *(cpThis->mpTail);
      *(cpThis->mpTail) = ~(0U);
      ++(cpThis->mpTail);

      if(cpThis->mpTail == cpThis->mpBufferEnd) /* Could do some fancy operator& stuff here ? */
      {
         cpThis->mpTail = cpThis->mpBuffer;
      }
      --(cpThis->mCount);

      libResult = LIB_SUCCESS;
   }

   return libResult;
}
