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


void apu_flt_centraldx_3x3(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh,
                           signed char k0, signed char k1, signed char k2){
#if 0
#if DEBUG
    if(!bw || !bh){
        /* No work to be done. */
        return;
    }else if((((intptr_t)src | (intptr_t)dst | bw | sstr | dstr) & 1) || bw<4){
        /* Invalid arguments */
        printf("Misaligned pointers, or step size is odd, or block width < 4.\n");
        fflush(stdout);
        *(volatile vec16u*)1;/* Cause same error as would normally be caused */
    }
#endif
#endif
    
    /* Block width | 4, >= 4 */
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /**
         * Restrictions on registers required to stop the compiler
         * doing 7CC instead of the achievable 6CC.
         */
        //#define chess_storage(V0)
        /*vec16s chess_storage(V0) v0, 
               chess_storage(V1) v1,
               chess_storage(V2) v2,
               chess_storage(V3) v3,
               chess_storage(V4) v4,
               chess_storage(V5) v5,
               chess_storage(V6) v6,
               chess_storage(V7) v7;*/
        vec16s v0, 
               v1,
               v2,
               chess_storage(V3) v3,
               chess_storage(V4) v4,
               chess_storage(V5) v5,
               chess_storage(V6) v6,
               chess_storage(V7) v7;
        vec16s l0, l1, l2, l3;/* Load targets. */
        
        /* Pointers */
        const vec16s* p0 = (const vec16s*)(src-sstr-2);
        const vec16s* p1 = (const vec16s*)(src     -2);
        const vec16s* p2 = (const vec16s*)(src+sstr-2);
        vec16s*       pd = dst;
        
        /* Loop preamble */
#define SAVE_TMPS do{t0=v0;t1=v1;t2=v2;t3=v3;t4=v4;t5=v5;t6=v6;t7=v7;}while(0)
        vec16s t0, t1, t2, t3, t4, t5, t6, t7;
        
        /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
        /* Peel -2 */
        {SAVE_TMPS;             ;             ;                       ; l0 = *p0++;      }
        {SAVE_TMPS;             ;             ;                       ; l1 = *p1++;      }
        {SAVE_TMPS;             ;             ;                       ; l2 = *p2++;v0=l0;}
        {SAVE_TMPS;             ;             ;                       ;           ;v1=l1;}
        {SAVE_TMPS;             ;             ;                       ;           ;v2=l2;}
        {SAVE_TMPS;             ;             ;                       ;           ;      }
        /* Peel -1 */
        {SAVE_TMPS;             ;             ; v3 = vmul_uhsl(t0, k0); l0 = *p0++;      }
        {SAVE_TMPS;             ;             ; v5 = vmul_uhsl(t1, k1); l1 = *p1++;      }
        {SAVE_TMPS; v5 = t3 + t5;             ; v3 = vmul_uhsl(t2, k2); l2 = *p2++;v0=l0;}
        {SAVE_TMPS; v7 = t3 + t5;             ; v3 = vmul_ulsl(t0, k0);           ;v1=l1;}
        {SAVE_TMPS;             ;             ; v4 = vmul_ulsl(t1, k1);           ;v2=l2;}
        {SAVE_TMPS; v4 = t3 + t4;             ; v3 = vmul_ulsl(t2, k2);           ;      }
        /* Peel  0 */
        {SAVE_TMPS; v6 = t3 + t4;             ; v3 = vmul_uhsl(t0, k0); l0 = *p0++;      }
        {SAVE_TMPS;             ;             ; v5 = vmul_uhsl(t1, k1); l1 = *p1++;      }
        {SAVE_TMPS; v5 = t3 + t5;             ; v3 = vmul_uhsl(t2, k2); l2 = *p2++;v0=l0;}
        {SAVE_TMPS; v5 = t3 + t5;             ; v3 = vmul_ulsl(t0, k0);           ;v1=l1;}
        {SAVE_TMPS; v7 = t5 - t7;             ; v4 = vmul_ulsl(t1, k1);           ;v2=l2;}
        {SAVE_TMPS; v4 = t3 + t4; v7 = t5 << 0; v3 = vmul_ulsl(t2, k2); *pd++ = t7;      }
        /* Core loop */
        for (int x=1; x<bw/2; ++x) chess_loop_range(1,){
            /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
            {SAVE_TMPS; v4 = t3 + t4;             ; v3 = vmul_uhsl(t0, k0); l0 = *p0++;      }
            {SAVE_TMPS; v6 = t4 - t6;             ; v5 = vmul_uhsl(t1, k1); l1 = *p1++;      }
            {SAVE_TMPS; v5 = t3 + t5;             ; v3 = vmul_uhsl(t2, k2); l2 = *p2++;v0=l0;}
            {SAVE_TMPS; v5 = t3 + t5;             ; v3 = vmul_ulsl(t0, k0);           ;v1=l1;}
            {SAVE_TMPS; v7 = t5 - t7; v6 = t4 << 0; v4 = vmul_ulsl(t1, k1); *pd++ = t6;v2=l2;}
            {SAVE_TMPS; v4 = t3 + t4; v7 = t5 << 0; v3 = vmul_ulsl(t2, k2); *pd++ = t7;      }
        }
        /* Peel  N */
        {SAVE_TMPS; v4 = t3 + t4;             ;                       ;           ;    }
        {SAVE_TMPS; v6 = t4 - t6;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ; *pd++ = t6;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        /*        |      ALU    |    Shift    |          Mul          |     Ld/St     */
#undef SAVE_TMPS
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

void apu_flt_centraldy_3x3(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                           int sstr, int bw, int bh,
                           signed char k0, signed char k1, signed char k2){
#if 0
#if DEBUG
    if(!bw || !bh){
        /* No work to be done. */
        return;
    }else if((((intptr_t)src | (intptr_t)dst | bw | sstr | dstr) & 1) || bw<4){
        /* Invalid arguments */
        printf("Misaligned pointers, or step size is odd, or block width < 4.\n");
        fflush(stdout);
        *(volatile vec16u*)1;/* Cause same error as would normally be caused */
    }
#endif
#endif
	vec16s vk0 = vec16s(k0);
	vec16s vk1 = vec16s(k1);
	vec16s vk2 = vec16s(k2);

    /* Block width | 4, >= 4 */
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        vec16s v0, v1, v2, v3, v4, v5, v6, v7;
        vec16s l0, l1, l2, l3;/* Load targets. */
        
        /* Pointers */
        const vec08u* p0 = (const vec08u*)(src-sstr-1);
        const vec08u* p2 = (const vec08u*)(src+sstr-1);
        vec16s*       pd = dst;
        
        /* Loop preamble */
#define SAVE_TMPS do{t0=v0;t1=v1;t2=v2;t3=v3;t4=v4;t5=v5;t6=v6;t7=v7;}while(0)
        vec16s t0, t1, t2, t3, t4, t5, t6, t7;
        
        /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
        /* Peel -2 */
        {SAVE_TMPS;             ;             ;                       ;           ;      }
        {SAVE_TMPS;             ;             ;                       ;           ;      }
        {SAVE_TMPS;             ;             ;                       ; l2 = *p0++;      }
        {SAVE_TMPS;             ;             ;                       ; l3 = *p2++;      }
        {SAVE_TMPS;             ;             ;                       ;           ;v0=l2;}
        {SAVE_TMPS;             ;             ;                       ;           ;v1=l3;}
        /* Peel -1 */
        {SAVE_TMPS; v7 = t1 - t0;             ;                       ; l0 = *p0++;      }
        {SAVE_TMPS;             ;             ;                       ; l1 = *p2++;      }
        {SAVE_TMPS;             ;             ;                       ; l2 = *p0++;v0=l0;}
        {SAVE_TMPS;             ;             ;                       ; l3 = *p2++;v1=l1;}
        {SAVE_TMPS; v6 = t1 - t0;             ;                       ;           ;v2=l2;}
        {SAVE_TMPS;             ;             ;                       ;           ;v0=l3;}
        /* Peel  0 */
        {SAVE_TMPS; v7 = t0 - t2;             ; v3 = vmul     (t7, vk0); l0 = *p0++;      }
        {SAVE_TMPS;             ;             ; v4 = vmul     (t6, vk1); l1 = *p2++;      }
        {SAVE_TMPS; v3 = t3 + t4;             ; v4 = vmul     (t7, vk2); l2 = *p0++;v0=l0;}
        {SAVE_TMPS; v3 = t3 + t4;             ; v4 = vmul     (t6, vk0); l3 = *p2++;v1=l1;}
        {SAVE_TMPS; v6 = t1 - t0;             ; v5 = vmul     (t7, vk1);           ;v2=l2;}
        {SAVE_TMPS; v5 = t4 + t5;             ; v4 = vmul     (t6, vk2); *pd++ = t3;v0=l3;}
        /* Core loop */
        for (int x=1; x<bw/2; ++x) chess_loop_range(1,){
            /*        |      ALU    |    Shift    |          Mul          |      Ld/St      */
            {SAVE_TMPS; v7 = t0 - t2;             ; v3 = vmul     (t7, vk0); l0 = *p0++;      }
            {SAVE_TMPS; v5 = t4 + t5;             ; v4 = vmul     (t6, vk1); l1 = *p2++;      }
            {SAVE_TMPS; v3 = t3 + t4;             ; v4 = vmul     (t7, vk2); l2 = *p0++;v0=l0;}
            {SAVE_TMPS; v3 = t3 + t4;             ; v4 = vmul     (t6, vk0); l3 = *p2++;v1=l1;}
            {SAVE_TMPS; v6 = t1 - t0;             ; v5 = vmul     (t7, vk1); *pd++ = t5;v2=l2;}
            {SAVE_TMPS; v5 = t4 + t5;             ; v4 = vmul     (t6, vk2); *pd++ = t3;v0=l3;}
        }
        /* Peel  N */
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        {SAVE_TMPS; v5 = t4 + t5;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        {SAVE_TMPS;             ;             ;                       ; *pd++ = t5;    }
        {SAVE_TMPS;             ;             ;                       ;           ;    }
        /*        |      ALU    |    Shift    |          Mul          |     Ld/St     */
#undef SAVE_TMPS
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

#if 0
#include <stdint.h>
void apu_flt_centraldx_3x3_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                               int sstr, int bw, int bh,
                               signed char k0, signed char k1, signed char k2){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /* Pointers */
        const vec08u* p0 = (const vec08u*)(src-sstr-1);
        const vec08u* p1 = (const vec08u*)(src     -1);
        const vec08u* p2 = (const vec08u*)(src+sstr-1);
        vec16s*       pd = dst;
        
        for (int x=0; x<bw; ++x) chess_loop_range(1,){
            vec08u px00, px02, px10, px12, px20, px22;
            px00 = *p0;p0 +=  2;
            px02 = *p0;p0 += -1;
            px10 = *p1;p1 +=  2;
            px12 = *p1;p1 += -1;
            px20 = *p2;p2 +=  2;
            px22 = *p2;p2 += -1;
            
            *pd++ = vmul_ulsl(px02, k0) - vmul_ulsl(px00, k0) +
                    vmul_ulsl(px12, k1) - vmul_ulsl(px10, k1) +
                    vmul_ulsl(px22, k2) - vmul_ulsl(px20, k2);
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

void apu_flt_centraldy_3x3_ref(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                               int sstr, int bw, int bh,
                               signed char k0, signed char k1, signed char k2){
    for (int y=0; y<bh; ++y) chess_loop_range(1,){
        /* Pointers */
        const vec08u* p0 = (const vec08u*)(src-sstr-1);
        const vec08u* p2 = (const vec08u*)(src+sstr-1);
        vec16s*       pd = dst;
        
        for (int x=0; x<bw; ++x) chess_loop_range(1,){
            vec08u px00, px01, px02, px20, px21, px22;
            px00 = *p0;p0 +=  1;
            px01 = *p0;p0 +=  1;
            px02 = *p0;p0 += -1;
            px20 = *p2;p2 +=  1;
            px21 = *p2;p2 +=  1;
            px22 = *p2;p2 += -1;
            
            *pd++ = vmul_ulsl(px20, k0) - vmul_ulsl(px00, k0) +
                    vmul_ulsl(px21, k1) - vmul_ulsl(px01, k1) +
                    vmul_ulsl(px22, k2) - vmul_ulsl(px02, k2);
        }
        
        /* Increment pointers */
        src += sstr;
        dst += dstr;
    }
}

#endif

}/* Namespace ht */

#endif /* ACF_KERNEL_IMPLEMENTATION */
