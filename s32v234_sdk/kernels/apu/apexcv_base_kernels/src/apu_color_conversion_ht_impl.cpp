/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2015 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION
//
#include "apu_color_conversion_impl.h"


namespace ht{/* Namespace ht */

/**
 * 3-channel to grayscale, 8-bit color conversion.
 */

void apu_csc_8UC3_Y(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                     int sstr, int bw, int bh,
                     uint8_t kA, uint8_t kB, uint8_t kC, uint16_t kR){
    /* Pack & Pin constants */
    int a = (kB<<8) | (kA<<0);
    int b =            kC;
    int c =            kR;
    
    for (int y=0;y<bh;y++) chess_loop_range(1,){
        /* Pointers */
        const vec16u* s = (const vec16u*)src;
        vec16s*       d = (      vec16s*)dst;
        
        /* Variables */
        vec16u chess_storage(V0) v0;
        vec16u chess_storage(V1) v1;
        vec16u chess_storage(V2) v2;
        vec16u chess_storage(V3) v3;
        vec16u chess_storage(V4) v4;
        vec16u chess_storage(V5) v5;
        vec16u chess_storage(V6) v6;
        vec16u chess_storage(V7) v7;
        vec16u l6, l7;
        
        
        /* Loop preamble */
#define SAVE_TMPS do{t0=v0;t1=v1;t2=v2;t3=v3;t4=v4;t5=v5;t6=v6;t7=v7;}while(0)
        vec16u t0, t1, t2, t3, t4, t5, t6, t7;
        
        /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
        /* Peel -2 */
        {SAVE_TMPS;             ;             ;                       ; l6 = *s++;       }
        {SAVE_TMPS;             ;             ;                       ; l7 = *s++;       }
        {SAVE_TMPS;             ;             ;                       ;           v6=l6; }
        /* Peel -1 */
        {SAVE_TMPS;             ;             ; v1 = vmul_ulul(t6, a) ; l6 = *s++;v7=l7; }
        {SAVE_TMPS; v0 = t1 + c ;             ; v1 = vmul_uhuh(t6, a) ; l7 = *s++;       }
        {SAVE_TMPS; v0 = t0 + t1;             ; v1 = vmul_ulul(t7, b) ;           v6=l6; }
        /* Core loop */
        for (int x=0; x<bw; x++) chess_loop_range(1,){
            /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
            {SAVE_TMPS; v0 = t0 + t1;             ; v1 = vmul_ulul(t6, a) ; l6 = *s++;v7=l7; }
            {SAVE_TMPS; v0 = t1 + c ; v6 = t0 >> 8; v1 = vmul_uhuh(t6, a) ; l7 = *s++;       }
            {SAVE_TMPS; v0 = t0 + t1;             ; v1 = vmul_ulul(t7, b) ; *d++ = (vec16s)t6;v6=l6; }
        }
#undef SAVE_TMPS
        
        /* Pointer increment */
        src += sstr;
        dst += dstr;
    }
}


}/* Namespace ht */
#endif /* ACF_KERNEL_IMPLEMENTATION */
