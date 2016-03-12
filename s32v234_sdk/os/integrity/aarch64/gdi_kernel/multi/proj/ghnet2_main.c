/*
 *                          Copyright 2000-2013                      
 *                         Green Hills Software                      
 *
 *    This program is the property of Green Hills Software.  Its
 *    contents constitute the proprietary information of Green Hills
 *    Software.  Your use of this program shall be in accordance with
 *    the shrink-wrap or click-through license agreement accompanying
 *    it or the executed license agreement by and between you or your
 *    company and Green Hills Software, which supersedes the former.
 *    If you have not agreed to the terms of a license agreement with
 *    Green Hills Software, do not use this program and promptly
 *    contact Green Hills Software.
 *
 */

#include <INTEGRITY.h>

extern Error TCPIPEntry(void);
char __NoLibSocketForInitialTask;
DISABLE_HEAP_EXTEND();

/* If a stack name has been defined, use/declare it */
#ifdef __GHS_TCPIP_STACK_NAME
char *__ghs_tcpip_stack_name = __GHS_TCPIP_STACK_NAME;
#endif

#ifdef DHCP_SUPPRESS_CLIENT_ID
char GHNet_DHCP_SuppressClientID;
#endif /* DHCP_SUPPRESS_CLIENT_ID */

/* Entrypoint for GHNet2 TCP/IP Stack running in protected AddressSpace */
int main(void)
{
#if !defined(INTEGRITY_SIMULATE) && !defined(GENERIC_SIMULATE) /* Don't start
	under simulation, because socket emulation obviates the stack. */
    CheckSuccess(TCPIPEntry());
#endif /* ifndef INTEGRITY_SIMULATE */
    Exit(0);
}
