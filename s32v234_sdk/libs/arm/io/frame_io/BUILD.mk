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
#    libframe_io.a
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

SDK_ROOT := ../../../../../../s32v234_sdk

ARM_LIB = libframe_io.a

##############################################################################
# libframe_io.a
##############################################################################
ARM_LIB_SRCS +=                                                              \
    frame_input_memory.cpp                                                   \
    frame_output_memory.cpp                                                  \
    frame_input_patterngen.cpp

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/arm/io/frame_io/include                               \
    -I$(OPENCV_ROOT)/include                                                 \
    -I$(SDK_ROOT)/libs/apu/common/include                                    \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
    -I$(SDK_ROOT)/libs/arm/isp/csi/user/include                              \
    -I$(SDK_ROOT)/libs/arm/io/sdi/include                                    \
    -I$(SDK_ROOT)/libs/arm/io/gdi/include                                    \

    
    
ifneq (,$(findstring linux,$(ODIR)))

    ARM_LIB_SRCS +=                                                          \
        frame_input_isp.cpp                                                  \
        frame_input_file.cpp                                                 \
        frame_input_linuxcam.cpp                                             \
        frame_output_file.cpp                                                \
        frame_output_v234fb.cpp                                              \
        frame_output_zynqfb.cpp

    
    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/io/image_camera_io/include                    \
        -I$(SDK_ROOT)/libs/arm/io/framebuffer/user/include/linux             \
        -I$(SDK_ROOT)/libs/arm/utils/log/include                             \
        -I$(SDK_ROOT)/libs/arm/utils/common/include                          \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/user/include                         \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/kernel/include                       \
        -I$(SDK_ROOT)/libs/arm/isp/sram/user/include                         \
        -I$(SDK_ROOT)/libs/arm/isp/sram/kernel/include                       \
        -I$(SDK_ROOT)/libs/arm/isp/sequencer/user/include                    \
        -I$(SDK_ROOT)/libs/arm/isp/sequencer/kernel/include                  \
        -I$(SDK_ROOT)/libs/arm/isp/csi/user/include                          \
        -I$(SDK_ROOT)/libs/arm/isp/csi/kernel/include                        \
        -I$(SDK_ROOT)/isp/inc                                                \
        -I$(SDK_ROOT)/platform/s32_v234                                      \
        -I$(OPENCV_ROOT)/include
endif



ifneq (,$(findstring sa,$(ODIR)))
    ARM_LIB_SRCS +=                                                          \
        frame_input_isp.cpp                                                  \
        frame_output_dcu.cpp                                                 \
        
    ARM_INCS +=                                                              \
        -I$(SDK_ROOT)/libs/arm/io/dcu/include                                \
	-I$(SDK_ROOT)/libs/arm/utils/log/include                             \
        -I$(SDK_ROOT)/libs/arm/utils/common/include                          \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/user/include                         \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/kernel/include                       \
        -I$(SDK_ROOT)/libs/arm/isp/sram/user/include                         \
        -I$(SDK_ROOT)/libs/arm/isp/sram/kernel/include                       \
        -I$(SDK_ROOT)/libs/arm/isp/sequencer/user/include                    \
        -I$(SDK_ROOT)/libs/arm/isp/sequencer/kernel/include                  \
        -I$(SDK_ROOT)/libs/arm/isp/csi/user/include                          \
        -I$(SDK_ROOT)/libs/arm/isp/csi/kernel/include                        \
        -I$(SDK_ROOT)/isp/inc                                                \
        -I$(SDK_ROOT)/platform/s32_v234                                      \
	
endif 

ifneq (,$(findstring build-zc702-gnu-linux-d,$(ODIR)))
      
    ARM_CXOPTS += -mfpu=neon -mfloat-abi=softfp

endif


##############################################################################
