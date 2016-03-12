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
* \file apu_gradient_matrix_kernel_impl.h
* \brief Gradient_matrix computes for an InputImage's GradX, GradY, GradXSqr, GradYSqr, GradX*GradY and accumulations over a neighborhood, given by (bw, bh), i.e. chunk size
* \addtogroup of_gradient_matrix
* @{
****************************************************************************/


#ifndef _APU_GRADIENT_MATRIX_IMPL_H_
#define _APU_GRADIENT_MATRIX_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#include "apu_vec.hpp"
using namespace APEX2;
#endif

// Factor needed to obtain more accuracy for the sub-pixel interpolation
#define inputShiftFact  3 
#define scaleInputBy  (1 << inputShiftFact)

#define ACCUM_MARGIN 3 // margin needed, due to indirect input and previous interpolation and gradient operations
#define ACCUM_OFFS	 1

#define accDownScale 10 //6 // shift factor for accumulation 2*log_2(ACCUM_TILE_SIZE -ACCUM_MARGIN) = 2*log_2( 7 ) ~= 6


#ifdef ACF_KERNEL_IMPLEMENTATION


/*!
   \brief Calculate the square gradients and gradX*gradY, i.e the elements of the spatial gradient matrix for the Lucas-Kanade step

   \param gradX			- [Input]  16bit Gradient matrix in X direction
   \param gradY			- [Input]  16bit Gradient in Y direction
   \param gradXSqr		- [Output] 32bit Square of GradX matrix
   \param gradYSqr		- [Output] 32bit Square of GradY matrix 
   \param gradXGradY	- [Output] 32bit GradX*GradY, i.e. dot product btw GradX and GradY matrices
   \param bw			- [Input]  Block width
   \param bh			- [Input]  Block height
   \param inStrideWidth	 - [Input]  Source block stride width (in elements not bytes, including padding)
   \param outStrideWidth - [Input]  Destination block stride width (in elements not bytes, including padding)
   */
void gradient_matrix_filter(vec16s* gradX, vec16s* gradY, 
	vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXGradY,
	int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth);


/*!
\brief Accumulate the inputs for the gradient matrix over a neighborhood specified by the input chunk size and compute the dot determinants.

\param gradXSqr		- [Input] 32bit Square of GradX matrix
\param gradYSqr		- [Input] 32bit Square of GradY matrix
\param gradXGradY	- [Input] 32bit GradX*GradY, i.e. dot product btw GradX and GradY matrices
\param accGradXSqr	- [Output] 32bit Accumulated value of GradXSqr values inside the selected chunks
\param accGradYSqr	- [Output] 32bit Accumulated value of GradYSqr values inside the selected chunks
\param accGradXY	- [Output] 32bit Accumulated value of GradXY values inside the selected chunks
\param accDetG_inv	- [Output] 32bit inverse 1/detG (DetG=accGradXSqr*accGradYSqr - accGradXY*accGradXY), in Q3.28 fixed point format
\param validPts		- [Output] Bool matrix, containing 0 for the points, where the min. Eigenvalue are lower than  0.001
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideLen	- [Input]  Source block stride width (in elements not bytes, including padding)
\param outStrideLen	- [Input]  Destination block stride width (in elements not bytes, including padding)
*/
void accum_gradient_matrix_filter(vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXGradY, 
	vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accGradXY
	, vec32u* accDetG_inv, vec16u* validPts,
	int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen
);



/*!
\brief Compute the inverse determinant of a gradient matrix and set validpts to false if inverse value exceeds threshold

\param accGradXSqr_H - [Input] 32bit High Word of accumulated value of GradXSqr values inside the selected chunks
\param accGradXSqr_L - [Input] 32bit Low Word of accumulated value of GradXSqr values inside the selected chunks
\param accGradYSqr_H - [Input] 32bit High Word of accumulated value of GradYSqr values inside the selected chunks
\param accGradYSqr_L - [Input] 32bit Low Word of accumulated value of GradYSqr values inside the selected chunks
\param accGradXY_H	 - [Input] 32bit High Word of accumulated value of GradXY values inside the selected chunks
\param accGradXY_L	 - [Input] 32bit Low Word of accumulated value of GradXY values inside the selected chunks
\param outAccGradXSqr -[Output] 32bit downscaled value of accumulated value of GradXSqr values inside the selected chunks
\param outAccGradYSqr -[Output] 32bit downscaled value of accumulated value of GradYSqr values inside the selected chunks
\param outAccGradXY	- [Output] 32bit downscaled value of accumulated value of GradXY values inside the selected chunks
\param accDetG_inv	- [Output] 32bit inverse 1/detG (DetG=accGradXSqr*accGradYSqr - accGradXY*accGradXY), in Q3.28 fixed point format
\param validPts		- [Output] Bool matrix, containing 0 for the points, where the min. Eigenvalue are lower than  0.001
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideLen	- [Input]  Source block stride width (in elements not bytes, including padding)
\param outStrideLen	- [Input]  Destination block stride width (in elements not bytes, including padding)
*/
void inverse_determinant_filter(vec32s* accGradXSqrH, vec32u* accGradXSqrL
	, vec32s* accGradYSqrH, vec32u* accGradYSqrL
	, vec32s* accGradXYH, vec32u* accGradXYL
	, vec32s* outAccGradXSqr, vec32s* outAccGradYSqr, vec32s* outAccGradXY
	, vec32u* accDetG_inv, vec16u* validPts
	, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen);




/*!
\brief Compute the inverse determinant of a signed 32bit gradient matrix and set validpts to false if inverse value exceeds threshold

\param accGradXSqr	- [Input]  unsigned 32bit accumulated value of GradXSqr values inside the selected chunks
\param accGradYSqr	- [Input]  unsigned 32bit accumulated value of GradYSqr values inside the selected chunks
\param accGradXY	- [Input]  unsigned 32bit accumulated value of GradXY values inside the selected chunks
\param accDetG_inv	- [Output] 32bit inverse 1/detG (DetG=accGradXSqr*accGradYSqr - accGradXY*accGradXY), in Q3.28 fixed point format
\param validPts		- [Output] Bool matrix, containing 0 for the points, where the min. Eigenvalue are lower than  0.001
\param accWidth		- [Input]  input accumulation width  of the block
\param accHeight	- [Input]  input accumulation height of the bloc
\param bw			- [Input]  Block width
\param bh			- [Input]  Block height
\param inStrideLen	- [Input]  Source block stride width (in elements not bytes, including padding)
\param outStrideLen	- [Input]  Destination block stride width (in elements not bytes, including padding)
*/
void inverse_det_simple_filter(vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accGradXY
	, vec32u* accDetG_inv, vec16u* validPts, int16s accWidth, int16s accHeight
	, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen);

#endif
#endif // _APU_GRADIENT_MATRIX_IMPL_H_  

/*! @} */
