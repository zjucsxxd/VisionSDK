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
*  \file apexcv_filter_ref.cpp
*  \brief Reference code for filter kernels
***********************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#include <apexcv_filter_ref.h>

#define vswap(a, b, c) if(c) { uint8_t tmp = a; a = b; b = tmp; }

using namespace std;

void dilate_3x3_08u_ref( uint8_t* dst, int dstr, 
                   const uint8_t* src, int sstr,
                               int bw, int bh )
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const uint8_t* s0 = src - sstr;
   const uint8_t* s1 = src;
   const uint8_t* s2 = src + sstr;
   
   // Loop
   int16_t a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   int16_t b_max, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; x+=2)
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];
         
         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];
 
         // Compare and find max
         a_max = a0;

         vswap(a1, a_max, a1 > a_max);
         vswap(a2, a_max, a2 > a_max);
         vswap(a3, a_max, a3 > a_max);
         vswap(a4, a_max, a4 > a_max);
         vswap(a5, a_max, a5 > a_max);
         
         //save max of common pixels
         b_max = a_max;
         
         vswap(a6, a_max, a6 > a_max);
         vswap(a7, a_max, a7 > a_max);
         vswap(a8, a_max, a8 > a_max);
         
         vswap(b6, b_max, b6 > b_max);
         vswap(b7, b_max, b7 > b_max);
         vswap(b8, b_max, b8 > b_max);
         
         
        
         // Assign to output
         dst[x]      = (uint8_t)a_max;
         dst[x + 1]  = (uint8_t)b_max;
      }
      
      // Proceed to next block
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;
   }
}

void dilate_3x3_16s_ref( int16_t* dst, int dstr,
                   const int16_t* src, int sstr,
                               int bw, int bh )
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const int16_t* s0 = src - sstr;
   const int16_t* s1 = src;
   const int16_t* s2 = src + sstr;

   // Loop
   int16_t a_max, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   int16_t b_max, b6, b7, b8;

   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; x+=2)
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];

         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];

         // Compare and find max
         a_max = a0;

         vswap(a1, a_max, a1 > a_max);
         vswap(a2, a_max, a2 > a_max);
         vswap(a3, a_max, a3 > a_max);
         vswap(a4, a_max, a4 > a_max);
         vswap(a5, a_max, a5 > a_max);

         //save max of common pixels
         b_max = a_max;

         vswap(a6, a_max, a6 > a_max);
         vswap(a7, a_max, a7 > a_max);
         vswap(a8, a_max, a8 > a_max);

         vswap(b6, b_max, b6 > b_max);
         vswap(b7, b_max, b7 > b_max);
         vswap(b8, b_max, b8 > b_max);

         // Assign to output
         dst[x]      = (int16_t)a_max;
         dst[x + 1]  = (int16_t)b_max;
      }

      // Proceed to next block
      s0   = s1;
      s1   = s2;
      s2  += sstr;
      dst += dstr;
   }
}

void erode_3x3_08u_ref( uint8_t* dst, int dstr, 
                  const uint8_t* src, int sstr,
                              int bw, int bh )
{
   // Structuring element: Rectangular - hardcoded
      //  1,  1,  1,
      //  1,  1,  1,
      //  1,  1,  1,

   // Neighbors:
   const uint8_t* s0 = src - sstr;
   const uint8_t* s1 = src;
   const uint8_t* s2 = src + sstr;
   
   // Loop
   int16_t a_min, a0, a1, a2, a3, a4, a5, a6, a7, a8;
   int16_t b_min, b6, b7, b8;
   
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; x+=2)
      {
         // Copy src cells
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         a6 = s0[x - 1];
         a7 = s1[x - 1];
         a8 = s2[x - 1];
         
         b6 = s0[x + 2];
         b7 = s1[x + 2];
         b8 = s2[x + 2];
            
         // Compare and find min
         a_min = a0;

         vswap(a1, a_min, a1 < a_min);
         vswap(a2, a_min, a2 < a_min);
         vswap(a3, a_min, a3 < a_min);
         vswap(a4, a_min, a4 < a_min);
         vswap(a5, a_min, a5 < a_min);
         
         //save min of common pixels
         b_min = a_min;
         
         vswap(a6, a_min, a6 < a_min);
         vswap(a7, a_min, a7 < a_min);
         vswap(a8, a_min, a8 < a_min);
         
         vswap(b6, b_min, b6 < b_min);
         vswap(b7, b_min, b7 < b_min);
         vswap(b8, b_min, b8 < b_min);
        
         // Assign to output
         dst[x]      = (uint8_t)a_min;
         dst[x + 1]  = (uint8_t)b_min;
      }
      
      // Proceed to next block
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;
   }
}

