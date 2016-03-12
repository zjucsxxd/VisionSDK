##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    optical_flow_kernel
#
#  AUTHOR
#    Anca Dima
#
#  DATE
#    2014-03-26
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../s32v234_sdk

APU_LIB = optical_flow_kernel.a

##############################################################################
# kernel lib
##############################################################################

APU_INCS +=                                                                  \
    -I../src                                                                 \
    -I$(SDK_ROOT)/libs/arm/utils/common/include                                    \
    -I$(SDK_ROOT)/kernels/apu/arithmetic_kernels/src                         \
    -I$(SDK_ROOT)/kernels/apu/filtering_kernels/src                          \
    -I$(SDK_ROOT)/kernels/apu/statistics_kernels/src                         \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                              \
    apu_copy_input_kernel.cpp                                                  \
    apu_copy_input_kernel_impl.cpp                                             \
    apu_gradient_matrix_kernel.cpp                                             \
    apu_gradient_matrix_kernel_impl.cpp                                        \
    apu_lucas_kanade_kernel.cpp                                                \
    apu_lucas_kanade_kernel_impl.cpp

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
		
##############################################################################
# kernel db generator (mandatory)
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

