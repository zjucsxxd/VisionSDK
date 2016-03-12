/* OpenCL runtime library: clSetKernelArg()

   Copyright (c) 2011 Universidad Rey Juan Carlos
                 2013 Pekka Jääskeläinen / Tampere University of Technology
   
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "config.h"
#include "pocl_cl.h"
#include "pocl_util.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

CL_API_ENTRY cl_int CL_API_CALL
POname(clSetKernelArg)(cl_kernel kernel,
               cl_uint arg_index,
               size_t arg_size,
               const void *arg_value) CL_API_SUFFIX__VERSION_1_0
{
  struct pocl_argument *p;
  void *value;
  
  if (kernel == NULL)
    return CL_INVALID_KERNEL;

  if (arg_index >= kernel->kmd.num_args)
    return CL_INVALID_ARG_INDEX;
  
  if (kernel->dyn_arguments == NULL)
    return CL_INVALID_KERNEL;

  if (arg_size == 0 && kernel->kmd.arg_is_local[arg_index])
    return CL_INVALID_ARG_SIZE;

  if ((kernel->kmd.arg_is_pointer[arg_index] || kernel->kmd.arg_is_image[arg_index])
        && (!kernel->kmd.arg_is_local[arg_index]) && (arg_size != sizeof(cl_mem)))
    return CL_INVALID_ARG_SIZE;

  p = &(kernel->dyn_arguments[arg_index]); 
  POCL_LOCK_OBJ (kernel);
  //kernel->arg_info[arg_index].is_set = 0;

  if (arg_value != NULL && 
      !(kernel->kmd.arg_is_pointer[arg_index] && 
        *(const int*)arg_value == 0))
    {
      POCL_FREE (p->value);

      value = malloc (arg_size);
      if (value == NULL)
      {
         POCL_UNLOCK_OBJ (kernel);
         return CL_OUT_OF_HOST_MEMORY;
      }
      memset (value, 0, arg_size);
      memcpy (value, arg_value, arg_size);
   
      p->value = value;
    }
  else
    {
      //pocl_aligned_free (p->value);
      POCL_FREE (p->value); // TEMP modified
      p->value = NULL;
    }

#if 0
  printf(
      "### clSetKernelArg for %s arg %d (size %u) set to %x points to %x\n", 
      kernel->name, arg_index, arg_size, p->value, *(int*)arg_value);
#endif

  p->size = arg_size;
  //kernel->arg_info[arg_index].is_set = 1;

  POCL_UNLOCK_OBJ (kernel);
  return CL_SUCCESS;
}
POsym(clSetKernelArg)
