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
*  \file apexcv_arithmetic_ref.cpp
*  \brief Reference code for arithmetic kernels
***********************************************************************************/
#include <cmath>

#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <limits>

//TODO: this reference code badly needs to be refactored

using namespace std;

template <typename S, typename D>
void abs_ref( const S* src, int sstr, 
					D* dst,  int dstr, 
			  int blockWidth, int blockHeight )
{
   long mx = numeric_limits<D>::max();
   
   for(int y = 0; y < blockHeight; ++y) {
      for(int x = 0; x < blockWidth; ++x) {
         long abs_val = abs((long)src[x]);
         
         if(abs_val > mx) {
            dst[x] = mx;
         } else {
            dst[x] = abs_val;
         }
      }
      
      dst += dstr;
      src += sstr;
   }
}

template <typename D>
void absdiff_ref( const D* src0, int sstr0, 
                  const D* src1, int sstr1,
                  D* dst,  int dstr, 
                  int blockWidth, int blockHeight )
{
   long mx = numeric_limits<D>::max();
   
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
         long absdiff = abs((long)max(src0[x], src1[x]) - (long)min(src0[x], src1[x]));
         
         if(absdiff > mx) {
            dst[x] = mx;
         } else {
            dst[x] = absdiff;
         }
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}

template <typename S, typename D>
void accumulate_ref(const S* src1,  int sstr1,
                    const S* src2,  int sstr2,
                    D* dst,  int dstr,
                    int bw, int bh) 
{
   for ( int by = 0; by < bh; by++ ) {
      for ( int bx = 0; bx < bw; ++bx ) {
         dst[bx] = src1[bx] + src2[bx];
      }
   
      src1 += sstr1;
      src2 += sstr2;
      dst  += dstr;
   }
}

template <typename S, typename D>
void accumulate_squared_ref(const S* src1,  int sstr1,
                            const S* src2,  int sstr2,
                            D* dst,  int dstr,
                            int bw, int bh, unsigned char scale) 
{
   uint16_t s1i;
   uint16_t s2i;
   uint16_t tx;
   
   for ( int by = 0; by < bh; by++ ) {
      for ( int bx = 0; bx < bw; ++bx ) {
         s1i = (uint16_t)src1[bx];
         s2i = (uint16_t)src2[bx];
         tx = (uint16_t)(s1i + ((s2i*s2i) >> scale));
		 
         if (tx > 32767) { tx = 32767; }
		 
		 dst[bx] = (int16_t)tx;
      }
   
      src1 += sstr1;
      src2 += sstr2;
      dst  += dstr;
   }
}

template <typename D>
void accumulate_weighted_ref(const D* src1,  int sstr1,
                             const D* src2,  int sstr2,
                                    D* dst,  int dstr,
                             int bw, int bh, unsigned char alpha) 
{   
   uint32_t s1i;
   uint32_t s2i;
   
   for ( int by = 0; by < bh; by++ ) {
   
      for ( int bx = 0; bx < bw; ++bx ) {
         s1i = (uint32_t)src1[bx] * (0x100 - alpha);
         s2i = (uint32_t)src2[bx] * alpha;
         dst[bx] = (D)((s1i + s2i) >> 8);
      }
   
      src1 += sstr1;
      src2 += sstr2;
      dst  += dstr;
   }
}

template <typename D>                                
void add_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight )
{
   long mx = numeric_limits<D>::max();
   long mn = numeric_limits<D>::min();
   
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
         long sum = src0[x] + src1[x];
         
         if(sum > mx) {
            dst[x] = mx;
         } else if(sum < mn) {
            dst[x] = mn;
         } else {
            dst[x] = sum;
         }
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}                           

template <typename D>                                     
void and_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight )
{
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
      
         dst[x] = src0[x] & src1[x];
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}

template <typename S, typename D>
void clz_ref( S* src, int sstr, 
              D* dst, int dstr, 
			     int blockWidth, int blockHeight )
{   
   uint8_t bits = sizeof(src[0]) * 8;
   D numZeros;
   uint8_t msb_08  = 128;
   uint16_t msb_16 = 32768;
   
   
   for(int y = 0; y < blockHeight; ++y) {
		for(int x = 0; x < blockWidth; ++x) {

			numZeros = 0;
			if (src[x] == 0) {
				numZeros = (D) bits;
			} else {
				for (int i = 1; i < bits; ++i) {
					if ((bits == 8 && (src[x] & msb_08)) || (bits == 16 && (src[x] & msb_16))) {
						break;
					}
	  				++numZeros;
					src[x] <<= 1;
				}
			}
         dst[x] = numZeros;
      }
       
      dst += dstr;
      src += sstr;
   }
}   

template <typename S, typename D>                                     
void magnitude_ref( const S* src0, int sstr0, 
                    const S* src1, int sstr1,
                          D* dst,  int dstr, 
                   int blockWidth, int blockHeight )
{
   const S* sx;
   const S* sy;
      
   for (int by = 0; by < blockHeight; by++) {
      sx = (const S*) src0;
      sy = (const S*) src1;
      
      for (int bx = 0; bx < blockWidth; bx++)  {         
         // Compute magnitude       
         uint32_t ax = (uint32_t)abs(sx[bx]);
         uint32_t ay = (uint32_t)abs(sy[bx]);
         
         uint32_t sx2 = (uint32_t)ax * (uint32_t)ax;
         uint32_t sy2 = (uint32_t)ay * (uint32_t)ay;
                  
         uint32_t s2 = sx2 + sy2;
        
		 dst[bx] = (D)sqrt((double)s2 );
      }
      src0 += sstr0;
      src1 += sstr1;
      dst  += dstr;      
   }
}                
            
template <typename D>            
void not_ref( const D* src0, int sstr0, 
              D* dst,  int dstr, 
              int blockWidth, int blockHeight )
{
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
      
         dst[x] = ~src0[x];
      }
      
      dst  += dstr;
      src0 += sstr0;
   }
}                           
       
template <typename D>       
void or_ref( const D* src0, int sstr0, 
             const D* src1, int sstr1,
             D* dst,  int dstr, 
             int blockWidth, int blockHeight )
{
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
      
         dst[x] = src0[x] | src1[x];
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}                  

template <typename S, typename D>       
void sub_ref( const S* src0, int sstr0, 
              const S* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight )
{
   long mx = numeric_limits<D>::max();
   long mn = numeric_limits<D>::min();

   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
         long diff = src0[x] - src1[x];

         if(diff > mx) {
            dst[x] = mx;
         } else if(diff < mn) {
            dst[x] = mn;
         } else {
            dst[x] = diff;
         }
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}         

template <typename D>       
void threshold_ref( const D* src0, int sstr0, 
                    unsigned int threshold,
                    unsigned char* dst,  int dstr, 
                    int blockWidth, int blockHeight )
{
   long mx = numeric_limits<D>::max();
   long mn = numeric_limits<D>::min();
   
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
      
         if(src0[x] > threshold) {
            dst[x] = mx;
         } else {
            dst[x] = mn;
         }
      }
      
      dst  += dstr;
      src0 += sstr0;
   }
}   

template <typename D>       
void xor_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight )
{
   for(int y = 0; y < blockHeight; ++y) {
   
      for(int x = 0; x < blockWidth; ++x) {
      
         dst[x] = src0[x] ^ src1[x];
      }
      
      dst  += dstr;
      src0 += sstr0;
      src1 += sstr1;
   }
}   

