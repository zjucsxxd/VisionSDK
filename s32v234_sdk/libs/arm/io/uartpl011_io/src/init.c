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

/****************************************************************************
 * init.c
 *
 * Defines setup functions for the test.
 ****************************************************************************/

#include "../include/init.h"
//#include "driver/utility.h"

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/* Top level control structure - this is a structure that holds
 * the absolute base address for each IP block in the system. */
//SystemCntlTop_t system_cntl_top;

/****************************************************************************
 * Setup function declarations
 ****************************************************************************/

/* Function to initialise the addresses of each device.*/
void init_add(SystemCntlTop_t* cntl_top) {
    cntl_top->uart0_cntl.addr    = UART0_BASE_ADDRESS;
    cntl_top->uart1_cntl.addr    = UART1_BASE_ADDRESS;
}

void init_devices(SystemCntlTop_t* cntl_top) {
    uartpl011_init(&cntl_top->uart0_cntl);
    uartpl011_init(&cntl_top->uart1_cntl);
}
