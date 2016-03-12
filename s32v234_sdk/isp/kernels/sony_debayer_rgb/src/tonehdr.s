.org    0x00
.global tonehdr_start
tonehdr_start:
        //mov  gpr4,0
        mov  confalu,(0 /* unsigned*/ | (1 << 1) /* saturate*/ | (7<<4) /* shr =8*/ ) 
        mov maskv,0xf
        done d0,i
d0:
//        mov lock,0
//short exposure line0/vh0
//long  exposure line1/vh5
//long  exposure cross point line2/vh10:  global = const

  
loop0:
        //min ina3,ina3,gpr0       # clipp long input to maximum value
        //lsr ina3,ina3,gpr1       # mov long exposure down
        //lsr vh10,vh10,gpr4
        mulh vh5,vh5,vh10        # multiply long exposure with scaling value
        //sub vh0,vh0,gpr2         # mov short exposure down
        mulh vh0,vh0,gpr3        # scale short exposure
        add vout0,vh0,vh5        # add short exposure
        done loop0,ixo

//        halt
.global tonehdr_end
tonehdr_end:
