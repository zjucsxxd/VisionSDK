##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    optional make package for recursive makes in projects that involve many
#    subdirs outside. most of the other make packages define some parameters
#    already
#
#  PARAMETERS
#    SUB_MAKES	directories to go and call make. add more with +=
#    SUB_DIRS	directories inolved, but without make (e.g. include dirs).
#		add more with +=
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    $Date: 2009/01/26 13:21:17 $
#
#  LANGUAGE
#    make
#
#  ID
#    $Id: sub.mk,v 1.51 2009/01/26 13:21:17 norberts Exp $
#
##############################################################################

ifndef _SUB_MK
_SUB_MK =	true

include		$(SDK_ROOT)/build/nbuild/platform.mk
include		$(SDK_ROOT)/build/nbuild/helpers.mk

ifdef _TAGS_MK
  $(warning WARNING: sub.mk should be included before tags.mk)
endif

##############################################################################
#  generate the cache with the variables
##############################################################################


__SUB_MAKES =	$(filter-out $(shell /bin/pwd), \
		$(shell for i in $(sort $(SUB_MAKES)) ; do \
		  [ -d $$i ] && (cd $$i ; /bin/pwd) done))

__SUB_DIRS =	$(shell for i in $(filter-out /usr/%,\
		$(sort $(SUB_DIRS) $(VPATH) )) ; do \
		  [ -d $$i ] && (cd $$i ; /bin/pwd) done)

.makefile.d: $(NBMAKEFILE)
	@printf "sub.mk: exporting "`pwd`"/$@\n"
	@printf > $@ "#%s\n%s\n%s\n" `/bin/pwd` \
		"__SUB_ALLMAKES += $(__SUB_MAKES)" \
		"__SUB_ALLDIRS += $(__SUB_DIRS)"

ifneq ($(MAKECMDGOALS),purge)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),depend)
include .sub-cache.d
endif

_SUB_ALLMAKES := 	$(call nsubuniq,$(filter-out $(shell /bin/pwd), \
			$(__SUB_ALLMAKES) $(__SUB_MAKES)))

_SUB_ALLDIRS := 	$(sort $(__SUB_ALLDIRS) \
			$(foreach d,$(__SUB_ALLMAKES),$(call cutodir,$d)))

.sub-cache.d: $(sort $(addsuffix /.sub-cache.d,$(_SUB_ALLMAKES))) .makefile.d
	@printf "sub.mk: collecting: "`pwd`"/$@\n"
	$(NBQ)cat $^ /dev/null > $@
	$(NBQ)echo $(addprefix $(shell pwd)/,.sub-cache.d: $(NBMAKEFILE)) \
	$(sort $(addsuffix /.sub-cache.d,$(_SUB_ALLMAKES))) >> $@
	@echo >> $@

%/.sub-cache.d:
	@make -C $(dir $@) .makefile.d $(notdir $@) || \
	{ echo sub.mk: faking $@ "(dont worry)" ; echo > $@; }

$(addprefix %/,$(NBMAKEFILE)):
	@echo `pwd`/$(firstword $(NBMAKEFILE)):0: "***" \
	there is no usable $(notdir $@) in \
	$(dir $@) "(sub.mk)" | tr -s / ; exit 1
endif
endif

##############################################################################
#  check, if all sub directories exist ...
##############################################################################

_SUB_CHKDIRS :=	$(strip $(shell for i in $(SUB_DIRS) ; \
		do [ -d $$i ] || { echo $$i ; \
		  echo 1>&2 sub.mk: SUB_DIR $$i is missing; j=`basename $$i` ;\
		  [ "$${j:0:$(ODPL)}" = "$(ODP)" ] && { \
		    echo 1>&2 sub.mk: $(ODP)dir "->" creating $$i ; \
		    mkdir $$i; \
		  } \
                } ; done) \
		$(shell for i in $(SUB_MAKES) ; \
		do [ -d $$i ] || { echo $$i ; \
		  echo 1>&2 SUB_MAKE $$i is missing; } ; done))
_SUB_CHK :=	{ [ "$(_SUB_CHKDIRS)" = "" ] || \
		{ echo $(_SUB_CHKDIRS) missing ... stop ; exit 1; } }


##############################################################################
#  targets to be applied to our sub makes
##############################################################################

.PHONY:	sub allsub cleansub emacspath showsub debugsub cleandepend \
	cvs update upcheck purge

purge::
	rm -f .*.d
	
cleandepend::
	rm -f .makefile.d .sub-cache.d
	make .makefile.d .sub-cache.d

# override to avoid recursion
SUB_CD ?=	.

# needed for grep Nothing to be done"
LANG = en_US

# apply some standard targets on all SUB_MAKES
sub allsub cleansub tidysub showtidysub:
	@$(_SUB_CHK)
	@for i in $(_SUB_ALLMAKES) $(SUB_CD) ; do \
	  if [ -f $$i/$(firstword $(NBMAKEFILE)) ] ; then \
	    make -nC $$i ${@:sub=} 2>&1 | \
	      grep -q "^make.*: Nothing to be done" || \
              make -C $$i ${@:sub=} || { kill $$$$; exit 1; } \
          else \
	    printf "make[-]: skipping directory $(COLBLK)$$i$(COLNIL)\n" ; fi \
	done $(_SUB_CM)

# apply depend targets on all SUB_MAKES that use headdep.mk
depend::
	@$(_SUB_CHK)
	@for i in $(sort $(_SUB_ALLMAKES)) $(SUB_CD) ; do \
	  if [ -f $$i/$(firstword $(NBMAKEFILE)) ] ; then \
	    grep -q "\\(headdep.mk\\)\\|\\(sub.mk\\)" $$i/$(firstword $(NBMAKEFILE)) && \
              { make -kC $$i cleandepend || { kill $$$$; exit 1; } } \
          else \
	    printf "make[-]: skipping directory $(COLBLK)$$i$(COLNIL)\n" ; fi \
	done $(_SUB_CM)


# generate a lisp command for emacs (that has be evaluated manually)
emacspath:
	@$(_SUB_CHK)
	@echo "(setq compilation-search-path (quote (nil"
	@for i in $(_SUB_ALLDIRS) ; do \
	  ( cd $$i || exit 1 ; echo "\""`pwd`"\""; ) \
        done
	@echo ")))"

# generate a lisp command for emacs (in a file)
sub.el: .sub-cache.d
	@$(_SUB_CHK)
	@echo "(setq compilation-search-path (quote (nil" > $@
	@for i in $(call nsubuniq, $(foreach d, $(shell pwd) \
	$(__SUB_ALLDIRS) $(__SUB_ALLMAKES) ,$(call cutodir,$d) $d)) ; do \
	  echo "\"$$i\""; done >> $@
	@echo ")))" >> $@

all:: sub.el

clean::
	rm -f sub.el


# show all subdirs
showsub:
	@for i in $(_SUB_ALLDIRS) ; do \
	  ( cd $$i || exit 1 ; pwd ) \
        done

# create a tarball from subdirs

tarsub: _SUB_MYDIR = $(shell mydir=`pwd`; bn=`basename $$mydir`; \
	[ "$${bn:0:2}" = "$(ODP)" ] && mydir=`dirname $$mydir`; echo $$mydir)

tarsub: _SUB_NAME = ~/tmp/$(notdir $(_SUB_MYDIR))-$(shell git rev-parse HEAD \
			| cut -b 1-6).tgz

tarsub: _SUB_TOP = $(shell basename $(NBTOP))

tarsub:
	@$(_SUB_CHK)
	@for i in $(_SUB_ALLDIRS) . ; do ( cd $$i; \
	  for j in `find . -name $(firstword $(NBMAKEFILE))` ; do \
	    echo cleaning `pwd` : `dirname $$j` ;\
	    make -C `dirname $$j` clean 2>&1 ; done) done $(_SUB_CM)
	@dirs=`for i in $(_SUB_ALLDIRS) $(_SUB_MYDIR) ; do \
	  printf "%s " $$i | sed \
	  "s|/[^[:space:]]*/$(_SUB_TOP)/|$(_SUB_TOP)/|g" ; \
	done ; echo` ; \
	cd `pwd | sed "s|/$(_SUB_TOP)/[^[:space:]]*||g"` ; \
	tar cvzf $(_SUB_NAME) --exclude=CVS --exclude=".*" --exclude "*~" \
	  $$dirs $(_SUB_TOP)/tools
	@echo created $(_SUB_NAME)

# debugging
debugsub:
	@printf "$(COLRED)vpath _____________$(COLNIL)\n"
	@echo $(VPATH)
	@printf "$(COLRED)local sub_makes _____________$(COLNIL)\n"
	@for i in $(SUB_MAKES) ; do echo $$i; done
	@printf "$(COLRED)local sub_dirs _____________$(COLNIL)\n"
	@for i in $(SUB_DIRS) ; do echo $$i; done
	@printf "$(COLRED)all sub_makes _______________$(COLNIL)\n"
	@for i in $(_SUB_ALLMAKES) ; do echo $$i; done
	@printf "$(COLRED)all sub_dirs ________________$(COLNIL)\n"
	@for i in $(_SUB_ALLDIRS) ; do echo $$i; done

#	@printf "$(COLRED) __SUB_ALLMAKES________________$(COLNIL)\n"
#	@for i in $(__SUB_ALLMAKES) ; do echo $$i; done

#	@printf "$(COLRED)all cvs_dirs ________________$(COLNIL)\n"
#	@for i in $(_SUB_CVSDIRS) ; do echo $$i; done
#	@$(_SUB_CHK)


##############################################################################
#  obsolescent: cvs commands on the whole sub-tree
##############################################################################

# keep makesupport up to date
# SUB_DIRS +=	$(SDK_ROOT)/build/nbuild

cvs:
	@$(_SUB_CHK)
	@gawk 'BEGIN{printf("starting $(COLRED)cvs $(CVSCMD)"\
	" $(CVSFLAGS)$(COLNIL) in \n");}'
	@for i in $(_SUB_CVSDIRS) ; do \
	  echo $$i ; \
        done; echo ----
	@for i in $(_SUB_CVSDIRS) ; do \
	  ( cd $$i || { echo $$i does not exist; exit 1 ; } ;\
	    gawk 'BEGIN{printf("$(COLBLK)Dir:"); \
		system("pwd | tr -d \"\n\""); \
                printf("$(COLNIL)\n");}' ; \
	    cvs $(CVSCMD) $(CVSFLAGS) $(CVSFILT) ) || $(CVSERR) ; \
	done

CVSERR =		exit 1

update:	CVSCMD = 	up -dP
update:	CVSFILT =	| grep -v "^? " | $(_SUB_CU)
update: cvs

upcheck: CVSCMD =	status 2>&1
upcheck: CVSFILT =	|grep -u "\(^File\)\|\(^cvs status\)\|\(^cvs server\)"\
			|grep -v Up-to-date | $(_SUB_CS)
upcheck: cvs

cvsdiff: CVSCMD =	diff
cvsdiff: CVSERR =	true
cvsdiff: cvs


#checkout missing subdirectories (higly experimental, use at your own risk)
cosub:
	@for i in $(SUB_MAKES) $(SUB_DIRS) ; do \
	[ -d $$i ] || \
	( printf "$(COLBLK)checkout: $$i$(COLNIL)\n"; \
	  cd `echo $$i | sed "s|/[[:alnum:]_-]\+||g"` ; \
	  p=`echo $$i | sed "s|\.\./||g;s|/| |g"` ; for d in $$p; do \
	    [ -d $$d ] && cd $$d || { cvs up -dl $$d; cd $$d; } ; \
	  done; \
          cvs up -dP ; make SUB_CACHE=false cosub 2>&1 | grep -v cosub || \
	  true )  \
	done
	@rm -f .sub-cache.d

# add a cvs tag to subdirs
TAG ?=	$(LOGNAME)_tmp
tagsub: CVSCMD =	tag $(TAG)
tagsub: cvs


##############################################################################
#  colorize the output
##############################################################################

ifeq ($(NBUILD_COLOR),yes)

_SUB_CS := 	(sed -u "s/^File.*Patch$$/§[01;35m&§[00m/;s/^File.*Modified$$/§[01;34m&§[00m/;s/^File.*Merge$$/§[01;31m&§[00m/;s/^File.*merge$$/§[01;31m&§[00m/" | tr "§" "\033")

_SUB_CU :=	(sed -u "s/^M .*/§[01;34m&§[00m/;s/^P .*/§[01;35m&§[00m/;s/^U .*/§[01;35m&§[00m/;" | tr "§" "\033")

_SUB_CM :=	| (sed -u "s/^\\(make...: Entering directory\\)\\(.*\\)$$/\\1§[01;38m\2§[00m/;" | tr "§" "\033")

else

_SUB_CS :=	cat
_SUB_CU :=	cat

endif

##############################################################################
# variables used by other make packages
##############################################################################

	
	
# apply some standard targets on all SUB_MAKES
purgesub:
	@$(_SUB_CHK)
	@for i in $(_SUB_ALLMAKES) $(SUB_CD) ; do \
	  printf "make[-]: purge directory $$i\n" ; \
	  rm -f $$i/.*.d ; \
	done $(_SUB_CM)

	
TIDY_WILDS +=	.*.d

endif
