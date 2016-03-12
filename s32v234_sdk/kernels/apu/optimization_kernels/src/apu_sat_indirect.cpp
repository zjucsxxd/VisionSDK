/*!
* \file apu_sat_indirect.cpp
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

#include "apu_sat_indirect.h"

#ifdef ACF_KERNEL_METADATA


/*

#ifndef APEX2_EMULATE
static  // declare as static only if the code is compiled by the Target compiler
#endif
KERNEL_INFO kernelInfoConcat(SAT_in32u_out64u_K)
(
SAT_in32u_out64u_KN,
5,
__port(__index(0),
__identifier(SAT_in32u_out64u_K_INPUT),
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

/****************************************************************************/
/*! OBSOLETE
Summed area table kernel metadata for an unsigned 32bit input image with signed 64bit output and chunks selected with an offset vector

\param SAT_indirect_in32s_out64s_K					Define forKernel name
\param 5									Number of ports
\param "Port SAT_in32u_out64u_K_IN"			Define for name of input image (signed 32bit)
\param "Port SAT_in32u_out64u_K_OUT_HIGH"	Define for name of high word block of output image (signed 32bit)
\param "Port SAT_in32u_out64u_K_OUT_LOW"	Define for name of low word block of output image (unsigned 32bit)
\param "Port SAT_in32u_out64u_K_ROW_OUT_HIGH" Define for name of high word of last row of previous tile buffer (signed 32bit)
\param "Port SAT_in32u_out64u_K_ROW_OUT_LOW"  Define for name of low word of last row of previous tile buffer (unsigned 32bit)
*****************************************************************************/
KERNEL_INFO kernelInfoConcat(SAT_indirect_in32s_out64s_K)
(
SAT_indirect_in32s_out64s_KN,
5,
__port(__index(0),
__identifier(SAT_in32u_out64u_K_INPUT),
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



#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_sat_indirect_impl.h"


/*
void apu_sat_indirect_in32u_out64u(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow)
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


void apu_sat_indirect_in32s_out64s(kernel_io_desc lIn, kernel_io_desc lOutHigh, kernel_io_desc lOutLow, kernel_io_desc lOutRowHigh, kernel_io_desc lOutRowLow)
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

	sat_indirect_in32s_out64s(lpvOutHigh, lpvOutLow, lpvRowHigh, lpvRowLow, lpvIn, lIn.chunkWidth, lIn.chunkHeight, inStrideW, outStrideW, firstTile);
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
