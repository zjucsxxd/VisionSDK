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
   Calculate a 3x3 dilate filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_dilate_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   
   // Loop
   // vec16s a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   // vec16s b_max, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) 
   {
      // Neighbors:
      const vec08u* ps0 = (src-1) + (y-1)*sstr;
      const vec08u* ps1 = (src-1) + (y  )*sstr;
      const vec08u* ps2 = (src-1) + (y+1)*sstr;
      
      vec16s chess_storage(V0) s0 = *ps0++;
      vec16s chess_storage(V1) s1 = *ps1++;
      vec16s chess_storage(V2) s2 = *ps2++;

      vec16s chess_storage(V4) amax = s0;    s0 = *ps0++;
               vswap(s1, amax, s1 > amax);   s1 = *ps1++;
               vswap(s2, amax, s2 > amax);   s2 = *ps2++;
      vec16s chess_storage(V5) bmax = s0;    s0 = *ps0++;
               vswap(s1, bmax, s1 > bmax);   s1 = *ps1++;
               vswap(s2, bmax, s2 > bmax);   s2 = *ps2++;
      
      for (int x = 0; x < bw; ++x) chess_loop_range(1,) 
      {
         vec16s chess_storage(V6) cmax = s0;    s0 = *ps0++;
                  vswap(s1, cmax, s1 > cmax);   s1 = *ps1++;
                  vswap(s2, cmax, s2 > cmax);   s2 = *ps2++;
               
         // Compare and find max
         vec16s o = amax;
         vec16s b = bmax; vswap(o, b, o < b);
         vec16s c = cmax; vswap(o, c, o < c);
         
         //save max of common pixels
         amax = bmax; bmax = cmax;
         // Assign to output
         dst[x] = (vec08u)o;
      }
      
      // Proceed to next line
      dst += dstr;
   }
}

#if 0
void
apu_flt_dilate_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const vec08u* s0 = src - sstr;
   const vec08u* s1 = src;
   const vec08u* s2 = src + sstr;
   
   // Loop
   vec16s a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   vec16s b_max, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) 
   {
      for (int x = 0; x < bw; x+=2) chess_loop_range(1,) 
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];
         
         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];
            
         // Compare and find max
         a_max = a0;

         vswap(a1, a_max, a1 > a_max);
         vswap(a2, a_max, a2 > a_max);
         vswap(a3, a_max, a3 > a_max);
         vswap(a4, a_max, a4 > a_max);
         vswap(a5, a_max, a5 > a_max);
         
         //save max of common pixels
         b_max = a_max;
         
         vswap(a6, a_max, a6 > a_max);
         vswap(a7, a_max, a7 > a_max);
         vswap(a8, a_max, a8 > a_max);
         
         vswap(b6, b_max, b6 > b_max);
         vswap(b7, b_max, b7 > b_max);
         vswap(b8, b_max, b8 > b_max);
        
         // Assign to output
         dst[x]      = (vec08u)a_max;
         dst[x + 1]  = (vec08u)b_max;
      }
      
      // Proceed to next block
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;
   }
}
#endif

/*!
   Calculate a 3x3 dilate filter (signed 16 bit).

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_dilate_3x3(
            vec16s* dst, int dstr,
      const vec16s* src, int sstr,
            int bw, int bh
)
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const vec16s* s0 = src - sstr;
   const vec16s* s1 = src;
   const vec16s* s2 = src + sstr;
   
   // Loop
   vec16s a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   vec16s b_max, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) 
   {
      for (int x = 0; x < bw; x+=2) chess_loop_range(1,) 
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];
         
         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];
            
         // Compare and find max
         a_max = a0;

         vswap(a1, a_max, a1 > a_max);
         vswap(a2, a_max, a2 > a_max);
         vswap(a3, a_max, a3 > a_max);
         vswap(a4, a_max, a4 > a_max);
         vswap(a5, a_max, a5 > a_max);
         
         //save max of common pixels
         b_max = a_max;
         
         vswap(a6, a_max, a6 > a_max);
         vswap(a7, a_max, a7 > a_max);
         vswap(a8, a_max, a8 > a_max);
         
         vswap(b6, b_max, b6 > b_max);
         vswap(b7, b_max, b7 > b_max);
         vswap(b8, b_max, b8 > b_max);
        
         // Assign to output
         dst[x]      = (vec16s)a_max;
         dst[x + 1]  = (vec16s)b_max;
      }
      
      // Proceed to next block
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;
   }
}
  
/*!
   Calculate a 3x3 erode filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_erode_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   
   // Loop
   // vec16s a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   // vec16s b_max, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) 
   {
      // Neighbors:
      const vec08u* ps0 = (src-1) + (y-1)*sstr;
      const vec08u* ps1 = (src-1) + (y  )*sstr;
      const vec08u* ps2 = (src-1) + (y+1)*sstr;
      
      vec16s chess_storage(V0) s0 = *ps0++;
      vec16s chess_storage(V1) s1 = *ps1++;
      vec16s chess_storage(V2) s2 = *ps2++;

      vec16s chess_storage(V4) amin = s0;    s0 = *ps0++;
               vswap(s1, amin, s1 < amin);   s1 = *ps1++;
               vswap(s2, amin, s2 < amin);   s2 = *ps2++;
      vec16s chess_storage(V5) bmin = s0;    s0 = *ps0++;
               vswap(s1, bmin, s1 < bmin);   s1 = *ps1++;
               vswap(s2, bmin, s2 < bmin);   s2 = *ps2++;
      
      for (int x = 0; x < bw; ++x) chess_loop_range(1,) 
      {
         vec16s chess_storage(V6) cmin = s0;    s0 = *ps0++;
                  vswap(s1, cmin, s1 < cmin);   s1 = *ps1++;
                  vswap(s2, cmin, s2 < cmin);   s2 = *ps2++;
               
         // Compare and find min
         vec16s o = amin;
         vec16s b = bmin; vswap(o, b, o > b);
         vec16s c = cmin; vswap(o, c, o > c);
         
         //save max of common pixels
         amin = bmin; bmin = cmin;
         // Assign to output
         dst[x] = (vec08u)o;
      }
      
      // Proceed to next line
      dst += dstr;
   }
}

/*!
   Calculate a 3x3 erode filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
#if 0
void
apu_flt_erode_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const vec08u* s0 = src - sstr;
   const vec08u* s1 = src;
   const vec08u* s2 = src + sstr;
   
   // Loop
   vec16s a_min, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   vec16s b_min, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) 
   {
      for (int x = 0; x < bw; x+=2) chess_loop_range(1,) 
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];
         
         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];
            
         // Compare and find min
         a_min = a0;

         vswap(a1, a_min, a1 < a_min);
         vswap(a2, a_min, a2 < a_min);
         vswap(a3, a_min, a3 < a_min);
         vswap(a4, a_min, a4 < a_min);
         vswap(a5, a_min, a5 < a_min);
         
         //save min of common pixels
         b_min = a_min;
         
         vswap(a6, a_min, a6 < a_min);
         vswap(a7, a_min, a7 < a_min);
         vswap(a8, a_min, a8 < a_min);
         
         vswap(b6, b_min, b6 < b_min);
         vswap(b7, b_min, b7 < b_min);
         vswap(b8, b_min, b8 < b_min);
        
         // Assign to output
         dst[x]      = (vec08u)a_min;
         dst[x + 1]  = (vec08u)b_min;
      }
      
      // Proceed to next block
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;
   }
}
#endif
#endif /* ACF_KERNEL_IMPLEMENTATION */
