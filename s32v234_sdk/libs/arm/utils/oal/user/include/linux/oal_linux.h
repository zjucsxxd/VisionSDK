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
* \file OAL_linux.h
* \brief common Linux OAL implementation header
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#ifndef OAL_LINUX_H_
#define OAL_LINUX_H_

#include <oal.h>
#include <cstdlib>
#include <cstring>

/*****************************************************************************
* prototypes
*****************************************************************************/

/****************************************************************************/
/** Gets the alignment from OAL file flag.
*
* \param aFlags OAL file flags
*
* \return alignment in bytes or 0 if no alignment required
*****************************************************************************/
size_t AlignmentGet(OAL_MEMORY_FLAG flags);

/****************************************************************************/
/** Converts the time used in OAL to Linux timespec.
*
* \param aTime time in microseconds
*
* \return time converted to timespec structure
*****************************************************************************/
inline timespec MicrosecondsToTimeSpec(unsigned int aTime)
{
  timespec ts;
  ts.tv_sec = __time_t(aTime / 1000000);
  ts.tv_nsec = __time_t((aTime % 1000000) * 1000);
  return ts;
}

/****************************************************************************/
/** Truncates the name to 7 chars, enforces linux conventions.
*
* \param apOutName output name (7 chars + nullchar), has to be at least 8 chars
*        long
* \param apOutLinuxName output linux name (8 chars + nullchar, '/'
*        added as a first char), has to be at least 9 chars long
* \param apInName input name
*
* \note for semaphores and shared memory
*****************************************************************************/
void LinuxNameTruncate7(char* apOutName, char *apOutLinuxName,
    const char* apcInName);

#endif /* OAL_LINUX_H_ */
