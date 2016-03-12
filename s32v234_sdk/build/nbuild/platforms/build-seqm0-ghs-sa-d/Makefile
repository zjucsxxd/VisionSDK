##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2015-02-25
#
#  LANGUAGE
#    make
#
##############################################################################

all::

ignore:

NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)

include		../BUILD.mk

##############################################################################
# Standard search path for sources
##############################################################################
VPATH +=	\
		../src

# nbuild packages
include		$(SDK_ROOT)/build/nbuild/toolchains/arm-none-linux-gnueabi.mk
include         $(SDK_ROOT)/build/nbuild/toolchains/arm-sa-ghs.mk
include         $(SDK_ROOT)/build/nbuild/sub.mk
include         $(SDK_ROOT)/build/nbuild/tags.mk
include         $(SDK_ROOT)/build/nbuild/headdep.mk
