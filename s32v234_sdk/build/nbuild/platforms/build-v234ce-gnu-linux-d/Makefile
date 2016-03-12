##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    full featured Makefile for arm gcc using nbuild packages.
#    internal use only
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-08-05
#
#  LANGUAGE
#    make
#
##############################################################################
# nbuild packages
ODIR :=		$(shell basename `pwd`)

include         ../BUILD.mk

ifeq ($(APEX_PREBUILD),1)
    APU_GRAPHS := ""
    APU_GRAPH_LIBS := ""
    APU_GRAPH_INCS := ""
	ifneq ($(ACL_KERNELS),)
		ACL_KERNELS := 
	endif
	ifneq ($(ACL_KERNEL_SRC_DIRS),)
		ACL_KERNEL_SRC_DIRS := 
	endif
	ifneq ($(ACL_KERNEL_LIBS),)
		ACL_KERNEL_LIBS := 
	endif
endif

VPATH += ../src
VPATH += ../graphs

include $(SDK_ROOT)/build/nbuild/core.mk

OPENCV_ROOT = $(SDK_ROOT)/ocv/linux-arm64
FFMPEG_ROOT = $(SDK_ROOT)/ffmpeg/linux-arm64

ifeq ($(X86_KERNEL_DB),"on")
	X86_APP =	$(basename $(APU_LIB))
	X86_APP_SRCS =	$(APU_LIB_SRCS)
	X86_APP_LIBS =  $(SDK_ROOT)/libs/x86/acf_offline/build-x86-gnu-linux-d/libacf_offline.a

	X86_DEFS +=	-DACF_KERNEL_METADATA
	X86_CCOPTS +=   --include apu2_kernel_db_lib.h 
	X86_INCS += 	-I$(SDK_ROOT)/libs/x86/acf_offline/include		\
			-I$(SDK_ROOT)/libs/apu/acf_target/include		\
			-I$(SDK_ROOT)/libs/apu/common/include			\
			-I$(SDK_ROOT)/libs/apu/common/include/driver		\

	X86_KERNEL_DB = "on"
endif

ifneq ($(strip $(X86_APP) $(X86_LIB)),)
	include $(SDK_ROOT)/build/nbuild/toolchains/x86-linux-gnu.mk
endif

ifneq ($(APU_GRAPHS),)
	include $(SDK_ROOT)/build/nbuild/apex_tools/apu-kernel-getgraphs.mk
endif

ifneq ($(ACL_KERNELS),)
	include $(SDK_ROOT)/build/nbuild/apex_tools/acl-kernel.mk
endif

ifeq ($(APU_LOAD_FROM_EXE),"on")
	include $(SDK_ROOT)/build/nbuild/apex_tools/apu-kernel-load.mk
endif

ifeq ($(X86_KERNEL_DB),"on")
	include $(SDK_ROOT)/build/nbuild/apex_tools/apu-kernel-database.mk
endif

ifneq ($(strip $(APU_APP) $(APU_LIB) $(APU_LOAD_BINS)),)
	include         $(SDK_ROOT)/build/nbuild/toolchains/apu-acf-sa-tct.mk
endif

ifneq ($(strip $(ACL_APP) $(ACL_LIB) $(ACL_LOAD_BINS)),)
	include         $(SDK_ROOT)/build/nbuild/toolchains/apu-acl-sa-tct.mk
endif

include $(SDK_ROOT)/build/nbuild/apex_tools/acl-get_md.mk

ifneq ($(strip $(ARM_APP) $(ARM_LIB)),)
	include         $(SDK_ROOT)/build/nbuild/toolchains/aarch64-linux-gnu.mk
endif

################## ISP firmware and graph, IPU ###############################
ifneq ($(strip $(SEQ_APP) $(SEQ_LIB)),)

ifeq ($(TOOLCH),ghs)	### GHS ###########################
include         $(SDK_ROOT)/build/nbuild/toolchains/arm-sa-ghs.mk
else	### GCC ###########################################
include         $(SDK_ROOT)/build/nbuild/toolchains/arm-sa-gnu-m0.mk
endif
endif


ifneq ($(IPUS_APP),)
include		$(SDK_ROOT)/build/nbuild/toolchains/ipus-sa-gnu.mk
endif

ifneq ($(IPUV_APP),)
  include		$(SDK_ROOT)/build/nbuild/toolchains/ipuv-sa-gnu.mk
endif

ifneq ($(strip $(IPUS_APP) $(IPUV_LIB)),)
	include		$(SDK_ROOT)/build/nbuild/isp_tools/isp-graphgen.mk
endif
##############################################################################

include         $(SDK_ROOT)/build/nbuild/sub.mk
#include         $(SDK_ROOT)/build/nbuild/tags.mk
include         $(SDK_ROOT)/build/nbuild/headdep.mk
