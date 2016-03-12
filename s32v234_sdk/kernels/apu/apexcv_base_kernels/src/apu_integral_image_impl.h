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
*  \file apu_integral_image.h
*  \brief APU integral image kernel.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION
#ifndef _APU_INTEGRAL_IMAGE_H_
#define _APU_INTEGRAL_IMAGE_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif

#include <stdint.h>

/*!
   Intiialize line buffer for temporary data required to compute integral image.

   \param tlst - [Output] Destination block pointer
   \param bw   - [Input]  Block width
 */
void
apu_integral_init(vec32u __cmem* tlst, int bw);

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
apu_integral_image(vec32u __cmem* dst, int dstr, const vec08u __cmem* src, vec32u __cmem* tlst, int sstr, int bw, int bh, int ncu);

#endif /* _APU_INTEGRAL_IMAGE_H_ */
#endif /* ACF_KERNEL_IMPLEMENTATION */
