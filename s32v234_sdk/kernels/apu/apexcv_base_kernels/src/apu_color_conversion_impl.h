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
*  \file apu_color_conversion.h
*  \brief APU color conversion kernels.
***********************************************************************************/
#ifdef ACF_KERNEL_IMPLEMENTATION

#ifndef _APU_COLOR_CONVERSION_IMPL_H_
#define _APU_COLOR_CONVERSION_IMPL_H_

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;
#endif



/*!
   Converts 16 bit RGB565 to 24 bit RGB888

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void 
apu_csc_rgb565_to_rgb888( vec32u* dst, int dstr,
                const vec16u* src, int sstr,
                           int bw, int bh);

/*!
   Converts 24 bit RGB888 to 16 bit RGB565

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
 */
void
apu_csc_rgb888_to_rgb565( vec16u* dst, int dstr,
                    const vec32u* src, int sstr,
                               int bw, int bh);

/*!
   Calculate grayscale pixel from RGBX pixel.

   \param dst  - [Output] Destination block pointer   (Grayscale)
   \param ds   - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer        (RGBX)
   \param ss   - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param r2y  - [Input]  Red to gray conversion factor
   \param g2y  - [Input]  Green to gray conversion factor
   \param b2y  - [Input]  Blue to gray conversion factor
 */
void
apu_csc_rgb2y( vec08u* dst, int ds,
               const vec08u* src, int ss,
               int bw, int bh,
               int r2y, int g2y, int b2y);

/*!
   Calculate YUVX pixel from RGBX pixel.

   References on formula and values used for conversion:
   http://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.601-7-201103-I!!PDF-E.pdf
   http://www.poynton.com/PDFs/ColorFAQ.pdf

   \param dst  - [Output] Destination block pointer  (YUVX)
   \param ds   - [Input]  Destination block span
   \param src  - [Input]  Source block pointer       (RGBX)
   \param ss   - [Input]  Source block span
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height

 */
void
apu_csc_rgb2yuv(      vec08u* dst, int ds,
                const vec08u* src, int ss,
                int bw, int bh);

/* Namespace for Hand-Tuned functions */
namespace ht{
/*!
   3-channel to grayscale, 8-bit color conversion.
 
   The source image is laid out in the format
  
              | A0 B0 C0 X0 | A1 B1 C1 X1 | A2 B2 C2 X2 | ...
  
   with each pixel consisting of three 8-bit channels and an 8-bit padding.
   The output image's pixels are a linear function of the corresponding input pixel's
   channels:
 
              Y = kA*A + kB*B + kC*C + kR
  
   with kA, kB, kC any 8-bit unsigned value and kR any 16-bit unsigned value.
  
   For input
            - RGBX: kA=76, kB=150, kC=29, kR=127
            - BGRX: kA=29, kB=150, kC=76, kR=127

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
   \param kA    - [Input]  Conversion Factor A
   \param kB    - [Input]  Conversion Factor B
   \param kC    - [Input]  Conversion Factor C
   \param kR    - [Input]  Conversion Factor R
 */
void apu_csc_8UC3_Y(vec16s* restrict dst, int dstr, const vec08u* restrict src,
                    int sstr, int bw, int bh,
                    uint8_t kA, uint8_t kB, uint8_t kC, uint16_t kR);
}

#endif /* _APU_COLOR_CONVERSION_H_ */
#endif /* ACF_KERNEL_IMPLEMENTATION */
