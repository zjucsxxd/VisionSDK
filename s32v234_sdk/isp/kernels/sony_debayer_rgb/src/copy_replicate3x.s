#.org    0x00
.global copy_replcate3x_start
# set shift_in/x to 1 pixels
# set shift_out to 1 pixels
# input to line 0
# in to LSB
# out from LSB
# out0 : copied input value
        
copy_replcate3x_start:
        //mov confalu,(0 /*unsigned*/ | (1<<1) /*saturate*/ | (14<<4) /*shr*/)
        done copy_replcate3x_loop1,i    // load first pixel

copy_replcate3x_loop1:	dout ina0,copy_replcate3x_pixr,o
copy_replcate3x_pixr:	dout ina0,copy_replcate3x_pixb,o
copy_replcate3x_pixb:	dout ina0,copy_replcate3x_loop1,ixo

        //halt
.global copy_replcate3x_end
copy_replcate3x_end:
