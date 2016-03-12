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
// orb.cpp : Defines the entry point for the console application.

#include "../include/descriptor.h"
#include <opencv2/opencv.hpp>

#ifdef __STANDALONE__
  #include "../../data/standalone/f0.h"
  #include "../../data/standalone/f1.h"
  #include <frame_output_dcu.h>
#endif

#include <iostream>
#include <fstream>

#ifndef APEX2_EMULATE
#include <icp_data.h>
#include <APU_FAST9.hpp>
#include <APU_MATCH_DESCRIPTORS.hpp>
#include <apex.h>
#include <oal.h>
using namespace icp;
#else
#include <acf_lib.hpp>
#include "..\graphs\apu_fast9_apu_process_desc.hpp"
#include "..\graphs\apu_match_descriptors_apu_process_desc.hpp"
using namespace APEX2;
#endif

/*
#ifdef APEX2_EMULATE
//kernel and graph visibilty
extern KERNEL_INFO _kernel_info_apu_gauss_3x3;
void apu_gauss_3x3(kernel_io_desc lIn0, kernel_io_desc lOut0);
extern KERNEL_INFO _kernel_info_apu_fast9;
void apu_fast9(kernel_io_desc lIn0, kernel_io_desc lOut0, kernel_io_desc lIn1);
extern KERNEL_INFO _kernel_info_apu_nms;
void apu_nms(kernel_io_desc lIn0, kernel_io_desc lOut0);
extern KERNEL_INFO _kernel_info_apu_match_descriptors;
void apu_match_descriptors(kernel_io_desc lIn0, kernel_io_desc lIn1, kernel_io_desc lInConfig, kernel_io_desc lOut0, kernel_io_desc lOut1);
#endif
*/
using namespace cv;
using namespace std;

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

struct Feature
{
  Point position;
  Descriptor descriptor;
  int matchedTo;
  int matchDist;

  Feature() :
    matchedTo(-1),
    matchDist(INT_MAX)
  {
  }
};

#include "apu_fast9_graph.h"
#include "apu_match_descriptors_graph.h"

