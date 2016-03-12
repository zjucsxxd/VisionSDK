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
#include "least_squares_line.h"

////////////////////////////////////////////////////////////////////////////////
// Method approximates a line through the vector of points (LSQ method)
// @param points Point vector where line is to be approximated
// @return 2D vector with line data [slope, shift]
////////////////////////////////////////////////////////////////////////////////
cv::Vec2f LeastSquaresLine::ApproximateLine(std::vector<cv::Point2i> points)
{
  double sumx = 0.0;
  double sumx2 = 0.0;
  double sumxy = 0.0;
  double sumy = 0.0; 
  double sumy2 = 0.0;
  double m, b;

  for (unsigned int i = 0; i<points.size(); i++)
  {
    sumx += points[i].x;
    sumx2 += points[i].x*points[i].x;
    sumxy += points[i].x*points[i].y;
    sumy += points[i].y;
    sumy2 += points[i].y*points[i].y;
  }

  double denom = (points.size() * sumx2 - sumx*sumx);
  if (denom == 0) 
  {
    // singular matrix. can't solve the problem.
    m = 0;
    b = 0;
    return cv::Vec2f(0, 0);
  }

  m = (points.size() * sumxy - sumx * sumy) / denom;
  b = (sumy * sumx2 - sumx * sumxy) / denom;

  return cv::Vec2f((float)m, (float)b);
}