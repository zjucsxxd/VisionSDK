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
*  \brief Histogram class containing histogram support
*
*  This class is an interface for using the histogram kernel on the host.
***********************************************************************************/
class Histogram
{
public:

/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   Histogram();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~Histogram();

/*!*********************************************************************************
*  \brief Histogram execution.
*
*  Calculates an image histogram (http://en.wikipedia.org/wiki/Image_histogram) from the _src_ buffer and returns the result in _dst_ buffer.
*  The resulting histogram has 256 bins each representing the respective number of pixel values found in the _src_ image.
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 32 bit bins
*
*  \return Error code (zero on success).
***********************************************************************************/
int exec(   DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
            DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

}; /* class Histogram */

}  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
