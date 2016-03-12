/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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
#include <oal.h>
#include "oal_memory_internals.h"
#include <global_types.h>
#include <INTEGRITY.h>

/*==============================================================================*/
/* OAL Memory structures							*/
/*==============================================================================*/
static MemoryRegion gsPhysicalOalMemRegion = NULLMemoryRegion;
static MemoryRegionPool* gspUnmappedPhysMemRegPool = 0;
static Address      gsPhysOffset              = 0;

typedef struct memory_s OAL_MEMORY2;
struct memory_s
{
  unsigned int     specialTag;        // indicates this is an OAL_MEMORY2 struct
  unsigned int     bytesRequested;    // size requested
  unsigned int     bytesAllocated;    // actual #bytes allocated
  OAL_MEMORY_FLAG  memFlags;          // memory type requested
  void*            pVirtualBase;      // OS 'virtual' ptr to start of all allocated memory (including header and alignment padding)
  void*            pVirtualCached;    // OS 'virtual' ptr to start of user buffer (cached)
  void*            pVirtualNoncached; // OS 'virtual' ptr to start of user buffer (noncached)
  Address          physAddr;          // physical address associated with start of user buffer (for HW use only)
  MemoryRegion     virtMemRegCached;    // cached virtual 'memory region' entity (mapped to 'physMemReg')
  MemoryRegion     virtMemRegNoncached; // noncached virtual 'memory region' entity (mapped to 'physMemReg')
  MemoryRegion     physMemReg;          // physical 'memory region' entity
};

#define sizeToAlloc(_s_, _a_)  ((_s_) + sizeof(OAL_MEMORY2) + (_a_-1))
#define ret_user_mem_addr(_baseAddr_, _a_) (((Address)(_baseAddr_) + sizeof(OAL_MEMORY2) + ((Address)_a_-1)) & (~((Address)_a_-1)))
#define ret_header_ptr(_pUser_) (OAL_MEMORY2*) ((uint8_t *)(_pUser_) - sizeof(OAL_MEMORY2))

/*==============================================================================*/
/* HEADER initialization							*/
/*==============================================================================*/
void INIT_HEADER_PTR (Address lVirtBaseAddrCached, Address lVirtBaseAddrNoncached, Address lPhysBaseAddr, MemoryRegion lVirtMemRegCached, MemoryRegion lVirtMemRegNoncached, MemoryRegion lPhysMemReg, OAL_MEMORY2** pHdr, unsigned int lAllignmentInBytes)
{
  //determine the offset from the start of the base physical address required to achieve the
  //desired 'user region' alignment
  Address lBaseOffset = ret_user_mem_addr(lPhysBaseAddr, lAllignmentInBytes) - lPhysBaseAddr;

  *pHdr = ret_header_ptr(lVirtBaseAddrCached + lBaseOffset);
  (*pHdr)->specialTag          = cSpecialTag;
  (*pHdr)->pVirtualBase        = (void*)lVirtBaseAddrCached;
  (*pHdr)->pVirtualCached      = (void*)(lVirtBaseAddrCached + lBaseOffset);
  (*pHdr)->pVirtualNoncached   = (void*)(lVirtBaseAddrNoncached + lBaseOffset);
  (*pHdr)->physAddr            = lPhysBaseAddr + lBaseOffset;
  (*pHdr)->virtMemRegCached    = lVirtMemRegCached;
  (*pHdr)->virtMemRegNoncached = lVirtMemRegNoncached;
  (*pHdr)->physMemReg          = lPhysMemReg;
}

#define OAL_MEM_DEFINE_BASE(_pHdr_, _pBuf_) OAL_MEMORY2* _pHdr_ = ret_header_ptr(_pBuf_)

#define OAL_MEM_IS_HDR(_pHdr_) (cSpecialTag == _pHdr_->specialTag)

#define OAL_MEM_CHK_HDR(_pHdr_, _res_)         \
   _res_ = LIB_FALSE;                          \
   if (cSpecialTag == _pHdr_->specialTag)      \
      _res_ = LIB_TRUE

/*==============================================================================*/
/* Macro to count # of bits.							*/
/*==============================================================================*/
unsigned int NonZeroBitCnt(unsigned int value)
{
  unsigned int x = value;
  unsigned int n = 0;
  while (x != 0)
  {
    n = n + (x & 0x01);
    x = x >> 1;
  }

  return n;
}

/*==============================================================================*/
/* Memory alloc initialization							*/
/*==============================================================================*/
LIB_RESULT OAL_MemoryAllocInit()
{
  LIB_RESULT lRetVal = LIB_FAILURE;
  Error lError; //integrity error

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

#ifdef __S32V234
  if (lRetVal == LIB_SUCCESS)
  {
    IODevice oal;

    lError = RequestResource((Object *) &oal, OAL_IODEVICE_NAME, "!systempassword");

    if (Success == lError)
    {
      Address virtbase;
      Value physbase;

      GetMemoryRegionAddresses(gsPhysicalOalMemRegion, &virtbase, NULL);

      lError = WriteIODeviceRegister(oal, OAL_IODEVICE_GET_PHYSICAL , virtbase);

      if (Success == lError)
      {
	lError = ReadIODeviceRegister(oal, OAL_IODEVICE_GET_PHYSICAL , &physbase);

	if (Success == lError)
	{
	  gsPhysOffset = virtbase - physbase;
	}
	else
	{
	  printf("INTEGRITY::ReadIODeviceResgiter(..., %s, ...) failed (%d):(\n", "OAL_IODEVICE_GET_PHYSICAL", lError);
	  lRetVal = LIB_FAILURE;
	}
      }
      else
      {
	printf("INTEGRITY::WriteIODeviceResgiter(..., %s, ...) failed (%d):(\n", "OAL_IODEVICE_GET_PHYSICAL", lError);
	lRetVal = LIB_FAILURE;
      }
    }
    else
    {
      printf("INTEGRITY::RequestResource(..., %s, ... ) failed (%d):(\n", OAL_IODEVICE_NAME, lError);
      lRetVal = LIB_FAILURE;
    }
  }
#endif
  
  return lRetVal;
}

/*==============================================================================*/
/* Allocate the memory for INTEGRITY RTOS					*/
/*==============================================================================*/
LIB_RESULT IntegrityAlloc(
      MemoryRegion* lpPhysMemReg, MemoryRegion* lpVirtMemRegCached, MemoryRegion* lpVirtMemRegNoncached, unsigned int lpSizeInBytes, Address* lpVirtBaseAddrCached, Address* lpVirtBaseAddrNoncached, Address* lpPhysBaseAddr)
{
  LIB_RESULT lRetVal = LIB_FAILURE;
  Value lAddr = 0;
  Value lLength = 0;
  Address lFirst = 0;
  Address lLast = 0;
  Error lError, lErrorMapCached;

  lError = AllocateAnyMemoryRegion(gspUnmappedPhysMemRegPool, lpSizeInBytes, lpPhysMemReg);
  if (Success == lError)
  {
    GetMemoryRegionAddresses(*lpPhysMemReg, &lFirst, &lLast);
    *lpPhysBaseAddr = (Address)(lFirst - gsPhysOffset);
    //printf("physMemReg: 0x%08x - 0x%08x\n", lFirst, lLast);

  
    lErrorMapCached = MapMemoryWithAttributes(__ghs_VirtualMemoryRegionPool, *lpPhysMemReg, lpVirtMemRegCached, &lAddr, &lLength, 0, MEMORY_READ|MEMORY_WRITE|MEMORY_VOLATILE );

    if (Success == lErrorMapCached)// && Success == lErrorMapNoncached)
    {
      GetMemoryRegionAddresses(*lpVirtMemRegCached, &lFirst, &lLast);
      *lpVirtBaseAddrCached = lFirst;
      *lpVirtBaseAddrNoncached = lFirst;
      lRetVal = LIB_SUCCESS;
    }
    else //at least one of the mappings failed; clean things up
    {
      if (Success == lErrorMapCached)
      {
	UnmapMemory(__ghs_VirtualMemoryRegionPool, *lpVirtMemRegCached);
      }

      DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, *lpPhysMemReg);
      printf("INTEGRITY::MapMemoryWithAttributes(...) failed (%d):(\n", lErrorMapCached);
    }
  }
  else
  {
    printf("INTEGRITY::AllocateAnyMemoryRegion(...) failed (%d):(\n", lError);
  }

  return lRetVal;
}

