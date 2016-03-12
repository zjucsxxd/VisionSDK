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
#include <cma_list.h>

#include <linux/vmalloc.h>
#include <linux/slab.h>

//////////////////////////////////////////////////////////////////////////////////
// Static variables
//////////////////////////////////////////////////////////////////////////////////

// CMA allocations list
t_MemArea *cma_list_allocations = NULL;

// CMA allocations back list
t_MemArea *cma_list_allocations_end = NULL;

// CMA allocations size
unsigned long cma_list_allocations_size = 0;

//////////////////////////////////////////////////////////////////////////////////
// Pushes the new area into managed physical allocations. 
// Does not map into user space!
// Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
//////////////////////////////////////////////////////////////////////////////////
int cma_list_area_push_back(t_MemArea *area)
{
  // If this is the first item in list
  if (cma_list_allocations_end == NULL) 
  {
    // Allocate a new space
    cma_list_allocations = area;//(t_MemArea *)vmalloc(sizeof(t_MemArea));
    if (cma_list_allocations == NULL) return CMA_OP_ERROR;
    
    // Save the input value
    //*cma_list_allocations = area;
    //cma_list_allocations->user_addresses = area.user_addresses;
    //cma_list_allocations->kernel_physical = area.kernel_physical;
    //cma_list_allocations->kernel_virtual = area.kernel_virtual;
    //cma_list_allocations->size = area.size;
  
    
    // Initialize neighbors to null
    cma_list_allocations_end = area;
    area->next = NULL;
    area->prev = NULL;
  }
  // If this is second and more item
  else
  {
    // Allocate a new space
    cma_list_allocations_end->next = area;//(t_MemArea *)vmalloc(sizeof(t_MemArea));
    if (cma_list_allocations_end->next == NULL) return CMA_OP_ERROR;
    
    // Save the input value
    cma_list_allocations_end->next = area;
    
    // Link neighbors to it
    cma_list_allocations_end->next->prev = cma_list_allocations_end;
    cma_list_allocations_end = cma_list_allocations_end->next;
    cma_list_allocations_end->next = NULL;
  }
  
  // At least, increment item counter and exit
  ++cma_list_allocations_size;
  return CMA_OP_OK;
}

//////////////////////////////////////////////////////////////////////////////////
// Finds appropriate t_MemArea structure by physical address.
// Returns pointer to this structure or NULL if not found.
//////////////////////////////////////////////////////////////////////////////////
t_MemArea * cma_list_area_find(unsigned long addr)
{
  // Go through the whole structure and search for the addr as kernel HW address
  t_MemArea *aux = cma_list_allocations;
  while (aux != NULL)
  {
    if (aux->kernel_physical == addr)
      return aux;
    aux = aux->next;
  }
  
  return NULL;
}

t_MemArea * cma_list_begin()
{
  // Go through the whole structure and search for the addr as kernel HW address
  return cma_list_allocations;
}
//////////////////////////////////////////////////////////////////////////////////
// Computes real size of the managed allocations (debug purposes)
// Returns the size.
//////////////////////////////////////////////////////////////////////////////////
unsigned long   cma_list_area_compute_size()
{
  // Go through the whole structure and count the number of items
  unsigned long size = 0;
  t_MemArea *aux = cma_list_allocations;
  while (aux != NULL)
  {
    ++size;
    aux = aux->next;
  }
  
  return size;
}

//////////////////////////////////////////////////////////////////////////////////
// Removes a managed physical allocation from the list.
// Successful only if there is no virtual map.
// Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
// Does not free *area pointer!
//////////////////////////////////////////////////////////////////////////////////
int cma_list_area_remove(t_MemArea *area)
{  
  // If area does not exist, bail out
  if (area == NULL) return CMA_OP_ERROR;
     
  // Check if there is no mapping with user space
  if (area->user_addresses == NULL) 
  {
    // Unlink the area from others
    if (area->prev != NULL)
      area->prev->next = area->next;
    if (area->next != NULL)
      area->next->prev = area->prev;
    if (area == cma_list_allocations)
      cma_list_allocations = area->next;
    if (area == cma_list_allocations_end)
      cma_list_allocations_end = area->prev;
    
    // Decrement the counter
    --cma_list_allocations_size;
    
    return CMA_OP_OK;
  }
  // Some mapping exists, bail out
  else
  {
    return CMA_OP_ERROR;
  }
  
}

