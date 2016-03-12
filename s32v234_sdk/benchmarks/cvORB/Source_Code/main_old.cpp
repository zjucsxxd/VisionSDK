/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
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

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include <iostream>

using namespace cv;
using namespace std;

Mat convertToDesiredFormat(const Mat& img1, int imgWidth, int imgHeight, int imgType){
	Mat img2(img1.rows, img1.cols, imgType);
	if (img1.type() != CV_8UC1) {
		Mat tmp, tmpResize;
		cv::cvtColor(img1, tmp, CV_RGB2GRAY);
		cv::resize(tmp, tmpResize, Size(imgWidth, imgHeight));
		tmpResize.convertTo(img2, imgType);
	}
	else {
		Mat tmpResize;
		cv::resize(img1, tmpResize, Size(imgWidth, imgHeight));
		tmpResize.convertTo(img2, imgType);
	}

	return img2;
}

#define WantedImg_WIDTH		1024
#define WantedImg_HEIGHT	1024

static void help(char** argv)
{
    cout << "\nThis program demonstrates keypoint finding and matching between 2 images using FAST and ORB methods\n"
     << argv[0] << " [image1] [image2] [ransacReprojThreshold]\n"
	 << "If ransacReprojThreshold>=0 then homography matrix are calculated\n"
     << "\n"
     << "Matches are filtered using homography matrix (if ransacReprojThreshold>=0, default value is 3)\n"
	<< endl;

	char a;
	cin >> a;
}

#define DRAW_RICH_KEYPOINTS_MODE     0
#define DRAW_OUTLIERS_MODE           0

const string cvWinName = "./../cvOutput/Correspondences";
const string winName = "./../Output/Correspondences";

enum { NONE_FILTER = 0, CROSS_CHECK_FILTER = 1 };

static int getMatcherFilterType( const string& str )
{
    if( str == "NoneFilter" )
        return NONE_FILTER;
    if( str == "CrossCheckFilter" )
        return CROSS_CHECK_FILTER;
    CV_Error(CV_StsBadArg, "Invalid filter name");
    return -1;
}

static void simpleMatching( Ptr<DescriptorMatcher>& descriptorMatcher,
                     const Mat& descriptors1, const Mat& descriptors2,
                     vector<DMatch>& matches12 )
{
    vector<DMatch> matches;
    descriptorMatcher->match( descriptors1, descriptors2, matches12 );
}

static void crossCheckMatching( Ptr<DescriptorMatcher>& descriptorMatcher,
                         const Mat& descriptors1, const Mat& descriptors2,
                         vector<DMatch>& filteredMatches12, int knn=1 )
{
    filteredMatches12.clear();
    vector<vector<DMatch> > matches12, matches21;
    descriptorMatcher->knnMatch( descriptors1, descriptors2, matches12, knn );
    descriptorMatcher->knnMatch( descriptors2, descriptors1, matches21, knn );
    for( size_t m = 0; m < matches12.size(); m++ )
    {
        bool findCrossCheck = false;
        for( size_t fk = 0; fk < matches12[m].size(); fk++ )
        {
            DMatch forward = matches12[m][fk];

            for( size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++ )
            {
                DMatch backward = matches21[forward.trainIdx][bk];
                if( backward.trainIdx == forward.queryIdx )
                {
                    filteredMatches12.push_back(forward);
                    findCrossCheck = true;
                    break;
                }
            }
            if( findCrossCheck ) break;
        }
    }
}

static void warpPerspectiveRand( const Mat& src, Mat& dst, Mat& H, RNG& rng )
{
    H.create(3, 3, CV_32FC1);
    H.at<float>(0,0) = rng.uniform( 0.8f, 1.2f);
    H.at<float>(0,1) = rng.uniform(-0.1f, 0.1f);
    H.at<float>(0,2) = rng.uniform(-0.1f, 0.1f)*src.cols;
    H.at<float>(1,0) = rng.uniform(-0.1f, 0.1f);
    H.at<float>(1,1) = rng.uniform( 0.8f, 1.2f);
    H.at<float>(1,2) = rng.uniform(-0.1f, 0.1f)*src.rows;
    H.at<float>(2,0) = rng.uniform( -1e-4f, 1e-4f);
    H.at<float>(2,1) = rng.uniform( -1e-4f, 1e-4f);
    H.at<float>(2,2) = rng.uniform( 0.8f, 1.2f);

    warpPerspective( src, dst, H, src.size() );
}

static void doIteration( const Mat& img1, Mat& img2, bool isWarpPerspective,
                  vector<KeyPoint>& keypoints1, const Mat& descriptors1,
                  Ptr<FeatureDetector>& detector, Ptr<DescriptorExtractor>& descriptorExtractor,
                  Ptr<DescriptorMatcher>& descriptorMatcher, int matcherFilter, bool eval,
                  double ransacReprojThreshold, RNG& rng, Mat& drawImg )
{
    assert( !img1.empty() );
    Mat H12;
    if( isWarpPerspective )
        warpPerspectiveRand(img1, img2, H12, rng );
    else
        assert( !img2.empty()/* && img2.cols==img1.cols && img2.rows==img1.rows*/ );

    cout << endl << "< Extracting keypoints from second image..." << endl;
    vector<KeyPoint> keypoints2;
    detector->detect( img2, keypoints2 );
    cout << keypoints2.size() << " points" << endl << ">" << endl;

    if( !H12.empty() && eval )
    {
        cout << "< Evaluate feature detector..." << endl;
        float repeatability;
        int correspCount;
        evaluateFeatureDetector( img1, img2, H12, &keypoints1, &keypoints2, repeatability, correspCount );
        cout << "repeatability = " << repeatability << endl;
        cout << "correspCount = " << correspCount << endl;
        cout << ">" << endl;
    }

    cout << "< Computing descriptors for keypoints from second image..." << endl;
    Mat descriptors2;
    descriptorExtractor->compute( img2, keypoints2, descriptors2 );
    cout << ">" << endl;

    cout << "< Matching descriptors..." << endl;
    vector<DMatch> filteredMatches;
    switch( matcherFilter )
    {
    case CROSS_CHECK_FILTER :
        crossCheckMatching( descriptorMatcher, descriptors1, descriptors2, filteredMatches, 1 );
        break;
    default :
        simpleMatching( descriptorMatcher, descriptors1, descriptors2, filteredMatches );
    }
    cout << ">" << endl;

    if( !H12.empty() && eval )
    {
        cout << "< Evaluate descriptor matcher..." << endl;
        vector<Point2f> curve;
        Ptr<GenericDescriptorMatcher> gdm = new VectorDescriptorMatcher( descriptorExtractor, descriptorMatcher );
        evaluateGenericDescriptorMatcher( img1, img2, H12, keypoints1, keypoints2, 0, 0, curve, gdm );

        Point2f firstPoint = *curve.begin();
        Point2f lastPoint = *curve.rbegin();
        int prevPointIndex = -1;
        cout << "1-precision = " << firstPoint.x << "; recall = " << firstPoint.y << endl;
        for( float l_p = 0; l_p <= 1 + FLT_EPSILON; l_p+=0.05f )
        {
            int nearest = getNearestPoint( curve, l_p );
            if( nearest >= 0 )
            {
                Point2f curPoint = curve[nearest];
                if( curPoint.x > firstPoint.x && curPoint.x < lastPoint.x && nearest != prevPointIndex )
                {
                    cout << "1-precision = " << curPoint.x << "; recall = " << curPoint.y << endl;
                    prevPointIndex = nearest;
                }
            }
        }
        cout << "1-precision = " << lastPoint.x << "; recall = " << lastPoint.y << endl;
        cout << ">" << endl;
    }

    vector<int> queryIdxs( filteredMatches.size() ), trainIdxs( filteredMatches.size() );
    for( size_t i = 0; i < filteredMatches.size(); i++ )
    {
        queryIdxs[i] = filteredMatches[i].queryIdx;
        trainIdxs[i] = filteredMatches[i].trainIdx;
    }

    if( !isWarpPerspective && ransacReprojThreshold >= 0 )
    {
        cout << "< Computing homography (RANSAC)..." << endl;
        vector<Point2f> points1; KeyPoint::convert(keypoints1, points1, queryIdxs);
        vector<Point2f> points2; KeyPoint::convert(keypoints2, points2, trainIdxs);
        H12 = findHomography( Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold );
        cout << ">" << endl;
    }

    //Mat drawImg;
    if( !H12.empty() ) // filter outliers
    {
        vector<char> matchesMask( filteredMatches.size(), 0 );
        vector<Point2f> points1; KeyPoint::convert(keypoints1, points1, queryIdxs);
        vector<Point2f> points2; KeyPoint::convert(keypoints2, points2, trainIdxs);
        Mat points1t; perspectiveTransform(Mat(points1), points1t, H12);

        double maxInlierDist = ransacReprojThreshold < 0 ? 3 : ransacReprojThreshold;
        for( size_t i1 = 0; i1 < points1.size(); i1++ )
        {
            if( norm(points2[i1] - points1t.at<Point2f>((int)i1,0)) <= maxInlierDist ) // inlier
                matchesMask[i1] = 1;
        }
        // draw inliers
        drawMatches( img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, Scalar(0, 255, 0), Scalar(255, 0, 0), matchesMask
#if DRAW_RICH_KEYPOINTS_MODE
                     , DrawMatchesFlags::DRAW_RICH_KEYPOINTS
#endif
                   );

#if DRAW_OUTLIERS_MODE
        // draw outliers
        for( size_t i1 = 0; i1 < matchesMask.size(); i1++ )
            matchesMask[i1] = !matchesMask[i1];
        drawMatches( img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, Scalar(255, 0, 0), Scalar(0, 0, 255), matchesMask,
                     DrawMatchesFlags::DRAW_OVER_OUTIMG | DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
#endif

        cout << "Number of inliers: " << countNonZero(matchesMask) << endl;
    }
    else
        drawMatches( img1, keypoints1, img2, keypoints2, filteredMatches, drawImg );

 }



 static int cvOrbComputation(Mat& img1, Mat& img2, char* ransac, /*std::string& firstImgRoot, std::string& secImgRoot, */int idx, char* idxStr, std::string& ext) 
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
	 bool isWarpPerspective = false;
	 if (!isWarpPerspective)
		 ransacReprojThreshold = atof(ransac/*argv[3]*/);

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




#define KERNEL_WIDTH	3
#define KERNEL_HEIGHT	3

 short smoothingKernel[KERNEL_HEIGHT][KERNEL_WIDTH] = {
	 1, 2, 1,
	 2, 4, 2,
	 1, 2, 1
 };

 template <class Tp>
 static Mat extendSymmetric(const Mat& img1, int fwidth, int fheight){
	 Mat imgExt(img1.rows + 2 * fheight, img1.cols + 2 * fwidth, img1.type(), Scalar(0));

	 Mat r(imgExt, cv::Rect(fwidth, fheight, img1.cols, img1.rows));
	 img1.copyTo(r);

	 for (int j = 0, l = fheight; j < img1.rows; ++j, l++) {
		 for (int i = 1, k = fwidth; i <= fwidth; ++i, --k) {
			 // extend symmetric to the left
			 imgExt.at<Tp>(l, k) = img1.at<Tp>(j, i);

			 // extend symmetric to the right
			 short tmp = img1.at<Tp>(j, img1.cols - i);
			 imgExt.at<Tp>(l, imgExt.cols - k) = img1.at<Tp>(j, img1.cols - i - 1);
		 }
	 }

	 int botLastRow = img1.rows + fheight;
	 for (int j = 0, l = fheight; j < fheight; ++j, --l) {
		 for (int i = 0; i < imgExt.cols; ++i) {
			 // extend symmetric to the top
			 imgExt.at<Tp>(j, i) = imgExt.at<Tp>(fheight + l, i);

			 // extend symmetric to the bottom
			 imgExt.at<Tp>(botLastRow + j, i) = imgExt.at<Tp>(botLastRow - j - 2, i);
		 }
	 }

	 return imgExt;
 }

 template <class Tp>
 static Mat applyFilter(const Mat& img1, short filt[KERNEL_HEIGHT][KERNEL_WIDTH], int fw, int fh)
 {
	 assert(!img1.empty());

	 cv::Mat imgExt = extendSymmetric<Tp>(img1, fw / 2, fh / 2);
	 cout << endl << "< applying filter..." << endl;

	 cv::Mat filteredImg(img1.rows, img1.cols, img1.type());
	 filteredImg = 0;

	 float filtNorm = 0;
	 for (int k = 0; k < fh; ++k) {
		 for (int l = 0; l < fw; ++l) {
			 filtNorm += abs(filt[k][l]);
		 }
	 }

	 for (int j = 0; j < img1.rows; ++j) {
		 for (int i = 0; i < img1.cols; ++i) {
			 float temp = 0;
			 for (int k = 0; k < fh; ++k) {
				 for (int l = 0; l < fw; ++l) {
					 temp += imgExt.at<Tp>(j + k, i + l) * ((float)filt[k][l]);
				 }
			 }

			 filteredImg.at<Tp>(j, i) = (Tp) rint(temp / filtNorm);
		 }
	 }

	 return filteredImg;
 }

#include "fast9.h"
//#include "match_descriptors.h"
#include "nms.h"
#include "descriptor.h"
#include "homography.h"

 void showImgWithFeatures(Mat& refM, Mat& img1LP, vector<KeyPoint> keyPoints){
	 Mat tmp = img1LP.clone();
	 refM.create(tmp.rows, tmp.cols, CV_8UC3);
	 tmp.convertTo(refM, CV_8UC3);

	 for (int i = 0; i < keyPoints.size();++i){
		 circle(refM, Point(keyPoints[i].pt), 3, Scalar(0, 255, 0), 2);
	 }
 }


int main(int argc, char** argv)
{
    if( argc != 4 )
    {
        help(argv);
       // return -1;
    }	

	cout << "< Reading the images..." << argv[1] << " and " << argv[2] <<endl;

	std::string firstImgName(argv[1]), secondImgName(argv[2]);
	int firstExtPos = firstImgName.find_last_of('.'), secExtPos = secondImgName.find_last_of('.');
	std::string ext = firstImgName.substr(firstExtPos, firstImgName.size()-firstExtPos);
	std::string firstImgRoot = firstImgName.substr(0, firstExtPos - 2), secImgRoot = secondImgName.substr(0, secExtPos - 2);

	int idx = std::atoi(firstImgName.substr(firstExtPos-2,2).c_str());

	char idxStr[5];
	sprintf(idxStr, "%02d", idx);

	//img1 = imread("../Input/left01.jpg", 0);
	Mat img1 = imread(firstImgName), img2;

	//img2 = imread("../Input/right01.jpg", 0);
	img2 = imread(secondImgName);

	cout << ">" << endl;
	if (img1.empty() || img2.empty())
	{
		cout << "Can not read images" << endl;
		return -1;
	}


	int lSrcWidth = WantedImg_WIDTH, lSrcHeight = WantedImg_HEIGHT;
	//VideoWriter writer("out_homography.mpg", CV_FOURCC('M', 'P', 'E', 'G'), 3.0, Size(lSrcWidth, lSrcHeight));
		
	unsigned char* tempDataF = new unsigned char[lSrcWidth * lSrcHeight];
	unsigned char* tempDataG = new unsigned char[lSrcWidth * lSrcHeight];
	const int reservedPoints = MAX_FEATURE_POINTS;

	vector<KeyPoint> filteredKeyPoints;
	filteredKeyPoints.reserve(reservedPoints);

	vector<KeyPoint> referenceKeyPoints;
	referenceKeyPoints.reserve(reservedPoints);


	vector<Feature> features;
	features.reserve(reservedPoints);

	vector<Feature> referenceFeatures;

	vector<DMatch> matches;
	matches.reserve(reservedPoints);


	Mat outMatches;
	Mat outM;
	int frameCount = 1;

	/* for OpenCV
	initModule_features2d();
	initModule_nonfree();
	*/

	while (!img1.empty() && !img2.empty()) {
		/* for OpenCV
		img1 = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);
		img2 = convertToDesiredFormat(img2, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);

		
		int ok = cvOrbComputation(img1, img2, argv[3], idx, idxStr, ext);
		*/

				
		img1 = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);
		outM = convertToDesiredFormat(img2, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC3);
		img2 = convertToDesiredFormat(img2, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);

		
		Mat paddedReference = img1;
		Mat gray = img2;

		int refWidth = paddedReference.cols;
		int refHeight = paddedReference.rows;

		
		int lRetVal = 0;

		Mat img1LP = applyFilter<unsigned char>(img1, smoothingKernel, KERNEL_WIDTH, KERNEL_HEIGHT);
		Mat img2LP = applyFilter<unsigned char>(img2, smoothingKernel, KERNEL_WIDTH, KERNEL_HEIGHT);

		Mat lOutputFeatures(img1LP.rows, img1LP.cols, img1LP.type());
		lOutputFeatures = 0;
		Mat lOutputFeatures2(img2LP.rows, img2LP.cols, img2LP.type());
		lOutputFeatures2 = 0;
		referenceFeatures.clear();
		referenceKeyPoints.clear();

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

#ifdef _DEBUG
		Mat refM, featM;
		showImgWithFeatures(refM, img1LP, referenceKeyPoints);
		showImgWithFeatures(featM, img2LP, filteredKeyPoints);
		imshow("Ref KeyPoints", refM);
		imshow("Feature KeyPoints", featM);
		waitKey();
#endif

		lRetVal |= FindMatches(
				referenceFeatures,
				features,
				matches,
				minDistLimit,
				RANGE_CHECK
				);

		drawMatches(img1, referenceKeyPoints, outM, filteredKeyPoints, matches, outMatches);
		imwrite( winName + std::string(idxStr) + ext, outMatches);

#ifdef _DEBUG
		imshow("out matches", outMatches);
		waitKey();
#endif

		//writer << outMatches;

		sprintf(idxStr, "%02d", ++idx);
		std::string firstNextName = firstImgRoot + std::string(idxStr) + ext, secNextName = secImgRoot + idxStr + ext;


		cout << "< Reading the images..." << firstNextName << " and " << secNextName << endl;


		img1 = imread(firstNextName);
		img2 = imread(secNextName);


		++frameCount;
	

	} // while there are images to read.
	
	
  delete[] tempDataF;
  delete[] tempDataG;
  
  return 0;
}
