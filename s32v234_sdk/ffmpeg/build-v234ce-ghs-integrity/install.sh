#!/bin/bash


#check argument is present
if [ $# -ne 1 ]
then echo "Please, specify the path to ffmpeg Integrity port sources as script argument!"
exit 1
fi

# append internal folder structure
FFMPEG_SRC=$1"/ffmpeg/ffmpeg-2.2.1"

#check the directory exists
if [ ! -d "$FFMPEG_SRC" ]
then echo "The specified directory does not exist."
exit 1
fi

# path to installation directory
INSTALL_DIR=../integrity-arm64

#create $INSTALL_DIR"/include/lib"$LIB_NAME directory for header files
mkdir -p $INSTALL_DIR"/include"

#create $INSTALL_DIR/lib directory for library files
mkdir -p $INSTALL_DIR"/lib"

# path to the directory where library binaries are located after built
BUILD_DIR="./"

#
# start the installation process
#

LIB_NAME=avcodec

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="avcodec.h
	 avfft.h 
	 dxva2.h 
	 old_codec_ids.h 
	 vaapi.h 
	 vda.h 
	 vdpau.h 
	 version.h 
	 xvmc.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=avdevice

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="avdevice.h
	 version.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=avfilter

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="asrc_abuffer.h
         avcodec.h
         avfilter.h
         avfiltergraph.h
         buffersink.h
         buffersrc.h
         version.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=avformat

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="avformat.h
         avio.h
         version.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=avutil

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="adler32.h
          aes.h
          attributes.h
          audio_fifo.h
          audioconvert.h
          avassert.h
          avconfig.h
          avstring.h
          avutil.h
          base64.h
          blowfish.h
          bprint.h
          bswap.h
          buffer.h
          channel_layout.h
          common.h
          cpu.h
          crc.h
          downmix_info.h
          error.h
          eval.h
          fifo.h
          file.h
          frame.h
          hmac.h
          imgutils.h
          intfloat.h
          intfloat_readwrite.h
          intreadwrite.h
          lfg.h
          log.h
          lzo.h
          opencl.h
          macros.h
          mathematics.h
          md5.h
          mem.h
          murmur3.h
          dict.h
          old_pix_fmts.h
          opt.h
          parseutils.h
          pixdesc.h
          pixfmt.h
          random_seed.h
          rational.h
          ripemd.h
          samplefmt.h
          sha.h
          sha512.h
          stereo3d.h
          time.h
          timecode.h
          timestamp.h
          version.h
          xtea.h"

#  ffversion.h not available

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=swresample

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib

HEADERS="swresample.h
         version.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done
          
LIB_NAME=swscale

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib	

HEADERS="swscale.h
         version.h"

mkdir -p $INSTALL_DIR"/include/lib"$LIB_NAME

for file in $HEADERS
do
	cp $FFMPEG_SRC"/lib"$LIB_NAME/$file $INSTALL_DIR"/include/lib"$LIB_NAME
done

LIB_NAME=z

cp $BUILD_DIR"/lib"$LIB_NAME".a" $INSTALL_DIR/lib
cp $BUILD_DIR"/lib"$LIB_NAME".dba" $INSTALL_DIR/lib




