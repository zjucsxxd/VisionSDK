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

#include <apexcv_interpolation_ref.h>
#include <apexcv_bicubicLUT.h>

void
interp_linear_grayscale_ref(
               uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
               int bw, int bh,
         const uint8_t* delta)
{
   uint8_t s11, s12; // 8-bit source values
   uint8_t deltaX;  //  8-bit x delta value

   int offset_idx = 0;     // 1-d offset for offset/delta lookup
   int dest_row = 0;
   int src_row = 0;
   int src_col = 0;

   // loop on destination pixels
   for (int y = 0; y < bh; ++y) {
      for (int x = 0; x < bw; ++x) {
         s11 = src[src_col];
         s12 = src[src_col+1];
         
         deltaX = delta[offset_idx];

         // Assumes only X delta available
         dst[dest_row + x] = ((((s12 - s11) * deltaX) + 0x80) >> 8) + s11;
         offset_idx++;
         src_col++;
      }
      src_row += sstr;
      src_col = src_row;
      dest_row += dstr;
   } // next row
}

void
interp_bilinear_grayscale_ref(
               uint8_t* dst, int dstr,
         const uint8_t* src, int sstr,
               int bw, int bh, 
         const uint8_t* delta)
{
   uint8_t s11, s12, s21, s22; // 8-bit source values
   uint8_t deltaX, deltaY;  //  8-bit delta values
   uint8_t r1, r2;      // Intermediate results

   int offset_idx = 0;     // 1-d offset for offset/delta lookup
   int dest_row = 0;
   int src_row = 0;
   int src_col = 0;

   // loop on destination pixels
   for (int y = 0; y < bh; ++y) {
      for (int x = 0; x < bw; ++x) {
         s11 = src[src_col];
         s12 = src[src_col+1];
         s21 = src[src_col+sstr];
         s22 = src[src_col+sstr+1];

         deltaX = delta[(offset_idx<<1)];
         deltaY = delta[(offset_idx<<1)+1];

         r1 = ((((s12 - s11) * deltaX) + 0x80) >> 8) + s11;
         r2 = ((((s22 - s21) * deltaX) + 0x80) >> 8) + s21;

         dst[dest_row + x] = ((((r2 - r1) * deltaY) + 0x80) >> 8) + r1;
         offset_idx++;
         src_col++;
      }
      src_row += sstr;
      src_col = src_row;
      dest_row += dstr;
   } // next row
}

uint8_t cubicInterpolate(const uint8_t t, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, int16_t lut[4]){
   int16_t tmp = ((int16_t)a0*lut[0] + (int16_t)a1*lut[1] + (int16_t)a2*lut[2] + (int16_t)a3*lut[3] + 128)>>8;
   return (uint8_t)tmp;
}

uint8_t RefXYInterpolation(const uint8_t p[4][4], const uint8_t x_offset, uint8_t y_offset, int16_t xlut[4], int16_t ylut[4]){
   uint8_t arr[4];
   arr[0] = cubicInterpolate(x_offset, p[0][0], p[1][0], p[2][0], p[3][0], xlut);
   arr[1] = cubicInterpolate(x_offset, p[0][1], p[1][1], p[2][1], p[3][1], xlut);
   arr[2] = cubicInterpolate(x_offset, p[0][2], p[1][2], p[2][2], p[3][2], xlut);
   arr[3] = cubicInterpolate(x_offset, p[0][3], p[1][3], p[2][3], p[3][3], xlut);
   return cubicInterpolate(y_offset, arr[0], arr[1], arr[2], arr[3], ylut);
}

void accessLUT(const uint8_t x_offset, const uint8_t y_offset, int16_t xlut[4], int16_t ylut[4]){
	xlut[0] = BicubicLUT[0][x_offset];
	xlut[1] = BicubicLUT[1][x_offset];
	xlut[2] = BicubicLUT[2][x_offset];
	xlut[3] = BicubicLUT[3][x_offset];

	ylut[0] = BicubicLUT[0][y_offset];
	ylut[1] = BicubicLUT[1][y_offset];
	ylut[2] = BicubicLUT[2][y_offset];
	ylut[3] = BicubicLUT[3][y_offset];
}

void interp_bicubic_grayscale_ref(uint8_t* dst, int dstr, const uint8_t* src, int sstr, int bw, int bh, const uint8_t x_offset, const uint8_t y_offset){
  int16_t xlut[4];
  int16_t ylut[4];
  accessLUT(x_offset, y_offset, xlut, ylut);
  uint8_t arr[4][4];

  for(int i = 0; i<bh; i++){
    for(int j = 0; j <bw; j++){
      for(int a = -1; a < 3; a++){
         for(int b = -1; b < 3; b++){
            arr[b+1][a+1] = src[j+b + (i+a)*sstr];
         }
      }
      dst[j + (i)*dstr] = uint8_t(RefXYInterpolation(arr, x_offset, y_offset, xlut, ylut));
    }
  }
}
