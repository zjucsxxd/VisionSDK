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
* \file apu_sat_box_filter_impl.c
* \brief sat_box_filter implementation for APEX
* \author Igor Aleksandrowicz
* \version
* \date
****************************************************************************/
#ifdef ACF_KERNEL_IMPLEMENTATION


#include "apu_sat_box_filter_impl.h"
#include "apu_add_impl.h"
#include "apu_difference_kernel_impl.h"

/*****************************************************************************
* functions
*****************************************************************************/
#ifdef APEX2_EMULATE
extern const int BOX_SIZE;// = 5;
extern const int BOX_AREA;// = (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);
#else
const int BOX_SIZE = 5;
const int BOX_AREA = (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);
#endif

void sat_box_filter_impl(vec08u* apDest,
	const vec32u* apcSrc,
	int aBlockWidth, int aBlockHeight,
	int aSourceStride, int aDestStride)
{
	int int32SourceStride = aSourceStride >> 2;
	for (int y = 0; y < aBlockHeight; ++y)
	{
		for (int x = 0; x < aBlockWidth; ++x)
		{
			vec32u vLeftTop = apcSrc[x - (BOX_SIZE + 1) - (BOX_SIZE + 1) * int32SourceStride];
			vec32u vRgtTop = apcSrc[x + BOX_SIZE - (BOX_SIZE + 1) * int32SourceStride];
			vec32u vLeftBot = apcSrc[x - (BOX_SIZE + 1) + BOX_SIZE * int32SourceStride];
			vec32u vRgtBot = apcSrc[x + BOX_SIZE + BOX_SIZE * int32SourceStride];
			vec32u v = (vRgtBot + vLeftTop - vRgtTop - vLeftBot) / BOX_AREA;
			vif(v > 255)
			{
				v = 255;
			}
			vendif;
			apDest[x] = vec08u(v);
		}

		apcSrc += int32SourceStride;
		apDest += aDestStride;
	}
}



