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
NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)
OS_TYPE :=	Linux

C2_APP =	$(X86_APP)
C2_APP_SRCS:=	$(X86_APP_SRCS)
C2_APP_LIBS:=	$(X86_APP_LIBS)

C2_LIB =	$(X86_LIB)
C2_LIB_SRCS:=	$(X86_LIB_SRCS)
C2_LIB_LIBS:=	$(X86_LIB_LIBS)
C2_LIB_ARCS:=	$(X86_LIB_ARCS)

C2_DEFS :=	$(X86_DEFS)
C2_INCS :=	$(X86_INCS)
C2_CCOPTS :=    $(X86_CCOPTS)

MCU = 		cortex-a9

##############################################################################
PLATFORM =	zc702

#X86_DIR = $(shell export PATH='$(PATH)'; which $(C0_CC) | sed 's|/bin/.*||; \
#	  s|/cygdrive/\(.\)|\1:|')
#X86_VERSION = "$(shell $(C0_CC) --version | grep ^arm | sed 's/^.* //g')"

SYS := $(shell echo $$OSTYPE)
ifeq ($(SYS),)
  NBUILD_PLATFORM :=	linux
else
ifneq ($(findstring solaris,$(SYS)),)
  NBUILD_PLATFORM := 	solaris
else
ifneq ($(findstring linux,$(SYS)),)
  NBUILD_PLATFORM :=	linux
else
ifneq ($(findstring INTEGRITY,$(SYS)),)
  NBUILD_PLATFORM :=	integrity
else
  NBUILD_PLATFORM :=	cygwin
endif
endif
endif
endif

ifneq ($(findstring cygwin,$(NBUILD_PLATFORM)),)
  COMPILER_PREFIX := i686-pc-mingw32-
endif

C2_CC :=	$(COMPILER_PREFIX)g++ -c
C2_CX :=	$(COMPILER_PREFIX)g++ -c
C2_AS :=	$(COMPILER_PREFIX)gcc -c
C2_LD :=	$(COMPILER_PREFIX)gcc
C2_AR :=	$(COMPILER_PREFIX)ar rcs

C2_PROMPT :=	offline/X86

# compiler specific options for core
C2_CCOPTS +=	$(X86_CCOPTS)
C2_CXOPTS +=
C2_ASOPTS +=
C2_LDOPTS +=	-lstdc++

include 	$(SDK_ROOT)/build/nbuild/.C2.mk

clean:: 
	  rm -f
