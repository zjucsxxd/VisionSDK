##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2015 Freescale Semiconductor;
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
#    Sequencer driver
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

ARM_LIB =		libh264encdrv.a

# library sources
##############################################################################
# libseqdrv.a
##############################################################################

ifneq (,$(findstring gnu-linux,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/arm/isp/h264enc/user/src
endif


ifneq (,$(findstring gnu-linux,$(ODIR)))
    ARM_LIB_SRCS +=                                                          \
        h264enc_user.cpp                                                         
endif

ARM_INCS +=                                                             \
	-I$(SDK_ROOT)/isp/inc/		                     		\
	-I$(SDK_ROOT)/platform/fpga_vs4			           	\
	-I$(SDK_ROOT)/libs/arm/utils/log/include		           	\
	-I$(SDK_ROOT)/libs/arm/isp/h264enc/kernel/include                	\
        -I$(SDK_ROOT)/libs/arm/isp/h264enc/user/include                             

##############################################################################
