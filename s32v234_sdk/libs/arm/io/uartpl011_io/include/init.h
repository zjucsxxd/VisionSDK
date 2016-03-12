/*
 * -----------------------------------------------------------------------------
 * Copyright (C) Australian Semiconductor Technology Company (ASTC). 2010.
 * All Rights Reserved.
 *
 * This is unpublished proprietary source code of the Australian Semiconductor
 * Technology Company (ASTC).  The copyright notice does not evidence any actual
 * or intended publication of such source code.
 * -----------------------------------------------------------------------------
 */
#ifndef __INIT_H_
#define __INIT_H_

/*
 * Includes.
 */
#include "uartpl011_driver_types.h"
#include "uartpl011_driver.h"              /* The UART driver. */

/****************************************************************************
 * Structure definitions
 ****************************************************************************/
typedef struct _SystemCntlTop {
    uart_cntl_t uart0_cntl;
    uart_cntl_t uart1_cntl;
} SystemCntlTop_t;

/****************************************************************************
 * Global variables - externed from declaration in init.c
 ****************************************************************************/
/* Top level control structure - this is a structure that holds
 * the absolute base address for each IP block in the system. */


/****************************************************************************
 * init.h
 *
 * Defines global variables and declares setup functions for the test.
 ****************************************************************************/
#define UART0_BASE_ADDRESS 0x3B000000
#define UART1_BASE_ADDRESS 0x3B000000


/****************************************************************************
 * Setup function declarations
 ****************************************************************************/
/* Function to initialise the addresses of each device.*/
void init_add(SystemCntlTop_t* cntl_top);
/* Load the default initialisation for each device */
void init_devices(SystemCntlTop_t* cntl_top);

#endif /*__INIT_H_*/
