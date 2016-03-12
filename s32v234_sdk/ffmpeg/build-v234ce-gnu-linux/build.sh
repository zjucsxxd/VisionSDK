##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2014, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    Configures, builds and installs ffmpeg libraries from source files.
#
#  AUTHOR
#    Tomas Babinec
#
#  DATE
#    2014-03-17
#
#  LANGUAGE
#    bash script
#
##############################################################################

#!/bin/sh

export ARCH=aarch64
export CROSS_COMPILE=aarch64-linux-gnu-

if [ $# -lt 1 ]
  then
  echo ""
  echo "  Error: you need to specify ffmpeg sources path as first parameter."
  echo ""
  exit;
fi

# remember current path
ORIGIN=$PWD

# go to ffmpeg source

echo ""
echo "Switching to FFMPEG source directory"
echo ""

cd $1

echo ""
echo "Configuring..."
echo ""

######################
# Source configuration
#
# - Update ffmpeg installation path in --prefix option (see below). 

./configure \
  --enable-cross-compile 						\
  --enable-shared 							\
  --disable-static 							\
  --cross-prefix=${CROSS_COMPILE} 					\
  --arch=aarch64 							\
  --target-os=linux 							\
  --prefix=${ORIGIN}/../linux-arm64
  
#################  
# Build & Install

echo ""
echo "Building FFMPEG libraries"
echo ""

#make

echo ""
echo "Installing FFMPEG libraries" 
echo ""
make install

# change library filenames to hardlinks with no version number and remove any symbolic links
${ORIGIN}/sym2hard.sh ${ORIGIN}/../linux-arm64/lib d

# return back
echo ""
echo "Returning back"
echo ""
cd $ORIGIN
