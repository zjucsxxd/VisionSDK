#/bin/tcsh -f
#convert yuv422.pgm -depth 8 -crop 1280x800+0+0 yuv422.h
echo convert ../pgm/L_00.bin.pgm -crop 1296x808+0+14 -depth 16 in.pgm
convert ../pgm/L_00.bin.pgm -crop 1296x808+0+14 -depth 16 in.pgm
convert -endian lsb in.pgm L00.h
convert ../pgm/S1_00.bin.pgm -crop 1296x808+0+14 -depth 16 in.pgm
convert -endian lsb in.pgm S00.h
rm -f in.pgm
echo "edit *.h according to template.h"

