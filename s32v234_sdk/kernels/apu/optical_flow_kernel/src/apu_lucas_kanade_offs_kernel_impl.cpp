
#ifdef ACF_KERNEL_IMPLEMENTATION


//#include "apu_add_impl.h"
#include "apu_lucas_kanade_offs_kernel_impl.h"
#include "apu_dot_multiplic_kernel_impl.h"
#include "apu_difference_kernel_impl.h"


/*

static
vec32s performDivisionInBounds_GoutOfBounds(vec32s& absTmpEtaX, vec32s& etaX, vec32s& tmpDetG, 
		vec32s& maxValToScale, vec32s& negMaxValToScale, vec32s& overflowExp, vec32s& maxVal, 
		vbool& xterm1OutBds, vbool& xterm2OutBds)
{
	vec32s tmpEtaX = etaX;

	// DetG was out of bounds
	vif(tmpDetG != 0) {	
		vif(xterm1OutBds || xterm2OutBds) { //nominator was also out of bounds ==> both were scaled
			tmpEtaX /= tmpDetG;		
		} velse{ //only detG is out of bounds		
			vif(absTmpEtaX < maxValToScale) {
				tmpEtaX = (tmpEtaX << overflowExp) / tmpDetG;
			} velse{
				tmpEtaX = (tmpEtaX / tmpDetG);
				//vec32s ax;
				//vabs(tmpEtaX, ax);
				vif(tmpEtaX < maxValToScale && tmpEtaX > negMaxValToScale) {
					tmpEtaX <<= overflowExp;
				} velse{		
					tmpEtaX = 0;
					/*
					vif(ax == tmpEtaX) {
						tmpEtaX = maxVal;
					} velse{
						tmpEtaX = -maxVal;
					}vendif
					* /
				} vendif
			} vendif
		}vendif 	
	} velse{// some detGs are zero
		tmpEtaX = 0;
		/*
		vif(tmpEtaX != 0) { //if value cannot be scaled to its real value, then scale it to the max value and avoid overflow
			vif(absTmpEtaX == tmpEtaX) {
				tmpEtaX = maxVal;
			} velse{
				tmpEtaX = -maxVal;
			}vendif
		} vendif
		* /
	} vendif
	return tmpEtaX;
}

static
vec32s performDivisionInBounds_GinBounds(vec32s& absTmpEtaX, vec32s& etaX, 
		vec32s& tmpDetG, vec32s& absTmpDetG, vec32s& maxValToScale, vec32s& negMaxValToScale,
		vec32s& overflowExp, vec32s& maxVal, vbool& xterm1OutBds, vbool& xterm2OutBds)
{
	vec32s tmpEtaX = etaX;

	vif(tmpDetG != 0) {
		vif(xterm1OutBds || xterm2OutBds) { //nominator was out of bounds 
			vif(absTmpDetG < maxValToScale) {
				tmpEtaX = tmpEtaX / (tmpDetG << overflowExp);
			} velse{
				tmpEtaX = (tmpEtaX / tmpDetG);
				//vec32s ax;
				//vabs(tmpEtaX, ax);
				vif(tmpEtaX < maxValToScale && tmpEtaX > negMaxValToScale) {
					tmpEtaX <<= overflowExp;
				}velse{
					tmpEtaX = 0;
					/*
					// assign either pos or neg. max value
					vif(ax == tmpEtaX) {
						tmpEtaX = maxVal; 
					} velse{
						tmpEtaX = -maxVal;
					}vendif
					* /
				} vendif
			}
			vendif
		} velse{
			tmpEtaX /= tmpDetG;
		}
		vendif
	} velse{ //some detGs are zero
		tmpEtaX = 0;
		/*
		vif(tmpEtaX != 0) {
			vif(absTmpEtaX == tmpEtaX) {
				tmpEtaX = maxVal;
			} velse{
				tmpEtaX = -maxVal;
			}vendif
		} vendif
		* /
	} vendif

	return tmpEtaX;
}
*/

#ifndef accDownScale
#define accDownScale 6
#endif


void lucas_kanade_offset_filter(vec32s* gOutX_high, vec32u* gOutX_low, vec32s* gOutY_high, vec32u* gOutY_low, vec32s* etaX, vec32s* etaY, vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accgradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen)
{
	//vec32u downaccGradXSqr;
	//vec32u downaccGradYSqr;
	//vec32s downaccgradXgradY;

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];

			vec32s accGradXSqrV = (vec32s)accGradXSqr[j];
			vec32s accGradYSqrV = (vec32s)accGradYSqr[j];
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
			//rsh_in32u_filter(&downGradXSqr, gradXSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32u_filter(&downaccGradYSqr, accGradYSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32s_filter(&downaccgradXgradY, accgradXYv, accDownScale, strideLen, 1, 1);
			//vec32s signedDownX = (vec32s)downGradXSqr;
			//vec32s signedDownY = (vec32s)downaccGradYSqr;


			dot_mult_in32s_filter(&tmpEtaX_t1_high, &tmpEtaX_t1_low, etaXv, &accGradYSqrV, 1, 1, 1, 1);
			dot_mult_in32s_filter(&tmpEtaX_t2_high, &tmpEtaX_t2_low, etaYv, accgradXYv, 1, 1, 1, 1);

			dot_mult_in32s_filter(&tmpEtaY_t1_high, &tmpEtaY_t1_low, etaYv, &accGradXSqrV, 1, 1, 1, 1);
			dot_mult_in32s_filter(&tmpEtaY_t2_high, &tmpEtaY_t2_low, etaXv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in_out64s(gOutX_high, gOutX_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, 1, 1, 1, 1);
			difference_filter_in_out64s(gOutY_high, gOutY_low, &tmpEtaY_t1_high, &tmpEtaY_t1_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, 1, 1, 1, 1);
			//difference_filter_in_out64s(gOutX_high, gOutX_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, 1, 1, strideLen);
			//difference_filter_in_out64s(gOutY_high, gOutY_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, &tmpEtaY_t1_high, &tmpEtaY_t1_low, 1, 1, strideLen);
		}

		accGradXSqr += inStrideLen;
		accGradYSqr += inStrideLen;
		accgradXgradY += inStrideLen;


		gOutX_high += outStrideLen;
		gOutY_high += outStrideLen;
		gOutX_low += outStrideLen;
		gOutY_low += outStrideLen;

	} // for all i < bh


} // end of kernel



