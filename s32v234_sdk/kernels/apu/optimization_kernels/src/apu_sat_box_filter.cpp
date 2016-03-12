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
* \file apu_sat_box_filter.cpp
* \addtogroup optimization
* \addtogroup sat_box_filter SAT-based box filter
* \ingroup optimization
* @{
* \brief SAT-based box filter
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif
#include "apu_sat_box_filter.h"


#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
extern const int BOX_64_WIDTH; //= ACCUM_TILE_SIZE_X;
extern const int BOX_64_HEIGHT; //= ACCUM_TILE_SIZE_Y;
extern const int BOX_64_AREA; //= BOX_64_WIDTH * BOX_64_HEIGHT;
extern const int BOX_SIZE;
extern const int BOX_AREA;
#else 
const int ACCUM_TILE_SIZE_X = 8;
const int ACCUM_TILE_SIZE_Y = 8;

const int BOX_64_WIDTH =  ACCUM_TILE_SIZE_X;
const int BOX_64_HEIGHT = ACCUM_TILE_SIZE_Y;
const int BOX_64_AREA = BOX_64_WIDTH * BOX_64_HEIGHT;

#endif


#ifdef ACF_KERNEL_METADATA
#ifdef APEX2_EMULATE
extern const int BOX_SIZE;
extern const int BOX_AREA;
#else 
const int BOX_SIZE = 5;
const int BOX_AREA = (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);
#endif

#ifndef APEX2_EMULATE
static // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
   Box filter using summed area table kernel metadata.
   
   \param SAT_BOX_FILTER_KN			Define for Kernel name
   \param 2							Number of ports
   \param "Port SAT_BOX_FILTER_IN"  Define for name of input summed area table image (unsigned 32bit)
   \param "Port SAT_BOX_FILTER_OUT"	Define for name of output image (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_BOX_FILTER_K) //_kernel_info_sat_box_filter
(
  SAT_BOX_FILTER_KN,
  2,
  __port(__index(0),
    __identifier(SAT_BOX_FILTER_IN),
    __attributes(ACF_ATTR_VEC_IN),
    __spatial_dep(BOX_SIZE + 1, BOX_SIZE, BOX_SIZE + 1, BOX_SIZE),
    __e0_data_type(d32u),
    __e0_size(1, 1),
    __ek_size(1, 1)),
  __port(__index(1),
  __identifier(SAT_BOX_FILTER_OUT),
    __attributes(ACF_ATTR_VEC_OUT),
    __spatial_dep(0,0,0,0),
    __e0_data_type(d08u),
    __e0_size(1, 1),
    __ek_size(1, 1))
);



/*
KERNEL_INFO kernelInfoConcat(SAT_BOX_FILTER_64u_K)
(
SAT_BOX_FILTER_64u_KN,
7,
__port(__index(0),
	__identifier(SAT_BOX_FILTER_KN_64_IN_HIGH),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
	
__port(__index(1),
	__identifier(SAT_BOX_FILTER_KN_64_IN_LOW),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(2),
	__identifier(SAT_BOX_FILTER_KN_64_OFFS_X),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(3),
	__identifier(SAT_BOX_FILTER_KN_64_OFFS_Y),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),


__port(__index(4),
	__identifier(SAT_BOX_FILTER_KN_64_NRPTS),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),


__port(__index(5),
	__identifier(SAT_BOX_FILTER_KN_64_OUT_HIGH),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(6),
	__identifier(SAT_BOX_FILTER_KN_64_OUT_LOW),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT))

);

*/

#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
Box filter using summed area table kernel metadata for signed 64bit direct inputs with specified offsets.

\param SAT_BOX_FILTER_64s_KN				Define for Kernel name
\param 8									Number of ports
\param "Port SAT_BOX_FILTER_KN_64_IN_HIGH"	Define for name of high word of input summed area table image (signed 32bit) 
\param "Port SAT_BOX_FILTER_KN_64_IN_LOW"	Define for name of low word of input summed area table image (unsigned 32bit)
\param "Port SAT_BOX_FILTER_KN_64_OFFS_X"	Define for name of x offset vector for the box filter to be used (signed 32bit)
\param "Port SAT_BOX_FILTER_KN_64_OFFS_Y"	Define for name of y offset vector for the box filter to be used (signed 32bit)
\param "Port SAT_BOX_FILTER_KN_64_NRPTS"	Define for name of scalar defining the number of elements in each of the above two vectors (unsigned 32bit)
\param "Port SAT_BOX_FILTER_KN_64_OUT_HIGH"	Define for name of high word of output image (signed 32bit)
\param "Port SAT_BOX_FILTER_KN_64_OUT_LOW"	Define for name of low word of output image (unsigned 32bit)
\param "Port SAT_BOX_FILTER_KN_64_TMPVECT"	Define for name of special memory block held for data transfer between two tiles (unsigned 8bit)

*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_BOX_FILTER_64s_K)
(
SAT_BOX_FILTER_64s_KN,
8,
__port(__index(0),
__identifier(SAT_BOX_FILTER_KN_64_IN_HIGH),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
__identifier(SAT_BOX_FILTER_KN_64_IN_LOW),
__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(2),
__identifier(SAT_BOX_FILTER_KN_64_OFFS_X),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(3),
__identifier(SAT_BOX_FILTER_KN_64_OFFS_Y),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(4),
	__identifier(SAT_BOX_FILTER_KN_64_NRPTS),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1,1)),

