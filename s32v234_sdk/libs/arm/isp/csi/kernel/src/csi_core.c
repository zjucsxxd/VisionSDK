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
 * \file     csi_core.c
 * \brief    init/exit functionality of CSI driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     21.9.2014
 * \note
 ****************************************************************************/

#include <linux/kernel.h>	// We're doing kernel work
#include <linux/module.h>	// Specifically, a module 
#include <linux/moduleparam.h>  // for cmd line arguments
#include <linux/device.h> // for class_create
#include <linux/init.h>
#include <linux/slab.h>		// for kmalloc


#include <linux/fs.h>
#include <linux/cdev.h>		// Char device structure 
#include <linux/mutex.h>	// for semaphore/mutex


#include "csi.h"
#include "csi_ioctl.h"
#include "csi_func.h"
#include "sony_func.h"
#include "vdb_log.h"

/////////////////////////////////////
//
// Global variables

// internal device open counter
static int gDeviceOpenCnt = 0;

// char device structure for fDMA module
struct cdev gCsiCdev;

// fDMA device number
int gCsiDevno;
// major device number
int gMajor;

// Csi driver class
static struct class *gCsiDriverClass = NULL;

// CSI locking mutex
//extern mutex_t gCsiMutex;

//****************************************************************************

//
// CSI local declarations
//

static int CsiOpen(struct inode *apInode, struct file *apFile);
static int CsiRelease(struct inode *apInode, struct file *apFile);
static int __init CsiInit(void);
static void __exit CsiExit(void);

//****************************************************************************

// 
// Essential kernel module behaviour definition 
//
static int CsiOpen(struct inode *apInode, struct file *apFile)
{
  VDB_LOG_NOTE("device_open(%p)\n", apFile);

  /*if (gDeviceOpenCnt)
  {
    return -EBUSY;
  } // if device opened alrealdy*/

  gDeviceOpenCnt++;
	  
  try_module_get(THIS_MODULE);
  return CSI_DRV_SUCCESS;
} // CsiOpen()

//****************************************************************************

//
// called whenever a process attempts to close the device file 
//
static int CsiRelease(struct inode *apInode, struct file *apFile)
{
  gDeviceOpenCnt--;

  module_put(THIS_MODULE);

  return CSI_DRV_SUCCESS;
} // CsiRelease()

//****************************************************************************

// Module Declarations 

// 
// This structure will hold the functions to be called
// when a process does something to the device we
// created. Since a pointer to this structure is kept in
// the devices table, it can't be local to
// init_module. NULL is for unimplemented functions. 
//
struct file_operations fops = {
  .unlocked_ioctl = CsiIoctl,
  .open = CsiOpen,
  .release = CsiRelease,	/* a.k.a. close */
}; // struct file_operations

//****************************************************************************

// 
// Initialize the module - Register the character device 
//
static int __init CsiInit(void)
{
  int32_t ret_val = 0;
  
  // enable logging
  vdb_LogInit();
  
  // *** Setup the driver ***  
  if(CSI_DRV_Setup() != CSI_DRV_SUCCESS)
  {
    ret_val = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("CSI setup failed.\n");
    goto csi_setup_failed;
  } // if driver setup failed
  
  if(SONY_DRV_Setup(CSI_IDX_0) != CSI_DRV_SUCCESS)
  {
    ret_val = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("SONY setup on CSI_IDX_0 failed.\n");
    goto csi_setup_failed;
  } // if driver setup failed
  
  if(SONY_DRV_Setup(CSI_IDX_1) != CSI_DRV_SUCCESS)
  {
    ret_val = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("SONY setup on CSI_IDX_1 failed.\n");
    goto csi_setup_failed;
  } // if driver setup failed
  
  
  //
  // initialize device file
  //
  
  // get device number
  if (alloc_chrdev_region(&gCsiDevno, 0, 1, CSI_DEVICE_NAME) < 0)
  {
    ret_val = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("Device number allocation failed.\n");
    goto device_number_allocation_failed;
  } // if alloc char dev number failed
  
  if((gCsiDriverClass = class_create(THIS_MODULE, "csidrv")) == NULL)
  {
    ret_val = CSI_DRV_FAILURE;
    printk(KERN_ALERT "Driver class creation failed.\n");
    goto driver_class_cration_failed;
  } // if csi driver class creation failed
  
  if (device_create(gCsiDriverClass, NULL, gCsiDevno, NULL, "csi") == NULL)
  {
    VDB_LOG_ERROR("Driver device creation failed.\n");
    goto device_creation_failed;
  }

  cdev_init(&gCsiCdev, &fops);
  gCsiCdev.owner = THIS_MODULE;
  gCsiCdev.ops = &fops;
  
  if(cdev_add(&gCsiCdev, gCsiDevno, 1))
  {
    ret_val = CSI_DRV_FAILURE;
    VDB_LOG_ERROR("Device registration failed.\n");
    goto registration_failed;
  } // if device registration failed

  gMajor = MAJOR(gCsiDevno);
  
  // print usage message
  VDB_LOG_NOTE("CSI driver module registration succeeded.\n"
    "I was assigned major number %d. To talk to\n"
    "the driver a dev file /dev/%s has been created\n"	
    "Remove the device file (rm) and module (rmmod) when done.\n",
    gMajor, CSI_DEVICE_NAME);
  
  // init error processing
  if( ret_val )
  {
    //csi_tdt_init_failed:	
      cdev_del(&gCsiCdev);
    registration_failed:
      device_destroy(gCsiDriverClass, gCsiDevno);
    device_creation_failed:
      class_destroy(gCsiDriverClass);
    driver_class_cration_failed:
      unregister_chrdev_region(gCsiDevno, 1);	  
    device_number_allocation_failed:
    
    csi_setup_failed:
      //CSI_Close();
      VDB_LOG_ERROR("Error during insmod. Terminating ...\n");
      vdb_LogStop();
  } // if some failure
  
  return ret_val;
} // CsiInit()

//****************************************************************************

// 
// Cleanup - unregister the appropriate file from /proc 
//
static void __exit CsiExit(void)
{
  // 
  // Unregister the device 
  //
  VDB_LOG_NOTE("Removing fDMA character device driver module.\n");
  cdev_del(&gCsiCdev);
  device_destroy(gCsiDriverClass, gCsiDevno);
  class_destroy(gCsiDriverClass);
  unregister_chrdev_region(gCsiDevno, 1);
  
  // relase resources
  CSI_DRV_Close();
  
  vdb_LogStop();
} // CsiExit()

//****************************************************************************

module_init(CsiInit);
module_exit(CsiExit);

//****************************************************************************

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomas Babinec <tomas.babinec <at> freescale.com>");
MODULE_DESCRIPTION("CSI Freescale driver.");
MODULE_ALIAS("mipi-csi");
