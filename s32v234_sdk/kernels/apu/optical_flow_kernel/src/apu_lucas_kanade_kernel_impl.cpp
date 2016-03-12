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

/*!
* \file apu_lucas_kanade_kernel_impl.cpp
* \brief Lucas-Kanade mismatch filter, eq.29 in "Pyramidal Implementation of the Lucas Kanade Feature Tracker Description of the algorithm", Jean-Yves Bouguet - intel.com. Implementation for APEX
* \author Anca Dima
* \version
* \date
****************************************************************************/


#ifdef ACF_KERNEL_IMPLEMENTATION


//#include "apu_add_impl.h"
#include "apu_lucas_kanade_kernel_impl.h"
#include "apu_accumulation_kernel_impl.h"
#include "apu_dot_multiplic_kernel_impl.h"
#include "apu_difference_kernel_impl.h"
#include "apu_dot_division_kernel_impl.h"
#include "apu_add_impl.h"
#include "apu_dot_sqr_kernel_impl.h"

//needed for the ACCUM_MARGIN and ACCUM_OFFS defines
#include "apu_gradient_matrix_kernel_impl.h"

#ifdef APEX2_EMULATE
#include "apu_cond.hpp"
#endif

#ifndef etaNormAmplif_ShiftFact
#define  etaNormAmplif_ShiftFact  8
#endif

void lucas_kanade_mismatch_filter(/*vec08u* imgA, vec08u* imgB, */vec32s* deltaK_GradX, vec32s* deltaK_GradY, vec32s* imgDeltaK, int16s inStrideWidth, int16s bw, int16s bh, int16s outStrideWidth, vec16s* gradX, vec16s* gradY)
{
	//difference_filter_in08u_out16s(imgDeltaK, imgA, imgB, sstr, bw, bh);
	dot_mult_in32s_in16s_out32s_filter(deltaK_GradX, imgDeltaK, gradX, bw, bh, inStrideWidth, outStrideWidth);
	//dot_mult_in16s_out32s_filter(deltaK_GradX, imgDeltaK, gradX, sstr, bw, bh);
	//dot_mult_in16s_out32s_filter(deltaK_GradY, imgDeltaK, gradY, sstr, bw, bh);	
	dot_mult_in32s_in16s_out32s_filter(deltaK_GradY, imgDeltaK, gradY, bw, bh, inStrideWidth, outStrideWidth);
} 


void lucas_kanade_accum_filter(vec32s* etaX, vec32s* etaY, int16s inStrideWidth, int16s bw, int16s bh, vec32s* deltaK_GradX, vec32s* deltaK_GradY)
{	
	int16s offsX = ACCUM_OFFS
		 , offsY = ACCUM_OFFS; // x,y offsets where to start the accumulation
	
	accumulation_in32s_filter(etaX, deltaK_GradX, inStrideWidth, offsX, offsY, bw - ACCUM_MARGIN, bh - ACCUM_MARGIN);
	accumulation_in32s_filter(etaY, deltaK_GradY, inStrideWidth, offsX, offsY, bw - ACCUM_MARGIN, bh - ACCUM_MARGIN);
}

void lucas_kanade_offset_filter(vec32s* gOutX_high, vec32u* gOutX_low, vec32s* gOutY_high, vec32u* gOutY_low, vec32s* etaX, vec32s* etaY, vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accgradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen)
{
	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];

			vec32s accGradXSqrV = (vec32s) accGradXSqr[j];
			vec32s accGradYSqrV = (vec32s) accGradYSqr[j];
			vec32s* accgradXYv = &accgradXgradY[j];
			gOutX_high[j] = 0;
			gOutY_high[j] = 0;
			gOutX_low[j] = 0;
			gOutY_low[j] = 0;

			vec32s tmpEtaX_t1_high;
			vec32u tmpEtaX_t1_low;
	
			vec32s tmpEtaX_t2_high;
			vec32u tmpEtaX_t2_low;

			vec32s tmpEtaY_t1_high;
			vec32u tmpEtaY_t1_low;

			vec32s tmpEtaY_t2_high;
			vec32u tmpEtaY_t2_low;
			//rsh_in32u_out32u_filter(&downGradXSqr, gradXSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32u_out32u_filter(&downaccGradYSqr, accGradYSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32s_out32s_filter(&downaccgradXgradY, accgradXYv, accDownScale, strideLen, 1, 1);
			//vec32s signedDownX = (vec32s)downGradXSqr;
			//vec32s signedDownY = (vec32s)downaccGradYSqr;
			
			
			dot_mult_in32s_out64s_filter(&tmpEtaX_t1_high, &tmpEtaX_t1_low, etaXv, &accGradYSqrV, 1, 1, 1, 1);
			dot_mult_in32s_out64s_filter(&tmpEtaX_t2_high, &tmpEtaX_t2_low, etaYv, accgradXYv, 1, 1, 1, 1);

			dot_mult_in32s_out64s_filter(&tmpEtaY_t1_high, &tmpEtaY_t1_low, etaYv, &accGradXSqrV, 1, 1, 1, 1);
			dot_mult_in32s_out64s_filter(&tmpEtaY_t2_high, &tmpEtaY_t2_low, etaXv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in64s_out64s(&gOutX_high[j], &gOutX_low[j], &tmpEtaX_t1_high, &tmpEtaX_t1_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, 1, 1, 1, 1);
			difference_filter_in64s_out64s(&gOutY_high[j], &gOutY_low[j], &tmpEtaY_t1_high, &tmpEtaY_t1_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, 1, 1, 1, 1);
		}

		accGradXSqr += inStrideLen;
		accGradYSqr += inStrideLen;
		accgradXgradY += inStrideLen;
		etaX += inStrideLen;
		etaY += inStrideLen;
		
		gOutX_high += outStrideLen;
		gOutY_high += outStrideLen;
		gOutX_low += outStrideLen;
		gOutY_low += outStrideLen;
		
	} // for all i < bh


} // end of kernel






