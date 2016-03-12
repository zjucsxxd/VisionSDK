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

ARM_LIB =	liblinflex.a

##############################################################################
# libacf2host.a
##############################################################################
ARM_LIB_SRCS +=	\
		uartlinflex_driver.c 	\
		printf.c

ARM_INCS +=	\
    -I$(SDK_ROOT)/platform/s32_v234                                      \
		

ARM_DEFS +=		\

##############################################################################
