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


#include <apexcv_base_arithmetic.h>
#include <stdint.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#include "apexcv_mat.hpp"

#include "apexcv_arithmetic_func.h"

//arithmetic kernel headers
#include <apexcv_base_arithmetic.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

namespace apexcv{
	
	void add(apexcv::Mat& src0, apexcv::Mat& src1, apexcv::Mat& res, apexcv::Mat mask, int dtype){
		printf("... ApexCV emulation ... \n");

		res.create(src0.rows, src0.cols, dtype == -1 ? src0.type() : dtype);

		int lRetVal = 0;

		apexcv::Arithmetic a;

		DATATYPE dt, dest_dt;

		dt = src0.GetElementDataType();
		dest_dt = dt;
		if (dtype != -1){
			dest_dt = dd_from_cv_type(dtype);
		}

		if (dt >= 0) {
			//initialize and populate buffers
			//Mat res(src0.GetWidth(), src0.GetHeight(), dt, src0.GetElementDimX(), src0.GetElementDimY());


			if (((DataDescriptor*)&src0)->IsOK() && ((DataDescriptor*)&src1)->IsOK() && ((DataDescriptor*)&res)->IsOK())
			{
				//run implementation
				lRetVal = a.add(src0, src1, res);
			}

			if (lRetVal != 0)
				;//throw();//eventually throw an exception
		}
	}


	apexcv::Mat abs(apexcv::Mat& src)
	{
		int result = 0;
		Mat dst(src.GetHeight(), src.GetWidth(), DATATYPE_08U);


		apexcv::Arithmetic a;
		result |= a.abs((DataDescriptor&)src, (DataDescriptor&)dst);

		if (result != 0) {
			//TODO: add standardized apex cv error codes
			//return 1;
			Mat r;
			return r;
		}

		return dst;
	}


int absdiff( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                         DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                 DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U && 
       src1.GetElementDataType() == DATATYPE_08U && 
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv::Arithmetic a; 
      
       result |= a.absdiff(src0, src1, dst);
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int accumulate( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                    DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
    int result = 0;   

    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_16S) {
      
       apexcv::Arithmetic a;   
      
       result |= a.accumulate(src0, src1, dst);
      
    } else {
       //TODO: add standardized apex cv error codes
       result = 1;
    }
     
	return result;
}

int accumulateSquared( DataDescriptor& src0 /*!< Source 0 memory buffer. */,
								   DataDescriptor& src1 /*!< Source 1 memory buffer. */,
								   DataDescriptor& dst /*!< Destination memory buffer. */,
								   unsigned char scale /*!< Scale amount. (0 <= scale <= 15) */)
{
	int result = 0;

    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_16S) {
      
       apexcv::Arithmetic a;   
      
       result |= a.accumulateSquared(src0, src1, dst, scale);
      
    } else {
      //TODO: add standardized apex cv error codes
      result = 1;
	}
      
	return result;
}

int accumulateWeighted( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                                    DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                            DataDescriptor&   dst /*!< Destination memory buffer. */,
                                    unsigned char       alpha /*!< Weight amount. (0_8 bit fixed point) */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv::Arithmetic a; 
      
       result |= a.accumulateWeighted(src0, src1, dst, alpha);
      
    } else {
       //TODO: add standardized apex cv error codes
       result = 1;
 	}
   
	return result;
}

/*int add( DataDescriptor&  src0 /*!< Source 0 memory buffer. * /,
                     DataDescriptor&  src1 /*!< Source 1 memory buffer. * /,
		             DataDescriptor&   dst /*!< Destination memory buffer. * / )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv_arithmetic<ADD_08U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_16S &&
              src1.GetElementDataType() == DATATYPE_16S &&
              dst.GetElementDataType()  == DATATYPE_16S) {
             
       apexcv_arithmetic<ADD_16S> a;   
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();      
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
      
	return result;
}*/

int bitwiseAND( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                            DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a;
      
    result |= a.bitwiseAND(src0, src1, dst);
      
    return result;
}

int clz( DataDescriptor&  src  /*!< Source 0 memory buffer. */,
                     DataDescriptor&  dst  /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a; 
      
    result |= a.clz(src, dst);
       
	return result;
}

int bitwiseNOT( DataDescriptor&  src /*!< Source 0 memory buffer. */,
                            DataDescriptor&  dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv::Arithmetic a; 
      
       result |= a.bitwiseNOT(src, dst);
       
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int bitwiseOR( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                           DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                           DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a; 
      
    result |= a.bitwiseOR(src0, src1, dst);
       
	return result;
}

int bitwiseXOR( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                            DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a; 
      
    result |= a.bitwiseXOR(src0, src1, dst);
   
	return result;
}

int magnitude( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                           DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                           DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a; 
      
    result |= a.magnitude(src0, src1, dst);
   
	return result;
}

int subtract( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                          DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                          DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    apexcv::Arithmetic a; 
      
    result |= a.subtract(src0, src1, dst);
   
	return result;
}

int threshold( DataDescriptor&        src /*!< Source 0 memory buffer. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. */,
                           unsigned int         threshold /*!< Threshold value. */ )
{
    int result = 0;
      
    apexcv::Arithmetic a; 
      
    result |= a.threshold(src, dst, threshold);
     
	return result;
}
                             

	// THIS has the advantage that, as long as it is not implemented on APEX it does not cause compile errors, when compiled with the APEXCV flags
	//! computes element-wise weighted product of the two arrays (dst = scale*src1*src2)
	void multiply(apexcv::Mat& src1, apexcv::Mat& src2,
		apexcv::Mat& dst, double scale, int dtype)
	{
		//printf("Fake APEX multiply function... just for testing if it works\n");
		cv::multiply(src1, src2, dst, scale, dtype);
	}

/* TO BE IMPLEMENTED
subtract(InputArray src1, InputArray src2, OutputArray dst,
InputArray mask = noArray(), int dtype = -1);

//! computes element-wise weighted product of the two arrays (dst = scale*src1*src2)
void multiply(InputArray src1, InputArray src2,
OutputArray dst, double scale = 1, int dtype = -1);

//! computes element-wise weighted quotient of the two arrays (dst = scale*src1/src2)
void divide(InputArray src1, InputArray src2, OutputArray dst,
double scale = 1, int dtype = -1);

//! computes element-wise weighted reciprocal of an array (dst = scale/src2)
void divide(double scale, InputArray src2,
OutputArray dst, int dtype = -1);

//! adds scaled array to another one (dst = alpha*src1 + src2)
void scaleAdd(InputArray src1, double alpha, InputArray src2, OutputArray dst);

//! computes weighted sum of two arrays (dst = alpha*src1 + beta*src2 + gamma)
void addWeighted(InputArray src1, double alpha, InputArray src2,
double beta, double gamma, OutputArray dst, int dtype = -1);

//! scales array elements, computes absolute values and converts the results to 8-bit unsigned integers: dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
void convertScaleAbs(InputArray src, OutputArray dst,
double alpha = 1, double beta = 0);
//! transforms array of numbers using a lookup table: dst(i)=lut(src(i))
void LUT(InputArray src, InputArray lut, OutputArray dst,
int interpolation = 0);

//! computes sum of array elements
CV_EXPORTS_AS(sumElems) Scalar sum(InputArray src);
//! computes the number of nonzero array elements
int countNonZero(InputArray src);
//! returns the list of locations of non-zero pixels
void findNonZero(InputArray src, OutputArray idx);

//! computes mean value of selected array elements
Scalar mean(InputArray src, InputArray mask = noArray());
//! computes mean value and standard deviation of all or selected array elements
void meanStdDev(InputArray src, OutputArray mean, OutputArray stddev,
InputArray mask = noArray());
//! computes norm of the selected array part
double norm(InputArray src1, int normType = NORM_L2, InputArray mask = noArray());
//! computes norm of selected part of the difference between two arrays
double norm(InputArray src1, InputArray src2,
int normType = NORM_L2, InputArray mask = noArray());

//! naive nearest neighbor finder
void batchDistance(InputArray src1, InputArray src2,
OutputArray dist, int dtype, OutputArray nidx,
int normType = NORM_L2, int K = 0,
InputArray mask = noArray(), int update = 0,
bool crosscheck = false);

//! scales and shifts array elements so that either the specified norm (alpha) or the minimum (alpha) and maximum (beta) array values get the specified values
void normalize(InputArray src, OutputArray dst, double alpha = 1, double beta = 0,
int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());

//! finds global minimum and maximum array elements and returns their values and their locations
void minMaxLoc(InputArray src, CV_OUT double* minVal,
CV_OUT double* maxVal = 0, CV_OUT Point* minLoc = 0,
CV_OUT Point* maxLoc = 0, InputArray mask = noArray());
void minMaxIdx(InputArray src, double* minVal, double* maxVal,
int* minIdx = 0, int* maxIdx = 0, InputArray mask = noArray());

//! transforms 2D matrix to 1D row or column vector by taking sum, minimum, maximum or mean value over all the rows
void reduce(InputArray src, OutputArray dst, int dim, int rtype, int dtype = -1);

//! makes multi-channel array out of several single-channel arrays
void merge(const Mat* mv, size_t count, OutputArray dst);
void merge(const vector<Mat>& mv, OutputArray dst);

//! makes multi-channel array out of several single-channel arrays
void merge(InputArrayOfArrays mv, OutputArray dst);

//! copies each plane of a multi-channel array to a dedicated array
void split(const Mat& src, Mat* mvbegin);
void split(const Mat& m, vector<Mat>& mv);

//! copies each plane of a multi-channel array to a dedicated array
void split(InputArray m, OutputArrayOfArrays mv);

//! copies selected channels from the input arrays to the selected channels of the output arrays
void mixChannels(const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts,
const int* fromTo, size_t npairs);
void mixChannels(const vector<Mat>& src, vector<Mat>& dst,
const int* fromTo, size_t npairs);
void mixChannels(InputArrayOfArrays src, InputArrayOfArrays dst,
const vector<int>& fromTo);

//! extracts a single channel from src (coi is 0-based index)
void extractChannel(InputArray src, OutputArray dst, int coi);

//! inserts a single channel to dst (coi is 0-based index)
void insertChannel(InputArray src, InputOutputArray dst, int coi);

//! reverses the order of the rows, columns or both in a matrix
void flip(InputArray src, OutputArray dst, int flipCode);

//! replicates the input matrix the specified number of times in the horizontal and/or vertical direction
void repeat(InputArray src, int ny, int nx, OutputArray dst);
Mat repeat(const Mat& src, int ny, int nx);

void hconcat(const Mat* src, size_t nsrc, OutputArray dst);
void hconcat(InputArray src1, InputArray src2, OutputArray dst);
void hconcat(InputArrayOfArrays src, OutputArray dst);

void vconcat(const Mat* src, size_t nsrc, OutputArray dst);
void vconcat(InputArray src1, InputArray src2, OutputArray dst);
void vconcat(InputArrayOfArrays src, OutputArray dst);

//! computes bitwise conjunction of the two arrays (dst = src1 & src2)
void bitwise_and(InputArray src1, InputArray src2,
OutputArray dst, InputArray mask = noArray());
//! computes bitwise disjunction of the two arrays (dst = src1 | src2)
void bitwise_or(InputArray src1, InputArray src2,
OutputArray dst, InputArray mask = noArray());
//! computes bitwise exclusive-or of the two arrays (dst = src1 ^ src2)
void bitwise_xor(InputArray src1, InputArray src2,
OutputArray dst, InputArray mask = noArray());
//! inverts each bit of array (dst = ~src)
void bitwise_not(InputArray src, OutputArray dst,
InputArray mask = noArray());
//! computes element-wise absolute difference of two arrays (dst = abs(src1 - src2))
void absdiff(InputArray src1, InputArray src2, OutputArray dst);
//! set mask elements for those array elements which are within the element-specific bounding box (dst = lowerb <= src && src < upperb)
void inRange(InputArray src, InputArray lowerb,
InputArray upperb, OutputArray dst);
//! compares elements of two arrays (dst = src1 <cmpop> src2)
void compare(InputArray src1, InputArray src2, OutputArray dst, int cmpop);
//! computes per-element minimum of two arrays (dst = min(src1, src2))
void min(InputArray src1, InputArray src2, OutputArray dst);
//! computes per-element maximum of two arrays (dst = max(src1, src2))
void max(InputArray src1, InputArray src2, OutputArray dst);

//! computes per-element minimum of two arrays (dst = min(src1, src2))
void min(const Mat& src1, const Mat& src2, Mat& dst);
//! computes per-element minimum of array and scalar (dst = min(src1, src2))
void min(const Mat& src1, double src2, Mat& dst);
//! computes per-element maximum of two arrays (dst = max(src1, src2))
void max(const Mat& src1, const Mat& src2, Mat& dst);
//! computes per-element maximum of array and scalar (dst = max(src1, src2))
void max(const Mat& src1, double src2, Mat& dst);

//! computes square root of each matrix element (dst = src**0.5)
void sqrt(InputArray src, OutputArray dst);
//! raises the input matrix elements to the specified power (b = a**power)
void pow(InputArray src, double power, OutputArray dst);
//! computes exponent of each matrix element (dst = e**src)
void exp(InputArray src, OutputArray dst);
//! computes natural logarithm of absolute value of each matrix element: dst = log(abs(src))
void log(InputArray src, OutputArray dst);
//! computes cube root of the argument
float cubeRoot(float val);
//! computes the angle in degrees (0..360) of the vector (x,y)
float fastAtan2(float y, float x);

void exp(const float* src, float* dst, int n);
void log(const float* src, float* dst, int n);
void fastAtan2(const float* y, const float* x, float* dst, int n, bool angleInDegrees);
void magnitude(const float* x, const float* y, float* dst, int n);

//! converts polar coordinates to Cartesian
void polarToCart(InputArray magnitude, InputArray angle,
OutputArray x, OutputArray y, bool angleInDegrees = false);
//! converts Cartesian coordinates to polar
void cartToPolar(InputArray x, InputArray y,
OutputArray magnitude, OutputArray angle,
bool angleInDegrees = false);
//! computes angle (angle(i)) of each (x(i), y(i)) vector
void phase(InputArray x, InputArray y, OutputArray angle,
bool angleInDegrees = false);
//! computes magnitude (magnitude(i)) of each (x(i), y(i)) vector
void magnitude(InputArray x, InputArray y, OutputArray magnitude);
//! checks that each matrix element is within the specified range.
bool checkRange(InputArray a, bool quiet = true, CV_OUT Point* pos = 0,
double minVal = -DBL_MAX, double maxVal = DBL_MAX);
//! converts NaN's to the given number
void patchNaNs(InputOutputArray a, double val = 0);

//! implements generalized matrix product algorithm GEMM from BLAS
void gemm(InputArray src1, InputArray src2, double alpha,
InputArray src3, double beta, OutputArray dst, int flags = 0);
//! multiplies matrix by its transposition from the left or from the right
void mulTransposed(InputArray src, OutputArray dst, bool aTa,
InputArray delta = noArray(),
double scale = 1, int dtype = -1);
//! transposes the matrix
void transpose(InputArray src, OutputArray dst);
//! performs affine transformation of each element of multi-channel input matrix
void transform(InputArray src, OutputArray dst, InputArray m);
//! performs perspective transformation of each element of multi-channel input matrix
void perspectiveTransform(InputArray src, OutputArray dst, InputArray m);

//! extends the symmetrical matrix from the lower half or from the upper half
void completeSymm(InputOutputArray mtx, bool lowerToUpper = false);
//! initializes scaled identity matrix
void setIdentity(InputOutputArray mtx, const Scalar& s = Scalar(1));
//! computes determinant of a square matrix
double determinant(InputArray mtx);
//! computes trace of a matrix
Scalar trace(InputArray mtx);
//! computes inverse or pseudo-inverse matrix
double invert(InputArray src, OutputArray dst, int flags = DECOMP_LU);
//! solves linear system or a least-square problem
bool solve(InputArray src1, InputArray src2,
OutputArray dst, int flags = DECOMP_LU);


*/

}  /* namespace apex */
