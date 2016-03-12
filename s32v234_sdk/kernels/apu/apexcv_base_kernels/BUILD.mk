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

APU_LIB = apexcv_base.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include

APU_LIB_SRCS +=                                                              \
    arithmetic_kernels.cpp                                                   \
	apu_arithmetic_impl.cpp                                                  \
	interpolation_kernels.cpp                                                \
	apu_interpolation_impl.cpp                                               \
	color_conversion_kernels.cpp                                             \
	apu_color_conversion_impl.cpp                                            \
	filter_kernels.cpp                                                       \
	apu_filter_impl.cpp                                                      \
	histogram_kernels.cpp                                                    \
	apu_histogram_impl.cpp                                                   \
	integral_image_kernels.cpp                                               \
	apu_integral_image_impl.cpp                                              \

	
APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_KERNEL_DB = "on"

##############################################################################

