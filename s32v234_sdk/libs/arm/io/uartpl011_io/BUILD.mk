##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    UART pl011 I/O library for standalone A53 application
#
#  AUTHOR
#    Rostislav Hulik + ASTC
#
#  DATE
#    2014-07-22
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../../../s32v234_sdk

ARM_LIB =	libpl011.a

##############################################################################
# libacf2host.a
##############################################################################
ARM_LIB_SRCS +=	\
		uartpl011_driver.c 	\
		io.c			\
		str.c			\
		init.c

ARM_INCS +=	\
		

ARM_DEFS +=		\

##############################################################################
