/******************************************************************************
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
 * (INCLUDING, BUT NOT LIMITEDl TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * \file 		sdi_io.cpp
 * \brief 		Dfinitions of SDI input/output objects.
 * \author 		Tomas Babinec
 * \version 		0.1
 * \date 		11-November-2014
 ****************************************************************************/

#ifdef SDI_ECLIPSE_DEF
#define GBO_FILE "GBOpts_APEX2_Pseudo_FPGA_Valid.h"
#endif

#include "s32vs234.h"
#include <unistd.h>
#include <string.h>
#ifndef __STANDALONE__
  #include <sys/mman.h>
#endif // ifndef __STANDALONE__
#include <errno.h>
#include <stdio.h>
#include "sdi.hpp"
#include "sdi_graph.hpp"
#include "vdb_log.h"
#include "oal.h"
#include "oal_extras.h"
#include "oal_process.h"

#include "sram.h"
#include "fdma.h"
#include "seq.h"

//****************************************************************************
// consts
//****************************************************************************

//****************************************************************************
// macros
//****************************************************************************
#define UNUSED(_x) (void)(_x)  // to suppress unused parameter warning

//****************************************************************************
// local variables
//****************************************************************************

//****************************************************************************
// local functions declarations
//****************************************************************************

//****************************************************************************
// static members definition
//****************************************************************************

//****************************************************************************
// methods implementation
//****************************************************************************

//****************************************************************************
// *** SDI_DdrBufferArr ***
//****************************************************************************

SDI_DdrBufferArr::SDI_DdrBufferArr():
      mFdmaTcIdx(FDMA_CHANNELS),
      mCnt(0),
      mpBuffers(NULL),
      mDeallocate(false),
      mDesc()
{
} // SDI_DdrBufferArr()

//****************************************************************************

SDI_DdrBufferArr::SDI_DdrBufferArr(const SDI_DdrBufferArr &arSrc):
      mpBuffers(NULL),
      mDeallocate(false),
      mDesc(arSrc.mDesc)
{
  if(arSrc.mpBuffers != NULL)
  {
    mFdmaTcIdx = arSrc.mFdmaTcIdx;
    mCnt = arSrc.mCnt;
    
    // allocate new buffer address array
    mpBuffers = (uint32_t*) malloc(sizeof(uint32_t) * mCnt);
    if(mpBuffers != NULL)
    {
      for(uint32_t i = 0; i < mCnt; i++)
      {
        mpBuffers[i] = arSrc.mpBuffers[i];
      } // for all buffers
    } // if allocation succeeded
  } // if buffers not NULL
  else
  {
    mFdmaTcIdx = FDMA_CHANNELS;
    mCnt = 0;
    mDesc = GDI_ImageDescriptor();
    mpBuffers = NULL;
  } // else from if buffers not NULL
} // SDI_DdrBufferArr(const SDI_DdrBufferArr &arSrc)

//****************************************************************************

SDI_DdrBufferArr::~SDI_DdrBufferArr()
{
  // free buffers if needed
  Free();
  
  if(mpBuffers != NULL)
  {
    free(mpBuffers);
  } // if buffer address array allocated
  
  mFdmaTcIdx = FDMA_CHANNELS;
  mCnt = 0;
  mDesc = GDI_ImageDescriptor();
  mpBuffers = NULL;
} // SDI_DdrBufferArr()

//****************************************************************************

LIB_RESULT SDI_DdrBufferArr::Allocate(GDI_ImageDescriptor &arDesc, uint32_t aCnt)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if((mCnt == 0) && (aCnt > 0))
  {
    
    mpBuffers = (uint32_t*) malloc(sizeof(uint32_t) * mCnt);
    if(mpBuffers != NULL)
    {
      size_t lMemSize   = arDesc.mHeight * arDesc.mWidthStep;
      
      // allocate buffers & get physical addresses
      for(uint32_t i = 0; i < aCnt; i++)
      {
        void* lpVirt = OAL_MemoryAllocFlag(
                              lMemSize, 
                              OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                              OAL_MEMORY_FLAG_CONTIGUOUS);
        
        if( lpVirt == NULL)
        {
          lRet = LIB_FAILURE;
          break;
        }
        mpBuffers[i] = (uint32_t)(uintptr_t)OAL_MemoryReturnAddress(
                              lpVirt, 
                              ACCESS_PHY); // get physical address

        memset((void*)(uintptr_t)mpBuffers[i], 0, lMemSize);
      } // for all framebuffers
      
      if(lRet != LIB_SUCCESS)
      {
        Free();
      } // if allocation failed
      else
      {
        // remember new config
        mCnt        = aCnt;
        mDesc       = arDesc;
        mDeallocate = true;
      } // else from if allocation failed
    } // if allocation suceeded
    else
    {
      lRet = LIB_FAILURE;
    } // if reallocation failed
    
  } // if not yet allocated
  else
  {
    lRet = LIB_FAILURE;
  } // else from if not yet allocated
  
  return lRet;
} // Allocate()

//****************************************************************************

void SDI_DdrBufferArr::Free()
{
  if(mpBuffers != NULL)
  {
    if(mDeallocate)
    {
      for(uint32_t i = 0; i < mCnt; i++)
      {
        if(mpBuffers[i] != 0)
        {
          OAL_MemoryFree((void*)(uintptr_t)mpBuffers[i]);
        } // if buffer not NULL
      } // for all buffers
    } // if buffers should be deallocated
    
    free(mpBuffers);
    mpBuffers = NULL;
  } // if buffers allocated
  
  mCnt = 0;
  mDesc = GDI_ImageDescriptor();
} // Free()

//***************************************************************************

uint32_t SDI_DdrBufferArr::ChannelIdxGet()
{
  return mFdmaTcIdx;
} // ChannelIdxGet()
  
//***************************************************************************

LIB_RESULT SDI_DdrBufferArr::ChannelIdxSet(uint32_t aFdmaChannelIndex)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  if(aFdmaChannelIndex < FDMA_CHANNELS)
  {
    mFdmaTcIdx = aFdmaChannelIndex;
  } //if valid index 
  else
  {
    lRet = LIB_FAILURE;
  } // else from if valid index
  
  return lRet;
} // ChannelIdxSet(uint32_t aFdmaChannelIndex)

//***************************************************************************

uint32_t SDI_DdrBufferArr::BufferCntGet()
{
  return mCnt;
} // BufferCntGet()

//****************************************************************************

GDI_Image SDI_DdrBufferArr::Query(uint32_t aIdx)
{
  GDI_Image lRet;
  if(aIdx < mCnt)
  {
    lRet.DescriptorSet(mDesc);
    lRet.mData = (uint8_t*)(uintptr_t)mpBuffers[aIdx];
  } // if valid buffer
  
  return lRet;
} // Query(uint32_t aIdx)

//****************************************************************************

LIB_RESULT SDI_DdrBufferArr::AddressArrSet(GDI_ImageDescriptor &arDesc, 
                                           uint32_t *apAddressArr, 
                                           uint32_t aCnt)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if(apAddressArr != NULL)
  {
    // release previous buffers
    Free();
    
    // allocate new address array
    mpBuffers = (uint32_t*) malloc(sizeof(uint32_t) * aCnt);
    if(mpBuffers == NULL)
    {
      lRet  = LIB_FAILURE;
      mCnt  = 0;
      mDesc = GDI_ImageDescriptor();
    } // if reallocation failed
    else
    {
      // remember new setup
      for(uint32_t i = 0; i < aCnt; i++)
      {
        mpBuffers[i] = apAddressArr[i];
      } // for all new addresses
      mCnt  = aCnt;
      mDesc = arDesc;
    } // else from if reallocation failed
    
    mDeallocate = false;
  } // if reallocation required
  
  return lRet;
} // AddressArrSet(GDI_ImageDescriptor &arDesc, uint32_t *apAddressArr, uint32_t aCnt)


//****************************************************************************

// *** sdi_io ***

//****************************************************************************

sdi_io::sdi_io() :
    mTypeIndex(SEQ_OTHRIX_LAST), 
    mpGraph(NULL),
    mResult(LIB_SUCCESS),
    mReserved(false),
    mHeadIndex(-1)    
{

} // sdi_input:sdi_io()

//****************************************************************************

sdi_io::sdi_io(SEQ_Othr_ix_t aIOtype) :
    mTypeIndex(aIOtype),
    mpGraph(NULL),
    mResult(LIB_SUCCESS),
    mReserved(false),
    mHeadIndex(-1)
{

} // sdi_input:sdi_io(SEQ_Other_ix_t aIOix)

//****************************************************************************

