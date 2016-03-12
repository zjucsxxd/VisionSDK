.global copy_1to1_ipus_start

copy_1to1_ipus_start:
        done loop11,i    // load first pixel

.local loop11
loop11:
	dout ina0,loop11,ixo

        halt
.global copy_1to1_ipus_end
copy_1to1_ipus_end:
