#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

static void help(char** argv)
{
    cout << "\nThis program demonstrates general filtering\n\nUsage:\n"
     << argv[0] << " [image1] \n"
	<< endl;
	cout << "Type in a character to continue with the default input img: ";
	char a;
	cin >> a;
}

#define KERNEL_WIDTH	9
#define KERNEL_HEIGHT	9


float smoothingKernel[KERNEL_HEIGHT][KERNEL_WIDTH] = {
	0.0005f,  0.0165f,   0.2015f,    0.9040f,	 1.4900f,     0.9099f,   0.2055f,  0.1165f, 0.0015f,
	0.0165f,  0.5483f,   6.6795f,   29.9370f,   49.3575f,    29.9870f,   6.6995f,  0.6483f, 0.0275f,
	0.2015f,  6.6795f,  81.3774f,  364.7082f,  601.3020f,   364.8082f,  81.4774f,  6.6895f, 0.2025f,
	0.9040f, 29.9370f, 364.7082f, 1634.5080f, 2694.8490f,  1635.5080f, 365.7082f, 30.9390f, 0.9140f,	
	1.4900f, 49.3575f, 601.3020f, 2694.8490f, 4443.0552f,  2696.8490f, 611.3020f, 49.3575f, 1.4900f,	
	0.9010f, 29.0370f, 363.7082f, 1632.5080f, 2690.8490f,  1633.5080f, 363.7082f, 28.9370f, 0.9140f,
	0.2005f,  6.4795f,  81.0774f,  364.3082f,  601.0020f,   364.6082f,  81.0774f,  6.0795f, 0.2115f,
	0.0105f,  0.5283f,   6.6395f,   29.9070f,   49.3175f,    29.9320f,   6.6395f,  0.5083f, 0.0175f,
	0.0001f,  0.0145f,   0.2000f,    0.9000f,    1.4850f,     0.9010f,   0.2010f,  0.0105f, 0.0025f,
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
static Mat applyFilter(const Mat& img1, float filt[KERNEL_HEIGHT][KERNEL_WIDTH], int fw, int fh)
{
    assert( !img1.empty() );

	cv::Mat imgExt = extendSymmetric<Tp>(img1, fw/2, fh/2);
    cout << endl << "< applying filter..." << endl;
	
	cv::Mat filteredImg(img1.rows, img1.cols, img1.type());
	filteredImg = 0;

	float filtNorm = 0;
	for (int k = 0; k < fh; ++k) {
		for (int l = 0; l < fw; ++l) {
			filtNorm += filt[k][l];
		}
	}

	if (filtNorm < 0.00000001f) {
		filtNorm = 1.0f;
	}

	for (int j = 0; j < img1.rows; ++j) {
		for (int i = 0; i < img1.cols; ++i) {
			float temp = 0;
			for (int k = 0; k < fh; ++k) {
				for (int l = 0; l < fw; ++l) {
					temp += imgExt.at<Tp>(j + k, i + l) * ((float)filt[k][l]);
				}
			}

			filteredImg.at<Tp>(j, i) = (Tp) (temp / filtNorm);
		}
	}

	return filteredImg;
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

int main(int argc, char** argv)
{
	std::string inImgName("./../Input/InputImg.tiff");
    if( argc != 2 )
    {
        help(argv);
       // return -1;
	}
	else {
		inImgName = std::string(argv[1]);
	}
	

	cout << "< Reading the image... " << inImgName <<endl;

	Mat img1 = imread(inImgName);
	if (img1.empty()) {
		cout << "ERROR: image not found" << endl;
		return -1;
	}


	cout << " image has " << img1.channels() << " channels and type ";
	switch (img1.type()) {
	case CV_8UC3:
		cout << "CV_8UC3\n";
		break;
	case CV_16UC3:
		cout << "CV_16UC3\n";
		break;
	default:
		cout << "not covered type\n";

	}

	int desFormat = CV_16UC1;
	Mat imgIn = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, desFormat);
	imgIn *= 100;

	double mV1 = 0.0, MV1 = 0.0;
	minMaxLoc(img1, &mV1, &MV1);

	double mV = 0.0, MV = 0.0;
	minMaxLoc(imgIn, &mV, &MV);

	imwrite("InputImg.tiff", imgIn);


	int desiredFormat = CV_32FC1;
	Mat img2 = convertToDesiredFormat(img1, WantedImg_WIDTH, WantedImg_HEIGHT, desiredFormat);
	
	Mat imgFiltered = applyFilter<float>(img2, smoothingKernel, KERNEL_WIDTH, KERNEL_HEIGHT);

	string filtImgName("./../Output/FilteredResult");
	writeToXML(filtImgName+std::string(".xml"), imgFiltered);
	writeBinary(filtImgName + std::string(".raw"), imgFiltered);

	Mat rescaled(imgFiltered.rows, imgFiltered.cols, desiredFormat), ucharCvt;

	double minV = 0.0, maxV = 0.0;
	minMaxLoc(imgFiltered, &minV, &maxV);
	// Convert range back to 0..255, to be able to show the image
	convertScaleAbs(imgFiltered, rescaled, 255.0 / (maxV-minV), -minV*255 /(maxV-minV) );

	// Convert to unsigned char for display purpose
	rescaled.convertTo(ucharCvt, CV_8UC1);
	
	imshow("Filtered Result", ucharCvt);
	waitKey();

	string filtUCharImgName("./../Output/FilteredUCHARResult.jpg");
	bool ok2 = imwrite(filtUCharImgName, ucharCvt);
	if (!ok2) {
		cout << "WARNING: could not write out filtered result into: " << filtUCharImgName;
	}

    return 0;
}
