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
*  \file apu_color_conversion.c
*  \brief APU color conversion kernels.
***********************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#include <stdio.h>
#include "apu_color_conversion_impl.h"
#include "apu_color_conversion_ht_impl.cpp"

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
                           int bw, int bh)
{
   vec08u r, g, b;
   for (int by = 0; by < bh; by++) chess_loop_range(1,)  {
      for (int bx = 0; bx < bw; bx++) chess_loop_range(1,)  {  
         r = (vec08u)((src[bx] >> 8) & 0xF8);
         g = (vec08u)((src[bx] >> 3) & 0xFC);
         b = (vec08u)((src[bx] & 0x1F) << 3);
         r |= (r >> 5);
         g |= (g >> 6);
         b |= (b >> 5);

         dst[bx] = (((vec32u)r << 16) | ((vec32u)g << 8) | (vec32u)b);
      }
      src += sstr;
      dst += dstr;
   }
}

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
                           int bw, int bh)
{
   vec08u r, g, b;
   for (int by = 0; by < bh; by++) chess_loop_range(1,)  {
      for (int bx = 0; bx < bw; bx++) chess_loop_range(1,)  {
         r = (vec08u)(src[bx] >> 19);
         g = (vec08u)((src[bx] >> 10) & 0x3F);
         b = (vec08u)((src[bx] >> 3) & 0x1F);

         dst[bx] = (((vec16u)r << 11) | ((vec16u)g << 5) | (vec16u)b);
      }
      src += sstr;
      dst += dstr;
   }
}

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
apu_csc_rgb2y (      vec08u* dst, int ds,
               const vec08u* src, int ss,
               int bw, int bh,
               int r2y, int g2y, int b2y)
{
   for (int y=0; y<bh; ++y)   chess_loop_range(1,)

   {
      const vec08u* s = (const vec08u*)src;
            vec08u* d = (      vec08u*)dst;

      const int rnd = 128;
      const int scl =   8;

      for (int x=0; x<bw; x+=4) chess_loop_range(1,)
      {
         // absolutly required by chunck of 3 (otherwise it is less efficient)
         const vec08u r0 = s[ 0];
         const vec08u g0 = s[ 1];
         const vec08u b0 = s[ 2]; s += 4;

         //
         const vec16u y0 =
               (   rnd
                + ((vec16u)r0 * r2y)
                + ((vec16u)g0 * g2y)
                + ((vec16u)b0 * b2y) ) >> scl;

         const vec08u r1 = s[ 0];
         const vec08u g1 = s[ 1];
         const vec08u b1 = s[ 2]; s += 4;

         const vec08u r2 = s[ 0];
         const vec08u g2 = s[ 1];
         const vec08u b2 = s[ 2]; s += 4;

         const vec08u r3 = s[ 0];
         const vec08u g3 = s[ 1];
         const vec08u b3 = s[ 2]; s += 4;

         const vec16u y1 =
               (   rnd
                + ((vec16u)r1 * r2y)
                + ((vec16u)g1 * g2y)
                + ((vec16u)b1 * b2y) ) >> scl;
         const vec16u y2 =
               (   rnd
                + ((vec16u)r2 * r2y)
                + ((vec16u)g2 * g2y)
                + ((vec16u)b2 * b2y) ) >> scl;
         const vec16u y3 =
               (   rnd
                + ((vec16u)r3 * r2y)
                + ((vec16u)g3 * g2y)
                + ((vec16u)b3 * b2y) ) >> scl;

         vec16u da = vsat(y0, 0, 255);
         vec16u db = vsat(y1, 0, 255);
         vec16u dc = vsat(y2, 0, 255);
         vec16u dd = vsat(y3, 0, 255);

         d[0] = (vec08u)da;
         d[1] = (vec08u)db;
         d[2] = (vec08u)dc;
         d[3] = (vec08u)dd; d+=4;
      }

      src += ss;
      dst += ds;
   }
}

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
                int bw, int bh)
{
   for (int y=0; y<bh; ++y)   chess_loop_range(1,)
   {
      const vec08u* s = (const vec08u*)src;
            vec08u* d = (      vec08u*)dst;

      for (int x=0; x<4*bw; x+=4) chess_loop_range(1,)
      {
         // must be vec16s
         const vec16u r = (vec16u)s[x+0];
         const vec16u g = (vec16u)s[x+1];
         const vec16u b = (vec16u)s[x+2];


         const vec16u y  = (
                           + (b *  29)
                           + (r *  77)
                           + (g * 150)
                           +     128
                     ) >> 8;

         const vec16u u  = (
                           + (r * -43)
                           + (g * -85)
                           + (b * 128)
                           +    128
                     ) >> 8;

         const vec16u v  = (
                           + (b * -21)
                           + (g *-107)
                           + (r * 128)
                           +    128
                     ) >> 8;

         d[x+0] = (vec08u)(y      );
         d[x+1] = (vec08u)(u + 128);
         d[x+2] = (vec08u)(v + 128);
         d[x+3] = 0;

      }

      src += ss;
      dst += ds;
   }
}

#endif /* ACF_KERNEL_IMPLEMENTATION */
