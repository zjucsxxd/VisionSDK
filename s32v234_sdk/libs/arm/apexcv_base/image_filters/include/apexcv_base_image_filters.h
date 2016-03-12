/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/
 
/*!*********************************************************************************
*  \file
*  \brief APEX-CV Base Library
***********************************************************************************/

#ifndef __APEXCV_BASE_HPP__
#define __APEXCV_BASE_HPP__


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif
namespace apexcv{

/*!*********************************************************************************
*  \brief Image filter class containing various image filters
*
*  This class is an interface for using image filters on the host. Filter windows 
*  that exceed the boundaries of the image use replicated pixels for the padding.
***********************************************************************************/
class ImageFilter
{
public:

/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   ImageFilter();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~ImageFilter();

/*!*********************************************************************************
*  \brief List of sobel filter types
***********************************************************************************/
enum SobelType {
   SOBEL_X 		/*!< Apply sobel filter in x direction */,
   SOBEL_Y 		/*!< Apply sobel filter in y direction */,
   SOBEL_BOTH   /*!< Apply sobel filter in both x and y direction then sum their absolute values */
};



/*!*********************************************************************************
*  \brief List of prewitt filter types
***********************************************************************************/
enum PrewittType {
   PREWITT_X 		/*!< Apply prewitt filter in x direction */,
   PREWITT_Y 		/*!< Apply prewitt filter in y direction */
};


/*!*********************************************************************************
*  \brief Bilateral image filter.
*
*  Applies a bilateral filter to _src_. _sigmaColor_ represents the weight of 
*  color/intensity difference and _sigmaSpace_ represents the weight of spacial 
*  difference. See:  \cite BILATERAL for more information.
*
*  Supported window size is:
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int bilateralFilter(       DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           int                 sigmaColor /*!< Sigma value for color space. */,
                           int                 sigmaSpace /*!< Sigma value for distance space. */ );

/*!*********************************************************************************
*  \brief Box image filter.
*
*  Applies a box filter to _src_ buffer.
*  Each _dst_ buffer pixel is calculated as follows: 
*  \f$dst = \frac{1}{9}\left[ {\begin{array}{ccc} 1 & 1 & 1\\ 1 & 1 & 1\\ 1 & 1 & 1\\ \end{array} } \right] \ast src\f$
*
*  Supported window size is:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - signed 16 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                          
int boxFilter(             DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ ,
                          int               windowSize=3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */ );

/*!*********************************************************************************
*  \brief Dilate image filter.
*
*  Applies a dilate filter to _src_ buffer. 
*  Each _dst_ buffer pixel is the maximum pixel value contained in the window of the respective _src_ buffer pixel.
*
*  Supported window size is:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - signed 16 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int dilateFilter(          DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Erode image filter.
*
*  Applies an erode filter to _src_ buffer.
*  Each _dst_ buffer pixel is the minimum pixel value contained in the window of the respective _src_ buffer pixel.
*
*  Supported window size is:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int erodeFilter(           DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );
																 
/*!*********************************************************************************
*  \brief Median filter.
*
*  Applies a median filter to _src_ buffer.
*  Each _dst_ buffer pixel is the median pixel value contained in the window of the respective _src_ buffer pixel.
*
*  Supported window sizes are:
*     - 3 x 3
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int medianFilter(	         DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                             DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                             int				     windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */ );																 

/*!*********************************************************************************
*  \brief Gaussian image filter.
*
*  Applies a gaussian filter to _src_ buffer.
*  Each _dst_ buffer pixel is calculated as follows: 
*  \f$dst = \frac{1}{16}\left[ {\begin{array}{ccc} 1 & 2 & 1\\ 2 & 4 & 2\\ 1 & 2 & 1\\ \end{array} } \right] \ast src\f$
*
*  Supported window size is:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                          
int gaussianFilter(             DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM. */,
                                DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           int               windowSize=3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */ );

								 
/*!*********************************************************************************
*  \brief Sobel filter.
*
*  Applies a sobel filter based on \ref SobelType to _src_ buffer and returns the result in _dst_ buffer. 
*  SOBEL_BOTH calculates both SOBEL_X and SOBEL_Y images and then sums their absolute values following the formula:
*  \f$dst(i, j) = |SOBEL_X(i, j)| + |SOBEL_Y(i, j)|\f$
*
*	The 3x3 filter coefficients for x and y directions are: 
*
*     \f$filter_x = \left[ {\begin{array}{ccc} -1 & 0 & +1 \\ -2 & 0 & +2 \\ -1 & 0 & +1 \\ \end{array} } \right],\f$
*     \f$filter_y = \left[ {\begin{array}{ccc} -1 & -2 & -1 \\ 0 & 0 & 0 \\ +1 & +2 & +1 \\ \end{array} } \right]\f$
*
*  The 5x5 filter coefficients for x and y directions are: 
*
*     \f$filter_x = \left[ {\begin{array}{ccccc} -1 & -2 & 0 & +2 & +1 \\ -4 & -8 & 0 & +8 & +4 \\ -6 & -12 & 0 & +12 & +6 \\ -4 & -8 & 0 & +8 & +4 \\ -1 & -2 & 0 & +2 & +1 \\ \end{array} } \right],\f$
*     \f$filter_y = \left[ {\begin{array}{ccccc} -1 & -4 & -6 & -4 & -1 \\ -2 & -8 & -12 & -8 & -2 \\ 0 & 0 & 0 & 0 & 0 \\ +2 & +8 & +12 & +8 & +2 \\ +1 & +4 & +6 & +4 & +1 \\ \end{array} } \right]\f$
*
*	Supported formats are: 
*		- x direction
*		- y direction
*		- both directions
*
*  Supported window sizes are:
*     - 3 x 3
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 8 bit to signed 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int sobelFilter(           DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           int				     windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */,															 
                           SobelType	   st = SOBEL_BOTH /*!< Specify which sobel filter type to use. Default is SOBEL_BOTH. See \ref SobelType. */ );

