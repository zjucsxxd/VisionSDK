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
 * \file      sdi_graph.hpp
 * \brief     Graph related objects declarations. Depends on GDT 
 *            generated metadata.
 * \author    Tomas Babinec
 * \version   0.1
 * \date      21-October-2014
 ****************************************************************************/

#ifndef SDI_GRAPH_META_HPP_
#define SDI_GRAPH_META_HPP_

#include "sdi_types.hpp"

//#include <vector>
#ifndef __STANDALONE__
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#endif // __STANDALONE__

#include "seq_graph_meta.h"
#include "fdma_types.h"

#include "seq_graph.h"
//#include "sdi_io.hpp"
//#include <map>
//#include <list>

using namespace std;

//****************************************************************************
// contant definitions
//****************************************************************************
#ifdef PRAM_SIZE
#undef PRAM_SIZE
#endif
#define PRAM_SIZE (4*1024)


//****************************************************************************
// types
//****************************************************************************

///< address or offset in graph
typedef uint32_t SDI_GraphAddr_t;

///< host pointer value
typedef uint64_t SDI_HostAddr_t;

//
// preliminary class sdi declarations
class sdi;
//class sdi_grabTask;
//class sdi_grabber;


/***************************************************************************/
/** Describes one graph object (its address and size).
 *
 ***************************************************************************/

#if 0
struct GraphObject
{
  const void* mcpAddr;
  SDI_GraphAddr_t mSize;

  /***************************************************************************/
  /** Constructor.
   *
   ***************************************************************************/
  GraphObject();
  /***************************************************************************/
  /** Constructor.
   *
   * \param apAddr  address of the object
   * \param aSize   size of the object
   ***************************************************************************/
  GraphObject(const void* apAddr, uint32_t aSize);
}; // GraphObject
#endif // if 0

/***************************************************************************/
/** Class encapsulating Sequencer graph handling.
 *
 ***************************************************************************/

class sdi_graph
{
  // *** orig graph data ***
  SEQ_Head_Ptr_t *mpGraph;		///< pointer to original graph structure
  GraphMetadata_t *mpMeta;		///< pointer to graph metadata
  uint32_t mHeadCnt;			///< number of heads in the graph
  
  // *** packed graph data ***
  void*       mpPackedGraph;          ///< pointer to packed graph
  void*       mpPackedObjects;        ///< pointer to first object in packed graph
  void*       mpGraphM0;              ///< pointer to the Graph location for M0
  void*       mpFetchedGraph;         ///< pointer to fetched graph
  SEQ_Buf_t** mppFetchedBufferList;    ///< pointer to fetched buffer list  
  
  FDMA_Tc_t* mTcs[FDMA_CHANNELS];   ///< FDMA channel struct pointers

#if 0 
  // *** graph statistic info *** 
  uint32_t mHeadCnt;
  SDI_GraphAddr_t mCurrOffset;        	///< last download offset used
  list<GraphObject> mObjectList;      	///< list of objects in graph - for packing
  list<SEQ_Buf_t*> mBufferList;       	///< list of SRAM buffers in graph - for packing
  list<SDI_GraphAddr_t> mPointerList;   ///< list of pointer locations (offsets from graph base)
  map<const void*, SDI_GraphAddr_t> mAddressMap;   ///< for pointer updates during graph packing
#endif 

  // *** FDMA node back-up *** 
  SEQ_FdmaCfg_t *mpFdma;		///< original address of the FdmaCfg head
  uint8_t mpFdmaPackedBck[sizeof(SEQ_FdmaCfg_t)];
					///< backup of the packed FdmaCfg head with original TC index assignment
  
  // *** IO nodes packed indexes ***
  int32_t mIoNodeIdxArr[SEQ_OTHRIX_LAST]; //< fast reference to IO nodes
  // *** IO nodes packed pointers ***
  SEQ_Head_t* mpIoNodePtrArr[SEQ_OTHRIX_LAST]; //< fast reference to IO nodes
  
  // *** CSI node shortcut ***
  SEQ_MipiCfg_t *mppCsi[CSI_IF_CNT]; ///< adress of Mipi nodes if present
  

public:
  /***************************************************************************/
  /** Conscturctor.
   *  Sets the structure to empty.
   ***************************************************************************/
  sdi_graph(void);
  
  /***************************************************************************/
  /** Constructor.
   *
   * \param aGraph    the precompiled Sequencer graph
   ***************************************************************************/
  sdi_graph(SEQ_Head_Ptr_t apGraph[], GraphMetadata_t *apMeta);
  
  /***************************************************************************/
  /** Destructor.
   *  Releases allocated resources.
   ***************************************************************************/
  ~sdi_graph(void);

#if 0  
  /***************************************************************************/
  /** Allocats SRAM buffers, reserves FDMA channels.
   *
   * \param arIO the IO object to fetch the configuration into
   * 
   * \return 	LIB_SUCCESS if all ok,
   * 		LIB_FAILURE otherwise
   ***************************************************************************/
  LIB_RESULT IOcfgFetch(sdi_io &arIO);
#endif //0
  
  /***************************************************************************/
  /** Allocats SRAM buffers, reserves FDMA channels.
   *
   * \return 		
   ***************************************************************************/
  LIB_RESULT Finalize();
  
  /***************************************************************************/
  /** Release all reserved resources (FDMA channels & SRAM buffers).
   *
   ***************************************************************************/
  void Free();
  
  /***************************************************************************/
  /** Reorders the FDMA channels in FDMA graph node to fit the allocated TC
   *  indexes.
   *   
   ***************************************************************************/
  void FdmaChannelReorder(void);
  
  /***************************************************************************/
  /** Downloads the graph to the PRAM.
   *
   * \return 		
   ***************************************************************************/
  LIB_RESULT Download(SDI_GraphAddr_t aOffset);
  
  LIB_RESULT Fetch(SEQ_Head_Ptr_t **appGraph, SEQ_Buf_t ***apppBufferList);
  
  /***************************************************************************/
  /** Downloads the graph to the PRAM.
   *
   * \param apMeta   	pointer to graph's metadata
   * \return		size of the graph in bytes.
   ***************************************************************************/
  static uint32_t SizeGet(GraphMetadata_t *apMeta);

  /***************************************************************************/
  /** Computes the PRAM size required for the Graph.
   *
   * \param apMeta pointer to graph's metadata
   * \param apMeta output value with number of engines in the graph
   * \return		size of the graph in bytes.
   ***************************************************************************/
  static uint32_t SizeGet(GraphMetadata_t *apMeta, uint32_t &arEngCnt);

  /***************************************************************************/
  /** Gets the size of the Graph.
   *
   * \return graph size in bytes
   ***************************************************************************/
  uint32_t SizeGet();

  /***************************************************************************/
  /** Gets SRAM address allocated for the given Sram buffer
   *
   * \param apSramBuf Buffer pointer to get.
   * \param arSramAddr Sram addr allocated for the given buffer.   
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT SramBufGet(SEQ_Buf_t* apSramBuf, uint32_t &arSramAddr);
  
  /***************************************************************************/
  /** Gets current setup of TC with given graph index.
   *
   * \param arTc TC structure to be filled with current setup.
   * \param aIdx channel index.
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT FdmaTcGet(FDMA_Tc_t& arTc, uint32_t aIdx);
  
  /***************************************************************************/
  /** Sets the given TC setup to the specified channel index.
   *
   * \param arTc new TC setup.
   * \param aIdx channel index.
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT FdmaTcSet(FDMA_Tc_t& arTc, uint32_t aIdx);
  
  /***************************************************************************/
  /** Gets FDMA TC table.
   *
   * \return pointer to array of preallocated TC pointers.
   *         NULL if FDMA not present in the graph.
   ***************************************************************************/
  FDMA_Tc_t** FdmaTcsGet(void);
  
  /***************************************************************************/
  /** Applys TCs setup to FDMA TDT in SRAM.
   *
   ***************************************************************************/
  LIB_RESULT FdmaTcsApply(void);
  
  /***************************************************************************/
  /** Gets current setup of MIPI CSI node with given index.
   *
   * \param aIdx mipi csi index (0 or 1).
   * \return Mipi csi descriptor, otherwise mIdx member contains > 1
   ***************************************************************************/
  SDI_MipiDescriptor MipiDescGet(enum CSI_IDX aIdx);
  
