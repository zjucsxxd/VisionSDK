 #./Kbuild

check_defined = \
    $(foreach 1,$1,$(__check_defined))
__check_defined = \
    $(if $(value $1),, \
      $(error Please define $1 pointing to kernel directory $(if $(value 2), ($(strip $2) ))))
      
obj-m	:= apex2.o
apex2-objs := 	../src/linux/apexdriver.o        \
		../src/linux/apexdriver_ioctl.o        \
		../src/linux/apexdriver_hw_reg_user.o    \
		../src/functions/apexdriver_cmem_if_hal.o               \
		../src/functions/apexdriver_global_hal.o                \
		../src/functions/apexdriver_stio_hal.o                  \
		../src/functions/apexdriver_apu_hal.o                   \
		../src/functions/apexdriver_apumk_hal_cmdque.o          \
		../src/functions/apexdriver_apumk_hal_comm.o            \
		../src/functions/apexdriver_mcdma_hal.o                 \
		../src/functions/apexdriver_seq_hal.o    

KERNELDIR ?= $(LINUX_S32V234_DIR)

PWD       := $(shell pwd)
CFLGS     := "-D DEBUG \
		-D __KERNEL_MODULE \
		-D __ARMV8 \
		-I $(PWD)/../include/ \
		-I $(PWD)/../include/functions \
		-I $(PWD)/../../user/include \
		-I $(PWD)/../include/linux \
		-I $(PWD)/../../../../../apu/common/include \
		-I $(PWD)/../../../../../apu/common/include/system \
		$(APEXDRIVER_ADDITIONAL_FLAGS)"
all: check-env
	$(MAKE) KCPPFLAGS=$(CFLGS) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERNELDIR) M=$(PWD)
	
allsub: all

check-env:
	$(call check_defined, LINUX_S32V234_DIR)

clean:
	$(MAKE) KCPPFLAGS=$(CFLGS) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERNELDIR) M=$(PWD) clean
	rm -rf $(apex2-objs) ../src/functions/.*.cmd ../src/linux/.*.cmd ../src/linux/functions/.*.cmd