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
/**
* \file     sdi_graph.cpp
* \brief    Defines Sequencer graph related functionality. Depends 
*           on GDT generated metadata.
* \author   Tomas Babinec
* \version  0.1
* \date     21-October-2014
****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include "s32vs234.h"
#include "sdi_graph.hpp"
#include "sram.h"
#include "fdma.h"
#include "fdma_public.h"
#include "sram_public.h"
#include "seq_graph.h"
#include "seq.h"
#include "seq_public.h"
#include "isp_hw.h"

#ifndef __STANDALONE__
#include <unistd.h>
#include <sys/mman.h>
#endif // #ifndef __STANDALONE__

// logging functionality
#define VDB_LOG_NOTE_OFF

#include "vdb_log.h"

#define VDB_LOG_NOTE_OFF

/*****************************************************************************
* Macros
*****************************************************************************/

#define SDI_LOG_LIB_RESULT(_func, _lres) \
{\
  if(_lres == LIB_SUCCESS)\
  {\
    VDB_LOG_NOTE(_func " returned: LIB_SUCCESS.\n\n");\
  }else if(_lres == LIB_FAILURE)\
  {\
    VDB_LOG_ERROR(_func " returned: LIB_FAILURE.\n\n");\
  }else\
  {\
    VDB_LOG_ERROR(_func " returned: unknown result.\n\n");\
  }\
} // SDI_LOG_LIB_RESULT()

/*****************************************************************************
* global data
*****************************************************************************/

int32_t gFdmaFD = -1;
int32_t gSeqFD = -1;
int32_t gSramFD = -1;

//****************************************************************************
// consts
//****************************************************************************

#define TDT_CNT 16
#define PRAM_M02HOST_OFFSET (PRAM_BASE - SEQ_PRAM_BASE)
#define CRAM_M02HOST_OFFSET  (CRAM_BASE - CRAM_BASE_M0)
#define SRAM_CHAR_VAL 7
#define DDR_CHAR_VAL (TDT_CNT + 1)

//****************************************************************************
// macros
//****************************************************************************

#define CRAM_HOST2M0(_HostAddr) ((uint32_t)(_HostAddr - CRAM_M02HOST_OFFSET)) 
#define CRAM_M02HOST(_M0Addr) ((uint32_t)(_M0Addr + CRAM_M02HOST_OFFSET))

#define PRAM_HOST2M0(_HostAddr) ((uint32_t)(_HostAddr - PRAM_M02HOST_OFFSET)) 
#define PRAM_M02HOST(_ProAddr) ((uint32_t)(_ProAddr + PRAM_M02HOST_OFFSET))


#define ALIGN2(_x) (((_x)/2 + (((_x)%2)?1:0)) * 2)


//****************************************************************************
// local variables
//****************************************************************************


//****************************************************************************
// local functions declarations
//****************************************************************************
static uint8_t* M0GraphMap(void);
static void M0GraphUnmap(uint8_t *apMem);

//****************************************************************************
// methods implementation
//****************************************************************************

#if 0
// *** sdi_GraphObject implementation ***

GraphObject::GraphObject(const void* apAddr, uint32_t aSize):mcpAddr(apAddr), mSize(aSize)
{};

//****************************************************************************

GraphObject::GraphObject():mcpAddr(NULL), mSize(0)
{};

//****************************************************************************
#endif //if 0

// *** sdi_graph implementation ***

sdi_graph::sdi_graph():
  mpGraph(NULL),
  mpMeta(NULL),
  mHeadCnt(0),
  mpPackedGraph(NULL),  
  mpPackedObjects(NULL),
  mpFdma(NULL)
{
  mpGraphM0 = (void*)M0GraphMap();
  
  memset(mpFdmaPackedBck, 0, sizeof(SEQ_FdmaCfg_t));
  
  // reset all IO indexes
  for(uint32_t i = 0; i < SEQ_OTHRIX_LAST; i++)
  {
    mIoNodeIdxArr[i]  = -1;
    mpIoNodePtrArr[i] = NULL;
  } // for all TC pointers
  
  // reset all TC pointers
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    mTcs[i] = NULL;
  } // for all TC pointers
} // sdi_graph::sdi_graph()

//****************************************************************************

sdi_graph::sdi_graph(SEQ_Head_Ptr_t apGraph[], GraphMetadata_t *apMeta):
    mpGraph(apGraph),
    mpMeta(apMeta),
    mpPackedGraph(NULL),
    mpPackedObjects(NULL),
    mpFdma(NULL)
{
  mpGraphM0 = (void*)M0GraphMap();
  
  // get number of heads in the graph
  //mHeadCnt = sizeof(apGraph) / sizeof(SEQ_Head_t*);
  mHeadCnt = 0;
  
  memset(mpFdmaPackedBck, 0, sizeof(SEQ_FdmaCfg_t));
  
  // reset CSI node pointers
  for(uint32_t i = 0; i < CSI_IF_CNT; i++)
  {
    mppCsi[i] = NULL;
  }
  
  // reset all IO indexes
  for(uint32_t i = 0; i < SEQ_OTHRIX_LAST; i++)
  {
    mIoNodeIdxArr[i]  = -1;
    mpIoNodePtrArr[i] = NULL;
  } // for all TC pointers
  
  // reset all TC pointers
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    mTcs[i] = NULL;
  } // for all TC pointers

  // pack the graph
  if(apMeta->mObjCnt > 0)
  {
    Pack();
    Scan(); // only to get FDMA node
    
    FdmaTCsPrepare();  
  } // if there are some objects
  else
  {
    VDB_LOG_WARNING("No objects in the graph.\n");
  } // else from if there are some objects
} // sdi_graph::sdi_graph(SEQ_Head_t *aGraph[])

//****************************************************************************

