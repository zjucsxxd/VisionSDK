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

// Minimal memory/string functions.

#include "../include/str.h"

long strlen(const char* s)
{
  int len = 0;

  while (s != 0 && *s != '\0') {
    len++;
    s++;
  }

  return len;
}

char *strcpy(char *dest, const char *src)
{
    int i = 0;
    for (i = 0; i < strlen(src); ++i) {
        dest[i] = src[i];
    }
    return dest;
}

int
strcmp ( const char *str1, const char *str2 )
{
   while ( *str1 || *str2 ) {
       if ( *str1 != *str2 ) return *str1 - *str2;
       ++str1;
       ++str2;
   }
   return 0;
}

/* atoi:  convert characters s to n */
int atoi(char s[])
{
    int n = 0;
    char a = 0;
    while (s != 0 && *s != '\0') {
        a = *s;
        if (a >= '0' && a <= '9')
        {
            n = n*10 + (a - '0');
        } else {
            break;
        }
        *s++;
    }
    return n;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i = 0, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */

    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void ftoa(double n, char s[], int precision)
{
    int i = 0, sign;
    long long int d = 0, e = 0;

    if ((sign = (int)n) < 0)  /* record sign */
        n = -n;          /* make n positive */

    e = (int)n;
    n -= e; //Leaving only decimals
    // Multiply the value based on precision
    for (i = 0; i < precision; i++) {
       n *= 10.0;
    }
    d = (int)n;
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = d % 10 + '0';   /* get next digit */
    } while ((d /= 10) > 0);     /* delete it */

    if (precision != 0)
        s[i++] = '.';

    do {       /* generate digits in reverse order */
        s[i++] = e % 10 + '0';   /* get next digit */
    } while ((e /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itola(long int n, char s[])
{
    int i = 0;
    long int sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */

    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itolla(long long int n, char s[])
{
    int i = 0;
    long long int sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */

    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* itox:  convert n to characters in s */
void itox(unsigned int n, char s[])
{
    int i = 0;

    do {       /* generate digits in reverse order */
        s[i++] = (n % 16)["0123456789ABCDEF"];   /* get next digit */
    } while ((n /= 16) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
}

/* itox:  convert n to characters in s */
void itolx(unsigned long int n, char s[])
{
    int i = 0;

    do {       /* generate digits in reverse order */
        s[i++] = (n % 16)["0123456789ABCDEF"];   /* get next digit */
    } while ((n /= 16) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
}

/* itox:  convert n to characters in s */
void itollx(unsigned long long int n, char s[])
{
    int i = 0;

    do {       /* generate digits in reverse order */
        s[i++] = (n % 16)["0123456789ABCDEF"];   /* get next digit */
    } while ((n /= 16) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
}


/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


