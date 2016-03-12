#ifdef ACF_KERNEL_IMPLEMENTATION
/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file apu_bilinear_interpolation_kernel_impl.c
* \brief Builds the sum of all elements of a chunk and writes out a vector of sum values.
* \author Anca Dima
* \version
* \date
****************************************************************************/

// In order to compile it as CPP do following: 
// In Visual Studio->Solution Explorer->Project "convolution_Kernel", right click -> Properties -> C/C++ ->Advanced->CompileAs->Compile As C++

#include "apu_bilinear_interpolation_kernel_impl.h"
#include "apu_difference_kernel_impl.h"
#include "apu_add_impl.h"
#include "apu_dot_sqr_kernel_impl.h"
#include "apu_dot_multiplic_kernel_impl.h"
#include "apu_dot_division_kernel_impl.h"

#ifdef APEX2_EMULATE
#include <stdio.h>
#include <iostream>
#include "apu_cond.hpp"
#endif

void bilinear_interpolation_filter_in08u_out16s(vec16s* lpvOut, vec08u* lpvIn, vec16s* xOffs, vec16u* quotx, vec16s* yOffs, vec16u* quoty, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth)
{
   vec08u* crtRow = lpvIn;
   vec08u* nextRow = crtRow + inStrideWidth;
   vec16s* crtOutRow = lpvOut;
  
   int32s k = 0;
	
   // there is onle one x,y,quot offset for each chunk of data and CU
   vec32s xOffs32 = (vec32s)*xOffs;
   vec32s yOffs32 = (vec32s)*yOffs;
   vec32s quot32x = (vec32s)*quotx;
   vec32s quot32y = (vec32s)*quoty;

	vec32s alpha1 = (quot32x - xOffs32)<<bilinearUpScale;
	vec32s alpha2 = xOffs32 << bilinearUpScale;
	vec32s beta1 = (quot32y- yOffs32);
	vec32s quotSqr = quot32x * quot32y;
	vec32s alpha1_beta1 = (alpha1*beta1) / quotSqr;
	vec32s alpha2_beta1 = (alpha2*beta1) / quotSqr;
	vec32s alpha1_yOffs32 = (alpha1*yOffs32) / quotSqr;
	vec32s alpha2_yOffs32 = (alpha2*yOffs32) / quotSqr;

	for (int16s y = 0; y < bh-1; ++y)
	{

		for (int16s x = 0; x < bw-1; ++x) 
		{
			vif(quotSqr != 0) {
				vec32s tmp = (alpha1_beta1*vec32s(crtRow[x]) + alpha2_beta1*vec32s(crtRow[x + 1]) + alpha1_yOffs32*vec32s(nextRow[x]) + alpha2_yOffs32*vec32s(nextRow[x + 1]));
				crtOutRow[x] = vec16s(tmp);
			} velse{
				crtOutRow[x] = 0;
			}vendif


		}
		// only copy the last value.			
		crtOutRow[bw - 1] = crtOutRow[bw - 2];

		crtRow += inStrideWidth;
		nextRow += inStrideWidth;
		crtOutRow += outStrideWidth;
	}

	vec16s* oneRowAbove = crtOutRow - outStrideWidth;
	// last row is just copied and scaled up
	for (int16s x = 0; x < bw; ++x)
	{
		crtOutRow[x] = oneRowAbove[x];
	}

 } 


