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
 * uartpl011_private.h - Private data structures and types definitions
 * for use in the UARTPL011 device driver.
 */

#ifndef __UARTPL011_PRIVATE_H__
#define __UARTPL011_PRIVATE_H__

/*
 * Device memory map structure.
 */

#define UARTDR 0            /* RX/TX data. */
#define UARTRSR_UARTECR 1   /* RX status, Error clear. */
#define UARTFR 6           /* Flags. */
#define UARTILPR 8         /* IRDA low-power counter. */
#define UARTIBRD 9         /* Integer part of clock divisor. */
#define UARTFBRD 10         /* Fractional part of clock dividor. */
#define UARTLCR_H 11        /* UART control, high part. */
#define UARTCR 12           /* UART control, low part. */
#define UARTIFLS 13         /* FIFO level settings. */
#define UARTIMSC 14         /* Interrupt mask settings. */
#define UARTRIS 15          /* Raw interrupt status. */
#define UARTMIS 16          /* Masked interrupt status. */
#define UARTICR 17          /* Clears interrupts. */
#define UARTDMACR 18        /* DMA control. */
#define UARTTCR 32          /* Test control register */
#define UARTITIP 33         /* Access to inputs in test mode. */
#define UARTITOP 34         /* Access to outputs in test mode. */
#define UARTTDR 35          /* Alternate data access in test mode. */
#define UARTPeriphID0 1016   /* Periph ID part 0 */
#define UARTPeriphID1 1017   /* Periph ID part 1 */
#define UARTPeriphID2 1018   /* Periph ID part 2 */
#define UARTPeriphID3 1019   /* Periph ID part 3 */
#define UARTPCellID0 1020    /* Cell ID part 0 */
#define UARTPCellID1 1021    /* Cell ID part 1 */
#define UARTPCellID2 1022    /* Cell ID part 2 */
#define UARTPCellID3 1023    /* Cell ID part 3 */


#endif /* __UARTPL011_PRIVATE_H__ */
