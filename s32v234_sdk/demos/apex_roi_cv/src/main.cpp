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

#ifdef APEX2_EMULATE
#include <tchar.h>
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;

#include "apu_gauss_5x5_apu_process_desc.hpp"
#else
#include <icp_data.h>
#include <APU_GAUSS_5X5.hpp>
#include <apex.h>
#include <oal.h>
#include <stdio.h>
#include <stringify_macros.h>
using namespace icp;
#endif

#include <opencv2/opencv.hpp>  
using namespace cv;

#ifdef INPUT_PATH_REL
  #define INPUT_ROOT __FULL_DIR__ XSTR(INPUT_PATH_REL)
#else
  #ifdef APEX2_EMULATE
    #define INPUT_ROOT "../data/"
  #else
    #define INPUT_ROOT ""
  #endif
#endif

#ifdef OUTPUT_PATH_REL
  #define OUTPUT_ROOT __FULL_DIR__ XSTR(OUTPUT_PATH_REL)
#else
  #define OUTPUT_ROOT ""
#endif

#include "time_measure.h"
/****************************************************************************
* Main function 
* The function will initialize two parallel processes for APEX0 and APEX1, which will
* execute the Gauss filter on the same image. Both processes apply ROI on images,
* however each process is set by different way. One ROi is set via image settings,
* the second via connect IO function
****************************************************************************/
#ifdef APEX2_EMULATE
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int, char**)
#endif
{
  int lRetVal = 0;

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

#ifdef APEX2_EMULATE
	REGISTER_PROCESS_TYPE(APU_GAUSS_5X5, apu_gauss_5x5_process_desc);
#endif
	if (in.data == NULL) {
		std::cerr << "Could not open input image: " << std::string(INPUT_ROOT"in_grey_256x256.png");
		return -1;
	}

  // Create images
  DataDescriptor lInput0_example1 (in.cols, in.rows, DATATYPE_08U);
  DataDescriptor lOutput0_example1(in.cols, in.rows, DATATYPE_08U);
  DataDescriptor lInput0_example2 (in.cols, in.rows, DATATYPE_08U);
  DataDescriptor lOutput0_example2(in.cols, in.rows, DATATYPE_08U);
  
  lOutput0_example1.FillValue(0);
  lOutput0_example2.FillValue(0);
  
  if (lInput0_example1.IsOK() != 0 && lOutput0_example1.IsOK() != 0 && lInput0_example2.IsOK() != 0 && lOutput0_example2.IsOK() != 0)
  {
    // Load image into input data
    unsigned char *data1 = (unsigned char *)lInput0_example1.GetDataPtr();
    unsigned char *data2 = (unsigned char *)lInput0_example2.GetDataPtr();
    for (int i = 0; i < in.cols * in.rows; ++i)
    {
      data1[i] = in.data[i];
      data2[i] = in.data[i];
    }

#ifdef _DEBUG
	cv::Mat tmp1(in.cols, in.rows, CV_8UC1, (void*)data1);
	cv::Mat tmp2(in.cols, in.rows, CV_8UC1, (void*)data2);
	cv::imshow("in1", tmp1);
	cv::imshow("in2", tmp2);
	waitKey();
#endif
    ///////////////////////////////////////////////////////////////////////
    // Data init done, now set the APEX processes for full image
    APU_GAUSS_5X5 process1(APEX_APEX0);
    lRetVal |= process1.Initialize();
    lRetVal |= process1.ConnectIO("INPUT_0", lInput0_example1);
    lRetVal |= process1.ConnectIO("OUTPUT_0", lOutput0_example1);
	
	///////////////////////////////////////////////////////////////////////
    // Data init done, now set the APEX processes for ROI
	APU_GAUSS_5X5 process2(APEX_APEX1);
    lRetVal |= process2.Initialize();
    

	for (int i = 0; i < 8; ++i)
	{
		unsigned long time[4];
		time[0]	= FSL_Ticks();
		//						 X,  Y,      W,      H
		lInput0_example1.SetROI(128, 88, 8 + i * 16, 32 + i * 8);
		lOutput0_example1.SetROI(128, 88, 8 + i * 16, 32 + i * 8);

		lRetVal |= process1.Start();
		lRetVal |= process1.Wait();
		time[1]	= FSL_Ticks();
		//                                                               X,  W,			 Y,      H
		lRetVal |= process2.ConnectIO_ROI("INPUT_0", lInput0_example2, 128, 8 + i * 16, 88, 32 + i * 8);
		lRetVal |= process2.ConnectIO_ROI("OUTPUT_0", lOutput0_example2, 128, 8 + i * 16, 88, 32 + i * 8);
		
		time[2]	= FSL_Ticks();
		lRetVal |= process2.Start();
		lRetVal |= process2.Wait();
		time[3]	= FSL_Ticks();

		printf("Image size ratio: %f %%\n", (((10.0 + i*5)*(30.0 + i*5)) / (256.0*256.0)) * 100);
		printf("Time ratio:       %f %%\n", (float)((time[3] - time[2]) / (float)(time[1] - time[0]))*100);
		printf("Time full image: %d us\n", time[1] - time[0]);
		printf("Time ROI  image: %d us\n", time[3] - time[2]);
		printf("=============================\n");

		// Output both images to files
		Mat out1(lOutput0_example1.GetHeight(), lOutput0_example1.GetWidth(), CV_8UC1, (void*)lOutput0_example1.GetDataPtr(), lOutput0_example1.GetSpan());
		Mat out2(lOutput0_example2.GetHeight(), lOutput0_example2.GetWidth(), CV_8UC1, (void*)lOutput0_example2.GetDataPtr(), lOutput0_example2.GetSpan());

#ifdef _DEBUG
		{
			cv::imshow("out1", out1);
			cv::imshow("out2", out2);
			waitKey();
		}
#endif
#ifdef __STANDALONE__
/*		cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
		io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
		cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);

		cvtColor(in, in, CV_GRAY2RGB);
		cvtColor(out1, out1, CV_GRAY2RGB);
		cvtColor(out2, out2, CV_GRAY2RGB);
		cv::rectangle(out1, cv::Point(0, 0), cv::Point(out1.cols - 1, out1.rows - 1), cv::Scalar(255, 255, 255));
		cv::rectangle(out2, cv::Point(0, 0), cv::Point(out2.cols - 1, out2.rows - 1), cv::Scalar(255, 255, 255));
		in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
		out1.copyTo(output_mat(cv::Rect(300, 412, 256, 256)));
		out2.copyTo(output_mat(cv::Rect(600, 412, 256, 256)));

		warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
		output.PutFrame(output_mat.data);*/
#else
#ifndef __INTEGRITY
		imwrite(OUTPUT_ROOT"out_gauss5x5_roi_1_" + std::to_string(i) + ".png", out1);
		imwrite(OUTPUT_ROOT"out_gauss5x5_roi_2_" + std::to_string(i) + ".png", out2);
#endif
#endif

		lInput0_example1.ClearROI();
		lOutput0_example1.ClearROI();
		lInput0_example2.ClearROI();
		lOutput0_example2.ClearROI();

	}

  }
  else
  {
    lRetVal = 1;
  }

  // Output both images to files
  Mat out1(lOutput0_example1.GetHeight(), lOutput0_example1.GetWidth(), CV_8UC1, (void*) lOutput0_example1.GetDataPtr(), lOutput0_example1.GetSpan());
  Mat out2(lOutput0_example2.GetHeight(), lOutput0_example2.GetWidth(), CV_8UC1, (void*) lOutput0_example2.GetDataPtr(), lOutput0_example2.GetSpan());


#ifdef __STANDALONE__
  cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
  io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
	
  cvtColor(in, in, CV_GRAY2RGB);
  cvtColor(out1, out1, CV_GRAY2RGB);
  cvtColor(out2, out2, CV_GRAY2RGB);
  cv::rectangle(out1, cv::Point(0, 0), cv::Point(out1.cols-1, out1.rows-1), cv::Scalar(255, 255, 255));
  cv::rectangle(out2, cv::Point(0, 0), cv::Point(out2.cols-1, out2.rows-1), cv::Scalar(255, 255, 255));
  in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
  out1.copyTo(output_mat(cv::Rect(300, 412, 256, 256)));
  out2.copyTo(output_mat(cv::Rect(600, 412, 256, 256)));
  
  warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
  output.PutFrame(output_mat.data);
#else
  imwrite(OUTPUT_ROOT"out_gauss5x5_roi_1.png", out1);
  imwrite(OUTPUT_ROOT"out_gauss5x5_roi_2.png", out2);
#endif

  lInput0_example1.SetFreeOnExit(true);
  lOutput0_example1.SetFreeOnExit(true);
  lInput0_example2.SetFreeOnExit(true);
  lOutput0_example2.SetFreeOnExit(true);
  return 0;
}

