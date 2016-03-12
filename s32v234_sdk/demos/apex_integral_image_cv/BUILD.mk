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

SDK_ROOT :=	../../../../s32v234_sdk

##############################################################################
# acf kernels and graphs
##############################################################################
APU_GRAPH_LIBS =                                                                           \
    $(SDK_ROOT)/kernels/apu/optimization_kernels/build-apu-tct-sa-d/optimization_kernels.a

APU_GRAPH_INCS = -I../graphs

APU_GRAPHS = ../graphs/apu_sat_apu_process_desc.hpp

##############################################################################
# acf_app
##############################################################################
ARM_APP = apex_integral_image_cv

ARM_APP_SRCS = integral_image.cpp 

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
	-I$(SDK_ROOT)/libs/arm/io/frame_io/include                               \
	-I$(SDK_ROOT)/libs/arm/io/dcu/include                                    \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
	-I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I$(OPENCV_ROOT)/include                                                 

ARM_APP_LIBS =                                                               \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
    $(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                           \
	$(SDK_ROOT)/libs/arm/io/frame_io/$(ODIR)/libframe_io.a                   \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a                     \
	$(SDK_ROOT)/libs/arm/utils/common/$(ODIR)/libcommon.a                    \
	$(SDK_ROOT)/libs/arm/io/dcu/$(ODIR)/libdcu.a    

##############################################################################
# STANDALONE SPECIFIC INCLUDES
##############################################################################	
ifneq (,$(findstring -sa-d,$(ODIR)))

    ARM_LDOPTS +=                                                            \
        -lopencv_video                                                       \
		-lopencv_flann                                                       \
		-lopencv_features2d                                                  \
		-lopencv_imgproc                                                     \
		-lopencv_highgui                                                     \
		-lopencv_core                                                        \
		-lzlib

else
##############################################################################
# INTEGRITY SPECIFIC INCLUDES
##############################################################################
ifneq (,$(findstring -integrity-d,$(ODIR)))
    ARM_LDOPTS +=                                                            \
        -L$(SDK_ROOT)/ocv/integrity-arm/share/OpenCV/3rdparty/lib            \
        -lposix                                                              \
        -livfs                                                               \
        -lIlmImf                                                             \
        -lzlib                                                               \
        --exceptions                                                         \
		-lopencv_objdetect                                                   \
        -lopencv_core                                                        \
        -lopencv_highgui                                                     \
        -lopencv_imgproc                                                     \
        -lopencv_features2d                                                  \
        -lopencv_flann                                                       \
        -llibjasper                                                          \
        -llibjpeg                                                            \
        -llibpng                                                             \
        -llibtiff

##############################################################################
# LINUX SPECIFIC INCLUDES
##############################################################################			
else
    ARM_LDOPTS +=                                                            \
        -lopencv_core                                                        \
        -lopencv_highgui                                                     \
        -lopencv_imgproc                                                     \
        -lopencv_features2d                                                  \
        -lopencv_flann                                                       \
        -lavcodec                                                            \
        -lavdevice                                                           \
        -lavfilter                                                           \
        -lavformat                                                           \
        -lavutil                                                             \
        -lswresample                                                         \
        -lswscale
endif
endif