/*==============================================================================*/
/* Allocate the memory OAL function						*/
/*==============================================================================*/
void* OAL_MemoryAllocFlag(uint32_t size, OAL_MEMORY_FLAG flags)
{
  void* rp = 0;
  OAL_MEMORY2* pHdr = 0;
  unsigned int nBytes2Align = 0; // For dealing with alignment flags
  unsigned long sizeWithHdrs = 0;
  int lErrorFlag = 0;
  int lTmp = 0;
  Address lVirtBaseAddrCached = 0;
  Address lVirtBaseAddrNoncached = 0;
  Address lPhysBaseAddr = 0;
  MemoryRegion lVirtMemRegCached    = NULLMemoryRegion;
  MemoryRegion lVirtMemRegNoncached = NULLMemoryRegion;
  MemoryRegion lPhysMemReg          = NULLMemoryRegion;

  if (OAL_MEMORY_FLAG_ALIGN(0) == (flags & OAL_MEMORY_FLAG_ALIGN(0)))
  {
    unsigned int n = NonZeroBitCnt((flags & 0xFF00) >> 8);
    if (1 == n) //if only one alignment option
    {
      if (OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE) == (flags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)))
      {
	nBytes2Align = CACHE_LINE_SIZE_IN_BYTES;
      }
      else if (OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE) == (flags & OAL_MEMORY_FLAG_ALIGN(ALIGN2_PAGE)))
      {
	nBytes2Align = PAGE_SIZE_IN_BYTES;
      }
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
	    }
	}
      }
    }
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
    sizeWithHdrs = sizeToAlloc(size, nBytes2Align);

    //adjust 'sizeWithHdrs' so it is in page resolution (integrity memory region pool restriction)
    lTmp = (sizeWithHdrs % PAGE_SIZE_IN_BYTES);
    if (lTmp != 0)
    {
	sizeWithHdrs += (PAGE_SIZE_IN_BYTES - lTmp);
    }

    if (LIB_SUCCESS == IntegrityAlloc(&lPhysMemReg, &lVirtMemRegCached, &lVirtMemRegNoncached, sizeWithHdrs, &lVirtBaseAddrCached, &lVirtBaseAddrNoncached, &lPhysBaseAddr))
    {
      INIT_HEADER_PTR(lVirtBaseAddrCached, lVirtBaseAddrNoncached, lPhysBaseAddr, lVirtMemRegCached, lVirtMemRegNoncached, lPhysMemReg, &pHdr, nBytes2Align);

      pHdr->bytesRequested = size;
      pHdr->bytesAllocated = sizeWithHdrs;
      pHdr->memFlags       = flags;

      rp = pHdr->pVirtualCached;

      if (flags & OAL_MEMORY_FLAG_ZERO)
      {
	memset(rp, 0, size);
      }
    }
    else //integrity allocation failed
    {
	lErrorFlag = 1;
    }
  }

  return rp;
}

/*==============================================================================*/
/* Return the specific address							*/
/*==============================================================================*/
void *OAL_MemoryReturnAddress(void *pMemory, OAL_MEMORY_ACCESS access)
{
  void *lpAddr = 0;
  LIB_BOOL isValid;
  OAL_MEM_DEFINE_BASE(lpHdr, pMemory);
  OAL_MEM_CHK_HDR(lpHdr, isValid);

  if (LIB_TRUE == isValid)
  {
    switch (access)
    {
      case ACCESS_PHY:
	lpAddr = (void*)lpHdr->physAddr;
      break;
      case ACCESS_CH_WB:
      case ACCESS_CH_WT:
	OAL_MemoryFlushAndInvalidate(pMemory, lpHdr->bytesRequested);
	lpAddr = lpHdr->pVirtualCached;
      break;
      case ACCESS_NCH_B:
      case ACCESS_NCH_NB:
	OAL_MemoryFlushAndInvalidate(pMemory, lpHdr->bytesAllocated);
	lpAddr = lpHdr->pVirtualNoncached;
      break;
    }
  }

  return lpAddr;
}

