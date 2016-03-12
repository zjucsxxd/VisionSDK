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
#    (tempate for a) generated make package to compile C2 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C2_APP	   	name of the application to generate
#    C2_APP_SRCS	source files of the application
#    C2_APP_LIBS    full paths of libraries linked to the application
#
#    C2_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C2_LIB_SRCS	source files of the library
#    C2_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C2_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C2_DEFS      	defines (used also in header dependency generation
#
#    C2_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C2_CCOPTS	additional compiler options (C and C++)
#    C2_CXOPTS	additional compiler options (C++ only)
#    C2_ASOPTS	additional assembler options
#    C2_LDOPTS   	additional linker options
#    C2_AROPTS   	additional archiver options
#
#
#    C2_CC		C compiler
#    C2_CX		C++ compiler
#    C2_AS		assembler
#    C2_LD		linker
#    C2_AR		archiver
#
#    C2_PROMPT	nice string that starts short messages
#
#    C2_OD		optional, default is objdump
#    C2_OC		optional, default is objcopy
#    C2_NM		optional, default is nm
#
#    C2_SRSECS	sections to be extracted when generating an srecord
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

ifeq ($(strip $(C2_APP) $(C2_LIB)),)
  #$(warning warning: no C2 target (lib/app) set)
endif

# ifeq ($(strip $(C2_APP_SRCS) $(C2_LIB_SRCS)),)
  # $(error error: no C2 sources set)
# endif

ifeq ($(strip $(C2_CC)),)
  $(error error: C2_CC undefined)
endif

ifeq ($(strip $(C2_CX)),)
  $(error error: C2_CX undefined)
endif

ifeq ($(strip $(C2_AS)),)
  $(error error: C2_AS undefined)
endif

ifeq ($(strip $(C2_LD)),)
  $(error error: C2_LD undefined)
endif

ifeq ($(strip $(C2_AR)),)
  $(error error: C2_AR undefined)
endif

# defaults for some rare customization options
C2_OD ?=		objdump
C2_OC ?=		objcopy
C2_NM ?=		nm
C2_CCOO ?=	-o $@
C2_LDOO ?=	-o $@
C2_AROO ?=	$@
C2_SRSECS ?=	.text .data .rodata


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C2-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C2_APP)),)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),purge)
ifneq ($(MAKECMDGOALS),depend)
ifneq ($(MAKECMDGOALS),purgesub)
include $(__TL_CACHE)
endif
endif
endif
endif
endif
endif

# 3 recursion rules from lib part
__C2_LIB_LIBSF =  $(call npath2abs,$(C2_LIB_LIBS))

__C2showlibs:
	$(call nshowlibs,$(__C2_LIB_LIBSF),C2)

__C2cachelibs:
	$(call ncachelibs,$(__C2_LIB_LIBSF),C2)

# our libs with full pathname
__C2_APP_LIBSF =  $(call npath2abs,$(C2_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C2appcachelibs:
	$(call ncachelibs,$(__C2_APP_LIBSF),C2)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C2TL_MFS))
	@printf "C2.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C2appcachelibs | awk > $@ '\
	  /^__C2TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C2TL_MF/ {  var[1,n[1]++]=$$0 } \
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
__C2_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C2_APP_LIBSF) \
			$(__C2TL_LIBS)))

debugtl::
	@echo __C2_APP_LIBSF=$(__C2_APP_LIBSF)
	@echo __C2TL_LIBS=$(__C2TL_LIBS)
	@echo npath2rel, __C2_APP_LIBSF=$(call npath2rel, $(__C2_APP_LIBSF))

# recursively show libs
__C2appshowlibs:
	$(call nshowlibs,$(__C2_APP_LIBSF),C2)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C2_APP)
	@make --no-print-directory __C2appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C2_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	clean all pre_all debugC2

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications


##############################################################################
# build the app (and run it, to create *_db.h )
##############################################################################

ifneq ($(basename $(C2_APP)),)

_C2_APP_OBJS =	$(call _src2obj2,$(C2_APP_SRCS))

_C2_APP =	$(basename $(C2_APP))

$(C2_APP): $(_C2_APP_OBJS) $(__C2_APP_LDLIBS)
ifeq ($(V),0)
	@echo "  $(C2_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
else
	@echo "  $(C2_PROMPT) LD $@"
