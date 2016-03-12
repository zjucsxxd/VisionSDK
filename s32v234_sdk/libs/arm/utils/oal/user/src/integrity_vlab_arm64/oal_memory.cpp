/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file OAL_Memory.cpp
* \brief OAL memory regions management
* \author Tomas Babinec
* \author Rostislav Hulik, Igor Aleksandrowicz
* \version 0.9
* \date 25-02-2014
* \note Based on CGV's contiguous memory region allocation for Integrity OS.
****************************************************************************/

#include <oal.h>
#include "oal_memory_internals.h"
#include <global_types.h>
#include <INTEGRITY.h>
#include <vector>
#include <semaphore.h>
#include <pthread.h>

/*****************************************************************************
* types
*****************************************************************************/

typedef struct MemoryHeader OAL_MemHeader;

/****************************************************************************/
/** OAL_MemoryHeader structure defining OAL allocated memory region header.
 *
 * Simplifies access to memory region metadata. Requires additional space to be
 * allocated for the region -> above the requested size.
 ****************************************************************************/
struct MemoryHeader
{
  unsigned int     specialTag;        ///< indicates this is an OAL_MemHeader struct
  unsigned int     bytesRequested;    ///< size requested
  unsigned int     bytesAllocated;    ///< actual #bytes allocated
  OAL_MEMORY_FLAG  memFlags;          ///< memory type requested
  void*            pVirtualBase;      ///< OS 'virtual' ptr to start of all allocated memory (including header and alignment padding)
  void*            pVirtualCached;    ///< OS 'virtual' ptr to start of user buffer (cached)
  void*            pVirtualNoncached; ///< OS 'virtual' ptr to start of user buffer (noncached)
  uint64_t     physAddr;          ///< physical address associated with start of user buffer (for HW use only)
  MemoryRegion     virtMemRegCached;    ///< cached virtual 'memory region' entity (mapped to 'physMemReg')
  MemoryRegion     virtMemRegNoncached; ///< noncached virtual 'memory region' entity (mapped to 'physMemReg')
  MemoryRegion     physMemReg;          ///< physical 'memory region' entity
}; // struct MemoryHeader

/****************************************************************************/
/** ContiguousMemoryBlock structure defines mapping of an OAL allocated memory
 *	region.
 *
 * Inteded to be managed automatically by CMBMapper class.
 ****************************************************************************/
struct ContiguousMemoryBlock
{
	// members
  OAL_MemHeader* mpHeaderPointer;
	void* mpBaseVirtualPointer;
	void* mpUserVirtualPointer;
	uint32_t mMappedCnt;
	MemoryRegion mVirtualMemReg;

	// methods
	ContiguousMemoryBlock():
		mpHeaderPointer(NULL),
		mpBaseVirtualPointer(NULL),
		mpUserVirtualPointer(NULL),
		mMappedCnt(0),
		mVirtualMemReg(0)
	{
	} // ContiguousMemoryBlock()

  void Invalidate()
  {
    mpUserVirtualPointer = NULL;
		mMappedCnt = 0;
  } // Invalidate()

  bool IsValid()
  {
    return mpUserVirtualPointer != NULL;
  } // IsValid()
}; // struct ContiguousMemoryBlock

/****************************************************************************/
/** CMBMapper class manages mapping of OAL alocated contiguous regions.
 *
 * Only regions allocated in different address-space are managed by the Mapper.
 * Otherwise, all relevant information is stored in the header.
 ****************************************************************************/
class CMBMapper
{
	// members
  std::vector<ContiguousMemoryBlock> mRegister; ///< vector of allocated blocks
  pthread_mutex_t mMutex;			///< mutex for thread-safe access

	/****************************************************************************/
  /** Looks for CMB record of the specified memory region in the CMB vector.
   *
   * \param aHandle handle of the requested physical region (physical address)
	 * \param arIdx if mapping exists (handle found), index of the CMB is returned
	 * here, otherwise set to index of an invalid CMB. If all CMBs valid, the arIdx
	 * is set to number of CMBs.
   *
   * \return LIB_SUCCESS if the region record has been found, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT FindByHandle(uint32_t aHandle, uint32_t &arIdx);

	/****************************************************************************/
  /** Looks for CMB record of the specified memory region in the CMB vector.
   *
   * \param apcVirtAddr pointer to virtual mapping of the requested physical
	 *				region
	 * \param arIdx if mapping exists (address found), index of the CMB is returned
	 * here, otherwise set to index of an invalid CMB. If all CMBs valid, the arIdx
	 * is set to the number of CMBs.
   *
   * \return LIB_SUCCESS if the region record has been found, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT FindByAddr(const void *apcVirtAddr, uint32_t &arIdx);
	
public:
  CMBMapper();

  /****************************************************************************/
  /** Creates mapping of the specified physical region in this address-space.
   *
	 *	First looks for an Resource manager record of this region. Than maps it.
	 *
   * \param aPhysMemHandle handle of the requested physical region (physical address)
	 * 
   * \return LIB_SUCCESS if all ok, LIB_FAILURE otherwise
   ****************************************************************************/
	void* Map(uint32_t aPhysMemHandle);

	/****************************************************************************/
  /** Adds already mapped region to the register.
   *
	 *	First looks for an Resource manager record of this region. Than maps it.
	 *
   * \param apcVirtAddr pointer to virtual mapping to be registered
	 * 
   * \return LIB_SUCCESS if all ok, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT Register(const void* apcVirtAddr);

  /****************************************************************************/
  /** Destroys mapping of the specified physical region in this address-space.
   *
	 *	First looks for an existing mapping of this region. Than unmaps it.
	 *
   * \param apcVirtAddr pointer to virtual mapping of the requested phisical region.
	 * 
   * \return LIB_SUCCESS if all ok, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT UnMap(const void *apcVirtAddr);

  /****************************************************************************/
  /** Destroys mapping of the specified physical region in this address-space.
   *
	 *	First looks for an existing mapping of this region. Than unmaps it.
	 *
   * \param aHandle handle to the physical memory region (physical address)
	 * 
   * \return LIB_SUCCESS if all ok, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT UnMap(uint32_t aHandle);

  /****************************************************************************/
  /** Removes mapping record from mapper.
   *
	 *	First looks for an existing mapping of this region. Than unregisters it.
	 *
   * \param apcVirtAddr pointer to virtual mapping of the region to be unregistered.
	 * 
   * \return LIB_SUCCESS if all ok, LIB_FAILURE otherwise
   ****************************************************************************/
	LIB_RESULT UnRegister(const void *apcVirtAddr);

  /****************************************************************************/
  /** Returns physical address coresponding to the specified virtual address.
	 *
   *	Works only for addresses acquired by Map method.
	 *	First looks for an existing mapping record for this region.
	 *
   * \param apcVirtAddr pointer representing virtual address to be translated to physical.
	 * 
   * \return physical address if all ok, 0 otherwise
   ****************************************************************************/
	uint32_t GetPhysicalAddress(const void *apcVirtAddr);

	/****************************************************************************/
  /** Returns virtual address coresponding to the specified physical address.
	 *
   *	Works only for addresses acquired by GetPhyscialAddress method.
	 *	First looks for an existing mapping record for this region.
	 *
   * \param aPhysMemHandle handle of the requested physical region (physical address)
	 * 
   * \return virtual address if all ok, NULL otherwise
   ****************************************************************************/
	void* GetVirtualAddress(uint32_t aPhysMemHandle);
	
  ~CMBMapper()
  {
    pthread_mutex_destroy(&mMutex);
  } // ~CMBMapper()
}; // class CMBMapper

/*****************************************************************************
* local macros
*****************************************************************************/

#define SIZE_TO_ALLOC(_s_, _a_)  ((_s_) + sizeof(OAL_MemHeader) + (_a_-1))
#define RET_USER_MEM_ADDR(_baseAddr_, _a_) (((uint64_t)(_baseAddr_) + sizeof(OAL_MemHeader) + (_a_-1)) & (~(_a_-1)))
#define RET_HEADER_PTR(_pUser_) (OAL_MemHeader*) ((uint64_t)(_pUser_) - sizeof(OAL_MemHeader))

/*****************************************************************************
* global variables
*****************************************************************************/
///< object describing the whole available contiguous memory arrea in DDR
static MemoryRegion gsPhysicalOalMemRegion = NULLMemoryRegion;
///< Integrity object managing allocation from the contiguous memory area
static MemoryRegionPool* gspUnmappedPhysMemRegPool = 0;
///< location of the DDR contiguous region in memory
static uint64_t      gsPhysOffset              = 0;

// mapper class instance (one for each address-space)
static CMBMapper gsCMBMapper;


