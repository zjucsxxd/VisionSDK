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
# acf kernels and graphs
##############################################################################
ACL_KERNEL_LIBS =                                                                 \
    $(SDK_ROOT)/kernels/cl/unsorted_kernels/build-apu-tct-sa-d/unsorted_kernels.a \

ACL_KERNELS =                                                                \
    bitonicSort_AMD
    

ACL_KERNEL_SRC_DIRS = -I$(SDK_ROOT)/kernels/cl/unsorted_kernels/src

##############################################################################
# acf_app
##############################################################################

ARM_APP = apexcl_bitonic_sort

ARM_APP_SRCS =                                                               \
    main.cpp                                                                 \
    BitonicSort.cpp 

ARM_INCS =                                                                   \
    -I$(SDK_ROOT)/libs/arm/apex/icp/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            \
    -I$(SDK_ROOT)/libs/arm/utils/ocl/include                                 \
    -I../include                                                             \
    -I.

ARM_CCOPTS += -w -DAPEX
ARM_CXOPTS += -w -DAPEX

ifeq (,$(findstring -integrity-d,$(ODIR)))
	ARM_LDOPTS += -lm
else
	ARM_LDOPTS += -livfsserver -livfs -lhostio
endif

ARM_APP_LIBS =                                                               \
    $(SDK_ROOT)/libs/arm/utils/ocl/$(ODIR)/libocl.a                          \
    $(SDK_ROOT)/libs/arm/apex/ocl_apex/$(ODIR)/libocl.a                      \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
    $(SDK_ROOT)/libs/arm/apex/icp/$(ODIR)/libicp.a                           \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a
    
