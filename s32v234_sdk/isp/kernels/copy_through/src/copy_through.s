.org    0x0
.global s_copy_through_start
s_copy_through_start:

//   ina
// |2|1|0|
// |5|4|3| <== SDMA
// |8|7|6|

  mov confalu,(0 /*unsigned*/ | (0<<1) /*saturate*/ | (0<<4) /*shr*/)

  done d0,i		// shift data into matrix
d0:

loop:
  dout ina0,loop,ixo	// move out0,gpr0 + "done loop,ixo"

//  halt

.global s_copy_through_end
s_copy_through_end:
