/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/

 
/*!*********************************************************************************
*  \file
*  \brief APEX-CV Base Library
***********************************************************************************/

#ifndef __APEXCV_CORE_HPP__
#define __APEXCV_CORE_HPP__

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "acf_data_descriptor.hpp"
using namespace APEX2;
#endif

#include "opencv2/core/types_c.h"

namespace apexcv{

	
	template<typename X, typename Y>
	struct is_same
	{
		static const bool value = false;
	};

	template<typename X>
	struct is_same < X, X >
	{
		static const bool value = true;
	};

	
	template <typename D>
	DATATYPE get_datatype()
	{
		if (is_same<D, uint8_t>::value)
			return DATATYPE_08U;
		else if (is_same<D, uint16_t>::value)
			return DATATYPE_16U;
		else if (is_same<D, uint32_t>::value)
			return DATATYPE_32U;
		else if (is_same<D, int8_t>::value)
			return DATATYPE_08S;
		else if (is_same<D, int16_t>::value)
			return DATATYPE_16S;
		else if (is_same<D, int32_t>::value)
			return DATATYPE_32S;
		else
			return (DATATYPE)-1;
	}

	template <typename D>
	int cv_type(int nrChannels)
	{
		if (is_same<D, uint8_t>::value)
			return CV_8UC(nrChannels);

		else if (is_same<D, uint16_t>::value)
			return CV_16UC(nrChannels);

		else if (is_same<D, uint32_t>::value)
			return CV_32SC(nrChannels);

		else if (is_same<D, int8_t>::value)
			return CV_8SC(nrChannels);

		else if (is_same<D, int16_t>::value)
			return CV_16SC(nrChannels);

		else if (is_same<D, int32_t>::value)
			return CV_32SC(nrChannels);

		else if (is_same<D, float>::value)
			return CV_32FC(nrChannels);

		else if (is_same<D, double>::value)
			return CV_64FC(nrChannels);

		else
			return -1;
	}

	int cv_from_dd_type(DATATYPE ddT, int nrChann = 1);
	
	DATATYPE dd_from_cv_type(int cvT);

}  /* namespace apexcv */
#endif /* __APEXCV_BASE_HPP__ */
