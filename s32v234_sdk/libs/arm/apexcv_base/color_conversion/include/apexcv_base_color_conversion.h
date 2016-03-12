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
*  \brief Color converter class containing support for converting image color types
*
*  This class is an interface for using color conversion functions on the host.
***********************************************************************************/
class ColorConverter
{
public:
	
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
	ColorConverter();
	
/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
	~ColorConverter();
   
/*!*********************************************************************************
*  \brief List of conversion types
***********************************************************************************/
enum ConversionType {
   RGB565_TO_RGB888 /*!< 16 bit RGB565 to 32 bit representation of RGB888X */,
   RGB888_TO_RGB565 /*!< 32 bit representation of RGB888X to 16 bit RGB565 */,
   RGB888_TO_Y      /*!< 4-tuple 8 bit R, G, B, X to 8 bit Y */,
   RGB888_TO_YUV    /*!< 4-tuple 8 bit R, G, B, X to 4-tuple 8 bit Y, U, V, X */
};

/*!*********************************************************************************
*  \brief Convert function.
*
*  Converts an image from one type to another based on \ref ConversionType.
*
*  R2YFactor, G2YFactor and B2YFactor are Q0.8 fixed point values used with RGB888_TO_Y following the formula:
*  
*  \f$Y = \left \lfloor{\frac{R2YFactor}{256} * R + \frac{G2YFactor}{256} * G + \frac{B2YFactor}{256} * B + 0.5}\right \rfloor\f$
*
*  For example, conversion following Recommendation ITU-R BT.601-7 (http://www.itu.int/rec/R-REC-BT.601-7-201103-I/en) would use factor values of 77(0.299), 150(0.587) and 29(0.114).
*
*  \return Error code (zero on success).
***********************************************************************************/
int convert(               DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                           DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                           ConversionType              ct /*!< Color conversion type. See \ref ConversionType */,
                           int       		  R2YFactor = 0 /*!< Conversion factor for red used with RGB888_TO_Y */,
                           int        		  G2YFactor = 0 /*!< Conversion factor for green used with RGB888_TO_Y */,
                           int        		  B2YFactor = 0 /*!< Conversion factor for blue used with RGB888_TO_Y*/ );														 

}; /* class ColorConverter */

namespace OPT {
/*!*********************************************************************************
*  \brief Color converter class containing support for converting image color types
*
*  This class is an interface for using color conversion functions on the host.
***********************************************************************************/
class ColorConverter
{
public:
   
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
   ColorConverter();
   
/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
   ~ColorConverter();
   
/*!*********************************************************************************
*  \brief List of conversion types
***********************************************************************************/
enum ConversionType {
   HT_8UC3_TO_Y     /*!< 4-tuple 8 bit A, B, C, X to signed 16 bit Y */
};

/*!*********************************************************************************
*  \brief Convert function.
*
*  Converts an image from one type to another based on \ref ConversionType.
*
*  R2YFactor, G2YFactor and B2YFactor are Q0.8 fixed point values used with RGB888_TO_Y following the formula:
*  
*  \f$Y = \left \lfloor{\frac{R2YFactor}{256} * R + \frac{G2YFactor}{256} * G + \frac{B2YFactor}{256} * B + 0.5}\right \rfloor\f$
*
*  For example, conversion following Recommendation ITU-R BT.601-7 (http://www.itu.int/rec/R-REC-BT.601-7-201103-I/en) would use factor values of 77(0.299), 150(0.587) and 29(0.114).
*
*  \return Error code (zero on success).
***********************************************************************************/
int convert(                     DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                 DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                 ConversionType              ct /*!< Color conversion type. See \ref ConversionType */,
                                 int              R2YFactor = 0 /*!< Conversion factor for red channel */,
                                 int              G2YFactor = 0 /*!< Conversion factor for green channel */,
                                 int              B2YFactor = 0 /*!< Conversion factor for blue channel*/,
                                 int            ShiftFactor = 0 /*!< Shift factor. Used in HT_8UC3_TO_Y. */);                                         

}; /* class ColorConverter */
} // namespace OPT
} // namespace apexcv
#endif /* __APEXCV_BASE_HPP__ */