/*****************************************************************************
* local functions
*****************************************************************************/

/****************************************************************************/
/** Counts non-zero bits in the value.
 *
 * \param aValue value to process.
 * 
 * \return number of non-zero bits in the aValue parameter.
 ****************************************************************************/
unsigned int NonZeroBitCnt(unsigned int aValue)
{
  unsigned int x = aValue;
  unsigned int n = 0;
  while (x != 0)
  {
    n = n + (x & 0x01);
    x = x >> 1;
  }

  return n;
} // unsigned int NonZeroBitCnt(unsigned int aValue)

////////////////////////////////////////////
//
// END: CMBMapper functionality
//
////////////////////////////////////////////

/****************************************************************************/
/** Simple contructor for the CMBMapper class
*****************************************************************************/

CMBMapper::CMBMapper()
{
	pthread_mutexattr_t attr;
	bool ok = true;
	ok = ok && (pthread_mutexattr_init(&attr) == 0);
	
	if (ok && pthread_mutex_init(&mMutex, &attr))
	{
		//TODO: how to handle the error?
	} // 
  (void)pthread_mutexattr_destroy(&attr);
} // CMBMapper::CMBMapper()


void* CMBMapper::Map(uint32_t aPhysMemHandle)
{
	MemoryRegion physMemReg, virtMemReg;
  Address virtBaseAddr = 0;
	Address physBaseAddr = 0, physLastAddr = 0;
  Value virtLength = 0;
  Error lError, lErrorMap;
	void* retUserVirtualPointer = NULL;

	// lock mapper until finished
	pthread_mutex_lock(&gsCMBMapper.mMutex);

	// check if not there already
	uint32_t idx = 0;

	if( gsCMBMapper.FindByHandle(aPhysMemHandle, idx) == LIB_FAILURE)
	{
		// block not mapped yet
		// generate name for the physical region 
		char physMemRegName[8+3];
		sprintf(physMemRegName,"OM%8x", (unsigned)aPhysMemHandle);
		// Request physical memory region
		lError = RequestResource((Object*)&physMemReg,physMemRegName,NULL);

		
		if (Success == lError)
		{
			// get base address of the physical memory region
			GetMemoryRegionAddresses(physMemReg, &physBaseAddr, &physLastAddr);
			// map physical region to virtual region and get its address
			lErrorMap = MapMemoryWithAttributes(__ghs_VirtualMemoryRegionPool, physMemReg, &virtMemReg, &virtBaseAddr, &virtLength, 0, MEMORY_READ|MEMORY_WRITE|MEMORY_VOLATILE );

			if (Success == lErrorMap)
			{
				if(gsCMBMapper.mRegister.size() == idx)
				{
					gsCMBMapper.mRegister.push_back(ContiguousMemoryBlock());
				} // if not present yet, create entry
				
				// get shortcut to CMB at index "idx"
				ContiguousMemoryBlock &block = gsCMBMapper.mRegister[idx];
				// fill the CMB
				// compute address of the header
				block.mpHeaderPointer =  (OAL_MemHeader*)(virtBaseAddr + aPhysMemHandle - physBaseAddr - sizeof(OAL_MemHeader));
				block.mpBaseVirtualPointer = (void*)virtBaseAddr;
				// compute address of the virtual user region
				block.mpUserVirtualPointer = (void*)(virtBaseAddr + aPhysMemHandle - physBaseAddr);

				// remember what to return
				retUserVirtualPointer =	block.mpUserVirtualPointer;
			} // if MapMemory succeeded
			else //at least one of the mappings failed; clean things up
			{
				if (Success == lErrorMap)
				{
					UnmapMemory(__ghs_VirtualMemoryRegionPool, virtMemReg);
				}

				DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, physMemReg);
				printf("INTEGRITY::MapMemoryWithAttributes(...) failed (%d):(\n", lErrorMap);
			} // else from if MapMemory succeeded
		} // if AllocateAnyMemoryRegion succeeded
		else
		{
			printf("INTEGRITY::AllocateAnyMemoryRegion(...) failed (%d):(\n", lError);
		} // else from if AllocateAnyMemoryRegion succeeded
	} // if not mapped yet
	else
	{
		// get user virtual address from register
		retUserVirtualPointer = gsCMBMapper.mRegister[idx].mpUserVirtualPointer;
	} // else from if not mapped yet

	// unlock mapper
	pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return retUserVirtualPointer;
} // CMBMapper::Map(uint32_t aPhysMemHandle)

