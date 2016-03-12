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

namespace ht{/* Namespace ht */


/**
 * Computes the positive/negative gains of the filter by summing up all
 * positive and negative coefficients together separately and returning both.
 */

static inline void filterGain8bit(const int8_t* flt,
                                  unsigned      numTaps,
                                  int32_t&      pos,
                                  int32_t&      neg){

    pos = neg = 0;

    for(unsigned i=0;i<numTaps;i++){
        flt[i] >= 0 ? pos += flt[i] : neg += flt[i];
    }
}

/**
 * Computes from the filter's gain the right shift required for
 * normalization of intermediates to yield an 8-bit unsigned value.
 *
 * If the gain is not an exact power-of-2, a compromise is adopted. The
 * shift is computed to yield a value greater than 8 but less than 9 bits
 * in size. A saturation will be then required to clip off excesses
 * beyond the range of 8-bit unsigned.
 *
 * Assumes the filter gain is non-zero.
 */

static inline int filterShiftU8bit(uint32_t posGain){
    return 31-clz(posGain);
}

/*!
   Calculate the output of generic (3 x 3) filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
 */
void apu_flt_generic_3x3(
         vec08u* restrict dst, int dstr,
   const vec08u* restrict src, int sstr,
   int bw, int bh,
   const int8_t* restrict flt, int fscale){
   /* Adjust pointers for our needs */
   src -= sstr;

   /* Compute gain of filter */
   int normSh = fscale;
   vec32s vNormSh = normSh;

   /* Load filter coefficients in registers */
   const int32_t* f = (const int32_t*)flt;
   int32_t lf0  = *f++;
   int32_t lf1  = *f++;
   int32_t lf2  = *f++;

   /* For each row... */
   for (int by=0; by<bh; ++by) chess_loop_range(1,){
      /* Compute row pointers */
      vec08u* restrict chess_storage(R5) dst_ = chess_copy(dst);
      const vec16u* va = (const vec16u*)(src);
      const vec16u* vb = (const vec16u*)((const vec08u*)va + sstr);
      const vec16u* vc = (const vec16u*)((const vec08u*)vb + sstr);
      vec16s chess_storage(V0) lh = 0;
      vec16s chess_storage(V2) rh = 0;
      vec16u chess_storage(V1) ll = 0;
      vec16u chess_storage(V3) rl = 0;

      /* Load initial column */
      vec16u v0 = va++[-1], v1 = vb++[-1], v2 = vc++[-1],
             v3,            v4,            v5;

      /* For each column... */
      for (int bx=0; bx<bw; bx+=2) chess_loop_range(1,){
         /* Temporaries */
         vec16s chess_storage(V7) lm;
         vec16s chess_storage(V7) rm;

         /**
          * Pessimization: Force coefficients to be unpacked every iteration,
          * avoiding the compiler's preference for spilling to memory
          * (and consuming power).
          */

         lf0         = chess_copy(lf0);/* Defeat LICM */
         lf1         = chess_copy(lf1);/* Defeat LICM */
         lf2         = chess_copy(lf2);/* Defeat LICM */
         int32_t f0  = lf0 >>  0;
         int32_t f1  = lf0 >> 16;
         int32_t f2  = lf1 >>  0;
         int32_t f3  = lf1 >> 16;
         int32_t f4  = lf2 >>  0;

         /**
          * f0l f0h f1l
          * f1h f2l f2h
          * f3l f3h f4l
          */

         /* HOT ZONE BEGIN */
         /*      VACC      |            VMUL            |    S/VLD     | */
                             lm = vmul_uhsl(v0,  f0)    , v0   = *va-- ;
         vacl(lh, ll, lm)  , lm = vmul_uhsh(v1,  f1)    , v1   = *vb-- ;
         vacl(lh, ll, lm)  , lm = vmul_uhsl(v2,  f3)    , v2   = *vc-- ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v0,  f1)    , v0   = *va, va+=2;
         vacl(rh, rl, rm)  , rm = vmul_ulsh(v1,  f2)    , v1   = *vb, vb+=2;
         vacl(rh, rl, rm)  , rm = vmul_ulsl(v2,  f4)    , v2   = *vc, vc+=2;
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v0,  f0)                   ;
         vacl(lh, ll, lm)  , lm = vmul_uhsl(v0,  f1)                   ;
         vacl(lh, ll, lm)  , lm = vmul_ulsl(v1,  f2)                   ;
         vacl(lh, ll, lm)  , lm = vmul_uhsh(v1,  f2)                   ;
         vacl(lh, ll, lm)  , lm = vmul_ulsh(v2,  f3)                   ;
         vacl(lh, ll, lm)  , lm = vmul_uhsl(v2,  f4)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v0,  f0)                   ;
         vacl(rh, rl, rm)  , rm = vmul_uhsh(v0,  f0)                   ;
         vacl(rh, rl, rm)  , rm = vmul_ulsh(v1,  f1)                   ;
         vacl(rh, rl, rm)  , rm = vmul_uhsl(v1,  f2)                   ;
         vacl(rh, rl, rm)  , rm = vmul_ulsl(v2,  f3)                   ;
         vacl(rh, rl, rm)  , rm = vmul_uhsh(v2,  f3)                   ;
         vacl(rh, rl, rm)                                              ;
         /*    VACC        |            VMUL            |    S/VLD     | */
         /* HOT ZONE  END  */
         // Saturation TODO: use vsat for 32 bit vector once supported
         vec32s lacc = vsra(vec32s(lh, ll), vNormSh);
         vec32s racc = vsra(vec32s(rh, rl), vNormSh);
         ll = lacc.low();
         rl = racc.low();

