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

#ifndef apu_hal_H
#define apu_hal_H

//#include "APURegisterMap.h"
#include "apu_comm.h"

// sizes definition (in 32-bit words)


#ifdef __cplusplus
extern "C"
{
#endif 


#define APU_LOAD_ID_IMEM            0
#define APU_LOAD_ID_DMEM            1
#define APU_LOAD_ID_VMEM            2


#define APU_MAX_NUMBER_OF_APUS      4


//#define APU_DMEM_SIZE                32*1024
//#define APU_IMEM_SIZE                32*1024


// 32-bit
#define IMEM_SIZE_MAX               8192
#define DMEM_SIZE_MAX               8192
// 64 CU, 4K/CU
#define VMEM_SIZE_MAX               2048  // 2k words

#define IMEM_INIT        1
#define DMEM_INIT        1
#define VMEM_INIT        1
                                                   
// APU D/I Buffer Types
//typedef volatile unsigned int APU_DATA[APU_DMEM_SIZE];
//typedef volatile unsigned int APU_INST[APU_IMEM_SIZE];


// APU HAL
// --------------------------------------------------------------------------
void apu_hal_Enable(unsigned int APUID, unsigned int isEnable);
void apu_hal_Reset(unsigned int APUID);

volatile unsigned int *apu_hal_GetDMEMAddress(unsigned int APUID);
volatile unsigned int *apu_hal_GetIMEMAddress(unsigned int APUID);

// APU Code
// Loader                       
// --------------------------------------------------------------------------
void apu_hal_Load(int apuid,
                  int im_size, const int* im_addr, const int* im_data,
                  int dm_size, const int* dm_addr, const int* dm_data,
                  int vm_size, const int* vm_addr, const int* vm_data);


#ifndef SEG_HOST_TYPE
typedef int64_t  SEG_HOST_TYPE;
typedef uint32_t SEG_MEM_TYPE;
#endif
typedef SEG_HOST_TYPE LOAD_SEGMENT_t[4];
int32_t apu_hal_LoadSegment(int32_t apuid,
                            const LOAD_SEGMENT_t* seg_addr);
void apu_hal_QueryLoad_MEM_REQ(const LOAD_SEGMENT_t* seg_addr,
                               int32_t* pCmemReq,
                               int32_t* pDmemReq,
                               int32_t* pPmemReq);
int32_t apu_hal_RetMemSizes (CMEM_IF_APU_CFG apuconfig,
                              int32_t* pSmemSize,
                              int32_t* pCmemSize);

// IRQ related functions.
void apu_hal_DisableAllIRQs (void);
void apu_hal_ClearAllIRQs(void);

//methods related to DMA loading
int32_t apu_hal_CopyLoadToOalMemory(const SEG_MEM_TYPE* pLoadPmem,
                                    int32_t loadPmemSize,
                                    const SEG_MEM_TYPE* pLoadDmem,
                                    int32_t loadDmemSize,
                                    const SEG_MEM_TYPE* pLoadCmem,
                                    int32_t loadCmemSize,
                                    void** loadOalMemoryPtr_PMEM,
                                    void** loadOalMemoryPtr_DMEM,
                                    void** loadOalMemoryPtr_CMEM);

int32_t apu_hal_GenLoadLL(int32_t apuid,
                          const LOAD_SEGMENT_t* seg_addr,
                          const SEG_MEM_TYPE* pPmemLoadBase, //base address of *_LOAD_PMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          const SEG_MEM_TYPE* pDmemLoadBase, //base address of *_LOAD_DMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          const SEG_MEM_TYPE* pCmemLoadBase, //base address of *_LOAD_CMEM so the offset can be calculated from the src address in LOAD_SEGMENTS
                          uint32_t loadPhysPtr_PMEM,         //base address (physical) of *_LOAD_PMEM
                          uint32_t loadPhysPtr_DMEM,         //base address (physical) of *_LOAD_DMEM
                          uint32_t loadPhysPtr_CMEM,         //base address (physical) of *_LOAD_CMEM
                          void** llOalMemoryPtr);

int32_t apu_hal_LoadSegments_DMA(int32_t apuid,
                                 int32_t dmaCh,
                                 void* pLoadSegmentsLLBufferOal);

// --------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif 

//***************************************************************************
#endif  // apu_hal_H

