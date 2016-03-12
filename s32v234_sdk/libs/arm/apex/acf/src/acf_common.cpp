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
#include <acf_common.h>
#include <icp_data.h>


int32_t RetE0DataSizeInBytes(e0_desc* lpE0)
{
   return icp::DataDescriptor::ReturnElementSize(lpE0->dataType);
}

int32_t RetE0WidthInBytes(e0_desc* lpE0)
{
   return (RetE0DataSizeInBytes(lpE0) * lpE0->x);
}

int32_t RetE0SizeInBytes(e0_desc* lpE0)
{
   return (RetE0DataSizeInBytes(lpE0) * lpE0->x * lpE0->y);
}

e0_desc RetE0Desc(icp::DATATYPE lDataType, int32_t lX, int32_t lY)
{
   e0_desc lE0;
   lE0.dataType = lDataType;
   lE0.x = lX;
   lE0.y = lY;
   return lE0;
}

int32_t E0Compare(e0_desc* lpE0_A, e0_desc* lpE0_B)
{
   int32_t lMatch = 0;

   //do the base data type sizes match?
   if (lpE0_A->dataType == lpE0_B->dataType)
   {
      //do the x and y dimensions match?
      if ((lpE0_A->x == lpE0_B->x) &&
          (lpE0_A->y == lpE0_B->y))
      {
         lMatch = 1;
      }
   }

   return lMatch;
}