void
bilateral_5x5_init(uint32_t *r_lut, uint32_t *d_lut, int sigmaR, int sigmaD)
{
   float inv_sigmaR = -0.5f / (sigmaR * sigmaR);
   float inv_sigmaD = -0.5f / (sigmaD * sigmaD);
   float y;
   
   for (int i = 0; i < 256; ++i)
   {
      y = expf((i * i) * inv_sigmaR);
      r_lut[i] = (uint32_t)(y * 255 + 0.5f);
   }
   
   for (int j = 0; j < 9; ++j)
   {
      y = expf(j * inv_sigmaD);
      d_lut[j] = (uint32_t)(y * 255 + 0.5f);
   }
}

void             
bilateral_5x5_ref(  uint8_t* dst, int dstr,
              const uint8_t* src, int sstr,
                          int bw, int bh,
                      int sigmaR, int sigmaD )
{  
   uint32_t weight;          //FP  0_16
   uint32_t sum_wi;          //FP 13_16
   uint32_t sum_weight;      //FP  5_16
   uint32_t r_lut[256];
   uint32_t d_lut[9];
   
   bilateral_5x5_init(r_lut, d_lut, sigmaR, sigmaD);
   
   
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; ++x) 
      {
         uint32_t center_i = src[y * sstr + x];
         sum_weight = 0;
         sum_wi = 0;
         
         for (int fy = -2; fy < 3; ++fy)
         {
            for (int fx = -2; fx < 3; ++fx)
            { 
               uint32_t filter_i = src[(y + fy) * sstr + (x + fx)];
               uint32_t vidx = max(center_i, filter_i) - min(center_i, filter_i);
               
               weight = r_lut[vidx] * d_lut[fx*fx+fy*fy];
               sum_weight += weight;
               sum_wi += filter_i * weight;
            }
         }
         //TODO: temporary divide
         dst[y*dstr+x] = (uint8_t)(((sum_wi / (sum_weight >> 1)) + 1) >> 1);
      }
   }
}

void             
box_3x3_ref( uint8_t* dst, int dstr,
       const uint8_t* src, int sstr,
                   int bw, int bh )
{  
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; ++x) 
      {
         uint32_t sum = 0;
         
         for (int fy = -1; fy < 2; ++fy)
         {
            for (int fx = -1; fx < 2; ++fx)
            { 
               sum += src[(y + fy) * sstr + (x + fx)];
            }
         }
         dst[y*dstr+x] = (uint8_t)round((double)sum / 9.0);
      }
   }
}

void             
box_3x3_nr_ref( uint8_t* dst, int dstr,
       const uint8_t* src, int sstr,
                   int bw, int bh )
{  
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; ++x) 
      {
         uint32_t sum = 0;
         
         for (int fy = -1; fy < 2; ++fy)
         {
            for (int fx = -1; fx < 2; ++fx)
            { 
               sum += src[(y + fy) * sstr + (x + fx)];
            }
         }
         dst[y*dstr+x] = (uint8_t)(sum / 9);
      }
   }
}

void             
box_3x3_ref( int16_t* dst, int dstr,
       const int16_t* src, int sstr,
                   int bw, int bh )
{  
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; ++x) 
      {
         uint32_t sum = 0;
         
         for (int fy = -1; fy < 2; ++fy)
         {
            for (int fx = -1; fx < 2; ++fx)
            { 
               sum += (short)(src[(y + fy) * sstr + (x + fx)]);
            }
         }
         dst[y*dstr+x] = (int16_t)sum;
      }
   }
}

void
box_5x5_ref( int16_t* dst, int dstr,
       const int16_t* src, int sstr,
                   int bw, int bh )
{  
   for (int y = 0; y < bh; ++y)
   {
      for (int x = 0; x < bw; ++x) 
      {
         int32_t sum = 0;
         
         for (int fy = -2; fy < 3; ++fy)
         {
            for (int fx = -2; fx < 3; ++fx)
            { 
               sum += src[(y + fy) * sstr + (x + fx)];
            }
         }
         dst[y*dstr+x] = (int16_t)sum;
      }
   }
}

