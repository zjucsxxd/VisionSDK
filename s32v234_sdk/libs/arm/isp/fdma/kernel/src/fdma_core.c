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
 * \file     fdma_core.c
 * \brief    init/exit functionality of fDMA driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     2.4.2014
 * \note
 ****************************************************************************/
//#include <stdint.h>
//#include "s32vs234.h"

#include <linux/kernel.h>	// We're doing kernel work
#include <linux/module.h>	// Specifically, a module 
#include <linux/moduleparam.h>  // for cmd line arguments
#include <linux/device.h> // for class_create
#include <linux/init.h>
#include <linux/slab.h>		// for kmalloc


#include <linux/fs.h>
#include <linux/cdev.h>		// Char device structure 
#include <linux/mutex.h>	// for semaphore/mutex


#include "fdma.h"
#include "fdma_ioctl.h"
#include "fdma_func.h"
#include "vdb_log.h"

/////////////////////////////////////
//
// Command line arguments

static int32_t gsTDcnt = 16;

module_param(gsTDcnt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
MODULE_PARM_DESC(gsTDcnt, "Defines the number of transfer descriptors in SRAM table.");

/////////////////////////////////////
//
// Global variables

// internal device open counter
static int gDeviceOpenCnt = 0;

// char device structure for fDMA module
struct cdev gFdmaCdev;

// fDMA device number
int gFdmaDevno;
// major device number
int gMajor;

// Fdma driver class
static struct class *gFdmaDriverClass = NULL;

// FDMA HW registers placeholder
extern FDMA_Regs_t gFdmaRegs;

// transaction descriptors table in SRAM
extern FDMA_Tdt_t gTdt;

// Array of available TDMs (one for each TD in SRAM TDT)
extern FDMA_Tdm_t gTdmArr[];

// list of unused TDMs
extern FDMA_TdmList_t gFreeTdmList;

// Array of TC events (one for each TD in SRAM TDT)
extern FDMA_TcEvent_t gTcEventArr[];

// fDMA locking mutex
extern mutex_t gFdmaMutex;

// available sequencer mode (1 = Sequencer-based, 0 = Sequencer-less);
extern char gSequencerOn; // fdma module internal variable

//
// SRAM Manager kernel functionality interface
//

uint32_t sram_single_malloc(uint32_t);
uint32_t sram_free(uint32_t);
uint32_t SRAM_MultiMalloc(uint32_t aSize);
void SRAM_Free(uint32_t aPhysAddr);

//
// FDMA local declarations
//

static int FdmaOpen(struct inode *apInode, struct file *apFile);
static int FdmaRelease(struct inode *apInode, struct file *apFile);
static int __init FdmaInit(void);
static void __exit FdmaExit(void);

// 
// Essential kernel module behaviour definition 
//
static int FdmaOpen(struct inode *apInode, struct file *apFile)
{
  VDB_LOG_NOTE("device_open(%p)\n", apFile);

  /*if (gDeviceOpenCnt)
  {
    return -EBUSY;
  } // if device opened alrealdy*/

  gDeviceOpenCnt++;
	  
  try_module_get(THIS_MODULE);
  return FDMA_DRV_SUCCESS;
} // FdmaOpen()

//
// called whenever a process attempts to close the device file 
//
static int FdmaRelease(struct inode *apInode, struct file *apFile)
{
  gDeviceOpenCnt--;

  module_put(THIS_MODULE);

  return FDMA_DRV_SUCCESS;
} // FdmaRelease()


// Module Declarations 

// 
// This structure will hold the functions to be called
// when a process does something to the device we
// created. Since a pointer to this structure is kept in
// the devices table, it can't be local to
// init_module. NULL is for unimplemented functions. 
//
struct file_operations fops = {
	.unlocked_ioctl = FdmaIoctl,
	.open = FdmaOpen,
	.release = FdmaRelease,	/* a.k.a. close */
}; // struct file_operations
 
// 
// Initialize the module - Register the character device 
//
static int __init FdmaInit(void)
{
  int32_t ret_val = 0;
  
  // enable logging
  vdb_LogInit();
  
  // *** Setup the driver ***
	  
  if(FDMA_Setup() != FDMA_DRV_SUCCESS)
  {
    ret_val = FDMA_DRV_FAILURE;
    VDB_LOG_ERROR("FDMA setup failed.\n");
    goto fdma_setup_failed;
  } // if driver setup failed
  
  //
  // initialize device file
  //
  
  // get device number
  if (alloc_chrdev_region(&gFdmaDevno, 0, 1, FDMA_DEVICE_NAME) < 0)
  {
    ret_val = FDMA_DRV_FAILURE;
    VDB_LOG_ERROR("Device number allocation failed.\n");
    goto device_number_allocation_failed;
  } // if alloc char dev number failed
  
  if((gFdmaDriverClass = class_create(THIS_MODULE, "fdmadrv")) == NULL)
  {
    ret_val = FDMA_DRV_FAILURE;
    printk(KERN_ALERT "Driver class creation failed.\n");
    goto driver_class_cration_failed;
  } // if fdma driver class creation failed
  
  if (device_create(gFdmaDriverClass, NULL, gFdmaDevno, NULL, "fdma") == NULL)
  {
    VDB_LOG_ERROR("Driver device creation failed.\n");
    goto device_creation_failed;
  }

  cdev_init(&gFdmaCdev, &fops);
  gFdmaCdev.owner = THIS_MODULE;
  gFdmaCdev.ops = &fops;
  
  if(cdev_add(&gFdmaCdev, gFdmaDevno, 1))
  {
    ret_val = FDMA_DRV_FAILURE;
    VDB_LOG_ERROR("Device registration failed.\n");
    goto registration_failed;
  } // if device registration failed

  gMajor = MAJOR(gFdmaDevno);
  
  // print usage message
  VDB_LOG_NOTE("FDMA driver module registration succeeded.\n"
    "I was assigned major number %d. To talk to\n"
    "the driver a dev file /dev/%s has been created\n"	
    "Remove the device file (rm) and module (rmmod) when done.\n",
    gMajor, FDMA_DEVICE_NAME);
  
  // init error processing
  if( ret_val )
  {
    //fdma_tdt_init_failed:	
      cdev_del(&gFdmaCdev);
    registration_failed:
      device_destroy(gFdmaDriverClass, gFdmaDevno);
    device_creation_failed:
      class_destroy(gFdmaDriverClass);
    driver_class_cration_failed:
      unregister_chrdev_region(gFdmaDevno, 1);	  
    device_number_allocation_failed:
    
    fdma_setup_failed:
      //FDMA_Close();
      VDB_LOG_ERROR("Error during insmod. Terminating ...\n");
      vdb_LogStop();
  } // if some failure
  
  return ret_val;
} // FdmaInit()

// 
// Cleanup - unregister the appropriate file from /proc 
//
static void __exit FdmaExit(void)
{
  // 
  // Unregister the device 
  //
  VDB_LOG_NOTE("Removing fDMA character device driver module.\n");
  cdev_del(&gFdmaCdev);
  device_destroy(gFdmaDriverClass, gFdmaDevno);
  class_destroy(gFdmaDriverClass);
  unregister_chrdev_region(gFdmaDevno, 1);
  
  // relase resources
  FDMA_Close();
  
  vdb_LogStop();
} // FdmaExit()


module_init(FdmaInit);
module_exit(FdmaExit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomas Babinec <tomas.babinec <at> freescale.com>");
MODULE_DESCRIPTION("fDMA Freescale driver.");
MODULE_ALIAS("fdma");
