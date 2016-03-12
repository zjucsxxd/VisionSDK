##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    incrementally generate TAGS files. MUST be included after other packages
#    or it will not find all subdirectories
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    $Date: 2009/02/09 11:37:02 $
#
#  LANGUAGE
#    make
#
#  ID
#    $Id: tags.mk,v 1.16 2009/02/09 11:37:02 norberts Exp $
#
##############################################################################

ifndef _TAGS_MK
_TAGS_MK =	true

include		$(SDK_ROOT)/build/nbuild/platform.mk

##############################################################################

.%.t: %
	$(NBQ)etags -o $@ $^

ifeq ($(_SUB_CHKDIRS),)
_TAGDIRS := 	$(sort $(foreach d, $(_SUB_ALLDIRS),\
		$(shell [ -d $d ] && { cd $d ; pwd; } )) \
		$(call cutodir,$(shell pwd)))
_TAGSRCS := 	$(filter-out %_sym.h, \
		$(sort $(foreach d,$(_TAGDIRS), \
		$(foreach s,c h mas S C mac cpp hpp,$(wildcard $d/*.$s)))))
_TAGFILES :=	$(foreach i,$(_TAGSRCS),$(dir $i).$(notdir $i).t)
endif

ifneq ($(NBUILD_PLATFORM),cygwin)
TAGS: $(_TAGFILES)
	@echo updating: TAGS
	$(NBQ)rm -f $@; for i in $(_TAGDIRS) ; do \
	[ `echo $$i/.*.t | cut -f 1 -d " "` != "$$i/.*.t" ] && \
	cat $$i/.*.t >> $@ || true ; done

#	overflows in the openvg conformance test suite
#	$(NBQ)cat > $@ $^ /dev/null
else
TAGS:
endif

tags: TAGS

cleantags:
	@echo removing: TAGS + tagfiles
	$(NBQ)rm -f TAGS ;\
	for i in $(_TAGDIRS) ; do rm -f $$i/.*.t ; done

#	overflows in the openvg conformance test suite
#	@rm -f $(_TAGFILES) TAGS

debugtags:
	@echo VPATH=$(VPATH)
	@echo would scan directories
	@for i in $(_TAGDIRS) ; do echo $$i; done
	@echo would build tags for:
	@for i in $(_TAGSRCS) ; do echo $$i; done
	@echo tagfiles
	@for i in $(_TAGFILES) ; do echo $$i; done

TIDY_WILDS +=	.*.t
tidy:: 		cleantags

ifneq ($(shell which etags),)
all:: TAGS
else
all::
	@printf "$(COLRED)warning:$(COLNIL) %s\n" \
		"not building TAGS because 'etags' not found"
endif

endif
