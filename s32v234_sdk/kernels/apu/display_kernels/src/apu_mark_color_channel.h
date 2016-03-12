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

#ifndef APU_MARK_COL_H
#define  APU_MARK_COL_H

#include "stringify_macros.h"

#define	MARK_COL_K		apu_mark_color_channel
#define MARK_COL_KN		XSTR(MARK_COL_K)

#define MARK_COL_KN_IN		"INPUT_IMAGE"
#define MARK_COL_KN_OUT		"OUTPUT"
#define MARK_COL_KN_MARKER	"INPUT_MARKER"
#define MARK_COL_KN_CHN_IDX	"INPUT_CHANNEL_INDEX"
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp"
using namespace APEX2;

extKernelInfoDecl(MARK_COL_K);
void MARK_COL_K(kernel_io_desc lInImage, kernel_io_desc lInMarker, kernel_io_desc lInChannelIndex, kernel_io_desc lOut);

#endif

#endif 
