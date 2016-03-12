Support Libraries build
=======================

All libraries are part of the auto build, i.e. they are build when the 
appropriate application referencing them is build.

For Linux build, the kernel modules are necessary to build separately! 
(see below)

For INTEGRITY build, no building here is required (libraries gpjs are included 
in the application project) 

To build the APEX and OAL kernel libraries, their gpj can be added to BSP's gpj, 
which should be rebuild afterwards.

In case the BSP cannot be rebuild (sources not available), the APEX and OAL 
prebuild binaries are located in appropriate folders and specifically linked to 
an Integrity OS kernel project located in s32v234_sdk/os/integrity/apex_kernel.


LINUX KERNEL MODULES BUILD PREREQUISITES
----------------------------------------

In order to build kernel modules, it's necessary to export following environment 
variables:

export ARCH=arm						    (or arm64 for 64-bit 
							     build)
export CROSS_COMPILE=arm-none-linux-gnueabi-                (compiler prefix)
export PATH=/path/to/your/arm/cross/compiler/binaries:$PATH
export LINUX_ZC702_DIR=/linux/sources/directory/for/zc702/  (optional, only for 
							     zc702 build)
export LINUX_VPA53_DIR=/linux/sources/directory/for/vpa53/  (optional, only for 
							     A53 build)
PATH=/path/to/your/arm/cross/compiler/binaries:$PATH
PATH=/path/to/your/64bit/arm/cross/compiler/binaries:$PATH

BUILD OF KERNEL MODULES
-----------------------

- cd to apex/build-* directory
- sh build.sh
- resulting *.ko file is to be copied in the target board and intalled to the OS 
  (insmod)



