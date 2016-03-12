// --------------------------------------------------------------------------
// COPYRIGHT (c) Freescale 2009
// Freescale Confidential Proprietary
//  All Rights Reserved
// --------------------------------------------------------------------------
//!\file    typedefs.h
//!\brief   This file contains various type defines for datatypes
//

// TYPE: Header File
// DEPARTMENT: MSG
// CREATED BY: Jeff Loeliger  (B04629)

// --------------------------------------------------------------------------
// PURPOSE:  This file contains various type defines for datatypes
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#if defined(__MWERKS__) || defined(__ghs__) || defined(__GNUC__) || defined(__STANDALONE__) || defined(__KERNEL__)	// Metrowerk CodeWarrior || GreenHills || GCC || STANDALONE || KERNEL
#ifndef __KERNEL__
    #include <stdint.h>	// Standard typedefs used by header files, based on ISO C standard
#endif

    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;
    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;
    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;

#else
    // This is needed for compilers that don't have a stdint.h file
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef volatile signed char vint8_t;
    typedef volatile unsigned char vuint8_t;
    typedef signed short int16_t;
    typedef unsigned short uint16_t;
    typedef volatile signed short vint16_t;
    typedef volatile unsigned short vuint16_t;
    typedef signed int int32_t;
    typedef unsigned int uint32_t;
    typedef volatile signed int vint32_t;
    typedef volatile unsigned int vuint32_t;
#endif

/*********************************************************************
 *
 * Copyright:
 *	Freescale Semiconductor, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Freescale
 *  Semiconductor, Inc. This software is provided on an "AS IS"
 *  basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, Freescale
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH
 *  REGARD TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF)
 *  AND ANY ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Freescale Semiconductor assumes no responsibility for the
 *  maintenance and support of this software
 *
 ********************************************************************/

 #endif // _TYPEDEFS_H_
