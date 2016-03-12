/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/
/*!*********************************************************************************
*  \file apu_filter.c
*  \brief APU filter kernels.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "apu_filter_impl.h"

/*!
   Applies a 3x3 prewitt filter in the x direction.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void  
apu_flt_prewitt_3x3_x(
         vec16s* dst, int dstr,        
   const vec08u* src, int sstr,        
              int bw, int bh )                  
{
   const vec08u* s0 = src - sstr;
   const vec08u* s1 = src;
   const vec08u* s2 = src + sstr;
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec16s r;
         r  = s0[bx + 1]; 
         r -= s0[bx - 1];
         r += s1[bx + 1];
         r -= s1[bx - 1];
         r += s2[bx + 1];
         r -= s2[bx - 1];

         dst[bx] = r;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;  
   }
}

/*!
   Applies a 3x3 prewitt filter in the y direction.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void  
apu_flt_prewitt_3x3_y(
         vec16s* dst, int dstr,        
   const vec08u* src, int sstr,        
              int bw, int bh )                     
{
   const vec08u* s0 = src - sstr;
   const vec08u* s1 = src;
   const vec08u* s2 = src + sstr;
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec16s r;
         r  = s0[bx - 1]; 
         r += s0[bx];
         r += s0[bx + 1];
         r -= s2[bx - 1];
         r -= s2[bx];
         r -= s2[bx + 1];

         dst[bx] = r;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;  
   }
}

#endif /* ACF_KERNEL_IMPLEMENTATION */