//   ina
// |2|1|0|
// |5|4|3| <== SDMA
// |8|7|6| 

.global chroma_key_start
chroma_key_start:
	mov gpr0,0x4000		// r level
	mov gpr1,0x8000		// g level

	done chroma_key_d0,i
chroma_key_d0:
	done chroma_key_d1,i
chroma_key_d1:
	done chroma_key_d2,i
chroma_key_d2:

	// *** expecting BGR ***
	sub zero,ina2,gpr0		// check r
	bcs chroma_key_output		// strong red -> keep color
	sub zero,ina1,gpr1		// check g
	bcs chroma_key_output		// strong green -> keep color
//	mov ina0,0xffff			// set to max blue
	mov ina1,0x0			// set g to 0
	mov ina2,0x0			// set r to 0

chroma_key_output:
	dout ina2,chroma_key_g,o	// r
chroma_key_g:
	dout ina1,chroma_key_b,o	// g
chroma_key_b:
	dout ina0,chroma_key_d0,ixo	// b, next

//	halt

.global chroma_key_end	
chroma_key_end:
