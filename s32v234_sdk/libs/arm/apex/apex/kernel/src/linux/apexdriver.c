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
 * @file apexdriver.c
 *
 * \\author Rostislav Hulik (Freescale Semiconductor)
 * \date 28. 11. 2013
 *
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

#include <apexdriver_hw_reg_user.h>
#include <apexdriver_ioctl.h>
//#include <apexdriver_intheader.h>
#include <linux/interrupt.h>
//#include <functions/apexdriver_interrupt.h>

#define APEX_APEXDRIVER_DEVICE_ID             "apex2"

//irqreturn_t apexdriver_irq_handler_1(int32_t irq, void *dev_id);
//irqreturn_t apexdriver_irq_handler_2(int32_t irq, void *dev_id);

/*======================================================================================*/
/* Global variable for the device class							*/
static struct class *apexdriver_class;

/*======================================================================================*/
/* Global variable for the main device number						*/
static dev_t apexdriver_dev;

/*======================================================================================*/
/* Global variable for the character device structure (Driver)				*/
static struct cdev apexdriver_c_dev;

/*======================================================================================*/
/* File operations declared for global driver						*/
static struct file_operations apexdriver_fops_main =
{
	.unlocked_ioctl = apexdriver_ioctl,
};

/*======================================================================================*/
/* Module initialization procedure							*/
/* @return 0 If module successfully initialized, -1 otherwise				*/
/*======================================================================================*/
static int32_t apexdriver_init(void)
{
	printk(KERN_ALERT "APEX 2 Module - Initializing...\n");

	/* Init main module */
	if (alloc_chrdev_region(&apexdriver_dev, 0, 1, "apexdriver_dev_main") < 0)
	  goto apexdriver_fail_alloc;

	if ((apexdriver_class = class_create(THIS_MODULE, "chardrv")) == NULL)
	  goto apexdriver_fail_class;

	if (device_create(apexdriver_class, NULL, apexdriver_dev, NULL, APEX_APEXDRIVER_DEVICE_ID) == NULL)
	  goto apexdriver_fail_device;

	cdev_init(&apexdriver_c_dev, &apexdriver_fops_main);
	if (cdev_add(&apexdriver_c_dev, apexdriver_dev, 1) == -1)
	  goto apexdriver_fail_cdev;

	if (InitVirtualHwPtrArray() != 0)
	  goto apexdriver_fail_map;

	//if (request_irq(APEX_APEX0_IRQ, &apexdriver_irq_handler_1, IRQF_TRIGGER_RISING, "apexdriver_done_1", NULL))
	//  goto apexdriver_fail_irq1;
	
	//if (request_irq(APEX_APEX1_IRQ, &apexdriver_irq_handler_2, IRQF_TRIGGER_RISING, "apexdriver_done_2", NULL))
	//  goto apexdriver_fail_irq2;
	
	printk(KERN_ALERT "APEX 2 Module - Successfully loaded...\n");
	return 0;

	/* Failure gotos */

	/* Error Main driver functionality init */
	//apexdriver_fail_irq2:
	  //free_irq(APEX_APEX0_IRQ, NULL);
	//apexdriver_fail_irq1:
	apexdriver_fail_map:
      UnmapVirtualHwPtrArray();
	apexdriver_fail_cdev:
	  device_destroy(apexdriver_class, apexdriver_dev);
	apexdriver_fail_device:
	  class_destroy(apexdriver_class);
	apexdriver_fail_class:
	  unregister_chrdev_region(apexdriver_dev, 1);
	apexdriver_fail_alloc:

	//Release_APEX_Interrupts();
	printk(KERN_ALERT "APEX 2 Module - Error on load, exiting...!!\n");
	return -1;
}

/*======================================================================================*/
/* Function called on exit of the kernel module. Removes all allocated devices.		*/
/*======================================================================================*/
static void apexdriver_exit(void)
{
  //free_irq(APEX_APEX0_IRQ, NULL);
  //free_irq(APEX_APEX1_IRQ, NULL);
  UnmapVirtualHwPtrArray();
  device_destroy(apexdriver_class, apexdriver_dev);
  class_destroy(apexdriver_class);
  unregister_chrdev_region(apexdriver_dev, 1);
		
  printk(KERN_ALERT "APEX 2 Module - Shutdown.\n");
}

module_init(apexdriver_init);
module_exit(apexdriver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rostislav Hulik <rostislav.hulik <at> freescale.com>");
MODULE_DESCRIPTION("APEX 2 Freescale driver.");
MODULE_ALIAS("apex2");