sdi_graph::~sdi_graph()
{
  VDB_LOG_NOTE("Graph destructor.\n");
  
  FdmaTCsRemove();
    
  SramBuffersFree();
  
#ifdef ARM   
  // unmap PRAM
  M0GraphUnmap((uint8_t*)mpGraphM0);
#endif
  
  if(mpPackedGraph)
  {
    free(mpPackedGraph);
  }
  
  if(mpFetchedGraph)
  {
    free(mpFetchedGraph);
  }
  
  if(mppFetchedBufferList)
  {
    free(mppFetchedBufferList);
  }
} // sdi_graph::~sdi_graph()

//****************************************************************************

uint8_t* M0GraphMap(void)
{
  uint8_t *lpMem = NULL;
#ifndef __STANDALONE__  
  int32_t lFd = 0;
  
  lFd = open("/dev/mem", O_RDWR);
  
  VDB_LOG_NOTE("Mapping PRAM %x.\n", PRAM_BASE);
  
  if(lFd < 0)
  {
    VDB_LOG_ERROR("Failed to open /dev/mem\n");
  } //if failed to open /dev/mem
  else
  { 
    lpMem = (uint8_t*) mmap(NULL, PRAM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lFd, PRAM_BASE);
    if (lpMem == NULL) 
    {
      VDB_LOG_ERROR("Can't map PRAM: %s\n", strerror(errno));
    }
    
    close(lFd);
  } // else from if failed to open /dev/mem
#else // #ifndef __STANDALONE__
  lpMem = (uint8_t*)SEQ_GRAPH_ADDR;
#endif // else from if #ifndef __STANDALONE__

  return lpMem;
} // M0GraphMap()

//****************************************************************************

void M0GraphUnmap(uint8_t *apMem)
{
  VDB_LOG_NOTE("UnMapping PRAM.\n");
#ifndef __STANDALONE__  
  if(apMem != NULL)
  {
    munmap(apMem,PRAM_SIZE);
  } // if apMem not NULL
  else
  {
    VDB_LOG_WARNING("Pointer is NULL. PRAM not unmapped.\n");
  } // else from if apMem not NULL
#endif // #ifndef __STANDALONE__
} // M0GraphUnmap()

//****************************************************************************
#if 0
LIB_RESULT sdi_graph::IOcfgFetch(sdi_io &arIO)
{
  LIB_RESULT lRes = LIB_SUCCESS;
  
  switch(arIO.mTypeIndex)
  {
    case SEQ_OTHRIX_FDMA:
    {
      sdi_FdmaIO &lrFdmaIO = (sdi_FdmaIO&) arIO;
      lrFdmaIO.mppTcs = mTcs;
    }
      break;
      
    case SEQ_OTHRIX_H264ENC:
    case SEQ_OTHRIX_H264DEC:
    case SEQ_OTHRIX_JPEGDEC:
    case SEQ_OTHRIX_MIPICSI0:
    case SEQ_OTHRIX_MIPICSI1:
      VDB_LOG_NOTE("CfgFetch not implemented for this IO object type.\n");
      break; 
    default:
      VDB_LOG_ERROR("Unknown IO device type.\n");
      break;
  };
  
  return lRes;
} // sdi_graph::IOcfgFetch(sdi_io &arIO);
#endif
//****************************************************************************

inline void *sdi_graph::Off2Packed(uint32_t aOffset)
{
  return (mpPackedGraph != NULL)?(void*)((uint8_t*)mpPackedGraph + aOffset):NULL;
} // void *sdi_graph::Off2Packed(uint32_t aOffset)

//****************************************************************************

LIB_RESULT sdi_graph::FdmaTCsPrepare()
{
  LIB_RESULT lRes = LIB_SUCCESS;
  
  // if FDMA
  if(mpFdma != NULL)
  {
    // get pointer to FDMA config backup place
    SEQ_FdmaCfg_t *lpFdmaPackedBck = (SEQ_FdmaCfg_t *) mpFdmaPackedBck;
    
    // back up its contents (original TC indexes will be changed based on TC allocation)
    memcpy(lpFdmaPackedBck,mpFdma, sizeof(SEQ_FdmaCfg_t));
    
    // Prepare TCs for all channels used in the graph    
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      //is this TC used as input or output?
      if((mpFdma->mOutBuf[i].mpOutBuf != 0) && (mpFdma->mInBuf[i].mpInBuf != 0))
      {
        // allocate TC structure
        mTcs[i] = (FDMA_Tc_t*) new(FDMA_Tc_t);
        memset(mTcs[i],0, sizeof(FDMA_Tc_t));
        if(mTcs[i] != NULL)
        {
          // get both buffer structures
          SEQ_Buf_t* lpInBuf  = (SEQ_Buf_t*)(Off2Packed((uint32_t)mpFdma->mInBuf[i].mpInBuf));
          SEQ_Buf_t* lpOutBuf = (SEQ_Buf_t*)(Off2Packed((uint32_t)mpFdma->mOutBuf[i].mpOutBuf));
          SEQ_Buf_t *lpSramBuf = NULL, *lpDdrBuf = NULL;
          
          if((lpInBuf == NULL) || (lpOutBuf == NULL) || (lpInBuf->mpBuf == lpOutBuf->mpBuf))
          {
            VDB_LOG_ERROR("Bad FDMA I/O buffers.\n");
          } // if bad IO buffers
          else
          {
            if(lpInBuf->mpBuf == 0)
            {
              lpSramBuf = lpInBuf;
              lpDdrBuf  = lpOutBuf;
              mTcs[i]->mTd.mDir = 0;			// SRAM->DDR
            } // if SRAM -> DDR
            else
            {
              lpSramBuf = lpOutBuf;
              lpDdrBuf  = lpInBuf;
              mTcs[i]->mTd.mDir = 1;			// DDR->SRAM
            } // else
            
            // general TD setup
            mTcs[i]->mTd.mTransRecWrBack = 1;		// enable TD update
            mTcs[i]->mTd.mLineSize = lpSramBuf->mcLineBytes;
            // SRAM side TD setup
            mTcs[i]->mTd.mSramImgStartAddr = 0; // not yet allocated
            mTcs[i]->mTd.mSramLineStride = lpSramBuf->mcLineStride/8;
            mTcs[i]->mTd.mSramLineCnt = lpSramBuf->mcLineMax;
            mTcs[i]->mTd.mSramCurrLine = 0;
            // DDR side TD setup
            mTcs[i]->mTd.mDdrImgStartAddr = 0; // not yet allocated
            mTcs[i]->mTd.mDdrLineStride = lpDdrBuf->mcLineStride/32;
            mTcs[i]->mTd.mDdrLineCnt = lpDdrBuf->mcLineMax;
            mTcs[i]->mTd.mDdrCurrLine = 0;	    
          }
        } // if TC allocation OK
        else
        {
          VDB_LOG_ERROR("Tc at index %u allocation failed\n", (unsigned) i);
          // set to NULL
          mTcs[i] = NULL;
          lRes = LIB_FAILURE;
          break;
        } // else from if TC allocation OK
      } // if i-th channel used
    } // for all possible FDMA channels
  } // if FDMA node exists
  
  return lRes;
} // FdmaTCsPrepare()

