// IPUS kernel
// INPUT:
// INA0: starting with R: even lines rgrgrg, odd lines gbgbgb
// INA1: starting with G: even lines gbgbgb, odd lines rgrgrg
// OUTPUT:
// reducing by top/bottom lines & left/right column
// OUT0: R
// OUT1: G
// OUT2: B
// no subsampling
// REGISTERS:
// SET BY SEQUENCER
//GPR0: channel gain R
//GPR1: channel gain G (not used)
//GPR2: channel gain B
// SET BY KERNEL

.global debayer_rgb_simple_planar_start
debayer_rgb_simple_planar_start:
        done debayer_rgb_simple_planar_d0,i
debayer_rgb_simple_planar_d0:
//        done debayer_rgb_simple_planar_d1,i
//debayer_rgb_simple_planar_d1:
        done debayer_rgb_simple_planar_d2,i
debayer_rgb_simple_planar_d2:

	mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)   
        mov confhist,((10 <<8) /* shift down (to 64 bins)*/ | 64 /* offset */)

	//mov gpr1,256 // gain g
	//mov gpr0,400 // gain r
	//mov gpr2,490 // gain b

        lsl zero,ypos,15
        bne debayer_rgb_simple_planar_loop_odd:

// *********************************
debayer_rgb_simple_planar_loop_even:
	mulh ina3,ina3,gpr2  // B              X R G              R G X
	//mulh ina0,ina0,gpr1  // G   pixel 0  X X B     pixel 1  X B X
	mulh ina1,ina1,gpr0  // R


        mov out2,ina3        //b0
        mov hbininch,ina0    //g0 to histogram
	mov out1,ina0        //g0
	dout ina1,debayer_rgb_simple_planar_e1,ixo        // r0

debayer_rgb_simple_planar_e1:
	dout ina2,debayer_rgb_simple_planar_loop_even,ixo  // r1



// *********************************
debayer_rgb_simple_planar_loop_odd:
	mulh ina4,ina4,gpr0  // R              X G B              G B X
	//mulh ina1,ina1,gpr1  // G   pixel 1  X R X     pixel 2  R X X
	mulh ina0,ina0,gpr2  // B


	mov out2,ina0        // b0
	mov out1,ina1        // g0
	dout ina4,debayer_rgb_simple_planar_o1,ixo        // r0
debayer_rgb_simple_planar_o1:
	dout ina5,debayer_rgb_simple_planar_loop_odd,ixo  // r1
	
//	halt

.global debayer_rgb_simple_planar_end
debayer_rgb_simple_planar_end:
