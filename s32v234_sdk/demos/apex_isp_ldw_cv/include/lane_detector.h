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
#ifndef _LANE_DETECTOR__H
#define _LANE_DETECTOR__H

#include <opencv2/opencv.hpp>
#include "transform_lut.h"
#include "kalman_filter.h"
#include "HISTORY_MAXIMUM.hpp"
#include <icp_data.h>
#include "warp.h"

#include <frame_input_file.h>


////////////////////////////////////////////////////////////////////////////////
/**
 * Class encapsulates detected lane data
 */
class Lane
{
  public:
    /**
     * Left lane points in camera coordinates
     */
    cv::Point2i left[2];
    
    /**
     * Right lane points in camera coordinates
     */
    cv::Point2i right[2];
    
    /**
     * Left lane points in bird eye view coordinates
     */
    cv::Point2i left_bird[2];
    
    /**
     * Right lane points in bird eye view coordinates
     */
    cv::Point2i right_bird[2];

    /**
     * Left lane line equation in bird eye view coordinates
     */
    cv::Vec3d left_eq;
    
    /**
     * Right lane line equation in bird eye view coordinates
     */
    cv::Vec3d right_eq;
};

////////////////////////////////////////////////////////////////////////////////
/**
 * Class encapsulating main lane detector functions 
 */
class LaneDetector
{
  public:
    /**
     * Constructor
     * Initializes parameters and opens the input file
     * Pre-computes camera parameters.
     * @param filename Input file
     * @param params Detection parameters
     */
    LaneDetector();
    
    /**
     * Destructor - frees resources
     */
    ~LaneDetector();

    /**
     * Function loads next frame from the input file and finds lane position
     * using implemented algorithm.
     * @return True if there is frame read and detected
     */
    bool GetNextFrame(char *buffer);
    
    /**
     * Returns lane information for current frame
     * @return Detected lane
     */
    Lane GetCurrentLane();
    
    /**
     * Function checks if lane was crossed in current frame
     */
    void CheckLaneCross();

    /**
     * Input color image
     */
    cv::Mat m_color_image;
    
    /**
     * Input bird eye image (edge intensity)
     */
    cv::Mat m_bird_image;
    
    /**
     * History maximum from bitd eye images
     */
    cv::Mat m_bird_max;
    
    /**
     * History maximum from bitd eye images
     */
    icp::DataDescriptor m_bird_max_icp;

    /**
     * True if left lane was crossed
     */
    bool m_left_warning;
    
    /**
     * True if right lane was crossed
     */
    bool m_right_warning;
    
    /**
     * True if we're safely inside lane
     */
    bool m_inside_lane;
    
    /**
     * True if detected lane is healthy
     */
    bool m_lane_healthy;
    
    	
    /**
     * Frame counter
     */
    int m_frame_counter;
    
  private:
    /**
     * Auxiliary function used in GetNextFrame
     * Saves current frame, warps bird eye image and computes maximum image
     * from n last bird eye frames
     */
    void SaveHistory();
    
    /**
     * Auxiliary function used in GetNextFrame
     * Finds lane candidate points 
     */
    void GetLinePoints();
    
    /**
     * Auxiliary function used in GetNextFrame
     * Approximates left lane 
     */
    void GetApproxLineLeft();
    
    /**
     * Auxiliary function used in GetNextFrame
     * Approximates right lane 
     */
    void GetApproxLineRight();

    /**
     * Transformation bird eye view -> scene 
     */
    Transform_LUT m_transform;

	
    /**
     * Pre-computed lookup lanes for ray casting into bird-eye view - origin
     */
    cv::Point2i m_lookup_line_origin;
    
    /**
     * Pre-computed lookup lanes for ray casting into bird-eye view - ends
     */
    cv::Point2i *m_lookup_line_ends;

    /**
     * Found contour points (inner road lane contour)
     */
    std::vector<cv::Point2i> m_contour_pts;
    
    /**
     * Filtered right lane points candidates
     */
    std::vector<cv::Point2i> m_line_right_pts;
    
    /**
     * Filtered left lane points candidates
     */
    std::vector<cv::Point2i> m_line_left_pts;
    
    /**
     * Detected and filtered lane for current frame
     */
    Lane m_detected_lane;

    /**
     * Kalman filter for left equation - a parameter
     */
    KalmanFilter m_kfLeftA;
    
    /**
     * Kalman filter for left equation - b parameter
     */
    KalmanFilter m_kfLeftB;
    
    /**
     * Kalman filter for left equation - c parameter
     */
    KalmanFilter m_kfLeftC;
    
    /**
     * Kalman filter for right equation - a parameter
     */
    KalmanFilter m_kfRightA;
    
    /**
     * Kalman filter for right equation - b parameter
     */
    KalmanFilter m_kfRightB;
    
    /**
     * Kalman filter for right equation - c parameter
     */
    KalmanFilter m_kfRightC;
	
    /**
     * Vector of bools with healthy detected lane in history
     */
    std::list<bool> m_lane_healthy_history;
	
    /**
     * APEX computed history process
     */
    HISTORY_MAXIMUM m_maximum_process;
    
    /**
     * Last n bird eye views in history
     */
    icp::DataDescriptor *m_bird_history_icp;
    
    /**
     * Pointer to the last value in circular history buffer
     */
    icp::DataDescriptor *m_bird_history_icp_last;
    
    /**
     * Offset from array of history images start to the last
     */
    int m_bird_history_offset;
    
    /**
     * Warp bird-eye
     */
    Warp warp;
};


#endif