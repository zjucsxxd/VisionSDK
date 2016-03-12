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
#endif

#include "apex.h"

#include <opencv2/opencv.hpp>  
#include <icp_data.h>
#include <APU_GAUSS_5X5.hpp>
#include <oal.h>
#include <stringify_macros.h>
using namespace cv;

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

  int lSrcWidth = in.cols;
  int lSrcHeight = in.rows;
  int lRetVal = 0;
  
  // Create images
  icp::DataDescriptor lInput0(lSrcWidth, lSrcHeight, icp::DATATYPE_08U);
  icp::DataDescriptor lOutput0(lSrcWidth, lSrcHeight, icp::DATATYPE_08U);

  if (lInput0.IsOK() != 0 && lOutput0.IsOK() != 0)
  {
    // Load image into input data
    unsigned char *data = (unsigned char *)lInput0.GetDataPtr();
    for (int i = 0; i < lSrcWidth * lSrcHeight; ++i)
    {
      data[i] = in.data[i];
    }

    // Run the APEX process
    APU_GAUSS_5X5 process(0);

    // init
    lRetVal |= process.Initialize();
    lRetVal |= process.ConnectIO("INPUT_0", lInput0);
    lRetVal |= process.ConnectIO("OUTPUT_0", lOutput0);

    // execute
    lRetVal |= process.Start();
    lRetVal |= process.Wait();
  }
  else
  {
    lRetVal = 1;
  }

  // Output the picture
  Mat out(in.rows, in.cols, CV_8UC1);
  unsigned char *data = (unsigned char *)lOutput0.GetDataPtr();
  for (int i = 0; i < in.rows * in.cols; ++i)
  {
    out.at<unsigned char>(i) = data[i];
  }

  
  #ifdef __STANDALONE__
  cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
  io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
	
  cvtColor(out, out, CV_GRAY2RGB);	
  cvtColor(in, in, CV_GRAY2RGB);	
  in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
  out.copyTo(output_mat(cv::Rect(300, 412, 256, 256)));
  
  warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
  output.PutFrame(output_mat.data);
#else
  imwrite(OUTPUT_ROOT"out_gauss5x5.png", out);
#endif
  lInput0.SetFreeOnExit(true);
  lOutput0.SetFreeOnExit(true);
  return 0;
}

