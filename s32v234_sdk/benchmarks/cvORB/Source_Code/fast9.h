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
* \file fast9.h
* \brief FAST 9 corner detection implementation
****************************************************************************/

#ifndef FAST9_H

#define FAST9_H


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
	const unsigned char* apcSrc, int   aSourceStride, int   aCircleIndex);
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
	unsigned char acSource, unsigned char acReference, int aThreshold);

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
	unsigned char acSource, unsigned char acReference, int aThreshold, short *difs);
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
	const unsigned char* apcSrc, int aSourceStride, int aThreshold);


/****************************************************************************/
/** Vector minimum.
*****************************************************************************/
static inline short vMin(short aA, short aB);

/****************************************************************************/
/** Vector maximum.
*****************************************************************************/
static inline short vMax(short aA, short aB);

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
	const unsigned char* apcSrc, int aSourceStride, int aThreshold);

void apu_fast9_unsuppressed_score(
	const unsigned char* apcSrc, unsigned char* apDst,
	int   aSourceStride, int aDestinationStride,
	int   aBlockWidth, int aBlockHeight,
	unsigned char aThreshold);

#endif