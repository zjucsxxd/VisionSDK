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
/**
 * @file apexdriver_apu.c
 *
 * \\author Rostislav Hulik (Freescale Semiconductor)
 * \date 28. 11. 2013
 *
 */

#include <apexdriver_regmap.h>
#include <functions/apexdriver_global.h>
#include <functions/apexdriver_apu.h>
#include <functions/apexdriver_reset.h>
#include <apexdriver_trace.h>
#ifdef __STANDALONE__
  #include <string.h>
#endif // ifdef __STANDALONE__
/*======================================================================================*/
/* DMEM offset for multiple APUs (helper variable)					*/
uint32_t dmem_offset [] = {
  DMEM_APU0_OFFSET,	// APU 0
  DMEM_APU1_OFFSET	// APU 1
};

/*======================================================================================*/
/* IMEM offset for multiple APUs (helper variable)					*/
uint32_t imem_offset [] = {
  IMEM_APU0_OFFSET,	// APU 0
  IMEM_APU1_OFFSET	// APU 1
};

/*======================================================================================*/
/* VMEM offset for multiple APUs (helper variable)					*/
uint32_t vmem_offset [] = {
  VMEM_APU0_OFFSET,	// APU 0
  VMEM_APU1_OFFSET	// APU 1
};

/*======================================================================================*/
/* SMEM structure pointers (helper variable)						*/
typedef struct
{
  volatile uint32_t *imem;
  volatile uint32_t *dmem;
  volatile uint32_t *vmem;
} APEXDRIVER_SMEM;

/*======================================================================================*/
/* Function loads a program into SMEM for a specified APUs				*/
/*======================================================================================*/
void apexdriver_load_program 	(uint32_t apex_id, uint32_t apu_id, const APEXDRIVER_LOAD_PROGRAM* program)
{
  int32_t i, n;
  volatile APEXDRIVER_SMEM address0;
  volatile APEXDRIVER_SMEM address1;
  int32_t memtype;
  
  APEXDRIVER_TRACE_PRINT("APEXDRIVER_LOAD_PROGRAM APEXID: %d\n", apex_id)
  /* Disable and reset APU */
  apexdriver_disable_apu(apex_id, apu_id);
  apexdriver_reset_apu(apex_id, apu_id);

  switch (apex_id)
  {
// APEX 0 case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX0:
      /* Compute SMEM mappings for specified APU */
      address0.imem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ imem_offset[apu_id];
      address0.dmem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ dmem_offset[apu_id];
      address0.vmem = apexdriver_get_virtual_ptr(APEX_1_REG_GOC) 	+ vmem_offset[apu_id];
      
#if (CLEAR_VMEM == 1)
      {
        volatile int* cmem = 0;
        int i = 0;
        cmem = (volatile int*)apexdriver_get_virtual_ptr(APEX_1_REG_BOC63_00);
		for (i = 0; i < VMEM_SIZE_32; ++i)
		{
          cmem[4*i+0] = 0;
          cmem[4*i+1] = 0;
          cmem[4*i+2] = 0;
          cmem[4*i+3] = 0;
		}
      }
#endif
#if (CLEAR_DMEM == 1)
      {
		int i;
		for (i = 0; i < DMEM_SIZE_32; ++i)
		{
          address0.dmem[i] = 0;
		}
      }
#endif

      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr = 0;
		
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
		int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
	
        uint32_t size32 = (program[n].size >> 2);
  
	switch (memtype)
	{
	  case 0:
	    dst_addr = (volatile int32_t *)(address0.imem + (program[n].dst_offset>>2));
	    break;
	  case 1:
	    dst_addr = (volatile int32_t *)(address0.dmem + (program[n].dst_offset>>2));
	    break;
	  case 2:
	    dst_addr = (volatile int32_t *)(address0.vmem + (program[n].dst_offset>>2));
	    break;
	  default:
	    dst_addr = 0;
	    break;
	}
       	

        /* If the source is not zero (it's used), save it into destination */
    
        if (src_ptr != 0)
		{
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
			  for (i = 0; i < size32; ++i)
        {
          dst_addr[i] = src_ptr[i]; 
        }
		  }
		}
  
        memtype = program[++n].memtype;
      }
      break;
      
// APEX 1 case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX1:
      /* Compute SMEM mappings for specified APU */
      address0.imem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ imem_offset[apu_id];
      address0.dmem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ dmem_offset[apu_id];
      address0.vmem = apexdriver_get_virtual_ptr(APEX_2_REG_GOC) 	+ vmem_offset[apu_id];
      
#if (CLEAR_VMEM == 1)
      {
        volatile int* cmem = 0;
        int i = 0;
        cmem = (volatile int*)apexdriver_get_virtual_ptr(APEX_2_REG_BOC63_00);
		for (i = 0; i < VMEM_SIZE_32; ++i)
		{
          cmem[4*i+0] = 0;
          cmem[4*i+1] = 0;
          cmem[4*i+2] = 0;
          cmem[4*i+3] = 0;
		}
      }
#endif
#if (CLEAR_DMEM == 1)
      {
		int i;
        for (i = 0; i < DMEM_SIZE_32; ++i)
		{
          address0.dmem[i] = 0;
		}
      }
#endif

      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr = 0;
		
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
		int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
	
        uint32_t size32 = (program[n].size >> 2);
  
	switch (memtype)
	{
	  case 0:
	    dst_addr = (volatile int32_t *)(address0.imem + (program[n].dst_offset>>2));
	    break;
	  case 1:
	    dst_addr = (volatile int32_t *)(address0.dmem + (program[n].dst_offset>>2));
	    break;
	  case 2:
	    dst_addr = (volatile int32_t *)(address0.vmem + (program[n].dst_offset>>2));
	    break;
	  default:
	    dst_addr = 0;
	    break;
	}
       	

        /* If the source is not zero (it's used), save it into destination */
    
        if (src_ptr != 0)
		{
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
        for (i = 0; i < size32; ++i)
        {
          dst_addr[i] = src_ptr[i]; 
        }
		  }
		}
  
        memtype = program[++n].memtype;
      }
      break;

// APEX BOTH case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX_BOTH:
      /* Compute SMEM mappings for specified APU */
      address0.imem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ imem_offset[apu_id];
      address0.dmem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ dmem_offset[apu_id];
      address0.vmem = apexdriver_get_virtual_ptr(APEX_1_REG_GOC) 	+ vmem_offset[apu_id];
      address1.imem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ imem_offset[apu_id];
      address1.dmem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ dmem_offset[apu_id];
      address1.vmem = apexdriver_get_virtual_ptr(APEX_2_REG_GOC) 	+ vmem_offset[apu_id];
      
#if (CLEAR_VMEM == 1)
      {
        volatile int* cmem0 = 0;
		volatile int* cmem1 = 0;
        cmem0 = (volatile int*)apexdriver_get_virtual_ptr(APEX_1_REG_BOC63_00);
		cmem1 = (volatile int*)apexdriver_get_virtual_ptr(APEX_2_REG_BOC63_00);
		for (i = 0; i < VMEM_SIZE_32; ++i)
		{
          cmem0[4*i+0] = 0;
          cmem0[4*i+1] = 0;
          cmem0[4*i+2] = 0;
          cmem0[4*i+3] = 0;
		  cmem1[4*i+0] = 0;
          cmem1[4*i+1] = 0;
          cmem1[4*i+2] = 0;
          cmem1[4*i+3] = 0;
		}
      }
#endif
#if (CLEAR_DMEM == 1)
      {
        int i;
        for (i = 0; i < DMEM_SIZE_32; ++i)
		{
          address0.dmem[i] = 0;
		  address1.dmem[i] = 0;
		}
      }
#endif
      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr0 = 0;
	volatile int32_t* dst_addr1 = 0;
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
		int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
        uint32_t size32 = (program[n].size >> 2);
  
	switch (memtype)
	{
	  case 0:
	    dst_addr0 = (volatile int32_t *)(address0.imem + (program[n].dst_offset>>2));
	    dst_addr1 = (volatile int32_t *)(address1.imem + (program[n].dst_offset>>2));
	    break;
	  case 1:
	    dst_addr0 = (volatile int32_t *)(address0.dmem + (program[n].dst_offset>>2));
	    dst_addr1 = (volatile int32_t *)(address1.dmem + (program[n].dst_offset>>2));
	    break;
	  case 2:
	    dst_addr0 = (volatile int32_t *)(address0.vmem + (program[n].dst_offset>>2));
	    dst_addr1 = (volatile int32_t *)(address1.vmem + (program[n].dst_offset>>2));
	    break;
	  default:
	    dst_addr0 = 0;
	    break;
	}

    if (src_ptr != 0)
		{
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
        for (i = 0; i < size32; ++i)
        {
          dst_addr0[i] = src_ptr[i];
          dst_addr1[i] = src_ptr[i]; 
        }
		  }
		}
	    
  
        memtype = program[++n].memtype;
      }
      break;
      
    default:
      address0.imem = 0;
      address0.dmem = 0;
      address0.vmem = 0;
      break;
  }

  
}

void apexdriver_load_data (uint32_t apex_id, uint32_t apu_id, const APEXDRIVER_LOAD_PROGRAM* program)
{
  int32_t i, n;
  volatile APEXDRIVER_SMEM address0;
  volatile APEXDRIVER_SMEM address1;
  int32_t memtype;
  
  APEXDRIVER_TRACE_PRINT("APEXDRIVER_LOAD_DATA APEXID: %d\n", apex_id)
  /* Disable and reset APU */
  apexdriver_disable_apu(apex_id, apu_id);
  apexdriver_reset_apu(apex_id, apu_id);

  switch (apex_id)
  {
// APEX 0 case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX0:
      /* Compute SMEM mappings for specified APU */      
      address0.dmem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ dmem_offset[apu_id];
      
#if (CLEAR_DMEM == 1)
      {
        for (i = 0; i < DMEM_SIZE_32; ++i)
	{
          address0.dmem[i] = 0;
	  APEXDRIVER_TRACE_SET(APEX_1_REG_SMEM, dmem_offset[apu_id] + i*4, 0)
	}
      }
  #endif
  
      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr = 0;
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
	int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
	
        uint32_t size32 = (program[n].size >> 2);
  
	if (memtype == 1)
	    dst_addr = (volatile int32_t *)(address0.dmem + (program[n].dst_offset>>2));
	else
	    dst_addr = 0;
       	

        /* If the source is not zero (it's used), save it into destination */
    
        if (src_ptr != 0 && dst_addr != 0)
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
            for (i = 0; i < size32; ++i)
	    {
              dst_addr[i] = src_ptr[i];
	      }
	    }
  
        memtype = program[++n].memtype;
      }
      break;
      
// APEX 1 case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX1:
      /* Compute SMEM mappings for specified APU */
      address0.dmem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ dmem_offset[apu_id];
      
#if (CLEAR_DMEM == 1)
      {
        for (i = 0; i < DMEM_SIZE_32; ++i)
	{
          address0.dmem[i] = 0;
	  APEXDRIVER_TRACE_SET(APEX_2_REG_SMEM, dmem_offset[apu_id] + i*4, 0)
	}
      }
  #endif
      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr = 0;
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
	int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
        uint32_t size32 = (program[n].size >> 2);
  
       	if (memtype == 1)
	    dst_addr = (volatile int32_t *)(address0.dmem + (program[n].dst_offset>>2));
	else
	    dst_addr = 0;

        /* If the source is not zero (it's used), save it into destination */
    
        if (src_ptr != 0 && dst_addr != 0)
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
            for (i = 0; i < size32; ++i)
	    {
              dst_addr[i] = src_ptr[i];
	    }
          }
  
        memtype = program[++n].memtype;
      }
      break;

// APEX BOTH case
//////////////////////////////////////////////////////////////////////////////////////////////      
    case APEX_APEX_BOTH:
      /* Compute SMEM mappings for specified APU */
      address0.dmem = apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) 	+ dmem_offset[apu_id];
      address1.dmem = apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) 	+ dmem_offset[apu_id];
      

#if (CLEAR_DMEM == 1)
      {
        for (i = 0; i < DMEM_SIZE_32; ++i)
	{
          address0.dmem[i] = 0;
	  address1.dmem[i] = 0;
	  
	  APEXDRIVER_TRACE_SET(APEX_1_REG_SMEM, dmem_offset[apu_id] + i*4, 0)
	  APEXDRIVER_TRACE_SET(APEX_2_REG_SMEM, dmem_offset[apu_id] + i*4, 0)
	}
      }
  #endif
      /* Load program data into memory */
      n = 0;
      memtype = program[n].memtype;
  
      /* While reading the data */
      while (memtype != -1)
      {
        volatile int32_t* dst_addr0 = 0;
	volatile int32_t* dst_addr1 = 0;
#ifdef __ARMV8
        int32_t* src_ptr = (int32_t *)program[n].src_ptr;
#else
	int32_t* src_ptr = (int32_t *)(int32_t)program[n].src_ptr;
#endif
        uint32_t size32 = (program[n].size >> 2);
  
	if (memtype == 1)
	{
	    dst_addr0 = (volatile int32_t *)(address0.imem + (program[n].dst_offset>>2));
	    dst_addr1 = (volatile int32_t *)(address1.imem + (program[n].dst_offset>>2));
	}
	else
	{
	    dst_addr0 = 0;
	    dst_addr1 = 0;
	}

        /* If the source is not zero (it's used), save it into destination */
    
        if (src_ptr != 0 && dst_addr0 != 0)
          if(((program[n].dst_offset < DMEM_SIZE) && (memtype == 1) ) || (memtype == 0) || (memtype == 2))
          {
            for (i = 0; i < size32; ++i)
	    {
              dst_addr0[i] = src_ptr[i];
	      dst_addr1[i] = src_ptr[i];
	    }
	  }
	    
  
        memtype = program[++n].memtype;
      }
      break;
      
    default:
      address0.imem = 0;
      address0.dmem = 0;
      address0.vmem = 0;
      break;
  }

  
}
  
