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
* \file apu_offset_select_kernel_impl.c
* \brief The pixels in a specified neighborhood around a certain offset (offsets are left top corner in the patch) are selected and copied to a new matrix. 
*		  Works similar to IndirectInputs, but if selected patches are out of matrix dimensions. Then only the in-matrix elements are copied. All others are set to zero
* \author Anca Dima
* \version
* \date
****************************************************************************/

// In order to compile it as CPP do following: 
// In Visual Studio->Solution Explorer->Project "convolution_Kernel", right click -> Properties -> C/C++ ->Advanced->CompileAs->Compile As C++

#include "apu_offset_select_kernel_impl.h"

int32s offset_select_filter_sorted(vec08u* dst, int16u outCellWidth, int16u outCellHeight, int32u nrCUs, vec08u* srcA, int16u crtImgWidth, int32u* offsets, int32u nrOffsets, int32u inCellWidth, int32u /*inCellHeight*/, int32u crtStartRow, int16u& idxFirstCell, int16u /*bw*/, int16u bh, int16u inSstr, int16u /*outSstr*/)
{
   vec08u* fsrcA = srcA;   
   vec08u* out = dst; //\warning should be initialized to zero. Will have width = nrOffsets * xNeigh, and height = yNeigh 
   
   int32u szInputType = sizeof(int08u);
   int32u inputImgSpan = crtImgWidth *szInputType;
 
   /*
   if (bw <= (neighX<<1) || bh <= (neighY<<1))
	   return -1;
	*/

   int32u outRowSize = nrCUs * outCellWidth * sizeof(int08u);
   int32u outTileSize = outRowSize * outCellHeight; // out span of the whole tile
 
   int16u endRow = crtStartRow + bh; //bh is the input blockheight
  // int16u offsetIdx = 0;

   int int32SourceStride = inSstr;

   --outCellWidth; // for having the real idx of the endX and endY
   --outCellHeight;

   for (int32u offsetIdx = idxFirstCell; offsetIdx < nrOffsets; ++offsetIdx) 
   {
	   int16u outCUIdx = offsetIdx % nrCUs;
	   int16u outTileIdx = offsetIdx / nrCUs;
	   vec08u *crtOutTile = out + outTileIdx * outTileSize;

	   int32u crtOffset = offsets[offsetIdx];
	   int32u  crtX = crtOffset % (inputImgSpan) //offsetsX[offsetIdx] // these are absolute image (x,y) coords
		   , crtY = crtOffset / inputImgSpan;    //offsetsY[offsetIdx];

	   // select the x offsets which are inside this input tile
	   int32s initStartOffsetX = ((int32s)crtX);
	   int32u startOffsetX = (int32u) (crtX >= 0? initStartOffsetX : 0); // limit X to image dimensions
	   int32u endOffsetX = crtX + outCellWidth;
	   endOffsetX = endOffsetX < crtImgWidth ? endOffsetX : crtImgWidth-1;

	   // adapt the y offsets which are inside this input tile
	   int32s initStartOffsetY = ((int32s)crtY);
	   int32u startOffsetY = (int32u)(crtY >= 0? initStartOffsetY : 0);
	   startOffsetY = startOffsetY > crtStartRow ? startOffsetY: crtStartRow;	
	   int32u endOffsetY = crtY + outCellHeight;
	   endOffsetY = endOffsetY < endRow ? endOffsetY : endRow;
	   if (endOffsetY < endRow) {
		   idxFirstCell = offsetIdx + 1;
	   }

	    if (startOffsetY < endRow &&  endOffsetY > crtStartRow) {		  
		   // start at the row which is still inside the chunk.
		   for (int32u i = startOffsetY, l = startOffsetY - initStartOffsetY; i < endOffsetY; ++i, ++l) {
			   // l is at its first iteration the delta between the wanted y and the currently loaded y.
			   // i.e. l is the y offset inside the output chunk
			   vec08u *crtOutRow = crtOutTile + outRowSize*l;

			   int32u rowInChunk = i - crtStartRow;
			   vec08u* crtRow = fsrcA + inSstr*rowInChunk; // the current input row we are looking at...

			   for (int32u j = startOffsetX, k = startOffsetX - initStartOffsetX; j < endOffsetX; ++j, ++k) {
	
				   int16u outCellX = k;
				 
				   int16u inCuIdx = j / inCellWidth;
				   int16u xInCU = j % inCellWidth;
				   vec08u crtCUVect = crtRow[xInCU];

				   int08u cmemData = vget(crtCUVect, inCuIdx);
				   crtOutRow[outCellX] = vput(crtOutRow[outCellX], cmemData, outCUIdx);

			   }
		   }
	   }
   }
   return 0;
} 




