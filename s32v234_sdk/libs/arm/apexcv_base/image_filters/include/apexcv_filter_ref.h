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
*  \file apexcv_filter_ref.hpp
*  \brief Reference code for filter kernels
***********************************************************************************/

#ifndef _APEXCV_FILTER_REF_HPP_
#define _APEXCV_FILTER_REF_HPP_

#include <stdint.h>

/*!
   Calculate a 3x3 dilate filter.

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void dilate_3x3_08u_ref( uint8_t* dst, int dstr,
                   const uint8_t* src, int sstr,
                                int bw, int bh );

/*!
   Calculate a 3x3 dilate filter.

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void dilate_3x3_16s_ref( int16_t* dst, int dstr,
                   const int16_t* src, int sstr,
                               int bw, int bh );

/*!
   Calculate a 3x3 erode filter.

   \param dst   - [Output] Destination block pointer
   \param dstr  - [Input]  Destination block stride
   \param src   - [Input]  Source values block pointer
   \param sstr  - [Input]  Source values block stride
   \param bw    - [Input]  Block width
   \param bh    - [Input]  Block height
*/
void erode_3x3_08u_ref( uint8_t* dst, int dstr,
                  const uint8_t* src, int sstr,
                               int bw, int bh );

/*!
   Calculates 5x5 bilateral filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
   \param sigmaR - [Input]  Intensity sigma
   \param sigmaD - [Input]  Distance sigma
 */
void
bilateral_5x5_ref(  uint8_t* dst, int dstr,
              const uint8_t* src, int sstr,
                          int bw, int bh,
                      int sigmaR, int sigmaD );

/*!
   Calculates 3x3 box filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
box_3x3_ref(  uint8_t* dst, int dstr,
        const uint8_t* src, int sstr,
                    int bw, int bh );

/*!
   Calculates 3x3 box filter of image with no rounding

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
box_3x3_nr_ref(uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
                     int bw, int bh );

/*!
   Calculates 3x3 box filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
box_3x3_ref(  int16_t* dst, int dstr,
        const int16_t* src, int sstr,
                    int bw, int bh );

/*!
   Calculates 5x5 box filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
box_5x5_ref(  int16_t* dst, int dstr,
        const int16_t* src, int sstr,
                    int bw, int bh );

/*!
   Calculates 3x3 central x derivative of an image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
   \param k1     - [Input]  1st Coefficient
   \param k2     - [Input]  2nd Coefficient
   \param k3     - [Input]  3rd Coefficient
 */
void
derivative_x_3x3_16s_ref(  int16_t* dst, int dstr,
                     const uint8_t* src, int sstr,
                                 int bw, int bh,
                         int k0, int k1, int k2);

/*!
   Calculates 3x3 central y derivative of an image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
   \param k1     - [Input]  1st Coefficient
   \param k2     - [Input]  2nd Coefficient
   \param k3     - [Input]  3rd Coefficient
 */
void
derivative_y_3x3_16s_ref(  int16_t* dst, int dstr,
                     const uint8_t* src, int sstr,
                                 int bw, int bh,
                         int k0, int k1, int k2);

/*!
   Calculate a 3x3 median filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
median_3x3_08u_ref( uint8_t* dst, int dstr,
              const uint8_t* src, int sstr,
                          int bw, int bh);

/*!
   Calculate a 5x5 median filter.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
median_5x5_08u_ref( uint8_t* dst, int dstr,
              const uint8_t* src, int sstr,
                          int bw, int bh);

/*!
   Calculates 3x3 gaussian filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
gaussian_3x3_08u_ref(  uint8_t* dst, int dstr,
        const uint8_t* src, int sstr,
                    int bw, int bh );

/*!
   Calculates 5x5 gaussian filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
 */
void
gaussian_5x5_08u_ref(  uint8_t* dst, int dstr,
        const uint8_t* src, int sstr,
                    int bw, int bh );

/*!
   Perform a 16s to 08s saturation. Scales down by 8 and
   rounds before saturation.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
saturate_08s_ref(
            int8_t* dst, int dstr,
      const int16_t* src, int sstr,
            int bw, int bh);

/*!
   Calculates 3x3 separable filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
   \param fRow   - [Input]  Row coefficients
   \param fCol   - [Input]  Column Coefficients
 */
void
separable_3x3_16s_ref(  int16_t* dst, int dstr,
                  const uint8_t* src, int sstr,
                              int bw, int bh,
             const signed char* fRow,
             const signed char* fCol);
             
/*!
   Calculates 5x5 separable filter of image

   \param dst    - [Output] Destination block pointer
   \param dstr   - [Input]  Destination block stride
   \param src    - [Input]  Source value block pointer
   \param sstr   - [Input]  Source value block stride
   \param bw     - [Input]  Block width
   \param bh     - [Input]  Block height
   \param fRow   - [Input]  Row coefficients
   \param fCol   - [Input]  Column Coefficients
 */
void
separable_5x5_16s_ref(  int16_t* dst, int dstr,
                  const uint8_t* src, int sstr,
                              int bw, int bh,
             const signed char* fRow,
             const signed char* fCol);

/*!
   Calculate first order derivative x using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_x_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);
      
/*!
   Calculate first order derivative x using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_x_3x3_08s_ref(
             int8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);
      
/*!
   Calculate first order derivative y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_y_3x3_08s_ref(
             int8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

/*!
   Calculate first order derivative y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_y_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

/*!
   Calculate first order derivative x using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_x_5x5_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

/*!
   Calculate first order derivative y using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_y_5x5_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);
      
/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 3x3.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_3x3_16s_ref(
            int16_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

/*!
   Calculate sum of absolute values of first order derivatives x and y using sobel 5x5.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
sobel_5x5_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh);

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
convolve_08u_ref(
         uint8_t* dst, int dstr,
   const uint8_t* src, int sstr,
   int bw, int bh,
   const int8_t* flt, int fw, int fh);

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
convolve_scale_08u_ref(
         uint8_t* dst, int dstr,
   const uint8_t* src, int sstr,
   int bw, int bh,
   const int8_t* flt, int fw, int fh,
   int fscl);

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
convolve_scale_08u_nr_ref(
         uint8_t* dst, int dstr,
   const uint8_t* src, int sstr,
   int bw, int bh,
   const int8_t* flt, int fw, int fh,
   int fscl);

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
convolve_16s_ref(
         int16_t* dst, int dstr,
   const uint8_t* src, int sstr,
   int bw, int bh,
   const int8_t* flt, int fw, int fh);

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
convolve_scale_16s_ref(
         int16_t* dst, int dstr,
   const uint8_t* src, int sstr,
   int bw, int bh,
   const int8_t* flt, int fw, int fh,
   int fscl);

/*!
   Applies a 3x3 prewitt filter in the x direction.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
prewitt_x_3x3_ref(
         int16_t* dst, int dstr,
   const uint8_t* src, int sstr,
               int bw, int bh );

/*!
   Applies a 3x3 prewitt filter in the y direction.

   \param dst  - [Output] Destination block pointer
   \param dstr - [Input]  Destination block stride
   \param src  - [Input]  Source block pointer
   \param sstr - [Input]  Source block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height
 */
void
prewitt_y_3x3_ref(
         int16_t* dst, int dstr,
   const uint8_t* src, int sstr,
               int bw, int bh );

#endif /* _APEXCV_FILTER_REF_HPP_ */
