##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-08-05
#
#  LANGUAGE
#    make
#
##############################################################################

_graph2upper =	$(shell echo $(subst _apu_process_desc.hpp,,$(1)) |tr a-z A-Z)

_GRAPHS =		$(notdir $(call _graph2upper,$(APU_GRAPHS)))
APU_LOAD_BINS =		$(addsuffix _APU_LOAD.elf,$(_GRAPHS))
APU_LOAD_HEADERS =	$(addsuffix _APU_LOAD.h,$(_GRAPHS))
APU_LOAD_SRCS =		$(addsuffix __MKDBstub.c,$(_GRAPHS)) $(addsuffix .c,$(_GRAPHS))
APU_LOAD_OBJS = 	$(patsubst %.c,%.o,$(APU_LOAD_SRCS))
	
ifneq ($(findstring cygwin,$(NBUILD_PLATFORM)),)
  COMPILER_PREFIX := i686-pc-mingw32-
endif
	
APU_INCS =	\
		-I. 						\
		-I $(SDK_ROOT)/libs/apu/common/include 		\
		-I $(SDK_ROOT)/libs/apu/common/include/driver 	\
		-I $(SDK_ROOT)/libs/x86/acf_offline/include 	\
		

ifneq ($(APEX_PREBUILD),1)
C1_OTHER_LIBS = $(SDK_ROOT)/libs/apu/acf_target/build-apu-tct-sa-d/libacf_target.a \
		$(SDK_ROOT)/libs/x86/acf_offline/build-x86-gnu-linux-d/libacf_offline.a \
		$(SDK_ROOT)/libs/apu/common/build-apu-tct-sa-d/libapu_common.a 

APU_LOAD_LDOPTS = $(SDK_ROOT)/libs/apu/acf_target/build-apu-tct-sa-d/libacf_target.a \
		  $(SDK_ROOT)/libs/apu/common/build-apu-tct-sa-d/libapu_common.a 
		  
endif		

APU_LOAD_LDOPTS += $(APU_GRAPH_LIBS) \
		+W bridge,-m +W bridge,-fH +l 					\
		$(SDK_ROOT)/libs/apu/acf_target/include/apu2_load.bcf 
		
		
# parser to extract INSTANCE_ID and CLASS_ID
parser = 	$(SDK_ROOT)/build/nbuild/scripts/parse.pl

# replace hpp by _main.exe 
_graph2exe = 	$(strip $(foreach suf, hpp,\
		$(patsubst %.$(suf),%_main.exe,$(filter %.$(suf),$(1)))))

# variables we need for the autobuild process
df = 		$(*F)

APU_GRAPH_INCS +=	\
		-I $(SDK_ROOT)/libs/apu/acf_target/include	\
		-I$(SDK_ROOT)/libs/apu/acf_target/include	\
		-I$(SDK_ROOT)/libs/apu/common/include		\
		-I$(SDK_ROOT)/libs/apu/common/include/driver	\
		-I $(SDK_ROOT)/libs/x86/acf_offline/include \
		-I../. -I.

KERNEL_LDOPTS +=	\
		$(SDK_ROOT)/libs/x86/acf_offline/build-x86-gnu-linux-d/libacf_offline.a

KERNEL_EXES =	$(notdir $(call _graph2exe,$(APU_GRAPHS)))
	

%_apu_process_desc_main.exe : %_apu_process_desc_main.o
	$(NBQ) $(COMPILER_PREFIX)g++ $< $(KERNEL_LDOPTS) -o $@ -I.
	./$@ >>$(basename $@).log

%_apu_process_desc_main.o : %_apu_process_desc_main.cpp
	@$(COMPILER_PREFIX)g++ -M $(APU_GRAPH_INCS) -o $(df).d $<
	@mv -f $(df).d $(df).d.tmp
	@sed -e "s|^[^ ].*:|$(df).o:|" < $(df).d.tmp > $(df).d 
	@cp $(df).d $(df).P; 
	@sed -e 's/#.*//' -e 's/^.*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P
	@rm -f $(df).d
	@rm -f $(df).d.tmp
	$(call nbmsg,"$(C2_PROMPT) CX" $@) \
	$(COMPILER_PREFIX)g++ -c $(APU_GRAPH_INCS) -std=c++0x -o  $@ $<

	
%_apu_process_desc_main.cpp: %_apu_process_desc.hpp User_KernelDB.h
	@echo "Creating $@ with INST_ID $(shell perl $(parser) $< INST)" 
	@echo "#include \"User_KernelDB.h\"" >> $@
	@echo "#include \"$<\"" >> $@
	@echo "int main ()" >> $@
	@echo "{" >> $@
	@echo "   int lRetVal = 0;" >> $@
	@echo "   $(shell perl $(parser) $< CLASS) obj;" >> $@
	@echo "   obj.Create();" >> $@
	@echo "   if (obj.RetErrorState() == 0)" >> $@
	@echo "   { " >> $@
	@echo "      if (obj.Resolve() == 0)" >> $@
	@echo "      { " >> $@
	@echo "         obj.GenerateProcess();" >> $@
	@echo "      }" >> $@
	@echo "      else" >> $@
	@echo "      { " >> $@
	@echo "         lRetVal = 1;" >> $@
	@echo "      }" >> $@
	@echo "   }" >> $@
	@echo "   else" >> $@
	@echo "   { " >> $@
	@echo "      lRetVal = 1;" >> $@
	@echo "   }" >> $@
	@echo "   return lRetVal;" >> $@
	@echo "}" >> $@


	
all:: $(C1_OTHER_LIBS) $(KERNEL_EXES) $(APU_LOAD_HEADERS)
	

%_APU_LOAD.h : %_APU_LOAD.elf
	read_elf -pPMh=32 -mDMb=8 -mVMb=1024 $< -eGb -t $(tcl_script) -Tload_name=$(subst _APU_LOAD.elf,,$<) > $@

User_KernelDB.h:
	@$(foreach inc, $(basename $(APU_GRAPH_LIBS)), \
	echo "#include \"$(inc)_db.h\"" >> $@;\
	)
		
		
clean::
	rm -f $(KERNEL_EXES) *_apu_process_desc_main.* *nativekernel.hpp *KernelDB.h build_args.txt *.P *.c *.cpp *.map
ifneq ($(APEX_PREBUILD),1)
	rm -f *.h *.hpp
endif
	

