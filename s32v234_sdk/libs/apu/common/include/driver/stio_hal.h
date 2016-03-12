/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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

#ifndef STIO_HAL_HPP___
#define STIO_HAL_HPP___

#define STIO_INDEX_SOUT1_CONFIG_INDEX   0
#define STIO_INDEX_SOUT2_CONFIG_INDEX   1
#define STIO_INDEX_SOUT3_CONFIG_INDEX   2
#define STIO_INDEX_SOUT4_CONFIG_INDEX   3
#define STIO_INDEX_SIN1_CONFIG_INDEX    4
#define STIO_INDEX_SIN2_CONFIG_INDEX    5
#define STIO_INDEX_SIN3_CONFIG_INDEX    6
#define STIO_INDEX_SIN4_CONFIG_INDEX    7

enum STIO_LINETYPE
{
   STIO_LT_YUYV   = 0x10,
   STIO_LT_UVUV   = 0x20,
   STIO_LT_PLANAR = 0x30,

   STIO_LT_PLANAR44 = 0x40,
   STIO_LT_PLANAR22 = 0x50,
   
   STIO_LT_UYVY     = 0x60,
   STIO_LT_YVYU     = 0x70,

   STIO_LT_MAX      = 0x60

};

enum STIO_STREAMS
{
   STIO_OUT1       = 0,
   STIO_OUT2       = 1,   
   STIO_OUT3       = 2,
   STIO_OUT4       = 3,
   STIO_IN1        = 4,
   STIO_IN2        = 5,    
   STIO_IN3        = 6,
   STIO_IN4        = 7,
   STIO_IN1_SHADOW = 8,
   STIO_IN2_SHADOW = 9,
   STIO_IN3_SHADOW =10,
   STIO_IN4_SHADOW =11    
};

//void stio_hal_config(APEX_642CL_STREAM_DMA_STREAM_DCR *r, unsigned int i);
void stio_hal_pollwait_sti0_done();
void stio_hal_interruptclear_sti0_done();
void stio_hal_interruptclear_sti1_done();
void stio_hal_interruptclear_sti0_framestart();
void stio_hal_interruptclear_sti1_framestart();
void stio_hal_interruptclear_sto0_done();
void stio_hal_interruptclear_sti_done(int channel);
void stio_hal_interruptclear_sto_done(int channel);

#if 0 //TODO: everything below is unverified HAL code ... cleanup and verification required!

#if (ATD_HW_PLATFORM == ATD_TYCHE)
   #define StreamOut1_FIFO_Addr  0xA0010300 
   #define StreamIn1_FIFO_Addr  0xA0010600 
   #define StreamIn2_FIFO_Addr  0xA0010700 
#endif




#define STIO_INDEX_SOUT_CONFIG_INDEX   0
 
enum STIO_LINETYPE
{
   STIO_LT_YUYV     = 0x0,
   STIO_LT_UVUV     = 0x1,
   STIO_LT_PLANAR   = 0x2,
   STIO_LT_PLANAR44 = 0x3,
   STIO_LT_PLANAR22 = 0x4,
   STIO_LT_MAX      = 0x5
};

enum STIO_STREAMS
{
   STIO_OUT1       = 0,
   STIO_OUT2       = 1,   
   STIO_OUT3       = 2,
   STIO_OUT4       = 3,
   STIO_IN1        = 4,
   STIO_IN2        = 5,    
   STIO_IN3        = 6,
   STIO_IN4        = 7,
   STIO_IN1_SHADOW = 8,
   STIO_IN2_SHADOW = 9,
   STIO_IN3_SHADOW =10,
   STIO_IN4_SHADOW =11    
};

void STIO_ClearInterrupt(void);
void STIO_RESET(void);
void STIO_StreamIn1Source_Set(int slectSource);

unsigned int STIO_Config(SIO_CHNLS_REGISTERS_SHORT *pSioReg, STIO_STREAMS streamID);

unsigned int STIO_Config_Planar(SIO_CHNLS_REGISTERS_SHORT *pSioReg,
                                      unsigned int imageW,
                                      unsigned int blockW,
                                      unsigned int blockH,
                                      unsigned int cuStart,
                                      unsigned int addr);

unsigned int STIO_Config_Planar(SIO_CHNLS_REGISTERS_SHORT *pSioReg,
                                      unsigned int imageW,
                                      unsigned int blockW,
                                      unsigned int blockH,
                                      unsigned int cuStart,
                                      unsigned int addr,
                                      unsigned int CUMasks[4]);

unsigned int STIO_Config(SIO_CHNLS_REGISTERS_SHORT *pSioReg,
                             STIO_LINETYPE              lineType,
                             unsigned int               YAddress,
                             unsigned int               CAddress,
                             unsigned int               CUStart,
                             unsigned int               line_size,    // In pixels
                             unsigned int               num_of_lines, //
                             unsigned int               block_width,  // In pixels, put 8 for 8x8 blocks
                             int                        interface,
                             unsigned int               CUEnd);
                         
unsigned int STIO_Config(STIO_LINETYPE    lineType,
                             unsigned int    YAddress,
                             unsigned int    CAddress,
                             unsigned int    CUStart, 
                             unsigned int    line_size,    // In pixels
                             unsigned int    num_of_lines, // 
                             unsigned int    block_width,  // In pixels, put 8 for 8x8 blocks
                             int             interface,
                             unsigned int    CUEnd = 64);

extern SIO_CHNLS_REGISTERS_SHORT gSioTemp;

void STIO_DecodeConfigure(SIO_CHNLS_REGISTERS_SHORT * p);

void STI_StreamIN1_Start(void);
void STI_StreamIN1_Wait(void);
void STI_StreamIN2_Start(void);
void STI_StreamIN2_Wait(void);
void STO_StreamOut_Start(void);
void STO_StreamOut_Wait(void);


__inline void STIO_RESET(STIO_STREAMS streams)
{
   int bp;
   volatile STIO_REGISTERS *const lpSTIORegisters = (STIO_REGISTERS*)ReturnVirtualHwPtr(HW_REG_STIO);

   lpSTIORegisters->dmaDisable.as32BitValue     = 1 << streams;
   lpSTIORegisters->interruptClear.as32BitValue = 1 << streams;
   lpSTIORegisters->interruptMask.as32BitValue |= 1 << streams;   // mask out further interrupt
   bp = 4 ^ (int) streams;
   bp >>= 1;
   lpSTIORegisters->miscControl.as32BitValue   |= ( 1 << bp);
   for ( int i = 0; i < 0x1000; i++)
   {
   }
   lpSTIORegisters->miscControl.as32BitValue   &= ~( 1 << bp);
}
__inline void STIO_START(STIO_STREAMS streams)
{
   volatile STIO_REGISTERS *const lpSTIORegisters = (STIO_REGISTERS*)ReturnVirtualHwPtr(HW_REG_STIO);

   lpSTIORegisters->dmaEnable.as32BitValue      = 1 << streams;
}

__inline void STIO_WAIT(STIO_STREAMS streams)
{
   volatile STIO_REGISTERS *const lpSTIORegisters = (STIO_REGISTERS*)ReturnVirtualHwPtr(HW_REG_STIO);

   while ( !(lpSTIORegisters->interruptSource.as32BitValue & ( 1 << streams) ) )
   {
      // polling for done
   }

   lpSTIORegisters->interruptClear.as32BitValue |= 1 << streams;
}

__inline void STIO_WAIT_STARTED(STIO_STREAMS streams)
   
{
   volatile STIO_REGISTERS *const lpSTIORegisters = (STIO_REGISTERS*)ReturnVirtualHwPtr(HW_REG_STIO);

   while ( !(lpSTIORegisters->dmaEnable.as32BitValue & ( 1 << streams) ) )
   {
      // polling for done
   }
}

__inline void STIO_MC_ENABLED(int enabled)
{
   volatile STIO_REGISTERS *const lpSTIORegisters = (STIO_REGISTERS*)ReturnVirtualHwPtr(HW_REG_STIO);

   reg32write (lpSTIORegisters->miscControl, mcEnable, enabled);
}

#endif //if 0

#endif //STIO_HAL_HPP___

