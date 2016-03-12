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

/* Information for doxygen */
/**
 *  \file   OAL_Task.hpp
 *  \brief  function declarations for OAL Task
 *
 */

#ifndef PLATFORM_OAL_TASK_HPP
#define PLATFORM_OAL_TASK_HPP

/***************************************************************************/
/* Include files. */
#include <global_build_options.h>
#include <oal.h>
#include <global_errors.h>
#include <global_types.h>
#include <stdint.h>


//**************************************************************************/
// Literals & definitions
const uint32_t gcOalTaskNameMaximumSizeInChar = 32;


//**************************************************************************/
// Class declaration.

/**
*  \file OAL_Task.hpp
*  \addtogroup OAL_Task OAL Task
*  @{ 
*  \brief This class encapsulates task creation and control functions.
*  \details
*   This class shall not be instantiated since it as a pure virtual member function.
*   It is a parent class from which child classes are defined.
*  @}
*/

class OAL_Task  // Abstract Task Class
{
/**
*  \addtogroup OAL_Task OAL Task
*  @{
*/
public: 
   /***************************************************************************/
   /**
    * \details
    * This function initializes the data members of the object
    *
    **************************************************************************/
   OAL_Task();



   /***************************************************************************/
   /**
    * \details
    * This function frees any outstanding resources in the objects possession.
    * 
    **************************************************************************/
   virtual ~OAL_Task();



   /***************************************************************************/
   /**
    * \details
    * This function creates and activates a new task.
    * It is equivalent to calling "Init" and "Activate".
    * 
    *
    * \param  cStackSizeInBytes - [in] Size in bytes of the tasks stack
    * \param  cTaskPriority     - [in] Specifies a priority value between 0 and 255.
    *                             The lower the numeric value, the higher the tasks priority.
    * \param  cTaskName         - [in] Pointer to a 31 character name for the task.
    *                             This name is shared by the task and its default message queue.
    *                             For name registration to succeed this name must be unique.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    *    - #OAL_ERR_LOG_EINVALIDPARAM
    **************************************************************************/
   LIB_RESULT Spawn(const uint32_t cStackSizeInBytes,
                    const uint32_t cTaskPriority,
                    const char   cTaskName[]);




   /***************************************************************************/
   /**
    * \details
    * This function initializes the stack and control block; but the task will not
    * be scheduled to run on the CPU.
    * 
    *
    * \param  cStackSizeInBytes - [in] Size in bytes of the tasks stack
    * \param  cTaskPriority     - [in] Specifies a priority value between 0 and 255.
    *                             The lower the numeric value, the higher the tasks priority.
    * \param  cTaskName         - [in] Pointer to a 31 character name for the task.
    *                             This name is shared by the task and its default message queue.
    *                             For name registration to succeed this name must be unique.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    *    - #OAL_ERR_LOG_EINVALIDPARAM
    **************************************************************************/
   LIB_RESULT Init(const uint32_t cStackSizeInBytes,
                   const uint32_t cTaskPriority,
                   const char   cTaskName[]);



   /***************************************************************************/
   /**
    * \details
    * This function activates a task created with "Init".
    * Activation schedules the task to run on the CPU.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT Activate();



   /***************************************************************************/
   /**
    * \details
    * This function causes the task to cease to exist; the stack and control block
    * resources are freed. If the task is safe from deletion, This function will block
    * until the task is made unsafe.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT Delete();



   /***************************************************************************/
   /**
    * \details
    * This function suspends the task.
    * The task is suspended regardless of its current state.
    * The way to resume the task it to use "Resume".
    * This is a dangerous function since it may lead to deadlocks; it should only
    * be used to assist in debugging.
    *
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT Suspend();



   /***************************************************************************/
   /**
    * \details
    * This function resumes the task from its suspended state.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT Resume();

   /***************************************************************************/
   /**
   * \details
   * This function waits for the thread to finish.
   *
   * \return
   *    - #LIB_SUCCESS
   *    - #LIB_FAILURE
   **************************************************************************/
   LIB_RESULT Join();



   /***************************************************************************/
   /**
    * \details
    * This function reinitializes a finished task reusing the values passed during the
    * last call to "Init" or "Spawn"
    *
    * The function "Activate" shall need to be called for the reset task to start
    * running.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT Reset();



   /***************************************************************************/
   /**
    * \details
    * This function changes the task priority.
    * 
    *
    * \param  cPriority - [in] Specifies a priority value between 0 and 255.
    *                     The lower the numeric value, the higher the tasks priority.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    *    - #OAL_ERR_LOG_EINVALIDPARAM
    **************************************************************************/
   LIB_RESULT PrioritySet(const uint32_t cPriority);



   /***************************************************************************/
   /**
    * \details
    * This function returns the task priority.
    * The current priority is copied to the variable "rReturnedPriority".
    * 
    *
    * \param  rReturnedPriority - [out] Current task priority.
    *                             This value is only valid if result is LIB_SUCCESS.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT PriorityGet(uint32_t& rReturnedPriority);



   /***************************************************************************/
   /**
    * \details
    * This function returns the default message queue id of this task.
    * The id is copied to the variable "rReturnedMessageQueueId".
    * The message queue gets created during task activation.
    * 
    *
    * \param  rReturnedMessageQueueId - [out] Default message queue id.
    *                                   This value is only valid if result is LIB_SUCCESS.
    *               
    *
    * \return 
    *    - #LIB_SUCCESS
    *    - #LIB_FAILURE
    **************************************************************************/
   LIB_RESULT MessageQueueGet(uint32_t& rReturnedMessageQueueId);
/**
 * @}
*/
private:
   virtual void TaskOpen(){};
   virtual void TaskService() = 0; // Pure Virtual hence you CANNOT instantiate this class
   virtual void TaskClose(){};


private:
   uint32_t      mMessageQueueId;
   OAL_TCB       mTaskControlBlock;
   uint32_t      mStackSizeInBytes;
   uint32_t      mPriority;   // Lower the value; higher the priority
   char          mName[gcOalTaskNameMaximumSizeInChar];
   OAL_SEMAPHORE mSemaphoreThreadSafety;
   bool          mIsSemaphoreThreadSafetyCreated;
   bool          mIsTaskInitialized;
   bool          mIsTaskActivated;
   bool          mIsTaskSuspended;
   bool          mIsTaskFinished;
   
   //TODO: was void instead of void*...
   static void* TaskEntryRoutine(void* pVoid);

private:
   OAL_Task( const OAL_Task& );            // Do not implement
   OAL_Task& operator=( const OAL_Task& ); // Do not implement
}; // End of OAL_Task declaration.


#endif // PLATFORM_OAL_TASK_HPP
