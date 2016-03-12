##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2016, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    Build instructions for FFMPEG library
#
#  AUTHOR
#    Tomas Babinec
#
#  DATE
#    2014-03-17
#
#  LANGUAGE
#    human readable text
#
##############################################################################


==========================================================================
| Please replace the SDK_ROOT text by the path to your s32v234_sdk folder |
==========================================================================

 FFMPEG build instructions for Integrity OS
===========================================

  1) Extract ffmpeg source port for Integrity
  -------------------------------------------
    - Switch into SDK_ROOT/ffmpeg directory.
    - Extract the ffmpeg-2.2.1_integrity.tar.gz to a directory of your choice,
      e.g. SDK_ROOT/../ffmpeg-2.2.1_integrity. To achieve this run:
      tar -zxvf ffmpeg-2.2.1_integrity.tar.gz SDK_ROOT/../ffmpeg-2.2.1_integrity

  2) Check Environment variables
  ------------------------------
    - Export necessary environment variables
	 
      INTEGRITY_ROOT_PATH="path/to/your/integrity/installation"
      MULTI_ROOT_PATH="path/to/your/multi/installation"
      MULTI_COMPILER_ROOT_PATH="path/to/your/multi/compiler/folder"
      
  3) Set up top level Multi project:
  ----------------------------------
    - In Multi project manager open the ffmpeg_integrity.gpj project located in
      SDK_ROOT/ffmpeg/build-v234ce-ghs-integrity directory.
    - To the top level project add the packages.gpj project file located in the
      folder you've chosen in step 1.
     
  4) Build the ffmpeg libraries
  -----------------------------
    - Build the top level project.
   
  5) Install headers and library binaries
  ---------------------------------------
    - Switch to SDK_ROOT/ffmpeg/build-zc702-ghs-multi-integrity-d directory.
    - Run install.sh script with one argument specifying path to the directory
      you've chosen in step one.
      e.g.: sh install.sh SDK_ROOT/SDK_ROOT/../ffmpeg-2.2.1_integrity.
    - Now the headers and libraries that might be required for applications to
      be build are located in SDK_ROOT/ffmpeg/integrity-arm directory.
      
 FFMPEG build instructions for Linux
====================================

  1) Download ffmpeg version 2.8.5
  ----------------------------------
    - download archive from https://www.ffmpeg.org/releases/ffmpeg-2.8.5.tar.bz2
    - extract its contents to working directory (let's say ~/)

  2) Set following system variables:
  ----------------------------------
    - export CROSS_COMPILE=aarch64-linux-gnu-
      - Compiler prefix specification
    - export PATH=/path/to/your/arm/cross/compiler/binaries:$PATH
      - Path to the compiler binaries
    - export PATH=/path/to/your/arm/cross/compiler/binaries:$PATH
      - Path to the compiler binaries
     
  3) Build ffmpeg libraries
  -------------------------
    - cd to SDK_ROOT/ffmpeg/build-v234ce-gnu-linux
    - run:
      sh build.sh ~/ffmpeg-2.8.5   
      (usage: first parameter specifies ffmpeg source directory)
      
Version numbering note:
-----------------------
By default after build and installation of the ffmpeg libraries the build.sh 
script automaticatly removes the version number from the library hardlink 
filenames and deletes any symbolic links to it. This way the built libraries can 
be safely transferred to Windows and used at build time in cygwin environment. 

At runtime the OS looks for the libraries with version number appended to its 
file name. Therefore to execute applications linked to the ffmpeg libraries, 
library files with version strings appended have to be supplied. They can be 
found prepared in SDK_ROOT/os/sdcard_build/lib folder.

To find out dependancies of the elf file, the 
"readelf -d /path/to/the/elf/binary" command can be used.

To allow the libraries to be located when application is executed the 
LD_LIBRARY_PATH has to be set to their location by executing command:
export LD_LIBRARY_PATH=/path/to/runtime/libraries