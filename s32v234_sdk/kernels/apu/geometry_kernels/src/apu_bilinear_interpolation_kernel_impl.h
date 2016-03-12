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
* \file apu_bilinear_interpolation_kernel_impl.h
* \brief Bilinear interpolation for sub-pixel accuracy
* \addtogroup bilinear_interpolation
* @{
****************************************************************************/

#ifndef _APU_bilinear_interpolation_IMPL_H_
#define _APU_bilinear_interpolation_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_lib.hpp"
using namespace APEX2;
#endif

#define bilinearUpScale		3

/*!
Computes subpixel gray values (i.e. bilinear interpolation) in following way: 
Out(x,y) = [(quotx-xOffs)(quoty-yOffs)In(x,y) + xOffs(quoty-yOffs)In(x+1, y) + yOffs*(quotx-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)
Each chunk has only one xOffs, yOffs and quotx, quoty for a whole bw*bh block
\brief Bilinear interpolation of subpixel gray values with unsigned 8bit indirect inputs and signed 16bit outputs

\param lpvOut	- [Output] signed 16bit pointer to output block
\param lpvIn	- [Input]  unsigned 8bit image source block pointer
\param xOffs	- [Input]  signed 16bit X Offset for the block interpolation (actually the fractional value is xOffs/quot and lies btw [0,1])
\param quotx	- [Input]  unsigned 16bit Quotient for x component of bilinear interpolation
\param yOffs	- [Input]  signed 16bit Y Offset for the block interpolation (actually the fractional value is yOffs/quot and lies btw [0,1])
\param quoty	- [Input]  unsigned 16bit Quotient for y component of bilinear interpolation
\param bw		- [Input]  Source block width
\param bh		- [Input]  Source block height
\param inStrideWidth  - [Input]  Source block width in elements (including padding)
\param outStrideWidth - [Input]  Destination block width in elements (including padding)
*/
void bilinear_interpolation_filter_in08u_out16s(vec16s* lpvOut, vec08u* lpvIn, vec16s* xOffs, vec16u* quotx, vec16s* yOffs, vec16u* quoty, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth);


/*!
Computes subpixel gray values of a unsigned 16bit input image in following way:
Out(x,y) = [(quotx-xOffs)(quoty-yOffs)In(x,y) + xOffs(quoty-yOffs)In(x+1, y) + yOffs*(quotx-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]/(quotx*quoty)
Each chunk has only one xOffs, yOffs and quotx, quoty for a whole bw*bh block

\brief Bilinear interpolation of subpixel gray values with unsigned 16bit indirect inputs and signed 16bit outputs

\param lpvOut	- [Output] signed 16bit pointer to output block
\param lpvIn	- [Input]  unsigned 16bit image source block pointer
\param xOffs	- [Input]  signed 16bit X Offset for the block interpolation (actually the fractional value is xOffs/quot and lies btw [0,1])
\param quotx	- [Input]  unsigned 16bit Quotient for x component of bilinear interpolation
\param yOffs	- [Input]  signed 16bit Y Offset for the block interpolation (actually the fractional value is yOffs/quot and lies btw [0,1])
\param quoty	- [Input]  unsigned 16bit Quotient for y component of bilinear interpolation
\param bw		- [Input] Source block width
\param bh		- [Input] Source block height
\param inStrideWidth  - [Input]  Source block width in elements (including padding)
\param outStrideWidth - [Input]  Destination block width in elements (including padding)
*/
void bilinear_interpolation_filter_in16u_out16s(vec16s* lpvOut, vec16u* lpvIn, vec32s* xOffs, vec32u* quotx, vec32s* yOffs, vec32u* quoty, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth);


/*!
Computes subpixel gray values in following way:
Out(x,y) = [(1-xOffs)(1-yOffs)In(x,y) + xOffs(1-yOffs)In(x+1, y) + yOffs*(1-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]
Each chunk has only one xOffs, yOffs  for a whole bw*bh block

\brief Bilinear interpolation of subpixel gray values with unsigned 16bit indirect inputs and signed 16bit outputs and offsets in fixed point Q3.28 format

\precond		- the xOffs, yOffs are always 1 > x/yOffs > 0 and in a Q3.28 format
\param lpvOut	- [Output] signed 16bit pointer to output
\param lpvIn	- [Input]  unsigned 16bit image source block pointer
\param xOffs	- [Input]  signed 32bit X Offset for the block interpolation (lies btw [0,1] and is in fixed point Q3.28 fractional format)
\param yOffs	- [Input]  signed 32bit Y Offset for the block interpolation (lies btw [0,1] and is in fixed point Q3.28 fractional format)
\param bw		- [Input]  Source block width
\param bh		- [Input]  Source block height
\param inStrideWidth  - [Input]  Source block width in elements (including padding)
\param outStrideWidth - [Input]  Destination block width in elements (including padding)
*/
void bilinear_interpolation_filter_in16u_out16s_Q3_28(vec16s* lpvOut, vec16u* lpvIn, vec32s* xOffs, vec32s* yOffs, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth);


/*!
Computes subpixel gray values in following way:
Out(x,y) = [(1-xOffs)(1-yOffs)In(x,y) + xOffs(1-yOffs)In(x+1, y) + yOffs*(1-xOffs)*In(x, y+1) + xOffs*yOffs*In(x+1,y+1)]
Each chunk has only one xOffs, yOffs  for a whole bw*bh block.  
The inputs are direct and an indirect-inputs simulation is done through the offsets of the blocks, 
which are given in the xPts/yPts vectors and are of size: ACCUM_TILE_SIZE_X/ACCUM_TILE_SIZE_Y constants

\brief Bilinear interpolation of subpixel gray values with unsigned 16bit direct inputs and signed 16bit outputs and offsets in fixed point Q3.28 format

\precond			- the xOffs, yOffs are always 1 > x/yOffs > 0 and in a Q3.28 format
\param lpvOut		- [Output] signed 16bit pointer to output block
\param lpvIn		- [Input]  unsigned 16bit image source block pointer
\param lpvtmpDiv	- [Output] temporary image containing the number of overlapping interpolation bricks for the division of the interpolated values
\param xPts			- [Input]  signed 32bit X coordinate for the left corner of the chunk corresponding with the X/Y Offs vectors
\param yPts			- [Input]  signed 32bit Y coordinate for the left corner of the chunk corresponding with the X/Y Offs vectors
\param xOffs		- [Input]  signed 32bit X Offset for the block interpolation (the fractional value is xOffs/quot and lies btw [0,1] in Q3.28 fixed point format)
\param yOffs		- [Input]  signed 32bit Y Offset for the block interpolation (the fractional value is yOffs/quot and lies btw [0,1] in Q3.28 fixed point format)
\param nrPts		- [Input]  unsigned 16bit nr of points in above four vectors
\param startRow		- [Input]  the starting row of the current tile
\param crtFirstIdx			- [Input]  the starting index in the offset array, such that not all the array has to be scanned at each tile.
\param vIndicesWillBeDone	- [Output] static CU array, storing the last index in the vector which was already processed (for avoiding multiple processing of the same patch
\param accum_a1b1L			- [Temporary] temporary accumulation results wich are passed from one block to the next
\param accum_a1b2L			- [Temporary] temporary accumulation results wich are passed from one block to the next
\param accum_a2b1L			- [Temporary] temporary accumulation results wich are passed from one block to the next
\param accum_a2b2L			- [Temporary] temporary accumulation results wich are passed from one block to the next
\param crtImgWidth			- [Input]  the total width (in nr. of pixels) of the input image
\param bw					- [Input]  Source block width
\param bh					- [Input]  Source block height
\param outCellWidth			- [Input]  Destination block width
\param outCellHeight		- [Input]  Destination block height
\param inStrideWidth		- [Input]  Source block width in elements (including padding)
\param outStrideWidth		- [Input]  Destination block width in elements (including padding)
*/
void bilinear_interpolation_withOffsPar_filter_in16u_out16s_Q3_28(vec16s* lpvOut, vec16u* lpvIn, vec08u*lpvtmpDiv, int32s* xPts, int32s* yPts
	, int32s* xOffs, int32s* yOffs, int16u nrPts, int16u startRow, int16u& crtFirstIdx, vec16s& vIndicesWillBeDone
	, vec32u *accum_a1b1L, vec32u *accum_a1b2L, vec32u *accum_a2b1L, vec32u *accum_a2b2L//, int08u* tmpDone
	, int16u crtImgWidth, int16s bw, int16s bh, int16s outCellWidth, int16s outCellHeight, int16s inStrideWidth, int16s outStrideWidth);


#endif // _APU_bilinear_interpolation_IMPL_H_  

/*! @} */
