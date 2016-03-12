.org    0x0
.global sram_load_start
sram_load_start:

  done d1,i		// read in
d1:
  
loop:
//  nop			// throttle speed
//  nop			// throttle speed
  
  mov out0,ina0		// copy input#0 to output#0
  mov out1,ina1		// copy input#1 to output#1
  
  done loop,ixo		// read in/dec. x/write out/branch to 'loop'
  halt

.global sram_load_end
sram_load_end:
