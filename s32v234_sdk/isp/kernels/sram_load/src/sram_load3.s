//.org    0x0
.global sram_load3_start
sram_load3_start:

  done d3_1,i		// read in
d3_1:
  
loop3:
//  nop			// throttle speed
//  nop			// throttle speed
  
  mov out0,ina0		// copy input#0 to output#0
  mov out1,ina1		// copy input#1 to output#1
  done d3_2,o		// write out/branch to 'd3_2'

d3_2:  
  mov out0,ina0		// copy input#0 to output#0
  mov out1,ina1		// copy input#1 to output#1
  done d3_3,o		// write out/branch to 'd3_3'
  
d3_3:  
  mov out0,ina0		// copy input#0 to output#0
  mov out1,ina1		// copy input#1 to output#1
  
  done loop3,ixo	// read in/dec. x/write out/branch to 'loop3'
  halt

.global sram_load3_end
sram_load3_end:
