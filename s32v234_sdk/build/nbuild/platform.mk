##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    centralize treatment of some platform dependent stuff
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    $Date: 2008/12/17 14:09:46 $
#
#  LANGUAGE
#    make
#
#  ID
#    $Id: platform.mk,v 1.21 2008/12/17 14:09:46 norberts Exp $
#
##############################################################################

ifndef _PLATFORM_MK
_PLATFORM_MK =	true

SHELL = /bin/bash

##############################################################################
# determine platform and give it a simple name
##############################################################################

SYS := $(shell echo $$OSTYPE)
BITS := $(shell arch)
HNAME := $(shell echo $$HOSTNAME)

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

# bitwidth of the (linux) system
ifeq ($(BITS),x86_64)
  NBUILD_PLATBITS =	64
else
  NBUILD_PLATBITS =	32
endif

# some explicit hosts in MUC
ifneq ($(findstring -zwg18,$(HNAME)),)
  NBUILD_PLATFORM :=	linux
  NBUILD_COLOR ?=	no
endif
ifneq ($(findstring ammer,$(HNAME)),)
  NBUILD_PLATFORM :=	linux
endif

export NBUILD_PLATFORM
export NBUILD_PLATBITS

debugplat:
	@echo OSTYPE = $(SYS)
	@echo HOSTNAME = $(HNAME)
	@echo HOSTTYPE = $(BITS)
	@echo NBUILD_PLATFORM = $(NBUILD_PLATFORM)
	@echo NBUILD_PLATBITS = $(NBUILD_PLATBITS)


##############################################################################
# some assertions
##############################################################################

_EMPTY :=
_SPACE :=	$(_EMPTY) $(_EMPTY)

ifeq ($(findstring $(_SPACE),$(shell pwd)),$(_SPACE))
  $(error error: spaces in directory names (here: $(shell pwd))\
    not supported)
endif


##############################################################################
# tools that may behave differently
##############################################################################

# patch :=	patch
#
# ifeq ($(NBUILD_PLATFORM),solaris)
#   patch :=	gpatch
# endif

ifeq ($(NBUILD_PLATFORM),cygwin)
NBUILD_COLOR ?= 	yes
endif

ifeq ($(NBUILD_PLATFORM),linux)
NBUILD_COLOR ?= 	yes
endif

# ifeq ($(findstring patch 2.5,$(shell $(patch) --version | head -1)),)
#   $(error error: wrong version of tool "patch")
# endif

ifeq ($(findstring GNU Awk 4,$(shell gawk --version | head -1)),)
  ifeq ($(findstring GNU Awk 3,$(shell gawk --version | head -1)),)
    $(error error: wrong version of tool "gawk")
  endif
endif

ifeq ($(NBUILD_PLATBITS),64)
XLIBPATH =	/usr/X11R6/lib64
else
XLIBPATH =	/usr/X11R6/lib
endif


##############################################################################
# colorized output
##############################################################################

ifeq ($(TERM),dumb)
NBUILD_COLOR := no
endif

ifeq ($(EMACS),t)
NBUILD_COLOR := no
endif

ifeq ($(NBUILD_PLATFORM),cygwin)
ifeq ($(findstring bash,$(BASH)),)
NBUILD_COLOR := no
endif
endif

ifeq ($(NBUILD_COLOR),yes)
COLNIL :=	\033[0m
COLRED :=	\033[1;31m
COLBLU :=	\033[1;34m
COLMAG :=	\033[1;35m
COLGRE :=	\033[1;32m
COLCYA :=	\033[1;36m
COLBLK :=	\033[0;1;38m
endif

debugcolor:
	@echo -ne "$(COLRED)red $(COLBLU)blu $(COLMAG)mag $(COLBLK)blk "
	@echo -e "$(COLCYA)cyan $(COLGRE)green$(COLNIL)"

##############################################################################
# executable file name extension
##############################################################################

ifeq ($(NBUILD_PLATFORM),cygwin)
EXE_EXT = .exe
endif

ifeq ($(NBUILD_PLATFORM),linux)
EXE_EXT =
endif

##############################################################################
# verbosity
##############################################################################

V ?=	0
ifeq ($(V),0)
  NBQ =		@
  nbmsg =	@echo "  "$(1) ;
endif

##############################################################################
# use translibs
##############################################################################

NBUILD_TL ?=	1

endif
