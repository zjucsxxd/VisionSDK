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
*  \file apexcv_rgb888_to_yuv.hpp
*  \brief Host-ACF interface for rgb888 to yuv 
***********************************************************************************/

#ifndef _APEXCV_RGB888_TO_YUV_HPP_
#define _APEXCV_RGB888_TO_YUV_HPP_

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;

#include <RGB888_TO_YUV.hpp>

#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;

#include "rgb888_to_yuv_apu_process_desc.hpp"
REGISTER_PROCESS_TYPE(RGB888_TO_YUV, rgb888_to_yuv_apu_process_desc)

#endif


/*!*********************************************************************************
*  \brief Host-ACF interface for rgb888 to yuv.
*
*  This template class is an interface for creating, initializing, processing and releasing
*  the APU implementation of rgb888 to yuv on the host.
***********************************************************************************/
				 
class apexcv_rgb888_to_yuv
{
   public:
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
      apexcv_rgb888_to_yuv()  {};
   
/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/   
      ~apexcv_rgb888_to_yuv() {};
   
/*!*********************************************************************************
*  \brief Initialize the process.
*
*  \return Error code for the initialization (zero on success).
*
*  We initialize the process on the host by initializing the ACF process
*
***********************************************************************************/                     
      int Initialize( DataDescriptor& lInput0,
					  DataDescriptor& lOutput0 );
                       
/*!*********************************************************************************
*  \brief Release the process.
*
*  \return Error code for the release (zero on success).
***********************************************************************************/					  
      int Release();
   
/*!*********************************************************************************
*  \brief Execute the process.
*
*  \return Error code for the execution (zero on success).
*
***********************************************************************************/   
      int Process();

   private:
   
/*!*********************************************************************************
*  \brief Process declaration for rgb888 to yuv
***********************************************************************************/
      RGB888_TO_YUV mProcess;
};

#endif /* _APEXCV_RGB888_TO_YUV_HPP_ */