/*
void sat_box_filter_64u_selectedPoints(int32u* apDestHigh, int32u* apDestLow, 
	const vec32u* apcSrcHigh, const vec32u* apcSrcLow, //int16u nrCUs,
	int32s* offsetsX, int32s* offsetsY, 
	int32u nrOffsets, int16u crtStartRow, int32u& idxFirstCell,
	int inBlockWidth, int inBlockHeight, int outCellWidth, int outCellHeight,
	int aSourceStride, int aDestStride)
{
	//int32u outWidth = nrCUs * outCellWidth;

	int16u crtEndRow = crtStartRow + inBlockHeight;

	int int32SourceStride = aSourceStride >> 2;
	int int32DestStride = aDestStride >> 2;
	//int boxArea = outCellWidth * outCellHeight;

	for (int i = idxFirstCell; i < nrOffsets; i++)
	{ 
		int32s crtX = offsetsX[i], endX = crtX + outCellWidth;
		int32s crtY = offsetsY[i], endY = crtY + outCellHeight;


		if (crtY >= crtEndRow || endY < crtStartRow)
		{
			//offset is outside this tile
			if (endY < crtStartRow) {
				idxFirstCell = i + 1;
				continue;
			}
			else
			if (crtY > crtEndRow) {
				break;
			}
		}

		int xInCuLeft = crtX % inBlockWidth, xInCuRight = endX % inBlockWidth;
		int nrCuLeft = crtX / inBlockWidth, nrCuRight = endX / inBlockWidth;

		/*
		int16u destX = (i % outWidth) % outCellWidth, destY = i / outWidth;// , nrDestCU = i / outCellWidth;
		int32u *destVect_Low = apDestLow + outWidth * destY;
		int32u *destVect_High = apDestHigh + outWidth * destY;
		* /
		int16u destX = (i % int32DestStride), destY = i / int32DestStride;// , nrDestCU = i / outCellWidth;
		int32u *destVect_Low = apDestLow + int32DestStride * destY;
		int32u *destVect_High = apDestHigh + int32DestStride * destY;

		//vec32u destVal_low = vec32u( vget(destVect_Low[destX], nrDestCU) );
		//vec32s destVal_high = vec32s( vget(destVect_High[destX], nrDestCU) );

		vec32u destVal_low = vec32u(destVect_Low[destX]);
		vec32s destVal_high = vec32s( destVect_High[destX]);

		//v = (vRgtBot + vLeftTop - vRgtTop - vLeftBot) / BOX_64_AREA;
		if (crtY >= crtStartRow ) { // top row is inside this tile
			int16s cellY = crtY - crtStartRow;
			vec32u vLeftTop_Hi = apcSrcHigh[xInCuLeft + cellY * int32SourceStride];
			vec32u vRgtTop_Hi = apcSrcHigh[xInCuRight + cellY * int32SourceStride];

			vec32u vLeftTop_Low = apcSrcLow[xInCuLeft + cellY * int32SourceStride];
			vec32u vRgtTop_Low = apcSrcLow[xInCuRight + cellY * int32SourceStride];
			
			vec32s vLeftTop_Hi_val = vec32s( vget(vLeftTop_Hi, nrCuLeft) );
			vec32u vLeftTop_Low_val = vec32u( vget(vLeftTop_Low, nrCuLeft) );

			vec32s vRgtTop_Hi_val = vec32s( vget(vRgtTop_Hi, nrCuRight) );
			vec32u vRgtTop_Low_val = vec32u( vget(vRgtTop_Low, nrCuRight) );

			vec32s resHigh;
			vec32u resLow;
			add_in64s_out64s(&resHigh, &resLow, &vLeftTop_Hi_val, &vLeftTop_Low_val, &destVal_high, &destVal_low, 1, 1, 1, 1);

			vec32s diffHigh;
			vec32u diffLow;
			difference_filter_in64s_out64s(&diffHigh, &diffLow, &resHigh, &resLow, &vRgtTop_Hi_val, &vRgtTop_Low_val, 1, 1, 1, 1);

			destVal_low = diffLow;
			destVal_high = diffHigh;
		}

		if ( endY < crtEndRow) {
			idxFirstCell = i;
			int16s cellY = endY - crtStartRow;

			vec32u vLeftBot_Hi = apcSrcHigh[xInCuLeft + cellY *int32SourceStride];
			vec32u vRgtBot_Hi = apcSrcHigh[xInCuRight + cellY *int32SourceStride];

			vec32u vLeftBot_Low = apcSrcLow[xInCuLeft + cellY *int32SourceStride];
			vec32u vRgtBot_Low = apcSrcLow[xInCuRight + cellY *int32SourceStride];

			vec32s vLeftBot_Hi_val = vec32s(vget(vLeftBot_Hi, nrCuLeft));
			vec32u vLeftBot_Low_val = vec32u(vget(vLeftBot_Low, nrCuLeft));

			vec32s vRgtBot_Hi_val = vec32s(vget(vRgtBot_Hi, nrCuRight));
			vec32u vRgtBot_Low_val = vec32u(vget(vRgtBot_Low, nrCuRight));

			
			vec32s resHigh;
			vec32u resLow;
			add_in64s_out64s(&resHigh, &resLow, &vRgtBot_Hi_val, &vRgtBot_Low_val, &destVal_high, &destVal_low, 1, 1, 1, 1);

			vec32s diffHigh;
			vec32u diffLow;
			difference_filter_in64s_out64s(&diffHigh, &diffLow, &resHigh, &resLow, &vLeftBot_Hi_val, &vLeftBot_Low_val, 1, 1, 1, 1);

			destVal_low = diffLow;
			destVal_high = diffHigh;
		}

		int32u destVal;
		destVal = vget(destVal_low, 0);
		destVect_Low[destX] =  destVal;
		destVal = vget(destVal_high, 0);
		destVect_High[destX] = destVal;
		
	}
}
*/

