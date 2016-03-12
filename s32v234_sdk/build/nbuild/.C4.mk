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
#    (tempate for a) generated make package to compile C4 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C4_APP	   	name of the application to generate
#    C4_APP_SRCS	source files of the application
#    C4_APP_LIBS    full paths of libraries linked to the application
#
#    C4_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C4_LIB_SRCS	source files of the library
#    C4_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C4_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C4_DEFS      	defines (used also in header dependency generation
#
#    C4_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C4_CCOPTS	additional compiler options (C and C++)
#    C4_CXOPTS	additional compiler options (C++ only)
#    C4_ASOPTS	additional assembler options
#    C4_LDOPTS   	additional linker options
#    C4_AROPTS   	additional archiver options
#
#
#    C4_CC		C compiler
#    C4_CX		C++ compiler
#    C4_AS		assembler
#    C4_LD		linker
#    C4_AR		archiver
#	 C4_SR2ROM	srecord to rom utility
#
#    C4_PROMPT	nice string that starts short messages
#
#    C4_OD		optional, default is objdump
#    C4_OC		optional, default is objcopy
#    C4_NM		optional, default is nm
#
#    C4_SRSECS	sections to be extracted when generating an srecord
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

ifeq ($(strip $(C4_APP) $(C4_LIB)),)
  $(error error: no C4 target (lib/app) set)
endif

ifeq ($(strip $(C4_APP_SRCS) $(C4_LIB_SRCS)),)
  $(error error: no C4 sources set)
endif

ifeq ($(strip $(C4_AS)),)
  $(error error: C4_AS undefined)
endif

# defaults for some rare customization options
C4_OD ?=		objdump
C4_OC ?=		objcopy
C4_NM ?=		nm
C4_CCOO ?=	-o $@
C4_LDOO ?=	-o $@
C4_AROO ?=	$@
C4_SRSECS ?=	.text .data .rodata
C4_SR2ROM ?=	sr2rom


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C4-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C4_APP)),)
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
__C4_LIB_LIBSF =  $(call npath2abs,$(C4_LIB_LIBS))

__C4showlibs:
	$(call nshowlibs,$(__C4_LIB_LIBSF),C4)

__C4cachelibs:
	$(call ncachelibs,$(__C4_LIB_LIBSF),C4)

# our libs with full pathname
__C4_APP_LIBSF =  $(call npath2abs,$(C4_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C4appcachelibs:
	$(call ncachelibs,$(__C4_APP_LIBSF),C4)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C4TL_MFS))
	@printf "C4.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C4appcachelibs | awk > $@ '\
	  /^__C4TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C4TL_MF/ {  var[1,n[1]++]=$$0 } \
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
__C4_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C4_APP_LIBSF) \
			$(__C4TL_LIBS)))

debugtl::
	@echo __C4_APP_LIBSF=$(__C4_APP_LIBSF)
	@echo __C4TL_LIBS=$(__C4TL_LIBS)
	@echo npath2rel, __C4_APP_LIBSF=$(call npath2rel, $(__C4_APP_LIBSF))

# recursively show libs
__C4appshowlibs:
	$(call nshowlibs,$(__C4_APP_LIBSF),C4)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C4_APP)
	@make --no-print-directory __C4appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C4_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	clean all pre_all debugC4

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications



##############################################################################
# build the app
##############################################################################

ifneq ($(basename $(C4_APP)),)

_C4_APP_OBJS =	$(call _src2obj,$(C4_APP_SRCS))

_C4_APP =	$(basename $(C4_APP))

$(C4_APP): $(_C4_APP_OBJS)
	$(call nbmsg,"$(C4_PROMPT) AS" $@)	\
	$(C4_AS) $(C4_ASOPTS) 				\
	$(_C4_4ALLOPTS)	$(C4_APP_SRCS)		\
	-o $(C4_APP)

#$(C4_APP): $(_C4_APP_OBJS) $(__C4_APP_LDLIBS)
#ifeq ($(V),0)
#	@echo "  $(C4_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
#else
#	@echo "  $(C4_PROMPT) LD $@"
#endif
#	$(NBQ)$(C4_LD) $(C4_LDSCRIPT) $(C4_LDOO) $+ \
#	$(C4_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"

_C4_APP_CLEAN =	$(C4_APP) $(_C4_APP_OBJS) \
		$(_C4_APP).tsym $(_C4_APP)_sym.h $(_C4_APP).dis $(_C4_APP)_kmem.c $(_C4_APP).srec

