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
#    (tempate for a) generated make package to compile C6 firmware,
#    typically included by a core and compiler specific make package
#
#  PARAMETERS
#    C6_APP	   	name of the application to generate
#    C6_APP_SRCS	source files of the application
#    C6_APP_LIBS    full paths of libraries linked to the application
#
#    C6_LIB	   	name of the library to generate (instead or in
#			addition to the app
#    C6_LIB_SRCS	source files of the library
#    C6_LIB_LIBS    full paths of libraries required by the libs
#
#
#    C6_INCS      	include paths (beside of the paths of sub-libs), used
#			also in header dependency generation
#    C6_DEFS      	defines (used also in header dependency generation
#
#    C6_LDSCRIPT  	linker script (including switch -xxx if required)
#
#    C6_CCOPTS	additional compiler options (C and C++)
#    C6_CXOPTS	additional compiler options (C++ only)
#    C6_ASOPTS	additional assembler options
#    C6_LDOPTS   	additional linker options
#    C6_AROPTS   	additional archiver options
#
#
#    C6_CC		C compiler
#    C6_CX		C++ compiler
#    C6_AS		assembler
#    C6_LD		linker
#    C6_AR		archiver
#
#    C6_PROMPT	nice string that starts short messages
#
#    C6_OD		optional, default is objdump
#    C6_OC		optional, default is objcopy
#    C6_NM		optional, default is nm
#
#    C6_SRSECS	sections to be extracted when generating an srecord
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

ifeq ($(strip $(C6_APP) $(C6_LIB)),)
  $(error error: no C6 target (lib/app) set)
endif

ifeq ($(strip $(C6_APP_SRCS) $(C6_LIB_SRCS)),)
  $(error error: no C6 sources set)
endif

ifeq ($(strip $(C6_CC)),)
  $(error error: C6_CC undefined)
endif

ifeq ($(strip $(C6_CX)),)
  $(error error: C6_CX undefined)
endif

ifeq ($(strip $(C6_AS)),)
  $(error error: C6_AS undefined)
endif

ifeq ($(strip $(C6_LD)),)
  $(error error: C6_LD undefined)
endif

ifeq ($(strip $(C6_AR)),)
  $(error error: C6_AR undefined)
endif

# defaults for some rare customization options
C6_OD ?=		objdump
C6_OC ?=		objcopy
C6_NM ?=		nm
C6_CCOO ?=	-o $@
C6_LDOO ?=	-o $@
C6_AROO ?=	$@
C6_SRSECS ?=	.text .data .rodata .vectable


##############################################################################

include		$(SDK_ROOT)/build/nbuild/helpers.mk
include		$(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# experimental: "translibs", i.e. transitive library linking
##############################################################################

__TL_CACHE =	.C6-tl-cache.d

# include our translib cache (only if we need it)
ifeq  ($(NBUILD_TL),1)
ifneq ($(basename $(C6_APP)),)
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
__C6_LIB_LIBSF =  $(call npath2abs,$(C6_LIB_LIBS))

__C6showlibs:
	$(call nshowlibs,$(__C6_LIB_LIBSF),C6)

__C6cachelibs:
	$(call ncachelibs,$(__C6_LIB_LIBSF),C6)

# our libs with full pathname
__C6_APP_LIBSF =  $(call npath2abs,$(C6_APP_LIBS))

# recursively output libs and their dependencies on MFs
__C6appcachelibs:
	$(call ncachelibs,$(__C6_APP_LIBSF),C6)

# regenerate the translib cache if a MF has changed
$(__TL_CACHE): $(sort $(NBMAKEFILE) $(__C6TL_MFS))
	@printf "C6.mk: regenerating lib cache "`pwd`"/$@\n"
	@make --no-print-directory __C6appcachelibs | awk > $@ '\
	  /^__C6TL_LIB/ { var[0,n[0]++]=$$0 } \
	  /^__C6TL_MF/ {  var[1,n[1]++]=$$0 } \
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
__C6_APP_LDLIBS = $(call nlibuniq, $(call npath2rel, $(__C6_APP_LIBSF) \
			$(__C6TL_LIBS)))

debugtl::
	@echo __C6_APP_LIBSF=$(__C6_APP_LIBSF)
	@echo __C6TL_LIBS=$(__C6TL_LIBS)
	@echo npath2rel, __C6_APP_LIBSF=$(call npath2rel, $(__C6_APP_LIBSF))

# recursively show libs
__C6appshowlibs:
	$(call nshowlibs,$(__C6_APP_LIBSF),C6)

# show all libs and translibs nicely formated
showlibs::
	@echo "---------------------------"
	@echo $(C6_APP)
	@make --no-print-directory __C6appshowlibs __NEST="\r"
	@echo "---------------------------"
	@echo "reduced libs for linker cmd"
	@echo "---------------------------"
	@for i in $(__C6_APP_LDLIBS); do echo $$i ; done

# cleaning dependencies
cleandepend::
	rm -f $(__TL_CACHE)


##############################################################################
# phony targets
##############################################################################

.PHONY: 	clean all pre_all debugC6

all::		pre_all

pre_all:: # just a hook, maybe useful in special applications



##############################################################################
# build the app
##############################################################################

ifneq ($(basename $(C6_APP)),)

_C6_APP_OBJS =	$(call _src2obj,$(C6_APP_SRCS))

_C6_APP =	$(basename $(C6_APP))

$(C6_APP): $(_C6_APP_OBJS) $(__C6_APP_LDLIBS)
ifeq ($(V),0)
	@echo "  $(C6_PROMPT) LD $@ <= $(filter-out %.ld,$+)"
else
	@echo "  $(C6_PROMPT) LD $@"
endif
	$(NBQ)$(C6_LD) $(C6_LDSCRIPT) $(C6_LDOO) $+ \
	$(C6_LDOPTS) $(ERRORFILT)
	@echo "------------------------------------------------------------"

_C6_APP_CLEAN =	$(C6_FCLEAN) $(C6_APP) $(_C6_APP_OBJS) \
		$(_C6_APP).tsym $(_C6_APP)_sym.h $(_C6_APP).dis

all::	$(C6_APP)

clean::
	rm -f $(strip $(_C6_APP_CLEAN))

debugC6::
	@echo "C6_APP =             $(C6_APP)"
	@echo "_C6_APP_OBJS =       $(_C6_APP_OBJS)"

endif


##############################################################################
# build the lib
##############################################################################

ifneq ($(C6_LIB),)

_C6_LIB_OBJS =	$(call _src2obj,$(C6_LIB_SRCS))

$(C6_LIB): $(_C6_LIB_OBJS)
	@echo "  $(C6_PROMPT) AR $(C6_AROPTS) $(C6_LIB)" #"<=" $(_C6_LIB_OBJS)
	$(NBQ)rm -f $@
	$(NBQ)$(C6_AR) $(C6_AROPTS) $(C6_AROO) $^ $(ERRORFILT)
	@echo "------------------------------------------------------------"

all::	$(C6_LIB)

#### Supress lib removal (make clean L=0)
L ?=    1
ifneq ($(L),1)
  C6_LIB =
endif

clean::
	rm -f $(strip $(C6_LIB) $(_C6_LIB_OBJS))

debugC6::
	@echo "C6_LIB =             $(C6_LIB)"
	@echo "_C6_LIB_OBJS =       $(_C6_LIB_OBJS)"

endif


##############################################################################
# override compile/assemble rules for C6 targets
##############################################################################

# prefer files found locally over VPATH

VPATH :=		. .. $(VPATH)

# collect all our options into the final compile rules

_C6_LIBINCS =	$(filter-out -I, $(sort $(foreach d,	\
			$(C6_APP_LIBS) $(C6_LIB_LIBS),	\
			-I$(call incdir,$d))))

_C6_4ALLOPTS =	$(C6_DEFS) $(C6_INCS) $(_C6_LIBINCS)

_C6_OBJS =		$(_C6_APP_OBJS) $(_C6_LIB_OBJS)

$(_C6_OBJS): COMPILE.c = 	$(call nbmsg,"$(C6_PROMPT) CC" $@) \
				  $(C6_CC) $(C6_CCOPTS) \
				  $(_C6_4ALLOPTS)

$(_C6_OBJS): COMPILE.cpp = 	$(call nbmsg,"$(C6_PROMPT) CX" $@) \
				  $(C6_CX) \
				  $(C6_CXOPTS) $(_C6_4ALLOPTS)

$(_C6_OBJS): COMPILE.S = 	$(call nbmsg,"$(C6_PROMPT) AS" $@) \
				  $(C6_AS) $(C6_ASOPTS) \
				  $(_C6_4ALLOPTS)

$(_C6_OBJS): COMPILE.s = 	$(call nbmsg,"$(C6_PROMPT) AS" $@) \
				  $(C6_AS) $(C6_ASOPTS) \
				  $(_C6_4ALLOPTS)

$(_C6_OBJS): OUTPUT_OPTION = $(C6_CCOO)


# show the variables
debugC6::
	@echo "C6_DEFS =            $(C6_DEFS)"
	@echo "C6_INCS =            $(C6_INCS)"
	@echo "_C6_LIBINCS =        $(_C6_LIBINCS)"
	@echo "_C6_4ALLOPTS =       $(_C6_4ALLOPTS)"
	@echo "VPATH = $(VPATH)"


##############################################################################
# implicit rules for auxiliary files. not built by default, using Makefile
# must add them to all:: if required
##############################################################################

# something similar to the log file of a standalone assembler
# does currently not work, because based on stabs symbols (not dwarf)
#
#$(_C6).log: $(_C6).elf
#	@echo faking: $@
#	$(NBQ)for i in `objdump -g $< | awk \
#        '$$2=="file"&&$$4=="line"&&$$6=="addr" {print $$3}' | sort -u` ; do \
#	  [ ! -f $$i ] && echo "source file $$i not found" || { \
#	  (echo DEBUG_START; objdump -g $< ; \
#	   echo FILE_START ; cat $$i) | gawk -v fn=$$i '$(_C6_AWKSPELL)' | \
#	   grep -v FILE_START; } done > $@
#	$(NBQ)(echo ; echo DATA: ; $(C6_NM) -n $< | \
#	grep -i " D "||echo none) >> $@

# disassembly
$(_C6_APP).dis: $(_C6_APP).elf
	@echo disassembling: $< to $@
	$(NBQ)$(C6_OD) -S $< > $@
	$(NBQ)(echo ; echo DATA: ; $(C6_NM) -n $< | \
	grep -i " D "||echo none) >> $@

# text symbols for nicer listing of PC regs
$(_C6_APP).tsym: $(_C6_APP).elf
	@echo "generating: $@"
	$(NBQ)$(C6_NM) -n $< | grep -i " t " > $@

# include file with symbols
$(_C6_APP)_sym.h: %_sym.h: %.elf
	@echo "generating: $@"
	@$(C6_NM) -n $< | gawk -v name=$* > $@ \
	'BEGIN{gsub("/","_",name);\
	printf("#ifndef %s_SYM_H\n#define %s_SYM_H\n",name,name);}\
	{ if($$2=="T" || $$2=="D") \
	{gsub("[.]","_",$$3); printf("#define %s_%s 0x%s\n",name,$$3,$$1);}}\
	END{printf("#endif\n");}'

# srecord file

ifeq ($(TOOLCH),ghs)	### GHS ###########################
$(_C6_APP).srec: $(_C6_APP).elf
else	### GCC ###########################################
$(_C6_APP).run: $(_C6_APP).elf
endif
	@echo "generating: $@"
	$(NBQ)$(C6_OC) -O srec --srec-forceS3 \
	  $(addprefix -j ,$(C6_SRSECS)) $< $@
          
# C array from srecord file
ifeq ($(TOOLCH),ghs)	### GHS ###########################
$(_C6_APP).run: $(_C6_APP).elf
endif
$(_C6_APP)_srec.c: $(_C6_APP).run
ifeq ($(TOOLCH),gcc)
	@dos2unix $<
endif
	@echo "generating $(TOOLCH): $@"
	@echo "$<"
	@echo "/* Sequencer Firmware Srecord */" > $@
	@echo "">> $@
	@echo "char sequencer_srec[] = {\\" >> $@
	@echo "\"\\">> $@
	@awk '{print $$0"\\"}' $< >> $@
	@echo "\"\\">> $@
	@echo "};" >> $@

##############################################################################
# another hook
##############################################################################

all:: post_all

post_all::

##############################################################################
# variables exported to sub.mk and headdep.mk (only effective if these
# packages are used)
##############################################################################

ifneq ($(_C6_APP),)
SUB_MAKES +=	$(foreach d,$(C6_APP_LIBS),$(dir $d))
endif

SUB_MAKES +=	$(foreach d,$(C6_LIB_LIBS),$(dir $d))

# include directories
SUB_DIRS +=	$(subst -I,,$(C6_INCS))

# directories of outlying source file
SUB_DIRS +=	$(sort $(foreach d,$(filter ../%,\
		$(C6_APP_SRCS) $(C6_LIB_SRCS)),$(dir $d)))

# sources for header dependencies
HDEP_SRCS += 	$(filter-out %.s,$(C6_APP_SRCS) $(C6_LIB_SRCS))

# flags used during header dependency generation (include pathes and defines)
HDEP_FLAGS +=	$(_C6_4ALLOPTS)


##############################################################################
# submakes required for initial build of external libraries
# use the sub.mk package if they should be rebuilt (by 'allsub' target)
##############################################################################

$(filter %.o,$(C6_APP_LIBS)): %.o:
	$(NBA)make -C $(dir $@) $(notdir $@)

$(filter ../%,$(filter %.a,$(__C6_APP_LDLIBS))): %.a:
	$(NBQ)make -C $(dir $@) $(notdir $@)
