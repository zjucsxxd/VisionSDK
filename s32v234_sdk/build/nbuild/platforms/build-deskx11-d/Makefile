##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    full featured Makefile for desk builds (linux/x11) using nbuild packages.
#    internal use only
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    2011-02-24
#
#  LANGUAGE
#    make
#
##############################################################################

all::

NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)

include		../BUILD.mk

OPENCV_ROOT = $(SDK_ROOT)/ocv/linux-x86
FFMPEG_ROOT = $(SDK_ROOT)/ffmpeg/linux-x86

VPATH += ../src
VPATH += ../graphs

C0_APP =	$(ARM_APP)
C0_APP_SRCS:=	$(ARM_APP_SRCS)
C0_APP_LIBS:=	$(ARM_APP_LIBS)

C0_LIB =	$(ARM_LIB)
C0_LIB_SRCS:=	$(ARM_LIB_SRCS)
C0_LIB_LIBS:=	$(ARM_LIB_LIBS)

C0_DEFS :=	$(ARM_DEFS)
C0_INCS :=	$(ARM_INCS)

C0_LDOPTS :=	$(ARM_LDOPTS)
C0_CCOPTS :=	$(ARM_CCOPTS)
C0_CXOPTS :=	$(ARM_CXOPTS)

##############################################################################

##############################################################################
# Legacy variables from CGV build environment
##############################################################################
GBOFILE = 	GBOpts_APEX2_Pseudo_FPGA_Valid
APPLICATION =	ICP
CHIP =		2301
SCAT =		SCAT16_APEX2
MKSDK =		NONE
##############################################################################

C0_INCS +=	-I.

run: all
	./$(ARM_APP)

# ACF Specific defines (may also go into BUILD.mk)

C0_DEFS +=	\
		-D__GNU__					\
		-D NDEBUG					\
		-D GBO_FILE=\"$(GBOFILE).h\"	\

# compiler specific options for platform, not in headdep
C0_CCOPTS += 	-g
ifeq ($(MK_WB_BUILD),)
C0_CXOPTS +=	-fno-rtti	-fpermissive		\
		-g
endif
C0_ASOPTS +=	-g

include	$(SDK_ROOT)/build/nbuild/platform.mk

ifeq ($(NBUILD_PLATFORM),linux)
C0_LDOPTS +=	-lpthread -lrt -L$(OPENCV_ROOT)/lib/ -L$(FFMPEG_ROOT)/lib/
endif

# nbuild packages
include         $(SDK_ROOT)/build/nbuild/toolchains/x86-x11-linux-gnu.mk
include         $(SDK_ROOT)/build/nbuild/sub.mk
include         $(SDK_ROOT)/build/nbuild/tags.mk
include         $(SDK_ROOT)/build/nbuild/headdep.mk