void
derivative_x_3x3_16s_ref(  int16_t* dst, int dstr,
                     const uint8_t* src, int sstr,
                                 int bw, int bh,
                           int k0, int k1, int k2
)
{
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         dst[j] = -k0*src[-sstr+j-1] + k0*src[-sstr+j+1]
                  -k1*src[      j-1] + k1*src[      j+1]
                  -k2*src[+sstr+j-1] + k2*src[+sstr+j+1];
      }
      dst += dstr;
      src += sstr;
   }
}

void
derivative_y_3x3_16s_ref(  int16_t* dst, int dstr,
                     const uint8_t* src, int sstr,
                                 int bw, int bh,
                           int k0, int k1, int k2
)
{
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         dst[j] = -k0*src[-sstr+j-1] - k1*src[-sstr+j] - k2*src[-sstr+j+1]
                  +k0*src[+sstr+j-1] + k1*src[+sstr+j] + k2*src[+sstr+j+1];
      }
      dst += dstr;
      src += sstr;
   }
}

#define swap(a, b) vswap(a, b, a > b);
#define min3(a, b, c) swap(a, b); swap(a, c);
#define max3(a, b, c) swap(a, c); swap(b, c);
#define min4(a, b, c, d) swap(a, b); swap(c, d); swap(a, c);
#define max4(a, b, c, d) swap(a, b); swap(c, d); swap(b, d);
#define min5(a, b, c, d, e) swap(a, b); swap(c, d); min3(a, c, e);
#define max5(a, b, c, d, e) swap(a, b); swap(c, d); max3(b, d, e);
#define min6(a, b, c, d, e, f) swap(a, b); swap(c, d); swap(e, f); min3(a, c, e);
#define max6(a, b, c, d, e, f) swap(a, b); swap(c, d); swap(e, f); max3(b, d, f);
#define minmax3(a, b, c) min3(a, b, c); swap(b, c);
#define minmax4(a, b, c, d) swap(a, b); swap(c, d); swap(a, c); swap(b, d);
#define minmax5(a, b, c, d, e) swap(a, b); swap(c, d); min3(a, c, e); max3(b, d, e);

#define minmax6(a, b, c, d, e, f) \
swap(a, b); swap(c, d); swap(e, f); min3(a, c, e); max3(b, d, f);

#define minmax7(a, b, c, d, e, f, g) \
swap(a, b); swap(c, d); swap(e, f); min4(a, c, e, g); max4(b, d, f, g);

#define minmax8(a, b, c, d, e, f, g, h) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); min4(a, c, e, g); max4(b, d, f, h);

#define minmax9(a, b, c, d, e, f, g, h, i) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); min5(a, c, e, g, i); max5(b, d, f, h, i);

#define minmax10(a, b, c, d, e, f, g, h, i, j) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); min5(a, c, e, g, i); \
max5(b, d, f, h, j);

#define minmax11(a, b, c, d, e, f, g, h, i, j, k) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); min6(a, c, e, g, i, k); \
max6(b, d, f, h, j, k);

#define minmax12(a, b, c, d, e, f, g, h, i, j, k, l) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); \
min6(a, c, e, g, i, k); max6(b, d, f, h, j, l);

#define minmax13(a, b, c, d, e, f, g, h, i, j, k, l, m) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); min3(a, c, e); \
min3(g, i, k); min3(a, g, m); max3(b, d, f); max3(h, j, l); max3(f, l, m);

#define minmax14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) \
swap(a, b); swap(c, d); swap(e, f); swap(g, h); swap(i, j); swap(k, l); swap(m, n); \
min3(a, c, e); min3(g, i, k); min3(a, g, m); max3(b, d, f); max3(h, j, l); max3(f, l, n);

