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
 *  \file   Oal.h
 *  \brief  Interface definition for the OAL (OS abstraction) library.
 *
 *  OAL provides an abstraction of standard OS interface functions used within
 *  MMP the system.
 */

#ifndef _OAL_H_
#define _OAL_H_

#include <stdint.h>

#include "global_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

void CleanAndInvalidateDCache(void *pointer, int size);
void CleanAndInvalidateDCacheByAddress(char *pBufferStart, char *pBufferEnd);
void InvalidateDCacheByAddress(char *pBufferStart, char *pBufferEnd);


// The tick period.
#define OAL_MS_PER_TICK    10

#define OAL_TICK_MUSEC     ( OAL_MS_PER_TICK * 1000 ) // For backward compatibility
#define OAL_MUSEC_PER_TICK ( OAL_MS_PER_TICK * 1000 )

//OAL Wait time definition
#define OAL_WAITFOREVER    0xFFFFFFFF
#define OAL_ONESECOND      (100 * OAL_TICK_MUSEC)

// OAL Semaphore types
typedef enum
{
  OAL_SEMAPHORE_COUNTING,
  OAL_SEMAPHORE_MUTEX,
  OAL_SEMAPHORE_BINARY,
  OAL_SEMAPHORE_INVALID
} OAL_SEMAPHORE_TYPE;

// This macro can be used to eliminate the 'unused parameter' warning
// emitted by the ARM compilers
#define OAL_RESERVED_PARAM(x)   (x = x)

typedef void* OAL_TCB; ///< opaque value returned to the task creator to be used when referring to a task

////////////////////////////////////////////////////////////////////////
//
// NOTE:
//      1. Parameters marked [out] in the API descriptions are pointers.
//         The value referenced by these pointers may be modified inside
//         the OAL code.
//      2. Tokens starting with \ or @ in the comments are used for
//         formatting the API documentation.
//
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \file Oal.h
/// \addtogroup OAL_Memory OAL Memory
/// @{
///
/// \name Memory functions
///
/// This API allows dynamically allocating a block of memory described by a
/// pointer whose address component points to a virtual address interpreted
/// by the MMU. MMU configures various regions as cache-able,
/// non-cacheable, etc. and handles the mapping of this virtual address
/// to its physical location and other properties associated with the
/// caching mechanisms that are available.
///
/// Application code running on the ARM should not care about the
/// virtualness of any pointers and considers that property transparent to
/// normal operation. There are certain low level operations that can
/// optimized by accessing memory in different way. MMU regions allow the
/// same physical memory location to be mapped with different
/// properties. It is possible using the #OAL_MemoryReturnAddress() API to
/// retrieve an address to have the appropriate properties that are handy
/// for the current use case. If the subsequent are going to be executed by
/// the hardware, one of the <I>Cache Control APIs</I> (e.g. #OAL_MemoryFlush())
/// can be used to make sure that the cache coherency is maintained.
///
/// One example is when writing to the registers of a device; we don't want
/// to use a cacheable virtual pointer because data won't be written to the
/// device. In this case using the non-cacheable virtual pointer is the only
/// way.
///
/// Additionally, for devices that are able to communicate with each or
/// read/write to memory on their own, the only possible value that they can
/// be programmed with is the physical location of that memory. It is
/// possible to retrieve the physical address associate with a virtual
/// pointer to configure the parameters of a device. Physical addresses
/// should only be used in such cases.
///
/// Mandatory Function Call Ordering Sequence: for allocations<br>
/// <ol><li>#OAL_MemoryAlloc
/// </li><li>manipulate data
/// </li><li>optionally: #OAL_MemoryFlushAndInvalidate
/// </li><li>optionally: #OAL_MemoryReturnAddress() [ACCESS_PHY]
/// </li><li>optionally: configure the DMA with the returned address 
///                      and wait for transfer/copy complete
/// </li><li>#OAL_MemoryFree
/// </li></ol>
///
////////////////////////////////////////////////////////////////////////
/// @{

// 0x000000FF : Mask for Top level flags.
// 0x0000FF00 : Mask for Alignment flags.
// 0x00FF0000 : Mask for Byte alignment value.
// 0xFF000000 : Not used.
#define ALIGN2_CACHELINE 0x00000100         ///< Memory is aligned on a cache line
#define ALIGN2_PAGE      0x00000200         ///< Memory is aligned on a page
#define BYTE_N           0x00000400
#define ALIGN2_BYTE(N)  (BYTE_N | (N << 16))///< Memory is aligned on an N-byte boundary

