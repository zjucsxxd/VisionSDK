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
 * device_io.h
 * 
 * Defines the various macros required for input/output accesses.
 * Provides more control over the accesses such as disabling them.
 */

#ifndef __DEVICE_IO_H_
#define __DEVICE_IO_H_

#include "test.h"
#include "uartpl011_driver_types.h"

/****************************************************************************
 * Macros
 ****************************************************************************/

#define FUNC_HAS_TIMEOUT(startval) \
    int32_t _timeout_ = startval; \
    int timeout_not_exceeded = 0
#define TIMEOUT_LOOP_BEGIN \
    while (_timeout_ > 0) {
#define LOOP_TIMED_OUT (timeout_not_exceeded == 0)

#define TIMESTEP
#define TIMEOUT_LOOP_END \
    _timeout_--; \
    }
#define TIMEOUT_CHECK \
    timeout_not_exceeded = (_timeout_ > 0); \
    TEST(timeout_not_exceeded);

#define DEVICE_RD(addr, size, data) memcpy(data, (uint8_t*)(addr), size*sizeof(uint8_t))
#define DEVICE_RD8(addr)  (uint8_t) (*((uint8_t  *)(addr)))
#define DEVICE_RD16(addr) (uint16_t)(*((uint16_t *)(addr)))
#define DEVICE_RD32(addr) (uint32_t)(*((uint32_t *)(addr)))
#define DEVICE_RD64(addr) (uint64_t)(*((uint64_t *)(addr)))

#define DEVICE_WR(addr, size, data) memcpy((uint8_t *)(addr), data, size*sizeof(uint8_t))
#define DEVICE_WR8(addr, data)  *((uint8_t  *)(addr)) = data
#define DEVICE_WR16(addr, data) *((uint16_t *)(addr)) = data
#define DEVICE_WR32(addr, data) *((uint32_t *)(addr)) = data
#define DEVICE_WR64(addr, data) *((uint64_t *)(addr)) = data

#define INTERRUPT_FN(fn) interrupt void fn()
#define INTERRUPT_FN_END(fn)

#endif /*__DEVICE_IO_H_ */
