/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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
 
#ifndef _APU_OCL_DATATYPES_H
#define _APU_OCL_DATATYPES_H

#include <stdint.h>
// should be in "/runtime/include/stddef.h"
typedef vec32u    vec_size_t;
// typedef vec32s    vec_size_t;
typedef uint32_t  cl_uint;


#ifdef __OPENCL_C_VERSION__
#define GLOBALA(t)    __global    t
#define LOCALA(t)    __local    t
typedef size_t  event_t;
#else
#define GLOBALA(t)    t chess_storage(XMb)
#define LOCALA(t)     t chess_storage(VMb)
//typedef vec32u  event_t;
typedef size_t  event_t;
#endif




#endif // _APU_OCL_DATATYPES_H