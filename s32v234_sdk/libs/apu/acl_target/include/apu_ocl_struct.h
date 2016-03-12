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
 
#ifndef _APU_OCL_STRUCT_H
#define _APU_OCL_STRUCT_H

#include <stdio.h>

// Memory access in simulation
//#define APU_OCL_SIM
#define APU_OCL_DBG


#ifdef APU_OCL_SIM
#define APU_OCL_SIM_HOST_IO
#include "apex_dma_iss.h"
#endif

//
typedef struct cl_argument  {
   size_t buf_size;     // in bytes, non-zero for host-allocated local memory
   void*  value;        // global pointer; NULL for local memory
} CL_DYN_ARG;

// kernel metadata structure


#define MAX_KERNEL_ARGS    8
#define MAX_KERNEL_NAME    64//32
enum {
    arg_is_local  = 0x0,
    arg_is_global = 0x1,
    arg_is_value  = 0x2
};

enum {
    arg_ro = 0x1,
    arg_wo = 0x2,
    arg_rw = 0x3
};

typedef struct
{  
   // __attribute__((work_group_size_hint(X, Y, Z)))
   int8_t  reqd_wg_size[4];               // 1
   // number of kernel arguments
   int16_t num_args;                      
   int16_t krnl_mode;                     // 1
   // argument type: __global ptr, __local ptr, or value
   int8_t  args_type[MAX_KERNEL_ARGS];    // 2
   // read only, write only or read_write (currently not in use)
   int8_t  args_rw  [MAX_KERNEL_ARGS];    // 2
   // compiler generatd datastructure pointer
   int32_t* krnl_ctx;                     // 1
   // kernel function pointer                     
   int32_t  krnl_addr;                    // 1
   // kernel set argument function pointer
   int32_t  krnl_setarg;                  // 1, 9 32-bit


} CL_KRNL_MD;


struct _acl_kernel    {


   // kernel arguments set with clSetKernelArg().
   // These are copied to the command queue command at enqueue.
   // If the argument is declared with the __local qualifier,
   // the arg_value entry must be NULL.
   CL_DYN_ARG dyn_arguments[MAX_KERNEL_ARGS];
   CL_KRNL_MD krnl_md;


};


enum {
    md_DMb_wg,
    md_DMb_wi,
    md_VMb_wg,
    md_VMb_wi,
    md_nargs
};

typedef struct
{
   int8_t  krnl_nm[MAX_KERNEL_NAME];   // 32 bytes
   int32_t krnl_md;                    // 4
#ifdef APU_OCL_SIM
   int32_t* krnl_rt;
#endif
} CL_KRNL_DB_ENTRY;

#ifdef APU_OCL_SIM
struct CL_KRNL_DB_XMEM_BUF_t
{
   int      mKernelID;
   int      mArgID;
   int      mAttr;
   int      mAddr;
   int      mSize;
   char     mName[128];
};
#endif

typedef _acl_kernel acl_kernel;

#endif // _APU_OCL_STRUCT_H
