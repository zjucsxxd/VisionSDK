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

#ifndef __APEXCV_BASE_INTERPOL_HPP__
#define __APEXCV_BASE_INTERPOL_HPP__

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else 

#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#endif

namespace apexcv{

/*!*********************************************************************************
*  \brief Image interpolation class containing various interpolation methods
*
*  This class is an interface for using image interpolations on the host.
*  Interpolation windows that exceed the boundaries of the image use replicated 
*  pixels for the padding.
***********************************************************************************/
class Interpolation
{
public:

/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   Interpolation();

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~Interpolation();

/*!*********************************************************************************
*  \brief Linear Grayscale interpolation.
*
*  Applies linear interpolation to _src_. _deltaX_ represents the distance the 
*  resultant pixel was from the left adjacent pixel, normalized between 0-255. 
*
*  Supported window size is:
*     - 2 x 1
*
*  Supported image size is:
*     - Width: multiple of 2
*     - Height: any
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int linearGrayscale(       DataDescriptor&        src /*!< Source memory buffer. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. */,
                           DataDescriptor&     deltaX /*!< Delta X values for interpolation. */ );

                                 /*!*********************************************************************************
*  \brief Bilinear Grayscale interpolation.
*
*  Applies bilinear interpolation to _src_. _delta_ represents the distance the 
*  resultant pixel was from the left adjacent pixels and from the top adjacent
*  pixels <x, y>, normalized between 0-255. 
*
*  Supported window size is:
*     - 2 x 2
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int bilinearGrayscale(     DataDescriptor&        src /*!< Source memory buffer. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. */,
                           DataDescriptor&      delta /*!< Delta XY values for interpolation. */ );
         
/*!*********************************************************************************
*  \brief Bicubic Grayscale interpolation.
*
*  Applies bicubic interpolation to _src_. _x_offset_ represents the distance the 
*  resultant pixel was from the left adjacent pixel, this distance is determined as x_offset amount of increments
*  where each increment is of size 1/50*pixel width. _y_offset_ is the same as x_offset but in the y direction 
*
*  Supported window size is:
*     - 4 x 4
*
*  Supported datatypes are:
*     - unsigned 8 bit to unsigned 8 bit
*
*  \return Error code (zero on success).
***********************************************************************************/
int bicubicGrayscale(            DataDescriptor&        src /*!< Source memory buffer. */,
                                 DataDescriptor&        dst /*!< Destination memory buffer. */,
                                 DataDescriptor&      x_offset /*!< Delta XY values for interpolation. */,
                                 DataDescriptor&      y_offset /*!< Delta XY values for interpolation. */ );		 
}; /* class Interpolation */

}  /* namespace apex */
#endif /* __APEXCV_BASE_HPP__ */
