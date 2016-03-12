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
 * \file     h264enc_core.c
 * \brief    init/exit functionality of H264 encoder driver
 * \author   Tomas Babinec
 * \version  0.1
 * \date     20.6.2014
 * \note
 ****************************************************************************/

#include <linux/kernel.h>	// We're doing kernel work
#include <linux/module.h>	// Specifically, a module 
#include <linux/device.h>	// for class_create
#include "s32vs234.h"
#include <linux/moduleparam.h>  // for parameter use
#include <linux/init.h>
#include <linux/slab.h>		// for kmalloc
#include <linux/sched.h>        // for current->pid

#include <linux/fs.h>
#include <linux/cdev.h>		// Char device structure 
#include <asm/uaccess.h>	// for get_user and put_user 
#include <linux/mutex.h>	// for semaphore/mutex

#include "h264enc.h"
#include "h264enc_ioctl.h"
#include "h264enc_func.h"
#include "vdb_log.h"

/////////////////////////////////////
//
// Command line arguments

//static int32_t gsTDcnt = 16;

//module_param(gsTDcnt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
//MODULE_PARM_DESC(gsTDcnt, "Defines the number of transfer descriptors in SRAM table.");

/////////////////////////////////////
//
// Global variables

// internal device open counter
static int gDeviceOpenCnt = 0;

// char device structure for H264 Encoder module
struct cdev gH264EncCdev;

// H264 Encoder device number
int gH264EncDevno;
// major device number
int gMajor;

// H264 Encoder driver class
static struct class *gH264EncDriverClass = NULL;

// H264 Encoder HW registers placeholder
H264ENC_Regs_t gH264EncRegs;

// H264 Encoder locking mutex
struct mutex gH264EncMutex;

// PID of the user
extern pid_t gH264EncUserPid;

//
// H264 Encoder local declarations
//

static int H264EncOpen(struct inode *apInode, struct file *apFile);
static int H264EncRelease(struct inode *apInode, struct file *apFile);
static int __init H264EncInit(void);
static void __exit H264EncExit(void);

// 
// Essential kernel module behaviour definition 
//
static int H264EncOpen(struct inode *apInode, struct file *apFile)
{
	VDB_LOG_NOTE("device_open(%p)\n", apFile);

	// only one open allowed
	if (gDeviceOpenCnt > 0)
	{
	  VDB_LOG_ERROR("Openned already.\n");
	  return -EBUSY;
	} // if device opened already

	// remember the user PID
        gH264EncUserPid = current->pid;
        
	gDeviceOpenCnt++;
		
	try_module_get(THIS_MODULE);
	return H264ENC_DRV_SUCCESS;
} // H264EncOpen()

//
// called whenever a process attempts to close the device file 
//
static int H264EncRelease(struct inode *apInode, struct file *apFile)
{
        gH264EncUserPid = 0;
        
	gDeviceOpenCnt--;

	module_put(THIS_MODULE);

	return H264ENC_DRV_SUCCESS;
} // H264EncRelease()


// Module Declarations 

// 
// This structure will hold the functions to be called
// when a process does something to the device we
// created. Since a pointer to this structure is kept in
// the devices table, it can't be local to
// init_module. NULL is for unimplemented functions. 
//
struct file_operations fops = {
	.unlocked_ioctl = H264EncIoctl,
	.open = H264EncOpen,
	.release = H264EncRelease,	/* a.k.a. close */
}; // struct file_operations

// 
// Initialize the module - Register the character device 
//
static int __init H264EncInit()
{
	int32_t ret_val = 0;

	// enable logging
	vdb_LogInit();
	
	//
	// Setup the driver
	//
	
	if(H264ENC_Setup() != H264ENC_DRV_SUCCESS)
	{
	  ret_val = H264ENC_DRV_FAILURE;
	  VDB_LOG_ERROR("Device number allocation failed.\n");
	  goto h264enc_setup_failed;
	} // if driver setup failed
	
	//
	// initialize device file
	//
	
	VDB_LOG_NOTE("Setup ended OK.\n");
	// get device number
	if (alloc_chrdev_region(&gH264EncDevno, 0, 1, H264ENC_DEVICE_NAME) < 0)
	{
	  ret_val = H264ENC_DRV_FAILURE;
	  VDB_LOG_ERROR("Device number allocation failed.\n");
	  goto device_number_allocation_failed;
	} // if alloc char dev number failed
	VDB_LOG_NOTE("chrdev region allocated OK.\n");
	if((gH264EncDriverClass = class_create(THIS_MODULE, "h264EncDrv")) == NULL)
	{
	  ret_val = H264ENC_DRV_FAILURE;
	  printk(KERN_ALERT "Driver class creation failed.\n");
	  goto driver_class_cration_failed;
	} // if h264enc driver class creation failed
	VDB_LOG_NOTE("driver class created OK.\n");
	if (device_create(gH264EncDriverClass, NULL, gH264EncDevno, NULL, H264ENC_DEVICE_NAME) == NULL)
	{
	  VDB_LOG_ERROR("Driver device creation failed.\n");
	  goto device_creation_failed;
	}

	cdev_init(&gH264EncCdev, &fops);
	gH264EncCdev.owner = THIS_MODULE;
  gH264EncCdev.ops = &fops;
  VDB_LOG_NOTE("Cdev inited.\n");
	
	if(cdev_add(&gH264EncCdev, gH264EncDevno, 1))
	{
	  ret_val = H264ENC_DRV_FAILURE;
	 VDB_LOG_ERROR("Device registration failed.\n");
	  goto registration_failed;
	} // if device registration failed
	VDB_LOG_NOTE("Cdev Added.\n");

	gMajor = MAJOR(gH264EncDevno);
	
	// print usage message
	VDB_LOG_NOTE("H264ENC driver module registration succeeded.\n"
		     "I was assigned major number %d. To talk to\n"
		     "the driver's dev file /dev/%s has been created\n"	
		     "Remove the device file (rm) and module (rmmod) when done.\n",
		     gMajor, H264ENC_DEVICE_NAME);
	
	// init error processing
	if( ret_val )
	{
	  //h264enc_tdt_init_failed:	
	    cdev_del(&gH264EncCdev);
	  registration_failed:
	    device_destroy(gH264EncDriverClass, gH264EncDevno);
	  device_creation_failed:
	    class_destroy(gH264EncDriverClass);
	  driver_class_cration_failed:
	    unregister_chrdev_region(gH264EncDevno, 1);	  
	  device_number_allocation_failed:
	  
	  h264enc_setup_failed:
	    H264ENC_Close();
	    VDB_LOG_ERROR("Error during insmod. Terminating ...\n");
	    vdb_LogStop();
	} // if some failure
	
	return ret_val;
} // H264EncInit()

// 
// Cleanup - unregister the appropriate file from /proc 
//
static void __exit H264EncExit()
{
	// 
	// Unregister the device 
	//
	printk(KERN_INFO "Removing H264 Encoder character device driver module.\n");
	cdev_del(&gH264EncCdev);
	device_destroy(gH264EncDriverClass, gH264EncDevno);
	class_destroy(gH264EncDriverClass);
	unregister_chrdev_region(gH264EncDevno, 1);
	
	// relase resources
	H264ENC_Close();
	
	vdb_LogStop();
} // H264EncExit()

module_init(H264EncInit);
module_exit(H264EncExit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomas Babinec <tomas.babinec <at> freescale.com>");
MODULE_DESCRIPTION("H264 Encoder Freescale driver.");
MODULE_ALIAS(H264ENC_DEVICE_NAME);