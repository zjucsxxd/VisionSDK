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
 *  \file   OAL_Exception.h
 *  \brief  OAL exception handling
 *
 *  OAL exception handling
 */

/// \addtogroup OAL_Exception OAL Exception
/// @{
/// \brief Exception handling API
///  \details
/// This file contains the functions and macros for exception handling.
/// An exception is handled (resolved) by saving the current state of execution in 
/// a predefined place and switching the execution to a specific function known as 
/// an exception handler. Depending on the situation, the handler may later resume 
/// the execution at the original location using the saved information.  
///
/// Exception testing is required to prevent fatal errors, where normal program execution 
/// is halted or system is in undefined state (memory corrupted, some variables out of range, etc.). 
/// Examples of fatal errors are divide-by-zero, null pointer addressing, 
/// failed dynamic memory allocation, etc. 


#ifndef OAL_EXCEPTION_LOGGER__H
#define OAL_EXCEPTION_LOGGER__H
 
/* Include files. */

#include <Debug.h>
#include <stdlib.h>

/* I wish i could just include "debug.h" without having to resolve all 
     other compiler errors the appear.... */
#ifdef __cplusplus
extern "C" 
{
#endif

#define EXCEPTION_CHECK_PRE_POST_CONDITIONS     // Move to global build options ? 

// --------------------------------------------------------

#ifdef EXCEPTION_CHECK_PRE_POST_CONDITIONS
////////////////////////////////////////////////////////////////////////
/// \details
///
///  This macro is used to throw an exception.
///
/// \param  expr - [in] Expression to be evaluated (if false then apply assertion)
///
////////////////////////////////////////////////////////////////////////
#define LIB_ASSERT(expr)                               \
   if(!(expr))                                         \
   {                                                   \
      DEBUG_printf( "\n%s \n%s%s \n%s%d\n",            \
         "Assertion failed !!!",                       \
         "in file ", __FILE__,                         \
         "at line ", __LINE__);                        \
      exit(1);                                         \
   }
#else
////////////////////////////////////////////////////////////////////////
/// \details
///
///  This macro is used to throw an exception.
///
/// \param  expr - [in] Expression to be evaluated (if false then apply assertion)
///
////////////////////////////////////////////////////////////////////////
#define LIB_ASSERT(expr)  
#endif  

//void DEBUG_printf (const char *f, ...);

/// Exception cause enum.
typedef enum
{
   EXCEPTION_NULL_POINTER,             ///< trying to use null pointer
   EXCEPTION_MEMORY_NOT_AVAILABLE,     ///< failed to allocate memory
   EXCEPTION_OVERFLOW,                 ///< variable overflow
   EXCEPTION_UNDERFLOW,                ///< variable underflow
   EXCEPTION_OUT_OF_RANGE,             ///< varibale/pointer out of range
   EXCEPTION_DIVIDE_BY_ZERO,           ///< trying to divide by 0        
   EXCEPTION_RESOURCE_NOT_AVAILABLE,   ///< required resource can not be obtained
   EXCEPTION_GENERIC,                  ///< generic problem, no details
   EXCEPTION_NONE                      ///< no exception 
} EXCEPTION_CAUSE;

/// Exception category (type) enum.
typedef enum
{
   EXCEPTION_RESUMABLE,                ///< exception is not fatal, program will resume
   EXCEPTION_FATAL_NON_RESUMABLE       ///< fatal exception, program can not be resumed, will go into halt
} EXCEPTION_CATEGORY;

////////////////////////////////////////////////////////////////////////
/// \details
/// 
/// This macro is used to throw an exception.
///
/// \param  descr     - [in] Exception cause described in  #EXCEPTION_CAUSE structure
/// \param  type      - [in] Exception category (type) described in #EXCEPTION_CATEGORY structure
///
////////////////////////////////////////////////////////////////////////
#define THROW_EXCEPTION(descr, type) throw_exception(descr, type, __FILE__, __LINE__)

////////////////////////////////////////////////////////////////////////
/// \details
///
/// This function is used to throw an exception.
///
/// \param  descr     - [in] Exception cause described in  #EXCEPTION_CAUSE structure
/// \param  type      - [in] Exception category (type) described in #EXCEPTION_CATEGORY structure
/// \param  file      - [in] Pointer to the file name where exception occurred
/// \param  line      - [in] Line number in the file where exception occurred
///
////////////////////////////////////////////////////////////////////////
void throw_exception(EXCEPTION_CAUSE descr, 
                     EXCEPTION_CATEGORY type,
                     const char *file, 
                     unsigned int line);

////////////////////////////////////////////////////////////////////////
/// \details
///
/// This function is used to clear an exception.
///
///
////////////////////////////////////////////////////////////////////////
void clear_exception();

////////////////////////////////////////////////////////////////////////
/// \details
///
/// This function is used to check if some exception has been thrown.
///
/// \return 
///    - #EXCEPTION_CAUSE  cause of exception
///
////////////////////////////////////////////////////////////////////////
EXCEPTION_CAUSE check_exception(); 

// end of \defgroup OAL_Exception
/// @}

//
typedef struct
{
   unsigned int returnAddress; 
   unsigned int svc_r0;        
   unsigned int svc_r1;        
   unsigned int svc_r2;        
   unsigned int svc_r3;        
   unsigned int svc_r4;        
   unsigned int svc_r5;        
   unsigned int svc_r6;        
   unsigned int svc_r7;        
   unsigned int svc_r8;        
   unsigned int svc_r9;        
   unsigned int svc_r10;        
   unsigned int svc_r11;        
   unsigned int svc_r12;        
   unsigned int svc_sp;         
   unsigned int svc_lr;         
   unsigned int svc_spsr;       
   unsigned int svc_pc;         
   unsigned int sys_sp;         
   unsigned int sys_lr;         
   unsigned int irq_sp;         
   unsigned int irq_lr;         
   unsigned int irq_spsr;       
   unsigned int abt_sp;         
   unsigned int abt_lr;         
   unsigned int abt_spsr;       
   unsigned int udf_sp;         
   unsigned int udf_lr;         
   unsigned int udf_spsr;       
   unsigned int fiq_r8;         
   unsigned int fiq_r9;         
   unsigned int fiq_r10;        
   unsigned int fiq_r11;        
   unsigned int fiq_r12;        
   unsigned int fiq_sp;         
   unsigned int fiq_lr;         
   unsigned int fiq_spsr;       
   unsigned int cpsr;           
   unsigned int p15_far;        
   unsigned int p15_ifsr;       
   unsigned int p15_dfsr;      
} OAL_ExceptionRegisterDump;


void OAL_ExceptionLogger(
   int                        ExceptionType, 
   OAL_ExceptionRegisterDump *pRegisters, 
   unsigned int              *pStack
);


#ifdef __cplusplus
}
#endif


#endif /* OAL_EXCEPTION_LOGGER__H */

