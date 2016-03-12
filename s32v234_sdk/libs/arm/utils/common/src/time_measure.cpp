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
#include "time_measure.h"
#include <stdint.h>


//OpenCV int64 is 32-bit on ARM, getTickCount doesn't work correctly...
#ifdef __STANDALONE__
	//#define USE_OPENCV_TIMER
#endif

#ifndef __STANDALONE__
	#ifdef APEX2_EMULATE
		#ifdef OPENCV_DEFINED
			#define USE_OPENCV_TIMER
		#endif
	#endif

	#ifdef __INTEGRITY
		#define USE_OPENCV_TIMER
	#endif
	
	#include "time_measure.h"
	#include "stringify_macros.h"

	#ifdef USE_OPENCV_TIMER 
		#include <opencv2/core/core.hpp>
	#else 
		#include <ctime>
	#endif
#else
#ifndef USE_OPENCV_TIMER
#include <time.h>
extern "C"
	{
		unsigned long get_uptime_microS();
	}
#else
		#include <opencv2/core/core.hpp>
#endif
#endif

//OpenCV int64 is 32-bit on ARM, getTickCount doesn't work correctly...
uint64_t FSL_Ticks()
{
#ifdef __STANDALONE__
#ifndef USE_OPENCV_TIMER
	return get_uptime_microS();
	//timespec ts;
	//clock_gettime(CLOCK_MONOTONIC, &ts);
	//return int64_t(ts.tv_sec) * 1000000000 + int64_t(ts.tv_nsec);
#else
	return cv::getTickCount();
#endif
#else
	#ifdef USE_OPENCV_TIMER
		return cv::getTickCount();
	#else
		#ifdef WIN32
			clock_t ts;
			ts = clock();
			return (uint64_t) ts;
		#else
			timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			return uint64_t(ts.tv_sec) * 1000000000 + uint64_t(ts.tv_nsec);
		#endif
	#endif
#endif
}

double FSL_GetFrequency() {
	double frequency = 1.0;
#ifdef USE_OPENCV_TIMER
	frequency = cv::getTickFrequency(); //= 1000000
#else
#ifdef WIN32
	frequency = double(CLOCKS_PER_SEC);
#else
	frequency = (double)1000000000;
#endif
#endif

	return frequency;
}
double FSL_TicksToSeconds(uint64_t ticks)
{	
  return double(ticks) / FSL_GetFrequency();
}

