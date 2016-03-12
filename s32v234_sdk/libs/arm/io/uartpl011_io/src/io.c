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

// Minimal standard I/O functions.
//

//#include <stdarg.h>
typedef __builtin_va_list va_list;
#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,l)	__builtin_va_arg(v,l)

#include "../include/io.h"
#include "../include/str.h"
#include "../include/uartpl011_driver.h"
void abort(void)
{ 
  while(1);
}

static uart_cntl_t* uart_cntl;

void ioSetUART(void* cntl)
{
    uart_cntl = (uart_cntl_t*)cntl;
}

void flush_buffer(void)
{
    uartpl011_flush_buffer(uart_cntl);
}

int putchar(int c)
{
    tx(uart_cntl, (unsigned char) c);
    return 0;
}

int puts(const char* s)
{
    while (s != 0 && *s != '\0') {
        putchar(*s++);
    }
    return 0;
}

int isdigit(const int p)
{
    switch (p) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 1;
        default:
            break;
    }

    return 0;
}

// Adapted from minimal printf(), page 156, K&R, 2nd ed.
// We do even less here than in K&R, handling only integer
// and string data. Brought to you by the magic of varargs.
int printf(const char* fmt, ...)
{
    va_list ap;
    const char* p;
    char* sval;
    char ibuf[20];
    char cval;
    int ival;
    long int lival;
    long long int llival;

    unsigned int uival;
    unsigned long int luival;
    unsigned long long int lluival;
    double fval;
    int precision = 3;

    va_start(ap, fmt); // make ap point to first unnamed arg */
    for (p=fmt; p != 0 && *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        ++p;
        //Consume number formatting as not supported
        while (isdigit(*p)) {
            ++p;
        }
        // Get decimal places for precision
        if (*p == '.')
        {
            int i = 0;
            ++p;
            while (isdigit(*p)) {
                ibuf[i++] = *p;
                ++p;
            }
            ibuf[i] = '\0';
            precision = atoi(ibuf);
        } else {
            precision = 3;
        }

        switch (*p) {
        case 'f':
            fval = va_arg(ap, double);
            ftoa(fval, ibuf, precision);
            puts(ibuf);
            break;
        case 'l':
            switch (*++p) {
            case 'l':
                switch (*++p) {
                case 'd':
                case 'i':
                    llival = va_arg(ap, long long int);
                    itoa(llival, ibuf);
                    puts(ibuf);
                    break;

                case 'u':
                    lluival = va_arg(ap, unsigned long long int);
                    itoa(lluival, ibuf);
                    puts(ibuf);
                    break;
                case 'x':
                case 'X':
                    lluival = va_arg(ap, unsigned long long int);
                    itox(lluival, ibuf);
                    puts(ibuf);
                    break;
                default:
                    putchar(*p);
                    break;
                }
                break;

            case 'd':
            case 'i':
                lival = va_arg(ap, long int);
                itoa(lival, ibuf);
                puts(ibuf);
                break;

            case 'u':
                luival = va_arg(ap, unsigned long int);
                itoa(luival, ibuf);
                puts(ibuf);
                break;
            case 'x':
            case 'X':
                luival = va_arg(ap, unsigned long int);
                itox(luival, ibuf);
                puts(ibuf);
                break;
            default:
                putchar(*p);
                break;
            }
            break;
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            itoa(ival, ibuf);
            puts(ibuf);
            break;

        case 'u':
            uival = va_arg(ap, unsigned int);
            itoa(uival, ibuf);
            puts(ibuf);
            break;
        case 'x':
        case 'X':
            uival = va_arg(ap, unsigned int);
            itox(uival, ibuf);
            puts(ibuf);
            break;

        case 'c':
            cval = va_arg(ap, int);
            putchar(cval);
            break;
        case 's':
            for (sval= va_arg(ap, char *); sval != 0 && *sval != '\0'; sval++) {
              putchar(*sval);
            }
            break;

        default:
            putchar(*p);
            break;
        }
    }

    va_end(ap);

    return 0;
}

