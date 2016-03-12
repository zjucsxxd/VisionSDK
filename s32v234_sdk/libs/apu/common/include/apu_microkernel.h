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

#ifndef _APU_MICROKERNEL_H_
#define _APU_MICROKERNEL_H_

#include "stdint.h"

//////////////////////////////////////////////////
//            KERNEL RELATED
//////////////////////////////////////////////////
// RESERVED MEMORY SIZE
// 32 bytes per entry
#define APU_DMEM_KERNEL_DB_ENTRY       32


// KERNEL REGISTRATION
#define REGISTERED_FUNC   7
typedef int (*myFunct)(int * const, int const);

typedef struct
{
   int32_t kernel_addr;       // IMEM ADDR: MAX (0x8000)
   char    kernel_name[28];
} KERNEL_INFO;



#endif /* _APU_MICROKERNEL_H_ */
