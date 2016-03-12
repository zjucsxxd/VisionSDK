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
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONCSIUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file     sony_public.h
* \brief    public declarations for Sony user space library
* \author   Tomas Babinec
* \version  0.1
* \date     03-November-2014
* \note
****************************************************************************/

#ifndef SONY_PUBLIC_H
#define SONY_PUBLIC_H

#include "config.h"
#include "csi.h"
#include "csi_public.h"
#include "sony_types.h"
#include "seq_types.h"

//*****************************************************************************
// constants
//*****************************************************************************

// *** SONY exposure control ***
#define SONY_EXP_MAX_CHNG          8192
#define SONY_EXP_100_MULTI         12
#define SONY_EXP_100_CHNG          (1 << SONY_EXP_100_MULTI)
#define SONY_EXP_AGAIN_DOUBLE      60
#define SONY_EXP_AGAIN_MAX         720
#ifdef CAM_SONY_DOL
#define SONY_EXP_CGAIN_UP_THRESH   (64 * 12) ///< threshold to switch to high ConvGain
#define SONY_EXP_CGAIN_DOWN_THRESH (64 * 2)  ///< threshold to switch to low ConvGain
#define SONY_EXP_AGAIN_UP_THRESH   ((sGeometry.mVmax - 1)*2)
#define SONY_EXP_AGAIN_DOWN_THRESH (((3 * sGeometry.mVmax) >> 3)*2)
#else
#define SONY_EXP_AGAIN_UP_THRESH   (sGeometry.mVmax - 1)
#define SONY_EXP_AGAIN_DOWN_THRESH ((3 * sGeometry.mVmax) >> 3)
#define SONY_EXP_CGAIN_UP_THRESH   (32 * 12) ///< threshold to switch to high ConvGain
#define SONY_EXP_CGAIN_DOWN_THRESH (32 * 2)  ///< threshold to switch to low ConvGain
#endif

//*****************************************************************************
// types
//*****************************************************************************

//*****************************************************************************
// public functionality declarations
//*****************************************************************************

/****************************************************************************/
/** Configures Sony camera registers.
* 
* \param apMessage[in] message to be sent
* 
* \return CSI_LIB_SUCCESS if all ok
*         CSI_LIB_FAILURE otherwise
*****************************************************************************/
CSI_LIB_RESULT SONY_RegConfig(enum CSI_IDX aCsiIdx);

CSI_LIB_RESULT SONY_ExposureStatusGet(enum CSI_IDX aCsiIdx, SONY_ExpState_t &arExpState);

/****************************************************************************/
/** Enables CSI transmission from Sony camera.
 * 
 * \param apGraphPackage packed graph structure
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI transmission from Sony camera.
* 
* \return CSI_LIB_SUCCESS if all ok, 
*         CSI_LIB_FAILURE otherwise
*****************************************************************************/
CSI_LIB_RESULT SONY_CsiDisable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Gets the camera exposure setup.
 *
 * Reads values over i2c from camera module.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpo  pointer to structure to be filled with exposure settings
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_ExposureGet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo);

/****************************************************************************/
/** Sets the camera exposure values.
 *
 * The single exposure value is split into exposure lines / conversion gain /
 * analog gain configuration and set over i2c to the sensor.
 * 
 * \param aCsiIdx    CSI interface index the camera is connected to.
 * \param aExposure  number defining the exposure level <0; SONY_EXP_MAX>
 *                   values higher than SONY_EXP_TIME_MAX use analog gain
 *                   config, which will increase level of noise in the image
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_ExposureSet(enum CSI_IDX aCsiIdx, uint32_t aExposure);

/****************************************************************************/
/** Sets the camera exposure values.
 *
 * Writes values over i2c to camera module. Provided values can be updated to 
 * fit camera requirements. Updated values available on return.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpo  pointer to exoposure structure 
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_ExposureSet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo);

/****************************************************************************/
/** Gets the camera geometry.
 *
 * Reads values over i2c from camera module.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apGeom  pointer to structure to be filled with geometry
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_GeometryGet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom);

/****************************************************************************/
/** Sets the camera geometry.
 *
 * Writes values over i2c to camera module. Provided values can be updated to 
 * fit camera requirements. Updated values available on return.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apGeom  pointer to structure to be filled with geometry
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT SONY_GeometrySet(enum CSI_IDX aCsiIdx, SONY_Geometry_t* apGeom);

/************************************************************************/
/** Contols exposure to achieve certain level of overexposed pixels.
  * 
  * \param  apHist   histogram data
  * \param  aOverExp number of pixel that should be overexposed
  ************************************************************************/
void SONY_ExposureControlOver(SEQ_IpuHist_t *apHist, uint32_t aOverExp);

/************************************************************************/
/** Contols exposure to achieve certain level of overexposed pixels.
  * 
  * \param  apHist         histogram data
  * \param  aOverExpPixCnt number of pixel that should be overexposed
  * \param  aOverExpLevel  level that should be treated as overexposed
  * \param  aExp           pointer to the new relative exposure update value
  *                        if 0 then the new value is updated automatically
  ************************************************************************/
void SONY_ExposureControlOver(SEQ_IpuHist_t *apHist,
			      uint32_t aOverExpPixCnt, uint32_t aOverExpLevel,
			      uint32_t *aExp);

/************************************************************************/
/** Contols exposure to achieve balanced brightnes.
  * 
  * \param  apHist   histogram data
  * \param  aOffset  offset from balanced brightnes <-0.5, 0.5>
  ************************************************************************/
void SONY_ExposureControlEqual(SEQ_IpuHist_t *apHist, float aOffset);

/************************************************************************/
/** Contols exposure to achieve balanced brightnes.
  * 
  * \param  apHist   histogram data
  * \param  aOffset  offset from balanced brightnes <-0.5, 0.5>
  * \param  aExp           pointer to the new relative exposure update value
  *                        if 0 then the new value is updated automatically
   ************************************************************************/
void SONY_ExposureControlEqual(SEQ_IpuHist_t *apHist, float aOffset,
			      uint32_t *aExp);

/************************************************************************/
/** Computes histogram energy divided by number of pixels.
  * 
  * \param  apHist   histogram data
  * 
  * \return  relative histogram energy <0.0, 1.0>
  ************************************************************************/
float SONY_HistogramEnergyRelativ(SEQ_IpuHist_t *apHist);

/************************************************************************/
/** Computes Channel Gain values from histograms.
  * 
  * \param  apHist         histogram data
  * \param  aPixCntLevel   pixel count that is measured in histogram
  *                        to measure sensitivity
  * \param  aChGain        resulting levels to reach pixel count in
  *                        histogram
  * 
  ************************************************************************/
void SONY_ChGainMeasure(SEQ_IpuHist_t *apHist,
                        uint32_t PixCntLevel,
                        SONY_ChGain_t *aChGain);

#endif // SONY_PUBLIC_H

/* EOF */