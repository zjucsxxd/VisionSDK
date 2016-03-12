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
#    2013-08-05
#
#  LANGUAGE
#    make
#
##############################################################################

GCC_APP =        $(GEN_APP)
GCC_APP_SRCS:=   $(KERNEL_LIB_SRCS)
GCC_APP_LIBS:=   $(GEN_APP_LIBS)
GCC_APP_GRAPH:=	$(ACF_GRAPHS)

GCC_LIB =        $(GEN_LIB)
GCC_LIB_SRCS:=   $(GEN_LIB_SRCS)
GCC_LIB_LIBS:=   $(GEN_LIB_LIBS)

GCC_DEFS :=      $(GEN_DEFS)
GCC_INCS :=      $(GEN_INCS)

GCC_DEFS +=	\
		-DACF_KERNEL_METADATA

GCC_INCS +=	\
		-I $(SDK_ROOT)/libs/x86/acf_offline/include 	\
		-I $(SDK_ROOT)/libs/apu/common/include		\
		-I $(SDK_ROOT)/libs/apu/common/include/driver

# compiler specific options for platform, not in headdep
GCC_CCOPTS +=	\
		--include apu2_kernel_db_lib.h \
		#--include acf_autokernel_inc.h
		
GCC_CXOPTS +=
GCC_ASOPTS +=
GCC_LDOPTS +=

########## Load generation settings
GCC_LOAD_BINS =	$(LOAD_BINS)
GCC_LOAD_OBJS =	$(LOAD_OBJS)
GCC_LOAD_SRCS =	$(LOAD_SRCS)
GCC_LOAD_INCS =	$(LOAD_INCS)
GCC_LOAD_LDOPTS =$(LOAD_LDOPTS)
