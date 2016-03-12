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

CGV_INLINE_PREFIX int RetLocalMemDescSizeInBytes(ACF_LocalMemDesc* lpLM)
{
   return lpLM->chunkE0Span*(lpLM->chunkHeight*lpLM->numBuffers + lpLM->padding.n + lpLM->padding.s);
}

//the use of the function has been reduced and is on its way to being eliminated
//due to the use of modulus in some cases (currently only called by RetAddr_iter(), which
//is called by ACF_CollectVarLengthScatteredLists() and various linked list generation functions)
CGV_INLINE_PREFIX int RetBufferIndex(ACF_LocalMemDesc* lpLM, int lIter)
{
   int lNumBuffers = lpLM->numBuffers;
   int lMask = lNumBuffers-1; //lNumBuffers must be >= 1
   if((lNumBuffers&lMask) == 0) //if lNumBuffers is a power of 2
      return lIter&lMask;
   else
      return lIter%lNumBuffers; //SLOW - need an alternative for this!!!
}

CGV_INLINE_PREFIX void* RetAddr_iter(ACF_LocalMemDesc* lpLM, int lIter)
{
   return (void*)((char*)lpLM->pBuf0 + RetBufferIndex(lpLM, lIter)*(lpLM->bufferOffset));
}

CGV_INLINE_PREFIX void* RetAddr_cbindex(ACF_LocalMemDesc* lpLM, int16_t lCbIndex)
{
   return (void*)((char*)lpLM->pBuf0 + lCbIndex*(lpLM->bufferOffset));
}

CGV_INLINE_PREFIX void CbIndexIncrement(int16_t* lpIndex, uint16_t lNumBuffers)
{
   if (++(*lpIndex) == lNumBuffers)
      *lpIndex = 0;
}
