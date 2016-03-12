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
#ifndef _HEADER_IOCTLCMD_H
#define _HEADER_IOCTLCMD_H

#include <linux/fs.h>

/*======================================================================*/
/* Driver global functions */
/*======================================================================*/

/**
 * Add new allocation into the list
 */
#define CMD_ALLOC 				_IOW('m',  0, int)

/**
 * Remove the allocation from the list
 */
#define CMD_FREE 				_IOW('m',  1, int)

/**
 * Return existing virtual address of the current pid mapping
 */
#define CMD_VIRTUAL 				_IOW('m',  2, int)

/**
 * Create a new mapping for the current process
 */
#define CMD_MAP 				_IOW('m',  3, int)

/**
 * Remove a mapping for the current process
 */
#define CMD_UNMAP 				_IOW('m',  4, int)

/**
 * Get the size of the allocation
 */
#define CMD_SIZE 				_IOW('m',  5, int)

/**
 * Return existing physical address of the current pid mapping
 */
#define CMD_PHYSICAL 				_IOW('m',  6, int)

#define CMD_RESET 				_IOW('m',  7, int)

#define CMD_FLUSH				_IOW('m',  8, int)
typedef struct
{
  void * phys_ptr;
  void * virt_base;
  int  size;
} CMD_FLUSH_TYPE;

#endif
