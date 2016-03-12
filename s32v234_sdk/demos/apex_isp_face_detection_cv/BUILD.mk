##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2016 Freescale Semiconductor;
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
#    Basic DCU output functionality test.
#
#  AUTHOR
#    Tomas Babinec
#
#  DATE
#    2015-06-05
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../s32v234_sdk

ARM_APP = apex_isp_face_detection_cv
ISP_GRAPH = mipi_simple

##############################################################################
# acf kernels and graphs
##############################################################################
APU_GRAPH_LIBS =                                                                                   \
    $(SDK_ROOT)/kernels/apu/object_detection_kernels/build-apu-tct-sa-d/object_detection_kernels.a \
    $(SDK_ROOT)/kernels/apu/optimization_kernels/build-apu-tct-sa-d/optimization_kernels.a

APU_GRAPH_INCS = -I../graphs		\
	-I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I$(SDK_ROOT)/kernels/apu/arithmetic_kernels/src                         \
    -I$(SDK_ROOT)/kernels/apu/object_detection_kernels/src                   \
    -I$(SDK_ROOT)/kernels/apu/optimization_kernels/src                       \


APU_GRAPHS =                                                                 \
    ../graphs/apu_face_detection_lbp_10_apu_process_desc.hpp                 \
    ../graphs/apu_face_detection_lbp_6_apu_process_desc.hpp                  \
    ../graphs/apu_face_detection_lbp_4_apu_process_desc.hpp                  \
    ../graphs/apu_face_detection_lbp_2_apu_process_desc.hpp
	
##############################################################################
# isp_app
##############################################################################

VPATH = ../src/lib

ARM_APP_SRCS += ICL_Kalman.cpp                                              \
                kalman_filter.cpp                                           \
                main.cpp                                                    \
                tinyxml2.cpp 

ARM_INCS +=                                                                   \
    -I../src                                                                  \
    -I../include                                                              \
    -I$(SDK_ROOT)/platform/s32_v234                                           \
    -I$(SDK_ROOT)/ocv/standalone-arm64/include                                \
    -I$(OPENCV_ROOT)/include                                                  \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                             \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                   \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                   \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                             \
    -I$(SDK_ROOT)/libs/arm/utils/log/include                                  \
    -I$(SDK_ROOT)/libs/arm/io/sdi/include                                     \
    -I$(SDK_ROOT)/libs/arm/io/gdi/include                                     \
    -I$(SDK_ROOT)/libs/arm/utils/common/include                               \
    -I$(SDK_ROOT)/libs/arm/isp/fdma/user/include                              \
    -I$(SDK_ROOT)/libs/arm/isp/fdma/kernel/include                            \
    -I$(SDK_ROOT)/libs/arm/isp/sram/user/include                              \
    -I$(SDK_ROOT)/libs/arm/isp/sram/kernel/include                            \
    -I$(SDK_ROOT)/libs/arm/isp/sequencer/user/include                         \
    -I$(SDK_ROOT)/libs/arm/isp/sequencer/kernel/include                       \
    -I$(SDK_ROOT)/isp/inc                                                     \
    -I$(SDK_ROOT)/libs/arm/io/framebuffer/user/include/linux                  \
    -I$(SDK_ROOT)/libs/arm/io/image_camera_io/include                         \
    -I$(SDK_ROOT)/libs/arm/io/frame_io/include                                \
    -I$(SDK_ROOT)/isp/graphs/mipi_simple/inc                                  \
    -I$(SDK_ROOT)/libs/arm/isp/csi/kernel/include                             \
    -I$(SDK_ROOT)/libs/arm/isp/csi/user/include                               \
    -I$(SDK_ROOT)/libs/arm/io/dcu/include

ARM_APP_LIBS +=                                                               \
    $(SDK_ROOT)/libs/arm/io/frame_io/$(ODIR)/libframe_io.a                    \
    $(SDK_ROOT)/libs/arm/io/sdi/$(ODIR)/libsdi.a                              \
    $(SDK_ROOT)/libs/arm/isp/csi/user/$(ODIR)/libcsidrv.a                     \
    $(SDK_ROOT)/libs/arm/io/i2c/$(ODIR)/libi2c.a                              \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                            \
    $(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                            \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                 \
    $(SDK_ROOT)/libs/arm/utils/log/$(ODIR)/liblog.a                           \
    $(SDK_ROOT)/libs/arm/isp/sequencer/user/$(ODIR)/libseqdrv.a               \
    $(SDK_ROOT)/libs/arm/isp/fdma/user/$(ODIR)/libfdmadrv.a                   \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a                      \
    $(SDK_ROOT)/libs/arm/isp/sram/user/$(ODIR)/libsramdrv.a                   \
    $(SDK_ROOT)/libs/arm/io/dcu/$(ODIR)/libdcu.a                              \
    $(SDK_ROOT)/isp/firmware/$(ODIR)/sequencer.a                              \
    $(SDK_ROOT)/isp/graphs/$(ISP_GRAPH)/$(ODIR)/$(ISP_GRAPH).a                \

ARM_LDOPTS +=                                                                \
        -lopencv_video                                                       \
	-lopencv_flann                                                       \
	-lopencv_features2d                                                  \
	-lopencv_imgproc                                                     \
	-lopencv_highgui                                                     \
	-lopencv_core                                                        \
	-lzlib

ifneq (,$(findstring -gnu-linux,$(ODIR)))
ARM_LDOPTS +=                                                                \
        -lavcodec                                                            \
        -lavdevice                                                           \
        -lavfilter                                                           \
        -lavformat                                                           \
        -lavutil                                                             \
        -lswresample                                                         \
        -lswscale
endif