void
median_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
                 int bw, int bh)
{
   const uint8_t* s0 = src - sstr;
   const uint8_t* s1 = src;
   const uint8_t* s2 = src + sstr;
   
   int16_t a0, a1, a2, a3, a4, a5;
   int16_t b1, b2, b3, b4, b5;
   
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; x+=2)
      {
         a0 = s0[x];
         a1 = s0[x + 1];
         a2 = s1[x];
         a3 = s1[x + 1];
         a4 = s2[x];
         a5 = s2[x + 1];
         
         minmax6(a0, a1, a2, a3, a4, a5);
         
         b1 = a1; b2 = a2; b3 = a3; b4 = a4;
         
         a5 = s0[x - 1];
         b5 = s0[x + 2];
         minmax5(a1, a2, a3, a4, a5);
         minmax5(b1, b2, b3, b4, b5);
         a5 = s1[x - 1];
         b5 = s1[x + 2];
         minmax4(a2, a3, a4, a5);
         minmax4(b2, b3, b4, b5);
         a5 = s2[x - 1];
         b5 = s2[x + 2];
         minmax3(a3, a4, a5);
         minmax3(b3, b4, b5);
         
         dst[x] = (uint8_t)a4;
         dst[x + 1] = (uint8_t)b4;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;      
   }
}

