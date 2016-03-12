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
*  \file apexcv_color_conversion_ref.hpp
*  \brief Reference code for color conversion kernels
***********************************************************************************/

#ifndef _APEXCV_COLOR_CONVERSION_REF_HPP_
#define _APEXCV_COLOR_CONVERSION_REF_HPP_

#include <stdint.h>

/*!
   Converts 16 bit RGB565 to 24 bit RGB888

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void rgb565_to_rgb888_ref( uint32_t* dst, uint32_t dstr,
                     const uint16_t* src, uint32_t sstr,
                uint32_t bw, uint32_t bh );


/*!
   Converts 24 bit RGB888 to 16 bit RGB565

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void rgb888_to_rgb565_ref( uint16_t* dst, uint32_t dstr,
            const uint32_t * src, uint32_t sstr,
            uint32_t bw, uint32_t bh );

/*!
   Calculate grayscale pixel from RGBX pixel.

   \param dst  - [Output] Destination block pointer   (Grayscale)
   \param ds   - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer        (RGBX)
   \param ss   - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param R2Y  - [Input]  Red to gray conversion factor
   \param G2Y  - [Input]  Green to gray conversion factor
   \param B2Y  - [Input]  Blue to gray conversion factor
 */
void rgb888_to_y_ref( uint8_t* dst, uint32_t ds,
                const uint8_t* src, uint32_t ss,
            uint32_t bw, uint32_t bh,
            uint32_t R2Y, uint32_t G2Y, uint32_t B2Y);

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
void rgb888_to_yuv_ref( uint8_t* dst, uint32_t ds,
                  const uint8_t* src, uint32_t ss,
              uint32_t bw, uint32_t bh);

/*!
   Calculate grayscale pixel from 3-Channel pixel.

   \param dst  - [Output] Destination block pointer   (Grayscale)
   \param ds   - [Input]  Destination block span
   \param src  - [Input]  Source block pointer        (RGBX)
   \param ss   - [Input]  Source block span
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
   \param KA   - [Input]  Channel 1 to gray conversion factor
   \param KB   - [Input]  Channel 2 to gray conversion factor
   \param KC   - [Input]  Channel 3 to gray conversion factor
   \param KR   - [Input]  Pixel Addition factor
 */
void csc_8UC3_to_y_ref( int16_t* dst, int ds,
                   const uint8_t* src, int ss,
                   int bw, int bh,
                   uint8_t KA, uint8_t KB, uint8_t KC, uint16_t KR);

#endif /* _APEXCV_COLOR_CONVERSION_REF_HPP_ */
