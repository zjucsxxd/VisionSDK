##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    resizing kernels 
#
#  AUTHOR
#    Anca Dima & Igor Aleksandrowicz
#
#  DATE
#    2014-08-06
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../s32v234_sdk

APU_LIB = resizing_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                              \
    apu_downsample.cpp                                                       \
    apu_downsample_impl.cpp                                                  \
    apu_upsample.cpp                                                         \
    apu_upsample_impl.cpp                                                    \
    apu_resize_vertical.cpp                                                  \
    apu_resize_vertical_impl.cpp                                             \
    passthrough_kernel.cpp													 \
	passthrough_kernel_impl.cpp

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

