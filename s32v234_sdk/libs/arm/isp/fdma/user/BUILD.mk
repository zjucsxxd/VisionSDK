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
#    FDMA driver
#
#  AUTHOR
#    Stefan Schwarz
#    Tomas Babinec
#
#  DATE
#    2015-02-25
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../../../../s32v234_sdk

ARM_LIB =		libfdmadrv.a

# library sources
##############################################################################
# libfdmadrv.a
##############################################################################

VPATH += $(SDK_ROOT)/libs/arm/isp/fdma/user/src

ARM_LIB_SRCS +=                                                              \
        fdma_user.cpp  

ifneq (,$(findstring v234ce,$(ODIR)))
  ARM_INCS +=                                                            \
    -I$(SDK_ROOT)/platform/s32_v234                                      \
    
else
  ARM_INCS +=                                                            \
    -I$(SDK_ROOT)/platform/fpga_vs4                                      \
    
endif

ARM_INCS +=                                                                  \
        -I$(SDK_ROOT)/isp/inc                                                \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/kernel/include                       \
        -I$(SDK_ROOT)/libs/arm/isp/fdma/user/include                         \
        -I$(SDK_ROOT)/libs/arm/utils/log/include

ifneq (,$(findstring gnu-linux,$(ODIR)))

else

ifneq (,$(findstring gnu-sa,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/arm/isp/fdma/kernel/src                        \
    
    ARM_LIB_SRCS +=                                                          \
       fdma_func.c                                                           \

endif

endif


##############################################################################
