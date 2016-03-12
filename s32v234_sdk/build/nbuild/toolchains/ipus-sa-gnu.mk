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
#    2015-01-08
#
#  LANGUAGE
#    make
#
##############################################################################
all::

NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)
OS_TYPE :=	None

C4_APP =	$(IPUS_APP)
C4_APP_SRCS:=	$(IPUS_APP_SRCS)

C4_DEFS :=	$(IPUS_DEFS)
C4_INCS :=	$(IPUS_INCS)

##############################################################################
C4_DEFS +=
C4_INCS +=
C4_ASOPTS +=
		
include	$(SDK_ROOT)/build/nbuild/platform.mk

C4_AS :=	$(SDK_ROOT)/tools/isp/ipu/as-IPUS.exe
C4_OD :=	$(SDK_ROOT)/tools/isp/ipu/objdump-IPUS.exe
C4_SR2ROM := 	$(SDK_ROOT)/tools/sr2rom/sr2rom

C4_PROMPT :=	ipus/sa

include 	$(SDK_ROOT)/build/nbuild/.C4.mk

clean::
	rm -f *.su
