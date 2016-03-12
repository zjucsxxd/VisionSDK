#./Kbuild

check_defined = \
    $(foreach 1,$1,$(__check_defined))
__check_defined = \
    $(if $(value $1),, \
      $(error Please define $1 pointing to kernel directory $(if $(value 2), ($(strip $2) ))))

INCLUDE_DIRS := \
	$(LINUX_S32V234_DIR)/../linux_hdr/                      \
	$(PWD)/../include/                                      \
	$(PWD)/../../../fdma/kernel/include/                    \
	$(PWD)/../../../csi/kernel/include/                     \
	$(PWD)/../../../../utils/log/include/                   \
	$(PWD)/../../../../../../platform/s32_v234/             \
	$(PWD)/../../../../../../isp/inc/                       \

CFLGS :=	\
	-g                 \
	-O0                \
	-D DEBUG           \
	-D __KERNEL_MODULE \
	-D __ARMV8         \
	-nostdinc          \
	
	
CFLGS += $(foreach includedir, $(INCLUDE_DIRS),-I$(includedir))	

KBUILD_EXTRA_SYMBOLS :=  ${PWD}/../../../csi/kernel/build-v234ce-gnu-linux-d/Module.symvers 

# module string prefix
MODULE := seq

# defines driver module object & output file
obj-m := $(MODULE).o 

# what object (source) files is the final output composed of
$(MODULE)-objs := 	\
		../src/$(MODULE)_core.o         \
		../src/$(MODULE)_ioctl.o        \
		../src/$(MODULE)_func.o         \
		../../../../utils/log/src/vdb_log.o
		
KDIR :=$(LINUX_S32V234_DIR)

### Targets ###

.PHONY: clean all 
		
all: module

module: check-env
	$(MAKE) KCPPFLAGS="$(CFLGS)" ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KDIR)  M=$(PWD) modules

allsub: all

check-env:
	$(call check_defined, LINUX_S32V234_DIR)
	
clean:
	rm -rf *~ core *.o .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order ../src/.*.cmd ../src/*.o $($(MODULE)-objs)