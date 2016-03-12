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

#include "apex.h"

#include <opencv2/opencv.hpp>  
#include <icp_data.h>
#include <APU_DOWNSAMPLE_UPSAMPLE.hpp>
#include <oal.h>
#include <stringify_macros.h>

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
  
  //////////////////////////////////////////////////
  // Read the input using OpenCV (in standalone version, read image array)
  #ifdef __STANDALONE__
    Mat in(256, 256, CV_8UC1, in_grey_256x256);
  #else
    Mat in = imread(INPUT_ROOT"in_grey_256x256.png", 0);
  #endif

  printf("DOWNSAMPLE_UPSAMPLE:\n");

  Mat outDownsampled(in.rows / 2, in.cols / 2, CV_8UC1);
  Mat outUpsampled(in.rows * 2, in.cols * 2, CV_8UC1);
  DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
  DataDescriptor dataOutDownsample(outDownsampled.cols, outDownsampled.rows, DATATYPE_08U);
  DataDescriptor dataOutUpsample(outUpsampled.cols, outUpsampled.rows, DATATYPE_08U);
  memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

  APU_DOWNSAMPLE_UPSAMPLE process;

  int lRetVal = 0;
  lRetVal |= process.Initialize();
  lRetVal |= process.ConnectIO("INPUT", dataIn);
  lRetVal |= process.ConnectIO("OUTPUT_DOWN", dataOutDownsample);
  lRetVal |= process.ConnectIO("OUTPUT_UP", dataOutUpsample);

  // execute
  lRetVal |= process.Start();
  lRetVal |= process.Wait();

  if (lRetVal)
  {
    printf("process error!\n");
  }

  memcpy(outDownsampled.data, dataOutDownsample.GetDataPtr(), outDownsampled.cols * outDownsampled.rows);
  memcpy(outUpsampled.data, dataOutUpsample.GetDataPtr(), outUpsampled.cols * outUpsampled.rows);

  //////////////////////////////////////////////////
  // Process the output - if standalone, compare with reference
  //                    - if OS, save the images
  #ifdef __STANDALONE__
    cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
    io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
    cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);

    cvtColor(outDownsampled, outDownsampled, CV_GRAY2RGB);
    cvtColor(outUpsampled, outUpsampled, CV_GRAY2RGB);
    cvtColor(in, in, CV_GRAY2RGB);
    in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
    outDownsampled.copyTo(output_mat(cv::Rect(300, 476, 128, 128)));
    outUpsampled.copyTo(output_mat(cv::Rect(500, 284, 512, 512)));
  
    warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
    output.PutFrame(output_mat.data);
  #else
    imwrite(OUTPUT_ROOT"downsampled.png", outDownsampled);
    imwrite(OUTPUT_ROOT"upsampled.png", outUpsampled);
  #endif
    dataIn.SetFreeOnExit(true);
    dataOutDownsample.SetFreeOnExit(true);
    dataOutUpsample.SetFreeOnExit(true);
  return 0;
}
