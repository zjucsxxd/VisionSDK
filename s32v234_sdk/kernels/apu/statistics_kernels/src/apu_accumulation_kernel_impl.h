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
* \file apu_accumulation_kernel_impl.h
* \brief accumulation of values from a chunk
* \addtogroup accumulation
* @{
****************************************************************************/

#ifndef _APU_ACCUMULATION_IMPL_H_
#define _APU_ACCUMULATION_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_lib.hpp"
using namespace APEX2;
#endif

/*!
Accumulates the sum of all signed 32bit values in a chunk. Input is a vector/matrix, output is one sum-value 
\brief Accumulates all values in a chunk (signed 32bit).
\param dst  - [Output] pointer to output accumulation value
\param srcA - [Input]  Source block pointer of img A
\param sstr - [Input]  Source block width in elements (including padding)
\param xOffs - [Input] X Offset where to start accumulation
\param yOffs - [Input] Y Offset where to start accumulation
\param xAccWidth   - [Input]  Width inside block for which accumulation has to be performed
\param yAccHeight   - [Input]  Height inside block for which accumulation has to be performed
*/
void accumulation_in32s_filter(vec32s* dst, vec32s* srcA, int16s sstr, int16s xOffs, int16s yOffs, int16s xAccWidth, int16s yAccHeight);

/*!
Accumulates the sum of all unsigned 32bit values in a chunk. Input is a vector/matrix, output is one sum-value 
\brief Accumulates all values in a chunk (unsigned 32bit).
\param dst  - [Output] pointer to output accumulation value
\param srcA - [Input]  Source block pointer of img A
\param sstr - [Input]  Source block width in elements (including padding)
\param xOffs - [Input] X Offset where to start accumulation
\param yOffs - [Input] Y Offset where to start accumulation
\param xAccWidth   - [Input]  Width inside block for which accumulation has to be performed
\param yAccHeight   - [Input]  Height inside block for which accumulation has to be performed
*/
void accumulation_in32u_filter(vec32u* lpvOut, vec32u* lpvIn, int16s strideWidth, int16s xOffs, int16s yOffs, int16s xAccWidth, int16s yAccHeight);

/*!
Accumulates the sum of all signed 32bit values in a chunk. Input is a vector/matrix, output is one sum-value
\brief Accumulates all values in a chunk (signed 32bit) which is given by the offsets and weights by the box width.
\param dst  - [Output] pointer to signed 32bit output accumulation value
\param srcA - [Input]  signed 32bit source block pointer of img A
\param sstr - [Input]  Source block width in elements (including padding)
\param xOffs - [Input] X Offset where to start accumulation
\param yOffs - [Input] Y Offset where to start accumulation
\param xAccWidth   - [Input]  Width inside block for which accumulation has to be performed
\param yAccHeight   - [Input]  Height inside block for which accumulation has to be performed
*/
void accumulation_in32s_weighted_filter(vec32s* lpvOut, vec32s* lpvIn, int16s strideWidth, int16s xOffs, int16s yOffs, int16s xAccWidth, int16s yAccHeight);


/*!
Accumulates the sum of all unsigned 32bit values in a chunk.Input is a vector / matrix, output is one sum - value
\brief Accumulates all values in a chunk (unsigned 32bit) which is given by the offsets and weights by the box width.
\param dst - [Output] pointer to unsigned 32bit output accumulation value
\param srcA - [Input]  unsigned 32bit source block pointer of img A
\param sstr - [Input]  Source block width in elements(including padding)
\param xOffs - [Input] X Offset where to start accumulation
\param yOffs - [Input] Y Offset where to start accumulation
\param xAccWidth - [Input]  Width inside block for which accumulation has to be performed
\param yAccHeight - [Input]  Height inside block for which accumulation has to be performed
*/
void accumulation_in32u_weighted_filter(vec32u* lpvOut, vec32u* lpvIn, int16s strideWidth, int16s xOffs, int16s yOffs, int16s xAccWidth, int16s yAccHeight);

#endif // _APU_accumulation_IMPL_H_  

/*! @} */
