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

ARM_APP = qspi_readwrite

ARM_APP_SRCS = main.cpp

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/arm/apex/acf/include                                  \
    -I$(SDK_ROOT)/libs/arm/apex/apex/user/include                            \
	-I$(SDK_ROOT)/libs/arm/io/qspi/include                                   \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                            

ARM_APP_LIBS =                                                               \
    $(SDK_ROOT)/libs/arm/apex/acf/$(ODIR)/libacf.a                           \
	$(SDK_ROOT)/libs/arm/io/qspi/$(ODIR)/libqspi.a                           \
    $(SDK_ROOT)/libs/arm/apex/apex/user/$(ODIR)/libapex2drv.a                \
    $(SDK_ROOT)/libs/arm/utils/oal/user/$(ODIR)/liboal.a                     \
	


