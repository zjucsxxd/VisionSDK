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

/*	This application examplifies how to create processes from ACF_Graphs. 
	It exemplifies int in two different ways: 
		1. In a direct way, where the process is constructed and initialized in the main function directly
		   (exemplified by the processes: APU_ROTATE, APU_DOWNSAMPLE_UPSAMPLE, APU_HISTOGRAM.hpp, APU_FAST9.hpp, APU_FAST9_COLOR). 
		   This method is well suited for applications with not more than three processes.

		2. By constructing for each process a separate class which takes care of all initializations and process construction mechanisms.
			(exemplified by the processes: GAUSS_3x3, GAUSS_5x5, CONVOLUTION, SAT)
*/


#ifdef APEX2_EMULATE
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _APEX2_EMULATE_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#endif

#ifdef __STANDALONE__
#include "../../data/standalone/in_grey_256x256.h"
#include "../../data/standalone/in_color_256x256.h"
#include <frame_output_dcu.h>
#endif

#ifndef APEX2_EMULATE
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#ifndef APU_VSIZE
#define APU_VSIZE 32
#endif
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include     "acf_lib.hpp"
using namespace APEX2;
#endif

//to activate time measuring, please define the DEF_TIME_MEASURE in \s32v234_sdk\libs\arm\utils\common\include\config_time_measure.h
#include "time_measure.h"

//#ifdef DEF_TIME_MEASURE
//uint64_t total_apex_ticks = 0;
//uint64_t total_load_ticks = 0;
//#endif

#include "chunk_size_definitions.h"


#ifndef APEX2_EMULATE // This is needed only for the Target Compiler
#include <icp_data.h>
#include <apex.h>
#include <oal.h>

// next graphs are included in the direct way
#include "apu_rotate_graph.h"
#include <APU_ROTATE.hpp>

#include "apu_downsample_upsample_graph.h"
#include <APU_DOWNSAMPLE_UPSAMPLE.hpp>

#include "apu_histogram_graph.h"
#include <APU_HISTOGRAM.hpp>

#include "apu_fast9_graph.h"
#include <APU_FAST9.hpp>
#include <APU_FAST9_COLOR.hpp>

#else
// next graphs are included in the direct way
#include "apu_rotate_apu_process_desc.hpp"
#include "apu_downsample_upsample_apu_process_desc.hpp"
#include "apu_histogram_apu_process_desc.hpp"
#include "apu_fast9_apu_process_desc.hpp"
#include "apu_fast9_color_apu_process_desc.hpp"
///////////
#endif

//graphs included by declaring a process class around them
#include "apu_gauss_3x3_process.h"
#include "apu_gauss_5x5_process.h"
#include "apu_sat_process.h"
#include "apu_convolution_process.h"

// ////////Includes for convolution
#include "c_filter.hpp"
using namespace Convolution;
#include "symmetry_flags.h"

using namespace cv;
using namespace std;



#define IMG_WIDTH 256
#define IMG_HEIGHT 256
const int tileWidth = IMG_WIDTH / APU_VSIZE;
const int tileHeight = IMG_HEIGHT / 32;
extern const int SAT_TILE_HEIGHT;


#ifdef __INTEGRITY__
#define INPUT_ROOT "/apex/"
#else
#define INPUT_ROOT ""
#endif

#ifdef APEX2_EMULATE
int _tmain(int, _TCHAR**)
#else
int main(int, char**)
#endif
{

#ifndef APEX2_EMULATE // This is needed only for the Target Compiler
	// HW and resources init
  #ifndef __STANDALONE__
  OAL_MemoryAllocInit();
  #endif
  ACF_Init();
  using namespace icp;
#endif

#ifdef APEX2_EMULATE

	REGISTER_PROCESS_TYPE(ROTATE_PI, apu_rotate_apu_process_desc)
	REGISTER_PROCESS_TYPE(DOWNSAMPLE_UPSAMPLE_PI, apu_downsample_upsample_apu_process_desc)
	REGISTER_PROCESS_TYPE(HISTOGRAM_PI, apu_histogram_apu_process_desc)
	REGISTER_PROCESS_TYPE(FAST9_PI, apu_fast9_apu_process_desc)
	REGISTER_PROCESS_TYPE(FAST9_COLOR_PI, apu_fast9_color_apu_process_desc)
#endif

  const char firstImg[] = INPUT_ROOT"in_grey_256x256.png";
  const char secondImg[] = INPUT_ROOT"in_color_256x256.png";

  // Read the input using OpenCV
#ifdef __STANDALONE__
  Mat in(256, 256, CV_8UC1, in_grey_256x256);
  Mat inColor(256, 256, CV_8UC1, in_color_256x256);
#else
  Mat in = imread(firstImg, CV_LOAD_IMAGE_GRAYSCALE);
  Mat inColor = imread(secondImg, CV_LOAD_IMAGE_COLOR);
#endif
   
  if (in.empty() || inColor.empty())
  {
    std::cout << "input images " << firstImg <<" or " << secondImg <<" not found" << std::endl << "Press any key to resume" <<std::endl;
	waitKey();
    return -1;
  }

#ifdef APEX2_EMULATE
  imshow("input", in);
  imshow("color input", inColor);
#endif

  // GAUSS 5x5
  {
	  printf("Gauss 5x5\n");
	  int lSrcWidth = in.cols;
	  int lSrcHeight = in.rows;
	  int lRetVal = 0;

	  // Create images
	  DataDescriptor lInput0(lSrcWidth, lSrcHeight, DATATYPE_08U);
	  memcpy(lInput0.GetDataPtr(), in.data, in.rows*in.cols);

	  if (lInput0.IsOK() != 0)
	  {
		  // Run the APEX process
		  CGauss_5x5_Proc process(&lInput0);

		  // execute
		  lRetVal |= process.Exec();
		  // Output the picture
		  Mat out(in.rows, in.cols, CV_8UC1, process.lOutput.GetDataPtr());
		  
#ifdef APEX2_EMULATE
		  imshow("out_gauss5x5.png", out);
#else
	#ifndef __STANDALONE__
		  imwrite("out_gauss5x5.png", out);
	#endif
#endif
		  //Do not free the memory, since it belongs to the "in" image
		  lInput0.SetFreeOnExit(true);

	  }
	  else
	  {
		  lRetVal = 1;
	  }

  }


  // GAUSS 3x3
  { 
	  printf("Gauss 3x3\n");
	  int lSrcWidth = in.cols;
	  int lSrcHeight = in.rows;
	  int lRetVal = 0;

	  // Create images
	  DataDescriptor lInput0(lSrcWidth, lSrcHeight, DATATYPE_08U);
	  memcpy(lInput0.GetDataPtr(), in.data, in.rows*in.cols);

	  if (lInput0.IsOK() != 0)
	  {		 
		  // Run the APEX process		  
		  CGauss_3x3_Proc process;
		  // initialize explicitely, outside the constructor
		  process.InitData(&lInput0); 
		  process.Connect();

		  // execute
		  lRetVal |= process.Exec();

		  // Output the picture
		  Mat out(in.rows, in.cols, CV_8UC1, process.lOutput.GetDataPtr());

#ifdef APEX2_EMULATE
		  imshow("out_gauss_3x3", out);
#else
	#ifndef __STANDALONE__
		  imwrite("out_gauss_3x3.png", out);
	#endif
#endif
		  //Do not free the memory, since it belongs to the "in" image
		  lInput0.SetFreeOnExit(true);
	  }
	  else
	  {
		  lRetVal = 1;
	  }
	  
  }

  //HISTOGRAM
  {
    printf("histogram: \n");

    const int HIST_SIZE = 256;
    unsigned int histogramA[HIST_SIZE] = {};
    for (int i = 0; i < in.rows * in.cols; ++i)
    {
      ++histogramA[in.data[i]];
    }

    DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
    DataDescriptor dataOut(HIST_SIZE, 1, DATATYPE_32U);
    memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

    APU_HISTOGRAM process;

    int lRetVal = 0;
    lRetVal |= process.Initialize();
	lRetVal |= process.ConnectIO(HISTOGRAM_GRAPH_IN, dataIn);
    lRetVal |= process.ConnectIO(HISTOGRAM_GRAPH_OUT, dataOut);

#ifdef APEX2_EMULATE
    printf("histogram process graph plan: \n");
    printf("%s\n", process.GetExecutionPlanDescription().c_str());
#endif

    // execute
    lRetVal |= process.Start();
    lRetVal |= process.Wait();

#ifdef APEX2_EMULATE
	if (lRetVal)
    {
      printf("process error!\n");
	  printf("%s\n", process.ErrorMessage().c_str());
    }
#endif

    unsigned int* histogramB = (unsigned int*)dataOut.GetDataPtr();
	unsigned int histMax = 0, histMaxRef = 0;
	for (int i = 0; i < HIST_SIZE; ++i)
	{
		if (histogramB[i] > histMax)
		{
			histMax = histogramB[i];
		}

		if (histogramA[i] > histMaxRef)
		{
			histMaxRef = histogramA[i];
		}

	}

	const unsigned int histImageHeight = 128;
	Mat out(histImageHeight, HIST_SIZE, CV_8UC1);
	Mat outRef(histImageHeight, HIST_SIZE, CV_8UC1);
	for (unsigned int i = 0; i < HIST_SIZE; ++i)
	{
		float ratio = histogramB[i] / float(histMax);
		float ratioRef = histogramA[i] / float(histMaxRef);
		unsigned int columnHeight = (unsigned int)(ratio * histImageHeight + .5f);
		unsigned int columnHeightRef = (unsigned int)(ratioRef * histImageHeight + .5f);
		for (unsigned int y = 0; y < histImageHeight; ++y)
		{
			uint8_t value = y < columnHeight ? 255 : 0;
			out.at<uint8_t>(histImageHeight - y - 1, i) = value;

			uint8_t valueRef = y < columnHeightRef ? 255 : 0;
			outRef.at<uint8_t>(histImageHeight - y - 1, i) = valueRef;
		}
	}
#ifdef APEX2_EMULATE
	imshow("histogram", out);
	imshow("histogram REF", outRef);
	//cv::waitKey();
#endif

    bool ok = true;
    for (int i = 0; i < HIST_SIZE; ++i)
    {
      if (histogramA[i] != histogramB[i])
      {
        ok = false;
      }
    }
    if(!ok)
    {
      printf("reference and ACF histograms don't match:\n");
      printf("reference:\n");
      for (int i = 0; i < HIST_SIZE; ++i)
      {
        printf("%d ", histogramA[i]);
      }
      printf("\n");
      printf("ACF2:\n");
      for (int i = 0; i < HIST_SIZE; ++i)
      {
        printf("%d ", histogramB[i]);
      }
      printf("\n");
    }
    else
    {
      printf("reference and ACF histograms match\n\n");
    }
  }

//#ifdef APEX2_EMULATE
  /* */
  //FAST9
  {
	  printf("FAST9: \n\n");
	  unsigned char threshold = 50;

	  Mat out(in.rows, in.cols, CV_8UC1);
	  DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
	  DataDescriptor dataThreshold(1, 1, DATATYPE_08U);
	  DataDescriptor dataOut(in.cols, in.rows, DATATYPE_08U);
	  memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);
	  ((unsigned char*)dataThreshold.GetDataPtr())[0] = threshold;

	  FAST9_PI process;

	  int lRetVal = 0;
	  lRetVal |= process.Initialize();
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_IN0, dataIn);
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_IN1, dataThreshold);

	  lRetVal |= process.ConnectIO(FAST9_GRAPH_OUT, dataOut);

#ifdef APEX2_EMULATE
	  printf("FAST9 process graph plan: \n");
	  printf("%s\n", process.GetExecutionPlanDescription().c_str());
#endif

	  // execute
	  lRetVal |= process.Start();
	  lRetVal |= process.Wait();

#ifdef APEX2_EMULATE
	  if (lRetVal)
	  {
		  printf("process error!\n");
		  printf("%s\n", process.ErrorMessage().c_str());
	  }
#endif

	  memcpy(out.data, dataOut.GetDataPtr(), in.cols * in.rows);
#ifdef APEX2_EMULATE	 
	  imshow("output_fast9", out);
#endif
  }
 /* */
//#ifdef APEX2_EMULATE



  // FAST9_COLOR

  {
	  printf("FAST9 color: \n\n");
	  unsigned char threshold = 50;
	  unsigned char markColorChannel = 1;

	  Mat out(inColor.rows, inColor.cols, CV_8UC3);
	  //TODO: use datadescriptor's pixel size, pass to the constructor?
	  DataDescriptor dataIn(inColor.cols, inColor.rows, DATATYPE_08U, 3, 1);
	  DataDescriptor dataThreshold(1, 1, DATATYPE_08U);
	  DataDescriptor dataMarkColorChannel(1, 1, DATATYPE_08U);
	  DataDescriptor dataOut(in.cols, in.rows, DATATYPE_08U, 3, 1);
	  memcpy(dataIn.GetDataPtr(), inColor.data, inColor.cols * inColor.rows * 3);
	  ((unsigned char*)dataThreshold.GetDataPtr())[0] = threshold;
	  ((unsigned char*)dataMarkColorChannel.GetDataPtr())[0] = markColorChannel;

	  FAST9_COLOR_PI process;

	  int lRetVal = 0;
	  lRetVal |= process.Initialize();
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_IN0, dataIn);
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_THR, dataThreshold);
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_MARK, dataMarkColorChannel);
	  lRetVal |= process.ConnectIO(FAST9_GRAPH_OUT, dataOut);

#ifdef APEX2_EMULATE
	  printf("FAST9 color process graph plan: \n");
	  printf("%s\n", process.GetExecutionPlanDescription().c_str());
#endif

	  // execute
	  lRetVal |= process.Start();
	  lRetVal |= process.Wait();

#ifdef APEX2_EMULATE
	  if (lRetVal)
	  {
		  printf("process error!\n");
		  printf("%s\n", process.ErrorMessage().c_str());
	  }
#endif
	  memcpy(out.data, dataOut.GetDataPtr(), in.cols * in.rows * 3);
#ifdef APEX2_EMULATE
	  imshow("output_fast9_color", out);
#endif
  }
  //#endif

  //ROTATE
  {	  // This is the explicit way to  initialize a graph and run it, as opposed to the Gauss_5x5 example. 
    printf("ROTATE: \n\n");
    //unsigned char threshold = 50;

    DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
    DataDescriptor dataOut(in.cols, in.rows, DATATYPE_08U);
    memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

    DataDescriptor dataOffsets(in.cols / ROT_TRANSFER_TILE_SIZE_X, in.rows / ROT_TRANSFER_TILE_SIZE_Y, DATATYPE_32U);
	  //DataDescriptor dataOffsets(in.cols / tileWidth, in.rows / tileHeight, DATATYPE_32U);
    unsigned int* offsetData = (unsigned int*)dataOffsets.GetDataPtr();
    for (unsigned int y = 0; y < dataOffsets.GetHeight(); ++y)
    {
      for (unsigned int x = 0; x < dataOffsets.GetWidth(); ++x)
      {
        unsigned int index = y * dataOffsets.GetWidth() + x;
        unsigned int xShuffled = dataOffsets.GetWidth() - x - 1;
        unsigned int yShuffled = dataOffsets.GetHeight() - y - 1;
        unsigned int offset = yShuffled * in.cols * ROT_TRANSFER_TILE_SIZE_Y + xShuffled * ROT_TRANSFER_TILE_SIZE_X;
		    //unsigned int offset = yShuffled * in.cols * tileHeight + xShuffled * tileWidth;
        offsetData[index] = offset;
      }
    }

    ROTATE_PI process;
	
    int lRetVal = 0;
    lRetVal |= process.Initialize();
    //lRetVal |= process.ConnectIO(process.mGraph.m_inputName, dataIn);
	lRetVal |= process.ConnectIndirectInput(ROTATE_GRAPH_IN, dataIn, dataOffsets);
    lRetVal |= process.ConnectIO(ROTATE_GRAPH_OUT, dataOut);

    printf("ROTATE process graph plan: \n");
#ifdef APEX2_EMULATE
    printf("%s\n", process.GetExecutionPlanDescription().c_str());
#endif

    // execute
    lRetVal |= process.Start();
    lRetVal |= process.Wait();

#ifdef APEX2_EMULATE
    if (lRetVal)
    {
      printf("process error!\n");
      printf("%s\n", process.ErrorMessage().c_str());
    }
#endif
	Mat out(in.rows, in.cols, CV_8UC1, dataOut.GetDataPtr());

#ifdef APEX2_EMULATE
    imshow("output_indirect_rotate", out);
#else
	#ifndef __STANDALONE__
		imwrite("output_indirect_rotate.png", out);
	#endif
#endif
  }


  //SAT
  {
    printf("SAT (integral image): \n\n");
	DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
    memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

	CSat_Proc process(&dataIn);
	process.Exec();

	Mat res(in.cols, in.rows, CV_32SC1, process.lOutput.GetDataPtr());
	double minV = 0, maxV = 0;
	cv::minMaxLoc(res, &minV, &maxV);
	printf("minV: %f maxV: %f\n", minV, maxV);
    Mat out_sat(in.rows, in.cols, CV_8UC1);
	cv::convertScaleAbs(res, out_sat, 1.0/20000.0f);

    Mat out_filter(in.rows, in.cols, CV_8UC1, process.lOutputFilter.GetDataPtr());

#ifdef APEX2_EMULATE
    imshow("summed area table (integral image)", out_sat);
    imshow("box filter using SAT (II)", out_filter);
#else
	#ifndef __STANDALONE__
		imwrite("integral_image.png", out_sat);
		imwrite("box_filter_using_SAT_II.png", out_filter);
	#endif
#endif

  }
  

  //DOWNSAMPLE_UPSAMPLE
  { // This is the explicit way to  initialize a graph and run it, as opposed to the Gauss_5x5 example. 
    printf("DOWNSAMPLE_UPSAMPLE: \n\n");

    DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
	DataDescriptor dataOutDownsample(in.cols / 2, in.rows / 2, DATATYPE_08U);
	DataDescriptor dataOutUpsample(in.cols * 2, in.rows * 2, DATATYPE_08U);
    memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

    DOWNSAMPLE_UPSAMPLE_PI process;
    int lRetVal = 0;
    lRetVal |= process.Initialize();
	//lRetVal |= process.ConnectIO(process.mGraph.m_inputName, dataIn);
	lRetVal |= process.ConnectIO(DOWNSAMPLE_UPSAMPLE_IN, dataIn);
	lRetVal |= process.ConnectIO(DOWNSAMPLE_UPSAMPLE_OUT_DOWN, dataOutDownsample);
	lRetVal |= process.ConnectIO(DOWNSAMPLE_UPSAMPLE_OUT_UP, dataOutUpsample);

    printf("DOWNSAMPLE_UPSAMPLE process graph plan: \n");
#ifdef APEX2_EMULATE
	printf("%s\n", process.GetExecutionPlanDescription().c_str());
#endif

    // execute
    lRetVal |= process.Start();
    lRetVal |= process.Wait();

#ifdef APEX2_EMULATE
    if (lRetVal)
    {
      printf("process error!\n");
      printf("%s\n", process.ErrorMessage().c_str());
    }
#endif

	Mat outDownsampled(dataOutDownsample.GetHeight(), dataOutDownsample.GetWidth(), CV_8UC1, dataOutDownsample.GetDataPtr());
	Mat outUpsampled(dataOutUpsample.GetHeight(), dataOutUpsample.GetWidth(), CV_8UC1, dataOutUpsample.GetDataPtr());

#ifdef APEX2_EMULATE
    imshow("downsampled", outDownsampled);
    imshow("upsampled", outUpsampled);
#else 
	#ifndef __STANDALONE__
		imwrite("downsampled.png", outDownsampled);
		imwrite("upsampled.png", outUpsampled);
	#endif
#endif

	dataIn.SetFreeOnExit(true);
	dataOutDownsample.SetFreeOnExit(true);
	dataOutUpsample.SetFreeOnExit(true);
  }



  // CONVOLUTION  
  {
	  printf("CONVOLUTION: \n\n");

	  // Pick a filter

	  // Others could be (see c_filter.h in the matrix project), or add your own filter to CFilter.cpp
	  /*
	  const CFilter<3, 3, short> gaussFilter3x3(16, gaussFilter3x3Data);
	  const CFilter<5, 5, short> gaussFilter5x5(64, gaussFilter5x5Data);
	  const CFilter<3, 1, short> gradientXFilter(1, gradientX);
	  const CFilter<1, 3, short> gradientYFilter(1, gradientY);
	  const CFilter<3, 3, short> gradientXYFilter(1, gradientXY);
	  const CFilter<3, 3, short> scharrXFilter(scharrX);
	  const CFilter<3, 3, short> scharrYFilter(scharrY);

	  */


	  DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
	  memcpy(dataIn.GetDataPtr(), in.data, in.cols*in.rows);

//! Needed for FW, FH definitions
#include "apu_correlation_kernel.h"
	  /* Need to adapt these in apu_correlation_kernel.h
	  #define FW 3
	  #define FH 3
	  #define HFW 1 // half filter width, needed for the filter's spatial dependencies
	  #define HFH 1 // half filter height, needed for the filter's spatial dependencies
	  */
	  CConvolution_Proc<FW, FH, short> process(&dataIn, &scharrYFilter);
	  int lRetVal = 0;

	  printf("\nBefore execution of convolution\n");
	  // execute
	  lRetVal |= process.Exec();

	  printf("After execution of convolution\n");
	  Mat out(in.rows, in.cols, CV_16SC1);
	  memcpy(out.data, process.lOutput.GetDataPtr(), process.lOutput.GetSpanRow()*process.lOutput.GetHeight());
	  
	  double minV = 0, maxV = 0;
	  cv::minMaxLoc(out, &minV, &maxV);
	  printf("Convolution min: %d max: %d\n", minV, maxV);

	  Mat out8uc;
	  convertScaleAbs(out, out8uc);
#ifdef APEX2_EMULATE
	  imshow("output_convolution", out8uc);
#else
	#ifndef __STANDALONE__
	  imwrite("output_convolution.png", out8uc);
	#endif
#endif
	  printf("\nEnd of convolution\n");
  }
  

#ifdef APEX2_EMULATE
  waitKey();
#endif

  return 0;
}
