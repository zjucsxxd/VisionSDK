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
#    ISP RGB, YUV and GreyScale8
#
#  AUTHOR
#    Armin Strobl
#
#  DATE
#    2016-01-15
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../../s32v234_sdk

##############################################################################
# ISP Graph
##############################################################################
ARM_LIB =	rgb_yuv_gs8.a

ARM_LIB_SRCS =	\
		rgb_yuv_gs8.c

ARM_INCS =	\
		-I../inc							\
		-I$(SDK_ROOT)/isp/inc						\
		-I$(SDK_ROOT)/platform/s32_v234					\

GDT_OPTS =	-m

##############################################################################
# IPUx kernels 
##############################################################################
IPUS_APP = ipus.elf
IPUS_APP_SRCS = \
	../../../kernels/sony_isp/src/exposure.s			\
	../../../kernels/sony_isp/src/exposure_tonehdr.s		\
	../../../kernels/sony_isp/src/debayer_g.s			\
	../../../kernels/sony_isp/src/debayer_br.s			\
	../../../kernels/sony_isp/src/debayer_br_advanced.s		\
	../../../kernels/sony_isp/src/gamma_yuv444touyvy.s		\
	../../../kernels/sony_isp/src/yuv444touyvy.s			\
	../../../kernels/sony_isp/src/copy_replicate3x.s		\
	../../../kernels/sony_isp/src/planar444_to_interleaved.s	\
	../../../kernels/sony_isp/src/debayer_rgb_simple_interleaved.s	\
	../../../kernels/sony_isp/src/scale2by1.s			\

IPUV_APP = ipuv.elf
IPUV_APP_SRCS = \
	../../../kernels/sony_isp/src/tonehdr.s				\
	../../../kernels/sony_isp/src/rgb2yuv.s				\

KMEM = kmem
