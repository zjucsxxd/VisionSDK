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
#    SDI lib
#
#  AUTHOR
#    Tomas Babinec
#
#  DATE
#    2013-09-06
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../../s32v234_sdk

ARM_LIB =   libsdi.a
##############################################################################
# libsdi.a
##############################################################################
ARM_LIB_SRCS += \
                sdi_graph.cpp \
                sdi_io.cpp \
                sdi.cpp 

ARM_INCS +=		\
                -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                \
                -I$(SDK_ROOT)/libs/arm/io/sdi/include                        \
                -I$(SDK_ROOT)/libs/arm/utils/log/include                     \
                -I$(SDK_ROOT)/libs/arm/io/gdi/include                        \
                -I$(SDK_ROOT)/libs/arm/isp/fdma/user/include                 \
                -I$(SDK_ROOT)/libs/arm/isp/fdma/kernel/include               \
                -I$(SDK_ROOT)/isp/inc                                        \
                -I$(SDK_ROOT)/libs/arm/isp/sequencer/user/include            \
                -I$(SDK_ROOT)/libs/arm/isp/sequencer/kernel/include          \
                -I$(SDK_ROOT)/libs/arm/isp/sram/user/include                 \
                -I$(SDK_ROOT)/libs/arm/isp/sram/kernel/include               \
                -I$(SDK_ROOT)/libs/arm/isp/csi/user/include                  \
                -I$(SDK_ROOT)/libs/arm/isp/csi/kernel/include                \
                
                
ifneq ($(findstring deskx11,$(ODIR)),)
ARM_LIB_SRCS += \
                sdi_io.cpp \
                sdi.cpp     
    
endif                
                

ifneq (,$(findstring v234ce-gnu-sa-d,$(ODIR)))
ARM_INCS +=  \
    -I$(SDK_ROOT)/platform/s32_v234                              \
    
else 

ARM_INCS +=  \
    -I$(SDK_ROOT)/platform/s32_v234                              \
    
endif                
                
ARM_DEFS += \

ARM_INCS += -I$(OPENCV_ROOT)/include
 
ARM_LDOPTS +=                                                                \
    -lopencv_core                                                            \
    -lopencv_imgproc                                                         \
    -lopencv_highgui

#ifneq ($(findstring zc702,$(ODIR)),)
#    ARM_LDOPTS +=                                                            \
#        -lavcodec                                                            \
#        -lavdevice                                                           \
#        -lavfilter                                                           \
#        -lavformat                                                           \
#        -lavutil                                                             \
#        -lswresample                                                         \
#        -lswscale
#endif

##############################################################################
