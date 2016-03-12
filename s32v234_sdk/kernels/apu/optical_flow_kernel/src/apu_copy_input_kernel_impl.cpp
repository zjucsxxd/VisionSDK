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
* \file apu_copy_input_kernel_impl.cpp
* \brief Copies the input to the output - implementations for APEX
* \author Anca Dima
* \version
* \date
****************************************************************************/

#ifdef ACF_KERNEL_IMPLEMENTATION


#include "apu_copy_input_kernel_impl.h"

void copy_input_in08u_out08u(vec08u* src, vec08u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec08u* crtIn = src;
	vec08u* crtOut = out;
	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = crtIn[j];
		}
		crtIn += sstrIn;
		crtOut += sstrOut;
	}
}


void copy_input_in08u_out16u(vec08u* src, vec16u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec08u* crtIn = src;
	vec16u* crtOut = out;

	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = (vec16u) crtIn[j];
		}
		crtIn += sstrIn;
		crtOut += sstrOut;
	}
}


void copy_input_in16s_out16s(vec16s* src, vec16s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec16s* crtIn = src;
	vec16s* crtOut = out;
	int16s instrLen = sstrIn;
	int16s outstrLen = sstrOut;
	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = crtIn[j];
		}
		crtIn += instrLen;
		crtOut += outstrLen;
	}
}

#ifndef inputShiftFact
#define inputShiftFact  3 
#endif

void copy_input_in16u_out16s(vec16u* src, vec16s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec16u* crtIn = src;
	vec16s* crtOut = out;
	int16s instrLen = sstrIn;
	int16s outstrLen = sstrOut;

	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = (vec16s)crtIn[j];
		}
		crtIn += instrLen;
		crtOut += outstrLen;
	}
}


void copy_input_in32s_out32s(vec32s* src, vec32s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec32s* crtIn = src;
	vec32s* crtOut = out;
	int16s instrLen = sstrIn;
	int16s outstrLen = sstrOut;

	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = crtIn[j];
		}
		crtIn += instrLen;
		crtOut += outstrLen;
	}
}


void copy_input_in32u_out32u(vec32u* src, vec32u* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec32u* crtIn = src;
	vec32u* crtOut = out;

	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = crtIn[j];
		}
		crtIn += sstrIn;
		crtOut += sstrOut;
	}
}



void copy_input_in32u_out32s(vec32u* src, vec32s* out, int16s bw, int16s bh, int16s sstrIn, int16s sstrOut)
{
	// copy input to output data in order to keep
	vec32u* crtIn = src;
	vec32s* crtOut = out;

	for (int i = 0; i < bh; ++i)
	{
		for (int j = 0; j < bw; ++j){
			crtOut[j] = (vec32s) crtIn[j];
		}
		crtIn += sstrIn;
		crtOut += sstrOut;
	}
}


#endif //#ifdef ACF_KERNEL_IMPLEMENTATION
