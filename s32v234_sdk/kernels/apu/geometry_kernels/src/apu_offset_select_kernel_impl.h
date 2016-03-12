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
* \file apu_offset_select_kernel_impl.h
* \brief The pixels in a specified neighborhood around a certain offset (offsets are centered in the patch) are selected and copied to a new matrix. 
*        Works similar to IndirectInputs, but leaves pixels at zero, if neighborhoods are out of matrix dimensions
* \addtogroup offset_select
* @{
****************************************************************************/

#ifndef _APU_OFFS_SELECT_KN_IMPL_H_
#define _APU_OFFS_SELECT_KN_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#include "apu_vec.hpp"
using namespace APEX2;
#endif

/*!
* \brief The pixels in a specified neighborhood around a certain offset (offsets are centered in the patch) are selected and copied to a new matrix.
		 Works similar to IndirectInputs, but if patches are out of matrix dimensions, the outside pixels remain zero
\precondition	The array of offsets should be sorted by ascending order of y coordinate
\param dst			- [Output] Destination block pointer
\param nrOutCellsInARow - [Input] total number of cells in the output image (needed to compute the row size in elements in the output image
\param srcA			- [Input]  Source block pointer of img A
\param  crtImgWidth	- [Input] the width of the whole image
\param	offsetsX	- [Input]  the x Coordinates of the points to be selected
\param offsetsY		- [Input]  the y Coordinates of the points to be selected
\param nrOffsets	- [Input]  the number of Coordinates
\param neighX		- [Input]  the X-neighborhood to cut around the coordinates
\param neighY		- [Input]  the Y-neighborhood to cut around the coordinates
\param crtStartRow	- [Input]  the row in the image from where the chunk is extracted
\param idxFirstCell - [Input]  the index in the image from where the chunk is extracted
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inSstr		- [Input]  Source block stride
\param outSstr		- [Input]  Destination block stride (in nr elements, not bytes!)
*/
int32s offset_select_filter_sorted(vec08u* dst, int16u outCellWidth, int16u outCellHeight, int32u nrCUs, vec08u* srcA, int16u crtImgWidth, int32u* offsets, int32u nrOffsets, int32u inCellWidth, int32u inCellHeight, int32u crtStartRow, int16u& idxFirstCell, int16u bw, int16u bh, int16u inSstr, int16u outSstr);



/*!
* \brief The pixels in a specified neighborhood around a certain offset (offsets are centered in the patch) are selected and copied to a new matrix.
Works similar to IndirectInputs, but if patches are out of matrix dimensions, the outside pixels remain zero
\param dst			- [Output] Destination block pointer
\param nrOutCellsInARow - [Input] total number of cells in the output image (needed to compute the row size in elements in the output image
\param srcA			- [Input]  Source block pointer of img A
\param  crtImgWidth	- [Input] the width of the whole image
\param	offsetsX	- [Input]  the x Coordinates of the points to be selected
\param offsetsY		- [Input]  the y Coordinates of the points to be selected
\param nrOffsets	- [Input]  the number of Coordinates
\param neighX		- [Input]  the X-neighborhood to cut around the coordinates
\param neighY		- [Input]  the Y-neighborhood to cut around the coordinates
\param crtStartRow	- [Input]  the row in the image from where the chunk is extracted
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inSstr		- [Input]  Source block stride
\param outSstr		- [Input]  Destination block stride (in nr elements, not bytes!)
*/
int32s offset_select_filter(vec08u* dst, int16u outCellWidth, int16u outCellHeight, int32u nrCUs, vec08u* srcA, int16u crtImgWidth, int32u* offsets, int32u nrOffsets, int32u inCellWidth, int32u inCellHeight, int32u crtStartRow, int16u bw, int16u bh, int16u inSstr, int16u outSstr);

#endif // _APU_offset_select_IMPL_H_  

/*! @} */
