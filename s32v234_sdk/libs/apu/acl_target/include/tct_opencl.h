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

#ifndef _tct_opencl_h
#define _tct_opencl_h

#include <stddef.h>
#include "apu_ocl_datatypes.h"

#ifdef __OPENCL_C_VERSION__
#define GLOBAL(t)    __global    t
#define CONSTANT(t)  __constant  t
#else
#define GLOBAL(t)    t chess_storage(XMb)
#define CONSTANT(t)  t
#endif
/*
#ifdef __OPENCL_C_VERSION__
#define GLOBAL __global
#define LOCAL  __local
#define CONSTANT __constant
#else
#define GLOBAL
#define LOCAL
#define CONSTANT
#endif
*/

#define __attribute__(_A) 

//#define __constant   global
#define __const      const
#define __kernel     kernel

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;

uint get_work_dim();

size_t get_local_id(uint dim);      // s
size_t get_group_id(uint dim);      // w
size_t get_local_size(uint dim);    // S
size_t get_num_groups(uint dim);    // W
size_t get_global_offset(uint dim); // F
size_t get_global_size(uint dim);   // G

inline size_t get_global_id(uint dim) {
    return get_global_offset(dim) + get_group_id(dim) * get_local_size(dim) + get_local_id(dim);
}


typedef int    global_ptrdiff_t;
typedef vec32s vec_global_ptrdiff_t;
typedef vec32s global_ptrdiff_vt;

typedef vec32u vec_size_t;
// typedef vec32s vec_size_t;

typedef vec32s vint;
typedef vec32u vuint;

typedef vec16s vshort;
typedef vec16u vushort;



// support added in "tct_opencl_apu.h"
#if 1
typedef int cl_mem_fence_flags;
#define CLK_LOCAL_MEM_FENCE   0x00000001
#define CLK_GLOBAL_MEM_FENCE  0x00000002
#endif

void work_group_barrier(cl_mem_fence_flags) property(workgroup);
inline void barrier(cl_mem_fence_flags fl) {
    work_group_barrier(fl);
}

void work_group_barrier_hard(cl_mem_fence_flags) property(workgroup_must_yield);
inline void barrier_hard(cl_mem_fence_flags fl) {
    work_group_barrier_hard(fl);
}

//typedef size_t event_t;

/*
void async_work_group_copy_(event_t&) property(workgroup);
inline event_t async_work_group_copy(event_t event) {
    async_work_group_copy_(event);
    return event;
}*/

void wait_group_events(int, event_t*) property(workgroup_must_yield);

void mem_fence_(cl_mem_fence_flags flags) property(workgroup_must_yield);
inline void mem_fence(cl_mem_fence_flags fl) {
   mem_fence_(fl);
}

struct _cl_runtime {
    uint wd;        // get_work_dim

    size_t S[3];    // get_local_size
    size_t W[3];    // get_num_groups
    size_t F[3];    // get_global_offset
    size_t G[3];    // get_global_size
};

// single include files
//#include "tct_opencl_apu.h"

#endif
