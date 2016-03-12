/*!
* \file apu_gradient_matrix_kernel.c
* \addtogroup of_lucas_kanade
* @{
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif


#ifdef ACF_KERNEL_METADATA

#include "apu_lucas_kanade_offs_kernel.h"


#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
#else
//extern 
const int ACCUM_TILE_SIZE_X = 10; // have to be defined here, otherwise g++ linker complains
//extern 
const int ACCUM_TILE_SIZE_Y = 10;
#endif

#ifndef APEX2_EMULATE
static
#endif
KERNEL_INFO _kernel_info_apu_lucas_kanade_offset
(
LUCAS_KANADE_OFFSET_KN,
9,
__port(__index(0),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(7),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(8),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))
);

#ifndef APEX2_EMULATE
static
#endif
KERNEL_INFO _kernel_info_apu_lucas_kanade_offset_x
(
LUCAS_KANADE_OFFSET_X_KN,
7,
__port(__index(0),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))
);


#ifndef APEX2_EMULATE
static
#endif
KERNEL_INFO _kernel_info_apu_lucas_kanade_offset_y
(
LUCAS_KANADE_OFFSET_Y_KN,
7,
__port(__index(0),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KERNEL_OFFS_ETA_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(2),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_HIGH),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(3),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_LOW),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(4),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_X_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(5),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_Y_SQR),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32u),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(6),
__identifier(LUCAS_KANADE_KERNEL_ACC_GRAD_XY),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1))
);

/*
__port(__index(0),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_IN_X_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

__port(__index(1),
__identifier(LUCAS_KANADE_KERNEL_OFFS_G_IN_Y_VECT),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(0, 0, 0, 0),
__e0_data_type(d32s),
__e0_size(1, 1),
__ek_size(1, 1)),

,
		__port(__index(10),
			  __identifier(LUCAS_KANADE_KERNEL_ETA_NORM),
			  __attributes(ACF_ATTR_SCL_OUT_STATIC_FIXED),
			  __spatial_dep(0, 0, 0, 0),
			  __e0_data_type(d32u),
			  __e0_size(1, 1),
			  __ek_size(1, 1))
*/

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION
#include "apu_lucas_kanade_offs_kernel_impl.h"

//extern int ACF_FIRST_TILE_FLAG;
//extern int ACF_LAST_TILE_FLAG; //” instead of ACF_RET_VAR.




void apu_lucas_kanade_offset(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/)
{
	vec32s*	gOutX_high = (vec32s*)lOutOffsetGXVect_high.pMem;
	vec32s*	gOutY_high = (vec32s*)lOutOffsetGYVect_high.pMem;
	vec32u*	gOutX_low = (vec32u*)lOutOffsetGXVect_low.pMem;
	vec32u*	gOutY_low = (vec32u*)lOutOffsetGYVect_low.pMem;
	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutOffsetGXVect_high.chunkSpan / outDataSz;


	vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
	vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;
	int32s etaInXSz = sizeof(etaInX);

	vec32u*	gradXSqr = (vec32u*)inGradXSqrImg.pMem;
	vec32u*	gradYSqr = (vec32u*)inGradYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	//vec32s*	detG = (vec32s*)inDetGImg.pMem;


	//vec32u	vEtaNorm = 0;
	//int32u& etaNorm = *((int32u*)lEtaNorm.pMem);
	//static int32s nrPointsToProcess = 0;

	////lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen, gradXSqr, gradYSqr, gradXgradY/*, detG, &vEtaNorm* /);
	//lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY , gradXSqr, gradYSqr, gradXgradY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen/*, detG, &vEtaNorm* /);

	/*
	for (int i = 0; i < nrTiles; ++i) {
	etaNorm += vget(vEtaNorm, firstCUIdx + i);
	}
	*/
	/*
	for (int i = 0; i < nrTiles; ++i) {
	int32s crtEtaValX = vget((*etaInX), firstCUIdx + i);
	int32s crtEtaValY = vget((*etaInY), firstCUIdx + i);

	int32u absX = (int32u) (crtEtaValX > 0 ? crtEtaValX : -crtEtaValX);
	int32u absY = (int32u) (crtEtaValY > 0 ? crtEtaValY : -crtEtaValY);
	etaNorm += absX + absY;
	}*/
}

	
void apu_lucas_kanade_offset_x(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/)
{
vec32s*	gOutX_high = (vec32s*)lOutOffsetGXVect_high.pMem;
vec32u*	gOutX_low = (vec32u*)lOutOffsetGXVect_low.pMem;
int16s outDataSz = sizeof(int32s);
int16s outStrideLen = lOutOffsetGXVect_high.chunkSpan / outDataSz;


vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
int32s inDataSz = sizeof(int32s);
int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;
int32s etaInXSz = sizeof(etaInX);

vec32u*	gradXSqr = (vec32u*)inGradXSqrImg.pMem;
vec32u*	gradYSqr = (vec32u*)inGradYSqrImg.pMem;
vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
//vec32s*	detG = (vec32s*)inDetGImg.pMem;


//vec32u	vEtaNorm = 0;
//int32u& etaNorm = *((int32u*)lEtaNorm.pMem);
//static int32s nrPointsToProcess = 0;

////lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen, gradXSqr, gradYSqr, gradXgradY/*, detG, &vEtaNorm*/);
lucas_kanade_offset_filter_x(gOutX_high, gOutX_low, etaInX, etaInY , gradXSqr, gradYSqr, gradXgradY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen/*, detG, &vEtaNorm*/);

/*
for (int i = 0; i < nrTiles; ++i) {
etaNorm += vget(vEtaNorm, firstCUIdx + i);
}
*/
/*
for (int i = 0; i < nrTiles; ++i) {
int32s crtEtaValX = vget((*etaInX), firstCUIdx + i);
int32s crtEtaValY = vget((*etaInY), firstCUIdx + i);

int32u absX = (int32u) (crtEtaValX > 0 ? crtEtaValX : -crtEtaValX);
int32u absY = (int32u) (crtEtaValY > 0 ? crtEtaValY : -crtEtaValY);
etaNorm += absX + absY;
}*/
}
			 


void apu_lucas_kanade_offset_y(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/)
{
	vec32s*	gOutY_high = (vec32s*)lOutOffsetGYVect_high.pMem;
	vec32u*	gOutY_low = (vec32u*)lOutOffsetGYVect_low.pMem;
	int16s outDataSz = sizeof(int32s);
	int16s outStrideLen = lOutOffsetGYVect_high.chunkSpan / outDataSz;


	vec32s*	etaInX = (vec32s*)lInOffsetEtaXVect.pMem;
	vec32s*	etaInY = (vec32s*)lInOffsetEtaYVect.pMem;
	int32s inDataSz = sizeof(int32s);
	int16s inStrideLen = lInOffsetEtaXVect.chunkSpan / inDataSz;
	int32s etaInXSz = sizeof(etaInX);

	vec32u*	gradXSqr = (vec32u*)inGradXSqrImg.pMem;
	vec32u*	gradYSqr = (vec32u*)inGradYSqrImg.pMem;
	vec32s*	gradXgradY = (vec32s*)inGradXGradYImg.pMem;
	//vec32s*	detG = (vec32s*)inDetGImg.pMem;


	//vec32u	vEtaNorm = 0;
	//int32u& etaNorm = *((int32u*)lEtaNorm.pMem);
	//static int32s nrPointsToProcess = 0;

	////lucas_kanade_offset_filter(gOutX_high, gOutX_low, gOutY_high, gOutY_low, etaInX, etaInY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen, gradXSqr, gradYSqr, gradXgradY/*, detG, &vEtaNorm*/);
	lucas_kanade_offset_filter_y(gOutY_high, gOutY_low, etaInX, etaInY , gradXSqr, gradYSqr, gradXgradY, inDataSz, lInOffsetEtaXVect.chunkWidth, lInOffsetEtaXVect.chunkHeight, outStrideLen/*, detG, &vEtaNorm*/);

	/*
	for (int i = 0; i < nrTiles; ++i) {
	etaNorm += vget(vEtaNorm, firstCUIdx + i);
	}
	*/
	/*
	for (int i = 0; i < nrTiles; ++i) {
	int32s crtEtaValX = vget((*etaInX), firstCUIdx + i);
	int32s crtEtaValY = vget((*etaInY), firstCUIdx + i);

	int32u absX = (int32u) (crtEtaValX > 0 ? crtEtaValX : -crtEtaValX);
	int32u absY = (int32u) (crtEtaValY > 0 ? crtEtaValY : -crtEtaValY);
	etaNorm += absX + absY;
	}*/
}



#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
