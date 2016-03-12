// kernel to convert Bayer pattern to gray level with 1:2 resolution
// reading two input lines with R, GR and next line GB, B and
// producing a single output value for the 2x2 input window
// Line INA0, even line  16bpp or 8bpp MSB aligned (buffertype = 0 or 1)
// Line INA1, odd line   16bpp or 8bpp MSB aligned (buffertype = 0 or 1)
// Line Out0, combined line       8bpp MSB aligned (buffertype = 1)
// expect that per output line the input lines progress by two lines
// additional hints:
// needs to cut lines from the top of the image (optical black) and
// frame from right (e.g., down from 1296 to 1280)



//.org    0x00
.global debayer_rgb_start
debayer_rgb_start:

  done d0,i
d0:
  done d1,i
d1:
  mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)
//  mov confaddt,(0/*w*/) | (0/*apply mask*/<<2) | (0 /* unsigned*/<<3) | (0/* shift right*/ <<5) | (64 /* factor*/ <<9)
  and gpr0,1
  //mov maskv,0b000011011
  mov gpr0,417 // gain r
  mov gpr1,256 // gain g
  mov gpr2,305 // gain b

  mov loopcnt,200
evenl0:  // first line rgrgrg
     mulh ina1,ina1,gpr0
     mulh ina0,ina0,gpr1
     mulh ina3,ina3,gpr2
eb0:  dout ina3,eg0,o // b
eg0:  dout ina0,er0,o // g
er0:  dout ina1,evenlodd0,ixo  // r
evenlodd0:
  ldon evenl0,i       # shift input by two

  mov loopcnt,100
evenl1:  // first line rgrgrg
     mulh ina1,ina1,gpr0
     mulh ina0,ina0,gpr1
     mulh ina3,ina3,gpr2
//     add gpr1,ina1,ina0
//     lsr gpr1,gpr1,1
//     add gpr1,gpr1,ina3
//     lsr gpr1,gpr1,1
bw0:  dout ina3,bw1,o // b
bw1:  dout ina0,bw2,o // g
bw2:  dout ina1,bw3,o // r
bw3:  dout ina3,bw4,o // b
bw4:  dout ina0,bw5,o // g
bw5:  dout ina1,evenlodd1,ixo  // r
evenlodd1:
  ldon evenl1,i       # shift input by two

  mov loopcnt,340
evenl2:  // first line rgrgrg
     mulh ina1,ina1,gpr0
     mulh ina0,ina0,gpr1
     mulh ina3,ina3,gpr2
eb2:  dout ina3,eg2,o // b
eg2:  dout ina0,er2,o // g
er2:  dout ina1,evenlodd2,ixo  // r
evenlodd2:
  ldon evenl2,i       # shift input by two

/*
  mov gpr0,ypos 
  sub gpr0,100
  bne raw
  done raw,i

raw:
r0:  dout ina2,r1,o
r1:  dout ina1,r2,o
r2:  dout ina0,r3,io
r3:
     done raw,ix
*/
/*
diff0:   
        add gpr1,ina2,ina1
        add gpr1,gpr1,ina5
        lsl gpr1,gpr1,5
        dout gpr1,diff1,o
diff1:
        done diff2,io
diff2:
        done diff0,ixo
*/
     halt

.global debayer_rgb_end	
debayer_rgb_end:
