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
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/ioport.h>
#include <asm/io.h>

#include <oal_alloc.h>
#include <oal_mspace.h>

int 	oal_ddr_init = 0;
void *	oal_ddr_base_virt = 0;
mspace 	oal_ddr_space;


unsigned long OAL_ContAllocDDRGetBaseVirt()
{
  return (unsigned long) oal_ddr_base_virt;
}

void OAL_ContAllocDDRInit()
//void OAL_ContAllocDDRInit(unsigned long base, unsigned long size)
{
   oal_ddr_base_virt = ioremap(OAL_DDR_PHYSICAL_POOL_BASE, OAL_DDR_PHYSICAL_POOL_SIZE);
   oal_ddr_space = create_mspace_with_base(oal_ddr_base_virt, OAL_DDR_PHYSICAL_POOL_SIZE, 0);
   oal_ddr_init = 1;
}

void OAL_ContAllocDDRReset()
//void OAL_ContAllocDDRInit(unsigned long base, unsigned long size)
{
  if (oal_ddr_init == 1)
   oal_ddr_space = create_mspace_with_base(oal_ddr_base_virt, OAL_DDR_PHYSICAL_POOL_SIZE, 0);
}

void *OAL_ContAllocDDRAlloc(unsigned long size)
{
  if (oal_ddr_init == 0) return 0;
  
  return mspace_malloc(oal_ddr_space, size);
}

void OAL_ContAllocDDRFree(void * addr)
{
  if (oal_ddr_init == 0) return;
  mspace_free(oal_ddr_space, addr);
}