//////////////////////////////////////////////////////////////////////////////////
// Pushes a new virtual mapping into specific physical region.
// Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
//////////////////////////////////////////////////////////////////////////////////
int cma_list_user_push_back(t_MemArea *area, t_UserAddress *addr)
{
  //t_UserAddress *aux;
  // Check if the parent exists
  if (area == NULL) return CMA_OP_ERROR;
  
  // Alloc a new address
  //aux = (t_UserAddress *)vmalloc(sizeof(t_UserAddress));
  if (addr == NULL) return CMA_OP_ERROR;
  
  // Save current data
  //*aux = addr;
  
  // If this is a first item, initialize all values.
  if (area->user_addresses == NULL) 
  {
    area->user_addresses = addr;    
    area->user_addresses->next = NULL;
    area->user_addresses->prev = NULL;
  }
  // If there is already something, push it in front of it and link pointers.
  else
  {
    addr->next = area->user_addresses;
    addr->prev = NULL;
    addr->next->prev = addr;
    area->user_addresses = addr;
  }
  return CMA_OP_OK;
}

//////////////////////////////////////////////////////////////////////////////////
// Finds appropriate t_UserAddress by specified pid of the process.
// Returns the pointer to the result or NULL.
//////////////////////////////////////////////////////////////////////////////////
t_UserAddress * cma_list_user_find(t_MemArea *area, unsigned int pid)
{
  // Go through the whole structure and search for the virtual mapping by pid
  t_UserAddress *aux = area->user_addresses;
  while (aux != NULL)
  {
    if (aux->pid == pid)
      return aux;
    aux = aux->next;
  }
  return NULL;
}

t_MemArea * cma_list_user_find_physical(unsigned int pid, unsigned long user_virtual)
{
  // Go through the whole structure and search for the addr as kernel HW address
  t_MemArea *aux = cma_list_allocations;
  while (aux != NULL)
  {
    t_UserAddress *user = aux->user_addresses;
    while (user != NULL)
    {
      printk("%lu\n", user->user_virtual);
      if (user->pid == pid && user->user_virtual == user_virtual)
	return aux;
      user = user->next;
    }
    aux = aux->next;
  }
  
  return NULL;
}

void cma_list_reset()
{
  // Go through the whole structure and search for the addr as kernel HW address
  t_MemArea *aux = cma_list_allocations;
  t_MemArea *next;
  while (aux != NULL)
  {
    t_UserAddress *addr = aux->user_addresses;
    t_UserAddress *addrnext;
    next = aux->next;
    while (addr != NULL)
    {
      addrnext = addr->next;
      vfree(addr);
      addr = addrnext;
    }
    vfree(aux);
    aux = next;
  }
  
  cma_list_allocations = NULL;
  cma_list_allocations_end = NULL;
  cma_list_allocations_size = 0;
  
  return;
}

//////////////////////////////////////////////////////////////////////////////////
// Removes user space mapping. 
// Only owner of the mapping can free the mapping.
// Returns CMA_OP_OK on success, CMA_OP_ERROR otherwise.
//////////////////////////////////////////////////////////////////////////////////
int cma_list_user_remove(t_MemArea *area, unsigned int pid, t_UserAddress **addr)
{
  // Check if area exists.
  if (area == NULL) return CMA_OP_ERROR;
     
  // If some mapping exists, continue
  if (area->user_addresses != NULL) 
  {
    // Find the appropriate structure of the mapping.
    *addr = cma_list_user_find(area, pid);
    if (!(*addr)) return CMA_OP_ERROR;
    
    // Unlink it
    if ((*addr)->prev != NULL)
      (*addr)->prev->next = (*addr)->next;
    if ((*addr)->next != NULL)
      (*addr)->next->prev = (*addr)->prev;
    if ((*addr) == area->user_addresses)
      area->user_addresses = (*addr)->next;
        
    // Free memory
    //vfree(addr);
    return CMA_OP_OK;
  }
  else
  {
    return CMA_OP_ERROR;
  }
}