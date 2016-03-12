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
 
 /* Information for doxygen */
/**
 *  \file   GlobalTypes.h
 *  \brief  Global types
 *
 */
#ifndef GLOBALTYPES_H 
#define GLOBALTYPES_H

// signed integer types
typedef signed char      sint8;
typedef signed short int sint16;
typedef signed long int  sint32;
typedef signed int       sint;
typedef long long        int64;
typedef long long        sint64;

// unsigned integer types
typedef unsigned int     uint;

// Define ATD_SAMSUNG_TYPES_COMPATIBLE in the makefile/project file if the existing
// system headers do define the following data types

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned long int  uint32;
typedef unsigned long long uint64;

// For backwards compatibility
#include <stdbool.h>

#define FALSE 0
#define TRUE  1

// Current Definition:
typedef uint32 LIB_BOOL;

#define LIB_FALSE 0
#define LIB_TRUE  1


// Some useful Macros. If the target system headers already define these
// macros, those definitions will override the ones below
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef NULL
#define NULL 0
#endif



typedef struct ATVD_PERF_RESULT
{
	float 			  frame_rate;
	unsigned long 	  memory_leak; 
} PERF_RESULT;

typedef enum
{
   LIB_ALPHA_BACKGROUND,
   LIB_ALPHA_1,
   LIB_ALPHA_2,
   LIB_ALPHA_3,
   LIB_ALPHA_4,
   LIB_ALPHA_5,
   LIB_ALPHA_6,
   LIB_ALPHA_7,
   LIB_ALPHA_FOREGROUND
} LIB_ALPHA;

typedef enum
{
   LIB_FLASH_AUTO = 1,
   LIB_FLASH_ON   = 2,
   LIB_FLASH_OFF       = 3,
   LIB_FLASH_TORCH_ON  = 4,
   LIB_FLASH_TORCH_OFF = 5
} LIB_FLASH;

typedef enum
{
   LIB_AF_OFF,
   LIB_AF_ON
} LIB_AF;

typedef enum
{
    LIB_OPTICAL_ZOOM_STEP_0,
    LIB_OPTICAL_ZOOM_STEP_1,
    LIB_OPTICAL_ZOOM_STEP_2,
    LIB_OPTICAL_ZOOM_STEP_3,
    LIB_OPTICAL_ZOOM_STEP_4,
    LIB_OPTICAL_ZOOM_STEP_5,
    LIB_OPTICAL_ZOOM_STEP_6,
    LIB_OPTICAL_ZOOM_STEP_7,
    LIB_OPTICAL_ZOOM_STEP_8,
    LIB_DIGITAL_ZOOM_STEP_1,
    LIB_DIGITAL_ZOOM_STEP_2,
    LIB_DIGITAL_ZOOM_STEP_3,
    LIB_DIGITAL_ZOOM_STEP_4,
    LIB_DIGITAL_ZOOM_RELEASE
} LIB_OPTICAL_ZOOM_STEP;

typedef enum
{
    LIB_LINEAR_ZOOM_TELE,
    LIB_LINEAR_ZOOM_WIDE,
    LIB_LINEAR_ZOOM_FIX
}LIB_LINEAR_ZOOM_STEP;


/**
 * \brief LIB_ROTATION
 *
 */
typedef enum {
   LIB_ROTATION_NONE     = 0,  ///< Don't rotate.
   LIB_ROTATION_MIRROR   = 1,  ///< flip by x co-ordinate.
   LIB_ROTATION_VERTICAL = 2,  ///< flip by y co-ordinate.
   LIB_ROTATION_90       = 3,  ///< rotate clockwise 90 degree.
   LIB_ROTATION_180      = 4,  ///< rotate clockwise 180 degree.
   LIB_ROTATION_270      = 5   ///<rotate clockwise 270 degree.
} LIB_ROTATION;


/**
 * \brief LIB_ORIENTATION
 *
 */
typedef enum {
   LIB_ORIENTATION_NONE            = 0,     ///<  No orientation change from default
   LIB_ORIENTATION_ROTATE_90       = 1,     ///< 90 degree clockwise orientation.
   LIB_ORIENTATION_ROTATE_180      = 2,     ///< 180 degree clockwise orientation.
   LIB_ORIENTATION_ROTATE_270      = 3,     ///< 270 degree clockwise orientation.
   LIB_ORIENTATION_MIRROR          = 0x10,  ///< Left - Right Horizontal Mirror from original
   LIB_ORIENTATION_VERTICAL        = 0x20,  ///< Up - Down Vertical Mirror from original
   LIB_ORIENTATION_MIRROR_VERTICAL = 0x30   ///< Horizontal and Vertical Mirror from original
} LIB_ORIENTATION;

