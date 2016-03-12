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
#ifndef _OAL_MEMORY_INTERNALS_H__
#define _OAL_MEMORY_INTERNALS_H__

//Define for using the System memory heap.
#define OAL_SYSTEM_MEMORY_POOL_ID      0

//Define for using the Application memory heap.
#define OAL_APP_MEMORY_POOL_ID         1

//Defines for cache line and page sizes
#define PAGE_SIZE_IN_BYTES       (4*1024)
#define CACHE_LINE_SIZE_IN_BYTES (32)

static const unsigned int cInvalid    = 0xffffffff;
static const unsigned int cSpecialTag = 0xDEADBEEF;

#endif // _OAL_MEMORY_INTERNALS_H__
