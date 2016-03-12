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
*  \brief Integral Image class containing integral image support
*
*  This class is an interface for using the integral image kernel on the host.
***********************************************************************************/
class IntegralImage
{
public:

/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   IntegralImage();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~IntegralImage();

/*!*********************************************************************************
*  \brief Integral Image execution.
*
*  Calculates an integral image (http://en.wikipedia.org/wiki/Summed_area_table) from the _src_ buffer and returns the result in _dst_ buffer. Each _dst_ pixel respresents the sum of all _src_ pixels left of and above
*  the _dst_ pixel including the _src_ pixel 
*  
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 32 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int exec(       				DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                                DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */ );

}; /* class IntegralImage */

}  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
