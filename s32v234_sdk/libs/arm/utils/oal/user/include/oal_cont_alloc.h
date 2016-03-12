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
#ifndef _HEADEROALCONTALLOC_H
#define _HEADEROALCONTALLOC_H

#include "global_errors.h"
#define NULL_ADDRESS 0

//#define DDR_PHYSICAL_POOL_BASE 0x50000000


void OAL_ContAllocDDRInit(unsigned long base, unsigned long size);
unsigned long OAL_ContAllocDDRGetBaseVirt();
void *OAL_ContAllocDDRAlloc(unsigned long size);
void OAL_ContAllocDDRFree(void * addr);

/**
 * Allocates physically contiguous region of specified size. 
 * Returns HW address of the allocated memory or NULL_ADDRESS if error.
 * HW address works like identification.
 */
unsigned long OAL_ContAllocAllocPhysical(unsigned long size);

/**
 * Frees physically contiguous region of specified size.
 * Returns true on success, false otherwise.
 * If mapping into user space exists, free function will fail. 
 * The unmap function must preceede.
 */
bool OAL_ContAllocFreePhysical(unsigned long kernel_physical);

/**
 * Returns HW addresses mapping into user space (i.e. user virtual address).
 * If mapping does not exist, it's created. returns address on success, NULL otherwise.
 */
void *OAL_ContAllocGetVirtual(unsigned long kernel_physical);

/**
 * Returns HW address from user space virtual address
 * If mapping does not exist, function returns NULL_ADDRESS.
 */
unsigned long OAL_ContAllocGetPhysical(void * user_virtual);

/**
 * Unmaps use space mapping of specified HW address for current process. 
 * Unmapping is possible only for current process. If other mapping exists, owner processes must free it.
 * Returns true on success, false otherwise.
 */
bool OAL_ContAllocUnmapVirtual(unsigned long kernel_physical);


#endif