#define OAL_MEMORY_FLAG_CONTIGUOUS     0x01 ///< Memory block is physically contiguous
#define OAL_MEMORY_FLAG_NONSWAPABLE    0x02 ///< Memory allocated will never be swapped
#define OAL_MEMORY_FLAG_ZERO           0x04 ///< Memory is initialized with value zero
#define OAL_MEMORY_FLAG_ALIGN(ALIGN2) (0x08 | (ALIGN2)) ///< Memory is aligned as specified
#define OAL_MEMORY_FLAG_CONTIGUOUS_CMA 0x10 ///< Memory block is physically contiguous in DDR memory

// hack for Linux : how to merge?
// #define OAL_MEMORY_FLAG_PREALLOC_IN_BUF	0x10
// #define OAL_MEMORY_FLAG_PREALLOC_OUT_BUF	0x20
// #define OAL_MEMORY_FLAG_PREALLOC_RGB_BUF	0x40

/// Specifies the properties of allocated memory.
/// 
/// #OAL_MEMORY_FLAG Options:
/// - #OAL_MEMORY_FLAG_CONTIGUOUS
/// - #OAL_MEMORY_FLAG_NONSWAPABLE
/// - #OAL_MEMORY_FLAG_ZERO
/// - #OAL_MEMORY_FLAG_ALIGN()
///
/// #OAL_MEMORY_FLAG_ALIGN() Options:
/// - #ALIGN2_CACHELINE : 32 byte alignment on ARM Nucleus
/// - #ALIGN2_PAGE      :  4 KB   alignment on ARM Nucleus
/// - #ALIGN2_BYTE()    : as specified
/// 
/// Usage Examples:
/// - Note that multiple OAL_MEMORY_FLAG options can be enabled at the same time 
///   by listing them with the '|' (or) operator.
/// - #OAL_MemoryAllocFlag(size, #OAL_MEMORY_FLAG_ZERO); \n
/// Memory is allocated and then zero initialized. \n
/// - #OAL_MemoryAllocFlag(size, #OAL_MEMORY_FLAG_CONTIGUOUS | #ALIGN2_CACHELINE); \n
/// Memory is allocated as a contiguous block aligned to the cache line. 
/// This would be ideal when memory is manipulated by both the ARM and the HW. 
/// It would allow for proper cache manipulation. \n
/// - #OAL_MemoryAllocFlag(size, #ALIGN2_BYTE(8)); \n
/// In this case, the starting address is aligned to an address multiple of 8-bytes. 
/// It is guaranteed that the last three digits in Hex representation is zero. 
/// The parameter passed in for #ALIGN2_BYTE() has to be a power of 2. Maximum value
/// for this parameter is 32768.
typedef uint32_t OAL_MEMORY_FLAG;

/*================================================*/
/* Mapped registers base addresses and sizes ZYNQ */
#ifdef __ZC702
  #define OAL_DDR_PHYSICAL_POOL_BASE       	0x80000000
/*================================================*/
/* Mapped registers base addresses and sizes S32V234 Customer EVB */
#else
  #define OAL_DDR_PHYSICAL_POOL_BASE       	0x80000000
#endif

#define OAL_DDR_PHYSICAL_POOL_SIZE 0xF000000
#define OAL_DDR_RESOURCE_NAME 	   "oal_memory"
#ifdef __S32V234
#define OAL_IODEVICE_NAME "OALIODevice"
#define OAL_IODEVICE_GET_PHYSICAL 1
#endif
/////////////////////////////////////////////////////////////////////////
///
/// Initializes userspace version of contiguous memory allocator.
///
/// \return 
///    - On Success: LIB_SUCCESS
///    - On Failure: LIB_FAILURE
/////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_MemoryAllocInit(void);
/////////////////////////////////////////////////////////////////////////
///
/// Allocate a block of memory that meets certain criteria. This is a variation
/// on OAL_MemoryAlloc(). Memory will be allocated from
/// the appropriate heap while satisfying all the properties of flags. Memory
/// allocation of size zero will allocate a block of size and return 
/// a valid pointer.
///
/// \param size    - [in] Amount of memory to allocate in bytes
/// \param flags   - [in] Memory flags
///
/// \return 
///    - On Success: The Start address of the memory block
///    - On Failure: NULL
/////////////////////////////////////////////////////////////////////////
void *OAL_MemoryAllocFlag(uint32_t size, OAL_MEMORY_FLAG flags);

/////////////////////////////////////////////////////////////////////////
///
/// Resets kernel space allocator.
///
/////////////////////////////////////////////////////////////////////////
void OAL_MemoryAllocReset(void);


/////////////////////////////////////////////////////////////////////////
///
/// Allocate a block of memory. Memory allocation of size zero will 
/// allocate a block of size and return a valid pointer.
///
/// \param size - [in] The amount of memory to allocate in bytes
///
/// \return 
///    - On Success: The Start address of the memory block
///    - On Failure: NULL
/////////////////////////////////////////////////////////////////////////
void* OAL_MemoryAlloc(uint32_t size);


/////////////////////////////////////////////////////////////////////////
///
/// Allocate a block of memory and set the memory contents to zero.
///
/// \param size - [in] The amount of memory to allocate in bytes
///
/// \return 
///    - On Success: The Start address of the memory block
///    - On Failure: NULL
/////////////////////////////////////////////////////////////////////////
/*inline void* OAL_MemoryAllocNull(uint32_t size)
{
   void *p = 0;
   p = OAL_MemoryAllocFlag(size, OAL_MEMORY_FLAG_CONTIGUOUS | OAL_MEMORY_FLAG_ZERO);
   return p;
}*/

/// Specifies the type of access to allocated memory.
typedef uint32_t OAL_MEMORY_ACCESS;

////////////////////////////////////////////////////////////////////////
/// 
/// After the memory is allocated, that memory can be accessed in various
/// ways. Depending on how the user is manipulating the data in the memory
/// space, at certain points in time different accesses may be required. 
/// Use #OAL_MemoryReturnAddress() to get the address that is coupled with 
/// the requested access type. 
///
////////////////////////////////////////////////////////////////////////
enum
{
   ACCESS_PHY,    ///< Physical access
   ACCESS_CH_WB,  ///< Cached access with Writeback policy
   ACCESS_CH_WT,  ///< Cached access with Writethrough policy
   ACCESS_NCH_B,  ///< Non-Cached Bufferable access
   ACCESS_NCH_NB  ///< Non-Cached Non-Bufferable Access
};

////////////////////////////////////////////////////////////////////////
///
/// \details
/// Takes the given memory pointer and returns the pointer
/// that allows proper access as identified in the access parameter
///
/// The value of pBuffer passed has to be the value returned from one 
/// of the #OAL_MemoryAlloc functions.
/// 
/// - #ACCESS_PHY   : Returns the physical address of memory. Accessing this via
/// the CPU will fail.
/// - otherwise     : Takes the pBuffer as physical address and returns its 
/// virtual mapping.
/// - #ACCESS_CH_WB : [Disabled] Returns the address that will be interpreted as cached with a 
/// write back policy. 
/// - #ACCESS_CH_WT : [Disabled] Returns the address that will be interpreted as cached with a 
/// write through policy. 
/// - #ACCESS_NCH_B : [Disabled] Returns the address that will be interpreted as non-cached 
/// but buffered. 
/// - #ACCESS_NCH_NB: [Disabled] Returns the address that will be interpreted as non-cached 
/// and not buffered. 
/// 
/// \param pBuffer - [in] Pointer to a memory buffer; it must be a pointer
///                returned by #OAL_MemoryAlloc() or variations. 
/// \param access  - [in] Access Type requested
///
/// \return
///        Address of buffer with appropriate access type
///
/// \warning User is responsible from appropriately handling 
/// coherency issues. This function is just going to generate an address. 
/// It will not attempt to resolve the coherency.
////////////////////////////////////////////////////////////////////////
void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access);


////////////////////////////////////////////////////////////////////////
/// 
/// Release the allocated memory and return it to memory manager.
///
/// \param pBuffer - [in] Start address of the allocated memory block; it must be a pointer
///                returned by #OAL_MemoryAlloc() or variations. 
////////////////////////////////////////////////////////////////////////
void OAL_MemoryFree(void *pBuffer);


//@}


/// \name Cache Control Functions
/// 
/// These functions operate on a memory region specified by the user. 
/// There are no restrictions on the pointer that may be passed. They
/// find if any part of the region specified by pAddr and size are 
/// currently held in the cache and operate only on those cache lines.
/// 
/// The pointer passed Must be returned by #OAL_MemoryAlloc() or
/// its variations.
/// 
/// Flush: If any region of this memory is currently held in
/// the CPU cache, those contents will be written back to 
/// physical memory. 
/// 
/// FlushAndInvalidate: On top of the flush operations, all the
/// cache lines will be marked invalid. This will require 
/// a subsequent read operation to fetch data from physical memory. 
///
/// Invalidate: Simply scratches out all the cache lines. 
/// Data kept in the cache is lost. Any subsequent read will fetch
/// the data from physical memory
///@{ 

