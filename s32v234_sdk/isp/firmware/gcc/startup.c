/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2015 Freescale Semiconductor;
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

#include "typedefs.h"

//***************************************************************************

extern unsigned int __bss_start__;
extern unsigned int __bss_end__;

extern unsigned int __CM0_0_STACK_ADDRESS;

extern void _reset(void);
extern void exception(void);

//***************************************************************************

void _done(void);

//***************************************************************************

__attribute__((section(".vectable"))) const uint32_t vecTab[16] __attribute__((used)) =
{
  (uint32_t)&__CM0_0_STACK_ADDRESS,	// #0 stack
  (uint32_t)_reset + 0x1,		// #1 reset
  (uint32_t)exception,			// #2 NMI
  (uint32_t)exception,			// #3 hard fault
  (uint32_t)_done,			// #4
  (uint32_t)_done,			// #5
  (uint32_t)_done,			// #6
  (uint32_t)_done,			// #7
  (uint32_t)_done,			// #8
  (uint32_t)_done,			// #9
  (uint32_t)_done,			// #a
  (uint32_t)_done,			// #b
  (uint32_t)_done,			// #c
  (uint32_t)_done,			// #d
  (uint32_t)_done,			// #e
  (uint32_t)_done			// #f
  
}; // vecTab[]

//***************************************************************************

void _comp_init(void)
{
  uint32_t* bss_begin = (uint32_t*)&__bss_start__;
  uint32_t* bss_end   = (uint32_t*)&__bss_end__;

  while(bss_begin <= bss_end)
  {
    *bss_begin = 0;
    bss_begin++;
  }
 
} // _comp_init()

//***************************************************************************

void _done(void)
{
  for(;;);
  
} // _done()

//***************************************************************************