int main(int argc, char* argv[])
{
  bool apu_matching = true;
  /*if (argc > 1)
  {
    if (strcmp(argv[1], "-am") == 0)
    {
      apu_matching = true;
    }
  }*/
#ifndef APEX2_EMULATE
  // HW and resources init
  #ifndef __STANDALONE__
  OAL_MemoryAllocInit();
  #endif
  ACF_Init();
  using namespace icp;
#else
  /*
  REGISTER_ACF_KERNEL(_kernel_info_apu_gauss_3x3, apu_gauss_3x3)
  REGISTER_ACF_KERNEL(_kernel_info_apu_fast9, apu_fast9)
  REGISTER_ACF_KERNEL(_kernel_info_apu_nms, apu_nms)
  REGISTER_ACF_KERNEL(_kernel_info_apu_match_descriptors, apu_match_descriptors)
  */
  REGISTER_PROCESS_TYPE(FAST9_PI, apu_fast9_apu_process_desc)
  REGISTER_PROCESS_TYPE(MATCH_DESCRIPTORS_PI, apu_match_descriptors_apu_process_desc)
#endif


  #include "time_measure.h"
  double frequency = FSL_GetFrequency();
  printf("Host frequency: %f\n", frequency);

  // Read the input using OpenCV
  #ifdef __STANDALONE__
    Mat in0(576, 768, CV_8UC1, f0);
	Mat in1(576, 768, CV_8UC1, f1);
  #else
    Mat in0 = imread(INPUT_ROOT"f0.png", 0);
    Mat in1 = imread(INPUT_ROOT"f1.png", 0);
  #endif

  if (in0.empty() || in1.empty())
  {
    printf("input images not found\n");
    return 1;
  }

  if ((in0.rows != in1.rows) || (in0.cols != in1.cols))
  {
    printf("input images have different dimensions\n");
    return 1;
  }

  int lSrcWidth = in0.cols;
  int lSrcHeight = in0.rows;
  int lRetVal = 0;

  unsigned char* tempDataF = new unsigned char[lSrcWidth * lSrcHeight];
  unsigned char* tempDataG = new unsigned char[lSrcWidth * lSrcHeight];

  // Create images
  DataDescriptor lInput0(lSrcWidth, lSrcHeight, DATATYPE_08U);
  DataDescriptor lOutput0(lSrcWidth, lSrcHeight, DATATYPE_08U);
  DataDescriptor lOutput1(lSrcWidth, lSrcHeight, DATATYPE_08U);
  DataDescriptor lInputThreshold(1, 1, DATATYPE_08U);

  ((uint8_t*)lInputThreshold.GetDataPtr())[0] = 30;

  const int reservedPoints = 1024;

  vector<KeyPoint> filteredKeyPoints0;
  vector<KeyPoint> filteredKeyPoints1;
  filteredKeyPoints0.reserve(reservedPoints);
  filteredKeyPoints1.reserve(reservedPoints);

  vector<Feature> features0;
  vector<Feature> features1;
  features0.reserve(reservedPoints);
  features1.reserve(reservedPoints);

  vector<DMatch> matches;
  matches.reserve(reservedPoints);

#ifndef __STANDALONE__
  int64 startTicks = getTickCount();
#else
  int64 startTicks = 0;
#endif

  int64 fast0Ticks = 0;
  int64 fast1Ticks = 0;
  int64 nonCopyFeatures0StartTicks = 0;
  int64 nonCopyFeatures1StartTicks = 0;
  int64 features0Ticks = 0;
  int64 features1Ticks = 0;

  double nonCopyTotalTime = .0;
  double armTime = .0;
  double apexTime = .0;

  if (lInput0.IsOK() != 0 && lOutput0.IsOK() != 0 && lOutput1.IsOK() != 0)
  {
    // Load image into input data
    unsigned char *inData = (unsigned char *)lInput0.GetDataPtr();
    memcpy(inData, in0.data, lSrcWidth * lSrcHeight);

    // Run the APEX process
    FAST9_PI process0;

    // init
    lRetVal |= process0.Initialize();
	lRetVal |= process0.ConnectIO(FAST9_GR_IN0, lInput0);
	lRetVal |= process0.ConnectIO(FAST9_GR_IN1, lInputThreshold);
	lRetVal |= process0.ConnectIO(FAST9_GR_OUT0, lOutput0);
	lRetVal |= process0.ConnectIO(FAST9_GR_OUT1, lOutput1);

    if (lRetVal)
    {
#ifdef APEX2_EMULATE
      printf("%s\n", process0.ErrorMessage());
#endif
      delete[] tempDataF;
      delete[] tempDataG;
      return -1;
    }

    // execute for the first image
#ifndef __STANDALONE__
  int64 preFast0Ticks = getTickCount();
#else
  int64 preFast0Ticks = 0;
#endif

    lRetVal |= process0.Start();
    lRetVal |= process0.Wait();

#ifndef __STANDALONE__
  fast0Ticks = getTickCount();
#else
  fast0Ticks = 0;
#endif
    double timeElapsed = FSL_TicksToSeconds(fast0Ticks - preFast0Ticks) ;
	double timeElapsedWithCopy = FSL_TicksToSeconds(fast0Ticks - startTicks);
    printf("fast 0: %f s (%f with copying)\n", timeElapsed, timeElapsedWithCopy);

    nonCopyTotalTime += timeElapsed;
    apexTime += timeElapsed;

    unsigned char *outDataF = (unsigned char *)lOutput0.GetDataPtr();
    unsigned char *outDataG = (unsigned char *)lOutput1.GetDataPtr();

    const int minBorderDist = 30;

    memcpy(tempDataF, outDataF, lSrcWidth * lSrcHeight);
    memcpy(tempDataG, outDataG, lSrcWidth * lSrcHeight);

    
#ifndef __STANDALONE__
  nonCopyFeatures0StartTicks = getTickCount();
#else
  nonCopyFeatures0StartTicks = 0;
#endif

    // compute the first image's descriptors
    for (int y = minBorderDist; y < lSrcHeight - minBorderDist; ++y)
    {
      for (int x = minBorderDist; x < lSrcWidth - minBorderDist; ++x)
      {
        Point p(x, y);
        int index = y * lSrcWidth + x;
        if (tempDataF[index] > 0)
        {
          Feature f;
          float xBase, yBase;
          //GetCentroidRotation(tempDataG, lSrcWidth, p, &xBase, &yBase);
          GetCentroidRotationLUT(tempDataG, lSrcWidth, p, &xBase, &yBase);
          f.descriptor = CreateDescriptorRotated(tempDataG, lSrcWidth, p, xBase, yBase);
          f.position = p;
          features0.push_back(f);
          filteredKeyPoints0.push_back(KeyPoint(p, 1.f));
        }
      }
    }

#ifndef __STANDALONE__
  features0Ticks = getTickCount();
#else
  features0Ticks = 0;
#endif
    timeElapsed = double(features0Ticks - nonCopyFeatures0StartTicks) / frequency;
    timeElapsedWithCopy = double(features0Ticks - fast0Ticks) / frequency;
	printf("features 0: %f s (%f with copying)\n", timeElapsed, timeElapsedWithCopy);

    nonCopyTotalTime += timeElapsed;
    armTime += timeElapsed;

    memcpy(inData, in1.data, lSrcWidth * lSrcHeight);

    FAST9_PI process1;
    lRetVal |= process1.Initialize();
    lRetVal |= process1.ConnectIO("INPUT_0", lInput0);
    lRetVal |= process1.ConnectIO("INPUT_1", lInputThreshold);
    lRetVal |= process1.ConnectIO("OUTPUT_0", lOutput0);
    lRetVal |= process1.ConnectIO("OUTPUT_1", lOutput1);
    // execute for the second image
    
#ifndef __STANDALONE__
  int64 preFast1Ticks = getTickCount();
#else
  int64 preFast1Ticks = 0;
#endif
    lRetVal |= process1.Start();
    lRetVal |= process1.Wait();

    if (lRetVal)
    {
#ifdef APEX2_EMULATE
      printf("%s\n", process1.ErrorMessage());
#endif
      delete[] tempDataF;
      delete[] tempDataG;
      return -1;
    }

#ifndef __STANDALONE__
  fast1Ticks = getTickCount();
#else
  fast1Ticks = 0;
#endif

    
    timeElapsed = double(fast1Ticks - preFast1Ticks) / frequency;
    timeElapsedWithCopy = double(fast1Ticks - features0Ticks) / frequency;
	printf("fast 1: %f s (%f with copying)\n", timeElapsed, timeElapsedWithCopy);

    nonCopyTotalTime += timeElapsed;
    apexTime += timeElapsed;

    memcpy(tempDataF, outDataF, lSrcWidth * lSrcHeight);
    memcpy(tempDataG, outDataG, lSrcWidth * lSrcHeight);

#ifndef __STANDALONE__
  nonCopyFeatures1StartTicks = getTickCount();
#else
  nonCopyFeatures1StartTicks = 0;
#endif

    // compute the second image's descriptors
    for (int y = minBorderDist; y < lSrcHeight - minBorderDist; ++y)
    {
      for (int x = minBorderDist; x < lSrcWidth - minBorderDist; ++x)
      {

        Point p(x, y);
        int index = y * lSrcWidth + x;
        if (tempDataF[index] > 0)
        {
          Feature f;
          float xBase, yBase;
          //GetCentroidRotation(tempDataG, lSrcWidth, p, &xBase, &yBase);
          GetCentroidRotationLUT(tempDataG, lSrcWidth, p, &xBase, &yBase);
          f.descriptor = CreateDescriptorRotated(tempDataG, lSrcWidth, p, xBase, yBase);
          f.position = p;
          features1.push_back(f);
          filteredKeyPoints1.push_back(KeyPoint(p, 1.f));
        }
      }
    }

#ifndef __STANDALONE__
  features1Ticks = getTickCount();
#else
  features1Ticks = 0;
#endif

    timeElapsed = double(features1Ticks - nonCopyFeatures1StartTicks) / frequency;
    timeElapsedWithCopy = double(features1Ticks - fast1Ticks) / frequency;
	printf("features 1: %f s (%f with copying)\n", timeElapsed, timeElapsedWithCopy);

    nonCopyTotalTime += timeElapsed;
    armTime += timeElapsed;
  }
  else
  {
    lRetVal = 1;
  }

  lInput0.SetFreeOnExit(true);
  lOutput0.SetFreeOnExit(true);
  lOutput1.SetFreeOnExit(true);

  const int minDistLimit = 40;
  const int rangeTest = 40;

  double apexMatchTime = 0.f;
  if (apu_matching)
  {
    const unsigned int matchingDataChunkX = 128;
    const unsigned int matchingDataChunkY = 4;
    const unsigned int cuCount = 32;

    int64 matchTicksPre, matchTicksPost;
    //TODO: different descriptors for the frames!
    DataDescriptor matchesData0(512, 1, DATATYPE_16S);
    DataDescriptor matchesData1(512, 1, DATATYPE_16S);
    DataDescriptor descriptorsData0(matchingDataChunkX * cuCount, matchingDataChunkY, DATATYPE_08U);
    DataDescriptor descriptorsData1(matchingDataChunkX * cuCount, matchingDataChunkY, DATATYPE_08U);
    DataDescriptor descriptorConfiguration(4, 1, DATATYPE_16U);
    int16_t* matchesDataPtr = (int16_t*)matchesData0.GetDataPtr();
    uint16_t* descriptorConfigurationPtr = (uint16_t*)descriptorConfiguration.GetDataPtr();
    descriptorConfigurationPtr[0] = (uint16_t)features0.size();
    descriptorConfigurationPtr[1] = (uint16_t)features1.size();
    descriptorConfigurationPtr[2] = (uint16_t)minDistLimit;
    descriptorConfigurationPtr[3] = (uint16_t)rangeTest;

    //TODO: extremely hackish...
    uint8_t* descriptorsData0Ptr = (uint8_t*)descriptorsData0.GetDataPtr();
    for (unsigned int h = 0; h < matchingDataChunkY; ++h)
    {
      for (unsigned int i = 0; i < matchingDataChunkX; ++i)
      {
        unsigned int index = h * matchingDataChunkX + i;
        int rowOffset = h * matchingDataChunkX * cuCount;
        for (unsigned int j = 0; j < cuCount; ++j)
        {
          descriptorsData0Ptr[rowOffset + j * matchingDataChunkX + i] = index < features0.size() ? features0[index].descriptor.GetByte(j) : 0;
        }
      }
    }
    uint8_t* descriptorsData1Ptr = (uint8_t*)descriptorsData1.GetDataPtr();
    for (unsigned int h = 0; h < matchingDataChunkY; ++h)
    {
      for (unsigned int i = 0; i < matchingDataChunkX; ++i)
      {
        unsigned int index = h * matchingDataChunkX + i;
        int rowOffset = h * matchingDataChunkX * cuCount;
        for (unsigned int j = 0; j < cuCount; ++j)
        {
          descriptorsData1Ptr[rowOffset + j * matchingDataChunkX + i] = index < features1.size() ? features1[index].descriptor.GetByte(j) : 0;
        }
      }
    }

    MATCH_DESCRIPTORS_PI matchingProcess;
    lRetVal |= matchingProcess.Initialize();
    lRetVal |= matchingProcess.ConnectIO(MATCH_DESCR_GR_IN0, descriptorsData0);
	lRetVal |= matchingProcess.ConnectIO(MATCH_DESCR_GR_IN1, descriptorsData1);
	lRetVal |= matchingProcess.ConnectIO(MATCH_DESCR_GR_CFG, descriptorConfiguration);
	lRetVal |= matchingProcess.ConnectIO(MATCH_DESCR_GR_OUT0, matchesData0);
	lRetVal |= matchingProcess.ConnectIO(MATCH_DESCR_GR_OUT1, matchesData1);

#ifndef __STANDALONE__
  matchTicksPre = getTickCount();
#else
  matchTicksPre = 0;
#endif

	
    lRetVal |= matchingProcess.Start();
    lRetVal |= matchingProcess.Wait();
#ifndef __STANDALONE__
  matchTicksPost = getTickCount();
#else
  matchTicksPost = 0;
#endif


    if (lRetVal)
    {
#ifdef APEX2_EMULATE
      printf("%s\n", matchingProcess.ErrorMessage());
#endif
      delete[] tempDataF;
      delete[] tempDataG;
      return -1;
    }

    for (unsigned int i0 = 0; i0 < features0.size(); ++i0)
    {
      int matchedTo = (int)matchesDataPtr[i0];
      if (matchedTo >= 0)
      {
        DMatch m;
        m.imgIdx = 0;
        m.queryIdx = (int)i0;
        m.trainIdx = matchedTo;
        m.distance = float(.0f);
        matches.push_back(m);
      }
    }

    matchesData0.SetFreeOnExit(true);
    matchesData1.SetFreeOnExit(true);
    descriptorsData0.SetFreeOnExit(true);
    descriptorsData1.SetFreeOnExit(true);
    descriptorConfiguration.SetFreeOnExit(true);

    apexMatchTime = double(matchTicksPost - matchTicksPre) / frequency;
    apexTime += apexMatchTime;
  }
  else
  {
    // match the keypoints
    // TODO: now just simple and incorrect matching, should be a stable marriage problem?
    for (unsigned int i0 = 0; i0 < features0.size(); ++i0)
    {
      //for range testing
      int hamDistA = INT_MAX;
      int hamDistB = INT_MAX;
      Feature f0 = features0[i0];
      int f1Index = -1;
      for (unsigned int i1 = 0; i1 < features1.size(); ++i1)
      {
        Feature f1 = features1[i1];
        //popcount early exit didn't help
        int d = f0.descriptor.HammingDistance(f1.descriptor);
        if (f1.matchedTo >= 0)
        {
          //overwrite... what if it's not a final match after the overwrite?
          //if (d >= f1.matchDist)
          {
            continue;
          }

          features0[f1.matchedTo].matchedTo = -1;
          features1[i1].matchedTo = -1;
        }

        if (((unsigned int)d) <= minDistLimit)
        {
          if (d < hamDistA)
          {
            hamDistB = hamDistA;
            hamDistA = d;
            f1Index = i1;
          }
          else if (d < hamDistB)
          {
            hamDistB = d;
          }
        }
        else if (d < hamDistB)
        {
          hamDistB = d;
        }
      }

      if (f1Index >= 0 && (hamDistB - hamDistA > rangeTest))
      {
        features0[i0].matchedTo = f1Index;
        features1[f1Index].matchedTo = i0;
        features0[i0].matchDist = features1[f1Index].matchDist = hamDistA;
      }
    }

    //TODO: can be performed in previous cycle when not using overwrites
    for (unsigned int i0 = 0; i0 < features0.size(); ++i0)
    {
      Feature f0 = features0[i0];
      if (f0.matchedTo >= 0)
      {
        DMatch m;
        m.imgIdx = 0;
        m.queryIdx = i0;
        m.trainIdx = f0.matchedTo;
        m.distance = float(f0.matchDist);
        matches.push_back(m);
      }
    }
  }

#ifndef __STANDALONE__
  int64 endTicks = getTickCount();
#else
  int64 endTicks = 0;
#endif

  double timeElapsed = double(endTicks - features1Ticks) / frequency;
  armTime += timeElapsed;
  if (apu_matching)
  {
    printf("matching (apu): %f s\n", apexMatchTime);
    armTime -= apexMatchTime;
  }
  else
  {
    printf("matching: %f s\n", timeElapsed);
  }

  timeElapsed = double(endTicks - startTicks) / frequency;
  printf("total: %f s (%f with copying)\n", nonCopyTotalTime, timeElapsed);
  printf("arm: %f s, apex: %f s\n", armTime, apexTime);

  Mat out(in0.rows, in0.cols + in1.cols, CV_8UC3);
  
  for (int i = 0; i < filteredKeyPoints0.size(); ++i)
	circle(in0, filteredKeyPoints0[i].pt, 2, Scalar(50, 50, 50), 2);
  
  for (int i = 0; i < filteredKeyPoints1.size(); ++i)
	circle(in1, filteredKeyPoints1[i].pt, 2, Scalar(50, 50, 50), 2);
  
  for (int j = 0; j < in0.rows; ++j)
  for (int i = 0; i < in0.cols; ++i)
  {
	  out.at<Vec3b>(j, i)[0] = in0.at<unsigned char>(j, i);
	  out.at<Vec3b>(j, i)[1] = in0.at<unsigned char>(j, i);
	  out.at<Vec3b>(j, i)[2] = in0.at<unsigned char>(j, i);
	  out.at<Vec3b>(j, i+in0.cols)[0] = in1.at<unsigned char>(j, i);
	  out.at<Vec3b>(j, i+in0.cols)[1] = in1.at<unsigned char>(j, i);
	  out.at<Vec3b>(j, i+in0.cols)[2] = in1.at<unsigned char>(j, i);
  }
  
  unsigned char color = 50;
  int sw = 0;
  for( int i = 0; i < matches.size(); i++ )
  {
      int i1 = matches[i].queryIdx;
      int i2 = matches[i].trainIdx;
     
      Point kp1 = filteredKeyPoints0[i1].pt;
	  Point kp2 = filteredKeyPoints1[i2].pt;
	  kp2.x += in0.cols;
	  Scalar col;
	  if (sw % 3 == 0)
		  col = Scalar(255, color, color);
	  if (sw % 3 == 1)
		  col = Scalar(color, 255, color);
	  if (sw % 3 == 2)
		  col = Scalar(color, color, 255);
	  circle(out, kp1, 2, col, 2);
	  circle(out, kp2, 2, col, 2);
	  line( out, kp1, kp2, col, 1, CV_AA);
	  color += 50;
	  sw += 1;
	  
    
    }
 // drawMatches(in0, filteredKeyPoints0, in1, filteredKeyPoints1, matches, out);
  
#ifdef __STANDALONE__
  cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
  io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
  
  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(out.cols/2, out.rows/2), 180, 1.0);
  
  cv::Mat dst_roi = output_mat(cv::Rect(0, (1080 -  (out.rows * (1920.0 / out.cols)))/2, 1920, out.rows * (1920.0 / out.cols)));
  
  //warpAffine(out, dst_roi, rot_mat, out.size());
  warpAffine(out, out, rot_mat, out.size());
  cv::resize(out, dst_roi, cv::Size(0, 0), 1920.0 / out.cols, 1920.0 / out.cols, cv::INTER_NEAREST);
  
  //out.copyTo(dst_roi);
  output.PutFrame(output_mat.data);
  //if (dd_out == ref_out) printf("Data match with reference.\n");
  //else printf("Data do NOT match with reference.\n");
#else
  imwrite(OUTPUT_ROOT"out.png", out);
#endif

  

  delete[] tempDataF;
  delete[] tempDataG;

#ifdef APEX2_EMULATE
  imshow("matches", out);
  waitKey();
#endif

  return lRetVal;
}
