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

#ifndef _LINKEDLISTUTILITIES_H
#define _LINKEDLISTUTILITIES_H

#include <icp_datatype.h>
#include <stdint.h>

//linked list entry sizes (in words)
#define LLE_SIZE_2D_DMA_XMEM_CMEM 24
#define LLE_SIZE_2D_DMA_MEM_MEM   8
#define LLE_SIZE_MCE              24
#define LLE_SIZE_HRSZ_SIDEBAND    28
#define LLE_SIZE_1D_FILL          8
#define LLE_SIZE_1D_MEM_MEM       8

#define LLE_SIZE_2D_DMA_XMEM_HRSZ (LLE_SIZE_2D_DMA_MEM_MEM + LLE_SIZE_HRSZ_SIDEBAND)
// See ALGO-61 for an explanation as to why these are different sizes
//#define LLE_SIZE_2D_DMA_HRSZ_CMEM LLE_SIZE_2D_DMA_XMEM_CMEM
// 8 + 28, 128-bit aligned, 36.
#define LLE_SIZE_2D_DMA_HRSZ_CMEM 36
#define LLE_SIZE_2D_DMA_CMEM_HRSZ (LLE_SIZE_2D_DMA_XMEM_CMEM + LLE_SIZE_HRSZ_SIDEBAND)

#ifdef __cplusplus
extern "C" {
#endif

void LLE_2DDMATransferConfig_XMEM_CMEM (uint32_t* llBuffer,
                                        ICP_DATATYPE elementDataType,
                                        int32_t elementDimX,
                                        int32_t elementDimY,
                                        int32_t srcAddr,
                                        int32_t dstAddr,
                                        int32_t span,
                                        int32_t tileWidthInChunks,
                                        int32_t chunkWidth,
                                        int32_t chunkHeight,
                                        int32_t chunkSpan,
                                        int32_t cmemAddr,
                                        int32_t startCu);

void LLE_2DDMATransferConfig_XMEM_HRSZ (uint32_t* llBuffer,
                                        ICP_DATATYPE elementDataType,
                                        int32_t elementDimX,
                                        int32_t elementDimY,
                                        int32_t srcAddr,
                                        int32_t dstAddr,
                                        int32_t span,
                                        int32_t width,
                                        int32_t height,
                                        uint32_t *pHrszConfig);

void LLE_2DDMATransferConfig_CMEM_HRSZ (uint32_t* llBuffer,
                                        ICP_DATATYPE elementDataType,
                                        int32_t elementDimX,
                                        int32_t elementDimY,
                                        int32_t srcAddr,
                                        int32_t dstAddr,
                                        int32_t imageWidth,
                                        int32_t tileWidthInChunks,
                                        int32_t chunkWidth,
                                        int32_t chunkHeight,
                                        int32_t chunkSpan,
                                        int32_t cmemAddr,
                                        int32_t startCu,
                                        uint32_t *pHrszConfig);
                                        
void LLE_2DDMATransferConfig_MEM_MEM (uint32_t* llBuffer,
                                      ICP_DATATYPE elementDataType,
                                      int32_t elementDimX,
                                      int32_t elementDimY,
                                      int32_t srcAddr,
                                      int32_t dstAddr,
                                      int32_t srcSpan,
                                      int32_t dstSpan,
                                      int32_t chunkWidth,
                                      int32_t chunkHeight);
                                      
void LLE_3DDMATransferConfig_MEM_MEM ( uint32_t* llBuffer, //size must be >=8 words
                                       ICP_DATATYPE elementDataType,
                                       int32_t elementDimX,
                                       int32_t elementDimY,
                                       int32_t srcAddr,        // XMEM_Addr
                                       int32_t dstAddr,        // XMEM_Addr
                                       int32_t ptrArrayAddr,   // APPLY ON XMEM_Addr
                                       int32_t ptrOffsetVal,   // APPLY ON XMEM_Addr
                                       int32_t span,           // APPLY ON XMEM_Addr
                                       int32_t tileWidthInChunks,
                                       int32_t chunkWidth,
                                       int32_t chunkHeight,
                                       int32_t chunkSpan,
                                       uint8_t lTransferToDmemFlag,
                                       uint8_t lastFlag);

void LLE_3DDMATransferConfig (uint32_t* llBuffer,     //size must be >=24 words
                              ICP_DATATYPE elementDataType,
                              int32_t elementDimX,
                              int32_t elementDimY,
                              int32_t srcAddr,        // XMEM_Addr/ STREAM_OUT0
                              int32_t dstAddr,        // STREAM_IN0/ STREAM_IN1/ XMEM_Addr
                              int32_t ptrArrayAddr,   // OFFSET TABLE (ALIGN32): INCR OFFSET & HOST VIEW
                              int32_t ptrOffsetVal,   // APPLY ON XMEM_Addr
                              int32_t span,           // APPLY ON XMEM_Addr
                              int32_t tileWidthInChunks,
                              int32_t chunkWidth,
                              int32_t chunkHeight,
                              int32_t chunkSpan,
                              int32_t cmemAddr,
                              int32_t startCu,
                              int32_t maskCu_00, int32_t maskCu_32,
                              uint8_t lastFlag);
                              
void LLE_MCETransferConfig (uint32_t* llBuffer, //size must be >=24 words
                            ICP_DATATYPE elementDataType,
                            int32_t elementDimX,
                            int32_t elementDimY,
                            int32_t baseAddr,
                            int32_t ptrArrayAddr,
                            int32_t dstAddr,
                            int32_t srcDataSpan,
                            int32_t tileWidthInChunks,
                            int32_t chunkWidth,
                            int32_t chunkHeight,
                            int32_t chunkSpan,
                            int32_t cmemAddr,
                            int32_t startCu,
                            int32_t maskCu_00, int32_t maskCu_32,
                            uint8_t lastFlag);

void LLE_1D_Fill (uint32_t* llBuffer,  //size must be >=8 words
                  uint32_t dstAddr,    //physical destination address DMA will write to
                  int32_t fillSizeInBytes);

void LLE_1D_MEM_MEM (uint32_t* llBuffer,  //size must be >=8 words
                     uint32_t srcAddr,    //physical source address DMA will read from
                     uint32_t dstAddr,    //physical destination address DMA will write to
                     int32_t transferSizeInBytes);

void LLE_DMA_Finalize(uint32_t* llEntry);

int32_t DoesChunkWidthSatisfyStreamHwLimits(int32_t lChunkWidthInBytes);
int32_t DoesChunkWidthSatisfyMceHwLimits(int32_t lChunkWidthInBytes);

#ifdef __cplusplus
}
#endif


#endif //_LINKEDLISTUTILITIES_H
