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
#    (tempate for a) generated make package to compile C5 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C5_APP	   	name of the application to generate
#    C5_APP_SRCS	source files of the application
#    C5_APP_LIBS    full paths of libraries linked to the application
#
#    C5_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C5_LIB_SRCS	source files of the library
#    C5_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C5_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C5_DEFS      	defines (used also in header dependency generation
#
#    C5_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C5_CCOPTS	additional compiler options (C and C++)
#    C5_CXOPTS	additional compiler options (C++ only)
#    C5_ASOPTS	additional assembler options
#    C5_LDOPTS   	additional linker options
#    C5_AROPTS   	additional archiver options
#
#
#    C5_CC		C compiler
#    C5_CX		C++ compiler
#    C5_AS		assembler
#    C5_LD		linker
#    C5_AR		archiver
#	 C5_SR2ROM	srecord to rom utility
#
#    C5_PROMPT	nice string that starts short messages
#
#    C5_OD		optional, default is objdump
#    C5_OC		optional, default is objcopy
#    C5_NM		optional, default is nm
#
#    C5_SRSECS	sections to be extracted when generating an srecord
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

ifeq ($(strip $(C5_APP) $(C5_LIB)),)
  $(error error: no C5 target (lib/app) set)
endif

ifeq ($(strip $(C5_APP_SRCS) $(C5_LIB_SRCS)),)
  $(error error: no C5 sources set)
endif

ifeq ($(strip $(C5_AS)),)
  $(error error: C5_AS undefined)
endif

# defaults for some rare customization options
C5_OD ?=		objdump
C5_OC ?=		objcopy
C5_NM ?=		nm
C5_CCOO ?=	-o $@
C5_LDOO ?=	-o $@
C5_AROO ?=	$@
C5_SRSECS ?=	.text .data .rodata
C5_SR2ROM ?=	sr2rom


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C5-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C5_APP)),)
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
__C5_LIB_LIBSF =  $(call npath2abs,$(C5_LIB_LIBS))

__C5showlibs:
	$(call nshowlibs,$(__C5_LIB_LIBSF),C5)

__C5cachelibs:
	$(call ncachelibs,$(__C5_LIB_LIBSF),C5)

# our libs with full pathname
__C5_APP_LIBSF =  $(call npath2abs,$(C5_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C5appcachelibs:
	$(call ncachelibs,$(__C5_APP_LIBSF),C5)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C5TL_MFS))
	@printf "C5.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C5appcachelibs | awk > $@ '\
	  /^__C5TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C5TL_MF/ {  var[1,n[1]++]=$$0 } \
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
__C5_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C5_APP_LIBSF) \
			$(__C5TL_LIBS)))

debugtl::
	@echo __C5_APP_LIBSF=$(__C5_APP_LIBSF)
	@echo __C5TL_LIBS=$(__C5TL_LIBS)
	@echo npath2rel, __C5_APP_LIBSF=$(call npath2rel, $(__C5_APP_LIBSF))

# recursively show libs
__C5appshowlibs:
	$(call nshowlibs,$(__C5_APP_LIBSF),C5)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C5_APP)
	@make --no-print-directory __C5appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C5_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	clean all pre_all debugC5

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications



##############################################################################
# build the app
##############################################################################

ifneq ($(basename $(C5_APP)),)

_C5_APP_OBJS =	$(call _src2obj,$(C5_APP_SRCS))

_C5_APP =	$(basename $(C5_APP))

$(C5_APP): $(_C5_APP_OBJS)
	$(call nbmsg,"$(C5_PROMPT) AS" $@)	\
	$(C5_AS) $(C5_ASOPTS) 				\
	$(_C5_4ALLOPTS)	$(C5_APP_SRCS)		\
	-o $(C5_APP)

#$(C5_APP): $(_C5_APP_OBJS) $(__C5_APP_LDLIBS)
#ifeq ($(V),0)
#	@echo "  $(C5_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
#else
#	@echo "  $(C5_PROMPT) LD $@"
#endif
#	$(NBQ)$(C5_LD) $(C5_LDSCRIPT) $(C5_LDOO) $+ \
#	$(C5_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"

_C5_APP_CLEAN =	$(C5_APP) $(_C5_APP_OBJS) \
		$(_C5_APP).tsym $(_C5_APP)_sym.h $(_C5_APP).dis $(_C5_APP)_kmem.c $(_C5_APP).srec

all::	$(C5_APP) #$(_C5_APP).dis $(_C5_APP)_kmem.c $(_C5_APP)_sym.h

clean::
	rm -f $(strip $(_C5_APP_CLEAN))

debugC5::
	@echo "C5_APP =             $(C5_APP)"
	@echo "_C5_APP_OBJS =       $(_C5_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C5_LIB),)

_C5_LIB_OBJS =	$(call _src2obj,$(C5_LIB_SRCS))

$(C5_LIB): $(_C5_LIB_OBJS)
	@echo "  $(C5_PROMPT) AR $(C5_AROPTS) $(C5_LIB)" #"<=" $(_C5_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C5_AR) $(C5_AROPTS) $(C5_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C5_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1
ifneq ($(L),1)
  C5_LIB =
endif

clean::
	rm -f $(strip $(C5_LIB) $(_C5_LIB_OBJS))

debugC5::
	@echo "C5_LIB =             $(C5_LIB)"
	@echo "_C5_LIB_OBJS =       $(_C5_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C5 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C5_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C5_APP_LIBS) $(C5_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C5_4ALLOPTS =	$(C5_DEFS) $(C5_INCS) $(_C5_LIBINCS)

_C5_OBJS =		$(_C5_APP_OBJS) $(_C5_LIB_OBJS)

$(_C5_OBJS): COMPILE.c = 	$(call nbmsg,"$(C5_PROMPT) CC" $@) \
				  $(C5_CC) $(C5_CCOPTS) \
				  $(_C5_4ALLOPTS)

$(_C5_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C5_PROMPT) CX" $@) \
				  $(C5_CX) $(C5_CCOPTS) \
				  $(C5_CXOPTS) $(_C5_4ALLOPTS)

$(_C5_OBJS): COMPILE.S = 	$(call nbmsg,"$(C5_PROMPT) AS" $@) \
				  $(C5_AS) $(C5_ASOPTS) \
				  $(_C5_4ALLOPTS)

$(_C5_OBJS): COMPILE.s = 	$(call nbmsg,"$(C5_PROMPT) AS" $@) \
				  $(C5_AS) $(C5_ASOPTS) \
				  $(_C5_4ALLOPTS)

$(_C5_OBJS): OUTPUT_OPTION = $(C5_CCOO)


# show the variables
debugC5::
	@echo "C5_DEFS =            $(C5_DEFS)"
	@echo "C5_INCS =            $(C5_INCS)"
	@echo "_C5_LIBINCS =        $(_C5_LIBINCS)"
	@echo "_C5_4ALLOPTS =       $(_C5_4ALLOPTS)"
	@echo "_C5_APP_OBJS =       $(_C5_APP_OBJS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C5).log: $(_C5).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C5_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C5_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
$(_C5_APP).dis: $(_C5_APP).elf
	@echo disassembling: $< to $@
	$(NBQ)$(C5_OD) -S $< > $@
	$(NBQ)(echo ; echo DATA: ; $(C5_NM) -n $< | \
	grep -i " D "||echo none) >> $@

# text symbols for nicer listing of PC regs
$(_C5_APP).tsym: $(_C5_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C5_NM) -n $< | grep -i " t " > $@

# include file with symbols
$(_C5_APP)_sym.h: %_sym.h: %.elf
	@echo "generating: $@"
	@$(C5_NM) -n $< | gawk -v name=$* > $@ \
	'BEGIN{gsub("/","_",name);\
	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
	{ if($$2=="T" || $$2=="D") \
	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
	END{printf("#endif\n");}'

# srecord file
$(_C5_APP).srec: $(_C5_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C5_OC) -O srec \
	  $(addprefix -j ,$(C5_SRSECS)) $< $@
	  
# memory dump of srecord file
$(_C5_APP)_kmem.c: %_kmem.c: $(_C5_APP).srec
	@echo "generating: $@"
	@$(C5_SR2ROM) -w 8 -p none -f hex -q $< $@


##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C5_APP),)
SUB_MAKES +=	$(foreach d,$(C5_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C5_LIB_LIBS),$(dir $d))

# include directories
SUB_DIRS +=	$(subst -I,,$(C5_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C5_APP_SRCS) $(C5_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C5_APP_SRCS) $(C5_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C5_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C5_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C5_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
