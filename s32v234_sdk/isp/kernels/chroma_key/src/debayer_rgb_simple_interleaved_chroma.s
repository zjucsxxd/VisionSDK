// IPUS kernel
// 2 input line: line 0, line 1
// starting with R
// no subsampling
// reducing by top/bottom lines & left/right column

.global debayer_rgb_simple_interleaved_chroma_start
debayer_rgb_simple_interleaved_chroma_start:
        done debayer_rgb_simple_interleaved_chroma_d0,i
debayer_rgb_simple_interleaved_chroma_d0:
        done debayer_rgb_simple_interleaved_chroma_d2,i
debayer_rgb_simple_interleaved_chroma_d2:

	//mov confalu, (0 /* unsigned*/ | (1<<1) /*saturate*/ | (8<< 4) /* SHR: 16.0*/)   
	// gpr1 : gain g
        // gpr0 : gain r
	// gpr2 : gain b

        lsl zero,ypos,15
        bne debayer_rgb_simple_interleaved_chroma_loop_odd:

// *********************************
debayer_rgb_simple_interleaved_chroma_loop_even:

	dout ina3,debayer_rgb_simple_interleaved_chroma_eg0,o          // b0
debayer_rgb_simple_interleaved_chroma_eg0:
	dout ina0,debayer_rgb_simple_interleaved_chroma_er0,o          // g0
debayer_rgb_simple_interleaved_chroma_er0:
	dout ina1,debayer_rgb_simple_interleaved_chroma_eb1,ixo        // r0
debayer_rgb_simple_interleaved_chroma_eb1:

        dout ina4,debayer_rgb_simple_interleaved_chroma_eg1,o          // b1
debayer_rgb_simple_interleaved_chroma_eg1:
	dout ina1,debayer_rgb_simple_interleaved_chroma_er1,o          // g1
debayer_rgb_simple_interleaved_chroma_er1:
	dout ina2,debayer_rgb_simple_interleaved_chroma_loop_even,ixo  // r1

// *********************************
debayer_rgb_simple_interleaved_chroma_loop_odd:

	dout ina0,debayer_rgb_simple_interleaved_chroma_og0,o          // b0
debayer_rgb_simple_interleaved_chroma_og0:
	dout ina1,debayer_rgb_simple_interleaved_chroma_or0,o          // g0
debayer_rgb_simple_interleaved_chroma_or0:
	dout ina4,debayer_rgb_simple_interleaved_chroma_ob1,ixo        // r0
debayer_rgb_simple_interleaved_chroma_ob1:

        dout ina1,debayer_rgb_simple_interleaved_chroma_og1,o          // b1
debayer_rgb_simple_interleaved_chroma_og1:
	dout ina2,debayer_rgb_simple_interleaved_chroma_or1,o          // g1
debayer_rgb_simple_interleaved_chroma_or1:
	dout ina5,debayer_rgb_simple_interleaved_chroma_loop_odd,ixo   // r1
	
//	halt

.global debayer_rgb_simple_interleaved_chroma_end
debayer_rgb_simple_interleaved_chroma_end:
