##############################################################################
#
#  Copyright (c) 2006, Freescale Semiconductor. All Rights Reserved.
#  Freescale Confidential Proprietary
#
##############################################################################
#
#  CONTENT
#    not only clean, but even tidy
#
#  AUTHOR
#    Norbert Stoeffler
#
#  DATE
#    $Date: 2007/03/23 10:13:57 $
#
#  LANGUAGE
#    make
#
#  ID
#    $Id: tidy.mk,v 1.5 2007/03/23 10:13:57 norberts Exp $
#
##############################################################################

ifndef _TIDY_MK
_TIDY_MK =	true


##############################################################################

TIDY_WILDS +=	*~ 

tidy:: clean
	rm -f $(sort $(TIDY_WILDS))

showtidy:
	@echo would remove: "$(sort $(TIDY_WILDS))"

##############################################################################

endif