void lucas_kanade_offset_filter_x(vec32s* gOutX_high, vec32u* gOutX_low, vec32s* etaX, vec32s* etaY, vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accgradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen)
{
	//vec32u downaccGradXSqr;
	//vec32u downaccGradYSqr;
	//vec32s downaccgradXgradY;

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];

			vec32s accGradXSqrV = (vec32s)accGradXSqr[j];
			vec32s accGradYSqrV = (vec32s)accGradYSqr[j];
			vec32s* accgradXYv = &accgradXgradY[j];
			gOutX_high[j] = 0;
			gOutX_low[j] = 0;

			vec32s tmpEtaX_t1_high;
			vec32u tmpEtaX_t1_low;

			vec32s tmpEtaX_t2_high;
			vec32u tmpEtaX_t2_low;

			//rsh_in32u_filter(&downGradXSqr, gradXSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32u_filter(&downaccGradYSqr, accGradYSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32s_filter(&downaccgradXgradY, accgradXYv, accDownScale, strideLen, 1, 1);
			//vec32s signedDownX = (vec32s)downGradXSqr;
			//vec32s signedDownY = (vec32s)downaccGradYSqr;


			dot_mult_in32s_filter(&tmpEtaX_t1_high, &tmpEtaX_t1_low, etaXv, &accGradYSqrV, 1, 1, 1, 1);
			dot_mult_in32s_filter(&tmpEtaX_t2_high, &tmpEtaX_t2_low, etaYv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in_out64s(gOutX_high, gOutX_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, 1, 1, 1, 1);
			//difference_filter_in_out64s(gOutX_high, gOutX_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, 1, 1, strideLen);
			//difference_filter_in_out64s(gOutY_high, gOutY_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, &tmpEtaY_t1_high, &tmpEtaY_t1_low, 1, 1, strideLen);
		}

		accGradXSqr += inStrideLen;
		accGradYSqr += inStrideLen;
		accgradXgradY += inStrideLen;


		gOutX_high += outStrideLen;
		gOutX_low += outStrideLen;

	} // for all i < bh


} // end of kernel


void lucas_kanade_offset_filter_y(vec32s* gOutY_high, vec32u* gOutY_low, vec32s* etaX, vec32s* etaY, vec32u* accGradXSqr, vec32u* accGradYSqr, vec32s* accgradXgradY, int16s inStrideLen, int16s bw, int16s bh, int16s outStrideLen)
{
	//vec32u downaccGradXSqr;
	//vec32u downaccGradYSqr;
	//vec32s downaccgradXgradY;

	for (int16s i = 0; i < bh; ++i) {

		for (int16s j = 0; j < bw; ++j) {
			vec32s* etaXv = &etaX[j];
			vec32s* etaYv = &etaY[j];

			vec32s accGradXSqrV = (vec32s)accGradXSqr[j];
			vec32s accGradYSqrV = (vec32s)accGradYSqr[j];
			vec32s* accgradXYv = &accgradXgradY[j];
			gOutY_high[j] = 0;
			gOutY_low[j] = 0;


			vec32s tmpEtaY_t1_high;
			vec32u tmpEtaY_t1_low;

			vec32s tmpEtaY_t2_high;
			vec32u tmpEtaY_t2_low;
			//rsh_in32u_filter(&downGradXSqr, gradXSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32u_filter(&downaccGradYSqr, accGradYSqrV, accDownScale, strideLen, 1, 1);
			//rsh_in32s_filter(&downaccgradXgradY, accgradXYv, accDownScale, strideLen, 1, 1);
			//vec32s signedDownX = (vec32s)downGradXSqr;
			//vec32s signedDownY = (vec32s)downaccGradYSqr;

			dot_mult_in32s_filter(&tmpEtaY_t1_high, &tmpEtaY_t1_low, etaYv, &accGradXSqrV, 1, 1, 1, 1);
			dot_mult_in32s_filter(&tmpEtaY_t2_high, &tmpEtaY_t2_low, etaXv, accgradXYv, 1, 1, 1, 1);

			difference_filter_in_out64s(gOutY_high, gOutY_low, &tmpEtaY_t1_high, &tmpEtaY_t1_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, 1, 1, 1, 1);
			//difference_filter_in_out64s(gOutX_high, gOutX_low, &tmpEtaX_t2_high, &tmpEtaX_t2_low, &tmpEtaX_t1_high, &tmpEtaX_t1_low, 1, 1, strideLen);
			//difference_filter_in_out64s(gOutY_high, gOutY_low, &tmpEtaY_t2_high, &tmpEtaY_t2_low, &tmpEtaY_t1_high, &tmpEtaY_t1_low, 1, 1, strideLen);
		}

		accGradXSqr += inStrideLen;
		accGradYSqr += inStrideLen;
		accgradXgradY += inStrideLen;


		gOutY_high += outStrideLen;
		gOutY_low += outStrideLen;

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

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