void bilinear_interpolation_filter_in16u_out16s(vec16s* lpvOut, vec16u* lpvIn, vec32s* xOffs, vec32u* quotx, vec32s* yOffs, vec32u* quoty, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth)
{
	vec16u* crtRow = lpvIn;
	vec16u* nextRow = crtRow + inStrideWidth;
	vec16s* crtOutRow = lpvOut;
	int32s k = 0;

	// there is onle one x,y,quot offset for each chunk of data and CU

	
	vec32u lastBitMask = 0x7FFFFFFF;

	vec32s quot32x = (vec32s)*quotx;
	vec32s alpha2 = (*xOffs);// << bilinearUpScale;

	vif(*quotx > lastBitMask) {
		quot32x >>= 1;
		alpha2 >>=  1;
	} vendif


	vec32s quot32y = (vec32s)*quoty;
	vec32s beta2 = (*yOffs);// << bilinearUpScale;

	vif(*quoty > lastBitMask) {
		quot32y >>= 1;
		beta2 >>= 1;
	} vendif
	
	vec32s alpha1_high;
	vec32u alpha1_low;
	difference_filter_in32s_out64s(&alpha1_high, &alpha1_low, &quot32x, &alpha2, 1,1,1,1);// << bilinearUpScale;

	vec32s beta1_high;
	vec32u beta1_low;
	difference_filter_in32s_out64s(&beta1_high, &beta1_low, &quot32y, &beta2, 1, 1, 1, 1);// << bilinearUpScale;

	/* Below following operations are performed
	 
		alpha1_beta1 = alpha1*beta1;
		alpha2_beta1 = alpha2*beta1;
		alpha1_beta2 = alpha1*beta2;
		alpha2_beta2 = alpha2*beta2;
	*/
	vec32s alpha1_beta1_high;
	vec32u alpha1_beta1_low;
	dot_mult_in64s_out64s_filter(&alpha1_beta1_high, &alpha1_beta1_low, &alpha1_high, &alpha1_low, &beta1_high, &beta1_low, 1,1,1,1);

	vec32s alpha2_beta1_high;
	vec32u alpha2_beta1_low;
	vec32s alpha2_high = 0;
	vif(alpha2 < 0) {
		alpha2_high = -1;
	} vendif

	vec32u alpha2_low = vec32u(alpha2);
	dot_mult_in64s_out64s_filter(&alpha2_beta1_high, &alpha2_beta1_low, &alpha2_high, &alpha2_low, &beta1_high, &beta1_low, 1,1,1,1);

	vec32s alpha1_beta2_high;
	vec32u alpha1_beta2_low;
	vec32s beta2_high = 0;
	vif(beta2 < 0) {
		beta2_high = -1;
	} vendif

	vec32u beta2_low = vec32u(beta2);
	dot_mult_in64s_out64s_filter(&alpha1_beta2_high, &alpha1_beta2_low, &alpha1_high, &alpha1_low, &beta2_high, &beta2_low, 1,1,1,1);

	vec32s alpha2_beta2_high;
	vec32u alpha2_beta2_low;
	dot_mult_in32s_out64s_filter(&alpha2_beta2_high, &alpha2_beta2_low, &alpha2, &beta2, 1,1,1,1);

	// Do inverse on 32 bit x and y quotients, since the multiplied value could have more than 32 bits.
	vec08u log2XFact, log2YFact;
	vec32s invXQuot, invYQuot;
	int08u shiftNR = 3; //thus we will have Q3.28 numbers
	computeInv_NewtonRaphson(&invXQuot, &quot32x, &log2XFact, shiftNR, 1, 1, 1, 1);
	computeInv_NewtonRaphson(&invYQuot, &quot32y, &log2YFact, shiftNR, 1, 1, 1, 1);

	//Multiply the inverses. WARNING: the result has now to be downscaled by quotRShft^2 (see below) 
	//quotSqr = quot32x * quot32y;
	vec32s quotSqr_high;
	vec32u quotSqr_low;
	dot_mult_in32s_out64s_filter(&quotSqr_high, &quotSqr_low, &invXQuot, &invYQuot, 1, 1, 1, 1);
	
	int08u quotRShft = 31 - shiftNR;//32-shiftNr?
	vec08u quotRShftVect = quotRShft;
	int08u rightShiftFact = 2 * quotRShft - bilinearUpScale;
	vec08u shiftVect = rightShiftFact;
	//vec32u maskMin = vec32u(0x7fffffff) >> shiftNR;
	vif(quotSqr_high > 0) {
		vec32s tmpQuot_high;
		vec32u tmpQuot_low;
		rsh_in64s_out64s_filter(&tmpQuot_high, &tmpQuot_low, &quotSqr_high, &quotSqr_low, &quotRShftVect, 1, 1, 1, 1);
		quotSqr_high = tmpQuot_high;
		quotSqr_low = tmpQuot_low;
		shiftVect -= quotRShft;
	} vendif

	vec32s a1_b1_h;
	vec32u a1_b1_l;
	dot_mult_in64s_out64s_filter(&a1_b1_h, &a1_b1_l, &alpha1_beta1_high, &alpha1_beta1_low, &quotSqr_high, &quotSqr_low, 1, 1, 1, 1);

	vec32s a1_b2_h;
	vec32u a1_b2_l;
	dot_mult_in64s_out64s_filter(&a1_b2_h, &a1_b2_l, &alpha1_beta2_high, &alpha1_beta2_low, &quotSqr_high, &quotSqr_low, 1, 1, 1, 1);

	vec32s a2_b1_h;
	vec32u a2_b1_l;
	dot_mult_in64s_out64s_filter(&a2_b1_h, &a2_b1_l, &alpha2_beta1_high, &alpha2_beta1_low, &quotSqr_high, &quotSqr_low, 1, 1, 1, 1);

	vec32s a2_b2_h;
	vec32u a2_b2_l;
	dot_mult_in64s_out64s_filter(&a2_b2_h, &a2_b2_l, &alpha2_beta2_high, &alpha2_beta2_low, &quotSqr_high, &quotSqr_low, 1, 1, 1, 1);

	//int08u rightShiftFact = (2*quotRShft - bilinearUpScale);
	//vbool stillToShift = true;
	vec08u crtShiftFact = 2;
	//vec08u shiftVect = rightShiftFact;

	bool hasToShift = true;
	alpha1_beta1_high = a1_b1_h;
	alpha1_beta1_low = a1_b1_l;
	alpha1_beta2_high = a1_b2_h; 
	alpha1_beta2_low = a1_b2_l;
	alpha2_beta1_high = a2_b1_h;
	alpha2_beta1_low =  a2_b1_l;
	alpha2_beta2_high = a2_b2_h;
	alpha2_beta2_low = a2_b2_l;


	while (hasToShift == true)  
	{
		vbool stillToShift = ((a1_b1_h > 0 || a1_b1_l > lastBitMask) || (a1_b2_h > 0 || a1_b2_l > lastBitMask) 
							|| (a2_b1_h > 0 || a2_b1_l > lastBitMask) || (a2_b2_h > 0 || a2_b2_l > lastBitMask) ) 
							&& (shiftVect > crtShiftFact);

	
		vif(stillToShift) {
			rsh_in64s_out64s_filter(&alpha1_beta1_high, &alpha1_beta1_low, &a1_b1_h, &a1_b1_l, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&alpha1_beta2_high, &alpha1_beta2_low, &a1_b2_h, &a1_b2_l, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&alpha2_beta1_high, &alpha2_beta1_low, &a2_b1_h, &a2_b1_l, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&alpha2_beta2_high, &alpha2_beta2_low, &a2_b2_h, &a2_b2_l, &crtShiftFact, 1, 1, 1, 1);
			shiftVect -= crtShiftFact;
		}vendif

		crtShiftFact = 0;


		hasToShift = vany(stillToShift);
		if (hasToShift) {
			a1_b1_h = alpha1_beta1_high; a1_b1_l = alpha1_beta1_low;
			vif(a1_b1_h < 0) {
				change64bitSign(a1_b1_h, a1_b1_l);
			} vendif

			a1_b2_h = alpha1_beta2_high; a1_b2_l = alpha1_beta2_low;
			vif(a1_b2_h < 0) {
				change64bitSign(a1_b2_h, a1_b2_l);
			} vendif


			a2_b1_h = alpha2_beta1_high; a2_b1_l = alpha2_beta1_low;
			vif(a2_b1_h < 0) {
				change64bitSign(a2_b1_h, a2_b1_l);
			} vendif

			a2_b2_h = alpha2_beta2_high; a2_b2_l = alpha2_beta2_low;
			vif(a2_b2_h < 0) {
				change64bitSign(a2_b2_h, a2_b2_l);
			} vendif
			/*
				#ifdef APEX2_EMULATE
				std::cout << "WARNING BILINEAR interpolation: values too high before end computation\n";
			#endif*/

			vec32s maxHighWord;
			vif(a1_b1_h > a2_b2_h) {
				maxHighWord = a1_b1_h;
			} velse{
				maxHighWord = a2_b2_h;
			}vendif

			vif(maxHighWord < a1_b2_h) {
				maxHighWord = a1_b2_h;
			} vendif

			vif(maxHighWord < a2_b1_h) {
				maxHighWord = a2_b1_h;
			} vendif

			computeLog2(&crtShiftFact, &maxHighWord, 1, 1, 1, 1);
			crtShiftFact++;
		}

		a1_b1_h = alpha1_beta1_high; a1_b1_l = alpha1_beta1_low;
		a1_b2_h = alpha1_beta2_high; a1_b2_l = alpha1_beta2_low;
		a2_b1_h = alpha2_beta1_high; a2_b1_l = alpha2_beta1_low;
		a2_b2_h = alpha2_beta2_high; a2_b2_l = alpha2_beta2_low;

	}

	alpha1_beta1_high = vec32s(alpha1_beta1_low);
	alpha1_beta2_high = vec32s(alpha1_beta2_low);
	alpha2_beta1_high = vec32s(alpha2_beta1_low);
	alpha2_beta2_high = vec32s(alpha2_beta2_low);

	int32s mask16s = 0x7FFF;

	for (int16s y = 0; y < bh-1; ++y)
	{

		for (int16s x = 0; x < bw-1; ++x)
		{
			vif(quot32x != 0 && quot32y != 0) {
				//Compute: tmp = ((alpha1_beta1*vec32s(crtRow[x]) + alpha2_beta1*vec32s(crtRow[x + 1]) + alpha1_beta2*vec32s(nextRow[x]) + alpha2_beta2*vec32s(nextRow[x + 1])) / quotSqr);
				
				vec32s tmp1_high, tmp2_high, tmp3_high, tmp4_high, tmp12_high;
				vec32u tmp1_low, tmp2_low, tmp3_low, tmp4_low, tmp12_low;
				vec32s pix11 = vec32s(crtRow[x]), pix12 = vec32s(crtRow[x + 1]), pix21 = vec32s(nextRow[x]), pix22 = vec32s(nextRow[x+1]);
				
				dot_mult_in32s_out64s_filter(&tmp1_high, &tmp1_low, &alpha1_beta1_high, &pix11, 1, 1, 1, 1);
				dot_mult_in32s_out64s_filter(&tmp2_high, &tmp2_low, &alpha2_beta1_high, &pix12, 1, 1, 1, 1);
				dot_mult_in32s_out64s_filter(&tmp3_high, &tmp3_low, &alpha1_beta2_high, &pix21, 1, 1, 1, 1);
				dot_mult_in32s_out64s_filter(&tmp4_high, &tmp4_low, &alpha2_beta2_high, &pix22, 1, 1, 1, 1);

				add_in64s_out64s(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, 1, 1, 1, 1);
				tmp1_high = 0; tmp1_low = 0;
				add_in64s_out64s(&tmp1_high, &tmp1_low, &tmp12_high, &tmp12_low, &tmp3_high, &tmp3_low, 1, 1, 1, 1);
				tmp2_high = 0; tmp2_low = 0;
				add_in64s_out64s(&tmp2_high, &tmp2_low, &tmp1_high, &tmp1_low, &tmp4_high, &tmp4_low, 1, 1, 1, 1);

				tmp1_high = 0; tmp1_low = 0;
				rsh_in64s_out64s_filter(&tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, &shiftVect, 1, 1, 1, 1);
				tmp12_high = tmp1_high; tmp12_low = tmp1_low;
				vif(tmp12_high < 0) {
					change64bitSign(tmp12_high, tmp12_low);
				} vendif
				vbool stillToShift = tmp12_high > 0 || tmp12_low > mask16s;
					
				/*
#ifdef APEX2_EMULATE
				if (vany(stillToShift)) {
					std::cout << "WARNING BILINEAR interpolation: values too high at end computation\n";
				}
#endif
*/
				vif(stillToShift) {
					vec08u log2Fact = 0;
					compute64bitLog2(&log2Fact, &tmp1_high, &tmp1_low, 1, 1, 1, 1);
					vif(log2Fact > 15) {
						log2Fact -= 15;
						rsh_in64s_out64s_filter(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &log2Fact, 1, 1, 1, 1);
					} vendif

				} velse {
					tmp12_low = tmp1_low; // could have changed sign above
				} vendif
								
				crtOutRow[x] = vec16s(tmp12_low);
			} velse{
				crtOutRow[x] = 0;
			}vendif
		}
		// fill in the last column with the values of the previous column
		crtOutRow[bw - 1] = crtOutRow[bw - 2];

		// only copy the last value.			
		crtOutRow[bw - 1] = crtOutRow[bw - 2];

		crtRow += inStrideWidth;
		nextRow += inStrideWidth;
		crtOutRow += outStrideWidth;
		
	}

	vec16s* oneRowAbove = crtOutRow - outStrideWidth;
	// last row is just copied and scaled up
	for (int16s x = 0; x < bw; ++x)
	{
		crtOutRow[x] = oneRowAbove[x];
	}
}

