##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2014, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    Configures, builds and installs fftw libraries from source files.
#
#  AUTHOR
#    Roman Kubica
#
#  DATE
#    2015-10-07
#
#  LANGUAGE
#    bash script
#
##############################################################################

#!/bin/sh

# remember current path
ORIGIN=$PWD
SDK_ROOT=$PWD/../..

cp $ORIGIN/patch_files/fftw-wisdom.c $SDK_ROOT/../fftw_src/tools
cp $ORIGIN/patch_files/bench-main.c $SDK_ROOT/../fftw_src/libbench2
cp $ORIGIN/patch_files/timer.c $SDK_ROOT/../fftw_src/libbench2
cp $ORIGIN/patch_files/simd-neon.h $SDK_ROOT/../fftw_src/simd-support
cp $ORIGIN/patch_files/configure $SDK_ROOT/../fftw_src

cd $SDK_ROOT/../fftw_src

echo ""
echo "Configure..."
echo ""

ARM_INCS="-I${SDK_ROOT}/libs/arm/utils/oal/user/include \
-I${SDK_ROOT}/libs/arm/io/uartlinflex_io/include \
-I${SDK_ROOT}/libs/arm/apex/apex/user/include \
-I${SDK_ROOT}/libs/arm/startup/v234ce_standalone/include \
-I${SDK_ROOT}/libs/arm/io/i2c/include"
 
ARM_LIBS_PATH="-L${SDK_ROOT}/libs/arm/apex/apex/user/build-v234ce-gnu-sa-d \
 -L${SDK_ROOT}/libs/arm/utils/oal/user/build-v234ce-gnu-sa-d \
 -L${SDK_ROOT}/libs/arm/io/uartlinflex_io/build-v234ce-gnu-sa-d \
 -L${SDK_ROOT}/libs/arm/startup/v234ce_standalone/build-v234ce-gnu-sa-d \
 -L${SDK_ROOT}/libs/arm/io/i2c/build-v234ce-gnu-sa-d" 
 
LIBS=" -lv234ce \
-llinflex \
-lapex2drv \
-loal \
-lc \
-lg \
-lgcc \
-lstdc++ \
-li2c \
-lrdimon"

PREFIX=" --prefix=${SDK_ROOT}/fftw/standalone-arm64 --host=aarch64-none-elf --enable-single --enable-neon" 

PREFIX2="CC=aarch64-none-elf-gcc -mcpu=cortex-a53 -nostdlib -fno-builtin -fno-exceptions" 

./configure CPPFLAGS="${ARM_INCS}" LDFLAGS="${ARM_LIBS_PATH}" ${PREFIX} "${PREFIX2}" LIBS="${LIBS}"

#################
# Build & Install

#make

echo ""
echo "Building FFTW library"
echo ""

make

#install 

echo ""
echo "Installing FFTW library"
echo ""

make install

cd $ORIGIN

