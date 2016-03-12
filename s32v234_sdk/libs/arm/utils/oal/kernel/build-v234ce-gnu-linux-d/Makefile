 #./Kbuild

check_defined = \
    $(foreach 1,$1,$(__check_defined))
__check_defined = \
    $(if $(value $1),, \
      $(error Please define $1 pointing to kernel directory $(if $(value 2), ($(strip $2) ))))

obj-m	:= oal_cma.o
oal_cma-objs := 	../src/linux/oal_alloc.o \
			../src/linux/oal_mem.o \
			../src/linux/oal_mspace.o \
			../src/linux/ioctl_func.o \
			../src/linux/cma_list.o \
			../src/linux/cache.o

KERNELDIR ?= $(LINUX_S32V234_DIR)

PWD       := $(shell pwd)
CFLGS     := "-D DEBUG \
		-D __KERNEL_MODULE \
		-D __ARMV8 \
		-I $(PWD)/../include/ \
		-I $(KERNELDIR)/arch/arm/include \
		-I $(KERNELDIR)/arm/include/generated \
		$(APEXDRIVER_ADDITIONAL_FLAGS)"

all: check-env
	$(MAKE) KCPPFLAGS=$(CFLGS) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERNELDIR) M=$(PWD)
	
allsub: all

check-env:
	$(call check_defined, LINUX_S32V234_DIR)

clean:
	$(MAKE) KCPPFLAGS=$(CFLGS) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERNELDIR) M=$(PWD) clean
	rm -rf $(apex2-objs) ../src/linux/.*.cmd ../src/linux/*.o