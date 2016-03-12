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
* \brief    definition of sony camera registers configuration for DOL2
* \author   Tomas Babinec
* \version  0.1
* \date     27.11.2015
* \note
****************************************************************************/

#ifndef SONY_CONFIG_H
#define SONY_CONFIG_H

#define FPS 15

//#define ROI_1288x808
#define ROI_1288x728
// also patch ../../../io/frame_io/src/frame_input_isp.c line 181
// (mFrameHeight = ...)


#ifdef ROI_1288x808
#define SONY_CROP_RES 1288x808
#define SONY_CROPPING (0x40)
#define SONY_YSIZE 861
#define WINPVL ((SONY_YSIZE-809)&0xff)
#define WINPVH (((SONY_YSIZE-809)>>8)&0xff)
#else

#ifdef ROI_1288x728
#define SONY_CROP_RES 1288x728
#define SONY_CROPPING (0x40)
//781
#define SONY_YSIZE (729+34+16)
#define SONY_YPOS ((977-SONY_YSIZE)>>1)
#define WINPVL ((SONY_YSIZE-729)&0xff)
#define WINPVH (((SONY_YSIZE-729)>>8)&0xff)

#else 
#define SONY_CROPPING (0x00)
#define SONY_YSIZE 1100

#endif  //fdef ROI_1288x728
#endif  //ifdef ROI_1288x808
#define VMAXL (SONY_YSIZE & 0xff)
#define VMAXH ((SONY_YSIZE >>8) & 0xff)
#define HMAXL ((30*2250*1100/SONY_YSIZE/FPS) & 0xff)
#define HMAXH (((30*2250*1100/SONY_YSIZE/FPS) >>8 ) & 0xff)

#define CHIP_ID_02 0x30
#define CHIP_ID_03 0x31
#define CHIP_ID_04 0x32
#define CHIP_ID_05 0x33

static uint8_t Sony_Table[] = 
{
    CHIP_ID_02, 0x00, 0x01,  // standby
    CHIP_ID_02, 0x03, 0x01,  // SW reset
    CHIP_ID_02, 0x03, 0x00,  // SW reset off
    CHIP_ID_02, 0x00, 0x01,  // standby
    CHIP_ID_02, 0x01, 0x01,  // Reghold: no update on VSync
 
    CHIP_ID_02, 0x02, 0x00,  // master mode start
    CHIP_ID_02, 0x05, 0x01,  // 12 bit A to D conversion
    CHIP_ID_02, 0x07, 0x43,  // cropping mode + vertical flip
    CHIP_ID_02, 0x06, 0x00,  // all pixel scan (no subsampling)
    CHIP_ID_02, 0x09, 0x11,  // 60fps, HCG // diff 0x2 - 30fps
    CHIP_ID_02, 0x0C, 0x11,  // DOL mode, DOL 2frame
    CHIP_ID_02, 0x0F, 0x00,  // fixed 0x00
    CHIP_ID_02, 0x12, 0x2C,  // fixed 2c
    CHIP_ID_02, 0x13, 0x01,  // fixed 01
    CHIP_ID_02, 0x16, 0x09,  // fixed 09
    
    CHIP_ID_02, 0x14,  0,    // 6dB analog gain
    CHIP_ID_02, 0x15,  0,    // MSB
    
    CHIP_ID_02, 0x18, 0x0B,  // VMAX 0x30B = 779 // diff 729
    CHIP_ID_02, 0x19, 0x03,  // MSB
    
    CHIP_ID_02, 0x1B, HMAXL,  // HMAX 0xC69 (=4765 =0x129d for 20fps)
    CHIP_ID_02, 0x1C, HMAXH,  // MSB
    
    CHIP_ID_02, 0x1D, 0xC2,  // fixed c2
    
    CHIP_ID_02, 0x20, 0x04,  // SHS1 (Low) 0x4 // diff 0x3
    CHIP_ID_02, 0x21, 0x00,  // SHS1 (High) 0
    CHIP_ID_02, 0x22, 0x00,  // SHS1 (High) 0
    CHIP_ID_02, 0x23, 0x95,  // SHS2 (Low) 0x95 // diff 0x95
    CHIP_ID_02, 0x24, 0x00,  // SHS2 (High) 0
    CHIP_ID_02, 0x25, 0x00,  // SHS2 (High) 0
    
    CHIP_ID_02, 0x2C, 0x31,  // RHS1 (Low) 0x31 // diff 0x09
    //CHIP_ID_02, 0x2D, 0x31,  // RHS1 (Low) 0x31 // diff 0x09
        
    CHIP_ID_02, 0x36, 0x02,   // WINOB -2 (value=2 means 0 lines)

    CHIP_ID_02, 0x38, SONY_YPOS,  // WINPV
    CHIP_ID_02, 0x3A, 0xD9,  // WINWV (low) 0x2D8 = 728
    CHIP_ID_02, 0x3B, 0x02,  // WINWV (high)
    
    CHIP_ID_02, 0x3C, 0x0A,  // WINPH ((1308 - 1288)/2)
    CHIP_ID_02, 0x3E, 0x08,  // WINWV (low) 0x508 = 1288
    CHIP_ID_02, 0x3F, 0x05,  // WINWV (high)
    
    CHIP_ID_02, 0x49, 0x0A,  // vsync, hsync
    CHIP_ID_02, 0x54, 0x66,  // mipi-csi output
    
    CHIP_ID_02, 0x5D, 0x00,  // in clk 2
    CHIP_ID_02, 0x5F, 0x00,  // in clk 4
    
    CHIP_ID_02, 0x70, 0x02,  // fixed 02
    CHIP_ID_02, 0x71, 0x01,  // fixed 01
    CHIP_ID_02, 0x9E, 0x22,  // fixed 22
    CHIP_ID_02, 0xA5, 0xFB,  // fixed fb
    CHIP_ID_02, 0xA6, 0x02,  // fixed 02
    CHIP_ID_02, 0xB3, 0xFF,  // fixed ff
    CHIP_ID_02, 0xB4, 0x01,  // fixed 01
    CHIP_ID_02, 0xB5, 0x42,  // fixed 42
    CHIP_ID_02, 0xB8, 0x10,  // reserved
    
    CHIP_ID_02, 0xC2, 0x01,  // mipi output xlsx says 0x01, old DOL has 0x03???   
    
    CHIP_ID_03, 0x08, 0x01,  // XVSMSKCNT = 1, subsamples XVS for DOL 2
    CHIP_ID_03, 0x09, 0x01,  // XVSMSKCNT_INT = 1, subsamples XVS for DOL 2
    CHIP_ID_03, 0x0F, 0x0F,  // fixed 0f
    CHIP_ID_03, 0x10, 0x0E,  // fixed 0e
    CHIP_ID_03, 0x11, 0xE7,  // fixed e7
    CHIP_ID_03, 0x12, 0x9C,  // fixed 9c
    CHIP_ID_03, 0x13, 0x83,  // fixed 83
    CHIP_ID_03, 0x14, 0x10,  // fixed 10
    CHIP_ID_03, 0x15, 0x42,  // fixed 42
    CHIP_ID_03, 0x28, 0x1E,  // fixed 1e
    CHIP_ID_03, 0xED, 0x38,  // fixed 38
    
    CHIP_ID_04, 0x0c, 0xCF, // fixed cf
    CHIP_ID_04, 0x4C, 0x40,  // fixed 40
    CHIP_ID_04, 0x4D, 0x03,  // fixed 03
    CHIP_ID_04, 0x61, 0xE0,  // fixed e0
    CHIP_ID_04, 0x62, 0x02,  // fixed 02
    CHIP_ID_04, 0x6E, 0x2F,  // fixed 2f
    CHIP_ID_04, 0x6F, 0x30,
    CHIP_ID_04, 0x70, 0x03,
    CHIP_ID_04, 0x98, 0x00,
    CHIP_ID_04, 0x9A, 0x12,
    CHIP_ID_04, 0x9B, 0xF1,
    CHIP_ID_04, 0x9C, 0x0C,

#if 1    
    CHIP_ID_05, 0x44, 0x00,  // output signal interface
    CHIP_ID_05, 0x46, 0x01,  // 2 lanes
    
    CHIP_ID_05, 0x57, 0x00,   // PIC_SIZE_V (CSI): 1536 from top // diff 0x5bc
    CHIP_ID_05, 0x58, 0x06,   // PIC_SIZE_V (CSI): MSB
    
    CHIP_ID_05, 0x6B, 0x57,  // THSEXIT global timing // dif 0x37
    CHIP_ID_05, 0x7F, 0x01,  // 2 lanes
    CHIP_ID_05, 0x81, 0x1B,  // INCK_FREQ1 MSB, globale timing, 27 MHz clk
    CHIP_ID_05, 0x82, 0x6F,  // TCLKPOST, globale timing // diff 0x5f
    CHIP_ID_05, 0x83, 0x27,  // THSPREPARE, global timing // diff 0x17
    CHIP_ID_05, 0x84, 0x4F,  // THSZERO, global timing // diff 0x37
    CHIP_ID_05, 0x85, 0x2F,  // THSTRAIL, global timing // diff 0x17
    CHIP_ID_05, 0x86, 0x2F,  // TCLKTRAIL, global timing // diff 0x17
    CHIP_ID_05, 0x87, 0x2F,  // TCLKPREPARE, global timing // diff 0x17
    CHIP_ID_05, 0x88, 0x9F,  // TCLKZERO, global timing // diff 0x4F
    CHIP_ID_05, 0x89, 0x37,  // TLPX, global timing // diff 0x27
    CHIP_ID_05, 0x8D, 0x3D,  // INCK_FREQ2, 27 MHz
    CHIP_ID_05, 0x8E, 0x01,  // INCK_FREQ2, 27 MHz
#else
    
    0x33, 0x44, 0x00,  // output signal interface REPETITION 0 - 60fps, 594Mbps
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
    
    CHIP_ID_05, 0x57, 0x00,   // PIC_SIZE_V (CSI): 1536 from top // diff 0x5bc
    CHIP_ID_05, 0x58, 0x06,   // PIC_SIZE_V (CSI): MSB
#endif

    CHIP_ID_02, 0x01, 0x00,  // Reghold: update on VSync

};


static uint8_t Sony_Flip_Table[] = {

}; //Sony__Flip_Table[]

static uint8_t Sony_ConvH_Table[] = {
}; //Sony_ConvH_Table[]

static uint8_t Sony_ConvL_Table[] = {
}; //Sony_ConvH_Table[]

static uint8_t Sony_6dbAgain_Table[] = {
  CHIP_ID_02, 0x15, 0x00,      // 6 db analog gain
  CHIP_ID_02, 0x14, 0x3c,
  CHIP_ID_02, 0x21, 0x00,      // 960 lines of exposure
  CHIP_ID_02, 0x20, 0x8b
}; //Sony_6dbAgain_Table[]

#endif // SONY_CONFIG_H