/*
void sat_box_filter_64s_selectedPoints(int32s* apDestHigh, int32u* apDestLow,
		const vec32s* apcSrcHigh, const vec32u* apcSrcLow, //int16u nrCUs,
		int32u* offsetsX, int32u* offsetsY, int32u nrOffsets, 
		int16u crtStartRow, int32u& idxFirstCell,
		int inBlockWidth, int inBlockHeight, int outCellWidth, int outCellHeight,
		int aSourceStride, int aDestStride)
{
	//int32u outWidth = nrCUs * outCellWidth;

	int16u crtEndRow = crtStartRow + inBlockHeight;

	int int32SourceStride = aSourceStride >> 2;
	int int32DestStride = aDestStride >> 2;

	--outCellWidth; // for having the real idx of the endX and endY
	--outCellHeight;

	for (int i = idxFirstCell; i < nrOffsets; i++)
	{
		int32s crtX = offsetsX[i], endX = crtX + outCellWidth;
		int32s crtY = offsetsY[i], endY = crtY + outCellHeight;
		crtX = crtX < 0 ? 0 : crtX;

		int32s xInCuLeft = crtX % inBlockWidth, xInCuRight = endX % inBlockWidth;
		int32s nrCuLeft = crtX / inBlockWidth, nrCuRight = endX / inBlockWidth;


		if (crtY >= crtEndRow || endY < crtStartRow || endX < 0	|| nrCuLeft >= APU_VSIZE)
		{
			//offset is outside this tile
			if (endY < crtStartRow) {
				idxFirstCell = i + 1;
				continue;
			} else
			if (crtY > crtEndRow) {
				break;
			}
		}

		if (nrCuRight >= APU_VSIZE) {
			endX = outCellWidth;
			nrCuRight = APU_VSIZE - 1;
		}

		//int16u destX = (i % outWidth) % outCellWidth, destY = i / outWidth, nrDestCU = i / outCellWidth;
		//vec32u *destVect_Low = apDestLow + outWidth * destY;
		//vec32s *destVect_High = apDestHigh + outWidth * destY;
		int16u destX = (i % int32DestStride), destY = i / int32DestStride;// , nrDestCU = i / outCellWidth;
		int32u *destVect_Low = apDestLow + int32DestStride * destY;
		int32s *destVect_High = apDestHigh + int32DestStride * destY;

		vec32u destVal_low = vec32u(destVect_Low[destX]);//vec32u(vget(destVect_Low[destX], nrDestCU));
		vec32s destVal_high = vec32s(destVect_High[destX]);//vec32s(vget(destVect_High[destX], nrDestCU));

		//v = (vRgtBot + vLeftTop - vRgtTop - vLeftBot) / BOX_64_AREA;
		if (crtY >= crtStartRow) { // top row is inside this tile
			int16s cellY = crtY - crtStartRow;
			vec32s vLeftTop_Hi = apcSrcHigh[xInCuLeft + cellY * int32SourceStride];
			vec32s vRgtTop_Hi = apcSrcHigh[xInCuRight + cellY * int32SourceStride];

			vec32u vLeftTop_Low = apcSrcLow[xInCuLeft + cellY * int32SourceStride];
			vec32u vRgtTop_Low = apcSrcLow[xInCuRight + cellY * int32SourceStride];

			vec32s vLeftTop_Hi_val = vec32s(vget(vLeftTop_Hi, nrCuLeft));
			vec32u vLeftTop_Low_val = vec32u(vget(vLeftTop_Low, nrCuLeft));

			vec32s vRgtTop_Hi_val = vec32s(vget(vRgtTop_Hi, nrCuRight));
			vec32u vRgtTop_Low_val = vec32u(vget(vRgtTop_Low, nrCuRight));

			vec32s resHigh;
			vec32u resLow;
			add_in64s_out64s(&resHigh, &resLow, &vLeftTop_Hi_val, &vLeftTop_Low_val, &destVal_high, &destVal_low, 1, 1, 1, 1);

			vec32s diffHigh;
			vec32u diffLow;
			difference_filter_in64s_out64s(&diffHigh, &diffLow, &resHigh, &resLow, &vRgtTop_Hi_val, &vRgtTop_Low_val, 1, 1, 1, 1);

			destVal_low = diffLow;
			destVal_high = diffHigh;
		}

		if (endY < crtEndRow) {
			idxFirstCell = i+1;
			int16s cellY = endY - crtStartRow;

			vec32u vLeftBot_Hi = apcSrcHigh[xInCuLeft + cellY *int32SourceStride];
			vec32u vRgtBot_Hi = apcSrcHigh[xInCuRight + cellY *int32SourceStride];

			vec32u vLeftBot_Low = apcSrcLow[xInCuLeft + cellY *int32SourceStride];
			vec32u vRgtBot_Low = apcSrcLow[xInCuRight + cellY *int32SourceStride];

			vec32s vLeftBot_Hi_val = vec32s(vget(vLeftBot_Hi, nrCuLeft));
			vec32u vLeftBot_Low_val = vec32u(vget(vLeftBot_Low, nrCuLeft));

			vec32s vRgtBot_Hi_val = vec32s(vget(vRgtBot_Hi, nrCuRight));
			vec32u vRgtBot_Low_val = vec32u(vget(vRgtBot_Low, nrCuRight));


			vec32s resHigh;
			vec32u resLow;
			add_in64s_out64s(&resHigh, &resLow, &vRgtBot_Hi_val, &vRgtBot_Low_val, &destVal_high, &destVal_low, 1, 1, 1, 1);

			vec32s diffHigh;
			vec32u diffLow;
			difference_filter_in64s_out64s(&diffHigh, &diffLow, &resHigh, &resLow, &vLeftBot_Hi_val, &vLeftBot_Low_val, 1, 1, 1, 1);

			destVal_low = diffLow;
			destVal_high = diffHigh;
		}

		int32u destVal;
		destVal = vget(destVal_low, 0);
		destVect_Low[destX] = destVal;

		int32s destVals = vget(destVal_high, 0);
		destVect_High[destX] = destVals;

	}
}
*/



