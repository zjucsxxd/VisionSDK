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

/// Helper function to implement OpenCV ORB matching

#ifndef OCV_MATCHING_H
#define OCV_MATCHING_H

#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace cv;


#define DRAW_RICH_KEYPOINTS_MODE     0
#define DRAW_OUTLIERS_MODE           0

enum { NONE_FILTER = 0, CROSS_CHECK_FILTER = 1 };


void simpleMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
	const Mat& descriptors1, const Mat& descriptors2,
	vector<DMatch>& matches12);

void crossCheckMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
	const Mat& descriptors1, const Mat& descriptors2,
	vector<DMatch>& filteredMatches12, int knn = 1);

void warpPerspectiveRand(const Mat& src, Mat& dst, Mat& H, RNG& rng);

void doIteration(const Mat& img1, Mat& img2, bool isWarpPerspective,
	vector<KeyPoint>& keypoints1, const Mat& descriptors1,
	Ptr<FeatureDetector>& detector, Ptr<DescriptorExtractor>& descriptorExtractor,
	Ptr<DescriptorMatcher>& descriptorMatcher, int matcherFilter, bool eval,
	double ransacReprojThreshold, RNG& rng, Mat& drawImg);

int cvOrbComputation(Mat& img1, Mat& img2, string& ransacThresh, int idx, char* idxStr, std::string& ext);


#endif