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

namespace ht{/* Namespace ht */

void apu_flt_saturate (
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

/* Sobel 3x3 */
void apu_flt_sobel_3x3(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                         int sstr, int bw, int bh){
    const int chess_storage(R18) k2k1 = chess_copy(0x0201);
    const int chess_storage(R19) k0k2 = chess_copy(0x0002);
    const int chess_storage(R20) k255 = chess_copy(0x00FF);
    
    /* Block width | 4, >= 4 */
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /* Variables */
        vec16s chess_storage(V0) lxcol, chess_storage(V1) mxcol, rxcol;
        vec16s chess_storage(V2) lycol, chess_storage(V3) mycol, rycol;
        vec16s lpix,  mpix,  upix;
        
        
        /* Row Pointers */
        const vec08u* src0 = (const vec08u*)(src-sstr-1);
        const vec08u* src1 = (const vec08u*)(src     -1);
        const vec08u* src2 = (const vec08u*)(src+sstr-1);
        vec16s*       dst0 = dst;
        
        upix = *src0++;
        lpix = *src2++;
        mpix = *src1++;
        lycol = lpix-upix;
        lxcol = upix+vmul_ulsh(mpix, k2k1)+lpix;
        upix = *src0++;
        lpix = *src2++;
        mpix = *src1++;
        mycol = lpix-upix;
        mxcol = upix+vmul_ulsh(mpix, k2k1)+lpix;
        upix = *src0++;
        lpix = *src2++;
        mpix = *src1++;
        rycol = lpix-upix;
        
        
        /* Core loop */
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            
            /* Compute separable, column direction */
            rxcol = upix+vmul_ulsh(mpix, k2k1)+lpix;
            
            /* Compute separable, row direction */
            lxcol = rxcol-lxcol;
			lycol = lycol + vmul(mycol, (vec16s) k0k2) + rycol;
            
            /* Abs+Abs+Add+Sat+Store */
            *dst0++ = vsat(vabs_diff(lxcol, (vec16s)0)+vabs_diff(lycol, (vec16s)0), 0, k255);
            
            /* Save State */
            lxcol = mxcol;mxcol = rxcol;
            lycol = mycol;mycol = rycol;
            
            /* Load next 3 pixels */
            upix = *src0++;
            lpix = *src2++;
            mpix = *src1++;
            rycol = lpix-upix;
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

void apu_flt_sobel_3x3_x(
               vec08s* dst, int dstr,
               vec16s* dst16s,
         const vec08u* src, int sstr,
               int bw, int bh
)
{
   ht::apu_flt_centraldx_3x3( dst16s, dstr, src, sstr, bw, bh, 1, 2, 1 );
   ht::apu_flt_saturate( dst, dstr, dst16s, dstr, bw, bh ); 
}

void apu_flt_sobel_3x3_y (
               vec08s* dst, int dstr,
               vec16s* dst16s,
         const vec08u* src, int sstr,
               int bw, int bh
)
{
   ht::apu_flt_centraldy_3x3( dst16s, dstr, src, sstr, bw, bh, 1, 2, 1 );
   ht::apu_flt_saturate( dst, dstr, dst16s, dstr, bw, bh ); 
}

#if 0
#include <stdint.h>
void apu_flt_sobel_3x3_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            vec16s dx =   -(vec16s)src[x-sstr-1] +                          +   (vec16s)src[x-sstr+1] +
                        -2*(vec16s)src[x     -1] +                            2*(vec16s)src[x     +1] +
                          -(vec16s)src[x+sstr-1] +                          +   (vec16s)src[x+sstr+1];
            vec16s dy =   -(vec16s)src[x-sstr-1] + -2*(vec16s)src[x-sstr  ] +  -(vec16s)src[x-sstr+1] +
                           
                           (vec16s)src[x+sstr-1] +  2*(vec16s)src[x+sstr  ] +   (vec16s)src[x+sstr+1];
            
            /* Abs+Abs+Add+Sat+Store */
            dst[x] = vsat(vabs_diff(dx, (vec16s)0)+vabs_diff(dy, (vec16s)0), 0, 255);
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

void apu_flt_sobel_5x5_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            vec16s i00 = src[x-2*sstr-2], i01 = src[x-2*sstr-1], i02 = src[x-2*sstr  ], i03 = src[x-2*sstr+1], i04 = src[x-2*sstr+2],
                   i10 = src[x-1*sstr-2], i11 = src[x-1*sstr-1], i12 = src[x-1*sstr  ], i13 = src[x-1*sstr+1], i14 = src[x-1*sstr+2],
                   i20 = src[x+0*sstr-2], i21 = src[x+0*sstr-1],                        i23 = src[x+0*sstr+1], i24 = src[x+0*sstr+2],
                   i30 = src[x+1*sstr-2], i31 = src[x+1*sstr-1], i32 = src[x+1*sstr  ], i33 = src[x+1*sstr+1], i34 = src[x+1*sstr+2],
                   i40 = src[x+2*sstr-2], i41 = src[x+2*sstr-1], i42 = src[x+2*sstr  ], i43 = src[x+2*sstr+1], i44 = src[x+2*sstr+2];
            
            vec16s dx = -1*i00 + -2*i01 +        +  2*i03 +  1*i04 +
                        -4*i10 + -8*i11 +        +  8*i13 +  4*i14 +
                        -6*i20 +-12*i21 +        + 12*i23 +  6*i24 +
                        -4*i30 + -8*i31 +        +  8*i33 +  4*i34 +
                        -1*i40 + -2*i41 +        +  2*i43 +  1*i44;
            vec16s dy = -1*i00 + -4*i01 + -6*i02 + -4*i03 + -1*i04 +
                        -2*i10 + -8*i11 +-12*i12 + -8*i13 + -2*i14 +
                        
                         2*i30 +  8*i31 + 12*i32 +  8*i33 +  2*i34 +
                         1*i40 +  4*i41 +  6*i42 +  4*i43 +  1*i44;
            
            /* Abs+Abs+Add+Sat+Store */
            dst[x] = vsat(vabs_diff(dx, (vec16s)0)+vabs_diff(dy, (vec16s)0), 0, 255);
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}
#endif

}/* Namespace ht */

#endif /* ACF_KERNEL_IMPLEMENTATION */