LIB_RESULT
CMBMapper::UnMap(const void *apcVirtAddr)
{
	LIB_RESULT res = LIB_SUCCESS;
	// lock mapper until finished
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	
	uint32_t idx;
	if(FindByAddr(apcVirtAddr, idx) == LIB_SUCCESS)
	{
		if(mRegister[idx].mMappedCnt > 1)
		{
			--mRegister[idx].mMappedCnt;
		} // if not the last mapping of the region
		else
		{
			mRegister[idx].Invalidate();
			UnmapMemory(__ghs_VirtualMemoryRegionPool, mRegister[idx].mVirtualMemReg);
		} // else from if not the last mapping of the region
	} // if mapping exists
	else
	{
		res = LIB_FAILURE;
	} // else from if mapping exists

	// unlock mapper
	pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return res; 	
} // CMBMapper::UnMap(const void *apcVirtAddr)

LIB_RESULT
CMBMapper::UnMap(uint32_t aHandle)
{
	LIB_RESULT res = LIB_SUCCESS;
	// lock mapper until finished
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	
	uint32_t idx;
	if(FindByHandle(aHandle, idx) == LIB_SUCCESS)
	{
		if(mRegister[idx].mMappedCnt > 1)
		{
			--mRegister[idx].mMappedCnt;
		} // if not the last mapping of the region
		else
		{
			mRegister[idx].Invalidate();
			UnmapMemory(__ghs_VirtualMemoryRegionPool, mRegister[idx].mVirtualMemReg);
		} // else from if not the last mapping of the region
	} // if mapping exists
	else
	{
		res = LIB_FAILURE;
	} // else from if mapping exists

	// unlock mapper
	pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return res; 	
} // CMBMapper::UnMap(uint32_t aHandle)

LIB_RESULT CMBMapper::Register(const void* apcVirtAddr)
{
	LIB_RESULT lres = LIB_SUCCESS;

	// lock mapper until finished
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	
	uint32_t idx;
	if(FindByAddr(apcVirtAddr, idx) != LIB_SUCCESS)
	{
		if(idx >= mRegister.size())
		{
			// create new slot
			mRegister.push_back(ContiguousMemoryBlock());
		} // if no invalid slot
	
		// get shortcut to CMB at index "idx"
		ContiguousMemoryBlock &block = gsCMBMapper.mRegister[idx];
		// fill the CMB
		// compute address of the header
		block.mpHeaderPointer =  (OAL_MemHeader*)(apcVirtAddr - sizeof(OAL_MemHeader));
		block.mpBaseVirtualPointer = block.mpHeaderPointer->pVirtualBase;
		// set address of the virtual user region
		block.mpUserVirtualPointer = block.mpHeaderPointer->pVirtualNoncached;
		block.mVirtualMemReg = block.mpHeaderPointer->virtMemRegNoncached;
	} // if mapping doesn't exist

	pthread_mutex_unlock(&gsCMBMapper.mMutex);
	
	return lres;
} // 	CMBMApper::Register(const void* apcVirtAddr);

LIB_RESULT
CMBMapper::UnRegister(const void *apcVirtAddr)
{
	LIB_RESULT res = LIB_SUCCESS;
	// lock mapper until finished
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	
	uint32_t idx;
	if(FindByAddr(apcVirtAddr, idx) == LIB_SUCCESS)
	{
		// unregister
		mRegister[idx].Invalidate();
	} // if mapping exists
	else
	{
		res = LIB_FAILURE;
	} // else from if mapping exists

	// unlock mapper
	pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return res; 	
} // CMBMapper::UnRegister(const void *apcVirtAddr)

LIB_RESULT
CMBMapper::FindByHandle(uint32_t aHandle, uint32_t &arIdx)
{
	LIB_RESULT res = LIB_FAILURE;
	// set the index to out of register size in case nothing found
	arIdx = mRegister.size();
	// look for the CMB
  for (uint32_t i = 0; i < mRegister.size(); ++i)
  {
    if (!mRegister[i].IsValid())
    {
      arIdx = i;
    } // if CMB not valid
		else
		{
			if(mRegister[i].mpHeaderPointer->physAddr == aHandle)
			{
				arIdx = i;
				res = LIB_SUCCESS;
				break;
			} // if mapping found
		} // else from if CMB not valid		
  } // for all register entries

	return res;
} // FindByHandle(uint32_t aHandle, uint32_t &arIdx)

LIB_RESULT
CMBMapper::FindByAddr(const void *apcVirtAddr, uint32_t &arIdx)
{
	LIB_RESULT res = LIB_FAILURE;
	// set the index to out of register size in case nothing found
	arIdx = mRegister.size();
	// look for the CMB
  for (uint32_t i = 0; i < mRegister.size(); ++i)
  {
    if (!mRegister[i].IsValid())
    {
      arIdx = i;
    } // if CMB not valid
		else
		{
			if(mRegister[i].mpHeaderPointer->pVirtualNoncached == apcVirtAddr)
			{
				arIdx = i;
				res = LIB_SUCCESS;
				break;
			} // if mapping found
		} // else from if CMB not valid		
  } // for all register entries

	return res;
} // CMBMapper::ContiguousMemoryBlockFindByaddr(uint32_t aHandle, uint32_t &arIdx)

uint32_t
CMBMapper::GetPhysicalAddress(const void *apcVirtAddr)
{
	uint32_t ret = 0;
	uint32_t idx;

	// lock mutex
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	// try to find the mapping
	if(FindByAddr(apcVirtAddr, idx) == LIB_SUCCESS)
	{
		ret = mRegister[idx].mpHeaderPointer->physAddr;
	} // if among mapped

 pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return ret;	
} // CMBMapper::GetPhysicalAddress(const void *apcVirtAddr)

void* CMBMapper::GetVirtualAddress(uint32_t aPhysMemHandle)
{
	void* ret = 0;
	uint32_t idx;

	// lock mutex
	pthread_mutex_lock(&gsCMBMapper.mMutex);
	// try to find the mapping
	if(FindByHandle(aPhysMemHandle, idx) == LIB_SUCCESS)
	{
		ret = mRegister[idx].mpHeaderPointer->pVirtualNoncached;
	} // if among mapped

 pthread_mutex_unlock(&gsCMBMapper.mMutex);

	return ret;	
} // void* CMBMapper::GetVirtualAddress(uint32_t aPhysMemHandle);


////////////////////////////////////////////
//
// END: CMBMapper functionality
//
////////////////////////////////////////////

/****************************************************************************/
/** Allocates OAL memory (virtual only) under Integrity OS.
*
*	Adds header to the region.
*
* \param appHdr pointer to memory region header. Set by this function if all
*	successful.
*	\param aSizeInBytes number of bytes to be allocated. (including allignment)
*	\param aAllignmentInBytes size of the allignment
*
* \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
*****************************************************************************/
LIB_RESULT IntegrityAlloc(OAL_MemHeader** appHdr, unsigned aSizeInBytes,
		unsigned aAllignmentInBytes)
{
  LIB_RESULT lRetVal = LIB_FAILURE;

  void* virtAddr = malloc(aSizeInBytes);
  void* virtUserAddr = NULL;
  if(virtAddr != NULL)
  {
    uint64_t tmp = (uint64_t) virtAddr;
    //determine the offset from the start of the base physical address required to achieve the
    //desired 'user region' alignment
    uint64_t baseOffset = RET_USER_MEM_ADDR((uint64_t) virtAddr, aAllignmentInBytes) - (uint64_t) virtAddr;

		virtUserAddr = virtAddr + baseOffset;
    // Fill the header
    *appHdr = RET_HEADER_PTR(virtUserAddr);
    (*appHdr)->specialTag          = cSpecialTag;
    (*appHdr)->pVirtualBase        = (void*)virtAddr;
    (*appHdr)->pVirtualCached      = (void*)(virtUserAddr);
    (*appHdr)->pVirtualNoncached   = (void*)(virtUserAddr);
    (*appHdr)->physAddr            = 0;
    (*appHdr)->virtMemRegCached    = 0;
    (*appHdr)->virtMemRegNoncached = 0;
    (*appHdr)->physMemReg          = 0;

    // return success
    lRetVal = LIB_SUCCESS;
  }
  else
  {
    printf("INTEGRITY::malloc(...) failed :(\n");
  }

  return lRetVal;
} // LIB_RESULT IntegrityAlloc()

