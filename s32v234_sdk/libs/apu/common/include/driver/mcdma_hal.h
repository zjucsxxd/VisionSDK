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

#ifndef _MCDMA_HAL_H_
#define _MCDMA_HAL_H_

#ifndef MCDMA_TYPES_H_CV230X
#define MCDMA_TYPES_H_CV230X

#define MAX_DMA_CHANNELS        8


#if 0
typedef struct DMAConfigTable
{
   unsigned int                  SourceAddress;                //0x30
   unsigned int                  DestinationAddress;           //0x34
   unsigned int                  ListLinkAddress;              //0x38
   DMA_CHANNEL_N_CONFIGURATION   ConfigRegister;               //0x3C
   unsigned int                  TransferSize;                 //0x40
} DMAConfigTable;
#endif //0

// [APEX-2-CL] same
typedef enum
{
   DMA_LOW       = 0,
   DMA_MEDIUM_1  = 1,
   DMA_MEDIUM_2  = 2,
   DMA_HIGH      = 3
} DMA_PRIORITY;

#if 0
// [Deprecated] Don't use!!!!!
// Also naming conflict
typedef enum
{
   BEAT1  = 0,    //  1 beat transfer.
   BEAT2  = 1,    //  2 beats burst transfer.
   BEAT3  = 2,    //  3 beats burst transfer.
   BEAT4  = 3,    //  4 beats burst transfer.
   BEAT5  = 4,    //  5 beats burst transfer.
   BEAT6  = 5,    //  6 beats burst transfer.
   BEAT7  = 6,    //  7 beats burst transfer.
   BEAT8  = 7,    //  8 beats burst transfer.
   BEAT9  = 8,    //  9 beats burst transfer.
   BEAT10 = 9,    // 10 beats burst transfer.
   BEAT11 = 10,   // 11 beats burst transfer.
   BEAT12 = 11,   // 12 beats burst transfer.
   BEAT13 = 12,   // 13 beats burst transfer.
   BEAT14 = 13,   // 14 beats burst transfer.
   BEAT15 = 14,   // 15 beats burst transfer.
   BEAT16 = 15,    // 16 beats burst transfer.
   SINGLE = 0,    // Single transfer.
   // backward cmpatible
   INCR   = 1,    // Incrementing burst of unspecified length.
   WRAP4  = 3,    // 4 beat wrapping burst.
   INCR4  = 3,    // 4 beat incrementing burst.
   WRAP8  = 7,    // 8 beat wrapping burst.
   INCR8  = 7,    // 8 beat incrementing burst.
   WRAP16 = 15,    // 16 beat wrapping burst.
   INCR16 = 15     // 16 beat incrementing burst.
} DMA_BURST_SIZE;

#endif //0

// [APEX-2-CL] New configuration!!!!
typedef enum
{
   INCR1  = 0,  // 1 beats.
   INCR2  = 1,  // 2 beats.
   INCR3  = 2,  // 3 beats.
   INCR4  = 3,  // 4 beat
   INCR5  = 4,  // 5 beats.
   INCR6  = 5,  // 6 beats.
   INCR7  = 6,  // 7 beats.
   INCR8  = 7,  // 8 beats.
   INCR9  = 8,  // 9 beats
   INCR10 = 9,  // 10 beats.
   INCR11 = 10, // 11 beats.
   INCR12 = 11, // 12 beats.
   INCR13 = 12, // 13 beats
   INCR14 = 13, // 14 beats
   INCR15 = 14, // 15 beats
   INCR16 = 15  // 16 beats
} DMA_BURST_SIZE;

// [APEX-2-CL] same
typedef enum
{
   DMA_BURST_BEAT_BYTE_SIZE       = 0,   // 8 bits.
   DMA_BURST_BEAT_HALFWORD_SIZE   = 1,   // 16 bits.
   DMA_BURST_BEAT_WORD_SIZE       = 2,   // 32 bits.
   DMA_BURST_BEAT_DWORD_SIZE      = 3,   // 64 bits.
   DMA_BURST_BEAT_DDWORD_SIZE     = 4    // 128 bits.
} DMA_BURST_BEAT_SIZE;

