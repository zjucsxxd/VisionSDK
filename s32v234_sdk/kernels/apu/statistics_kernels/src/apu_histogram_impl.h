
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
/*!
* \file apu_histogram_impl.h
* \brief histogram computation for APEX
* \addtogroup histogram
* @{
****************************************************************************/

#ifndef _APU_HISTOGRAM_IMPL_H_
#define _APU_HISTOGRAM_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/*!
Histogram computation of an input image
\brief Elementwise unsigned 8bit addition => unsigned 16bit 
\param lpvIn0 	 	- [Input]  8bit source block pointer of img 0
\param lpvOut0	 	- [Output] 32 unsigned bit destination block pointer
\param isFirstTile	- [Input]  boolean: true if the algorithm is at its first tile
\param lStride0  	- [Input]  Source block width (in bytes) including padding
\param chunkWidth	- [Input]  Block width
\param chunkHeight	- [Input]  Block height
*/
void hist(vec08u* lpvIn0, vec32u* lpvOut0, bool isFirstTile, int lStrideIn0, int chunkWidth, int chunkHeight, int outChunkWidth);


#endif //#ifdef 

/*! @} */