int32_t apexdriver_query_program(uint32_t apex_id, uint32_t apu_id, const APEXDRIVER_LOAD_PROGRAM* program,
			       int32_t* dmem_addr, int32_t* dmem_size,
			       const int32_t dmem_min_size,
                               int32_t* cmem_addr, int32_t* cmem_size,
			       const int32_t cmem_min_size)
{
  
  int32_t rval = 0;
  int32_t dmem_end = 0;
  int32_t cmem_end = 0;
  int32_t num_cu   = 0;
  
  uint32_t lHwVersion = 0;
  if (apex_id == APEX_APEX_BOTH) lHwVersion = apexdriver_global_get_hw_version(APEX_APEX0);
  else lHwVersion = apexdriver_global_get_hw_version(apex_id);
   
  switch(lHwVersion)
  {
  case 0x321:
	dmem_end = 0x8000;
	cmem_end = 0x1000;
	num_cu   = 128;
    break;
  case 0x642:
	dmem_end = 0x8000;
	cmem_end = 0x1000;
	num_cu   = 128; //32 because of how 'sizes' are calculated in ACLOAD
    break;
  default:
    rval = 1;
   }
   
  int32_t memtype;
  int32_t n          = 0;
  int32_t cmem_found = cmem_min_size;
  int32_t dmem_found = dmem_min_size;  

   // Load program and data memory
   dmem_addr[0]   = 0;
   cmem_addr[0]   = 0;

   // start loop
   memtype = program[n].memtype;
   
   while (memtype != -1)
   {
     int32_t dst_size = program[n].size;
     int32_t dst_offset  = program[n].dst_offset;
     int32_t next_offset = 0;

     if (memtype == 1)
     {
       int32_t size;
       next_offset = (program[n+1].dst_offset == 0x10800)?(dmem_end):program[n+1].dst_offset;
       size = (next_offset - dst_offset - dst_size);

         if (size > dmem_found)
         {
            dmem_addr[0] = dst_offset + dst_size;
            dmem_found   = size;
         }
      }
      else if (memtype == 2)
      {
	int32_t size;
        next_offset = (program[n+1].memtype == -1)?(cmem_end):program[n+1].dst_offset;
	dst_size = dst_size/num_cu;
        size = (next_offset - dst_offset - dst_size);

        if (size >= cmem_found)
        {
          cmem_addr[0] = dst_offset + dst_size;
          cmem_found =  size;
        }
      }

      memtype = program[++n].memtype;
   }

   if ((dmem_found >= dmem_min_size) && (cmem_found >= cmem_min_size))
   {
	dmem_size[0] = dmem_found;
	cmem_size[0] = cmem_found;
   }
   else rval = -1;
   //printf("aaa2\n");
   return rval;
}

/*======================================================================================*/
/* Active wait helper function								*/
/*======================================================================================*/
void apexdriver_com_wait(int32_t count)
{
   static int32_t l = 0;
   for (; count>0; --count) { ++l;}
}

