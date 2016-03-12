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

#ifndef _ACF_HWUTILITIES_H
#define _ACF_HWUTILITIES_H

#include <acf_common.h>

//for sequencer hal 'local' override (improved efficiency for ACF)
typedef unsigned int REG32;
#include <apex_642cl_seq_map.h>

//defines associated with sequencer resources
//NOTE: the 'program done' interrupt SEQ_RESOURCE_INTERRUPT_PROGRAM_DONE is defined in ACF_Common.h since it is
//      shared between the host and the ACP
#define SEQ_RESOURCE_DMA_INPUT_LLBUF_AVAIL_DMA   1 //indicates input DMA LL buffer is available for the DMA (kick transfer)
#define SEQ_RESOURCE_DMA_INPUT_DATABUF_AVAIL_APU 2 //indicates input DMA data buffer is available for processing by the APU
#define SEQ_RESOURCE_DMA_INPUT_DATABUF_AVAIL_DMA 3 //indicates DMA input data buffer is available to the DMA to write into

#define SEQ_RESOURCE_MCE_INPUT_LLBUF_AVAIL_MCE   5 //indicates input MCE LL buffer is available for the MCE (kick transfer)
#define SEQ_RESOURCE_MCE_INPUT_DATABUF_AVAIL_APU 6 //indicates input MCE data buffer is available for processing by the APU
#define SEQ_RESOURCE_MCE_INPUT_DATABUF_AVAIL_MCE 7 //indicates MCE input data buffer is available to the MCE to write into

#define SEQ_RESOURCE_OUTPUT_LLBUF_AVAIL_DMA      8 //indicates output DMA LL buffer is available for the DMA (kick SO transfer)
#define SEQ_RESOURCE_OUTPUT_DATABUF_AVAIL_APU    9 //indicates output data buffer is available to the APU to write into

// NB:  These are currently used by custom resize only.  They are placed here so that
// resources are not reused without reconsidering the custom resize design.  These
// values are subject to future review.
#define SEQ_RESOURCE_DMA_HRSZ_SCALER_AVAIL_DMA                  12 //indicates HRSZ scaler hardware is available to the DMA to write to
#define SEQ_RESOURCE_DMA_INPUT_LLBUF_AVAIL_DMA_EXTMEM_TO_HRSZ   13
#define SEQ_RESOURCE_DMA_INPUT_LLBUF_AVAIL_DMA_HRSZ_TO_STREAMIN 14


#define SEQ_RESOURCE_INTERRUPT_STREAMOUT_CNT     29
#define SEQ_RESOURCE_DEBUG_ITER_CNT              31

typedef struct _ACF_AdvTransferInfo
{
   uint16_t lTransferSizeInBytes;   //size of 1D transfer (for cases where transfer size is variable, like variable size list collection)
   uint32_t lTotalBytesTransferred; //keep track of total number of bytes transferred (where to write in external memory if size is not calculated)
} ACF_AdvTransferInfo;

typedef struct _acf_llentry_desc
{
   acf_io_desc* pIoDesc;                  //which 'acf_io_desc' is this entry associated with?
   ACF_LocalMemDesc* pLmDesc;             //which 'ACF_LocalMemDesc' is this entry associated with?
   ACF_AdvTransferInfo* pAdvTransferInfo; //which 'ACF_AdvTransferInfo' is this entry associated with?
   int size;                              //size of the entry in words
   int* pEntry[2];                        //pointer (i.e. address) of the linked list entry and its double buffered counterpart
   int16_t _framework_cbindex;
} acf_llentry_desc;

typedef struct _acf_llentry_mce_desc
{
   acf_io_mce_desc* pIoDesc;  //which 'io_mce_desc' is this entry associated with?
   ACF_LocalMemDesc* pLmDesc; //which 'localmem_desc' is this entry associated with?
   int size;                  //size of the entry in words
   int* pEntry[2];            //pointer (i.e. address) of the linked list entry and its double buffered counterpart
   int16_t _framework_cbindex;
} acf_llentry_mce_desc;

enum
{
   INPUT_TRANSFER,
   OUTPUT_TRANSFER
};

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void ACF_LLE_2DTransferConfig_XMEM_CMEM (int* llBuffer,
                                         e0_desc &e0,
                                         int srcAddr,           //STREAM_OUT1 || STREAM_OUT2 || <some memory address>
                                         int dstAddr,           //STREAM_IN1 || STREAM_IN2 || <some memory address>
                                         int span,              //in bytes (src or dst)
                                         int tileWidthInChunks, //tile width in units of 'chunks'
                                         int chunkWidth,        //in units of e0
                                         int chunkHeight,       //in units of e0
                                         int chunkSpan,         //span of cmem chunk in bytes
                                         int cmemAddr,          //cmem is 16-bit addressable from DMA pov (not 8-bit)
                                         int startCu);          //CU in which the first chunk of the tile is located

void ACF_LLE_2DTransferConfig_MEM_MEM (int* llBuffer,
                                       e0_desc &e0,
                                       int srcAddr,
                                       int dstAddr,
                                       int srcSpan,
                                       int dstSpan,
                                       int chunkWidth,   //in units of e0
                                       int chunkHeight); //in units of e0

void ACF_AppendLLE_DMEM_XMEM(int* lpLinkedListBuf,
                             int* lTransferArray,
                             int  lTransferArraySize,
                             acf_llentry_desc* lpLleDb,
                             int lTransferType,
                             int lLlEntrySizeInWords);

//methods associated with MCE+STI (input only)
void ACF_LLE_MCETransferConfig (int* llBuffer,
                                e0_desc &e0,
                                int baseAddr,          //base address to which ptrs values in table of ptrs will be added (=0 if table of ptrs is absolute)
                                int ptrArrayAddr,      //address of array of pointers
                                int dstAddr,           //STREAM_IN1 || STREAM_IN2
                                int srcDataSpan,       //span of src data
                                int tileWidthInChunks, //tile width in units of 'chunks'
                                int chunkWidth,        //in units of e0
                                int chunkHeight,       //in units of e0
                                int chunkSpan,         //span of cmem chunk in bytes
                                int cmemAddr,          //cmem is 16-bit addressable from DMA pov (not 8-bit)
                                int startCu);          //CU in which the first chunk of the tile is located
                                
void ACF_GenLL_MCE(int* lpLinkedListBuf,          //pointer to linked list buffer
                   int* lTransferArray,           //indicate which DB entries should be added to the linked list
                   int  lTransferArraySize,       //the size of 'lTransferArray' (i.e. number of MCE inputs)
                   acf_llentry_mce_desc* lpLleDb, //pointer to relevant linked list entry database
                   int lNumIterations,            //number of input iterations per IO
                   int lLastTileWidthInChunks);   //width of the last tile in units of chunks

void ACF_XFER_DMEM_XMEM(acf_io_desc& lIoDesc, ACF_LocalMemDesc& lLmDesc, uint32_t lDmaCh, uint32_t lXMEMtoDMEM);
void ACF_2DXFER_XMEM_CMEM(acf_io_desc& lIoDesc,
                          ACF_LocalMemDesc& lLmDesc,
                          uint32_t lDmaCh,
                          uint32_t lStreamCh,
                          uint32_t lXMEMtoCMEM,
                          uint32_t lTileWidthInChunks,
                          uint32_t lStartCu);

void SEQ_INIT_RESOURCE(int lResource, int lValue);
void SEQ_INCREMENT_RESOURCE(int lResource); //for resize
void ACF_InitSeqRegPtr();


struct transfer
{
   int8_t numIdx; //number of LLEs described in idxArray (idx maps to lle db)
   int8_t idxArray[16]; //TODO: hard-coded for now - the max number of LLE that can be concatenated to form a single logical transfer
   int8_t seqResDescAvailDma; //indicates that a descriptor is configured and is available for the DMA (kick logical transfer)
   int8_t seqResBufAvailApu; //indicates input DMA data buffer is available for processing by the APU (logical transfer complete)
   int* lastEntryPtr[2]; //pointers to 'last' entries of double buffered logical transfer (for required 'last' update during execution)
};


int16_t ACF_OrgLogXfer_CmemOnly(int8_t lNumDmaCh,
                                int8_t lNumStreamCh,
                                int8_t lNumTransfers,
                                int8_t* lpNumLogicalTransfers,
                                struct transfer* lpLogicalTransfers);

