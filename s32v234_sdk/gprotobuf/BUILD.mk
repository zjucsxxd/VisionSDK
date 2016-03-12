##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    GDI test
#
#  AUTHOR
#    Samuel Mudrik
#
#  DATE
#    2013-11-14
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../s32v234_sdk
GTEST_ROOT=$(SDK_ROOT)/../gprotobuf_src

# scarecrow for nbuild, as it needs some APP name
ARM_LIB = libprotobuf.a

# scarecrow for nbuild, sa it needs some APP_SRCS
ARM_APP_SRCS = 0

# all the compilation is in fact done by autoconf.mk
include 	$(SDK_ROOT)/build/nbuild/autoconf.mk