         /*lacc = vselect(lacc, 0, lacc >= 0);
         lacc = vselect(lacc, 255, lacc <= 255);
         racc = vselect(racc, 0, racc >= 0);
         racc = vselect(racc, 255, racc <= 255);
         */

         const int usatByte = chess_copy(0xFF);
         ll = vsat((vec16s)ll, 0, usatByte);
         rl = vsat((vec16s)rl, 0, usatByte);

         *dst_++ = (vec08u)ll;
         *dst_++ = (vec08u)rl;

         rh = (lh  &= 0);
         rl = (ll >>= 15);
      }

      src  += sstr;
      dst += dstr;
   }
}

/*!
   Calculate the output of generic (5 x 5) filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
 */
void apu_flt_generic_5x5(
         vec08u* restrict dst, int dstr,
   const vec08u* restrict src, int sstr,
   int bw, int bh,
   const int8_t* restrict flt, int fscale){
   /* Adjust pointers for our needs */
   src -= 2*sstr;
   src -= 2;

   /* Compute gain of filter */
   int normSh = fscale;
   vec32s vNormSh = normSh;

   /* Load filter coefficients in registers */
   const int32_t* f = (const int32_t*)flt;
   int32_t lf0  = *f++;
   int32_t lf1  = *f++;
   int32_t lf2  = *f++;
   int32_t lf3  = *f++;
   int32_t lf4  = *f++;
   int32_t lf5  = *f++;
   int32_t lf6  = *f++;

   /* For each row... */
   for (int by=0; by<bh; ++by) chess_loop_range(1,){
      /* Compute row pointers */
      vec08u* restrict chess_storage(R5) dst_ = chess_copy(dst);
      const vec16u* va = (const vec16u*)(src);
      const vec16u* vb = (const vec16u*)((const vec08u*)va + sstr);
      const vec16u* vc = (const vec16u*)((const vec08u*)vb + sstr);
      const vec16u* vd = (const vec16u*)((const vec08u*)vc + sstr);
      const vec16u* ve = (const vec16u*)((const vec08u*)vd + sstr);
      vec16s chess_storage(V0) lh = 0;
      vec16s chess_storage(V2) rh = 0;
      vec16u chess_storage(V1) ll = 0;
      vec16u chess_storage(V3) rl = 0;

      /* For each column... */
      for (int bx=0; bx<bw; bx+=2) chess_loop_range(1,){
         /* Temporaries */
         vec16s chess_storage(V7) lm;
         vec16s chess_storage(V7) rm;
         vec16u  v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14;

         /**
          * Pessimization: Force coefficients to be unpacked every iteration,
          * avoiding the compiler's preference for spilling to memory
          * (and consuming power).
          */

         lf0         = chess_copy(lf0);/* Defeat LICM */
         lf1         = chess_copy(lf1);/* Defeat LICM */
         lf2         = chess_copy(lf2);/* Defeat LICM */
         lf3         = chess_copy(lf3);/* Defeat LICM */
         lf4         = chess_copy(lf4);/* Defeat LICM */
         lf5         = chess_copy(lf5);/* Defeat LICM */
         lf6         = chess_copy(lf6);/* Defeat LICM */
         int32_t f0  = lf0 >>  0;
         int32_t f1  = lf0 >> 16;
         int32_t f2  = lf1 >>  0;
         int32_t f3  = lf1 >> 16;
         int32_t f4  = lf2 >>  0;
         int32_t f5  = lf2 >> 16;
         int32_t f6  = lf3 >>  0;
         int32_t f7  = lf3 >> 16;
         int32_t f8  = lf4 >>  0;
         int32_t f9  = lf4 >> 16;
         int32_t f10 = lf5 >>  0;
         int32_t f11 = lf5 >> 16;
         int32_t f12 = lf6 >>  0;
         /* HOT ZONE BEGIN */
         /*      VACC      |            VMUL            |    S/VLD     | */
                                                          v0   = *va++ ; /* Start Row 0 */
                                                                       ;
                                                                       ;
                             lm = vmul_ulsl(v0,  f0)    , v1   = *va++ ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v0,  f0)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v0,  f0)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v1,  f0)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v1,  f1)    , v2   = *va-- ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v1,  f1)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v1,  f1)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v2,  f1)    , v3   = *vb++ ; /* Start Row 1 */
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v2,  f2)                   ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v2,  f2)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v3,  f2)    , v4   = *vb++ ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v3,  f2)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsl(v3,  f3)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v4,  f3)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v4,  f3)    , v5   = *vb-- ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v4,  f3)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsl(v4,  f4)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v5,  f4)    , v6   = *vc++ ; /* Start Row 2 */
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v5,  f4)                   ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v5,  f4)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v6,  f5)    , v7   = *vc++ ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v6,  f5)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v6,  f5)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v7,  f5)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v7,  f6)    , v8   = *vc-- ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v7,  f6)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v7,  f6)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v8,  f6)    , v9   = *vd++ ; /* Start Row 3 */
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v8,  f7)                   ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v8,  f7)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v9,  f7)    , v10  = *vd++ ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v9,  f7)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsl(v9,  f8)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v10, f8)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v10, f8)    , v11  = *vd-- ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v10, f8)                   ;
         vacl(rh, rl, rm)  , lm = vmul_uhsl(v10, f9)                   ;
         vacl(lh, ll, lm)  , rm = vmul_ulsl(v11, f9)    , v12  = *ve++ ; /* Start Row 4 */
         vacl(rh, rl, rm)  , lm = vmul_ulsh(v11, f9)                   ;
         vacl(lh, ll, lm)  , rm = vmul_uhsh(v11, f9)                   ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v12, f10)   , v13  = *ve++ ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v12, f10)                  ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v12, f10)                  ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v13, f10)                  ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v13, f11)   , v14  = *ve-- ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v13, f11)                  ;
         vacl(rh, rl, rm)  , lm = vmul_uhsh(v13, f11)                  ;
         vacl(lh, ll, lm)  , rm = vmul_ulsh(v14, f11)                  ;
         vacl(rh, rl, rm)  , lm = vmul_ulsl(v14, f12)                  ;
         vacl(lh, ll, lm)  , rm = vmul_uhsl(v14, f12)                  ;
         vacl(rh, rl, rm)                                              ;
         /*    VACC        |            VMUL            |    S/VLD     | */
         /* HOT ZONE  END  */
         // Saturation TODO: use vsat for 32 bit vector once supported
         vec32s lacc = vsra(vec32s(lh, ll), vNormSh);
         vec32s racc = vsra(vec32s(rh, rl), vNormSh);
         ll = lacc.low();
         rl = racc.low();

         /*lacc = vselect(lacc, 0, lacc >= 0);
         lacc = vselect(lacc, 255, lacc <= 255);
         racc = vselect(racc, 0, racc >= 0);
         racc = vselect(racc, 255, racc <= 255);
         */

         const int usatByte = chess_copy(0xFF);
         ll = vsat((vec16s)ll, 0, usatByte);
         rl = vsat((vec16s)rl, 0, usatByte);

         *dst_++ = (vec08u)ll;
         *dst_++ = (vec08u)rl;

         rh = (lh  &= 0);
         rl = (ll >>= 15);
      }

      src  += sstr;
      dst += dstr;
   }
}

}/* Namespace ht */

#endif /* ACF_KERNEL_IMPLEMENTATION */
