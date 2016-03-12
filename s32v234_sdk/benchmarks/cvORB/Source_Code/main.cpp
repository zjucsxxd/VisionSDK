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
#include <iostream>
using namespace std;


// helper function for OpenCV ORB implementation
#include "ocvMatching.h"

// Class for own ORB implementation
#include "ownCppORB.h"

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
		<< argv[0] << " [image1] [image2] [-ocv [ransacThreshold(=3)]]\n"
		<< "If -ocv  is specified then the openCV methods are used. \nOtherwise own CPP implementation is used.\n\n"
		<< "Please press a character to continue with default values: ";
	char a;
	cin >> a;
}

int main(int argc, char** argv)
{
	std::string firstImgName("left01.jpg"), secondImgName("right01.jpg");
	std::string ransacThreshold("3");

	bool computeWithOpenCV = false;
    if( argc <= 2 )
    {
        help(argv);
       // return -1;
	} else {
		firstImgName = std::string(argv[1]);
		secondImgName = std::string(argv[2]);
		if (argc >= 4) {
			if (std::string(argv[3]) == "-ocv") {
				computeWithOpenCV = true;
			}
			if (argc == 5) {
				ransacThreshold = std::string(argv[4]);
			}
		}
	}


	cout << "< Reading the images..." << firstImgName << " and " << secondImgName <<endl;

	int firstExtPos = firstImgName.find_last_of('.'), secExtPos = secondImgName.find_last_of('.');
	std::string ext = firstImgName.substr(firstExtPos, firstImgName.size()-firstExtPos);
	std::string firstImgRoot = firstImgName.substr(0, firstExtPos - 2), secImgRoot = secondImgName.substr(0, secExtPos - 2);

	int idx = std::atoi(firstImgName.substr(firstExtPos-2,2).c_str());

	char idxStr[5];
	sprintf_s(idxStr, "%02d", idx);

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

	COwnOrb ownOrb;
	

	int lSrcWidth = WantedImg_WIDTH, lSrcHeight = WantedImg_HEIGHT;
	//VideoWriter writer("out_homography.mpg", CV_FOURCC('M', 'P', 'E', 'G'), 3.0, Size(lSrcWidth, lSrcHeight));
	
	
	if (computeWithOpenCV) {
		/* for OpenCV*/
		initModule_features2d();
		initModule_nonfree();
	}
	else {
		ownOrb.create(lSrcWidth, lSrcHeight);
	}

	while (!img1.empty() && !img2.empty()) {
		img1 = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);
		img2 = convertToDesiredFormat(img2, WantedImg_WIDTH, WantedImg_HEIGHT, CV_8UC1);

		if (computeWithOpenCV) {
			/* OpenCV implementation*/
			int ok = cvOrbComputation(img1, img2, ransacThreshold, idx, idxStr, ext);
		}
		else {
			ownOrb.doComputation(img1, img2, idxStr, ext);
		}

		sprintf_s(idxStr, "%02d", ++idx);
		std::string firstNextName = firstImgRoot + std::string(idxStr) + ext, secNextName = secImgRoot + idxStr + ext;
		
		cout << "< Reading the images..." << firstNextName << " and " << secNextName << endl;
		
		img1 = imread(firstNextName);
		img2 = imread(secNextName);
		
	} // while there are images to read.
	
  
  return 0;
}
