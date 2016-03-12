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
* \file apu_sat_box_filter_indirect.cpp
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
#include "apu_sat_box_filter_indirect.h"


#ifdef APEX2_EMULATE
extern const int SAT_TILE_SIZE_X = 8;
extern const int SAT_TILE_SIZE_Y = 8;
extern const int BOX_64_WIDTH;// = SAT_TILE_SIZE_X;
extern const int BOX_64_HEIGHT;// = SAT_TILE_SIZE_Y;
extern const int BOX_64_AREA;// = SAT_TILE_SIZE_X * SAT_TILE_SIZE_Y;
#else 
const int SAT_TILE_SIZE_X = 8;
const int SAT_TILE_SIZE_Y = 8;

const int BOX_64_WIDTH = SAT_TILE_SIZE_X;
const int BOX_64_HEIGHT = SAT_TILE_SIZE_Y;
const int BOX_64_AREA = SAT_TILE_SIZE_X * SAT_TILE_SIZE_Y;


#endif


#ifdef ACF_KERNEL_METADATA
#ifdef APEX2_EMULATE
extern const int BOX_SIZE;
extern const int BOX_AREA;
#else 
const int BOX_SIZE = 5;
const int BOX_AREA = (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);

static  // declare as static only if the code is compiled by the Target compiler
#endif

/****************************************************************************/
/*!
Box filter using summed area table kernel metadata. Does not need indirect inputs.

\param apu_sat_box_filter Kernel name
\param 8                  Number of ports
\param "Port SAT_BOX_FILTER_KERNEL_64_INPUT_HIGH"	Define for name of high signed 32 bit word of input summed area table image
\param "Port SAT_BOX_FILTER_KERNEL_64_INPUT_LOW"	Define for name of low unsigned 32 bit word of input summed area table image
\param "Port SAT_BOX_FILTER_KERNEL_64_OFFS_X"		Define for name of input x offset vector (signed 32bit)
\param "Port SAT_BOX_FILTER_KERNEL_64_OFFS_Y"		Define for name of input y offset vector (signed 32bit)
\param "Port SAT_BOX_FILTER_KERNEL_64_NRPTS"		Define for name of number of points present in the offset vectors (unsigned 32bit)
\param "Port SAT_BOX_FILTER_KERNEL_64_OUTPUT_HIGH"  Define for name of high signed 32 bit word of output image
\param "Port SAT_BOX_FILTER_KERNEL_64_OUTPUT_LOW"	Define for name of low unsigned 32 bit word of output image
\param "Port SAT_BOX_FILTER_KERNEL_64_TMPVECT"		Define for name of temporary vector (memory allocation in the CMEM) (unsigned 8bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_BOX_FILTER_INDIR_64s_K)
(
SAT_BOX_FILTER_INDIR_64s_KN,
8,
__port(__index(0),
__identifier(SAT_BOX_FILTER_KERNEL_64_INPUT_HIGH),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
__identifier(SAT_BOX_FILTER_KERNEL_64_INPUT_LOW),
__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(2),
__identifier(SAT_BOX_FILTER_KERNEL_64_OFFS_X),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT)),

__port(__index(3),
__identifier(SAT_BOX_FILTER_KERNEL_64_OFFS_Y),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT)),

__port(__index(4),
	__identifier(SAT_BOX_FILTER_KERNEL_64_NRPTS),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1,1)),

__port(__index(5),
__identifier(SAT_BOX_FILTER_KERNEL_64_OUTPUT_HIGH),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT)),

__port(__index(6),
__identifier(SAT_BOX_FILTER_KERNEL_64_OUTPUT_LOW),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT)),

__port(__index(7),
	__identifier(SAT_BOX_FILTER_KERNEL_64_TMPVECT),
	__attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH, SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT))

);
#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_sat_box_filter_indirect_impl.h"
#include <string.h>


void apu_sat_box_filter_indirect_64s_selected_points(kernel_io_desc lInHigh, kernel_io_desc lInLow, kernel_io_desc lOffsX, kernel_io_desc lOffsY, kernel_io_desc lNrPts, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc ltmpDone)
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
		static int32u vSz = SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_WIDTH * SAT_BOX_FILTER_KERNEL_64_MAX_VECTOR_HEIGHT;
		int32u outputSz = sizeof(int32s) * vSz;
		memset(lpvOutHigh, '\0', outputSz);
		memset(lpvOutLow, '\0', outputSz);
		//vIndicesWillBeDone = -1;
		memset(tmpDone, '\0', vSz);
	}	

	//sat_box_filter_64s_selectedPoints(lpvOutHigh, lpvOutLow, lpvInHigh, lpvInLow, /*lTileWidthInChunks, * /lpvOffsX, lpvOffsY, nrOffsets, crtStartRow, idxFirstCell, lInHigh.chunkWidth, lInHigh.chunkHeight, cellWidth, cellHeight, lInHigh.chunkSpan, lOutHigh.chunkSpan);
	
	
	sat_box_filterParal_indir_64s_selectedPoints(
		lpvOutHigh, lpvOutLow, lpvInHigh, lpvInLow, lTileWidthInChunks, 
		lpvOffsX, lpvOffsY, nrOffsets, crtStartRow, idxFirstCell, tmpDone,
		lInHigh.chunkWidth, lInHigh.chunkHeight, cellWidth, cellHeight, lInHigh.chunkSpan, lOutHigh.chunkSpan);


	crtStartRow += lInLow.chunkHeight;

}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
