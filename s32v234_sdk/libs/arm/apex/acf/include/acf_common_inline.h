#ifndef __ACF_COMMON_INLINE__H__
#define __ACF_COMMON_INLINE__H__

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

#endif