__port(__index(5),
__identifier(SAT_BOX_FILTER_KN_64_OUT_HIGH),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(6),
__identifier(SAT_BOX_FILTER_KN_64_OUT_LOW),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT)),

__port(__index(7),
	__identifier(SAT_BOX_FILTER_KN_64_TMPVECT),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT))

);
#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_sat_box_filter_impl.h"
#include <string.h>

void apu_sat_box_filter(kernel_io_desc lIn0, kernel_io_desc lOut0)
{
  vec32u* lpvIn0 = (vec32u*)lIn0.pMem;
  vec08u* lpvOut0 = (vec08u*)lOut0.pMem;

  sat_box_filter_impl(lpvOut0, lpvIn0, lIn0.chunkWidth, lIn0.chunkHeight, lIn0.chunkSpan, lOut0.chunkSpan);
}

/*

void apu_sat_box_filter_64u_selected_points(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow)
{
	vec32u* lpvInLow = (vec32u*)lInLow.pMem;
	vec32u* lpvInHigh = (vec32u*)lInHigh.pMem;
	int32u* lpvOutHigh = (int32u*)lOutHigh.pMem;
	int32u* lpvOutLow = (int32u*)lOutLow.pMem;
	int32s* lpvOffsX = (int32s*)lOffsX.pMem;
	int32s* lpvOffsY = (int32s*)lOffsY.pMem;

	int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
	int16u lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);

	static int16u crtStartRow;
	static int32u idxFirstCell;

	int16u outCellWidth = 1;//BOX_64_WIDTH;
	int16u outCellHeight = 1;// BOX_64_HEIGHT;


	int32s nrOffsets = *((int32s*) lNrPts.pMem);

	if (lFirstTileFl) {
		crtStartRow = 0;
		idxFirstCell = 0;
		int32u outputSz = sizeof(int32s)* SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH * SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT;
		memset(lpvOutHigh, '\0', outputSz);
		memset(lpvOutLow, '\0', outputSz);
	}

	sat_box_filter_64u_selectedPoints(lpvOutHigh, lpvOutLow, lpvInHigh, lpvInLow, /*lTileWidthInChunks, * /lpvOffsX, lpvOffsY, nrOffsets, crtStartRow, idxFirstCell, lInHigh.chunkWidth, lInHigh.chunkHeight, outCellWidth, outCellHeight, lInHigh.chunkSpan, lOutHigh.chunkSpan);

	crtStartRow += lInLow.chunkHeight;

}
*/


void apu_sat_box_filter_64s_selected_points(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc ltmpDone)
{
	vec32u* lpvInLow = (vec32u*)lInLow.pMem;
	vec32s* lpvInHigh = (vec32s*)lInHigh.pMem;
	int32s* lpvOutHigh = (int32s*)lOutHigh.pMem;
	int32u* lpvOutLow = (int32u*)lOutLow.pMem;
	int32s* lpvOffsX = (int32s*)lOffsX.pMem;
	int32s* lpvOffsY = (int32s*)lOffsY.pMem;
	int08u* tmpDone = (int08u*) ltmpDone.pMem;

	//static vec16s vIndicesWillBeDone;
	static int16u crtStartRow;
	static int32u idxFirstCell;
	int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
	int16u lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
		
	int16u cellWidth = BOX_64_WIDTH;
	int16u cellHeight = BOX_64_HEIGHT;
	
	int nrOffsets = *((int32s*)lNrPts.pMem);
	if (lFirstTileFl) {
		crtStartRow = 0;
		idxFirstCell = 0;
		static int32u vSz = SAT_BOX_FILTER_KN_64_MAX_VECTOR_WIDTH * SAT_BOX_FILTER_KN_64_MAX_VECTOR_HEIGHT;
		int32u outputSz = sizeof(int32s) * vSz;
		memset(lpvOutHigh, '\0', outputSz);
		memset(lpvOutLow, '\0', outputSz);
		//vIndicesWillBeDone = -1;
		memset(tmpDone, '\0', vSz);
	}	

	//sat_box_filter_64s_selectedPoints(lpvOutHigh, lpvOutLow, lpvInHigh, lpvInLow, /*lTileWidthInChunks, * /lpvOffsX, lpvOffsY, nrOffsets, crtStartRow, idxFirstCell, lInHigh.chunkWidth, lInHigh.chunkHeight, cellWidth, cellHeight, lInHigh.chunkSpan, lOutHigh.chunkSpan);
	
	
	sat_box_filterParal_64s_selectedPoints(
		lpvOutHigh, lpvOutLow, lpvInHigh, lpvInLow, lTileWidthInChunks, 
		lpvOffsX, lpvOffsY, nrOffsets, crtStartRow, idxFirstCell, tmpDone,
		lInHigh.chunkWidth, lInHigh.chunkHeight, cellWidth, cellHeight, lInHigh.chunkSpan, lOutHigh.chunkSpan);


	crtStartRow += lInLow.chunkHeight;

}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
