/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
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
* \file 		sdi_types.hpp
* \brief 		Types types definition.
* \author 	Tomas Babinec
* \version 	0.1
* \date 		17-September-2013
****************************************************************************/

#ifndef SDI_TYPES_HPP_
#define SDI_TYPES_HPP_

#include "global_errors.h"
#include "gdi_image.hpp"
#include "csi_types.h"

/*****************************************************************************
* defines
*****************************************************************************/

//#define SDI_MAX_OUTPUT_CNT 5  ///< maximum allowed number of simultaneous outputs
#define SDI_SENSOR_CNT 4      ///< number off supported sensors
#define SDI_MAX_CLIENT_NUM 10 ///< maxim number of clients for SDI

/*****************************************************************************
* enums
*****************************************************************************/

/***************************************************************************/
/** Enumeration of supported sensors.
 *
 ***************************************************************************/

enum SDI_SENSOR
{
  SDI_SENSOR_INVALID = 0, ///!< SDI_SENSOR_INVALID
  SDI_SENSOR_CAM1,        ///!< SDI_SENSOR_CAM1
  SDI_SENSOR_CAM2,        ///!< SDI_SENSOR_CAM2
  SDI_SENSOR_ETH1,        ///!< SDI_SENSOR_ETH1
  SDI_SENSOR_ETH2         ///!< SDI_SENSOR_ETH2
}; // SDI_SENSOR

/***************************************************************************/
/** Enumeration of possible SDI parameters.
 *
 * \note For both input&output.
 * Entries borrowed from Monitor1.
 *
 ***************************************************************************/
enum SDI_IO_PARAM
{
  SDI_IO_PARAM_INVALID,       //!< SDI_IO_PARAM_INVALID
  SDI_IO_PARAM_DDR_BUF_LIST,  //!< list of DDR buffers
  SDI_IO_PARAM_SRAM_BUF,
  SDI_IO_PARAM_AE_LOCK,       //!< SDI_IO_PARAM_AE_LOCK
  SDI_IO_PARAM_AUTOFOCUS,     //!< SDI_IO_PARAM_AUTOFOCUS
  SDI_IO_PARAM_AWB_LOCK,      //!< SDI_IO_PARAM_AWB_LOCK
  SDI_IO_PARAM_EFFECT,        //!< SDI_IO_PARAM_EFFECT
  SDI_IO_PARAM_ESD_STATUS,    //!< SDI_IO_PARAM_ESD_STATUS
  SDI_IO_PARAM_EXPOSURE,      //!< SDI_IO_PARAM_EXPOSURE
  SDI_IO_PARAM_FACE_DETECTION,//!< SDI_IO_PARAM_FACE_DETECTION
  SDI_IO_PARAM_FLICKER_MODE,  //!< SDI_IO_PARAM_FLICKER_MODE
  SDI_IO_PARAM_ILLUMINANCE,   //!< SDI_IO_PARAM_ILLUMINANCE
  SDI_IO_PARAM_MACRO,         //!< SDI_IO_PARAM_MACRO
  SDI_IO_PARAM_SATURATION,    //!< SDI_IO_PARAM_SATURATION
  SDI_IO_PARAM_SCENE_MODE,    //!< SDI_IO_PARAM_SCENE_MODE
  SDI_IO_PARAM_SHARPNESS,     //!< SDI_IO_PARAM_SHARPNESS
  SDI_IO_PARAM_SPOT,          //!< SDI_IO_PARAM_SPOT
  SDI_IO_PARAM_STABILIZATION, //!< SDI_IO_PARAM_STABILIZATION
  SDI_IO_PARAM_STROBE,        //!< SDI_IO_PARAM_STROBE
  SDI_IO_PARAM_STROBE_MODE,   //!< SDI_IO_PARAM_STROBE_MODE
  SDI_IO_PARAM_WDR,           //!< SDI_IO_PARAM_WDR
  SDI_IO_PARAM_WHITE_BALANCE, //!< SDI_IO_PARAM_WHITE_BALANCE
  SDI_IO_PARAM_INPUT_SOURCE,  //!< SDI_IO_PARAM_INPUT_SOURCE
  SDI_IO_PARAM_FRAME_RATE,    //!< SDI_IO_PARAM_FRAME_RATE
  SDI_IO_PARAM_MIRROR,        //!< SDI_IO_PARAM_MIRROR
  SDI_IO_PARAM_LAST           ///< last parameter in the list
}; // SDI_IO_PARAM

/***************************************************************************/
/** Enumeration of possible SDI preprocessing steps.
 *
 * \note For both input&output.
 * Entries borrowed from Monitor1.
 */
enum SDI_IO_PROCESS
{
  SDI_PROCESS_NONE          , ///< None
  SDI_PROCESS_GRAYSCALE     , ///< Grayscale
  SDI_PROCESS_NEGATIVE      , ///< Negative
  SDI_PROCESS_SKETCH        , ///< Sketch
  SDI_PROCESS_SEPIA         , ///< Sepia
  SDI_PROCESS_EMBOSS        , ///< Emboss
  SDI_PROCESS_BLUE          , ///< Blue
  SDI_PROCESS_BW            , ///< Black/White
  SDI_PROCESS_ORANGE        , ///< Orange
  SDI_PROCESS_GREEN         , ///< Green
  SDI_PROCESS_AQUA          , ///< Aqua
  SDI_PROCESS_ANTIQUE       , ///< Antique
  SDI_PROCESS_MOONLIGHT     , ///< Moon light
  SDI_PROCESS_CONTRAST      , ///< Contrast
  SDI_PROCESS_COOL          , ///< Cool
  SDI_PROCESS_VIOLET        , ///< Violet
  SDI_PROCESS_EDGE_DETECTION, ///< Edge Detection
  SDI_PROCESS_SOLARIZE      , ///< Solarize
  SDI_PROCESS_WATERCOLOR    , ///< Water color
  SDI_PROCESS_NOISEREDUCTION, ///< Noise reduction
  SDI_PROCESS_YELLOW        , ///< Yellow
  SDI_PROCESS_NIGHT         , ///< Night
  SDI_PROCESS_RED           , ///< Red
  SDI_PROCESS_PINK          , ///< Pink
  SDI_PROCESS_PURPLE        , ///< Purple
  SDI_PROCESS_OUTLINE,        ///< Outline
  SDI_PROCESS_ALL,            ///< all PROCESSs passed as structure in the mpValue of ParameterSet();
}; // SDI_IO_PROCESS

//*****************************************************************************

enum SDI_RESULT
{
  SDI_SUCCESS = LIB_SUCCESS,  ///< everything went ok
  SDI_FAILURE = LIB_FAILURE,  ///< something failed (general information)
  SDI_NOT_ENOUGH_RESOURCES,   ///< SDI has not enough resources to support this requirement
  SDI_GRABBER_NOT_READY,      ///< grabber is not ready for requested operation
}; // SDI_RESULT

//*****************************************************************************

struct SDI_DdrBuffList
{
  uint32_t mIdx;              ///< current index in the list
  uint32_t mCnt;              ///< number of buffers in the list
  GDI_Image** mppBufs;        ///< pointer to the buffer array
}; // SDI_DdrBufList

//*****************************************************************************

struct SDI_MipiVcDescriptor
{
  uint32_t mBufAddr;          ///< SRAM buffer address
  uint32_t mLineCnt;          ///< number of lines fitting into buffer
  uint32_t mLineBytes;        ///< number of bytes per line
  uint32_t mLineStride;       ///< number of bytes to next line begin
}; // SDI_MipiVcDescriptor_t; 

//*****************************************************************************

struct SDI_MipiDescriptor
{
  enum CSI_IDX            mIdx;      ///< Mipi CSI index;
  SDI_MipiVcDescriptor    mpVc[4];   ///< VC config
}; // SDI_MipiDescriptor_t;

//*****************************************************************************

#endif // SDI_TYPES_HPP_ 
