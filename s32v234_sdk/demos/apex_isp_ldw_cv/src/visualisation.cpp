#include <visualisation.h>

namespace visualisation
{
  static int left_warning = -10;
  static int right_warning = -10;
////////////////////////////////////////////////////////////////////////////////
// Function draws a left lane cross warning into the mat image
////////////////////////////////////////////////////////////////////////////////
void drawLeftWarning(cv::Mat mat)
{
  cv::circle(mat, cv::Point(30, 33), 25, cv::Scalar(0, 0, 255), 2);
  
  cv::putText(mat, "Lane crossing!", cv::Point(62, 35), 
	      1, 1.5, cv::Scalar(0, 0, 255), 1);
  
  // Warning counter - if it's negative, we show exclamation mark, if not, 
  // we hide it - the flashing effect
  ++left_warning;
  if (left_warning > 0)
  {
    if (left_warning > 10) left_warning = -10;
    
    cv::line(mat, cv::Point(30, 20), cv::Point(30, 35), 
	     cv::Scalar(0, 0, 255), 4);
    
    cv::circle(mat, cv::Point(30, 45), 4, cv::Scalar(0, 0, 255), -1);

  }
}

////////////////////////////////////////////////////////////////////////////////
// Function draws a right lane cross warning into the mat image
////////////////////////////////////////////////////////////////////////////////
void drawRightWarning(cv::Mat mat)
{
  cv::circle(mat, cv::Point(640 - 30, 33), 25, cv::Scalar(0, 0, 255), 2);
  
  cv::putText(mat, "Lane crossing!", cv::Point(640 - 250, 35), 
	      1, 1.5, cv::Scalar(0, 0, 255), 1);
  
  // Warning counter - if it's negative, we show exclamation mark, if not, 
  // we hide it - the flashing effect
  ++right_warning;
  if (right_warning > 0)
  {
    if (right_warning > 10) right_warning = -10;
    
    cv::line(mat, cv::Point(640 - 30, 20), cv::Point(640 - 30, 35), 
	     cv::Scalar(0, 0, 255), 4);
    
    cv::circle(mat, cv::Point(640 - 30, 45), 4, cv::Scalar(0, 0, 255), -1);

  }
}

////////////////////////////////////////////////////////////////////////////////
// Function draws a right lane cross warning into the mat image
////////////////////////////////////////////////////////////////////////////////
void drawLineHealthy(cv::Mat mat, LaneDetector *detector)
{
	if (detector->m_lane_healthy)
	{
		cv::line(mat, cv::Point(640 - 5, 20), cv::Point(640 - 7, 26), cv::Scalar(0, 150, 0), 3);
		cv::line(mat, cv::Point(640 + 5, 20), cv::Point(640 + 7, 26), cv::Scalar(0, 150, 0), 3);
		cv::line(mat, cv::Point(640 - 8, 30), cv::Point(640 - 10, 36), cv::Scalar(0, 150, 0), 3);
		cv::line(mat, cv::Point(640 + 8, 30), cv::Point(640 + 10, 36), cv::Scalar(0, 150, 0), 3);
		cv::line(mat, cv::Point(640 - 11, 40), cv::Point(640 - 13, 46), cv::Scalar(0, 150, 0), 3);
		cv::line(mat, cv::Point(640 + 11, 40), cv::Point(640 + 13, 46), cv::Scalar(0, 150, 0), 3);
		cv::circle(mat, cv::Point(640, 34), 25, cv::Scalar(0, 150, 0), 3);
	}
	else
	{
		cv::line(mat, cv::Point(640 + 8, 34 + 8), cv::Point(640 - 8, 34 - 8), cv::Scalar(0, 0, 150), 3);
		cv::line(mat, cv::Point(640 + 8, 34 - 8), cv::Point(640 - 8, 34 + 8), cv::Scalar(0, 0, 150), 3);
		cv::circle(mat, cv::Point(640, 34), 25, cv::Scalar(0, 0, 150), 3);
	}
      
      // reset counters for flashing warnings
      left_warning = -10;
      right_warning = -10;
}

void drawLaneQuadrangle(cv::Mat mat, LaneDetector *detector)
{
    Lane lane = detector->GetCurrentLane();
  
    // Compute lane quadrangle points
    cv::Vec2i vec_left = lane.left[1] - lane.left[0];
    cv::Vec2i vec_right = lane.right[1] - lane.right[0];

	
	lane.left[0].x = (lane.left[0].x) * 2;
    lane.left[0].y = (lane.left[0].y - 120) * 2;
    lane.right[0].x = (lane.right[0].x) * 2;
    lane.right[0].y = (lane.right[0].y - 120) * 2;
    lane.left[1].x += vec_left.val[0]*0.8;
    lane.left[1].y += vec_left.val[1] * 0.8;
    lane.right[1].x += vec_right.val[0] * 0.8;
    lane.right[1].y += vec_right.val[1] * 0.8;
	
	lane.left[1].x = (lane.left[1].x) * 2;
    lane.left[1].y = (lane.left[1].y - 120) * 2;
    lane.right[1].x = (lane.right[1].x) * 2;
    lane.right[1].y = (lane.right[1].y - 120) * 2;
	
	cv::circle(mat, cv::Point(1240, 40), 10, cv::Scalar(0, 0, 255), 2);
	cv::circle(mat, cv::Point(1240, 680), 10, cv::Scalar(0, 0, 255), 2);
	cv::circle(mat, cv::Point(40,   40), 10, cv::Scalar(0, 0, 255), 2);
	cv::circle(mat, cv::Point(40,   680), 10, cv::Scalar(0, 0, 255), 2);
	if (detector->m_lane_healthy)
	{
		line(mat, lane.left[0], lane.left[1], cv::Scalar(0, 255, 0), 3);
		line(mat, lane.right[0], lane.right[1], cv::Scalar(0, 255, 0), 3);
	}
	else
	{
		line(mat, lane.left[0], lane.left[1], cv::Scalar(0, 0, 255), 3);
		line(mat, lane.right[0], lane.right[1], cv::Scalar(0, 0, 255), 3);
	}
	
    /*std::vector<std::vector<cv::Point2i> > points(1);
    points[0].push_back(lane.left[1]);
    points[0].push_back(lane.right[1]);
    points[0].push_back(lane.right[0]);
    points[0].push_back(lane.left[0]);
	
    // Draw nice transparent lane quadrangle
    cv::Mat mask = cv::Mat::zeros(mat.size(), CV_8UC1);
    cv::fillPoly(mask, points, cv::Scalar(255));
    
    // If lane is healthy, we show green quad
    if (detector->m_lane_healthy)
    {
      for (int i = 0; i < mask.size().height*mask.size().width; ++i)
      if (mask.at<unsigned char>(i) > 0)
      {
	if (mat.at<cv::Vec3b>(i).val[1] < 155) 
	  mat.at<cv::Vec3b>(i).val[1] += 100;
	else mat.at<cv::Vec3b>(i).val[1] = 255;
      }
    }
    
    // Otherwise, we show the red one
    else
    {
      for (int i = 0; i < mask.size().height*mask.size().width; ++i)
      if (mask.at<unsigned char>(i) > 0)
      {
	if (mat.at<cv::Vec3b>(i).val[2] < 155) 
	  mat.at<cv::Vec3b>(i).val[2] += 100;
	else mat.at<cv::Vec3b>(i).val[2] = 255;
      }
    }*/
}

}