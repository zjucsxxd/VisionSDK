#.org    0x00
# set shift_in/x to 1 pixels
# set shift_out to 1 pixels
# input to line 0
# in to LSB
# out from LSB
# out0 : copied input value
        
.global copy_replicate3x_start
copy_replicate3x_start:
        //mov confalu,(0 /*unsigned*/ | (1<<1) /*saturate*/ | (14<<4) /*shr*/)
        done copy_replicate3x_loop1,i    // load first pixel

copy_replicate3x_loop1:	dout ina0,copy_replicate3x_pixr,o
copy_replicate3x_pixr:	dout ina0,copy_replicate3x_pixb,o
copy_replicate3x_pixb:	dout ina0,copy_replicate3x_loop1,ixo

        //halt
.global copy_replicate3x_end
copy_replicate3x_end:
