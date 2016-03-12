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

// Local helper functions
static inline vec16u apu_flt_gaussian_3x3(const vec08u* src, int sstr);
static inline vec16u apu_flt_gaussian_5x5(const vec08u* src, int sstr);

/*!
   Calculate a gaussian 3x3 filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_gaussian_3x3(vec08u* dst, int dstr,
               const vec08u* src, int sstr,
                     int bw, int bh)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16u tx = apu_flt_gaussian_3x3(&src[x], sstr);
        
         dst[x] = (vec08u)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

// LOCAL HELPER FUNCTION
//  1,  2,  1,
//  2,  4,  2,  * 1/16
//  1,  2,  1,
static
inline
vec16u
apu_flt_gaussian_3x3(const vec08u* src, int sstr)
{
   vec16u t1 = +   (vec16u)src[-sstr+1] + 2*(vec16u)src[-sstr  ] +   (vec16u)src[-sstr-1]
               + 2*(vec16u)src[     +1] + 4*(vec16u)src[      0] + 2*(vec16u)src[     -1]
               +   (vec16u)src[+sstr+1] + 2*(vec16u)src[+sstr  ] +   (vec16u)src[+sstr-1]; 
               
   vec16u vd = t1>>4;
               
   return vd;
}

/*!
   Calculate a gaussian 5x5 filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
apu_flt_gaussian_5x5(vec08u* dst, int dstr,
               const vec08u* src, int sstr,
                     int bw, int bh)
{
   for (int y=0; y<bh; ++y) chess_loop_range(1,) 
   {
      for (int x=0; x<bw; ++x) chess_loop_range(1,) 
      {
         vec16u tx = apu_flt_gaussian_5x5(&src[x], sstr);
        
         dst[x] = (vec08u)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

// LOCAL HELPER FUNCTION
//  1,   4,   6,  4,  1,
//  4,  16,  24, 16,  4, 
//  6,  24,  36, 24,  6, * 1/256
//  4,  16,  24, 16,  4,
//  1,   4,   6,  4,  1,
static
inline
vec16u
apu_flt_gaussian_5x5(const vec08u* src, int sstr)
{
   vec16u t1 = +   (vec16u)src[-2*sstr - 2] +  4*(vec16u)src[-2*sstr - 1] +  6*(vec16u)src[-2*sstr] +  4*(vec16u)src[-2*sstr + 1] +   (vec16u)src[-2*sstr + 2]
               + 4*(vec16u)src[-  sstr - 2] + 16*(vec16u)src[-  sstr - 1] + 24*(vec16u)src[-  sstr] + 16*(vec16u)src[-  sstr + 1] + 4*(vec16u)src[-  sstr + 2]
               + 6*(vec16u)src[        - 2] + 24*(vec16u)src[        - 1] + 36*(vec16u)src[      0] + 24*(vec16u)src[        + 1] + 6*(vec16u)src[        + 2]
               + 4*(vec16u)src[+  sstr - 2] + 16*(vec16u)src[+  sstr - 1] + 24*(vec16u)src[+  sstr] + 16*(vec16u)src[+  sstr + 1] + 4*(vec16u)src[+  sstr + 2]
               +   (vec16u)src[+2*sstr - 2] +  4*(vec16u)src[+2*sstr - 1] +  6*(vec16u)src[+2*sstr] +  4*(vec16u)src[+2*sstr + 1] +   (vec16u)src[+2*sstr + 2];
               
   vec16u vd = t1>>8;
               
   return vd;
}

#endif /* ACF_KERNEL_IMPLEMENTATION */
