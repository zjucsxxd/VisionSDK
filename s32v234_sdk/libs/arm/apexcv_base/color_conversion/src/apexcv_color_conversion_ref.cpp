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
*  \file apexcv_color_conversion_ref.cpp
*  \brief Reference code for color conversion kernels
***********************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <apexcv_color_conversion_ref.h>

void rgb565_to_rgb888_ref( uint32_t* dst, uint32_t dstr,
                     const uint16_t* src, uint32_t sstr,
                uint32_t bw, uint32_t bh )
{
   uint8_t r, g, b;
   
   for(uint32_t y = 0; y < bh; ++y) {
      for(uint32_t x = 0; x < bw; ++x) {

         r = (src[x] >> 8) & 0xF8;
         g = (src[x] >> 3) & 0xFC;
         b = (src[x] << 3) & 0xF8;
         
         r = r | (r >> 5);
         g = g | (g >> 6);
         b = b | (b >> 5);
         
         dst[x] = (r << 16) | (g << 8) | b;
      }
      
      dst += dstr;
      src += sstr;
   }
}

void rgb888_to_rgb565_ref( uint16_t* dst, uint32_t dstr,
      const uint32_t * src, uint32_t sstr,
      uint32_t bw, uint32_t bh )
{
   uint8_t r, g, b;
   
   for(uint32_t y = 0; y < bh; ++y) {
      for(uint32_t x = 0; x < bw; ++x) {

         r = src[x] >> 19;
         g = (src[x] >> 10) & 0x3F; 
         b = (src[x] >> 3) & 0x1F;
         
         dst[x] = (r << 11) | (g << 5) | b; 
      }
      
      dst += dstr;
      src += sstr;
   }
}

void rgb888_to_y_ref( uint8_t* dst, uint32_t ds,
                   const uint8_t* src, uint32_t ss,
                   uint32_t bw, uint32_t bh,
                   uint32_t R2Y, uint32_t G2Y, uint32_t B2Y)
{
   for (uint32_t y=0; y<bh; ++y)
                              
   {
      const uint8_t* s = (const uint8_t*)src;
            uint8_t* d = (      uint8_t*)dst;
      
      const uint32_t rnd = 128;
      const uint32_t scl =   8;
      
      for (uint32_t x=0; x<bw; x+=16)
      {  
         // absolutly required by chunck of 3 (otherwise it is less efficient)
         const uint16_t r0 = s[ 0];
         const uint16_t g0 = s[ 1];
         const uint16_t b0 = s[ 2]; s += 4;
         //printf("%d %d %d\n", r0, g0, b0 );
         //
         const uint16_t y0 =
               (   rnd
                + (r0 * R2Y)
                + (g0 * G2Y)
                + (b0 * B2Y) ) >> scl;
            
         const uint16_t r1 = s[ 0];
         const uint16_t g1 = s[ 1];
         const uint16_t b1 = s[ 2]; s += 4;

         const uint16_t r2 = s[ 0];
         const uint16_t g2 = s[ 1];
         const uint16_t b2 = s[ 2]; s += 4;

         const uint16_t r3 = s[ 0];
         const uint16_t g3 = s[ 1];
         const uint16_t b3 = s[ 2]; s += 4;
         
         const uint16_t y1 =
               (   rnd
                + (r1 * R2Y)
                + (g1 * G2Y)
                + (b1 * B2Y) ) >> scl;
                        
         //printf("rnd: %d, r0: %d, g0: %d, b0: %d, R2Y: %d, G2Y: %d, B2Y: %d, scl: %d, y0: %d\n", rnd, r1, g1, b1, R2Y, G2Y, B2Y, scl, y1);

         const uint16_t y2 =
               (   rnd
                + (r2 * R2Y)
                + (g2 * G2Y)
                + (b2 * B2Y) ) >> scl;
         const uint16_t y3 =
               (   rnd
                + (r3 * R2Y)
                + (g3 * G2Y)
                + (b3 * B2Y) ) >> scl;
                
         d[0] = (y0 > 255) ? 255 : (uint8_t)y0;
         d[1] = (y1 > 255) ? 255 : (uint8_t)y1;
         d[2] = (y2 > 255) ? 255 : (uint8_t)y2;
         d[3] = (y3 > 255) ? 255 : (uint8_t)y3; d += 4;       
      }
      
      src += ss;
      dst += ds;
   }
}

void rgb888_to_yuv_ref(uint8_t* dst, uint32_t ds,
                 const uint8_t* src, uint32_t ss,
             uint32_t bw, uint32_t bh)
{
   for (uint32_t i=0; i<bh; ++i)
   {
      const uint8_t* s = (const uint8_t*)src;
            uint8_t* d = (      uint8_t*)dst;
      
      for (uint32_t x=0; x<4*bw; x+=4)
      {  
         // must be vec16s
         const uint16_t r = (uint16_t)s[x+0];
         const uint16_t g = (uint16_t)s[x+1];
         const uint16_t b = (uint16_t)s[x+2];
         

         const uint16_t y  = (  
                           + (b *  29)
                           + (r *  77)
                           + (g * 150)
                           +     128
                     ) >> 8;
      
         const uint16_t u  = (  
                           + (r * -43)
                           + (g * -85)
                           + (b * 128)
                           +    128
                     ) >> 8;
      
         const uint16_t v  = (  
                           + (b * -21)
                           + (g *-107)
                           + (r * 128)
                           +    128
                     ) >> 8;
                     
         d[x+0] = (uint8_t)(y      );
         d[x+1] = (uint8_t)(u + 128);
         d[x+2] = (uint8_t)(v + 128);
         d[x+3] = 0;

      }
      
      src += ss;
      dst += ds;
   }   
}

void csc_8UC3_to_y_ref( int16_t* dst, int ds,
                   const uint8_t* src, int ss,
                   int bw, int bh,
                   uint8_t KA, uint8_t KB, uint8_t KC, uint16_t KR
)
{
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         uint16_t c1 =  KA*src[4*j];
         uint16_t c2 =  KB*src[4*j+1];
         uint16_t c3 =  KC*src[4*j+2];
         dst[j] = (int16_t)(c1 + c2 + c3 + KR)>>8;
      }
      dst += ds;
      src += ss;
   }
}
