Necessary prerequisites for building the apps
=============================================

Build Environment
-----------------

Linux OS
  The Linux OS build can be cross-compiled from either Linux or Windows OS. Under Windows OS, a Cygwin bash is recommended along with gcc/g++ compilers. This package is not part of Vision SDK. Cygwin has to be installed separately and added to system PATH.

INTEGRITY RTOS
  The INTEGRITY build can be cross-compiled using Greenhills MULTI IDE in both, Linux and Windows operating systems.


Export following environment variables for Linux build:
-------------------------------------------------------

User space build:
  PATH=/path/to/your/compiler/binaries:$PATH  			(Path to the arm cross compiler binaries)
  PATH=/path/to/your/64bit/compiler/binaries:$PATH	  	(Path to the 64-bit arm cross compiler binaries)
  PATH=/path/to/your/CHESS/compiler/binaries:$PATH      	(Path to the target APEX compiler binaries)
  
  
Kernel modules or OS kernel build:
  ARCH=arm  							(Target architecture - if 664-bit, then ARCH=arm64)
  CROSS_COMPILE=arm-none-linux-gnueabi-                		(Compiler prefix specification)
  PATH=/path/to/your/compiler/binaries:$PATH          		(Path to the compiler binaries)
  LINUX_ZC702_DIR=/linux/sources/directory/for/zc702/  		(optional - Path to the linux sources e.g. linux-xlnx direcrory)
  LINUX_VPA53_DIR=/linux/sources/directory/for/vpa53/   	(optional - Path to the linux sources e.g. linux-linaro-tracking direcrory)
  PATH=/path/to/your/compiler/binaries:$PATH  			(Path to the arm cross compiler binaries)
  PATH=/path/to/your/64bit/compiler/binaries:$PATH	  	(Path to the 64-bit arm cross compiler binaries)

Export following environment variables for INTEGRITY build:
-----------------------------------------------------------

INTEGRITY_ROOT_PATH="path/to/the/integrity/install"  
MULTI_ROOT_PATH="path/to/the/multi/tools"
PATH="path/to/the/multi/compiler":$PATH


Building the examples and the SDK
=================================

Go to the:
  - demos directory and follow the README.txt there to build demo applications (builds also necessary libs)
  - libs directory and follow the README.txt there to build only SDK libs
  - os directory and follow the README.txt there to build the SD card environment (OS kernels, u-boot etc.)
  
  
Contents of the package
=======================

-- build
     - Contains build toolchains for several compilation options
     
-- demos
     - A directory with several demo applications for SDK use
     - A good point to start with
     
-- docs
     - Documentation storage
     
-- kernels
     - Storage directory for APEX kernels used in apps
     
-- libs
     - SDK libraries (APEX Driver, GDI, OAL, ACF etc.)
     
-- ocv
     - Directory with build scripts for OpenCV (incl. pre-compiled binaries using CodeSourcery ARM Linux compiler v. 2013.05)
     
-- os
     - Environment build directory (OS, u-boot). Incl. pre-compiled SD card contents.
     
-- qt
     - Directory with build scripts for Qt (obsolete).

