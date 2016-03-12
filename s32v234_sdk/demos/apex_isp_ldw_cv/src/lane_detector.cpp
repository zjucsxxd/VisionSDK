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
#include "lane_detector.h"

#include "least_squares_line.h"
#include <config_ldw.h>
#include "apex.h"

////////////////////////////////////////////////////////////////////////////////
// Aux structure to be used for sorting two vectors of vectors along Z axis
////////////////////////////////////////////////////////////////////////////////
struct vectorSorter {
  bool operator() (cv::Vec3d pt1, cv::Vec3d pt2) 
  { 
    return (pt1.val[2] < pt2.val[2]); 
  }
} vectorSort;

////////////////////////////////////////////////////////////////////////////////
// Constructor
// Initializes parameters and opens the input file
// Pre-computes camera parameters.
// @param filename Input file
// @param params Detection parameters
////////////////////////////////////////////////////////////////////////////////
LaneDetector::LaneDetector() //: m_maximum_process(APEX_APEX1)
{ 
  // Init frame counter
  m_frame_counter = 0;
  
  // Init pre-computed lookup line ends
  m_lookup_line_ends = new cv::Point2i[CONFIG_LOOKUP_LINES];

  // Init lookup lines origin
  m_lookup_line_origin = cv::Point2i(CONFIG_BIRD_WIDTH / 2, 
				     CONFIG_BIRD_HEIGHT - 1);
  cv::Point2i end(0, CONFIG_BIRD_HEIGHT);

  // Compute line step (angular) and pre-compute line ends
  double step = CV_PI / CONFIG_LOOKUP_LINES;
  int i;
  double angle; 
  for (i = 0, angle = 0; i < CONFIG_LOOKUP_LINES; ++i, angle += step)
  {
    cv::Point2i line;
    line.y = (int)((double)end.x*cos(angle) - (double)end.y*sin(angle) + 0.5);
    line.x = (int)((double)end.x*sin(angle) + (double)end.y*cos(angle) + 0.5);

    line.x += m_lookup_line_origin.x;
    line.y += m_lookup_line_origin.y;
    m_lookup_line_ends[i] = line;
  } 

  // Initialize Kalman filters
  m_kfLeftA.Initialize( CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 1);
  m_kfLeftB.Initialize( CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 0);
  m_kfLeftC.Initialize( CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 10);
  m_kfRightA.Initialize(CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 1);
  m_kfRightB.Initialize(CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 0);
  m_kfRightC.Initialize(CONFIG_KALMAN_MEASUREMENT_NOISE, 
			CONFIG_KALMAN_POST_ERROR, 10);

  // Init warning flags
  m_left_warning = false;
  m_right_warning = false;
  m_inside_lane = true;
  m_lane_healthy = true;
  
  for (i = 0; i < 10; ++i)
    m_lane_healthy_history.push_back(true);

  // History maximum image initi
  m_bird_max = cv::Mat::zeros(cv::Size(CONFIG_BIRD_WIDTH, 
				       CONFIG_BIRD_HEIGHT), 
			      CV_8UC1);
  
  // History offset init
  m_bird_history_offset = 0;
  
  // Init history edge images
  m_bird_history_icp = new icp::DataDescriptor[CONFIG_HISTORY];
  for (i = 0; i < CONFIG_HISTORY; ++i)
    m_bird_history_icp[i].Init(CONFIG_BIRD_WIDTH, 
			       CONFIG_BIRD_HEIGHT, 
			       icp::DATATYPE_08U);
    
  m_bird_history_icp_last = m_bird_history_icp;
  m_bird_max_icp.Init(CONFIG_BIRD_WIDTH, 
		      CONFIG_BIRD_HEIGHT, 
		      icp::DATATYPE_08U);
  
  // Initialize history APEX process
  m_maximum_process.Initialize();
  m_maximum_process.ConnectIO("SRC_0",  m_bird_history_icp[0]);
  m_maximum_process.ConnectIO("SRC_1",  m_bird_history_icp[1]);
  m_maximum_process.ConnectIO("SRC_2",  m_bird_history_icp[2]);
  m_maximum_process.ConnectIO("SRC_3",  m_bird_history_icp[3]);
  m_maximum_process.ConnectIO("SRC_4",  m_bird_history_icp[4]);
  m_maximum_process.ConnectIO("SRC_5",  m_bird_history_icp[5]);
  m_maximum_process.ConnectIO("SRC_6",  m_bird_history_icp[6]);
  m_maximum_process.ConnectIO("SRC_7",  m_bird_history_icp[7]);
  m_maximum_process.ConnectIO("SRC_8",  m_bird_history_icp[8]);
  m_maximum_process.ConnectIO("SRC_9",  m_bird_history_icp[9]);
  m_maximum_process.ConnectIO("SRC_10", m_bird_history_icp[10]);
  m_maximum_process.ConnectIO("SRC_11", m_bird_history_icp[11]);
  m_maximum_process.ConnectIO("SRC_12", m_bird_history_icp[12]);
  m_maximum_process.ConnectIO("SRC_13", m_bird_history_icp[13]);
  m_maximum_process.ConnectIO("SRC_14", m_bird_history_icp[14]);
  m_maximum_process.ConnectIO("DST_IMG", m_bird_max_icp);

  //m_maximum_process.Start_Prepare();
}

////////////////////////////////////////////////////////////////////////////////
// Destructor - frees resources
////////////////////////////////////////////////////////////////////////////////
LaneDetector::~LaneDetector()
{
  for (int i = 0; i < CONFIG_HISTORY; ++i)
    m_bird_history_icp[i].SetFreeOnExit(true);
  delete[] m_bird_history_icp;
  delete[] m_lookup_line_ends;
  
}

////////////////////////////////////////////////////////////////////////////////
// Auxiliary function used in GetNextFrame
// Saves current frame, warps bird eye image and computes maximum image
// from n last bird eye frames
////////////////////////////////////////////////////////////////////////////////

void LaneDetector::SaveHistory()
{
  // Convert input image to grayscale
  cv::Mat image;
  cv::cvtColor(m_color_image, image, CV_BGR2GRAY);
  
  // Warp it into bird eye view
  warp.Warp_BirdEye(image, m_bird_image, m_transform);
  
  // Copy result in bird eye history vector and incremnt offset
  memcpy(m_bird_history_icp_last->GetDataPtr(), 
	 m_bird_image.data, 
	 m_bird_image.rows * m_bird_image.cols);

  // Start APEX History save
  /*HISTORY_MAXIMUM m_maximum_process2(APEX_APEX1);
  m_maximum_process2.Initialize();
  m_maximum_process2.ConnectIO("SRC_0",  m_bird_history_icp[0]);
  m_maximum_process2.ConnectIO("SRC_1",  m_bird_history_icp[1]);
  m_maximum_process2.ConnectIO("SRC_2",  m_bird_history_icp[2]);
  m_maximum_process2.ConnectIO("SRC_3",  m_bird_history_icp[3]);
  m_maximum_process2.ConnectIO("SRC_4",  m_bird_history_icp[4]);
  m_maximum_process2.ConnectIO("SRC_5",  m_bird_history_icp[5]);
  m_maximum_process2.ConnectIO("SRC_6",  m_bird_history_icp[6]);
  m_maximum_process2.ConnectIO("SRC_7",  m_bird_history_icp[7]);
  m_maximum_process2.ConnectIO("SRC_8",  m_bird_history_icp[8]);
  m_maximum_process2.ConnectIO("SRC_9",  m_bird_history_icp[9]);
  m_maximum_process2.ConnectIO("SRC_10", m_bird_history_icp[10]);
  m_maximum_process2.ConnectIO("SRC_11", m_bird_history_icp[11]);
  m_maximum_process2.ConnectIO("SRC_12", m_bird_history_icp[12]);
  m_maximum_process2.ConnectIO("SRC_13", m_bird_history_icp[13]);
  m_maximum_process2.ConnectIO("SRC_14", m_bird_history_icp[14]);
  m_maximum_process2.ConnectIO("DST_IMG", m_bird_max_icp);*/

  m_maximum_process.Start();
  //m_maximum_process.Start_Run();
  
  m_bird_history_offset = (m_bird_history_offset + 1) % CONFIG_HISTORY;
  m_bird_history_icp_last = m_bird_history_icp + m_bird_history_offset;
  
  //m_maximum_process.Wait_NoReset();
  m_maximum_process.Wait();
  
  // Copy result into OpenCV structure
  memcpy(m_bird_max.data, 
	 m_bird_max_icp.GetDataPtr(), 
	 m_bird_image.rows * m_bird_image.cols);	
}

////////////////////////////////////////////////////////////////////////////////
// Auxiliary function used in GetNextFrame
// Finds lane candidate points 
////////////////////////////////////////////////////////////////////////////////
void LaneDetector::GetLinePoints()
{
  // Clear last frame 
  m_contour_pts.clear();
  m_line_right_pts.clear();
  m_line_left_pts.clear();
  
  // pass all pre-computed lines and ray-cast them until threshold
  // save the points
  for (int i = 0; i < CONFIG_LOOKUP_LINES; ++i)
  {
    cv::LineIterator it(m_bird_max, 
			m_lookup_line_origin, 
			m_lookup_line_ends[i], 4);
    
    for (int a = 0; a < it.count; a++, ++it)
    {
      if (*(unsigned char *)*it > CONFIG_WHITE_THRESHOLD && 
	  it.pos().y > CONFIG_Y_MAX_POS)
      {
	if (m_contour_pts.empty())
	{
	  m_contour_pts.push_back(it.pos());
	}
	// We save point only if its distance from the last one is bigger than
	// the parameter
	else if ((abs(it.pos().x - m_contour_pts.back().x) > 
			CONFIG_MIN_POINT_DISTANCE || 
		  abs(it.pos().y - m_contour_pts.back().y) > 
			CONFIG_MIN_POINT_DISTANCE))
	{
	  m_contour_pts.push_back(it.pos());
	}
	break;
      }
    }
  }

  // From found points, get the equations
  std::vector<cv::Vec3d> lineLeft_eq;
  std::vector<cv::Vec3d> lineRight_eq;
  
  // First, get left and right point candidates
  for (int i = 0; i < (int)m_contour_pts.size() - 1; ++i)
  {
    cv::Vec2d vect(m_contour_pts[i + 1].x - m_contour_pts[i].x, 
		   m_contour_pts[i + 1].y - m_contour_pts[i].y);
    
    vect = cv::normalize(vect);
    double angle = acos(vect.dot(cv::Vec2d(1.0, 0.0)));
    // if two points are ~vertical, we continue
    if (abs(angle - CV_PI / 2) < CONFIG_MAX_ANGLE_FROM_VERTICAL)
    {
      // from the direction of the vector, we decide left or right lane
      cv::Vec2d norm(vect.val[1], -vect.val[0]);
      double c =  -(m_contour_pts[i].x * norm.val[0] + 
		  m_contour_pts[i].y * norm.val[1]);

      // right lane candidate
      if (vect.val[1] < 0)
      {
	lineRight_eq.push_back(cv::Vec3d(norm.val[0], norm.val[1], c));
      }
      // left lane candidate
      else
      {	
	lineLeft_eq.push_back(cv::Vec3d(norm.val[0], norm.val[1], c));
      }
    }
  }

  sort(lineLeft_eq.begin(), lineLeft_eq.end(), vectorSort);
  sort(lineRight_eq.begin(), lineRight_eq.end(), vectorSort);
  
  // filter lines according to its direction
  for (unsigned int i = 0; i < m_contour_pts.size(); ++i)
  {
    if (lineLeft_eq.size() > 0)
    {
      double dist = 
	  lineLeft_eq[lineLeft_eq.size() / 2].val[0] * m_contour_pts[i].x + 
	  lineLeft_eq[lineLeft_eq.size() / 2].val[1] * m_contour_pts[i].y + 
	  lineLeft_eq[lineLeft_eq.size() / 2].val[2];
	  
      if (abs(dist) < CONFIG_MAX_DISTANCE_FROM_PREDICTED_LINE)
      {
	m_line_left_pts.push_back(m_contour_pts[i]);
      }
    }
    if (lineRight_eq.size() > 0)
    {
      double dist = 
	  lineRight_eq[lineRight_eq.size() / 2].val[0] * m_contour_pts[i].x + 
	  lineRight_eq[lineRight_eq.size() / 2].val[1] * m_contour_pts[i].y + 
	  lineRight_eq[lineRight_eq.size() / 2].val[2];
	  
      if (abs(dist) < CONFIG_MAX_DISTANCE_FROM_PREDICTED_LINE)
      {
	m_line_right_pts.push_back(m_contour_pts[i]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// Auxiliary function used in GetNextFrame
// Approximates left lane 
////////////////////////////////////////////////////////////////////////////////
void LaneDetector::GetApproxLineLeft()
{
  // get detected lane
  cv::Vec3d eq(m_kfLeftA.GetValue(), 
	       m_kfLeftB.GetValue(), 
	       m_kfLeftC.GetValue());

  // If something is found
  if (m_line_left_pts.size() > 0)
  {
    // approximate left line
    cv::Vec2d lineLeftApprox = 
			  LeastSquaresLine::ApproximateLine(m_line_left_pts);
    cv::Vec3d eqbackup(lineLeftApprox.val[0], -1.0, lineLeftApprox.val[1]);

    cv::Vec2d norm(eqbackup.val[0], eqbackup.val[1]);
    double lenght = sqrt(norm.val[0] * norm.val[0] + norm.val[1] * norm.val[1]);
    eqbackup.val[0] /= lenght;
    eqbackup.val[1] /= lenght;
    eqbackup.val[2] /= lenght;

    // normalize direction
    if (eqbackup.val[0] > 0)
    {
      eqbackup.val[0] *= -1.0;
      eqbackup.val[1] *= -1.0;
      eqbackup.val[2] *= -1.0;
    }

    cv::Vec2d linevec(eqbackup.val[1], -eqbackup.val[0]);
    double angle = acos(linevec.dot(cv::Vec2d(0.0, 1.0)));

    // If angle is withing borders, we update Kalman filter
    if (angle < CONFIG_MAX_ANGLE_FROM_VERTICAL)
    {
      m_kfLeftA.NextMeasurement(eqbackup.val[0]);
      m_kfLeftB.NextMeasurement(eqbackup.val[1]);
      m_kfLeftC.NextMeasurement(eqbackup.val[2]);
    }
  }

  // Compite points on line
  cv::Point one(0, CONFIG_Y_MAX_POS);
  cv::Point two(0, m_bird_image.rows-1);
	  
  one.x = (int)(-(one.y * eq.val[1] + eq.val[2]) / eq.val[0] + 0.5);
  two.x = (int)(-(two.y * eq.val[1] + eq.val[2]) / eq.val[0] + 0.5);

  m_detected_lane.left_bird[0] = one;
  m_detected_lane.left_bird[1] = two;

  cv::Mat pt_bird(cv::Size(1, 3), CV_64FC1);
  cv::Mat pt_scene(cv::Size(1, 3), CV_64FC1);

  pt_bird.at<double>(0, 0) = one.x;
  pt_bird.at<double>(1, 0) = one.y;
  pt_bird.at<double>(2, 0) = 1;

  gemm(m_transform.GetHMat(),pt_bird,1,NULL,0,pt_scene);

  cv::Point2i scene;
  if (pt_scene.at<double>(2, 0) != 0)
  {
	  one.x = (int)(pt_scene.at<double>(0, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
	  one.y = (int)(pt_scene.at<double>(1, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
  }

  pt_bird.at<double>(0, 0) = two.x;
  pt_bird.at<double>(1, 0) = two.y;
  pt_bird.at<double>(2, 0) = 1;

  gemm(m_transform.GetHMat(),pt_bird,1,NULL,0,pt_scene);

  if (pt_scene.at<double>(2, 0) != 0)
  {
	  two.x = (int)(pt_scene.at<double>(0, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
	  two.y = (int)(pt_scene.at<double>(1, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
  }

  m_detected_lane.left[0] = one; 
  m_detected_lane.left[1] = two;
  m_detected_lane.left_eq = eq;
}

////////////////////////////////////////////////////////////////////////////////
// Auxiliary function used in GetNextFrame
// Approximates right lane 
////////////////////////////////////////////////////////////////////////////////
void LaneDetector::GetApproxLineRight()
{
  // get detected lane
  cv::Vec3d eq(m_kfRightA.GetValue(), 
	       m_kfRightB.GetValue(), 
	       m_kfRightC.GetValue());

  // If something is found
  if (m_line_right_pts.size() > 0)
  {
    // approximate right line
    cv::Vec2d lineRightApprox = 
			  LeastSquaresLine::ApproximateLine(m_line_right_pts);

    cv::Vec3d eqbackup(lineRightApprox.val[0], -1.0, lineRightApprox.val[1]);

    cv::Vec2d norm(eqbackup.val[0], eqbackup.val[1]);
    double lenght = sqrt(norm.val[0] * norm.val[0] + norm.val[1] * norm.val[1]);
    eqbackup.val[0] /= lenght;
    eqbackup.val[1] /= lenght;
    eqbackup.val[2] /= lenght;

    // normalize direction
    if (eqbackup.val[0] > 0)
    {
      eqbackup.val[0] *= -1.0;
      eqbackup.val[1] *= -1.0;
      eqbackup.val[2] *= -1.0;
    }

    cv::Vec2d linevec(eqbackup.val[1], -eqbackup.val[0]);
    double angle = acos(linevec.dot(cv::Vec2d(0.0, 1.0)));

    // If angle is withing borders, we update Kalman filter
    if (angle < CONFIG_MAX_ANGLE_FROM_VERTICAL)
    {
      m_kfRightA.NextMeasurement(eqbackup.val[0]);
      m_kfRightB.NextMeasurement(eqbackup.val[1]);
      m_kfRightC.NextMeasurement(eqbackup.val[2]);
    }
  }

  // Compite points on line
  cv::Point one(0, CONFIG_Y_MAX_POS);
  cv::Point two(0, m_bird_image.rows - 1);

  one.x = (int)(-(one.y * eq.val[1] + eq.val[2]) / eq.val[0] + 0.5);
  two.x = (int)(-(two.y * eq.val[1] + eq.val[2]) / eq.val[0] + 0.5);

  m_detected_lane.right_bird[0] = one;
  m_detected_lane.right_bird[1] = two;

  cv::Mat pt_bird(cv::Size(1, 3), CV_64FC1);
  cv::Mat pt_scene(cv::Size(1, 3), CV_64FC1);

  pt_bird.at<double>(0, 0) = one.x;
  pt_bird.at<double>(1, 0) = one.y;
  pt_bird.at<double>(2, 0) = 1;

  gemm(m_transform.GetHMat(),pt_bird,1,NULL,0,pt_scene);

  cv::Point2i scene;
  if (pt_scene.at<double>(2, 0) != 0)
  {
	  one.x = (int)(pt_scene.at<double>(0, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
	  one.y = (int)(pt_scene.at<double>(1, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
  }

  pt_bird.at<double>(0, 0) = two.x;
  pt_bird.at<double>(1, 0) = two.y;
  pt_bird.at<double>(2, 0) = 1;

  gemm(m_transform.GetHMat(),pt_bird,1,NULL,0,pt_scene);

  if (pt_scene.at<double>(2, 0) != 0)
  {
	  two.x = (int)(pt_scene.at<double>(0, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
	  two.y = (int)(pt_scene.at<double>(1, 0) / 
			pt_scene.at<double>(2, 0) + 0.5);
  }

  m_detected_lane.right[0] = one;
  m_detected_lane.right[1] = two;
  m_detected_lane.right_eq = eq;
}

////////////////////////////////////////////////////////////////////////////////
// Returns lane information for current frame
// @return Detected lane
////////////////////////////////////////////////////////////////////////////////
Lane LaneDetector::GetCurrentLane()
{
	return m_detected_lane;
}

////////////////////////////////////////////////////////////////////////////////
// Function loads next frame from the input file and finds lane position
// using implemented algorithm.
// @return True if there is frame read and detected
////////////////////////////////////////////////////////////////////////////////
bool LaneDetector::GetNextFrame(char *buffer)
{
  // Get next frame
  m_color_image = cv::Mat(CONFIG_SCENE_SIZE_H, CONFIG_SCENE_SIZE_W, CV_8UC3, buffer);
  if (m_color_image.empty()) return false;

  ++m_frame_counter;

  SaveHistory();
  
  // If we fill whole history buffer, we continue
  if (m_frame_counter > CONFIG_HISTORY)
  {
    // detect lanes and crossings
    GetLinePoints();
    GetApproxLineLeft();
    GetApproxLineRight();

    // Check state of lanes (healthy?)
    cv::Vec2d left_vector(m_detected_lane.left_eq.val[1], 
			  -m_detected_lane.left_eq.val[0]);
    
    cv::Vec2d right_vector(m_detected_lane.right_eq.val[1], 
			   -m_detected_lane.right_eq.val[0]);
    
    double angle = acos(left_vector.dot(right_vector));

    // TODO to parameters
    float left_car_corner = 75 - m_detected_lane.left_bird[0].x;
    float right_car_corner = m_detected_lane.right_bird[0].x - 117;

    if (angle < 0.15 && left_car_corner > 0 && right_car_corner > 0) 
      m_lane_healthy = true;
    else 
      m_lane_healthy = false;

    m_lane_healthy_history.pop_front();
    m_lane_healthy_history.push_back(m_lane_healthy);
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////
// Function checks if lane was crossed in current frame
// TODO to parameters
////////////////////////////////////////////////////////////////////////////////
void LaneDetector::CheckLaneCross()
{
  cv::Rect left_check_rect(60, 200, 10, 40);
  cv::Rect right_check_rect(192 - 85, 200, 10, 40);

  cv::Mat mask_left = m_bird_max(left_check_rect);
  cv::Mat mask_right = m_bird_max(right_check_rect);
  
  int mean_left = 0.0;
  int mean_right = 0.0;
  for (int i = 0; i < mask_left.rows * mask_left.cols; ++i)
  {
	  mean_left += mask_left.data[i];
	  mean_right += mask_right.data[i];
  }
  mean_left /= mask_left.rows * mask_left.cols;
  mean_right /= mask_right.rows * mask_right.cols;
  printf("%d %d\n", mean_left, mean_right);

  if (mean_left > 60 && !m_right_warning)//m_inside_lane)
  {
    m_left_warning = true;
    m_inside_lane = false;

	m_lane_healthy_history.pop_front();
	m_lane_healthy_history.push_back(false);
  }
  else if (mean_right > 60 && !m_left_warning)//m_inside_lane)
  {
    m_right_warning = true;
    m_inside_lane = false;

	m_lane_healthy_history.pop_front();
	m_lane_healthy_history.push_back(false);
  }
  else if (mean_right <= 60 && mean_left <= 60)
  {
    int cnt = 0;
    for (std::list<bool>::iterator it = m_lane_healthy_history.begin(); 
	 it != m_lane_healthy_history.end(); ++it)
    {
      if (*it) ++cnt;
    }
    if (cnt == 10)
    {
      m_left_warning = false;
      m_right_warning = false;
      m_inside_lane = true;
    }
  }	
  //cv::rectangle(m_bird_image, left_check_rect, cv::Scalar(255, 255, 255));
  //cv::rectangle(m_bird_image, right_check_rect, cv::Scalar(255, 255, 255));
}