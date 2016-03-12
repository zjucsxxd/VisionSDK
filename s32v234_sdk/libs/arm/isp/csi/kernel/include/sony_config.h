/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2015 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file     sony_config.h
* \brief    definition of sony camera registers configuration
* \author   Tomas Babinec
* \version  0.1
* \date     31.3.2015
* \note
****************************************************************************/

#ifndef SONY_CONFIG_H
#define SONY_CONFIG_H

#define FPS 30

//#define ROI_1288x808
#define ROI_1288x728
//#define SIZE_720P
// also patch ../../../io/frame_io/src/frame_input_isp.c line 181
// (mFrameHeight = ...)


#ifdef ROI_1288x808
#define SONY_CROP_RES 1288x808
#define SONY_CROPPING (0x40)
#define SONY_WINMODE  SONY_CROPPING
#define SONY_YSIZE 861
#define WINPVL ((SONY_YSIZE-809)&0xff)
#define WINPVH (((SONY_YSIZE-809)>>8)&0xff)
#else

#ifdef ROI_1288x728
#define SONY_CROP_RES 1288x728
#define SONY_CROPPING (0x40)
#define SONY_WINMODE  SONY_CROPPING
#define SONY_YSIZE ((729+15) | 1)
#define WINPVL ((SONY_YSIZE-729)&0xff)
#define WINPVH (((SONY_YSIZE-729)>>8)&0xff)

#else
#ifdef SIZE_720P
#define SONY_CROP_RES 1288x728
#define SONY_WINMODE  (0x10)
#define SONY_YSIZE (750| 1)
#define WINPVL ((SONY_YSIZE-729)&0xff)
#define WINPVH (((SONY_YSIZE-729)>>8)&0xff)

#else 
#define SONY_WINMODE  (0x00)
//#define SONY_CROPPING (0x00)
#define SONY_YSIZE 1100

#endif  //ifdef SIZE_720P
#endif  //ifdef ROI_1288x728
#endif  //ifdef ROI_1288x808
#define VMAXL (SONY_YSIZE & 0xff)
#define VMAXH ((SONY_YSIZE >>8) & 0xff)
#define HMAXL ((30*4500*1100/SONY_YSIZE/FPS) & 0xff)
#define HMAXH (((30*4500*1100/SONY_YSIZE/FPS) >>8 ) & 0xff)

