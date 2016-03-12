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
#include <oal_cont_alloc.h>
#include <oal.h>

#define MSPACES 1
#include <standalone/oal_mspace.h>

#ifndef NULL
#define NULL 0
#endif

bool 	ddr_init = false;
void *	ddr_base_virt = NULL;
mspace 	ddr_space;


unsigned long OAL_ContAllocDDRGetBaseVirt()
{
  return (unsigned long) ddr_base_virt;
}

LIB_RESULT OAL_MemoryAllocInit()
//void OAL_ContAllocDDRInit(unsigned long base, unsigned long size)
{
   ddr_base_virt = (void *)OAL_DDR_PHYSICAL_POOL_BASE;
   ddr_space = create_mspace_with_base(ddr_base_virt, OAL_DDR_PHYSICAL_POOL_SIZE, 0);
   ddr_init = true;
   return LIB_SUCCESS;
}

void *OAL_ContAllocDDRAlloc(unsigned long size)
{
  if (!ddr_init) return NULL;
  return mspace_malloc(ddr_space, size);
}

void OAL_ContAllocDDRFree(void * addr)
{
  if (!ddr_init) return;
  mspace_free(ddr_space, addr);
  addr = 0;
}