/*==============================================================================*/
/* Return allocated size							*/
/*==============================================================================*/
unsigned int OAL_MemoryGetBytesRequested(void *pMemory)
{
  int lBytesRequested = 0;
  LIB_BOOL isValid = LIB_FALSE;

  OAL_MEM_DEFINE_BASE(pHdr, pMemory);
  OAL_MEM_CHK_HDR(pHdr, isValid);

  if (LIB_TRUE == isValid)
  {
    lBytesRequested = pHdr->bytesRequested;
  }

  return lBytesRequested;
}

/*==============================================================================*/
/* Free the memory OAL function							*/
/*==============================================================================*/
void OAL_MemoryFree(void* pMemory)
{
  //TODO: check OS return calls for errors ... ?

  OAL_MEMORY2 *lpOalMemory = ret_header_ptr(pMemory);

  if (OAL_MEM_IS_HDR(lpOalMemory))
  {
    MemoryRegion lVirtMemRegCached    = lpOalMemory->virtMemRegCached;
    
    MemoryRegion lPhysMemReg          = lpOalMemory->physMemReg;
    UnmapMemory(__ghs_VirtualMemoryRegionPool, lVirtMemRegCached);
    //UnmapMemory(__ghs_VirtualMemoryRegionPool, lVirtMemRegNoncached);
    DeallocateMemoryRegion(gspUnmappedPhysMemRegPool, lPhysMemReg);  
  }
  else
  {
    printf("OAL_MemoryFree(...) - pMemory is not a valid OAL memory pointer\n");
  }
}

/*==============================================================================*/
/* Flush the memory OAL function						*/
/*==============================================================================*/
void OAL_MemoryFlush(void *pMemory, uint32_t size)
{
  OAL_MemoryFlushAndInvalidate(pMemory, size);
}

/*==============================================================================*/
/* Invalidate the memory OAL function						*/
/*==============================================================================*/
void OAL_MemoryInvalidate(void *pMemory, uint32_t size)
{
  OAL_MemoryFlushAndInvalidate(pMemory, size);
}

/*==============================================================================*/
/* Flush and invalidate the memory OAL function					*/
/*==============================================================================*/
void OAL_MemoryFlushAndInvalidate(void *pMemory, uint32_t size)
{
#ifdef __S32V234
  Error lError; //integrity error

  lError = ManageCaches((Address)pMemory, (Length)size, ACCESS_DST_COHERENT);
  if (lError != Success)
  {
    printf("INTEGRITY::ManageCaches(..., ACCESS_DST_COHERENT) failed (%d):(\n", lError);
  }
#else
  Error lError; //integrity error
  LIB_BOOL isValid;
  OAL_MEM_DEFINE_BASE(lpHdr, pMemory);
  OAL_MEM_CHK_HDR(lpHdr, isValid);

  if (LIB_TRUE == isValid)
  {
    //for now ignore the size and flush the entire page aligned memory region for simplicity
    lError = ManageCaches((Address)lpHdr->pVirtualBase, (Length)lpHdr->bytesAllocated, ACCESS_DST_COHERENT);
    if (lError != Success)
    {
	printf("INTEGRITY::ManageCaches(..., ACCESS_DST_COHERENT) failed (%d):(\n", lError);
    }
  }
  else
  {
    printf("OAL_MemoryFlushAndInvalidate(...) - pMemory is not a valid OAL memory pointer\n");
  }
#endif // __S32V234
}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __S32V234
void flush_dcache_range(void *pMemory, unsigned int size)
{
  OAL_MemoryFlushAndInvalidate(pMemory, size);
}
#endif

#ifdef __cplusplus
}
#endif
