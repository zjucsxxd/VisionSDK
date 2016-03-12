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
* \file APU_extras.h
* \brief extra APU functions
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#ifndef _APU_EXTRAS_H_
#define _APU_EXTRAS_H_

#include <string>
#include <cstdint>

namespace APEX2
{
  //possible results of data transformation operations
  enum APEX2OperationResult
  {
    APEX2_OK,
    APEX2_WARNING,
    APEX2_ERROR,
  };


	/****************************************************************************/
	/** Transforms input image data to output CMEM data using the block layout. Filter is anisotropic (i.e. different Width and Height size)
	*
	* \param apOut pointer to output array
	* \param apcIn pointer to the input array including padding
	*        (i.e. it's always safe to point to the first pixel)
	* \param aCUTileWidth width of CU block
	* \param aCUImageHeight height of the image
	* \param aPaddingX required output padding for X direction
	* \param aPaddingY required output padding for Y direction
	* \param aCUCount number of CUs
	* \param aInputWidth width of the input
  * \param apMessage optional output message
  *
  * \return operation result
	*
	* \note apOut, apcIn can't point to the same data
	*
	*****************************************************************************/
	template <typename T>
  APEX2OperationResult ArrayToCMEMDataSym(T* apOut, const T* apcIn, int aCUTileWidth,
    int aCUImageHeight, int aPaddingX, int aPaddingY, int aCUCount, int aInputWidth, std::string* apMessage = 0)
	{
    int imgWidth = aInputWidth, imgHeight = aCUImageHeight;
		int outIndex = 0;
		for (int y = -aPaddingY; y < imgHeight + aPaddingY; ++y)
		{
			// symmetric extension
			//int crtY = y < 0 ? abs(y)  : (y >= imgHeight ? 2 * imgHeight - y - 1 : y);

			// replicating extension
			int crtY = y < 0 ? 0 : (y >= imgHeight ? imgHeight - 1 : y);
			//we will be working with the row - start on first nonpadded pixel
			const T* row = apcIn + crtY * aInputWidth;// +aPaddingX;

			//go through the tile row (actually a column in CMEM) + padding pixels
			for (int i = -aPaddingX; i < aCUTileWidth + aPaddingX; ++i)
			{
				//for each CU / element in vector
				for (int j = 0; j < aCUCount; ++j)
				{
					int idx = j * aCUTileWidth + i;
					
					//symmetric extension
					//int crtx = idx < 0 ? abs(idx) : (idx >= imgWidth ? 2 * imgWidth - idx - 1 : idx);

					// replicating extension
					int crtx = idx < 0 ? 0: (idx >= imgWidth ? imgWidth - 1 : idx);

					T pixel = row[crtx];
					apOut[outIndex++] = pixel;
				}
			}
		}
    return APEX2_OK;
	}

/****************************************************************************/
/** Transforms input image data to output CMEM data using the block layout.
*
* \param apOut pointer to output array
* \param apcIn pointer to the input array including padding
*        (i.e. it's always safe to point to the first pixel)
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aPadding required output padding
* \param aCUCount number of CUs
* \param aInputWidth width of the input
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult ArrayToCMEMData(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aPadding, int aCUCount, int aInputWidth, std::string* apMessage = 0)
{
  int outIndex = 0;
  for (int y = 0; y < aCUImageHeight + 2 * aPadding; ++y)
  {
    //we will be working with the row - start on the first nonpadded pixel
    const T* row = apcIn + y * aInputWidth + aPadding;
    //go through the tile row (actually a column in CMEM) + padding pixels
    for (int i = -aPadding; i < aCUTileWidth + aPadding; ++i)
    {
      //for each CU / element in vector
      for (int j = 0; j < aCUCount; ++j)
      {
        T pixel = row[j * aCUTileWidth + i];
        apOut[outIndex++] = pixel;
      }
    }
  }
  return APEX2_OK;
}

/****************************************************************************/
/** Transforms input image data to output CMEM data using the block layout and
* the provided offsets.
*
* \param apOut pointer to the output array
* \param apcIn pointer to the input array including padding
*        (i.e. it's always safe to point to the first pixel)
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aCUTileCount number of CU tiles to process
* \param aCUCount number of CUs
* \param aInputWidth width of the input 
* \param aInputHeight height of the input
* \param apcOffsets pointer to offset data
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T, typename O>
APEX2OperationResult ArrayToCMEMDataIndirect(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aCUTileCount, int aCUCount, int aInputWidth, int aInputHeight,
	const O* apcOffsets, std::string* apMessage = 0)
{
	int outIndex = 0;
	const int8_t* bytePointer = (const int8_t*)apcIn;
	int bytesInInput = aInputWidth * aInputHeight * sizeof(T);
	APEX2OperationResult result = APEX2_OK;
	for (int tileNum = 0; tileNum < aCUTileCount; ++tileNum)
	{
    for (int y = 0; y < aCUImageHeight; ++y)
		{
			//go through the tile row (actually a column in CMEM) + padding pixels
			for (int i = 0; i < aCUTileWidth; ++i)
			{
				//for each CU / element in vector
				for (int j = 0; j < aCUCount; ++j)
				{
					O chunkOffset = apcOffsets[tileNum * aCUCount + j];
          //CAUTION: cfm to ACF-Spec offsets have to be provided respectively to byte addresses (not pixel addresses!)
					int finalOffset = (int)chunkOffset + (y * aInputWidth + i) * sizeof(T);

					if (finalOffset < 0 || finalOffset >= bytesInInput)
					{
						*apMessage = "indirect input offset out of input data range";
						return APEX2_ERROR;
					}

					int chunkElementOffset = chunkOffset / sizeof(T);
					int coX = chunkElementOffset % aInputWidth;
					//NOTE: not really needed when the function is used the intended way
					int coY = chunkElementOffset / aInputWidth;

          if (coX > aInputWidth - aCUTileWidth || coY > aInputHeight - aCUImageHeight)
					{
						*apMessage = "indirect input chunk wraps around the image border (the offset is too far to the right or bottom)";
						result = APEX2_WARNING;
					}

					const int8_t* byteAddress = &(bytePointer[finalOffset]);
					T pixel = *((T*)byteAddress);
					apOut[outIndex++] = pixel;
				}
			}
		}
	}
	return result;
}
/****************************************************************************/
/** Transforms input CMEM data to output image data. Ignores padding pixels.
*
* \param apOut pointer to output array
* \param apcIn pointer to CMEM input array
*        (should point to the first element even when padding used)
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aPadding input padding
* \param aCUCount number of CUs
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult CMEMDataToArray(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aPadding, int aPaddingVert, int aCUCount, std::string* message = 0)
{
  int outIndex = 0;
  int inSpan = aCUTileWidth + 2 * aPadding;
  apcIn += (aPaddingVert * inSpan + aPadding) * aCUCount;

  for (int y = 0; y < aCUImageHeight; ++y)
  {
    for (int x = 0; x < aCUTileWidth * aCUCount; ++x)
    {
      int blockNum = x / aCUTileWidth;
      int blockOffset = x % aCUTileWidth;
      
      T pixel = apcIn[blockOffset * aCUCount + blockNum];
      
      apOut[outIndex++] = pixel;
    }
    apcIn += inSpan * aCUCount;
  }
  return APEX2_OK;
}

/****************************************************************************/
/** Computes an array size needed for input image (with padding).
*
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aPadding padding
* \param aCUCount number of CUs
*
*****************************************************************************/
int inline SrcImageArraySize(int aCUTileWidth,
  int aCUImageHeight, int aPadding, int aCUCount)
{
  return (aCUImageHeight + 2 * aPadding) *
    (aCUTileWidth * aCUCount + 2 * aPadding);
}

/****************************************************************************/
/** Computes an array size needed for output image (without padding).
*
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aCUCount number of CUs
*
*****************************************************************************/
int inline DstImageArraySize(int aCUTileWidth,
  int aCUImageHeight, int aCUCount)
{
  return SrcImageArraySize(aCUTileWidth, aCUImageHeight, 0, aCUCount);
}


/****************************************************************************/
/** Computes an array size needed for CMEM data (in elements, with padding).
*
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aPaddingX required output padding for X direction
* \param aPaddingY required output padding for Y direction
* \param aCUCount number of CUs
*
*****************************************************************************/
int inline CMEMArraySize(int aCUTileWidth,
  int aCUImageHeight, int aPaddingX, int aPaddingY, int aCUCount)
{
	return (aCUTileWidth + 2 * aPaddingX) *
    (aCUImageHeight + 2 * aPaddingY) * aCUCount;
}



/****************************************************************************/
/** Computes an array size needed for CMEM data (in elements, with padding).
*
* \param aCUTileWidth width of CU block
* \param aCUImageHeight height of the image
* \param aPadding required output padding
* \param aCUCount number of CUs
*
*****************************************************************************/
/*int inline CMEMArraySize(int aCUTileWidth,
	int aCUImageHeight, int aPadding, int aPaddingVert, int aCUCount)
{
  return (aCUTileWidth + 2 * aPadding) *
    (aCUImageHeight + 2 * aPaddingVert) * aCUCount;
}
*/
/****************************************************************************/
/** Adds the padding and replicates padded pixels' values from neighboring
*  tiles. The pixels are always 1x1. The padded pixels are created by
* replicating the border pixels.
*
* \param apOut pointer to the output array
* \param apcIn pointer to the (not padded) input array
* \param aCUTileWidth width of CU block of the input
* \param aCUImageHeight height of the image
* \param aOutputPadding required output padding
* \param aCUCount number of CUs
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult AddPaddingCMEM(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aOutputPadding, int aCUCount, std::string* apMessage = 0)
{
  //non-padded span for jumping to the next row of the input
  int inputImageSpan = aCUCount * aCUTileWidth;
  //padded span used for jumping to the next row of the output
  int tileSpan = aCUTileWidth + 2 * aOutputPadding;
  //output pixel index
  int outIndex = 0;
  for (int row = -aOutputPadding; row < aCUImageHeight + aOutputPadding; ++row)
  {
    //the current input row offset
    int currentRowOffset = row * aCUTileWidth * aCUCount;

    //handling padded rows... the current input row offset is set to the first/last row of the input
    if (row < 0)
    {
      currentRowOffset = 0;
    }
    else if (row >= aCUTileHeight)
    {
      currentRowOffset = (aCUTileHeight - 1) * aCUTileWidth * aCUCount;
    }

    for (int ti = 0; ti < tileSpan; ++ti)
    {
      for (int vi = 0; vi < aCUCount; ++vi)
      {
        //which input pixel in the current row corresponds to the current iteration
        int origRowIndex = vi * aCUTileWidth + ti - aOutputPadding;

        //handle the indices for left and right padded pixels
        if (origRowIndex < 0)
        {
          origRowIndex = 0;
        }
        else if (origRowIndex >= inputImageSpan)
        {
          origRowIndex = inputImageSpan - 1;
        }

        //decompose the inside-row index to the tile index and inside-tile pixel indices
        int inputTileIndex = origRowIndex / aCUTileWidth;
        int inputTilePixelIndex = origRowIndex % aCUTileWidth;

        //compose the final input CMEM index
        int inputCMEMIndex = currentRowOffset + inputTilePixelIndex * aCUCount + inputTileIndex;

        //output index is simply incremented, the algorithm goes through all output pixels in a linear fashion
        apOut[outIndex++] = apcIn[inputCMEMIndex];
      }
    }
  }
  return APEX2_OK;
}

/****************************************************************************/
/** Removes padding from the input.
*
* \param apOut pointer to the output array
* \param apcIn pointer to the input array
* \param aCUTileWidth width of CU block of the input (without padding)
* \param aCUImageHeight height of the input (without padding)
* \param aInputPadding input padding
* \param aCUCount number of CUs
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult RemovePaddingCMEM(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aInputPadding, int aCUCount, std::string* apMessage = 0)
{
  //how many bytes should be skipped when movin to next input row
  int inputTileSpan = aCUTileWidth + 2 * aInputPadding;

  int outIndex = 0;
  //input row index is set to the first non-padded pixel here
  int inRowIndex = (inputTileSpan * aInputPadding + aInputPadding) * aCUCount;
  for (int row = 0; row < aCUImageHeight; ++row)
  {
    for (int i = 0; i < aCUTileWidth * aCUCount; ++i)
    {
      //outIndex is simply incremented here, nothing in output is skipped
      apOut[outIndex++] = apcIn[inRowIndex + i];
    }
    //input row index is set to the next row
    inRowIndex += inputTileSpan * aCUCount;
  }
  return APEX2_OK;
}

/****************************************************************************/
/** Change padding. The pixels are always 1x1. The padded pixels are created
* by replicating the border pixels.
*
* \param apOut pointer to the output array
* \param apcIn pointer to the input array
* \param aCUTileWidth width of CU block of the input (without padding)
* \param aCUImageHeight height of the input (without padding)
* \param aOutputPadding output padding
* \param aInputPadding input padding
* \param aCUCount number of CUs
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult ChangePaddingCMEM(T* apOut, const T* apcIn, int aCUTileWidth,
  int aCUImageHeight, int aOutputPadding, int aInputPadding, int aCUCount, std::string* apMessage = 0)
{
  //input image span of the non-padded region
  int inputImageSpan = aCUCount * aCUTileWidth;
  //input span including padding for jumping to the next row of the input
  int inputDataSpan = aCUCount * (aCUTileWidth + 2 * aInputPadding);
  //offset to the first non-padded pixel
  int inputDataOffset = aInputPadding * inputDataSpan + aInputPadding * aCUCount;
  //output tile span including padding
  int tileSpan = aCUTileWidth + 2 * aOutputPadding;
  //current output pixel index
  int outIndex = 0;
  for (int row = -aOutputPadding; row < aCUImageHeight + aOutputPadding; ++row)
  {
	  int adjustedRow = row;
    //handling padded rows... the current input row offset is set to the first/last row of the input
    if (row < 0)
    {
		adjustedRow  = 0;
    }
    else if (row >= aCUTileHeight)
    {
		adjustedRow = aCUTileHeight - 1;
      //currentRowOffset = inputDataOffset + (aCUTileHeight - 1) * inputDataSpan;
    }
    //the current input row offset
    int currentRowOffset = inputDataOffset + adjustedRow * inputDataSpan;

    for (int ti = 0; ti < tileSpan; ++ti)
    {
      for (int vi = 0; vi < aCUCount; ++vi)
      {
        //which input pixel in the current row corresponds to the current iteration
        int origRowIndex = vi * aCUTileWidth + ti - aOutputPadding;

        //handle the indices for left and right padded pixels
        if (origRowIndex < 0)
        {
          origRowIndex = 0;
        }
        else if (origRowIndex >= inputImageSpan)
        {
          origRowIndex = inputImageSpan - 1;
        }

        //decompose the inside-row index to the tile index and inside-tile pixel indices
        int inputTileIndex = origRowIndex / aCUTileWidth;
        int inputTilePixelIndex = origRowIndex % aCUTileWidth;

        //compose the final input CMEM index
        int inputCMEMIndex = currentRowOffset + inputTilePixelIndex * aCUCount + inputTileIndex;

        //output index is simply incremented, the algorithm goes through all output pixels in a linear fashion
        apOut[outIndex++] = apcIn[inputCMEMIndex];
      }
    }
  }
  return APEX2_OK;
}

/****************************************************************************/
/** Change padding using with granularity (e0) info. Supports different
* padding in each direction. The padded pixels are created by replicating the
* border pixels (which can be larger than 1x1).
*
* \param apOut pointer to the output array
* \param apcIn pointer to the input array
* \param aCUTileWidth width of CU block of the input (without padding)
* \param aCUImageHeight height of the input (without padding)
* \param aOutputPaddingsLRTB
*   output paddings in left, right, top, bottom directions in T elements
* \param aInputPaddingsLRTB
*   input paddings in left, right, top, bottom directions in T elements
* \param aCUCount number of CUs
* \param inputGranularityX data granularity in X direction
* \param inputGranularityY data granularity in Y direction
* \param apMessage optional output message
*
* \return operation result
*
* \note apOut, apcIn can't point to the same data
*
*****************************************************************************/
template <typename T>
APEX2OperationResult ChangePaddingCMEM(T* apOut, const T* apcIn, int inputImageSpan, int aCUTileWidth,
  int aCUImageHeight, int aOutputPaddingsLRTB[4], int aInputPaddingsLRTB[4], int aCUCount,
  int inputGranularityX = 1, int inputGranularityY = 1, std::string* apMessage = 0)
{
  //input image span of the non-padded region
 // int inputImageSpan = aCUCount * aCUTileWidth;
  //input span including padding for jumping to the next row of the input
  int inputDataSpan = aCUCount * (aCUTileWidth + aInputPaddingsLRTB[0] + aInputPaddingsLRTB[1]);
  //offset to the first non-padded pixel
  int inputDataOffset = aInputPaddingsLRTB[2] * inputDataSpan + aInputPaddingsLRTB[0] * aCUCount;
  //output tile span including padding
  int tileSpan = aCUTileWidth + aOutputPaddingsLRTB[0] + aOutputPaddingsLRTB[1];
  //current output pixel index
  int outIndex = 0;
  for (int row = -aOutputPaddingsLRTB[2]; row < aCUImageHeight + aOutputPaddingsLRTB[3]; ++row)
  {
    //the input row is adjusted when pointing to the padded rows according to the Y granularity (pixel height)
    int adjustedRow = row;
    if (adjustedRow < 0)
    {
		adjustedRow = 0;
		// This was mirroring padding 
      //adjustedRow = (/*aOutputPaddingsLRTB[2] +*/ abs(adjustedRow) ) * /*%*/inputGranularityY;
    }
    else if (adjustedRow >= aCUImageHeight)
    {
		adjustedRow = aCUImageHeight - 1;
		// This was mirroring padding 
		//adjustedRow = 2*aCUImageHeight*inputGranularityY - inputGranularityY /*+*/ - (adjustedRow * /*%*/ inputGranularityY);
    }

    //the current input row offset
    int currentRowOffset = inputDataOffset + adjustedRow * inputDataSpan;
    for (int ti = 0; ti < tileSpan; ++ti)
    {
      for (int vi = 0; vi < aCUCount; ++vi)
      {
        //which input pixel in the current row corresponds to the current iteration
        int origRowIndex = vi * aCUTileWidth + ti - aOutputPaddingsLRTB[0];

        //handle the indices for left and right padded pixels taking the Y granularity (pixel width) into account
        if (origRowIndex < 0)
        {
		  // symmetric padding
          //origRowIndex = (/*aOutputPaddingsLRTB[0] + */abs(origRowIndex)) */*%*/ inputGranularityX;
		 //if (origRowIndex >= inputImageSpan) {
			//  origRowIndex = inputImageSpan - 1;
		  //}
			
			// replicating padding
			origRowIndex = 0;
		  
		 /* if (origRowIndex >= inputImageSpan) {
			  origRowIndex = inputImageSpan - 1;
		  }*/
        }
        else if (origRowIndex >= inputImageSpan)
        {
		  //symmetric padding
          //origRowIndex = 2*inputImageSpan*inputGranularityX - inputGranularityX /*+*/ - (origRowIndex */*%*/ inputGranularityX);
		  //if (origRowIndex < 0) {
			//  origRowIndex = 0;
		  //}

			// replicating padding
			origRowIndex = inputImageSpan*inputGranularityX - inputGranularityX;
		  if (origRowIndex < 0) {
			  origRowIndex = 0;
		  }

        }

        //decompose the inside-row index to the tile index and inside-tile pixel indices
        int inputTileIndex = origRowIndex / aCUTileWidth;
        int inputTilePixelIndex = origRowIndex % aCUTileWidth;

        //compose the final input CMEM index
        int inputCMEMIndex = currentRowOffset + inputTilePixelIndex * aCUCount + inputTileIndex;

        //output index is simply incremented, the algorithm goes through all output pixels in a linear fashion
        apOut[outIndex++] = apcIn[inputCMEMIndex];
      }
    }
  }
  return APEX2_OK;
}

}

#endif // _APU_EXTRAS_H_

