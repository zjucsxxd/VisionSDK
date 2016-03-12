//	gpr0:	gain r			(417)
//	gpr1:	gain g			(256)
//	gpr2:	gain b			(305)
//	gpr3:	BOX_X   		(100)
//	gpr4:	BOX_Y			(100)
//	gpr5:	BOX_X+BOX_W		(540)
//	gpr6:	BOX_W			(440)
//	gpr7:	SCR_W-BOX_W-BOX_X	(100)
//	gpr8:	SCR_H-2*BOX_Y		(280)
//	gpr9:	XOR val r		(0xffff)
//	gpr10:	XOR val g		(0xffff)
//	gpr11:	XOR val b		(0xffff)

//.org    0x00
.global debayer_rgb_start
debayer_rgb_start:
	mov  gpr0,400 // red
	mov  gpr2,490 // blue

	done d0,i
d0:
	done d1,i
d1:
	mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)

	mov loopcnt,gpr3
evenl0:  // first line rgrgrg
	mulh ina1,ina1,gpr0
	//mulh ina0,ina0,gpr1
	mulh ina3,ina3,gpr2
eb0:
	dout ina3,eg0,o // b
eg0:
	dout ina0,er0,o // g
er0:
	dout ina1,evenlodd0,ixo  // r
evenlodd0:
	ldon evenl0,i       # shift input by two

	mov gpr13,ypos 
	sub gpr13,gpr13,gpr4
	bge chkzoom
nozoom:
	mov loopcnt,gpr5
	bal evenl2

chkzoom:
	sub gpr13,gpr13,gpr8
	bge nozoom
  
dozoom:
	mov loopcnt,gpr6

evenl1:  // first line rgrgrg
	mulh ina1,ina1,gpr0
	xor ina1,ina1,gpr9
	//mulh ina0,ina0,gpr1
	xor ina0,ina0,gpr10
	mulh ina3,ina3,gpr2
	xor ina3,ina3,gpr11
eb1:
	dout ina3,eg1,o // b
eg1:
	dout ina0,er1,o // g
er1:
	dout ina1,evenlodd1,ixo  // r
evenlodd1:
	ldon evenl1,i       # shift input by two

	mov loopcnt,gpr7
evenl2:  // first line rgrgrg
	mulh ina1,ina1,gpr0
	//mulh ina0,ina0,gpr1
	mulh ina3,ina3,gpr2
eb2:
	dout ina3,eg2,o // b
eg2:
	dout ina0,er2,o // g
er2:
	dout ina1,evenlodd2,ixo  // r
evenlodd2:
	ldon evenl2,i       # shift input by two

//	halt

.global debayer_rgb_end	
debayer_rgb_end:
