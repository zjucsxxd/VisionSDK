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
* \file apu_gradient_matrix_kernel_impl.cpp
* \brief Gradient_matrix computes for an InputImage's GradX, GradY, GradXSqr, GradYSqr, GradX*GradY and accumulations over a neighborhood, given by (bw, bh), i.e. chunk size. Implementation for APEX
* \author Anca Dima
* \version
* \date
****************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION

#ifdef APEX2_EMULATE
#include "apu_vec.hpp"
#include "apu_cond.hpp"
#endif


#include "apu_gradient_matrix_kernel_impl.h"
#include "apu_accumulation_kernel_impl.h"
#include "apu_dot_multiplic_kernel_impl.h"
#include "apu_dot_sqr_kernel_impl.h"
#include "apu_difference_kernel_impl.h"
#include "apu_correlation_kernel_impl.h"
#include "apu_dot_division_kernel_impl.h"


void gradient_matrix_filter(vec16s* gradX, vec16s* gradY, 
	 vec32u* gradXSqr, vec32u* gradYSqr, vec32s* gradXgradY,
	 int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideWidth)
{	
	dot_sqr_in16s_out32u_filter(gradXSqr, gradX,  bw, bh, inStrideWidth, outStrideWidth);
	dot_sqr_in16s_out32u_filter(gradYSqr, gradY,  bw, bh, inStrideWidth, outStrideWidth);
	dot_mult_in16s_out32s_filter(gradXgradY, gradX, gradY,  bw, bh, inStrideWidth, outStrideWidth);
} 


void accum_gradient_matrix_filter(vec32u* gradXSqr, vec32u* gradYSqr,
	vec32s* gradXgradY, 	
	vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accGradXY,
	vec32u* accDetG_inv, vec16u* validPts,
	int16s bw, int16s bh, int16s inStrideWidth, int16s outStrideLen)
{
	vec32s accDetG_high;

	{
		int16s offsX = ACCUM_OFFS, offsY = ACCUM_OFFS; // x,y offsets where to start the accumulation

		accumulation_in32u_filter(accGradXSqr, gradXSqr, inStrideWidth, offsX, offsY, bw - ACCUM_MARGIN, bh - ACCUM_MARGIN);
		accumulation_in32u_filter(accGradYSqr, gradYSqr, inStrideWidth, offsX, offsY, bw - ACCUM_MARGIN, bh - ACCUM_MARGIN);
		accumulation_in32s_filter(accGradXY, gradXgradY, inStrideWidth, offsX, offsY, bw - ACCUM_MARGIN, bh - ACCUM_MARGIN);

		// Accumulation transforms a vector of matrices to a vector of single values. 
		// Thus treat the subsequent data as single element vectors

		*accGradXSqr >>= accDownScale;
		*accGradYSqr >>= accDownScale;
		*accGradXY >>= accDownScale;

	#ifdef _DEBUG
		/* just for debugging
		int i = 0;
		long long xSqrTmsYSqr = (long long)vget((*accGradXSqr), i) * (long long)vget((*accGradYSqr), i);
		long long xySqr = (long long) vget((*accGradXY), i) * (long long)vget((*accGradXY), i);
		long long det = xSqrTmsYSqr - xySqr;
		long long sumXSqr_ySqr = (long long)vget((*accGradXSqr), i) + (long long)vget((*accGradYSqr), i);
		long long difEigen = sumXSqr_ySqr - (det >> 17);*/
	#endif

		vec32u tmpAB_high, tmpCD_high;
		vec32u tmpAB_low, tmpCD_low;

		dot_mult_in32u_out64u_filter(&tmpAB_high, &tmpAB_low, accGradXSqr, accGradYSqr, 1, 1, outStrideLen, outStrideLen);
		dot_sqr_in32s_out64u_filter(&tmpCD_high, &tmpCD_low, accGradXY, 1, 1, outStrideLen, outStrideLen);

		difference_filter_in64u_out64s(&accDetG_high, accDetG_inv, &tmpAB_high, &tmpAB_low, &tmpCD_high, &tmpCD_low, 1, 1, outStrideLen, outStrideLen);


		// Filter out too low eigenvalues:
		// (IxSqr, IySqr, Ixy) >>= 20 in front...of the OpenCV computation
		// Point is not valid if min eigenValue is lower than 0.001 . 
		// Min Eigvalue is (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy))/2*bw*bh < 0.001  ==>
		// (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy)) < 0.002*bw*bh ==> (IxSqr + IySqr - c/f)^2 < (IxSqr - IySqr)^2 +4Ixy*Ixy); where c = 2*bw*bh*downscaleFact, f = 1000 ==> 
		// (IxSqr+IySqr)^2 -2*c/f*(IxSqr+IySqr) + (c/f)^2 <  (IxSqr - IySqr)^2 +4Ixy*Ixy ==>  4*IxSqr*IySqr - 2*c/f(IxSqr+IySqr) + (c/f)^2 < 4Ixy*Ixy
		// Point is NOT valid if:
		// c^2 < 2*c*f*(IxSqr+IySqr) +f^2*4(Ixy^2 - IxSqr*IySqr); c = 2*bw*bh*downScaleFact = 2^6*2^20; initial downScaleFactor of IxSqr, IySqr, Ixy is 2^20
		// (c/2f)^2 < (c/2f)*(IxSqr+IySqr) + (Ixy^2 - IxSqr*IySqr)

		// factor f=1000 is close to 1024, ie 2^10, 
		vbool hasCarry;
		vbool getCarry = false;
		vec32u sumGradXSqr_GradYSqr_low = (vec32u)vaddx(*accGradXSqr, *accGradYSqr, getCarry, hasCarry); // this is A
		vec32s sumGradXSqr_GradYSqr_high = vec32s(hasCarry);


		static const int32s upscale = ((inputShiftFact + scharrFiltUpscale / 2) << 1);
		static const int32s downscale = accDownScale, initScale = 19, diffScale = initScale - (downscale - upscale); //10
		const int32u  accumSz = 2 * (bw - ACCUM_MARGIN) * (bh - ACCUM_MARGIN); // ~= 2^7
		static const int32u f = 2000; //2 x 1000
		int32u cnstFact = diffScale > 23 ? accumSz*((1 << diffScale) / f) : (accumSz* (1 << diffScale)) / f;
		int32u cnstSqrLow = 0, cnstSqrHigh = 0;
		if (cnstFact < (1 << 16)) {
			cnstSqrLow = cnstFact*cnstFact; //cnstFact ~2^6=64, cnstSqr ~2^12=4096
		}
		else {
			vec32s cnstVect = (int32s)cnstFact;
			vec32u dstH = 0, dstL = 0;
			dot_sqr_in32s_out64u_filter(&dstH, &dstL, &cnstVect, 1, 1, 1, 1);
			cnstSqrLow = vget(dstL, 0);
			cnstSqrHigh = vget(dstH, 0);
		}

		vbool ThasCarry, TgetCarry = false;
		static const int32u one = 1;
		int32u invCnstFact = ((one << 31) / cnstFact) << 1;
		vec32s TsumEigenHigh = (sumGradXSqr_GradYSqr_high * cnstFact) + (vec32s)(sumGradXSqr_GradYSqr_low / invCnstFact);
		vec32u TsumEigenLow = sumGradXSqr_GradYSqr_low *cnstFact;

		vec32s TdiffEigenLow = (vec32s)vsubx(TsumEigenLow, *accDetG_inv, TgetCarry, ThasCarry);
		vec32s TdiffEigenHigh = (vec32s)vsubx(TsumEigenHigh, accDetG_high, ThasCarry, TgetCarry);
		int32u amplFact = 3;//2 // 1;
		int32u TdiffEigenHighThresh = (cnstSqrHigh << amplFact) + (cnstSqrLow >> (32 - amplFact));
		int32u TdiffEigenLowThresh = (cnstSqrLow << amplFact);

		vec32u absDiffLow = (vec32u)vabs(TdiffEigenLow);
		vec32u absDiffHigh = (vec32u)vabs(TdiffEigenHigh);
		vec16u TaltValid;
		if (TdiffEigenHighThresh == 0)
			TaltValid = (vec16u)((absDiffLow < TdiffEigenLowThresh) && (TdiffEigenHigh == 0 || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
		else {
			vif(TdiffEigenHighThresh < absDiffHigh && TdiffEigenHigh > 0) {
				TaltValid = (vec16u)false;
			} velse{
				TaltValid = (vec16u)((TdiffEigenHighThresh >= absDiffHigh || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
			} vendif
				//difference_filter_in64u_out64s(&dH, &dL, &TdiffEigenHighThresh, &TdiffEigenLowThresh, &absDiffHigh, &absDiffLow, 1, 1, 1,1);
				//TaltValid = (vec16u)((dH > 0 || (dH == 0 && dL >= 0)) && (accDetG_inv != 0 || accDetG_high != 0));
		}
		*validPts = TaltValid;
	} 

	vif (*validPts == true) {
		vec32s absDetGHigh = accDetG_high;
		vec32u absDetGLow = *accDetG_inv;

		vif(absDetGHigh < 0) {
			change64bitSign(absDetGHigh, absDetGLow);
		} vendif

		vec08u log2Fact;
		int32u firstBit0u = 0x7FFFFFFF;
		vif(absDetGHigh > 0 || absDetGLow > firstBit0u) {

			computeLog2(&log2Fact, &absDetGHigh, 1, 1, 1, 1);
			log2Fact++;

			vec32s tmpDetGHigh;
			vec32u tmpDetGLow;
			rsh_in64s_out64s_filter(&tmpDetGHigh, &tmpDetGLow, &accDetG_high, accDetG_inv, &log2Fact, 1, 1, 1, 1);
			accDetG_high = tmpDetGHigh;
			*accDetG_inv = tmpDetGLow;

			rsh_in32u_out32u_filter(&tmpDetGLow, accGradXSqr, &log2Fact, 1, 1, 1, 1);
			*accGradXSqr = tmpDetGLow;

			rsh_in32u_out32u_filter(&tmpDetGLow, accGradYSqr, &log2Fact, 1, 1, 1, 1);
			*accGradYSqr = tmpDetGLow;

			rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXY, &log2Fact, 1, 1, 1, 1);
			*accGradXY = tmpDetGHigh;

		} vendif

		vec32s detG32Bit = vec32s(*accDetG_inv), invDetG_Q3_28;
		int08s shiftFact = 3; //compute Q3.28 fixed point representation of the detG inverse
		computeInv_NewtonRaphson(&invDetG_Q3_28, &detG32Bit, &log2Fact, shiftFact, 1, 1, 1, 1);

		*accDetG_inv = vec32u(invDetG_Q3_28);
	} vendif
}

void inverse_determinant_filter_obs(vec32s* accGradXSqrH, vec32u* accGradXSqrL, 
			vec32s* accGradYSqrH, vec32u* accGradYSqrL, vec32s* accGradXYH, vec32u* accGradXYL, 
			vec32s* outAccGradXSqr, vec32s* outAccGradYSqr, vec32s* outAccGradXY, 
			vec32u* accDetG_inv, vec16u* validPts, 
			int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen)
{
	int16s offsX = ACCUM_OFFS, offsY = ACCUM_OFFS; // x,y offsets where to start the accumulation

	vec32s *accGradXSqr = outAccGradXSqr, *accGradYSqr = outAccGradYSqr;
	vec32s *accGradXY = outAccGradXY;


	vec08u rshFact = vec08u(accDownScale);
	for (int16s by = 0; by < bh; ++by)  // y data row
	{
		for (int16s bx = 0; bx < bw; ++bx) // x in the blck_tile
		{
			vec32s accDetG_high;

			{
				vec32u dstLowXY;
				{
					//accGradXSqr >> accDownScale, a.s.o
					vec32s dstHighXsqr, dstHighYsqr, dstHighXY;
					vec32u tmpAccGrad;
					rsh_in64s_out64s_filter(&dstHighXsqr, &tmpAccGrad, accGradXSqrH, accGradXSqrL, &rshFact, 1, 1, 1, 1);
					*accGradXSqr = vec32s(tmpAccGrad);
					rsh_in64s_out64s_filter(&dstHighYsqr, &tmpAccGrad, accGradYSqrH, accGradYSqrL, &rshFact, 1, 1, 1, 1);
					*accGradYSqr = vec32s(tmpAccGrad);
					rsh_in64s_out64s_filter(&dstHighXY, &dstLowXY, accGradXYH, accGradXYL, &rshFact, 1, 1, 1, 1);
					*accGradXY = (vec32s)dstLowXY;
					/*
					vif(dstHighXsqr != 0 || dstHighYsqr != 0 || (dstHighXsqr > 0 || (dstHighXsqr < -1) ) ) {
						printf("\nWARNING: Values of detG have more than 32 bits\n");
					} vendif
					*/
				}
#ifdef _DEBUG
				/* just for debugging
				int i = 0;
				long long xSqrTmsYSqr = (long long)vget((*accGradXSqr), i) * (long long)vget((*accGradYSqr), i);
				long long xySqr = (long long) vget((*accGradXY), i) * (long long)vget((*accGradXY), i);
				long long det = xSqrTmsYSqr - xySqr;
				long long sumXSqr_ySqr = (long long)vget((*accGradXSqr), i) + (long long)vget((*accGradYSqr), i);
				long long difEigen = sumXSqr_ySqr - (det >> 17);*/
#endif

				vec32s tmpAB_high;
				vec32u tmpAB_low, tmpCD_low, tmpCD_high;

				dot_mult_in32s_out64s_filter(&tmpAB_high, &tmpAB_low, accGradXSqr, accGradYSqr, 1, 1, outStrideLen, outStrideLen);
				dot_sqr_in32s_out64u_filter(&tmpCD_high, &tmpCD_low, accGradXY, 1, 1, outStrideLen, outStrideLen);
				vec32s tmpCD_highS = (vec32s)tmpCD_high;
				difference_filter_in64s_out64s(&accDetG_high, accDetG_inv, &tmpAB_high, &tmpAB_low, &tmpCD_highS, &tmpCD_low, 1, 1, outStrideLen, outStrideLen);


				// Filter out too low eigenvalues:
				// (IxSqr, IySqr, Ixy) >>= 20 in front...of the OpenCV computation
				// Point is not valid if min eigenValue is lower than 0.001 . Min Eigvalue is (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy))/2*bw*bh < 0.001  ==>
				// (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy)) < 0.002*bw*bh ==> (IxSqr + IySqr - c/f)^2 < (IxSqr - IySqr)^2 +4Ixy*Ixy); where c = 2*bw*bh*downscaleFact, f = 1000 ==> 
				// (IxSqr+IySqr)^2 -2*c/f*(IxSqr+IySqr) + (c/f)^2 <  (IxSqr - IySqr)^2 +4Ixy*Ixy ==>  4*IxSqr*IySqr - 2*c/f(IxSqr+IySqr) + (c/f)^2 < 4Ixy*Ixy
				// Point is NOT valid if:
				// c^2 < 2*c*f*(IxSqr+IySqr) +f^2*4(Ixy^2 - IxSqr*IySqr); c = 2*bw*bh*downScaleFact = 2^6*2^20; initial downScaleFactor of IxSqr, IySqr, Ixy is 2^20
				// (c/2f)^2 < (c/2f)*(IxSqr+IySqr) + (Ixy^2 - IxSqr*IySqr)

				// factor f=1000 is close to 1024, ie 2^10, 
				vbool hasCarry;
				vbool getCarry = false;
				vec32u sumGradXSqr_GradYSqr_low = (vec32u)vaddx(*accGradXSqr, *accGradYSqr, getCarry, hasCarry); // this is A
				vec32s sumGradXSqr_GradYSqr_high = vec32s(hasCarry);


				static const int32s upscale = ((inputShiftFact + scharrFiltUpscale / 2) << 1);
				static const int32s downscale = accDownScale, initScale = 19, diffScale = initScale - (downscale - upscale); //10
				const int32u  accumSz = 2 * (bw - ACCUM_MARGIN) * (bh - ACCUM_MARGIN); // 2^7
				static const int32u f = 2000; //2 x 1000
				int32u cnstFact = diffScale > 23 ? accumSz*((1 << diffScale) / f) : (accumSz* (1 << diffScale)) / f;
				int32u cnstSqrLow = 0, cnstSqrHigh = 0;
				if (cnstFact < (1 << 16)) {
					cnstSqrLow = cnstFact*cnstFact; //cnstFact ~2^6=64, cnstSqr ~2^12=4096
				}
				else {
					vec32s cnstVect = (int32s)cnstFact;
					vec32u dstH = 0, dstL = 0;
					dot_sqr_in32s_out64u_filter(&dstH, &dstL, &cnstVect, 1, 1, 1, 1);
					cnstSqrLow = vget(dstL, 0);
					cnstSqrHigh = vget(dstH, 0);
				}

				vbool ThasCarry, TgetCarry = false;
				static const int32u one = 1;
				int32u invCnstFact = ((one << 31) / cnstFact) << 1;
				vec32s TsumEigenHigh = (sumGradXSqr_GradYSqr_high * cnstFact) + (vec32s)(sumGradXSqr_GradYSqr_low / invCnstFact);
				vec32u TsumEigenLow = sumGradXSqr_GradYSqr_low *cnstFact;

				vec32s TdiffEigenLow = (vec32s)vsubx(TsumEigenLow, *accDetG_inv, TgetCarry, ThasCarry);
				vec32s TdiffEigenHigh = (vec32s)vsubx(TsumEigenHigh, accDetG_high, ThasCarry, TgetCarry);
				int32u amplFact = 7;// 1;
				int32u TdiffEigenHighThresh = (cnstSqrHigh << amplFact) + (cnstSqrLow >> (32 - amplFact));
				int32u TdiffEigenLowThresh = (cnstSqrLow << amplFact);

				vec32u absDiffLow = (vec32u)vabs(TdiffEigenLow);
				vec32u absDiffHigh = (vec32u)vabs(TdiffEigenHigh);
				vec16u TaltValid;
				if (TdiffEigenHighThresh == 0) 
					TaltValid = (vec16u)((absDiffLow < TdiffEigenLowThresh) && (TdiffEigenHigh == 0 || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
				else {
					vif(TdiffEigenHighThresh < absDiffHigh && TdiffEigenHigh > 0) {
						TaltValid = (vec16u)false;
					} velse{
						TaltValid = (vec16u)((TdiffEigenHighThresh >= absDiffHigh || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
					} vendif
						//difference_filter_in64u_out64s(&dH, &dL, &TdiffEigenHighThresh, &TdiffEigenLowThresh, &absDiffHigh, &absDiffLow, 1, 1, 1,1);
						//TaltValid = (vec16u)((dH > 0 || (dH == 0 && dL >= 0)) && (accDetG_inv != 0 || accDetG_high != 0));
				}
				*validPts = TaltValid;
			}

			vif(*validPts == true) {
				vec32s absDetGHigh = accDetG_high;
				vec32u absDetGLow = *accDetG_inv;

				vif(absDetGHigh < 0) {
					change64bitSign(absDetGHigh, absDetGLow);
				} vendif

					vec08u log2Fact;
				int32u firstBit0u = 0x7FFFFFFF;
				vif(absDetGHigh > 0 || absDetGLow > firstBit0u) {

					computeLog2(&log2Fact, &absDetGHigh, 1, 1, 1, 1);
					log2Fact++;

					vec32s tmpDetGHigh;
					vec32u tmpDetGLow;
					rsh_in64s_out64s_filter(&tmpDetGHigh, &tmpDetGLow, &accDetG_high, accDetG_inv, &log2Fact, 1, 1, 1, 1);
					accDetG_high = tmpDetGHigh;
					*accDetG_inv = tmpDetGLow;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXSqr, &log2Fact, 1, 1, 1, 1);
					*accGradXSqr = tmpDetGHigh;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradYSqr, &log2Fact, 1, 1, 1, 1);
					*accGradYSqr = tmpDetGHigh;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXY, &log2Fact, 1, 1, 1, 1);
					*accGradXY = tmpDetGHigh;

				} vendif

				vec32s detG32Bit = vec32s(*accDetG_inv), invDetG_Q3_28;
				int08s shiftFact = 3; //compute Q3.28 fixed point representation of the detG inverse
				computeInv_NewtonRaphson(&invDetG_Q3_28, &detG32Bit, &log2Fact, shiftFact, 1, 1, 1, 1);

				*accDetG_inv = vec32u(invDetG_Q3_28);
			} vendif
		}

		accDetG_inv += outStrideLen;
		validPts += outStrideLen;
		accGradXSqr += outStrideLen;
		accGradYSqr += outStrideLen;
		accGradXY += outStrideLen;

		accGradXSqrH += inStrideLen; 
		accGradXSqrL += inStrideLen; 
		accGradYSqrH += inStrideLen; 
		accGradYSqrL += inStrideLen; 
		accGradXYH += inStrideLen; 
		accGradXYL += inStrideLen;

	}

}



void inverse_determinant_filter(vec32s* accGradXSqrH, vec32u* accGradXSqrL,
	vec32s* accGradYSqrH, vec32u* accGradYSqrL, vec32s* accGradXYH, vec32u* accGradXYL,
	vec32s* outAccGradXSqr, vec32s* outAccGradYSqr, vec32s* outAccGradXY,
	vec32u* accDetG_inv, vec16u* validPts,
	int16s bw, int16s bh, int16s inStrideLen, int16s outStrideLen)
{
	int16s offsX = ACCUM_OFFS, offsY = ACCUM_OFFS; // x,y offsets where to start the accumulation

	vec32s *accGradXSqr = outAccGradXSqr, *accGradYSqr = outAccGradYSqr;
	vec32s *accGradXY = outAccGradXY;


	vec08u rshFact = vec08u(accDownScale);
	for (int16s by = 0; by < bh; ++by)  // y data row
	{
		for (int16s bx = 0; bx < bw; ++bx) // x in the blck_tile
		{
			vec32s accDetG_high;

			{
				vec32u dstLowXY;
				{
					//accGradXSqr >> accDownScale, a.s.o
					vec32s dstHighXsqr, dstHighYsqr, dstHighXY;
					vec32u tmpAccGrad;
					rsh_in64s_out64s_filter(&dstHighXsqr, &tmpAccGrad, accGradXSqrH, accGradXSqrL, &rshFact, 1, 1, 1, 1);
					*accGradXSqr = vec32s(tmpAccGrad);
					rsh_in64s_out64s_filter(&dstHighYsqr, &tmpAccGrad, accGradYSqrH, accGradYSqrL, &rshFact, 1, 1, 1, 1);
					*accGradYSqr = vec32s(tmpAccGrad);
					rsh_in64s_out64s_filter(&dstHighXY, &dstLowXY, accGradXYH, accGradXYL, &rshFact, 1, 1, 1, 1);
					*accGradXY = (vec32s)dstLowXY;
					/*
					vif(dstHighXsqr != 0 || dstHighYsqr != 0 || (dstHighXsqr > 0 || (dstHighXsqr < -1) ) ) {
					printf("\nWARNING: Values of detG have more than 32 bits\n");
					} vendif
					*/
				}
#ifdef _DEBUG
				/* just for debugging
				int i = 0;
				long long xSqrTmsYSqr = (long long)vget((*accGradXSqr), i) * (long long)vget((*accGradYSqr), i);
				long long xySqr = (long long) vget((*accGradXY), i) * (long long)vget((*accGradXY), i);
				long long det = xSqrTmsYSqr - xySqr;
				long long sumXSqr_ySqr = (long long)vget((*accGradXSqr), i) + (long long)vget((*accGradYSqr), i);
				long long difEigen = sumXSqr_ySqr - (det >> 17);*/
#endif

				vec32s tmpAB_high;
				vec32u tmpAB_low, tmpCD_low, tmpCD_high;

				dot_mult_in32s_out64s_filter(&tmpAB_high, &tmpAB_low, accGradXSqr, accGradYSqr, 1, 1, outStrideLen, outStrideLen);
				dot_sqr_in32s_out64u_filter(&tmpCD_high, &tmpCD_low, accGradXY, 1, 1, outStrideLen, outStrideLen);
				vec32s tmpCD_highS = (vec32s)tmpCD_high;
				difference_filter_in64s_out64s(&accDetG_high, accDetG_inv, &tmpAB_high, &tmpAB_low, &tmpCD_highS, &tmpCD_low, 1, 1, outStrideLen, outStrideLen);


				// Filter out too low eigenvalues:
				// (IxSqr, IySqr, Ixy) >>= 20 in front...of the OpenCV computation
				// Point is not valid if min eigenValue is lower than 0.001 . Min Eigvalue is (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy))/2*bw*bh < 0.001  ==>
				// (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy)) < 0.002*bw*bh ==> (IxSqr + IySqr - c/f)^2 < (IxSqr - IySqr)^2 +4Ixy*Ixy); where c = 2*bw*bh*downscaleFact, f = 1000 ==> 
				// (IxSqr+IySqr)^2 -2*c/f*(IxSqr+IySqr) + (c/f)^2 <  (IxSqr - IySqr)^2 +4Ixy*Ixy ==>  4*IxSqr*IySqr - 2*c/f(IxSqr+IySqr) + (c/f)^2 < 4Ixy*Ixy
				// Point is NOT valid if:
				// c^2 < 2*c*f*(IxSqr+IySqr) +f^2*4(Ixy^2 - IxSqr*IySqr); c = 2*bw*bh*downScaleFact = 2^6*2^20; initial downScaleFactor of IxSqr, IySqr, Ixy is 2^20
				// (c/2f)^2 < (c/2f)*(IxSqr+IySqr) + (Ixy^2 - IxSqr*IySqr)

				// factor f=1000 is close to 1024, ie 2^10, 
				vbool hasCarry;
				vbool getCarry = false;
				vec32u sumGradXSqr_GradYSqr_low = (vec32u)vaddx(*accGradXSqr, *accGradYSqr, getCarry, hasCarry); // this is A
				vec32s sumGradXSqr_GradYSqr_high = vec32s(hasCarry);


				static const int32s upscale = ((inputShiftFact + scharrFiltUpscale / 2) << 1);
				static const int32s downscale = accDownScale, initScale = 19, diffScale = initScale - (downscale - upscale); //10
				const int32u  accumSz = 2 * (bw - ACCUM_MARGIN) * (bh - ACCUM_MARGIN); // 2^7
				static const int32u f = 2000; //2 x 1000
				int32u cnstFact = diffScale > 23 ? accumSz*((1 << diffScale) / f) : (accumSz* (1 << diffScale)) / f;
				int32u cnstSqrLow = 0, cnstSqrHigh = 0;
				if (cnstFact < (1 << 16)) {
					cnstSqrLow = cnstFact*cnstFact; //cnstFact ~2^6=64, cnstSqr ~2^12=4096
				}
				else {
					vec32s cnstVect = (int32s)cnstFact;
					vec32u dstH = 0, dstL = 0;
					dot_sqr_in32s_out64u_filter(&dstH, &dstL, &cnstVect, 1, 1, 1, 1);
					cnstSqrLow = vget(dstL, 0);
					cnstSqrHigh = vget(dstH, 0);
				}

				vbool ThasCarry, TgetCarry = false;
				static const int32u one = 1;
				int32u invCnstFact = ((one << 31) / cnstFact) << 1;
				vec32s TsumEigenHigh = (sumGradXSqr_GradYSqr_high * cnstFact) + (vec32s)(sumGradXSqr_GradYSqr_low / invCnstFact);
				vec32u TsumEigenLow = sumGradXSqr_GradYSqr_low *cnstFact;

				vec32s TdiffEigenLow = (vec32s)vsubx(TsumEigenLow, *accDetG_inv, TgetCarry, ThasCarry);
				vec32s TdiffEigenHigh = (vec32s)vsubx(TsumEigenHigh, accDetG_high, ThasCarry, TgetCarry);
				int32u amplFact = 7;// 1;
				int32u TdiffEigenHighThresh = (cnstSqrHigh << amplFact) + (cnstSqrLow >> (32 - amplFact));
				int32u TdiffEigenLowThresh = (cnstSqrLow << amplFact);

				vec32u absDiffLow = (vec32u)vabs(TdiffEigenLow);
				vec32u absDiffHigh = (vec32u)vabs(TdiffEigenHigh);
				vec16u TaltValid;
				if (TdiffEigenHighThresh == 0)
					TaltValid = (vec16u)((absDiffLow < TdiffEigenLowThresh) && (TdiffEigenHigh == 0 || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
				else {
					vif(TdiffEigenHighThresh < absDiffHigh && TdiffEigenHigh > 0) {
						TaltValid = (vec16u)false;
					} velse{
						TaltValid = (vec16u)((TdiffEigenHighThresh >= absDiffHigh || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
					} vendif
						//difference_filter_in64u_out64s(&dH, &dL, &TdiffEigenHighThresh, &TdiffEigenLowThresh, &absDiffHigh, &absDiffLow, 1, 1, 1,1);
						//TaltValid = (vec16u)((dH > 0 || (dH == 0 && dL >= 0)) && (accDetG_inv != 0 || accDetG_high != 0));
				}
				*validPts = TaltValid;
			}

			vif(*validPts == true) {
				vec32s absDetGHigh = accDetG_high;
				vec32u absDetGLow = *accDetG_inv;

				vif(absDetGHigh < 0) {
					change64bitSign(absDetGHigh, absDetGLow);
				} vendif

					vec08u log2Fact;
				int32u firstBit0u = 0x7FFFFFFF;
				vif(absDetGHigh > 0 || absDetGLow > firstBit0u) {

					computeLog2(&log2Fact, &absDetGHigh, 1, 1, 1, 1);
					log2Fact++;

					vec32s tmpDetGHigh;
					vec32u tmpDetGLow;
					rsh_in64s_out64s_filter(&tmpDetGHigh, &tmpDetGLow, &accDetG_high, accDetG_inv, &log2Fact, 1, 1, 1, 1);
					accDetG_high = tmpDetGHigh;
					*accDetG_inv = tmpDetGLow;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXSqr, &log2Fact, 1, 1, 1, 1);
					*accGradXSqr = tmpDetGHigh;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradYSqr, &log2Fact, 1, 1, 1, 1);
					*accGradYSqr = tmpDetGHigh;

					rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXY, &log2Fact, 1, 1, 1, 1);
					*accGradXY = tmpDetGHigh;

				} vendif

					vec32s detG32Bit = vec32s(*accDetG_inv), invDetG_Q3_28;
				int08s shiftFact = 3; //compute Q3.28 fixed point representation of the detG inverse
				computeInv_NewtonRaphson(&invDetG_Q3_28, &detG32Bit, &log2Fact, shiftFact, 1, 1, 1, 1);

				*accDetG_inv = vec32u(invDetG_Q3_28);
			} vendif
		}

		accDetG_inv += outStrideLen;
		validPts += outStrideLen;
		accGradXSqr += outStrideLen;
		accGradYSqr += outStrideLen;
		accGradXY += outStrideLen;

		accGradXSqrH += inStrideLen;
		accGradXSqrL += inStrideLen;
		accGradYSqrH += inStrideLen;
		accGradYSqrL += inStrideLen;
		accGradXYH += inStrideLen;
		accGradXYL += inStrideLen;

	}

}





void inverse_det_simple_filter(vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accGradXY
	, vec32u* accDetG_inv, vec16u* validPts, int16s accWidth, int16s accHeight
	, int16s /*bw*/, int16s /*bh*/, int16s /*inStrideLen*/, int16s outStrideLen)
{
	vec32s accDetG_high;
	//for (int j = 0; j < bh; ++j) // bw, bh are typically 1 in this kernel
	//for (int i = 0; i < bw; ++i)
	{

		//*accGradXSqr >>= accDownScale;
#ifdef _DEBUG
		/* just for debugging
		int i = 0;
		long long xSqrTmsYSqr = (long long)vget((*accGradXSqr), i) * (long long)vget((*accGradYSqr), i);
		long long xySqr = (long long) vget((*accGradXY), i) * (long long)vget((*accGradXY), i);
		long long det = xSqrTmsYSqr - xySqr;
		long long sumXSqr_ySqr = (long long)vget((*accGradXSqr), i) + (long long)vget((*accGradYSqr), i);
		long long difEigen = sumXSqr_ySqr - (det >> 17);*/
#endif

		vec32u tmpAB_high, tmpCD_high;
		vec32u tmpAB_low, tmpCD_low;

		dot_mult_in32u_out64u_filter(&tmpAB_high, &tmpAB_low, accGradXSqr, accGradYSqr, 1, 1, outStrideLen, outStrideLen);
		dot_sqr_in32s_out64u_filter(&tmpCD_high, &tmpCD_low, accGradXY, 1, 1, outStrideLen, outStrideLen);

		difference_filter_in64u_out64s(&accDetG_high, accDetG_inv, &tmpAB_high, &tmpAB_low, &tmpCD_high, &tmpCD_low, 1, 1, outStrideLen, outStrideLen);


		// Filter out too low eigenvalues:
		// (IxSqr, IySqr, Ixy) >>= 20 in front...of the OpenCV computation
		// Point is not valid if min eigenValue is lower than 0.001 . Min Eigvalue is (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy))/2*bw*bh < 0.001  ==>
		// (IxSqr + IySqr - sqrt((IxSqr - IySqr)^2 +4Ixy*Ixy)) < 0.002*bw*bh ==> (IxSqr + IySqr - c/f)^2 < (IxSqr - IySqr)^2 +4Ixy*Ixy); where c = 2*bw*bh*downscaleFact, f = 1000 ==> 
		// (IxSqr+IySqr)^2 -2*c/f*(IxSqr+IySqr) + (c/f)^2 <  (IxSqr - IySqr)^2 +4Ixy*Ixy ==>  4*IxSqr*IySqr - 2*c/f(IxSqr+IySqr) + (c/f)^2 < 4Ixy*Ixy
		// Point is NOT valid if:
		// c^2 < 2*c*f*(IxSqr+IySqr) +f^2*4(Ixy^2 - IxSqr*IySqr); c = 2*bw*bh*downScaleFact = 2^6*2^20; initial downScaleFactor of IxSqr, IySqr, Ixy is 2^20
		// (c/2f)^2 < (c/2f)*(IxSqr+IySqr) + (Ixy^2 - IxSqr*IySqr)

		// factor f=1000 is close to 1024, ie 2^10, 
		vbool hasCarry;
		vbool getCarry = false;
		vec32u sumGradXSqr_GradYSqr_low = (vec32u)vaddx(*accGradXSqr, *accGradYSqr, getCarry, hasCarry); // this is A
		vec32s sumGradXSqr_GradYSqr_high = vec32s(hasCarry);


		static const int32s upscale = ((inputShiftFact + scharrFiltUpscale / 2) << 1);
		static const int32s downscale = accDownScale, initScale = 19, diffScale = initScale - (downscale - upscale); //10
		const int32u  accumSz = 2 * (accWidth - ACCUM_MARGIN) * (accHeight - ACCUM_MARGIN); // ~= 2^7
		static const int32u f = 2000; //2 x 1000
		int32u cnstFact = diffScale > 23 ? accumSz*((1 << diffScale) / f) : (accumSz* (1 << diffScale)) / f;
		int32u cnstSqrLow = 0, cnstSqrHigh = 0;
		if (cnstFact < (1 << 16)) {
			cnstSqrLow = cnstFact*cnstFact; //cnstFact ~2^6=64, cnstSqr ~2^12=4096
		}
		else {
			vec32s cnstVect = (int32s)cnstFact;
			vec32u dstH = 0, dstL = 0;
			dot_sqr_in32s_out64u_filter(&dstH, &dstL, &cnstVect, 1, 1, 1, 1);
			cnstSqrLow = vget(dstL, 0);
			cnstSqrHigh = vget(dstH, 0);
		}

		vbool ThasCarry, TgetCarry = false;
		static const int32u one = 1;
		int32u invCnstFact = ((one << 31) / cnstFact) << 1;
		vec32s TsumEigenHigh = (sumGradXSqr_GradYSqr_high * cnstFact) + (vec32s)(sumGradXSqr_GradYSqr_low / invCnstFact);
		vec32u TsumEigenLow = sumGradXSqr_GradYSqr_low *cnstFact;

		vec32s TdiffEigenLow = (vec32s)vsubx(TsumEigenLow, *accDetG_inv, TgetCarry, ThasCarry);
		vec32s TdiffEigenHigh = (vec32s)vsubx(TsumEigenHigh, accDetG_high, ThasCarry, TgetCarry);
		int32u amplFact = 3;//2 // 1;
		int32u TdiffEigenHighThresh = (cnstSqrHigh << amplFact) + (cnstSqrLow >> (32 - amplFact));
		int32u TdiffEigenLowThresh = (cnstSqrLow << amplFact);

		vec32u absDiffLow = (vec32u)vabs(TdiffEigenLow);
		vec32u absDiffHigh = (vec32u)vabs(TdiffEigenHigh);
		vec16u TaltValid;
		if (TdiffEigenHighThresh == 0)
			TaltValid = (vec16u)((absDiffLow < TdiffEigenLowThresh) && (TdiffEigenHigh == 0 || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
		else {
			vif(TdiffEigenHighThresh < absDiffHigh && TdiffEigenHigh > 0) {
				TaltValid = (vec16u)false;
			} velse{
				TaltValid = (vec16u)((TdiffEigenHighThresh >= absDiffHigh || TdiffEigenHigh == -1) && (*accDetG_inv != 0 || accDetG_high != 0));
			} vendif
				//difference_filter_in64u_out64s(&dH, &dL, &TdiffEigenHighThresh, &TdiffEigenLowThresh, &absDiffHigh, &absDiffLow, 1, 1, 1,1);
				//TaltValid = (vec16u)((dH > 0 || (dH == 0 && dL >= 0)) && (accDetG_inv != 0 || accDetG_high != 0));
		}
		*validPts = TaltValid;
	}

	vif(*validPts == true) {
		vec32s absDetGHigh = accDetG_high;
		vec32u absDetGLow = *accDetG_inv;

		vif(absDetGHigh < 0) {
			change64bitSign(absDetGHigh, absDetGLow);
		} vendif

			vec08u log2Fact;
		int32u firstBit0u = 0x7FFFFFFF;
		vif(absDetGHigh > 0 || absDetGLow > firstBit0u) {

			computeLog2(&log2Fact, &absDetGHigh, 1, 1, 1, 1);
			log2Fact++;

			vec32s tmpDetGHigh;
			vec32u tmpDetGLow;
			rsh_in64s_out64s_filter(&tmpDetGHigh, &tmpDetGLow, &accDetG_high, accDetG_inv, &log2Fact, 1, 1, 1, 1);
			accDetG_high = tmpDetGHigh;
			*accDetG_inv = tmpDetGLow;

			rsh_in32u_out32u_filter(&tmpDetGLow, accGradXSqr, &log2Fact, 1, 1, 1, 1);
			*accGradXSqr = tmpDetGLow;

			rsh_in32u_out32u_filter(&tmpDetGLow, accGradYSqr, &log2Fact, 1, 1, 1, 1);
			*accGradYSqr = tmpDetGLow;

			rsh_in32s_out32s_filter(&tmpDetGHigh, accGradXY, &log2Fact, 1, 1, 1, 1);
			*accGradXY = tmpDetGHigh;

		} vendif

			vec32s detG32Bit = vec32s(*accDetG_inv), invDetG_Q3_28;
		int08s shiftFact = 3; //compute Q3.28 fixed point representation of the detG inverse
		computeInv_NewtonRaphson(&invDetG_Q3_28, &detG32Bit, &log2Fact, shiftFact, 1, 1, 1, 1);

		*accDetG_inv = vec32u(invDetG_Q3_28);
	} vendif
}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
