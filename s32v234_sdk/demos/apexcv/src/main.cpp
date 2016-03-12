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

/****************************************************************************
* Includes
****************************************************************************/
#include "test_apexcv.h"
using namespace apexcv;

#ifndef APEX2_EMULATE
#ifndef APEXCV
#define APEXCV 1

#include <apex.h>
#include <icp_data.h>

using namespace icp;
#endif

#include <oal.h>


#endif

#ifdef APEXCV
#include "apexcv_mat.hpp"
#include "apexcv_core.h"
#include "apexcv_arithmetic_func.h"
using namespace apexcv;
#else
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

#ifdef APEX2_EMULATE
#include "acf_lib.hpp"
#endif

/****************************************************************************
* Main function
****************************************************************************/

int main(int, char**)
{

#ifndef APEX2_EMULATE 
  #ifndef __STANDALONE__
  OAL_MemoryAllocInit();
  #endif
	ACF_Init();
	using namespace icp;
#endif
	 test_apexcv_filter();
	 test_apexcv_color_conversion();
	 test_apexcv_arithmetic();
	 test_apexcv_interpolation();
	 test_apexcv_histogram(); 
	 test_apexcv_integral_image();

	return 0;
}

