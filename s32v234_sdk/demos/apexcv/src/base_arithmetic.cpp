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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <cstring>

#ifndef APEX2_EMULATE
#include <icp_data.h>

using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include <oal.h>

#include "apexcv_core.h"
#include "apexcv_arithmetic_func.h"

#include "apexcv_base_arithmetic.h"
#include "apexcv_arithmetic_ref.h"

#define SRC_WIDTH 256
#define SRC_HEIGHT 32

#define TEST_LOOP_COUNT 1

#ifndef APEX2_EMULATE
#ifdef __STANDALONE__
extern "C"
{
	unsigned long get_uptime_microS();
}
#endif
#else 
#define DEF_TIME_MEASURE 1
#include "time_measure.h"
using namespace APEX2;
unsigned long get_uptime_microS() {
	return (unsigned long)FSL_Ticks();
}
#endif

#include "apexcv_core.h"
//TODO: this test code badly needs to be refactored
using namespace apexcv;

namespace apexcv {
	//TODO: C++03 workaround. Use std::is_same<> from <type_traits> when C++11 is supported.

	// Fake multiply test, since multiply is not yet implemented on APEX yet. 
	template <typename S, typename D>
	int test_mult(S* lSrc0, S* lSrc1, D* lDst, int lSrcWidth, int lSrcHeight) {
		int lRetVal = 0;
		int cvTp = cv_type<S>(1), cvDTp = cv_type<D>(1);
		Mat cvSrc0(lSrcHeight, lSrcWidth, cvTp, (void*)lSrc0);
		Mat cvSrc1(lSrcHeight, lSrcWidth, cvTp, (void*)lSrc1);
		Mat cvDst(lSrcHeight, lSrcWidth, cvDTp);

		multiply(cvSrc0, cvSrc1, cvDst);

		return lRetVal;
	}

