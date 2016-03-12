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
* \file     fdma_types.h
* \brief    types declarations for fDMA driver
* \author   Tomas Babinec
* \version  0.1
* \date     9.6.2014
* \note
****************************************************************************/
#ifndef FDMA_TYPES_H
#define FDMA_TYPES_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include "s32vs234.h"

#if !defined(__KERNEL__) && !defined(__STANDALONE__)
#include <stdint.h>
#endif // if !defined(__KERNEL__) && !defined(__STANDALONE__)

#include "fdma.h"

//*****************************************************************************
// types
//*****************************************************************************
typedef struct mutex mutex_t;

//typedef volatile uint32_t vuint32_t;
typedef volatile struct FDMA_tag FDMA_Regs_t;

/*****************************************************************************
* struct definitions
*****************************************************************************/
#if defined(__KERNEL__) || defined(__STANDALONE__)

struct fdma_regs;

struct fdma_td;

typedef struct fdma_tdt
{
  struct fdma_td *mpBase;
  uint32_t mTdCnt;
} FDMA_Tdt_t; // struct fdma_tdt (transaction descriptor table)

struct fdma_tdm;

typedef struct fdma_tdm_list_node
{
  struct fdma_tdm_list_node *mpPrev;
  struct fdma_tdm_list_node *mpNext;
  struct fdma_tdm *mpTdm;
} FDMA_TdmListNode_t; // struct fdma_tdm_list_node (one node from list of fdma tdms)

typedef struct fdma_tdm_list
{
  struct fdma_tdm_list_node *mpHead;
  struct fdma_tdm_list_node *mpTail;
  uint32_t mLength;
  struct fdma_tdm_list_node mNodePool[FDMA_TD_CNT];
} FDMA_TdmList_t; // struct fdma_tdm_list (double-linked list of transaction descriptor metadata)

struct fdma_tc;

typedef struct fdma_tc_event
{
  uint32_t mXfrStat;
  uint32_t mXfrCalcCrcVal;
  uint32_t mXfrCurrDdrPtr;	
  uint32_t mXfrCurrSramPtr;  
  uint32_t mXfrRecNum;  	// not needed defined by the index
  uint32_t mSramNextLine;  
} FDMA_TcEvent_t; // struct fdma_tc_event 

#endif // #if defined(__KERNEL__) || defined(__STANDALONE__)

typedef struct fdma_td
{
  uint32_t mDdrImgStartAddr : 32;	// 31:0
  uint32_t mDdrLineStride : 16;		// 47:32
  uint32_t mDdrLineCnt : 16;  		// 63:48
  uint32_t mCrcStartAddr :32;  		// 95:64
  uint32_t mCrcEna : 1;			// 96
  uint32_t mCrcMode : 2;		// 98:97
  uint32_t mCrcPoly : 1;		// 99
  uint32_t mDir : 1;			// 100
  uint32_t mWrEna : 1;			// 101
  uint32_t mTransRecWrBack : 1;		// 102
  uint32_t mThreadId : 3;		// 105:103
  uint32_t mImgDoneSel : 1;  		// 106
  uint32_t mLineSize : 21;		// 127:107
  uint32_t mSramImgStartAddr : 32;	// 159:128
  uint32_t mSramLineStride : 18;	// 177:160
  uint32_t mSramLineCnt : 14;		// 191:178
  uint32_t mDdrBurstLength : 2;		// 193:192
  uint32_t mStuffBits : 30;		// 223:194
  uint32_t mDdrCurrLine : 16;		// 239:224
  uint32_t mSramCurrLine : 16;		// 255:240
} FDMA_Td_t; // struct fdma_td (transaction descriptor)

typedef struct fdma_tdm
{
  uint8_t mTdIdx;
  pid_t mOwnerProcId;
  uint8_t mReserved;
  
} FDMA_Tdm_t; // struct fdma_tdm (transaction descriptor metatdata)

typedef struct fdma_tc
{
  struct fdma_tdm mTdm;
  struct fdma_td mTd;
} FDMA_Tc_t; // struct fdma_tc (transfer channel)

#ifdef __cplusplus 
} //extern "C" { 
#endif

#endif // FDMA_TYPES_H