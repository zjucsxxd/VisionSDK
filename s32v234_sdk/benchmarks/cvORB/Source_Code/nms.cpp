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

#include "nms.h"

void nms(const unsigned char* apcIn, unsigned char* apOut,
  int aInStride, int aOutStride,
 int aTileWidth, int aTileHeight)
{
  for (int y = 0; y < aTileHeight; ++y)
  {
    for (int x = 0; x < aTileWidth; ++x)
    {
      unsigned char v = apcIn[x];
	  // compare value with its 8 neighbors and set it to zero if it is lower than one of them
      bool fail = v <= apcIn[x - 1 - aInStride];
      fail = fail || (v <= apcIn[x - aInStride]);
      fail = fail || (v <= apcIn[x + 1 - aInStride]);
      fail = fail || (v <= apcIn[x - 1]);
      fail = fail || (v <= apcIn[x + 1]);
      fail = fail || (v <= apcIn[x - 1 + aInStride]);
      fail = fail || (v <= apcIn[x + aInStride]);
      fail = fail || (v <= apcIn[x + 1 + aInStride]);
      if (fail)
      {
        v = 0;
      }
      
      apOut[x] = v;
    }

    apcIn += aInStride;
    apOut += aOutStride;
  }
}
