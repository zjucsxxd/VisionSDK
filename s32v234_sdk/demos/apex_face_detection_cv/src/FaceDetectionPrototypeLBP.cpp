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

#include "tinyxml2.h"

#ifdef APEX2_EMULATE
#define USE_OPENCV_TIMER
#endif
#ifdef __INTEGRITY
#define USE_OPENCV_TIMER
#endif

#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <stdint.h>

using namespace std;
using namespace cv;
using namespace tinyxml2;

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

#define USE_FIXED_POINT 1

typedef int32_t STAGE_FIXED_POINT_TYPE;
const int STAGE_FRACTIONAL_BITS = 28;
const int STAGE_FIXED_POINT_MULTIPLIER = (1 << STAGE_FRACTIONAL_BITS);

#ifdef __STANDALONE__
  #include "../../data/standalone/input_faces.h"
  #include "../../data/standalone/lbpcascade_frontalface.h"
  #include <frame_output_dcu.h>
#endif

#ifdef APEX2_EMULATE
#include <acf_lib.hpp>
#include "../graphs/apu_face_detection_lbp_apu_process_desc.hpp"



using namespace APEX2;
#else
#include <icp_data.h>
#include <APU_FACE_DETECTION_LBP.hpp>
#include "apex.h"
#include <oal.h>
using namespace icp;
#endif

#include "../graphs/chunk_config.hpp"

#include <time.h>
#include "time_measure.h"

/*
//OpenCV int64 is 32-bit on ARM, getTickCount doesn't work correctly...
int64_t FSL_Ticks()
{
#ifdef USE_OPENCV_TIMER
  return getTickCount();
#else
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return int64_t(ts.tv_sec) * 1000000000 + int64_t(ts.tv_nsec);
#endif
}

double FSL_TicksToSeconds(int64_t ticks)
{
#ifdef USE_OPENCV_TIMER
  return ticks / getTickFrequency();
#else
  return ticks / (double)1000000000;
#endif
}
*/
struct lbpFeature
{
  int rectangleIndex;
  int values[8];
#if USE_FIXED_POINT
  STAGE_FIXED_POINT_TYPE leafValuesFixed[2];
#else
  double leafValues[2];
#endif
};

struct lbpRectangle
{
  int x, y, width, height;
};

struct lbpStage
{
  int firstFeatureIndex;
  int featureCount;
#if USE_FIXED_POINT
  STAGE_FIXED_POINT_TYPE thresholdFixed;
#else
  double threshold;
#endif
};

struct APEX_lbpFeature
{
  int32_t values[8];
  STAGE_FIXED_POINT_TYPE leafValues[2];
  uint8_t x, y, width, height;
};

struct APEX_lbpStage
{
  uint8_t featureCount;
  STAGE_FIXED_POINT_TYPE threshold;
};

#include "apu_face_detection_lbp_graph.h"

