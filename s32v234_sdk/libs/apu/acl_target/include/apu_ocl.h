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
 
#ifndef _APU_OCL_H
#define _APU_OCL_H


#include "apu_ocl_datatypes.h"
#include "apu_ocl_wg.h"
#include "apu_ocl_struct.h"
//#include <stdio.h>

//#define APU_OCL_SIM_HOST_IO

#define SMEM_HOST_START_DEFAULT     0x74000000
// Work array size: VSIZE defined in "common.h"
#define VSIZE     32

extern int32_t NUMBER_OF_CU;

#if 0
// 6.12.1 Work-Item Functions
#define get_global_id(_DIMINDX_)    apu_ocl::get_global_id_##_DIMINDX_##()
#define get_local_id(_DIMINDX_)     apu_ocl::get_local_id_##_DIMINDX_##()
#define get_group_id(_DIMINDX_)     apu_ocl::get_group_id_##_DIMINDX_##()

#define get_local_size(_DIMINDX_)   apu_ocl::get_local_size_##_DIMINDX_##()
#define get_global_size(_DIMINDX_)  apu_ocl::get_global_size_##_DIMINDX_##()
#define get_num_groups(_DIMINDX_)   apu_ocl::get_num_groups_##_DIMINDX_##()

// [APU_CL]
#define get_array_id(_DIMINDX_)     apu_ocl::get_array_id_##_DIMINDX_##()
#define get_array_size(_DIMINDX_)   apu_ocl::get_array_size_##_DIMINDX_##()

#else
// 6.12.1 Work-Item Functions
#define get_global_id(_DIMINDX_)    get_global_id_##_DIMINDX_##()
#define get_local_id(_DIMINDX_)     get_local_id_##_DIMINDX_##()
#define get_group_id(_DIMINDX_)     get_group_id_##_DIMINDX_##()

#define get_local_size(_DIMINDX_)   get_local_size_##_DIMINDX_##()
#define get_global_size(_DIMINDX_)  get_global_size_##_DIMINDX_##()
#define get_num_groups(_DIMINDX_)   get_num_groups_##_DIMINDX_##()

// [APU_CL]
#define get_array_id(_DIMINDX_)     get_array_id_##_DIMINDX_##()
#define get_array_size(_DIMINDX_)   get_array_size_##_DIMINDX_##()
#endif


//
namespace apu_ocl
{

   /*****************************
   * CL DATA TYPES
   ******************************/
#if 0
   /* Kernel context object */
   // Dynamic arguments with clSetKernelArg
   struct _cl_context   {
      size_t buf_size;  // only needed for host local mem alloc
      void * value;  /*w32*/
   };
   typedef _cl_context cl_context;
   
   /* Argument list Object */
   struct _acl_args_list    {     
             uint32_t    num_args;
      struct cl_argument arguments[MAX_KERNEL_ARGS];
   };
   typedef _acl_args_list acl_argument_list;
   
   /*****************
   * APU2 OCL RUN-TIME
   ******************/
   // [OPENCV]
   // index (compile-time configuration)
   // (conversion provided by macros for different return data types (scalar/vector))
  
  struct _acl_runtime_v
  {
   // vectorization dimension (work group index)
   vec32u wx;       // work group index 
   vec32u gx;       // global index      (in work items)
   vec16u wa;
  };
  
  typedef _acl_runtime_v acl_runtime_v;
#endif
  
  struct _acl_runtime
  {
      #if 0
      // indices require for each work-item
      uint32_t     wy, wz;   // work group index 
      uint32_t sx, sy, sz;   // local  index      (in work items)
      uint32_t     gy, gz;   // global index      (in work items)

            
      // sizes for work group execution      
      size_t lw_size[3];      // local work size      ( in work items)
      size_t gw_size[3];      // global size          ( in work items);
      size_t go_size[3];      // global size          ( in work items);
      size_t ng_size[3];      // num of work groups   ( in work groups);
      #endif
      size_t wa_size[3];      // work array size      ( in work groups);
      // work array indices
      // create an additional level of hierarchy (work-array) in apu run-time
      // (i.e. work-array is defined as a 32x1x1 work-group (single dimension))
      uint32_t     ax;     // work group index of work array (index [0])
      
      #if 0
      acl_runtime_v* rt_v;
      // arguments: global, local(host)
      acl_argument_list arguments_list;
      #endif
   
      /*****************************
      * Work-Item Built-In Functions
      ******************************/
      /*
      vec_size_t  get_global_id_0() { return rt_v->gx; }
      size_t      get_global_id_1() { return gy; }
      size_t      get_global_id_2() { return gz; }
      
      size_t      get_local_id_0()  { return sx; }
      size_t      get_local_id_1()  { return sy; }
      size_t      get_local_id_2()  { return sz; }
      
      vec_size_t  get_group_id_0()  { return rt_v->wx; }
      size_t      get_group_id_1()  { return wy; }
      size_t      get_group_id_2()  { return wz; }
      
      size_t      get_local_size_0()  { return lw_size[0]; }
      size_t      get_local_size_1()  { return lw_size[1]; }
      size_t      get_local_size_2()  { return lw_size[2]; }
      
      size_t      get_global_size_0()  { return gw_size[0]; }
      size_t      get_global_size_1()  { return gw_size[1]; }
      size_t      get_global_size_2()  { return gw_size[2]; }
      
      size_t      get_num_groups_0()  { return ng_size[0]; }
      size_t      get_num_groups_1()  { return ng_size[1]; }
      size_t      get_num_groups_2()  { return ng_size[2]; }
      */
      
      // [APU_CL]
      // size
      /*****************************
      * Internal Work-Array Built-In Functions
      ******************************/
      size_t      get_array_id_0()  { return ax; }
      size_t      get_array_size_0()  { return wa_size[0]; }
      size_t      get_array_size_1()  { return wa_size[1]; }
      size_t      get_array_size_2()  { return wa_size[2]; }
      


   };   

   
   //
   //typedef acl_argument_list cl_local;
   //typedef acl_argument_list cl_private;
   //typedef acl_argument_list cl_const;
   typedef _acl_runtime      acl_runtime;
   

}

char chess_storage(DMb)* kernel_add_ptr_arg(char chess_storage(DMb)* p, void* a);

#define KERNEL_DECL_ADD_ARG(type) \
    char chess_storage(DMb)* kernel_add_ ## type ## _arg(char chess_storage(DMb)* p, void* a);
    
KERNEL_DECL_ADD_ARG(short)
KERNEL_DECL_ADD_ARG(int)

extern volatile uint32_t DEBUG_BUF[32];

#endif // _APU_OCL_h
