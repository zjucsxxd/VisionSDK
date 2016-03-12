/*****************************************************************************
 *
 * Freescale Confidential Proprietary
 *
 * Copyright (c) 2015 Freescale Semiconductor;
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
 * \file     seq_core.c
 * \brief    init/exit functionality of sequencer driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     4 September 2015
 * \note
 ****************************************************************************/

#include <linux/kernel.h>	// We're doing kernel work
#include <linux/module.h>	// Specifically, a module 
#include <linux/device.h>	// for class_create
#include <linux/moduleparam.h>  // for parameter use
#include <linux/kmod.h>		// for inter_module_xxx
#include <linux/init.h>
#include <linux/mm.h>     // mmap, VM_RESERVED

#include <linux/fs.h>
#include <linux/cdev.h>		// Char device structure 
#include <asm/uaccess.h>	// for get_user and put_user 
#include <linux/mutex.h>	// for semaphore/mutex
#include <linux/sched.h>	// for current->pid
  
#include "seq.h"
#include "seq_func.h"
#include "seq_ioctl.h"
#include "vdb_log.h"

/////////////////////////////////////
//
// Command line arguments

//static int32_t gsTDcnt = 16;

//module_param(gsTDcnt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
//MODULE_PARM_DESC(gsTDcnt, "Defines the number of transfer descriptos in SRAM table.");

/////////////////////////////////////
//
// Global variables

// internal device open counter
static int gDeviceOpenCnt = 0;

// SEQ HW registers placeholder
// SEQ_Regs_t gSeqRegs;

// Sequencer locking mutex
struct mutex gSeqMutex;

// PRAM simulation (4k bytes)
//char gPram[4 * 1024];

// char device structure for Sequencer module
struct cdev gSeqCdev;

// Sequencer device number
int gSeqDevno;
// major device number
int gMajor;

// Sequencer driver class
static struct class *gSeqDriverClass = NULL;

//
// Sequencer local declarations
//

static int SeqOpen(struct inode *apInode, struct file *apFile);
static int SeqRelease(struct inode *apInode, struct file *apFile);
static int __init SeqInit(void);
static void __exit SeqExit(void);

//
// external kernel modules functionality interface
//

static int SeqMmap(struct file *filp, struct vm_area_struct *vma)
{
  unsigned long lSize = (unsigned long)(vma->vm_end - vma->vm_start);
  unsigned long lPhysAddr = (vma->vm_pgoff << PAGE_SHIFT);
  int lRet = 0;

  // *** check region ***
  switch(lPhysAddr)
  {
    case KRAM_BASE:
    {
      if(lSize > KRAM_SIZE)
      {
        lRet = -EINVAL;
      } // if too big return error
    } // if KRAM
    break;
    case PRAM_BASE:
    {
      if(lSize > PRAM_SIZE)
      {
        lRet = -EINVAL;
      } // if too big return error
    } // if PRAM
    break;
    case CRAM_BASE:
    {
      if(lSize > CRAM_SIZE)
      {
        lRet = -EINVAL;
      } // if too big return error
    } // if CRAM
    break;
    default:
    {
      lRet = -EINVAL;
    } // if other region
    break;
  } // switch regions

  
  if(lRet == 0)
  {
    vma->vm_flags |= VM_IO;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    
    lRet = remap_pfn_range(vma, vma->vm_start, __phys_to_pfn(lPhysAddr), lSize, vma->vm_page_prot);   
  } // if all ok so far
  
  return lRet; 
} // SeqMmap()


// 
// called whenever a process attempts to open the device file 
//
static int SeqOpen(struct inode *apInode, struct file *apFile)
{
  VDB_LOG_NOTE("Openning Sequencer device.\n", apFile);

  // if only one open allowed
  if (gDeviceOpenCnt > 0)
  {
    return -EBUSY;
  } // if device opened already

  gDeviceOpenCnt++;

  // remember the user PID
  SEQ_UserPidSet(current->pid);

  try_module_get(THIS_MODULE);
  return SEQ_DRV_SUCCESS;
} // SeqOpen()

//
// called whenever a process attempts to close the device file 
//
static int SeqRelease(struct inode *apInode, struct file *apFile)
{
  gDeviceOpenCnt--;

  module_put(THIS_MODULE);

  SEQ_UserPidSet(0);

  return SEQ_DRV_SUCCESS;
} // SeqRelease()

// Module Declarations 

// 
// This structure will hold the functions to be called
// when a process does something to the device we
// created. Since a pointer to this structure is kept in
// the devices table, it can't be local to
// init_module. NULL is for unimplemented functions. 
//
struct file_operations fops = {
  .owner = THIS_MODULE,
  .unlocked_ioctl = SeqIoctl,
  .mmap = SeqMmap,
  .open = SeqOpen,
  .release = SeqRelease,	/* a.k.a. close */
}; // struct file_operations

// 
// Initialize the module - Register the character device 
//
static int __init SeqInit()
{
  int32_t ret_val = 0;
    
  // enable logging
  vdb_LogInit();

  VDB_LOG_NOTE("Sequencer driver here\n");
  //
  // Setup the driver
  //

  if(SEQ_Setup() != SEQ_DRV_SUCCESS)
  {
    ret_val = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Sequencer setup failed.\n");
    goto seq_setup_failed;
  } // if driver setup failed

  //
  // initialize device file
  //

  // get device number
  if (alloc_chrdev_region(&gSeqDevno, 0, 1, SEQ_DEVICE_NAME) < 0)
  {
    ret_val = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Device number allocation failed.\n");
    goto device_number_allocation_failed;
  } // if alloc char dev number failedl

  if((gSeqDriverClass = class_create(THIS_MODULE, "seqdrv")) == NULL)
  {
    ret_val = SEQ_DRV_FAILURE;
    printk(KERN_ALERT "Driver class creation failed.\n");
    goto driver_class_cration_failed;
  } // if fdma driver class creation failed

  if (device_create(gSeqDriverClass, NULL, gSeqDevno, NULL, "seq") == NULL)
  {
    VDB_LOG_ERROR("Driver device creation failed.\n");
    goto device_creation_failed;
  } // if device cration failed

  cdev_init(&gSeqCdev, &fops);
  gSeqCdev.owner = THIS_MODULE;
  gSeqCdev.ops = &fops;

  if(cdev_add(&gSeqCdev, gSeqDevno, 1))
  {
    ret_val = SEQ_DRV_FAILURE;
    VDB_LOG_ERROR("Device registration failed.\n");
    goto registration_failed;
  } // if device registration failed

  gMajor = MAJOR(gSeqDevno);

  // print usage message
  VDB_LOG_NOTE("Seq driver module registration succeeded.\n"
          "I was assigned major number %d. To talk to\n"
          "the driver a dev file /dev/%s has been created\n"	
          "Remove the device file (rm) and module (rmmod) when done.\n",
          gMajor, SEQ_DEVICE_NAME);

  // init error processing
  if( ret_val )
  {
    //fdma_tdt_init_failed:	
      cdev_del(&gSeqCdev);
    registration_failed:
      device_destroy(gSeqDriverClass, gSeqDevno);
    device_creation_failed:
      class_destroy(gSeqDriverClass);
    driver_class_cration_failed:
      unregister_chrdev_region(gSeqDevno, 1);	  
    device_number_allocation_failed:
    
    seq_setup_failed:
      //SEQ_Close();
      VDB_LOG_ERROR("Error during insmod. Terminating ...\n");
      vdb_LogStop();
  } // if some failure

  return ret_val;
} // SeqInit()

// 
// Cleanup - unregister the appropriate file from /proc 
//
static void __exit SeqExit()
{
  // 
  // Unregister the device 
  //
  VDB_LOG_NOTE("Removing Sequencer character device driver module.\n");
  cdev_del(&gSeqCdev);
  device_destroy(gSeqDriverClass, gSeqDevno);
  SEQ_Close();
  class_destroy(gSeqDriverClass);
  unregister_chrdev_region(gSeqDevno, 1);	
} // SeqExit()

module_init(SeqInit);
module_exit(SeqExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomas Babinec <tomas.babinec <at> freescale.com>");
MODULE_DESCRIPTION("Sequencer Freescale driver.");
MODULE_ALIAS("seq");