int main(int, char**)
{
#ifdef APEX2_EMULATE
  REGISTER_PROCESS_TYPE(FACE_DETECTION_PI, apu_face_detection_lbp_apu_process_desc)
#else
  // HW and resources init
  #ifndef __STANDALONE__
  OAL_MemoryAllocInit();
  #endif
  ACF_Init();
  using namespace icp;
#endif

#ifdef __STANDALONE__
    Mat input(320, 384, CV_8UC1, input_faces);
#else
    Mat input = imread(INPUT_ROOT"input_faces.png", 0);
#endif
  
  
  if (input.empty())
  {
    cout << "input image not found" << endl;
    return -1;
  }

  #ifdef __STANDALONE__
    XMLDocument cascades;
	if (cascades.LoadString(lbpcascade_frontalface) != XML_SUCCESS)
	{
		cout << "can't open the cascades file" << endl;
		return -1;
	}
  #else
    XMLDocument cascades;
	if (cascades.LoadFile(INPUT_ROOT"lbpcascade_frontalface.xml") != XML_SUCCESS)
	{
		cout << "can't open the cascades file" << endl;
		return -1;
	}
  #endif
  

  //start at the size node
  XMLNode* node = cascades.FirstChild()->NextSibling()->NextSibling()->FirstChild()->FirstChild()->NextSibling()->NextSibling();

  int windowWidth, windowHeight;

  {
    stringstream ss(node->ToElement()->GetText());
    ss >> windowHeight;
  }

  node = node->NextSibling();

  {
    stringstream ss(node->ToElement()->GetText());
    ss >> windowWidth;
  }

  //TODO: stage params?

  //stages
  node = node->NextSibling()->NextSibling()->NextSibling()->NextSibling();

  //int windowViewScale = 20;

  vector<lbpFeature> lbpFeatures;
  vector<lbpRectangle> lbpRectangles;
  vector<lbpStage> lbpStages;

  XMLNode* stageNode = node->FirstChild();

  while (stageNode)
  {
    stageNode = stageNode->NextSibling();
    lbpStage lbps;
    lbps.firstFeatureIndex = (int)lbpFeatures.size();

    XMLNode* stageSumNode = stageNode->FirstChild()->NextSibling();
    stringstream sss(stageSumNode->ToElement()->GetText());
#if USE_FIXED_POINT
    double dThr;
    sss >> dThr;
    lbps.thresholdFixed = STAGE_FIXED_POINT_TYPE(dThr * STAGE_FIXED_POINT_MULTIPLIER);
#else
    sss >> lbps.threshold;
#endif

    XMLNode* featureNode = stageSumNode->NextSibling()->FirstChild();
    while (featureNode)
    {
      featureNode = featureNode->NextSibling();
      lbpFeature lbpf;

      XMLNode* innerNode = featureNode->FirstChild();
      stringstream fss0(innerNode->ToElement()->GetText());
      string temp;
      fss0 >> temp >> temp >> lbpf.rectangleIndex >>
        lbpf.values[0] >> lbpf.values[1] >> lbpf.values[2] >> lbpf.values[3] >>
        lbpf.values[4] >> lbpf.values[5] >> lbpf.values[6] >> lbpf.values[7];

      innerNode = innerNode->NextSibling();

      stringstream fss1(innerNode->ToElement()->GetText());
#if USE_FIXED_POINT
      double dLV0, dLV1;
      fss1 >> dLV0 >> dLV1;
      lbpf.leafValuesFixed[0] = STAGE_FIXED_POINT_TYPE(dLV0 * STAGE_FIXED_POINT_MULTIPLIER);
      lbpf.leafValuesFixed[1] = STAGE_FIXED_POINT_TYPE(dLV1 * STAGE_FIXED_POINT_MULTIPLIER);
#else
      fss1 >> lbpf.leafValues[0] >> lbpf.leafValues[1];
#endif

      lbpFeatures.push_back(lbpf);

      featureNode = featureNode->NextSibling();
    }

    lbps.featureCount = (int)lbpFeatures.size() - lbps.firstFeatureIndex;
    lbpStages.push_back(lbps);

    stageNode = stageNode->NextSibling();
  }

  node = node->NextSibling();
  XMLNode* rectangleNode = node->FirstChild();
  while (rectangleNode)
  {
    lbpRectangle lbpr;
    stringstream rss(rectangleNode->FirstChild()->ToElement()->GetText());
    rss >> lbpr.x >> lbpr.y >> lbpr.width >> lbpr.height;

    lbpRectangles.push_back(lbpr);

    rectangleNode = rectangleNode->NextSibling();
  }

  //apex structs
  APEX_lbpFeature* apexLBPFeatures = new APEX_lbpFeature[lbpFeatures.size()];
  APEX_lbpStage* apexLBPStages = new APEX_lbpStage[lbpStages.size()];
  int apexLBPFeaturesSize = lbpFeatures.size() * sizeof(APEX_lbpFeature);
  int apexLBPStagesSize = lbpStages.size() * sizeof(APEX_lbpStage);

  for (unsigned int i = 0; i < lbpFeatures.size(); ++i)
  {
    lbpFeature lbpf = lbpFeatures[i];
    lbpRectangle lbpr = lbpRectangles[lbpf.rectangleIndex];
    for (int j = 0; j < 8; ++j)
    {
      apexLBPFeatures[i].values[j] = lbpf.values[j];
    }
    apexLBPFeatures[i].leafValues[0] = lbpf.leafValuesFixed[0];
    apexLBPFeatures[i].leafValues[1] = lbpf.leafValuesFixed[1];
    apexLBPFeatures[i].x = lbpr.x;
    apexLBPFeatures[i].y = lbpr.y;
    apexLBPFeatures[i].width = lbpr.width;
    apexLBPFeatures[i].height = lbpr.height;
  }

  for (unsigned int i = 0; i < lbpStages.size(); ++i)
  {
    apexLBPStages[i].threshold = lbpStages[i].thresholdFixed;
    apexLBPStages[i].featureCount = lbpStages[i].featureCount;
  }

  ////////////////////////////////cascades ready
#ifndef __STANDALONE__
  Mat outputCustom;
  cvtColor(input, outputCustom, CV_GRAY2BGR);

  Mat ii;
  integral(input, ii, CV_32S);

  int64_t preCustomTicks = FSL_Ticks();

  for (int y = 0; y < input.rows - windowHeight; ++y)
  {
    for (int x = 0; x < input.cols - windowWidth; ++x)
    {
      bool detected = true;
      for (int si = 0; si < (int)lbpStages.size(); ++si)
      {
        lbpStage lbps = lbpStages[si];

#if USE_FIXED_POINT
        STAGE_FIXED_POINT_TYPE stageSumFixed = 0;
#else
        double stageSum = .0;
#endif
        for (int fi = lbps.firstFeatureIndex; fi < lbps.firstFeatureIndex + lbps.featureCount; ++fi)
        {
          lbpFeature lbpf = lbpFeatures[fi];
          lbpRectangle lbpr = lbpRectangles[lbpf.rectangleIndex];

          //grid pattern values
          int gpv[16];

          int gridStartX = x + lbpr.x;
          int gridStartY = y + lbpr.y;
          int gridOffsetX = 0;
          int gridOffsetY = 0;

          for (int wpY = 0; wpY < 4; ++wpY)
          {
            gridOffsetX = 0;
            for (int wpX = 0; wpX < 4; ++wpX)
            {
              int wpi = wpY * 4 + wpX;

              gpv[wpi] = (int)ii.at<int32_t>(gridStartY + gridOffsetY, gridStartX + gridOffsetX);
              gridOffsetX += lbpr.width;
            }
            gridOffsetY += lbpr.height;
          }

          int center = gpv[5] + gpv[10] - gpv[6] - gpv[9];

          int c0 = gpv[0] + gpv[5] - gpv[1] - gpv[4];
          int c1 = gpv[1] + gpv[6] - gpv[2] - gpv[5];
          int c2 = gpv[2] + gpv[7] - gpv[3] - gpv[6];
          int c3 = gpv[6] + gpv[11] - gpv[7] - gpv[10];
          int c4 = gpv[10] + gpv[15] - gpv[11] - gpv[14];
          int c5 = gpv[9] + gpv[14] - gpv[10] - gpv[13];
          int c6 = gpv[8] + gpv[13] - gpv[9] - gpv[12];
          int c7 = gpv[4] + gpv[9] - gpv[5] - gpv[8];

          int code =
            (c0 >= center ? 0x0080 : 0) |
            (c1 >= center ? 0x0040 : 0) |
            (c2 >= center ? 0x0020 : 0) |
            (c3 >= center ? 0x0010 : 0) |
            (c4 >= center ? 0x0008 : 0) |
            (c5 >= center ? 0x0004 : 0) |
            (c6 >= center ? 0x0002 : 0) |
            (c7 >= center ? 0x0001 : 0);

          //get one of the 256 bits contained in values[8] indexed by code
          int featureVal = lbpf.values[code >> 5];

          int leafIndex = featureVal & (1 << (code & 0x1f)) ? 0 : 1;
#if USE_FIXED_POINT
          stageSumFixed += lbpf.leafValuesFixed[leafIndex];
#else
          stageSum += lbpf.leafValues[leafIndex];
#endif
        }

#if USE_FIXED_POINT
        if (stageSumFixed < lbps.thresholdFixed)
#else
        if (stageSum < lbps.threshold)
#endif
        {
          detected = false;
          break;
        }
      }

      if (detected)
      {
        rectangle(outputCustom, Rect(x, y, windowWidth, windowHeight), Scalar(0, 255, 0));
      }

    }
  }

  int64_t postCustomTicks = FSL_Ticks();

  std::cout << "custom implementation finished" << endl;
#endif // if 0 (custom implementation)

#ifndef __STANDALONE__
  int64_t preCascadeClassifierTicks = FSL_Ticks();
  CascadeClassifier cf(INPUT_ROOT"lbpcascade_frontalface.xml");
  if (cf.empty())
  {
    cout << "cascades not found" << endl;
    return -1;
  }
  int64_t postCascadeClassifierTicks = FSL_Ticks();
  std::cout << "cascade classifier finished" << endl;

  Mat outputRef;
  cvtColor(input, outputRef, CV_GRAY2BGR);

  int64_t preOCVTicks = FSL_Ticks();
  vector<Rect> faces;
  cf.detectMultiScale(input, faces, 1.1, 0, 0, Size(24, 24), Size(24, 24));
  //cf.detectMultiScale(input, faces);
  int64_t postOCVTicks = FSL_Ticks();

  for (unsigned int i = 0; i < faces.size(); ++i)
  {
    rectangle(outputRef, faces[i], Scalar(0, 255, 0));
  }

  std::cout << "OpenCV implementation finished" << endl;
#endif

  DataDescriptor dataInImage(input.cols, input.rows, DATATYPE_08U);
  DataDescriptor dataInCascadeSizesAndSkip(3, 1, DATATYPE_16U);

  DataDescriptor dataInCascadeFeatures(10000, 1, DATATYPE_08U);
  DataDescriptor dataInCascadeStages(200, 1, DATATYPE_08U);

  DataDescriptor dataInPixelShifts(64, 1, DATATYPE_08U);
  DataDescriptor dataInPixelOffsets(64, 1, DATATYPE_08U);

  DataDescriptor dataInSkip(1, 1, DATATYPE_08U);

  DataDescriptor dataOut(input.cols, input.rows, DATATYPE_08U);

  uint32_t* diiPtr = (uint32_t*)dataInImage.GetDataPtr();
  memcpy(diiPtr, input.data, input.cols * input.rows);

  uint16_t* cascadeSizesAndSkipPtr = (uint16_t*)dataInCascadeSizesAndSkip.GetDataPtr();
  cascadeSizesAndSkipPtr[0] = uint16_t(lbpFeatures.size());
  cascadeSizesAndSkipPtr[1] = uint16_t(lbpStages.size());
  cascadeSizesAndSkipPtr[2] = 0;

  memcpy(dataInCascadeFeatures.GetDataPtr(), apexLBPFeatures, apexLBPFeaturesSize);
  memcpy(dataInCascadeStages.GetDataPtr(), apexLBPStages, apexLBPStagesSize);

  uint8_t pixelShifts[64];
  uint8_t pixelOffsets[64];
  for (int i = 0; i < 64; ++i)
  {
    pixelShifts[i] = uint8_t(i / CHUNK_WIDTH);
    pixelOffsets[i] = uint8_t(i % CHUNK_WIDTH);
  }
  memcpy(dataInPixelShifts.GetDataPtr(), pixelShifts, 64);
  memcpy(dataInPixelOffsets.GetDataPtr(), pixelOffsets, 64);

  FACE_DETECTION_PI process;

  int lRetVal = 0;
  lRetVal |= process.Initialize();
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_IMG, dataInImage);
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_CASC_SZ, dataInCascadeSizesAndSkip);
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_CASC_FEAT, dataInCascadeFeatures);
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_CASC_STAGES, dataInCascadeStages);
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_PIX_SHFT, dataInPixelShifts);
  lRetVal |= process.ConnectIO(FACE_DET_GR_IN_PIX_OFFS, dataInPixelOffsets);
  lRetVal |= process.ConnectIO(FACE_DET_GR_OUT, dataOut);

  int64_t preAPEXTicks = FSL_Ticks();
  lRetVal |= process.Start();
  lRetVal |= process.Wait();
  int64_t postAPEXTicks = FSL_Ticks();

  printf("APEX implementation finished\n");

#ifdef APEX2_EMULATE
  if (lRetVal || process.ErrorOccured())
  {
    printf("process error!\n");
    printf("%s\n", process.ErrorMessage());
  }
#endif

  Mat outputAPEXmask(input.rows, input.cols, CV_8UC1);
  memcpy(outputAPEXmask.data, dataOut.GetDataPtr(), input.cols * input.rows);
  Mat outputAPEX;
  cvtColor(input, outputAPEX, CV_GRAY2BGR);
  for (int y = windowHeight; y < input.rows; ++y)
  {
    for (int x = 0; x < input.cols - windowWidth; ++x)
    {
      if (outputAPEXmask.at<uint8_t>(y, x) != 0)
      {
        rectangle(outputAPEX, Rect(x, y - windowHeight, windowWidth, windowHeight), Scalar(0, 255, 0));
        //rectangle(outputAPEX, Rect(x, y, 1, 1), Scalar(0, 255, 0));
      }
    }
  }

  

#ifndef __STANDALONE__
  cout << "custom host implementation: " << FSL_TicksToSeconds(postCustomTicks - preCustomTicks) << " s" << endl;
  cout << "cascade classifier implementation: " << FSL_TicksToSeconds(postCascadeClassifierTicks - preCascadeClassifierTicks) << " s" << endl;
  cout << "APEX implementation: " << FSL_TicksToSeconds(postAPEXTicks - preAPEXTicks) << " s" << endl;
  cout << "OpenCV implementation: " << FSL_TicksToSeconds(postOCVTicks - preOCVTicks) << " s" << endl;
#ifdef APEX2_EMULATE
  imshow("reference OpenCV output", outputRef);
  imwrite(OUTPUT_ROOT"faces_ref.png", outputRef);
#else
  imwrite(OUTPUT_ROOT"faces_ref.png", outputRef);
  imwrite(OUTPUT_ROOT"faces_custom.png", outputCustom);
  imwrite(OUTPUT_ROOT"faces_apex.png", outputAPEX);
#endif

#else
  cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
  io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);
	
  outputAPEX.copyTo(output_mat(cv::Rect(0, 540 - (outputAPEX.rows/2), outputAPEX.cols, outputAPEX.rows)));
  
  warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
  output.PutFrame(output_mat.data);
#endif

#ifdef APEX2_EMULATE
  imshow("input", input);
  imshow("host output", outputCustom);
  imshow("APEX output", outputAPEX);
  waitKey();
#endif



  delete[] apexLBPFeatures;
  delete[] apexLBPStages;

	return 0;
}
