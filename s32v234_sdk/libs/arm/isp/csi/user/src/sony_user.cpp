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
 * \file     sony_user.cpp
 * \brief    User-space library calls to access Sony functionality.
 * \author   Tomas Babinec
 * \version  0.1
 * \date     24-november-2015
 * \note
 ****************************************************************************/
#include "s32vs234.h"
#include <stdint.h>
#include <errno.h>
#include <string.h>

#ifndef __STANDALONE__
  #include <signal.h>
  #include <fcntl.h>		// open 
  #include <unistd.h>		// exit 
  #include <sys/ioctl.h>	// ioctl 
  #include <sys/mman.h>	// mmap
#else
  #include "csi_func.h"
  #include "sony_func.h"
#endif // else from #ifndef __STANDALONE__

#define VDB_LOG_NOTE_OFF

#include "sony_public.h"
#include "vdb_log.h"

//****************************************************************************
// consts
//****************************************************************************
#define HIST_GREEN_START 128
#define HIST_GREEN_STOP  189
#define HIST_START_IDX (127)
#define HIST_STOP_IDX  (64)

//****************************************************************************
// types
//****************************************************************************


//****************************************************************************
// global variables
//****************************************************************************
#ifndef __STANDALONE__
  extern int32_t gCsiFD;   ///< csi driver file descriptor
#endif //ifndef __STANDALONE__

//*****************************************************************************
// local data
//*****************************************************************************

//static CSI_EventHandler_t sEventHandler = NULL; ///< user registerred event handler
//static CSI_EventHandlerClass *spEventHandlerClass = NULL; ///< user registerred event handler
//static uint8_t sInitialized = 0;	///< >0 if initialized

// chip geometry settings
static SONY_Geometry_t sGeometry;
static SONY_Exposure_t sExposure;

//*****************************************************************************
// functions definitions
//*****************************************************************************

CSI_LIB_RESULT SONY_RegConfig(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_REG_CONFIG, aCsiIdx)) < 0) 
  {
    VDB_LOG_ERROR("Failed to configure camera registers.\n");
    lRet = CSI_LIB_FAILURE;
  } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
  SONY_DRV_RegConfig(aCsiIdx);
    
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SONY_RegConfig(CSI_BufferList_t *apBuffsList)


//*****************************************************************************

CSI_LIB_RESULT SONY_ExposureStatusGet(enum CSI_IDX aCsiIdx, SONY_ExpState_t &arExpState)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_EXP_STATUS_GET,aCsiIdx)) < 0) 
  {
    VDB_LOG_ERROR("Failed to get camera exposure setup.\n");
    lRet = CSI_LIB_FAILURE;
  } // if ioctl returned failure
  else
  {
    arExpState = (SONY_ExpState_t)lRetVal;
  } // else from if ioctl returned failure

#else // #ifndef __STANDALONE__
  arExpState = SONY_DRV_ExpStateGet(aCsiIdx);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SONY_ExposureStatusGet()

//*****************************************************************************

CSI_LIB_RESULT SONY_ExposureGet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

  if(apExpo != NULL)
  {
    apExpo->mCsiIdx = aCsiIdx;
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_EXP_GET, apExpo)) < 0) 
    {
      VDB_LOG_ERROR("Failed to get camera exposure setup.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_ExposureGet(aCsiIdx, apExpo);    
#endif // else #ifndef __STANDALONE__
    sExposure = *apExpo;
  } // if apExpo not null
  else
  {
    VDB_LOG_ERROR("Exposure structure is NULL.\n");
    lRet = CSI_LIB_FAILURE;
  } // else from if apExpo not null 
  
  return lRet;
} // SONY_ExposureGet()

//*****************************************************************************

