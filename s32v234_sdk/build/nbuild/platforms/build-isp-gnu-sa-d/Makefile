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
C0_DEFS +=	\
		
C0_INCS +=	\
		-I.
		
##############################################################################
# where to find the sources
##############################################################################

VPATH +=	

# compiler specific options for platform, not in headdep
C0_CCOPTS +=	 

C0_ASOPTS +=	

# nbuild packages
include		$(SDK_ROOT)/build/nbuild/toolchains/arm-none-linux-gnueabi.mk

ifneq ($(IPUS_APP),)
include		$(SDK_ROOT)/build/nbuild/toolchains/ipus-sa-gnu.mk
endif

ifneq ($(IPUV_APP),)
  include		$(SDK_ROOT)/build/nbuild/toolchains/ipuv-sa-gnu.mk
endif

include		$(SDK_ROOT)/build/nbuild/isp_tools/isp-graphgen.mk
include		$(SDK_ROOT)/build/nbuild/sub.mk
#include	$(SDK_ROOT)/build/nbuild/tags.mk
include		$(SDK_ROOT)/build/nbuild/headdep.mk
