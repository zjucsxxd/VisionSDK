# any IPUS engine
# in0  :  Y
# in1  :  U
# in1  :  V
# out0 :  Y, U, Y, V

.global yuv444toyuyv_start
yuv444toyuyv_start:
        mov confalu,(0 /*unsigned*/ | (1<<1) /*saturate*/ | (0<<4) /*shr*/)
        done yuv444toyuyv_d1,i
yuv444toyuyv_d1:
        mov maskv,0b011011011
        done yuv444toyuyv_loop,i

yuv444toyuyv_loop:
        asl w,ina,1
        sub zero,ina0,ina1    // check for a zero in the neighborhood
        bge yuv444toyuyv_take_second
        dout w1,yuv444toyuyv_take_first1,xo
yuv444toyuyv_take_first1:
        dout w4,yuv444toyuyv_take_first2,xo
yuv444toyuyv_take_first2:
        dout w0,yuv444toyuyv_take_first3,ixo
yuv444toyuyv_take_first3:
        dout w8,yuv444toyuyv_loop,ixo  // already moved by one


yuv444toyuyv_take_second:
        dout w1,yuv444toyuyv_take_second1,xo
yuv444toyuyv_take_second1:
        dout w3,yuv444toyuyv_take_second2,xo
yuv444toyuyv_take_second2:
        dout w0,yuv444toyuyv_take_second3,ixo
yuv444toyuyv_take_second3:
        dout w7,yuv444toyuyv_loop,ixo  // already moved by one

        //halt
.global yuv444toyuyv_end
yuv444toyuyv_end:
