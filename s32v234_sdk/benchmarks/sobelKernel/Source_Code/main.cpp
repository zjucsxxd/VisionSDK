#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

static void help(char** argv)
{
	cout << "\nThis program demonstrates sobel filtering\nUsage:\n"
		<< argv[0] << " [image1] \n"
		<< endl;

	char a;
	cin >> a;
}

#define KERNEL_WIDTH	3
#define KERNEL_HEIGHT	3

short sobelX[KERNEL_HEIGHT][KERNEL_WIDTH] = {
	1, 0, -1,
	2, 0, -2,
	1, 0, -1
};



short sobelY[KERNEL_HEIGHT][KERNEL_WIDTH] = {
	1, 2, 1,
	0, 0, 0,
	-1, -2, -1
};


static
bool writeBinary(std::string& filepath, const Mat& image) {
	// Save the image data in binary format
	std::ofstream os(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!os.is_open())
		return false;

	os << (int)image.rows << " " << (int)image.cols << " " << (int)image.type() << " ";
	os.write((char*)image.data, image.step.p[0] * image.rows);
	os.close();
	return true;
}

static
bool readBinary(std::string& filepath, Mat& image) {
	// Load the image data from binary format
	std::ifstream is(filepath, std::ios::in | std::ios::binary);
	if (!is.is_open())
		return false;
	int rows, cols, type;
	is >> rows; is.ignore(1);
	is >> cols; is.ignore(1);
	is >> type; is.ignore(1);

	image.create(rows, cols, type);
	is.read((char*)image.data, image.step.p[0] * image.rows);
	is.close();
	return true;
}

static
void writeToXML(std::string& fileName, const Mat& img) {
	//Writing
	cv::FileStorage fs;
	fs.open(fileName, cv::FileStorage::WRITE);
	fs << "TheImg" << img;

	fs.release(); //Very Important
}

static
void readFromXML(std::string& fileName, Mat& img){
	cv::FileStorage fs;
	//Reading
	fs.open(fileName, cv::FileStorage::READ);
	fs["TheImg"] >> img;
}

static Mat extendSymmetric(const Mat& img1, int fwidth, int fheight){
	Mat imgExt(img1.rows + 2 * fheight, img1.cols + 2 * fwidth, CV_16S, Scalar(0));

	Mat r(imgExt, cv::Rect(fwidth, fheight, img1.cols, img1.rows));
	img1.copyTo(r);

	for (int j = 0, l = fheight; j < img1.rows; ++j, l++) {
		for (int i = 1, k = fwidth; i <= fwidth; ++i, --k) {
			// extend symmetric to the left
			imgExt.at<short>(l, k) = img1.at<short>(j, i);

			// extend symmetric to the right
			short tmp = img1.at<short>(j, img1.cols - i);
			imgExt.at<short>(l, imgExt.cols - k) = img1.at<short>(j, img1.cols - i - 1);
		}
	}

	int botLastRow = img1.rows + fheight;
	for (int j = 0, l = fheight; j < fheight; ++j, --l) {
		for (int i = 0; i < imgExt.cols; ++i) {
			// extend symmetric to the right
			short tmp = imgExt.at<short>(fheight + l, i);

			// extend symmetric to the top
			imgExt.at<short>(j, i) = imgExt.at<short>(fheight + l, i);

			// extend symmetric to the bottom
			short tmp2 = imgExt.at<short>(botLastRow - j - 2, i);
			imgExt.at<short>(botLastRow + j, i) = imgExt.at<short>(botLastRow - j - 2, i);
		}
	}

	return imgExt;
}


static Mat applyFilter(const Mat& img1, int nrRows, int nrCols, short filt[KERNEL_HEIGHT][KERNEL_WIDTH], int fw, int fh, float filtNorm)
{
	assert(!img1.empty());

	cout << endl << "< applying filter..." << endl;

	cv::Mat filteredImg(nrRows, nrCols, CV_16S);
	filteredImg = 0;


	for (int j = 0; j < nrRows; ++j) {
		for (int i = 0; i < nrCols; ++i) {
			float temp = 0;
			for (int k = 0; k < fh; ++k) {
				for (int l = 0; l < fw; ++l) {
					temp += img1.at<short>(j + k, i + l) * ((float)filt[k][l]);
				}
			}

			filteredImg.at<short>(j, i) = (short)rint(temp / filtNorm);
		}
	}

	return filteredImg;
}


static 
Mat imgArcTan(const Mat& imX, const Mat& imY)
{
	assert(!imX.empty() && !imY.empty() && imX.cols == imY.cols && imX.rows == imY.rows);

	cout << endl << "< performing arc tan of image..." << endl;

	cv::Mat filteredImg(imX.rows, imX.cols, CV_32FC1);
	filteredImg = 0.0f;


	for (int j = 0; j < imX.rows; ++j) {
		for (int i = 0; i < imX.cols; ++i) {
			float aTanVal = 0;
			unsigned short crtX = imX.at<short>(j, i);
			unsigned short crtY = imY.at<short>(j, i);
			aTanVal = atan2f((float) crtY, (float) crtX);
			filteredImg.at<float>(j, i) = aTanVal;
		}
	}

	return filteredImg;
}

float computeFiltNorm(short filt[KERNEL_HEIGHT][KERNEL_WIDTH], int fw, int fh) {
	float filtNorm = 0;
	for (int k = 0; k < fh; ++k) {
		for (int l = 0; l < fw; ++l) {
			filtNorm += (filt[k][l]);
		}
	}

	if (filtNorm < 0.0000000001f) {
		filtNorm = 1.0f;
	}
	return filtNorm;
}


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


void 	convertToUCharAndSave(const Mat& inputImg, std::string& outputName) {
	double minV = 0, maxV = 0;
	minMaxLoc(inputImg, &minV, &maxV);

	Mat rescaled(inputImg.rows, inputImg.cols, inputImg.type()), ucharCvt;

	// Convert range back to 0..255, to be able to show the image
	convertScaleAbs(inputImg, rescaled, 255.0 / (maxV - minV), -minV * 255 / (maxV - minV));

	// Convert to unsigned char for display purpose
	rescaled.convertTo(ucharCvt, CV_8UC1);

	imshow(outputName, ucharCvt);
	waitKey();

	bool ok2 = imwrite(outputName, ucharCvt);
	if (!ok2) {
		cout << "WARNING: could not write out filtered result into: " << outputName;
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		help(argv);
		// return -1;
	}

	cout << "< Reading the image... " << argv[1] << endl;

	std::string firstImgName(argv[1]);

	Mat img1 = imread(firstImgName);
	if (img1.empty()) {
		cout << "ERROR: image not found" << endl;
	}

	Mat img2 = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, CV_16SC1);
	cv::Mat imgExt = extendSymmetric(img2, KERNEL_WIDTH/2, KERNEL_HEIGHT/ 2);

	float sobelXNorm = computeFiltNorm(sobelX, KERNEL_WIDTH, KERNEL_HEIGHT);

	Mat imgFilteredX = applyFilter(imgExt, img2.rows, img2.cols, sobelX, KERNEL_WIDTH, KERNEL_HEIGHT, sobelXNorm);
	Mat imgFilteredY = applyFilter(imgExt, img2.rows, img2.cols, sobelY, KERNEL_WIDTH, KERNEL_HEIGHT, sobelXNorm);


	Mat sobelMagSqrTmp = imgFilteredX.mul(imgFilteredX) + imgFilteredY.mul(imgFilteredY)
	  , sobelMag(imgFilteredX.rows, imgFilteredX.cols, CV_32FC1, 0);
	Mat sobelMagSqr;
	sobelMagSqrTmp.convertTo(sobelMagSqr, CV_32FC1);
	cv::sqrt(sobelMagSqr, sobelMag);
	
	string outMagName = "./../Output/SobelMagnitude.xml";
	writeToXML(outMagName, sobelMag);
	
	Mat imATan = imgArcTan(imgFilteredX, imgFilteredY);
	string outTanName = "./../Output/SobelArcTan.xml";
	writeToXML(outTanName, imATan);
	

	string outSobelXUCharName = "./../Output/SobelX_UCHAR.jpg";
	convertToUCharAndSave(imgFilteredX, outSobelXUCharName);

	string outSobelYUCharName = "./../Output/SobelY_UCHAR.jpg";
	convertToUCharAndSave(imgFilteredY, outSobelYUCharName);

	string outMagUCharName = "./../Output/SobelMagnitude_UCHAR.jpg";
	convertToUCharAndSave(sobelMag,outMagUCharName);
	
	string outTanUCharName = "./../Output/SobelArcTan_UCHAR.jpg";
	convertToUCharAndSave(imATan, outTanUCharName);

	return 0;
}
