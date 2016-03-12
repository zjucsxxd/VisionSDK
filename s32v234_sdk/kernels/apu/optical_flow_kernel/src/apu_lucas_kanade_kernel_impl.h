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
* \file apu_lucas_kanade_kernel_impl.h
* \brief Lucas-Kanade mismatch filter, eq.29 in "Pyramidal Implementation of the Lucas Kanade Feature Tracker Description of the algorithm", Jean-Yves Bouguet - intel.com
* \addtogroup of_lucas_kanade
* @{
*/
#ifndef _APU_LUCAS_KANADE_IMPL_H_
#define _APU_LUCAS_KANADE_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#include "apu_vec.hpp"
using namespace APEX2;
#endif


/*!
 \brief Calculate the mismatch vector of the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.

 (  Eq 30)
  
   \param deltaK_GradX	- [Output]  32bit Accumulated value for deltaK*gradX inside the current Chunk
   \param deltaK_GradY	- [Output]  32bit Accumulated value for deltaK*gradY inside the current Chunk
   \param inStrideWidth - [Input]  Source block stride width (i.e. nr. of elements including padding)
   \param bw			- [Input]  Block width
   \param bh			- [Input]  Block height
   \param outStrideWidth - [Input] Destination block stride width (i.e. nr. of elements including padding)
   \param imgDeltaK		- [Input] 32bit (temporal) Difference of image patches from imgA cut out around selected points and interpolated ImgB cut out around SHIFTED selected points
   \param gradX			- [Input] 32bit  Gradient in X direction of imgA cut out around selected points 
   \param gradY			- [Input] 32bit  Gradient in Y direction of imgA cut out around selected points
*/
void lucas_kanade_mismatch_filter(vec32s* deltaK_GradX, vec32s* deltaK_GradY, vec32s* imgDeltaK, int16s inStrideWidth, int16s bw, int16s bh, int16s outStrideWidth, vec16s* gradX, vec16s* gradY);

/*!
\brief Calculate the accumulated mismatch vector (over the whole chunk) of an input image and a second shifted input image.

(Eq.29)

\param nuEtaX		- [Output] accumulated X component of mismatch vector (nuEtaX = acc(deltaK*gradX))
\param nuEtaY		- [Output] accumulated Y component of mismatch vector (nuEtaY = acc(deltaK*gradY))
\param inStrideWidth - [Input]  Source block stride width (i.e. nr. of elements including padding)
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param deltaK_GradX	- [Input]  x component of mismatch vector
\param deltaK_GradY	- [Input]  y component of mismatch vector
****/
void lucas_kanade_accum_filter(vec32s* etaX, vec32s* etaY
							, int16s inStrideWidth, int16s bw, int16s bh
							, vec32s* deltaK_GradX, vec32s* deltaK_GradY);



/*
Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.
[nuEtaX		 =	[accGradYSqr	 -accGradXY]	*	[nuEtaX
nuEtaY]			-accGradXY		accGradXSqr]		nuEtaY]

nuEtaX = accGradYSqr*nuEtaX - accGradXY*nuEtaY
nuEtaY = accGradXSqr*nuEtaY - accGradXY*nuEtaX

\param gOutX_high -[Output] High word of 64bit X component of offsets vector
\param gOutX_low - [Output] Low word of 64bit X component of offsets vector
\param gOutY_high -[Output] High word of 64bit Y component of offsets vector
\param gOutY_low - [Output] Low word of 64bit Y component of offsets vector
\param etaInX	- [Input] accumulated X component of mismatch vector
\param etaInY	- [Input] accumulated Y component of mismatch vector
\param gradXSqr	- [Input]  accumulated gradX*gradX of imgA cut out around selected points and accumulated over a neighborhood
\param gradYSqr	- [Input]  accumulated gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param gradXgradY -[Input]  accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param detG		- [Input]  Determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood
\param vEtaNorm	- [Output]	partial etaNorm vector
\param sstr		- [Input]  Source block stride
\param bw		- [Input]  Block width
\param bh		- [Input]  Block height

void lucas_kanade_offset_filter(vec32s* gOutX_high, vec32u* gOutX_low, vec32s* gOutY_high, vec32u* gOutY_low, vec32s* etaInX, vec32s* etaInY, vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen);

*/

/*!
\brief Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.

[nuEtaX		 =	(1/detG)* [accGradYSqr		-accGradXY]	*	[nuEtaX
nuEtaY]					  -accGradXY		accGradXSqr]	nuEtaY]

Either
nuEtaX = (accGradYSqr*nuEtaX - accGradXY*nuEtaY)/detG
or 
nuEtaY = (accGradXSqr*nuEtaY - accGradXY*nuEtaX)/detG

\param gOut			- [Output] 32bit integer part of Offset
\param gOutOffs		- [Output] 32bit offset vector in Q3.28 fixed point format
\param etaX			- [Input]  accumulated X component of mismatch vector
\param etaY			- [Input]  accumulated Y component of mismatch vector
\param gradXorYSqr	- [Input]  accumulated either gradX*gradX or gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param gradXgradY	- [Input]  accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param accDetG_inv	- [Input]  Inverse of Determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood
\param inValidPts	- [Input]  Boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high).
\param outValidPts	- [Input]  Boolean vector. Values are true, if the corresponding gOut are not too high.
\param vEtaNorm		- [Output] etaNorm vector containing the sum of 16*(gOut+gOutOffs)^2 over the whole vector
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideLen	- [Input]  Source block stride width (in pixels not bytes!)
\param ouStrideLen	- [Input]  Destination block stride width (in pixels not bytes!)
*/
void lucas_kanade_offset_filter_xOry(vec32s* gOut, vec32s* gOutOffs, vec32s* etaX, vec32s* etaY
								, vec32s* accGradXorYSqr, vec32s* accgradXgradY, vec32u *accDetG_inv
								, vec16u* inValidPts, vec16u* outValidPts, vec32u* vEtaNorm
								, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen);


/*!
\brief Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image. The gradient matrix values are unsigned

[nuEtaX		 =	(1/detG)* [accGradYSqr		-accGradXY]	*	[nuEtaX
nuEtaY]					  -accGradXY		accGradXSqr]	nuEtaY]

Either
nuEtaX = (accGradYSqr*nuEtaX - accGradXY*nuEtaY)/detG
or
nuEtaY = (accGradXSqr*nuEtaY - accGradXY*nuEtaX)/detG

\param gOut			- [Output] 32bit integer part of Offset
\param gOutOffs		- [Output] 32bit offset vector in Q3.28 fixed point format
\param etaX			- [Input]  accumulated X component of mismatch vector
\param etaY			- [Input]  accumulated Y component of mismatch vector
\param gradXorYSqr	- [Input]  accumulated either gradX*gradX or gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param gradXgradY	- [Input]  accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param accDetG_inv	- [Input]  Inverse of Determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood
\param inValidPts	- [Input]  Boolean vector. Values are true, if the corresponding determinant value correspond to certain validity criteria(i.e. are high enough but not too high).
\param outValidPts	- [Input]  Boolean vector. Values are true, if the corresponding gOut are not too high.
\param vEtaNorm		- [Output] etaNorm vector containing the sum of 16*(gOut+gOutOffs)^2 over the whole vector
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideLen	- [Input]  Source block stride width (in pixels not bytes!)
\param ouStrideLen	- [Input]  Destination block stride width (in pixels not bytes!)
*/
void lucas_kanade_offset_filter_xOry_unsigned(vec32s* gOut, vec32s* gOutOffs, vec32s* etaX, vec32s* etaY
									, vec32u* accGradXorYSqr, vec32s* accgradXgradY, vec32u *accDetG_inv
									, vec16u* inValidPts, vec16u* outValidPts, vec32u* vEtaNorm
									, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen);


/*!
\brief Compute from x,y image coordinates the byte offset inside a linear array

\param lPointOffsets - [Output] Byte indices inside the linear array of the (x,y)-(tWidth,tHeight) coordinate
\param newValidPts	- [Output] Flag array containing the validPts & points inside the array boundaries.
\param xCoords		- [Input] Array containing the x-Coordinates of the points 
\param yCoords		- [Input] Array containing the y-Coordinates of the points
\param validPoints  - [Input] Flag array being true for the points which have to be computed 
\param  imgWidth	- [Input] Image width 
\param imgHeight	- [Input] Image height
\param tWidth		- [Input] Tile width 
\param tHeight		- [Input] Tile height 
\param dataSz		- [Input] Size in bytes of the input data element
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideWidth  - [Input]  Source block stride width (i.e. nr. of elements including padding)
\param outStrideWidth - [Input] Destination block stride width (i.e. nr. of elements including padding)
*/
void transformCoordsToPointOffsets(vec32u* lPointOffsets, vec16u* newValidPts, vec32s* xCoords, vec32s* yCoords, vec16u* validPoints,
								   int32s imgWidth, int32s imgHeight, int32s tWidth, int32s tHeight,
								   int32s dataSz, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth);

#endif // _APU_lucas_kanade_IMPL_H_  

/*! @} */
