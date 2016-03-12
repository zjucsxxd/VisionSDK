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
#    Template Project for demonstration purposes
#
#  AUTHOR
#    Anca Dima
#
#  DATE
#    2014-08-04
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../../s32v234_sdk

##############################################################################
# acf kernels and graphs
##############################################################################
APU_GRAPH_LIBS =                                                             \
    $(SDK_ROOT)/kernels/apu/apexcv_base_kernels/build-apu-tct-sa-d/apexcv_base.a

APU_GRAPH_INCS =                                                             \
    -I../graphs                                                              \
    -I$(SDK_ROOT)/libs/arm/utils/common/include								 \
	-I$(SDK_ROOT)/kernels/apu/apexcv_base_kernels/src						 \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/apexcv_core/include                   \

APU_GRAPHS =                                                                 \
    rgb565_to_rgb888_apu_process_desc.hpp                                    \
	rgb888_to_rgb565_apu_process_desc.hpp                                    \
	rgb888_to_y_apu_process_desc.hpp                                         \
	rgb888_to_yuv_apu_process_desc.hpp                                       \
	ht_8uc3_to_y_apu_process_desc.hpp

##############################################################################
# acf_app
##############################################################################
ARM_LIB = apexcv_color_conversion.a

ARM_LIB_SRCS =                                                               \
    color_conversion.cpp                                                     \
	apexcv_rgb565_to_rgb888.cpp                                              \
	apexcv_rgb888_to_rgb565.cpp                                              \
	apexcv_rgb888_to_y.cpp                                                   \
	apexcv_rgb888_to_yuv.cpp                                                 \
	apexcv_ht_8uc3_to_y.cpp                                                  \
	apexcv_color_conversion_ref.cpp
    

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/apexcv_core/include                   \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
	-I../include                                                             \
	-I../src                                                                 \
    -I../graphs         

