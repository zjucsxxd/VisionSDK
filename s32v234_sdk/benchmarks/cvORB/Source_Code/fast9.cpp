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
* \file fast9.cpp
* \brief FAST 9 corner detection implementation
****************************************************************************/

#include "fast9.h"

/*****************************************************************************
* constants
*****************************************************************************/

//corner score value of non-corners
static const short cNonCornerScore = -0x7fff;

//offsets of the 16-pixel ring around the pixel used for corner detection
static const int   cCircleOffsets[16][2] =
{
	{ 0, 3 }, { 1, 3 }, { 2, 2 }, { 3, 1 }, { 3, 0 }, { 3, -1 }, { 2, -2 }, { 1, -3 },
	{ 0, -3 }, { -1, -3 }, { -2, -2 }, { -3, -1 }, { -3, 0 }, { -3, 1 }, { -2, 2 }, { -1, 3 }
};

/*****************************************************************************
* local functions
*****************************************************************************/

/****************************************************************************/
/** Gets pixel by index to the pixel ring.
*
* \param apcSrc pointer to the source pixel(s)
* \param aSourceStride line stride of the source data
* \param aCircleIndex index into the ring 0 <= aCircleIndexx <= 16
*
* \return vector containing requested pixels
*
*****************************************************************************/
static inline unsigned char getPixelFromCircle(
	const unsigned char* apcSrc, int   aSourceStride, int   aCircleIndex) 
{
	return apcSrc[
		(cCircleOffsets[aCircleIndex][0]) +
			(cCircleOffsets[aCircleIndex][1] * aSourceStride)];
}
/****************************************************************************/
/** Classifies a source pixel in relation to the reference pixel.
*
* pixel classes:
*               0 - similar
*               1 - darker
*               2 - brighter
*
* \param acSource pointer to the source pixel(s)
* \param acReference pointer to the reference pixel(s)
* \param aThreshold threshold used for classification
*
* \return vector containing pixel classifications
*
*****************************************************************************/
static inline unsigned char classifyPixel(
	unsigned char acSource, unsigned char acReference, int aThreshold)
{
	unsigned char result = 0;

	short dif = ((short) acReference) - ((short) acSource);

	//darker
	if(dif < -aThreshold)
	{
		result = 2;
	}
	
		if(dif > aThreshold)
	{
			result = 1;

		}
	;

	return result;
}

/****************************************************************************/
/** Classifies a source pixel in relation to the reference pixel.
*
* pixel classes:
*               0 - similar
*               1 - darker
*               2 - brighter
*
* \param acSource pointer to the source pixel(s)
* \param acReference pointer to the reference pixel(s)
* \param aThreshold threshold used for classification
*
* \return vector containing pixel classifications
*
*****************************************************************************/
static inline unsigned char classifyPixelDif(
	unsigned char acSource, unsigned char acReference, int aThreshold, short *difs)
{
	unsigned char result = 0;
	short dif;
	dif = ((short)acReference) - ((short)acSource);

	//darker
	if(dif < -aThreshold)
	{
		result = 2;
	}
	
		if(dif > aThreshold)
	{
			result = 1;
		}
	
		*difs = dif;
	return result;
}