//
//The channel can be directed to use a particular AXI port.
//
typedef enum
{
   AXI_PORT_0       = 0,   // use AXI port 0
   AXI_PORT_1       = 1    // use AXI port 1
} AXI_PORT_CHANNEL;

#if 0
//
// Define different configuration structures
//
typedef struct
{
//   DMA_TRANSFER_MODE   TransferMode; // no more affect for transfering 
   DMA_PRIORITY        ChannelPriority;
   DMA_BURST_SIZE      BurstSize;
   DMA_BURST_BEAT_SIZE WordSize;
   unsigned int        RepeatDMA;
   unsigned int        LinkListEnable;
} DMA_TRANSFER_INFO;

//
// Define different transfer types for the API
//
// [Deprecated] Don't use!!!!!
typedef enum
{
   MEM_TO_MEM               = 0,
   MEM_TO_PERIPHERAL        = 1,
   PERIPHERAL_TO_MEM        = 2,
   PERIPHERAL_TO_PERIPHERAL = 3,
   MEM_FILL                 = 4
} DMA_TYPE;
#endif //0

// [APEX-2-CL] New configuration!!!!
typedef enum
{
   DMA_PORT_MEMORY    = 0,
   DMA_PORT_PERIPHERAL= 1
} DMA_PORT_TYPE;

// Define different transfer formats
typedef enum
{
   LINEAR   = 0,
   U2D      = 1,
   U3D      = 2,
   U4D      = 3
} DMA_FORMAT;


typedef enum
{
   SRC_MCDMA_INTERNAL_FIFO  = 0,
   SRC_CMEM_DMA_STREAM_OUT0  = 1,
   SRC_CMEM_DMA_STREAM_OUT1 = 2,
   SRC_MOTION_COMP0   = 3,
   SRC_MOTION_COMP1   = 4,
   SRC_APU0_DMEM_FIFO = 5,
   SRC_APU1_DMEM_FIFO = 6,
   SRC_MEM_FILL0      = 7,
   SRC_MEM_FILL1      = 8,
   SRC_HRSZ0          = 9,
   SRC_HRSZ1          = 10,
   SRC_UNUSED = 0xffffffff
} DMA_SRC_PERIPHERAL;

typedef enum
{
   DST_MCDMA_INTERNAL_FIFO = 0,
   DST_CMEM_DMA_STREAM_IN0 = 1,
   DST_CMEM_DMA_STREAM_IN1 = 2,
   DST_APU0_DMEM_FIFO      = 5,
   DST_APU1_DMEM_FIFO      = 6,
   DST_HRSZ0               = 9,
   DST_HRSZ1               = 10,
   DST_CMEM_DMA_STREAM_IN2 = 11,
   DST_CMEM_DMA_STREAM_IN3 = 12,
   DST_UNUSED = 0xffffffff
} DMA_DST_PERIPHERAL;

#endif // #ifndef MCDMA_TYPES_H_CV230X



#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

void mcdma_hal_program_seq_linkedlist (unsigned int ChannelN, unsigned int LinkedListAddr);
void mcdma_hal_program_nonseq_linkedlist(unsigned int ChannelN, unsigned int LinkedListAddr);
void mcdma_hal_interruptclear_ch_done(unsigned int ChannelN);
void mcdma_hal_start(unsigned int ChannelN);
void mcdma_hal_wait(unsigned int ChannelN);
void mcdma_hal_ch_clear(unsigned int ChannelN);
void mcdma_hal_set_memory_fill_words(unsigned int FillWord0,
                                     unsigned int FillWord1,
                                     unsigned int FillWord2,
                                     unsigned int FillWord3);

void mcdma_hal_enable_perf_counter();
void mcdma_hal_disable_perf_counter();
unsigned int mcdma_hal_read_perf_counter_total();
unsigned int mcdma_hal_read_perf_counter_busrd(); //bus read
unsigned int mcdma_hal_read_perf_counter_buswr(); //bus write

int RetStreamInPeriphId(int lIdx);
int RetStreamOutPeriphId(int lIdx);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_MCDMA_HAL_H_
