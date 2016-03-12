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
* \file APU_ACF.cpp
* \brief APU_lib I/O data descriptor implementation
* \author Igor Aleksandrowicz
* \version
* \date 10-February-2014
****************************************************************************/


#include <cstring>
#include <climits>
#include <sstream>
#include <cstdint>
#include <ctime>
#include <oal.h>

using std::stringstream;

/****************************************************************************
* functions
****************************************************************************/
void *OAL_MemoryReturnAddress(void *pBuffer, OAL_MEMORY_ACCESS access) {
	return pBuffer;
}

void OAL_MemoryFree(void* mem) {
	free(mem);
}

void *OAL_MemoryAllocFlag(uint32_t sz, OAL_MEMORY_FLAG flags){
	void *newMem = malloc(sz);
	return newMem;
}

void *OAL_MemoryAlloc(uint32_t sz){
	void *newMem = malloc(sz);
	return newMem;
}

void OAL_MemoryAllocReset(void) {
	// ???
};

LIB_RESULT OAL_MemoryAllocInit(void){
	//???
	return LIB_SUCCESS;
}