///
/// \param pAddr   - [in] Start Address of the memory region to be flushed; it must
///                be returned by #OAL_MemoryAlloc() or its variations. 
/// \param size    - [in] Size of the memory region
///
void OAL_MemoryFlush                 (void *pAddr, uint32_t size);

///
/// \param pAddr   - [in] Start Address of the memory region to be flushed and
///                invalidated. It must be returned by #OAL_MemoryAlloc() or
///                its variations. 
/// \param size    - [in] Size of the memory region
///
void OAL_MemoryFlushAndInvalidate    (void *pAddr, uint32_t size);

///
/// \param pAddr   - [in] Start Address of the memory region to be invalidated;
///                it must be returned by #OAL_MemoryAlloc() or its
///                variations.  
/// \param size    - [in] Size of the memory region
///
void OAL_MemoryInvalidate            (void *pAddr, uint32_t size);

///
/// Invalidate the whole cache.
///
void OAL_MemoryFlushAndInvalidateAll (void);
//@}


////////////////////////////////////////////////////////////////////////
///
/// \name OAL Memory Pool Functions
///
/// OAL Memory Pool set of APIs provide a way of managing memory for 
/// objects of the same size. If the user has to deal with a number of 
/// objects of the same size, an ideal way would to create a pool of 
/// memory for these memory objects and use this pool to get the memory
/// for these objects. 
///
/// In this scheme, memory would be allocated from the system memory
/// manager once and managed independantly by the Memory Pool implementation.
/// The benefits of this approach would be reduced fragmentation and
/// quicker processing times for memory allocation. Fragmentation would be
/// reduced because memory is allocated once and freed only when the pool
/// is destroyed. All intermediate memory requests use the same memory
/// pointers that are preallocated. Processing time for an Allocation would
/// be deterministic because the memory need not search the whole memory
/// space for memory.  Searching the pool for memory is very quick.
/// 
/// Similar to OAL_MemoryAllocFlag(), user will be creating a pool of 
/// memory with certain properties. Afterwards, all memory regions 
/// allocated would be fixed size and have the same set of properties.
////////////////////////////////////////////////////////////////////////

/// @{

/// opaque handle for OAL Memory Pools
typedef struct memPool_s *OAL_MEM_POOL;


////////////////////////////////////////////////////////////////////////
/// Creates a pool for objects of size 'size'. Pool allocates memory 
/// for 'count' number of objects. The memory allocated for
/// these objects are specified using 'flags'. Neither 'size', nor 'count'
/// can be zero.
///
/// \param size    - [in] Size of each memory block in pool 
/// \param count   - [in] Number of memory blocks in pool 
/// \param flags   - [in] Memory flags
/// 
/// \return 
///    - On Success: a non-zero pool handle is returned
///    - On Failure: zero
////////////////////////////////////////////////////////////////////////
OAL_MEM_POOL OAL_MemoryPoolCreate (uint32_t size, 
                                   uint32_t count, 
                                   OAL_MEMORY_FLAG flags);
                                    
////////////////////////////////////////////////////////////////////////
/// Deletes the pool and returns the memory managed in this pool
/// back to the system. In case the memory for this pool is not completely
/// freed, delayed destroy will be in effect. Pool will exist until
/// all memory is returned to it and will be destroyed only then. During
/// this time, all memory allocation from this pool will fail. 
/// 
/// This is how the OAL Buffers worked and that functioality is kept. 
///
/// \param pool  - [in] Pool handle
/// 
/// \return 
/// \warning Delayed destroy is a potential concern in the system.
////////////////////////////////////////////////////////////////////////
void OAL_MemoryPoolDestroy (OAL_MEM_POOL pool);

////////////////////////////////////////////////////////////////////////
/// Requests memory from pool. No size and flags parameters are required
/// because those properties are fixed when the pool is created. 
///
/// \param pool  - [in] Pool handle
///
/// \return 
///    - On Success: The Start address of the memory block
///    - On Failure: NULL
////////////////////////////////////////////////////////////////////////
void* OAL_MemoryPoolAlloc (OAL_MEM_POOL pool);

