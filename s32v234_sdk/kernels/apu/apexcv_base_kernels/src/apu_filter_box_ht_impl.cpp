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


/**
 * Computes the normalized 3x3 box filter.
 */

void apu_flt_box_3x3(      vec08u* restrict dst, int dstr,
                        const vec08u* restrict src, int sstr,
                                  int bw,  int bh ){
   int chess_storage(R19) m = chess_copy(28);
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,){
       /* Variables */
       vec16u lcol, mcol, ncol, rcol;
       vec16u lacc, racc;
       
       /* Row pointers */
       const vec08u* src0 = src-sstr-1;
       const vec08u* src1 = src     -1;
       const vec08u* src2 = src+sstr-1;
       vec08u*       dst0 = dst;
       
       /* Loop Preamble */
       lcol = (vec16u)*src0++ + (vec16u)*src1++ + (vec16u)*src2++;
       mcol = (vec16u)*src0++ + (vec16u)*src1++ + (vec16u)*src2++;
       ncol = (vec16u)*src0++ + (vec16u)*src1++ + (vec16u)*src2++;
       lacc = lcol+mcol+ncol;
       
	   vec16u vm = vec16u(m);
       /* For each column, */
       for (int x = 0; x < bw; x+=2) chess_loop_range(1,){
           /* Load and sum next three rows twice */
           rcol = (vec16u)*src0++ + (vec16u)*src1++ + (vec16u)*src2++;

           
           /* Compute a left and right sum */
           racc = mcol+ncol+rcol;
           
           
           /* Shift state */
           lcol = ncol;
           mcol = rcol;
           ncol = (vec16u)*src0++ + (vec16u)*src1++ + (vec16u)*src2++;
           
           /* Deep magic. */
		   vec16u ldiv9 = vmul(lacc, vm);
           ldiv9  += vm+(ldiv9>>6);
           ldiv9 >>= 8;
           lacc = lcol+mcol+ncol;/* <- Not deep magic. */
		   vec16u rdiv9 = vmul(racc, vm);
           rdiv9  += vm+(rdiv9>>6);
           rdiv9 >>= 8;
           
           /* Save */
           *dst0++ = (vec08u)ldiv9;
           *dst0++ = (vec08u)rdiv9;
       }
       
       /* Pointer increment */
       dst += dstr;
       src += sstr;
   }
}

#if 0
/**
 * Computes the normalized 3x3 box filter.
 */

void apu_filter_box_3x3_ref(      vec08u* restrict dst, int dstr,
                            const vec08u* restrict src, int sstr,
                                      int bw,  int bh ){
   for (int y = 0; y < bh; ++y) chess_loop_range(1,){
       for (int x = 0; x < bw; x++) chess_loop_range(1,){
           dst[x] = (src[x-sstr-1] + src[x-sstr  ] + src[x-sstr+1] + 
                     src[x     -1] + src[x       ] + src[x     +1] + 
                     src[x+sstr-1] + src[x+sstr  ] + src[x+sstr+1])
                     /
                     9;
       }
       
       /* Pointer increment */
       dst += dstr;
       src += sstr;
   }
}
#endif

}/* Namespace ht */
#endif /* ACF_KERNEL_IMPLEMENTATION */
