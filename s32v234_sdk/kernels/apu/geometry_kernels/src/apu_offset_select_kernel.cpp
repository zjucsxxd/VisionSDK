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
* \file apu_offset_select_kernel.c
* \addtogroup geometry
* \addtogroup offset_select Offset selection
* \ingroup geometry
* @{
* \brief Image patch selection by offset
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA

#include "apu_offset_select_kernel.h"

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
Indirect input kernel metadata. Mimics the indirect input functionality of the APEX, i.e it selects as chunks of the output image the bricks starting at the offsets and having a defined chunk size (NEIGH_X, NEIGH_Y)
Outputs 8bit unsigned selected chunks of input image. The chunk size macro definitions have to be adapted by the user to his/her own need (OFFS_SELECT_KN_SELECTION_NEIGH_X, OFFS_SELECT_KN_SELECTION_NEIGH_Y)
The output chunks are constructed even if the (offset + chunk_size) crosses the limit of the current chunk/tile.

\param  OFFS_SELECT_KN					Define for Kernel name
\param 4								Number of ports
\param "Port OFFS_SELECT_KN_IN"			Define for name of input image (unsigned 8bit)
\param "Port OFFS_SELECT_KN_OUT"		Define for name of output image (unsigned 8bit).
\param "Port OFFS_SELECT_KN_IN_OFFSS"	Define for name of input offset vector (specifying the offset byte (!not element) of the input) (unsigned 32bit). 
\param "Port OFFS_SELECT_KN_IN_NR_OFFSS" Define for name of the number of vector elements (static unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(OFFS_SELECT_K) (
   OFFS_SELECT_KN,
   4,
   __port(__index(0),
          __identifier(OFFS_SELECT_KN_IN),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0), 
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),

   __port(__index(1),
          __identifier(OFFS_SELECT_KN_OUT),
          __attributes(ACF_ATTR_VEC_OUT_STATIC_FIXED),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
		  __e0_size(OFFS_SELECT_KN_SELECTION_NEIGH_X, OFFS_SELECT_KN_SELECTION_NEIGH_Y),
		  __ek_size(1, OFFS_SELECT_KN_OUT_HEIGHT)),

  __port(__index(2),
		  __identifier(OFFS_SELECT_KN_IN_OFFSS),
		  __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
		  __spatial_dep(0,0,0,0), 
		  __e0_data_type(d32u),
		  __e0_size(1, 1),
		  __ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),
	  
	__port(__index(3),
		  __identifier(OFFS_SELECT_KN_IN_NR_OFFSS),
		  __attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
		  __spatial_dep(0, 0, 0, 0),
		  __e0_data_type(d32u),
		  __e0_size(1, 1),
		  __ek_size(1, 1))
);
 
#ifndef APEX2_EMULATE
static
#endif
/****************************************************************************/
/*!
Indirect input kernel metadata. Mimics the indirect input functionality of the APEX, i.e it selects as chunks of the output image the bricks starting at the offsets and having a defined chunk size (NEIGH_X, NEIGH_Y)
Outputs 8bit unsigned selected chunks of input image. The chunk size macro definitions have to be adapted by the user to his/her own need (OFFS_SELECT_KN_SELECTION_NEIGH_X, OFFS_SELECT_KN_SELECTION_NEIGH_Y)
The output chunks are constructed even if the (offset + chunk_size) crosses the limit of the current chunk/tile.

\param  OFFS_SELECT_KN					Define for Kernel name
\param 4								Number of ports
\param "Port OFFS_SELECT_KN_IN"			Define for name of input image (unsigned 8bit)
\param "Port OFFS_SELECT_KN_OUT"		Define for name of output image (unsigned 8bit).
\param "Port OFFS_SELECT_KN_IN_OFFSS"	Define for name of input offset vector (specifying the offset byte (!not element) of the input) (unsigned 32bit).
\param "Port OFFS_SELECT_KN_IN_NR_OFFSS" Define for name of the number of vector elements (static unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(OFFS_SELECT_SORTED_K)(
	OFFS_SELECT_SORTED_KN,
	4,
	__port(__index(0),
	__identifier(OFFS_SELECT_KN_IN),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

	__port(__index(1),
	__identifier(OFFS_SELECT_KN_OUT),
	__attributes(ACF_ATTR_VEC_OUT_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08u),
	__e0_size(OFFS_SELECT_KN_SELECTION_NEIGH_X, OFFS_SELECT_KN_SELECTION_NEIGH_Y),
	__ek_size(1, OFFS_SELECT_KN_OUT_HEIGHT)),

	__port(__index(2),
	__identifier(OFFS_SELECT_KN_IN_OFFSS),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(OFFS_SELECT_KN_MAX_VECTOR_SIZE, 1)),

	__port(__index(3),
	__identifier(OFFS_SELECT_KN_IN_NR_OFFSS),
	__attributes(ACF_ATTR_SCL_IN_STATIC_FIXED),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1))
	);


#endif //#ifdef ACF_KERNEL_METADATA


#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_offset_select_kernel.h"

#include "apu_offset_select_kernel_impl.h"
#include <string.h>

int apu_offset_select(kernel_io_desc lImgInA, kernel_io_desc lImgOut, kernel_io_desc lOffsets, kernel_io_desc lNrOffsets)
{
	vec08u*  lpvImgInA = (vec08u*)lImgInA.pMem;
	vec08u*  lpvImgOut = (vec08u*)lImgOut.pMem;


	int32u nrOffsets = *((int32u*)lNrOffsets.pMem);

	int32u neighX = OFFS_SELECT_KN_SELECTION_NEIGH_X;
	int32u neighY = OFFS_SELECT_KN_SELECTION_NEIGH_Y;

	int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
	int16u lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);

	static int16u crtStartRow = 0;
	if (lFirstTileFl) {
		crtStartRow = 0;
	}

	memset(lpvImgOut, '\0', lImgOut.chunkHeight*lImgOut.chunkSpan*APU_VSIZE);

	int32u* offsets = (int32u*)lOffsets.pMem;

	int16u inSstr = (int16u)lImgInA.chunkSpan / sizeof(int08u);
	int16u outSstr = (int16u)lImgOut.chunkSpan / sizeof(int08u);

	int32s ok = offset_select_filter(lpvImgOut, lImgOut.chunkWidth, lImgOut.chunkHeight, lTileWidthInChunks, lpvImgInA, lTileWidthInChunks * lImgInA.chunkWidth, offsets/*X, offsetsY*/, nrOffsets, neighX, neighY, crtStartRow, lImgInA.chunkWidth, lImgInA.chunkHeight, inSstr, outSstr);

	crtStartRow += lImgInA.chunkHeight;

	return ok;
}


int apu_offset_select_sorted(kernel_io_desc lImgInA, kernel_io_desc lImgOut, kernel_io_desc lOffsets, kernel_io_desc lNrOffsets)
{
   vec08u*  lpvImgInA	= (vec08u*) lImgInA.pMem;
   vec08u*  lpvImgOut	= (vec08u*) lImgOut.pMem;


   int32u nrOffsets = *((int32u*)lNrOffsets.pMem);
 
   int32u neighX = OFFS_SELECT_KN_SELECTION_NEIGH_X; 
   int32u neighY = OFFS_SELECT_KN_SELECTION_NEIGH_Y; 

   int16u lFirstTileFl = ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
   int16u lTileWidthInChunks = ACF_RET_VAR(ACF_VAR_TILE_WIDTH_IN_CHUNKS);
 
   static int16u crtStartRow = 0;
   static int16u idxFirstCell;
   if (lFirstTileFl) {
	   crtStartRow = 0;
	   idxFirstCell = 0;
   }

   memset(lpvImgOut, '\0', lImgOut.chunkHeight*lImgOut.chunkSpan*APU_VSIZE);

   int32u* offsets = (int32u*)lOffsets.pMem;
  
   int16u inSstr = (int16u)lImgInA.chunkSpan / sizeof(int08u);
   int16u outSstr = (int16u)lImgOut.chunkSpan / sizeof(int08u);

   int32s ok = offset_select_filter_sorted(lpvImgOut, lImgOut.chunkWidth, lImgOut.chunkHeight, lTileWidthInChunks, lpvImgInA, lTileWidthInChunks * lImgInA.chunkWidth, offsets/*X, offsetsY*/, nrOffsets, neighX, neighY, crtStartRow, idxFirstCell, lImgInA.chunkWidth, lImgInA.chunkHeight, inSstr, outSstr);

   crtStartRow += lImgInA.chunkHeight;
  
   return ok;
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
