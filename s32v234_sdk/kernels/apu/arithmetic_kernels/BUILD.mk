##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    Arithmetic Kernels
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

APU_LIB = arithmetic_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                              \
    apu_add.cpp                                                              \
    apu_add_impl.cpp                                                         \
    apu_max.cpp                                                              \
    apu_max_impl.cpp                                                         \
    apu_difference_kernel.cpp                                                  \
    apu_difference_kernel_impl.cpp                                             \
    apu_dot_multiplic_kernel.cpp                                               \
    apu_dot_multiplic_kernel_impl.cpp                                          \
    apu_dot_division_kernel.cpp                                                \
    apu_dot_division_kernel_impl.cpp                                           \
    apu_dot_sqr_kernel.cpp                                                     \
    apu_dot_sqr_kernel_impl.cpp

#    apu_pixel_a1.cpp                                                           \
#    apu_pixel_a1_impl.cpp                                                      \

	
APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

