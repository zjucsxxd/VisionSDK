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

#ifndef APEX2_EMULATE // This is needed only for the Target Compiler

  #include <stdio.h>
  #ifdef __STANDALONE__
    #include "../../data/standalone/in_color_256x256.h"
    #include <frame_output_dcu.h>
  #endif

  #include <opencv2/opencv.hpp>  
  #include <iostream>
  #include <fstream>
  #include <iomanip>

  #include <icp_data.h>
  #include <apex.h>
  #include <oal.h>
  #include <APU_FAST9_COLOR.hpp>
#else
  #include "apu_lib.hpp"
  #include "apu_extras.hpp"
  #include "acf_lib.hpp"
  using namespace APEX2;

  #include "DefineAllProcessDesc.h"
  #include "apu_fast9_color_apu_process_desc.hpp"

  #define IMG_WIDTH 256
  #define IMG_HEIGHT 256
  const int tileWidth = IMG_WIDTH / VSIZE;
  const int tileHeight = IMG_HEIGHT / VSIZE;
  const int SAT_TILE_HEIGHT = 8;
  using namespace icp;
#endif

using namespace cv;
using namespace std;

#include "GraphNames.h"

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

#include "apu_dilate_diamond.h"
#include "apu_mark.h"
#include "apu_mark_color_channel.h"
#include "apu_16low_to_8.h"
#include "apu_nms.h"
#include "apu_fast9.h"
#include "apu_rgb_to_grayscale.h"
#include "apu_gauss_3x3.h"

/****************************************************************************
* Main function
****************************************************************************/
#ifdef APEX2_EMULATE
int _tmain(int, _TCHAR**)
#else
int main(int, char**)
#endif
{
  // This is needed only for the Target Compiler
  // HW and resources init
#ifndef APEX2_EMULATE 
#ifndef __STANDALONE__
  OAL_MemoryAllocInit();
#endif
 	ACF_Init();
	using namespace icp;
#endif

  #ifdef APEX2_EMULATE	
    REGISTER_PROCESS_TYPE(FAST9_COLOR_PI, apu_fast9_color_apu_process_desc)
    XREGISTER_ACF_KERNEL(DILATE_DIAMOND_k)
    XREGISTER_ACF_KERNEL(MARK_K)
    XREGISTER_ACF_KERNEL(NMS_K)
    XREGISTER_ACF_KERNEL(_16LOW_TO_8_K)
    XREGISTER_ACF_KERNEL(FAST9_K)
    XREGISTER_ACF_KERNEL(SATURATE_NONZERO_K)
    XREGISTER_ACF_KERNEL(MARK_COLOR_CHANNEL_K)
    XREGISTER_ACF_KERNEL(RGB_TO_GRAYSCALE_K)
    XREGISTER_ACF_KERNEL(GAUSS_3X3_K)
  #endif

  // Read the input using OpenCV
  #ifdef __STANDALONE__
    Mat in(256, 256, CV_8UC3, in_color_256x256);
  #else
    Mat in = imread(INPUT_ROOT"in_color_256x256.png", CV_LOAD_IMAGE_COLOR);
  #endif
  #ifdef APEX2_EMULATE
    imshow("Input Image", in);
    waitKey();
  #endif

  printf("FAST9 color:\n");
  uint8_t threshold = 50;
  uint8_t markColorChannel = 1;

  Mat out(in.rows, in.cols, CV_8UC3);
  DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U, 3, 1);
  DataDescriptor dataThreshold(1, 1, DATATYPE_08U);
  DataDescriptor dataMarkColorChannel(1, 1, DATATYPE_08U);
  DataDescriptor dataOut(in.cols, in.rows, DATATYPE_08U, 3, 1);
  uint8_t* dataInP = (uint8_t*)dataIn.GetDataPtr();
  for (int i = 0; i < in.cols * in.rows * 3; i += 3)
  {
    dataInP[i] = in.data[i + 2];
    dataInP[i + 1] = in.data[i + 1];
    dataInP[i + 2] = in.data[i];
  }
  ((uint8_t*)dataThreshold.GetDataPtr())[0] = threshold;
  ((uint8_t*)dataMarkColorChannel.GetDataPtr())[0] = markColorChannel;

  FAST9_COLOR_PI process;

  int lRetVal = 0;
  lRetVal |= process.Initialize();
  lRetVal |= process.ConnectIO("INPUT", dataIn);
  lRetVal |= process.ConnectIO("THRESHOLD", dataThreshold);
  lRetVal |= process.ConnectIO("MARK_COLOR_CHANNEL", dataMarkColorChannel);
  lRetVal |= process.ConnectIO("OUTPUT", dataOut);

  // execute
  lRetVal |= process.Start();
  lRetVal |= process.Wait();
  uint8_t* dataOutP = (uint8_t*)dataOut.GetDataPtr();
  for (int i = 0; i < out.cols * out.rows * 3; i += 3)
  {
    out.data[i] = dataOutP[i + 2];
    out.data[i + 1] = dataOutP[i + 1];
    out.data[i + 2] = dataOutP[i];
    #ifdef __STANDALONE__
      dataOutP[i] = out.data[i + 2];
      dataOutP[i + 2] = out.data[i];
    #endif
  }

  #ifdef APEX2_EMULATE
    cv::imshow("Fast9", out);
    cv::waitKey();
  #endif 
  
  #ifdef __STANDALONE__
    cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
    io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
    cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
    out.copyTo(output_mat(cv::Rect(832, 412, 256, 256)));
    warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
    output.PutFrame(output_mat.data);
  #else
    imwrite(OUTPUT_ROOT"out_fast9_color.png", out);
  #endif
  
  dataIn.SetFreeOnExit(true);
  dataThreshold.SetFreeOnExit(true);
  dataMarkColorChannel.SetFreeOnExit(true);
  dataOut.SetFreeOnExit(true);

  return 0;
}
