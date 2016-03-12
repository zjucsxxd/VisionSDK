#./Kbuild

#CFLGS     := "-nostdinc\
#		-D DEBUG \
#		-D __KERNEL_MODULE \
#		-D __ZC702 \
#		-I $(PWD)/../include/ \
#		-I $(PWD)/../../../../apu/common/include \
#		-I $(KERNELDIR)/arch/arm/include \
#		-I $(KERNELDIR)/arm/include/generated \
#		$(APEXDRIVER_ADDITIONAL_FLAGS)"

check_defined = \
    $(foreach 1,$1,$(__check_defined))
__check_defined = \
    $(if $(value $1),, \
      $(error Please define $1 pointing to kernel directory $(if $(value 2), ($(strip $2) ))))

PWD := $(shell pwd)

INCLUDE_DIRS := \
	$(LINUX_S32V234_DIR)/../linux_hdr/            \
	$(PWD)/../include/                            \
	$(PWD)/../../../../utils/log/include/         \
	$(PWD)/../../../../../../platform/s32_v234/   \

CFLGS =			\
	-g                      \
        -Og                     \
	-nostdinc		\
	-D DEBUG 		\
	-D __KERNEL_MODULE 	\
	-D __ARMV8 		
	
CFLGS += $(foreach includedir, $(INCLUDE_DIRS),-I$(includedir))	
			
# module string prefix
MODULE := sram

# defines driver module object & output file
obj-m := $(MODULE).o 

# what object (source) files is the final output composed of
$(MODULE)-objs := 	\
		../src/mspace_allocator.o	\
		../src/$(MODULE)_core.o 	\
		../src/$(MODULE)_ioctl.o	\
		../src/$(MODULE)_func.o		\
		../../../../utils/log/src/vdb_log.o
		
KERNELDIR ?= $(LINUX_S32V234_DIR)

### Targets ###

.PHONY: clean all 
		
all: module

module: check-env
	$(MAKE) KCPPFLAGS="$(CFLGS)" ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERNELDIR) M=$(PWD) modules

allsub: all

check-env:
	$(call check_defined, LINUX_S32V234_DIR)
	
clean:
	rm -rf *~ core *.o .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order ../src/.*.cmd $($(MODULE)-objs)
