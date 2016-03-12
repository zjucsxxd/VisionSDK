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
 * io.h
 *
 * Minimal standard I/O functions.
 */

#ifndef _IO_H_
#define _IO_H_
//#include <stdio.h>

/* Set IO device that will handle the string output.
 * \param cntl Pointer to a device configuration, usually a UART
 */

#ifdef __cplusplus 
extern "C"
{
#endif
void ioSetUART(void* cntl);

/* Flush character buffer at end of test */
void flush_buffer(void);

/* Output a single character.
 * \param c a single character
 * \return 0 for succcess
 */
int putchar(int c);

/* Output a string.
 * \param s a string
 * \return 0 for succcess
 */
int puts(const char* s);

/* Output a string printf style replacing the %s in
 * string with supplied arguments.
 * Only supports %d and %s. Unrecognised formats will be printed
 * \param fmt - string with format characters
 * \param variable length argument to be placed into string
 * \return 0 for success
 */
int printf(const char* fmt, ...);
#ifdef __cplusplus 
}
#endif

#endif
