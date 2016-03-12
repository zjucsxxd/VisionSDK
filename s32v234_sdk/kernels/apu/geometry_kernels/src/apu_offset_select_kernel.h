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

#ifndef APU_OFFS_SELECT_KN_H
#define APU_OFFS_SELECT_KN_H



#include "stringify_macros.h"


#ifdef APEX2_EMULATE
#include "apu_config.hpp"
#endif

#define OFFS_SELECT_K					apu_offset_select
#define OFFS_SELECT_KN					XSTR(OFFS_SELECT_K)

#define OFFS_SELECT_SORTED_K			apu_offset_select_sorted
#define OFFS_SELECT_SORTED_KN			XSTR(OFFS_SELECT_SORTED_K)


#define OFFS_SELECT_KN_IN		"INPUT"
#define OFFS_SELECT_KN_OUT		"OUTPUT"
#define OFFS_SELECT_KN_IN_OFFSS		"IN_OFFSS"
#define OFFS_SELECT_KN_IN_NR_OFFSS	"IN_NR_OFFSS"

#define OFFS_SELECT_KN_SELECTION_NEIGH_X	3
#define	OFFS_SELECT_KN_SELECTION_NEIGH_Y	5

#define OFFS_SELECT_KN_MAX_VECTOR_SIZE		128

#ifdef APEX2_EMULATE
#define OFFS_SELECT_KN_OUT_WIDTH		APU_VSIZE
#else
#define OFFS_SELECT_KN_OUT_WIDTH		32
#endif

#define OFFS_SELECT_KN_OUT_HEIGHT		(OFFS_SELECT_KN_MAX_VECTOR_SIZE/OFFS_SELECT_KN_OUT_WIDTH + 1)

#ifdef APEX2_EMULATE
extKernelInfoDecl(OFFS_SELECT_K);
int OFFS_SELECT_K(kernel_io_desc lImgInA, kernel_io_desc lImgOut, kernel_io_desc lOffsets/*X, kernel_io_desc lOffsetsY*/, kernel_io_desc lNrOffsets/*, kernel_io_desc lNeighX, kernel_io_desc lNeighY*/);

extKernelInfoDecl(OFFS_SELECT_SORTED_K);
int OFFS_SELECT_SORTED_K(kernel_io_desc lImgInA, kernel_io_desc lImgOut, kernel_io_desc lOffsets/*X, kernel_io_desc lOffsetsY*/, kernel_io_desc lNrOffsets/*, kernel_io_desc lNeighX, kernel_io_desc lNeighY*/);

#endif

#endif