void bilinear_interpolation_filter_in16u_out16s_Q3_28(vec16s* lpvOut, vec16u* lpvIn, vec32s* xOffs, vec32s* yOffs, int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth)
{
	vec16u* crtRow = lpvIn;
	vec16u* nextRow = crtRow + inStrideWidth;
	vec16s* crtOutRow = lpvOut;
	int32s k = 0;

	// there is onle one x,y,quot offset for each chunk of data and CU
	vec32s oneQ3_28 = 1 << 28;
	
	vec32s alpha2 = (*xOffs);// << bilinearUpScale;
	vec32s beta2 = (*yOffs);// << bilinearUpScale;

	vec32s alpha1 = oneQ3_28 - alpha2;

	vec32s beta1  = oneQ3_28 - beta2;

	/* Below following operations are performed

	alpha1_beta1 = alpha1*beta1;
	alpha2_beta1 = alpha2*beta1;
	alpha1_beta2 = alpha1*beta2;
	alpha2_beta2 = alpha2*beta2;
	*/
	vec32s alpha1_beta1_high;
	vec32u alpha1_beta1_low;
	dot_mult_in32s_out64s_filter(&alpha1_beta1_high, &alpha1_beta1_low, &alpha1, &beta1, 1, 1, 1, 1);

	vec32s alpha2_beta1_high;
	vec32u alpha2_beta1_low;
	dot_mult_in32s_out64s_filter(&alpha2_beta1_high, &alpha2_beta1_low, &alpha2, &beta1, 1, 1, 1, 1);

	vec32s alpha1_beta2_high;
	vec32u alpha1_beta2_low;
	dot_mult_in32s_out64s_filter(&alpha1_beta2_high, &alpha1_beta2_low, &alpha1, &beta2, 1, 1, 1, 1);

	vec32s alpha2_beta2_high;
	vec32u alpha2_beta2_low;
	dot_mult_in32s_out64s_filter(&alpha2_beta2_high, &alpha2_beta2_low, &alpha2, &beta2, 1, 1, 1, 1);

	int08u shiftNR = 3; //thus we will have Q3.28 numbers

	int08u quotRShft = 31 - shiftNR;
	int08u rightShiftFact = 2 * quotRShft - bilinearUpScale;
	vec08u shiftVect = rightShiftFact;
	vec08u crtShiftFact = quotRShft;

	vec32s a1_b1_h, a1_b2_h, a2_b1_h, a2_b2_h;
	vec32u a1_b1_l, a1_b2_l, a2_b1_l, a2_b2_l;
		
	rsh_in64s_out64s_filter(&a1_b1_h, &a1_b1_l, &alpha1_beta1_high, &alpha1_beta1_low, &crtShiftFact, 1, 1, 1, 1);
	rsh_in64s_out64s_filter(&a1_b2_h, &a1_b2_l, &alpha1_beta2_high, &alpha1_beta2_low, &crtShiftFact, 1, 1, 1, 1);
	rsh_in64s_out64s_filter(&a2_b1_h, &a2_b1_l, &alpha2_beta1_high, &alpha2_beta1_low, &crtShiftFact, 1, 1, 1, 1);
	rsh_in64s_out64s_filter(&a2_b2_h, &a2_b2_l, &alpha2_beta2_high, &alpha2_beta2_low, &crtShiftFact, 1, 1, 1, 1);

	shiftVect -= crtShiftFact;
	crtShiftFact = 0;

	int32s mask16s = 0x7FFF;

	vec32u tmp1_high, tmp2_high, tmp12_high, tmp1_low, tmp2_low, tmp12_low;
	vec32u pix11, pix12, pix21, pix22;

	for (int16s y = 0; y < bh-1; ++y)
	{
		for (int16s x = 0; x < bw-1; ++x)
		{			
			pix11 = vec32u(crtRow[x]);
			pix12 = vec32u(crtRow[x + 1]);
			pix21 = vec32u(nextRow[x]);
			pix22 = vec32u(nextRow[x + 1]);
			//Compute: tmp = ((alpha1_beta1*vec32s(crtRow[x]) + alpha2_beta1*vec32s(crtRow[x + 1]) + alpha1_beta2*vec32s(nextRow[x]) + alpha2_beta2*vec32s(nextRow[x + 1])) / quotSqr);

			dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a1_b1_l, &pix11, 1, 1, 1, 1);
			dot_mult_in32u_out64u_filter(&tmp2_high, &tmp2_low, &a2_b1_l, &pix12, 1, 1, 1, 1);
			add_in64u_out64u(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, 1, 1, 1, 1);
				
			dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a1_b2_l, &pix21, 1, 1, 1, 1);
			add_in64u_out64u(&tmp2_high, &tmp2_low, &tmp1_high, &tmp1_low, &tmp12_high, &tmp12_low, 1, 1, 1, 1);

			dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a2_b2_l, &pix22, 1, 1, 1, 1);
			add_in64u_out64u(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, 1, 1, 1, 1);
							
			rsh_in64u_out64u_filter(&tmp1_high, &tmp1_low, &tmp12_high, &tmp12_low, &shiftVect, 1, 1, 1, 1);
			vbool stillToShift = tmp1_high > 0 || tmp1_low > mask16s;
								
