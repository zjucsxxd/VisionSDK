##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    APU_EMULATION_TEST demo application to demonstrate ACF library usage
#
#  AUTHOR
#    Anca Dima
#
#  DATE
#    2013-02-10
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../s32v234_sdk

##############################################################################
# acf kernels and graphs
##############################################################################
APU_GRAPH_LIBS =                                                                                     \
    $(SDK_ROOT)/kernels/apu/arithmetic_kernels/build-apu-tct-sa-d/arithmetic_kernels.a               \
    $(SDK_ROOT)/kernels/apu/comparison_kernels/build-apu-tct-sa-d/comparison_kernels.a               \
    $(SDK_ROOT)/kernels/apu/conversion_kernels/build-apu-tct-sa-d/conversion_kernels.a               \
    $(SDK_ROOT)/kernels/apu/display_kernels/build-apu-tct-sa-d/display_kernels.a                     \
    $(SDK_ROOT)/kernels/apu/feature_detection_kernels/build-apu-tct-sa-d/feature_detection_kernels.a \
    $(SDK_ROOT)/kernels/apu/filtering_kernels/build-apu-tct-sa-d/filtering_kernels.a                 \
    $(SDK_ROOT)/kernels/apu/geometry_kernels/build-apu-tct-sa-d/geometry_kernels.a                   \
    $(SDK_ROOT)/kernels/apu/morphology_kernels/build-apu-tct-sa-d/morphology_kernels.a               \
    $(SDK_ROOT)/kernels/apu/object_detection_kernels/build-apu-tct-sa-d/object_detection_kernels.a   \
    $(SDK_ROOT)/kernels/apu/optimization_kernels/build-apu-tct-sa-d/optimization_kernels.a           \
    $(SDK_ROOT)/kernels/apu/resizing_kernels/build-apu-tct-sa-d/resizing_kernels.a                   \
    $(SDK_ROOT)/kernels/apu/statistics_kernels/build-apu-tct-sa-d/statistics_kernels.a

APU_GRAPH_INCS =                                                             \
    -I../graphs                                                              \
    -I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I$(SDK_ROOT)/kernels/apu/arithmetic_kernels/src                         \
    -I$(SDK_ROOT)/kernels/apu/comparison_kernels/src                         \
	-I$(SDK_ROOT)/kernels/apu/conversion_kernels/src                         \
    -I$(SDK_ROOT)/kernels/apu/display_kernels/src                            \
    -I$(SDK_ROOT)/kernels/apu/feature_detection_kernels/src                  \
    -I$(SDK_ROOT)/kernels/apu/filtering_kernels/src                          \
    -I$(SDK_ROOT)/kernels/apu/geometry_kernels/src                           \
    -I$(SDK_ROOT)/kernels/apu/morphology_kernels/src                         \
    -I$(SDK_ROOT)/kernels/apu/object_detection_kernels/src                   \
    -I$(SDK_ROOT)/kernels/apu/optimization_kernels/src                       \
    -I$(SDK_ROOT)/kernels/apu/resizing_kernels/src                           \
    -I$(SDK_ROOT)/kernels/apu/statistics_kernels/src                         \

APU_GRAPHS =                                                                 \
    ../graphs/apu_gauss_5x5_apu_process_desc.hpp                             \
    ../graphs/apu_gauss_3x3_apu_process_desc.hpp                             \
    ../graphs/apu_convolution_apu_process_desc.hpp                           \
    ../graphs/apu_rotate_apu_process_desc.hpp                                \
    ../graphs/apu_sat_apu_process_desc.hpp                                   \
    ../graphs/apu_downsample_upsample_apu_process_desc.hpp                   \
    ../graphs/apu_histogram_apu_process_desc.hpp							 \
	../graphs/apu_fast9_apu_process_desc.hpp								\
    ../graphs/apu_fast9_color_apu_process_desc.hpp							\

##############################################################################
# acf_app
##############################################################################
ARM_APP = apex_emulation_test

ARM_APP_SRCS =                                                               \
    apu_gauss_5x5_process.cpp                                                \
    apu_gauss_3x3_process.cpp                                                \
    apu_convolution_process.cpp                                              \
    apu_sat_process.cpp                                                      \
    apex_emulation_test.cpp 

ARM_INCS +=                                                                  \
    -I./                                                                     \
    -I../src                                                                 \
    -I../graphs                                                              \
    -I$(SDK_ROOT)/libs/arm/utils/common/include                              \
    -I$(SDK_ROOT)/kernels/apu/filtering_kernels/src                          \
    -I$(SDK_ROOT)/libs/arm/utils/matrix/src                                  \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
    -I$(OPENCV_ROOT)/include

X86_INCS += -I$(SDK_ROOT)/libs/arm/utils/common/include

ARM_APP_LIBS =                                                               \
    $(SDK_ROOT)/libs/arm/utils/common/$(ODIR)/libcommon.a                    \
    $(SDK_ROOT)/libs/arm/utils/matrix/$(ODIR)/libmatrix.a                    \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
    $(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                           \
    $(SDK_ROOT)/libs/arm/utils/matrix/$(ODIR)/libmatrix.a                    \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a                     \
    $(SDK_ROOT)/libs/arm/utils/matrix/$(ODIR)/libmatrix.a
 

##############################################################################
# STANDALONE SPECIFIC INCLUDES
##############################################################################	
ifneq (,$(findstring -sa-d,$(ODIR)))
	ARM_INCS += -I$(SDK_ROOT)/libs/arm/io/frame_io/include                \
				-I$(SDK_ROOT)/libs/arm/io/dcu/include				\

    ARM_LDOPTS +=                                                            \
        -lopencv_video                                                       \
		-lopencv_flann                                                       \
		-lopencv_features2d                                                  \
		-lopencv_imgproc                                                     \
		-lopencv_highgui                                                     \
		-lopencv_core                                                        \
		-lzlib

##############################################################################
# INTEGRITY SPECIFIC INCLUDES
##############################################################################	
else
ifneq (,$(findstring -integrity-d,$(ODIR)))

    ARM_LDOPTS +=                                                            \
		-lposix                                                              \
        -livfs                                                               \
        -lIlmImf                                                             \
        -lzlib                                                               \
        --exceptions                                                         \
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



