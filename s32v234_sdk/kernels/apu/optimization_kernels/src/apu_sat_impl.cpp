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

#ifdef APEX2_EMULATE
#include <apu_lib.hpp>
#include <apu_vec.hpp>
//#include <acf_kernel.hpp>
using namespace APEX2;
#endif

#include "apu_sat_impl.h"
#include "apu_add_impl.h"

static inline vec32u vectorMoveShiftRight32(vec32u aV, int aNElements)
{
  vec16u vL = vec16u(aV);
  vec16u vH = vec16u(aV >> 16);
  for (int i = 0; i < aNElements; ++i)
  {
    vL = vmsr(vL);
    vH = vmsr(vH);
  }
  aV = ((vec32u)vH << 16) | vec32u(vL);
  return aV;
}


static inline vec32s vectorMoveShiftRight32s(vec32s aV, int aNElements)
{
	vec16u vL = vec16u(aV);
	vec16s vH = vec16s(aV >> 16);
	for (int i = 0; i < aNElements; ++i)
	{
		vL = vmsr(vL);
		vH = vmsr(vH);
	}
	aV = ((vec32s)vH << 16) | vec32s(vL);
	return aV;
}


static inline vec32u interBlockAccum32(vec32u aV)
{
  aV = vectorMoveShiftRight32(aV, 1);
  int stillShift = APU_VSIZE;
  for (int i = 1; i <= stillShift; i <<= 1){
	  aV += vectorMoveShiftRight32(aV, i);
  }
  /*
  This is what is done in the loop above with 32 CUs. The loop is valid also for 64 CUs
  aV += vectorMoveShiftRight32(aV, 1);
  aV += vectorMoveShiftRight32(aV, 2);
  aV += vectorMoveShiftRight32(aV, 4);
  aV += vectorMoveShiftRight32(aV, 8);
  aV += vectorMoveShiftRight32(aV, 16);
  aV += vectorMoveShiftRight32(aV, 32);*/
  return aV;
}

static inline vec32s interBlockAccum32s(vec32s aV)
{
	aV = vectorMoveShiftRight32s(aV, 1);
	int stillShift = APU_VSIZE;
	for (int i = 1; i <= stillShift; i <<= 1){
		aV += vectorMoveShiftRight32s(aV, i);
	}
	/*
	This is what is done in the loop above with 32 CUs. The loop is valid also for 64 CUs
	aV += vectorMoveShiftRight32(aV, 1);
	aV += vectorMoveShiftRight32(aV, 2);
	aV += vectorMoveShiftRight32(aV, 4);
	aV += vectorMoveShiftRight32(aV, 8);
	aV += vectorMoveShiftRight32(aV, 16);
	aV += vectorMoveShiftRight32(aV, 32);*/
	return aV;
}




static inline void interBlockAccum64(vec32u* aVHigh, vec32u* aVLow)
{
	*aVHigh = vectorMoveShiftRight32(*aVHigh, 1);
	*aVLow = vectorMoveShiftRight32(*aVLow, 1);

	int stillShift = APU_VSIZE;
	
	for (int i = 1; i <= stillShift; i <<= 1){
		vec32u tmpHigh, tmpLow;
		vec32u shiftedHigh = vectorMoveShiftRight32(*aVHigh, i);
		vec32u shiftedLow = vectorMoveShiftRight32(*aVLow, i);
		add_in64u_out64u(&tmpHigh, &tmpLow, aVHigh, aVLow, &shiftedHigh, &shiftedLow, 1, 1, 1, 1);
		*aVHigh = tmpHigh;
		*aVLow = tmpLow;
	}	
}


static inline void interBlockAccum64s(vec32s* aVHigh, vec32u* aVLow)
{
	*aVHigh = vectorMoveShiftRight32s(*aVHigh, 1);
	*aVLow = vectorMoveShiftRight32(*aVLow, 1);

	int stillShift = APU_VSIZE;

	for (int i = 1; i <= stillShift; i <<= 1){
		vec32s tmpHigh; 
		vec32u tmpLow;
		vec32s shiftedHigh = vectorMoveShiftRight32s(*aVHigh, i);
		vec32u shiftedLow = vectorMoveShiftRight32(*aVLow, i);
		add_in64s_out64s(&tmpHigh, &tmpLow, aVHigh, aVLow, &shiftedHigh, &shiftedLow, 1, 1, 1, 1);
		*aVHigh = tmpHigh;
		*aVLow = tmpLow;
	}
}


void sat32(vec32u* apDest, vec32u* apPrevRow,
  const vec08u* apcSrc,
  int inStrideW, int outStrideW,
  int bw, int bh, int08u aFirstTile)
{
  int destinationStride32 = outStrideW >> 2;
  //null the previous row in the first tile
  //TODO: is it possible outside the kernel implementation function?
  if (aFirstTile)
  {
    for (int16s x = 0; x < bw; ++x)
    {
      apPrevRow[x] = 0;
    }
  }

  //first step uses the previous row
  vec32u blockAccum = 0;
  for (int16s x = 0; x < bw; ++x) chess_prepare_for_pipelining
  {
    blockAccum += (vec32u)(apcSrc[x]);
    apDest[x] = blockAccum + apPrevRow[x];
  }

  blockAccum = interBlockAccum32(blockAccum);

  for (int16s x = 0; x < bw; ++x)
  {
    apDest[x] += blockAccum;
  }

  for (int16s y = 1; y < bh; ++y)
  {
    apDest += destinationStride32;
    apcSrc += inStrideW;

    blockAccum = 0;
    for (int16s x = 0; x < bw; ++x)
    {
      blockAccum += (vec32u)(apcSrc[x]);
      apDest[x] = blockAccum + apDest[x - destinationStride32];
    }

    blockAccum = interBlockAccum32(blockAccum);

    for (int16s x = 0; x < bw; ++x)
    {
      apDest[x] += blockAccum;
    }
  }

  //save the last row as the previous row
  for (int16s x = 0; x < bw; ++x)
  {
    apPrevRow[x] = apDest[x];
  }
}


void sat_sgn_32(vec32s* apDest, vec32u* apAbsDest, vec32s* apPrevRow, vec32u* apPrevAbsRow,
	const vec08s* apcSrc,
	int inStrideW, int outStrideW,
	int bw, int bh, int08u aFirstTile)
{
	int destinationStride32 = outStrideW >> 2;
	//null the previous row in the first tile
	//TODO: is it possible outside the kernel implementation function?
	if (aFirstTile)
	{
		for (int16s x = 0; x < bw; ++x)
		{
			apPrevRow[x] = 0;
			apPrevAbsRow[x] = 0;
		}
	}
	
	//first step uses the previous row
	vec32s blockAccum = 0, blockAbsAccum = 0;
	for (int16s x = 0; x < bw; ++x) chess_prepare_for_pipelining
	{
		blockAccum += (vec32s)(apcSrc[x]);
		apDest[x] = blockAccum + apPrevRow[x];

		blockAbsAccum += (vec32s)vabs(apcSrc[x]);
		apAbsDest[x] = blockAbsAccum + apPrevAbsRow[x];

	}

	blockAccum =  interBlockAccum32s(blockAccum);
	blockAbsAccum = (vec32s)interBlockAccum32(blockAbsAccum);

	for (int16s x = 0; x < bw; ++x)
	{
		apDest[x] += blockAccum;
		apAbsDest[x] += blockAbsAccum;
	}

	for (int16s y = 1; y < bh; ++y)
	{
		apDest += destinationStride32;
		apAbsDest += destinationStride32;

		apcSrc += inStrideW;

		blockAccum = 0;
		for (int16s x = 0; x < bw; ++x)
		{
			blockAccum += (vec32s)(apcSrc[x]);
			apDest[x] = blockAccum + apDest[x - destinationStride32];

			blockAbsAccum += (vec32s)vabs(apcSrc[x]);
			apAbsDest[x] = blockAbsAccum + apAbsDest[x - destinationStride32];

		}

		blockAccum = interBlockAccum32s(blockAccum);
		blockAbsAccum = (vec32s)interBlockAccum32(blockAbsAccum);

		for (int16s x = 0; x < bw; ++x)
		{
			apDest[x] += blockAccum;
			apAbsDest[x] += blockAbsAccum;
		}
	}
	
	//save the last row as the previous row
	for (int16s x = 0; x < bw; ++x)
	{
		apPrevRow[x] = apDest[x];
		apPrevAbsRow[x] = apAbsDest[x];
	}
}


/*
void sat_in32u_out64u(vec32u* apDestHigh, vec32u* apDestLow,
	vec32u* apPrevRowHigh, vec32u* apPrevRowLow,
	const vec32u* apcSrc,
	int16s bw, int16s bh, int16s inStrideW, int16s outStrideW, int08u aFirstTile)
{
	//null the previous row in the first tile
	//TODO: is it possible outside the kernel implementation function?
	if (aFirstTile)
	{
		for (int16s x = 0; x < bw; ++x)
		{
			apPrevRowLow[x] = 0;
			apPrevRowHigh[x] = 0;
		}
	}

	//first step uses the previous row
	vec32u blockAccumLow = 0, blockAccumHigh = 0, newblockAccumLow = 0, newblockAccumHigh = 0, dummyHigh = 0;
	for (int16s x = 0; x < bw; ++x)
	{
		vec32u v = (vec32u)(apcSrc[x]);
		add_in64u_out64u(&newblockAccumHigh, &newblockAccumLow, &dummyHigh, &v, &blockAccumHigh, &blockAccumLow, 1, 1, 1, 1);
		blockAccumHigh = newblockAccumHigh;
		blockAccumLow = newblockAccumLow;

		add_in64u_out64u(&apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, &apPrevRowHigh[x], &apPrevRowLow[x], 1, 1, 1, 1);
	}

	interBlockAccum64(&blockAccumHigh, &blockAccumLow);

	for (int16s x = 0; x < bw; ++x)
	{
		add_in64u_out64u(&newblockAccumHigh, &newblockAccumLow, &apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, 1, 1, 1, 1);
		apDestHigh[x] = newblockAccumHigh;
		apDestLow[x] = newblockAccumLow;
	}

	for (int16s y = 1; y < bh; ++y)
	{
		apDestLow += outStrideW;
		apDestHigh += outStrideW;
		apcSrc += inStrideW;

		blockAccumHigh = 0, blockAccumLow = 0, newblockAccumHigh = 0, newblockAccumLow = 0;
		for (int16s x = 0; x < bw; ++x)
		{
			vec32u v = (vec32u)(apcSrc[x]);
			add_in64u_out64u(&newblockAccumHigh, &newblockAccumLow, &blockAccumHigh, &blockAccumLow, &dummyHigh, &v, 1, 1, 1, 1);
			blockAccumHigh = newblockAccumHigh;
			blockAccumLow = newblockAccumLow;

			add_in64u_out64u(&apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, &apDestHigh[x - outStrideW], &apDestLow[x - outStrideW],1,1,1,1);			
		}

		interBlockAccum64(&blockAccumHigh, &blockAccumLow);


		for (int16s x = 0; x < bw; ++x)
		{
			add_in64u_out64u(&newblockAccumHigh, &newblockAccumLow, &apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, 1,1,1,1);
			apDestHigh[x] = newblockAccumHigh;
			apDestLow[x] = newblockAccumLow;
		}
	}

	//save the last row as the previous row
	for (int16s x = 0; x < bw; ++x)
	{
		apPrevRowHigh[x] = apDestHigh[x];
		apPrevRowLow[x] = apDestLow[x];
	}
}


*/

