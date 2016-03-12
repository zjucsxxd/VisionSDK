/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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
 
#ifndef _ICP_DATATYPE_H
#define _ICP_DATATYPE_H

#include <stdint.h>

/// \addtogroup icp_datatype ICP_DATATYPE
/// @{

/// ICP_DATATYPE - defines common base data formats.
typedef enum _ICP_DATATYPE
{
   ICP_DATATYPE_08U, ///<8-bit unsigned
   ICP_DATATYPE_08S, ///<8-bit signed
   ICP_DATATYPE_16U, ///<16-bit unsigned
   ICP_DATATYPE_16S, ///<16-bit signed
   ICP_DATATYPE_32U, ///<32-bit unsigned
   ICP_DATATYPE_32S  ///<32-bit signed
} ICP_DATATYPE;

/// @}

#ifdef __cplusplus
extern "C"
#endif
int32_t RetIcpDataTypeSizeInBytes(ICP_DATATYPE lDataType);

#endif //_ICP_DATATYPE_H
