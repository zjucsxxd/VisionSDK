.global debayer_rb_start
debayer_rb_start:
        mov  confalu,(0 /* unsigned*/ | (1 << 1) /* saturate*/ | (16<<4) /* shr =0*/ ) 
        //mov confsgn,1            # signed
        //mov confsat,0            # saturation off
        mov confaddt,(0/*w*/) | (0/*apply mask*/<<2) | (0 /* unsigned*/<<3) | (1 /* keep higher*/<<4) | (4/* shift right -6*/ <<5) | (64 /* factor*/ <<9)
        //mov confthres,0          # kill values < 0
        //mov maskv,0x1ff
        //mov 1                  # to W
        //mov maskv,0x145        # 101 000 101
        //mov 2                  # to W
        //swp
        done d0,i
d0:
        done d1,i
d1:
        and ypos,1               # check for even lines (B first)
        done d2,i
d2:

        beq bluefirst
// 7 instructions

//loop:
//        dout ina4,loop,ixo

readfirst:      
loop10: // R2,2 first
        mov maskv,0x1ff
        lsr w,ina,2

        //mov maskv,0x028          # 000101000
        add out1,w3,w5           # B2,3 horizontal sum

        //mov maskv,0x082          # 010000010
        add out0,w1,w7           # R2,3 vertical sum

        done loop11,ixo
loop11:  // B1,1 First
        mov maskv,0x145          # 101000101
        lsr w,ina,3

        lsr out1,ina4,1          # B3,3
        dout sum,loop10,ixo      # R3,3

  //9 instruction

bluefirst:
loop00:  // B1,1 First
        mov maskv,0x145          # 101000101
        lsr w,ina,3
        lsr out0,ina4,1          # R2,2
        mov out1,sum             # B2,2

        done loop01,ixo
loop01:
        mov maskv,0x1ff
        lsr w,ina,2

        //mov maskv,0x028          # 000101000
        add out0,w3,w5             # R3,2 horizobtal sum

        //mov maskv,0x092          # 010010010
        add out1,w1,w7             # B3,2 vertical sum

        done loop00,ixo
//10 instructions
  
        //halt
.global debayer_rb_end
debayer_rb_end:
