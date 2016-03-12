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
//
#ifndef APEX2_EMULATE
chess_properties {
   pointer_index_type      DMb, DMh, DMw: int15;
   pointer_postmodify_type DMb, DMh, DMw: int5; 
   pointer_index_type      VMb, VMw: int12;
   pointer_postmodify_type VMb, VMw: int5;    
};
#endif


#include "apu_filter_impl.h"

static inline vec16s apu_flt_sobel_3x3_x(const vec08u* src, int sstr);
static inline vec16s apu_flt_sobel_3x3_y(const vec08u* src, int sstr);
static inline vec16s apu_flt_sobel_5x5_x(const vec08u* src, int sstr);
static inline vec16s apu_flt_sobel_5x5_y(const vec08u* src, int sstr);

/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_sobel_3x3(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s tx = apu_flt_sobel_3x3_x(&src[x], sstr);
         //vif (tx<0)     { tx = -tx; } vendif
         tx = vabs(tx);
         vec16s ty = apu_flt_sobel_3x3_y(&src[x], sstr);
         //vif (ty<0)     { ty = -ty; } vendif
         ty = vabs(ty);
   
         vec16u t = tx+ty;
         // vif (t > 255)  { t  = 255;   } vendif
         t  = vsat(t, 0, 255);
   
         dst[x] = (vec08u)t;
      }
      
      src += sstr;
      dst += dstr;
   }
}

/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 3x3.

   \param dst_0  - [Output] Destination block pointer
   \param dstr_0 - [Input]  Destination block stride
   \param dst_1  - [Output] Destination block pointer
   \param dstr_1 - [Input]  Destination block stride
   \param src    - [Input]  Source block pointer
   \param sstr   - [Input]  Source block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
apu_flt_sobel_3x3_xy(
            vec08u* dst_0, int dstr_0,
            vec08u* dst_1, int dstr_1,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s tx = apu_flt_sobel_3x3_x(&src[x], sstr);

         vec16s ty = apu_flt_sobel_3x3_y(&src[x], sstr);
   
         dst_0[x] = (vec08u)vsat(tx, 0, 255);
         dst_1[x] = (vec08u)vsat(ty, 0, 255);
      }
      
      src   += sstr;
      dst_0 += dstr_0;
      dst_1 += dstr_1;
   }
}

void
apu_flt_sobel_3x3_x(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s tx = apu_flt_sobel_3x3_x(&src[x], sstr);

         // Absolute Value & Saturation
         tx = vsat(tx, 0, 255);
        
         dst[x] = (vec08u)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void apu_flt_sobel_3x3_x(
            vec08s* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
//! 3x3 Sobel x filter
    for (int h = 0; h < bh; h++)
    {
        for (int w = 0; w < bw; w++)
        {
            vec16s tx = (apu_flt_sobel_3x3_x(&src[w], sstr)>>3);
            dst[w] = (vec08s)vsat(tx, -128, 127);    // clamp to [-128,127]
        }
        src += sstr;
        dst += dstr;
    }
}

/*!
   Calculate first order derivative y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_sobel_3x3_y(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s ty = apu_flt_sobel_3x3_y(&src[x], sstr);
         
         // Absolute Value & Saturation
         ty = vsat(ty, 0, 255);
         
         dst[x] = (vec08u)ty;
      }
      
      src += sstr;
      dst += dstr;
   }
}

/*!
   Calculate first order derivative y using sobel 3x3.
   (unsigned 8 bit to signed 8 bit)

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void apu_flt_sobel_3x3_y(
            vec08s* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
//! 3x3 Sobel y filter
    for (int h = 0; h < bh; h++)
    {
        for (int w = 0; w < bw; w++)
        {
            vec16s ty = (apu_flt_sobel_3x3_y(&src[w], sstr)>>3);
            dst[w] = (vec08s)vsat(ty, -128, 127);    // clamp to [-128, 127]
        }
        src += sstr;
        dst += dstr;
    }
}

/*! 
   Saturation step for 16 bits sobel results to 8 bits. 
   Scales the output by 8, and rounds up ( (input >> 2) + 1 ) >> 1 )
*/
void apu_flt_saturate_sobel_3x3 (
               vec08s* dst, int dstr,
         const vec16s* src, int sstr,
               int bw, int bh
)
{
   for (int16u h = 0; h < bh; h++) chess_loop_range(1,) // skip the check for bh being 0
   {
      const vec16s* restrict ps = src; // need temp ptrs because dst and src incremented by stride lenghts
      vec08s* restrict pd = dst;
      
      vec16s a = *ps++;
      vec16s b = *ps++;
      
      for (int16u w = 0; w < bw; w+=2) chess_loop_range(1,)
      {
         *pd++ = (vec08s)vsat(((a + 4) >> 3),-128,127);
         a = *ps++;
         *pd++ = (vec08s)vsat(((b + 4) >> 3),-128,127);
         b = *ps++;
      }
      dst += dstr;
      src += sstr;
   }
}
/*!
   Apply a 3x3 Sobel x filter to an image
   (unsigned 8-bit -> signed 16-bit -> scaled signed 8-bit)

   \param dst     - [Output]  Pointer to the destination buffer.
   \param dstr    - [Input]   Stride of the destination buffer.
   \param dst16s  - [Output]  Pointer to the 16-bit output buffer before the saturation step
   \param src     - [Input]   Pointer to the source image. The source image is assumed to be padded as (n,s,w,e) = (1,1,2,2).
   \param sstr    - [Input]   Stride of the padded source image.
   \param bw      - [Input]   Chunk width.
   \param bh      - [Input]   Chunk height.
*/
void apu_flt_sobel_3x3_x(
               vec08s* dst, int dstr,
               vec16s* dst16s,
         const vec08u* src, int sstr,
               int bw, int bh
)
{
   ht::apu_flt_centraldx_3x3( dst16s, dstr, src, sstr, bw, bh, 1, 2, 1 );
   apu_flt_saturate_sobel_3x3( dst, dstr, dst16s, dstr, bw, bh ); 
}
/*!
   Apply a 3x3 Sobel y filter to an image
   (unsigned 8-bit -> signed 16-bit -> scaled signed 8-bit)

   \param dst     - [Output]  Pointer to the destination buffer.
   \param dstr    - [Input]   Stride of the destination buffer.
   \param dst16s  - [Output]  Pointer to the 16-bit output buffer before the saturation step
   \param src     - [Input]   Pointer to the source image. The source image is assumed to be padded as (n,s,w,e) = (1,1,2,2).
   \param sstr    - [Input]   Stride of the padded source image.
   \param bw      - [Input]   Chunk width.
   \param bh      - [Input]   Chunk height.
*/
void apu_flt_sobel_3x3_y (
               vec08s* dst, int dstr,
               vec16s* dst16s,
         const vec08u* src, int sstr,
               int bw, int bh
)
{
   ht::apu_flt_centraldy_3x3( dst16s, dstr, src, sstr, bw, bh, 1, 2, 1 );
   apu_flt_saturate_sobel_3x3( dst, dstr, dst16s, dstr, bw, bh ); 
}

/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_sobel_5x5(            
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s tx = apu_flt_sobel_5x5_x(&src[x], sstr);
         //vif (tx<0)     { tx = -tx; } vendif
         tx = vabs(tx);
         
         vec16s ty = apu_flt_sobel_5x5_y(&src[x], sstr);
         //vif (ty<0)     { ty = -ty; } vendif
         ty = vabs(ty);
         
         vec16u t = tx+ty;
         vif (t > 255)  { t  = 255; } vendif
   
         dst[x] = (vec08u)t;
      }
      
      src += sstr;
      dst += dstr;
   }
}

/*!
   Calculate first order derivative x using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_sobel_5x5_x(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s tx = apu_flt_sobel_5x5_x(&src[x], sstr);
         
         // Absolute Value & Saturation
         tx = vsat(tx, 0, 255);
         
         dst[x] = (vec08u)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

/*!
   Calculate first order derivative x using sobel 5x5.
   (unsigned 8 bit to signed 8 bit)

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void 
apu_flt_sobel_5x5_x(
            vec08s* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
//! 5x5 Sobel x filter
    for (int h = 0; h < bh; h++)
    {
        for (int w = 0; w < bw; w++)
        {
            vec16s tx = (apu_flt_sobel_5x5_x(&src[w], sstr)>>5);
            dst[w] = (vec08s)vsat(tx, -128, 127);    // clamp to [-128, 127]
        }
        src += sstr;
        dst += dstr;
    }
}

/*!
   Calculate first order derivative y using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_sobel_5x5_y(            
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,)  
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16s ty = apu_flt_sobel_5x5_y(&src[x], sstr);

         // Absolute Value & Saturation
         ty = vsat(ty, 0, 255);
      
         dst[x] = (vec08u)ty;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void 
apu_flt_sobel_5x5_y(            
            vec08s* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh
)
{
//! 5x5 Sobel y filter
    for (int h = 0; h < bh; h++)
    {
        for (int w = 0; w < bw; w++)
        {
            vec16s ty = (apu_flt_sobel_5x5_y(&src[w], sstr)>>5);
            dst[w] = (vec08s)vsat(ty, -128, 127);    // clamp tp [-128, 127]
        }
        src += sstr;
        dst += dstr;
    }
}

// LOCAL HELPER FUNCTIONS

//  -1,  0,  1,
//  -2,  0,  2,
//  -1,  0,  1,
static
inline
vec16s
apu_flt_sobel_3x3_x(const vec08u* src, int sstr)
{
	vec16s vd = +(vec16s)src[-sstr + 1] - (vec16s)src[-sstr - 1]
		+ (( (vec16s) src[+1] - (vec16s)src[-1]) << 1 )
		+ (vec16s)src[+sstr + 1] - (vec16s)src[+sstr - 1];
               
               
   return vd;
}

// -1, -2, -1,
//  0,  0,  0,
// +1, +2, +1,
static
inline
vec16s
apu_flt_sobel_3x3_y(const vec08u* src, int sstr)
{
	vec16s t7 = +(vec16s)src[+sstr + 1] - (vec16s)src[-sstr - 1];
	vec16s t9 = +(vec16s)src[+sstr - 1] - (vec16s) src[-sstr + 1];
	vec16s t8 = +(vec16s)src[+sstr] - (vec16s)src[-sstr];
   vec16s vd = t7 + (t8 << 1) + t9;
   
   return vd;
}


/*
    -1,  -2,  0,  +2,  +1,
    -4,  -8,  0,  +8,  +4,
    -6, -12,  0, +12,  +6,
    -4,  -8,  0,  +8,  +4,
    -1,  -2,  0,  +2,  +1, 
 */    
static
inline
vec16s
apu_flt_sobel_5x5_x(const vec08u* src, int sstr)
{
	const vec16s t22 = -(vec16s)src[-2 * sstr - 2] + (vec16s)src[-2 * sstr + 2] - (vec16s)src[+2 * sstr - 2] + (vec16s)src[+2 * sstr + 2];
	const vec16s t12 = -(vec16s)src[-2 * sstr - 1] + (vec16s)src[-2 * sstr + 1] - (vec16s)src[+2 * sstr - 1] + (vec16s)src[+2 * sstr + 1];
	const vec16s t21 = -(vec16s)src[-1 * sstr - 2] + (vec16s)src[-1 * sstr + 2] - (vec16s)src[+1 * sstr - 2] + (vec16s)src[+1 * sstr + 2];
	const vec16s t11 = -(vec16s)src[-1 * sstr - 1] + (vec16s)src[-1 * sstr + 1] - (vec16s)src[+1 * sstr - 1] + (vec16s)src[+1 * sstr + 1];
	const vec16s t20 = -(vec16s)src[-2] + (vec16s)src[+2];
	const vec16s t10 = -(vec16s)src[-1] + (vec16s)src[+1];

   const vec16s tx   = t22 + 2*t12 + 4*t21 + 8*t11 + 6*t20 + 12*t10;
   
   return tx;
}

/*
    -1,  -4,  -6,  -4,  -1,
    -2,  -8, -12,  -8,  -2,
     0,   0,   0,   0,   0,
    +2,  +8, +12,  +8,  +2,
    +1,  +4,  +6,  +4,  +1,
*/
static
inline
vec16s
apu_flt_sobel_5x5_y(const vec08u* src, int sstr)
{
	const vec16s t22 = -(vec16s)src[-2 * sstr - 2] - (vec16s)src[-2 * sstr + 2] + (vec16s)src[+2 * sstr - 2] + (vec16s)src[+2 * sstr + 2];
	const vec16s t12 = -(vec16s)src[-2 * sstr - 1] - (vec16s)src[-2 * sstr + 1] + (vec16s)src[+2 * sstr - 1] + (vec16s)src[+2 * sstr + 1];
	const vec16s t21 = -(vec16s)src[-1 * sstr - 2] - (vec16s)src[-1 * sstr + 2] + (vec16s)src[+1 * sstr - 2] + (vec16s)src[+1 * sstr + 2];
	const vec16s t11 = -(vec16s)src[-1 * sstr - 1] - (vec16s)src[-1 * sstr + 1] + (vec16s)src[+1 * sstr - 1] + (vec16s)src[+1 * sstr + 1];
	const vec16s t02 = -(vec16s)src[-2 * sstr] + (vec16s)src[+2 * sstr];
	const vec16s t01 = -(vec16s)src[-1 * sstr] + (vec16s)src[+1 * sstr];

   const vec16s tx   = t22 + 4*t12 + 2*t21 + 8*t11 + 6*t02 + 12*t01;
   
   return tx;
}

#endif /* ACF_KERNEL_IMPLEMENTATION */