endif
	$(NBQ)$(C2_LD) $(C2_LDSCRIPT) $(C2_LDOO) $+ \
	$(C2_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"

_C2_APP_CLEAN =	$(C2_APP) $(_C2_APP_OBJS) \
		$(_C2_APP).tsym $(_C2_APP)_sym.h $(_C2_APP).dis

all::	$(C2_APP)

clean::
	rm -f $(strip $(_C2_APP_CLEAN))

debugC2::
	@echo "C2_APP =             $(C2_APP)"
	@echo "_C2_APP_OBJS =       $(_C2_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C2_LIB),)

_C2_LIB_OBJS =	$(call _src2obj2,$(C2_LIB_SRCS))

$(C2_LIB): $(_C2_LIB_OBJS)
	@echo "  $(C2_PROMPT) AR $(C2_AROPTS) $(C2_LIB)" #"<=" $(_C2_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C2_AR) $(C2_AROPTS) $(C2_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C2_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1
ifneq ($(L),1)
  C2_LIB =
endif

clean::
	rm -f $(strip $(C2_LIB) $(_C2_LIB_OBJS))

debugC2::
	@echo "C2_LIB =             $(C2_LIB)"
	@echo "_C2_LIB_OBJS =       $(_C2_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C2 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C2_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C2_APP_LIBS) $(C2_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C2_4ALLOPTS =	$(C2_DEFS) $(C2_INCS) $(_C2_LIBINCS)

_C2_OBJS =		$(_C2_APP_OBJS) $(_C2_LIB_OBJS)

$(_C2_OBJS): COMPILE.c = 	$(call nbmsg,"$(C2_PROMPT) CC" $@) \
				  $(C2_CC) $(C2_CCOPTS) \
				  $(_C2_4ALLOPTS)

$(_C2_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C2_PROMPT) CX" $@) \
				  $(C2_CX) $(C2_CCOPTS) \
				  $(C2_CXOPTS) $(_C2_4ALLOPTS)

$(_C2_OBJS): COMPILE.S = 	$(call nbmsg,"$(C2_PROMPT) AS" $@) \
				  $(C2_AS) $(C2_ASOPTS) \
				  $(_C2_4ALLOPTS)

$(_C2_OBJS): COMPILE.s = 	$(call nbmsg,"$(C2_PROMPT) AS" $@) \
				  $(C2_AS) $(C2_ASOPTS) \
				  $(_C2_4ALLOPTS)

$(_C2_OBJS): OUTPUT_OPTION = $(C2_CCOO)


# show the variables
debugC2::
	@echo "C2_DEFS =            $(C2_DEFS)"
	@echo "C2_INCS =            $(C2_INCS)"
	@echo "_C2_LIBINCS =        $(_C2_LIBINCS)"
	@echo "_C2_4ALLOPTS =       $(_C2_4ALLOPTS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C2).log: $(_C2).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C2_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C2_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
$(_C2_APP).dis: $(_C2_APP).elf
	@echo disassembling: $< to $@
	$(NBQ)$(C2_OD) -S $< > $@
	$(NBQ)(echo ; echo DATA: ; $(C2_NM) -n $< | \
	grep -i " D "||echo none) >> $@

# text symbols for nicer listing of PC regs
$(_C2_APP).tsym: $(_C2_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C2_NM) -n $< | grep -i " t " > $@

# include file with symbols
$(_C2_APP)_sym.h: %_sym.h: %.elf
	@echo "generating: $@"
	@$(C2_NM) -n $< | gawk -v name=$* > $@ \
	'BEGIN{gsub("/","_",name);\
	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
	{ if($$2=="T" || $$2=="D") \
	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
	END{printf("#endif\n");}'

# srecord file
$(_C2_APP).srec: $(_C2_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C2_OC) -O srec \
	  $(addprefix -j ,$(C2_SRSECS)) $< $@


#_C2_APP_GRAPH:=	$(basename C2_APP_GRAPH)
#$(_C2_APP_GRAPH):  $(_C2_APP_GRAPH)


##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C2_APP),)
SUB_MAKES +=	$(foreach d,$(C2_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C2_LIB_LIBS),$(dir $d))

# include directories
SUB_DIRS +=	$(subst -I,,$(C2_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C2_APP_SRCS) $(C2_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C2_APP_SRCS) $(C2_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C2_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C2_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C2_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
