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
*  \file apu_histogram.h
*  \brief APU histogram kernels.
***********************************************************************************/
#ifdef ACF_KERNEL_IMPLEMENTATION

#ifndef _APU_HISTOGRAM_H_
#define _APU_HISTOGRAM_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

#include <stdint.h>

/*!
   Initialize Local Histograms (CMEM)

   \param hist  - [Output] 256-bin Local Histograms (CMEM)
 */
void  apu_hist_init_l(vec16u*   hist);
/*!
   Initialize Local Histograms (CMEM)

   \param hist  - [Output] Local Histograms (CMEM)
   \param nbr   - [Input]  Number of Bins
 */
void  apu_hist_init_l(vec16u*   hist, int nbr);

/*!
   Initialize Global Histograms (DMEM)

   \param hist  - [Output] Global Histogram (DMEM)
   \param nbr   - [Input]  Number of Bins
 */
void  apu_hist_init_g(uint32_t* hist);
/*!
   Initialize Global Histograms (DMEM)

   \param hist  - [Output] Global Histogram (DMEM)
   \param nbr   - [Input]  Number of Bins
 */
void  apu_hist_init_g(uint32_t* hist, int nbr);


/*!
   Calculate a local histogram for an image tile.  
   This input image is 8 bits per pixel, 
   and the histogram must have at enough bins to contain maximum source value 
   (256 bins, for [0-255]).

   \param lhist - [Output] 256-bin Local Histogram (CMEM)
   \param src   - [Input]  Source Pointer buffer
   \param sstr  - [Input]  Source Stride
   \param bw    - [Input]  Source Width, in pixels (must be a multiple of 2, 16-bit aligned)
   \param bh    - [Input]  Source Height
 */
void  apu_hist1_l(vec16u __cmem* lhist, const vec08u __cmem* src, int sstr, int bw, int bh);

/*!
   Accumulate in Global Histogram (DMEM) all the Local Histograms (CMEM)

   \param ghist - [Output] 256-bin Global Histogram (DMEM)
   \param lhist - [Input]  256-bin Local  Histogram (CMEM)
   \param ncu   - [Input]  Number of CUs
 */
void  apu_hist1_gn(uint32_t* ghist, const vec16u __cmem* lhist, int bcu, int ecu);

#endif /* _APU_HISTOGRAM_H_ */
#endif /* _APU_HISTOGRAM_H_ */
