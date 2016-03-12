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
* \file apu_lucas_kanade_offs_kernel_impl.h
* \brief Lucas-Kanade mismatch filter, eq.29 in "Pyramidal Implementation of the Lucas Kanade Feature Tracker Description of the algorithm", Jean-Yves Bouguet - intel.com
* \addtogroup of_lucas_kanade
* @{
****************************************************************************/

#ifndef _APU_LUCAS_KANADE_OFFS_IMPL_H_
#define _APU_LUCAS_KANADE_OFFS_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#include "apu_vec.hpp"
using namespace APEX2;
#endif


/*!
Calculate the inner Lucas Kanade Kernel of selected points (with neighborhoods) of an input image and a second shifted input image.
[nuEtaX		 =	[accGradYSqr	 -accGradXY]	*	[nuEtaX
nuEtaY]			-accGradXY		accGradXSqr]		nuEtaY]

\param gOutX_high-[Output] High word of 64bit X component of offsets vector
\param gOutX_low- [Output] Low word of 64bit X component of offsets vector
\param gOutY_high-[Output] High word of 64bit Y component of offsets vector
\param gOutY_low- [Output] Low word of 64bit Y component of offsets vector
\param nuEtaX	- [Input] accumulated X component of mismatch vector
\param nuEtaY	- [Input] accumulated Y component of mismatch vector
\param sstr		- [Input]  Source block stride
\param bw		- [Input]  Block width
\param bh		- [Input]  Block height
\param gradXSqr	- [Input]  accumulated gradX*gradX of imgA cut out around selected points and accumulated over a neighborhood
\param gradYSqr	- [Input]  accumulated gradY*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param gradXgradY-[Input]  accumulated gradX*gradY of imgA cut out around selected points and accumulated over a neighborhood
\param detG		- [Input]  Determinant of above G matrix of imgA cut out around selected points and accumulated over a neighborhood
\param vEtaNorm	- [Output]	partial etaNorm vector
*/
void lucas_kanade_offset_filter(vec32s* gOutX_high, vec32u* gOutX_low, vec32s* gOutY_high, vec32u* gOutY_low, vec32s* etaX, vec32s* etaY, vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accgradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen);

void lucas_kanade_offset_filter_x(vec32s* gOutX_high, vec32u* gOutX_low/*, vec32s* gInX, vec32s* gInY*/, vec32s* etaInX,  vec32s* etaInY, vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen/*, vec32s* detG,*/ /*vec32u* vEtaNorm*/);
void lucas_kanade_offset_filter_y(vec32s* gOutY_high, vec32u* gOutY_low/*, vec32s* gInX, vec32s* gInY*/,vec32s* etaInX,  vec32s* etaInY, vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen/*, vec32s* detG,*/ /*vec32u* vEtaNorm*/);

#endif // _APU_lucas_kanade_IMPL_H_  

/*! @} */