//****************************************************************************

LIB_RESULT sdi_graph::FdmaTCsReserve()
{
  LIB_RESULT lRes = LIB_SUCCESS;
  
  // if FDMA
  if(mpFdma != NULL)
  {           
    // reserve all prepared TCs    
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      //is TC prepared
      if(mTcs[i] != NULL)
      {
#if 0        
        // reserve TC
        //if (ioctl(gFdmaFD, IOCTL_FDMA_TD_RESERVE, &(mTcs[i]->mTdm)) != FDMA_DRV_SUCCESS) 
        if (FdmaTcReserve(mTcs[i]) != FDMA_LIB_SUCCESS) 
        {
          VDB_LOG_ERROR("Tc at index %u reserve failed\n", (unsigned) i);
          lRes = LIB_FAILURE;
          break;
        } // if ioctl returned failure 
        else
        {
#endif // if 0
          mTcs[i]->mTdm.mTdIdx        = i; 
          mTcs[i]->mTdm.mOwnerProcId  = 333;
          mTcs[i]->mTdm.mReserved     = 1;
          
          // get pointer to the sram buffer
          SEQ_Buf_t* lpSramBuf  = NULL;
          if(mTcs[i]->mTd.mDir == 1)
          {
            lpSramBuf = (SEQ_Buf_t*)(Off2Packed((uint32_t)mpFdma->mOutBuf[i].mpOutBuf));
          } // if DDR->SRAM
          else
          {
            lpSramBuf = (SEQ_Buf_t*)(Off2Packed((uint32_t)mpFdma->mInBuf[i].mpInBuf));
          } // else from if DDR->SRAM
          
          // set SRAM address to TC
          mTcs[i]->mTd.mSramImgStartAddr = (uint32_t)(lpSramBuf->mpBuf);

#if 0           
          // update TD in SRAM
          //if(ioctl(gFdmaFD, IOCTL_FDMA_TD_CONFIG, mTcs[i]) != FDMA_DRV_SUCCESS) 
          if(FdmaTcIspConfig(mTcs[i]) != FDMA_LIB_SUCCESS)
          {
            VDB_LOG_ERROR("TcConfig failed.\n");
            lRes = LIB_FAILURE;
          } // if ioctl returned failure        
        } // else from if ioctl returned failure	
#endif // 0
      } // if TC prepared
    } // for all possible FDMA channels
  } // if FDMA node exists
  
  return lRes;
} // FdmaTCsReserve()

//****************************************************************************

void sdi_graph::FdmaTCsRelease()
{
  // reset all TC pointers
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    if((mTcs[i] != NULL) && ((mTcs[i]->mTdm.mReserved) > 0))
    {
#if 0      
      // release TC
      //if (ioctl(gFdmaFD, IOCTL_FDMA_TD_RELEASE, &(mTcs[i]->mTdm)) != FDMA_DRV_SUCCESS)
      if(FdmaTcRelease(mTcs[i]) != FDMA_LIB_SUCCESS)
      {
        VDB_LOG_ERROR("TC number %u release failed\n", (unsigned) i);
      } // if ioctl returned failure
      else
      {
#endif //if 0
        VDB_LOG_NOTE("TC number %u released OK\n", (unsigned) i);
        mTcs[i]->mTdm.mReserved = 0;
#if 0
      } // else from if ioctl returned failure
#endif // 0
    } // if TC allocated
  } // for all TC pointers
} // sdi_graph::FdmaTCsRelease()

//****************************************************************************

void sdi_graph::FdmaTCsRemove()
{
  FdmaTCsRelease();
  // release & delete all TC pointers
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    if(mTcs[i] != NULL)
    {
      // delete TC
      delete(mTcs[i]);
      mTcs[i] = NULL;
    } // if TC allocated
  } // for all TC pointers
} // sdi_graph::FdmaTCsRemove()

//****************************************************************************

LIB_RESULT sdi_graph::SramBuffersAllocate()
{
  LIB_RESULT lRet = LIB_SUCCESS;
  int32_t lRes = 0;
  
  // *** allocate all sram buffers ***
  for(uint32_t i = 0; i < mpMeta->mBfrCnt; i++)
  {
    SEQ_Buf_t* lpCurrBuff = (SEQ_Buf_t*)Off2Packed((uint32_t)mpMeta->mpBufferList[i]);
    
    if(lpCurrBuff->mpBuf != 0)
    {
      continue;
    } // if DDR buffer - no allocation
    
    // compute size required
    uint32_t lSize = lpCurrBuff->mcLineMax * lpCurrBuff->mcLineStride;

    // allocate SRAM 
    lRes = SramMultiMalloc(lSize);

    if(lRes == 0)
    {
      VDB_LOG_NOTE("Allocation from MULTI-banked region failed. Retrying from Single-banked region.\n");
      // attempt to allocate from Single-banked region
      lRes = SramSingleMalloc(lSize);
      if(lRes == 0)
      {
        VDB_LOG_ERROR("Failed to allocate SRAM buffer.\n");
        lRet = LIB_FAILURE;
        break;
      } // if also the second allocation failed
    } // if alloc failed
    
    // set addr to buffer
    lpCurrBuff->mpBuf = (SEQ_Mem_Ptr_t)( lRes);
  } // for all buffers

  return lRet;
} // sdi_graph::SramBuffersAllocate()

