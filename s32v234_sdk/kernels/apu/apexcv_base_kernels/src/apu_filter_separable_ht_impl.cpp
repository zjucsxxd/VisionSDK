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
 * Separable 3x3 kernel.
 */

void apu_flt_separable_3x3(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh, const int8_t* fRow, const int8_t* fCol){
    /* Load coefficients. */
    typedef int16_t coeff_t;
    register coeff_t chess_storage(R15) fCol10 = fCol[1]<<8 | (uint8_t)fCol[0]; fCol += 2;
    register coeff_t chess_storage(R14) fCol2  =              (uint8_t)fCol[0];
    register coeff_t chess_storage(R13) fRow0  = *fRow++;
    register coeff_t chess_storage(R12) fRow1  = *fRow++;
    register coeff_t chess_storage(R11) fRow2  = *fRow++;
    
    /* Block width | 4, >= 4 */
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /* Variables */
        vec16s chess_storage(V0) s0, chess_storage(V1) s1, /* Left, Middle */
               chess_storage(V2) s2;                       /* Right column */
        vec08u row0, row1, row2;
        vec08u chess_storage(V6) pix0, chess_storage(V7) pix1;
        vec16s acc;
        
        /* Row Pointers */
        const vec08u* restrict chess_storage(R2) src0 = (const vec08u*)(src-1*sstr-1);
        const vec08u* restrict chess_storage(R3) src1 = (const vec08u*)(src+0*sstr-1);
        const vec08u* restrict chess_storage(R4) src2 = (const vec08u*)(src+1*sstr-1);
        vec16s*       restrict chess_storage(R6) dst0 = dst;
        
        /* Preamble */
        /* Loop-2 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
		s0 = vmul_slul((vec16s)fCol10, pix0 = row0);
		s0 += vmul_shul((vec16s)fCol10, pix1 = row1);
		s0 += vmul_slul((vec16s)fCol2,  pix0 = row2);
        /* Loop-1 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
		s1 = vmul_slul((vec16s)fCol10, pix0 = row0);
		s1 += vmul_shul((vec16s)fCol10, pix1 = row1);
		s1 += vmul_slul((vec16s)fCol2, pix0 = row2);
        
        /* Core loop */
            row0 = *src0++;
            row1 = *src1++;
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            /* Load next 5 pixels */
            row2 = *src2++;
            
            /* Column Filter */
			s2 = vmul_slul((vec16s)fCol10, pix0 = row0);
			s2 += vmul_shul((vec16s)fCol10, pix1 = row1);
			s2 += vmul_slul((vec16s)fCol2, pix0 = row2);
            
            /* Row Filter */
			acc = vmul((vec16s)fRow0, s0);
			acc += vmul((vec16s)fRow1, s1);
			acc += vmul((vec16s)fRow2, s2);
            
            /* Store */
            *dst0++ = acc;
            
            /* Shift State */
            s0=s1;s1=s2;
            row0 = *src0++;
            row1 = *src1++;
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

/**
 * Separable 5x5 kernel.
 */

void apu_flt_separable_5x5(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh, const int8_t* fRow, const int8_t* fCol){
    /* Load coefficients. */
    typedef int16_t coeff_t;
    register coeff_t chess_storage(R15) fCol10 = fCol[1]<<8 | (uint8_t)fCol[0]; fCol += 2;
    register coeff_t chess_storage(R14) fCol32 = fCol[1]<<8 | (uint8_t)fCol[0]; fCol += 2;
    register coeff_t chess_storage(R13) fCol4  =              (uint8_t)fCol[0];
    register coeff_t chess_storage(R12) fRow0  = *fRow++;
    register coeff_t chess_storage(R11) fRow1  = *fRow++;
    register coeff_t chess_storage(R10) fRow2  = *fRow++;
    register coeff_t chess_storage(R9)  fRow3  = *fRow++;
    register coeff_t chess_storage(R8)  fRow4  = *fRow++;
    
    /* Block width | 4, >= 4 */
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /* Variables */
        vec16s chess_storage(V0) s0, chess_storage(V1) s1, /* Left, Left Middle */
               chess_storage(V2) s2, chess_storage(V3) s3, /* Middle, Right Middle */
               chess_storage(V4) s4;                       /* Right column */
        vec08u row0, row1, row2, row3, row4;
        vec08u chess_storage(V7) pix;
        vec16s acc;
        
        /* Row Pointers */
        const vec08u* restrict chess_storage(R1) src0 = (const vec08u*)(src-2*sstr-2);
        const vec08u* restrict chess_storage(R2) src1 = (const vec08u*)(src-1*sstr-2);
        const vec08u* restrict chess_storage(R3) src2 = (const vec08u*)(src+0*sstr-2);
        const vec08u* restrict chess_storage(R4) src3 = (const vec08u*)(src+1*sstr-2);
        const vec08u* restrict chess_storage(R5) src4 = (const vec08u*)(src+2*sstr-2);
        vec16s*       restrict chess_storage(R6) dst0 = dst;
        
        /* Preamble */
        /* Loop-4 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
        row3 = *src3++;
        row4 = *src4++;
		s0 = vmul_slul((vec16s)fCol10, pix = row0);
		s0 += vmul_shul((vec16s)fCol10, pix = row1);
		s0 += vmul_slul((vec16s)fCol32, pix = row2);
		s0 += vmul_shul((vec16s)fCol32, pix = row3);
		s0 += vmul_slul((vec16s)fCol4, pix = row4);
        /* Loop-3 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
        row3 = *src3++;
        row4 = *src4++;
		s1 = vmul_slul((vec16s)fCol10, pix = row0);
		s1 += vmul_shul((vec16s)fCol10, pix = row1);
		s1 += vmul_slul((vec16s)fCol32, pix = row2);
		s1 += vmul_shul((vec16s)fCol32, pix = row3);
		s1 += vmul_slul((vec16s)fCol4, pix = row4);
        /* Loop-2 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
        row3 = *src3++;
        row4 = *src4++;
		s2 = vmul_slul((vec16s)fCol10, pix = row0);
		s2 += vmul_shul((vec16s)fCol10, pix = row1);
		s2 += vmul_slul((vec16s)fCol32, pix = row2);
		s2 += vmul_shul((vec16s)fCol32, pix = row3);
		s2 += vmul_slul((vec16s)fCol4, pix = row4);
        /* Loop-1 */
        row0 = *src0++;
        row1 = *src1++;
        row2 = *src2++;
        row3 = *src3++;
        row4 = *src4++;
		s3 = vmul_slul((vec16s)fCol10, pix = row0);
		s3 += vmul_shul((vec16s)fCol10, pix = row1);
		s3 += vmul_slul((vec16s)fCol32, pix = row2);
		s3 += vmul_shul((vec16s)fCol32, pix = row3);
		s3 += vmul_slul((vec16s)fCol4, pix = row4);
        
        /* Core loop */
            row0 = *src0++;
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            /* Load next 5 pixels */
            row1 = *src1++;
            row2 = *src2++;
            row3 = *src3++;
            row4 = *src4++;
            
            /* Column Filter */
			s4 = vmul_slul((vec16s)fCol10, pix = row0);
			s4 += vmul_shul((vec16s)fCol10, pix = row1);
			s4 += vmul_slul((vec16s)fCol32, pix = row2);
			s4 += vmul_shul((vec16s)fCol32, pix = row3);
			s4 += vmul_slul((vec16s)fCol4, pix = row4);
            
            /* Row Filter */
			acc = vmul((vec16s)fRow0, s0);
			acc += vmul((vec16s)fRow1, s1);
			acc += vmul((vec16s)fRow2, s2);
			acc += vmul((vec16s)fRow3, s3);
			acc += vmul((vec16s)fRow4, s4);
            
            /* Store */
            *dst0++ = acc;
            
            /* Shift State */
            s0=s1;s1=s2;s2=s3;s3=s4;
            
            
            row0 = *src0++;
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

#if 0
void apu_flt_separable_3x3_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                               int sstr, int bw, int bh, const int8_t* fRow, const int8_t* fCol){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            vec16s i00 = src[x-1*sstr-1], i01 = src[x-1*sstr+0], i02 = src[x-1*sstr+1],
                   i10 = src[x+0*sstr-1], i11 = src[x+0*sstr+0], i12 = src[x+0*sstr+1],
                   i20 = src[x+1*sstr-1], i21 = src[x+1*sstr+0], i22 = src[x+1*sstr+1];
            
            vec16s acc = fRow[0]*fCol[0]*i00 + fRow[1]*fCol[0]*i01 + fRow[2]*fCol[0]*i02 +
                         fRow[0]*fCol[1]*i10 + fRow[1]*fCol[1]*i11 + fRow[2]*fCol[1]*i12 +
                         fRow[0]*fCol[2]*i20 + fRow[1]*fCol[2]*i21 + fRow[2]*fCol[2]*i22;
            
            dst[x] = acc;
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

void apu_flt_separable_5x5_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                               int sstr, int bw, int bh, const int8_t* fRow, const int8_t* fCol){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        for (int x=0; x<bw; x+=1) chess_loop_range(1,){
            vec16s i00 = src[x-2*sstr-2], i01 = src[x-2*sstr-1], i02 = src[x-2*sstr  ], i03 = src[x-2*sstr+1], i04 = src[x-2*sstr+2],
                   i10 = src[x-1*sstr-2], i11 = src[x-1*sstr-1], i12 = src[x-1*sstr  ], i13 = src[x-1*sstr+1], i14 = src[x-1*sstr+2],
                   i20 = src[x+0*sstr-2], i21 = src[x+0*sstr-1], i22 = src[x+0*sstr  ], i23 = src[x+0*sstr+1], i24 = src[x+0*sstr+2],
                   i30 = src[x+1*sstr-2], i31 = src[x+1*sstr-1], i32 = src[x+1*sstr  ], i33 = src[x+1*sstr+1], i34 = src[x+1*sstr+2],
                   i40 = src[x+2*sstr-2], i41 = src[x+2*sstr-1], i42 = src[x+2*sstr  ], i43 = src[x+2*sstr+1], i44 = src[x+2*sstr+2];
            
            vec16s acc = fRow[0]*fCol[0]*i00 + fRow[1]*fCol[0]*i01 + fRow[2]*fCol[0]*i02 + fRow[3]*fCol[0]*i03 + fRow[4]*fCol[0]*i04 +
                         fRow[0]*fCol[1]*i10 + fRow[1]*fCol[1]*i11 + fRow[2]*fCol[1]*i12 + fRow[3]*fCol[1]*i13 + fRow[4]*fCol[1]*i14 +
                         fRow[0]*fCol[2]*i20 + fRow[1]*fCol[2]*i21 + fRow[2]*fCol[2]*i22 + fRow[3]*fCol[2]*i23 + fRow[4]*fCol[2]*i24 +
                         fRow[0]*fCol[3]*i30 + fRow[1]*fCol[3]*i31 + fRow[2]*fCol[3]*i32 + fRow[3]*fCol[3]*i33 + fRow[4]*fCol[3]*i34 +
                         fRow[0]*fCol[4]*i40 + fRow[1]*fCol[4]*i41 + fRow[2]*fCol[4]*i42 + fRow[3]*fCol[4]*i43 + fRow[4]*fCol[4]*i44;
            
            dst[x] = acc;
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}
#endif

}/* Namespace ht */

#endif /* ACF_KERNEL_IMPLEMENTATION */
