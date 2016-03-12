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

#ifndef APU_REDUCTION_KN_H
#define APU_REDUCTION_KN_H

#include "stringify_macros.h" 

#define REDUCTION_K		apu_reduction
#define REDUCTION_KN	XSTR(REDUCTION_K)

#define REDUCTION_KN_IN	 "INPUT_0"
#define REDUCTION_KN_OUT "OUTPUT_0"

#ifdef APEX2_EMULATE
extKernelInfoDecl(REDUCTION_K);
/****************************************************************************/
/*! Reduction kernel implementation. Reduces 256 vectors on each CU to 256 scalars by accumulation.
\brief Reduction from 256 vectors on each CU to 256 scalars 

\param lIn0		- [Input]  unsigned 32bit vector input
\param lOut0	- [Output] unsigned 32bit scalar output
*****************************************************************************/
void REDUCTION_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

#endif //APEX2_EMULATE

#endif //#ifndef APU_REDUCTION_KN_H
