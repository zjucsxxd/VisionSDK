/*
 * File:		printf.h
 * Purpose:		The standard C library routine printf(), but without
 *				all the baggage.
 */
 

#ifdef __cplusplus 
extern "C"
{
#endif

int printf (const char *fmt, ...);
int sprintf (char *s, const char *fmt, ...);


#ifdef __cplusplus 
}
#endif