/****************************************************************************/
/** Allocates OAL memory (contiguous only) under Integrity OS.
*
*	Adds header to the region.
* Physical region is registered to defaut ResourceManager under the name:
* OMXXXXXXXX where XXXXXXXX is a hex representation of the user part physical
* address.
*
* \param appHdr pointer to memory region header. Set by this function if all
*	successful.
*	\param aSizeInBytes number of bytes to be allocated. (including allignment)
*	\param aAllignmentInBytes size of the allignment
*
* \return LIB_SUCCESS if all OK, otherwise LIB_FAILURE
*****************************************************************************/
LIB_RESULT IntegrityContAlloc(
		OAL_MemHeader** appHdr, unsigned aSizeInBytes, unsigned aAllignmentInBytes)
{
	MemoryRegion physMemReg, physMemReg_link, virtMemReg;
  LIB_RESULT lRetVal = LIB_FAILURE;
  Address virtAddr = 0;
  Value virtLength = 0;
  Address physFirst = 0;
  Address physLast = 0;
  Error lError, lErrorMap;

	// Allocate physical region
  lError = AllocateAnyMemoryRegion(gspUnmappedPhysMemRegPool, aSizeInBytes, &physMemReg);
  if (Success == lError)
  {
		// Get physical addresses of the physical memory region
    GetMemoryRegionAddresses(physMemReg, &physFirst, &physLast);

		// map physical region to virtual region and get its address
		lError = LinkMemoryRegion(physMemReg, &physMemReg_link);
		// map directly to the physical memory region, not to its link only
    lErrorMap = MapMemoryWithAttributes(__ghs_VirtualMemoryRegionPool, physMemReg, &virtMemReg, &virtAddr, &virtLength, 0, MEMORY_READ|MEMORY_WRITE|MEMORY_VOLATILE );

    if (Success == lErrorMap)
    {
			//determine the offset from the start of the base physical address required to achieve the
			//desired 'user region' alignment
			uint64_t baseOffset = RET_USER_MEM_ADDR(physFirst, aAllignmentInBytes) - physFirst;
				
			// generate name for the physical region 
			char physMemRegName[8+3];
			sprintf(physMemRegName,"OM%8x", (unsigned)(physFirst + baseOffset));

			// register physical memory region link (should work) / not the MR directly
			lError = RegisterLinkableResource((Object)physMemReg_link,physMemRegName,NULL); // Error: ObjectCannotBeMoved -> cannot be mapped

			if(lError == Success)
			{
				// Fill the header
				*appHdr = RET_HEADER_PTR(virtAddr + baseOffset);
				(*appHdr)->specialTag          = cSpecialTag;
				(*appHdr)->pVirtualBase        = (void*)virtAddr;
				(*appHdr)->pVirtualCached      = (void*)(virtAddr + baseOffset);
				(*appHdr)->pVirtualNoncached   = (void*)(virtAddr + baseOffset);
				(*appHdr)->physAddr            = physFirst + baseOffset;
				(*appHdr)->virtMemRegCached    = virtMemReg;
				(*appHdr)->virtMemRegNoncached = virtMemReg;
				(*appHdr)->physMemReg          = physMemReg;

				// register region
				gsCMBMapper.Register((*appHdr)->pVirtualNoncached);

				// return success
				lRetVal = LIB_SUCCESS;
			} // if succeeded to register physical memory region
			else
			{
				// failed to register the physical memory region
				UnmapMemory(__ghs_VirtualMemoryRegionPool, virtMemReg);
      
				DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, physMemReg);
				printf("INTEGRITY::MapMemoryWithAttributes(...) failed (%d):(\n", lErrorMap);
			} // else from if succeeded to register physical memory
			
    } // if MapMemory succeeded
    else //at least one of the mappings failed; clean things up
    {
      if (Success == lErrorMap)
      {
				UnmapMemory(__ghs_VirtualMemoryRegionPool, virtMemReg);
      }

      DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, physMemReg);
      printf("INTEGRITY::MapMemoryWithAttributes(...) failed (%d):(\n", lErrorMap);
    } // else from if MapMemory succeeded
  } // if AllocateAnyMemoryRegion succeeded
  else
  {
    printf("INTEGRITY::AllocateAnyMemoryRegion(...) failed (%d):(\n", lError);
  } // else from if AllocateAnyMemoryRegion succeeded

  return lRetVal;
} // IntegrityContAlloc()

/*****************************************************************************
* exported functions
*****************************************************************************/

