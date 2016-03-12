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
#ifndef _ACF_PROCESS_PORTINFO_HPP
#define _ACF_PROCESS_PORTINFO_HPP

#include <icp_data.h>
#include <acf_common.h>
#include <stdint.h>
#include <string>

class ACF_Process_PortInfo
{
public:

   ACF_Process_PortInfo()
   {
      mConfiguredFlag = 0;

      mRoiDepInfoN = 0;
      mRoiDepInfoS = 0;
      mRoiDepInfoE = 0;
      mRoiDepInfoW = 0;
   }
   
   ACF_Process_PortInfo(const ACF_Process_PortInfo &second)
   {
      mPortIdentifier = second.mPortIdentifier;
      mE0 = second.mE0;
      mChunkWidth = second.mChunkWidth;
      mChunkHeight = second.mChunkHeight;
      mInputOutput = second.mInputOutput;
      mNonstaticStatic = second.mNonstaticStatic;
      mDirectIndirect = second.mDirectIndirect;
      mNonfixedFixed = second.mNonfixedFixed;
      mRegFifo = second.mRegFifo;
      mLmIndex = second.mLmIndex;
      mRoiDepInfoN = second.mRoiDepInfoN;
      mRoiDepInfoS = second.mRoiDepInfoS;
      mRoiDepInfoE = second.mRoiDepInfoE;
      mRoiDepInfoW = second.mRoiDepInfoW;

	  mContigDataDesc = second.mContigDataDesc;
      mOffsetArray = second.mOffsetArray;
      mConfiguredFlag = second.mConfiguredFlag;
   }

   //this port information comes via the offline world to characterize the port
   //and allow sanity checks to be done when the user connects something
   //(e.g. does e0 of the connected image/buffer match the port?)
   std::string mPortIdentifier;
   e0_desc mE0;
   int32_t mChunkWidth;
   int32_t mChunkHeight;
   int8_t mInputOutput;     //0=input, 1=output
   int8_t mNonstaticStatic; //0=nonstatic, 1=static
   int8_t mDirectIndirect;  //0=direct, 1=indirect
   int8_t mNonfixedFixed;   //0=nonfixed, 1=fixed
   int8_t mRegFifo;         //0=regular, 1=fifo
   int8_t mLmIndex;
   int8_t mRoiDepInfoN;
   int8_t mRoiDepInfoS;
   int8_t mRoiDepInfoE;
   int8_t mRoiDepInfoW;

   //this information comes from the user at run-time on the host processor
   icp::DataDescriptor mContigDataDesc; //description of src/dst data buffer
   icp::DataDescriptor mOffsetArray;    //description of offset array in indirect case
   int32_t mConfiguredFlag;

   bool IsInput()
   {
      if (mInputOutput == 0) return true;
      else return false;
   }

   bool IsOutput()
   {
      if (mInputOutput == 1) return true;
      else return false;
   }

   bool IsDirect()
   {
      if (mDirectIndirect == 0) return true;
      else return false;
   }

   bool IsIndirect()
   {
      if (mDirectIndirect == 1) return true;
      else return false;
   }

   bool IsNonStatic()
   {
      if (mNonstaticStatic == 0) return true;
      else return false;
   }   

   bool IsStatic()
   {
      if (mNonstaticStatic == 1) return true;
      else return false;
   }

   bool IsNonFixed()
   {
      if (mNonfixedFixed == 0) return true;
      else return false;
   }

   bool IsFixed()
   {
      if (mNonfixedFixed == 1) return true;
      else return false;
   }

   bool IsReg()
   {
      if (mRegFifo == 0) return true;
      else return false;
   }

   bool IsFifo()
   {
      if (mRegFifo == 1) return true;
      else return false;
   }
};

#endif //_ACF_PROCESS_PORTINFO_HPP
