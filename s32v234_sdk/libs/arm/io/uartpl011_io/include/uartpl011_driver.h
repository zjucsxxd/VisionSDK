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

/*
 * uartpl011_driver.h - Device driver for the UARTPL011 device.
 */

#ifndef __UARTPL011_DRIVER_H__
#define __UARTPL011_DRIVER_H__

#include "uartpl011_driver_types.h"

/*
 * Device configuration structure.
 */
typedef struct _uartpl011_conf_t {    
    unsigned short clkDivisor;
    unsigned long lcr;   
} uartpl011_conf_t;

/*
 * Device control structure.
 */
typedef struct _uartpl011_cntl_t {    
    unsigned long addr; /* Base address of device in memory map */    
    uartpl011_conf_t conf; /* Configuration structure */
} uart_cntl_t;

/*
 * Load the default settings into the given configuration structure.
 */
void uartpl011_load_defaults(uartpl011_conf_t* conf);

/*
 * Configure the device.
 * \param cntl: device control structure
 */
void uartpl011_conf(uart_cntl_t* cntl);

/*
 * Initialise the device with the default configuration.
 *
 * Equivalent to,
 *     uartpl011_load_defaults(&cntl->conf);
 *     uartpl011_conf(cntl);
 * \param cntl: device control structure
 */
void uartpl011_init(uart_cntl_t* cntl);

/*
 * Enable this UART to receive and send characters.
 *
 * \param cntl: device control structure
 */
void uartpl011_enable(uart_cntl_t* cntl);

/*
 * Function to undertake a simple self-check of the device. Ideally this 
 * function should not vary the state of the device.
 *
 * \param cntl: device control structure, used to configure the self-check.
 * \return 1 if self-check succeeded, 0 otherwise.
 */
int uartpl011_self_check(uart_cntl_t* cntl);

/*
 * Function to undertake a register reset value check.
 *
 * \param cntl: device control structure
 * \return 1 if check succeeded, 0 otherwise.
 */
int uartpl011_reset_value_check(uart_cntl_t* cntl);

/* Function to transmit a character to UART
 * 
 * \param cntl: device control structure
 * \param data: write character to UART.
 */
void tx(uart_cntl_t* cntl, unsigned long data);

/* Function to read a character from UART
 * 
 * \param cntl: device control structure
 * \return character.
 */
unsigned long rx(uart_cntl_t* cntl);

/* Function to flush the character buffer of current characters */
void uartpl011_flush_buffer(uart_cntl_t* cntl);

/* Function to handle interrupt settings
 * 
 * \param cntl: device control structure
 */
void uartpl011_handle_interrupt(uart_cntl_t* cntl);

/* Function to handle interrupt settings
 * 
 * \param cntl: device control structure
 * \param enable: enable the selected interrupts, others are disabled
 */
void uartpl011_enable_interrupts(uart_cntl_t* cntl, uint32_t enable);


#endif /* __UARTPL011_DRIVER_H__ */