//****************************************************************************

void sdi_graph::SramBuffersFree()
{
  // free all sram buffers
  for(uint32_t i = 0; i < mpMeta->mBfrCnt; i++)
  {
    SEQ_Buf_t* lpCurrBuff = (SEQ_Buf_t*)Off2Packed((uint32_t)mpMeta->mpBufferList[i]);
    
    // free SRAM 
    if(lpCurrBuff->mpBuf != 0)
    {
      uint32_t lPhysAddr =(uint32_t)(lpCurrBuff->mpBuf);
    
      SramFree(lPhysAddr);
          
      // set null to buffer
      lpCurrBuff->mpBuf = 0;
    } // if buffer not NULL
  } // while iterator not at the end 
} // sdi_graph::SramBuffersFree()

//**************************************************************************** 

LIB_RESULT sdi_graph::Finalize()
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // allocate all sram buffers
  if(SramBuffersAllocate() != LIB_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to allocate SRAM buffers.\n");
    lRet = LIB_FAILURE;
  } // if SRAM buffs allocation failed
  else
  {
    // reserve required TCs
    if(FdmaTCsReserve() != LIB_SUCCESS)
    {
      // allocate TC if any used
      VDB_LOG_ERROR("Failed to allocate required Fdma TCs.\n");
      // free SRAM buffers
      lRet = LIB_FAILURE;
    } // if failed to allocate FDMA TCs
  } // else from if SRAM buffs allocation failed
  
  return lRet;
} //sdi_graph::Finalize()

//**************************************************************************** 

void sdi_graph::Free()
{
  FdmaTCsRemove();
  SramBuffersFree();
} // sdi_graph::Free()

//****************************************************************************

LIB_RESULT sdi_graph::SramBufGet(SEQ_Buf_t* apSramBuf, uint32_t &arSramAddr)
{
  LIB_RESULT lRetVal = LIB_SUCCESS;
  SEQ_Buf_t* lpBuf = NULL;
  
  for(uint32_t i = 0; i < mpMeta->mObjCnt; i++)
  {
    if(apSramBuf == mpMeta->mpObjectList[i].mcpAddr)
    {
      lpBuf = (SEQ_Buf_t*) Off2Packed((uint32_t)mpMeta->mpObjectList[i].mcOffset);
    }
  }
  
  if(lpBuf == NULL)
  {
    VDB_LOG_ERROR("Failed to find Buffer pointer in address map.\n");
    lRetVal = LIB_FAILURE;
  } // if buffer not found
  else
  {
    arSramAddr = (uint32_t)(lpBuf->mpBuf);
  } // else from if buffer not found
  
  return lRetVal;
} // SramBufGet()

//****************************************************************************

LIB_RESULT sdi_graph::FdmaTcGet(FDMA_Tc_t& arTc, uint32_t aIdx)
{
  LIB_RESULT aRetVal = LIB_SUCCESS;
  if(mTcs[aIdx] != NULL)
  {
    if(mTcs[aIdx]->mTdm.mReserved)
    {
      // copy TC content
      arTc = *(mTcs[aIdx]);
    } // if reserved
    else
    {
      VDB_LOG_ERROR("Tc at index %u not reserved.\n", (unsigned) aIdx);
      aRetVal = LIB_FAILURE;
    } // else from if reserved      
  } // if TC exists
  else 
  {
    VDB_LOG_ERROR("Channel %u not used in the graph.\n", (unsigned) aIdx);
    aRetVal = LIB_FAILURE;
  } // else form if TC exists  
  
  return aRetVal;
} // FdmaTcGet()

//****************************************************************************

LIB_RESULT sdi_graph::FdmaTcSet(FDMA_Tc_t& arTc, uint32_t aIdx)
{
  LIB_RESULT aRetVal = LIB_SUCCESS;
  if(mTcs[aIdx] != NULL)
  {
    // remember TC content
    *(mTcs[aIdx]) = arTc;
#if 0
    // send to fdma driver
    if(mTcs[aIdx]->mTdm.mReserved)
    {
      //if(ioctl(gFdmaFD, IOCTL_FDMA_TD_CONFIG, mTcs[aIdx]) != FDMA_DRV_SUCCESS) 
      if( FdmaTcConfig(mTcs[aIdx]) != FDMA_LIB_SUCCESS)
      {
        VDB_LOG_ERROR("TcConfig failed.\n");
        aRetVal = LIB_FAILURE;
      } // if ioctl returned failure
    } // if TC reserved allready
    else
    {
      VDB_LOG_ERROR("TC not reserved.\n");
      aRetVal = LIB_FAILURE;
    } // else from if TC reserved allready
#endif // 0
  } // if TC exists
  else 
  {
    VDB_LOG_ERROR("Channel %u not used in the graph.\n", (unsigned) aIdx);
    aRetVal = LIB_FAILURE;
  } // else form if TC exists  
  
  return aRetVal;
} // FdmaTcSet()

//****************************************************************************

FDMA_Tc_t** sdi_graph::FdmaTcsGet(void)
{
  return mTcs;
} // FdmaTcsGet(void)

//****************************************************************************

LIB_RESULT sdi_graph::FdmaTcsApply()
{
  LIB_RESULT aRetVal = LIB_SUCCESS;
  // reserve all prepared TCs    
  for(int32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    if(mTcs[i] != NULL)
    {
      // send to fdma driver
      if(mTcs[i]->mTdm.mReserved)
      {
        //if(ioctl(gFdmaFD, IOCTL_FDMA_TD_CONFIG, mTcs[aIdx]) != FDMA_DRV_SUCCESS) 
        if( FdmaTcIspConfig(mTcs[i]) != FDMA_LIB_SUCCESS)
        {
          VDB_LOG_ERROR("TcConfig failed.\n");
          aRetVal = LIB_FAILURE;
        } // if ioctl returned failure
      } // if TC reserved allready
      else
      {
        VDB_LOG_ERROR("TC not reserved.\n");
        aRetVal = LIB_FAILURE;
      } // else from if TC reserved allready
    } // if TC used
  } // for all possible TCs
  
  return aRetVal;
} // FdmaTcsApply()