typedef struct {
   unsigned short    width;  ///< width
   unsigned short    height; ///< height
} LIB_DIM;

typedef struct {
   unsigned int    width;
   unsigned int    height;
} LIB_BIG_DIM;

typedef enum {
   LIB_FILTER_INVALID,
   LIB_FILTER_NONE,
   LIB_FILTER_3x3,
   LIB_FILTER_LPF
} LIB_FILTER;

/**
 * \brief LIB Effect
 *
 */
typedef enum
{
    LIB_EFFECT_NONE          , ///< None
    LIB_EFFECT_GRAYSCALE     , ///< Grayscale
    LIB_EFFECT_NEGATIVE      , ///< Negative
    LIB_EFFECT_SKETCH        , ///< Sketch    
    LIB_EFFECT_SEPIA         , ///< Sepia
    LIB_EFFECT_EMBOSS        , ///< Emboss
    LIB_EFFECT_BLUE          , ///< Blue
    LIB_EFFECT_BW            , ///< Black/White
    LIB_EFFECT_ORANGE        , ///< Orange
    LIB_EFFECT_GREEN         , ///< Green
    LIB_EFFECT_AQUA          , ///< Aqua
    LIB_EFFECT_ANTIQUE       , ///< Antique
    LIB_EFFECT_MOONLIGHT     , ///< Moon light
    LIB_EFFECT_CONTRAST      , ///< Contrast 
    LIB_EFFECT_COOL          , ///< Cool
    LIB_EFFECT_VIOLET        , ///< Violet
    LIB_EFFECT_EDGE_DETECTION, ///< Edge Detection
    LIB_EFFECT_SOLARIZE      , ///< Solarize
    LIB_EFFECT_WATERCOLOR    , ///< Water color
    LIB_EFFECT_NOISEREDUCTION, ///< Noise reduction
    LIB_EFFECT_YELLOW        , ///< Yellow
    LIB_EFFECT_NIGHT         , ///< Night
    LIB_EFFECT_RED           , ///< Red
    LIB_EFFECT_PINK          , ///< Pink
    LIB_EFFECT_PURPLE        , ///< Purple
    LIB_EFFECT_OUTLINE         ///< Outline
} LIB_EFFECT;

/**
 * \brief LIB ISO mode
 *
 */
typedef enum
{
   LIB_ISO_MODE_AUTO  = 0, ///< Auto
   LIB_ISO_MODE_50    = 1, ///< 50
   LIB_ISO_MODE_100   = 2, ///< 100
   LIB_ISO_MODE_200   = 3, ///< 200
   LIB_ISO_MODE_400   = 4, ///< 400
   LIB_ISO_MODE_800   = 5, ///< 800
   LIB_ISO_MODE_1000  = 6, ///< 1000
   LIB_ISO_MODE_1600  = 7, ///< 1600
   LIB_ISO_MODE_3200  = 8  ///< 3200
} LIB_ISO_MODE;

/**
 * \brief LIB Environment
 *
 */
typedef enum
{
   LIB_ENVIRONMENT_AUTO,              ///< Auto
   LIB_ENVIRONMENT_SUNLIGHT,          ///< Sunlight
   LIB_ENVIRONMENT_CLOUDY,            ///< Cloudy
   LIB_ENVIRONMENT_INCANDESCENT,      ///< Incandescent
   LIB_ENVIRONMENT_FLUORESCENT_LIGHT, ///< Fluorescent light
   LIB_ENVIRONMENT_DAYLIGHT_WHITE,    ///< Daylight white
   LIB_ENVIRONMENT_DAYLIGHT_WHITE_AAA,///< Daylight white AAA
   LIB_ENVIRONMENT_FLUORESCENT_BULB,  ///< Fluorescent bulb
   LIB_ENVIRONMENT_FLUORESCENT_COOL,  ///< Fluorescent cool
   LIB_ENVIRONMENT_FLUORESCENT_WARM,  ///< Fluorescent warm
   LIB_ENVIRONMENT_WHITE_LIGHT,       ///< White light
   LIB_ENVIRONMENT_HALOGEN,           ///< Halogen
   LIB_ENVIRONMENT_NIGHT_ON,          ///< Night on
   LIB_ENVIRONMENT_NIGHT_OFF,         ///< Ngith off
   LIB_ENVIRONMENT_SHADE,             ///< Shade
   LIB_ENVIRONMENT_HORIZON,           ///< Horizon
   LIB_ENVIRONMENT_FLASH              ///< Flash
  
} LIB_ENVIRONMENT;


/**
 * \brief LIB_SHARPNESS
 *
 */
typedef enum
{
   LIB_SHARPNESS_MINUS_2, ///< Minus 2
   LIB_SHARPNESS_MINUS_1, ///< Minus 1
   LIB_SHARPNESS_DEFAULT, ///< Default
   LIB_SHARPNESS_PLUS_1,  ///< Plus 1
   LIB_SHARPNESS_PLUS_2   ///< Plus 2
} LIB_SHARPNESS;

/**
 * \brief LIB Contrast
 *
 */
typedef enum
{
   LIB_CONTRAST_MINUS_2, ///< Minus 2
   LIB_CONTRAST_MINUS_1, ///< Minus 1
   LIB_CONTRAST_DEFAULT, ///< Default
   LIB_CONTRAST_PLUS_1,  ///< Plus 1
   LIB_CONTRAST_PLUS_2   ///< Plus 2
} LIB_CONTRAST;

typedef enum
{
   LIB_ME_CENTERWEIGHTED,
   LIB_ME_SPOT,
   LIB_ME_MATRIX,
   LIB_METERING_EXPOSURE_ForceInt = 0x12345678
} LIB_METERING_EXPOSURE;

typedef enum
{
    LIB_SCENE_AUTO,
    LIB_SCENE_PORTRAIT,
    LIB_SCENE_LANDSCAPE,
    LIB_SCENE_SPORTS,
    LIB_SCENE_PARTY_INDOOR,
    LIB_SCENE_SUNSET,
    LIB_SCENE_DUSK_DAWN,
    LIB_SCENE_BACK_LIGHT,
    LIB_SCENE_BEACH_SNOW,
    LIB_SCENE_WAVE_SNOW,
    LIB_SCENE_AUTUMM_COLOR,
    LIB_SCENE_NIGHT_ON,
    LIB_SCENE_FIREWORK,
    LIB_SCENE_TEXT,
    LIB_SCENE_SNOW_WINDOW,
    LIB_SCENE_CANDLE_LIGHT
}LIB_SCENE_MODE;

typedef enum
{
   LIB_AF_ONESHOT,
   LIB_AF_CONTINUOUS,
   LIB_AF_SETMACRO,
   LIB_AF_STEP,
   LIB_AF_POSITION,
   LIB_AUTOFOCUS_ForceInt = 0x12345678
} LIB_AUTOFOCUS;

typedef enum
{
    LIB_STABILIZATION_OFF,
    LIB_STABILIZATION_ON
}LIB_STABILIZATION_SET;

typedef enum
{
    LIB_WDR_OFF,
    LIB_WDR_ON
}LIB_WDR_SET;

typedef enum
{
    LIB_FACEDETECTION_OFF,
    LIB_FACEDETECTION_ON,
    LIB_FACEDETECTION_WITHOUT_WINDOW,
    LIB_FACEDETECTION_RELEASE    
}LIB_FACEDETECTION_SET;

typedef enum
{
    LIB_MACRO_OFF,
    LIB_MACRO_ON,
    LIB_MACRO_INVALID
}LIB_MACRO_SET;

typedef enum
{
   LIB_SATURATION_MINUS_2,
   LIB_SATURATION_MINUS_1,
   LIB_SATURATION_DEFAULT,
   LIB_SATURATION_PLUS_1,
   LIB_SATURATION_PLUS_2
}LIB_SATURATION_SET;

typedef enum
{
   LIB_SPOT_OFF,
   LIB_SPOT_ON,
   LIB_SPOT_CENTER_WEIGHTED
}LIB_SPOT_SET;

typedef enum
{
    LIB_AF_NORMAL,
    LIB_AF_MACRO
}LIB_AF_SET;

typedef enum
{
    LIB_AE_LOCK,
    LIB_AE_UNLOCK
}LIB_AE_LOCK_CTRL;

typedef enum
{
    LIB_AWB_LOCK,
    LIB_AWB_UNLOCK
}LIB_AWB_LOCK_CTRL;

typedef enum
{
   LIB_AUTO_DETECT_MODE,
   LIB_50HZ_FLICKERLESS_MODE,
   LIB_60HZ_FLICKERLESS_MODE,
   LIB_50_60HZ_FLICKERLESS_MODE,
   LIB_NO_FLICKERLESS_MODE,
   LIB_AUTO_REDETECT_MODE   
} LIB_FLICKER_MODE;

typedef enum
{
   LIB_JPEG_COMPRESSION_NORMAL,
   LIB_JPEG_COMPRESSION_MEDIUM,
   LIB_JPEG_COMPRESSION_HIGH,
   LIB_JPEG_COMPRESSION_SUPER_HIGH
} LIB_JPEG_COMPRESSION_LEVEL;

typedef enum
{
    LIB_ADAPTIVE_LUMINANCE_OFF,
    LIB_ADAPTIVE_LUMINANCE_ON
} LIB_ADAPTIVE_LUMINANCE_SET;

typedef struct
{	
   unsigned int exposureTimeNumerator;
   unsigned int exposureTimeDenominator;

   int shutterSpeedNumerator;
   int shutterSpeedDenominator;
      
   unsigned int apertureNumerator;
   unsigned int apertureDenominator;

   int brightnessNumerator;
   int brightnessDenominator;

   int exposureBiasNumerator;
   int exposureBiasDenominator;

   unsigned short iso;
   unsigned short Flash;
   unsigned short q_factor;  
   unsigned char ispVersionMajor;
   unsigned char ispVersionMinor;
} LIB_ISP_EXIF_INFO;

typedef enum
{
   LIB_IMAGE_EXIF_ORIENTATION_ROW_TOP_COLUMN_LFT    = 0x00000001,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_TOP_COLUMN_RGT    = 0x00000002,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_BOT_COLUMN_RGT    = 0x00000003,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_BOT_COLUMN_LFT    = 0x00000004,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_LFT_COLUMN_TOP    = 0x00000005,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_RGT_COLUMN_TOP    = 0x00000006,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_RGT_COLUMN_BOT    = 0x00000007,
   LIB_IMAGE_EXIF_ORIENTATION_ROW_LFT_COLUMN_BOT    = 0x00000008
   
} LIB_IMAGE_EXIF_ORIENTATION;

typedef struct
{
   LIB_DIM                          jpgimagesize;
   LIB_IMAGE_EXIF_ORIENTATION	      orientation;
   char                             softwareversion[32];
   char                             modelName[32];
} LIB_IMAGE_EXIF_CONFIG;

// audio I2S interface control, from MMP side
typedef struct 
{
   LIB_BOOL bMclkDir;               // 0 - input (NCO disabled), 1 - output (NCO enabled)
   LIB_BOOL bClkxDir;               // 0 - input, 1 - output
   LIB_BOOL bClkrDir;               // 0 - input, 1 - output
   LIB_BOOL bFsxDir;                // 0 - input, 1 - output
   LIB_BOOL bFsrDir;                // 0 - input, 1 - output
   LIB_BOOL bTxDataDir;             // 0 - input (gpio[20]) , 1 - output (default)
   LIB_BOOL bRxDataDir;             // 0 - input (default) , 1 - output (gpio[17])
   LIB_BOOL bEnableTx;              // 0 - disable, 1- enable
   LIB_BOOL bEnableRx;              // 0 - disable, 1- enable
   LIB_BOOL bClkrSharing;           // 0 - unique, 1 - shared with transmit !!! opposite from chip specs !!!
   LIB_BOOL bFsrSharing;            // 0 - unique, 1 - shared with transmit
   
   LIB_BOOL bStereo;                // 0 - mono, 1 - stereo (this is rx direction only, stereo should be used), tx is always stereo
   LIB_BOOL bClkxPolarity;          // 0 - rising edge, 1 - falling edge
   LIB_BOOL bClkrPolarity;          // 0 - rising edge, 1 - falling edge
   LIB_BOOL bFsxPolarity;           // 0 - active high, 1 - active low
   LIB_BOOL bFsrPolarity;           // 0 - active high, 1 - active low
   
   unsigned int txClkDiv;           // typical value 4
   unsigned int rxClkDiv;           // typical value 4
   unsigned int txFramePeriod;      // typical value 64
   unsigned int rxFramePeriod;      // typical value 64
   unsigned int txFrameWidth;       // typical value 32
   unsigned int rxFrameWidth;       // typical value 32
   unsigned int txDataWordLength;   // typical value 16
   unsigned int rxDataWordLength;   // typical value 16
   unsigned int txDelay;            // typical value 0
   unsigned int rxDelay;            // typical value 0

   unsigned int txFifoSize;         // typical value 3
   unsigned int rxFifoSize;         // typical value 3   
}LIB_I2S_INTERFACE_CONFIGURATION;

typedef void * WINDOW_HANDLE;

typedef enum
{
   LIB_EVENT_NONE = 0,                 // A non-event
   LIB_EVENT_RESET,                    // The media processor has reset. 
   LIB_EVENT_READY,                    // The media processor is ready. 
   LIB_EVENT_TIMEOUT,                  // Timeout error has occurred. 
   LIB_EVENT_OUT_OF_MEMORY,            // Out of memory. 
   LIB_EVENT_CHANNEL_OVERFLOW,         // Channel overflow has occurred. 
   LIB_EVENT_CARD_INSERTION,           // Card insertion was detected. 
   LIB_EVENT_CARD_REMOVAL,             // Card removal was detected. 
   LIB_EVENT_IMAGE,                    // Image event.
   LIB_EVENT_MEDIAPLAYER,              // MediaPlayer event.
   LIB_EVENT_AUDIOPLAYER = 10,         // AudioPlayer event. 
   
   LIB_EVENT_TONEPLAYER,               // TonePlayer event. 
   LIB_EVENT_GMPLAYER,
   LIB_EVENT_MEDIARECORDER,            // Audio/Video decoder event. 
   LIB_EVENT_UNKNOWN_EVENT,            // Unknown event notification. 
   LIB_EVENT_FILE_IO_ERROR,            // A file I/O error occurred. 
   LIB_EVENT_FILE_DEVICE_FORMAT,       // File device format event. 
   LIB_EVENT_UNKNOWN_MESSAGE,          // An unknown message was received. 
   LIB_EVENT_CORRUPT_MESSAGE,          // A corrupt message was received. 
   LIB_EVENT_AUTOFOCUS,                // An auto focus event. 
   LIB_EVENT_SYSTEM_HEARTBEAT = 20,    // The media Processor system heartbeat event. 

   LIB_EVENT_NOT_OPERATIONAL,          // The media Processor is not responding. 
   LIB_EVENT_HEARTBEAT_MISSING,        // Have not received a heartbeat from the processor. 
   LIB_EVENT_DISK_SPACE_ERROR,         // A disk space error occured. 
   LIB_EVENT_SENSOR,                   // Something sensor related occured 
   LIB_EVENT_SOCKET,                   // Socket (Network interface) event 
   LIB_EVENT_MTP_SWITCH_TO_MODEM,      // MTP Mode -> MODEM(AT Command) Mode (MV_SOC4_JANGJH 060517)
   LIB_EVENT_MTP_MUSICINFO_TO_HOST,    // MTP Add and Delete Music File (MV_SOC4_JANGJH 060604)
   LIB_EVENT_MTP_SET_RTC,              // MTP Request Set RTC to B/B (MV_SOC4_JANGJH 060707)
   LIB_EVENT_SWERR,                    // Software Error
   LIB_EVENT_ESD_SENSOR_NOT_ALIVE = 30,// ESD sensor malfunction event

   LIB_EVENT_HOST_PORT_RECEIVE_FAILED, // Packet size is too big from receive port.
   LIB_EVENT_HOST_PORT_SEND_FAILED,    // Rxfifo doesn't response within assignd time.   
   
   LIB_EVENT_DRM_GET_KEY,
   LIB_EVENT_REQ_MTP_GET_TIME,         //MV_SOC4_JANGJH 060920
   LIB_EVENT_DVBH,
   LIB_EVENT_FILE_DELIVERY,
   LIB_EVENT_USB_CHARGER_ON,
   LIB_EVENT_USB_CHARGER_OFF,

   LIB_EVENT_PANORAMA,                  // Panorama event
   
   LIB_EVENT_IMAGESLIDE = 40,           // ImageSlide Event

   LIB_EVENT_MEDIAPLAYER_BC,            // Events for the new Media Player
   LIB_EVENT_TRANSCODER,                // Events for the Transcoder 
   LIB_EVENT_MEDIAEDITOR,               // Events for the Media Editor 
   LIB_EVENT_AUDIO_EFFECT_LM,  		    // Event for Audio effect level meter 
   LIB_EVENT_DISK_READY,                // Disk is ready for usage: only for SD/MMC
   LIB_EVENT_DISK_MOUNT_FAIL,           // Disk is Mount fail for usage: only for SD/MMC
   LIB_EVENT_DISK_NEED_FORMAT,			 // Disk is Need format for usage: only for SD/MMC
   LIB_EVENT_USB_DISCONNECTED,          // Events for USB Disconnected 
   LIB_EVENT_MEDIADEC,
   LIB_EVENT_MEDIAAUDIODEC = 50,
   LIB_EVENT_MTP_PLISTINFO_TO_HOST,     // MTP Add and Delete PlayList File 
   LIB_EVENT_MTP_STATE_TO_HOST,		    // JS Park MTP STATE To Host 
   LIB_EVENT_DATABASE,
   LIB_EVENT_UTIL_TO_HOST,	             // MTP Get Battery Level 
   LIB_EVENT_DISK_IO_ERROR,			    // Disk is IO_ERROR : only for SD/MMC -	KIMBC	2007.06.15	   
   LIB_EVENT_DISK_DRIVE_INIT_ERROR,     // Disk initialized never completes   
   LIB_EVENT_USER_KEY,             	    // User Key Event 2008.01.29 bnkim  
   LIB_EVENT_PANOMAX,                   // PanoramaMax event
   LIB_EVENT_FACESMILEDETECKT,			 // Face & Smile deteck event 
   LIB_EVENT_OPENVG = 60,
   LIB_EVENT_CAPTURE_FILE_SAVE_DONE,	 // Capture and File save done event 
   LIB_EVENT_NAND_DISK_IO_ERROR,			 // Disk is IO_ERROR : only for moviNand 
   LIB_EVENT_NAND_DISK_DRIVE_INIT_ERROR,// Disk initialized never completes. moviNand 
   LIB_EVENT_NAND_DISK_READY,           // Disk is ready for usage: only for moviNand 
   LIB_EVENT_NAND_DISK_MOUNT_FAIL,      // Disk is Mount fail for usage: only for moviNand 
   LIB_EVENT_NAND_DISK_NEED_FORMAT,		 // Disk is Need format for usage: only for moviNand 
   LIB_EVENT_SHUTTER_SOUND_ON,			 // FUJITSU M5Mo ISP Shutter sound event
   LIB_EVENT_SOUNDSTUDIO,
   LIB_EVENT_SECDVBPLAYER = 70          // SEC AV Player EVENT
} LIB_EVENT;


typedef enum
{
   LIB_BOX_EDGE_INVALID,
   LIB_BOX_EDGE_NONE,
   LIB_BOX_EDGE_TOP,
   LIB_BOX_EDGE_BOTTOM,
   LIB_BOX_EDGE_LEFT,
   LIB_BOX_EDGE_RIGHT
} LIB_BOX_EDGE;


typedef enum
{
   LIB_TEXT_ALIGN_INVALID,
   LIB_TEXT_ALIGN_NONE,
   LIB_TEXT_ALIGN_LEFT,
   LIB_TEXT_ALIGN_CENTER,
   LIB_TEXT_ALIGN_RIGHT
} LIB_TEXT_ALIGN;

typedef enum
{
    JOY_UP         = 0x01,
    JOY_DOWN       = 0x02,
    JOY_LEFT       = 0x04,
    JOY_RIGHT      = 0x08,

    JOY_SELECT            = 0x10,
    JOY_UP_SELECT         = 0x11,
    JOY_DOWN_SELECT       = 0x12,
    JOY_LEFT_SELECT       = 0x14,
    JOY_RIGHT_SELECT      = 0x18,

    JOY_SELECT2            = 0x20,
    JOY_DOWN_SELECT2       = 0x22,
    JOY_LEFT_SELECT2       = 0x24,
    JOY_RIGHT_SELECT2      = 0x28,

    JOY_NONE       = 0x00
} JOYSTICK_EVENT;


typedef enum
{
   TouchDown    =   0,
   TouchMove    =   1,
   TouchUp      =   2,
   TouchRelease =   9

} TouchEventCode;

#endif // GLOBALTYPES_H
