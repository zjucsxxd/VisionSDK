.global copy_1to3_ipus_start

copy_1to3_ipus_start:
        done loop13,i    // load first pixel

.local loop13
loop13:
	dout ina0,loop13_1,o
.local loop13_1
loop13_1:
	dout ina0,loop13_2,o
.local loop13_2
loop13_2:
	dout ina0,loop13,ixo

        halt
.global copy_1to3_ipus_end
copy_1to3_ipus_end:
