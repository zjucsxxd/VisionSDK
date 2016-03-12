#ifndef __VISUALISATION__H__
#define __VISUALISATION__H__

#include <opencv2/opencv.hpp>

#include <lane_detector.h>
namespace visualisation
{
  void drawLeftWarning(cv::Mat mat);
  void drawRightWarning(cv::Mat mat);
  void drawLineHealthy(cv::Mat mat, LaneDetector *detector);
  void drawLaneQuadrangle(cv::Mat mat, LaneDetector *detector);
}

#endif