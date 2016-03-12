# IPUS 
//gpr0		R black  offset: default 0xf08 
//gpr1		Gr black offset: default 0xf08
//gpr2		Gb black offset: default 0xf08
//gpr3		B black  offset: default 0xf08
//
//gain factors
//gpr4		R  gain default: 400 (Soyn cam), 590 (Sony EVB), 
//gpr5		Gr gain	default: 256  
//gpr6		Gb gain	default: 256  
//gpr7		B  gain	default: 490 (Soyn cam), 402 (Sony EVB), 
//
//knee point from 0 - 256
//gpr8		factor for line 0 (short exposure)
//gpr9		factor for line 1 (long exposure) computed from gpr8

.global exposure_tonehdr_start
exposure_tonehdr_start:

        mov  confalu,(0 /* unsigned*/ | (1 << 1) /* saturate*/ | (8<<4) /* shr =8*/ ) 
        //mov confshr,8
	mov gpr9,256
	sub gpr9,gpr9,gpr8

  
        done exposure_tonehdr_d1_2,i
exposure_tonehdr_d1_2:
        //mov confsgn,0
        //mov confsat,1
        mov lock,0
// configure HIST engine
        lsl zero,ypos,15
        bne exposure_tonehdr_oddline1


  
exposure_tonehdr_evenline1:
        mov confhist,((10 <<8) | 64)
        mov gpr12,10             # ina(15:0)  >> 10 for histogram  hbinl
        mov gpr13,0
exposure_tonehdr_loop0_0:  //R
        sub ina0,ina0,gpr0       # black correction
        mulh gpr10,ina0,gpr4     # channel gain
        sub ina3,ina3,gpr0       # black correction
        mulh gpr11,ina3,gpr4     # channel gain

        mulh sacc0,gpr10,gpr8    # hdr knee point
        mulh acc0,gpr11,gpr9     # hdr kneeq

        lsr hbinincl,ina0,gpr12  # long exposure_tonehdr histogram (0-63)
        dout acc0,exposure_tonehdr_loop0_1,ixo

exposure_tonehdr_loop0_1:  //GR
        sub ina0,ina0,gpr1       # black correction
        mulh gpr10,ina0,gpr5     # channel gain
        sub ina3,ina3,gpr1       # black correction
        mulh gpr11,ina3,gpr5     # channel gain

        mulh sacc0,gpr10,gpr8    # hdr knee point
        mulh acc0,gpr11,gpr9     # hdr kneeq

        mov hbininch,ina0        # long exposure_tonehdr histogram
        dout acc0,exposure_tonehdr_loop0_0,ixo

exposure_tonehdr_oddline1:
        mov confhist,((10 <<8) | 192)
        mov gpr12,10             # ina(15:0)  >> 10 for histogram  hbinincl (64 bins per component)
        mov gpr13,128            # offset bin for odd lines

exposure_tonehdr_loop1_0:  // GB
        sub ina0,ina0,gpr2       # black correction
        mulh gpr10,ina0,gpr6     # channel gain
        sub ina3,ina3,gpr2       # black correction
        mulh gpr11,ina3,gpr6     # channel gain

        mulh sacc0,gpr10,gpr8    # hdr knee point
        mulh acc0,gpr11,gpr9     # hdr kneeq

        lsr ina0,ina0,gpr12      # scale for 64 bins
        add hbinincl,ina0,gpr13  # long exposure_tonehdr histogram
        dout acc0,exposure_tonehdr_loop1_1,ixo

exposure_tonehdr_loop1_1: //B
        sub ina0,ina0,gpr3       # black correction
        mulh gpr10,ina0,gpr7     # channel gain
        sub ina3,ina3,gpr3       # black correction
        mulh gpr11,ina3,gpr7     # channel gain

        mulh sacc0,gpr10,gpr8    # hdr knee point
        mulh acc0,gpr11,gpr9     # hdr kneeq

        mov hbininch,ina0        # long exposure_tonehdr histogram
        dout acc0,exposure_tonehdr_loop1_0,ixo
  
//        halt
.global exposure_tonehdr_end
exposure_tonehdr_end:
