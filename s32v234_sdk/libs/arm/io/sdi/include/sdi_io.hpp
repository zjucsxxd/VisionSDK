/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2015 Freescale Semiconductor;
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
 * \file 		sdi_io.hpp
 * \brief 		Declaration of SDI input/output objects.
 * \author 		Tomas Babinec
 * \version 		0.1
 * \date 		11-November-2014
 ****************************************************************************/

#ifndef SDI_IO_HPP_
#define SDI_IO_HPP_

#include <stdint.h>
#include <vector>

#include "oal_task.hpp"
#include "oal_process.h"
#include "gdi_image.hpp"
#include "sdi_graph.hpp"
#include "seq_graph.h"
#include "fdma_types.h"
#include "seq_types.h"
#include "sdi_types.hpp"
#include "csi_public.h"


//#include "sdi_graph.hpp"
#include <map>
#include <list>

using namespace std;

//****************************************************************************
// contant definitions
//****************************************************************************

//****************************************************************************
// types
//****************************************************************************

//
// preliminary class sdi declarations
class sdi;
class sdi_FdmaIO;
class sdi_grabber;

/***************************************************************************/
/** Structure describing one Frame for SDI use.
 *
 ***************************************************************************/
struct SDI_Frame
{
  GDI_Image mImage;
  
  friend sdi_grabber;

private:
   uint32_t mChannelIdx; ///< pointer to array of HW addresses in uint32_t format
   uint32_t mBufferIdx;  ///< true if to be deallocated automatically
}; // SDI_DdrBufList

/***************************************************************************/
/** Structure describing ddr buffer array.
 *
 ***************************************************************************/
struct SDI_DdrBufferArr
{
  uint32_t            mFdmaTcIdx;  ///< index of FDMA TC
  uint32_t            mCnt;        ///< number buffers in the array
  uint32_t           *mpBuffers;   ///< pointer to array of HW addresses in uint32_t format
  bool                mDeallocate; ///< true if to be deallocated automatically
  
  friend sdi_FdmaIO;

public:
  
  GDI_ImageDescriptor mDesc;       ///< buffer image descriptor
  
  /***************************************************************************/
  /** Simple constructor. Address array left empty.
   ***************************************************************************/
  SDI_DdrBufferArr(void);
  
  /***************************************************************************/
  /** Copy constructor. 
   * 
   * Buffer addresses copied from the source object.
   * 
   * \param arSrc source object
   ***************************************************************************/
  SDI_DdrBufferArr(const SDI_DdrBufferArr &arSrc);
  
  /***************************************************************************/
  /** Destructor.
   ***************************************************************************/
  ~SDI_DdrBufferArr(void);
  
  /***************************************************************************/
  /** Allocates DDR buffers described by mDesc and mCnt members.
   *
   * \param  arDesc image descriptor
   * \param  aCnt   number of buffers to be allocated
   * 
   * \return LIB_SUCCESS if all ok
   *         LIB_FAILURE if failed
   ***************************************************************************/
  LIB_RESULT Allocate(GDI_ImageDescriptor &arDesc, uint32_t aCnt);
  
  /***************************************************************************/
  /** Frees allocated memory.
   * 
   * Includes also the DDR buffers if Allocate function was used befor. For
   * buffers provided through Set method only the pointers are removed.
   ***************************************************************************/
  void Free(void);
  
  /***************************************************************************/
  /** Gets index of corresponding FDMA channel.
   * 
   * \return index of corresponding FDMA channel,
   *         FDMA_CHANNELS if no channel assigned
   ***************************************************************************/
  uint32_t ChannelIdxGet(void);
  
  /***************************************************************************/
  /** Sets index of corresponding FDMA channel.
   * 
   * \param aFdmaChannelIndex index of the FDMA channel to be assigned
   * 
   * \return LIB_SUCCESS if ok,
   *         LIB_FAILURE if index out of bounds (>= FDMA_CHANNELS)
   ***************************************************************************/
  LIB_RESULT ChannelIdxSet(uint32_t aFdmaChannelIndex);
  
  /***************************************************************************/
  /** Gets number of contained buffers.
   * 
   * \return number of contained buffers.
   ***************************************************************************/
  uint32_t BufferCntGet(void);
  
  /***************************************************************************/
  /** Gets GDI_Image with requested buffer index.
   * 
   * \return image container with mData member not NULL if buffer exists
   *         otherwise the mData member is set to NULL
   ***************************************************************************/
  GDI_Image Query(uint32_t aIdx);
  
  /***************************************************************************/
  /** Rmembers new set of addresses.
   * 
   * \param arDesc       image descriptor
   * \param apAddressArr array of addresses to be remembered
   * \param aCnt         number of addresses in the array
   *
   * \return LIB_SUCCESS if all ok
   *         LIB_FAILURE if failed
   ***************************************************************************/
  LIB_RESULT AddressArrSet(GDI_ImageDescriptor &arDesc, 
                           uint32_t *apAddressArr, 
                           uint32_t aCnt);
   
}; // SDI_DdrBufList

/***************************************************************************/
/** Class describing a general input or output object.
 *
 ***************************************************************************/
class sdi_io
{
protected:  
  SEQ_Othr_ix_t mTypeIndex; ///< which IO engine type the object stands for
  sdi_graph *mpGraph;       ///< to what graph this io belongs to
  LIB_RESULT mResult;       ///< result of last operation with the object
  
  // TODO: move bool reserved array to shared mem and index it by sensory type ID
  bool mReserved;         ///< is this io reserved? 

  friend class sdi;
    
public:
  int32_t mHeadIndex; ///< index of the corresponding head from a packed graph
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_io();
  
  /***************************************************************************/
  /** Constructor.
   * 
   * \param aIOtype index of the IO type
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_io(SEQ_Othr_ix_t aIOtype);
  
  /***************************************************************************/
  /** Constructor.
   * 
   * \param aIOtype index of the IO type
   * \param apGraph the graph this IO belongs to
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_io(SEQ_Othr_ix_t aIOtype, sdi_graph *apGraph);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  virtual LIB_RESULT Reserve(void) = 0;
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  virtual LIB_RESULT Release(void) = 0;
  
  /***************************************************************************/
  /** Setup IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   * Applies all previously set parameters to the reserved HW block.
   ***************************************************************************/
  virtual LIB_RESULT Setup(void) = 0;
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  virtual LIB_RESULT Start(void) = 0;

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  virtual LIB_RESULT Stop(void) = 0;
  
  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  virtual LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue) = 0;

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  virtual LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue) = 0;
  
  /***************************************************************************/
  /** Remembers result of the last opperation.
   *
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ResultGet(void);

  /***************************************************************************/
  /** Virtual destructor.
   *
   ***************************************************************************/
  virtual ~sdi_io(void);
private:

}; // sdi_io 

/***************************************************************************/
/** Class describing FDMA IO object.
 *
 ***************************************************************************/
class sdi_FdmaIO : sdi_io
{
  //friend class sdi_graph;
  
  FDMA_Tc_t** mppTcs;	///< pointer to FDMA channel struct pointers
  SDI_DdrBufferArr *mppBuffArrs[FDMA_CHANNELS]; ///< storage for buffer arrays
  uint32_t mTest;  

public:
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_FdmaIO(void);
  
  /***************************************************************************/
  /** Constructor based on graph specification.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_FdmaIO(sdi_graph *apGraph);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Reserve(void);
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Release(void);
  
  /***************************************************************************/
  /** Sets Up IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Setup(void);
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Start(void);

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Stop(void);

  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue);
  
  /***************************************************************************/
  /** Gets image descriptor for the specified channel.
   *
   * \param aChnlIdx  index of the corresponding FDMA channel
   * \param arDesc    image descriptor
   * \return  LIB_SUCCESS if all ok, 
   *          LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT DdrBufferDescGet(uint32_t aChnlIdx, GDI_ImageDescriptor &arDesc);
  
  /***************************************************************************/
  /** Allocates required buffers for the channel.
   *
   * \param aChnlIdx  index of the corresponding FDMA channel
   * \param aCnt      number of buffers to be allocated
   * \return  LIB_SUCCESS if all ok, 
   *          LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT DdrBuffersAlloc(uint32_t aChnlIdx, uint32_t aCnt);
  
  /***************************************************************************/
  /** Releases buffer memory allocated for this channel.
   *
   * \param aChnlIdx  index of the corresponding FDMA channel
   * \return  LIB_SUCCESS if all ok, 
   *          LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT DdrBuffersFree(uint32_t aChnlIdx);
  
  /***************************************************************************/
  /** Sets specified buffers to be used by the channel.
   *
   * \param aChnlIdx  index of the corresponding FDMA channel
   * \param arDesc    image descriptor
   * \return  LIB_SUCCESS if all ok, 
   *          LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT DdrBuffersSet(uint32_t aChnlIdx, SDI_DdrBufferArr &arBuffers);
  
  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aChnlIdx  index of the corresponding FDMA channel
   * \param arDesc    image descriptor
   * \return  LIB_SUCCESS if all ok, 
   *          LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT DdrBufferQuery(uint32_t aChnlIdx, uint32_t aBufferIdx, GDI_Image &arBuffer);

  /***************************************************************************/
  /** destructor.
   *
   ***************************************************************************/
   ~sdi_FdmaIO(void);
private:
  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param apBuffList pointer to structure with DDR buffers
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT DdrBuffListSet(SDI_DdrBuffList *apBuffList);
  
}; // sdi_Fdma 

