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
#ifndef _HEADER_IOCTLFUNC
#define _HEADER_IOCTLFUNC

#include <ioctl_defs.h>

/**
 * Function allocates a contiguous memory block and add an item into management list.
 * Returns allocated HW address if success, 0 otherwise.
 */
unsigned long oal_alloc(unsigned long size);

/**
 * Function removes a contiguous memory block and removes an entry from the management list.
 * Returns 0 if success and ULONG_MAX if fail.
 * Does not free virtual mappings.
 */
unsigned long oal_free(unsigned long kernel_physical);

/**
 * Function returns a size of allocated memory block.
 */
unsigned long oal_getsize(unsigned long kernel_physical);

/**
 * Function returns a current process virtual memory mapping.
 */
unsigned long oal_getvirtual(unsigned long kernel_physical);

/**
 * Function returns a current process physical memory mapping.
 */
unsigned long oal_getphysical(unsigned long user_virtual);

/**
 * Function adds a new memory mapping into the management list (current process).
 */
unsigned long oal_map(t_MapStruct address);

/**
 * Function removes a memory mapping for current process.
 */
unsigned long oal_unmap(unsigned long kernel_physical);

void oal_reset(void);

#endif