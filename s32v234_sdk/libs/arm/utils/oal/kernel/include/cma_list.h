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
#ifndef _HEADERCMALIST_H
#define _HEADERCMALIST_H

#include <struct_defs.h>

/**
 * Operation OK flag
 */
#define CMA_OP_OK 1

/**
 * Operation error flag
 */
#define CMA_OP_ERROR -1

/*=============================================================================*/
/* Functions managing physical contiguous allocations                          */
/*=============================================================================*/

/**
 * Pushes the new area into managed physical allocations. 
 * Does not map into user space!
 * Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
 */
int cma_list_area_push_back(t_MemArea *area);

/**
 * Finds appropriate t_MemArea structure by physical address.
 * Returns pointer to this structure or NULL if not found.
 */
t_MemArea *cma_list_area_find(unsigned long addr);

/**
 * Removes a managed physical allocation from the list.
 * Successful only if there is no virtual map.
 * Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
 * Does not free *area pointer!
 */
int cma_list_area_remove(t_MemArea *area);

/**
 * Computes real size of the managed allocations (debug purposes)
 * Returns the size.
 */
unsigned long cma_list_area_compute_size(void);

/*=============================================================================*/
/* Functions managing virtual user mappings                                    */
/*=============================================================================*/

/**
 * Pushes a new virtual mapping into specific physical region.
 * Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
 */
int cma_list_user_push_back(t_MemArea *area, t_UserAddress *addr);

/**
 * Finds appropriate t_UserAddress by specified pid of the process.
 * Returns the pointer to the result or NULL.
 */
t_UserAddress * cma_list_user_find(t_MemArea *area, unsigned int pid);

/**
 * Finds appropriate t_MemArea by specified pid and virtual address.
 * Returns the pointer to the area or NULL.
 */
t_MemArea * cma_list_user_find_physical(unsigned int pid, unsigned long user_virtual);

/**
 * Removes user space mapping. 
 * Only owner of the mapping can free the mapping.
 * Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
 */
int cma_list_user_remove(t_MemArea *area, unsigned int pid, t_UserAddress **addr);

void cma_list_reset(void);
t_MemArea * cma_list_begin(void);


#endif