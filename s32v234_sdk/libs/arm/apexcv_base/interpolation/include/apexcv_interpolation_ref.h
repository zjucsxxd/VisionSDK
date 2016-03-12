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
*  \file apexcv_interpolation_ref.hpp
*  \brief Reference code for interpolation kernels
***********************************************************************************/

#ifndef _APEXCV_INTERPOLATION_REF_H_
#define _APEXCV_INTERPOLATION_REF_H_

#include <stdint.h>

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
interp_linear_grayscale_ref(
               uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
               int bw, int bh,
         const uint8_t* delta);

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
interp_bilinear_grayscale_ref(
               uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
               int bw, int bh, 
         const uint8_t* delta);

void interp_bicubic_grayscale_ref(
               uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
               int bw, int bh,
         const uint8_t x_offset, const uint8_t y_offset);

            
#endif /* _APEXCV_INTERPOLATION_REF_H_ */
