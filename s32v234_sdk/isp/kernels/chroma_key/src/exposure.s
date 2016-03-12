.global exposure_start
exposure_start:
        //mov gpr0,0xf08    // R black offset
        //mov gpr1,0xf08    // Gr black offset
        //mov gpr2,0xf08    // Gb black offset
        //mov gpr3,0xf08    // B black offset
        //
        ////mov gpr4,596      // R gain
        //mov gpr4,490      // R gain
        ////mov gpr4,256      // R gain
        //mov gpr5,256      // Gr gain
        //mov gpr6,256      // Gb gain
        //mov gpr7,402      // B gain
        ////mov gpr7,256      // B gain
        ////mov gpr7,490      // B gain

        mov  confalu,(0 /* unsigned*/ | (1 << 1) /* saturate*/ | (8<<4) /* shr =8*/ ) 
        //mov confshr,8

  
        done exposure_d1_2,i
exposure_d1_2:
        //mov confsgn,0
        //mov confsat,1
        mov lock,0
// configure HIST engine
        lsl zero,ypos,15
        beq exposure_evenline1


exposure_oddline1:
        mov confhist,((10 <<8) | 192)
        mov gpr10,10             # ina(15:0)  >> 10 for histogram  hbinincl (64 bins per component)
        mov gpr11,128            # offset bin for odd lines
exposure_loop1_0:
        sub ina0,ina0,gpr2       # black correction
        mulh out0,ina0,gpr6      # channel gain
        sub ina3,ina3,gpr2       # black correction
        mulh out1,ina3,gpr6      # channel gain
        lsr ina3,ina3,gpr10      # scale for 64 bins
        add hbinincl,ina3,gpr11  # long exposure histogram
        done exposure_loop1_1,ixo

exposure_loop1_1: //B
        sub ina0,ina0,gpr3       # black correction
        mulh out0,ina0,gpr7      # channel gain
        sub ina3,ina3,gpr3       # black correction
        mulh out1,ina3,gpr7      # channel gain
        mov hbininch,ina3        # long exposure histogram
        done exposure_loop1_0,ixo
  
  
exposure_evenline1:
        mov confhist,((10 <<8) | 64)
        mov gpr10,10             # ina(15:0)  >> 10 for histogram  hbinl
        mov gpr11,0
exposure_loop0_0:  //R
        sub ina0,ina0,gpr0       # black correction
        mulh out0,ina0,gpr4      # channel gain
        sub ina3,ina3,gpr0       # black correction
        mulh out1,ina3,gpr4      # channel gain
        lsr hbinincl,ina3,gpr10  # long exposure histogram (0-63)
        done exposure_loop0_1,ixo

exposure_loop0_1:
        sub ina0,ina0,gpr1       # black correction
        mulh out0,ina0,gpr5      # channel gain
        sub ina3,ina3,gpr1       # black correction
        mulh out1,ina3,gpr5      # channel gain
        mov hbininch,ina3        # long exposure histogram
        done exposure_loop0_0,ixo

//        halt
.global exposure_end
exposure_end:
