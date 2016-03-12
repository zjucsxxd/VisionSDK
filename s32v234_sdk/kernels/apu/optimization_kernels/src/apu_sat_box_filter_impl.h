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
* \file apu_sat_box_filter_impl.h
* \brief Box filter using SAT implementation for APEX
* \addtogroup sat_box_filter
* @{
****************************************************************************/

#ifndef _APU_SAT_BOX_FILTER_IMPL_H_
#define _APU_SAT_BOX_FILTER_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
extern const int BOX_SIZE; // = 5;
extern const int BOX_AREA; //= (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);

#endif

/****************************************************************************/
/** 
  Applies a box filter (== sum over that patch) to the image using its summed area table (integral
   image).
   
   out(i,j) = in(i - box_size - 1, j - box_size - 1) + in(i + box_size, j + box_size) - in(i - box_size - 1, j + box_size) - in(i + box_size, j - box_size - 1)

\brief Sum of values over one patch
\precondition the input image is a SAT image (i.e. integral computed with the sat32() function
\param apDest		- [Output] 8bit destination image containing sum of values over one patch
\param apcSrc		- [Input]  32bit source block pointer
\param aBlockWidth		- [Input]  Block width
\param aBlockHeight		- [Input]  Block height
\param aSourceStride	- [Input]  Source block width (in bytes) including padding
\param aDestinationStride- [Input]  Destination block width (in bytes) including padding

******************************************************************************/
void sat_box_filter_impl(
  vec08u* apDest,
  const vec32u* apcSrc,
  int aBlockWidth,
  int aBlockHeight,
  int aSourceStride,
  int aDestStride
  );



/*
Computes the unsigned sum of values over one patch, by using the SAT (integral) image computed previously
\brief Sum of values over one patch
\precondition the input image is a SAT image (i.e. integral computed with the sat_in32u_out64u() function, the offsets and the destination are plain vectors and have the same dimensions

\param apDestHigh		- [Output] 32bit high word of the destination image containing sum of values over one patch
\param apDestLow		- [Output] 32bit low word of the destination image containing sum of values over one patch
\param apcSrcHigh		- [Input]  32bit high word of source block pointer 
\param apcSrcLow		- [Input]  32bit low word of source block pointer 
\param offsetsX			- [Input]  32bit X coordinates where the difference shall be made to X+cellWidth
\param offsetsX			- [Input]  32bit Y coordinates where the difference shall be made to X+cellWidth
\param nrOffsets		- [Input]  Scalar value indicating the size of the offsetsX/Y array
\param crtStartRow		- [Input]  Scalar value indicating the starting Y coordinate of the crt stride
\param idxFirstCell		- [Input]  Scalar value indicating the first index in the offsetsX/Y arrays to be processed in the current stride
\param inBlockWidth		- [Input]  Block width
\param inBlockHeight	- [Input]  Block height
\param aSourceStride	- [Input]  Source block width (in bytes) including padding
\param aDestinationStride-[Input]  Destination block width (in bytes) including padding

void sat_box_filter_64u_selectedPoints(int32u* apDestHigh, int32u* apDestLow,
	const vec32u* apcSrcHigh, const vec32u* apcSrcLow, //int16u nrCUs,
	int32s* offsetsX, int32s* offsetsY, 
	int32u nrOffsets, int16u crtStartRow, int32u& idxFirstCell,
	int inBlockWidth, int inBlockHeight, int outCellWidth, int outCellHeight, int aSourceStride, int aDestStride);
*/

/*!
Computes the signed sum of values over one patch, by using the SAT (integral) image computed previously
\brief Sum of values over one patch
\precondition the input image is a SAT image (i.e. integral computed with the sat_in32u_out64u() function, the offsets and the destination are plain vectors and have the same dimensions
\precondition the offsetsX/Y are sorted in ascending order of the Y coordinates

\param apDestHigh		- [Output] 32bit high word of the destination image containing sum of values over one patch
\param apDestLow		- [Output] 32bit low word of the destination image containing sum of values over one patch
\param apcSrcHigh		- [Input]  32bit high word of source block pointer
\param apcSrcLow		- [Input]  32bit low word of source block pointer
\param offsetsX			- [Input]  32bit X coordinates where the difference shall be made to X+cellWidth
\param offsetsX			- [Input]  32bit Y coordinates where the difference shall be made to X+cellWidth
\param nrOffsets		- [Input]  Scalar value indicating the size of the offsetsX/Y array
\param crtStartRow		- [Input]  Scalar value indicating the starting Y coordinate of the crt stride
\param idxFirstCell		- [Input]  Scalar value indicating the first index in the offsetsX/Y arrays to be processed in the current stride
\param inBlockWidth		- [Input]  Block width
\param inBlockHeight	- [Input]  Block height
\param aSourceStride	- [Input]  Source block width (in bytes) including padding
\param aDestinationStride-[Input]  Destination block width (in bytes) including padding
*/
void sat_box_filterParal_64s_selectedPoints(int32s* apDestHigh, int32u* apDestLow,
	const vec32s* apcSrcHigh, const vec32u* apcSrcLow, int16u nrCUs,
	int32s* offsetsX, int32s* offsetsY, int32u nrOffsets, int16u crtStartRow, int32u& idxFirstCell,
	int08u* ltmpDone,
	int32s inBlockWidth, int32s inBlockHeight, int32s outCellWidth, int32s outCellHeight,
	int32s aSourceStride, int32s aDestStride);

#endif // _APU_sat_box_filter_IMPL_H_ 

/*! @} */
