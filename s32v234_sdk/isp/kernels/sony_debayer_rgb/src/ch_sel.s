.global ch_sel_start
# set shift_in/x to 1 pixels
# set shift_out to 1 pixels
# input to line 0,1,2
# in  16 bit
# out 16 bit
# out0 : copied input value from on of the channels

ch_sel_start:
        //mov confalu,(0 /*unsigned*/ | (1<<1) /*saturate*/ | (14<<4) /*shr*/)
        done ch_sel_loop,i    // load first pixel

ch_sel_loop:
//	mov loopcnt,8
//delay:	nop
//	loop delay
	dout ina0,ch_sel_loop,ixo     // select channel 0
 	//dout ina3,loop,ixo    // select channel 1
	//dout ina6,loop,ixo    // select channel 2

        halt
.global ch_sel_end
ch_sel_end:
