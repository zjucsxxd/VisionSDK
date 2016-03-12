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
#include <APU_SAT.hpp>
#include <apex.h>
#include <oal.h>
#include <stringify_macros.h>
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

  int lRetVal = 0;

  printf("SAT (integral image): \n\n");

  const int SAT_TILE_HEIGHT = 8;

  Mat out_sat(in.rows, in.cols, CV_8UC1);
  Mat out_filter(in.rows, in.cols, CV_8UC1);
  DataDescriptor dataIn(in.cols, in.rows, DATATYPE_08U);
  DataDescriptor dataRow(in.cols, SAT_TILE_HEIGHT, DATATYPE_32U);
  DataDescriptor dataOutSAT(in.cols, in.rows, DATATYPE_32U);
  DataDescriptor dataOutFilter(in.cols, in.rows, DATATYPE_08U);
  memcpy(dataIn.GetDataPtr(), in.data, in.cols * in.rows);

  APU_SAT process(APEX_APEX1);

  lRetVal |= process.Initialize();
  lRetVal |= process.ConnectIO("INPUT_0", dataIn);
  lRetVal |= process.ConnectIO("OUTPUT_0", dataOutSAT);
  lRetVal |= process.ConnectIO("OUTPUT_1", dataOutFilter);

  // execute
  lRetVal |= process.Start();
  lRetVal |= process.Wait();

  if (lRetVal)
  {
    printf("Process error!\n");
  }

  uint32_t* acfDataOut = (uint32_t*)dataOutSAT.GetDataPtr();
  for (int i = 0; i < in.cols * in.rows; ++i)
  {
    uint32_t iiv = acfDataOut[i] / 20000;
    if (iiv > 255)
    {
      iiv = 255;
    }
    out_sat.data[i] = uint8_t(iiv);
  }


  memcpy(out_filter.data, dataOutFilter.GetDataPtr(), in.cols * in.rows);
  
#ifdef __STANDALONE__
  cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
  io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
	
  cvtColor(in, in, CV_GRAY2RGB);	
  cvtColor(out_sat, out_sat, CV_GRAY2RGB);		
  in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
  out_sat.copyTo(output_mat(cv::Rect(300, 412, 256, 256)));
  cvtColor(out_filter, out_filter, CV_GRAY2RGB);
  out_filter.copyTo(output_mat(cv::Rect(600, 412, 256, 256)));
  
  warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
  output.PutFrame(output_mat.data);
#else
  imwrite(OUTPUT_ROOT"sat.png", out_sat);
  imwrite(OUTPUT_ROOT"sat_box_filter.png", out_filter);
#endif

  return 0;
}
