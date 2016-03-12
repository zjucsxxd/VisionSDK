
#ifdef __STANDALONE__
#include "../../data/standalone/in_grey_256x256.h"
#include <frame_output_dcu.h>
#endif

#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <cstdlib>
#include <stdio.h>
#include <oal.h>

inline void Gaussian(unsigned char* src, unsigned char* dst, int width, int size);

#ifdef __INTEGRITY__
#define INPUT_ROOT "/apex/"
#else
#define INPUT_ROOT ""
#endif

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
		
	unsigned char *inputImage = (unsigned char*)(in.data);
	Mat out = in.clone();
	unsigned char *outputImage = (unsigned char*)(out.data);
	
	Size s = in.size();
	int rows = s.height;
	int cols = s.width;
	int size = rows * cols;
		
	Gaussian(inputImage, outputImage, cols, size);
	
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
	imwrite(INPUT_ROOT"out_gauss5x5.png", out);
#endif

	return 0;

}

inline void Gaussian(unsigned char* src, unsigned char* dst, int width, int size)
{
	uint64_t simd_iteration = (size - 2 * width) & ~7;
	simd_iteration >>= 5;

	uint64_t *offset = new uint64_t[8];
	offset[0] = (-width - 1);
	offset[1] = -width;
	offset[2] = (-width + 1);
	offset[3] = (-1);
	offset[4] = (0);
	offset[5] = (1);
	offset[6] = (width - 1);
	offset[7] = (width);
	offset[8] = (width + 1);

	asm volatile(

		"1:																		\n\t"
		"mov 				 x7, %x0											\n\t"

		//midle point
		"LD1				 {v4.8B, v5.8B, v6.8B,v7.8B},  [%[src]]				\n\t"
	
		"UXTL				 v4.8H, v4.8B									    \n\t"
		"UXTL				 v5.8H, v5.8B									    \n\t"
		"UXTL				 v6.8H, v6.8B									    \n\t"
		"UXTL				 v7.8H, v7.8B									    \n\t"
		
		"UQSHL				 v4.8H, v4.8H, #2								    \n\t"
		"UQSHL				 v5.8H, v5.8H, #2								    \n\t"
		"UQSHL				 v6.8H, v6.8H, #2								    \n\t"
		"UQSHL				 v7.8H, v7.8H, #2								    \n\t"
			 
		//1.step
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"
		
		"LD1				 {v8.8B, v9.8B, v10.8B,v11.8B},  [x6]				\n\t"

		"UXTL				 v8.8H, v8.8B									    \n\t"
		"UXTL				 v9.8H, v9.8B									    \n\t"
		"UXTL				 v10.8H, v10.8B									    \n\t"
		"UXTL				 v11.8H, v11.8B									    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//2.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"UQSHL				 v8.8H, v8.8H, #1								    \n\t"
		"UQSHL				 v9.8H, v9.8H, #1								    \n\t"
		"UQSHL				 v10.8H, v10.8H, #1								    \n\t"
		"UQSHL				 v11.8H, v11.8H, #1								    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//3.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//4.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"UQSHL				 v8.8H, v8.8H, #1								    \n\t"
		"UQSHL				 v9.8H, v9.8H, #1								    \n\t"
		"UQSHL				 v10.8H, v10.8H, #1								    \n\t"
		"UQSHL				 v11.8H, v11.8H, #1								    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//5.step - middle point

		//6.step
		"add			   	 %x1, %x1, #16										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"UQSHL				 v8.8H, v8.8H, #1								    \n\t"
		"UQSHL				 v9.8H, v9.8H, #1								    \n\t"
		"UQSHL				 v10.8H, v10.8H, #1								    \n\t"
		"UQSHL				 v11.8H, v11.8H, #1								    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//7.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//8.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"UQSHL				 v8.8H, v8.8H, #1								    \n\t"
		"UQSHL				 v9.8H, v9.8H, #1								    \n\t"
		"UQSHL				 v10.8H, v10.8H, #1								    \n\t"
		"UQSHL				 v11.8H, v11.8H, #1								    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		//9.step
		"add			   	 %x1, %x1, #8										\n\t"
		"ldr 				 x10, [%x1]											\n\t"
		"add                 x6, x7, x10									    \n\t"

		"LD1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [x6]					\n\t"

		"UXTL				 v8.8H, v0.8B									    \n\t"
		"UXTL				 v9.8H, v1.8B									    \n\t"
		"UXTL				 v10.8H, v2.8B									    \n\t"
		"UXTL				 v11.8H, v3.8B									    \n\t"

		"ADD                 v4.8H, v4.8H, v8.8H								\n\t"
		"ADD                 v5.8H, v5.8H, v9.8H								\n\t"
		"ADD                 v6.8H, v6.8H, v10.8H								\n\t"
		"ADD                 v7.8H, v7.8H, v11.8H								\n\t"

		"subs				 %x1, %x1, #64										\n\t" /*decrementation of offset*/
		"add				 %x0, %x0, #32										\n\t" /*incrementation of source data*/

		"USHR				 v0.8H, v4.8H, #4								    \n\t" /*division by 16*/
		"USHR				 v1.8H, v5.8H, #4								    \n\t"
		"USHR				 v2.8H, v6.8H, #4								    \n\t"
		"USHR				 v3.8H, v7.8H, #4								    \n\t"
	
		"XTN				 v0.8B, v0.8H									    \n\t" /*narrowing */
		"XTN				 v1.8B, v1.8H									    \n\t"
		"XTN				 v2.8B, v2.8H									    \n\t"
		"XTN				 v3.8B, v3.8H									    \n\t"

		"ST1				 {v0.8B, v1.8B, v2.8B,v3.8B},  [%[dst]], #32		\n\t"

		"subs				 %[simd_it], %[simd_it], #1							\n\t"
		"bne				 1b													\n\t"
					
		:
		: [src]"r"(src + width), [offset]"r"(offset), [dst]"r"(dst + width), [simd_it]"r"(simd_iteration)
		: 

		);
	
		//border handling in C
		//first line
		for (int i = 1; i < width - 1; i++)
		{
			dst[i] = (
				(src[i - 1]) +
				(src[i] << 1) +
				(src[i + 1]) +
				(src[i - 1] << 1) +
				(src[i] << 2) +
				(src[i + 1] << 1) +
				(src[i + width - 1]) +
				(src[i + width] << 1) +
				(src[i + width + 1])
				) >> 4;
		}
		//last line
		for (int i = size - width; i < size - 1; i++)
		{
			dst[i] = (
				(src[i - width - 1]) +
				(src[i - width] << 1) +
				(src[i - width + 1]) +
				(src[i - 1] << 1) +
				(src[i - 1]) +
				(src[i] << 2) +
				(src[i] << 1) +
				(src[i + 1] << 1) +
				src[i + 1]
				) >> 4;
		}

		//upper left corner
		dst[0] = (
			(src[0] << 3) +
			src[0] +
			(src[1] << 1) +
			src[1] +
			(src[width] << 1) +
			src[width] +
			src[width + 1]
			) >> 4;

		//upper right corner
		dst[width - 1] = (
			(src[width - 1] << 3) +
			src[width - 1] +
			(src[width - 2] << 1) +
			src[width - 2] +
			(src[2 * width - 1] << 1) +
			src[2 * width - 1] +
			src[2 * width - 2]
			) >> 4;

		//lower left corner
		dst[size - width] = (
			(src[size - width] << 3) +
			src[size - width] +
			(src[size - 2 * width] << 1) +
			src[size - 2 * width] +
			(src[size - 2 * width + 1] << 1) +
			src[size - 2 * width + 1] +
			src[size - 2 * width + 2])
			>> 4;

		//lower right corner
		dst[size - 1] = ((src[size - 1] << 3) +
			src[size - 1] +
			(src[size - 2] << 1) +
			src[size - 2] +
			(src[size - 2 * width - 1] << 1) +
			src[size - 2 * width - 1] +
			src[size - 2 * width - -2])
			>> 4;
			
		//side borders
		for (volatile int i = width; i <= (size - width); i += width)
		{
			dst[i] = ((src[i - width]) +
				(src[i - width] << 1) +
				(src[i - width + 1]) +
				(src[i] << 1) +
				(src[i] << 2) +
				(src[i + 1] << 1) +
				(src[i + width]) +
				(src[i + width] << 1) +
				(src[i + width + 1]))
				>> 4;

			dst[i - 1] = ((src[i - 1 - width - 1]) +
				(src[i - 1 - width] << 1) +
				(src[i - 1 - width]) +
				(src[i - 1 - 1] << 1) +
				(src[i - 1] << 2) +
				(src[i - 1] << 1) +
				(src[i - 1 + width - 1]) +
				(src[i - 1 + width] << 1) +
				(src[i - 1 + width]))
				>> 4;
		}
}
