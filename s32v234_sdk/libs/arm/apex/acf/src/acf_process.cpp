/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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
#include <acf_process.h>
#include <stdint.h>
  #include <iostream>
  #include <iomanip>

#ifdef __STANDALONE__
	#include <printf.h>
#endif

using namespace std;

ACF_Process::ACF_Process()
{
   mErrorState = 0;
   mRoiInfoL = 0;
   mRoiInfoR = 0;
   mRoiInfoT = 0;
   mRoiInfoB = 0;
   mRoiInfoManualFlag = 0;
   mInitializedFlag = 0;
   mSpatialDepFlag = 0;
}

ACF_Process::~ACF_Process()
{
}

int32_t ACF_Process::ConnectIO(std::string lPortIdentifier, icp::DataDescriptor& lContigDataDesc)
{
   int32_t lRetVal = 0;

   ACF_Process_PortInfo* lpPortInfo = RetPortInfo(lPortIdentifier);

   if (lpPortInfo != 0) //if port was found
   {
      if (lpPortInfo->IsDirect())
      {
		 //if (!(lpPortInfo->mContigDataDesc == lContigDataDesc)) mProcessApuLoadFlag = 1;
         lpPortInfo->mContigDataDesc = lContigDataDesc;
		 
         e0_desc lE0DescIo = RetE0Desc(lpPortInfo->mContigDataDesc.GetElementDataType(),
                                       lpPortInfo->mContigDataDesc.GetElementDimX(),
                                       lpPortInfo->mContigDataDesc.GetElementDimY());

         if (E0Compare(&lE0DescIo, &lpPortInfo->mE0))
         {
            lpPortInfo->mConfiguredFlag = 1;
         }
         else
         {
            printf("ACF_Process::ConnectIO(%s, ... ) -> e0 mismatch between port and data\n", lPortIdentifier.c_str());
            lRetVal = 1;
            mErrorState = 1;
         }
      }
      else
      {
	printf("ACF_Process::ConnectIO(%s, ... ) -> this port has been flagged for indirect input\n", lPortIdentifier.c_str());
         lRetVal = 1;
         mErrorState = 1;
      }
   }
   else //port couldn't be found
   {
     printf("ACF_Process::ConnectIO(%s, ... ) -> port could not be found\n", lPortIdentifier.c_str());
      lRetVal = 1;
      mErrorState = 1;
   }

   return lRetVal;
}

int32_t ACF_Process::ConnectIO_ROI(std::string lPortIdentifier,
                                   icp::DataDescriptor& lContigDataDesc,
                                   int32_t ROI_left,
                                   int32_t ROI_top,
                                   int32_t ROI_width,
                                   int32_t ROI_height)
{
   int32_t lRetVal = 0;
   lContigDataDesc.SetROI(ROI_left, ROI_top, ROI_width, ROI_height);
   icp::DataDescriptor lDescRoi(lContigDataDesc);
   
   lRetVal = ConnectIO(lPortIdentifier, lDescRoi);
   lContigDataDesc.ClearROI();
   return lRetVal;
}

int32_t ACF_Process::ConnectIndirectInput(std::string lPortIdentifier,
                                          icp::DataDescriptor& lSrcData,
                                          icp::DataDescriptor& lChunkOffsetArray)
{
   int32_t lRetVal = 0;

   ACF_Process_PortInfo* lpPortInfo = RetPortInfo(lPortIdentifier);

   if (lpPortInfo != 0) //if port was found
   {
      if (lpPortInfo->IsIndirect())
      {
         //if (!(lpPortInfo->mContigDataDesc == lSrcData)) mProcessApuLoadFlag = 1;
		 lpPortInfo->mContigDataDesc = lSrcData;
		 

         e0_desc lE0DescIo = RetE0Desc(lpPortInfo->mContigDataDesc.GetElementDataType(),
                                       lpPortInfo->mContigDataDesc.GetElementDimX(),
                                       lpPortInfo->mContigDataDesc.GetElementDimY());

         if (E0Compare(&lE0DescIo, &lpPortInfo->mE0))
         {
            if ((lChunkOffsetArray.GetWidth()&0x3) == 0) //HW LIMITATION: number of chunk offset pointers must be a multiple of 4 in the horizontal direction (GOC)
            {
               //if (!(lpPortInfo->mOffsetArray == lChunkOffsetArray)) mProcessApuLoadFlag = 1;
			   lpPortInfo->mOffsetArray    = lChunkOffsetArray;
			   
               lpPortInfo->mConfiguredFlag = 1;
            }
            else //width of chunk offset array is NOT a multiple of 4
            {
               printf("ACF_Process::ConnectIndirectInput(%s, ... ) -> width of chunk offset array must be a multiple of 4 (i.e. # of pointers in the horizontal dimension must be a multiple of 4)\n", lPortIdentifier.c_str());
               lRetVal = 1;
               mErrorState = 1;
            }
         }
         else //e0 mismatch
         {
	   printf("ACF_Process::ConnectIndirectInput(%s, ... ) -> e0 mismatch between port and source data\n", lPortIdentifier.c_str());
            lRetVal = 1;
            mErrorState = 1;
         }
      }
      else
      {
	printf("ACF_Process::ConnectIndirectInput(%s, ... ) -> this port has not been flagged for indirect input\n", lPortIdentifier.c_str());
         lRetVal = 1;
         mErrorState = 1;
      }
   }
   else //port couldn't be found
   {
      printf("ACF_Process::ConnectIndirectInput(%s, ... ) -> port could not be found\n", lPortIdentifier.c_str());
      lRetVal = 1;
      mErrorState = 1;
   }

   return lRetVal;
}

void ACF_Process::SetProcessIdentifier(std::string lProcessIdentifier)
{
   mProcessIdentifier = lProcessIdentifier;
}

std::string ACF_Process::RetProcessIdentifier()
{
   return mProcessIdentifier;
}

void ACF_Process::AddPort(std::string lPortIdentifier,
                          icp::DATATYPE lE0DataType, int32_t lE0x, int32_t lE0y,
                          int32_t lChunkWidth, int32_t lChunkHeight,
                          int32_t lInputOutput,
                          int32_t lNonstaticStatic,
                          int32_t lDirectIndirect,
                          int32_t lNonfixedFixed,
                          int32_t lRegFifo,
                          int32_t lLmIndex,
                          int32_t lRoiDepInfo)
{
   ACF_Process_PortInfo lPortInfo;

   lPortInfo.mPortIdentifier  = lPortIdentifier;
   lPortInfo.mE0.dataType     = lE0DataType;
   lPortInfo.mE0.x            = lE0x;
   lPortInfo.mE0.y            = lE0y;
   lPortInfo.mChunkWidth      = lChunkWidth;
   lPortInfo.mChunkHeight     = lChunkHeight;
   lPortInfo.mInputOutput     = lInputOutput;
   lPortInfo.mNonstaticStatic = lNonstaticStatic;
   lPortInfo.mDirectIndirect  = lDirectIndirect;
   lPortInfo.mNonfixedFixed   = lNonfixedFixed;
   lPortInfo.mRegFifo         = lRegFifo;
   lPortInfo.mLmIndex         = lLmIndex;
   lPortInfo.mRoiDepInfoN     = ((lRoiDepInfo>>24)&0xFF);
   lPortInfo.mRoiDepInfoS     = ((lRoiDepInfo>>16)&0xFF);
   lPortInfo.mRoiDepInfoE     = ((lRoiDepInfo>> 8)&0xFF);
   lPortInfo.mRoiDepInfoW     = ((lRoiDepInfo>> 0)&0xFF);

   mPortInfoVec.push_back(lPortInfo);
}

ACF_Process_PortInfo* ACF_Process::RetPortInfo(std::string lPortIdentifier)
{
   ACF_Process_PortInfo* lpPortInfo = 0;

   for (int32_t i=0; i<(int32_t)mPortInfoVec.size(); i++)
   {
      if (mPortInfoVec[i].mPortIdentifier == lPortIdentifier)
      {
         lpPortInfo = &mPortInfoVec[i];
         break;
      }
   }

   return lpPortInfo;
}

int32_t ACF_Process::SetRoiInfo(int32_t lRoiInfoL, int32_t lRoiInfoR, int32_t lRoiInfoT, int32_t lRoiInfoB)
{
   mRoiInfoL = lRoiInfoL;
   mRoiInfoR = lRoiInfoR;
   mRoiInfoT = lRoiInfoT;
   mRoiInfoB = lRoiInfoB;

   mRoiInfoManualFlag = 1;

   return 0;
}

