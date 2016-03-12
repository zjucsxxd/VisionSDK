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

#ifndef _ACF_UTILITIES_H
#define _ACF_UTILITIES_H

#include <acf_common.h>
#include <acf_hwutilities.h>
#include <apu2_kernel_port.h> //needed for 'kernel_io_desc'
#include <stdint.h>

void memcpy_int(int* lpSrc, int* lpDst, int lSize); //size is in units of 'ints'
kernel_io_desc RetIoDesc(ACF_LocalMemDesc& lLmDesc, int lIter, int lLmIndex); //only called by resize...
void ACF_CollectVarLengthScatteredLists(int lIter,
                                        ACF_LocalMemDesc lLmDescCmem,
                                        ACF_LocalMemDesc lLmDescDmem,
                                        vec16u lvBytesPushedIntoFifo,
                                        ACF_AdvTransferInfo* lpAdvTransferInfo,
                                        uint32_t* lpTotalFifoSize,
                                        int lStartCu, int lTileWidthInChunks);

/////////////////////////////////////////////////////////////////////////
/// Indicate to ACF that the kernel output 'lIoDescVecBuffer' contains
/// a series of 1D lists of length 'lvVecBufferSize'.
///
/// \param[in] lIoDescVecBuffer
/// The kernel_io_desc associated with the desired ACF_ATTR_VEC_OUT_FIFO port.
///
/// \param[in] lvVecBufferSize
/// A vector containing the 1D list size information in bytes.
///
/// \param lIoDescFifoSize
/// The kernel_io_desc associated with the ACF_ATTR_SCL_OUT_STATIC_FIXED port
/// that will contain the final 1D list size in bytes.
/////////////////////////////////////////////////////////////////////////
void ACF_PUSH_VEC_BUFFER_TO_FIFO(kernel_io_desc lIoDescVecBuffer,
                                 vec16u lvVecBufferSize,
                                 kernel_io_desc lIoDescFifoSize);

/////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function performs padding in CMEM.
/// \param [in] lLM                   Structure which contains the information detailing the layout of CMEM,
///                                       including allocated padding buffer sizes, chunk height
///                                       and width, buffer pointers, number of buffers, and
///                                       e0 information
/// \param [in] lCbIndex              Circular buffer index
/// \param [in] lIter                 The current iteration number.
/// \param [in] lNumIterations        The total number of iterations to be processed.
/// \param [in] lTileWidthInChunks    The width of the processing, in CUS.  Currently, it is assumed
///                                       that the processing starts at CU 0.
/// \param [in] lPadTop               The number of e0's to pad at the top of the chunk.
/// \param [in] lPadBot               The number of e0's to pad at the bottom of the chunk.
/// \param [in] lPadLeft              The number of e0's to pad at the left of the chunk.
/// \param [in] lPadRight             The number of e0's to pad at the right of the chunk.
/// \return
///   No return value is given.
/////////////////////////////////////////////////////////////////////////

/* All 12 padding functions below have this same signature:
void ACF_PAD_##_e0####_L#######R(ACF_LocalMemDesc* lpLM,
                                 int lCbIndex,
                                 int lIter,
                                 int lNumIterations,
                                 int lTileWidthInChunks,
                                 int lPadTop,
                                 int lPadBot,
                                 int lPadLeft,
                                 int lPadRight,
                                 int lPadChOffsetTop,
                                 int lPadChOffsetBot,
                                 int lPadChOffsetLeft,
                                 int lPadChOffsetRight,
                                 int lCuArrayWidth);*/

void ACF_PAD_08_e0xis1_LequaltoR    (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_08_e0xis1_LnotequaltoR (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_08_e0xnot1_LequaltoR   (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_08_e0xnot1_LnotequaltoR(ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_16_e0xis1_LequaltoR    (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_16_e0xis1_LnotequaltoR (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_16_e0xnot1_LequaltoR   (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_16_e0xnot1_LnotequaltoR(ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_32_e0xis1_LequaltoR    (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_32_e0xis1_LnotequaltoR (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_32_e0xnot1_LequaltoR   (ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);
void ACF_PAD_32_e0xnot1_LnotequaltoR(ACF_LocalMemDesc*, int, int, int, int, int, int, int, int, int, int, int, int, int);

/////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function performs circular buffer related padding, in CMEM.
/// \param [in] lLM                   Structure which contains the information detailing the layout of CMEM,
///                                       including allocated padding buffer sizes, chunk height
///                                       and width, buffer pointers, number of buffers, and
///                                       e0 information
/// \param [in] lCbIndex              Circular buffer index
/// \param [in] lIter                 The current iteration number.
/// \param [in] lNumIterations        The total number of iterations to be processed.
/// \param [in] lPadTop               The number of e0 blocks to pad at the top of the chunk.
/// \param [in] lPadBot               The number of e0 blocks to pad at the bottom of the chunk.
/// \param [in] lPadLeft              The number of e0 blocks to pad at the left of the chunk.
/// \param [in] lPadRight             The number of e0 blocks to pad at the right of the chunk.
/// \return
///   No return value is given.
/////////////////////////////////////////////////////////////////////////

void ACF_COPYBUF(ACF_LocalMemDesc* lpLM, int lCbIndex, int lIter, int lNumIterations, int lPadTop, int lPadBot, int lPadLeft, int lPadRight);

int LmInit(ACF_LocalMemDesc* pLmDesc,
           ICP_DATATYPE dataType, int e0x, int e0y,
           int padN, int padS, int padE, int padW,
           int pairedLmIndex,
           acf_scenario_buffer_data* pSenarioBufferData,
           int padOffsetR, int padOffsetRefChunkWidth, int padOffsetB, int padOffsetRetChunkHeight,
           int memTypeFlag); //0=SCL, 1=VEC

void IoDescInit(kernel_io_desc* pIoDesc,
                ACF_LocalMemDesc* pLmDesc,
                int lmIndex);

//---------------------
//INLINE FUNCTIONS
//---------------------

#ifdef CGV_FORCE_INLINE
#define CGV_INLINE_PREFIX inline
#else
#define CGV_INLINE_PREFIX
#endif

CGV_INLINE_PREFIX kernel_io_desc* RetIoDesc(ACF_LocalMemDesc* lpLmDesc, kernel_io_desc* lpKernelIoDesc);
CGV_INLINE_PREFIX void ACF_UpdateTileFlags(int lIter, int lNumIter);

#ifdef CGV_FORCE_INLINE
#include "acf_utilities_inline.h" //include implementations for inline functions
#endif

#endif //_ACF_UTILITIES_H
