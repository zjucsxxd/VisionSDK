/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2013 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 *  Created by: Ramin Azarmehr
 ******************************************************************************/

/*!*********************************************************************************
*  @file
*  @brief General definitions and declarations (Standard C), for Vertical Resizer 
***********************************************************************************/

#ifndef _APU_RESIZE_DEFINITIONS_H_
#define _APU_RESIZE_DEFINITIONS_H_

#include <stdint.h>

#define RSZ_DECIMAL_SCL       16    /*!< Fixed-point scaler */
#define FLT_BANK_SIZE         32  /*!< Polyphase filter bank size  */



//! Filter banks
//! 8 Phases, 4 Taps
#define FLT_UP_SAMPLING {0 , 256,   0,   0,\
                        -11, 245,  23,  -1,\
                        -17, 220,  58,  -5,\
                        -18, 184, 100, -10,\
                        -15, 143, 143, -15,\
                        -10, 100, 184, -18,\
                         -5,  58, 220, -17,\
                         -1,  23, 245, -11}
//! 8 Phases, 4 Taps
#define FLT_DOWN_SAMPLING1 {28, 200,  28, 0,\
                            15, 194,  47, 0,\
                             7, 178,  71, 0,\
                             2, 156,  98, 0,\
                             0, 128, 128, 0,\
                             0,  98, 156, 2,\
                             0,  71, 178, 7,\
                             0,  47, 194, 15}
//! 4 Phases, 8 Taps
#define FLT_DOWN_SAMPLING2 {2, 32, 94,  94, 32,  2, 0, 0,\
                            0, 19, 80, 105, 47,  5, 0, 0,\
                            0, 11, 64, 106, 64, 11, 0, 0,\
                            0,  5, 47, 105, 80, 19, 0, 0}


/*!*********************************************************************************
*  \brief Struct for Resize descriptor
*
*  Sizes and Offsets are on vertical direction (Y)
*
*  NB: src_current_line, src_offs cleared by a call to get_polyphase_params();
***********************************************************************************/
struct RESIZE_DESCRIPTOR{
    int32_t dst_bh, dst_bw;       /*!< Destination block width and height */
//    int32_t dst_offs, dst_size;   /*!< Destination offset and size (i.e height) */   // to be reviewed - not used by ACF version - used in simulation?
    int32_t src_current_line, unused;   /*!< Line number of the top left corner of the source (input) block. */
    int32_t src_offs, scl_fact;   /*!< Source offset - Scale Factor */
    int32_t phases, taps;         /*!< Number of taps and phases */
    int32_t out_scale, out_round; /*!< Values for scaling and rounding */   
    const int16_t *fbnk;          /*!< Polyphase Filter Bank */  
};

/*!*****************************************************************************************
*  \brief Size of descriptors in Bytes
*  
*  Did not use sizeof to prevent probable size mismatch of same types on different platforms 
********************************************************************************************/

#define RESIZE_DESC_SIZE (POLYPHASE_FLT_SIZE*2 + (10*4)) /*!< sizeof(RESIZE_DESCRIPTOR) in bytes */




#endif /* _APU_RESIZE_DEFINITIONS_H_ */
