#/bin/tcsh -f
#convert yuv422.pgm -depth 8 -crop 1280x800+0+0 yuv422.h
convert -endian lsb yuv422.pgm -crop 2560x800+0+0 gray:yuv422.raw
convert -size 2560x800 gray:yuv422.raw yuv422.h
#convert S00.pgm S00.h
rm -f yuv422.raw
echo "edit *.h according to template.h"

