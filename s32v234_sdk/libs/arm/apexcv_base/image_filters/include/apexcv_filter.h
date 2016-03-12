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
*  \file apexcv_filter.hpp
*  \brief Host-ACF interface for filter operations.
***********************************************************************************/

#ifndef _APEXCV_FILTER_HPP_
#define _APEXCV_FILTER_HPP_


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include "all_filter_graph_registrations.h"


/*!*********************************************************************************
*  \brief Host-ACF interface for filter operations.
*
*  This template class is an interface for creating, initializing, processing and releasing
*  the APU implementation of the filter kernels on the host.
***********************************************************************************/

template <class A>
class apexcv_filter
{
   public:
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
      apexcv_filter()  {};

/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/
      ~apexcv_filter() {};

/*!*********************************************************************************
*  \brief Initialize the process.
*
*  \return Error code for the initialization (zero on success).
*
*  We initialize the process on the host by initializing the ACF process
*  \snippet apexcv_filter.cpp initialize
*  and connecting the memory buffers to the ACF graph ports
*  \snippet apexcv_filter.cpp connect
***********************************************************************************/
      int Initialize( DataDescriptor& lInput0,
                      DataDescriptor& lOutput0,
                      DataDescriptor& sigmaR, 
					  DataDescriptor& sigmaD
					  /*DataDescriptor& r_lut,*/
					  /*DataDescriptor& d_lut*/);

      int Initialize_Scale( DataDescriptor& lInput0,
                            DataDescriptor& lOutput0,
                            DataDescriptor& lFilterCoeff,
                            DataDescriptor& lFilterScale );
                            
      int Initialize( DataDescriptor& lInput0,
                      DataDescriptor& lOutput0,
                      DataDescriptor& lFilterCoeff );

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
*  Execution consists of starting the ACF process
*  \snippet apexcv_filter.cpp start
*  and waiting for it to complete
*  \snippet apexcv_filter.cpp wait
***********************************************************************************/
      int Process();

   private:

/*!*********************************************************************************
*  \brief Process declaration for filter operations
***********************************************************************************/
      A mProcess;
};


#endif /* _APEXCV_FILTER_HPP_ */