CSI_LIB_RESULT SONY_ExposureSet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

  if(apExpo != NULL)
  {
    apExpo->mCsiIdx = aCsiIdx;
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_EXP_SET, apExpo)) < 0) 
    {
      VDB_LOG_ERROR("Failed to set camera exposure setup.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_ExposureSet(aCsiIdx, apExpo);    
#endif // else #ifndef __STANDALONE__
    sExposure = *apExpo;
  } // if apExpo not null
  else
  {
    VDB_LOG_ERROR("Exposure structure is NULL.\n");
    lRet = CSI_LIB_FAILURE;
  } // else from if apExpo not null 
  
  return lRet;
} // SONY_ExposureSet()

//*****************************************************************************

#define EXP_DEBUG 0//200  // number of frames to debug the exposure values
#if (EXP_DEBUG > 0)
  static uint32_t sppExpRec[EXP_DEBUG][4]; // aExposure, exp lines, conv gain, a gain
  static uint32_t sExpRecIdx = 0;
  static float    spHistEnergy[EXP_DEBUG] = {0.0};
#endif // #if (EXP_DEBUG > 0)

CSI_LIB_RESULT SONY_ExposureSet(enum CSI_IDX aCsiIdx, uint32_t aExposure)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;
  uint32_t lExpLines   = 0;
  uint32_t lConv       = sExposure.mConversionGain;
  uint32_t lAnalogGain = sExposure.mAnalogGain;

  // *** if increase required ***
  if(aExposure > SONY_EXP_100_CHNG)
  {
    lExpLines = (sExposure.mExposureLines * aExposure) >> SONY_EXP_100_MULTI;
    if(lExpLines == sExposure.mExposureLines)
    {
      // do at least one line increase
      lExpLines++;
    } // if no change
                 
    if(lExpLines > SONY_EXP_AGAIN_UP_THRESH) // too much
    {
      // increase conversion gain if possible
      if(lConv == 0)
      {
        lExpLines >>= 1;
        lConv       = 1;
      } // if conversion LOW
      
      // use analog gain if needed
      if(lExpLines > SONY_EXP_AGAIN_UP_THRESH) // still too much
      {
        // use 2x analog gain (+6dB) only once
        if(lAnalogGain < SONY_EXP_AGAIN_MAX)
        {
          lExpLines   >>= 1;
          lAnalogGain += SONY_EXP_AGAIN_DOUBLE;
        } // if some again margin left
       
        if(lExpLines > SONY_EXP_AGAIN_UP_THRESH) // still too much - cut
        {
          lExpLines = SONY_EXP_AGAIN_UP_THRESH;
        } // if still too much
      } // if still too much
    } // if exp lines HIGH
    else
    {
      // increase conversion gain if possible
      if((lConv == 0) && (lExpLines > SONY_EXP_CGAIN_UP_THRESH))
      {
        lExpLines >>= 1;
        lConv       = 1;
      } // exp lines high and conversion LOW
      
      // decrease analog gain if possible
      if(lAnalogGain > 0)
      {
        if(lExpLines < SONY_EXP_AGAIN_DOWN_THRESH)
        {
          // try to reduce analog gain
          lAnalogGain -= SONY_EXP_AGAIN_DOUBLE;
          lExpLines <<= 1; // 2x explines
        } // if exp lines low
      } // if analog gain used
    } // else from if exp lines HIGH
  } // if increase required
  
  //*** if decrease required ***
  if(aExposure <= SONY_EXP_100_CHNG)
  {
    lExpLines = (sExposure.mExposureLines * aExposure) >> SONY_EXP_100_MULTI;
    
    // if analog gain set at the moment                 
    if(lAnalogGain > 0)
    {
      if(lExpLines < SONY_EXP_AGAIN_DOWN_THRESH)
      {
        // try to reduce analog gain first
        lAnalogGain -= SONY_EXP_AGAIN_DOUBLE;
        lExpLines <<= 1; // 2x explines
      } // if exp lines low   
    } // if some analog gain set

    // if too low exp lines, try to decrease conversion gain if possible
    if(lExpLines < SONY_EXP_CGAIN_DOWN_THRESH)
    {
      // decrease conversion gain if possible
      if(sExposure.mConversionGain == 1)
      {
        lExpLines <<= 1;
        lConv       = 0;
      } // if conversion gain High
    } // if exp lines too low   
  } // if decrease required

  sExposure.mAnalogGain     = lAnalogGain;
  sExposure.mExposureLines  = /*sGeometry.mVmax -*/ lExpLines /*- 1*/;
  sExposure.mConversionGain = lConv;
  
  sExposure.mCsiIdx = aCsiIdx;

#if (EXP_DEBUG > 0)
  if(sExpRecIdx < EXP_DEBUG)
  {
    sppExpRec[sExpRecIdx][0] = aExposure; // aExposure, exp lines, conv gain, a gain
    sppExpRec[sExpRecIdx][1] = lExpLines;
    sppExpRec[sExpRecIdx][2] = lConv;
    sppExpRec[sExpRecIdx][3] = lAnalogGain;
    sExpRecIdx++;
  } // if not all recorded
  else
  {
    while(1); // wait here
  }// else from if not all recorded
#endif // #if (EXP_DEBUG > 0)  
  
#ifndef __STANDALONE__   
  int32_t lRetVal = 0;
  if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_EXP_SET, &sExposure)) < 0) 
  {
    VDB_LOG_ERROR("Failed to set camera exposure setup.\n");
    lRet = CSI_LIB_FAILURE;
  } // if ioctl returned failure

#else // #ifndef __STANDALONE__
  SONY_DRV_ExposureSet(aCsiIdx, &sExposure);    
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SONY_ExposureSet()

//*****************************************************************************

CSI_LIB_RESULT SONY_GeometryGet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

  if(apGeom != NULL)
  {
    apGeom->mCsiIdx = aCsiIdx;
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_GEO_GET, apGeom)) < 0) 
    {
      VDB_LOG_ERROR("Failed to get camera geometry setup.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_GeometryGet(aCsiIdx, apGeom);
#endif // else #ifndef __STANDALONE__
    sGeometry = *apGeom;
  } // if apGeom not null
  else
  {
    VDB_LOG_ERROR("Geometry structure is NULL.\n");
    lRet = CSI_LIB_FAILURE;
  } // else from if apGeom not null 
  
  return lRet;
} // SONY_GeometryGet()

//*****************************************************************************

CSI_LIB_RESULT SONY_GeometrySet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

  if(apGeom != NULL)
  {
    apGeom->mCsiIdx = aCsiIdx;
#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_GEO_SET, apGeom)) < 0) 
    {
      VDB_LOG_ERROR("Failed to set camera geometry.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_GeometrySet(aCsiIdx, apGeom);
#endif // else #ifndef __STANDALONE__
    sGeometry = *apGeom;
  } // if apGeom not null
  else
  {
    VDB_LOG_ERROR("Geometry structure is NULL.\n");
    lRet = CSI_LIB_FAILURE;
  } // else from if apGeom not null 
  
  return lRet;
} // SONY_GeometrySet()

//*****************************************************************************

CSI_LIB_RESULT SONY_CsiEnable(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_START, aCsiIdx)) < 0) 
    {
      VDB_LOG_ERROR("Failed to start Sony camera CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_CsiEnable(aCsiIdx);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SONY_CsiEnable(enum CSI_IDX aCsiIdx)

//*****************************************************************************

CSI_LIB_RESULT SONY_CsiDisable(enum CSI_IDX aCsiIdx)
{
  CSI_LIB_RESULT lRet = CSI_LIB_SUCCESS;

#ifndef __STANDALONE__   
    int32_t lRetVal = 0;
    if ((lRetVal = ioctl(gCsiFD, IOCTL_SONY_STOP, aCsiIdx)) < 0) 
    {
      VDB_LOG_ERROR("Failed to stop Sony camera CSI interface.\n");
      lRet = CSI_LIB_FAILURE;
    } // if ioctl returned failure
  
#else // #ifndef __STANDALONE__
    SONY_DRV_CsiDisable(aCsiIdx);
#endif // else #ifndef __STANDALONE__
  
  return lRet;
} // SONY_CsiDisable(enum CSI_IDX aCsiIdx)

//*****************************************************************************

float SONY_HistogramEnergyRelativ(SEQ_IpuHist_t *apHist)
{
  uint64_t lEnergy = 0;
  uint32_t lSum    = 0; 
  
  for(uint32_t i = HIST_GREEN_START; i < HIST_GREEN_STOP; i++)
  {
    lEnergy += apHist->mpData[i] * (i - HIST_GREEN_START);
    lSum    += apHist->mpData[i];
  }
  
  return (lEnergy/((float)lSum * (HIST_GREEN_STOP - HIST_GREEN_START)));
} // SONY_HistogramEnergyRelativ

//***************************************************************************

void SONY_ExposureControlOver(SEQ_IpuHist_t *apHist, uint32_t aOverExpPixCnt)
{
  SONY_ExposureControlOver(apHist, aOverExpPixCnt, 32, 0);
} // SONY_ExposureControlOver

//***************************************************************************

void SONY_ExposureControlOver(SEQ_IpuHist_t *apHist,
			      uint32_t aOverExpPixCnt, uint32_t aOverExpLevel,
			      uint32_t *aExp)
{
  uint16_t lIndex        = HIST_START_IDX;
  int16_t  lIndexStop    = 0;
  uint32_t lSumLev       = 0;
  uint32_t lSum          = 0;
  uint32_t lExposure     = SONY_EXP_100_CHNG;

  aOverExpLevel+=HIST_STOP_IDX;
  if (aOverExpLevel>HIST_START_IDX) aOverExpLevel=HIST_START_IDX;
  if (aOverExpLevel<HIST_STOP_IDX) aOverExpLevel=HIST_STOP_IDX;
  
  // lSumLev is computed
  while (lIndex >= aOverExpLevel)
  {        
    if (lSum <  aOverExpPixCnt) {
      lSum += apHist->mpData[lIndex];
      lIndexStop = lIndex;
    }
    lSumLev += apHist->mpData[lIndex--];
  }

  // overexposed level is reached
  while ((lIndex >= HIST_STOP_IDX) && 
          (lSum < aOverExpPixCnt)) 
  {

    lSum += apHist->mpData[lIndex--];
    lIndexStop = lIndex;
  }

  lIndexStop -= HIST_STOP_IDX;
  if (lIndexStop < 1) 
  {
    lIndexStop = 1;
  }
  
  
  if (lIndexStop >= (aOverExpLevel-HIST_STOP_IDX)) 
  {
    if (lSumLev > 2*aOverExpPixCnt)            
    {     
      // (x 3/4)
      lExposure = (SONY_EXP_100_CHNG*96) >> 7;   
    } // if 2x too muany
    else if (lSumLev > ((3*aOverExpPixCnt)>>1))     
    {  
      // (x 7/8)
      lExposure = (SONY_EXP_100_CHNG*112)>>7;   
    } // if 1,5x too many
    else if (lSumLev > ((5*aOverExpPixCnt)>>2))     
    {  
      // (x 15/16)
      lExposure = (SONY_EXP_100_CHNG*120)>>7;   
    } // if 1,25 too many
    else if (lSumLev > ((9*aOverExpPixCnt)>>3))    
    {  
      // (x 31/32)
      lExposure = (SONY_EXP_100_CHNG*124)>>7;   
    } // if 1,125 too many
  } // too many overexposed pixels
  else 
  {
    aOverExpLevel-=HIST_STOP_IDX;
    lExposure += ((SONY_EXP_100_CHNG << 10)*
		  (aOverExpLevel - lIndexStop)/(aOverExpLevel)) >> 13;    
  } // else form if too many overexposed pixels
  
  if (aExp)
  {
      *aExp=lExposure;
  }
  else if(lExposure != SONY_EXP_100_CHNG)
  {
    // apply exposure change
    SONY_ExposureSet(CSI_IDX_0, lExposure);
  } // if exposure change required
} // SONY_ExposureControlOver

//***************************************************************************

void SONY_ExposureControlEqual(SEQ_IpuHist_t *apHist, float aOffset)
{ 
  SONY_ExposureControlEqual(apHist, aOffset, 0);
} // SONY_ExposureControl()

//***************************************************************************

void SONY_ExposureControlEqual(SEQ_IpuHist_t *apHist, float aOffset,
			      uint32_t *aExp)
{ 
  if(apHist != NULL)
  {
    if(aOffset > 0.5)
    {
      aOffset = 0.5;
    }
    if(aOffset < -0.5)
    {
      aOffset = -0.5;
    }
    
    float lRelEnergy = SONY_HistogramEnergyRelativ(apHist);
#if (EXP_DEBUG > 0)    
    if(sExpRecIdx < EXP_DEBUG)
    {
      spHistEnergy[sExpRecIdx] = lRelEnergy;
    }
#endif // #if (EXP_DEBUG > 0)
    
    lRelEnergy = (0.5 + aOffset - lRelEnergy) * 0.5;

    if (aExp)
    {
      *aExp=SONY_EXP_100_CHNG + lRelEnergy * SONY_EXP_100_CHNG;
    }
    else
    {  
      SONY_ExposureSet(CSI_IDX_0, SONY_EXP_100_CHNG + lRelEnergy * SONY_EXP_100_CHNG);
    }
  } // if histogram not NULL
} // SONY_ExposureControl()

//***************************************************************************

// 6 bit + 2 to reach 8.8 Multiplier in IPU kernel
#define _ChGainFractionalBits_ 6
  
void SONY_ChGainMeasure(SEQ_IpuHist_t *apHist,
                        uint32_t PixCntLevel,
                        SONY_ChGain_t *aChGain)
{
  uint32_t lSum;
  uint32_t lNextSum;
  uint16_t lLevel;
  uint16_t *lpLevel;
  uint8_t  lIndex;
  uint8_t  lIndexStop;
  uint8_t  lChannel;

  aChGain->mMax=0;
  aChGain->mMin=(64<<6)-1;

  if (!aChGain) 
  {
    return;
  } // if achGain not NULL
  
  for (lChannel=0; lChannel < 4; lChannel++) 
  {
    lpLevel=&aChGain->mLevel[lChannel];

    lLevel=0;
    lIndexStop=lChannel<<6;
    lNextSum=lSum=0;
    for (lIndex=lIndexStop+63; lIndex>=lIndexStop; lIndex--) 
    {
      lNextSum+=apHist->mpData[lIndex];
      if (lNextSum>PixCntLevel) 
      {
        // linear interpolation for higher precision
        *lpLevel=
          ((lIndex-1-(lChannel<<6))<<_ChGainFractionalBits_) +
          (((PixCntLevel-lSum)<<_ChGainFractionalBits_)+((lNextSum-lSum)<<1))/
          (lNextSum-lSum);
        // for checking range
        if (aChGain->mMax<*lpLevel) aChGain->mMax=*lpLevel;
        if (aChGain->mMin>*lpLevel) aChGain->mMin=*lpLevel;
        break;  // next channel
      } // if (lNextSum>PixCntLevel) 
      else 
      {
        lSum=lNextSum;
      } //else from if (lNextSum>PixCntLevel) 
      if(lIndex == 0)
      {
        break;
      }
    } // for index range
  } // for all channels

  return;
  
} // SONY_ChGainMeasure

//***************************************************************************

/*EOF*/
