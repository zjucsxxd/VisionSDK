##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#   Geometry Kernels build
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-11-09
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../s32v234_sdk

APU_LIB = geometry_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################
VPATH += ../src

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I../src                                                                 \
    -I$(SDK_ROOT)/kernels/apu/arithmetic_kernels/src                         \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                                \
    apu_rotate_180.cpp                                                         \
    apu_rotate_180_impl.cpp                                                    \
    remap_bilinear.cpp                                                         \
	remap_bilinear_impl.cpp                                                    \
    apu_bilinear_interpolation_kernel.cpp                                      \
    apu_bilinear_interpolation_kernel_impl.cpp                                 \
    apu_offset_select_kernel.cpp                                               \
    apu_offset_select_kernel_impl.cpp

APU_LIB_LIBS = $(SDK_ROOT)/kernels/apu/arithmetic_kernels/$(ODIR)/arithmetic_kernels.a

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

