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
* \file Oal_not_implemented.cpp
* \brief not implemented OAL functions
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <linux/oal_linux.h>
#include <oal_file.h>

/*****************************************************************************
* functions
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

//HW interrupts
void OAL_InterruptLock(void)
{
}

//HW interrupts
void OAL_InterruptFree(void)
{
}

//HW interrupts
void OAL_SISRVecConnect(int,
                        void (*)(int))
{
}

//HW interrupts
LIB_RESULT OAL_SISRInit(void (*)(void), unsigned int ,
    unsigned int , const char* , OAL_SISR_ID* )
{
  return LIB_FAILURE;
}

//HW interrupts
void OAL_SISREnableIrq(unsigned int )
{
}

//HW interrupts
void OAL_SISRActivate(OAL_SISR_ID )
{
}

//HW interrupts
LIB_RESULT OAL_SISRDelete(OAL_SISR_ID )
{
  return LIB_FAILURE;
}

//HW interrupts
void OAL_SISRDisableIrq(unsigned int )
{
}

//no way to get the directory handle
LIB_RESULT OAL_FileGetFirstDirectoryEntry(OAL_DIRECTORY_HANDLE *,
    OAL_DIRECTORY_ENTRY  *, char *)
{
  return LIB_FAILURE;
}

//no way to get the directory handle
LIB_RESULT OAL_FileGetNextDirectoryEntry(OAL_DIRECTORY_HANDLE *,
    OAL_DIRECTORY_ENTRY  *)
{
  return LIB_FAILURE;
}

//no way to get the directory handle
LIB_RESULT OAL_FileDoneWithDirectory(OAL_DIRECTORY_HANDLE *)
{
  return LIB_FAILURE;
}

/*
 * TODO: duplicated (OAL_GetFileState, OAL_GetFileIDState), many attributes
 * don't apply to Linux
*/
LIB_RESULT OAL_GetFileState(char *, OAL_DIRECTORY_ENTRY *)
{
  return LIB_FAILURE;
}

/*
 * TODO: duplicated (OAL_GetFileState, OAL_GetFileIDState), many attributes
 * don't apply to Linux
*/
LIB_RESULT OAL_GetFileIDState(OAL_FILE_DESCRIPTOR *,
    OAL_DIRECTORY_ENTRY  *)
{
  return LIB_FAILURE;
}

//TODO: many attributes don't apply to Linux
LIB_RESULT OAL_SetFileIDState(OAL_FILE_DESCRIPTOR *, int ,
    OAL_DATE_TIME* , OAL_FILE_ATTRIBUTES *)
{
  return LIB_FAILURE;
}

//the function refers to the whole drive flush
LIB_RESULT OAL_DiskFlush(const char *)
{
  return LIB_FAILURE;
}

//volume labels in Linux?
LIB_RESULT OAL_DriveSetVolumeLabel(char *, char *)
{
  return LIB_FAILURE;
}

//volume labels in Linux?
LIB_RESULT OAL_DriveGetVolumeLabel(char *, char *)
{
  return LIB_FAILURE;
}

//empty implementation of OAL_MemoryGetBytesRequested()
unsigned int OAL_MemoryGetBytesRequested(void *)
{
  return 0;
}

LIB_RESULT OAL_IRQInit(void (*)(void), unsigned int , unsigned int , IRQ_MODE )
{
	return LIB_FAILURE;
}

void OAL_IRQEnable(unsigned int )
{
	
}

LIB_RESULT OAL_IRQDelete(unsigned int )
{
	return LIB_FAILURE;
}

void OAL_IRQDisable(unsigned int )
{
	
}

#ifdef __cplusplus
}
#endif