//****************************************************************************

SDI_MipiDescriptor sdi_graph::MipiDescGet(enum CSI_IDX aIdx)
{
  SDI_MipiDescriptor lMipiDesc;
  lMipiDesc.mIdx = CSI_IDX_INVALID;
  if( (uint32_t)aIdx < 2 )
  {
    if(mppCsi[aIdx] != NULL)
    {
      lMipiDesc.mIdx        = (enum CSI_IDX) aIdx;
      // get mipi buffer 
      for(uint32_t i = 0; i < MIPI_VIRT_CHN_NUM; i++)
      {
        if((uint32_t)mppCsi[aIdx]->mpOutBuf[i] != 0)
        {
          SEQ_Buf_t* lpMipiBuf  = (SEQ_Buf_t*)(Off2Packed((uint32_t)mppCsi[aIdx]->mpOutBuf[i]));
        
          lMipiDesc.mpVc[i].mBufAddr    = lpMipiBuf->mpBuf;
          lMipiDesc.mpVc[i].mLineCnt    = lpMipiBuf->mcLineMax;
          lMipiDesc.mpVc[i].mLineBytes  = lpMipiBuf->mcLineBytes;
          lMipiDesc.mpVc[i].mLineStride = lpMipiBuf->mcLineStride;
        }
        else
        {
          memset(&lMipiDesc.mpVc[i], 0, sizeof(SDI_MipiDescriptor));
        }
      } // for all used virtual channels
    }
  }
  return lMipiDesc;
} // MipiBufferAddrGet()

//****************************************************************************
LIB_RESULT sdi_graph::IOindexesGet(uint32_t aIOidxs[])
{
  LIB_RESULT lRet = LIB_SUCCESS;
  if(aIOidxs != NULL)
  {
    // reset all indexes
    for (uint32_t i = 0; i < SEQ_OTHRIX_LAST; ++i)
    {
      aIOidxs[i] = SEQ_OTHRIX_LAST;
    } // for all possible IOs
    
    // copy TC content
    if(mpPackedGraph != NULL)
    {
      SEQ_Head_t **lppHeads = (SEQ_Head_t**) mpPackedGraph;
      uint32_t i = 0;
      // for all heads
      while(lppHeads[i] != NULL)
      {
        SEQ_Head_t *lpHead = (SEQ_Head_t*)(((uintptr_t)lppHeads[i]) + (uintptr_t)mpPackedGraph);
        if(lpHead->mcNodeType == SEQ_NODE_OTHER)
        {
          aIOidxs[lpHead->mcEngIndex] = i;
        } // if OTHER engine type
        i++;
      } // while any heady left
    } // if graph packed
    else
    {
      VDB_LOG_WARNING("There is no packed graph at the moment.\n");
    }
  } // if idx array exists
  else 
  {
    VDB_LOG_ERROR("Supplied IO indexes array is NULL.\n");
    lRet = LIB_FAILURE;
  } // else form if idx array exists
  
  return lRet;
} // IOindexesGet(int32_t aIOidxs[])

//****************************************************************************

LIB_RESULT sdi_graph::IoQuery(SEQ_Othr_ix_t aIoNodeId)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if(mIoNodeIdxArr[aIoNodeId] == -1)
  {
    lRet = LIB_FAILURE;
  } // if node not present
  
  return lRet;
} // IOindexesGet(SEQ_Othr_ix_t aIoNodeId)

//****************************************************************************

void sdi_graph::FdmaChannelReorder(void)
{
  if(mpFdma != NULL)
  {
    // get pointer to backed-up FDMA config
    SEQ_FdmaCfg_t *lpFdmaPackedBck = (SEQ_FdmaCfg_t *) mpFdmaPackedBck;
    
    // *** ONLY FOR DEBUG ***
    /*Offset2Addr((uintptr_t)mpPackedGraph);
    SEQ_Head_t **lpHeads = (SEQ_Head_t**)(mpPackedGraph);
    SEQ_IpuCfg_t *pIpuV = (SEQ_IpuCfg_t*)(lpHeads[0]);
    SEQ_IpuCfg_t *pIpuV0 = *((SEQ_IpuCfg_t**)(mpPackedGraph));
    SEQ_IpuCfg_t *pIpuV1 = *((SEQ_IpuCfg_t**)((uint8_t*)mpPackedGraph + 4));
    SEQ_IpuCfg_t *pIpuV2 = *((SEQ_IpuCfg_t**)((uint8_t*)mpPackedGraph + 8));
    SEQ_IpuCfg_t *pIpuV3 = *((SEQ_IpuCfg_t**)((uint8_t*)mpPackedGraph + 12));
    SEQ_FdmaCfg_t *pFdma = *((SEQ_FdmaCfg_t**)((uint8_t*)mpPackedGraph + 16));*/

    // erase FDMA node PRAM copy
    memset(mpFdma->mOutBuf,0, sizeof(SEQ_FdmaDst_t) * FDMA_CHANNELS);
    memset(mpFdma->mInBuf,0, sizeof(SEQ_FdmaSrc_t) * FDMA_CHANNELS);

    // set proper channel numbers
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      if(mTcs[i] != NULL)
      {   
        //VDB_LOG_NOTE("Copying FDMA source channel from idx %u to idx %u.\n", (unsigned) i, (unsigned) mTcs[i]->mTdm.mTdIdx);
        // copy the setup to propper channel num in PRAM version
        memcpy(&(mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx]), &(lpFdmaPackedBck->mInBuf[i]), sizeof(SEQ_FdmaSrc_t));
      
        //VDB_LOG_NOTE("Copying FDMA destination channel from idx %u to idx %u.\n", (unsigned) i, (unsigned) mTcs[i]->mTdm.mTdIdx);
        // copy the setup to propper channel num in PRAM version
        mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx] = lpFdmaPackedBck->mOutBuf[i];
        
        // set proper channel number to consumer object
        // get consumer index to the buffer
        uint32_t lConsIx = mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mcConsIx;
        // get pointer to the buffer
        SEQ_Buf_t *lpSrcBuf = (SEQ_Buf_t*)(Off2Packed((uintptr_t)mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf));
        // set the correct channel Idx
        memcpy((void*)&(lpSrcBuf->mConsumer[lConsIx].mcChann), &(mTcs[i]->mTdm.mTdIdx), 2);      
        
      } // if channel used
    } // for all possible channels
  } // if FDMA used
}

//****************************************************************************

LIB_RESULT sdi_graph::Download(SDI_GraphAddr_t aOffset)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  uintptr_t lGraphCRAM = 0;
  
  if(SEQ_GraphAddressGet(&lGraphCRAM) != LIB_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to get Graph download address.\n");
    lRet = LIB_FAILURE;
  } // if failed to get graph address
  else
  {
    if(SEQ_GRAPH_SIZE_MAX < mpMeta->mGraphSize)
    {
      VDB_LOG_ERROR("Graph too big (0x%x bytes) for the slot (0x%x bytes).\n", 
                    (unsigned) mpMeta->mGraphSize, 
                    (unsigned) (SEQ_GRAPH_SIZE_MAX));
      lRet = LIB_FAILURE;
    } // if graph too big
    else
    {      
      // *** update pointers for future graph location ***
      Offset2Addr((uintptr_t)CRAM_HOST2M0(lGraphCRAM + aOffset));

      //VDB_LOG_NOTE("PRAM space <%x, %x>\n", mpGraphM0, (uint8_t*)mpGraphM0 + 4*1024);
      
      // *** prepare PRAM buffer list (0 termminated) ***
      uint32_t *lpBufferList = (uint32_t*) malloc((mpMeta->mBfrCnt + 1) * sizeof(uint32_t));
      if(lpBufferList != NULL)
      {
        for(uint32_t i = 0; i < mpMeta->mBfrCnt; i++)
        {
          lpBufferList[i] = (uintptr_t)CRAM_HOST2M0(mpMeta->mpBufferList[i] + lGraphCRAM + aOffset);
        } // while iterator not at the end 
        lpBufferList[mpMeta->mBfrCnt] = 0; // set the 0 terminator
        
        // *** generate graph package and download it ***
        SEQ_GraphPackage_t lGraphPackage;
        lGraphPackage.mGraphSize      = mpMeta->mGraphSize;
        lGraphPackage.mpGraphData     = mpPackedGraph;
        lGraphPackage.mBufferListSize = (mpMeta->mBfrCnt + 1) * sizeof(uint32_t);
        lGraphPackage.mpBufferList    = lpBufferList;
        if(mppCsi[0] != NULL)
        {
          lGraphPackage.mCSINumLines  = mppCsi[0]->mcNumInputLines;//mpMeta->mcGraphLimits.mcCSINumLines;
        } // if CSI[0] used
        else
        {
          if(mppCsi[1] != NULL)
          {
            lGraphPackage.mCSINumLines  = mppCsi[1]->mcNumInputLines;//mpMeta->mcGraphLimits.mcCSINumLines;
          } // if CSI[1] used
          else
          {
            lGraphPackage.mCSINumLines  = 0;
          } // else form if CSI[1] used
        } // else from if CSI[0] not used
        
        // download the graph 
        if(SEQ_GraphDownload(&lGraphPackage) != LIB_SUCCESS)
        {
          VDB_LOG_ERROR("Graph download failed.\n");
          lRet = LIB_FAILURE;
        } // if graph download failed
        
        free(lpBufferList);
      } // if buffer list allocated ok
      else
      {
        VDB_LOG_ERROR("Buffer-list allocation for PRAM failed.\n");
        lRet = LIB_FAILURE;
      } // else from if buffer list allocation failed        
      // *** revert from pointers offsets ***
      Addr2Offset((uintptr_t)CRAM_HOST2M0(lGraphCRAM + aOffset));
    } // else from if graph too big
  } // else from if failed to get graph address  
  
  return lRet;
} // sdi_graph::Download(SDI_GraphAddr_t aOffset)

//****************************************************************************

