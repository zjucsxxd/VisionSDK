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
/**
* \file     seq_func.h
* \brief    declaration of Sequencer driver internal functionality
* \author   Tomas Babinec
* \version  0.1
* \date     12.6.2014
* \note
****************************************************************************/
#ifndef SEQ_FUNC_H
#define SEQ_FUNC_H

#ifndef __STANDALONE__
#include <linux/interrupt.h>    // For interrupts
#endif //#ifdef __STANDALONE__

#include "seq.h"
#include "seq_types.h"

#ifdef __cplusplus 
extern "C" { 
#endif

typedef volatile uint32_t vuint32_t;

//*****************************************************************************
// constants
//*****************************************************************************

#define SEQ_WDT_TIMEOUT 300	  ///< Sent message watch dog timeout
#define SEQ_RAB_TIMEOUT SEQ_WDT_TIMEOUT	  ///< Ready after boot wait timeout

#ifdef __STANDALONE__
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint32_t irqreturn_t;
#endif // #ifndef __STANDALONE__

/*****************************************************************************
* macros
*****************************************************************************/

#include "fdma_types.h"
//*****************************************************************************
// struct definitions
//*****************************************************************************

//*****************************************************************************
// functions (prototypes)
//*****************************************************************************

/****************************************************************************/
/** Sets up the internal functionality of the Sequencer kernel module. 
* Initializes Sequencer related resources.
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_Setup(void);

/****************************************************************************/
/** Releases all Sequencer related resources.
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_Close(void);

/****************************************************************************/
/** Resets the Sequencer HW.
*  
*****************************************************************************/
void SEQ_DRV_Reset(void);

/****************************************************************************/
/** Attempt to boot Sequencer.
* Waits for the ready-after-boot message to arrive. Fails if wait times out or
* reset is done.
* 
*  \return SEQ_DRV_SUCCESS if all OK, otherwise SEQ_DRV_FAILURE.
*****************************************************************************/
uint32_t SEQ_DRV_Boot(void);

#if 0
/****************************************************************************/
/** Handles IRQs signalled at that time.
*
*  \note Currently implemented only for OUTBOUNTD_MSG_RDY and INBOUND_MSG_ACK.
*****************************************************************************/
void SEQ_DRV_IrqsProcess(void);

/****************************************************************************/
/** Handler for Sequencer message IRQ.
* 
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
irqreturn_t SEQ_MsgIrqHandler(int32_t aIrq, void *apDev_id);

/****************************************************************************/
/** Handler for HOST message acknowledge IRQ.
* 
* \param aIrq 	  irq number
* \param apDev_id identification of the device
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
irqreturn_t SEQ_MsgAckIrqHandler(int32_t aIrq, void *apDev_id);

/****************************************************************************/
/** Does Message related deffered work.
* 
* \param aArg not used
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
void SEQ_S2hMsgTasklet(unsigned long aArg);

/****************************************************************************/
/** Sets up and schedules a timer.
* \note Fixed behavior as watch dog for Sequencer's in-time-response check.
* \TODO: make it configurable.
*****************************************************************************/
void SEQ_WDTSchedule(void);

/****************************************************************************/
/** Removes a previously scheduled timer.
* \note Fixed behavior as watch dog for Sequencer's in-time-response check.
* \TODO: make it configurable.
*****************************************************************************/
void SEQ_WDTRemove(void);

/****************************************************************************/
/** Initializes specified messaging pool message pool.
*
* Computes wrapparound if needed.
* 
* \param apMsgPool pointer to messaging pool
* \param apMsgBase pointer to first message in the pool
* \param aMsgCnt   number of messages in the pool
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
void SEQ_MsgPoolInit(SEQ_MessagePool_t *apMsgPool, uint8_t* apMsgBase, uint32_t aMsgCnt);

/****************************************************************************/
/** Shifts write pointer in message pool.
*
* Computes wrapparound if needed. In case of an owerflow the write pointer is
* set to NULL and SEQ_DRV_FAILURE is returned.
* 
* \param apMsgPool pointer to messaging pool
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_MsgPoolWriteShift(SEQ_MessagePool_t *apMsgPool);

/****************************************************************************/
/** Shifts read pointer in message pool.
* 
* Computes wrapparound if needed. If the pool is empty already, SEQ_DRV_FAILURE  
* is returned.
* 
* \param apMsgPool pointer to messaging pool
* 
* \return SEQ_DRV_SUCCESS if all ok, SEQ_DRV_FAILURE if pool empty already
*
*****************************************************************************/
int32_t SEQ_MsgPoolReadShift(SEQ_MessagePool_t *apMsgPool);

#endif //0

/****************************************************************************/
/** Handles IRQs signalled at that time.
*
*  \note Currently implemented only for OUTBOUNTD_MSG_RDY and INBOUND_MSG_ACK.
*****************************************************************************/
void SEQ_DRV_IrqsProcess(void);

/****************************************************************************/
/** Sends message to Sequencer.
* 
* \param apMsg pointer to the message structure
* \param aWait if non zero the call blocks until SeqFW acknowledges the MSG.
*****************************************************************************/
int32_t SEQ_DRV_MsgSend(SEQ_Message_t *apMsg, uint8_t aWait);

/****************************************************************************/
/** Invokes fDMA TD scheduling through Sequencer HW.
* 
* \param aTdIdx index of the TD to be scheduled 
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_FdmaTdSchedule(uint32_t aTdIdx);

/****************************************************************************/
/** Downloads Graph to PRAM location.
* 
* \param apGraph pointer to graph structure in user-space
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_DRV_GraphDownload(SEQ_GraphPackage_t *apGraph);

int32_t SEQ_DRV_GraphFetch(SEQ_GraphPackage_t *apGraph);

/****************************************************************************/
/** Executes the Graph.
* 
* \param aFrmCnt number of frames to capture
* \param aFrmCnt number of lines per input frame (0 => given by CSI)
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_DRV_GraphStart(uint32_t aFrmCnt, uint32_t aInputLines);

/****************************************************************************/
/** Requests graceful stop of the Graph execution.
 * 
 * Current frame will be finished.
 * 
 * \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
 ****************************************************************************/
int32_t SEQ_DRV_GraphStop(void);

/****************************************************************************/
/** Returns 0 if graph execution is off.
 * 
 * \return 0 if graph is off
 *         1 if graph is on
 ****************************************************************************/
int32_t SEQ_DRV_GraphStateGet(void);

/****************************************************************************/
/** Requests frame buffers for one frame stream.
* 
* Based on data given in "Request" structure prepares specified stream and
* allocates framebuffer structures. Addresses for buffer data have to be 
* included in the request structure.
* 
* Request for 0 buffer count makes the previous stream setup to be released.
* 
* \param apRequest defines request details
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_DRV_FrmBuffersRequest(SEQ_BufferRequest_t *apRequest);

/****************************************************************************/
/** Resets all allocated streams.
*
*****************************************************************************/
void SEQ_DRV_FrmStreamsReset(void);

/****************************************************************************/
/** Queries buffer at given location.
* 
* Based on buffer location specified by the stream and buffer index in 
* BufferInfo structure the status and size of the buffer is updated in 
* the structure.
* 
* \param apRequest defines request details
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no such buffer exists
*
*****************************************************************************/
int32_t SEQ_DRV_FrmBufferQuery(SEQ_FrmBufferInfo_t *apBufferInfo);

/****************************************************************************/
/** Adds frame buffer to work queue.
* 
* Performs checks if buffer is available to user.
* 
* \param apBufferInfo buffer identification (stream + buffer index).
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_DRV_FrmBufferPush(SEQ_FrmBufferInfo_t *apBufferInfo);

/****************************************************************************/
/** Removes frame buffer from DONE queue.
* 
* \param apBufferInfo buffer identification (stream + buffer index).
* 
* \return SEQ_DRV_SUCCESS if all ok, otherwise SEQ_DRV_FAILURE
*
*****************************************************************************/
int32_t SEQ_DRV_FrmBufferPop(SEQ_FrmBufferInfo_t *apBufferInfo);

/****************************************************************************/
/** Copies PRAM auxiliary data to given structure.
* 
* \param apAuxData address of the AuxData package
*
*****************************************************************************/
void SEQ_DRV_PramAuxDataGet(SEQ_AuxData_t* apAuxData);

/****************************************************************************/
/** sets user proccess pid
* 
* \param aUsrPid user pid to be set
*
*****************************************************************************/
void SEQ_UserPidSet(pid_t aUsrPid);

/****************************************************************************/
/** Enables auto exposure control.
* 
*****************************************************************************/
void SEQ_DRV_AutoExpEnable(void);

/****************************************************************************/
/** Disables auto exposute control.
*
*****************************************************************************/
void SEQ_DRV_AutoExpDisable(void);

/****************************************************************************/
/** Request IPU profiling to be executed for next N frames.
* 
* \param aFrmCnt number of frames to let the profiling to be on
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
int32_t SEQ_DRV_IpuPerformanceInfoRequest(uint32_t aFrmCnt);

/****************************************************************************/
/** Fetches IPU performance info from registers.
* 
* \param apIpuRegs pointer to array of IPU performance register structures
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no data ready yet or apIpuRegs was NULL
*****************************************************************************/
int32_t SEQ_DRV_IpuPerformanceInfoGet(SEQ_IpuPerformanceRegs_t *apIpuRegs);

/****************************************************************************/
/** Enables Sony automatic exposure.
* 
*****************************************************************************/
void SEQ_DRV_AutoExpEnable(void);

/****************************************************************************/
/** Enables logging of specified events.
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
uint32_t SEQ_DRV_EventLogEnable(void);

/****************************************************************************/
/** Enables logging of specified events.
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE otherwise
*****************************************************************************/
uint32_t SEQ_DRV_EventLogDisable(void);

/****************************************************************************/
/** Gets the Event series.
* The event series contains so far recieved events. Max 500 0000 events can be
* collected.
* 
* \param apEventSeries pointer to event series structure
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no data ready yet or apIpuRegs was NULL
*****************************************************************************/
int32_t SEQ_DRV_EventLogGet(SEQ_EventLog_t **appEventLog);

/****************************************************************************/
/** Enables the use of histogram on particular IPU.
*   Only IPU 0-3 are capable of generating histogram.
* 
* \param aIpuIdx index of the IPU
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no data ready yet or apIpuRegs was NULL
*****************************************************************************/
int32_t SEQ_DRV_IpuHistogramEnable(SEQ_IpuEngine_t aIpuIdx);

/****************************************************************************/
/** Disables the use of histogram on particular IPU.
*   Only IPU 0-3 are capable of generating histogram.
* 
* \param aIpuIdx index of the IPU
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no data ready yet or apIpuRegs was NULL
*****************************************************************************/
void SEQ_DRV_IpuHistogramDisable(SEQ_IpuEngine_t aIpuIdx);

/****************************************************************************/
/** Gets the histogram from specified IPU engine.
*   Only IPU 0-3 are capable of generating histogram.
* 
* \param apHist pointer to histogram head structure
* 
* \return SEQ_DRV_SUCCESS if all ok, 
*         SEQ_DRV_FAILURE if no data ready yet or apIpuRegs was NULL
*****************************************************************************/
int32_t SEQ_DRV_IpuHistogramGet(SEQ_IpuHistHead_t *apHist);


void AllocTest(void);

#ifdef __cplusplus 
} 
#endif 

#endif // SEQ_FUNC_H