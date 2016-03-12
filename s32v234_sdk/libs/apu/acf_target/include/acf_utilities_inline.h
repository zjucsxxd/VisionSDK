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

CGV_INLINE_PREFIX kernel_io_desc* RetIoDesc(ACF_LocalMemDesc* lpLmDesc, kernel_io_desc* lpKernelIoDesc)
{
   //NOTE: this function assumes:
   // - lpKernelIoDesc->pMem has been initialized to (lpLmDesc->pBuf0 - lpLmDesc->bufferOffset)
   // - lpKernelIoDesc->_framework_cbindex has been initialized to -1
   //so there is no difference between the first time this is called and subsequent times

   //increment mem pointer to point to next buffer
   lpKernelIoDesc->pMem = (void*)((char*)lpKernelIoDesc->pMem + lpLmDesc->bufferOffset);
   lpKernelIoDesc->_framework_cbindex ++;

   //wrap around if necessary
   if (lpKernelIoDesc->_framework_cbindex >= lpLmDesc->numBuffers)
   {
      lpKernelIoDesc->pMem = lpLmDesc->pBuf0;
      lpKernelIoDesc->_framework_cbindex = 0;
   }

   return lpKernelIoDesc;
}

//following externs are globals allocated by the main program
extern int16_t gsACF_FIRST_TILE_FLAG;
extern int16_t gsACF_LAST_TILE_FLAG;
CGV_INLINE_PREFIX void ACF_UpdateTileFlags(int lIter, int lNumIter)
{
   gsACF_FIRST_TILE_FLAG = 0;
   gsACF_LAST_TILE_FLAG = 0;
   if (lIter == 0)
      gsACF_FIRST_TILE_FLAG = 1;
   if (lIter == lNumIter-1)
      gsACF_LAST_TILE_FLAG = 1;
}
