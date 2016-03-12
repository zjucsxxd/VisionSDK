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
*  \file apu_arithmetic.h
*  \brief APU basic arithmetic kernels.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#ifndef _APU_ARITHMETIC_IMPL_H_
#define _APU_ARITHMETIC_IMPL_H_

/**************************************************************************** /
/*!
* \file apu_arithmetic_impl.h
* \brief arithmetic functions implementation for APEX
* \addtogroup apexcv arithmetic implementation for APEX
* @{
****************************************************************************/
#include <stdint.h>



#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

/*! 
	Computes Square root of its input 
	\param a - [Input] Source value
	\return	   [Output] Square root of input value
*/
vec32u vsqrt_32(vec32u a);

/*!
   Calculates the absolute value from one sources
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source value block pointer
   \param sstr  - [Input]  Source value block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_abs(    vec08u* dst, int dstr,
      const vec08s* src, int sstr,
                 int bw, int bh);            

/*!
   Calculates the absolute difference between two sources
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_absdiff(    vec08u* dst, int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);
					 
/*!
   Calculates sum of two images
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 block pointer
   \param sstr1 - [Input]  Source 1 block stride
   \param src2  - [Input]  Source 2 block pointer
   \param sstr2 - [Input]  Source 2 block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void 
apu_accumulate(vec16s* dst,  int dstr,
               const vec08u* src1,  int sstr1,
               const vec08u* src2,  int sstr2,
                int bw, int bh);

/*!
   Calculates squared sum of two images
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 block pointer
   \param sstr1 - [Input]  Source 1 block stride
   \param src2  - [Input]  Source 2 block pointer
   \param sstr2 - [Input]  Source 2 block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param scale - [Input]  Image 2 Scale
*/
void 
apu_accumulate_squared(vec16s* dst,  int dstr,
               const vec08u* src1,  int sstr1,
               const vec08u* src2,  int sstr2,
                int bw, int bh, uint8_t scale);

/*!
   Calculates weighted sum of two images
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 block pointer
   \param sstr1 - [Input]  Source 1 block stride
   \param src2  - [Input]  Source 2 block pointer
   \param sstr2 - [Input]  Source 2 block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param alpha - [Input]  Weight between [0 and 256]
  
   ASSUMPTION: both sources are of same size. Weight is determined by alpha which ranges from [0-256].
               ie. ~70% weight is 179. Accuracy is lost if user of API wants exactly 70% but result is 
               accurate w.r.t alpha.
*/
void 
apu_accumulate_weighted(vec08u* dst,  int dstr,
                  const vec08u* src1, int sstr1,
                  const vec08u* src2, int sstr2,
                  int bw, int bh, uint8_t alpha);
                  
/*!
   Adds source 1 to source 2 (unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_add(        vec08u* dst, int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);

/*!
   Adds source 1 to source 2 (signed 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_add(        vec16s* dst, int dstr,
         const vec16s* src1, int sstr1,
         const vec16s* src2, int sstr2,
                     int bw, int bh);

/*!
   Calculates the bitwise AND from two sources (unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_and(        vec08u* dst, int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);                    
                     
/*!
   Calculates the bitwise AND from two sources (unsigned 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_and(        vec16u* dst, int dstr,
         const vec16u* src1, int sstr1,
         const vec16u* src2, int sstr2,
                     int bw, int bh);                   

/*!
   Calculates the bitwise AND from two sources (unsigned 32 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_and(        vec32u* dst, int dstr,
         const vec32u* src1, int sstr1,
         const vec32u* src2, int sstr2,
                     int bw, int bh);
                     
/*!
   Counts leading zeros (signed 16 bit)

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source value block pointer
   \param sstr  - [Input]  Source value block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void
apu_clz(       vec08u* dst, int dstr,
               const vec16s* src, int sstr,
               int bw, int bh);

/*!
   Counts leading zeros (unsigned 16 bit)

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source value block pointer
   \param sstr  - [Input]  Source value block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void
apu_clz(       vec08u* dst, int dstr,
               const vec16u* src, int sstr,
               int bw, int bh);
/*!
   Counts leading zeros (signed 8 bit)

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source value block pointer
   \param sstr  - [Input]  Source value block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/

void
apu_clz(       vec08u* dst, int dstr,
               const vec08s* src, int sstr,
               int bw, int bh);
/*!
   Counts leading zeros (unsigned 8 bit)

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source value block pointer
   \param sstr  - [Input]  Source value block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void
apu_clz(       vec08u* dst, int dstr,
               const vec08u* src, int sstr,
               int bw, int bh);


/*!
   Calculates magnitude of image matrix
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param srcx  - [Input]  Source x values block pointer
   \param sstrx - [Input]  Source x values block stride
   \param srcy  - [Input]  Source y values block pointer
   \param sstry - [Input]  Source y values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_magnitude( vec16u* dst, int dstr,
        const vec16s* srcx, int sstrx,
        const vec16s* srcy, int sstry,
                    int bw, int bh);
                    
/*!
   Calculates the bitwise NOT of the source.
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_not(       vec08u* dst, int dstr,
         const vec08u* src, int sstr,
                    int bw, int bh);
                    
/*!
   Calculates the bitwise OR from two sources (unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_or(        vec08u* dst, int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);                 
                     
/*!
   Calculates the bitwise OR from two sources (unsigned 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_or(        vec16u* dst, int dstr,
         const vec16u* src1, int sstr1,
         const vec16u* src2, int sstr2,
                     int bw, int bh);              

/*!
   Calculates the bitwise OR from two sources (unsigned 32 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_or(        vec32u* dst, int dstr,
         const vec32u* src1, int sstr1,
         const vec32u* src2, int sstr2,
                     int bw, int bh);

/*!
   Subtracts source 2 from source 1 (unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_sub(       vec16s* dst,  int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);       

/*!
   Subtracts source 2 from source 1 (signed 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_sub(       vec16s* dst,  int dstr,
         const vec16s* src1, int sstr1,
         const vec16s* src2, int sstr2,
                     int bw, int bh);
                     
/*!
   Calculates an unsigned 8 bit boolean output image based on threshold (input unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param thres - [Input]  Threshold value
 */
void 
apu_threshold( vec08u* dst, int dstr,
         const vec08u* src, int sstr,
            int bw, int bh, uint8_t threshold);

/*!
   Calculates an unsigned 8 bit boolean output image based on threshold (input unsigned 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param thres - [Input]  Threshold value
 */
void 
apu_threshold( vec08u* dst, int dstr,
         const vec16u* src, int sstr,
            int bw, int bh, uint16_t threshold);

/*!
   Calculates an unsigned 8 bit boolean output image based on threshold (input unsigned 32 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param thres - [Input]  Threshold value
 */
void 
apu_threshold( vec08u* dst, int dstr,
         const vec32u* src, int sstr,
            int bw, int bh, uint32_t threshold);
        
/*!
   Calculates the bitwise XOR from two sources (unsigned 8 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_xor(        vec08u* dst, int dstr,
         const vec08u* src1, int sstr1,
         const vec08u* src2, int sstr2,
                     int bw, int bh);              
                     
/*!
   Calculates the bitwise XOR from two sources (unsigned 16 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_xor(        vec16u* dst, int dstr,
         const vec16u* src1, int sstr1,
         const vec16u* src2, int sstr2,
                     int bw, int bh); 

/*!
   Calculates the bitwise XOR from two sources (unsigned 32 bit)
 
   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src1  - [Input]  Source 1 values block pointer
   \param sstr1 - [Input]  Source 1 values block stride
   \param src2  - [Input]  Source 2 values block pointer
   \param sstr2 - [Input]  Source 2 values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_xor(        vec32u* dst, int dstr,
         const vec32u* src1, int sstr1,
         const vec32u* src2, int sstr2,
                     int bw, int bh);
                     
/*!
   Calculate minimum SAD & location given a template and a window
 
   \param lpvIn0           - [Input]  Source template block pointer
   \param lStrideIn0       - [Input]  Template block stride
   \param lChunkWidthIn0   - [Input]  Template block width
   \param lChunkHeightIn0  - [Input]  Template block height
   \param lpvIn1           - [Input]  Source window block pointer
   \param lStrideIn1       - [Input]  Window block stride
   \param lChunkWidthIn1   - [Input]  Window block width
   \param lChunkHeightIn1  - [Input]  Window block height
   \param lpvOut0          - [Output] Destination block pointer
   \param lStrideOut0      - [Input]  Destination block stride
   \param lChunkWidthOut0  - [Input]  Template block width
   \param lChunkHeightOut0 - [Input]  Template block height
 */
void
apu_sad (vec08u* lpvIn0, int16_t lStrideIn0, int16_t lChunkWidthIn0, int16_t lChunkHeightIn0,
         vec08u* lpvIn1, int16_t lStrideIn1, int16_t lChunkWidthIn1, int16_t lChunkHeightIn1,
         vec32u* lpvOut0, int16_t lStrideOut0, int16_t lChunkWidthOut0, int16_t lChunkHeightOut0);
                    
#endif /* _APU_ARITHMETIC_H_ */
/*! @} */
#endif /* ACF_KERNEL_IMPLEMENTATION */