void
median_5x5_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
                 int bw, int bh)
{  
   const uint8_t* s0 = src - sstr - sstr;
   const uint8_t* s1 = src - sstr;
   const uint8_t* s2 = src;
   const uint8_t* s3 = src + sstr;
   const uint8_t* s4 = src + sstr + sstr;
   
   int16_t a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13;
   int16_t b7, b8, b9, b10, b11, b12, b13;
   
   for (int y=0; y<bh; ++y)
   {
      for(int x=0; x<bw; x+=2)
      {
          a0 = s0[x - 1];
          a1 = s0[x];
          a2 = s0[x + 1];
          a3 = s0[x + 2];
          a4 = s1[x - 1];
          a5 = s1[x];
          a6 = s1[x + 1];
          a7 = s1[x + 2];
          a8 = s2[x - 1];
          a9 = s2[x];
          a10 = s2[x + 1];
          a11 = s2[x + 2];
          a12 = s3[x - 1];
          a13 = s3[x];
          
          minmax14(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s3[x + 1];
          minmax13(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s3[x + 2];
          minmax12(a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x - 1];
          minmax11(a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x];
          minmax10(a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x + 1];
          minmax9(a5, a6, a7, a8, a9, a10, a11, a12, a13);
          a13 = s4[x + 2];
          minmax8(a6, a7, a8, a9, a10, a11, a12, a13);
          
          b7 = a7; b8 = a8; b9 = a9; b10 = a10; b11 = a11; b12 = a12;
          
          a13 = s0[x - 2];
          b13 = s0[x + 3];
          minmax7(a7, a8, a9, a10, a11, a12, a13);
          minmax7(b7, b8, b9, b10, b11, b12, b13);
          a13 = s1[x - 2];
          b13 = s1[x + 3];
          minmax6(a8, a9, a10, a11, a12, a13);
          minmax6(b8, b9, b10, b11, b12, b13);
          a13 = s2[x - 2];
          b13 = s2[x + 3];
          minmax5(a9, a10, a11, a12, a13);
          minmax5(b9, b10, b11, b12, b13);
          a13 = s3[x - 2];
          b13 = s3[x + 3];
          minmax4(a10, a11, a12, a13);
          minmax4(b10, b11, b12, b13)
          a13 = s4[x - 2];
          b13 = s4[x + 3];
          minmax3(a11, a12, a13);
          minmax3(b11, b12, b13);
          
          dst[x] = (uint8_t)a12;
          dst[x + 1] = (uint8_t)b12;
      }
      
      s0   = s1;
      s1   = s2; 
      s2   = s3;
      s3   = s4;
      s4  += sstr;
      dst += dstr;      
   }
}

// Local helper functions
static inline uint16_t apu_filter_gaussian_3x3(const uint8_t* src, int sstr);
static inline uint16_t apu_filter_gaussian_5x5(const uint8_t* src, int sstr);

void
gaussian_3x3_08u_ref (uint8_t* dst, int dstr,
            const uint8_t* src, int sstr,
                 int bw, int bh)
{
   for (int y=0; y<bh; ++y) 
   {
      for (int x=0; x<bw; ++x) 
      {
         uint16_t tx = apu_filter_gaussian_3x3(&src[x], sstr);
        
         dst[x] = (uint8_t)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
gaussian_5x5_08u_ref (uint8_t* dst, int dstr,
            const uint8_t* src, int sstr,
                 int bw, int bh)
{
   for (int y=0; y<bh; ++y) 
   {
      for (int x=0; x<bw; ++x) 
      {
         uint16_t tx = apu_filter_gaussian_5x5(&src[x], sstr);
        
         dst[x] = (uint8_t)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

// LOCAL HELPER FUNCTION
//  1,  2,  1,
//  2,  4,  2,  * 1/16
//  1,  2,  1,
static
inline
uint16_t
apu_filter_gaussian_3x3(const uint8_t* src, int sstr)
{
   uint16_t t1 = +   src[-sstr-1] + 2*src[-sstr  ] +   src[-sstr+1]
                 + 2*src[     -1] + 4*src[      0] + 2*src[     +1]
                 +   src[+sstr-1] + 2*src[+sstr  ] +   src[+sstr+1]; 
               
   uint16_t vd = t1>>4;
               
   return vd;
}

// LOCAL HELPER FUNCTION
//  1,   4,   6,  4,  1,
//  4,  16,  24, 16,  4, 
//  6,  24,  36, 24,  6, * 1/256
//  4,  16,  24, 16,  4,
//  1,   4,   6,  4,  1,
static
inline
uint16_t
apu_filter_gaussian_5x5(const uint8_t* src, int sstr)
{
   uint16_t t1 = +   src[-2*sstr - 2] +  4*src[-2*sstr - 1] +  6*src[-2*sstr] +  4*src[-2*sstr + 1] +   src[-2*sstr + 2]
                 + 4*src[-  sstr - 2] + 16*src[-  sstr - 1] + 24*src[-  sstr] + 16*src[-  sstr + 1] + 4*src[-  sstr + 2]
                 + 6*src[        - 2] + 24*src[        - 1] + 36*src[      0] + 24*src[        + 1] + 6*src[        + 2]
                 + 4*src[+  sstr - 2] + 16*src[+  sstr - 1] + 24*src[+  sstr] + 16*src[+  sstr + 1] + 4*src[+  sstr + 2]
                 +   src[+2*sstr - 2] +  4*src[+2*sstr - 1] +  6*src[+2*sstr] +  4*src[+2*sstr + 1] +   src[+2*sstr + 2];
               
   uint16_t vd = t1>>8;

   return vd;
}

void
separable_3x3_16s_ref(  int16_t* dst, int dstr,
                  const uint8_t* src, int sstr,
                              int bw, int bh,
             const signed char* fRow,
             const signed char* fCol
)
{
   int16_t c1, c2, c3;
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         c1 = fCol[0]*src[-sstr+j-1] + fCol[1]*src[j-1] + fCol[2]*src[sstr+j-1];
         c2 = fCol[0]*src[-sstr+j  ] + fCol[1]*src[j  ] + fCol[2]*src[sstr+j  ];
         c3 = fCol[0]*src[-sstr+j+1] + fCol[1]*src[j+1] + fCol[2]*src[sstr+j+1];
         dst[j] = fRow[0]*c1 + fRow[1]*c2 + fRow[2]*c3;
      }
      src += sstr;
      dst += dstr;
   }
}

void
separable_5x5_16s_ref(  int16_t* dst, int dstr,
                  const uint8_t* src, int sstr,
                              int bw, int bh,
             const signed char* fRow,
             const signed char* fCol
)
{
   int16_t c1, c2, c3, c4, c5;
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         c1 = fCol[0]*src[-2*sstr+j-2] + fCol[1]*src[-sstr+j-2] + fCol[2]*src[j-2] + fCol[3]*src[sstr+j-2] + fCol[4]*src[2*sstr+j-2];
         c2 = fCol[0]*src[-2*sstr+j-1] + fCol[1]*src[-sstr+j-1] + fCol[2]*src[j-1] + fCol[3]*src[sstr+j-1] + fCol[4]*src[2*sstr+j-1];
         c3 = fCol[0]*src[-2*sstr+j  ] + fCol[1]*src[-sstr+j  ] + fCol[2]*src[j  ] + fCol[3]*src[sstr+j  ] + fCol[4]*src[2*sstr+j  ];
         c4 = fCol[0]*src[-2*sstr+j+1] + fCol[1]*src[-sstr+j+1] + fCol[2]*src[j+1] + fCol[3]*src[sstr+j+1] + fCol[4]*src[2*sstr+j+1];
         c5 = fCol[0]*src[-2*sstr+j+2] + fCol[1]*src[-sstr+j+2] + fCol[2]*src[j+2] + fCol[3]*src[sstr+j+2] + fCol[4]*src[2*sstr+j+2];
         dst[j] = fRow[0]*c1 + fRow[1]*c2 + fRow[2]*c3 + fRow[3]*c4 + fRow[4]*c5;
      }
      src += sstr;
      dst += dstr;
   }
}

// Local helper functions
static inline int16_t apu_filter_sobel_3x3_x(const uint8_t* src, int sstr);
static inline int16_t apu_filter_sobel_3x3_y(const uint8_t* src, int sstr);
static inline int16_t apu_filter_sobel_5x5_x(const uint8_t* src, int sstr);
static inline int16_t apu_filter_sobel_5x5_y(const uint8_t* src, int sstr);

void
sobel_x_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t tx = apu_filter_sobel_3x3_x(&src[x], sstr);

         // Absolute Value & Saturation
         if(tx > 255) {
            tx = 255;
         } else if (tx < 0) {
            tx = 0;
         }
        
         dst[x] = (uint8_t)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_x_3x3_08s_ref(
             int8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t tx = apu_filter_sobel_3x3_x(&src[x], sstr);
         
         tx = (tx + 4) >> 3;
         
         // Absolute Value & Saturation
         if(tx > 127) {
            tx = 127;
         } else if (tx < -128) {
            tx = -128;
         }
        
         dst[x] = (int8_t)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_y_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t ty = apu_filter_sobel_3x3_y(&src[x], sstr);
         
         // Absolute Value & Saturation
         if(ty > 255) {
            ty = 255;
         } else if (ty < 0) {
            ty = 0;
         }
         
         dst[x] = (uint8_t)ty;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_y_3x3_08s_ref(
             int8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t ty = apu_filter_sobel_3x3_y(&src[x], sstr);
         
         ty = (ty + 4) >> 3;

         // Absolute Value & Saturation
         if(ty > 127) {
            ty = 127;
         } else if (ty < -128) {
            ty = -128;
         }
         
         dst[x] = (int8_t)ty;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_x_5x5_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t tx = apu_filter_sobel_5x5_x(&src[x], sstr);
         
         // Absolute Value & Saturation
        if(tx > 255) {
               tx = 255;
            } else if (tx < 0) {
               tx = 0;
            }
         
         dst[x] = (uint8_t)tx;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_y_5x5_08u_ref(            
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)  
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t ty = apu_filter_sobel_5x5_y(&src[x], sstr);

        // Absolute Value & Saturation
        if(ty > 255) {
               ty = 255;
            } else if (ty < 0) {
               ty = 0;
            }
      
         dst[x] = (uint8_t)ty;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_3x3_08u_ref(
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x) 
      {
         int16_t tx = apu_filter_sobel_3x3_x(&src[x], sstr);
         if (tx<0)     { tx = -tx; }

         int16_t ty = apu_filter_sobel_3x3_y(&src[x], sstr);
         if (ty<0)     { ty = -ty; }

   
         int16_t t = tx+ty;
         if (t > 255)  { t  = 255;   }
   
         dst[x] = (uint8_t)t;
      }
      
      src += sstr;
      dst += dstr;
   }
}

void
sobel_3x3_16s_ref(
            int16_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y)
   {
      for (int x=0; x<bw; ++x) 
      {
         int16_t tx = apu_filter_sobel_3x3_x(&src[x], sstr);
         int16_t ty = apu_filter_sobel_3x3_y(&src[x], sstr);
   
         uint16_t t = abs(tx)+abs(ty);
         if (t > 255) t = 255;
   
         dst[x] = (uint8_t)t;
      }
      
      src += sstr;
      dst += dstr;
   }
}


void
sobel_5x5_08u_ref(            
            uint8_t* dst, int dstr,
      const uint8_t* src, int sstr,
      int bw, int bh)
{
   for (int y=0; y<bh; ++y) 
   {
      for (int x=0; x<bw; ++x)
      {
         int16_t tx = apu_filter_sobel_5x5_x(&src[x], sstr);
         if (tx<0)     { tx = -tx; }
         
         int16_t ty = apu_filter_sobel_5x5_y(&src[x], sstr);
         if (ty<0)     { ty = -ty; }
         
         int16_t t = tx+ty;
         if (t > 255)  { t  = 255; }
   
         dst[x] = (uint8_t)t;
      }
      
      src += sstr;
      dst += dstr;
   }
}

// LOCAL HELPER FUNCTIONS

//  -1,  0,  1,
//  -2,  0,  2,
//  -1,  0,  1,
static
inline
int16_t
apu_filter_sobel_3x3_x(const uint8_t* src, int sstr)
{
   int16_t vd = +   src[-sstr+1] -   src[-sstr-1]
               + 2*src[     +1] - 2*src[     -1]
               +   src[+sstr+1] -   src[+sstr-1]; 
               
               
   return vd;
}

// -1, -2, -1,
//  0,  0,  0,
// +1, +2, +1,
static
inline
int16_t
apu_filter_sobel_3x3_y(const uint8_t* src, int sstr)
{
   int16_t t7 = + src[+sstr+1] - src[-sstr-1];
   int16_t t9 = + src[+sstr-1] - src[-sstr+1];
   int16_t t8 = + src[+sstr  ] - src[-sstr  ];
   int16_t vd = t7 + 2*t8 + t9;
   
   return vd;
}


/*
    -1,  -2,  0,  +2,  +1,
    -4,  -8,  0,  +8,  +4,
    -6, -12,  0, +12,  +6,
    -4,  -8,  0,  +8,  +4,
    -1,  -2,  0,  +2,  +1, 
 */    
static
inline
int16_t
apu_filter_sobel_5x5_x(const uint8_t* src, int sstr)
{
   const int16_t t22  = - src[-2*sstr-2] + src[-2*sstr+2] - src[+2*sstr-2] + src[+2*sstr+2];
   const int16_t t12  = - src[-2*sstr-1] + src[-2*sstr+1] - src[+2*sstr-1] + src[+2*sstr+1];
   const int16_t t21  = - src[-1*sstr-2] + src[-1*sstr+2] - src[+1*sstr-2] + src[+1*sstr+2];
   const int16_t t11  = - src[-1*sstr-1] + src[-1*sstr+1] - src[+1*sstr-1] + src[+1*sstr+1];
   const int16_t t20  = - src[       -2] + src[       +2];
   const int16_t t10  = - src[       -1] + src[       +1];

   const int16_t tx   = t22 + 2*t12 + 4*t21 + 8*t11 + 6*t20 + 12*t10;
   
   return tx;
}

/*
    -1,  -4,  -6,  -4,  -1,
    -2,  -8, -12,  -8,  -2,
     0,   0,   0,   0,   0,
    +2,  +8, +12,  +8,  +2,
    +1,  +4,  +6,  +4,  +1,
*/
static
inline
int16_t
apu_filter_sobel_5x5_y(const uint8_t* src, int sstr)
{
   const int16_t t22  = - src[-2*sstr-2] - src[-2*sstr+2] + src[+2*sstr-2] + src[+2*sstr+2];
   const int16_t t12  = - src[-2*sstr-1] - src[-2*sstr+1] + src[+2*sstr-1] + src[+2*sstr+1];
   const int16_t t21  = - src[-1*sstr-2] - src[-1*sstr+2] + src[+1*sstr-2] + src[+1*sstr+2];
   const int16_t t11  = - src[-1*sstr-1] - src[-1*sstr+1] + src[+1*sstr-1] + src[+1*sstr+1];
   const int16_t t02  = - src[-2*sstr  ] + src[+2*sstr  ];
   const int16_t t01  = - src[-1*sstr  ] + src[+1*sstr  ];

   const int16_t tx   = t22 + 4*t12 + 2*t21 + 8*t11 + 6*t02 + 12*t01;
   
   return tx;
}

void  
convolve_08u_ref(
         uint8_t* dst, int dstr,        
   const uint8_t* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh)
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx)
      {
         int16_t r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy)
         {
            for (int fx=0; fx<fw; ++fx, ++fk)
            {
               r += ((int16_t)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         
         // Saturation
             if(r > 255) {
                r = 255;
             } else if(r < 0) {
               r = 0;
             }
         
         dst[by*dstr + bx] = (uint8_t)r;
      }
   }
}   

void  
convolve_scale_08u_ref(
         uint8_t* dst, int dstr,        
   const uint8_t* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh,  
   int fscl)                     
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   const int fone = (1 << fscl);
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx) 
      {
         int16_t r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy)
         {
            for (int fx=0; fx<fw; ++fx, ++fk)
            {
               r += ((int16_t)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         // Rounding & Scaling
         r  += (fone >> 1);
         r >>= fscl;
         
         // Saturation
         if(r > 255) {
            r = 255;
         } else if(r < 0) {
            r = 0;
         }
         
         dst[by*dstr + bx] = (uint8_t)r;
      }
   }
}   

void  
convolve_scale_08u_nr_ref(
         uint8_t* dst, int dstr,        
   const uint8_t* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh,  
   int fscl)                     
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx) 
      {
         int16_t r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy)
         {
            for (int fx=0; fx<fw; ++fx, ++fk)
            {
               r += ((int16_t)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         // Rounding & Scaling
         r >>= fscl;
         
         // Saturation
         if(r > 255) {
            r = 255;
         } else if(r < 0) {
            r = 0;
         }
         
         dst[by*dstr + bx] = (uint8_t)r;
      }
   }
}   

