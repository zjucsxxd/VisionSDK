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
#    (tempate for a) generated make package to compile C0 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C0_APP	   	name of the application to generate
#    C0_APP_SRCS	source files of the application
#    C0_APP_LIBS    full paths of libraries linked to the application
#
#    C0_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C0_LIB_SRCS	source files of the library
#    C0_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C0_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C0_DEFS      	defines (used also in header dependency generation
#
#    C0_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C0_CCOPTS	additional compiler options (C and C++)
#    C0_CXOPTS	additional compiler options (C++ only)
#    C0_ASOPTS	additional assembler options
#    C0_LDOPTS   	additional linker options
#    C0_AROPTS   	additional archiver options
#
#
#    C0_CC		C compiler
#    C0_CX		C++ compiler
#    C0_AS		assembler
#    C0_LD		linker
#    C0_AR		archiver
#
#    C0_PROMPT	nice string that starts short messages
#
#    C0_OD		optional, default is objdump
#    C0_OC		optional, default is objcopy
#    C0_NM		optional, default is nm
#
#    C0_SRSECS	sections to be extracted when generating an srecord
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

ifeq ($(strip $(C0_APP) $(C0_LIB)),)
  $(error error: no C0 target (lib/app) set)
endif

ifeq ($(strip $(C0_APP_SRCS) $(C0_LIB_SRCS)),)
  $(error error: no C0 sources set)
endif

ifeq ($(strip $(C0_CC)),)
  $(error error: C0_CC undefined)
endif

ifeq ($(strip $(C0_CX)),)
  $(error error: C0_CX undefined)
endif

ifeq ($(strip $(C0_AS)),)
  $(error error: C0_AS undefined)
endif

ifeq ($(strip $(C0_LD)),)
  $(error error: C0_LD undefined)
endif

ifeq ($(strip $(C0_AR)),)
  $(error error: C0_AR undefined)
endif

# defaults for some rare customization options
C0_OD ?=		objdump
C0_OC ?=		objcopy
C0_NM ?=		nm
C0_CCOO ?=	-o $@
C0_LDOO ?=	-o $@
C0_AROO ?=	$@
C0_SRSECS ?=	.text .data .rodata


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C0-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C0_APP)),)
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
__C0_LIB_LIBSF =  $(call npath2abs,$(C0_LIB_LIBS))

__C0showlibs:
	$(call nshowlibs,$(__C0_LIB_LIBSF),C0)

__C0cachelibs:
	$(call ncachelibs,$(__C0_LIB_LIBSF),C0)

# our libs with full pathname
__C0_APP_LIBSF =  $(call npath2abs,$(C0_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C0appcachelibs:
	$(call ncachelibs,$(__C0_APP_LIBSF),C0)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C0TL_MFS))
	@printf "C0.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C0appcachelibs | awk > $@ '\
	  /^__C0TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C0TL_MF/ {  var[1,n[1]++]=$$0 } \
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
__C0_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C0_APP_LIBSF) \
			$(__C0TL_LIBS)))

debugtl::
	@echo __C0_APP_LIBSF=$(__C0_APP_LIBSF)
	@echo __C0TL_LIBS=$(__C0TL_LIBS)
	@echo npath2rel, __C0_APP_LIBSF=$(call npath2rel, $(__C0_APP_LIBSF))

# recursively show libs
__C0appshowlibs:
	$(call nshowlibs,$(__C0_APP_LIBSF),C0)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C0_APP)
	@make --no-print-directory __C0appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C0_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	purge clean all pre_all debugC0

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications


##############################################################################
# build the app
##############################################################################

ifneq ($(basename $(C0_APP)),)

_C0_APP_OBJS =	$(call _src2obj,$(C0_APP_SRCS))

_C0_APP =	$(basename $(C0_APP))

$(C0_APP): $(_C0_APP_OBJS) $(__C0_APP_LDLIBS)
ifeq ($(V),0)
	@echo "  $(C0_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
else
	@echo "  $(C0_PROMPT) LD $@"
endif
	$(NBQ)$(C0_LD) $(C0_LDSCRIPT) $(C0_LDOO) $+ \
	$(C0_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"
	@echo "Integrating into .ael file..."
	$(C0_INT) $(C0_INTOPTS) -intfile multi/$(C0_APP).int -bsp devtree-arm64 $(C0_APP) -o $(C0_APP)_app
	@echo "Done..."
	@echo "------------------------------------------------------------"
	
_C0_APP_CLEAN =	$(C0_APP) $(_C0_APP_OBJS) \
		$(_C0_APP).tsym $(_C0_APP)_sym.h $(_C0_APP).dis

all::	$(C0_APP)

clean::
	rm -f $(strip $(_C0_APP_CLEAN))
	rm -f $(C0_FCLEAN)

debugC0::
	@echo "C0_APP =             $(C0_APP)"
	@echo "_C0_APP_OBJS =       $(_C0_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C0_LIB),)

_C0_LIB_OBJS =	$(call _src2obj,$(C0_LIB_SRCS))

$(C0_LIB): $(_C0_LIB_OBJS)
	@echo "  $(C0_PROMPT) AR $(C0_AROPTS) $(C0_LIB)" #"<=" $(_C0_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C0_AR) $(C0_AROPTS) -o $(C0_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C0_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1
ifneq ($(L),1)
  C0_LIB =
endif

clean::
	rm -f $(strip $(C0_LIB) $(_C0_LIB_OBJS))
	rm -f *.dbo *.dba *.ti

debugC0::
	@echo "C0_LIB =             $(C0_LIB)"
	@echo "_C0_LIB_OBJS =       $(_C0_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C0 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C0_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C0_APP_LIBS) $(C0_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C0_4ALLOPTS =	$(C0_DEFS) $(C0_INCS) $(_C0_LIBINCS)

_C0_OBJS =		$(_C0_APP_OBJS) $(_C0_LIB_OBJS)

$(_C0_OBJS): COMPILE.c = 	$(call nbmsg,"$(C0_PROMPT) CC" $@) \
				  $(C0_CC) $(C0_CCOPTS) \
				  $(_C0_4ALLOPTS)

$(_C0_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C0_PROMPT) CX" $@) \
				  $(C0_CX) $(C0_CCOPTS) \
				  $(C0_CXOPTS) $(_C0_4ALLOPTS)

$(_C0_OBJS): COMPILE.S = 	$(call nbmsg,"$(C0_PROMPT) AS" $@) \
				  $(C0_AS) $(C0_ASOPTS) \
				  $(_C0_4ALLOPTS)

$(_C0_OBJS): COMPILE.s = 	$(call nbmsg,"$(C0_PROMPT) AS" $@) \
				  $(C0_AS) $(C0_ASOPTS) \
				  $(_C0_4ALLOPTS)

$(_C0_OBJS): OUTPUT_OPTION = $(C0_CCOO)


# show the variables
debugC0::
	@echo "C0_DEFS =            $(C0_DEFS)"
	@echo "C0_INCS =            $(C0_INCS)"
	@echo "_C0_LIBINCS =        $(_C0_LIBINCS)"
	@echo "_C0_4ALLOPTS =       $(_C0_4ALLOPTS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C0).log: $(_C0).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C0_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C0_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
$(_C0_APP).dis: $(_C0_APP).elf
	@echo disassembling: $< to $@
	$(NBQ)$(C0_OD) -S $< > $@
	$(NBQ)(echo ; echo DATA: ; $(C0_NM) -n $< | \
	grep -i " D "||echo none) >> $@

# text symbols for nicer listing of PC regs
$(_C0_APP).tsym: $(_C0_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C0_NM) -n $< | grep -i " t " > $@

# include file with symbols
$(_C0_APP)_sym.h: %_sym.h: %.elf
	@echo "generating: $@"
	@$(C0_NM) -n $< | gawk -v name=$* > $@ \
	'BEGIN{gsub("/","_",name);\
	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
	{ if($$2=="T" || $$2=="D") \
	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
	END{printf("#endif\n");}'

# srecord file
$(_C0_APP).srec: $(_C0_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C0_OC) -O srec \
	  $(addprefix -j ,$(C0_SRSECS)) $< $@


##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C0_APP),)
SUB_MAKES +=	$(foreach d,$(C0_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C0_LIB_LIBS),$(dir $d))

# include directories
SUB_DIRS +=	$(subst -I,,$(C0_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C0_APP_SRCS) $(C0_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C0_APP_SRCS) $(C0_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C0_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C0_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C0_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
