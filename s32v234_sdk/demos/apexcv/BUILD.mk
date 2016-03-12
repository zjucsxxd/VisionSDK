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

SDK_ROOT := ../../../../s32v234_sdk

##############################################################################
# acf_app
##############################################################################

ARM_APP = apexcv

ARM_APP_SRCS = main.cpp                                                      \
               base_arithmetic.cpp                                           \
			   base_color_conversion.cpp                                     \
			   base_histogram.cpp                                            \
			   base_integral_image.cpp                                       \
			   base_interpolation.cpp                                        \
			   base_image_filters.cpp

ARM_INCS +=                                                                  \
    -I../include                                                             \
	-I$(OPENCV_ROOT)/include												 \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/apexcv_core/include                   \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/arithmetic/include                    \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/interpolation/include                 \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/color_conversion/include              \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/image_filters/include                 \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/histogram/include                     \
	-I$(SDK_ROOT)/libs/arm/apexcv_base/integral_image/include                \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
	-I$(SDK_ROOT)/libs/arm/utils/common/include                              \

ARM_APP_LIBS =                                                               \
	$(SDK_ROOT)/libs/arm/apexcv_base/apexcv_core/$(ODIR)/apexcv_core.a       \
	$(SDK_ROOT)/libs/arm/apexcv_base/arithmetic/$(ODIR)/apexcv_arithmetic.a             \
	$(SDK_ROOT)/libs/arm/apexcv_base/color_conversion/$(ODIR)/apexcv_color_conversion.a \
	$(SDK_ROOT)/libs/arm/apexcv_base/histogram/$(ODIR)/apexcv_histogram.a               \
	$(SDK_ROOT)/libs/arm/apexcv_base/integral_image/$(ODIR)/apexcv_integral_image.a     \
	$(SDK_ROOT)/libs/arm/apexcv_base/interpolation/$(ODIR)/apexcv_interpolation.a       \
	$(SDK_ROOT)/libs/arm/apexcv_base/image_filters/$(ODIR)/apexcv_image_filters.a       \
	$(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
	$(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                           
    
ifeq ($(APEX_USERSPACE),1)
	ARM_APP_LIBS += $(SDK_ROOT)/libs/arm/apex/apex_user/$(ODIR)/libapex2drv.a
else
	ARM_APP_LIBS += $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a
endif

ARM_APP_LIBS +=                                                               \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a                     \
    $(SDK_ROOT)/libs/arm/utils/common/$(ODIR)/libcommon.a
	   


##############################################################################
# STANDALONE SPECIFIC INCLUDES
##############################################################################	
ifneq (,$(findstring -sa-d,$(ODIR)))
#	ARM_INCS += -I$(SDK_ROOT)/libs/arm/io/frame_io/include                \
#				-I$(SDK_ROOT)/libs/arm/io/dcu/include				\

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
        -lopencv_calib3d                                                     \
        -lopencv_ml                                                         \
        -lopencv_video                                                      \
        -lopencv_videostab                                                  \
        -lopencv_flann                                                       \
        -lopencv_features2d                                                  \
        -lopencv_photo                                                      \
        -lopencv_legacy                                                     \
        -lopencv_objdetect                                                  \
        -lavcodec                                                            \
        -lavfilter                                                           \
        -lavutil                                                             \
        -lavformat                                                           \
        -lavdevice                                                           \
        -lswresample                                                         \
        -lswscale															\
        -lopencv_gpu                                                        \

endif
endif



