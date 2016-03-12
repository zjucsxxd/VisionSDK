# don't edit, generated from _core.mk
##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2009, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    (tempate for a) generated make package to compile C1 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C1_APP	   	name of the application to generate
#    C1_APP_SRCS	source files of the application
#    C1_APP_LIBS    full paths of libraries linked to the application
#
#    C1_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C1_LIB_SRCS	source files of the library
#    C1_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C1_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C1_DEFS      	defines (used also in header dependency generation
#
#    C1_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C1_CCOPTS	additional compiler options (C and C++)
#    C1_CXOPTS	additional compiler options (C++ only)
#    C1_ASOPTS	additional assembler options
#    C1_LDOPTS   	additional linker options
#    C1_AROPTS   	additional archiver options
#
#
#    C1_CC		C compiler
#    C1_CX		C++ compiler
#    C1_AS		assembler
#    C1_LD		linker
#    C1_AR		archiver
#
#    C1_PROMPT	nice string that starts short messages
#
#    C1_OD		optional, default is objdump
#    C1_OC		optional, default is objcopy
#    C1_NM		optional, default is nm
#
#    C1_SRSECS	sections to be extracted when generating an srecord
#			file
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    2009-12-17 initial
#    2011-04-04 completely revised
#
#  LANGUAGE
#    make
#
##############################################################################

##############################################################################
# check required parameters
##############################################################################

ifeq ($(origin SDK_ROOT),undefined)
  $(error error: SDK_ROOT undefined)
endif

# ifeq ($(strip $(C1_APP) $(C1_LIB)),)
  # $(error error: no C1 target (lib/app) set)
# endif

# ifeq ($(strip $(C1_APP_SRCS) $(C1_LIB_SRCS)),)
  # $(error error: no C1 sources set)
# endif

ifeq ($(strip $(C1_CC)),)
  $(error error: C1_CC undefined)
endif

ifeq ($(strip $(C1_CX)),)
  $(error error: C1_CX undefined)
endif

ifeq ($(strip $(C1_AS)),)
  $(error error: C1_AS undefined)
endif

ifeq ($(strip $(C1_LD)),)
  $(error error: C1_LD undefined)
endif

ifeq ($(strip $(C1_AR)),)
  $(error error: C1_AR undefined)
endif

# defaults for some rare customization options
C1_OD ?=		objdump
C1_OC ?=		objcopy
C1_NM ?=		nm
C1_CCOO ?=	-o $@
C1_LDOO ?=	-o $@
C1_AROO ?=	$@
C1_SRSECS ?=	.text .data .rodata


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C1-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C1_APP)),)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),purge)
ifneq ($(MAKECMDGOALS),purgesub)
ifneq ($(MAKECMDGOALS),depend)
include $(__TL_CACHE)
endif
endif
endif
endif
endif
endif

# 3 recursion rules from lib part
__C1_LIB_LIBSF =  $(call npath2abs,$(C1_LIB_LIBS))

__C1showlibs:
	$(call nshowlibs,$(__C1_LIB_LIBSF),C1)

__C1cachelibs:
	$(call ncachelibs,$(__C1_LIB_LIBSF),C1)

# our libs with full pathname
__C1_APP_LIBSF =  $(call npath2abs,$(C1_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C1appcachelibs:
	$(call ncachelibs,$(__C1_APP_LIBSF),C1)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C1TL_MFS))
	@printf "C1.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C1appcachelibs | awk > $@ '\
	  /^__C1TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C1TL_MF/ {  var[1,n[1]++]=$$0 } \
	  END{ \
	    for(v=0;v<2;v++){ \
	      l=0; \
	      for(i=n[v];i>0;i--){ \
	        for(j=0;j<l;j++) \
		  if(a[j]==var[v,i]) break; \
	        if(j==l) a[l++]=var[v,i]; \
	      } \
	      for(j=l-1;j>=0;j--) print a[j]; \
            } \
	  }'

# recuded libs for linker
__C1_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C1_APP_LIBSF) \
			$(__C1TL_LIBS)))

debugtl::
	@echo __C1_APP_LIBSF=$(__C1_APP_LIBSF)
	@echo __C1TL_LIBS=$(__C1TL_LIBS)
	@echo npath2rel, __C1_APP_LIBSF=$(call npath2rel, $(__C1_APP_LIBSF))

# recursively show libs
__C1appshowlibs:
	$(call nshowlibs,$(__C1_APP_LIBSF),C1)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C1_APP)
	@make --no-print-directory __C1appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C1_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	clean all pre_all debugC1

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications


##############################################################################
# build the load binary
##############################################################################
_C1_LOAD_OBJS = $(APU_LOAD_OBJS)
_C1_LOAD_CCOPTS = 	$(C1_LOAD_CCOPTS) $(C1_LOAD_INCS)	
_C1_LOAD_LDOPTS = 	$(C1_LOAD_LDOPTS)
	
# +W bridge options ask the linker (bridge) to generate a map file with Hex addresses
%_APU_LOAD.elf: %.o %__MKDBstub.o

ifeq ($(V),0)
	@echo "  $(C1_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
else
	@echo "  $(C1_PROMPT) LD $@"
endif
	$(NBQ)$(C1_LD) $(C1_LDOO)  $+ $(_C1_LOAD_LDOPTS)
	@echo "------------------------------------------------------------"
	
all:: 

clean::
	rm -f $(C1_LOAD_BINS) $(_C1_LOAD_OBJS)
	
##############################################################################
# build the app
###########################################APU_INCS###################################

ifneq ($(basename $(C1_APP)),)

_C1_APP_OBJS =	$(call _src2obj,$(C1_APP_SRCS))

_C1_APP =	$(basename $(C1_APP))

$(C1_APP): $(_C1_APP_OBJS) $(__C1_APP_LDLIBS)
ifeq ($(V),0)
	@echo "  $(C1_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
else
	@echo "  $(C1_PROMPT) LD $@"
endif
	$(NBQ)$(C1_LD) $(C1_LDSCRIPT) $(C1_LDOO) $+ $(C1_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"

_C1_APP_CLEAN =	$(C1_APP) $(_C1_APP_OBJS) \
		$(_C1_APP).tsym $(_C1_APP)_sym.h $(_C1_APP).dis

all::	$(C1_APP)

clean::
	rm -f $(strip $(_C1_APP_CLEAN))

debugC1::
	@echo "C1_APP =             $(C1_APP)"
	@echo "_C1_APP_OBJS =       $(_C1_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C1_LIB),)

_C1_LIB_OBJS =	$(call _src2obj,$(C1_LIB_SRCS))

$(C1_LIB): $(_C1_LIB_OBJS)
	@echo "  $(C1_PROMPT) AR $(C1_AROPTS) $(C1_LIB)" #"<=" $(_C1_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C1_AR) $(C1_AROPTS) $(C1_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C1_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1 
ifneq ($(L),1)
  C1_LIB =
endif

clean::
	rm -f $(strip $(C1_LIB) $(_C1_LIB_OBJS))

debugC1::
	@echo "C1_LIB =             $(C1_LIB)"
	@echo "_C1_LIB_OBJS =       $(_C1_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C1 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C1_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C1_APP_LIBS) $(C1_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C1_4ALLOPTS =	$(C1_DEFS) $(C1_INCS) $(_C1_LIBINCS)

_C1_OBJS =		$(_C1_APP_OBJS) $(_C1_LIB_OBJS)

$(_C1_OBJS): COMPILE.c = 	$(call nbmsg,"$(C1_PROMPT) CC" $@) \
				  $(C1_CC) $(C1_CCOPTS) \
				  $(_C1_4ALLOPTS)

$(_C1_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C1_PROMPT) CX" $@) \
				  $(C1_CX) $(C1_CCOPTS) \
				  $(C1_CXOPTS) $(_C1_4ALLOPTS)

$(_C1_OBJS): COMPILE.S = 	$(call nbmsg,"$(C1_PROMPT) AS" $@) \
				  $(C1_AS) $(C1_ASOPTS) \
				  $(_C1_4ALLOPTS)

$(_C1_OBJS): COMPILE.s = 	$(call nbmsg,"$(C1_PROMPT) AS" $@) \
				  $(C1_AS) $(C1_ASOPTS) \
				  $(_C1_4ALLOPTS)
				  
$(_C1_OBJS): COMPILE.cl = 	$(call nbmsg,"$(C1_PROMPT) CL" $@) \
				  $(C1_CC) $(C1_CCOPTS) \
				  $(_C1_4ALLOPTS)

$(_C1_OBJS): OUTPUT_OPTION = $(C1_CCOO)

$(_C1_LOAD_OBJS): COMPILE.c = 	$(call nbmsg,"$(C1_PROMPT) CC" $@) \
				  $(C1_CC) $(_C1_LOAD_CCOPTS) \
				 

$(_C1_LOAD_OBJS):
	$(call nbmsg,"$(C1_PROMPT) CC" $@) \
	$(C1_CC) $(C1_CCOPTS) $(patsubst %.o,%.c,$@) -o $@

# show the variables
debugC1:: 
	@echo "C1_DEFS =            $(C1_DEFS)"
	@echo "C1_INCS =            $(C1_INCS)"
	@echo "_C1_LIBINCS =        $(_C1_LIBINCS)"
	@echo "_C1_4ALLOPTS =       $(_C1_4ALLOPTS)"
	@echo "APU_LOAD_SRCS =       $(APU_LOAD_SRCS)"
	@echo "_C1_LOAD_OBJS =       $(_C1_LOAD_OBJS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C1).log: $(_C1).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C1_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C1_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
#$(_C1_APP).dis: $(_C1_APP).elf
#	@echo disassembling: $< to $@
#	$(NBQ)$(C1_OD) -S $< > $@
#	$(NBQ)(echo ; echo DATA: ; $(C1_NM) -n $< | \
#	grep -i " D "||echo none) >> $@
#
# text symbols for nicer listing of PC regs
#$(_C1_APP).tsym: $(_C1_APP).elf
#	@echo "generating: $@"
#	$(NBQ)$(C1_NM) -n $< | grep -i " t " > $@
#
# include file with symbols
#$(_C1_APP)_sym.h: %_sym.h: %.elf
#	@echo "generating: $@"
#	@$(C1_NM) -n $< | gawk -v name=$* > $@ \
#	'BEGIN{gsub("/","_",name);\
#	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
#	{ if($$2=="T" || $$2=="D") \
#	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
#	END{printf("#endif\n");}'

# srecord file
#$(_C1_APP).srec: $(_C1_APP).elf
#	@echo "generating: $@"
#	$(NBQ)$(C1_OC) -O srec \
#	  $(addprefix -j ,$(C1_SRSECS)) $< $@


##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C1_APP),)
SUB_MAKES +=	$(foreach d,$(C1_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C1_LIB_LIBS),$(dir $d))

SUB_MAKES +=	$(foreach d,$(C1_OTHER_LIBS),$(dir $d))

SUB_MAKES +=	$(foreach d,$(APU_GRAPH_LIBS),$(dir $d))


# include directories
SUB_DIRS +=	$(subst -I,,$(C1_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C1_APP_SRCS) $(C1_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C1_APP_SRCS) $(C1_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C1_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C1_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C1_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
