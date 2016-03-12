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
tcl_script = 	$(SDK_ROOT)/build/nbuild/scripts/gen_apu_load_cl.tcl

############ Target Chess ####################################################
C1_APP :=	$(ACL_APP).elf
C1_APP_SRCS:=   $(ACL_APP_SRCS)
C1_APP_LIBS:=	$(ACL_APP_LIBS)

C1_LIB :=	$(ACL_LIB)
C1_LIB_SRCS:=	$(ACL_LIB_SRCS)
C1_LIB_LIBS:=	$(ACL_LIB_LIBS)

C1_DEFS :=	$(ACL_DEFS)
C1_INCS =	$(ACL_INCS)

C1_DEFS +=
C1_INCS +=

# compiler specific options for platform, not in headdep
C1_CCOPTS +=	$(ACL_CCOPTS)		
C1_CXOPTS +=	$(ACL_CCOPTS)
C1_ASOPTS +=	
C1_LDOPTS +=	$(ACL_LDOPTS)

########## Load generation settings
C1_LOAD_BINS =	$(ACL_LOAD_BINS)
C1_LOAD_OBJS =	$(ACL_LOAD_OBJS)
C1_LOAD_SRCS =	$(ACL_LOAD_SRCS)
C1_LOAD_INCS =	$(ACL_GRAPH_INCS)
C1_LOAD_LDOPTS =$(ACL_LOAD_LDOPTS)


############ Auto Build (load_generation) ####################################

##############################################################################
# nbuild packages



C1_CC :=	chesscc -c +p4
C1_CX :=	chesscc -c +p4
C1_AS :=	chesscc -c +p4
C1_LD :=	chesscc
C1_AR :=	chesscc

C1_PROMPT :=	apu/chess

C1_CCOPTS +=	\

C1_AROPTS += -a -o
C1_CXOPTS +=
C1_ASOPTS +=

C1_LDOPTS += 

include 	$(SDK_ROOT)/build/nbuild/.C1.mk
include         $(SDK_ROOT)/build/nbuild/sub.mk

clean:: 
	  rm -f *.h *.log *.a


############ TARGET compiler #################################################

