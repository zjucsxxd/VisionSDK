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

APU_LIB = filtering_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                              \
    apu_filter_a.cpp                                                         \
    apu_filter_a_impl.cpp                                                    \
    apu_filtering_sobel_3x3.cpp                                              \
    apu_filtering_sobel_3x3_impl.cpp                                         \
    apu_gauss_3x3.cpp                                                        \
    apu_gauss_3x3_impl.cpp                                                   \
    apu_gauss_5x5.cpp                                                        \
    apu_gauss_5x5_impl.cpp                                                   \
    apu_gradient.cpp                                                         \
    apu_gradient_impl.cpp                                                    \
    apu_nms.cpp                                                              \
    apu_nms_impl.cpp                                                         \
    apu_saturate_nonzero.cpp                                                 \
    apu_saturate_nonzero_impl.cpp                                            \
    col_filter_a.cpp                                                         \
    col_filter_impl.cpp                                                      \
    row_filter_a.cpp                                                         \
    row_filter_impl.cpp                                                      \
    apu_correlation_kernel.cpp                                               \
    apu_correlation_kernel_impl.cpp											 \
	apu_filter_median_3x3.cpp												 \
	apu_filter_median_3x3_impl.cpp											 \


#    apu_nms16.cpp                                                            \
#    apu_nms16_impl.cpp                                                       \

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

