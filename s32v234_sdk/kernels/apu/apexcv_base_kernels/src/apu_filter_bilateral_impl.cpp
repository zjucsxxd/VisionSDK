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

void
apu_flt_bilateral_5x5_init(vec08u __cmem *r_lut, uint8_t *d_lut, int sigmaR, int sigmaD)
{
   float inv_sigmaR = -0.5f / (sigmaR * sigmaR);
   float inv_sigmaD = -0.5f / (sigmaD * sigmaD);
   float y;
   
   for (int i = 0; i < 256; ++i)
   {
      y = expf((i * i) * inv_sigmaR);
      r_lut[i] = (uint8_t)(y * 255 + 0.5f);
   }
   
   for (int j = 0; j < 9; ++j)
   {
      y = expf(j * inv_sigmaD);
      d_lut[j] = (uint8_t)(y * 255 + 0.5f);
   }
}
             
void             
apu_flt_bilateral_5x5(  vec08u* dst, int dstr,
                  const vec08u* src, int sstr,
                             int bw, int bh,
               vec08u __cmem *r_lut, uint8_t *d_lut )
{  
   vec32u weight;          //FP  0_16
   vec32u sum_wi;          //FP 13_16
   vec32u sum_weight;      //FP  5_16
   
   for (int y = 0; y < bh; ++y) chess_loop_range(1,)
   {
      for (int x = 0; x < bw; ++x) chess_loop_range(1,) 
      {
         vec08u center_i = src[y * sstr + x];
         sum_weight = 0;
         sum_wi = 0;
         
         for (int fy = -2; fy < 3; ++fy) chess_loop_range(1,)
         {
            for (int fx = -2; fx < 3; ++fx) chess_loop_range(1,)
            { 
               vec08u filter_i = src[(y + fy) * sstr + (x + fx)];
               vec16s vidx = vabs_diffu(center_i, filter_i);
               
			   weight = ((vec32u)vload(r_lut, vidx)) * d_lut[fx*fx+fy*fy];
               sum_weight += weight;
               sum_wi += ((vec32u)filter_i )* weight;
            }
         }
         //TODO: temporary divide
         // dst[y*dstr+x] = (vec08u)((vec16u)((sum_wi / ((sum_weight+1) >> 1)) + 1) >> 1);
		 dst[y*dstr+x] = (vec08u)(vec16u)((sum_wi+((sum_weight+1)>>1)) / sum_weight);
         //dst[y*dstr+x] = (vec08u)(vec16u)tmp;
      }
   }
}
#endif /* ACF_KERNEL_IMPLEMENTATION */
