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

#ifndef __APEXCV_BASE_ARITHMETIC_HPP__
#define __APEXCV_BASE_ARITHMETIC_HPP__

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
*  \brief Arithmetic class containing various arithmetic functions
*
*  This class is an interface for using arithmetic functions on the host.
***********************************************************************************/

class Arithmetic
{

public:

/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   Arithmetic();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~Arithmetic();

   /*!*********************************************************************************
*  \brief Absolute value function.
*
*  Calculates the absolute value of _src0_ buffer and stores the result in _dst_ buffer.
*
*  Supported datatypes are:
*     - signed 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int abs( DataDescriptor&       src /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
            DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );
   
/*!*********************************************************************************
*  \brief Absolute difference function.
*
*  Calculates the absolute difference between _src0_ and _src1_ buffers and stores the result in _dst_ buffer.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int absdiff(            DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Accumulate function.
*
*  Calculates the addition of the _src0_ and _src1_ buffers and stores the result in _dst_ buffer.
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int accumulate(         DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );
                                 
/*!*********************************************************************************
*  \brief Accumulate Squared function.
*
*  Calculates the addition of the _src0_ and _src1_ (squared) buffers and stores the result in _dst_ buffer.
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int accumulateSquared( DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                          DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                          DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ ,
						  unsigned char            scale /*!< Shift amount. Value of [0, 15] */ );
/*!*********************************************************************************
*  \brief Accumulate Weighted function.
*
*  Accumulate weighted uses the equation:
*     \f$dst = src_0*(1 - \frac{alpha}{256}) + src_1*\frac{alpha}{256}\f$.
* 
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                                            
   int accumulateWeighted( DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           unsigned char            alpha /*!< Weight amount. 8 bit fixed point value of [0, 1) */ );
                                 
/*!*********************************************************************************
*  \brief Addition function.
*
*  Adds _src0_ and _src1_ buffers and stores the result in _dst_ buffer. In case of overflow the result is saturated.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - signed 16 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                    
   int add( DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
			DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
            DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */);
                                 
/*!*********************************************************************************
*  \brief Bitwise AND function.
* 
*  Bitwise ANDs _src0_ and _src1_ buffers and stores the result in _dst_ buffer. See (http://en.wikipedia.org/wiki/Bitwise_operation) for
* 	more information on bitwise operations.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 16 bit to unsigned 16 bit
*     - unsigned 32 bit to unsigned 32 bit
*
*  \return Error code (zero on success).
***********************************************************************************/   
   int bitwiseAND(         DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Bitwise NOT function.
* 
*  Bitwise NOTs _src_ buffer and stores the result in _dst_ buffer. See (http://en.wikipedia.org/wiki/Bitwise_operation) for
* 	more information on bitwise operations.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                           
   int bitwiseNOT(         DataDescriptor&        src /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Bitwise OR function.
* 
*  Bitwise ORs _src0_ and _src1_ buffers and stores the result in _dst_ buffer. See (http://en.wikipedia.org/wiki/Bitwise_operation) for
* 	more information on bitwise operations.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 16 bit to unsigned 16 bit
*     - unsigned 32 bit to unsigned 32 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                 
   int bitwiseOR(          DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );
                                 
/*!*********************************************************************************
*  \brief Bitwise XOR function.
* 
*  Bitwise XORs _src0_ and _src1_ buffers and stores the result in _dst_ buffer. See (http://en.wikipedia.org/wiki/Bitwise_operation) for
* 	more information on bitwise operations.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 16 bit to unsigned 16 bit
*     - unsigned 32 bit to unsigned 32 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int bitwiseXOR(         DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

   /*!*********************************************************************************
*  \brief Count leading zeros function.
*
*  Counts the leading zeros of _src0_ buffer and stores the result in _dst_ buffer.
*
*  Supported datatypes are:
*     - unsigned  8 bit to unsigned 8 bit
*     - signed    8 bit to unsigned 8 bit
*     - unsigned 16 bit to unsigned 8 bit
*     - signed   16 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int clz(            DataDescriptor&       src /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                       DataDescriptor&       dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Magnitude function.
* 
*  Calculates the magnitude between two sources following the format \f$dst = \sqrt{src_0^2 + src_1^2}\f$. The result is floored to the nearest integer. 
*  Note if you want to calculate the gradient magnitude you must calculate the image gradients and pass them in to this function.
*
*  Supported datatypes are:
*     - signed 16 bit to unsigned 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
   int magnitude(          DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );
                                 
/*!*********************************************************************************
*  \brief Subtraction function.
* 
*  Subtracts _src0_ from _src1_ buffers and stores the result in _dst_. In case of over/underflow the result is saturated.
*
*  Supported datatypes are:
*     - unsigned 8 bit to signed 16 bit
*     - signed 16 bit to signed 16 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                 
   int subtract(           DataDescriptor&       src0 /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&       src1 /*!< Source 1 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

/*!*********************************************************************************
*  \brief Threshold function.
* 
*  Returns an 8 bit boolean image based on the equation:
*  \f$ dst = \left\{ \begin{array}{ll}  255 & \text{if } src > threshold \\ 
*                                       0   & \text{otherwise}           \end{array} \right. \f$
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*     - unsigned 16 bit to unsigned 8 bit
*     - unsigned 32 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/                                 
   int threshold(          DataDescriptor&        src /*!< Source 0 memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           unsigned int         threshold /*!< Threshold value. */ );
                                 
}; /* class Arithmetic */

}  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
