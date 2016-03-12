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

#ifndef APU_LBP_KN_H
#define APU_LBP_KN_H

#include "stringify_macros.h"

#define LBP_K		apu_lbp
#define LBP_KN		XSTR(LBP_K)

#define LBP_KN_InImg		 "LBP_InImg"
#define LBP_KN_OUT			 "LBP_OUT"
#define LBP_KN_OUT_BL_NORM	 "LBP_OUT_BlNorm"


#ifdef APEX2_EMULATE
extKernelInfoDecl(LBP_K);
void LBP_K(kernel_io_desc lInImg, kernel_io_desc lOut, kernel_io_desc lOutBlNorm);
#endif //APEX2_EMULATE

#endif //#ifndef APU_LBP_KN_H