all::	$(C4_APP) #$(_C4_APP).dis $(_C4_APP)_kmem.c $(_C4_APP)_sym.h

clean::
	rm -f $(strip $(_C4_APP_CLEAN))

debugC4::
	@echo "C4_APP =             $(C4_APP)"
	@echo "_C4_APP_OBJS =       $(_C4_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C4_LIB),)

_C4_LIB_OBJS =	$(call _src2obj,$(C4_LIB_SRCS))

$(C4_LIB): $(_C4_LIB_OBJS)
	@echo "  $(C4_PROMPT) AR $(C4_AROPTS) $(C4_LIB)" #"<=" $(_C4_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C4_AR) $(C4_AROPTS) $(C4_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C4_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1
ifneq ($(L),1)
  C4_LIB =
endif

clean::
	rm -f $(strip $(C4_LIB) $(_C4_LIB_OBJS)) 

debugC4::
	@echo "C4_LIB =             $(C4_LIB)"
	@echo "_C4_LIB_OBJS =       $(_C4_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C4 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C4_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C4_APP_LIBS) $(C4_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C4_4ALLOPTS =	$(C4_DEFS) $(C4_INCS) $(_C4_LIBINCS)

_C4_OBJS =		$(_C4_APP_OBJS) $(_C4_LIB_OBJS)

$(_C4_OBJS): COMPILE.c = 	$(call nbmsg,"$(C4_PROMPT) CC" $@) \
				  $(C4_CC) $(C4_CCOPTS) \
				  $(_C4_4ALLOPTS)

$(_C4_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C4_PROMPT) CX" $@) \
				  $(C4_CX) $(C4_CCOPTS) \
				  $(C4_CXOPTS) $(_C4_4ALLOPTS)

$(_C4_OBJS): COMPILE.S = 	$(call nbmsg,"$(C4_PROMPT) AS" $@) \
				  $(C4_AS) $(C4_ASOPTS) \
				  $(_C4_4ALLOPTS)

$(_C4_OBJS): COMPILE.s = 	$(call nbmsg,"$(C4_PROMPT) AS" $@) \
				  $(C4_AS) $(C4_ASOPTS) \
				  $(_C4_4ALLOPTS)

$(_C4_OBJS): OUTPUT_OPTION = $(C4_CCOO)


# show the variables
debugC4::
	@echo "C4_DEFS =            $(C4_DEFS)"
	@echo "C4_INCS =            $(C4_INCS)"
	@echo "_C4_LIBINCS =        $(_C4_LIBINCS)"
	@echo "_C4_4ALLOPTS =       $(_C4_4ALLOPTS)"
	@echo "_C4_APP_OBJS =       $(_C4_APP_OBJS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C4).log: $(_C4).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C4_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C4_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
$(_C4_APP).dis: $(_C4_APP).elf
	@echo disassembling: $< to $@
	$(NBQ)$(C4_OD) -S $< > $@
	$(NBQ)(echo ; echo DATA: ; $(C4_NM) -n $< | \
	grep -i " D "||echo none) >> $@

# text symbols for nicer listing of PC regs
$(_C4_APP).tsym: $(_C4_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C4_NM) -n $< | grep -i " t " > $@

# include file with symbols
$(_C4_APP)_sym.h: %_sym.h: %.elf
	@echo "generating: $@"
	@$(C4_NM) -n $< | gawk -v name=$* > $@ \
	'BEGIN{gsub("/","_",name);\
	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
	{ if($$2=="T" || $$2=="D") \
	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
	END{printf("#endif\n");}'

# srecord file
$(_C4_APP).srec: $(_C4_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C4_OC) -O srec \
	  $(addprefix -j ,$(C4_SRSECS)) $< $@
	  
# memory dump of srecord file
$(_C4_APP)_kmem.c: %_kmem.c: $(_C4_APP).srec
	@echo "generating: $@"
	@$(C4_SR2ROM) -w 8 -p none -f hex -q $< $@


##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C4_APP),)
SUB_MAKES +=	$(foreach d,$(C4_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C4_LIB_LIBS),$(dir $d))

# include directories
SUB_DIRS +=	$(subst -I,,$(C4_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C4_APP_SRCS) $(C4_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C4_APP_SRCS) $(C4_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C4_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C4_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C4_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
