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

#ifdef __STANDALONE__
  #include "../../data/standalone/in_grey_256x256.h"
  #include <frame_output_dcu.h>
  #include <printf.h>
#endif

#include <opencv2/opencv.hpp>  
#include <icp_data.h>
#include <APU_HISTOGRAM.hpp>
#include "apex.h"
#include <oal.h>
#include <stdint.h>
using namespace cv;
using namespace icp;

#ifdef INPUT_PATH_REL
#define INPUT_ROOT __FULL_DIR__ XSTR(INPUT_PATH_REL)
#else
#define INPUT_ROOT ""
#endif
#ifdef OUTPUT_PATH_REL
#define OUTPUT_ROOT __FULL_DIR__ XSTR(OUTPUT_PATH_REL)
#else
#define OUTPUT_ROOT ""
#endif

#include "apu_histogram_graph.h"

/****************************************************************************
* Main function
****************************************************************************/
int main(int, char**)
{
  // HW and resources init
#ifndef APEX2_EMULATE 
#ifndef __STANDALONE__
  OAL_MemoryAllocInit();
#endif
 	ACF_Init();
	using namespace icp;
#endif
  
  // Read the input using OpenCV
  #ifdef __STANDALONE__
    Mat in(256, 256, CV_8UC1, in_grey_256x256);
  #else
    Mat in = imread(INPUT_ROOT"in_grey_256x256.png", 0);
  #endif

  printf("Histogram: \n\n");

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
  lRetVal |= process.ConnectIO(HISTOGRAM_IN, dataIn);
  lRetVal |= process.ConnectIO(HISTOGRAM_OUT, dataOut);

  // execute
  lRetVal |= process.Start();
  lRetVal |= process.Wait();

  if (lRetVal)
  {
    printf("Process error!\n");
  }

  unsigned int* histogramB = (unsigned int*)dataOut.GetDataPtr();

  unsigned int histMax = 0;
  for (int i = 0; i < HIST_SIZE; ++i)
  {
    if (histogramB[i] > histMax)
    {
      histMax = histogramB[i];
    }
  }

  const unsigned int histImageHeight = 128;
  Mat out(histImageHeight, HIST_SIZE, CV_8UC1);
  for (unsigned int i = 0; i < HIST_SIZE; ++i)
  {
    float ratio = histogramB[i] / float(histMax);
    unsigned int columnHeight = (unsigned int)(ratio * histImageHeight + .5f);
    for (unsigned int y = 0; y < histImageHeight; ++y)
    {
      uint8_t value = y < columnHeight ? 255 : 0;
      out.at<uint8_t>(histImageHeight - y - 1, i) = value;
    }
  }
  #ifndef __STANDALONE__
    imwrite(OUTPUT_ROOT"histogram.png", out);
  #else
	cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
	io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
	cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
	
	cvtColor(out, out, CV_GRAY2RGB);	
	cvtColor(in, in, CV_GRAY2RGB);	
	in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
	out.copyTo(output_mat(cv::Rect(300, 476, 256, 128)));
  
	warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
	output.PutFrame(output_mat.data);
  #endif

  bool ok = true;
  for (int i = 0; i < HIST_SIZE; ++i)
  {
    if (histogramA[i] != histogramB[i])
    {
      ok = false;
      break;
    }
  }
  if (!ok)
  {
    printf("Reference and ACF histograms don't match:\n\n");
    printf("Reference:\n");
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
    printf("Reference and ACF histograms match\n\n");
  }

  dataIn.SetFreeOnExit(true);
  dataOut.SetFreeOnExit(true);

  return 0;
}