sdi_io::sdi_io(SEQ_Othr_ix_t aIOtype, sdi_graph *apGraph) :
    mTypeIndex(aIOtype),
    mpGraph(apGraph),
    mResult(LIB_SUCCESS),
    mReserved(false),
    mHeadIndex(-1)
{

} // sdi_input:sdi_io(SEQ_Other_ix_t aIOix, sdi_graph)

//****************************************************************************

sdi_io::~sdi_io()
{
  mTypeIndex = SEQ_OTHRIX_LAST;
  mpGraph = NULL;
  mResult = LIB_SUCCESS;
  mHeadIndex = -1;
  mReserved = false;
} // sdi_input::~sdi_input()

//****************************************************************************

// *** sdi_FdmaIO ***

//****************************************************************************

sdi_FdmaIO::sdi_FdmaIO(): sdi_io(SEQ_OTHRIX_FDMA)
{ 
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    mppBuffArrs[i] = NULL;
  } // for all possible channels
} // sdi_FdmaIO::sdi_FdmaIO()

//****************************************************************************

sdi_FdmaIO::sdi_FdmaIO(sdi_graph *apGraph): sdi_io(SEQ_OTHRIX_FDMA, apGraph)
{ 
  mppTcs = mpGraph->FdmaTcsGet();
 
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
#if 0     
    if(mppTcs[i] != NULL)
    {
      mppBuffArrs[i] = new SDI_DdrBufferArr();
      if(mppBuffArrs[i] == NULL)
      {
        mResult = LIB_FAILURE;
      } // if alloc failed
    } // if channel used
    else
    {
#endif // 0
      mppBuffArrs[i] = NULL;
    //} // else from if channel used
  } // for all possible channels
} // sdi_FdmaIO::sdi_FdmaIO()

//****************************************************************************

LIB_RESULT sdi_FdmaIO::Reserve()
{
  mResult = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return mResult;  
} // sdi_FdmaIO::Reserve()

//****************************************************************************

LIB_RESULT sdi_FdmaIO::Release()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_FdmaIO::Release()
//****************************************************************************

LIB_RESULT sdi_FdmaIO::Setup()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  // finalize TC setup
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    if(mppTcs[i] != NULL)
    {
      // *** request Sequencer DDR buffers ***
      SEQ_BufferRequest_t lSeqBuffRequest;
      lSeqBuffRequest.mStreamIdx   = i;
      lSeqBuffRequest.mCnt         = mppBuffArrs[i]->mCnt;
      lSeqBuffRequest.mBaseShift   = 0;
      lSeqBuffRequest.mBufferSize  = mppBuffArrs[i]->mDesc.mWidthStep * mppBuffArrs[i]->mDesc.mHeight;
      lSeqBuffRequest.mpBuffers    = mppBuffArrs[i]->mpBuffers;
      
      if(SEQ_FrmBuffersRequest(&lSeqBuffRequest) == LIB_SUCCESS)
      {
        // *** query and push buffers ***
        SEQ_FrmBufferInfo_t lBufferInfo;
        lBufferInfo.mBufferIdx = 0;
        lBufferInfo.mStreamIdx = i;
        
        while(SEQ_FrmBufferQuery(&lBufferInfo) == SEQ_DRV_SUCCESS)
        {
          SEQ_FrmBufferPush(&lBufferInfo);
          lBufferInfo.mBufferIdx++;
        } // for all available buffers
        
        // finish setup of appropriate TD
        FDMA_Td_t &lrTD = mppTcs[i]->mTd;
        
        lrTD.mDdrImgStartAddr = mppBuffArrs[i]->mpBuffers[0]; // done by SEQ driver also
        lrTD.mDdrLineStride   = mppBuffArrs[i]->mDesc.mWidthStep/32;
        lrTD.mWrEna           = 1;
        lrTD.mCrcEna          = 0;
        lrTD.mCrcMode         = 0;
        lrTD.mCrcPoly         = 1;
      } // if buffer requested ok
      else
      {
        lRet = LIB_FAILURE;
      } // else from if buffer requested ok
    } // if channel used
  } // for all FDMA_CHANNELS
  
  // aplly TC setup to SRAM TDT
  if(mpGraph->FdmaTcsApply() != LIB_SUCCESS)
  {
    lRet = LIB_FAILURE;
  } // if TCs apply failed
  
  return lRet;  
} // sdi_FdmaIO::Setup()

//***************************************************************************

LIB_RESULT sdi_FdmaIO::Start(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // nothing to be done now
  
  return lRet;
} // sdi_FdmaIO::Start(void)

//***************************************************************************

LIB_RESULT sdi_FdmaIO::Stop(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // nothing to be done now
  
  return lRet;
} // sdi_FdmaIO::Stop(void)

//****************************************************************************

LIB_RESULT sdi_FdmaIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;

  switch(aParamId)
  {
    case SDI_IO_PARAM_DDR_BUF_LIST:
    {      
      if(DdrBuffListSet((SDI_DdrBuffList*) apValue) != LIB_SUCCESS)
      {
        lRet = LIB_FAILURE;
        
        VDB_LOG_ERROR("Failed to set the buffer list.\n");
      } // if DdrBufListSet failed
    }
    break;
    default:
      lRet = LIB_FAILURE;
      VDB_LOG_ERROR("No such parameter.\n");
      break;
  }; // switch aParamId
  
  return lRet;  
} // sdi_FdmaIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_FdmaIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;
} // sdi_FdmaIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_FdmaIO::DdrBufferDescGet(uint32_t aChnlIdx, GDI_ImageDescriptor &arDesc)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if((aChnlIdx < FDMA_CHNL_CNT) && (mppTcs[aChnlIdx] != NULL))
  {
    arDesc.mWidth       = mppTcs[aChnlIdx]->mTd.mLineSize;
    arDesc.mHeight      = mppTcs[aChnlIdx]->mTd.mDdrLineCnt;
    arDesc.mWidthStep   = mppTcs[aChnlIdx]->mTd.mDdrLineStride * 32;
    arDesc.mBpp         = 0;
    arDesc.mPixelFormat = GDI_IMAGE_FORMAT_NONE;
  } // if valid FDMA chnl index
  else
  {
    lRet = LIB_FAILURE;
  } // else from if valid FDMA chanel index
  
  return lRet;
} // DdrBufferDescGet(uint32_t aChnlIdx, GDI_ImageDescriptor arDesc)

//****************************************************************************

LIB_RESULT sdi_FdmaIO::DdrBuffersAlloc(uint32_t aChnlIdx, uint32_t aCnt)
{
  LIB_RESULT lRet = LIB_SUCCESS;

  if(aChnlIdx < FDMA_CHANNELS)
  {
    if(mppBuffArrs[aChnlIdx] != NULL)
    {
      SDI_DdrBufferArr   *lpBuffArr = mppBuffArrs[aChnlIdx];
      GDI_ImageDescriptor lDesc;
      DdrBufferDescGet(aChnlIdx, lDesc); // update the descriptor
      
      if(lpBuffArr->Allocate(lDesc, aCnt) != LIB_SUCCESS)
      {
        lRet = LIB_FAILURE;
      } // if Allocation failed
    } // if channel used
    else
    {
      lRet = LIB_FAILURE;
    } // else from if channel used
  } // if channel index valid  
  else
  {
    lRet = LIB_FAILURE;
  } // else from if channel index valid
  
  return lRet;
}
  
//****************************************************************************
  
LIB_RESULT sdi_FdmaIO::DdrBuffersFree(uint32_t aChnlIdx)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if(aChnlIdx < FDMA_CHANNELS)
  {
    if(mppBuffArrs[aChnlIdx] != NULL)
    {
      mppBuffArrs[aChnlIdx]->Free();
    } // if channel used
    else
    {
      lRet = LIB_FAILURE;
    } // else from if channel used
  } // if channel index valid  
  else
  {
    lRet = LIB_FAILURE;
  } // else from if channel index valid
  
  return lRet;
} // DdrBuffersFree(uint32_t aChnlIdx)
  
//****************************************************************************
  
LIB_RESULT sdi_FdmaIO::DdrBuffersSet(uint32_t aChnlIdx, SDI_DdrBufferArr &arBuffers)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if(aChnlIdx < FDMA_CHANNELS)
  {
    if(mppTcs[aChnlIdx] != NULL)
    {
      if(mppBuffArrs[aChnlIdx] == NULL)
      {
        // remember new buffer array
        mppBuffArrs[aChnlIdx] = (SDI_DdrBufferArr*) new SDI_DdrBufferArr(arBuffers);
        if(mppBuffArrs[aChnlIdx] == NULL)
        {
          lRet = LIB_FAILURE;
        } // if allocation failed
        else
        {
          mppBuffArrs[aChnlIdx]->ChannelIdxSet(aChnlIdx);
        } // else from if allocation failed
      } // if buffer array not assigned yet
      else
      {
        lRet = LIB_FAILURE;
      } // else from if buffer array not assigned yet
    } // if TC used
    else
    {
      lRet = LIB_FAILURE;
    } // else from if TC used
  } // if TC index inbounds
  else
  {
    lRet = LIB_FAILURE;
  } // else from if TC index in bounds
  
  return lRet;
}
  
//****************************************************************************
  
LIB_RESULT sdi_FdmaIO::DdrBufferQuery(uint32_t aChnlIdx, uint32_t aBufferIdx, GDI_Image &arBuffer)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  if(aChnlIdx < FDMA_CHANNELS)
  {
    if(mppBuffArrs[aChnlIdx] != NULL)
    {
      arBuffer = mppBuffArrs[aChnlIdx]->Query(aBufferIdx);
    } // if buffer used
    else 
    {
      lRet = LIB_FAILURE;
    } // else from if buffer used
  } // if valid buffer
  else 
  {
    lRet = LIB_FAILURE;
  } // else from if valid buffer
  
  return lRet;
}

//****************************************************************************

sdi_FdmaIO::~sdi_FdmaIO()
{
  mppTcs = NULL;
  
  for(uint32_t i = 0; i < FDMA_CHANNELS; i++)
  {
    if(mppBuffArrs[i] != NULL)
    {
      delete mppBuffArrs[i];
    } // if channel used
  } // for all possible channels
} // sdi_FdmaIO::~sdi_FdmaIO()

//****************************************************************************
LIB_RESULT sdi_FdmaIO::DdrBuffListSet(SDI_DdrBuffList *apBuffList)
{

  LIB_RESULT lRet = LIB_SUCCESS;
 
  if(apBuffList != NULL)
  {
#if 0 
    // check FDMA channel index is used
    if(mppTcs[apBuffList->mIdx])
    {
      SEQ_BufferList &lrBuffList = mBuffLists[apBuffList->mIdx];
      mTest = 1;
      
      // *** update buffer list storage ***
      
      if(lrBuffList.mpBuffers != NULL)
      {
        // free old addresses
        free(lrBuffList.mpBuffers);
        lrBuffList.mBufferCnt = 0;
        lrBuffList.mBufferIdx = 0;
        lrBuffList.mpBuffers = NULL;
      } // if some addresses set before

      lrBuffList.mpBuffers =(uint32_t*) malloc(sizeof(uint32_t) * apBuffList->mCnt);
      if(lrBuffList.mpBuffers == NULL)
      {
        lRet = LIB_FAILURE;
	
        VDB_LOG_ERROR("Malloc failed.\n");
      } // if malloc failed
      else
      {
        lrBuffList.mBufferCnt = apBuffList->mCnt;
	
        for(uint32_t i = 0; i < apBuffList->mCnt; ++i)
        {
          lrBuffList.mpBuffers[i] = apBuffList->mppBufs[i]->mHwAddress;
        } // for all buffers
        
        // *** setup DDR side of FDMA TD ***
        mppTcs[apBuffList->mIdx]->mTd.mDdrImgStartAddr = apBuffList->mppBufs[0]->mHwAddress;
        mppTcs[apBuffList->mIdx]->mTd.mDdrLineStride = apBuffList->mppBufs[0]->mDesc.mWidthStep;
        mppTcs[apBuffList->mIdx]->mTd.mDdrLineCnt = apBuffList->mppBufs[0]->mDesc.mHeight;
        mppTcs[apBuffList->mIdx]->mTd.mDdrCurrLine = 0;	
    
      } // else from if malloc failed
      
    } // if TC defined
    else
    {
      VDB_LOG_ERROR("No TC defined at index %u.\n", apBuffList->mIdx);
      lRet = LIB_FAILURE;
    } // else from if TC defined
#endif // 0  
  } // if parameter not NULL
  else
  {
    VDB_LOG_ERROR("Buffer list is NULL.\n");
    lRet = LIB_FAILURE;
  } // else from if parameter not NULL

  return lRet;

} // sdi_FdmaIO::DdrBufListSet()

//****************************************************************************

