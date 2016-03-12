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
* \file apu_copy_input_kernel_impl.h
* \brief Copies the input to the output. This for instance useful, when having indirect inputs, then the input matrix is rearranged - and here copied to the output
* \addtogroup of_copy_input
* @{
****************************************************************************/

#ifndef _APU_COPY_INPUT_IMPL_H_
#define _APU_COPY_INPUT_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#include "apu_vec.hpp"
using namespace APEX2;
#endif


/*!
	\brief Copy unsigned 8bit input to unsigned 8bit output. 

	This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

	\param src	- [Input]  unsigned 8bit Source block pointer
	\param out	- [Input]  unsigned 8bit Copy of the input image 
	\param bw   - [Input]  Block width
	\param bh	- [Input]  Block height
	\param sstrIn  - [Input]  Source block stride
	\param sstrOut - [Input]  Destination block stride
*/
void copy_input_in08u_out08u(vec08u* src, vec08u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);


/*!
\brief Copy unsigned 8bit input to unsigned 16bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\param src	- [Input]  unsigned 8bit Source block pointer
\param out	- [Input]  unsigned 16bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input]  Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in08u_out16u(vec08u* src, vec16u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);


/*!
\brief Copy signed 16bit input to signed 16bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\param src	- [Input]  signed 16bit Source block pointer
\param out	- [Input]  signed 16bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input] Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in16s_out16s(vec16s* src, vec16s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);


/*!
\brief Copy unsigned 16bit input to signed 16bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\warning NO OVERFLOW TEST is performed if unsigned data is converted into signed data
\param src	- [Input]  unsigned 16bit Source block pointer
\param out	- [Input]  signed 16bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input] Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in16u_out16s(vec16u* src, vec16s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);


/*!
\brief Copy signed 32bit input to signed 32bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\param src	- [Input]  signed 32bit Source block pointer
\param out	- [Input]  signed 32bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input] Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in32s_out32s(vec32s* src, vec32s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);

/*!
\brief Copy unsigned 32bit input to unsigned 32bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\param src	- [Input]  unsigned 32bit Source block pointer
\param out	- [Input]  unsigned 32bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input] Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in32u_out32u(vec32u* src, vec32u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);

/*!
\brief Copy unsigned 32bit input to signed 32bit output.

This is useful, when input is indirect data, thus matrix dimensions will change and data is reorganized

\warning NO OVERFLOW TEST is performed if unsigned data is converted into signed data
\param src	- [Input]  unsigned 32bit Source block pointer
\param out	- [Input]  signed 32bit Copy of the input image
\param bw   - [Input]  Block width
\param bh   - [Input]  Block height
\param sstrIn  -[Input] Source block stride
\param sstrOut -[Input] Destination block stride
*/
void copy_input_in32u_out32s(vec32u* src, vec32s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut);

#endif // _APU_COPY_INPUT_IMPL_H_  

/*! @} */