void sat_box_filterParal_64s_selectedPoints(int32s* apDestHigh, int32u* apDestLow,
	const vec32s* apcSrcHigh, const vec32u* apcSrcLow, int16u nrCUs,
	int32s* offsetsX, int32s* offsetsY, int32u nrOffsets, int16u crtStartRow, int32u& idxFirstCell,
	int08u* ltmpDone,
	int32s inBlockWidth, int32s inBlockHeight, int32s outCellWidth, int32s outCellHeight,
	int32s aSourceStride, int32s /*aDestStride*/)
{
	int32u imgWidth = nrCUs * outCellWidth;

	int16s crtStRow = (int16s)crtStartRow;
	int16s crtEndRow = crtStRow + inBlockHeight;

	int32s int32SourceStride = aSourceStride >> 2;

	--outCellWidth; // for having the real idx of the endX and endY
	--outCellHeight;

	vec16s offsetVectLeftTop, offsetVectRightTop;
	vec16s offsetVectLeftBot, offsetVectRightBot;
	vec16s shiftLeftTop, shiftLeftBot;

	vec32s idxArrTop, idxArrBot;
	vec32u destVal_low_top, destVal_low_bot; 
	vec32s destVal_high_top, destVal_high_bot;
	vec32u destVal_lowTmp; // to keep temporarily already computed values from former chunks
	vec32s destVal_highTmp;// to keep temporarily already computed values from former chunks


	bool somethingToDo = false;

    int crtIdxFirstCell = idxFirstCell;

	do {
		somethingToDo = false;

		offsetVectLeftTop = -1; offsetVectRightTop = -1;
		offsetVectLeftBot = -1; offsetVectRightBot = -1;
		shiftLeftTop = 0; shiftLeftBot = 0;
		idxArrTop = -1; idxArrBot = -1;

		destVal_low_top = 0;
		destVal_high_top = 0;
		destVal_low_bot = 0;
		destVal_high_bot = 0;
		destVal_lowTmp = 0;
		destVal_highTmp = 0;



		// repeat this, as long as there are still some offsets gathered for this chunk
		for (int32u i = crtIdxFirstCell; i < nrOffsets; i++)
		{
			// for all offsets inside this chunk, gather the chunk offsets in the corresponding CU's

			int32s crtX = offsetsX[i], endX = crtX + outCellWidth;
			int32s crtY = offsetsY[i], endY = crtY + outCellHeight;

			if (crtY >= crtEndRow || endY < crtStRow)
			{
				if (endY < crtStRow) {
					//offset is outside this tile (before it, thus move forward with the index)
					if (idxFirstCell == i) {
						++idxFirstCell;
					}

					if (crtIdxFirstCell == i) {
						++crtIdxFirstCell;
					}
					continue;
				}
				else
				if (crtY >= crtEndRow) {
					break;
				}
			}

			if (endX < 0 || crtX > (int32s)imgWidth) {
				continue;
			}

			crtX = crtX > 0 ? crtX : 0;
			endX = endX < (int32s)imgWidth ? endX : ((int32s)imgWidth - 1);
			//endY = endY < imgHeight ? endY : (imgHeight - 1);

			int32s xInCuLeft = crtX % inBlockWidth, xInCuRight = endX % inBlockWidth;
			int32s nrCuLeft = crtX / inBlockWidth, nrCuRight = endX / inBlockWidth;

				
			if (crtY >= crtStRow) {
				int val = apDestLow[i];
				if (val != 0) {
					if (crtIdxFirstCell == i && endY >= crtEndRow){
						++crtIdxFirstCell;
					}
				}
				else  {

					int16s crtOffsLeftTop = vget(offsetVectLeftTop, nrCuLeft);
					int16s crtOffsRightTop = vget(offsetVectRightTop, nrCuRight);

					int32s yTopOffs = (crtY - crtStRow) * int32SourceStride;
					if (crtOffsLeftTop < 0 && crtOffsRightTop < 0) {
						offsetVectLeftTop = vput(offsetVectLeftTop, int16s(xInCuLeft + yTopOffs), nrCuLeft);
						offsetVectRightTop = vput(offsetVectRightTop, int16s(xInCuRight + yTopOffs), nrCuRight);
						shiftLeftTop = vput(shiftLeftTop, int16s(nrCuRight - nrCuLeft), nrCuLeft);

						idxArrTop = vput(idxArrTop, int32s(i), nrCuLeft);
						somethingToDo = true;

						if (crtIdxFirstCell == i) {
							++crtIdxFirstCell;
						}
					}
				}
			}


			if (endY < crtEndRow) {
				unsigned char lastIdx = ltmpDone[i];
				if (lastIdx == 1) {
					if (crtIdxFirstCell == i) {
						++crtIdxFirstCell;
					}

					if (idxFirstCell == i) {
						++idxFirstCell;
					}

					continue;
				}


				int16s crtOffsLeftBot = vget(offsetVectLeftBot, nrCuLeft);
				int16s crtOffsRightBot = vget(offsetVectRightBot, nrCuRight);
				int16s yBotOffs = (endY - crtStartRow) * int32SourceStride;

				if (crtOffsLeftBot < 0 && crtOffsRightBot < 0) {
					offsetVectLeftBot = vput(offsetVectLeftBot, int16s(xInCuLeft + yBotOffs), nrCuLeft);
					offsetVectRightBot = vput(offsetVectRightBot, int16s(xInCuRight + yBotOffs), nrCuRight);
					idxArrBot = vput(idxArrBot, int32s(i), nrCuLeft);

					shiftLeftBot = vput(shiftLeftBot, int16s(nrCuRight - nrCuLeft), nrCuLeft);

					somethingToDo = true;

					if (idxFirstCell == i) {
						++idxFirstCell;
					}

					if (crtIdxFirstCell == i) {
						++crtIdxFirstCell;
					}

					ltmpDone[i] = 1;

					destVal_lowTmp = vput(destVal_lowTmp, apDestLow[i], nrCuLeft);
					destVal_highTmp = vput(destVal_highTmp, apDestHigh[i], nrCuLeft);
				}

			}
		}// for all offsets inside this chunk, gather the chunk offsets in the corresponding CU's


		if (somethingToDo) {
			// use a little bit parallelism for all of those values which can be computed concomitantly
			vec32s vLeftTop_Hi, vRgtTop_Hi;
			vec32u vLeftTop_Low, vRgtTop_Low;
			
			vif(offsetVectLeftTop >= 0 || offsetVectRightTop >= 0) {
				vif(offsetVectLeftTop >= 0) {
					vLeftTop_Hi = vload(apcSrcHigh, offsetVectLeftTop);//apcSrcHigh[xInCuLeft + cellY * int32SourceStride];
					vLeftTop_Low = vload(apcSrcLow, offsetVectLeftTop);//apcSrcLow[xInCuLeft + cellY * int32SourceStride];
				} vendif

				vif(offsetVectRightTop >= 0) {
					vRgtTop_Hi = vload(apcSrcHigh, offsetVectRightTop); // apcSrcHigh[xInCuRight + cellY * int32SourceStride];
					vRgtTop_Low = vload(apcSrcLow, offsetVectRightTop);//apcSrcLow[xInCuRight + cellY * int32SourceStride];
				} vendif

				vec32s vRgtTop_Hi_shifted = vRgtTop_Hi;
				vec32u vRgtTop_Low_shifted = vRgtTop_Low;

				vec16s cpyShiftLeft = shiftLeftTop;
				while ( vany(cpyShiftLeft > 0) ) {

					vif(cpyShiftLeft == 0 && offsetVectLeftTop >= 0 && offsetVectRightTop >= 0) {
						difference_filter_in64s_out64s(&destVal_high_top, &destVal_low_top, &vLeftTop_Hi, &vLeftTop_Low, &vRgtTop_Hi_shifted, &vRgtTop_Low_shifted, 1, 1, 1, 1);
					} vendif
					
					vif(cpyShiftLeft > 0){
					//for (int stillToShift = 0; stillToShift < outCellWidth; ++stillToShift) {
						vRgtTop_Hi_shifted = vmsl(vRgtTop_Hi_shifted);
						vRgtTop_Low_shifted = vmsl(vRgtTop_Low_shifted);
					//}
						offsetVectRightTop = vmsl(offsetVectRightTop);
							
						--cpyShiftLeft;
						//cpyShiftLeft = vmsl(cpyShiftLeft);
					} vendif
				}

				vif(offsetVectLeftTop >= 0) {
					difference_filter_in64s_out64s(&destVal_high_top, &destVal_low_top, &vLeftTop_Hi, &vLeftTop_Low, &vRgtTop_Hi_shifted, &vRgtTop_Low_shifted, 1, 1, 1, 1);
				} vendif
									
			}vendif
		

			vec32s vLeftBot_Hi, vRgtBot_Hi;
			vec32u vLeftBot_Low, vRgtBot_Low;

			vif(offsetVectLeftBot >= 0 || offsetVectRightBot >= 0) {
				vif(offsetVectLeftBot >= 0) {
					vLeftBot_Hi = vload(apcSrcHigh, offsetVectLeftBot);// apcSrcHigh[xInCuLeft + cellY *int32SourceStride];
					vLeftBot_Low = vload(apcSrcLow, offsetVectLeftBot); //apcSrcLow[xInCuLeft + cellY *int32SourceStride];
				} vendif

				vif(offsetVectRightBot >= 0){
					vRgtBot_Hi = vload(apcSrcHigh, offsetVectRightBot);//apcSrcHigh[xInCuRight + cellY *int32SourceStride];								
					vRgtBot_Low = vload(apcSrcLow, offsetVectRightBot); //apcSrcLow[xInCuRight + cellY *int32SourceStride];
				}vendif

				// put into destination the computed values from the top corners
				vif(idxArrTop == idxArrBot && idxArrBot >= 0) {
					destVal_lowTmp = destVal_low_top;
					destVal_highTmp = destVal_high_top;
				} vendif

				vec32s resHigh;
				vec32u resLow;
				// Below:
				//v = (vRgtBot + vLeftTop - vRgtTop - vLeftBot) / BOX_64_AREA;
				//	add_in64s_out64s(&resHigh, &resLow, &vRgtBot_Hi, &vRgtBot_Low, &destVal_high, &destVal_low, 1, 1, 1, 1);
				//	difference_filter_in64s_out64s(&destVal_high, &destVal_low, &resHigh, &resLow, &vLeftBot_Hi, &vLeftBot_Low, 1, 1, 1, 1);

				vec32s vRgtBot_Hi_shifted = vRgtBot_Hi;
				vec32u vRgtBot_Low_shifted = vRgtBot_Low;

				vec16s cpyShiftLeft = shiftLeftBot;

				while (vany(cpyShiftLeft > 0)) {
					//v = (vRgtBot + vLeftTop - vRgtTop - vLeftBot) / BOX_64_AREA;
					vif(cpyShiftLeft == 0 && offsetVectLeftBot >= 0 && offsetVectRightBot >= 0) {
						add_in64s_out64s(&resHigh, &resLow, &vRgtBot_Hi_shifted, &vRgtBot_Low_shifted, &destVal_highTmp, &destVal_lowTmp, 1, 1, 1, 1);
						difference_filter_in64s_out64s(&destVal_high_bot, &destVal_low_bot, &resHigh, &resLow, &vLeftBot_Hi, &vLeftBot_Low, 1, 1, 1, 1);
					} vendif

					vif(cpyShiftLeft > 0) {
						vRgtBot_Hi_shifted = vmsl(vRgtBot_Hi_shifted);
						vRgtBot_Low_shifted = vmsl(vRgtBot_Low_shifted);
						offsetVectRightBot = vmsl(offsetVectRightBot);
						--cpyShiftLeft;
						//cpyShiftLeft = vmsl(cpyShiftLeft);
					} vendif
				}

				vif(offsetVectLeftBot >= 0) {
					add_in64s_out64s(&resHigh, &resLow, &vRgtBot_Hi_shifted, &vRgtBot_Low_shifted, &destVal_highTmp, &destVal_lowTmp, 1, 1, 1, 1);
					difference_filter_in64s_out64s(&destVal_high_bot, &destVal_low_bot, &resHigh, &resLow, &vLeftBot_Hi, &vLeftBot_Low, 1, 1, 1, 1);
				} vendif

			} vendif

			// write results back to static destination vector
			for (int16u fI = 0; fI < nrCUs; ++fI){	
				
				int32s destIdxTop = vget(idxArrTop, fI);
				int32s destIdxBot = vget(idxArrBot, fI);
				if (destIdxTop >= 0 && destIdxTop != destIdxBot) {
					int32u destVal = vget(destVal_low_top, fI);
					apDestLow[destIdxTop] = destVal;

					int32s destVals = vget(destVal_high_top, fI);
					apDestHigh[destIdxTop] = destVals;
				}			

				if (destIdxBot >= 0) {
					int32u destVal = vget(destVal_low_bot, fI);
					apDestLow[destIdxBot] = destVal;

					int32s destVals = vget(destVal_high_bot, fI);
					apDestHigh[destIdxBot] = destVals;
				}


			}
		}
	} while (somethingToDo);

}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION 

