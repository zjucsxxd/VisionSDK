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
* \file apu_gauss_5x5_impl.h
* \brief 5x5 Gaussian filter implementation for APEX
* \addtogroup gauss
* @{
****************************************************************************/

#ifndef _APU_GAUSS_5X5_IMPL_H_
#define _APU_GAUSS_5X5_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/*!
   Calculate the output of 5x5 gaussian filter.
   \brief 5x5 gaussian filter.
   
   \param dst  - [Output] Destination block pointer
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void Gauss_5x5__filter(vec08u* dst, vec08u* src, int sstr, int bw, int bh);

#endif // _APU_GAUSS_5X5_IMPL_H_  

/*! @} */
