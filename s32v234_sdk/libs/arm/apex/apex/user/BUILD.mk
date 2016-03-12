##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2014 Freescale Semiconductor;
# All Rights Reserved
#
##############################################################################
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
##############################################################################
#
#  CONTENT
#    APEX2 driver
#
#  AUTHOR
#    Stefan Schwarz
#    Rostislav Hulik
#
#  DATE
#    2013-08-14
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../../../../s32v234_sdk

ARM_LIB =		libapex2drv.a

# library sources
##############################################################################
# libapex2drv.a
##############################################################################

ifneq (,$(findstring ghs-integrity,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/user/src/integrity
    ARM_LIB_SRCS +=                                                              \
		apex.cpp                                                         \
		apex_cmem_if_hal.cpp                                             \
		apex_mcdma_hal.cpp                                               \
		apex_global_hal.cpp                                              \
		apex_apu_hal.cpp                                                 \
		apex_apu_microkernel_hal.cpp                                     \
		apex_seq_hal.cpp                                                 
		
    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include                      \
	-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/integrity            \
	-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/functions            \
        -I$(SDK_ROOT)/libs/apu/common/include                                \
	-I$(SDK_ROOT)/libs/apu/common/include/driver                         \
	-I$(SDK_ROOT)/libs/apu/common/include/system 
    
else
ifneq (,$(findstring gnu-linux,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/user/src/linux
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/user/src/linux/functions

	
	ARM_LIB_SRCS +=                                                              \
		apexdriver_hw_reg_user.c                                             \
		apexdriver_apu_hal.c                                                 \
		apexdriver_apumk_hal_cmdque.c                                        \
		apexdriver_apumk_hal_comm.c                                          \
		apexdriver_cmem_if_hal.c                                             \
		apexdriver_global_hal.c                                              \
		apexdriver_mcdma_hal.c                                               \
		apexdriver_seq_hal.c                                                 \
		apexdriver_stio_hal.c                                                \
		apex.cpp                                                             \
                apex_cmem_if_hal.cpp                                                 \
                apex_mcdma_hal.cpp                                                   \
		apex_global_hal.cpp                                                  \
		apex_apu_hal.cpp                                                     \
		apex_apu_microkernel_hal.cpp                                         \
		apex_seq_hal.cpp
		

    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include                      \
		-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/linux                \
		-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/functions            \
        -I$(SDK_ROOT)/libs/apu/common/include                                \
		-I$(SDK_ROOT)/libs/apu/common/include/driver                         \
		-I$(SDK_ROOT)/libs/apu/common/include/system 
		
else
endif
endif

ifneq (,$(findstring sa-d,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/kernel/src/functions
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/kernel/src/standalone
    VPATH += $(SDK_ROOT)/libs/arm/apex/apex/user/src/standalone
    
    ARM_LIB_SRCS +=                                                          \
        apexdriver_hw_reg_user.cpp                                           \
		apexdriver_cmem_if_hal.c                                             \
		apexdriver_global_hal.c                                              \
		apexdriver_stio_hal.c                                                \
		apexdriver_apu_hal.c                                                 \
		apexdriver_apumk_hal_cmdque.c                                        \
		apexdriver_apumk_hal_comm.c                                          \
		apexdriver_mcdma_hal.c                                               \
		apexdriver_seq_hal.c                                                 \
		apex_cmem_if_hal.cpp                                                 \
		apex_global_hal.cpp                                                  \
		apex_stio_hal.cpp                                                    \
		apex_apu_hal.cpp                                                     \
		apex_apu_microkernel_hal.cpp                                         \
		apex_mcdma_hal.cpp                                                   \
		apex_seq_hal.cpp                                                     \
		apex.cpp
		

    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include                      \
		-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/standalone           \
		-I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include/functions            \
        -I$(SDK_ROOT)/libs/apu/common/include                                \
		-I$(SDK_ROOT)/libs/apu/common/include/driver                         \
		-I$(SDK_ROOT)/libs/apu/common/include/system 
else
endif

ARM_INCS +=                                                                  \
        -I$(SDK_ROOT)/libs/arm/apex/apex/kernel/include                      \
		-I$(SDK_ROOT)/libs/arm/apex/apex/user/include                        \
        -I$(SDK_ROOT)/libs/arm/utils/oal/user/include

##############################################################################
