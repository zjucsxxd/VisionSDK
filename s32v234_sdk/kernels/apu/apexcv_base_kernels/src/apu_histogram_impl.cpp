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
*  \file apu_histogram.c
*  \brief APU histogram kernels.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#include <stdint.h>
#include "apu_histogram_impl.h"

#define HIST_BIN_NBR     (256)

/*!
   Initialize Local Histograms (CMEM)

   \param hist  - [Output] Local Histograms (CMEM)
   \param nbr   - [Input]  Number of Bins
 */
void
apu_hist_init_l(vec16u* hst, int nbr)
{
   for (int k=0; k<nbr; ++k) 
      hst[k] = 0;
}

void
apu_hist_init_l(vec16u* hst)
{
   apu_hist_init_l(hst, HIST_BIN_NBR);
}

/*!
   Initialize Global Histograms (DMEM)

   \param hist  - [Output] Global Histogram (DMEM)
   \param nbr   - [Input]  Number of Bins
 */
void
apu_hist_init_g(uint32_t* hst, int nbr)
{
   for (int k=0; k<nbr; ++k) 
      hst[k] = 0;
}

void
apu_hist_init_g(uint32_t* hst)
{
   apu_hist_init_g(hst, HIST_BIN_NBR);
}

// Local Histogram (1D)
//    Maximum: 2^16-1 /CU
//    BEST CASE              10 CC
//       1 LD SOURCE (08u)    1
//       1 LD HIST   (16u)    4
//       1 ADD       (16u)    1
//       1 ST HIST   (16u)    4
// 
// 429 (26 CC, 2 NOP/iteration)
//    >>> potential data dependancies <<<
/*!
   Calculate a local histogram for an image tile.  
   This input image is 8 bits per pixel, 
   and the histogram must have at enough bins to contain maximum source value 
   (256 bins, for [0-255]).

   \param lhist - [Output] 256-bin Local Histogram (CMEM)
   \param src   - [Input]  Source Pointer buffer
   \param bw    - [Input]  Source Stride
   \param bw    - [Input]  Source Width, in pixels (must be a multiple of 2, 16-bit aligned)
   \param bh    - [Input]  Source Height
 */
void
apu_hist1_l(vec16u* lhist, const vec08u* src, int sstr, int bw, int bh)
{
   // data must be aligned 16-bit
   
   /* This code does not work with emulation library due to Memory organization in vectors<vectors of CU's> and not CU_vectors<data_vectors>, as it is needed here
   const vec16u* s = (const vec16u*)src;
   sstr >>= 1;
   // Local Histogram
   for (int y = 0; y<bh; ++y) 
   {
      vec16u v  = s[0];
      for (int x=1; x<(bw>>1); ++x)
      {
         const vec16s v0 = (vec16s)(v & 0x0FF);
         const vec16s v1 = (vec16s)(v >> 8);
         v  = s[x];
         const vec16u d0 = vload(lhist, v0) + 1; vstore(lhist, v0, d0);
         const vec16u d1 = vload(lhist, v1) + 1; vstore(lhist, v1, d1);
      }

      {
         const vec16s v0 = (vec16s)(v & 0x0FF);
         const vec16s v1 = (vec16s)(v >> 8);
         const vec16u d0 = vload(lhist, v0) + 1; vstore(lhist, v0, d0);
         const vec16u d1 = vload(lhist, v1) + 1; vstore(lhist, v1, d1);
      }
      
      s += sstr;
   }*/

   const vec08u* s = (const vec08u*)src;
   for (int y = 0; y<bh; ++y)
   {
	   
	   for (int x = 0; x < bw; ++x)
	   {
		   vec08u v = s[x];
		   const vec16u d0 = vload(lhist, v) + 1; vstore(lhist, v, d0);
		   int dummy = 0;
	   }

	   s += sstr;
   }
}


// Global Histogram (1D) (Reduction)  (using CU for intermediate results)
/*!
   Accumulate in Global Histogram (DMEM) all the Local Histograms (CMEM)

   \param ghist - [Output] 256-bin Global Histogram (DMEM)
   \param lhist - [Input]  256-bin Local  Histogram (CMEM)
   
   \bug: assumption all CUs are enabled... which depends on the image size.
 */
void
apu_hist1_gn(uint32_t* ghist, const vec16u __cmem* lhist, int bcu, int ecu)
{
	/* TODO: add a static value to each CU so we can get its CID.
   /*       once done we can use this code.
	if ((CID < bcu) || (CID >= ecu))
	{
		for (int k=0; k<HIST_BIN_NBR; ++k)
			list[k] = 0;
	}
	*/
   // Histogram Bin Reduction
   for (int k=0; k<HIST_BIN_NBR; ++k)
   {	
      /* Once the above code with CID is supported we can use this code.
      vec32u bb = (vec32u)lhist[k];
      vec32u aa = bb;
			
      for (int s=1; s<ncu; s<<=1)
      {
         for (int c=0; c<s; ++c) 
         {
            bb = vec32u(vmsl(bb.high()), vmsl(bb.low()));
         }
         aa += bb;
         bb  = aa;
      }
		
      // Transfer Data in DMEM
      {
         const uint32_t l = vget(aa.low(),  0);
         const uint32_t h = vget(aa.high(), 0);
         ghist[k] += (h << 16) | (l);
      }
		*/
      
      /* Temporary global accumulator */
      vec16u b = lhist[k];
		for (int c = bcu; c < ecu; c++) {
			
			ghist[k] += vget(b, c);
		}
   }
}

#endif /* ACF_KERNEL_IMPLEMENTATION */
