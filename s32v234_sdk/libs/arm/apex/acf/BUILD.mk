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
#    ACF2 Host lib
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-07-17
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../../../s32v234_sdk

ARM_LIB =		libacf.a

##############################################################################
# libacf2host.a
##############################################################################

    ARM_LIB_SRCS +=                                                          \
        acf_apu_program_params.cpp                                           \
        acf_process.cpp                                                      \
        acf_process_apu.cpp                                                  \
        acf_common.cpp                                                       \
		resource_manager_apex.cpp                                            \
        resource_manager_private.cpp                                         \
		resource_manager_public.cpp                                          \
		resource_manager_types.cpp                                           \
		kernel_manager_host.cpp

    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/apex/acf/include                              \
        -I$(SDK_ROOT)/libs/arm/apex/icp/include                              \
        -I$(SDK_ROOT)/libs/arm/utils/log                                     \
        -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                        \
        -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                        \
		-I$(SDK_ROOT)/libs/apu/common/include                                \
        -I$(SDK_ROOT)/libs/x86/acf_offline/include

##############################################################################