/*==============================================================================*/
/* Initialize OAL memory allocation functionality						*/
/*==============================================================================*/
LIB_RESULT OAL_MemoryAllocInit()
{
  LIB_RESULT lRetVal = LIB_FAILURE;
  Error lError; //integrity error

  gsPhysOffset = OAL_DDR_PHYSICAL_POOL_BASE;

  lError = RequestResource((Object *)&gsPhysicalOalMemRegion, OAL_DDR_RESOURCE_NAME, "!systempassword");
  
  if (Success == lError)
  {
    lError = InitializeMemoryPool(&gspUnmappedPhysMemRegPool, gsPhysicalOalMemRegion);
    
    if (Success == lError)
    {
      lRetVal = LIB_SUCCESS;
    }
    else  
    {
      printf("INTEGRITY::InitializeMemoryPool(...) failed (%d):(\n", lError);
    }
  }
  else
  {		
    printf("INTEGRITY::RequestResource(..., %s, ... ) failed (%d):(\n", OAL_DDR_RESOURCE_NAME, lError);
  }
  
  return lRetVal;
} // LIB_RESULT OAL_MemoryAllocInit()

/*==============================================================================*/
/* Allocate the OAL memory function						*/
/*==============================================================================*/
void* OAL_MemoryAllocFlag(uint32_t size, OAL_MEMORY_FLAG flags)
{
  void* retPointer = 0;
  OAL_MemHeader* pHdr = 0;
  unsigned int nBytes2Align = 0; // For dealing with alignment flags
  unsigned long sizeWithHdrs = 0;
  int lErrorFlag = 0;
  
  if (OAL_MEMORY_FLAG_ALIGN(0) == (flags & OAL_MEMORY_FLAG_ALIGN(0)))
  {
    unsigned int n = NonZeroBitCnt((flags & 0xFF00) >> 8);
    if (1 == n) //if only one alignment option
    {
      if (OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE) == (flags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)))
      {
				nBytes2Align = CACHE_LINE_SIZE_IN_BYTES;
      } // if OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)
      else if (OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE) == (flags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE)))
      {
				nBytes2Align = PAGE_SIZE_IN_BYTES;
      } // if OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE)
      else if (OAL_MEMORY_FLAG_ALIGN(ALIGN2_BYTE(0)) == (flags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_BYTE(0))))
      {
				nBytes2Align = ((flags >> 16) & 0xFF);
				{
					// Verify alignment (2^n)
					unsigned int n = NonZeroBitCnt(nBytes2Align);

					if (1 != n)
					{
						// ABORT! Is not a multiple of 2
						lErrorFlag = 1;
					} // if n != 1
				}
      } // if OAL_MEMORY_FLAG_ALIGN(ALIGN2_BYTE(0))
    } // if 1 == n
    else //multiple/conflicting alignment options detected
    {
			lErrorFlag = 1;
    }
  }
  else
  {
    nBytes2Align = 1;
  }

  if (0 == lErrorFlag) //if no errors were detected above proceed to allocate memory
  {
    //determine the size of the allocation including headers and alignment padding
    sizeWithHdrs = SIZE_TO_ALLOC(size, nBytes2Align);

    //adjust 'sizeWithHdrs' so it is in page resolution (integrity memory region pool restriction)
	  int lTmp = 0;
    lTmp = (sizeWithHdrs % PAGE_SIZE_IN_BYTES);
    if (lTmp != 0)
    {
			sizeWithHdrs += (PAGE_SIZE_IN_BYTES - lTmp);
    }
    
    if (flags & OAL_MEMORY_FLAG_CONTIGUOUS)
    {
			// allocate the contiguous memory region and maps it
      if (LIB_SUCCESS == IntegrityContAlloc(&pHdr, sizeWithHdrs, nBytes2Align))
      {
				pHdr->bytesRequested = size;
				pHdr->bytesAllocated = sizeWithHdrs;
				pHdr->memFlags       = flags;

				if (flags & OAL_MEMORY_FLAG_ZERO)
				{
					memset(pHdr->pVirtualCached, 0, size);
				} // if set to zero required
				retPointer = pHdr->pVirtualCached;
      } // if Alloc ok
    } // if contiguous region requested
    else
    {
      // alocat virtual region with the header too but set it to noncontig
      if (LIB_SUCCESS == IntegrityAlloc(&pHdr, sizeWithHdrs, nBytes2Align))
      {
				pHdr->bytesRequested = size;
				pHdr->bytesAllocated = sizeWithHdrs;
				pHdr->memFlags       = flags;

				if (flags & OAL_MEMORY_FLAG_ZERO)
				{
					memset(pHdr->pVirtualCached, 0, size);
				} // if set zero required
				retPointer = pHdr->pVirtualCached;
      } // if Alloc OK				
    } // else from if contiguous region requested
  } // if no errors detected

  return retPointer;
} // void* OAL_MemoryAllocFlag(uint32_t size, OAL_MEMORY_FLAG flags)

