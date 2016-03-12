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
 
#ifndef _APU_OCL_MEMACCESS_H
#define _APU_OCL_MEMACCESS_H

#include <stdint.h>
#include "apu_ocl_datatypes.h"

#define MCE_ENABLE      1

//
void apex_loadglobal_start(uint8_t chNo, uint8_t chType, const uint16_t ll_buf_idx);
void apex_loadglobal_wait(uint8_t chnum, uint8_t chtype);

namespace apu_ocl
{
   extern void load_global_init(
                                    int32_t globalAddr,       // src addr    
                                    int32_t dstAddr,          // SIN0/SIN1
                                    int32_t srcDataSpan,      // pointer increment
                                    int32_t num_wg,
                                    const int32_t  element_size,
                                    const int32_t* lw_size,
                                    const int32_t* ng_size,
                                    const int32_t* gw_size,
                                    const int32_t  local_addr,
                                    uint16_t ll_buf_index
                                 );      

   extern void load_global (                     vec08u*   dst, uint32_t  dst_span,
                          const int8_t chess_storage(XMb)@ src, uint32_t  src_span,
                                                 uint32_t  size_x, uint32_t size_y,
                                                 uint32_t  algn,
                                                 uint16_t  ll_buf_idx,
                                                 uint8_t   chnum ) ;                           
                                 
   extern void load_global (  vec08u* dst, 
                              const int8_t* const src, 
                              vec_size_t* src_offset, 
                              uint32_t size, 
                              uint32_t algn,
                              uint16_t ll_buf_index,
                              uint8_t  chnum);   
   
   extern void store_global(  int8_t* dst, 
                              vec_size_t* dst_offset, 
                              const vec08u* const src, 
                              uint32_t size, 
                              uint32_t algn,
                              uint16_t ll_buf_idx);   
   
}

#endif // _APU_OCL_MEMACCESS_H
