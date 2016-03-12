##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    automatic generation of dependencies that stem from #include directives.
#    just add all primary src files to HDEP_SRCS and include this file
#    _at the end_ of your makefile. other make packages (e.g. bcsim.mk
#    ine.mk) already add their sourcefiles, so HDEP_SRCS can normally
#    left untouched
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    2006
#
#  LANGUAGE
#    make
#
##############################################################################

ifndef _HEADDEP_MK
_HEADDEP_MK =	true

ifeq ($(origin SDK_ROOT),undefined)
  $(error error: SDK_ROOT undefined)
endif

#ifneq ($(findstring gcc (GCC) 2.,$(shell $(_HDEP_GCC) --version | head -1)),)
#  $(error "**** SORRY, this is only supported for gcc >= 3.x ****")
#endif

include $(SDK_ROOT)/build/nbuild/platform.mk


##############################################################################
# parameters
##############################################################################

ifeq ($(HDEP_SRCS),)
  $(warning warning: HDEP_SRCS is empty)
endif

H ?=		1
HEADDEP ?=	$(H)

# global parameters
_HDEP_PRE =	.
_HDEP_GCC =	gcc


##############################################################################
# all the little dependency makefiles that we include
##############################################################################

_HDEP_INC = 	$(sort \
		$(foreach i,$(filter-out ../%,$(filter-out \
		  $(HDEP_IGNORE), $(HDEP_SRCS))),\
		  $(dir $i)$(_HDEP_PRE)$(notdir $i).d) \
		$(foreach i,$(filter ../%,$(filter-out \
		  $(HDEP_IGNORE), $(HDEP_SRCS))),\
		  $(dir $i)$(_HDEP_PRE)$(_HDEP_UNIQ)$(notdir $i).d))

debugheaddep:
	@echo HDEP_SRCS=$(HDEP_SRCS)
	@echo HDEP_IGNORE=$(HDEP_IGNORE)
	@echo _HDEP_INC=$(_HDEP_INC)


##############################################################################
# rules to generate dependency files for different source file types
##############################################################################

# unique identifier to handle .c files that are included
# by different builds
_HDEP_DHASH :=
_HDEP_UNIQ :=	$(shell /bin/pwd | md5sum | head -c 6)_

# print a nice, reassuring message
_HDEP_BEGIN =	@echo headdep.mk: updating $@

define _HDEP_END
	@if [ -s $@.tmp ] ; then \
	  sed < $@.tmp 's|^\(.*\):|\1 $@:|' > $@ ;\
	  echo "#### dont care rules" >> $@ ; \
	  sed -e 's/^[^:]*: *//;/^[[:blank:]\\]*$$/ d;s/^.*[^\]$$/&:/g' \
	    < $@.tmp >> $@; \
	  rm $@.tmp ; \
	else rm $@ $@.tmp ; fi
endef
#	  sed -e 's/^[^:]*: *//;/^[[:blank:]\\]*$$/ d;s/^.*[^\]$$/&:/g' \
#	  sed -e 's/^[^:]*: *//;/^[[:blank:]\\]*$$/ d;s/^[^\]*$$/&:/g' \

define _HDEP_GNUISH
	$(_HDEP_BEGIN)
	$(NBQ)$(_HDEP_GCC) $(HDEP_FLAGS) -MM -MG -MT \
		$*-$(subst .,,$(suffix $<)).o $< > $@.tmp
	$(_HDEP_END)
endef

ifeq ($(MAKE_RESTARTS),)

# .c
$(_HDEP_PRE)$(_HDEP_UNIQ)%.c.d $(_HDEP_PRE)%.c.d: %.c
	$(_HDEP_GNUISH)

$(_HDEP_PRE)$(_HDEP_UNIQ)%.c.d $(_HDEP_PRE)%.c.d: ../%.c
	$(_HDEP_GNUISH)

# .S: gnu assembler with cpp
$(_HDEP_PRE)$(_HDEP_UNIQ)%.S.d $(_HDEP_PRE)%.S.d: %.S
	$(_HDEP_GNUISH)

$(_HDEP_PRE)$(_HDEP_UNIQ)%.S.d $(_HDEP_PRE)%.S.d: ../%.S
	$(_HDEP_GNUISH)

# .cpp
$(_HDEP_PRE)$(_HDEP_UNIQ)%.cpp.d $(_HDEP_PRE)%.cpp.d: %.cpp
	$(_HDEP_GNUISH)

$(_HDEP_PRE)$(_HDEP_UNIQ)%.cpp.d $(_HDEP_PRE)%.cpp.d: ../%.cpp
	$(_HDEP_GNUISH)

# .cc
$(_HDEP_PRE)$(_HDEP_UNIQ)%.cc.d $(_HDEP_PRE)%.cc.d: %.cc
	$(_HDEP_GNUISH)

$(_HDEP_PRE)$(_HDEP_UNIQ)%.cc.d $(_HDEP_PRE)%.cc.d: ../%.cc
	$(_HDEP_GNUISH)

# .mc: c with nmex macros
$(_HDEP_PRE)$(_HDEP_UNIQ)%.mc.d $(_HDEP_PRE)%.mc.d: %.mc
	$(_HDEP_BEGIN)
	$(_HDEP_GCC) $(HDEP_FLAGS) -x c -MM -MG -MT $*.o $< > $@.tmp
	$(_HDEP_END)

# .h
$(_HDEP_PRE)$(_HDEP_UNIQ)%.h.d $(_HDEP_PRE)%.h.d: %.h
	$(_HDEP_BEGIN)
	@$(_HDEP_GCC)  -x c -MM -MG $< > $@.tmp
	$(_HDEP_END)

# .mas: standalone assembler with macros (not validated with touch)
$(_HDEP_PRE)$(_HDEP_UNIQ)%.mas.d $(_HDEP_PRE)%.mas.d: %.mas
	$(_HDEP_BEGIN)
	@$(_HDEP_GCC) -I. $(IMPE_INCS) $(MVA_INCS) $(DPE_INCS) \
	-I $(SDK_ROOT)/build/nmex -x c \
	 -M -MT $*.dsr -MT $*.tsr -MT $*.sym -MT $*.log $< > $@.tmp
	$(_HDEP_END)

# .src: schematics, no generation tool yet
$(_HDEP_PRE)$(_HDEP_UNIQ)%.src.d $(_HDEP_PRE)%.src.d: %.src
	@touch $@

# .do: mg scripts, no generation tool yet
$(_HDEP_PRE)$(_HDEP_UNIQ)%.do.d $(_HDEP_PRE)%.do.d: %.do
	@touch $@

# .asm: standalone assembler, no generation tool yet
$(_HDEP_PRE)$(_HDEP_UNIQ)%.asm.d $(_HDEP_PRE)%.asm.d: %.asm
	@touch $@

endif

##############################################################################
# now include the dependencies
##############################################################################

HDEP_SKIP +=	clean depend purge purgesub

ifeq ($(findstring $(MAKECMDGOALS),$(HDEP_SKIP)),)
ifneq ($(HEADDEP),0)
include $(_HDEP_INC)
endif
endif

#if a .d file cannot be built, don't care and continue
$(_HDEP_INC) :

##############################################################################
# rebuild from scratch
##############################################################################

# remove all the .d files
cleandepend::
	rm -f $(_HDEP_INC)

depend::
	make cleandepend $(_HDEP_INC) HEADDEP=0

TIDY_WILDS +=	.*.d

endif