/***************************************************************************/
/** Class describing H264DEC IO object.
 *
 ***************************************************************************/
class sdi_H264DecIO : sdi_io
{

public:
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_H264DecIO(void);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Reserve(void);
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Release(void);
  
  /***************************************************************************/
  /** Sets Up IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Setup(void);
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Start(void);

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Stop(void);

  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** destructor.
   *
   ***************************************************************************/
   ~sdi_H264DecIO(void);
private:

}; // sdi_H264Dec 

/***************************************************************************/
/** Class describing H264ENC IO object.
 *
 ***************************************************************************/
class sdi_H264EncIO : sdi_io
{

public:
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_H264EncIO(void);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Reserve(void);
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Release(void);
  
  /***************************************************************************/
  /** Sets Up IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Setup(void);
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Start(void);

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Stop(void);

  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** destructor.
   *
   ***************************************************************************/
   ~sdi_H264EncIO(void);
private:

}; // sdi_H264Enc 

/***************************************************************************/
/** Class describing JpegDec IO object.
 *
 ***************************************************************************/
class sdi_JpegDecIO : sdi_io
{

public:
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_JpegDecIO(void);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Reserve(void);
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Release(void);
  
  /***************************************************************************/
  /** Sets Up IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Setup(void);
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Start(void);

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
   LIB_RESULT Stop(void);

  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** destructor.
   *
   ***************************************************************************/
   ~sdi_JpegDecIO(void);
private:

}; // sdi_JpegDec 

/***************************************************************************/
/** Class describing H264DEC IO object.
 *
 ***************************************************************************/
class sdi_MipiCsiIO : sdi_io
{
  SDI_MipiDescriptor mDesc;  ///< MIPI setup descriptor

public:
  
  /***************************************************************************/
  /** Constructor.
   *
   * Sets members to default values.
   ***************************************************************************/
  sdi_MipiCsiIO(void);
  
  /***************************************************************************/
  /** Constructor based on graph specification.
   *
   * Sets members to default values.
   * 
   * \param apGraph the graph where the IO exists
   * \param aCsiIdx the index of the csi interface
   ***************************************************************************/
  sdi_MipiCsiIO(sdi_graph *apGraph, enum CSI_IDX aCsiIdx);
  
  /***************************************************************************/
  /** Reserves IO device.
   *
   * HW specific reserve functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Reserve(void);
  
  /***************************************************************************/
  /** Releases IO device.
   *
   * HW specific release functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Release(void);
  
  /***************************************************************************/
  /** Sets Up IO device.
   *
   * HW specific setup functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Setup(void);
  
  /***************************************************************************/
  /** Starts the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Start(void);

  /***************************************************************************/
  /** Stops the IO device operation.
   *
   * HW specific functionality, if any. (to be invoked by SDI library)
   ***************************************************************************/
  LIB_RESULT Stop(void);

  /***************************************************************************/
  /** Sets given value to the specified parameter.
   *
   * \param aParamId  sensor parameter identification
   * \param apValue   pointer to sensor parameter value (might be a structure with all parameters)
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterSet(SDI_IO_PARAM aParamId, void *apValue);

  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \param aParamId    sensor parameter identification
   * \param apValue     pointer to structure where to store parameter values
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT ParameterGet(SDI_IO_PARAM aParamId, void *apValue);
  
  /***************************************************************************/
  /** Gets currently set value of the specified parameter.
   *
   * \return descriptor containing the Csi configuration.
   ***************************************************************************/
  SDI_MipiDescriptor DescriptorGet(void);

  /***************************************************************************/
  /** Destructor.
   *
   ***************************************************************************/
   ~sdi_MipiCsiIO(void);
private:

}; // sdi_MipiCsi 

#endif /* SDI_IO_HPP_ */
