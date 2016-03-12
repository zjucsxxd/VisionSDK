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
*  \file apexcv_arithmetic.hpp
*  \brief Host-ACF interface for arithmetic operations.
***********************************************************************************/

#ifndef _APEXCV_ARITHMETIC_HPP_
#define _APEXCV_ARITHMETIC_HPP_

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else 

#include "acf_data_descriptor.hpp" 
#include "acf_lib.hpp"
using namespace APEX2;

#endif

/*!*********************************************************************************
*  \brief Host-ACF interface for arithmetic operations.
*
*  This template class is an interface for creating, initializing, processing and releasing
*  the APU implementation of the arithmetic kernels on the host.
***********************************************************************************/

class ArithmBaseClass {
public:
	ArithmBaseClass(){};
	virtual ~ArithmBaseClass(){};
	virtual int Initialize(DataDescriptor& lInput0,
		DataDescriptor& lInput1,
		DataDescriptor& lAlpha,
		DataDescriptor& lOutput0) = 0;

	virtual int Initialize(DataDescriptor& lInput0,
		DataDescriptor& lInput1,
		DataDescriptor& lOutput0) = 0;

	virtual int Initialize(DataDescriptor& lInput0,
		DataDescriptor& lOutput0) = 0;

	/*!*********************************************************************************
	*  \brief Release the process.
	*
	*  \return Error code for the release (zero on success).
	***********************************************************************************/
	virtual int Release() = 0;

	/*!*********************************************************************************
	*  \brief Execute the process.
	*
	*  \return Error code for the execution (zero on success).
	*
	*  Execution consists of starting the ACF process
	*  \snippet apexcv_arithmetic.cpp start
	*  and waiting for it to complete
	*  \snippet apexcv_arithmetic.cpp wait
	***********************************************************************************/
	virtual int Process() = 0;
};

template <class A>					 
class apexcv_arithmetic : public ArithmBaseClass 
{
   public:
/*!*********************************************************************************
*  \brief Default constructor.
***********************************************************************************/
      apexcv_arithmetic()  {};
   
/*!*********************************************************************************
*  \brief Destructor.
***********************************************************************************/   
      ~apexcv_arithmetic() {};
   
/*!*********************************************************************************
*  \brief Initialize the process.
*
*  \return Error code for the initialization (zero on success).
*
*  We initialize the process on the host by initializing the ACF process
*  \snippet apexcv_arithmetic.cpp initialize
*  and connecting the memory buffers to the ACF graph ports
*  \snippet apexcv_arithmetic.cpp connect
***********************************************************************************/
      int Initialize( DataDescriptor& lInput0,
                      DataDescriptor& lInput1,
                      DataDescriptor& lAlpha,
                      DataDescriptor& lOutput0 );				
                      
      int Initialize( DataDescriptor& lInput0,
                      DataDescriptor& lInput1,
                      DataDescriptor& lOutput0 );
                      
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
*  \snippet apexcv_arithmetic.cpp start
*  and waiting for it to complete
*  \snippet apexcv_arithmetic.cpp wait
***********************************************************************************/   
      int Process();

   private:
   
/*!*********************************************************************************
*  \brief Process declaration for arithmetic operations
***********************************************************************************/
      A mProcess;
};

#endif /* _APEXCV_ARITHMETIC_HPP_ */
