//.org    0x0
.global mipi_ddr_start
mipi_ddr_start:

//   ina
// |2|1|0|
// |5|4|3| <== SDMA
// |8|7|6|

  done mipi_ddr_d0,i		// shift data into matrix
mipi_ddr_d0:

mipi_ddr_loop:
  mov  out1,ina0
  dout ina0,mipi_ddr_loop,ixo	// move out0,ina0 + "done loop,ixo"

//  halt

.global mipi_ddr_end
mipi_ddr_end:
