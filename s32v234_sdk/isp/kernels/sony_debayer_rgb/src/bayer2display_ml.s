// IPUS kernel
// 1 input line: line 0
// starting wantith R: even lines rgrgrg, odd lines gbgbgb
// no subsampling

.global bayer2display_ml_start
bayer2display_ml_start:
        done bayer2display_ml_d0,i
bayer2display_ml_d0:
//        done bayer2display_ml_d1,i
//bayer2display_ml_d1:
//        done bayer2display_ml_d2,i
//bayer2display_ml_d2:

	mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)   

	mov gpr0,256 // gain r
	mov gpr2,256 // gain b
	mov gpr3,1280  // active output line length
	
	//mov gpr0,400 // gain r
	//mov gpr2,490 // gain b
	//mov gpr1,20  // for loop test
	
        //lsl zero,ypos,15
        //bne bayer2display_ml_odd_b0:

// *********************************
bayer2display_ml_even_line:
	mov loopcnt,gpr3
bayer2display_ml_even_b0:
	//mov loopcnt,gpr1
	dout zero,bayer2display_ml_even_g0,o
bayer2display_ml_even_g0:
	dout zero,bayer2display_ml_even_r0,o
bayer2display_ml_even_r0:
	mulh out0,ina0,gpr0  // R
	ldon bayer2display_ml_even_b1,ixo
bayer2display_ml_even_b1:
	dout zero,bayer2display_ml_even_g1,o
bayer2display_ml_even_g1:
	dout ina0,bayer2display_ml_even_r1,o
bayer2display_ml_even_r1:
	//loop bayer2display_ml_even_r1
	ldot zero,bayer2display_ml_even_b0,ixo

	mov loopcnt,8   // skip pixels to start of next line
bayer2display_ml_even_trailer:
	ldon bayer2display_ml_even_trailer,i

// *********************************
bayer2display_ml_odd_line:
	mov loopcnt,gpr3

bayer2display_ml_odd_b0:
	//mov loopcnt,gpr1
	dout zero,bayer2display_ml_odd_g0,o
bayer2display_ml_odd_g0:
	dout ina0,bayer2display_ml_odd_r0,o
bayer2display_ml_odd_r0:
	dout zero,bayer2display_ml_odd_b1,ixo
bayer2display_ml_odd_b1:
	mulh out0,ina0,gpr2  // B
	ldon bayer2display_ml_odd_g1,o
bayer2display_ml_odd_g1:
	dout zero,bayer2display_ml_odd_r1,o
bayer2display_ml_odd_r1:
	//loop bayer2display_ml_odd_r1
	ldot zero,bayer2display_ml_odd_b0,ixo

	mov loopcnt,8   // skip pixels to start of next line
bayer2display_ml_odd_trailer:
	ldon bayer2display_ml_odd_trailer,i
	bal bayer2display_ml_even_line

.global bayer2display_ml_end
bayer2display_ml_end:
