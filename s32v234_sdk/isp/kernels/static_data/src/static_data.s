.global static_data_start
static_data_start:

//   ina
// |2|1|0|
// |5|4|3| <== SDMA
// |8|7|6|

  done static_data_loop,i		// shift data into matrix

static_data_loop:
//  dout ina0,static_data_d0,o
//static_data_d0:
//  dout ina0,static_data_d1,o
//static_data_d1:
  dout ina0,static_data_loop,ixo	// move out0,ina0 + "done loop,ixo"

//  halt

.global static_data_end
static_data_end:
