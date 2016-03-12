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
*  \file apu_integral_image.c
*  \brief APU integral image kernel.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#include <stdint.h>
#include "apu_integral_image_impl.h"

/*!
   Intiialize line buffer for temporary data required to compute integral image.

   \param tlst - [Output] Destination block pointer
   \param bw   - [Input]  Block width
 */
void
apu_integral_init(vec32u __cmem* tlst, int bw)
{
   for (int x=0; x<bw; x+=4) chess_loop_range(1,)
   {
      tlst[x+0] = 0;
      tlst[x+1] = 0;
      tlst[x+2] = 0;
      tlst[x+3] = 0;
   }
}

/*!
   Calculate integral images.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param tlst - [Input]  Temporary line pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param ncu  - [Input]  Number of CUs (32/64)
 */
void
apu_integral_image(vec32u __cmem* dst, int dstr, const vec08u __cmem* src, vec32u __cmem* tlst, int sstr, int bw, int bh, int ncu)
{
   for (int y=0; y<bh; ++y)
   {
      // Local Integration
      const vec08u __cmem* s = src;
      vec16u v0   = (vec16u)s[0];
      vec16u v1   = (vec16u)s[1];
      vec16u v2   = (vec16u)s[2];
      vec16u v3   = (vec16u)s[3];
             s += 4;
      vec16u ltot = 0;
      for (int x=4; x<bw; x+=4) chess_loop_range(1,) // at least 8 pixels
      {
         ltot += v0; v0 = (vec16u)s[0];
         ltot += v1; v1 = (vec16u)s[1];
         ltot += v2; v2 = (vec16u)s[2];
         ltot += v3; v3 = (vec16u)s[3];
         s += 4;
      }

      ltot += v0;
      ltot += v1;
      ltot += v2;
      ltot += v3;
      
      // Reduction
      vec32u ttot = (vec32u)ltot;
      ltot = vmsr(ltot);
      for (int c=1; c<ncu; ++c)
      {
         ttot += (vec32u)ltot;
         ltot  = vmsr(ltot);
      }
      
      // 
      s = src;
      tlst[bw-1] = dst[bw-1] = ttot + tlst[bw-1]; ttot -= (vec32u)s[bw-1]; 
      for (int x=(bw-2); x>=0; --x)
      {
         tlst[x] = dst[x] = ttot + tlst[x]; ttot -= (vec32u)s[x];
      }
      
      dst += dstr;
      src += sstr;
   }   
}


#endif /* ACF_KERNEL_IMPLEMENTATION */