// *** sdi_H264EncIO ***

//****************************************************************************

sdi_H264EncIO::sdi_H264EncIO():sdi_io(SEQ_OTHRIX_H264ENC)
{
  
} // sdi_H264EncIO::sdi_H264EncIO()

//****************************************************************************

LIB_RESULT sdi_H264EncIO::Reserve()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Reserve()

//****************************************************************************

LIB_RESULT sdi_H264EncIO::Release()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Release()
//****************************************************************************

LIB_RESULT sdi_H264EncIO::Setup()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Setup()

//***************************************************************************

LIB_RESULT sdi_H264EncIO::Start(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Start(void)

//***************************************************************************

LIB_RESULT sdi_H264EncIO::Stop(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Stop(void)

//****************************************************************************

LIB_RESULT sdi_H264EncIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_H264EncIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_H264EncIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;
} // sdi_H264EncIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

sdi_H264EncIO::~sdi_H264EncIO()
{
  
} // sdi_H264EncIO::~sdi_H264EncIO()

//****************************************************************************

// *** sdi_H264DecIO ***

//****************************************************************************

sdi_H264DecIO::sdi_H264DecIO():sdi_io(SEQ_OTHRIX_H264DEC)
{
} // sdi_H264DecIO::sdi_H264DecIO()

//****************************************************************************

LIB_RESULT sdi_H264DecIO::Reserve()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Reserve()

//****************************************************************************

LIB_RESULT sdi_H264DecIO::Release()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Release()
//****************************************************************************

LIB_RESULT sdi_H264DecIO::Setup()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Setup()

//***************************************************************************

LIB_RESULT sdi_H264DecIO::Start(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Start(void)

//***************************************************************************

LIB_RESULT sdi_H264DecIO::Stop(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Stop(void)

//****************************************************************************

LIB_RESULT sdi_H264DecIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_H264DecIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_H264DecIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;
} // sdi_H264DecIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

sdi_H264DecIO::~sdi_H264DecIO()
{
  
} // sdi_H264DecIO::~sdi_H264DecIO()

//****************************************************************************

// *** sdi_JpegDecIO ***

//****************************************************************************

sdi_JpegDecIO::sdi_JpegDecIO():sdi_io(SEQ_OTHRIX_JPEGDEC)
{
} // sdi_JpegDecIO::sdi_JpegDecIO()

//****************************************************************************

LIB_RESULT sdi_JpegDecIO::Reserve()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Reserve()

//****************************************************************************

LIB_RESULT sdi_JpegDecIO::Release()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Release()
//****************************************************************************

LIB_RESULT sdi_JpegDecIO::Setup()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::Setup()

//***************************************************************************

LIB_RESULT sdi_JpegDecIO::Start(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Start(void)

//***************************************************************************

LIB_RESULT sdi_JpegDecIO::Stop(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  
  return lRet;
} // sdi_FdmaIO::Stop(void)

//****************************************************************************

LIB_RESULT sdi_JpegDecIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_JpegDecIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_JpegDecIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;
} // sdi_JpegDecIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

sdi_JpegDecIO::~sdi_JpegDecIO()
{
  
} // sdi_JpegDecIO::~sdi_JpegDecIO()

//****************************************************************************

// *** sdi_MipiCsiIO ***

//****************************************************************************

sdi_MipiCsiIO::sdi_MipiCsiIO():sdi_io(SEQ_OTHRIX_MIPICSI0)
{
} // sdi_MipiCsiIO::sdi_MipiCsiIO()

//****************************************************************************

sdi_MipiCsiIO::sdi_MipiCsiIO(sdi_graph *apGraph, enum CSI_IDX aCsiIdx): sdi_io(SEQ_OTHRIX_MIPICSI0, apGraph)
{ 
  mDesc   = mpGraph->MipiDescGet(aCsiIdx);
  if((uint32_t)aCsiIdx == SEQ_OTHRIX_MIPICSI1)
  {
    mTypeIndex = SEQ_OTHRIX_MIPICSI1;
  } // MipiCsi1 interface
} // sdi_MipiCsiIO::sdi_MipiCsiIO()

//****************************************************************************

LIB_RESULT sdi_MipiCsiIO::Reserve()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_MipiCsiIO::Reserve()

//****************************************************************************

LIB_RESULT sdi_MipiCsiIO::Release()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_MipiCsiIO::Release()
//****************************************************************************

LIB_RESULT sdi_MipiCsiIO::Setup()
{
  LIB_RESULT lRet = LIB_SUCCESS;

  // update descriptor to get SRAM buffer address
  mDesc   = mpGraph->MipiDescGet(mDesc.mIdx);

  // get camera geometry
  SONY_Geometry_t lGeom;
  memset(&lGeom, 0, sizeof(SONY_Geometry_t));
  SONY_GeometryGet(CSI_IDX_0, &lGeom);

  // *** initialize CSI receiver ***
      
  CSI_Cfg_t lCsiConfig;
  lCsiConfig.mIdKey.mKey              = 0;
  lCsiConfig.mIdKey.mId.mCsi          = CSI_IDX_0;
  uint32_t lVcIdx                     = 0;
  for(int32_t i = 0; i < MIPI_VIRT_CHN_NUM; i++)
  {
    lCsiConfig.mpVc[i].mBufAddr       = mDesc.mpVc[i].mBufAddr;
    lCsiConfig.mpVc[i].mDoneLineCnt   = 1;
    lCsiConfig.mpVc[i].mLineCnt       = mDesc.mpVc[i].mLineCnt; // buffer lines
    lCsiConfig.mpVc[i].mFrameHeight   = lGeom.mHeight; // buffer lines
    lCsiConfig.mpVc[i].mLineBytes     = mDesc.mpVc[i].mLineBytes;
    lCsiConfig.mpVc[i].mLineStride    = mDesc.mpVc[i].mLineStride;
    
    if(lCsiConfig.mpVc[i].mBufAddr != 0)
    {
      lVcIdx += 1 << i;  // set approriate VC flag
    } // if VC used
  } // for all virtual channels
  
  lCsiConfig.mIdKey.mId.mVc = (enum CSI_VCID)lVcIdx;
  
  // configure the csi receiver
  CSI_Config(&lCsiConfig);
  // TODO: setup IRQ handler
  //CSI_IrqHandlerSet(mDesc.mIdx, CSI_IrqHandler);
  // configure & execute camera
  SONY_RegConfig((CSI_IDX)mDesc.mIdx);
  SONY_CsiEnable((CSI_IDX)mDesc.mIdx);
  
  return lRet;  
} // sdi_MipiCsiIO::Setup()

//***************************************************************************

LIB_RESULT sdi_MipiCsiIO::Start(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // start the camera
  SONY_CsiEnable((CSI_IDX)mDesc.mIdx);
  
  // execute CSI receiver
  CSI_IdKey_t lCsiKey;
  lCsiKey.mKey = 0;  
  CSI_IDX_SET(lCsiKey, mDesc.mIdx);
  CSI_VC_IDX_ADD(lCsiKey, 0);
  CSI_Start(lCsiKey);
  // from now on grabbing continuously in background
  
  return lRet;
} // sdi_FdmaIO::Start(void)

//***************************************************************************

LIB_RESULT sdi_MipiCsiIO::Stop(void)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  CSI_IdKey_t lCsiKey;
  lCsiKey.mKey = 0;  
  CSI_IDX_SET(lCsiKey, mDesc.mIdx);
  CSI_VC_IDX_ADD(lCsiKey, 0);
  CSI_Stop(lCsiKey);
  
  SONY_CsiDisable((CSI_IDX)mDesc.mIdx);
  
  return lRet;
} // sdi_FdmaIO::Stop(void)

//****************************************************************************

LIB_RESULT sdi_MipiCsiIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;  
} // sdi_MipiCsiIO::ParameterSet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

LIB_RESULT sdi_MipiCsiIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)
{
  LIB_RESULT lRet = LIB_SUCCESS;
  
  // TODO: remove unused warning suppression macro
  UNUSED(aParamId);
  UNUSED(apValue);
  
  VDB_LOG_FCN_NOT_IMPLEMENTED();
  return lRet;
} // sdi_MipiCsiIO::ParameterGet(SDI_IO_PARAM aParamId, void *apValue)

//****************************************************************************

SDI_MipiDescriptor sdi_MipiCsiIO::DescriptorGet()
{
  return mDesc;
} // sdi_MipiCsiIO::DescriptorGet()

//****************************************************************************

sdi_MipiCsiIO::~sdi_MipiCsiIO()
{
  
} // sdi_MipiCsiIO::~sdi_MipiCsiIO()