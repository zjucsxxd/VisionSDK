/*
 * -----------------------------------------------------------------------------
 * Copyright (C) Australian Semiconductor Technology Company (ASTC). 2009-2012.
 * All Rights Reserved.
 *
 * This is unpublished proprietary source code of the Australian Semiconductor
 * Technology Company (ASTC).  The copyright notice does not evidence any actual
 * or intended publication of such source code.
 * -----------------------------------------------------------------------------
 */

/*
 * str.h
 *
 * Simple header providing some string handling functionality
 */
#ifndef __STR_H_
#define __STR_H_
//#include <string.h>

/* Return the length of a provided string.
 * This iterates over the string looking for termination
 * character '\0'.
 * \param s string to check
 * \return length of string
 * \return 0 if s is NULL
 */
/*int strlen(const char* s);*/

char *strcpy(char *dest, const char *src);

int strcmp ( const char *str1, const char *str2 );

/* Convert double to decimal string representation and return in s.
 * If the number is negative a '-' will be prepended.
 * \param n number to convert (forced to 6 decimal places)
 * \param s character array filled with converted number
 */
void ftoa(double n, char s[], int precision);

/* Convert string of a number to an integer.
 * \param s character array represeint an integer
 * \return integer
 */
int atoi(char s[]);

/* Convert integer to decimal string representation and return in s.
 * If the number is negative a '-' will be prepended.
 * \param n number to convert
 * \param s character array filled with converted number
 */
void itoa(int n, char s[]);
void itola(long int n, char s[]);
void itolla(long long int n, char s[]);

/* Convert integer to hexadecimal string representation and return in s.
 * \param n number to convert
 * \param s character array filled with converted number
 */
void itox(unsigned int n, char s[]);
void itolx(unsigned long int n, char s[]);
void itollx(unsigned long long int n, char s[]);

/* Reverse a string in place.
 * \param s string that will be reversed
 */
void reverse(char s[]);

#endif /*__STR_H_*/