void  
convolve_16s_ref(
         int16_t* dst, int dstr,        
   const uint8_t* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh)
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx) 
      {
         int32_t r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy)
         {
            for (int fx=0; fx<fw; ++fx, ++fk)
            {
               r += ((int16_t)flt[fk] * (int16_t)src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         
         // Saturation
         if(r > 32767) {
            r = 32767;
         } else if(r < -32768) {
           r = -32768;
         }
         
         dst[by*dstr + bx] = (int16_t)r;
      }
   }
}   

void  
convolve_scale_16s_ref(
         int16_t* dst, int dstr,        
   const uint8_t* src, int sstr,        
   int bw, int bh,                     
   const int8_t* flt, int fw, int fh,  
   int fscl)                     
{
   // Adjust src
   src -= ((fh >> 1)*sstr + (fw >> 1));
   
   const int fone = (1 << fscl);
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx)
      {
         int32_t r = 0;
         for (int fy=0, fk=0; fy<fh; ++fy)
         {
            for (int fx=0; fx<fw; ++fx, ++fk)
            {
               r += ((int16_t)flt[fk] * src[(by+fy)*sstr + (bx+fx)]);
            }
         }
         // Rounding & Scaling
         r  += (fone >> 1);
         r >>= fscl;
         
         // Saturation
         if(r > 32767) {
            r = 32767;
         } else if(r < -32768) {
           r = -32768;
         };
         
         dst[by*dstr + bx] = (int16_t)r;
      }
   }
}

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
              int bw, int bh )                     
{
   const uint8_t* s0 = src - sstr;
   const uint8_t* s1 = src;
   const uint8_t* s2 = src + sstr;
   
   for (int by=0; by<bh; ++by)
   {
      for (int bx=0; bx<bw; ++bx)
      {
         int16_t r;
         r  = s0[bx + 1] - s0[bx - 1];
         r += s1[bx + 1] - s1[bx - 1];
         r += s2[bx + 1] - s2[bx - 1];

         dst[bx] = r;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;  
   }
}

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
              int bw, int bh )                     
{
   const uint8_t* s0 = src - sstr;
   const uint8_t* s1 = src;
   const uint8_t* s2 = src + sstr;
   
   for (int by=0; by<bh; ++by) 
   {
      for (int bx=0; bx<bw; ++bx)
      {
         int16_t r;
         r  =  s0[bx - 1] + s0[bx] + s0[bx + 1];
         r -= (s2[bx - 1] + s2[bx] + s2[bx + 1]);

         dst[bx] = r;
      }
      
      s0   = s1;
      s1   = s2; 
      s2  += sstr;
      dst += dstr;  
   }
}

void
saturate_08s_ref(
            int8_t* dst, int dstr,
      const int16_t* src, int sstr,
            int bw, int bh
)
{
   for (int i = 0; i < bh; ++i) {
      for (int j = 0; j < bw; ++j) {
         int16_t val = (src[j]+4)>>3;
         if (val < -128) {
            val = -128;
         } else if (val > 127) {
            val = 127;
         }
         
         dst[j] = (int8_t)val;
      }
      src += sstr;
      dst += dstr;
   }
}