void downScaleAndDivide(vec32s* gOut, vec32s* gOutOffs, vec32s* gIn_high, vec32u* gIn_low, /*vec32s* accDetG_high, */vec32u* accDetG_inv, vec16u* inValidPts, vec16u* outValidPts, vec32u* vEtaNorm, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen)
{
	const vec32s maxDist = 8;
	const vec08u etaAmplFact = etaNormAmplif_ShiftFact;
	vec08u q3_28_ShiftFact = 28;
	vec08u rshFact = (q3_28_ShiftFact << 1) - etaAmplFact;


	const vec16u ones = 1;

	const int08u shiftFact = 3;
	const int08u toShift = 31 - shiftFact;
	const int32u offsetMask = 0x7FFFFFFF >> shiftFact; // mask for the lowest 28 bits 
	const vec32s oneInQ3_28 = 1 << toShift;

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec16u* inVP = &inValidPts[j];
			vec16u* outVP = &outValidPts[j];
			vec32s* gO = &gOut[j];
			vec32s* gO_Offs = &gOutOffs[j];
			*outVP = *inVP;
			vEtaNorm[j] = 0;

			vif(*inVP == ones) {
				//accDetG_inv has unsigned type but contains actually a signed Q3.28 fixed point inverse of the determinant
				vec32s absGHigh = gIn_high[j], detGSigned = vec32s(accDetG_inv[j]);
				vec32u absGLow = gIn_low[j], absDetGLow = vabs(detGSigned); 

				vbool hasSgn = hasSign(gIn_high[j], detGSigned);

				vif(absGHigh < 0) {
					change64bitSign(absGHigh, absGLow);
				} vendif

				*gO = 0;

				vec32u offsHigh;
				vec32u offsLow;

				dot_mult_in32u_out64u_filter(&offsHigh, &offsLow, &absGLow, &absDetGLow, 1, 1, 1, 1);
				*gO_Offs = vec32s(offsLow & offsetMask);
				*gO = vec32s((offsLow  >> toShift) + (offsHigh << (shiftFact + 1)));

				vif(*gO >= maxDist)  {
					*outVP = 0;
					*gO = 0;
					*gO_Offs = 0;
				} velse {
					vif(hasSgn) {
						// if negative, it should be one less
						*gO = -(*gO) - 1;
						*gO_Offs = oneInQ3_28 - gOutOffs[j]; // revert the direction, go one pixel to the left and have Eps > 0
					} vendif

	
					vec32s gO_shift28_hi, gO_Offs_hi = 0, g0_pl_offs_hi;
					vec32u gO_shift28_lo, offs_sqr_lo, gO_Offs_lo, offs_sqr_hi, g0_pl_offs_lo, mul_lo, mul_hi, tmpEtaRsh_hi, tmpEtaRsh_lo;
					
					gO_Offs_lo = vec32u((*gO_Offs));
					vif(*gO_Offs < 0) {
						gO_Offs_hi = -1;
					}vendif

					// l-shift the integer part of the offset by 28 to have the same scale with the Q3_28 fractional part
					lsh_in32s_out64s_filter(&gO_shift28_hi, &gO_shift28_lo, gO, &q3_28_ShiftFact, 1, 1, 1, 1);

					// add integer part with fractional part at scale 2^28
					add_in64s_out64s(&g0_pl_offs_hi, &g0_pl_offs_lo, &gO_shift28_hi, &gO_shift28_lo, &gO_Offs_hi, &gO_Offs_lo, 1, 1, 1, 1);

					// compute the square of the offset
					dot_sqr_in64s_out64u_filter(&mul_hi, &mul_lo, &g0_pl_offs_hi, &g0_pl_offs_lo, 1, 1, 1, 1);

					// scale down to (offs^2)*8 from (offs*2^28)^2 == offs^2*2^56!
					rsh_in64u_out64u_filter(&tmpEtaRsh_hi, &tmpEtaRsh_lo, &mul_hi, &mul_lo, &rshFact, 1, 1, 1, 1);
					vEtaNorm[j] = tmpEtaRsh_lo;

				} vendif
				
			} velse {
				*outVP = 0;
				*gO = 0;
				*gO_Offs = 0;
			} vendif
		}
		
		gIn_high += inStrideLen;
		gIn_low += inStrideLen;

		accDetG_inv += inStrideLen;
		inValidPts += inStrideLen;

		outValidPts += outStrideLen;
		gOut += outStrideLen;
		gOutOffs += outStrideLen;
		vEtaNorm += outStrideLen;
	} // for all i < bh


}


