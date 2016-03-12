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
* \file APU_lib.h
* \brief APU types & language extensions library
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#ifndef _APU_LIB_H_
#define _APU_LIB_H_


//#include "apu_config.h"
#include "apu_vec.hpp"
//#include "apu_vbool.h"
#include "apu_cond.hpp"

namespace APEX2
{

/****************************************************************************
* defines
****************************************************************************/

#define __cmem
#define __dmem


#ifndef chess_loop_range
#define chess_loop_range(a,b) 
#endif 

#ifndef chess_unroll_loop
#define	chess_unroll_loop(a) 
#endif

#ifndef restrict
#define restrict
#endif

#ifndef chess_storage
#define chess_storage(a) 
#endif

#ifndef chess_copy
#define chess_copy(a)  a
#endif


/// Define needed by the chess compiler to optimize inner loops. Not applicable for Windows
#define chess_prepare_for_pipelining
#define chess_no_warn_pipelining
}

#endif // _APU_LIB_H_
