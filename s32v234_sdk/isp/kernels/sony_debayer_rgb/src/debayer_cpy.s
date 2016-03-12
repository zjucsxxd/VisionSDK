.global debayer_cpy_start
debayer_cpy_start:
        done d0_cpy,i
d0_cpy:
        done d1_cpy,i
d1_cpy:

	mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)   

	mov gpr0,580 // gain r
	mov gpr1,356 // gain g
	mov gpr2,424 // gain b
	
loop0:
	mulh ina1,ina1,gpr0
	mulh ina0,ina0,gpr1
	mulh ina3,ina3,gpr2

output:
	dout ina3,eg,o // b
eg:
	dout ina0,er,o  // g
er:
	dout ina1,evenlodd,ixo  // r
evenlodd:
	done loop0,i
	
//	halt

.global debayer_cpy_end
debayer_cpy_end:
