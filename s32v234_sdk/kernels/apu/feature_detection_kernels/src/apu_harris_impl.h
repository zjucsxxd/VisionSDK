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
* \file apu_harris_impl.h
* \brief Harris corner detection implementation for APEX
* \addtogroup harris
* @{
****************************************************************************/

#ifndef _APU_HARRIS_IMPL_H_
#define _APU_HARRIS_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/****************************************************************************/
/*!
   Finds the corners in the input data using the Harris algorithm. Outputs a Harris response value for each pixel.
   
   out[i] = (det(A[i]) - k * trace(A[i])^2) >> responseBitShift\n
   where A[i] is a structure tensor for pixel i
   
   See http://docs.opencv.org/doc/tutorials/features2d/trackingmotion/harris_detector/harris_detector.html
   \brief Harris corner detection

   \param apResponse output Harris response image
   \param apGradX image gradient x component
   \param apGradY image gradient y component
   \param aBlockWidth CU block width
   \param aBlockHeight CU block height
   \param aStride horizontal gradient image stride
   \param k Harris detector sensitivity
   \param responseBitShift bit shift that will be applied to the output response
   \param aWindowSize Harris detector window size
*****************************************************************************/
//TODO: scaled 8 bits?
void apuHarrisResponse(vec16u* apResponse,
  vec16s* apGradX, vec16s* apGradY, vec16s* apTemp,
  int aBlockWidth, int aBlockHeight, int aStride, int k, int responseBitShift, int aWindowSize, bool isFirstSlice);

#endif // _APU_HARRIS_IMPL_H_ 

/*! @} */
