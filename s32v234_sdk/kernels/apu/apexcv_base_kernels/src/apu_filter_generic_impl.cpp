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
   Calculate the output of generic (fw x fh) filter.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
   \param fw   - [Input]  Filter width
   \param fh   - [Input]  Filter height
 */
void  
apu_flt_fir2(
         vec08u* restrict dst_, int dstr,        
   const vec08u* restrict src, int sstr,        
   int bw, int bh,                     
   const int8_t* restrict flt, int fw, int fh)
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec16s r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy) chess_loop_range(1,) 
         {
            for (int fx=0; fx<fw; ++fx, ++fk) chess_loop_range(1,) 
            {
               r += ((vec16s)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         
         // Saturation
         r = vsat(r, 0, 255);
         
         dst_[by*dstr + bx] = (vec08u)r;
      }
   }
}   


/*!
   Calculate the output of generic (fw x fh) filter with scaling.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
   \param fw   - [Input]  Filter width
   \param fh   - [Input]  Filter height
   \param fscl - [Input]  Filter Scale (2^fscl)
 */

void  
apu_flt_fir2(
         vec08u* restrict dst, int dstr,        
   const vec08u* restrict src, int sstr,        
   int bw, int bh,                     
   const int8_t* restrict flt, int fw, int fh,  
   int fscl)                     
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   const int fone = (1 << fscl);
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec16s r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy) chess_loop_range(1,)  
         {
            for (int fx=0; fx<fw; ++fx, ++fk) chess_loop_range(1,) 
            {
               r += ((vec16s)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         // Rounding & Scaling
         r  += (fone >> 1);
         r >>= fscl;
         
         // Saturation
         r = vsat(r, 0, 255);
         
         dst[by*dstr + bx] = (vec08u)r;
      }
   }
}   

/*!
   Convolve: Calculate the output of generic (fw x fh) filter.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
   \param fw   - [Input]  Filter width
   \param fh   - [Input]  Filter height
 */
void  
apu_flt_fir2(
         vec16s* restrict dst, int dstr,        
   const vec08u* restrict src, int sstr,        
   int bw, int bh,                     
   const int8_t* restrict flt, int fw, int fh)
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec32s r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy) chess_loop_range(1,) 
         {
            for (int fx=0; fx<fw; ++fx, ++fk) chess_loop_range(1,) 
            {
               r += (vec32s)(flt[fk] * (vec16s)src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         
         // Saturation TODO: use vsat for 32 bit vector once supported
         r = vselect(r, vec32s(32767), r <= 32767);
		 r = vselect(r, vec32s(-32768), r >= -32768);
         
         dst[by*dstr + bx] = (vec16s)r;
      }
   }
}


/*!
   Convolve: Calculate the output of generic (fw x fh) filter with scaling.
   
   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param flt  - [Input]  Filter Coeffiencients (pointer)
   \param fw   - [Input]  Filter width
   \param fh   - [Input]  Filter height
   \param fscl - [Input]  Filter Scale (2^fscl)
 */
void  
apu_flt_fir2(
         vec16s* dst, int dstr,        
   const vec08u* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh,  
   int fscl)                     
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   const int fone = (1 << fscl);
   
   for (int by=0; by<bh; ++by) chess_loop_range(1,) 
   {
      for (int bx=0; bx<bw; ++bx) chess_loop_range(1,) 
      {
         vec32s r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy) chess_loop_range(1,) 
         {
            for (int fx=0; fx<fw; ++fx, ++fk) chess_loop_range(1,) 
            {
               r += (vec32s)(flt[fk] * (vec16s)src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         // Rounding & Scaling
         r  += (fone >> 1);
         r >>= fscl;
         
         // Saturation TODO: use vsat for 32 bit vector once supported
         r = vselect(r, vec32s(32767), r <= 32767);
		 r = vselect(r, vec32s(-32768), r >= -32768);
         
         dst[by*dstr + bx] = (vec16s)r;
      }
   }
}


#endif /* ACF_KERNEL_IMPLEMENTATION */
