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
 
#ifndef _APU_OCL_WG_H
#define _APU_OCL_WG_H

#include <stdint.h>
#include "apu_ocl_datatypes.h"

#if 0
typedef enum {
  CLK_LOCAL_MEM_FENCE   = 0x1,
  CLK_GLOBAL_MEM_FENCE  = 0x2
} cl_mem_fence_flags;

#endif
   

   
#define ACL_DECLARE_ASYNC_COPY_FUNCS(APUTYPE_LOCAL, GENTYPE_LOCAL, GENTYPE_GLOBAL)      \
   event_t async_work_group_copy(LOCALA(GENTYPE_LOCAL)*   dst, const GLOBALA(GENTYPE_GLOBAL)* src, size_t num_gentypes, const event_t& event) property(workgroup);\
   event_t async_work_group_copy(LOCALA(APUTYPE_LOCAL)*   dst, const GLOBALA(GENTYPE_GLOBAL)* src, size_t num_gentypes, const event_t& event) property(workgroup);\
   event_t async_work_group_copy(LOCALA(APUTYPE_LOCAL)*   dst, const GLOBALA(GENTYPE_GLOBAL)@ src, size_t num_gentypes, const event_t& event) property(workgroup);\
   event_t async_work_group_copy(GLOBALA(GENTYPE_GLOBAL)* dst, const LOCALA(GENTYPE_LOCAL)*   src, size_t num_gentypes, const event_t& event) property(workgroup);\
   event_t async_work_group_copy(GLOBALA(GENTYPE_GLOBAL)* dst, const LOCALA(APUTYPE_LOCAL)*   src, size_t num_gentypes, const event_t& event) property(workgroup);\
   event_t async_work_group_copy(GLOBALA(GENTYPE_GLOBAL)@ dst, const LOCALA(APUTYPE_LOCAL)*   src, size_t num_gentypes, const event_t& event) property(workgroup);


#define ACL_DECLARE_ASYNC_COPY_FUNCS_2D(APUTYPE_LOCAL, GENTYPE_LOCAL, GENTYPE_GLOBAL)           \
   event_t async_work_group_copy_2d(      LOCALA(GENTYPE_LOCAL)*   dst, size_t dst_stride,      \
                                    const GLOBALA(GENTYPE_GLOBAL)* src, size_t src_stride,      \
                                    size_t num_gentypes_w, size_t num_gentypes_h,               \
                                    const event_t& event) property(workgroup);                        \
   event_t async_work_group_copy_2d(      LOCALA(APUTYPE_LOCAL)*   dst, size_t dst_stride,      \
                                    const GLOBALA(GENTYPE_GLOBAL)* src, size_t src_stride,      \
                                    size_t num_gentypes_w, size_t num_gentypes_h,               \
                                    const event_t& event) property(workgroup);                        \
   event_t async_work_group_copy_2d(      LOCALA(APUTYPE_LOCAL)*   dst, size_t dst_stride,      \
                                    const GLOBALA(GENTYPE_GLOBAL)@ src,   size_t src_stride,    \
                                    size_t num_gentypes_w, size_t num_gentypes_h,               \
                                    const event_t& event) property(workgroup);
  
   
   // async_work_group_copy
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec32s,   int32_t,  int32_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec32u,   uint32_t, uint32_t);
   
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec16s,   int16_t,  int16_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec16u,   uint16_t, uint16_t);
   
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec08s,   int8_t,  int8_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec08u,   uint8_t, uint8_t);
   
   //
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec_uchar16, uchar16, uchar16);
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec_int4,    int4,    int4);
   ACL_DECLARE_ASYNC_COPY_FUNCS(vec_int8,    int8,    int8);

   
   // async_work_group_copy_2d
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec32s, int32_t,  int32_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec32u, uint32_t, uint32_t);
   
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec16s, int16_t,  int16_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec16u, uint16_t, uint16_t);
   
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec08s, int8_t,  int8_t);
   ACL_DECLARE_ASYNC_COPY_FUNCS_2D(vec08u, uint8_t, uint8_t);

   // wait_group_events
   void wait_group_events(int num_events, event_t* event_list) property(workgroup_must_yield);
   

#endif // _APU_OCL_WG_h