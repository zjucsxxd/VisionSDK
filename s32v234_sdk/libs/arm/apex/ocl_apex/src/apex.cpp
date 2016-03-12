/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/
 

#include <apex_apu_hal.h>
#include <apex_apu_microkernel_hal.h>
#include <apex_global_hal.h>
//#include <apex_hw_reg_user.h>
#include <kernel_manager.h>

#include "apex_acl.h"
#include "apu_ocl_struct.h"
#include "acl_krnl_manager.h"

#include "common.h"
#include "devices.h"

volatile int load_addr;

extern "C" {
#include "cpuinfo.h"
}

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//
#include <sys/time.h>
#include <sys/stat.h>

#include <dev_image.h>

#ifndef __APEX_OCL__
#include <dlfcn.h>

#endif

#define apuid     0
#define max(a,b) (((a) > (b)) ? (a) : (b))

#define COMMAND_LENGTH 2048
#define WORKGROUP_STRING_LENGTH 128

//TODO: shouldnt need to explicitly define alignment
#define ALIGNMENT 64 
//(max(ALIGNOF_FLOAT16, ALIGNOF_DOUBLE16)) 

struct data {
  /* Currently loaded kernel. */
  cl_kernel current_kernel;
  struct device_kernel *current_dev_kernel;
  /* Loaded kernel dynamic library handle. */
  void *current_dlhandle;
};

//XXX BDS
struct apex_data
{
    cl_kernel kernel;
    void *dlhandle;
    void (*kernhandle)(); //TODO: why hold this func when we have wgkernhandle?
    void (*wgkernhandle)();
};