/*==============================================================================*/
/* Allocate the OAL memory (no allignment) function						*/
/*==============================================================================*/
void* OAL_MemoryAlloc(uint32_t size)
{
  return OAL_MemoryAllocFlag(size, 0);
} // void* OAL_MemoryAlloc(uint32_t size)

/*==============================================================================*/
/* Map contiguous memory region							*/
/*==============================================================================*/
void* OAL_ContiguousMemoryMap(uint32_t aPhysMemHandle)
{
	// call the mapper
  return gsCMBMapper.Map(aPhysMemHandle);
} // OAL_ContigMemoryMap(uint32_t aPhysMemHandle)


/*==============================================================================*/
/* Unmap contiguous region by virtual address							*/
/*==============================================================================*/
LIB_RESULT OAL_ContiguousMemoryUnmap(void *apMemory)
{
	return gsCMBMapper.UnMap(apMemory);
} // OAL_ContigMemoryMap(uint32_t aPhysMemHandle)

/*==============================================================================*/
/* Unmap contiguous region by physical address							*/
/*==============================================================================*/
LIB_RESULT OAL_ContiguousMemoryUnmap(uint32_t aHandle)
{
	return gsCMBMapper.UnMap(aHandle);
} // OAL_ContigMemoryMap(uint32_t aPhysMemHandle)

/*==============================================================================*/
/* Return allocated size							*/
/*==============================================================================*/
unsigned int OAL_MemoryGetBytesRequested(void *pMemory)
{
	OAL_MemHeader* pHdr = RET_HEADER_PTR(pMemory);

  return pHdr->bytesRequested;
} // OAL_MemoryGetBytesRequested(void *pMemory)

/*==============================================================================*/
/* Free the memory OAL function							*/
/*==============================================================================*/
void OAL_MemoryFree(void* pMemory)
{
  OAL_MemHeader *lpOalMemory = RET_HEADER_PTR(pMemory);
  // do this only for the contiguous regions otherwise use free
  if ((lpOalMemory->memFlags & OAL_MEMORY_FLAG_CONTIGUOUS) == OAL_MEMORY_FLAG_CONTIGUOUS)
  {
		// unregister from mapper
		gsCMBMapper.UnRegister(pMemory);
		
		// get data from header
		MemoryRegion lVirtMemRegCached    = lpOalMemory->virtMemRegCached;
    MemoryRegion lPhysMemReg          = lpOalMemory->physMemReg;

		// generate name for the physical region 
		char physMemRegName[8+3];
		sprintf(physMemRegName,"OM%8x", (unsigned)lpOalMemory->physAddr);

		// remove from system
		DeleteResource(physMemRegName,NULL);
		UnmapMemory(__ghs_VirtualMemoryRegionPool, lVirtMemRegCached);
		DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, lPhysMemReg);

		// remove from Mapper
		
  } // if contiguous region
  else
  {
    free(lpOalMemory->pVirtualBase);
  } // else from if contiguous region
} // OAL_MemoryFree(void* pMemory)

#ifdef __cplusplus
extern "C" {
#endif

//works only for physical addresses allocated by contiguous allocator
void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access)
{
  void* ret = NULL;

	switch(access)
	{
		case ACCESS_PHY:
			{
				OAL_MemHeader *pHdr = RET_HEADER_PTR(pBuffer);
				ret = (void*)(pHdr->physAddr);
			} // case physical
			break;
		case ACCESS_CH_WB:
		case ACCESS_CH_WT:
		case ACCESS_NCH_B:
		case ACCESS_NCH_NB:
			{
				ret = (void*)gsCMBMapper.GetVirtualAddress((uint64_t)pBuffer);
			} // case virtual
			break;
		default:
			break;
	} // switch access
  return ret;
} // void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access)

#ifdef __cplusplus
}
#endif
