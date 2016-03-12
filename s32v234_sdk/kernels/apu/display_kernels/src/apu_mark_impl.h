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
* \file apu_mark_impl.h
* \brief image marking implementation for APEX
* \addtogroup marking
* @{
****************************************************************************/

#ifndef _APU_MARK_IMPL_H_
#define _APU_MARK_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/****************************************************************************/
/*!
   Marks the image. Output pixels are copied from the source image
   in positions where the marker pixels are zero and from the marker image
   otherwise.
   \brief Marks the image.

   \param dst       - [Output] Pointer to the destination buffer
   \param srcImage  - [Input]  Pointer to the source buffer
   \param srcMarker - [Input]  Pointer to the marker buffer
   \param bw        - [Input]  Width of one data block
   \param bh        - [Input]  Height of one data block
   \param sstride   - [Input]  Input stride
   \param mstride   - [Input]  Marker stride
*****************************************************************************/
void mark(vec08u* dst, vec08u* srcImage, vec08u* srcMarker, int bw, int bh, int sstride, int mstride);

#endif // _APU_mark_IMPL_H_ 

/*! @} */
