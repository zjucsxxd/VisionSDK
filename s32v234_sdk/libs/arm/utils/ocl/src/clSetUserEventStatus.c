#include "pocl_cl.h"
#include "utlist.h"

CL_API_ENTRY cl_int CL_API_CALL
POname(clSetUserEventStatus)(cl_event    event ,
                     cl_int      execution_status ) CL_API_SUFFIX__VERSION_1_1
{
  //POCL_ABORT_UNIMPLEMENTED();
  //return CL_SUCCESS;
  event_callback_item* cb_ptr;

  if((event->command_type != CL_COMMAND_USER) &&
     (event->status != CL_SUBMITTED))
    return CL_INVALID_EVENT;

  if(execution_status != CL_COMPLETE)
    return CL_INVALID_VALUE;
  else
    event->status = CL_COMPLETE;

  if(event->callback_list != NULL)
    {
      for (cb_ptr = event->callback_list; cb_ptr; cb_ptr = cb_ptr->next)
        {
          cb_ptr->callback_function (event, cb_ptr->trigger_status, 
                                     cb_ptr->user_data);
        }

      do
        {
          cb_ptr = event->callback_list;
          if(cb_ptr == NULL)
            break;
          
          POCL_LOCK_OBJ (event);
          LL_DELETE(event->callback_list, cb_ptr);
          POCL_UNLOCK_OBJ (event);
          POCL_FREE(cb_ptr);
          cb_ptr = (event_callback_item*)NULL;
        }
      while(1);
      //POname(clReleaseEvent) (event);
    }

            
  //POname(clFinish)(event->queue);
  
  return CL_SUCCESS;
}
POsym(clSetUserEventStatus)
