.org    0x0
.global s_kernel1_start
s_kernel1_start:

//   ina
// |2|1|0|
// |5|4|3| <== SDMA
// |8|7|6|

  mov confalu,(0 /*unsigned*/ | (0<<1) /*saturate*/ | (0<<4) /*shr*/)

//  mov gpr2,0x0 ### set gpr2 from outside ###

  mov gpr0,0xffff
  done loop,i		// shift data into matrix

loop:
//  add gpr0,0x3

//  mov gpr0,ina0
//  add gpr0,gpr0,gpr2

//  mov gpr1,ina3
//  add gpr1,gpr1,gpr2
  
//  mov out1,gpr1
//  add gpr2,0x1

  dout gpr0,loop,ixo	// move out0,gpr0 + "done loop,ixo"
  halt
.global s_kernel1_end
s_kernel1_end:
