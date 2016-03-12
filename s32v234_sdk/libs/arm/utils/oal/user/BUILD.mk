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
#    OAL for Linux lib
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-08-09
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../../../s32v234_sdk
ARM_LIB =   liboal.a

##############################################################################
# liboal.a
##############################################################################
ifneq (,$(findstring ghs-integrity,$(ODIR)))
    VPATH +=	$(SDK_ROOT)/libs/arm/utils/oal/user/src/integrity
    
    ARM_LIB_SRCS +=                                             \
        oal_semaphore.cpp                                       \
        oal_memory.cpp                                          \
        oal_interrupt.cpp                                       \
        oal_signal.cpp                                          \
        oal_not_implemented.cpp
        
else
ifneq (,$(findstring sa-d,$(ODIR)))
    VPATH +=	$(SDK_ROOT)/libs/arm/utils/oal/user/src/standalone
    
    ARM_LIB_SRCS +=                                             \
        oal_memory.cpp                                          \
        oal_semaphore.cpp                                       \
        oal_cont_alloc.cpp                                      \
	oal_irq.cpp                                             \
        oal_mspace.cpp

else
    VPATH +=	$(SDK_ROOT)/libs/arm/utils/oal/user/src/linux
    
    ARM_LIB_SRCS +=                                             \
        oal_memory.cpp                                          \
        oal_memory_rc.cpp                                       \
        oal_process.cpp                                         \
        oal_task.cpp                                            \
        oal_file.cpp                                            \
        oal_memory_pool.cpp                                     \
        oal_not_implemented.cpp                                 \
        oal_semaphore.cpp                                       \
        oal_timer.cpp                                           \
        oal_signal.cpp                                          \
        oal_cont_alloc.cpp                                      \
        oal_mspace.cpp
endif
endif

ARM_INCS +=                                                     \
        -I$(SDK_ROOT)/libs/arm/utils/oal/user/include                 \
        -I$(SDK_ROOT)/libs/arm/utils/oal/kernel/include

##############################################################################