/*!*********************************************************************************
*  \brief Sobel filter.
*
*  Applies a sobel filter based on \ref SobelType to _src_ buffer in the X and Y direction,
*  and returns the results in the _dstX_, and _dstY buffers respectively.
*
*  The 3x3 filter coefficients for x and y directions are: 
*
*     \f$filter_x = \left[ {\begin{array}{ccc} -1 & 0 & +1 \\ -2 & 0 & +2 \\ -1 & 0 & +1 \\ \end{array} } \right],\f$
*     \f$filter_y = \left[ {\begin{array}{ccc} -1 & -2 & -1 \\ 0 & 0 & 0 \\ +1 & +2 & +1 \\ \end{array} } \right]\f$
*
*  Supported window sizes are:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int sobelFilter(        DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                        DataDescriptor&       dstX /*!< Destination X memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                        DataDescriptor&       dstY /*!< Destination Y memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */);

/*!*********************************************************************************
*  \brief Convolve filter.
*
*  Applies a user defined filter with coefficients _filterCoeff_ to _src_ buffer and returns the result in _dst_ buffer.
*  _filterScale_ can be used to divide each filtered pixel by a value of \f$2^{filterScale}\f$. If the resulting pixel would overflow the _dst_ datatype
*  its value is saturated.
*
*  Supported window sizes are:
*     - 3 x 3
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int convolveFilter(        DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           signed char* filterCoeff /*!< Array containing the filter coefficients to be applied. */,															 
                           int		       windowSize = 3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */,
                           int		      filterScale = 0 /*!< Optional: used to scale the resulting filtered pixel by \f$2^{filterScale}\f$. Supported range of [0, 16]. */ );

/*!*********************************************************************************
*  \brief Prewitt filter.
*
*  Applies a prewitt filter based on \ref PrewittType to _src_ buffer and returns the result in _dst_ buffer. Similar to the \ref sobelFilter, prewitt uses the following filter coefficients:
* 
*  \f$filter_x = \left[ {\begin{array}{ccc} -1 & 0 & +1 \\ -1 & 0 & +1 \\ -1 & 0 & +1 \\ \end{array} } \right],\f$
*  \f$filter_y = \left[ {\begin{array}{ccc} -1 & -1 & -1 \\ 0 & 0 & 0 \\ +1 & +1 & +1 \\ \end{array} } \right]\f$
*  
*  Supported formats are: 
*	    - x direction
*	    - y direction
*
*  Supported window size is:
*      - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int prewittFilter(         DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           PrewittType	    pt = PREWITT_X /*!< Specify which prewitt filter type to use. Default is PREWITT_X. See \ref PrewittType. */ );
                                 
}; /* class ImageFilter */

namespace OPT {
	
/*!*********************************************************************************
*  \brief Image filter class containing various image filters
*
*  This class is an interface for using image filters on the host. Filter windows 
*  that exceed the boundaries of the image use replicated pixels for the padding.
***********************************************************************************/
class ImageFilter
{
public:
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   ImageFilter();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~ImageFilter();

/*!*********************************************************************************
*  \brief List of sobel filter types
***********************************************************************************/
enum SobelType {
   SOBEL_X     /*!< Apply sobel filter in x direction */,
   SOBEL_Y     /*!< Apply sobel filter in y direction */,
   SOBEL_BOTH  /*!< Apply sobel filter in both x and y direction then sum their absolute values */
};

/*!*********************************************************************************
*  \brief List of derivative types
***********************************************************************************/
enum DerivativeType {
   DERIVATIVE_X,
   DERIVATIVE_Y
};
/*!*********************************************************************************
*  \brief Box image filter.
*
*  Applies a box filter to _src_ buffer.
*  Each _dst_ buffer pixel is calculated as follows: 
*  \f$dst = \frac{1}{9}\left[ {\begin{array}{ccc} 1 & 1 & 1\\ 1 & 1 & 1\\ 1 & 1 & 1\\ \end{array} } \right] \ast src\f$
*
*  Supported window size is:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                          
int boxFilter(       DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM. */,
                     DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                     int               windowSize=3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */ );

/*!*********************************************************************************
*  \brief Generic Convolution Filter
*
*  Applies a user defined filter with coefficients _filterCoeff_ to _src_ buffer and returns the result in _dst_ buffer.
*  _filterScale_ can be used to divide each filtered pixel by a value of \f$2^{filterScale}\f$. If the resulting pixel would overflow the _dst_ datatype
*  its value is saturated.
*
*  For 3x3 kernels, the kernel's coefficients are
*
*           f0  f1  f2
*           f3  f4  f5
*           f6  f7  f8
*
*  For 5x5 kernels, the kernel's coefficients are
*
*           f0  f1  f2  f3  f4
*           f5  f6  f7  f8  f9
*           f10 f11 f12 f13 f14
*           f15 f16 f17 f18 f19
*           f20 f21 f22 f23 f24
*
*  Supported window sizes are:
*     - 3 x 3
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int convolveFilter(        DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                           const signed char* filterCoeff /*!< Array containing the filter coefficients to be applied. */,                                            
                           int             windowSize = 3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */,
                           int            filterScale = 0 /*!< Optional: used to scale (right shift) the resulting filtered pixel by \f$2^{filterScale}\f$. Supported range of [0, 16]. */ );

/*!*********************************************************************************
*  \brief General Central Derivative Filter
*
*  Compute general central derivative filter of size 3x3.
*
*  For dy filter, the image is convolved with the following kernel:
*
*          -k0 -k1 -k2
*           0   0   0
*           k0  k1  k2
*
*  For dx filter, the image is convolved with the following kernel:
*
*          -k0  0   k0
*          -k1  0   k1
*          -k2  0   k2
*
*  With k0, k1, k2 given as arguments to the function.
*
*  Supported formats are: 
*     - x derivative
*     - y derivative
*
*  Supported window sizes are:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int derivativeFilter(      DataDescriptor& src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                           DataDescriptor& dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                 DerivativeType dt /*!< Specify which derivative filter type to use. See \ref #DerivativeType. */,
                                    signed char k0 /*!< The first filter coefficient. */,
                                    signed char k1 /*!< The first filter coefficient. */,
                                    signed char k2 /*!< The first filter coefficient. */ );

/*!*********************************************************************************
*  \brief Saturate Signed 16-bit to 8-bit filter.
*
*  Saturates a signed 16-bit _src_ input to a signed 8-bit _dst_ output (pixel range [-128, 127]).
*  Scales down the pixels by 8 and rounds before saturation
*
*  Supported datatypes are:
*     - signed 16 bit to signed 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                          
int saturateFilter(        DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Generic Separable Filter
*
*  Applies a user defined filter with coefficients _filterRow_  and _filterCol to _src_ buffer and returns the result in _dst_ buffer.
*  There is no scaling or saturation of the resultant pixels.
*
*  The image is convolved with the 2D separable kernel
*
*        fCol[0]
*        fCol[1]  *  fRow[0] fRow[1] fRow[2]
*        fCol[2]
*
*  Supported window sizes are:
*     - 3 x 3
*     - 5 x 5
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int separableFilter(       DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                           signed char*   filterRow /*!< Array containing the row filter coefficients to be applied. */,                                            
                           signed char*   filterCol /*!< Array containing the column filter coefficients to be applied. */,                                            
                           int             windowSize = 3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */ );

/*!*********************************************************************************
*  \brief Sobel filter.
*
*  Applies a sobel filter based on \ref SobelType to _src_ buffer and returns the result in _dst_ buffer. 
*  SOBEL_BOTH calculates both SOBEL_X and SOBEL_Y images and then sums their absolute values following the formula:
*  \f$dst(i, j) = |SOBEL_X(i, j)| + |SOBEL_Y(i, j)|\f$
*
*  The 3x3 filter coefficients for x and y directions are: 
*
*     \f$filter_x = \left[ {\begin{array}{ccc} -1 & 0 & +1 \\ -2 & 0 & +2 \\ -1 & 0 & +1 \\ \end{array} } \right],\f$
*     \f$filter_y = \left[ {\begin{array}{ccc} -1 & -2 & -1 \\ 0 & 0 & 0 \\ +1 & +2 & +1 \\ \end{array} } \right]\f$
*
*  Supported formats are: 
*     - x direction
*     - y direction
*     - both directions (summation)
*
*  Supported window sizes are:
*     - 3 x 3
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 8 bit
*     - unsigned 8 bit to signed 16 bit (only summation)
*
*  \return Error code (zero on success).
***********************************************************************************/
int sobelFilter(        DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                        DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                        int               windowSize=3 /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */,                                              
                        SobelType      st = SOBEL_BOTH  /*!< Specify which sobel filter type to use. Default is SOBEL_SUM. See \ref SobelType. */ );
};	
} // namespace OPT

}  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