int16_t ACF_OrgLogXfer_DmemOnly(int8_t lNumDmaCh,
                                int8_t lNumTransfers,
                                int8_t* lpNumLogicalTransfers,
                                struct transfer* lpLogicalTransfers);

int16_t ACF_OrgLogXfer_CmemAndDmem(int8_t lNumDmaCh,
                                   int8_t lNumStreamCh,
                                   int8_t lNumCmemTransfers,
                                   int8_t lNumDmemTransfers,
                                   int8_t* lpNumLogicalTransfersCmem,
                                   struct transfer* lpLogicalTransfersCmem,
                                   int8_t* lpNumLogicalTransfersDmem,
                                   struct transfer* lpLogicalTransfersDmem);

void ConfigureLogicalTransfersDma(int8_t lNumLogicalTransfers,
                                  struct transfer* lpLogicalTransfers,
                                  acf_llentry_desc* lpLleDb,
                                  int8_t* lpDmaCh,
                                  int8_t* lpStreamCh,
                                  int8_t  lType); //0=streamin, 1=streamout, 2=memtomem

void ConfigureLogicalTransfersMce(int8_t lNumLogicalTransfers,
                                  struct transfer* lpLogicalTransfers,
                                  acf_llentry_mce_desc* lpLleDb,
                                  int8_t* lpMceCh,
                                  int8_t* lpStreamCh); //0=streamin, 1=streamout, 2=memtomem

//---------------------
//INLINE FUNCTIONS
//---------------------

#ifdef CGV_FORCE_INLINE
#define CGV_INLINE_PREFIX inline
#else
#define CGV_INLINE_PREFIX
#endif

CGV_INLINE_PREFIX int TransferReq(int* lTransferArray, int  lTransferArraySize);
CGV_INLINE_PREFIX void ACF_FinalizeLL(int* lpLinkedListEntry, int lLastFlag, int lLLBufIndex);
CGV_INLINE_PREFIX void ACF_LleSetLast(int* lpLinkedListEntry);
CGV_INLINE_PREFIX void ACF_LleSetLastMce(int* lpLinkedListEntry);
CGV_INLINE_PREFIX void ACF_AppendLLE_XMEM_CMEM_IN(int* lpLinkedListBuf,
                                int* lTransferArray,        //indicate which DB entries should be added to the linked list
                                int  lTransferArraySize,    //the size of 'lTransferArrayCmem' (i.e. number of transfers)
                                acf_llentry_desc* lpLleDb,  //pointer to relevant linked list entry database
                                int lNumIterations,         //number of input iterations per IO
                                int lLastTileWidthInChunks, //width of the last tile in units of chunks
                                int lLlEntrySizeInWords);
CGV_INLINE_PREFIX void ACF_AppendLLE_XMEM_CMEM_OUT(int* lpLinkedListBuf,
                                 int* lTransferArray,        //indicate which DB entries should be added to the linked list
                                 int  lTransferArraySize,    //the size of 'lTransferArrayCmem' (i.e. number of transfers)
                                 acf_llentry_desc* lpLleDb,  //pointer to relevant linked list entry database
                                 int lIterAdjust,            //adjust index associated with tile in memory (related to tile skip in ROI case)
                                 int lNumIterations,         //number of output iterations per IO
                                 int lLastTileWidthInChunks, //width of the last tile in units of chunks
                                 int lLlEntrySizeInWords);
CGV_INLINE_PREFIX void ACF_seq_hal_proc_inc_rscmask(int lProcId, int lRscMask);
CGV_INLINE_PREFIX void ACF_seq_hal_proc_dec_rscmask(int lProcId, int lRscMask);
CGV_INLINE_PREFIX int  ACF_seq_hal_ret_rsc_counter(int lRsc);
CGV_INLINE_PREFIX void ACF_seq_hal_clear_interrupts(int lMask);
CGV_INLINE_PREFIX void ACF_seq_hal_clear_interrupt(int lProcId);
CGV_INLINE_PREFIX int  ACF_seq_hal_query_interrupts();

extern APEX_642CL_SEQ_DCR volatile * gspSeqRegisters;

#ifdef CGV_FORCE_INLINE
#include "acf_hwutilities_inline.h" //include implementations for inline functions
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_ACF_HWUTILITIES_H