LIB_RESULT sdi_graph::Fetch(SEQ_Head_Ptr_t **appGraph, SEQ_Buf_t ***apppBufferList)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  uintptr_t lGraphCRAM = 0;
  
  
  if(SEQ_GraphAddressGet(&lGraphCRAM) != LIB_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to get Graph download address.\n");
    lRet = LIB_FAILURE;
  } // if failed to get graph address
  else
  {
    if(PRAM_SIZE - (lGraphCRAM - PRAM_BASE) < mpMeta->mGraphSize)
    {
      VDB_LOG_ERROR("Graph too big (0x%x bytes) for the PRAM slot (0x%x bytes).\n", 
                    (unsigned) mpMeta->mGraphSize, 
                    (unsigned) (PRAM_SIZE - (lGraphCRAM - PRAM_BASE)));
      lRet = LIB_FAILURE;
    } // if graph too big
    else
    {   
      // *** prepare Graph memory ***
      mpFetchedGraph = (void*) malloc(mpMeta->mGraphSize);
      *appGraph = (SEQ_Head_Ptr_t*)mpFetchedGraph;
      // *** prepare PRAM buffer list (0 termminated) ***
      mppFetchedBufferList = (SEQ_Buf_t**) malloc((mpMeta->mBfrCnt + 1) * sizeof(SEQ_Buf_t*));
      *apppBufferList = mppFetchedBufferList;
      
      if((*apppBufferList) != NULL)
      { 
        // *** fill in buffer list ***
        for(uint32_t i = 0; i < mpMeta->mBfrCnt; i++)
        {
          (*apppBufferList)[i] = (SEQ_Buf_t*)(mpMeta->mpBufferList[i] + (uintptr_t) mpFetchedGraph);
        } // while iterator not at the end 
        (*apppBufferList)[mpMeta->mBfrCnt] = 0; // set the 0 terminator
        
        // *** generate graph package ***
        SEQ_GraphPackage_t lGraphPackage;
        lGraphPackage.mGraphSize      = mpMeta->mGraphSize;
        lGraphPackage.mpGraphData     = mpFetchedGraph;
        lGraphPackage.mBufferListSize = (mpMeta->mBfrCnt + 1) * sizeof(uint32_t);
        lGraphPackage.mpBufferList    = NULL;
        
        // Fetch the graph 
        if(SEQ_GraphFetch(&lGraphPackage) != LIB_SUCCESS)
        {
          VDB_LOG_ERROR("Graph Upload failed.\n");
          lRet = LIB_FAILURE;
        } // if graph fetch failed
        
        // *** change addresses ***
        Addr2Addr(mpFetchedGraph, (SDI_GraphAddr_t)CRAM_HOST2M0(lGraphCRAM), (SDI_GraphAddr_t)(uintptr_t) mpFetchedGraph);
        
      } // if buffer list allocated ok
      else
      {
        VDB_LOG_ERROR("Buffer-list allocation for PRAM failed.\n");
        lRet = LIB_FAILURE;
      } // else from if buffer list allocation failed        
      
    } // else from if graph too big
   } // else from if failed to get graph address
  
  return lRet;
} // sdi_graph::Fetch(SDI_GraphAddr_t aOffset)

//****************************************************************************

uint32_t sdi_graph::SizeGet(GraphMetadata_t *apMeta)
{
  // *** find out number of engines in the graph
  uint32_t lEngCnt = 0;

  return SizeGet(apMeta, lEngCnt);
} // sdi_graph::SizeEval(SEQ_Head_t *aGraph[], uint32_t &arEngCnt)

//****************************************************************************

uint32_t sdi_graph::SizeGet(GraphMetadata_t *apMeta, uint32_t &arEngCnt)
{
  // *** find out number of engines in the graph
  arEngCnt = 0;
  
  return apMeta->mGraphSize;
} // sdi_graph::SizeEval(GraphMetadata_t *apMeta, uint32_t &arEngCnt)

//****************************************************************************

uint32_t sdi_graph::SizeGet()
{
  return mpMeta->mGraphSize;
} // SizeGet()

//****************************************************************************

LIB_RESULT sdi_graph::Scan()
{
  LIB_RESULT lRes = LIB_SUCCESS;

  // *** go throuhg all defined heads
  while(mpGraph[mHeadCnt] != 0)
  {
    // get pointer to current head from packed graph
    SEQ_Head_t *lpCurrHead = (SEQ_Head_t*)((uint8_t*)mpPackedGraph + (uintptr_t)(mpGraph[mHeadCnt]));
    LIB_RESULT (sdi_graph::*pHeadScan)(SEQ_Head_t*) = NULL;

    switch(lpCurrHead->mcNodeType)
    {
      case SEQ_NODE_SCALAR:
      case SEQ_NODE_VECTOR:
      case SEQ_NODE_FWLOAD:
        break;
      case SEQ_NODE_OTHER:
      {
        // remeber IO node packed index and pointer
        mIoNodeIdxArr[lpCurrHead->mcEngIndex]   = mHeadCnt;
        mpIoNodePtrArr[lpCurrHead->mcEngIndex]  = lpCurrHead;
        
        switch( lpCurrHead->mcEngIndex )
        {
          case SEQ_OTHRIX_FDMA:
          {
            // remember pointer to the FDMA head
            mpFdma = (SEQ_FdmaCfg_t*)lpCurrHead;
            // remember how to scan the head internals
            //pHeadScan = &sdi_graph::FdmaScan;
          } // SEQ_NODE_VECTOR
            break;
          case SEQ_OTHRIX_H264ENC:
          case SEQ_OTHRIX_H264DEC:
          case SEQ_OTHRIX_JPEGDEC:
          case SEQ_OTHRIX_MIPICSI0:
          {
            mppCsi[0] = (SEQ_MipiCfg_t*)lpCurrHead;
          }
            break;
          case SEQ_OTHRIX_MIPICSI1:
          {
            mppCsi[1] = (SEQ_MipiCfg_t*)lpCurrHead;
          }  
            break;
          default:
          {
            VDB_LOG_ERROR("Unknown engine index.\n");
            lRes = LIB_FAILURE;
          } // default
        } // switch engine index
      } // SEQ_NODE_OTHER
        break;
      default:
      {
        VDB_LOG_NOTE("Unknown engine type.\n");
        lRes = LIB_FAILURE;
      } // default
      break;
    } // switch engine type

    // *** scan the head internals ***
    if(pHeadScan != NULL)
    {
      (this->*pHeadScan)(lpCurrHead);
      pHeadScan = NULL;
    } // if specific scan required
    
    mHeadCnt++;
  } // for all heads

  return lRes;
} // sdi_graph::Scan(SEQ_Head_t *apGraph[])

//****************************************************************************

LIB_RESULT sdi_graph::FdmaScan(SEQ_Head_t *apHead)
{
  LIB_RESULT lRes = LIB_SUCCESS;
  SEQ_FdmaCfg_t *lpFdma = (SEQ_FdmaCfg_t*) apHead;
  
  VDB_LOG_NOTE("\n === Fdma Scan === Offset \n\n");  
  
  // remember the FDMA node pointer and original setup
  mpFdma = lpFdma;
  memcpy(mpFdmaPackedBck, lpFdma, sizeof(SEQ_FdmaCfg_t));
  
  return lRes;
} // sdi_graph::FdmaScan(SEQ_Head_t *apHead)