  /***************************************************************************/
  /** Gets what nodes are present and at which head index.
   *
   * \param[out] aIOs    array of indexes to IO graph nodes. Idx < 0 if not used.
   *
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT IOindexesGet(uint32_t aIOidxs[]);
  
  /***************************************************************************/
  /** Queries for the presence of the IO Node in the graph.
   *
   * \param[out] aIoNodeId ID of the node IO node to be queried
   *
   * \return LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT IoQuery(SEQ_Othr_ix_t aIoNodeId);

private:

  /***************************************************************************/
  /** Transforms the passed graph structure into a packed format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \note Parses the graph and remembers
   *
   * \param apGraph      the precompiled Sequencer graph
   * \param apBuf        array of buffers without producer   
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT Scan();

#if 0  
  /***************************************************************************/
  /** Adds the passed graph head structure into a packed graph format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \param apHead      head of the graph to be scanned
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT IpuScan(SEQ_Head_t *apHead);

  /***************************************************************************/
  /** Adds the passed buffer structure into a packed graph format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \param apBuffer      buffer to be scanned
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT SramBufferScan(SEQ_Buf_t *apBuffer);
#endif // if 0
  /***************************************************************************/
  /** Adds the passed graph head structure into a packed graph format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \param apHead      head of the graph to be scanned
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT FdmaScan(SEQ_Head_t *apHead);

#if 0
  /***************************************************************************/
  /** Adds the passed graph head structure into a packed graph format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \param apHead      head of the graph to be scanned
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT MipiScan(SEQ_Head_t *apHead);
  
  /***************************************************************************/
  /** Adds the passed graph head structure into a packed graph format.
   *  To be able to copy the graph by one memcopy call.
   *
   * \param apHead      head of the graph to be scanned
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT LoadScan(SEQ_Head_t *apHead);
  
#endif // if 0

  /***************************************************************************/
  /** Transforms the passed graph structure in to a packed format.
   *  To be able to copy the graph by one memcopy call.
   * 
   * \note Parses the graph and remembers 
   *
   * \param aGraph    	the precompiled Sequencer graph
   * \return 		LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT Pack();

  /***************************************************************************/
  /** Copies graph objects to packed format.
   *
   * \note Parses the graph and remembers
   *
   ***************************************************************************/
  void ObjectsCopy();

  /***************************************************************************/
  /** Changes pointer values in the packed graph to offsets.
   *
   * \param 	aAddrBase Base address from which to generate the offset.
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT Addr2Offset(uint32_t aAddrBase);

  /***************************************************************************/
  /** Updates pointer addresses in graph to fit future location.
   *
   * \param aAddrBase base address of the packed graph in memory
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT Offset2Addr(uint32_t aAddrBase);
  
  /***************************************************************************/
  /** Updates pointer addresses in graph to fit new location.
   *
   * \param apGraph      pointer to the packed graph copy to be updated
   * \param aOldAddrBase previous base address of the packed graph in memory
   * \param aNewAddrBase new base address of the packed graph in memory
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT Addr2Addr(void* apGraph, 
                       SDI_GraphAddr_t aOldAddrBase, 
                       SDI_GraphAddr_t aNewAddrBase);
  
  /***************************************************************************/
  /** Transforms Internal Graph offset to pointer in packed graph.
   *
   * \return    pointer corresponding to the offset
   * 		NULL if error
   ***************************************************************************/
  inline void *Off2Packed(uint32_t aOffset);
  
  /***************************************************************************/
  /** Generates empty TC for FDMA channels defined in the graph.
   * Sets up already known TD parameters.
   *
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT FdmaTCsPrepare(void);
  
  /***************************************************************************/
  /** Reserves required number of TCs.
   *
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT FdmaTCsReserve(void);
  
  /***************************************************************************/
  /** Releases previously reserved TCs.
   *
   ***************************************************************************/
  void FdmaTCsRelease(void);
  
  
  /***************************************************************************/
  /** Removes TC instances.
   * 
   * Releases the TC if still reserved.
   *
   ***************************************************************************/
  void FdmaTCsRemove(void);
  
  /***************************************************************************/
  /** Allocates all SRAM buffers for this graph.
   *
   * \return    LIB_SUCCESS if all ok, otherwise LIB_FAILURE
   ***************************************************************************/
  LIB_RESULT SramBuffersAllocate(void);
  
  /***************************************************************************/
  /** Releases all SRAM buffers for this graph.
   *
   ***************************************************************************/
  void SramBuffersFree(void);

#if 0  
  /***************************************************************************/
  /** Finds out the actual size of this engine type structure for PRAM.
   *  Counts in size of produced SEQ_Buf_t and parameters.
   *
   * \param apHead  pointer to the engine head
   * \return size of the engine type structure in bytes, -1 if failed
   ***************************************************************************/
  static int32_t SizeOfHead(SEQ_Head_t* apHead);
#endif // if 0  


}; // class sdi_graph

#endif /* SDI_GRAPH_META_HPP_ */