#ifdef APEX2_EMULATE
			if (vany(stillToShift)) {
				std::cout << "WARNING BILINEAR interpolation: values too high at end computation\n";
			}
#endif
				
			vif(stillToShift) {
				vec08u log2Fact = 0;					
				compute64bitLog2u(&log2Fact, &tmp1_high, &tmp1_low, 1, 1, 1, 1);
				vif(log2Fact > 15) {
					log2Fact -= 15;
					rsh_in64u_out64u_filter(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &log2Fact, 1, 1, 1, 1);
				} vendif

			} velse{
				tmp12_low = tmp1_low; // could have changed sign above
			} vendif

			crtOutRow[x] = vec16s(tmp12_low);			
		}

		// fill in the last column with the values of the previous column
		crtOutRow[bw - 1] = crtOutRow[bw - 2];

		crtRow += inStrideWidth;
		nextRow += inStrideWidth;
		crtOutRow += outStrideWidth;
	}

	vec16s* oneRowAbove = crtOutRow-outStrideWidth;
	// last row is just copied and scaled up
	for (int16s x = 0; x < bw; ++x)
	{
		crtOutRow[x] = oneRowAbove[x];
	}
	
}




#include <string.h>
#ifdef APEX2_EMULATE
#include <sstream>
#endif
void bilinear_interpolation_withOffsPar_filter_in16u_out16s_Q3_28(vec16s* lpvOut, vec16u* lpvIn, vec08u* lpvtmpDiv, int32s* xPts, int32s* yPts, int32s* xOffs, int32s* yOffs, int16u nrPts, int16u chunkStartRow, int16u& idxFirstCell, vec16s& vIndicesWillBeDone,
	vec32u *accum_a1b1L, vec32u *accum_a1b2L, vec32u *accum_a2b1L, vec32u *accum_a2b2L,// int08u* tmpDone,
	int16u crtImgWidth, int16s bw, int16s bh, int16s outCellWidth, int16s outCellHeight, int16s inStrideWidth, int16s outStrideWidth)
{

	int08u accumShift = 0; // 64 regions might overlap above a pixel and be added together. Thus have to downscale to avoid overflow (we have Q3.28 fixed point format)
	int08u shiftNR = 3; //thus we will have Q3.28 numbers
	int08u quotRShft = 31 - shiftNR;
	int08u rightShiftFact = 2 * quotRShft - bilinearUpScale;
	vec08u shiftVect = rightShiftFact;
	vec08u crtShiftFact = quotRShft;

	int16u chunkEndRow = chunkStartRow + bh;

	//const int32s chunkSz = (ACCUM_TILE_SIZE_X+2)*(ACCUM_TILE_SIZE_Y+2);


	int int32SourceStride = inStrideWidth;
	int int32DestStride = outStrideWidth;
	bool somethingToDo = false;
	//vbool cuActive = false;

	vec16s vIndices = -1;
	vec16s vOldIndicesDone = vIndicesWillBeDone, vNewIndicesDone = -1;
	
	// offset inside the selected chunk, goes from startOffsetX to endOffsetX, crtY to endY
	vec16s vEndX = -1;
	vec16s vStartX = -1;
	vec16s vEndY = -1;

	// index inside the APEX chunk, goes from startX % bw to bw, or (startY-chunkStartRow) to bh
	vec16s vX = -1;
	vec16s vY = -1;

	vec32s alpha2 = 0;
	vec32s beta2 = 0;

	int crtIdxFirstCell = idxFirstCell;

	bool totalSomethingToDo = false;

	--outCellWidth;
	--outCellHeight;

	do {
		somethingToDo = false;

		for (int16u i = crtIdxFirstCell; i < nrPts; i++)
		{
			int32s crtX = xPts[i], endX = crtX + outCellWidth;
			int32s crtY = yPts[i], endY = crtY + outCellHeight;

			if (crtY >= chunkEndRow || endY < chunkStartRow )
			{
				//offset is outside this tile
				if (endY < chunkStartRow) {
					idxFirstCell = i + 1;
					continue;
				}
				else
				if (crtY >= chunkEndRow) {
					// offset lies in one of the next chunks, thus stop iteration
					break;
				}
			}


			if (xOffs[i] == 0 && yOffs[i] == 0 || endX < 0) {
				// skip all offsets, for which no interpolation is needed
				
				if (i == crtIdxFirstCell)
					crtIdxFirstCell = i + 1;

				if (i == idxFirstCell)
					idxFirstCell = i + 1;

					continue;				
			}

			int16s startY = int16s(crtY > chunkStartRow ? crtY : chunkStartRow);
			int16s endOffsetY = (int16s) (endY < chunkEndRow ? endY%bh : bh-1);

			int32u startOffsetX = (int32u)(crtX >= 0 ? crtX : 0); // limit X to image dimensions
			int32u endOffsetX = endX < crtImgWidth ? endX : crtImgWidth - 1;
	
			int cuStart = startOffsetX / bw;
			int cuEnd = endOffsetX / bw;

			int lastIdx = vget(vOldIndicesDone, cuStart);
			//int lastIdx = tmpDone[i];
			//if (lastIdx == 1) {
			if ((int) i <= lastIdx) {			
				if (crtIdxFirstCell == i)
					++crtIdxFirstCell;

				if (idxFirstCell == i)
					++idxFirstCell;

				continue;
			}

			bool isFree = (0 > vget(vIndices, cuStart)) && (0 > vget(vIndices, cuEnd));
			if (isFree) {
				alpha2 = vput(alpha2, xOffs[i], cuStart);
				beta2 = vput(beta2, yOffs[i], cuStart);

				vIndices = vput(vIndices, (int16s)i, cuStart);
	
				int16s x = (int16s)(startOffsetX % bw);
				vX = vput(vX, x, cuStart);
				vStartX = vput(vStartX, (int16s) x, cuStart);

				int16s chunkEndX = (cuStart + 1)*bw;
				int16s crtEndOffsetX = (int16s)endOffsetX < chunkEndX ? endOffsetX%bw : bw-1;

				vEndX = vput(vEndX, crtEndOffsetX, cuStart);

				vY = vput(vY, (int16s)(startY - chunkStartRow), cuStart);				
				vEndY = vput(vEndY, endOffsetY, cuStart);
				
				//tmpDone[i] == true;

				if (cuStart == cuEnd){
					if (i == crtIdxFirstCell)
						crtIdxFirstCell++;

					vNewIndicesDone = vput(vNewIndicesDone, (int16s)i, cuStart);

					if (endY < chunkEndRow){
						vIndicesWillBeDone = vput(vIndicesWillBeDone, (int16s)i, cuStart);
						if (i == idxFirstCell){
							idxFirstCell = i + 1;
						}
					}
				}
			}
			else  {

				continue;
			}

			isFree = 0 > vget(vIndices, cuEnd); // could be already false, if cuStart == cuEnd
			if (isFree) {
				// this is executed, only if both CU's are free and cuEnd != cuStart; 

				alpha2 = vput(alpha2, xOffs[i], cuEnd);
				beta2 = vput(beta2, yOffs[i], cuEnd);
				vIndices = vput(vIndices, (int16s)i, cuEnd);

				vX = vput(vX, (int16s) 0, cuEnd);
				vStartX = vput(vStartX, (int16s) 0, cuEnd);
				
				vY = vput(vY, (int16s) (startY - chunkStartRow), cuEnd);

				int16s chunkEndX = (cuEnd+1)*bw;
				int16s crtEndOffsetX = (int16s)endOffsetX < chunkEndX ? endOffsetX%bw : bw - 1;
				vEndX = vput(vEndX, (int16s)crtEndOffsetX, cuEnd);
				vEndY = vput(vEndY, (int16s)endOffsetY, cuEnd);

				if (i == crtIdxFirstCell)
					crtIdxFirstCell++;

				vNewIndicesDone = vput(vNewIndicesDone, (int16s)i, cuStart);

				if (endY < chunkEndRow){
					vIndicesWillBeDone = vput(vIndicesWillBeDone, (int16s)i, cuStart);
					if (i == idxFirstCell){
						idxFirstCell = i+1;
					}
				}
			}
		}

		vOldIndicesDone = vNewIndicesDone;

		vec32s a1_b1_h, a1_b2_h, a2_b1_h, a2_b2_h;
		vec32u a1_b1_l, a1_b2_l, a2_b1_l, a2_b2_l;

		if (vany(vIndices >= 0)) {
			shiftVect = rightShiftFact;
			crtShiftFact = quotRShft;

			somethingToDo = true;

			vec32s oneQ3_28 = 1 << 28;


			vec32s alpha1 = oneQ3_28 - alpha2;
			vec32s beta1 = oneQ3_28 - beta2;

			vec32s alpha1_beta1_high;
			vec32u alpha1_beta1_low;
			dot_mult_in32s_out64s_filter(&alpha1_beta1_high, &alpha1_beta1_low, &alpha1, &beta1, 1, 1, 1, 1);

			vec32s alpha2_beta1_high;
			vec32u alpha2_beta1_low;
			dot_mult_in32s_out64s_filter(&alpha2_beta1_high, &alpha2_beta1_low, &alpha2, &beta1, 1, 1, 1, 1);

			vec32s alpha1_beta2_high;
			vec32u alpha1_beta2_low;
			dot_mult_in32s_out64s_filter(&alpha1_beta2_high, &alpha1_beta2_low, &alpha1, &beta2, 1, 1, 1, 1);

			vec32s alpha2_beta2_high;
			vec32u alpha2_beta2_low;
			dot_mult_in32s_out64s_filter(&alpha2_beta2_high, &alpha2_beta2_low, &alpha2, &beta2, 1, 1, 1, 1);
			
			crtShiftFact += accumShift; // due to accumulation, values could go out of bounds, thus scale down by 3 and transform numbers into Q6.25 fixed point format
			rsh_in64s_out64s_filter(&a1_b1_h, &a1_b1_l, &alpha1_beta1_high, &alpha1_beta1_low, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&a1_b2_h, &a1_b2_l, &alpha1_beta2_high, &alpha1_beta2_low, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&a2_b1_h, &a2_b1_l, &alpha2_beta1_high, &alpha2_beta1_low, &crtShiftFact, 1, 1, 1, 1);
			rsh_in64s_out64s_filter(&a2_b2_h, &a2_b2_l, &alpha2_beta2_high, &alpha2_beta2_low, &crtShiftFact, 1, 1, 1, 1);
			shiftVect -= (crtShiftFact-accumShift);
			crtShiftFact = 0;

			for (int cY = 0; cY < bh && vany(vIndices >= 0); cY++) {
				// virtual run through all lines, for covering a whole input chunk
				for (int cX = 0; cX < bw && vany(vIndices >= 0); cX++) {
					vif(vIndices >= 0) {

						vec16s chunkOffsetsOutX = vY * outStrideWidth + vX;
						
						vec32u  a1b1l = vec32u(vload(accum_a1b1L, chunkOffsetsOutX))
							, a1b2l = vec32u(vload(accum_a1b2L, chunkOffsetsOutX))
							, a2b1l = vec32u(vload(accum_a2b1L, chunkOffsetsOutX))
							, a2b2l = vec32u(vload(accum_a2b2L, chunkOffsetsOutX));

						vec08u nrInterpol = vload(lpvtmpDiv, chunkOffsetsOutX);
						vstore(lpvtmpDiv, chunkOffsetsOutX, (nrInterpol + 1));
						
						vstore(accum_a1b1L, chunkOffsetsOutX, (a1_b1_l + a1b1l));
						vstore(accum_a1b2L, chunkOffsetsOutX, (a1_b2_l + a1b2l));
						vstore(accum_a2b1L, chunkOffsetsOutX, (a2_b1_l + a2b1l));
						vstore(accum_a2b2L, chunkOffsetsOutX, (a2_b2_l + a2b2l));
#ifdef APEX2_EMULATE
#ifdef _DEBUG
					vbool vc = false;
					vbool vf = false;
					
					vbool stillToShift = false;
					vec32u a = vaddx(a1_b1_l, a1b1l, vc, vf);
					stillToShift = stillToShift || vf;

					vec32u b = vaddx(a1_b2_l, a1b2l, vc, vf);
					stillToShift = stillToShift || vf;

					vec32u c = vaddx(a2_b1_l , a2b1l, vc, vf);
					stillToShift = stillToShift || vf;

					vec32u d = vaddx(a2_b2_l, a2b2l, vc, vf);
					stillToShift = stillToShift || vf;

					if (vany(stillToShift && (vIndices >= 0))) {
						std::cout << "WARNING BILINEAR interpolation: alpha values too high at end computation\n";
					}
#endif
#endif
						++vX;
						vif(vX > vEndX) {
							++vY;
							vX = vStartX;
							vif(vY > vEndY) {
								vIndices = -1;
							} vendif
						}vendif

					} vendif
				}
			}
		}
		else {
			somethingToDo = false;
		}
		totalSomethingToDo |= somethingToDo;
	} while (somethingToDo);	

	if (totalSomethingToDo == true) {
		// if several interpolation regions overlap, then they were added together, thus one has to 
		vec16s* crtOutRow = lpvOut;
		vec16u* crtInRow = lpvIn;

		vec08u* tmpDivRow = lpvtmpDiv;
		vec08u zeroV = 0;
		
		vec16u* nextRow = crtInRow + inStrideWidth;
		vec32u  *a1b1l = accum_a1b1L
			, *a1b2l = accum_a1b2L 
			, *a2b1l = accum_a2b1L
			, *a2b2l = accum_a2b2L;

		int32s mask16s = 0x7FFF;

		shiftVect = rightShiftFact;
		crtShiftFact = quotRShft;
		shiftVect -= crtShiftFact;

		for (int iY = 0; iY < bh; iY++) {
			for (int iX = 0; iX < bw; iX++) {
				vif(tmpDivRow[iX] > zeroV) {		
					vec16u cR = crtInRow[iX], cRN = crtInRow[iX + 1], nR = nextRow[iX], nRN = nextRow[iX + 1];

					//Compute: tmp = ((alpha1_beta1*vec32s(crtRow[x]) + alpha2_beta1*vec32s(crtRow[x + 1]) + alpha1_beta2*vec32s(nextRow[x]) + alpha2_beta2*vec32s(nextRow[x + 1])) / quotSqr);
					vec32u tmp1_high, tmp2_high, tmp12_high, tmp1_low, tmp2_low, tmp12_low;
					vec32u pix11 = vec32u(cR), pix12 = vec32u(cRN), pix21 = vec32u(nR), pix22 = vec32u(nRN);
					vec32u tmpDivRow32u = vec32u(tmpDivRow[iX]);
					vec32u  a1_b1_l = (a1b1l[iX] / tmpDivRow32u) << accumShift
						, a1_b2_l = (a1b2l[iX] / tmpDivRow32u) << accumShift
						, a2_b1_l = (a2b1l[iX] / tmpDivRow32u) << accumShift
						, a2_b2_l = (a2b2l[iX] / tmpDivRow32u) << accumShift;

					dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a1_b1_l, &pix11, 1, 1, 1, 1);
					dot_mult_in32u_out64u_filter(&tmp2_high, &tmp2_low, &a2_b1_l, &pix12, 1, 1, 1, 1);
					add_in64u_out64u(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, 1, 1, 1, 1);

					dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a1_b2_l, &pix21, 1, 1, 1, 1);
					add_in64u_out64u(&tmp2_high, &tmp2_low, &tmp1_high, &tmp1_low, &tmp12_high, &tmp12_low, 1, 1, 1, 1);

					dot_mult_in32u_out64u_filter(&tmp1_high, &tmp1_low, &a2_b2_l, &pix22, 1, 1, 1, 1);
					add_in64u_out64u(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &tmp2_high, &tmp2_low, 1, 1, 1, 1);

					rsh_in64u_out64u_filter(&tmp1_high, &tmp1_low, &tmp12_high, &tmp12_low, &shiftVect, 1, 1, 1, 1);

					crtOutRow[iX] = vec16s(tmp1_low);
#ifdef APEX2_EMULATE
					vbool stillToShift = tmp1_high > 0 || tmp1_low > mask16s;
					if (vany(stillToShift)) {
						std::cout << "WARNING BILINEAR interpolation: values too high at end computation\n";
					}
					/*
					vif(stillToShift) {
					vec08u log2Fact = 0;
					compute64bitLog2u(&log2Fact, &tmp1_high, &tmp1_low, 1, 1, 1, 1);
					vif(log2Fact > 15) {
					log2Fact -= 15;
					rsh_in64u_out64u_filter(&tmp12_high, &tmp12_low, &tmp1_high, &tmp1_low, &log2Fact, 1, 1, 1, 1);
					} vendif

					} velse{
					tmp12_low = tmp1_low; // could have changed sign above
					} vendif */
#endif
				
				} velse{
					crtOutRow[iX] = (vec16s)(crtInRow[iX] << bilinearUpScale);
				}
				vendif
			}
			
			crtOutRow += outStrideWidth;
			tmpDivRow += outStrideWidth;
			crtInRow += inStrideWidth;
			nextRow += inStrideWidth;

			a1b1l += outStrideWidth;
			a1b2l += outStrideWidth;
			a2b1l += outStrideWidth;
			a2b2l += outStrideWidth;
		}

	}
	else {
		vec16s* crtOutRow = lpvOut;
		vec16u* crtInRow = lpvIn;
		for (int iY = 0; iY < bh; iY++) {
			for (int iX = 0; iX < bw; iX++) {
				crtOutRow[iX] = (vec16s)(crtInRow[iX] << bilinearUpScale);
			}
			crtOutRow += outStrideWidth;
			crtInRow += inStrideWidth;
		}
	}
		
}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