void lucas_kanade_offset_filter_xOry(vec32s* gOut, vec32s* gOutOffs, vec32s* etaX, vec32s* etaY, vec32s* accGradXorYSqr, vec32s* accgradXgradY, vec32u *accDetG_inv, vec16u* inValidPts, vec16u* outValidPts, vec32u* vEtaNorm, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen)
{

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];
			vec32s* gOutCrt = &gOut[j];
			vec32s* gOutOffsCrt = &gOutOffs[j];
			vec32u* accDetGInvCrt = &accDetG_inv[j];
			vec32u vEtaNormCrt; 


			vec32s *accGradXorYSqrV = &accGradXorYSqr[j];
			vec32s* accgradXYv = &accgradXgradY[j];
			vec32s gOutX_high;
			vec32u gOutX_low;

			vec32s tmpEtaX_t1_high;
			vec32u tmpEtaX_t1_low;

			vec32s tmpEtaX_t2_high;
			vec32u tmpEtaX_t2_low;

			vec16u* inVP = &inValidPts[j];
			vec16u* outVP = &outValidPts[j];
			
			dot_mult_in32s_out64s_filter(&tmpEtaX_t1_high, &tmpEtaX_t1_low, etaXv, accGradXorYSqrV, 1, 1, 1, 1);
			dot_mult_in32s_out64s_filter(&tmpEtaX_t2_high, &tmpEtaX_t2_low, etaYv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in64s_out64s(&gOutX_high, &gOutX_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, 1, 1, 1, 1);
			downScaleAndDivide(gOutCrt, gOutOffsCrt, &gOutX_high, &gOutX_low, accDetGInvCrt, inVP, outVP, &vEtaNormCrt, 1, 1, 1, 1);
			vif(outVP) {
				*vEtaNorm += vEtaNormCrt;
			} vendif
		}

		
		accGradXorYSqr += inStrideLen;
		accgradXgradY += inStrideLen;
		accDetG_inv += inStrideLen; // inverse of the determinant in Q3_28 format
		etaX += inStrideLen;
		etaY += inStrideLen;
		inValidPts += inStrideLen;

		//vEtaNorm += outStrideLen;
		outValidPts += outStrideLen;
		gOut += outStrideLen;
		gOutOffs += outStrideLen;
	} // for all i < bh


} // end of kernel



