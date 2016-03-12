##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    ACF kernel and graph build
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

APU_LIB = statistics_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include								 \

APU_LIB_SRCS +=                                                              \
    apu_histogram.cpp                                                        \
	apu_histogram_impl.cpp                                                        \
    apu_lbp.cpp                                                        \
	apu_lbp_impl.cpp                                                        \
    apu_histofgrad.cpp                                                        \
	apu_histofgrad_impl.cpp                                                        \
    apu_reduction.cpp                                                        \
	apu_reduction_impl.cpp                                                        \
    apu_accumulation_kernel.cpp                                                \
    apu_accumulation_kernel_impl.cpp

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

