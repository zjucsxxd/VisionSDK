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
#    Rostislav Hulik
#
#  DATE
#    2015-03-04
#
#  LANGUAGE
#    make
#
##############################################################################
all::

NBMAKEFILE =    Makefile ../BUILD.mk
ODIR :=         $(shell basename `pwd`)
OS_TYPE :=      None

C0_APP =        $(ARM_APP).elf
C0_APP_SRCS:=   $(ARM_APP_SRCS)


C0_LIB =        $(ARM_LIB)
C0_LIB_SRCS:=   $(ARM_LIB_SRCS)
C0_LIB_LIBS:=   $(ARM_LIB_LIBS)
C0_LIB_ARCS:=   $(ARM_LIB_ARCS)

C0_DEFS :=      $(ARM_DEFS)
C0_INCS :=      $(ARM_INCS)
C0_CCOPTS :=    $(ARM_CCOPTS)
C0_CXOPTS :=    $(ARM_CXOPTS)
C0_LDOPTS :=    -L$(OPENCV_ROOT)/lib/ $(ARM_LDOPTS) -L$(SDK_ROOT)/ocv/standalone-arm64/share/OpenCV/3rdparty/lib

##############################################################################
PLATFORM =      s32vpa53

C0_DEFS +=                                                                   \
    -DMPCIMXVS4                                                              \
    -DMPCIS32V234                                                            \
    -DLINARO                                                                 \
    -DAUTOSAR_OS_NOT_USED                                                    \
    -DSINTRAM                                                                \
	-D__ARMV8                                                                \
    -DDERIVATIVE_IMXVS4                                                      \
    -DDERIVATIVE_S32V234                                                     \
	-D__STANDALONE__
    
C0_INCS +=                                                                   \
    -I.                                                                      \
    -I$(SDK_ROOT)/libs/arm/startup/v234ce_standalone/include                 \
    -I$(SDK_ROOT)/libs/arm/io/uartlinflex_io/include                         \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include			                 \
	-I$(SDK_ROOT)/libs/arm/io/i2c/include

C0_CCOPTS +=                                                                 \
    -ggdb3                                                                   \
    -mcpu=cortex-a53                                                         \
    -nostdlib                                                                \
	-fno-builtin                                                             \
    -fno-exceptions                                                          \
    -std=c99


C0_CXOPTS +=                                                                 \
    -ggdb3                                                                   \
    -mcpu=cortex-a53                                                         \
	-nostdlib                                                                \
	-fno-builtin                                                             \
    -fno-exceptions                                                          \
    -std=gnu++0x

C0_ASOPTS += -mcpu=cortex-a53 -g

C0_LDOPTS += -T $(SDK_ROOT)/build/nbuild/platforms/build-v234ce-gnu-sa-d/linker.lds -lgcc -lc -lm -lrdimon -Wl,-Map=binary.map


C0_APP_LIBS +=                                                               \
	$(SDK_ROOT)/libs/arm/startup/v234ce_standalone/$(ODIR)/libv234ce.a       \
	$(SDK_ROOT)/libs/arm/io/i2c/$(ODIR)/libi2c.a                             \
	$(SDK_ROOT)/libs/arm/io/uartlinflex_io/$(ODIR)/liblinflex.a              \
	
C0_APP_LIBS+=   $(ARM_APP_LIBS)
	
include	$(SDK_ROOT)/build/nbuild/platform.mk

GCC_DIR = $(shell export PATH='$(PATH)'; which $(C0_CC) | sed 's|/bin/.*||; \
	  s|/cygdrive/\(.\)|\1:|')
GCC_VERSION = "$(shell $(C0_CC) --version | grep ^arm | sed 's/^.* //g')"

#CROSS_COMPILE=aarch64-linux-gnu-
CROSS_COMPILE=aarch64-none-elf-

C0_CC :=  $(CROSS_COMPILE)gcc -c
C0_CX :=  $(CROSS_COMPILE)g++ -c
C0_AS :=  $(CROSS_COMPILE)gcc -c
C0_LD :=  $(CROSS_COMPILE)g++
C0_AR :=  $(CROSS_COMPILE)ar rcs

C0_PROMPT := arm64/sa

C0_CCOPTS += 
C0_AROPTS +=
C0_CXOPTS +=
C0_ASOPTS +=
C0_LDOPTS += 

include $(SDK_ROOT)/build/nbuild/.C0.mk

	
clean::
	rm -f *.su *_log.txt
	

	