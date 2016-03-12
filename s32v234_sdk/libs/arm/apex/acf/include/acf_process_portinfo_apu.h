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
#ifndef _ACF_PROCESS_PORTINFO_APU_HPP
#define _ACF_PROCESS_PORTINFO_APU_HPP

#include <stdint.h>
#include <string.h>

class ACF_Process_PortInfo_APU
{
public:

   ACF_Process_PortInfo_APU(){}

   std::string mPortIdentifier;
   int8_t mCmemDmem;        //0=cmem, 1=dmem

   bool IsCmem()
   {
      if (mCmemDmem == 0) return true;
      else return false;
   }

   bool IsDmem()
   {
      if (mCmemDmem == 1) return true;
      else return false;
   }
};

#endif //_ACF_PROCESS_PORTINFO_APU_HPP

