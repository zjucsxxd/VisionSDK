#include "pocl_cl.h"
#include <pocl_mem_management.h>

CL_API_ENTRY cl_event CL_API_CALL
POname(clCreateUserEvent)(cl_context     context ,
                  cl_int *       errcode_ret ) CL_API_SUFFIX__VERSION_1_1 
{
  //POCL_ABORT_UNIMPLEMENTED();
  //return CL_SUCCESS;


  cl_event event;// = NULL;
  *errcode_ret = CL_SUCCESS;

  event = pocl_mem_manager_new_event();
  if (event == NULL)
  {
    *errcode_ret = CL_OUT_OF_HOST_MEMORY;
    return NULL;
  }
  
      
  event->queue = NULL;
  event->command_type = CL_COMMAND_USER;
  event->callback_list = NULL;
  event->implicit_event = 0;
  event->next = NULL;
  event->status = CL_SUBMITTED;

  return event;

}
POsym(clCreateUserEvent)
