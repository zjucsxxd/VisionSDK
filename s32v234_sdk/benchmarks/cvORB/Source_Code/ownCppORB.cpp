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

/// Simple CPP implementation for ORB 
#include <iostream>
using namespace std;



#include "filtering.hpp"
#include "ownCppORB.h"


#include "fast9.h"
#include "nms.h"
#include "descriptor.h"
#include "homography.h"

const int reservedPoints = MAX_FEATURE_POINTS;
const string winName = "./../Output/Correspondences";


short smoothingKernel[KERNEL_HEIGHT][KERNEL_WIDTH] = {
	1, 2, 1,
	2, 4, 2,
	1, 2, 1
};

COwnOrb::COwnOrb() 
: tempDataF(NULL)
, tempDataG(NULL)
{
	
}

void COwnOrb::create(int lSrcWidth, int lSrcHeight){
	tempDataF = new unsigned char[lSrcWidth * lSrcHeight];
	tempDataG = new unsigned char[lSrcWidth * lSrcHeight];

	filteredKeyPoints.reserve(reservedPoints);
	referenceKeyPoints.reserve(reservedPoints);
	features.reserve(reservedPoints);
	features.reserve(reservedPoints);
	matches.reserve(reservedPoints);
};

COwnOrb::~COwnOrb(){
	if (tempDataF != NULL) {
		delete[] tempDataF;
	}

	if (tempDataG != NULL) {
		delete[] tempDataG;
	}
};

void COwnOrb::doComputation(Mat& img1, Mat& img2, char* idxStr, std::string ext){
	static int frameCount = 0;
	Mat tmp = img2.clone();
	tmp.convertTo(outM, CV_8UC3);

	int refWidth = img1.cols;
	int refHeight = img1.rows;


	int lRetVal = 0;

	Mat img1LP = applyFilter<unsigned char>(img1, smoothingKernel, KERNEL_WIDTH, KERNEL_HEIGHT);
	Mat img2LP = applyFilter<unsigned char>(img2, smoothingKernel, KERNEL_WIDTH, KERNEL_HEIGHT);

	Mat lOutputFeatures(img1LP.rows, img1LP.cols, img1LP.type());
	lOutputFeatures = 0;
	Mat lOutputFeatures2(img2LP.rows, img2LP.cols, img2LP.type());
	lOutputFeatures2 = 0;

	referenceKeyPoints.clear();
	referenceFeatures.clear();

	lRetVal |= FindFeatures(img1LP,
		lOutputFeatures,
		referenceKeyPoints,
		referenceFeatures,
		tempDataF,
		tempDataG);


	const int minDistLimit = MATCH_DIST_LIMIT;
	//int frameBufferIndexWrite;

	filteredKeyPoints.clear();
	features.clear();
	matches.clear();


	for (unsigned int i = 0; i < referenceFeatures.size(); ++i)
	{
		referenceFeatures[i].ResetMatch();
	}

	lRetVal |= FindFeatures(img2LP,
		lOutputFeatures,
		filteredKeyPoints,
		features,
		tempDataF,
		tempDataG);

	lRetVal |= FindMatches(
		referenceFeatures,
		features,
		matches,
		minDistLimit,
		RANGE_CHECK
		);

	drawMatches(img1, referenceKeyPoints, outM, filteredKeyPoints, matches, outMatches);
	imwrite(winName + std::string(idxStr) + ext, outMatches);


#ifdef _DEBUG
	imshow("out matches", outMatches);
	waitKey();
#endif

	//writer << outMatches;
	++frameCount;
};
