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
* \file apu_rotate_180.h
* \brief 180-degree rotation implementation for APEX
* \addtogroup rotation
* @{
****************************************************************************/

#ifndef _APU_ROTATE_180_IMPL_H_
#define _APU_ROTATE_180_IMPL_H_

#include <stdint.h>

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/*****************************************************************************
* prototypes
*****************************************************************************/

/****************************************************************************/
/*!
  Rotates the image 180 degrees.
  \brief 180-degree rotation.
 
  \param dst                - [Output] pointer to the destination buffer
  \param src                - [Input]  pointer to the source buffer
  \param bw                 - [Input]  width of one data block
  \param bh                 - [Input]  height of one data block
  \param sstr               - [Input]  source stride
*****************************************************************************/

void rotate_180(vec08u* dst, vec08u* src, int bw, int bh, int sstr);

#endif // _APU_rotate_180_IMPL_H_

/*! @} */