	template <typename S, typename D>
	int test_abs(S* lSrc, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;
		int cvTp = cv_type<S>(1), cvDTp = cv_type<D>(1);
		Mat cvSrc(lSrcHeight, lSrcWidth, cvTp, (void*) lSrc);
		Mat cvDst(lSrcHeight, lSrcWidth, cvDTp);

	DATATYPE s_dt;
		DATATYPE d_dt;

		s_dt = get_datatype<S>();
		d_dt = get_datatype<D>();

		if (s_dt >= 0 && d_dt >= 0)
		{
	/*	
				DataDescriptor lSrcImg;
			lSrcImg.InitManual(lSrcWidth, lSrcHeight, lSrc, lSrc, s_dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, d_dt);

			if (lSrcImg.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				apexcv::Arithmetic a;
				//run implementation
				lRetVal = a.abs(lSrcImg, lDstImg);
				*/
				//obtain dst data pointers
				D* lpDstImg = (D*)cvDst.data;
				cvDst = abs(cvSrc);
				DataDescriptor lDstRef(lSrcWidth, lSrcHeight, d_dt);
				D* lpDstRef = (D*)lDstRef.GetDataPtr();
				abs_ref<S, D>(lSrc, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (cvDst == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;
				/*
			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);*/
			lDstRef.SetFreeOnExit(true);
		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_absdiff(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;
		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.absdiff(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				absdiff_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_accumulate(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DataDescriptor lSrc0Img;
		DataDescriptor lSrc1Img;
		DataDescriptor lDstImg;
		DataDescriptor lDstRef;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, DATATYPE_16S);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, DATATYPE_16S);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.accumulate(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				int16_t* lpDstImg = (int16_t*)lDstImg.GetDataPtr();
				int16_t* lpDstRef = (int16_t*)lDstRef.GetDataPtr();

				accumulate_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_accumulateSquared(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight, uint8_t scale)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, DATATYPE_16S);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, DATATYPE_16S);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.accumulateSquared(lSrc0Img, lSrc1Img, lDstImg, scale);

				//obtain dst data pointers
				int16_t* lpDstImg = (int16_t*)lDstImg.GetDataPtr();
				int16_t* lpDstRef = (int16_t*)lDstRef.GetDataPtr();

				accumulate_squared_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight, scale);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_accumulateWeighted(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight, uint8_t alpha)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.accumulateWeighted(lSrc0Img, lSrc1Img, lDstImg, alpha);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				accumulate_weighted_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight, alpha);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_add(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;
		int cvTp = cv_type<S>(1);
		Mat cvS0(lSrcHeight, lSrcWidth, cvTp, lSrc0);
		Mat cvS1(lSrcHeight, lSrcWidth, cvTp, lSrc1);
		Mat cvDst(lSrcHeight, lSrcWidth, cvTp);
		add(cvS0, cvS1, cvDst);

		DATATYPE dt;
		dt = get_datatype<S>();
		/*
		apexcv::Arithmetic a;
		
		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, lSrc0, dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, lSrc1, dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				DataDescriptor mask;
				//run implementation
				lRetVal = a.add(lSrc0Img, lSrc1Img, lDstImg, mask);
*/
				//obtain dst data pointers
				DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);
				S* lpDstImg = (S*)cvDst.data;
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				add_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (cvDst == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			/*}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}
*/
		return lRetVal;
	}

	template <typename S>
	int test_and(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.bitwiseAND(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				and_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S, typename D>
	int test_clz(S* lSrc, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE s_dt;
		DATATYPE d_dt;

		s_dt = get_datatype<S>();
		d_dt = get_datatype<D>();

		if (s_dt >= 0 && d_dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrcImg;
			lSrcImg.InitManual(lSrcWidth, lSrcHeight, lSrc, (void *)OAL_MemoryReturnAddress((void *)lSrc, ACCESS_PHY), s_dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, d_dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, d_dt);

			if (lSrcImg.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.clz(lSrcImg, lDstImg);

				//obtain dst data pointers
				D* lpDstImg = (D*)lDstImg.GetDataPtr();
				D* lpDstRef = (D*)lDstRef.GetDataPtr();

				clz_ref<S, D>(lSrc, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_magnitude(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, DATATYPE_16U);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, DATATYPE_16U);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//obtain dst data pointers
				uint16_t* lpDstImg = (uint16_t*)lDstImg.GetDataPtr();
				uint16_t* lpDstRef = (uint16_t*)lDstRef.GetDataPtr();

				magnitude_ref<S, uint16_t>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//run implementation
				lRetVal = a.magnitude(lSrc0Img, lSrc1Img, lDstImg);

				int idx = 0;
				int nrDiff = 0;
				int nrDiff1 = 0;
				for (int i = 0; i < lSrcHeight; ++i) {
					for (int j = 0; j < lSrcWidth; ++j, ++idx) {
						int diff = (int) std::abs((int)(lpDstImg[idx] - lpDstRef[idx]));
						if (diff == 1) {
							++nrDiff1;
						}
						if (diff > 1) {
							++nrDiff;
						}
					}
				}

				lRetVal |= (nrDiff > lSrcHeight*lSrcWidth*0.05);

				//compare results
				//if (lDstImg == lDstRef)
					//lRetVal |= 0;
				//else
					//lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_not(S* lSrc, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;
		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrcImg;
			lSrcImg.InitManual(lSrcWidth, lSrcHeight, lSrc, (void *)OAL_MemoryReturnAddress((void *)lSrc, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrcImg.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.bitwiseNOT(lSrcImg, lDstImg);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				not_ref<S>(lSrc, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_or(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.bitwiseOR(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				or_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_sub(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, DATATYPE_16S);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, DATATYPE_16S);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.subtract(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				int16_t* lpDstImg = (int16_t*)lDstImg.GetDataPtr();
				int16_t* lpDstRef = (int16_t*)lDstRef.GetDataPtr();

				sub_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_threshold(S* lSrc, int lSrcWidth, int lSrcHeight, unsigned int threshold)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;
		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrcImg;
			lSrcImg.InitManual(lSrcWidth, lSrcHeight, lSrc, (void *)OAL_MemoryReturnAddress((void *)lSrc, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, DATATYPE_08U);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, DATATYPE_08U);

			if (lSrcImg.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.threshold(lSrcImg, lDstImg, threshold);

				//obtain dst data pointers
				uint8_t* lpDstImg = (uint8_t*)lDstImg.GetDataPtr();
				uint8_t* lpDstRef = (uint8_t*)lDstRef.GetDataPtr();

				threshold_ref<S>(lSrc, lSrcWidth, threshold, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}

	template <typename S>
	int test_xor(S* lSrc0, S* lSrc1, int lSrcWidth, int lSrcHeight)
	{
		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt;

		dt = get_datatype<S>();

		if (dt >= 0) {
			//initialize and populate buffers
			DataDescriptor lSrc0Img;
			lSrc0Img.InitManual(lSrcWidth, lSrcHeight, lSrc0, (void *)OAL_MemoryReturnAddress((void *)lSrc0, ACCESS_PHY), dt);
			DataDescriptor lSrc1Img;
			lSrc1Img.InitManual(lSrcWidth, lSrcHeight, lSrc1, (void *)OAL_MemoryReturnAddress((void *)lSrc1, ACCESS_PHY), dt);
			DataDescriptor lDstImg(lSrcWidth, lSrcHeight, dt);
			DataDescriptor lDstRef(lSrcWidth, lSrcHeight, dt);

			if (lSrc0Img.IsOK() && lSrc1Img.IsOK() && lDstImg.IsOK() && lDstRef.IsOK())
			{
				//run implementation
				lRetVal = a.bitwiseXOR(lSrc0Img, lSrc1Img, lDstImg);

				//obtain dst data pointers
				S* lpDstImg = (S*)lDstImg.GetDataPtr();
				S* lpDstRef = (S*)lDstRef.GetDataPtr();

				xor_ref<S>(lSrc0, lSrcWidth, lSrc1, lSrcWidth, lpDstRef, lSrcWidth, lSrcWidth, lSrcHeight);

				//compare results
				if (lDstImg == lDstRef)
					lRetVal |= 0;
				else
					lRetVal |= 1;

			}
			else {
				lRetVal |= 1;
			}

			lDstImg.SetFreeOnExit(true);
			lDstRef.SetFreeOnExit(true);

		}
		else {
			lRetVal |= 1;
		}

		return lRetVal;
	}


	void test_apexcv_arithmetic()
	{
		int e = 0;
		unsigned int *src0 = (unsigned int *)OAL_MemoryAllocFlag(SRC_HEIGHT*SRC_WIDTH*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
		unsigned int *src1 = (unsigned int *)OAL_MemoryAllocFlag(SRC_HEIGHT*SRC_WIDTH*4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|OAL_MEMORY_FLAG_CONTIGUOUS);
		unsigned int *dst = (unsigned int *)OAL_MemoryAllocFlag(SRC_HEIGHT*SRC_WIDTH * 4, OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE) | OAL_MEMORY_FLAG_CONTIGUOUS);


#ifdef __STANDALONE__
		// get_uptime_microS instead of rand
		for (int y = 0; y < SRC_HEIGHT; ++y) {
			for (int x = 0; x < SRC_WIDTH; ++x) {
				src0[y * SRC_WIDTH + x] = ((get_uptime_microS() & 0x3) << 30) | ((get_uptime_microS() % 0x10000) << 15) | get_uptime_microS() % 0x10000;
				src1[y * SRC_WIDTH + x] = ((get_uptime_microS() & 0x3) << 30) | ((get_uptime_microS() % 0x10000) << 15) | get_uptime_microS() % 0x10000;
			}
		}
#else
		// get_uptime_microS instead of rand
		for (int y = 0; y < SRC_HEIGHT; ++y) {
			for (int x = 0; x < SRC_WIDTH; ++x) {
				src0[y * SRC_WIDTH + x] = ((rand() & 0x3) << 30) | ((rand() % 0x10000) << 15) | rand() % 0x10000;
				src1[y * SRC_WIDTH + x] = ((rand() & 0x3) << 30) | ((rand() % 0x10000) << 15) | rand() % 0x10000;
			}
		}	
#endif

		//Arithmetic test
		printf("Test ApexCV arithmetic start\n");

		{
			test_mult<int8_t, int8_t>((int8_t*)src0, (int8_t*)src1, (int8_t*)dst, SRC_WIDTH, SRC_HEIGHT);
		}
		//Abs test
		{
			printf("  Test ApexCV abs start\n");
			//08u
			e = test_abs<int8_t, uint8_t>((int8_t*)src0, SRC_WIDTH, SRC_HEIGHT);
			if (e)   printf("    08u Done                                     FAIL\n");
			else     printf("    08u Done                                     PASS\n");

			printf("  Test ApexCV abs end\n");
		}

		//Absdiff test
   {
	   printf("  Test ApexCV absdiff start\n");

	   //08u
	   e = test_absdiff<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV absdiff end\n");
   }

   //Accumulate test
   {
	   printf("  Test ApexCV accumulate start\n");

	   //08u
	   e = test_accumulate<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV accumulate end\n");
   }

   //Accumulate Squared test
   {
	   printf("  Test ApexCV accumulate squared start\n");

	   //08u
	   e = test_accumulateSquared<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT, 8);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV accumulate squared end\n");
   }

   //Accumulate weighted test
   {
	   printf("  Test ApexCV accumulate weighted start\n");

	   //08u
	   e = test_accumulateWeighted<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT, 179);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV accumulate weighted end\n");
   }

   //Add test
   {
	   printf("  Test ApexCV add start\n");

	   //08u
	   e = test_add<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16s
	   e = test_add<int16_t>((int16_t*)src0, (int16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16s Done                                     FAIL\n");
	   else     printf("    16s Done                                     PASS\n");

	   printf("  Test ApexCV add end\n");
   }

   //And test
   {
	   printf("  Test ApexCV and start\n");

	   //08u
	   e = test_and<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16u
	   e = test_and<uint16_t>((uint16_t*)src0, (uint16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16u Done                                     FAIL\n");
	   else     printf("    16u Done                                     PASS\n");

	   //32u
	   e = test_and<uint32_t>((uint32_t*)src0, (uint32_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    32u Done                                     FAIL\n");
	   else     printf("    32u Done                                     PASS\n");

	   printf("  Test ApexCV and end\n");
   }

   //Clz test
   {
	   printf("  Test ApexCV clz start\n");

	   //08u
	   e = test_clz<uint8_t, uint8_t>((uint8_t*)src0, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //08s
	   e = test_clz<int8_t, uint8_t>((int8_t*)src0, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08s Done                                     FAIL\n");
	   else     printf("    08s Done                                     PASS\n");

	   //16u
	   e = test_clz<uint16_t, uint8_t>((uint16_t*)src0, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16u Done                                     FAIL\n");
	   else     printf("    16u Done                                     PASS\n");

	   //16s
	   e = test_clz<int16_t, uint8_t>((int16_t*)src0, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16s Done                                     FAIL\n");
	   else     printf("    16s Done                                     PASS\n");

	   printf("  Test ApexCV clz end\n");
   }

   //Magnitude test
   {
	   printf("  Test ApexCV magnitude start\n");

	   //16s
	   e = test_magnitude<int16_t>((int16_t*)src0, (int16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16s Done                                     FAIL\n");
	   else     printf("    16s Done                                     PASS\n");

	   printf("  Test ApexCV magnitude end\n");
   }

   //Not test
   {
	   printf("  Test ApexCV not start\n");

	   //08u
	   e = test_not<uint8_t>((uint8_t*)src0, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   printf("  Test ApexCV not end\n");
   }

   //Or test
   {
	   printf("  Test ApexCV or start\n");

	   //08u
	   e = test_or<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16u
	   e = test_or<uint16_t>((uint16_t*)src0, (uint16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16u Done                                     FAIL\n");
	   else     printf("    16u Done                                     PASS\n");

	   //32u
	   e = test_or<uint32_t>((uint32_t*)src0, (uint32_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    32u Done                                     FAIL\n");
	   else     printf("    32u Done                                     PASS\n");

	   printf("  Test ApexCV or end\n");
   }

   //Sub test
   {
	   printf("  Test ApexCV sub start\n");

	   //08u
	   e = test_sub<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16s
	   e = test_sub<int16_t>((int16_t*)src0, (int16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16s Done                                     FAIL\n");
	   else     printf("    16s Done                                     PASS\n");

	   printf("  Test ApexCV sub end\n");
   }

   //Threshold test
   {
	   printf("  Test ApexCV threshold start\n");

	   //08u
	   e = test_threshold<uint8_t>((uint8_t*)src0, SRC_WIDTH, SRC_HEIGHT, 0xF0);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16u
	   e = test_threshold<uint16_t>((uint16_t*)src0, SRC_WIDTH, SRC_HEIGHT, 0xABCD);
	   if (e)   printf("    16u Done                                     FAIL\n");
	   else     printf("    16u Done                                     PASS\n");

	   //32u
	   e = test_threshold<uint32_t>((uint32_t*)src0, SRC_WIDTH, SRC_HEIGHT, 0x1234ABCD);
	   if (e)   printf("    32u Done                                     FAIL\n");
	   else     printf("    32u Done                                     PASS\n");

	   printf("  Test ApexCV threshold end\n");
   }

   //Xor test
   {
	   printf("  Test ApexCV xor start\n");

	   //08u
	   e = test_xor<uint8_t>((uint8_t*)src0, (uint8_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    08u Done                                     FAIL\n");
	   else     printf("    08u Done                                     PASS\n");

	   //16u
	   e = test_xor<uint16_t>((uint16_t*)src0, (uint16_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    16u Done                                     FAIL\n");
	   else     printf("    16u Done                                     PASS\n");

	   //32u
	   e = test_xor<uint32_t>((uint32_t*)src0, (uint32_t*)src1, SRC_WIDTH, SRC_HEIGHT);
	   if (e)   printf("    32u Done                                     FAIL\n");
	   else     printf("    32u Done                                     PASS\n");

	   printf("  Test ApexCV xor end\n");
   }

   OAL_MemoryFree(src0);
   OAL_MemoryFree(src1);


   //Arithmetic test done
   printf("Test ApexCV arithmetic end\n");
	}

} // end of namespace