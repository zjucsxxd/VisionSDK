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
#    Sequencer Firmware (for M0+)
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2015-02-24
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT :=	../../../../s32v234_sdk
#TOOLCH :=	ghs
TOOLCH :=	gcc

##############################################################################
# ISP Graph
##############################################################################
ARM_LIB =	sequencer.a

ARM_LIB_SRCS =  \
		sequencer_srec.c

##############################################################################
# Sequencer Firmware
##############################################################################
SEQ_APP =	sequencer

SEQ_APP_SRCS =	\
		../$(TOOLCH)/core_regs.s	\
		../$(TOOLCH)/crt0_start.s	\
		../$(TOOLCH)/startup.c		\
		seq_int.c			\
		seq_main.c			\
		seq_static.c			\
		
ifeq ($(TOOLCH),gcc)
SEQ_APP_SRCS +=	\
		seq_asm.S			\

endif

SEQ_DEFS =	
SEQ_INCS =	\
		-I../inc	\
		-I../../inc	\
		-I$(SDK_ROOT)/platform/s32_v234	\


ifeq ($(TOOLCH),ghs)	### GHS ###########################

### release ###
#OPT_CCOPTS =	-Ospeed
# -OI -Olink
# -Owholeprogram
#  DBG_CCOPTS =	--no_debug

### debug ###
OPT_CCOPTS =	-Onone
DBG_CCOPTS =	-G -dwarf2

SEQ_LDSCRIPT =	../$(TOOLCH)/cm0_ram.ld 

else	### GCC ###########################################

### release ###
OPT_CCOPTS =	-O3 -fno-builtin

### debug ###
#OPT_CCOPTS =	-O0 -fno-builtin
DBG_CCOPTS =	-g

SEQ_LDOPTS =	$(DBG_CCOPTS) -Xlinker -Map=$(SEQ_APP).map -Xlinker -L.  

SEQ_LDSCRIPT =	-Xlinker -T -Xlinker ../$(TOOLCH)/cm0_ram.ld

endif

SEQ_CCOPTS =	$(OPT_CCOPTS) $(DBG_CCOPTS)

##############################################################################
# Sequencer Firmware Libs
##############################################################################
SEQ_APP_LIBS =	\
	