////////////////////////////////////////////////////////////////////////
/// Returns the memory to the appropriate pool. Normally there would also
/// be a pool parameter to specify which pool to return the memory to. 
/// Because we allow passing buffers into other components in our system
/// and allow them to free it, and because that other components are not
/// aware of the pool that memory is coming from, it won't be possible 
/// for that component to specify the pool parameter. Pool parameter is
/// internally tracked to return the memory to its proper owner.
///
/// \param pMem - [in] Start address of the allocated memory block obtained from
///             the OAL_MemoryPoolAlloc() function.
/// 
////////////////////////////////////////////////////////////////////////
void OAL_MemoryPoolFree  (void *pMem);

////////////////////////////////////////////////////////////////////////
// endof group : OAL_MemoryPool
/// @}
////////////////////////////////////////////////////////////////////////


/// \name Referencing Counting Functions
/// 
/// This set of APIs can be used to share a buffer with other parties in
/// the system. It is important to highlight that the OAL_MemoryRC
/// structures is internally created and destroyed by these APIs and
/// therefore not owned by anyone in the system. Therefore no specific
/// deallocation should be called on this structure. It will be deallocated
/// when there is no active users on itself. This will also deallocate the
/// buffer contained within the structure. Deallocation mechanism assumes
/// that this buffer has been allocated the memory for this buffer has been
/// allocated using OAL_MemoryAllocate(). 
/// 
////////////////////////////////////////////////////////////////////////

/// @{

typedef struct memRefCounting_s *OAL_MemoryRC;

////////////////////////////////////////////////////////////////////////
/// 
/// Creates a structure that holds the memory and tracks its reference count. The
/// reference count is set to 1. 
///
/// \param pMem - [in] Pointer to a memory buffer; it must be a pointer
///                returned by #OAL_MemoryAlloc() or variations.
/// \return The newly created structure is returned.
///
////////////////////////////////////////////////////////////////////////
OAL_MemoryRC OAL_MemoryRCCreate(void *pMem);

////////////////////////////////////////////////////////////////////////
/// 
/// Decrements the reference count. 
/// If the reference count is down to zero as a result, releases the buffer
/// and the OAL_MemoryRC structure. If this happens, the structure is not
/// valid anymore.
///
/// \param pMemRC - [in] pointer to a reference Counting memory structure; 
///                 it must be a pointer returned by #OAL_MemoryAlloc() 
///                 or variations. 
/// \return Reference Count after completion of the call.
///
////////////////////////////////////////////////////////////////////////
int OAL_MemoryRCDecrement(OAL_MemoryRC pMemRC);


////////////////////////////////////////////////////////////////////////
/// 
/// Increments the reference count.
/// 
/// \param pMemRC - [in] pointer to a reference Counting memory structure
/// \return Reference Count after completion of the call.
/// 
////////////////////////////////////////////////////////////////////////
int  OAL_MemoryRCIncrement(OAL_MemoryRC pMemRC);

////////////////////////////////////////////////////////////////////////
/// 
/// Returns the reference count.
/// 
/// \param pMemRC - [in] pointer to a reference Counting memory structure
/// \return reference count.
/// 
////////////////////////////////////////////////////////////////////////
int  OAL_MemoryRCGetCount (OAL_MemoryRC pMemRC);

////////////////////////////////////////////////////////////////////////
///
/// Returns the buffer.
///
/// \param pMemRC - [in] pointer to a reference Counting memory structure
/// \return void pointer passed during call to OAL_MemoryRCCreate.
///
////////////////////////////////////////////////////////////////////////
void* OAL_MemoryRCGetBuffer(OAL_MemoryRC pMemRC);

////////////////////////////////////////////////////////////////////////
// endof group : OAL_MemoryRC
/// @}
////////////////////////////////////////////////////////////////////////


/// @}

////////////////////////////////////////////////////////////////////////
///
/// \addtogroup OAL_Semaphore OAL_Semaphore
///@{
/// \brief Critical region primitives
/// \details
/// Mandatory Function Call Ordering Sequence: in first task<br>
/// <ol><li>#OAL_SemaphoreCreate, always first
/// </li><li>#OAL_SemaphoreDelete, only when region needs no further protection
/// </li></ol>
///
/// Mandatory Function Call Ordering Sequence: in any task after first task item 1, before item 2<br>
/// <ol><li>#OAL_SemaphoreObtain, #OAL_SemaphoreTryObtain or #OAL_SemaphoreTimedWait
/// </li><li>if obtained, manipulate critical data
/// </li><li>if obtained, #OAL_SemaphoreRelease
/// </li></ol>
/// 
////////////////////////////////////////////////////////////////////////


