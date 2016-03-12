#ifdef __STANDALONE__
#include "../../data/standalone/in_grey_256x256.h"
#include <frame_output_dcu.h>
#endif

#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <cstdlib>
#include <stdio.h>
#include <oal.h>

#include "../../../fftw/standalone-arm64/include/fftw3.h"

#ifdef __INTEGRITY__
#define INPUT_ROOT "/apex/"
#else
#define INPUT_ROOT ""
#endif

void fourier_tform(unsigned char *inputImage, unsigned char *outputImage, int width, int height, int stride);

extern "C"
{
	unsigned long get_uptime_microS();
}

int main(int argc, char** argv)
{
	using namespace cv;
	
// Read the input using OpenCV
#ifdef __STANDALONE__
	Mat in(256, 256, CV_8UC1, in_grey_256x256);
#else
	Mat in = imread(INPUT_ROOT"in_grey_256x256.png", 0);
#endif

	using namespace cv;
	using namespace std;

	if (in.empty())
	{
		printf("no image \n");
		return 0;
	}

	unsigned char *inputImage = (unsigned char*)(in.data);	//input image
	Mat out = Mat::zeros(256, 256, CV_8UC1);
	unsigned char *outputImage = (unsigned char*)(out.data);  //output image

	Size s = in.size();
	int rows = s.height;
	int cols = s.width;
	int size = rows * cols;
	int stride = in.step;
	
	fourier_tform(inputImage, outputImage, cols, rows, stride);

#ifdef __STANDALONE__
	cv::Mat output_mat = cv::Mat::zeros(1080, 1920, CV_8UC3);
	io::FrameOutputDCU output(1920, 1080, io::IO_DATA_DEPTH_08, io::IO_DATA_CH3);
	cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(960, 540), 180, 1.0);

	cvtColor(out, out, CV_GRAY2RGB);
	cvtColor(in, in, CV_GRAY2RGB);
	in.copyTo(output_mat(cv::Rect(0, 412, 256, 256)));
	out.copyTo(output_mat(cv::Rect(300, 412, 256, 256)));

	warpAffine(output_mat, output_mat, rot_mat, output_mat.size());
	output.PutFrame(output_mat.data);
#else
	//no image output
#endif
	return 0;
}

void fourier_tform(unsigned char *inputImage, unsigned char *outputImage, int width, int height, int stride)
{
	fftwf_complex *input;
	fftwf_complex *fftw_result;
	fftwf_complex *ifftw_result;

	fftwf_plan plan_forward;
	fftwf_plan plan_backward;

	input = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * width * height);
	fftw_result = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * width * height);
	ifftw_result = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * width * height);

	plan_forward = fftwf_plan_dft_2d(width, height, input, fftw_result, FFTW_FORWARD, FFTW_ESTIMATE);
	plan_backward = fftwf_plan_dft_2d(width, height, fftw_result, ifftw_result, FFTW_BACKWARD, FFTW_ESTIMATE);

	int k = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			input[k][0] = (double)inputImage[i * stride + j];
			input[k][1] = 0.0;
			k++;
		}
	}

	// forward FFT
	fftwf_execute(plan_forward);
	
	// backward FFT
	fftwf_execute(plan_backward);

	// normalize IFFT result
	for (int i = 0; i < (width * height); i++) 
	{
		ifftw_result[i][0] /= (double)(width * height);
	}

	k = 0;

	//copy data into output image 
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			outputImage[i * stride + j] = (uchar)ifftw_result[k][0];
			k++;
		}
	}
	
	//free memory
	fftwf_destroy_plan(plan_forward);
	fftwf_destroy_plan(plan_backward);

	fftwf_free(input);
	fftwf_free(fftw_result);
	fftwf_free(ifftw_result);

	return;
}