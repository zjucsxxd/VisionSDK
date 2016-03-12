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

/**************************************************************************** /
/*!
* \file apu_interpolation_impl.h
* \brief interpolation functions implementation for APEX
* \addtogroup apexcv interpolation implementation for APEX
* @{
****************************************************************************/

/*!*********************************************************************************
*  \file apu_interpolation.h
*  \brief APU interpolation kernels.
***********************************************************************************/
#ifdef ACF_KERNEL_IMPLEMENTATION
#ifndef _APU_INTERPOLATION_IMPL_H_
#define _APU_INTERPOLATION_IMPL_H_


#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif


/*!
   Applies a Grayscale Linear Interpolation.
   
   \param dst       - [Output] Destination block pointer
   \param dstr      - [Input]  Destination block stride
   \param src       - [Input]  Source block pointer
   \param sstr      - [Input]  Source block stride
   \param bw        - [Input]  Block width
   \param bh        - [Input]  Block height
   \param delta     - [Input]  Delta X Values
 */
void 
apu_interp_linear_grayscale (
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
                 int bw, int bh,
      const vec08u* delta);
              
/*!
   Applies a Grayscale Bilinear Interpolation.
   
   \param dst       - [Output] Destination block pointer
   \param dstr      - [Input]  Destination block stride
   \param src       - [Input]  Source block pointer
   \param sstr      - [Input]  Source block stride
   \param bw        - [Input]  Block width
   \param bh        - [Input]  Block height
   \param delta     - [Input]  Delta XY Values
 */
void
apu_interp_bilinear_grayscale (
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
                 int bw, int bh,
      const vec08u* delta);

/*!
   Applies a Bicubic Interpolation.
   
   \param dst       - [Output] Destination block pointer
   \param dstr      - [Input]  Destination block stride
   \param src       - [Input]  Source block pointer
   \param sstr      - [Input]  Source block stride
   \param bw        - [Input]  Block width
   \param bh        - [Input]  Block height
   \param x_offset  - [Input]  X offset from source pixel
   \param y_offset  - [Input]  Y offset from source pixel
 */
void
apu_interp_bicubic_grayscale(
            vec08u* dst, int dstr,
      const vec08u* src, int sstr,
            int bw, int bh,
            uint8_t x_offset, uint8_t y_offset);

#endif /* _APU_INTERPOLATION_H_ */
#endif /* ACF_KERNEL_IMPLEMENTATION */


/*! @} */