/// Semaphore type
typedef struct tOalSemaphore* OAL_SEMAPHORE;   ///< an opaque pointer used to reference a created Semaphore

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Create an OS semaphore. If succeeds, the created Semaphore ID
/// will be subsequently referred to in later Semaphore calls.
///
/// Semaphores types are differentiated based on two attributes;
/// the legal values for the semaphore count and the resumption order
/// of suspended tasks.
///
/// Binary and mutex type semaphores are restricted to a count of 0 or 1.
/// Counting semaphores are allowed to have count values greater than 1.
/// The value of the count represents the number of times the semaphore can
/// be obtained without suspending the calling task. A task trying to obtain a
/// semaphore with a count of 0 will be suspended. Obtaining a semaphore will
/// decrement the count if it is greater than 0 and releasing increments the count.
///
/// Binary and counting type semaphores will resume tasks in the order in which
/// they tried to obtain the semaphore; a first in, first out order.
/// Mutex semaphores will resume first the higher priority tasks followed by the lower
/// priority tasks; within the same priority the order is first in, first out,(FIFO).
///
/// \param pSem - [out] Semaphore ID will be written to (*pSem)
/// \param pName - [in] String identifying new semaphore(name will be truncated to 7 characters)
/// \param type - [in] Semaphore type:
/// - OAL_SEMAPHORE_BINARY
/// - OAL_SEMAPHORE_COUNTING
/// - OAL_SEMAPHORE_MUTEX
/// \param count - [in] Initial count for counting semaphores
///
/// \return
/// - #LIB_SUCCESS
/// - #LIB_FAILURE
/// - #OAL_ERR_SEM_ENOMEM
/// - #OAL_ERR_SEM_EBADTYPE 
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreCreate(OAL_SEMAPHORE *pSem,
    const char *pName, OAL_SEMAPHORE_TYPE type, unsigned int count);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Wait on a semaphore until it is obtained.
///
/// \param sem - [in] Semaphore ID
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_SEM_EBADSEM
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreObtain(OAL_SEMAPHORE sem);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Try to obtain a semaphore. If the Semaphore is not available, the
/// function will return immediately with an error. If it is available
/// a SUCCESS return code will be returned.
///
/// \param sem - [in] Semaphore ID
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_SEM_ESEMLOCKED
///    - #OAL_ERR_SEM_EBADSEM
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreTryObtain(OAL_SEMAPHORE sem);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Try to obtain a semaphore until it times out. If the Semaphore is
/// not available, the calling task will be blocked until the Semaphore
/// becomes available or times out.
///
/// NOTE :  Timeout is expressed in microseconds but true timeout period
///         will be rounded up to the granularity of the OS timer which is 10ms.
///
/// \param sem - [in] Semaphore ID
/// \param time - [in] Timeout in microseconds
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_SEM_ETIMEOUT
///    - #OAL_ERR_SEM_EBADSEM
///    - #OAL_ERR_SEM_RESET
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreTimedWait(OAL_SEMAPHORE sem, unsigned int time);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Signal or release a semaphore assuming the passed Semaphore ID has
/// already been created.
///
/// \param sem - [in] Semaphore ID
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreRelease(OAL_SEMAPHORE sem);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Reset the semaphore. Tasks suspended on the semaphore will be
/// resumed with the appropriate error code.
///
/// \param sem - [in] Semaphore ID
/// \param count - [in] Initial count for the reset semaphore
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreReset(OAL_SEMAPHORE sem, unsigned int count);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Delete a semaphore assuming the Semaphore ID argument has been
/// already created.
///
/// \param sem - [in] Semaphore ID
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_SEM_EBADSEM
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SemaphoreDelete(OAL_SEMAPHORE sem);

// end of \addtogroup OAL_Semaphore OAL Semaphore
///@}

////////////////////////////////////////////////////////////////////////
/// \addtogroup OAL_Timer OAL Timer
/// @{
////////////////////////////////////////////////////////////////////////

