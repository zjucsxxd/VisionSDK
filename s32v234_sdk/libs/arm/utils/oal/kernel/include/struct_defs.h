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
#ifndef _HEADERSTRUCTDEFSKERNEL_H
#define _HEADERSTRUCTDEFSKERNEL_H


typedef struct UserAddress t_UserAddress;
typedef struct MemArea t_MemArea;

/**
 * Structure saves info about user space mappings
 */
typedef struct UserAddress
{
  /**
   * Process id
   */
  unsigned int pid;
  
  /**
   * User virtual memory
   */
  unsigned long user_virtual;
  
  /**
   * Next in double-linked list
   */
  t_UserAddress *next;
  
  /**
   * Previous in double-linked list
   */
  t_UserAddress *prev;
} t_UserAddress;

/**
 * Structure saves info about kernel space contiguous memory allocation
 */
typedef struct MemArea
{
  /**
   * User space mappings list
   */
  t_UserAddress* user_addresses;
  
  /**
   * Kernel physical address
   */
  unsigned long kernel_physical;
  
  /**
   * Kernel virtual address
   */
  unsigned long kernel_virtual;
  
  /**
   * Allocation size
   */
  unsigned long size;
  
  /**
   * Next in double-linked list
   */
  t_MemArea *next;
  
  /**
   * Previous in double-linked list
   */
  t_MemArea *prev;
  
} t_MemArea;

#endif