void lucas_kanade_offset_filter_xOry_unsigned(vec32s* gOut, vec32s* gOutOffs, vec32s* etaX, vec32s* etaY, vec32u* accGradXorYSqr, vec32s* accgradXgradY, vec32u *accDetG_inv, vec16u* inValidPts, vec16u* outValidPts, vec32u* vEtaNorm, int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen)
{

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];
			vec32s* gOutCrt = &gOut[j];
			vec32s* gOutOffsCrt = &gOutOffs[j];
			vec32u* accDetGInvCrt = &accDetG_inv[j];
			vec32u vEtaNormCrt;


			vec32s accGradXorYSqrV = vec32s(accGradXorYSqr[j]);
			vec32s* accgradXYv = &accgradXgradY[j];
			vec32s gOutX_high;
			vec32u gOutX_low;

			vec32s tmpEtaX_t1_high;
			vec32u tmpEtaX_t1_low;

			vec32s tmpEtaX_t2_high;
			vec32u tmpEtaX_t2_low;

			vec16u* inVP = &inValidPts[j];
			vec16u* outVP = &outValidPts[j];

			dot_mult_in32s_out64s_filter(&tmpEtaX_t1_high, &tmpEtaX_t1_low, etaXv, &accGradXorYSqrV, 1, 1, 1, 1);
			dot_mult_in32s_out64s_filter(&tmpEtaX_t2_high, &tmpEtaX_t2_low, etaYv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in64s_out64s(&gOutX_high, &gOutX_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, 1, 1, 1, 1);
			downScaleAndDivide(gOutCrt, gOutOffsCrt, &gOutX_high, &gOutX_low, accDetGInvCrt, inVP, outVP, &vEtaNormCrt, 1, 1, 1, 1);
			vif(outVP) {
				*vEtaNorm += vEtaNormCrt;
			} vendif
		}


		accGradXorYSqr += inStrideLen;
		accgradXgradY += inStrideLen;
		accDetG_inv += inStrideLen; // inverse of the determinant in Q3_28 format
		etaX += inStrideLen;
		etaY += inStrideLen;
		inValidPts += inStrideLen;

		//vEtaNorm += outStrideLen;
		outValidPts += outStrideLen;
		gOut += outStrideLen;
		gOutOffs += outStrideLen;
	} // for all i < bh


} // end of kernel

/*
void lucas_kanade_offset_filter(vec32s* gOutX_high, vec32s* gOutY_high, vec32s* gOutX_low, vec32s* gOutY_low, vec32s* etaX, vec32s* etaY, int16s sstr, int16s bw, int16s bh, vec32s* accGradXSqr, vec32s* accGradYSqr, vec32s* accgradXgradY, vec08u* validPoints)
{
	vec32s tmpEtaX, tmpEtaY 
		, tmpEtaX_t1 
		, tmpEtaX_t2 
		, tmpEtaY_t1 
		, tmpEtaY_t2 ;

	int32s strideLen = sstr;

	vec32s overflowThresh = (1 << 16);
	int32s overflowExpSc = 4; // it is 16, if the ACCUM_TILE_SIZE_X/Y is 8
	vec32s overflowExp = (vec32s) overflowExpSc;
	vec32s maxValToScale = (1 << (31 - overflowExpSc));
	vec32s negMaxValToScale = -maxValToScale;
	vec32s maxVal = (1 << 31);

	vec32s etaXvOutBds = 0;
	vec32s etaYvOutBds = 0;
	vec32s accGradXSqrVOutBds = 0;
	vec32s accGradYSqrVOutBds = 0;
	vec32s accgradXYvOutBds = 0;
	vec32s xterm1OutBds = 0, xterm2OutBds = 0;
	vec32s yterm1OutBds = 0, yterm2OutBds = 0;

	vec32s	accgradXYvRed = 0,
			accGradXSqrVRed = 0,
			accGradYSqrVRed = 0; // , gradXYvSqr = 0;, gradXYvRed_XYv = 0;

	vec32s etaXvRed = 0,
		   etaYvRed = 0;

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];

			vec32s* accGradXSqrV = &accGradXSqr[j];
			vec32s* accGradYSqrV = &accGradYSqr[j];
			vec32s* accgradXYv   = &accgradXgradY[j];
			gOutX_high[j] = 0;
			gOutY_high[j] = 0;
			gOutX_low[j] = 0;
			gOutY_low[j] = 0;

			vec32s absEtaXv = vabs(*etaXv);
			vec32s absEtaYv= vabs(*etaYv);
			//vec32s testDetG;

			vec32s absaccgradXYv = vabs(*accgradXYv);

			vec08u (*validPointsV) = &validPoints[j];
			
			vif((*validPointsV) > 0) {
				etaXvOutBds = vec32s(absEtaXv >= overflowThresh);
				etaYvOutBds = vec32s(absEtaYv >= overflowThresh);
				accGradXSqrVOutBds = vec32s(*accGradXSqrV >= overflowThresh);
				accGradYSqrVOutBds = vec32s(*accGradYSqrV >= overflowThresh);
				gradXYvOutBds = vec32s(absaccgradXYv >= overflowThresh);

	
				vif(etaXvOutBds > 0) {
					etaXvRed = ((*etaXv) >> overflowExp);
				} velse{
					etaXvRed = (*etaXv);
				}
				vendif

				vif(etaYvOutBds > 0) {
					etaYvRed = ((*etaYv) >> overflowExp);
				} velse{
					etaYvRed = (*etaYv);
				}
				vendif

				vif(gradXYvOutBds > 0) {
					gradXYvRed = ((*gradXYv) >> overflowExp);
					//gradXYvRed_XYv = gradXYvRed * (*gradXYv);
				} velse{
					gradXYvRed = (*gradXYv);
					//gradXYvSqr = (*gradXYv)  * (*gradXYv);
				}
				vendif

				vif(accGradYSqrVOutBds > 0) {
					accGradYSqrVRed = ((*accGradYSqrV) >> overflowExp);
				} velse {
					accGradYSqrVRed = (*accGradYSqrV);
				}
				vendif

				vif(accGradXSqrVOutBds > 0) {
					accGradXSqrVRed = ((*accGradXSqrV) >> overflowExp);
				}velse{
					accGradXSqrVRed = (*accGradXSqrV);
				}
				vendif
				xterm1OutBds = (etaXvOutBds + accGradYSqrVOutBds);
				xterm2OutBds = (etaYvOutBds + gradXYvOutBds);
				yterm1OutBds = (etaYvOutBds + accGradXSqrVOutBds);
				yterm2OutBds = (etaXvOutBds + gradXYvOutBds);
				

				tmpEtaX_t1 = etaXvRed * accGradYSqrVRed;
				tmpEtaX_t2 = -etaYvRed * gradXYvRed;
				tmpEtaY_t1 = etaYvRed * accGradXSqrVRed;
				tmpEtaY_t2 = -etaXvRed * gradXYvRed;



			vif(xterm1OutBds >= xterm2OutBds) {
				tmpEtaX = tmpEtaX_t1 + (tmpEtaX_t2 >> ((xterm1OutBds-xterm2OutBds) * overflowExp));
				gOutX_low[j] = xterm1OutBds * overflowExp;
			} velse{
				tmpEtaX = (tmpEtaX_t1 >> (xterm2OutBds - xterm1OutBds) * overflowExp) + tmpEtaX_t2;
				gOutX_low[j] = xterm2OutBds * overflowExp;
			}
			vendif

			vif(yterm1OutBds >= yterm2OutBds) {
				tmpEtaY = tmpEtaY_t1 + (tmpEtaY_t2 >> ((yterm1OutBds - yterm2OutBds) * overflowExp));
				gOutY_low[j] = yterm1OutBds * overflowExp;
			} velse{
				tmpEtaY = (tmpEtaY_t1 >> ((yterm2OutBds - yterm1OutBds) *overflowExp)) + tmpEtaY_t2;
				gOutY_low[j] = yterm2OutBds * overflowExp;
			}
			vendif

	

			gOutX_high[j] = tmpEtaX; // transfer eta to the output
			gOutY_high[j] = tmpEtaY;
	
		}
		vendif // validPoints > 0		

		} // for all j < bw
		etaX += strideLen;
		etaY += strideLen;
//		gInX += strideLen;
//		gInY += strideLen;
		accGradXSqr += strideLen;
		accGradYSqr += strideLen;
		accgradXgradY += strideLen;		

		gOutX_high += strideLen;
		gOutY_high += strideLen;
		gOutX_low += strideLen;
		gOutY_low += strideLen;

		validPoints += strideLen;
	} // for all i < bh
} // end of kernel
*/



