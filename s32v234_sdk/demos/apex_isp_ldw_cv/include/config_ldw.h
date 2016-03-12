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
#ifndef _CONFIG__H
#define _CONFIG__H

#include <opencv2/opencv.hpp>

#ifdef __INTEGRITY__
  #define INPUT_ROOT "/apex/"
#else
  #define INPUT_ROOT ""
#endif

//namespace config

	////////////////////////////////////////////////////////////////////////
	// Input file from front camera (BGR video)
	const std::string 	input_file = 			INPUT_ROOT"mvi_0049.avi";
	
	// Output file (BGR video)
	const std::string 	output_file = 			INPUT_ROOT"output.avi";
	
	// Input file size
	const cv::Size 		scene_size(640, 480);
	#define CONFIG_SCENE_SIZE_W 640
	#define CONFIG_SCENE_SIZE_H 480

	// Quadrangle depicting searched region around road 
	// (input frame coordinates)
	#define CONFIG_SCENE_POINT_0_0 166
	#define CONFIG_SCENE_POINT_0_1 287
	#define CONFIG_SCENE_POINT_1_0 396
	#define CONFIG_SCENE_POINT_1_1 287
	#define CONFIG_SCENE_POINT_2_0 10
	#define CONFIG_SCENE_POINT_2_1 348
	#define CONFIG_SCENE_POINT_3_0 532
	#define CONFIG_SCENE_POINT_3_1 348
	/*#define CONFIG_SCENE_POINT_2_0 10
	#define CONFIG_SCENE_POINT_2_1 358
	#define CONFIG_SCENE_POINT_3_0 497
	#define CONFIG_SCENE_POINT_3_1 358*/

	//#define CONFIG_SCENE_POINT_0_0 227
	//#define CONFIG_SCENE_POINT_0_1 222
	//#define CONFIG_SCENE_POINT_1_0 327
	//#define CONFIG_SCENE_POINT_1_1 222
	//#define CONFIG_SCENE_POINT_2_0 7
	//#define CONFIG_SCENE_POINT_2_1 305
	//#define CONFIG_SCENE_POINT_3_0 468
	//#define CONFIG_SCENE_POINT_3_1 305

	////////////////////////////////////////////////////////////////////////
	// Bird eye view size
	#define CONFIG_BIRD_SIZE_W 192
	#define CONFIG_BIRD_SIZE_H 320
	
	// Bird eye view chunk size
	#define CONFIG_BIRD_CHUNK_SIZE_W 6
	#define CONFIG_BIRD_CHUNK_SIZE_H 8
	
	
	// Bird eye view coordinates corresponding to the searched region
	// points (scene_points)
	#define CONFIG_BIRD_POINT_0_0 0
	#define CONFIG_BIRD_POINT_0_1 0
	#define CONFIG_BIRD_POINT_1_0 192
	#define CONFIG_BIRD_POINT_1_1 0
	#define CONFIG_BIRD_POINT_2_0 0
	#define CONFIG_BIRD_POINT_2_1 320
	#define CONFIG_BIRD_POINT_3_0 192
	#define CONFIG_BIRD_POINT_3_1 320
				
	// Bird eye view width
	#define CONFIG_BIRD_WIDTH 192
	
	// Bird eye view height
	#define CONFIG_BIRD_HEIGHT 320
	
	////////////////////////////////////////////////////////////////////////
	// Amount of frames from which maximum frame is computed
	// (dashed lines and noise filtering)
	#define CONFIG_HISTORY 15
	
	// Number of rays to be cast from car
	#define CONFIG_LOOKUP_LINES 320
	
	// "Ray cast" white threshold 
	#define CONFIG_WHITE_THRESHOLD 20
	
	// Maximum Y coordinate to be considered on bird eye view
	#define CONFIG_Y_MAX_POS 140
	//#define CONFIG_Y_MAX_POS 180
	
	// Minimal distance between found points
	#define CONFIG_MIN_POINT_DISTANCE 7
	
	// Maximum angle from vertical (for outlier filtering)
	#define CONFIG_MAX_ANGLE_FROM_VERTICAL 0.15
	
	// Maximum distance from first guess line
	//const double 		m_max_distance_from_predicted_line = 	2.0;
	#define CONFIG_MAX_DISTANCE_FROM_PREDICTED_LINE 2.0

	// Kalman filter measurement noise
	#define CONFIG_KALMAN_MEASUREMENT_NOISE   0.05
	
	// Kalman filter post error
	#define CONFIG_KALMAN_POST_ERROR    0.005


#endif