##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2011-02-18
#
#  LANGUAGE
#    make
#
##############################################################################



NBMAKEFILE =	Makefile ../BUILD.mk
ODIR :=		$(shell basename `pwd`)
OS_TYPE :=	
tcl_script = 	$(SDK_ROOT)/build/nbuild/scripts/gen_apu_load.tcl

############ Target Chess ####################################################
C1_APP :=	$(APU_APP).elf
C1_APP_SRCS:=   $(APU_APP_SRCS)
C1_APP_LIBS:=	$(APU_APP_LIBS)

C1_LIB :=	$(APU_LIB)
C1_LIB_SRCS:=	$(APU_LIB_SRCS)
C1_LIB_LIBS:=	$(APU_LIB_LIBS)

C1_DEFS :=	$(APU_DEFS)
C1_INCS =	$(APU_INCS)

C1_DEFS +=
C1_INCS +=

# compiler specific options for platform, not in headdep
C1_CCOPTS +=	$(APU_CCOPTS)		
C1_CXOPTS +=	$(APU_CCOPTS)
C1_ASOPTS +=	
C1_LDOPTS +=	$(APU_LDOPTS)

########## Load generation settings
C1_LOAD_BINS =	$(APU_LOAD_BINS)
C1_LOAD_OBJS =	$(APU_LOAD_OBJS)
C1_LOAD_SRCS =	$(APU_LOAD_SRCS)
C1_LOAD_INCS =	$(APU_GRAPH_INCS)
C1_LOAD_LDOPTS =$(APU_LOAD_LDOPTS)


############ Auto Build (load_generation) ####################################

##############################################################################
# nbuild packages



C1_CC :=	chesscc -c -p APU2 +p 4  +W noodle,+Oivsq
C1_CX :=	chesscc -c -p APU2 +p 4  +W noodle,+Oivsq
C1_AS :=	chesscc -c -p APU2 +p 4
C1_LD :=	chesscc
C1_AR :=	chesscc

C1_PROMPT :=	apu/chess

C1_CCOPTS +=	\
        -p APU2  -I $(SDK_ROOT)/libs/x86/acf_offline/include 	\
		-I$(SDK_ROOT)/libs/apu/acf_target/include 		\
		-I$(SDK_ROOT)/libs/apu/common/include			\
		-I$(SDK_ROOT)/libs/apu/common/include/driver		\
		-I$(SDK_ROOT)/libs/apu/common/include/system		\
        -include apu2_kernel_port.h \
		-include acf_autokernel_inc.h \
		-DCGV_FORCE_INLINE

C1_AROPTS += -a -o
C1_CXOPTS += -DCGV_FORCE_INLINE
C1_ASOPTS +=

C1_LDOPTS += -p APU2 +W bridge,-m +W bridge,-fH +l $(SDK_ROOT)/libs/apu/acf_target/include/apu2_load.bcf

include 	$(SDK_ROOT)/build/nbuild/.C1.mk
include         $(SDK_ROOT)/build/nbuild/sub.mk
#include         $(SDK_ROOT)/build/nbuild/tags.mk
#include         $(SDK_ROOT)/build/nbuild/headdep.mk

clean:: 
	  rm -f *.h *.log *.a


############ TARGET compiler #################################################

