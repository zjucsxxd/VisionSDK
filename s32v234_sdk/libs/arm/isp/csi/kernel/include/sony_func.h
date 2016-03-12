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
 * \file    sony_func.hpp
 * \brief   Sony IMX224MQV MIPI/CSI camera functionality declaration.
 * \author  Tomas Babinec
 * \version 0.1
 * \date    31-August-2015
 ****************************************************************************/

#ifndef SONY_FUNC_HPP_
#define SONY_FUNC_HPP_

#include "config.h"
#include "csi_types.h"
#include "sony_types.h"

#ifdef __cplusplus 
extern "C" { 
#endif

//****************************************************************************
// contant definitions
//****************************************************************************
#define SONY_FAILURE 1
#define SONY_SUCCESS 0  

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Configures Sony camera driver.
 * 
 * 
 ****************************************************************************/
int32_t SONY_DRV_Setup(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Configures Sony camera register.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void SONY_DRV_RegConfig(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Enables CSI output from Sony camera.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void SONY_DRV_CsiEnable(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Disables CSI output from Sony camera.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 ****************************************************************************/
void SONY_DRV_CsiDisable(enum CSI_IDX aCsiIdx);

// *** EXPOSURE CONTROL ***

/****************************************************************************/
/** Reads current setup of the conversion gain.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apConv  pointer to Converersion variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ConvGet(enum CSI_IDX aCsiIdx, uint8_t* apConv);

/****************************************************************************/
/** Sets the conversion gain to low.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ConvLowSet(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Sets the confersion gain to high.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ConvHighSet(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Sets the exposure control update rate in frames
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param anUpdateRate gives how many frames are skipped between exposure calculations
 *         a value of 0 means excposure values are recomputed every frame
 *         to enable the exposure control the application needs to set that value
 *         to disable the exposure control the application needs to set that valu to -1 (default)
 *
 * \return the newly set value
 ****************************************************************************/
int32_t SONY_DRV_ExposureEnable(enum CSI_IDX aCsiIdx,int32_t anUpdateRate);
// anUpdateRate is indication how many frames are skipped for the exposure control
// to disable the exposure control set a value of -1
// -1 is the default value, so the application needs to set that value

/****************************************************************************/
/** Reads current setup of the exposure line count.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpLines pointer to expline variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ExpLinesGet(enum CSI_IDX aCsiIdx, uint32_t* apExplines);

#ifdef CAM_SONY_DOL
/****************************************************************************/
/** Reads current setup of the exposure line count of short exposure.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpLines pointer to expline variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ExpLinesSGet(enum CSI_IDX aCsiIdx, uint32_t* apExplines);
#endif

/****************************************************************************/
/** Sets up the exposure line count.
 * 
 * The provided line count can be modified to fit the possible range.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aLineCnt exposure time in number of lines 
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ExpLinesSet(enum CSI_IDX aCsiIdx, uint32_t aLineCnt);

/****************************************************************************/
/** Reads current setup of the analog gain.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apGain  pointer to gain variable in dB*10
 *
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_GainGet(enum CSI_IDX aCsiIdx, uint32_t* apGain);

/****************************************************************************/
/** Sets up the analog gain.
 * 
 * The provided analog gained can be adjusted to fit the allowed range.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aGain   analog gain in dB*10 to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_GainSet(enum CSI_IDX aCsiIdx, uint32_t aGain);

/****************************************************************************/
/** Adjusts the exposure based on the IPU histogram.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apHist  IPU histogram from SEQ driver
 * 
 * \return newly set exposure time in number of lines
 ****************************************************************************/
uint32_t SONY_DRV_ExpControl(enum CSI_IDX aCsiIdx, uint32_t *apHist);

// *** GEOMETRY CONFIG ***

/****************************************************************************/
/** Gets the optical black number of lines per frame.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apLineCnt pointer to line count variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ObWvGet(enum CSI_IDX aCsiIdx, uint8_t* apLineCnt);

/****************************************************************************/
/** Sets the optical black number of lines per frame.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param sLineCnt number of lines to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ObWvSet(enum CSI_IDX aCsiIdx, uint8_t aLineCnt);

/****************************************************************************/
/** Gets the maximum number of lines per frame.
 * 
 * The actual number of lines depends on cropping setup.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apVmax  pointer to VMAX variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_VmaxGet(enum CSI_IDX aCsiIdx, uint32_t* apVmax);

/****************************************************************************/
/** Sets the maximum number of lines per frame.
 * 
 * The actual number of lines depends on cropping setup.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param sLineCnt number of lines to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_VmaxSet(enum CSI_IDX aCsiIdx, uint32_t aLineCnt);

/****************************************************************************/
/** Gets the maximum number of columns per frame.
 * 
 * The actual number of columns depends on cropping setup.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apHmax  pointer to HMAX variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_HmaxGet(enum CSI_IDX aCsiIdx, uint32_t* apHmax);

/****************************************************************************/
/** Sets the maximum number of columns per frame.
 * 
 * The actual number of lines depends on cropping setup.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aColCnt number of columns to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_HmaxSet(enum CSI_IDX aCsiIdx, uint32_t aColCnt);

/****************************************************************************/
/** Gets the crop window number of lines per frame.
 * 
 * The actual number of lines depends on cropping setup.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apHeight pointer to height variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropWvGet(enum CSI_IDX aCsiIdx, uint32_t* apHeight);

/****************************************************************************/
/** Sets the crop window number of lines per frame.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param sLineCnt number of lines to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropWvSet(enum CSI_IDX aCsiIdx, uint32_t aHeight);

/****************************************************************************/
/** Gets the crop window number of columns per frame.
 *
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apWidth pointer to width variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropWhGet(enum CSI_IDX aCsiIdx, uint32_t* apWidth);

/****************************************************************************/
/** Sets the crop window number of lines per frame.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aWidth number of columns to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropWhSet(enum CSI_IDX aCsiIdx, uint32_t aWidth);

/****************************************************************************/
/** Gets the crop window y offset.
 *
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apXoff pointer to y offset variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropPvGet(enum CSI_IDX aCsiIdx, uint32_t* apYoff);

/****************************************************************************/
/** Sets the crop window y offset.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aYoff y offset to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropPvSet(enum CSI_IDX aCsiIdx, uint32_t aYoff);

/****************************************************************************/
/** Gets the crop window x offset.
 *
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apXoff pointer to X offset variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropPhGet(enum CSI_IDX aCsiIdx, uint32_t* apXoff);

/****************************************************************************/
/** Sets the crop window x offset.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aXoff X offset variable to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_CropPhSet(enum CSI_IDX aCsiIdx, uint32_t aXoff);

/****************************************************************************/
/** Gets the window mode register value.
 *
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apWinmode pointer to winmode variable
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_WinmodeGet(enum CSI_IDX aCsiIdx, uint8_t* apWinmode);

/****************************************************************************/
/** Sets the window mode register value.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param aWinmode winmode register value to be set
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_WinmodeSet(enum CSI_IDX aCsiIdx, uint8_t aWinmode);

/****************************************************************************/
/** Gets the camera exposure setup.
 *
 * Reads values over i2c from camera module.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpo  pointer to structure to be filled with exposure settings
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ExposureGet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo);

/****************************************************************************/
/** Sets the camera exposure values.
 *
 * Writes values over i2c to camera module. Provided values can be updated to 
 * fit camera requirements. Updated values available on return.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apExpo  pointer to exoposure structure 
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_ExposureSet(enum CSI_IDX aCsiIdx, SONY_Exposure_t *apExpo);

void SONY_DRV_IrqHandler(enum CSI_IDX aCsiIdx, uint32_t aIrqType);

SONY_ExpState_t SONY_DRV_ExpStateGet(enum CSI_IDX aCsiIdx);

int32_t SONY_DRV_ExposureApply(enum CSI_IDX aCsiIdx);

/****************************************************************************/
/** Gets the camera geometry.
 *
 * Reads values over i2c from camera module.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apGeom  pointer to structure to be filled with geometry
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_GeometryGet(enum CSI_IDX aCsiIdx, SONY_Geometry_t *apGeom);

/****************************************************************************/
/** Sets the camera geometry.
 *
 * Writes values over i2c to camera module. Provided values can be updated to 
 * fit camera requirements. Updated values available on return.
 * 
 * \param aCsiIdx CSI interface index the camera is connected to.
 * \param apGeom  pointer to structure to be filled with geometry
 * 
 * \return SONY_DRV_SUCCESS if all ok
 *         SONY_DRV_FAILURE otherwise
 ****************************************************************************/
int32_t SONY_DRV_GeometrySet(enum CSI_IDX aCsiIdx, SONY_Geometry_t* apGeom);


#ifdef __cplusplus 
} //extern "C" 
#endif

#endif // SONY_FUNC_HPP_ 
