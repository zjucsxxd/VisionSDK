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

#include "opencv2/core/types_c.h"
#include "apexcv_core.h"

#include <stdint.h>

namespace apexcv{



	DATATYPE dd_from_cv_type(int cvT) {
		int cvTp = CV_MAT_DEPTH(cvT);
		switch (cvTp) {
		case CV_8U:
			return DATATYPE_08U;
		case CV_8S:
			return DATATYPE_08S;

		case CV_16U:
			return DATATYPE_16U;
		case CV_16S:
			return DATATYPE_16S;

		case CV_32S:
			return DATATYPE_32S;

		case CV_32F:
			return DATATYPE_32S;

		case CV_64F: // not implemented for APEX
		default:
			return (DATATYPE) -1;
		
		}
	}


	int cv_from_dd_type(DATATYPE ddT, int nrChann) {
		switch (ddT) {
		case DATATYPE_08U:
			return CV_MAKETYPE(CV_8U, nrChann);

		case DATATYPE_08S:
			return CV_MAKETYPE(CV_8S, nrChann);

		case DATATYPE_16U:
			return CV_MAKETYPE(CV_16U, nrChann);
		case DATATYPE_16S:
			return CV_MAKETYPE(CV_16S, nrChann);

		case DATATYPE_32S:
			return CV_MAKETYPE(CV_32S, nrChann);

		//case DATATYPE_32F:
			//return DATATYPE_32S;

		//case DATATYPE_64F: // not implemented for APEX
		default:
			return -1;

		}
	}



	template<>
	int cv_type<uint8_t>(int nrChannels);

	template<>
	int cv_type<uint16_t>(int nrChannels);
	
	template<>
	int cv_type<uint32_t>(int nrChannels);

	template<>
	int cv_type<int8_t>(int nrChannels);

	template<>
	int cv_type<int16_t>(int nrChannels);

	template<>
	int cv_type<int32_t>(int nrChannels);

	template<>
	DATATYPE get_datatype<uint8_t>();
	template<>
	DATATYPE get_datatype<uint16_t>();
	template<>
	DATATYPE get_datatype<uint32_t>();
	template<>
	DATATYPE get_datatype<int8_t>();

	template<>
	DATATYPE get_datatype<int16_t>();

	template<>
	DATATYPE get_datatype<int32_t>();


}  /* namespace apexcv */
