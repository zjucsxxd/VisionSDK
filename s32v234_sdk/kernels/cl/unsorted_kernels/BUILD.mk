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

ACL_LIB = unsorted_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

ACL_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/libs/apu/acl_target/include

ACL_LIB_SRCS +=                                                              \
    MedianFilter.cl                                                          \
    MemoryModel.cl                                                           \
    BitonicSort_Kernels.cl                                                   \
    FloydWarshall_Kernels.cl                                                 \
    Reduction_Kernels.cl                                                     \
    MedianFilter_Async.cl                                                    \
    MedianFilter_Async_2d.cl

ACL_DEFS += -DACF_KERNEL_IMPLEMENTATION -DAPEX

ACL_CCOPTS +=     -DAPEX                                                            \
    -p APU2 +W noodle,+Oivsq                                                 \
    +W noodle,-Wlow                                                          \
    -include tct_opencl.h                                                    \
    -include tct_opencl_apu.h                                                \
    -include tct_opencl_apu_builtin.h                                        \
    -include tct_opencl_apu_config.h                                         \
    -include apu_ocl_wg.h

ACL_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

ACL_GENERATE_MD = "on"


