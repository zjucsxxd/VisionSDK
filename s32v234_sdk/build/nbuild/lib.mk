##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    legacy make package to compile a library, updated to use new _core
#    package (2011)
#
#  PARAMETERS
#    LIB	name of the library
#    LIB_SRCS	source files (.c,.C) for the library
#    LIB_LIBS   (optional) full paths of required sub-libs
#    LIB_INCS   include paths (beside of the paths of sub-libs)
#    LIB_DEFS   compiler switches for defines
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    2008-12-12 (revised 2011-04-05)
#
#  LANGUAGE
#    make
#
#  ID
#    $Id: lib.mk,v 1.17 2008/12/12 12:10:06 norberts Exp $
#
##############################################################################

ifndef _LIB_MK
_LIB_MK =	true

ifeq ($(origin TOOLS),undefined)
  $(error error: TOOLS undefined)
endif

TOOL_CC :=	gcc -c
TOOL_CX :=	g++ -c
TOOL_AS :=	gcc -c
TOOL_LD :=	gcc
TOOL_AR :=	ar rcs

TOOL_PROMPT :=	tool

# translate old naming for new core package
TOOL_LIB = 	$(LIB)
TOOL_LIB_SRCS =	$(LIB_SRCS)
TOOL_LIB_LIBS =	$(LIB_LIBS)
TOOL_INCS =	$(LIB_INCS)
TOOL_DEFS =	$(LIB_DEFS)

# rest is inherited from meta package
include $(TOOLS)/nbuild/core.mk
include	$(TOOLS)/nbuild/.TOOL.mk

endif