//****************************************************************************

LIB_RESULT sdi_graph::Pack()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  // *** allocate memory for packed graph ***
  mpPackedGraph = malloc(mpMeta->mGraphSize);
  mpPackedObjects = (void*)((uint8_t*)mpPackedGraph + mpMeta->mpObjectList[0].mcOffset);
  
  // *** copy graph objects to predefined offset ***
  ObjectsCopy();
 
  return lRet;
} // sdi_graph::Pack(SEQ_Head_t *aGraph[])

//****************************************************************************

void sdi_graph::ObjectsCopy()
{
  // go through all objects
  for(uint32_t i = 0; i < mpMeta->mObjCnt; i++)
  {
    // prepare r/w addresses
    void *lpWrite = (void*)((uint8_t*)mpPackedGraph + mpMeta->mpObjectList[i].mcOffset);
    const void *lpRead  = mpMeta->mpObjectList[i].mcpAddr;
    
    // copy object
    memcpy(lpWrite,lpRead, mpMeta->mpObjectList[i].mcSize);
  } // for all objects
} // void sdi_graph::ObjectsCopy()

//****************************************************************************

LIB_RESULT sdi_graph::Addr2Offset(SDI_GraphAddr_t aAddrBase)
{
  LIB_RESULT lRes = LIB_SUCCESS;

  SDI_GraphAddr_t *lpCurrPointer = NULL;

  //*** go through all Pointers ***
  for(uint32_t i = 0; i < mpMeta->mPtrCnt; i++)
  {
    // get pointer at offset
    lpCurrPointer = (SDI_GraphAddr_t*)((uintptr_t)mpPackedGraph + mpMeta->mpPointerList[i]);

    // update the pointer
    *lpCurrPointer = (*lpCurrPointer) - aAddrBase;
  } // while iterator not at the end
  
  //*** go through all buffer pointers in FDMA ***
  // FDMA buffer pointers not in the pointer list (can change position)
  if(mpFdma != NULL)
  {
    // for all used TCs
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      if(mTcs[i] != NULL)
      {   
        // update input buffer address
        SDI_GraphAddr_t lNewAddress = ((SDI_GraphAddr_t) mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf) - aAddrBase;
        memcpy((void*)&(mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));
        
        // update output buffer address
        lNewAddress = ((SDI_GraphAddr_t) mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf) - aAddrBase;
        memcpy((void*)&(mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));      
      } // if channel used
    } // for all possible channels
  } // if FDMA used

  return lRes;
} // LIB_RESULT sdi_graph::Addr2Offset()

//****************************************************************************

LIB_RESULT sdi_graph::Addr2Addr(void* apGraph, SDI_GraphAddr_t aOldAddrBase, SDI_GraphAddr_t aNewAddrBase)
{
  LIB_RESULT lRes = LIB_SUCCESS;

  SEQ_Head_Ptr_t *lpCurrPointer = NULL;

  //*** go through all Pointers ***
  for(uint32_t i = 0; i < mpMeta->mPtrCnt; i++)
  {
    // get pointer at offset
    lpCurrPointer = (SEQ_Head_Ptr_t*)((uintptr_t)apGraph + mpMeta->mpPointerList[i]);

    // update the pointer
    *lpCurrPointer = (SEQ_Head_Ptr_t)(((uint32_t)(uintptr_t)(*lpCurrPointer)) - aOldAddrBase + aNewAddrBase);
  } // while iterator not at the end
  
  //*** go through all buffer pointers in FDMA ***
  // FDMA buffer pointers not in the pointer list (can change position)
  if(mpFdma != NULL)
  {
    // for all used TCs
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      if(mTcs[i] != NULL)
      {   
        // update input buffer address
        SDI_GraphAddr_t lNewAddress = ((SDI_GraphAddr_t) mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf) + aNewAddrBase;
        memcpy((void*)&(mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));
        
        // update output buffer address
        lNewAddress = ((SDI_GraphAddr_t) mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf) + aNewAddrBase;
        memcpy((void*)&(mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));      
      } // if channel used
    } // for all possible channels
  } // if FDMA used

  return lRes;
} // LIB_RESULT sdi_graph::Addr2Addr()

//****************************************************************************

LIB_RESULT sdi_graph::Offset2Addr(SDI_GraphAddr_t aAddrBase)
{
  LIB_RESULT lRes = LIB_SUCCESS;

  SDI_GraphAddr_t *lpCurrPointer = NULL;

  //*** go through all Pointers ***
  for(uint32_t i = 0; i < mpMeta->mPtrCnt; i++)
  {
    // get pointer at offset
    lpCurrPointer = (SDI_GraphAddr_t*)((uintptr_t)mpPackedGraph + mpMeta->mpPointerList[i]);

    // update the pointer
    if((*lpCurrPointer) != 0)
    {
      *lpCurrPointer = *lpCurrPointer + aAddrBase;
    }
  } // while iterator not at the end

  //*** go through all buffer pointers in FDMA ***
  // FDMA buffer pointers not in the pointer list (can change position)
  if(mpFdma != NULL)
  {
    // for all used TCs
    for(int32_t i = 0; i < FDMA_CHANNELS; i++)
    {
      if(mTcs[i] != NULL)
      {   
        // update input buffer address
        SDI_GraphAddr_t lNewAddress = (SDI_GraphAddr_t) (mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf);
        lNewAddress += aAddrBase;
        memcpy((void*)&(mpFdma->mInBuf[mTcs[i]->mTdm.mTdIdx].mpInBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));
        
        // update output buffer address
        lNewAddress = ((SDI_GraphAddr_t) mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf) + aAddrBase;
        memcpy((void*)&(mpFdma->mOutBuf[mTcs[i]->mTdm.mTdIdx].mpOutBuf), (void*)&lNewAddress, sizeof(SDI_GraphAddr_t));      
      } // if channel used
    } // for all possible channels
  } // if FDMA used

  return lRes;
} // AddrUpdate(uint32_t aAddrBase)

//****************************************************************************
