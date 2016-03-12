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
* \file apu_pass_through_impl.h
* \brief  Copies inputs to outputs. Implementation for APEX
* \addtogroup copying
* @{
****************************************************************************/
#ifndef _APU_SATURATE_NONZERO_IMPL_H_
#define _APU_SATURATE_NONZERO_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/****************************************************************************/
/*!
   Copies inputs to outputs.
   \brief Copies inputs to outputs.

   \param dst  - [Output] Pointer to the destination buffer
   \param src  - [Input]  Pointer to the source buffer
   \param dstr - [Input]  Line stride of the destination data
   \param sstr - [Input]  Line stride of the source data
   \param bw   - [Input]  Width of one data block
   \param bh   - [Input]  Height of one data block
*****************************************************************************/
void pass_through(vec08u* dst, vec08u* src, int dstr, int sstr, int bw, int bh);


#endif // _APU_pass_through_IMPL_H_ 

/*! @} */