typedef void *OAL_TIMER;                                    ///<Timer Section
typedef void (*OAL_TimerCallBackFunc)(unsigned int param);  ///<Timer Callback Function

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Enable or disable the already created timer based on the timer ID
/// provided.
///
/// \param timerId - [in] The timer ID
/// \param state   - [in] The timer state to be changed to (1=enabled, 0=disabled)
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_INVALID_TIMER_ID
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_ControlTimer(OAL_TIMER timerId, unsigned int state);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Create a software timer that allows the users to perform
/// timing task periodically. Note that the expiration call back will be
/// called within the OS context, and it is not supposed to be blocked.
/// Therefore, the user call back function must be brief and non-blocking,
/// or else the whole system will be in an abnormal state.
///
/// NOTE :  Timeout is expressed in microseconds but true period
///         will be rounded up to the granularity of the OS timer 
///         which is 10ms.
///
/// \param pTimerId          - [out] The timer ID returned if successfully created
/// \param name              - [in] The name of the timer to be created
/// \param userCallBack      - [in] The user callback when the timer expires
/// \param userCallBackParam - [in] The user callback parameter
/// \param initial_time      - [in] The initial timer expiration period in micro-second
/// \param reschedule_time   - [in] The next timer expiration periods in micro-second
/// \param startState        - [in] The timer state to on creation (1=enabled, 0=disabled)
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_INVALID_TIMER_ID
///    - #OAL_ERR_MEMORY_OUT_OF_MEMORY
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_CreateTimer(OAL_TIMER *pTimerId, const char *name,
                           OAL_TimerCallBackFunc userCallBack,
                           unsigned int userCallBackParam, unsigned int initial_time,
                           unsigned int reschedule_time, unsigned int startState);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Reset an already created software timer that allows the users to perform
/// timing task periodically.  Note that the expiration call back will be
/// called within the OS context, and it is not supposed to be blocked.
/// Therefore, the user call back function must be brief and non-blocking,
/// or else the whole system will be in an abnormal state.
///
/// NOTE :  Timeout is expressed in microseconds but true period
///         will be rounded up to the granularity of the OS timer
///         which is 10ms.
///
/// \param pTimerId          - [in] The timer ID
/// \param UserCallBack      - [in] The user callback when the timer expires
/// \param initial_time      - [in] The initial timer expiration period in micro-second
/// \param reschedule_time   - [in] The next timer expiration periods in micro-second
/// \param startState        - [in] The timer state to on creation (1=enabled, 0=disabled)
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_INVALID_TIMER_ID
///    - #OAL_ERR_MEMORY_OUT_OF_MEMORY
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_ResetTimer(OAL_TIMER *pTimerId,
                          OAL_TimerCallBackFunc UserCallBack,
                          unsigned int initial_time,
                          unsigned int reschedule_time,
                          unsigned int startState);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Delete the already created timer based on the specified timer ID.
///
/// \param timerId  - [in] The timer ID
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_INVALID_TIMER_ID
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_DeleteTimer(OAL_TIMER timerId);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Return the system timer tick count in millisecs.
///
/// \return
///    - Tick count in milliseconds
////////////////////////////////////////////////////////////////////////
unsigned int OAL_GetTickCountInMS(void);

// end of \addtogroup OAL_Timer OAL Timer
///@}

/// \addtogroup OAL_Task OAL Task
/// @{

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function suspends the calling task for the specified time 
/// in microseconds.
///
/// NOTE :  Sleep is expressed in microseconds but true period
///         will be rounded up to the granularity of the OS timer
///         which is 10ms.
///
/// \param time - [in] The sleep amount in microseconds
///
////////////////////////////////////////////////////////////////////////
void OAL_TaskSleep(unsigned int time);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function allows all other ready tasks of the same priority
/// a chance to execute before the calling task runs again.
///
////////////////////////////////////////////////////////////////////////
void OAL_TaskRelinquish(void);

// end of \addtogroup oal_task_api OAL Task
///@}


/// \addtogroup OAL_Semaphore OAL_Semaphore
/// @{

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// To temporarily disable the system interrupt.
/// Normally, this API is only used if you want to protect a critical
/// piece of codes very briefly.  For instance, call this where the
/// semaphore can not be used like in the HISR, the timer expiry.
///
////////////////////////////////////////////////////////////////////////
void OAL_InterruptLock(void);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// To re-enable the system interrupt.
/// Normally, this API is only used if you want to protect a critical
/// piece of codes very briefly.  For instance, call this where the
/// semaphore can not be used like in the HISR, the timer expiry.
///
////////////////////////////////////////////////////////////////////////
void OAL_InterruptFree(void);

// end of \addtogroup OAL_Semaphore OAL_Semaphore
///@}

