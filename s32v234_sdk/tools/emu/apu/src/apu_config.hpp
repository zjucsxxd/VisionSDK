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
* \file APU_lib.h
* \brief APU configuration header
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#ifndef _APU_CONFIG_H_
#define _APU_CONFIG_H_

#include <cstdint>

//Emulation library configuration

namespace APEX2
{

/****************************************************************************
* APU-C scalar types
****************************************************************************/

typedef uint8_t   int08u;
typedef int8_t    int08s;
typedef uint16_t  int16u;
typedef int16_t   int16s;
typedef uint32_t  int32u;
typedef int32_t   int32s;

/****************************************************************************
* constants
****************************************************************************/

//Vector width

//Target > 3.1.4
const int APU_VSIZE = 64;
//deprecated
const int VSIZE = APU_VSIZE;

//0 disables emulated cycle counting, cycle counting is slow
#define COUNT_CYCLES 0

}

#endif // _APU_CONFIG_H_