/****************************************************************************/
/** Performs corner ring checks on the source data.
*
* \param apcSrc pointer to the source pixel(s)
* \param aSourceStride line stride of the source data
* \param aThreshold threshold used for classification
*
* \return vector boolean containing test results (false - not a corner,
*         true - is a corner)
*
*****************************************************************************/
static inline bool checkCircle(
	const unsigned char* apcSrc, int aSourceStride, int aThreshold)
{
	const unsigned char v = apcSrc[0];

	unsigned char classifiedCirclePixels[16];

	unsigned char check = 0xff;

	//get pixels used in the first phase
	for (int i = 0; i < 4; ++i)
	{
		int circleIndex0 = i * 2;
		int circleIndex1 = circleIndex0 + 8;

		unsigned char circlePixel0 = getPixelFromCircle(
			apcSrc, aSourceStride, circleIndex0);
		unsigned char circlePixel1 = getPixelFromCircle(
			apcSrc, aSourceStride, circleIndex1);

		unsigned char classifiedCirclePixel0 = classifyPixel(
			v, circlePixel0, aThreshold);
		unsigned char classifiedCirclePixel1 = classifyPixel(
			v, circlePixel1, aThreshold);

		classifiedCirclePixels[circleIndex0] = classifiedCirclePixel0;
		classifiedCirclePixels[circleIndex1] = classifiedCirclePixel1;

		check &= classifiedCirclePixel0 | classifiedCirclePixel1;
	}

	//early exit 1
	bool checkAnd = 1;
	for (int i = 0; i < 16; ++i) {
		checkAnd &= (check == 0);
	}
	if (checkAnd)
	{
		return 0;
	}

	//second phase
	//get pixels used in the second phase
	for (int i = 0; i < 4; ++i)
	{
		int circleIndex0 = i * 2 + 1;
		int circleIndex1 = circleIndex0 + 8;

		unsigned char circlePixel0 = getPixelFromCircle(
			apcSrc, aSourceStride, circleIndex0);
		unsigned char circlePixel1 = getPixelFromCircle(
			apcSrc, aSourceStride, circleIndex1);

		unsigned char classifiedCirclePixel0 = classifyPixel(
			v, circlePixel0, aThreshold);
		unsigned char classifiedCirclePixel1 = classifyPixel(
			v, circlePixel1, aThreshold);

		classifiedCirclePixels[circleIndex0] = classifiedCirclePixel0;
		classifiedCirclePixels[circleIndex1] = classifiedCirclePixel1;

		check &= classifiedCirclePixel0 | classifiedCirclePixel1;
	}

    checkAnd = 1;
	for (int i = 0; i < 16; ++i) {
		checkAnd &= (check == 0);
	}
	if (checkAnd)
	{	//early exit 2
		return 0;
	}

	//check for 9 darker/brighter pixels ring
	unsigned char countDarker = 0;
	unsigned char countBrighter = 0;
	//25 ... we can find the first sequence pixel at 15th element
	for (int i = 0; i < 25; ++i)
	{
		//circle pixels darker than v
		if(classifiedCirclePixels[i & 0xf] == 1)
		{
			++countDarker;
		}
		else
		{
			//null the count only if < 9
			if(countDarker < 9)
			{
				countDarker = 0;
			}
			
		}
		

			if(classifiedCirclePixels[i & 0xf] == 2)
		{
				++countBrighter;
			}
		else
		{
			//null the count only if < 9
			if(countBrighter < 9)
			{
				countBrighter = 0;
			}
			
		}
		
	}



	//collect the results - 1 if the ring was found
	bool result = ((countBrighter >= 9) || (countDarker >= 9));

	return result;
}


/****************************************************************************/
/** Vector minimum.
*****************************************************************************/
static inline short vMin(short aA, short aB)
{
	short ret;

	if(aA < aB)
	{
		ret = aA;
	}
	
		if(aA >= aB)
	{
			ret = aB;
		}
	

		return ret;
}

/****************************************************************************/
/** Vector maximum.
*****************************************************************************/
static inline short vMax(short aA, short aB)
{
	short ret;

	if(aA > aB)
	{
		ret = aA;
	}
	
		if(aA <= aB)
	{
			ret = aB;
		}
	

		return ret;
}

/*****************************************************************************
* functions
*****************************************************************************/


/****************************************************************************/
/** Performs corner ring checks on the source data. Outputs the vector scores.
*
* \param apcSrc pointer to the source pixel(s)
* \param aSourceStride line stride of the source data
* \param aThreshold threshold used for classification
*
* \return vector containing result corner scores
*         (cNonCornerScore - not a corner)
*
*****************************************************************************/
static short checkCircleWithCornerScores(
	const unsigned char* apcSrc, int aSourceStride, int aThreshold)
{
	unsigned char v = apcSrc[0];

	unsigned char classifiedCirclePixels[16];

	unsigned char check = 0xff;
	short difs[16];
	//get pixels used in the first phase
	for (int i = 0; i < 4; ++i)
	{
		int circleIndex0 = i * 2;
		int circleIndex1 = circleIndex0 + 8;

		unsigned char circlePixel0 = getPixelFromCircle(apcSrc, aSourceStride, circleIndex0);

		unsigned char circlePixel1 = getPixelFromCircle(apcSrc, aSourceStride, circleIndex1);

		unsigned char classifiedCirclePixel0 = classifyPixelDif(v, circlePixel0, aThreshold, &difs[circleIndex0]);
		unsigned char classifiedCirclePixel1 = classifyPixelDif(v, circlePixel1, aThreshold, &difs[circleIndex1]);

		classifiedCirclePixels[circleIndex0] = classifiedCirclePixel0;
		classifiedCirclePixels[circleIndex1] = classifiedCirclePixel1;

		check &= classifiedCirclePixel0 | classifiedCirclePixel1;
	}

    bool checkAnd = 1;
	for (int i = 0; i < 16; ++i) {
		checkAnd &= (check == 0);
	}
	if (checkAnd)	
	//early exit 1
	{
		return cNonCornerScore;
	}

	//second phase
	//get pixels used in the second phase
	for (int i = 0; i < 4; ++i)
	{
		int circleIndex0 = i * 2 + 1;
		int circleIndex1 = circleIndex0 + 8;

		unsigned char circlePixel0 = getPixelFromCircle(apcSrc, aSourceStride, circleIndex0);
		unsigned char circlePixel1 = getPixelFromCircle(apcSrc, aSourceStride, circleIndex1);

		unsigned char classifiedCirclePixel0 = classifyPixelDif(v, circlePixel0, aThreshold, &difs[circleIndex0]);
		unsigned char classifiedCirclePixel1 = classifyPixelDif(v, circlePixel1, aThreshold, &difs[circleIndex1]);

		classifiedCirclePixels[circleIndex0] = classifiedCirclePixel0;
		classifiedCirclePixels[circleIndex1] = classifiedCirclePixel1;

		check &= classifiedCirclePixel0 | classifiedCirclePixel1;
	}

	checkAnd = 1;
	for (int i = 0; i < 16; ++i) {
		checkAnd &= (check == 0);
	}
	if (checkAnd)	//early exit 2
	{
		return cNonCornerScore;
	}

	//check for 9 darker/brighter pixels ring
	unsigned char countDarker = 0;
	unsigned char countBrighter = 0;
	//25 ... we can find the first sequence pixel at 15th element
	for (int i = 0; i < 25; ++i)
	{
		//circle pixels darker than v
		if(classifiedCirclePixels[i & 0xf] == 1)
		{
			++countDarker;
		}
		else
		{
			//null the count only if < 9
			if(countDarker < 9)
			{
				countDarker = 0;
			}
			
		}
		

			if(classifiedCirclePixels[i & 0xf] == 2)
		{
				++countBrighter;
			}
		else
		{
			//null the count only if < 9
			if(countBrighter < 9)
			{
				countBrighter = 0;
			}
			
		}
		
	}

	//collect the results 
	bool corners = ((countBrighter >= 9) || (countDarker >= 9));

	if (corners)
	{
		short a0 = aThreshold;
		for (int k = 0; k < 16; k += 2)
		{
			short a = vMin(difs[(k + 1) & 0xf], difs[(k + 2) & 0xf]);
			a = vMin(a, difs[(k + 3) & 0xf]);
			//TODO: early continue?
			bool aa0 = a > a0;
			if ((!aa0) || (!corners)) continue;
			//we still need the if - affects a0
			if(aa0)
			{
				a = vMin(a, difs[(k + 4) & 0xf]);
				a = vMin(a, difs[(k + 5) & 0xf]);
				a = vMin(a, difs[(k + 6) & 0xf]);
				a = vMin(a, difs[(k + 7) & 0xf]);
				a = vMin(a, difs[(k + 8) & 0xf]);
				a0 = vMax(a0, vMin(a, difs[k]));
				a0 = vMax(a0, vMin(a, difs[(k + 9) & 0xf]));
			}
			
		}

		short b0 = -a0;
		for (int k = 0; k < 16; k += 2)
		{
			//TODO: and instead of modulo?
			short b = vMax(difs[(k + 1) & 0xf], difs[(k + 2) & 0xf]);
			b = vMax(b, difs[(k + 3) & 0xf]);
			b = vMax(b, difs[(k + 4) & 0xf]);
			b = vMax(b, difs[(k + 5) & 0xf]);
			bool bb0 = b < b0;
			if ((!bb0) || (!corners)) continue;
			//TODO: early continue?
			//we still need the if - affects b0
			if(bb0)
			{
				b = vMax(b, difs[(k + 6) & 0xf]);
				b = vMax(b, difs[(k + 7) & 0xf]);
				b = vMax(b, difs[(k + 8) & 0xf]);
				b0 = vMin(b0, vMax(b, difs[k]));
				b0 = vMin(b0, vMax(b, difs[(k + 9) & 0xf]));
			}
			
		}

		short scores = -b0 - 1;

		//don't include noncorners
		if(!corners)
		{
			scores = cNonCornerScore;
		}
		
		return scores;
	}
	else
	{
		return cNonCornerScore;
	}

}

void apu_fast9_unsuppressed_score(
	const unsigned char* apcSrc, unsigned char* apDst,
	int   aSourceStride, int aDestinationStride,
	int   aBlockWidth, int aBlockHeight,
	unsigned char aThreshold)
{
	unsigned char   CornersFound = 0;
	for (int y = 0; y < aBlockHeight; ++y)
	{
		for (int x = 0; x < aBlockWidth; ++x)
		{
			short cornerScore = checkCircleWithCornerScores(&apcSrc[x], aSourceStride, aThreshold);
			unsigned char vtmp = 0;
			if(cornerScore > cNonCornerScore)
			{
				vtmp = (unsigned char)cornerScore;
			}			

			apDst[x] = vtmp;
		}
		apcSrc += aSourceStride;
		apDst += aDestinationStride;
	}
}

