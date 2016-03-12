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
* \file Oal_memoryrc.cpp
* \brief OAL reference counting implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <linux/oal_linux.h>

/*****************************************************************************
* types
*****************************************************************************/

/****************************************************************************/
/** Linux-specific RC type hidden by the OAL_MemoryRC
*****************************************************************************/
struct memRefCounting_s
{
  void* mPointer;
  int mCount;
};

/*****************************************************************************
* functions
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

OAL_MemoryRC OAL_MemoryRCCreate(void *pMem)
{
  OAL_MemoryRC prc = (OAL_MemoryRC)malloc(sizeof(memRefCounting_s));
  if (prc)
  {
    prc->mPointer = pMem;
    prc->mCount = 1;
  }
  return prc;
}

int OAL_MemoryRCDecrement(OAL_MemoryRC pMemRC)
{
  int rcc = --pMemRC->mCount;
  //TODO: handle < 0?
  if (!rcc)
  {
    OAL_MemoryFree(pMemRC->mPointer);
    free((void*) pMemRC);
  }

  return rcc;
}

int  OAL_MemoryRCIncrement(OAL_MemoryRC pMemRC)
{
  return ++pMemRC->mCount;
}

int  OAL_MemoryRCGetCount (OAL_MemoryRC pMemRC)
{
  return pMemRC->mCount;
}

void* OAL_MemoryRCGetBuffer(OAL_MemoryRC pMemRC)
{
  return pMemRC->mPointer;
}

#ifdef __cplusplus
}
#endif

