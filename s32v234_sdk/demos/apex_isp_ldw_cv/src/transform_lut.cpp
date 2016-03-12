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
#include "transform_lut.h"
#include "config_ldw.h"
#include <fstream>
////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////
Transform_LUT::Transform_LUT()
{
  // Init memory blocks
  m_block = (unsigned int *)malloc(sizeof(int) * (CONFIG_BIRD_SIZE_W / CONFIG_BIRD_CHUNK_SIZE_W) * (CONFIG_BIRD_SIZE_H / CONFIG_BIRD_CHUNK_SIZE_H));
			      
  m_local = (unsigned short *)malloc(sizeof(short) * CONFIG_BIRD_SIZE_W * CONFIG_BIRD_SIZE_H);
			      
  m_delta = (unsigned char *)malloc(sizeof(char) * CONFIG_BIRD_SIZE_W * CONFIG_BIRD_SIZE_H * 2);
		  
  cv::Point2f scene_points[] = {
	cv::Point2f(CONFIG_SCENE_POINT_0_0, CONFIG_SCENE_POINT_0_1),
	cv::Point2f(CONFIG_SCENE_POINT_1_0, CONFIG_SCENE_POINT_1_1),
	cv::Point2f(CONFIG_SCENE_POINT_2_0, CONFIG_SCENE_POINT_2_1),
	cv::Point2f(CONFIG_SCENE_POINT_3_0, CONFIG_SCENE_POINT_3_1) };
						  
  cv::Point2f bird_points[] = { 
    cv::Point2f(CONFIG_BIRD_POINT_0_0, CONFIG_BIRD_POINT_0_1),
	cv::Point2f(CONFIG_BIRD_POINT_1_0, CONFIG_BIRD_POINT_1_1),
	cv::Point2f(CONFIG_BIRD_POINT_2_0, CONFIG_BIRD_POINT_2_1),
	cv::Point2f(CONFIG_BIRD_POINT_3_0, CONFIG_BIRD_POINT_3_1) };
  // Compute perspective transform from bird eye points to the scene view
  m_H = cv::getPerspectiveTransform(bird_points, scene_points);
  cv::invert(m_H, m_invH);
  
  // Compute lookup tables
  CompLUTs();
}

////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////
Transform_LUT::~Transform_LUT()
{
  free(m_block);
  free(m_local);
  free(m_delta);
}

////////////////////////////////////////////////////////////////////////////////
// Gets pointer to the array of ints - block look up table
// @return Block look-up table
////////////////////////////////////////////////////////////////////////////////
unsigned int *Transform_LUT::GetBlockPtr()
{
  return m_block;
}

////////////////////////////////////////////////////////////////////////////////
// Gets pointer to the array of shorts - local offset look up table
// @return Local offset look-up table
////////////////////////////////////////////////////////////////////////////////
unsigned short *Transform_LUT::GetLocalPtr()
{
  return m_local;
}

////////////////////////////////////////////////////////////////////////////////
// Gets pointer to the array of pairs of chars - X, Y delta (decimal
// part of local offset for bilinear approximation) 
// @return decimal part of local offsets
////////////////////////////////////////////////////////////////////////////////
unsigned char *Transform_LUT::GetDeltaPtr()
{
  return m_delta;
}

////////////////////////////////////////////////////////////////////////////////
// Returns H matrix - warp from bird eye to scene
////////////////////////////////////////////////////////////////////////////////
cv::Mat Transform_LUT::GetHMat()
{
  return m_H;
}

////////////////////////////////////////////////////////////////////////////////
// Returns inverse H matrix - warp from bird eye to scene
////////////////////////////////////////////////////////////////////////////////
cv::Mat Transform_LUT::GetInverseHMat()
{
  return m_invH;
}

////////////////////////////////////////////////////////////////////////////////
// Auxiliary function computes look-up tables
////////////////////////////////////////////////////////////////////////////////
void Transform_LUT::CompLUTs()
{
  unsigned int block_index = 0;
  unsigned int loc_index = 0;
  unsigned int delta_index = 0;

  using namespace cv;
  // We are passing the bird eye image along Y axis
  for (	int y = 0; 
	y < CONFIG_BIRD_SIZE_H - CONFIG_BIRD_CHUNK_SIZE_H / 2; 
	y += CONFIG_BIRD_CHUNK_SIZE_H)
  {
    bool new_little_y = true;
    int base_x;
    int base_y;
    double base_x_f;
    double base_y_f;
    unsigned int index;
    
    // We save all data rowwise, so we need to pass everytime first Y coordinate
    // then the X one
    for (int little_y = 0; little_y <  CONFIG_BIRD_CHUNK_SIZE_H; 
	 ++little_y)
    {
      for ( int x = 0; 
	    x < CONFIG_BIRD_SIZE_W - CONFIG_BIRD_CHUNK_SIZE_W / 2; 
	    x += CONFIG_BIRD_CHUNK_SIZE_W)
      {
	Mat pt_lb(Size(1, 3), CV_64FC1);
	Mat pt_rb(Size(1, 3), CV_64FC1);
	Mat pt_lt(Size(1, 3), CV_64FC1);
	Mat pt_rt(Size(1, 3), CV_64FC1);
	Mat scene_pt_lb;
	Mat scene_pt_rb;
	Mat scene_pt_lt;
	Mat scene_pt_rt;
	pt_lb.at<double>(0, 0) = (double)x;
	pt_lb.at<double>(1, 0) = (double)y + CONFIG_BIRD_CHUNK_SIZE_H - 1;
	pt_lb.at<double>(2, 0) = 1;
	pt_rb.at<double>(0, 0) = (double)x + CONFIG_BIRD_CHUNK_SIZE_W - 1;
	pt_rb.at<double>(1, 0) = (double)y + CONFIG_BIRD_CHUNK_SIZE_H - 1;
	pt_rb.at<double>(2, 0) = 1;
	pt_lt.at<double>(0, 0) = (double)x;
	pt_lt.at<double>(1, 0) = (double)y;
	pt_lt.at<double>(2, 0) = 1;
	pt_rt.at<double>(0, 0) = (double)x + CONFIG_BIRD_CHUNK_SIZE_W - 1;
	pt_rt.at<double>(1, 0) = (double)y;
	pt_rt.at<double>(2, 0) = 1;

	gemm(m_H,pt_lb,1,NULL,0,scene_pt_lb);
	gemm(m_H,pt_rb,1,NULL,0,scene_pt_rb);
	gemm(m_H,pt_lt,1,NULL,0,scene_pt_lt);
	gemm(m_H,pt_rt,1,NULL,0,scene_pt_rt);

	if (scene_pt_lb.at<double>(2, 0) != 0)
	{
	  scene_pt_lb.at<double>(0, 0) /= scene_pt_lb.at<double>(2, 0);
	  scene_pt_lb.at<double>(1, 0) /= scene_pt_lb.at<double>(2, 0);
	}

	if (scene_pt_rb.at<double>(2, 0) != 0)
	{
	  scene_pt_rb.at<double>(0, 0) /= scene_pt_rb.at<double>(2, 0);
	  scene_pt_rb.at<double>(1, 0) /= scene_pt_rb.at<double>(2, 0);
	}

	if (scene_pt_lt.at<double>(2, 0) != 0)
	{
	  scene_pt_lt.at<double>(0, 0) /= scene_pt_lt.at<double>(2, 0);
	  scene_pt_lt.at<double>(1, 0) /= scene_pt_lt.at<double>(2, 0);
	}

	if (scene_pt_rt.at<double>(2, 0) != 0)
	{
	  scene_pt_rt.at<double>(0, 0) /= scene_pt_rt.at<double>(2, 0);
	  scene_pt_rt.at<double>(1, 0) /= scene_pt_rt.at<double>(2, 0);
	}

	base_x_f = 9999999.0;
	base_y_f = 9999999.0;

	if (scene_pt_lb.at<double>(0, 0) < base_x_f) 
	  base_x_f = scene_pt_lb.at<double>(0, 0);
	if (scene_pt_rb.at<double>(0, 0) < base_x_f) 
	  base_x_f = scene_pt_rb.at<double>(0, 0);
	if (scene_pt_lt.at<double>(0, 0) < base_x_f) 
	  base_x_f = scene_pt_lt.at<double>(0, 0);
	if (scene_pt_rt.at<double>(0, 0) < base_x_f) 
	  base_x_f = scene_pt_rt.at<double>(0, 0);

	if (scene_pt_lb.at<double>(1, 0) < base_y_f) 
	  base_y_f = scene_pt_lb.at<double>(1, 0);
	if (scene_pt_rb.at<double>(1, 0) < base_y_f) 
	  base_y_f = scene_pt_rb.at<double>(1, 0);
	if (scene_pt_lt.at<double>(1, 0) < base_y_f) 
	  base_y_f = scene_pt_lt.at<double>(1, 0);
	if (scene_pt_rt.at<double>(1, 0) < base_y_f) 
	  base_y_f = scene_pt_rt.at<double>(1, 0);

	base_x = (int)base_x_f;
	base_y = (int)base_y_f;

	index = base_y * CONFIG_SCENE_SIZE_W + base_x;
	if (new_little_y)
	{
	  m_block[block_index++] = index;
	}

	for (int little_x = 0; little_x <  CONFIG_BIRD_CHUNK_SIZE_W; 
	     ++little_x)
	{
	  Mat pt_local_up(Size(1, 3), CV_64FC1);
	  Mat pt_local_center(Size(1, 3), CV_64FC1);
	  Mat scene_pt_local_up;
	  Mat scene_pt_local_center;

	  pt_local_up.at<double>(0, 0) = (double)x + (double)little_x;
	  pt_local_up.at<double>(1, 0) = (double)y + (double)little_y;
	  pt_local_up.at<double>(2, 0) = 1;

	  gemm(m_H,pt_local_up,1,NULL,0,scene_pt_local_up);


	  if (scene_pt_local_up.at<double>(2, 0) != 0)
	  {
	    scene_pt_local_up.at<double>(0, 0) /= 
					    scene_pt_local_up.at<double>(2, 0);
	    scene_pt_local_up.at<double>(1, 0) /= 
					    scene_pt_local_up.at<double>(2, 0);
	  }

	  double local_x_f = scene_pt_local_up.at<double>(0, 0);
	  double local_y_f = scene_pt_local_up.at<double>(1, 0);
	  int local_x = (int)local_x_f;
	  int local_y = (int)local_y_f;

	  double delta_x = local_x_f - local_x;
	  double delta_y = local_y_f - local_y;

	  unsigned int local_index = 
			(int)(local_y - base_y) * 36 + (int)(local_x - base_x);

	  unsigned char dx = (unsigned char)(delta_x * 256.0);
	  unsigned char dy = (unsigned char)(delta_y * 256.0);
	  m_delta[delta_index++] = dx;
	  m_delta[delta_index++] = dy;

	  unsigned short out = local_index & 0x0000FFFF;
	  if (out > 520) out = 520;
	  m_local[loc_index++] = out;
	}
      }
      new_little_y = false;
}
	}
}