////////////////////////////////////////////////////////////////////////
///
/// \addtogroup OAL_SISR OAL_SISR
///@{
/// \brief Define and manage an Interrupt Service Routine
/// \details
/// Peripheral devices signal the processor through an IRQ mechanism. When an IRQ is
/// enabled and a signal for that IRQ is received, the IRQ interrupt handler jumps to the
/// IRQ vector address and runs the installed Low-level ISR (LISR) to service the IRQ.
/// This is done at interrupt execution context where no OS functions are available and
/// all lower priority interrupts are not serviced until the current LISR exits.
///
/// For cases where the handling of the IRQ requires full OS execution context, a High-level
/// ISR (HISR) should also be defined. The LISR for the IRQ can then activate the HISR when
/// needed. The LISR would then exit the interrupt level so the OS scheduling could resume.
/// The HISR would then start running as a short-lived run-to-completion highest priority task that
/// is subject to future interrupt level preemptions.
/// 
/// Mandatory Function Call Ordering Sequence: Low Level ISR<br>
/// <ol><li>#OAL_SISRVecConnect, always first. installs LISR function in IRQ vector table
/// </li><li>#OAL_SISREnableIrq enables IRQ table entry to be called by IRQ interrupt handler
/// </li><li>optionally: #OAL_SISRActivate which requires HISR definition, see below
/// </li><li>#OAL_SISRDisableIrq, always last disable an IRQ table entry from being called by IRQ handler
/// </li></ol>
///
/// Mandatory Function Call Ordering Sequence: High Level ISR<br>
/// <ol><li>#OAL_SISRInit, always first. Call sometime before activating by LISR
/// </li><li>#OAL_SISRActivate called from running LISR
/// </li><li>entry point of HISR runs when OS resumes and does normal \ref OAL_Task "task" activities, usually
/// handling data referenced by LISR as quickly as possible before next LISR fires
/// </li><li>entry point of HISR exits
/// </li><li>#OAL_SISRDelete, always last. Done anytime after Init
/// </li></ol>
////////////////////////////////////////////////////////////////////////

/// SISR identification
typedef void* OAL_SISR_ID; ///< an opaque type used when referring to SISR created with #OAL_SISRInit

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Connect the "low-level" ISR to an interrupt vector for the given vector number.
///
/// \param VecNumber - [in] Vector number
/// \param pLisrFunction - [in] "Low-level" ISR entry point
///
////////////////////////////////////////////////////////////////////////
void OAL_SISRVecConnect(int VecNumber,
                        void (*pLisrFunction)(int));

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Initialize an SISR.  The entry point function provided here
/// will be run as a "high-level" ISR whenever the "low-level" ISR
/// activates it.
///
/// \param pSISREntry - [in] Pointer to ISR entry point function
/// \param StackSize  - [in] Stack size required by the high-level ISR
/// \param priority   - [in] High-level ISR priority
/// \param SisrName   - [in] Name string
/// \param SisrId     - [out] SISR ID
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_SISR_ENOMEM
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SISRInit(void (*pSISREntry)(void), unsigned int StackSize,
    unsigned int priority, const char* SisrName, OAL_SISR_ID* SisrId);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Enable the system low level ISR associated with the IRQ number.
///
/// \param irq - [in] The irq number matching with the hardware interface.
///
////////////////////////////////////////////////////////////////////////
void OAL_SISREnableIrq(unsigned int irq);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Connect/activate a HISR C function .
///
/// \param sisr - [in] SISR ID
///
////////////////////////////////////////////////////////////////////////
void OAL_SISRActivate(OAL_SISR_ID sisr);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Delete an already created SISR.
///
/// \param SisrId  - [in] SISR ID
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SISRDelete(OAL_SISR_ID SisrId);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Disable the system low level ISR associated with the IRQ number.
///
/// \param irq - [in] The irq number matching with the hardware interface
///
////////////////////////////////////////////////////////////////////////
void OAL_SISRDisableIrq(unsigned int irq);

typedef enum {IRQ_LEVEL, IRQ_EDGE} IRQ_MODE;
// end of \addtogroup OAL_SISR
///@}
LIB_RESULT OAL_IRQInit(void (*pServiceRoutineFunc)(void), unsigned int irq, unsigned int priority, IRQ_MODE mode);
void OAL_IRQEnable(unsigned int irq);
LIB_RESULT OAL_IRQDelete(unsigned int irq);
void OAL_IRQDisable(unsigned int irq);

#ifdef __cplusplus
}
#endif

#endif // File Guard
