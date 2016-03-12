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
  mov loopcnt,(1280/2)/2

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

evenl:  // first line rgrgrg
//  lsr ina,1
     mulh ina1,ina1,gpr0
     mulh ina0,ina0,gpr1
     mulh ina3,ina3,gpr2
eb:  dout ina3,eg,o // b
eg:  dout ina0,er,o // g
er:  dout ina1,evenlodd,ixo  // r
evenlodd:
  ldon evenl,i       # shift input by two

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
        // compute horizontal difference
diff0:   
        add gpr1,ina2,ina1
        add gpr1,gpr1,ina5
        lsl gpr1,gpr1,5
        dout gpr1,diff1,o
diff1:
        done diff2,io
diff2:
        done diff0,ixo

     halt

.global debayer_rgb_end	
debayer_rgb_end:
