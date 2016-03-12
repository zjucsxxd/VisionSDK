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

 
/*!*********************************************************************************
*  \file
*  \brief APEX-CV Base Library
***********************************************************************************/

#ifndef __APEXCV_MAT_HPP__
#define __APEXCV_MAT_HPP__

#ifndef APEX2_EMULATE

#include <icp_data.h>
using namespace icp;
#else
#include "acf_data_descriptor.hpp"
using namespace APEX2;
#endif

#include <oal.h>
#include "opencv2/core/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types_c.h"

#include "apexcv_core.h"

namespace apexcv{

/*!*********************************************************************************
*  \brief apexcv::Mat class, which unifies the cv::Mat and apex DataDescriptor types
***********************************************************************************/
	class Mat : public DataDescriptor, public cv::Mat {
	public:

#define dd ((DataDescriptor*) this)
#define cvm ((cv::Mat*) this)

		/*!*********************************************************************************
		*  \brief Default constructor.
		***********************************************************************************/
		Mat()
			: DataDescriptor()
			, cv::Mat() {
		};

		/*!*********************************************************************************
		*  \brief Destructor.
		***********************************************************************************/
		virtual ~Mat(){
		};


		Mat(const cv::Mat& toCpy)
			: cv::Mat(toCpy)
			, DataDescriptor()
		{
			//dd->InitManual(cvm->cols, cvm->rows, (void*)cvm->data, (void*)cvm->data, (DATATYPE) dd_from_cv_type(toCpy.type), CV_MAT_CN(toCpy.type), 1);
			dd->SetFreeOnExit(false);
		}

		Mat(int rows, int cols, int typ)
			: DataDescriptor(cols, rows, (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1)
			, cv::Mat(rows, cols, typ, dd->GetDataPtr())
		{
			//dd->Init(cols, rows, (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			//dd->SetFreeOnExit(false);
			//(*cvm) = cv::Mat(size, typ, dd->GetDataPtr());
		}


		Mat(int rows, int cols, int typ, void* dataPtr)
			: DataDescriptor()
			, cv::Mat(rows, cols, typ, dataPtr)
		{
			//(*cvm) = cv::Mat(rows, cols, typ, dataPtr);
			dd->InitManual(cols, rows, (void*)cvm->data, (void *)OAL_MemoryReturnAddress((void *)cvm->data, ACCESS_PHY), (DATATYPE)dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			dd->SetFreeOnExit(false);
		}

		Mat(cv::Size& size, int typ)
			: DataDescriptor(size.width, size.height, (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1)
			, cv::Mat(size, typ, dd->GetDataPtr())
		{
			//dd->InitManual(size.width, size.height, (void*)cvm->data, (void *)OAL_MemoryReturnAddress((void *)cvm->data, ACCESS_PHY), (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			//dd->SetFreeOnExit(false);
		}

		Mat(cv::Size& size, int typ, void* dataPtr)
					: DataDescriptor()
					, cv::Mat(size, typ, dataPtr)
		{
			//(*cvm) = cv::Mat(size, typ, dataPtr);
			dd->InitManual(size.width, size.height, (void*)cvm->data, (void *)OAL_MemoryReturnAddress((void *)cvm->data, ACCESS_PHY), (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			dd->SetFreeOnExit(false);
		}

		Mat(int rows, int cols, int typ, cv::Scalar& s)
			: DataDescriptor()
			, cv::Mat(rows, cols, typ, s)
		{
		  //TODO
			dd->InitManual(cols, rows, (void*)cvm->data, (void *)OAL_MemoryReturnAddress((void *)cvm->data, ACCESS_PHY), (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			dd->SetFreeOnExit(false);
		}

		Mat(cv::Size& size, int typ, cv::Scalar& s)
			: DataDescriptor()
			, cv::Mat(size, typ, s)
		{
		  //TODO
			dd->InitManual(size.width, size.height, (void*)cvm->data, (void *)OAL_MemoryReturnAddress((void *)cvm->data, ACCESS_PHY), (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
			dd->SetFreeOnExit(false);
		}

		Mat(Mat& m, cv::Range& rowRange, cv::Range& colRange)
			: DataDescriptor()
			, cv::Mat(m, rowRange, colRange)
		{
		  //TODO
			//dd->InitManual(cvm->cols, cvm->rows, (void*)cvm->data, (void*)cvm->data, (DATATYPE) dd_from_cv_type(m.type), CV_MAT_CN(m.type), 1);
			dd->SetFreeOnExit(false);
		}

		void Init(int width, int height, DATATYPE dt) {
		  dd->Init(cvm->cols, cvm->rows, dt);
		  dd->SetFreeOnExit(false);	
		  //cvm->create(height, width, cv_from_dd_type(dt), dd->GetDataPtr());
		  (*cvm) = cv::Mat(height, width, cv_from_dd_type(dt), dd->GetDataPtr());
			
		}

		void Init(int width, int height, void* dataPtr, DATATYPE dt) {
		  dd->InitManual(width, height, (void*)dataPtr, (void *)OAL_MemoryReturnAddress((void *)dataPtr, ACCESS_PHY), dt);
		  dd->SetFreeOnExit(false);	
		  (*cvm) = cv::Mat(height, width, cv_from_dd_type(dt), (void*)dataPtr);
			
		}

		void Init(int size, void* dataPtr, DATATYPE dt) {
		  dd->InitManual(cvm->cols, cvm->rows, dataPtr, (void *)OAL_MemoryReturnAddress((void *)dataPtr, ACCESS_PHY), dt);
		  dd->SetFreeOnExit(false);	
		  (*cvm) = cv::Mat(1, size, cv_from_dd_type(dt), (void*)dataPtr);
			
		}

		void Init(int size, DATATYPE dt) {
		  //dd->Init(size, dt, CV_MAT_CN(cvm->type), 1);
		  //dd->SetFreeOnExit(false);
		  //(*cvm) = cv::Mat(1, size, cv_from_dd_type(dt), dd->GetDataPtr());
		  //cvm->create(1, size, cv_from_dd_type(dt), dd->GetDataPtr());
			
		}

		Mat& clone()
		{
			Mat *retVal = new Mat(cvm->clone());
			return *retVal;
		}

		void create(int rows, int cols, int typ) {
		  dd->Init(cvm->cols, cvm->rows, (DATATYPE) dd_from_cv_type(typ), CV_MAT_CN(typ), 1);
		  //cvm->create(rows, cols, typ, dd->GetDataPtr());
		  (*cvm) = cv::Mat(rows, cols, typ, dd->GetDataPtr());
			
		}

		static Mat& eye(int rows, int cols, int typ) {
			Mat* retVal = new Mat(cv::Mat::eye(rows, cols, typ));
			return *retVal;
		}

		//
		// C++: static Mat Mat::eye(Size size, int type)
		//

		static Mat& eye(cv::Size& size, int type) {
			Mat *retVal = new Mat(cv::Mat::eye(size, type));
			return *retVal;
		}

		Mat& inv(int method) {
			Mat *retVal = new Mat(cvm->inv(method));
			return *retVal;
		}

		Mat& inv() {
			Mat *retVal = new Mat(cvm->inv());
			return *retVal;
		}


		Mat& mul(Mat& m, double scale) {
			Mat* retVal = new Mat(cvm->mul(m, scale));
			return *retVal;
		}

		Mat& mul(Mat& m) {
			Mat *retVal = new Mat(cvm->mul(m));
			return *retVal;
		}

		static Mat& ones(int rows, int cols, int type) {
			Mat *retVal = new Mat(cv::Mat::ones(rows, cols, type));
			return *retVal;
		}

		void push_back(Mat& m) {
			cvm->push_back(m);
			//dd->InitManual(cvm->cols, cvm->rows, (void*)cvm->data, (void*)cvm->data, (DATATYPE) dd_from_cv_type(m.type), CV_MAT_CN(m.type), 1);
			return;
		}

		Mat& reshape(int cn, int rows) {
			Mat *retVal = new Mat(cvm->reshape(cn, rows));
			return *retVal;
		}

		//
		// C++: Mat Mat::row(int y)
		//
		Mat& row(int y) {
			Mat *retVal = new Mat(cvm->row(y));
			return *retVal;
		}

		//
		// C++: Mat Mat::rowRange(int startrow, int endrow)
		//
		Mat& rowRange(int startrow, int endrow) {
			Mat *retVal = new Mat(cvm->rowRange(startrow, endrow));
			return *retVal;
		}

		//
		// C++: Mat Mat::rowRange(Range r)
		//
		Mat& rowRange(cv::Range& r) {
			Mat *retVal = new Mat(cvm->rowRange(r));
			return *retVal;
		}


		Mat& setTo(cv::Scalar& s) {

			Mat *retVal = new Mat(cvm->setTo(s));
			return *retVal;
		}

		//
		// C++: Mat Mat::setTo(Scalar value, Mat mask = Mat())
		//
		Mat& setTo(cv::Scalar& value, cv::Mat& mask)	{

			Mat *retVal = new Mat(cvm->setTo(value, mask));
			return *retVal;
		}

		//
		// C++: Mat Mat::setTo(Mat value, Mat mask = Mat())
		//
		Mat& setTo(cv::Mat& value, cv::Mat& mask) {
			Mat *retVal = new Mat(cvm->setTo(value, mask));
			return *retVal;
		}

		Mat& setTo(Mat& value) {
			Mat *retVal = new Mat(cvm->setTo(value));
			return *retVal;
		}

		//
		// C++: Mat Mat::operator()(int rowStart, int rowEnd, int colStart, int
		// colEnd)
		//
		Mat& submat(int rowStart, int rowEnd, int colStart, int colEnd){
			Mat *retVal = NULL;
			//Mat *retVal = new Mat((*cvm).operator()(rowStart, rowEnd, colStart, colEnd));
			return *retVal;
		}

		//
		// C++: Mat Mat::operator()(Range rowRange, Range colRange)
		//
		Mat& submat(cv::Range& rowRange, cv::Range& colRange) {
			Mat *retVal = new Mat((*cvm).operator()(rowRange, colRange));
			return *retVal;
		}

		//
		// C++: Mat Mat::operator()(Rect roi)
		//
		Mat& submat(cv::Rect& roi) {
			Mat *retVal = new Mat((*cvm)(roi));
			return *retVal;
		}

		//
		// C++: Mat Mat::t() transpose matrix
		//
		Mat& t() {
			Mat *retVal = new Mat(cvm->t());
			return *retVal;
		}


		static Mat& zeros(int rows, int cols, int type) {
			Mat *retVal = new Mat(cv::Mat::zeros(rows, cols, type));
			return *retVal;
		}

		//
		// C++: Mat Mat::adjustROI(int dtop, int dbottom, int dleft, int dright)
		//
		Mat& adjustROI(int dtop, int dbottom, int dleft, int dright) {
			Mat *retVal = new Mat(cvm->adjustROI(dtop, dbottom, dleft, dright));
			return *retVal;
		}

		//
		// C++: Mat Mat::cross(Mat m)
		//
		Mat& cross(cv::Mat& m) {
			Mat *retVal = new Mat(cvm->cross(m));
			return *retVal;
		}

		//
		// C++: Mat Mat::diag(int d = 0)
		//
		Mat& diag(int d) {
			Mat *retVal = new Mat(cvm->diag(d));
			return *retVal;
		}

		Mat& diag() {
			Mat *retVal = new Mat(cvm->diag());
			return *retVal;
		}

		//
		// C++: static Mat Mat::diag(Mat d)
		//
		static Mat& diag(Mat& d) {
			Mat *retVal = new Mat(cv::Mat::diag(d));
			return *retVal;
		}

		Mat operator + (Mat& b) {
			Mat r(dd->GetHeight(), dd->GetWidth(), cv_from_dd_type(dd->GetElementDataType()));
			//add((*dd), b, r);
			return r;
		}



		/* TBD:
		Mat(Mat m, Rect roi)  {}

		void assignTo(Mat m, int type)
		void assignTo(Mat m)
		void convertTo(Mat m, int rtype, double alpha, double beta)
		void convertTo(Mat m, int rtype, double alpha)
		void convertTo(Mat m, int rtype)
		void copyTo(Mat m)
		void copyTo(Mat m, Mat mask)
		void locateROI(Size wholeSize, Point ofs)
		{
		double[] wholeSize_out = new double[2];
		double[] ofs_out = new double[2];
		locateROI_0(nativeObj, wholeSize_out, ofs_out);
		if(wholeSize!=null){ wholeSize.width = wholeSize_out[0]; wholeSize.height = wholeSize_out[1]; }
		if(ofs!=null){ ofs.x = ofs_out[0]; ofs.y = ofs_out[1]; }
		return;
		}
		*/
	};

	/* TO BE IMPLEMENTED
	///////////////////////////////// Mat_<_Tp> ////////////////////////////////////

	/*!
	Template matrix class derived from Mat

	The class Mat_ is a "thin" template wrapper on top of cv::Mat. It does not have any extra data fields,
	nor it or cv::Mat have any virtual methods and thus references or pointers to these two classes
	can be safely converted one to another. But do it with care, for example:

	\code
	// create 100x100 8-bit matrix
	Mat M(100,100,CV_8U);
	// this will compile fine. no any data conversion will be done.
	Mat_<float>& M1 = (Mat_<float>&)M;
	// the program will likely crash at the statement below
	M1(99,99) = 1.f;
	\endcode

	While cv::Mat is sufficient in most cases, cv::Mat_ can be more convenient if you use a lot of element
	access operations and if you know matrix type at compile time.
	Note that cv::Mat::at<_Tp>(int y, int x) and cv::Mat_<_Tp>::operator ()(int y, int x) do absolutely the
	same thing and run at the same speed, but the latter is certainly shorter:

	\code
	Mat_<double> M(20,20);
	for(int i = 0; i < M.rows; i++)
	for(int j = 0; j < M.cols; j++)
	M(i,j) = 1./(i+j+1);
	Mat E, V;
	eigen(M,E,V);
	cout << E.at<double>(0,0)/E.at<double>(M.rows-1,0);
	\endcode

	It is easy to use Mat_ for multi-channel images/matrices - just pass cv::Vec as cv::Mat_ template parameter:

	\code
	// allocate 320x240 color image and fill it with green (in RGB space)
	Mat_<Vec3b> img(240, 320, Vec3b(0,255,0));
	// now draw a diagonal white line
	for(int i = 0; i < 100; i++)
	img(i,i)=Vec3b(255,255,255);
	// and now modify the 2nd (red) channel of each pixel
	for(int i = 0; i < img.rows; i++)
	for(int j = 0; j < img.cols; j++)
	img(i,j)[2] ^= (uchar)(i ^ j); // img(y,x)[c] accesses c-th channel of the pixel (x,y)
	\endcode
	* /
	template<typename _Tp> class Mat_ : public Mat
	{
	public:
		typedef _Tp value_type;
		typedef typename DataType<_Tp>::channel_type channel_type;
		typedef MatIterator_<_Tp> iterator;
		typedef MatConstIterator_<_Tp> const_iterator;

		//! default constructor
		Mat_();
		//! equivalent to Mat(_rows, _cols, DataType<_Tp>::type)
		Mat_(int _rows, int _cols);
		//! constructor that sets each matrix element to specified value
		Mat_(int _rows, int _cols, const _Tp& value);
		//! equivalent to Mat(_size, DataType<_Tp>::type)
		explicit Mat_(Size _size);
		//! constructor that sets each matrix element to specified value
		Mat_(Size _size, const _Tp& value);
		//! n-dim array constructor
		Mat_(int _ndims, const int* _sizes);
		//! n-dim array constructor that sets each matrix element to specified value
		Mat_(int _ndims, const int* _sizes, const _Tp& value);
		//! copy/conversion contructor. If m is of different type, it's converted
		Mat_(const Mat& m);
		//! copy constructor
		Mat_(const Mat_& m);
		//! constructs a matrix on top of user-allocated data. step is in bytes(!!!), regardless of the type
		Mat_(int _rows, int _cols, _Tp* _data, size_t _step = AUTO_STEP);
		//! constructs n-dim matrix on top of user-allocated data. steps are in bytes(!!!), regardless of the type
		Mat_(int _ndims, const int* _sizes, _Tp* _data, const size_t* _steps = 0);
		//! selects a submatrix
		Mat_(const Mat_& m, const Range& rowRange, const Range& colRange = Range::all());
		//! selects a submatrix
		Mat_(const Mat_& m, const Rect& roi);
		//! selects a submatrix, n-dim version
		Mat_(const Mat_& m, const Range* ranges);
		//! from a matrix expression
		explicit Mat_(const MatExpr& e);
		//! makes a matrix out of Vec, std::vector, Point_ or Point3_. The matrix will have a single column
		explicit Mat_(const vector<_Tp>& vec, bool copyData = false);
		template<int n> explicit Mat_(const Vec<typename DataType<_Tp>::channel_type, n>& vec, bool copyData = true);
		template<int m, int n> explicit Mat_(const Matx<typename DataType<_Tp>::channel_type, m, n>& mtx, bool copyData = true);
		explicit Mat_(const Point_<typename DataType<_Tp>::channel_type>& pt, bool copyData = true);
		explicit Mat_(const Point3_<typename DataType<_Tp>::channel_type>& pt, bool copyData = true);
		explicit Mat_(const MatCommaInitializer_<_Tp>& commaInitializer);

		Mat_& operator = (const Mat& m);
		Mat_& operator = (const Mat_& m);
		//! set all the elements to s.
		Mat_& operator = (const _Tp& s);
		//! assign a matrix expression
		Mat_& operator = (const MatExpr& e);

		//! iterators; they are smart enough to skip gaps in the end of rows
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		//! equivalent to Mat::create(_rows, _cols, DataType<_Tp>::type)
		void create(int _rows, int _cols);
		//! equivalent to Mat::create(_size, DataType<_Tp>::type)
		void create(Size _size);
		//! equivalent to Mat::create(_ndims, _sizes, DatType<_Tp>::type)
		void create(int _ndims, const int* _sizes);
		//! cross-product
		Mat_ cross(const Mat_& m) const;
		//! data type conversion
		template<typename T2> operator Mat_<T2>() const;
		//! overridden forms of Mat::row() etc.
		Mat_ row(int y) const;
		Mat_ col(int x) const;
		Mat_ diag(int d = 0) const;
		Mat_ clone() const;

		//! overridden forms of Mat::elemSize() etc.
		size_t elemSize() const;
		size_t elemSize1() const;
		int type() const;
		int depth() const;
		int channels() const;
		size_t step1(int i = 0) const;
		//! returns step()/sizeof(_Tp)
		size_t stepT(int i = 0) const;

		//! overridden forms of Mat::zeros() etc. Data type is omitted, of course
		static MatExpr zeros(int rows, int cols);
		static MatExpr zeros(Size size);
		static MatExpr zeros(int _ndims, const int* _sizes);
		static MatExpr ones(int rows, int cols);
		static MatExpr ones(Size size);
		static MatExpr ones(int _ndims, const int* _sizes);
		static MatExpr eye(int rows, int cols);
		static MatExpr eye(Size size);

		//! some more overriden methods
		Mat_& adjustROI(int dtop, int dbottom, int dleft, int dright);
		Mat_ operator()(const Range& rowRange, const Range& colRange) const;
		Mat_ operator()(const Rect& roi) const;
		Mat_ operator()(const Range* ranges) const;

		//! more convenient forms of row and element access operators
		_Tp* operator [](int y);
		const _Tp* operator [](int y) const;

		//! returns reference to the specified element
		_Tp& operator ()(const int* idx);
		//! returns read-only reference to the specified element
		const _Tp& operator ()(const int* idx) const;

		//! returns reference to the specified element
		template<int n> _Tp& operator ()(const Vec<int, n>& idx);
		//! returns read-only reference to the specified element
		template<int n> const _Tp& operator ()(const Vec<int, n>& idx) const;

		//! returns reference to the specified element (1D case)
		_Tp& operator ()(int idx0);
		//! returns read-only reference to the specified element (1D case)
		const _Tp& operator ()(int idx0) const;
		//! returns reference to the specified element (2D case)
		_Tp& operator ()(int idx0, int idx1);
		//! returns read-only reference to the specified element (2D case)
		const _Tp& operator ()(int idx0, int idx1) const;
		//! returns reference to the specified element (3D case)
		_Tp& operator ()(int idx0, int idx1, int idx2);
		//! returns read-only reference to the specified element (3D case)
		const _Tp& operator ()(int idx0, int idx1, int idx2) const;

		_Tp& operator ()(Point pt);
		const _Tp& operator ()(Point pt) const;

		//! conversion to vector.
		operator vector<_Tp>() const;
		//! conversion to Vec
		template<int n> operator Vec<typename DataType<_Tp>::channel_type, n>() const;
		//! conversion to Matx
		template<int m, int n> operator Matx<typename DataType<_Tp>::channel_type, m, n>() const;
	};

	typedef Mat_<uchar> Mat1b;
	typedef Mat_<Vec2b> Mat2b;
	typedef Mat_<Vec3b> Mat3b;
	typedef Mat_<Vec4b> Mat4b;

	typedef Mat_<short> Mat1s;
	typedef Mat_<Vec2s> Mat2s;
	typedef Mat_<Vec3s> Mat3s;
	typedef Mat_<Vec4s> Mat4s;

	typedef Mat_<ushort> Mat1w;
	typedef Mat_<Vec2w> Mat2w;
	typedef Mat_<Vec3w> Mat3w;
	typedef Mat_<Vec4w> Mat4w;

	typedef Mat_<int>   Mat1i;
	typedef Mat_<Vec2i> Mat2i;
	typedef Mat_<Vec3i> Mat3i;
	typedef Mat_<Vec4i> Mat4i;

	typedef Mat_<float> Mat1f;
	typedef Mat_<Vec2f> Mat2f;
	typedef Mat_<Vec3f> Mat3f;
	typedef Mat_<Vec4f> Mat4f;

	typedef Mat_<double> Mat1d;
	typedef Mat_<Vec2d> Mat2d;
	typedef Mat_<Vec3d> Mat3d;
	typedef Mat_<Vec4d> Mat4d;


	typedef void(*ConvertData)(const void* from, void* to, int cn);
	typedef void(*ConvertScaleData)(const void* from, void* to, int cn, double alpha, double beta);

	//! returns the function for converting pixels from one data type to another
	CV_EXPORTS ConvertData getConvertElem(int fromType, int toType);
	//! returns the function for converting pixels from one data type to another with the optional scaling
	CV_EXPORTS ConvertScaleData getConvertScaleElem(int fromType, int toType);



	
	*/

 }  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
