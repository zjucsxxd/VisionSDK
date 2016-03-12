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

#define swap(a, b) vswap(a, b, a > b);
#define min3(a, b, c) swap(a, b); swap(a, c);
#define max3(a, b, c) swap(a, c); swap(b, c);
#define min4(a, b, c, d) swap(a, b); swap(c, d); swap(a, c);
#define max4(a, b, c, d) swap(a, b); swap(c, d); swap(b, d);
#define min5(a, b, c, d, e) swap(a, b); swap(c, d); min3(a, c, e);
#define max5(a, b, c, d, e) swap(a, b); swap(c, d); max3(b, d, e);
#define min6(a, b, c, d, e, f) swap(a, b); swap(c, d); swap(e, f); min3(a, c, e);
#define max6(a, b, c, d, e, f) swap(a, b); swap(c, d); swap(e, f); max3(b, d, f);
#define minmax3(a, b, c) min3(a, b, c); swap(b, c);
#define minmax4(a, b, c, d) swap(a, b); swap(c, d); swap(a, c); swap(b, d);
#define minmax5(a, b, c, d, e) swap(a, b); swap(c, d); min3(a, c, e); max3(b, d, e);

#define minmax6(a, b, c, d, e, f) \
swap(a, b); swap(c, d); swap(e, f); min3(a, c, e); max3(b, d, f);

#define minmax7(a, b, c, d, e, f, g) \
swap(a, b); swap(c, d); swap(e, f); min4(a, c, e, g); max4(b, d, f, g);

#define minmax8(a, b, c, d, e, f, g, h) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); min4(a, c, e, g); max4(b, d, f, h);

#define minmax9(a, b, c, d, e, f, g, h, i) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); min5(a, c, e, g, i); max5(b, d, f, h, i);

#define minmax10(a, b, c, d, e, f, g, h, i, j) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); min5(a, c, e, g, i); \
max5(b, d, f, h, j);

#define minmax11(a, b, c, d, e, f, g, h, i, j, k) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); min6(a, c, e, g, i, k); \
max6(b, d, f, h, j, k);

#define minmax12(a, b, c, d, e, f, g, h, i, j, k, l) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); \
min6(a, c, e, g, i, k); max6(b, d, f, h, j, l);

#define minmax13(a, b, c, d, e, f, g, h, i, j, k, l, m) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); min3(a, c, e); \
min3(g, i, k); min3(a, g, m); max3(b, d, f); max3(h, j, l); max3(f, l, m);

#define minmax14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); swap(m, n); \
min3(a, c, e); min3(g, i, k); min3(a, g, m); max3(b, d, f); max3(h, j, l); max3(f, l, n);

/*!
   Calculate a 3x3 median filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_median_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
                 int bw, int bh)
{
   const vec08u* s0 = src - sstr;
   const vec08u* s1 = src;
   const vec08u* s2 = src + sstr;
   
   vec16s a0, a1, a2, a3, a4, a5;
   vec16s b0, b1, b2, b3, b4, b5;
   
   for (int y=0; y<bh; ++y) chess_loop_range(1,)
   {
      for (int x=0; x<bw; x+=2) chess_loop_range(1,)
      {
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         
         minmax6(a0, a1, a2, a3, a4, a5);
         
         b0 = a0; b1 = a1; b2 = a2; b3 = a3; b4 = a4;
         
         a5 = s0[x - 1];
         b5 = s0[x + 2];
         minmax5(a1, a2, a3, a4, a5);
         minmax5(b1, b2, b3, b4, b5);
         a5 = s1[x - 1];
         b5 = s1[x + 2];
         minmax4(a2, a3, a4, a5);
         minmax4(b2, b3, b4, b5);
         a5 = s2[x - 1];
         b5 = s2[x + 2];
         minmax3(a3, a4, a5);
         minmax3(b3, b4, b5);
         
         dst[x] = (vec08u)a4;
         dst[x + 1] = (vec08u)b4;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;      
   }
}

/*!
   Calculate a 5x5 median filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_median_5x5(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
                 int bw, int bh)
{  
   const vec08u* s0 = src - sstr - sstr;
   const vec08u* s1 = src - sstr;
   const vec08u* s2 = src;
   const vec08u* s3 = src + sstr;
   const vec08u* s4 = src + sstr + sstr;
   
   vec16s a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13;
   vec16s b7, b8, b9, b10, b11, b12, b13;
   
   for (int y=0; y<bh; ++y) chess_loop_range(1,)
   {
      for(int x=0; x<bw; x+=2) chess_loop_range(1,)
      {
          a0 = s0[x - 1];
          a1 = s0[x];
          a2 = s0[x + 1];
          a3 = s0[x + 2];
          a4 = s1[x - 1];
          a5 = s1[x];
          a6 = s1[x + 1];
          a7 = s1[x + 2];
          a8 = s2[x - 1];
          a9 = s2[x];
          a10 = s2[x + 1];
          a11 = s2[x + 2];
          a12 = s3[x - 1];
          a13 = s3[x];
          
          minmax14(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s3[x + 1];
          minmax13(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s3[x + 2];
          minmax12(a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x - 1];
          minmax11(a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x];
          minmax10(a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x + 1];
          minmax9(a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x + 2];
          minmax8(a6, a7, a8, a9, a10, a11, a12, a13);
          
          b7 = a7; b8 = a8; b9 = a9; b10 = a10; b11 = a11; b12 = a12;
          
          a13 = s0[x - 2];
          b13 = s0[x + 3];
          minmax7(a7, a8, a9, a10, a11, a12, a13);
          minmax7(b7, b8, b9, b10, b11, b12, b13);
          a13 = s1[x - 2];
          b13 = s1[x + 3];
          minmax6(a8, a9, a10, a11, a12, a13);
          minmax6(b8, b9, b10, b11, b12, b13);
          a13 = s2[x - 2];
          b13 = s2[x + 3];
          minmax5(a9, a10, a11, a12, a13);
          minmax5(b9, b10, b11, b12, b13);
          a13 = s3[x - 2];
          b13 = s3[x + 3];
          minmax4(a10, a11, a12, a13);
          minmax4(b10, b11, b12, b13)
          a13 = s4[x - 2];
          b13 = s4[x + 3];
          minmax3(a11, a12, a13);
          minmax3(b11, b12, b13);
          
          dst[x] = (vec08u)a12;
          dst[x + 1] = (vec08u)b12;
      }
      
      s0   = s1;
      s1   = s2; 
      s2   = s3;
      s3   = s4;
      s4  += sstr;
      dst += dstr;      
   }
}
#endif /* ACF_KERNEL_IMPLEMENTATION */
