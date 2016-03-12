##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    ACF Add Image test
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-08-14
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../s32v234_sdk

##############################################################################
# acf kernels and graphs
##############################################################################
APU_GRAPH_LIBS =\
    $(SDK_ROOT)/kernels/apu/arithmetic_kernels/build-apu-tct-sa-d/arithmetic_kernels.a	\


APU_GRAPH_INCS =	-I../graphs          \
                    -I$(SDK_ROOT)/libs/arm/utils/common/include  \
					-I$(SDK_ROOT)/kernels/apu/arithmetic_kernels/src

APU_GRAPHS =	../graphs/apu_add_apu_process_desc.hpp

##############################################################################
# acf_app
##############################################################################
ARM_APP = apex_irq

ARM_APP_SRCS = main.cpp

ARM_INCS =                                                                   \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
	-I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I.

ARM_APP_LIBS =                                                               \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
    $(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                           \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a

	
