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
all::

NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)
OS_TYPE :=	Linux

C0_APP =	$(ARM_APP).elf
C0_APP_SRCS:=	$(ARM_APP_SRCS)
C0_APP_LIBS:=	$(ARM_APP_LIBS)

C0_LIB =	$(ARM_LIB)
C0_LIB_SRCS:=	$(ARM_LIB_SRCS)
C0_LIB_LIBS:=	$(ARM_LIB_LIBS)
C0_LIB_ARCS:=	$(ARM_LIB_ARCS)

C0_DEFS :=	$(ARM_DEFS)
C0_INCS :=	$(ARM_INCS)
C0_CCOPTS :=	$(ARM_CCOPTS)
C0_CXOPTS :=	$(ARM_CXOPTS)
C0_LDOPTS :=    -L$(OPENCV_ROOT)/lib/ -L$(FFMPEG_ROOT)/lib/ $(ARM_LDOPTS)


##############################################################################
PLATFORM =	s32v234_ce


C0_DEFS +=	\
		-D__GNU__					\
		-D__LINUX__					\
		-DARM						\
		-D__arm__					\
		-D NDEBUG					\
		-D __ARMV8					\
		-D CV220X_$(CPU) 				\
		-D GNUARM#

C0_INCS +=	\
		-I.						\

# compiler specific options for platform, not in headdep
C0_CCOPTS +=	\
		-O0						\
		-g						\
		-funsigned-bitfields				\
		-ffunction-sections				\
		-Wall						\
		-Wextra						\
		-mcpu=cortex-a53                                \
		-pedantic					\
		-std=c99

C0_CXOPTS +=	\
		-O0						\
		-g						\
		-funsigned-bitfields				\
		-ffunction-sections				\
		-fno-use-cxa-atexit				\
		-Wall						\
		-Wextra						\
		-mcpu=cortex-a53                                \
		-pedantic					\
		-std=gnu++0x					

C0_ASOPTS +=	\
		-mcpu=cortex-a53                                \

C0_LDOPTS +=	\
		-L$(SDKlib)					\
		-Wl,--cref,--gc-sections	\


include	$(SDK_ROOT)/build/nbuild/platform.mk

ifeq ($(NBUILD_PLATFORM),linux)
C0_LDOPTS +=	-lpthread -lrt -lstdc++
endif

GCC_DIR = $(shell export PATH='$(PATH)'; which $(C0_CC) | sed 's|/bin/.*||; \
	  s|/cygdrive/\(.\)|\1:|')
GCC_VERSION = "$(shell $(C0_CC) --version | grep ^arm | sed 's/^.* //g')"

GNU_PREFIX=aarch64-linux-gnu-
CROSS_COMPILE=aarch64-linux-gnu-

C0_CC :=	$(CROSS_COMPILE)gcc -c
C0_CX :=	$(CROSS_COMPILE)g++ -c
C0_AS :=	$(CROSS_COMPILE)g++ -c
C0_LD :=	$(CROSS_COMPILE)g++
C0_AR :=	$(CROSS_COMPILE)ar

C0_PROMPT :=	arm64/gnu

C0_AROPTS += rcs
C0_CXOPTS +=
C0_ASOPTS +=
C0_LDOPTS += -lpthread

include 	$(SDK_ROOT)/build/nbuild/.C0.mk

clean::
	rm -f *_log.txt