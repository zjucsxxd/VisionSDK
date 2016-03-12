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
#include <math.h>

void apu_flt_box_1x3(
               vec16s* dst, int dstr,
         const vec16s* src, int sstr,
               int bw, int bh
)
{
   /** process 2 pixels at a time
    * load 4 pixels, store 2 pixels
    * use the partial addition from the middle two rows for the rows above and below 
    */
   for (int h = 0; h < bh; h+=2)  chess_loop_range(1,) {
      /* Row Pointers */
      const vec16s* restrict src1 = src-sstr;
      const vec16s* restrict src2 = src;
      const vec16s* restrict src3 = src+sstr;
      const vec16s* restrict src4 = src3+sstr;
      vec16s* restrict dst1 = dst;
      vec16s* restrict dst2 = dst + dstr;

      vec16s sum1, sum2, sum_partial, src1_val, src2_val, src3_val, src4_val;

      /* Loop Preamble */
      src1_val = *src1++;
      src2_val = *src2++;
      src3_val = *src3++;
      src4_val = *src4++;

      sum_partial = src2_val + src3_val;
      sum1 = src1_val + sum_partial;
      sum2 = src4_val + sum_partial;

      /* Core loop */
      for (int w = 0; w < bw; w++) chess_loop_range(1,) {
         src1_val = *src1++;
         src2_val = *src2++;
         src3_val = *src3++;
         src4_val = *src4++;

         *dst1++ = sum1;
         *dst2++ = sum2;

         sum_partial = src2_val + src3_val;
         sum1 = src1_val + sum_partial;
         sum2 = src4_val + sum_partial;
      }
      src += 2*sstr;
      dst += 2*dstr;
   }
}

void apu_flt_box_3x1(
               vec16s* dst, int dstr,
         const vec16s* src, int sstr,
               int bw, int bh
)
{
   for (int h = 0; h < bh; h++)  chess_loop_range(1,) {
      const vec16s* restrict src_temp = src-1;
      vec16s* restrict dst_temp = dst;

      vec16s sum, l, m, r;
      sum  = l = *src_temp++;
      sum += m = *src_temp++;
      sum += r = *src_temp++;

      for (int w = 0; w < bw; w++) chess_loop_range(1,) chess_unroll_loop(2) {
         l = m >> 0, m = r >> 0, r = *src_temp++; // compiler doesn't produce optimal code without shifting by 0
         *dst_temp++ = sum;
         sum = l+m+r;
      }
      src += sstr;
      dst += dstr;
   }
}

// http://www.hackersdelight.org/divcMore.pdf Page 6
vec16u vdivu_by9(vec16u n)
{
   vec16u q, r;
   
   q = n - (n >> 3);
   q = q + (q >> 6);
   q = q >> 3;
   r = n - q * 9;
   
   return q + ((r + 7) >> 4);
}

void             
apu_flt_box_3x3( 
               vec08u* dst, int dstr,
         const vec08u* src, int sstr,
               int bw, int bh
)
{  
   for (int y = 0; y < bh; ++y) chess_loop_range(1,) {
      for (int x = 0; x < bw; ++x) chess_loop_range(1,) {
         vec16u sum = 0;
         
         for (int fy = -1; fy < 2; ++fy) chess_loop_range(1,) {
            for (int fx = -1; fx < 2; ++fx) chess_loop_range(1,) { 
               sum += (vec16u)src[(y + fy) * sstr + (x + fx)];
            }
         }
         //divide by 9
         dst[y*dstr+x] = (vec08u)((vdivu_by9(sum << 1) + 1) >> 1);
      }
   }
}

// Local helper functions
static inline vec16s _box_3x3(const vec16s *src, int stride);
static inline vec16s _box_5x5(const vec16s *src, int stride);
static inline vec16s _box_3x3_copy(const vec16s *src, int stride, vec16s prev);
static inline vec16s _box_5x5_copy(const vec16s *src, int stride, vec16s prev);

void apu_flt_box_3x3(
               vec16s* dst, int dstr,
         const vec16s* src, int sstr,
               int bw, int bh
)
{
//! Apply box filter
    vec16s prev;
    for (int h = 0; h < bh; h++) chess_loop_range(1,) {
        prev = _box_3x3(&src[0], sstr);  // first column in each row adds up 3x3 pixels
        dst[0] = prev;
        for (int w = 1; w < bw; w++) chess_loop_range(1,) {
            prev = _box_3x3_copy(&src[w], sstr, prev); // use previous sum to calculate current pixel sum
            dst[w] = prev;
        }
        src += sstr;
        dst += dstr;
    }
}

//! [apply 3x3 box]
// summation of 3x3 pixels
static inline vec16s _box_3x3(const vec16s *src, int stride)
{
    vec16s t0 = src[-stride-1] + src[-stride] + src[-stride+1]
                + src[-1] + src[0] + src[1] + src[stride-1] + src[stride] + src[stride+1];

    return t0;
}

// to decrease # of addition, subtract colomn[-2] from previous sum and add column[1]
static inline vec16s _box_3x3_copy(const vec16s *src, int stride, vec16s prev)
{
    vec16s tp = -src[-stride-2] + src[-stride+1]
                -src[-2]        + src[1]
                -src[stride-2]  + src[stride+1];

    return prev+tp;
}
//! [apply 3x3 box]

void apu_flt_box_5x5( 
               vec16s* dst, int dstr,
         const vec16s* src, int sstr,
               int bw, int bh
)
{
//! Apply box filter
    vec16s prev;
    for (int h = 0; h < bh; h++) chess_loop_range(1,) {
        prev = _box_5x5(&src[0], sstr);  // first column in each row adds up 5x5 pixels
        dst[0] = prev;
        for (int w = 1; w < bw; w++) chess_loop_range(1,) {
            prev = _box_5x5_copy(&src[w], sstr, prev); // use previous sum to calculate current pixel sum
            dst[w] = prev;
        }
        src += sstr;
        dst += dstr;
    }
}

//! [apply 5x5 box]
// summation of 5x5 pixels
static inline vec16s _box_5x5(const vec16s *src, int stride)
{
    vec16s t0 = src[-2*stride-2] + src[-2*stride-1] + src[-2*stride] + src[-2*stride+1] + src[-2*stride+2];
    vec16s t1 = src[-stride-2]   + src[-stride-1]   + src[-stride]   + src[-stride+1]   + src[-stride+2];
    vec16s t2 = src[-2]          + src[-1]          + src[0]         + src[1]           + src[2];
    vec16s t3 = src[stride-2]    + src[stride-1]    + src[stride]    + src[stride+1]    + src[stride+2];
    vec16s t4 = src[2*stride-2]  + src[2*stride-1]  + src[2*stride]  + src[2*stride+1]  + src[2*stride+2];

    return t0 + t1 + t2 + t3 + t4;
}

// to decrease # of addition, subtract colomn[-3] from previous sum and add column[2]
static inline vec16s _box_5x5_copy(const vec16s *src, int stride, vec16s prev)
{
    vec16s tp = -src[-2*stride-3]   + src[-2*stride+2]
                -src[-stride-3]     + src[-stride+2]
                -src[-3]            + src[2]
                -src[stride-3]      + src[stride+2]
                -src[2*stride-3]    + src[2*stride+2];

    return prev+tp;
}
//! [apply 5x5 box]

#endif /* ACF_KERNEL_IMPLEMENTATION */
