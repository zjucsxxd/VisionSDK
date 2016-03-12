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
#include <iostream>
using namespace std;


#include "ocvMatching.h"

const string cvWinName = "./../cvOutput/Correspondences";


void simpleMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
	const Mat& descriptors1, const Mat& descriptors2,
	vector<DMatch>& matches12)
{
	vector<DMatch> matches;
	descriptorMatcher->match(descriptors1, descriptors2, matches12);
}

void crossCheckMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
	const Mat& descriptors1, const Mat& descriptors2,
	vector<DMatch>& filteredMatches12, int knn)
{
	filteredMatches12.clear();
	vector<vector<DMatch> > matches12, matches21;
	descriptorMatcher->knnMatch(descriptors1, descriptors2, matches12, knn);
	descriptorMatcher->knnMatch(descriptors2, descriptors1, matches21, knn);
	for (size_t m = 0; m < matches12.size(); m++)
	{
		bool findCrossCheck = false;
		for (size_t fk = 0; fk < matches12[m].size(); fk++)
		{
			DMatch forward = matches12[m][fk];

			for (size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++)
			{
				DMatch backward = matches21[forward.trainIdx][bk];
				if (backward.trainIdx == forward.queryIdx)
				{
					filteredMatches12.push_back(forward);
					findCrossCheck = true;
					break;
				}
			}
			if (findCrossCheck) break;
		}
	}
}

void warpPerspectiveRand(const Mat& src, Mat& dst, Mat& H, RNG& rng)
{
	H.create(3, 3, CV_32FC1);
	H.at<float>(0, 0) = rng.uniform(0.8f, 1.2f);
	H.at<float>(0, 1) = rng.uniform(-0.1f, 0.1f);
	H.at<float>(0, 2) = rng.uniform(-0.1f, 0.1f)*src.cols;
	H.at<float>(1, 0) = rng.uniform(-0.1f, 0.1f);
	H.at<float>(1, 1) = rng.uniform(0.8f, 1.2f);
	H.at<float>(1, 2) = rng.uniform(-0.1f, 0.1f)*src.rows;
	H.at<float>(2, 0) = rng.uniform(-1e-4f, 1e-4f);
	H.at<float>(2, 1) = rng.uniform(-1e-4f, 1e-4f);
	H.at<float>(2, 2) = rng.uniform(0.8f, 1.2f);

	warpPerspective(src, dst, H, src.size());
}

void doIteration(const Mat& img1, Mat& img2, bool isWarpPerspective,
	vector<KeyPoint>& keypoints1, const Mat& descriptors1,
	Ptr<FeatureDetector>& detector, Ptr<DescriptorExtractor>& descriptorExtractor,
	Ptr<DescriptorMatcher>& descriptorMatcher, int matcherFilter, bool eval,
	double ransacReprojThreshold, RNG& rng, Mat& drawImg)
{
	assert(!img1.empty());
	Mat H12;
	if (isWarpPerspective)
		warpPerspectiveRand(img1, img2, H12, rng);
	else
		assert(!img2.empty()/* && img2.cols==img1.cols && img2.rows==img1.rows*/);

	cout << endl << "< Extracting keypoints from second image..." << endl;
	vector<KeyPoint> keypoints2;
	detector->detect(img2, keypoints2);
	cout << keypoints2.size() << " points" << endl << ">" << endl;

	if (!H12.empty() && eval)
	{
		cout << "< Evaluate feature detector..." << endl;
		float repeatability;
		int correspCount;
		evaluateFeatureDetector(img1, img2, H12, &keypoints1, &keypoints2, repeatability, correspCount);
		cout << "repeatability = " << repeatability << endl;
		cout << "correspCount = " << correspCount << endl;
		cout << ">" << endl;
	}

	cout << "< Computing descriptors for keypoints from second image..." << endl;
	Mat descriptors2;
	descriptorExtractor->compute(img2, keypoints2, descriptors2);
	cout << ">" << endl;

	cout << "< Matching descriptors..." << endl;
	vector<DMatch> filteredMatches;
	switch (matcherFilter)
	{
	case CROSS_CHECK_FILTER:
		crossCheckMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches, 1);
		break;
	default:
		simpleMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches);
	}
	cout << ">" << endl;

	if (!H12.empty() && eval)
	{
		cout << "< Evaluate descriptor matcher..." << endl;
		vector<Point2f> curve;
		Ptr<GenericDescriptorMatcher> gdm = new VectorDescriptorMatcher(descriptorExtractor, descriptorMatcher);
		evaluateGenericDescriptorMatcher(img1, img2, H12, keypoints1, keypoints2, 0, 0, curve, gdm);

		Point2f firstPoint = *curve.begin();
		Point2f lastPoint = *curve.rbegin();
		int prevPointIndex = -1;
		cout << "1-precision = " << firstPoint.x << "; recall = " << firstPoint.y << endl;
		for (float l_p = 0; l_p <= 1 + FLT_EPSILON; l_p += 0.05f)
		{
			int nearest = getNearestPoint(curve, l_p);
			if (nearest >= 0)
			{
				Point2f curPoint = curve[nearest];
				if (curPoint.x > firstPoint.x && curPoint.x < lastPoint.x && nearest != prevPointIndex)
				{
					cout << "1-precision = " << curPoint.x << "; recall = " << curPoint.y << endl;
					prevPointIndex = nearest;
				}
			}
		}
		cout << "1-precision = " << lastPoint.x << "; recall = " << lastPoint.y << endl;
		cout << ">" << endl;
	}

	vector<int> queryIdxs(filteredMatches.size()), trainIdxs(filteredMatches.size());
	for (size_t i = 0; i < filteredMatches.size(); i++)
	{
		queryIdxs[i] = filteredMatches[i].queryIdx;
		trainIdxs[i] = filteredMatches[i].trainIdx;
	}

	if (!isWarpPerspective && ransacReprojThreshold >= 0)
	{
		cout << "< Computing homography (RANSAC)..." << endl;
		vector<Point2f> points1; KeyPoint::convert(keypoints1, points1, queryIdxs);
		vector<Point2f> points2; KeyPoint::convert(keypoints2, points2, trainIdxs);
		H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
		cout << ">" << endl;
	}

	//Mat drawImg;
	if (!H12.empty()) // filter outliers
	{
		vector<char> matchesMask(filteredMatches.size(), 0);
		vector<Point2f> points1; KeyPoint::convert(keypoints1, points1, queryIdxs);
		vector<Point2f> points2; KeyPoint::convert(keypoints2, points2, trainIdxs);
		Mat points1t; perspectiveTransform(Mat(points1), points1t, H12);

		double maxInlierDist = ransacReprojThreshold < 0 ? 3 : ransacReprojThreshold;
		for (size_t i1 = 0; i1 < points1.size(); i1++)
		{
			if (norm(points2[i1] - points1t.at<Point2f>((int)i1, 0)) <= maxInlierDist) // inlier
				matchesMask[i1] = 1;
		}
		// draw inliers
		drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, Scalar(0, 255, 0), Scalar(255, 0, 0), matchesMask
#if DRAW_RICH_KEYPOINTS_MODE
			, DrawMatchesFlags::DRAW_RICH_KEYPOINTS
#endif
			);

#if DRAW_OUTLIERS_MODE
		// draw outliers
		for (size_t i1 = 0; i1 < matchesMask.size(); i1++)
			matchesMask[i1] = !matchesMask[i1];
		drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, Scalar(255, 0, 0), Scalar(0, 0, 255), matchesMask,
			DrawMatchesFlags::DRAW_OVER_OUTIMG | DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
#endif

		cout << "Number of inliers: " << countNonZero(matchesMask) << endl;
	}
	else
		drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg);

}



int cvOrbComputation(Mat& img1, Mat& img2, string& ransac, int idx, char* idxStr, std::string& ext)
{
	// Initiate detector
	float scaleFactor = 2.0f;//1.2f; // downsample rate
	int nfeatures = 500			// max nr of features to retain
		, nlevels = 8			// number of scale decomposition levels 
		, edgeThreshold = 31	// border size... should match patchSize
		, firstLevel = 0		// should be 0 for this implementation
		, WTA_K = 2				// The number of points that produce each element of the oriented BRIEF descriptor
		, scoreType = ORB::FAST_SCORE
		, patchSize = 31;		// patch size used by ORB

	bool crossCheck = true;

	double ransacReprojThreshold = -1;
	bool isWarpPerspective = ransac.empty();
	if (!isWarpPerspective)
		ransacReprojThreshold = atof(ransac.c_str());

	cout << "< Creating detector, descriptor extractor and descriptor matcher ..." << endl;
	Ptr<FeatureDetector> detector(new ORB(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize));
	Ptr<DescriptorExtractor> descriptorExtractor(new ORB(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize));
	Ptr<DescriptorMatcher> descriptorMatcher(new BFMatcher(NORM_HAMMING, crossCheck));
	int mactherFilterType = NONE_FILTER;

	cout << ">" << endl;
	if (detector.empty() || descriptorExtractor.empty() || descriptorMatcher.empty())
	{
		cout << "Can not create detector or descriptor extractor or descriptor matcher of given types" << endl;
		return -1;
	}


	cout << endl << "< Extracting keypoints from first image..." << endl;
	vector<KeyPoint> keypoints1;
	detector->detect(img1, keypoints1);
	cout << keypoints1.size() << " points" << endl << ">" << endl;

	cout << "< Computing descriptors for keypoints from first image..." << endl;
	Mat descriptors1;
	descriptorExtractor->compute(img1, keypoints1, descriptors1);
	cout << ">" << endl;

	bool eval = false;

	namedWindow(cvWinName, 1);
	Mat drawImg;
	RNG rng = theRNG();
	doIteration(img1, img2, isWarpPerspective, keypoints1, descriptors1,
		detector, descriptorExtractor, descriptorMatcher, mactherFilterType, eval,
		ransacReprojThreshold, rng, drawImg);

	imshow(cvWinName, drawImg);
	waitKey();
	imwrite(cvWinName + std::string(idxStr) + ext, drawImg);
}
