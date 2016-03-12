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
 * uartpl011_driver.c - Device driver for the UARTPL011 device.
 */

#include "../include/uartpl011_driver.h"
#include "../include/uartpl011_private.h"
#include "../include/device_io.h"    /* For DEVICE_RD/DEVICE_WR functionality */
#include "../include/io.h"   /* For printf */

/* Declare a variable 'regs' and initialise it with the address of
 * the device's register bank. */
#define INIT_REGS \
    volatile uint32_t* const regs = (uint32_t*) cntl->addr

/* Declare a large global array */
volatile uint8_t buffer[5000];
volatile uint32_t buffer_index = 0;
volatile uint32_t internal_count = 0;

void nop_delay(void)
{
    ;
}


void uartpl011_load_defaults(uartpl011_conf_t* conf)
{
    conf->clkDivisor = 0x0;
    conf->lcr = 0;
}

void uartpl011_conf(uart_cntl_t* cntl)
{
}

void uartpl011_init(uart_cntl_t* cntl)
{
    uartpl011_load_defaults(&cntl->conf);
    uartpl011_conf(cntl);
}

void uartpl011_enable(uart_cntl_t* cntl)
{
    INIT_REGS;

    //unsigned int value;
    // Currently guess 24MHz clock, setting baud rate to 230400
    // Fractional is 0x21, Integer is 6
    cntl->conf.clkDivisor = 0x2106;
    // FIFO enabled, 8 bit chars
    cntl->conf.lcr = 0xf70;

    //value = *(regs+UARTRSR_UARTECR);
    // Disable (default of UARTCR is 0x300)
    *(regs+UARTCR) = 0x300;

    // Set level of TX/RX FIFO to 1/4 full
    *(regs+UARTIFLS) = 0x101;

    // Set UART interrupt mask for receive and transmit
    //*(regs+UARTIMSC) = 0x30;

    // Configure clock divisor, prior to LCR_H programming
    *(regs+UARTIBRD) = (unsigned long)(cntl->conf.clkDivisor & 0xff);
    *(regs+UARTFBRD) = (unsigned long)((cntl->conf.clkDivisor >> 8) & 0xff);

    // FCR value
    *(regs+UARTLCR_H ) = cntl->conf.lcr;

    // Enable UART - UART and TX/RX enable
    *(regs+UARTCR) = 0x301;
}

void tx(uart_cntl_t* cntl, unsigned long data)
{
    // Rather than write to the UARTDR, we write to an internal buffer
    // to avoid overflow of the FIFO before transmission occurs
    buffer[buffer_index++] = data;
    //if (buffer_index > 4) {
        uartpl011_flush_buffer(cntl);
    //}
}

void uartpl011_flush_buffer(uart_cntl_t* cntl)
{
    INIT_REGS;
    uint32_t uartfr = 0;
    uint32_t busy = 0;
    //uint32_t X0;

    uint32_t i = 0, j = 0;
    // Loop through data and write to UARTDR
    for (i = 0; i < buffer_index; ++i)
    {
        *(regs+UARTDR) = buffer[i];
    }
    uartfr =  *(regs+UARTFR);
    busy = uartfr & 0x8;
    while (busy != 0) {
        for (j = 0; j < 1000; j++) {
            nop_delay();
        }
        busy =  *(regs+UARTFR) & 0x8;
    }
    buffer_index = 0;
}

unsigned long rx(uart_cntl_t* cntl)
{
    INIT_REGS;
    return *(regs+UARTDR);
}

void uartpl011_handle_interrupt(uart_cntl_t* cntl)
{
    INIT_REGS;
    uint32_t status = 0, actual = 0;
    uint32_t uartrsr = 0;
    uint32_t uartfr = 0;
    uint32_t uartimsc = *(regs+UARTIMSC);
    // Disable interrupts for duration of function
    uartpl011_enable_interrupts(cntl, 0);

    status =  *(regs+UARTMIS);

    if (status & (0x10|0x40)) { //RXIM | RTIM
        //Read the receive FIFO until empty
        uartfr =  *(regs+UARTFR);
        while ( (uartfr & 0x10) == 0x0) { //RXFE
            //Read FIFO
            actual =  *(regs+UARTDR);
            //Echo character back to screen
            *(regs+UARTDR) = actual;
            // Read UARTFR, expect flag to be set
            uartfr =  *(regs+UARTFR);
        }
    }
    if (status & 0x20) { //TXIM
        uint32_t i = 0, j = 0;
        uint32_t uartfr = 0;
        // This is requesting for data to be written to the transmit FIFO
        while (i < buffer_index) {
            *(regs+UARTDR) = buffer[i];
            ++i;
            ++internal_count;
            if (internal_count >= 20) {
                // Sit and wait for TXFE to be set again
                uartfr = *(regs+UARTFR);
                // Wait until FIFO becomes empty again
                while ((uartfr & 0x80) == 0x0)
                {
                    for (j = 0; j < 1000; j++) {
                        nop_delay();
                    }
                    uartfr =  *(regs+UARTFR);
                }

                internal_count = 0;
            }
        }
        buffer_index = 0;
        uartimsc &= ~0x20; // Disable TX empty interrupt
    }

    uartrsr =  *(regs+UARTRSR_UARTECR);
    if (uartrsr & 0x8) { //Overrun error
        // This is only in the RX FIFO. Assume taken care of with the above code
        // Clear the error.
        *(regs+UARTRSR_UARTECR) = 0x8;
        *(regs+UARTICR) = 0x400;
    }
    // Clear other errors
    *(regs+UARTRSR_UARTECR) = 0xF;
    // Clear remaining interrupts
    *(regs+UARTICR) = 0x7FF;
    uartpl011_enable_interrupts(cntl, uartimsc);
}

void uartpl011_enable_interrupts(uart_cntl_t* cntl, uint32_t enable)
{
    INIT_REGS;
    *(regs+UARTIMSC) = enable;
}


/*
 * Function to undertake a simple self-check of the device.
 */
int uartpl011_self_check(uart_cntl_t* cntl)
{
    INIT_REGS;
    int returnValue = 1; /* Test return value. */

    returnValue &= (*(regs+UARTFR) == 0x00000090);

    return returnValue;
}

/*
 * Function to undertake a register reset value check.
 */
int uartpl011_reset_value_check(uart_cntl_t* cntl)
{
    INIT_REGS;
    int returnValue = 1; /* Test return value. */
    int comparison = 0;
    int actual = 0;

    actual =  *(regs+UARTDR);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTDR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTRSR_UARTECR);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTRSR_UARTECR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTFR);
    comparison = (actual == 0x00000090);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTFR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000090, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTILPR);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTILPR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTIBRD);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTIBRD reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTFBRD);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTFBRD reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTLCR_H);
    comparison = (actual == 0x00000000);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTLCR_H reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTCR);
    comparison = (actual == 0x00000300);
    /* if (!comparison) {
        printf("   [UARTPL011: Register UARTCR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000300, actual);
    } */
    returnValue &= comparison;

    actual =  *(regs+UARTIFLS);
    comparison = (actual == 0x00000012);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTIFLS reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000012, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTIMSC);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTIMSC reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTRIS);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTRIS reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTMIS);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTMIS reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTICR);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTICR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTDMACR);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTDMACR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTTCR);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTTCR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTITIP);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTITIP reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTITOP);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTITOP reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTTDR);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTTDR reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPeriphID0);
    comparison = (actual == 0x00000011);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPeriphID0 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000011, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPeriphID1);
    comparison = (actual == 0x00000010);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPeriphID1 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000010, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPeriphID2);
    comparison = (actual == 0x00000034);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPeriphID2 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000034, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPeriphID3);
    comparison = (actual == 0x00000000);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPeriphID3 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000000, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPCellID0);
    comparison = (actual == 0x0000000D);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPCellID0 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x0000000D, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPCellID1);
    comparison = (actual == 0x000000F0);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPCellID1 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x000000F0, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPCellID2);
    comparison = (actual == 0x00000005);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPCellID2 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x00000005, actual);
    }*/
    returnValue &= comparison;

    actual =  *(regs+UARTPCellID3);
    comparison = (actual == 0x000000B1);
    /*if (!comparison) {
        printf("   [UARTPL011: Register UARTPCellID3 reset value incorrect, expected 0x%x, actual 0x%x.]\n",
            0x000000B1, actual);
    }*/
    returnValue &= comparison;

    return returnValue;
}