#ifdef __cplusplus
extern "C" {
#endif

void
pocl_apex_init_device_ops(struct pocl_device_ops *ops)
{
  ops->device_name = "apex";

  ops->init_device_infos = pocl_apex_init_device_infos;
  ops->probe = pocl_apex_probe;
  ops->uninit = pocl_apex_uninit;
  ops->init = pocl_apex_init;
  ops->alloc_mem_obj = pocl_apex_alloc_mem_obj;
  ops->free = pocl_apex_free;
  ops->read = pocl_apex_read;
  ops->read_rect = pocl_apex_read_rect;
  ops->write = pocl_apex_write;
  ops->write_rect = pocl_apex_write_rect;
  ops->copy = pocl_apex_copy;
  ops->copy_rect = pocl_apex_copy_rect;
  ops->map_mem = pocl_apex_map_mem;
  ops->run = pocl_apex_run;
  ops->run_native = pocl_apex_run_native;
  ops->get_timer_value = pocl_apex_get_timer_value;
  ops->build_program = NULL;/*pocl_apex_build_program;*/
  ops->create_workgroup = pocl_apex_create_workgroup;
  ops->create_kernel = pocl_apex_create_kernel;
}


void
pocl_apex_init_device_infos(struct _cl_device_id* dev)
{
  dev->type = CL_DEVICE_TYPE_ACCELERATOR;
  dev->vendor_id = 0;
  dev->max_compute_units = 1;
  dev->max_work_item_dimensions = 3;
  dev->max_work_item_sizes[0] = CL_INT_MAX;
  dev->max_work_item_sizes[1] = CL_INT_MAX;
  dev->max_work_item_sizes[2] = CL_INT_MAX;
  dev->max_work_group_size = 64;
  dev->preferred_wg_size_multiple = 8;
  dev->preferred_vector_width_char = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_CHAR;
  dev->preferred_vector_width_short = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_SHORT;
  dev->preferred_vector_width_int = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_INT;
  dev->preferred_vector_width_long = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_LONG;
  dev->preferred_vector_width_float = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_FLOAT;
  dev->preferred_vector_width_double = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_DOUBLE;
  dev->preferred_vector_width_half = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_HALF;
  /* TODO: figure out what the difference between preferred and native widths are */
  dev->native_vector_width_char = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_CHAR;
  dev->native_vector_width_short = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_SHORT;
  dev->native_vector_width_int = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_INT;
  dev->native_vector_width_long = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_LONG;
  dev->native_vector_width_float = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_FLOAT;
  dev->native_vector_width_double = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_DOUBLE;
  dev->native_vector_width_half = POCL_DEVICES_PREFERRED_VECTOR_WIDTH_HALF;
  dev->max_clock_frequency = 0;
  dev->address_bits = 32;
  dev->max_mem_alloc_size = 134217728; //128MB
  dev->image_support = CL_FALSE;
  dev->max_read_image_args = 0;
  dev->max_write_image_args = 0;
  dev->image2d_max_width = 0;
  dev->image2d_max_height = 0;
  dev->image3d_max_width = 0;
  dev->image3d_max_height = 0;
  dev->image3d_max_depth = 0;
  dev->image_max_buffer_size = 0;
  dev->image_max_array_size = 0;
  dev->max_samplers = 0;
  dev->max_parameter_size = 1024;
  dev->mem_base_addr_align = 128;
  dev->min_data_type_align_size = 0;
  dev->half_fp_config = 0;
  dev->single_fp_config = CL_FP_ROUND_TO_NEAREST | CL_FP_INF_NAN;
  dev->double_fp_config = CL_FP_ROUND_TO_NEAREST | CL_FP_INF_NAN;
  dev->global_mem_cache_type = CL_NONE;
  dev->global_mem_cacheline_size = 0;
  dev->global_mem_cache_size = 0;
  dev->global_mem_size = 0;
  dev->max_constant_buffer_size = 0;
  dev->max_constant_args = 0;
  dev->local_mem_type = CL_LOCAL;
  dev->local_mem_size = 0;
  dev->error_correction_support = CL_FALSE;
  dev->host_unified_memory = CL_TRUE;
  dev->profiling_timer_resolution = 0;
  dev->endian_little = !(WORDS_BIGENDIAN);
  dev->available = CL_TRUE;
  dev->compiler_available = CL_FALSE;
  dev->execution_capabilities = CL_EXEC_KERNEL | CL_EXEC_NATIVE_KERNEL;
  dev->queue_properties = CL_QUEUE_PROFILING_ENABLE;
  dev->platform = 0;
  dev->device_partition_properties[0] = 0;
  dev->printf_buffer_size = 0;
  dev->short_name = "apex";
  dev->vendor = "CogniVue";
  dev->driver_version = PACKAGE_VERSION;
  dev->profile = "EMBEDDED_PROFILE";
  dev->version = "OpenCL 1.2";
  dev->extensions = "";
  dev->llvm_target_triplet = "armv7a-none-gnueabihf";
  dev->llvm_cpu = "cortex-a9";
  dev->has_64bit_long = 0;
}

unsigned int
pocl_apex_probe(struct pocl_device_ops *ops)
{
  int env_count = pocl_device_get_env_count(ops->device_name);

  /* No env specified, so pthread will be used instead of basic */
  if(env_count < 0)
    return 0;

  return env_count;
}


void
pocl_apex_init (cl_device_id device, const char* parameters)
{
  struct data *d;
  
  d = (struct data *) malloc (sizeof (struct data));
  
  d->current_kernel = NULL;
  d->current_dlhandle = 0;
  device->data = d;

  /* The apex driver represents only one "compute unit" as
     it doesn't exploit multiple hardware threads. Multiple
     apex devices can be still used for task level parallelism 
     using multiple OpenCL devices. */
  device->max_compute_units = 1;
  
  if(!strcmp(device->llvm_cpu, "(unknown)"))
    device->llvm_cpu = NULL;

  // work-around LLVM bug where sizeof(long)=4
  #ifdef _CL_DISABLE_LONG
  device->has_64bit_long=0;
  #endif
}

void *
pocl_apex_malloc (void *device_data, cl_mem_flags flags,
		    size_t size, void *host_ptr)
{
  void *b;
  //struct data* d = (struct data*)device_data;

  if (flags & CL_MEM_COPY_HOST_PTR)
    {
#ifndef __APEX_OCL__
      if (posix_memalign (&b, ALIGNMENT, size) == 0)
        {
          memcpy (b, host_ptr, size);
          return b;
        }
#else
      b = OAL_MemoryAllocFlag( size,
                               OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                               OAL_MEMORY_FLAG_CONTIGUOUS);
      if (b != NULL)
      {
         memcpy (b, host_ptr, size);
      }
      return b;
#endif

    }
  
  if (flags & CL_MEM_USE_HOST_PTR && host_ptr != NULL)
    {
      return host_ptr;
    }

  // if flags is anything else:
#ifdef __APEX_OCL__
  {
     b = OAL_MemoryAllocFlag( size,
                              OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                              OAL_MEMORY_FLAG_CONTIGUOUS);
    return b;
  }

#else
  if (posix_memalign (&b, ALIGNMENT, size) == 0)
  {
      assert(b); 
      return b;
  }
  return NULL;
#endif
}

cl_int
pocl_apex_alloc_mem_obj (cl_device_id device, cl_mem mem_obj)
{
  void *b = NULL;
  cl_int flags = mem_obj->flags;

  /* if memory for this global memory is not yet allocated -> do it */
  if (mem_obj->device_ptrs[device->global_mem_id].mem_ptr == NULL)
    {
      if (flags & CL_MEM_USE_HOST_PTR && mem_obj->mem_host_ptr != NULL)
        {
          b = mem_obj->mem_host_ptr;
        }
      else
        {
#ifdef __APEX_OCL__
          b = OAL_MemoryAllocFlag( mem_obj->size,
                              OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                              OAL_MEMORY_FLAG_CONTIGUOUS);
#else
          if (posix_memalign (&b, MAX_EXTENDED_ALIGNMENT, 
                               mem_obj->size) != 0)
            return CL_MEM_OBJECT_ALLOCATION_FAILURE;
#endif  
        }        

      if (flags & CL_MEM_COPY_HOST_PTR)
        memcpy (b, mem_obj->mem_host_ptr, mem_obj->size);
    
      mem_obj->device_ptrs[device->global_mem_id].mem_ptr = b;
      }
  /* copy already allocated global mem info to devices own slot */
  mem_obj->device_ptrs[device->dev_id] = 
    mem_obj->device_ptrs[device->global_mem_id];
    
  return CL_SUCCESS;
}

void
pocl_apex_free (void *data, cl_mem_flags flags, void *ptr)
{

  if (flags & CL_MEM_USE_HOST_PTR)
    return;
  
#ifdef __APEX_OCL__
  if (flags & CL_MEM_COPY_HOST_PTR)
  {
     if (ptr != (void *)NULL)
     {
        OAL_MemoryFree (ptr);
        ptr = NULL;
     }
    return;
  }
#endif

  if (ptr != (void *)NULL)
  {
    OAL_MemoryFree (ptr);
    ptr = NULL;
  }
}

void
pocl_apex_read (void *data, void *host_ptr, const void *device_ptr, size_t cb)
{
  if (host_ptr == device_ptr)
    return;

  memcpy (host_ptr, device_ptr, cb);
}

void
pocl_apex_write (void *data, const void *host_ptr, void *device_ptr, size_t cb)
{
  if (host_ptr == device_ptr)
    return;

  memcpy (device_ptr, host_ptr, cb);
}

void
pocl_apex_run_native 
(void *data, 
 _cl_command_node* cmd)
{
  (*cmd->command.native.user_func)((void*)cmd->command.native.args);
}

volatile uint32_t lDmem;
volatile uint32_t lLoad_Segment = 0;
acl_krnl_manager acl_km;


int
pocl_apex_load_binary
(void *data, size_t bin_size, void *binary, const char *options,char *dev_tmpdir)
{
   /*
    char bin_filenm[POCL_FILENAME_LENGTH]; //TODO: build from source
    FILE *bin_file;
    int err = 0;
    snprintf(bin_filenm, POCL_FILENAME_LENGTH, "%s/%s", dev_tmpdir, "bin.so");
    memcpy(bin_hack, bin_filenm, POCL_FILENAME_LENGTH); //TODO: tmp
    bin_file = fopen(bin_filenm, "wb+");
    if(!bin_file) return -1;
    fwrite(binary, 1, bin_size, bin_file);
    fclose(bin_file);
    */
   load_addr = *((int32_t*)binary);
   int32_t msg;

   if (lLoad_Segment != load_addr)
   {
      //ensure CMEM interface is configured as expected
      switch (global_hal_RetHwVersion(0))
      {
         case 0x321: cmem_if_hal_set_apu_cfg(0, CFG_321__APU_0_CU_0_31_SMEM_0_1); break;
         case 0x642: cmem_if_hal_set_apu_cfg(0, CFG_642__APU_0_CU_0_63_SMEM_0_3); break;
      }

      // DISABLE
      apu_hal_Enable(0, apuid, 0);
      // LOAD
      apu_hal_LoadSegment(0, apuid, (const LOAD_SEGMENT_t*)load_addr);
      // ENABLE
      apu_hal_Enable(0, apuid, 1);
      // IPC
      apumk_hal_host_com_rx(0, apuid, (int32_t*)&msg);

      lLoad_Segment = load_addr;
   }
   return 0;
}

void
pocl_apex_run 
(void *data, _cl_command_node* cmd)
{
  struct data *d;
  //int error;
  int32_t rval = 0;
  //char bytecode[POCL_FILENAME_LENGTH];
  //char assembly[POCL_FILENAME_LENGTH];
  //char module[POCL_FILENAME_LENGTH];
  //char command[COMMAND_LENGTH];
  //char workgroup_string[WORKGROUP_STRING_LENGTH];
  unsigned device_i;
  struct pocl_argument *al;
  //size_t x, y, z;
  unsigned i;
  //pocl_workgroup w;
  //char* tmpdir = cmd->command.run.tmp_dir;
  cl_kernel kernel = cmd->command.run.kernel;
  struct pocl_context *pc = &cmd->command.run.pc;
  cl_device_id device;
  //int error;

  assert (data != NULL);
  d = (struct data *) data;

  d->current_kernel = kernel;

  /* Find which device number within the context correspond
     to current device.  */ //TODO: this seems like it can be improved at the datastructure level
  for (i = 0; i < kernel->context->num_devices; ++i)
    {
      if (kernel->context->devices[i]->data == data)
        {
          device_i = i;
          break;
        }
    }

  device = kernel->program->devices[device_i];
  pocl_apex_load_binary(device->data,
                        kernel->program->binary_sizes[device_i],
                        kernel->program->binaries[device_i], 
                        NULL,
                        NULL);

  //w=(pocl_workgroup)(((struct apex_data*)dev_kernel_data)->wgkernhandle);
  
  //void *arguments[kernel->kmd.num_args + kernel->kmd.num_locals];
  void *arguments[MAX_KERNEL_ARGS];

  //TODO: improve all below to allow for parallel Apex impl

  // Process the kernel arguments. Convert the opaque buffer
  //   pointers to real device pointers, allocate dynamic local 
  //   memory buffers, etc. 
  for (i = 0; i < kernel->kmd.num_args; ++i)
    {
      al = &(cmd->command.run.arguments[i]);
      if (kernel->kmd.arg_is_local[i])
        {
         /*
          arguments[i] = malloc (sizeof (void *));
          *(void **)(arguments[i]) = pocl_apex_malloc(data, 0, al->size, NULL);
          */
        }
      else if (kernel->kmd.arg_is_pointer[i])
        {
          // It's legal to pass a NULL pointer to clSetKernelArguments. In 
          // that case we must pass the same NULL forward to the kernel.
          // Otherwise, the user must have created a buffer with per device
          // pointers stored in the cl_mem.
          if (al->value == NULL)
            arguments[i] = NULL;
          else
            arguments[i] = &((*(cl_mem *) (al->value))->device_ptrs[device_i]);
        }
      else if (kernel->kmd.arg_is_image[i])
        {
          dev_image_t di;      
          cl_mem mem = *(cl_mem*)al->value;
          di.data = &((*(cl_mem *) (al->value))->device_ptrs[device_i]);
          di.width = mem->image_width;
          di.height = mem->image_height;
          di.row_pitch = mem->image_row_pitch;
          di.order = mem->image_channel_order;
          di.data_type = mem->image_channel_data_type;
          void* devptr = pocl_apex_malloc(data, 0, sizeof(dev_image_t), NULL);
          arguments[i] = malloc (sizeof (void *));
          *(void **)(arguments[i]) = devptr; 
          pocl_apex_write (data, &di, devptr, sizeof(dev_image_t));
        }
      else if (kernel->kmd.arg_is_sampler[i])
        {
          dev_sampler_t ds;
          
          arguments[i] = malloc (sizeof (void *));
          *(void **)(arguments[i]) = pocl_apex_malloc(data, 0, sizeof(dev_sampler_t), NULL);
          pocl_apex_write (data, &ds, *(void**)arguments[i], sizeof(dev_sampler_t));
        }
      else
        {
          arguments[i] = al->value;
        }
    }

  int32_t   params[64] = {0};
  int32_t   cnt = 0;

  // kernel metadata
  //   required work group size
  /*
  params[cnt++] = kernel->kmd.reqd_wg_size[0];
  params[cnt++] = kernel->kmd.reqd_wg_size[1];
  params[cnt++] = kernel->kmd.reqd_wg_size[2];
  */

  // kernel id
  int kid   = kernel->kmd.kid;
  // kernel number of arguments
  int nargs = acl_km.mkernel_list[kid].krnl_md.num_args;
  int smem  = (int32_t)0x74000000;


  //---------------------------------------------------
  params[cnt++] = smem;
  //printf("params[%d] = smem(%d)\n", (cnt-1), smem);
  // start push into the list
  // kernel mode
  params[cnt++] = nargs;
  //printf("params[%d] = nargs(%d)\n", (cnt-1), nargs);

  int mode = acl_km.mkernel_list[kid].krnl_md.krnl_mode;
  params[cnt++] = mode;
  //printf("params[%d] = mode(%d)\n", (cnt-1), mode);


  // NEED
  // argument address qualifier type
  for (size_t i=0; i<nargs; i++)
  {
     params[cnt++] = acl_km.mkernel_list[kid].krnl_md.args_type[i];
     //printf("params[%d] = acl_km.mkernel_list[%d].krnl_md.args_type[%d](%d)\n", (cnt-1), kid, i, acl_km.mkernel_list[kid].krnl_md.args_type[i]);
  }

  for (size_t i=0; i<nargs; i++)
  {
     params[cnt++] = acl_km.mkernel_list[kid].krnl_md.args_rw[i];
     //printf("params[%d] = acl_km.mkernel_list[%d].krnl_md.args_rw[%d](%d)\n", (cnt-1), kid, i, acl_km.mkernel_list[kid].krnl_md.args_rw[i]);
  }

  params[cnt++] = (int32_t)(int64_t)acl_km.mkernel_list[kid].krnl_md.krnl_ctx;
  //printf("params[%d] = acl_km.mkernel_list[%d].krnl_md.krnl_ctx(%d)\n", (cnt-1), kid, (int32_t)acl_km.mkernel_list[kid].krnl_md.krnl_ctx);


  // NEED
  // kernel wrapper id
  params[cnt++] = acl_km.mkernel_list[kid].krnl_md.krnl_addr;
  //printf("params[%d] = acl_km.mkernel_list[%d].krnl_md.krnl_addr(%d)\n", (cnt-1), kid, acl_km.mkernel_list[kid].krnl_md.krnl_addr);
  params[cnt++] = acl_km.mkernel_list[kid].krnl_md.krnl_setarg;
  //printf("params[%d] = acl_km.mkernel_list[%d].krnl_md.krnl_setarg(%d)\n", (cnt-1), kid, acl_km.mkernel_list[kid].krnl_md.krnl_setarg);  


  // pocl_context
  params[cnt++]   = pc->work_dim;
  //printf("params[%d] = pc->work_dim(%d)\n", (cnt-1), pc->work_dim);

  for (i=0; i<pc->work_dim; i++)
  {
     params[cnt++] = pc->local_size[i];
     //printf("params[%d] = pc->local_size[%d](%d)\n", (cnt-1), i, pc->local_size[i]);
  }

  for (i=0; i<pc->work_dim; i++)
  {
     params[cnt++] = pc->num_groups[i];
     //printf("params[%d] = pc->num_groups[%d](%d)\n", (cnt-1), i, pc->num_groups[i]);
  }
    
  for (i=0; i<pc->work_dim; i++)
  {
     params[cnt++] = pc->global_offset[i];
     //printf("params[%d] = pc->global_offset[%d](%d)\n", (cnt-1), i, pc->global_offset[i]);
  }
  for (i=0; i<pc->work_dim; i++)
  {
     params[cnt++] = pc->global_size[i];
     //printf("params[%d] = pc->global_size[%d](%d)\n", (cnt-1), i, pc->global_size[i]);
  }
#if 0
  //   dynamic argument type
  for (i = 0; i < kernel->kmd.num_args; ++i)
  {
      if (kernel->kmd.arg_is_local[i])
      {
         params[cnt++] = arg_is_local;
      }
      else if (kernel->arg_info[i].type == POCL_ARG_TYPE_POINTER)
      {
         params[cnt++] = arg_is_global;
      }
  }
#endif

  // dynamic argument content:
  //   global  size and ptr value
  for (i = 0; i <nargs; ++i)
  {
     al = &(cmd->command.run.arguments[i]);

      //if (kernel->kmd.arg_is_pointer[i])
      if (acl_km.mkernel_list[kid].krnl_md.args_type[i] == arg_is_global)
      {
         cl_mem mem = (*(cl_mem *) (al->value));
         params[cnt++] = mem->size;
         //printf("params[%d] = mem->size(%d)\n", (cnt-1), mem->size);
         // Retrieve OAL memory handle
         void* a = (void*)(mem->device_ptrs[device_i].mem_ptr);
         // Retrieve phy memory addr
         void* b = OAL_MemoryReturnAddress(a, ACCESS_PHY);
         // Retrieve phy memory addr
         void* c = OAL_MemoryReturnAddress(a, ACCESS_NCH_NB);
         OAL_MemoryFlushAndInvalidate(a, mem->size);
         params[cnt++] = (int32_t)(int64_t)b;
         //printf("params[%d] = b(%d)\n", (cnt-1), (int32_t)b);
         //printf("a: %d\n", ((uint32_t*)a)[2048]);
      }
  }
  // dynamic argument content:
  //   local size and 0 pointer
  for (i = 0; i < nargs; ++i)
  {
     al = &(cmd->command.run.arguments[i]);
      //if (kernel->kmd.arg_is_local[i])
     if (acl_km.mkernel_list[kid].krnl_md.args_type[i] == arg_is_local)
      {
         params[cnt++] = al->size;//mem->size;
         //printf("params[%d] = al->size(%d)\n", (cnt-1), al->size);
         params[cnt++] = 0;
         //printf("params[%d] = 0\n", (cnt-1));
      }

  }

  // dynamic argument content:
  //   value
  for (i = 0; i < nargs; ++i)
  {
     al = &(cmd->command.run.arguments[i]);
      //if (kernel->kmd.arg_is_local[i])
     if (acl_km.mkernel_list[kid].krnl_md.args_type[i] == arg_is_value)
      {
         params[cnt++] = al->size;//mem->size;
         //printf("params[%d] = al->size(%d)\n", (cnt-1), al->size);
         params[cnt++] = (int32_t)(*(int32_t *)(al->value));
         //printf("params[%d] = (int32_t)(*(int32_t *)(al->value))(%d)\n", (cnt-1), (int32_t)(*(int32_t *)(al->value)));
      }

  }

  
  // kernel wrapper addr
#if 0
  KernelManager km;
  km.InitLoadKernelDB(apuid, (const LOAD_SEGMENT_t*)load_addr);
  int32_t kernel_addr  = 0;
  rval  = km.ReturnKernelID((int*)&kernel_addr, kernel->name);

  if (rval != 0)
  {
     printf("[APU OCL] Kernel not found in the load!\n");
  }
  // add it to parameter list
  params[cnt++] = kernel_addr;
#endif

  lDmem = (uint32_t)0x74000000;

#if 0
   // local memory allocation
  for (i = kernel->kmd.num_args;
       i < kernel->kmd.num_args + kernel->kmd.num_locals;
       ++i)
    {
      al = &(cmd->command.run.arguments[i]);
      arguments[i] = malloc (sizeof (void *));
      *(void **)(arguments[i]) = pocl_apex_malloc(data, 0, al->size, NULL);
    }

  //TODO: parallelize this step, and reset to 'num_groups' once parallelized
  int32_t beg;
  int32_t apu_info   = 0;

  if (lLoad_Segment != load_addr)
  {
     // DISABLE
     apu_hal_Enable(0, apuid, 0);
     // LOAD
     apu_hal_LoadSegment(0, apuid, (const LOAD_SEGMENT_t*)load_addr);
     // ENABLE
     apu_hal_Enable(0, apuid, 1);
     // IPC
     apumk_hal_host_com_rx(0, apuid, (int32_t*)&beg);

     lLoad_Segment = load_addr;
  }
#endif
 // DEBUG_printf("APU: enabled  (%08X)\n", beg);
  //

  // apu ocl main entry (never change)

  KernelManager km;
  km.InitLoadKernelDB(apuid, (const LOAD_SEGMENT_t*)load_addr);

  int32_t apu_ocl_main_addr  = 0;
  rval = 0;
  rval = km.ReturnKernelID((int*)&apu_ocl_main_addr, "apu_ocl_main");
  if (rval != 0)
  {
     printf("[APU OCL] Kernel not found in the load!\n");
  }

  int32_t apu_info   = 0;
  apumk_hal_send_cmd(0, 0, //apu id
                     apu_ocl_main_addr,
                     cnt,
                     params);
  apumk_hal_host_com_tx(0, apuid, HOST_MSG_SENDCMD);
  apumk_hal_host_com_rx(0, apuid, (int32_t*)&apu_info);
  //printf("APU MESSAGE: (%08X) [SEND CMD 0 DONE]\n\n", apu_info);

#if 0
  for (z = 0; z < pc->num_groups[2]; ++z)
    {
      for (y = 0; y < pc->num_groups[1]; ++y)
        {
          for (x = 0; x < pc->num_groups[0]; ++x)
            {
              pc->group_id[0] = x;
              pc->group_id[1] = y;
              pc->group_id[2] = z;

              //w (arguments, pc);
              //_dot_product_workgroup (arguments, pc);

            }
        }
    }
#endif

  for (i = 0; i < kernel->kmd.num_args; ++i)
    {
     /*
      if (kernel->kmd.arg_is_local[i])
      {
        pocl_apex_free(data, 0, *(void **)(arguments[i]));
      }
      */
    }
  for (i = kernel->kmd.num_args;
       i < kernel->kmd.num_args + kernel->kmd.num_locals;
       ++i)
    pocl_apex_free(data, 0, *(void **)(arguments[i]));
   
}

void
pocl_apex_copy (void *data, const void *src_ptr, void *__restrict__ dst_ptr, size_t cb)
{
  if (src_ptr == dst_ptr)
    return;
  
  memcpy (dst_ptr, src_ptr, cb);
}

void
pocl_apex_copy_rect (void *data,
                      const void *__restrict const src_ptr,
                      void *__restrict__ const dst_ptr,
                      const size_t *__restrict__ const src_origin,
                      const size_t *__restrict__ const dst_origin, 
                      const size_t *__restrict__ const region,
                      size_t const src_row_pitch,
                      size_t const src_slice_pitch,
                      size_t const dst_row_pitch,
                      size_t const dst_slice_pitch)
{
  char const *__restrict const adjusted_src_ptr = 
    (char const*)src_ptr +
    src_origin[0] + src_row_pitch * (src_origin[1] + src_slice_pitch * src_origin[2]);
  char *__restrict__ const adjusted_dst_ptr = 
    (char*)dst_ptr +
    dst_origin[0] + dst_row_pitch * (dst_origin[1] + dst_slice_pitch * dst_origin[2]);
  
  size_t j, k;

  /* TODO: handle overlaping regions */
  
  for (k = 0; k < region[2]; ++k)
    for (j = 0; j < region[1]; ++j)
      memcpy (adjusted_dst_ptr + dst_row_pitch * j + dst_slice_pitch * k,
              adjusted_src_ptr + src_row_pitch * j + src_slice_pitch * k,
              region[0]);
}

void
pocl_apex_write_rect (void *data,
                       const void *__restrict__ const host_ptr,
                       void *__restrict__ const device_ptr,
                       const size_t *__restrict__ const buffer_origin,
                       const size_t *__restrict__ const host_origin, 
                       const size_t *__restrict__ const region,
                       size_t const buffer_row_pitch,
                       size_t const buffer_slice_pitch,
                       size_t const host_row_pitch,
                       size_t const host_slice_pitch)
{
  char *__restrict const adjusted_device_ptr = 
    (char*)device_ptr +
    buffer_origin[0] + buffer_row_pitch * (buffer_origin[1] + buffer_slice_pitch * buffer_origin[2]);
  char const *__restrict__ const adjusted_host_ptr = 
    (char const*)host_ptr +
    host_origin[0] + host_row_pitch * (host_origin[1] + host_slice_pitch * host_origin[2]);
  
  size_t j, k;

  /* TODO: handle overlaping regions */
  
  for (k = 0; k < region[2]; ++k)
    for (j = 0; j < region[1]; ++j)
      memcpy (adjusted_device_ptr + buffer_row_pitch * j + buffer_slice_pitch * k,
              adjusted_host_ptr + host_row_pitch * j + host_slice_pitch * k,
              region[0]);
}

void
pocl_apex_read_rect (void *data,
                      void *__restrict__ const host_ptr,
                      void *__restrict__ const device_ptr,
                      const size_t *__restrict__ const buffer_origin,
                      const size_t *__restrict__ const host_origin, 
                      const size_t *__restrict__ const region,
                      size_t const buffer_row_pitch,
                      size_t const buffer_slice_pitch,
                      size_t const host_row_pitch,
                      size_t const host_slice_pitch)
{
  char const *__restrict const adjusted_device_ptr = 
    (char const*)device_ptr +
    buffer_origin[0] + buffer_row_pitch * (buffer_origin[1] + buffer_slice_pitch * buffer_origin[2]);
  char *__restrict__ const adjusted_host_ptr = 
    (char*)host_ptr +
    host_origin[0] + host_row_pitch * (host_origin[1] + host_slice_pitch * host_origin[2]);
  
  size_t j, k;
  
  /* TODO: handle overlaping regions */
  
  for (k = 0; k < region[2]; ++k)
    for (j = 0; j < region[1]; ++j)
      memcpy (adjusted_host_ptr + host_row_pitch * j + host_slice_pitch * k,
              adjusted_device_ptr + buffer_row_pitch * j + buffer_slice_pitch * k,
              region[0]);
}


void *
pocl_apex_map_mem (void *data, void *buf_ptr, 
                      size_t offset, size_t size,
                      void *host_ptr) 
{
  /* All global pointers of the pthread/CPU device are in 
     the host address space already, and up to date. */
  if (host_ptr != NULL) return host_ptr;
  return buf_ptr + offset;
}

void
pocl_apex_uninit (cl_device_id device)
{
  struct data *d = (struct data*)device->data;
  free (d);
  device->data = NULL;

  // DISABLE
  apu_hal_Enable(0, apuid, 0);
}

cl_ulong
pocl_apex_get_timer_value (void *data) 
{
  struct timeval current;
  gettimeofday(&current, NULL);  
  return (current.tv_sec * 1000000 + current.tv_usec)*1000;
}

///////////////////////// 

/*
struct apex_data
{
    cl_kernel kernel;
    void *dlhandle;
    void (*kernhandle)();
};*/

//static char bin_hack[POCL_FILENAME_LENGTH]; //TODO: tmp

int
pocl_apex_build_program
(void *data, size_t bin_size, void *binary, const char *options, char *dev_tmpdir)
{
   return pocl_apex_load_binary(data, bin_size,binary, options, dev_tmpdir);
}

int
pocl_apex_create_workgroup(void *data, char *default_cmd, char *wg_tmpdir)
{
   int rval = 0;
   return rval;
}



int
pocl_apex_create_kernel
(cl_kernel kernel, cl_program program, const char *kernel_name, char *kern_tmpdir, kernel_metadata *out_kmd, void **out_dev_kernel_data)
{
    //kernel->device_kernels[device_i].dlsymha
    struct apex_data *data = (apex_data*)malloc(sizeof(struct apex_data));
    *out_dev_kernel_data = data;
    data->kernel = kernel;

#ifdef __APEX_OCL__
    // TBD
    // Opencl kernel metadata loader
    //kernel_metadata *kmd = (kernel_metadata*)example_metadata;
    int kernel_id = 0;
    unsigned int** pos     = (unsigned int**)program->binaries;
    unsigned int  bin_addr = (*pos)[0];
    acl_km.init(0, (const LOAD_SEGMENT_t*)bin_addr);
    acl_km.ret_id(&kernel_id, kernel_name);
    out_kmd->num_args = acl_km.ret_nargs(kernel_id);
    out_kmd->kid      = kernel_id;
    
#else
    char bin_filenm[POCL_FILENAME_LENGTH];
    char kernel_full_name[POCL_FILENAME_LENGTH]; //TODO: not a filename
    snprintf(kernel_full_name, POCL_FILENAME_LENGTH, "_%s", kernel_name);
    data->dlhandle = dlopen(bin_hack, RTLD_NOW);
    assert(data->dlhandle != NULL);
    data->kernhandle = dlsym(data->dlhandle, kernel_full_name);
    assert(data->kernhandle != NULL);
    snprintf(kernel_full_name, POCL_FILENAME_LENGTH, "_%s_workgroup", kernel_name);
    data->wgkernhandle = dlsym(data->dlhandle, kernel_full_name);
    assert(data->wgkernhandle);

    char kmdname[POCL_FILENAME_LENGTH]; //TODO: I know its not a filename...
    snprintf(kmdname, POCL_FILENAME_LENGTH, "_%s_metadata", kernel_name);
    kernel_metadata *kmd = dlsym(data->dlhandle, kmdname);
    assert(kmd != NULL);
    memcpy(out_kmd, kmd, sizeof(kernel_metadata));
#endif

    return 0;
}


#ifdef __cplusplus
}
#endif