void transformCoordsToPointOffsets(vec32u* lPointOffsets, vec16u* newValidPts, vec32s* xCoords, vec32s* yCoords, vec16u* validPoints, 
	 							   int32s imgWidth, int32s imgHeight, int32s tWidth, int32s tHeight, 
								   int32s dSz, int16s bw, int16s bh, int16s inputStrideWidth, int16s outputStrideWidth ) 
{
	vec32u* offsetData = lPointOffsets;
	int32s halfTileWidth = tWidth >> 1,
		   halfTileHeight = tHeight >> 1;

	for (int16s y = 0; y < bh; ++y)
	{
		for (int16s x = 0; x < bw; ++x)
		{
			offsetData[x] = 0;
			newValidPts[x] = validPoints[x];

			vif (validPoints[x] > 0) {
				vec32s crtX , crtY;

				crtX = xCoords[x] - halfTileWidth;
				crtY = yCoords[x] - halfTileHeight;				

				vif (crtX >= 0 && crtY >= 0 && crtX + tWidth < imgWidth && crtY + tHeight < imgHeight) {
					//newValidPts[x] = 1; // this was done above
					offsetData[x] = (crtY * imgWidth + crtX) * dSz;					
				} velse {
					//offsetData[x] = 0; // this was done above
					newValidPts[x] = 0;
				} vendif

			} vendif
		}

		xCoords += inputStrideWidth;
		yCoords += inputStrideWidth;
		validPoints += inputStrideWidth;
		newValidPts += outputStrideWidth;
		offsetData += outputStrideWidth;
		
	}

}



#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
