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
/**
* \file APU_ACF.h
* \brief APU ACF framework simulation
* \author Igor Aleksandrowicz
* \version
* \date 12-February-2014
****************************************************************************/

#ifndef _APU_ACF_H_
#define _APU_ACF_H_

#ifndef ACF_KERNEL_METADATA
#define ACF_KERNEL_METADATA
#endif

#ifndef ACF_KERNEL_IMPLEMENTATION
#define ACF_KERNEL_IMPLEMENTATION
#endif

#include "acf_process_desc_apu.hpp"
#include "stringify_macros.h"

namespace APEX2
{

//Within-system APEX processor ID. Doesn't really matter for the library, included for SDK compatibility.
  enum APEX_ID
  {
    APEX_APEX0,
    APEX_APEX1,
	APEX_APEX_BOTH
  };

  //syntax sugar macros
#define REGISTER_ACF_KERNEL(METADATA, FUNCTION) (ACF_Kernel::RegisterPrototypeInDatabase(ACF_Kernel((METADATA), (void*)(FUNCTION))));
#define XREGISTER_ACF_KERNEL(Kernel) REGISTER_ACF_KERNEL(kernelInfoConcat(Kernel), Kernel)

  //#define REGISTER_PROCESS_TYPE(NAME, DESC) typedef DESC NAME;
#define REGISTER_PROCESS_TYPE(NAME, DESC) class NAME : public DESC\
  {\
  public:\
    NAME(){};\
    NAME(APEX_ID id){};\
};

  void ACF_Init();
}

#endif // _APU_ACF_H_
