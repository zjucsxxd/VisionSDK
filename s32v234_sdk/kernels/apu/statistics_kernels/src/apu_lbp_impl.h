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
/**
* \file apu_lbp_impl.h
* \brief Linear Binary Pattern implementation for APEX
* \version
* \date
****************************************************************************/
#ifndef APU_LBP_IMPL_H
#define APU_LBP_IMPL_H

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/*!
Linear Binary Pattern computation of an input image
\brief returns histogram of lbp  
\param lpvInImg 	- [Input]  unsigned input image 
\param lpvOut	 	- [Output] histogram of lbp of 4x4 blocks 
\param lpvOut	 	- [Output] block norm for the histogram of lbp of 4x4 blocks 
\param isFirstTile	- [Input]  boolean: true if the algorithm is at its first tile
\param lStrideIn  	- [Input]  Source block width (in elements) including padding
\param chunkWidth	- [Input]  Block width
\param chunkHeight	- [Input]  Block height
\param lStrideOut  	- [Input]  Destination block width (in elements) including padding
*/
void lbp(vec08u* lpvInImg, vec16u* lpvOut, vec16u* lpvOutBlNorm, int lStrideIn, int chunkWidth, int chunkHeight, int lStrideOut);

#endif //#ifdef 

/*! @} */