static uint8_t Sony_Table[] = {
    0x30, 0x02, 0x00,  // master mode start
    0x30, 0x09, 0x02,  // frame rate = 2, conversion gain = low
    0x30, 0x0F, 0x00,  // fixed 00
    0x30, 0x12, 0x2C,  // fixed 2c
    0x30, 0x13, 0x01,  // fixed 01
    0x30, 0x16, 0x09,  // fixed 08
    0x30, 0x1D, 0xC2,  // fixed c2
    0x30, 0x49, 0x0A,  // vsync, hsync
    0x30, 0x54, 0x66,  // mipi-csi output
    0x30, 0x5D, 0x00,  // in clk 2
    0x30, 0x5F, 0x00,  // in clk 4
    0x30, 0x70, 0x02,  // fixed 02
    0x30, 0x71, 0x01,  // fixed 01
    0x30, 0x9E, 0x22,  // fixed 22
    0x30, 0xA5, 0xFB,  // fixed fb
    0x30, 0xA6, 0x02,  // fixed 02
    0x30, 0xB3, 0xFF,  // fixed ff
    0x30, 0xB4, 0x01,  // fixed 01
    0x30, 0xB5, 0x42,  // fixed 42
    0x30, 0xB8, 0x10,  // reserved
//    0x30, 0xC2, 0x01,  // cmos output... should be 0x03
    0x30, 0xC2, 0x01,  // mipi output... could be 0x01 as well
//    0x30, 0xC2, 0x03,  // mipi output
    0x31, 0x0F, 0x0F,  // fixed 0f
    0x31, 0x10, 0x0E,  // fixed 0e
    0x31, 0x11, 0xE7,  // fixed e7
    0x31, 0x12, 0x9C,  // fixed 9c
    0x31, 0x13, 0x83,  // fixed 83
    0x31, 0x14, 0x10,  // fixed 10
    0x31, 0x15, 0x42,  // fixed 42
    0x31, 0x28, 0x1E,  // fixed 1e
    0x31, 0xED, 0x38,  // fixed 38
    0x32, 0x0C, 0xCF,  // fixed cf
    0x32, 0x4C, 0x40,  // fixed 40
    0x32, 0x4D, 0x03,  // fixed 03
    0x32, 0x61, 0xE0,  // fixed e0
    0x32, 0x62, 0x02,  // fixed 02
    0x32, 0x6E, 0x2F,  // fixed 2f
    0x32, 0x6F, 0x30,
    0x32, 0x70, 0x03,
    0x32, 0x98, 0x00,
    0x32, 0x9A, 0x12,
    0x32, 0x9B, 0xF1,
    0x32, 0x9C, 0x0C,
    0x33, 0x44, 0x10,  // output signal interface
    0x33, 0x46, 0x01,  // 2 lanes
    0x33, 0x6B, 0x37,  // global timing
    0x33, 0x7F, 0x01,  // 2 lanes
    0x33, 0x82, 0x5F,  // globale timing
    0x33, 0x83, 0x17,  // global timing
    0x33, 0x84, 0x37,  // global timing
    0x33, 0x85, 0x17,  // global timing
    0x33, 0x86, 0x17,  // global timing
    0x33, 0x87, 0x17,  // global timing
    0x33, 0x88, 0x4F,  // global timing
    0x33, 0x89, 0x27,  // global timing
    0x33, 0x81, 0x1B,  // 27 MHz clk
    0x33, 0x8D, 0x3D,  // 27 MHz
    0x33, 0x8E, 0x01,  // 27 MHz

#ifdef ROI_1288x808   // window cropping mode 1288x808
    0x30, 0x07, SONY_WINMODE,   // window cropping mode
    0x30, 0x36, 0x00,   // optical black x-2 lines

    0x30, 0x38, 0x00,   // WINPV: 0 from top
    0x30, 0x39, 0x00,   // WINPV: MSB
    0x30, 0x3C, 0x0c,   // WINPH: 12 from left
    0x30, 0x3D, 0x00,   // WINPH: MSB

    0x30, 0x3A, 0x28,   // WINWV: 808 (0x328) from top
    0x30, 0x3B, 0x03,   // WINWV: MSB
    0x30, 0x3E, 0x08,   // WINWH: 1288 (0x508) from left
    0x30, 0x3F, 0x05,   // WINWH: MSB
#endif //ROI_1288x808

#ifdef ROI_1288x728   // window cropping mode 1288x808
    0x30, 0x18, VMAXL,
    0x30, 0x19, VMAXH,
    0x30, 0x1B, HMAXL,
    0x30, 0x1C, HMAXH,
    0x30, 0x07, SONY_WINMODE,   // window cropping mode
    0x30, 0x36, 0x02,   // optical black x lines: turned off
    0x33, 0x53, 0x00,   // CSI optical black x-2 lines

#ifdef WINPVL
    0x30, 0x38, WINPVL,   // WINPV: 0 from top
#else
    0x30, 0x38, 0X00,   // WINPV: 0 from top
#endif
#ifdef WINPVH
    0x30, 0x39, WINPVH,    // WINPV: MSB
#else
    0x30, 0x39, 0x00,   // WINPV: MSB
#endif
    0x30, 0x3C, 0x0c,   // WINPH: 12 from left
    0x30, 0x3D, 0x00,   // WINPH: MSB

    //0x30, 0x3A, 0xe0,   // WINWV: 736 from top to be nx32 lines 
    0x30, 0x3A, 0xd9,   // WINWV: 729 (0x2d9) from top
    0x30, 0x3B, 0x02,   // WINWV: MSB
    0x30, 0x3E, 0x08,   // WINWH: 1288 (0x508) from left
    0x30, 0x3F, 0x05,   // WINWH: MSB
    0x33, 0x57, 0xd9,   // PIC_SIZE (CSI): 729 from top
    0x33, 0x58, 0x02,   // PIC_SIZE (CSI): MSB

#endif //ROI_1288x728

#ifdef SIZE_720P   // SIZE_720P Mode
    0x30, 0x18, VMAXL,
    0x30, 0x19, VMAXH,
    0x30, 0x3A, 0xd9,   // not used just to display
    0x30, 0x3B, 0x02,
    0x30, 0x1B, HMAXL,
    0x30, 0x1C, HMAXH,
    0x30, 0x07, SONY_WINMODE,   // window cropping mode
    0x30, 0x36, 0x02,   // optical black x lines: turned off
    0x33, 0x53, 0x00,   // CSI optical black x-2 lines
    0x33, 0x57, 0xd9,   // PIC_SIZE (CSI): 729 from top
    0x33, 0x58, 0x02,   // PIC_SIZE (CSI): MSB

#endif //SIZE_720P


    
#if 0   // window cropping mode 640x480
    0x30, 0x07, 0x40,   // window cropping mode
    0x30, 0x38, 0x10,   // WINPV: 16 from top
    0x30, 0x39, 0x00,   // WINPV: MSB
    0x30, 0x3A, 0xE0,   // WINWV: 480 from top
    0x30, 0x3B, 0x01,   // WINWV: MSB
    0x30, 0x3C, 0x10,   // WINPH: 16 from left
    0x30, 0x3D, 0x00,   // WINPH: MSB
    0x30, 0x3E, 0x80,   // WINWH: 640 from left
    0x30, 0x3F, 0x02,   // WINWH: MSB

#endif



#if 0 // PG 1
    0x30, 0x8c, 0x51,  // test pattern generator
    0x30, 0x0A, 0x00,
    0x30, 0x0E, 0x00,
    0x30, 0x89, 0x00


#endif // PG1

#if 0 // PG A
    0x30, 0x8c, 0xA1,  // test pattern generator
    0x30, 0x0A, 0x00,
    0x30, 0x0E, 0x00,
    0x30, 0x89, 0x00,
    0x30, 0x96, 0xff,  // PGDATA 1 (LSB part)
    0x30, 0x97, 0x0f,  // PGDATA 1 (MSB part)
    0x30, 0x8D, 0xA0,  // PGHPOS (LSB part)
    0x30, 0x8E, 0x00   // PGHPOS (MSB part)
#endif // PG A
}; //Sony_Table[]


static uint8_t Sony_Flip_Table[] = {
    0x30, 0x07, (SONY_WINMODE|0x03)  // invert vertical [0] and horizontal [1] scan
                       // watch out for other cropping bits!!!
#ifdef WINPVL
    ,0x30, 0x38, WINPVL   // WINPV: 0 from top
#endif
#ifdef WINPVH
    ,0x30, 0x39, WINPVH    // WINPV: MSB
#endif

}; //Sony__Flip_Table[]

static uint8_t Sony_ConvH_Table[] = {
    0x30, 0x09, 0x12  // frame rate = 2, conversion gain = high
}; //Sony_ConvH_Table[]

static uint8_t Sony_ConvL_Table[] = {
    0x30, 0x09, 0x02  // frame rate = 2, conversion gain = low
}; //Sony_ConvH_Table[]

static uint8_t Sony_6dbAgain_Table[] = {
  0x30, 0x15, 0x00,      // 6 db analog gain
  0x30, 0x14, 0x3c,
  0x30, 0x21, 0x00,      // 960 lines of exposure
  0x30, 0x20, 0x8b
}; //Sony_6dbAgain_Table[]


#endif // SONY_CONFIG_H
