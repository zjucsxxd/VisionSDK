/*
 * -----------------------------------------------------------------------------
 * Copyright (C) Australian Semiconductor Technology Company (ASTC). 2010.
 * All Rights Reserved.
 * 
 * This is unpublished proprietary source code of the Australian Semiconductor
 * Technology Company (ASTC).  The copyright notice does not evidence any actual
 * or intended publication of such source code.
 * -----------------------------------------------------------------------------
 */

/*
 * driver_types.h
 * 
 * This header file contains generic constants, and enums, etc
 * utilised by the drivers.
 */

#ifndef __DRIVER_TYPES_H_
#define __DRIVER_TYPES_H_

// -------------------------------------------------------------------
// Standard integer types for 32-bit platform development 
// -------------------------------------------------------------------
/*
/// Signed 8-bit integer
typedef signed char         int8_t;
/// Signed 16-bit integer
typedef signed short        int16_t;
/// Signed 32-bit integer
typedef signed int          int32_t;
/// Signed 64-bit integer
typedef signed long long    int64_t;

/// Unsigned 8-bit integer
typedef unsigned char       uint8_t;
/// Unsigned 16-bit integer
typedef unsigned short      uint16_t;
/// Unsigned 32-bit integer
typedef unsigned int        uint32_t;
/// Unsigned 64-bit integer
typedef unsigned long long  uint64_t;


/// Volatile signed 8-bit integer
typedef volatile int8_t     vint8_t;
/// Volatile signed 16-bit integer
typedef volatile int16_t    vint16_t;
/// Volatile signed 32-bit integer
typedef volatile int32_t    vint32_t;
/// Volatile signed 64-bit integer
typedef volatile int64_t    vint64_t;

/// Volatile unsigned 8-bit integer
typedef volatile uint8_t    vuint8_t;
/// Volatile unsigned 16-bit integer
typedef volatile uint16_t   vuint16_t;
/// Volatile unsigned 32-bit integer
typedef volatile uint32_t   vuint32_t;
/// Volatile signed 64-bit integer
typedef volatile uint64_t   vuint64_t;*/
#include "../../../../arm/apex/apex/kernel/include/apexdriver_intheader.h"

// -------------------------------------------------------------------
// Types required by drivers
// -------------------------------------------------------------------

/* Enumerator providing convenience values for true/false. */
typedef enum BOOLEAN_e {
    FALSE = 0,
    TRUE = 1
} BOOLEAN_t;

#endif /*__DRIVER_TYPES_H_*/
