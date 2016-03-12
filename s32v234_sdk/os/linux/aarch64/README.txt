(For following build, the u-boot utilities from aarch64 are mandatory. Please see the u-boot README in order to build the mkimage app. - Step 6)


BUILD LINUX KERNEL
==================

1) Clone Linaro GIT repository
------------------------------

  - git clone http://git.linaro.org/git/kernel/linux-linaro-tracking.git
  
2) Create a new configuration for Linux build
---------------------------------------------

  - copy vlab/s32v234_defconfig into linux-linaro-tracking/arch/arm64/configs
  - copy vlab/A53.dts into linux-linaro-tracking/arch/arm64/boot/dts
  - alter dtb-$(CONFIG_ARCH_VEXPRESS) line in linux-linaro-tracking/arch/arm64/boot/dts/Makefile to contain A53.dtb
  
      ex: dtb-$(CONFIG_ARCH_VEXPRESS) += rtsm_ve-aemv8a.dtb [..more dtb files possible..] A53.dtb
      

3) Build the kernel and device tree file
----------------------------------------

 - make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- s32v234_defconfig
 - make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image
 - make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs
 
4) Wrap the image with u-boot info
----------------------------------

 - [u-boot-arm git dir]/tools/mkimage -A arm64 -O linux -T kernel -C none -a 0x80280000 -e 0x80280000 -n "Linux" -d arch/arm64/boot/Image uImage

5) Copy resulting files to your destination
-------------------------------------------

 - Copy following files into [VLAB Works install directory]/toolboxi.mxvs4-X.X.X/examples/linux/:
    uImage
    vmlinux (only for debug)
    arch/arm64/dts/A53.dtb
    

    
BUILD LINUX ROOTFS
==================

1) Clone busybox GIT Repository
-------------------------------

  - git clone git://git.busybox.net/busybox
  
2) Configure the build
----------------------

  - in busybox directory, execute:
    
    make menuconfig
    
  - In menu config, change following settings:
  
    Busybox Settings -> Build Options -> Build BusyBox as a static binary = TRUE    
    Busybox Settings -> Build Options -> Cross Compiler prefix = aarch64-linux-gnu-
    
  - exit and save
  
3) Build the rootfs
-------------------

  - make
  - make install
  
4) Alter the built rootfs
-------------------------

  - cd to _install
  - mkdir dev lib proc sys
  - copy vlab/etc directory from here to _install/etc
  - copy [COMPILER INSTALL DIRECTORY]/aarch64-linux-gnu/libc/lib/* to _install/lib/
  - copy [COMPILER INSTALL DIRECTORY]/aarch64-linux-gnu/lib/libstdc++* to _install/lib/aarch64-linux-gnu/
  - copy [COMPILER INSTALL DIRECTORY]/aarch64-linux-gnu/lib/libgcc_s* to _install/lib/aarch64-linux-gnu/
  
5) Make ramdisk image and apply the u-boot header
-------------------------------------------------

  - sudo mkcramfs -v _install temp.cramfs
  - [u-boot-arm git dir]/tools/mkimage -A arm64 -O linux -T ramdisk -C none -a 0xC0000000 -n "ramdisk" -d temp.cramfs rImage
  
  
5) Copy resulting files to your destination
-------------------------------------------

 - Copy following files into [VLAB Works install directory]/toolboxi.mxvs4-X.X.X/examples/linux/:
    rImage
  
