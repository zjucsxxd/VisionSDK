/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2013 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 *  Created by Jeff Lalonde <jlalonde@cognivue.com>
 ******************************************************************************/
/*!
* \file row_filter_impl.h
* \brief Row filter implementation for APU2.
* \addtogroup row_filter
* @{
****************************************************************************/

#ifndef _ROW_FILTER_IMPL_H_
#define _ROW_FILTER_IMPL_H_

#ifdef APEX2_EMULATE
#include "apu_lib.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

/* ! *********************************************************************************
*  Apply a row filter to an image.
***********************************************************************************/
void row_filter_impl(vec08u* dst       /*! Pointer to the destination image.*/,
                int dstStride     /*! Stride of the destination image.*/,
                const vec08u* src /*! Pointer to the source image.*/,
                int srcStride     /*! Stride of the source image.*/,
                int rows          /*! Rows of the source image, not including padding.*/,
                int cols          /*! Columns of the source image, not including padding.*/,
                const unsigned char* filter /*! Pointer to the row filter coefficients.  
                                                The coefficients are unsigned 8-bit fixed point numbers.*/,
                int filterSize    /*! Size of the column filter.*/,
                int filterQ       /*! Number of fractional bits for the filter coefficients.*/);
               
#endif   // ifndef _ROW_FILTER_IMPL_H_

/*! @} */