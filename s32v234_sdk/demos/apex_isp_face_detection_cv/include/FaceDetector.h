#ifndef __FACE_DETECTOR__H__
#define __FACE_DETECTOR__H__

#include <icp_data.h>
#include <tinyxml2.h>
#include "../../data/standalone/lbpcascade_frontalface.h"

#include <APU_FACE_DETECTION_LBP_10.hpp>
#include <APU_FACE_DETECTION_LBP_6.hpp>
#include <APU_FACE_DETECTION_LBP_4.hpp>
#include <APU_FACE_DETECTION_LBP_2.hpp>

const int RESX = 1280;
const int RESY = 720;
typedef int32_t STAGE_FIXED_POINT_TYPE;
const int STAGE_FRACTIONAL_BITS = 28;
const int STAGE_FIXED_POINT_MULTIPLIER = (1 << STAGE_FRACTIONAL_BITS);

const int SIZES = 8;
const int MIN_FACE_RECTANGLES = 2;

const bool SKIP_ODD = true;
  //int cusActive[SIZES] = {64, 64, 54, 54, 44, 44 };
  //int cusActive[SIZES] = { 32, 32, 26, 26, 20, 20 };
  //int cusActive[SIZES] = { 16, 16, 14, 14, 10, 10 };
  //int cusActive[SIZES] = { 40, 37, 34, 30 };
  //int cusActive[SIZES] = { 40, 36, 34, 32, 30, 28 };
  //int cusActive[SIZES] = { 42, 38, 34, 30, 26, 22 };
  

  //const int CHUNK_WIDTH_0 = 10;
  //const int CHUNK_WIDTH_1 = 6;
  const int CHUNK_WIDTH_0 = 4;
  const int CHUNK_WIDTH_1 = 4;
  

struct lbpFeature
{
  int rectangleIndex;
  int values[8];

  STAGE_FIXED_POINT_TYPE leafValuesFixed[2];

};

struct lbpRectangle
{
  int x, y, width, height;
};

struct lbpStage
{
  int firstFeatureIndex;
  int featureCount;
  STAGE_FIXED_POINT_TYPE thresholdFixed;
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

struct Size
{
  int width, height;
  Size(int X, int Y) : width(X), height(Y){}
  Size() : width(0), height(0){}
  void Set(int X, int Y)
  { 
    width = X;
	height = Y;
  }
};
  
struct FaceRectangle
{
  int x, y;
  int width, height;

  FaceRectangle(int aX, int aY, int aWidth, int aHeight);
  bool ContainsCenter(FaceRectangle& otherRectangle);
};

struct DetectedFace
{
  FaceRectangle testingFaceRectangle;

  FaceRectangle minFaceRectangle;
  FaceRectangle maxFaceRectangle;

  int faceRectangleCount;

  DetectedFace(FaceRectangle& faceRectangle);
  bool TryAddFaceRectangle(FaceRectangle& faceRectangle);
  FaceRectangle GetMidFaceRectangle();
};

class FaceDetector
{
	public:
		FaceDetector();
		void GetFaces(void * frame);
		void MarkFaces(void * frame);
	
	private:
		void InitCascades();
		void InitData();
		void FinishDetectionOnHost(int index);
		
		//FACE_DETECTION_10_PI process0(APEX_APEX0);
		//FACE_DETECTION_6_PI process1(APEX_APEX1);
		APU_FACE_DETECTION_LBP_4 process0;
		APU_FACE_DETECTION_LBP_4 process1;
		
		int lRetVal;
		tinyxml2::XMLDocument cascades;
		std::vector<lbpFeature> lbpFeatures;
		std::vector<lbpRectangle> lbpRectangles;
		std::vector<lbpStage> lbpStages;
		std::vector<DetectedFace> faces;
		
		icp::DataDescriptor dataInCascadeSizesAndSkip;
		icp::DataDescriptor dataInCascadeFeatures;
		icp::DataDescriptor dataInCascadeStages;
		icp::DataDescriptor dataInPixelShiftsA;
		icp::DataDescriptor dataInPixelOffsetsA;
		icp::DataDescriptor dataInPixelShiftsB;
		icp::DataDescriptor dataInPixelOffsetsB;
		icp::DataDescriptor dataOuts[SIZES];
		icp::DataDescriptor dataOutIntegralImages[SIZES];
		icp::DataDescriptor dataInImages[SIZES];
		icp::DataDescriptor pyramidStartFrame;
		
		APEX_lbpFeature* apexLBPFeatures;
		APEX_lbpStage* apexLBPStages;
		int apexLBPFeaturesSize;
		int apexLBPStagesSize;
		
		Size pyramidStartSize;
		Size sizes[SIZES];
		float scales[SIZES];
		
};


#endif