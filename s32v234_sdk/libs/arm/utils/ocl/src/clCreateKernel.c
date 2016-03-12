/* OpenCL runtime library: clCreateKernel()

   Copyright (c) 2011 Universidad Rey Juan Carlos and
                 2012 Pekka Jääskeläinen / Tampere Univ. of Technology
   
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

#include "pocl_cl.h"
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define COMMAND_LENGTH 1024

CL_API_ENTRY cl_kernel CL_API_CALL
POname(clCreateKernel)(cl_program program,
               const char *kernel_name,
               cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
  cl_kernel kernel;
  char device_tmpdir[POCL_FILENAME_LENGTH];
  int errcode;
  int error;
  int i;
  int device_i;

  if (kernel_name == NULL)
  {
    errcode = CL_INVALID_VALUE;
    goto ERROR;
  }
  
  if (program == NULL || program->num_devices == 0)
  {
    errcode = CL_INVALID_PROGRAM;
    goto ERROR;
  }

  if (program->binaries == NULL || program->binary_sizes == NULL)
  {
    errcode = CL_INVALID_PROGRAM_EXECUTABLE;
    goto ERROR;
  }

  kernel = (cl_kernel) malloc(sizeof(struct _cl_kernel));
  if (kernel == NULL)
  {
    errcode = CL_OUT_OF_HOST_MEMORY;
    goto ERROR;
  }

  POCL_INIT_OBJECT (kernel);

  kernel->function_name = (char *)NULL;
  kernel->name = (char *)NULL;
  
  kernel->device_data = malloc(sizeof(void *) * program->num_devices); //TODO: free
	
  for (device_i = 0; device_i < program->num_devices; ++device_i)
    {
      cl_device_id device = program->devices[device_i];
      if (device_i > 0)
        POname(clRetainKernel) (kernel);

      snprintf (device_tmpdir, POCL_FILENAME_LENGTH, "%s/%s", 
                program->temp_dir, program->devices[device_i]->short_name);

      if(device->ops->create_kernel != NULL) {
      //custom create kernel function
        kernel_metadata kmd;
        memset(&kmd, 0, sizeof(kernel_metadata));
        error = device->ops->create_kernel(kernel, program, kernel_name, device_tmpdir, &kmd, &kernel->device_data[device_i]);

        if(device_i == 0)
        {
          memcpy(&kernel->kmd, &kmd, sizeof(kernel_metadata));
        } else
        {
          if(!memcmp(&kernel->kmd, &kmd, sizeof(kernel_metadata)))
          {
            errcode = CL_INVALID_KERNEL_DEFINITION;
            goto ERROR_CLEAN_DEVICEDATA;
          }
        }
        //TODO: add error checking
      } else {
      
        /* If there is no device dir for this device, the program was
         not built for that device in clBuildProgram. This seems to
         be OK by the standard. */
#ifndef __APEX_OCL__         
        if (access (device_tmpdir, F_OK) != 0) continue;
        
        error = pocl_llvm_get_kernel_metadata 
            (program, kernel, device_i, kernel_name, 
             device_tmpdir, descriptor_filename, &errcode);

        if (error)
        {
          goto ERROR_CLEAN_KERNEL;
        } 
#endif        
      }
      /* when using the API, there is no descriptor file */
    }

  /* TODO: one of these two could be eliminated?  */
  kernel->function_name = strdup(kernel_name);
  kernel->name = strdup(kernel_name);

  kernel->context = program->context;
  kernel->program = program;
  kernel->next = NULL;

  //kernel->arg_info = (struct pocl_argument_info *) malloc (kernel->kmd.num_args * sizeof(struct pocl_argument_info));
  
  kernel->dyn_arguments =
    (struct pocl_argument *) malloc ((kernel->kmd.num_args + kernel->kmd.num_locals) *
     sizeof (struct pocl_argument));

  if (NULL == kernel->dyn_arguments)
  {
    errcode = CL_OUT_OF_HOST_MEMORY;
    goto ERROR_CLEAN_KERNEL;
  }

  kernel->reqd_wg_size = (int *) malloc (3*sizeof(int));
      
  if (NULL == kernel->reqd_wg_size)
  {
    errcode = CL_OUT_OF_HOST_MEMORY;
    goto ERROR_CLEAN_DYNARGS;
  }

  /* Initialize kernel "dynamic" arguments (in case the user doesn't). */
  /* CDG TODO: we need some way of setting the argument info. for now use defaults. */
  for (i = 0; i < kernel->kmd.num_args; ++i)
  {
    //kernel->arg_info[i].type = POCL_ARG_TYPE_POINTER;
    kernel->dyn_arguments[i].value = NULL;
    kernel->dyn_arguments[i].size = 0;
  }

  /* Initialize required workgroup size */
  for (i=0; i<3; i++)
     kernel->reqd_wg_size[i] = 0;

  /* Fill up automatic local arguments. */
  for (i = 0; i < kernel->kmd.num_locals; ++i)
  {
    kernel->dyn_arguments[kernel->kmd.num_args + i].value = NULL;
  }
        
  POCL_LOCK_OBJ (program);
  cl_kernel k = program->kernels;
  program->kernels = kernel;
  POCL_UNLOCK_OBJ (program);
  kernel->next = k;

  POCL_RETAIN_OBJECT(program);

  if (errcode_ret != NULL)
    *errcode_ret = CL_SUCCESS;
  return kernel;

ERROR_CLEAN_DYNARGS:
  POCL_FREE(kernel->dyn_arguments);
  kernel->dyn_arguments = NULL;
ERROR_CLEAN_DEVICEDATA:
  POCL_FREE(kernel->device_data);
  kernel->device_data = NULL;
ERROR_CLEAN_KERNEL:
  POCL_FREE(kernel);
ERROR:
  if(errcode_ret != NULL)
  {
    *errcode_ret = errcode;
  }
  return NULL;
}
POsym(clCreateKernel)