/*======================================================================================*/
/* Wait for APU message and signal the reception					*/
/*======================================================================================*/
uint32_t  apexdriver_host_com_rx  	(uint32_t apex_id, uint32_t apu_id, uint32_t* msg)
{
  volatile int32_t* shared0 = 0;
  volatile int32_t* shared1 = 0;
   
  APEXDRIVER_TRACE_PRINT("APEXDRIVER_HOST_COM_RX APEXID: %d\n", apex_id)
  switch (apex_id)
  {
    case APEX_APEX0:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      APEXDRIVER_TRACE_WAIT_WHILE_NBT(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 16, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20)
      while (!(shared0[4] > shared0[5]))
        apexdriver_com_wait(1000);

      /* read the message */
      if (msg)
        *msg = shared0[6];
   
      /* acknowledge */
      ++shared0[5];
      APEXDRIVER_TRACE_INC(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20);
      break;
    case APEX_APEX1:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      APEXDRIVER_TRACE_WAIT_WHILE_NBT(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 16, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20)
      while (!(shared0[4] > shared0[5]))
        apexdriver_com_wait(1000);

      /* read the message */
      if (msg)
        *msg = shared0[6];
   
      /* acknowledge */
      ++shared0[5];
      APEXDRIVER_TRACE_INC(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20);
      break;
    case APEX_APEX_BOTH:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      shared1 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      APEXDRIVER_TRACE_WAIT_WHILE_NBT(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 16, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20)
      APEXDRIVER_TRACE_WAIT_WHILE_NBT(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 16, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20)
      while (!(shared0[4] > shared0[5]) || !(shared1[4] > shared1[5]))
        apexdriver_com_wait(1000);

      /* read the message */
      if (msg)
      {
	if (shared0[6] == shared1[6])
	  *msg = shared0[6];
	else
	  *msg = 0;
      }
   
      /* acknowledge */
      ++shared0[5];
      ++shared1[5];
      APEXDRIVER_TRACE_INC(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20);
      APEXDRIVER_TRACE_INC(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 20);
      break;
    default:
      break;
  }
        
  return 0;
}

/*======================================================================================*/
/* Send the message to the APU and wait for acknowledge					*/
/*======================================================================================*/
uint32_t  apexdriver_host_com_tx  	(uint32_t apex_id, uint32_t apu_id, uint32_t msg)
{
  volatile int32_t* shared0 = 0;
  volatile int32_t* shared1 = 0;
   
  APEXDRIVER_TRACE_PRINT("APEXDRIVER_HOST_COM_TX APEXID: %d\n", apex_id)
  switch (apex_id)
  {
    case APEX_APEX0:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      /* Create and save the message into the right channel */
      shared0[2] = (int32_t)msg;
      APEXDRIVER_TRACE_SET(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 8, (int32_t)msg);
   
      /* send a message ready signal */
      ++shared0[0];
      APEXDRIVER_TRACE_INC(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
   
      /* wait until message has been recieved  	  */
      /* shared[0] == sent messages counter 	  */
      /* shared[1] == ackgnowledged messages counter */
      APEXDRIVER_TRACE_WAIT_WHILE_BT(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 4)
      while (shared0[0]  > shared0[1])
        apexdriver_com_wait(1000);
      break;
    case APEX_APEX1:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      /* Create and save the message into the right channel */
      shared0[2] = (int32_t)msg;
      APEXDRIVER_TRACE_SET(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 8, (int32_t)msg);
   
      /* send a message ready signal */
      ++shared0[0];
      APEXDRIVER_TRACE_INC(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
   
      /* wait until message has been recieved  	  */
      /* shared[0] == sent messages counter 	  */
      /* shared[1] == ackgnowledged messages counter */
      APEXDRIVER_TRACE_WAIT_WHILE_BT(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 4)
      while (shared0[0]  > shared0[1])
        apexdriver_com_wait(1000);
      break;
    case APEX_APEX_BOTH:
      shared0 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_1_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      shared1 = (volatile int32_t*)(apexdriver_get_virtual_ptr(APEX_2_REG_SMEM) + dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      /* Create and save the message into the right channel */
      shared0[2] = (int32_t)msg;
      shared1[2] = (int32_t)msg;
      APEXDRIVER_TRACE_SET(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 8, (int32_t)msg);
      APEXDRIVER_TRACE_SET(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 8, (int32_t)msg);
   
      /* send a message ready signal */
      ++shared0[0];
      ++shared1[0];
      APEXDRIVER_TRACE_INC(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
      APEXDRIVER_TRACE_INC(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET);
   
      /* wait until message has been recieved  	  */
      /* shared[0] == sent messages counter 	  */
      /* shared[1] == ackgnowledged messages counter */
      APEXDRIVER_TRACE_WAIT_WHILE_BT(APEX_1_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 4)
      APEXDRIVER_TRACE_WAIT_WHILE_BT(APEX_2_REG_SMEM, dmem_offset[apu_id] + DMEM_SHARED_OFFSET, dmem_offset[apu_id] + DMEM_SHARED_OFFSET + 4)
      while (shared0[0]  > shared0[1] || shared1[0]  > shared1[1])
        apexdriver_com_wait(1000);
      break;
    default:
      break;
  }
  
  return 0;
}