int32s offset_select_filter(vec08u* dst, int16u outCellWidth, int16u outCellHeight, int32u nrCUs, vec08u* srcA, int16u crtImgWidth, int32u* offsets, int32u nrOffsets, int32u inCellWidth, int32u /*inCellHeight*/, int32u crtStartRow, int16u /*bw*/, int16u bh, int16u inSstr, int16u /*outSstr*/)
{
	vec08u* fsrcA = srcA;
	vec08u* out = dst; //\warning should be initialized to zero. Will have width = nrOffsets * xNeigh, and height = yNeigh 

	int32u szInputType = sizeof(int08u);
	int32u inputImgSpan = crtImgWidth *szInputType;

	/*
	if (bw <= (neighX<<1) || bh <= (neighY<<1))
	return -1;
	*/

	int32u outRowSize = nrCUs * outCellWidth * sizeof(int08u);
	int32u outTileSize = outRowSize * outCellHeight; // out span of the whole tile

	int16u endRow = crtStartRow + bh; //bh is the input blockheight
	// int16u offsetIdx = 0;

	int int32SourceStride = inSstr;

	--outCellWidth; // for having the real idx of the endX and endY
	--outCellHeight;

	for (int32u offsetIdx = 0; offsetIdx < nrOffsets; ++offsetIdx)
	{
		int16u outCUIdx = offsetIdx % nrCUs;
		int16u outTileIdx = offsetIdx / nrCUs;
		vec08u *crtOutTile = out + outTileIdx * outTileSize;

		int32u crtOffset = offsets[offsetIdx];
		int32u  crtX = crtOffset % (inputImgSpan) //offsetsX[offsetIdx] // these are absolute image (x,y) coords
			, crtY = crtOffset / inputImgSpan;    //offsetsY[offsetIdx];

		// select the x offsets which are inside this input tile
		int32s initStartOffsetX = ((int32s)crtX);
		int32u startOffsetX = (int32u)(crtX >= 0 ? initStartOffsetX : 0); // limit X to image dimensions
		int32u endOffsetX = crtX + outCellWidth;
		endOffsetX = endOffsetX < crtImgWidth ? endOffsetX : crtImgWidth - 1;

		// adapt the y offsets which are inside this input tile
		int32s initStartOffsetY = ((int32s)crtY);
		int32u startOffsetY = (int32u)(crtY >= 0 ? initStartOffsetY : 0);
		startOffsetY = startOffsetY > crtStartRow ? startOffsetY : crtStartRow;
		int32u endOffsetY = crtY + outCellHeight;
		endOffsetY = endOffsetY < endRow ? endOffsetY : endRow;
	
		if (startOffsetY < endRow &&  endOffsetY > crtStartRow) {
			// start at the row which is still inside the chunk.
			for (int32u i = startOffsetY, l = startOffsetY - initStartOffsetY; i < endOffsetY; ++i, ++l) {
				// l is at its first iteration the delta between the wanted y and the currently loaded y.
				// i.e. l is the y offset inside the output chunk
				vec08u *crtOutRow = crtOutTile + outRowSize*l;

				int32u rowInChunk = i - crtStartRow;
				vec08u* crtRow = fsrcA + inSstr*rowInChunk; // the current input row we are looking at...

				for (int32u j = startOffsetX, k = startOffsetX - initStartOffsetX; j < endOffsetX; ++j, ++k) {

					int16u outCellX = k;

					int16u inCuIdx = j / inCellWidth;
					int16u xInCU = j % inCellWidth;
					vec08u crtCUVect = crtRow[xInCU];

					int08u cmemData = vget(crtCUVect, inCuIdx);
					crtOutRow[outCellX] = vput(crtOutRow[outCellX], cmemData, outCUIdx);

				}
			}
		}
	}
	return 0;
}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