void sat_in32s_out64s(vec32s* apDestHigh, vec32u* apDestLow,
	vec32s* apPrevRowHigh, vec32u* apPrevRowLow, const vec32s* apcSrc,
	int16s bw, int16s bh, int16s inStrideW, int16s outStrideW, int08u aFirstTile){


	//null the previous row in the first tile
	//TODO: is it possible outside the kernel implementation function?
	if (aFirstTile)
	{
		for (int16s x = 0; x < bw; ++x)
		{
			apPrevRowLow[x] = 0;
			apPrevRowHigh[x] = 0;
		}
	}

	//first step uses the previous row
	vec32u blockAccumLow = 0, newblockAccumLow = 0;
	vec32s blockAccumHigh = 0, newblockAccumHigh = 0, dummyHigh = 0;
	for (int16s x = 0; x < bw; ++x)
	{
		vec32u v = (vec32u) apcSrc[x];
		vif(apcSrc[x] < 0) {
			dummyHigh = -1;
		} velse{
			dummyHigh = 0;
		}vendif

		add_in64s_out64s(&newblockAccumHigh, &newblockAccumLow, &dummyHigh, &v, &blockAccumHigh, &blockAccumLow, 1, 1, 1, 1);
		blockAccumHigh = newblockAccumHigh;
		blockAccumLow = newblockAccumLow;

		add_in64s_out64s(&apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, &apPrevRowHigh[x], &apPrevRowLow[x], 1, 1, 1, 1);
	}

	interBlockAccum64s(&blockAccumHigh, &blockAccumLow);

	for (int16s x = 0; x < bw; ++x)
	{
		add_in64s_out64s(&newblockAccumHigh, &newblockAccumLow, &apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, 1, 1, 1, 1);
		apDestHigh[x] = newblockAccumHigh;
		apDestLow[x] = newblockAccumLow;
	}

	for (int16s y = 1; y < bh; ++y)
	{
		apDestLow += outStrideW;
		apDestHigh += outStrideW;
		apcSrc += inStrideW;

		blockAccumHigh = 0, blockAccumLow = 0, newblockAccumHigh = 0, newblockAccumLow = 0;
		for (int16s x = 0; x < bw; ++x)
		{
			vec32u v = (vec32u)(apcSrc[x]);

			vif(apcSrc[x] < 0) {
				dummyHigh = -1;
			} velse{
				dummyHigh = 0;
			}vendif


			add_in64s_out64s(&newblockAccumHigh, &newblockAccumLow, &blockAccumHigh, &blockAccumLow, &dummyHigh, &v, 1, 1, 1, 1);
			blockAccumHigh = newblockAccumHigh;
			blockAccumLow = newblockAccumLow;

			add_in64s_out64s(&apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, &apDestHigh[x - outStrideW], &apDestLow[x - outStrideW], 1, 1, 1, 1);
		}

		interBlockAccum64s(&blockAccumHigh, &blockAccumLow);


		for (int16s x = 0; x < bw; ++x)
		{
			add_in64s_out64s(&newblockAccumHigh, &newblockAccumLow, &apDestHigh[x], &apDestLow[x], &blockAccumHigh, &blockAccumLow, 1, 1, 1, 1);
			apDestHigh[x] = newblockAccumHigh;
			apDestLow[x] = newblockAccumLow;
		}
	}

	//save the last row as the previous row
	for (int16s x = 0; x < bw; ++x)
	{
		apPrevRowHigh[x] = apDestHigh[x];
		apPrevRowLow[x] = apDestLow[x];
	}

}



void sat32PlusSquared(vec32u* apDest, vec32u* apDestSquared,
  vec32u* apPrevRow, vec32u* apPrevRowSquared,
  const vec08u* apcSrc,
  int inStrideW, int outStrideW, int bw, int bh, int08u aFirstTile)
{
  int destinationStride32 = outStrideW >> 2;

  //null the previous row in the first tile
  //TODO: is it possible outside the kernel implementation function?
  if (aFirstTile)
  {
    for (int16s x = 0; x < bw; ++x)
    {
      apPrevRow[x] = 0;
      apPrevRowSquared[x] = 0;
    }
  }

  //first step uses the previous row
  vec32u blockAccum = 0;
  vec32u blockAccumSquared = 0;
  for (int16s x = 0; x < bw; ++x)
  {
    vec32u v = (vec32u)(apcSrc[x]);
    blockAccum += v;
    apDest[x] = blockAccum + apPrevRow[x];
    blockAccumSquared += v*v;
    apDestSquared[x] = blockAccumSquared + apPrevRowSquared[x];
  }

  blockAccum = interBlockAccum32(blockAccum);
  blockAccumSquared = interBlockAccum32(blockAccumSquared);

  for (int16s x = 0; x < bw; ++x)
  {
    apDest[x] += blockAccum;
    apDestSquared[x] += blockAccumSquared;
  }

  for (int16s y = 1; y < bh; ++y)
  {
    apDest += destinationStride32;
    apDestSquared += destinationStride32;
    apcSrc += inStrideW;

    blockAccum = 0;
    blockAccumSquared = 0;
    for (int16s x = 0; x < bw; ++x)
    {
      vec32u v = (vec32u)(apcSrc[x]);
      blockAccum += v;
      apDest[x] = blockAccum + apDest[x - destinationStride32];
      blockAccumSquared += v*v;
      apDestSquared[x] = blockAccumSquared + apDestSquared[x - destinationStride32];
    }

    blockAccum = interBlockAccum32(blockAccum);
    blockAccumSquared = interBlockAccum32(blockAccumSquared);

    for (int16s x = 0; x < bw; ++x)
    {
      apDest[x] += blockAccum;
      apDestSquared[x] += blockAccumSquared;
    }
  }

  //save the last row as the previous row
  for (int16s x = 0; x < bw; ++x)
  {
    apPrevRow[x] = apDest[x];
    apPrevRowSquared[x] = apDestSquared[x];
  }
}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
