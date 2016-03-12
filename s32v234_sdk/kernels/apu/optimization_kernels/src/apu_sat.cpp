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
* \file apu_sat.cpp
* \addtogroup optimization
* \addtogroup sat Summed area table
* \ingroup optimization
* @{
* \brief Summed area table (integral image) computation
*/
#ifdef APEX2_EMULATE
#include "apu_lib.hpp"
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#include "apu_sat.h"

#ifdef ACF_KERNEL_METADATA

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
   Summed area table kernel metadata.
   
   \param SAT_KN				Define for Kernel name
   \param 3						Number of ports
   \param "Port SAT_KN_IN"      Define for name of input image (unsigned 8bit)
   \param "Port SAT_KN_OUT"     Define for name of output image (unsigned 32bit)
   \param "Port SAT_KN_OUT_ROW" Define for name of last row of previous tile buffer (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_K)
(
	SAT_KN,
   3,
   __port(__index(0),
   __identifier(SAT_KN_IN),
          __attributes(ACF_ATTR_VEC_IN),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d08u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   __port(__index(1),
    __identifier(SAT_KN_OUT),
          __attributes(ACF_ATTR_VEC_OUT),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(1, 1)),
   //TODO: enforce height = 1?
   __port(__index(2),
   __identifier(SAT_KN_OUT_ROW),
          __attributes(ACF_ATTR_VEC_OUT_STATIC),
          __spatial_dep(0,0,0,0),
          __e0_data_type(d32u),
          __e0_size(1, 1),
          __ek_size(1, 1))
);

/****************************************************************************/
/*!
Signed Summed area table kernel metadata.

\param SAT_SGN_KN			 Define for Kernel name
\param 5					 Number of ports
\param "Port SAT_KN_IN"      Define for name of input image (signed 8bit)
\param "Port SAT_KN_OUT"     Define for name of output image (signed 32bit)
\param "Port SAT_KN_ABS_OUT" Define for name of output image (unsigned 32bit)
\param "Port SAT_KN_OUT_ROW" Define for name of last row of previous tile buffer (signed 32bit)
\param "Port SAT_KN_OUT_ABS_ROW" Define for name of last row of previous tile buffer (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_SGN_K)
(
SAT_SGN_KN,
5,
__port(__index(0),
	__identifier(SAT_KN_IN),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d08s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(1),
	__identifier(SAT_KN_OUT),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

	//TODO: enforce height = 1?
__port(__index(2),
	__identifier(SAT_KN_ABS_OUT),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(3),
	__identifier(SAT_KN_OUT_ROW),
	__attributes(ACF_ATTR_VEC_OUT_STATIC),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32s),
	__e0_size(1, 1),
	__ek_size(1, 1)),

__port(__index(4),
	__identifier(SAT_KN_OUT_ABS_ROW),
	__attributes(ACF_ATTR_VEC_OUT_STATIC),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1))
);

/*
KERNEL_INFO kernelInfoConcat(SAT_in32u_out64u_K)
(
SAT_in32u_out64u_KN,
5,
__port(__index(0),
__identifier(SAT_in32u_out64u_K_IN),
	__attributes(ACF_ATTR_VEC_IN),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(1),
__identifier(SAT_in32u_out64u_K_OUT_HIGH),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(2),
__identifier(SAT_in32u_out64u_K_OUT_LOW),
	__attributes(ACF_ATTR_VEC_OUT),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
	//TODO: enforce height = 1?
__port(__index(3),
__identifier(SAT_in32u_out64u_K_ROW_OUT_HIGH),
	__attributes(ACF_ATTR_VEC_OUT_STATIC),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1)),
__port(__index(4),
__identifier(SAT_in32u_out64u_K_ROW_OUT_LOW),
	__attributes(ACF_ATTR_VEC_OUT_STATIC),
	__spatial_dep(0, 0, 0, 0),
	__e0_data_type(d32u),
	__e0_size(1, 1),
	__ek_size(1, 1))
);

*/

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
Summed area table kernel metadata for an unsigned 32bit input image with signed 64bit output

\param SAT_in32s_out64s_KN					Define forKernel name
\param 5									Number of ports
\param "Port SAT_in32u_out64u_K_IN"			Define for name of input image (signed 32bit)
\param "Port SAT_in32u_out64u_K_OUT_HIGH"	Define for name of high word block of output image (signed 32bit)
\param "Port SAT_in32u_out64u_K_OUT_LOW"	Define for name of low word block of output image (unsigned 32bit)
\param "Port SAT_in32u_out64u_K_ROW_OUT_HIGH" Define for name of high word of last row of previous tile buffer (signed 32bit)
\param "Port SAT_in32u_out64u_K_ROW_OUT_LOW"  Define for name of low word of last row of previous tile buffer (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_in32s_out64s_K)
(
SAT_in32s_out64s_KN,
5,
__port(__index(0),
__identifier(SAT_in32u_out64u_K_IN),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),
__port(__index(1),
__identifier(SAT_in32u_out64u_K_OUT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),
__port(__index(2),
__identifier(SAT_in32u_out64u_K_OUT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),
//TODO: enforce height = 1?
__port(__index(3),
__identifier(SAT_in32u_out64u_K_ROW_OUT_HIGH),
__attributes(ACF_ATTR_VEC_OUT_STATIC),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),
__port(__index(4),
__identifier(SAT_in32u_out64u_K_ROW_OUT_LOW),
__attributes(ACF_ATTR_VEC_OUT_STATIC),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1))
);


#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
/****************************************************************************/
/*!
   Summed area table + SAT of squared values kernel metadata.
   
   \param SAT_PLUS_SQRD_KN					Define for Kernel name
   \param 5								    Number of ports
   \param "Port SATSQRD_KN_IN"              Define for name of input image (unsigned 8bit)
   \param "Port SATSQRD_KN_OUT"             Define for name of output image (SAT) (unsigned 32bit)
   \param "Port SATSQRD_KN_OUT_SQUARED"     Define for name of output image (SAT of squared values) (unsigned 32bit)
   \param "Port SATSQRD_KN_OUT_ROW"         Define for name of last row of previous tile buffer (SAT) (unsigned 32bit)
   \param "Port SATSQRD_KN_OUT_ROW_SQUARED" Define for name of last row of previous tile buffer (SAT of squared values) (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_PLUS_SQRD_K)
(
   SAT_PLUS_SQRD_KN,
  5,
  __port(__index(0),
  __identifier(SATSQRD_KN_IN),
    __attributes(ACF_ATTR_VEC_IN),
    __spatial_dep(0, 0, 0, 0),
    __e0_data_type(d08u),
    __e0_size(1, 1),
    __ek_size(1, 1)),
  __port(__index(1),
  __identifier(SATSQRD_KN_OUT),
    __attributes(ACF_ATTR_VEC_OUT),
    __spatial_dep(0, 0, 0, 0),
    __e0_data_type(d32u),
    __e0_size(1, 1),
    __ek_size(1, 1)),
  __port(__index(2),
  __identifier(SATSQRD_KN_OUT_SQUARED),
    __attributes(ACF_ATTR_VEC_OUT),
    __spatial_dep(0, 0, 0, 0),
    __e0_data_type(d32u),
    __e0_size(1, 1),
    __ek_size(1, 1)),
    //TODO: enforce height = 1?
  __port(__index(3),
  __identifier(SATSQRD_KN_OUT_ROW),
    __attributes(ACF_ATTR_VEC_OUT_STATIC),
    __spatial_dep(0, 0, 0, 0),
    __e0_data_type(d32u),
    __e0_size(1, 1),
    __ek_size(1, 1)),
    //TODO: enforce height = 1?
  __port(__index(4),
  __identifier(SATSQRD_KN_OUT_ROW_SQUARED),
    __attributes(ACF_ATTR_VEC_OUT_STATIC),
    __spatial_dep(0, 0, 0, 0),
    __e0_data_type(d32u),
    __e0_size(1, 1),
    __ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_sat_impl.h"

void apu_sat(kernel_io_desc lIn, kernel_io_desc lOut, kernel_io_desc lRow)
{
   vec08u*        lpvIn   = (vec08u*) lIn.pMem;
   vec32u*        lpvOut  = (vec32u*)  lOut.pMem;
   vec32u*        lpvRow  = (vec32u*)  lRow.pMem;
   int08u firstTile = (int08u)ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);

   sat32(lpvOut, lpvRow, lpvIn, lIn.chunkSpan, lOut.chunkSpan, lIn.chunkWidth, lIn.chunkHeight, firstTile);
}


void apu_sat_sgn(kernel_io_desc lIn, kernel_io_desc lOut, kernel_io_desc lAbsOut, kernel_io_desc lRow, kernel_io_desc lAbsRow)
{
	vec08s*        lpvIn = (vec08s*)lIn.pMem;
	vec32s*        lpvOut = (vec32s*)lOut.pMem;
	vec32s*        lpvRow = (vec32s*)lRow.pMem;

	vec32u*        lpvAbsOut = (vec32u*)lAbsOut.pMem;
	vec32u*        lpvAbsRow = (vec32u*)lAbsRow.pMem;

	int08u firstTile = (int08u)ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);

	sat_sgn_32(lpvOut, lpvAbsOut, lpvRow, lpvAbsRow, lpvIn, lIn.chunkSpan, lOut.chunkSpan, lIn.chunkWidth, lIn.chunkHeight, firstTile);
}

/*
void apu_sat_in32u_out64u(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow)
{
	vec32u*        lpvIn = (vec32u*)lIn.pMem;
	vec32u*        lpvOutHigh = (vec32u*)lOutHigh.pMem;
	vec32u*        lpvOutLow = (vec32u*)lOutLow.pMem;
	vec32u*        lpvRowHigh = (vec32u*)lOutRowHigh.pMem;
	vec32u*        lpvRowLow = (vec32u*)lOutRowLow.pMem;
	int08u firstTile = (int08u)ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);

	int16s inDataSz = sizeof(int32u);
	int16s inStrideW = lIn.chunkSpan / inDataSz;
	int16s outDataSz = sizeof(int32u);
	int16s outStrideW = lOutHigh.chunkSpan / outDataSz;

	sat_in32u_out64u(lpvOutHigh, lpvOutLow, lpvRowHigh, lpvRowLow, lpvIn, lIn.chunkWidth, lIn.chunkHeight, inStrideW, outStrideW, firstTile);
}

*/
void apu_sat_in32s_out64s(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow)
{
	vec32s*        lpvIn = (vec32s*)lIn.pMem;
	vec32s*        lpvOutHigh = (vec32s*)lOutHigh.pMem;
	vec32u*        lpvOutLow = (vec32u*)lOutLow.pMem;
	vec32s*        lpvRowHigh = (vec32s*)lOutRowHigh.pMem;
	vec32u*        lpvRowLow = (vec32u*)lOutRowLow.pMem;
	int08u firstTile = (int08u)ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);
	
	int16s inDataSz = sizeof(int32s);
	int16s inStrideW = lIn.chunkSpan / inDataSz;
	int16s outDataSz = sizeof(int32s);
	int16s outStrideW = lOutHigh.chunkSpan / outDataSz;

	sat_in32s_out64s(lpvOutHigh, lpvOutLow, lpvRowHigh, lpvRowLow, lpvIn, lIn.chunkWidth, lIn.chunkHeight, inStrideW, outStrideW, firstTile);
}

void apu_sat_plus_squared(
	kernel_io_desc lIn,
	kernel_io_desc lOut,
	kernel_io_desc lOutSquared,
	kernel_io_desc lRow,
	kernel_io_desc lRowSquared)
{
	vec08u*        lpvIn = (vec08u*)lIn.pMem;
	vec32u*        lpvOut = (vec32u*)lOut.pMem;
	vec32u*        lpvOutSquared = (vec32u*)lOutSquared.pMem;
	vec32u*        lpvRow = (vec32u*)lRow.pMem;
	vec32u*        lpvRowSquared = (vec32u*)lRowSquared.pMem;
	int08u firstTile = (int08u)ACF_RET_VAR(ACF_VAR_FIRST_TILE_FLAG);

	sat32PlusSquared(lpvOut, lpvOutSquared, lpvRow, lpvRowSquared, lpvIn, lIn.chunkSpan, lOut.chunkSpan, lIn.chunkWidth, lIn.chunkHeight, firstTile);
}
#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
