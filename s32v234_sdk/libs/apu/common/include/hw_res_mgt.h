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

#ifndef HW_RESMGT_H___CV230X
#define HW_RESMGT_H___CV230X

// Exclusive HW ressources, AND
// --------------------------------------------------------------------
#define HW_RESSOURCE_BEX  0x00000001  // Bit Extractor
#define HW_RESSOURCE_BMP  0x00000002  // Bit Manipulator
#define HW_RESSOURCE_APR   0x00000004 // Array Processor
#define HW_RESSOURCE_SIN   0x00000004 // Stream IN 1
#define HW_RESSOURCE_SOU   0x00000004 // Stream OUT
#define HW_RESSOURCE_SEQ  0x00000008  // HW Sequencer
#define HW_RESSOURCE_BTB  0x00000010  // Bit Blit
#define HW_RESSOURCE_CRY  0x00000020  // Crypto
#define HW_RESSOURCE_MCE  0x00000040  // MC Engine
#define HW_RESSOURCE_IMB  0x00000080  // Internal Memory 40k

// New HW RES entities for SIF block
#define HW_RESSOURCE_SIF_SCALER1   0x00000100  // SIF Scaler1
#define HW_RESSOURCE_SIF_SCALER2   0x00000200  // SIF Scaler2
#define HW_RESSOURCE_SIF_PROCESS   0x00000400  // SIF Processing(Effect/Mask) block
#define HW_RESSOURCE_SIF_DMAIN     0x00000800  // SIF DMA input

#define HW_RESSOURCE_VLC  0x00001000  // VLC (Block Encoder)
#define HW_RESSOURCE_VLD  0x00002000  // VLD (Block Decoder)
#define HW_RESSOURCE_264  0x00004000  // H264 HW Accelerator
#define HW_RESSOURCE_AR2  0x00008000  // Secondary ARM
#define HW_RESSOURCE_ROT  0x00010000  // Rotator

#define HW_RESSOURCE_AAL  0x0001FFFF  // AND exclusive ressources

#define HW_RESSOURCE_OAL  0x0001FFFF  // OR exclusive ressources
#define HW_RESSOURCE_NON  0x00000000  // OR exclusive ressources

// --------------------------------------------------------------------
#define HW_RESSOURCE_NND  4           // Number of nD DMA channels

#define HW_RESSOURCE_NTC (HW_RESSOURCE_NND)

// Return/Error codes
// --------------------------------------------------------------------
#define HW_RESMGT_SUCCESS               (0x00000000                )
#define HW_RESMGT_ERROR                 (0xF0000000                ) // Base error code
#define HW_RESMGT_ERROR_TIMEOUT         (HW_RESMGT_ERROR + 0x01)
#define HW_RESMGT_ERROR_INVALID         (HW_RESMGT_ERROR + 0x02)
#define HW_RESMGT_ERROR_MAXREACHED      (HW_RESMGT_ERROR + 0x04)
#define HW_RESMGT_ERROR_INVALIDTASKID   (HW_RESMGT_ERROR + 0x05)
#define HW_RESMGT_ERROR_INVALIDTRANSID  (HW_RESMGT_ERROR + 0x06)
#define HW_RESMGT_ERROR_RESNOTRELEASED  (HW_RESMGT_ERROR + 0x07)
#define HW_RESMGT_ERROR_CANTINITIALIZE  (HW_RESMGT_ERROR + 0x08)

// Constants
// --------------------------------------------------------------------
#define HW_RESMGT_MAXRESUSERS     16

#define HW_RESMGT_NOTGRANTEDID    0xFFFFFFFF

// Pending requests states
// --------------------------------------------------------------------
#define HW_RESMGT_STATE_INV       0x00000000
#define HW_RESMGT_STATE_RUN       0x00000001
#define HW_RESMGT_STATE_WAI       0x00000002
#define HW_RESMGT_STATE_WFW       0x00000003

#define HW_RESMGT_DEBUG           1
#define HW_RESMGT_ALLOW_NESTED_ALLOCATIONS 0

//#ifdef __cplusplus
//extern "C" {
//#endif /* #ifdef __cplusplus */

struct HWResCRV
{
   int v[HW_RESSOURCE_NTC];
};

void HWResMgt_Init();
void HWResMgt_Init(unsigned int lChannelStatus);

unsigned int HWResMgt_Allocate(unsigned int *id,        // Transaction ID
                               unsigned int r,          // Resource flags
                               unsigned int nD,         // nD Channels
                               unsigned int p,
                               HWResCRV *crv);
                               
unsigned int HWResMgt_AllocateTimeOut(unsigned int *id,     // Transaction ID
                                      unsigned int r,       // Resource flags
                                      unsigned int nD,      // nD Channels
                                      unsigned int p,       // Priority
                                      unsigned int time,    // time out period
                                      HWResCRV  *crv);   


unsigned int HWResMgt_Release(unsigned int id);

//#ifdef __cplusplus
//};
//#endif /* #ifdef __cplusplus */

#endif //HW_RESMGT_H___CV230X

