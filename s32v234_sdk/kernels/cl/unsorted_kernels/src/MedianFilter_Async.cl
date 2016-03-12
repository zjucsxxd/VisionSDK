// Copyright (c) 2009-2011 Intel Corporation
// All rights reserved.
// 
// WARRANTY DISCLAIMER
// 
// THESE MATERIALS ARE PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THESE
// MATERIALS, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Intel Corporation is the author of the Materials, and requests that all
// problem reports or change requests be submitted to it directly

// 3x3 median filter kernel based on partial sort

//Scalar version of kernel

#ifdef APEX
chess_property {
opencl_vectors: 3;  // 0x1 = wx, 0x2 = wy, 0x4 = wz
}
#endif

inline void MedianFilterFuncWGAsync(__local uint* uiRGBA, uint iStride, uint uiMask, uint* pDst)
{
    //extract next color channel
    uint r0,r1,r2,r3,r4,r5,r6,r7,r8;
    // row 0
    r0=uiRGBA[0]& uiMask;
    r1=uiRGBA[1]& uiMask;
    r2=uiRGBA[2]& uiMask;
    // row 1
    r3=uiRGBA[0+iStride]& uiMask;
    r4=uiRGBA[1+iStride]& uiMask;
    r5=uiRGBA[2+iStride]& uiMask;
    // row 2
    r6=uiRGBA[0+iStride*2]& uiMask;
    r7=uiRGBA[1+iStride*2]& uiMask;
    r8=uiRGBA[2+iStride*2]& uiMask;
        
    //perform partial bitonic sort to find current channel median
    uint uiMin = min(r0, r1);
    uint uiMax = max(r0, r1);
    r0 = uiMin;
    r1 = uiMax;
    
    uiMin = min(r3, r2);
    uiMax = max(r3, r2);
    r3 = uiMin;
    r2 = uiMax;
    
    uiMin = min(r2, r0);
    uiMax = max(r2, r0);
    r2 = uiMin;
    r0 = uiMax;
    
    uiMin = min(r3, r1);
    uiMax = max(r3, r1);
    r3 = uiMin;
    r1 = uiMax;
    
    uiMin = min(r1, r0);
    uiMax = max(r1, r0);
    r1 = uiMin;
    r0 = uiMax;
    
    uiMin = min(r3, r2);
    uiMax = max(r3, r2);
    r3 = uiMin;
    r2 = uiMax;
    
    uiMin = min(r5, r4);
    uiMax = max(r5, r4);
    r5 = uiMin;
    r4 = uiMax;
    
    uiMin = min(r7, r8);
    uiMax = max(r7, r8);
    r7 = uiMin;
    r8 = uiMax;
    
    uiMin = min(r6, r8);
    uiMax = max(r6, r8);
    r6 = uiMin;
    r8 = uiMax;
    
    uiMin = min(r6, r7);
    uiMax = max(r6, r7);
    r6 = uiMin;
    r7 = uiMax;
    
    uiMin = min(r4, r8);
    uiMax = max(r4, r8);
    r4 = uiMin;
    r8 = uiMax;
    
    uiMin = min(r4, r6);
    uiMax = max(r4, r6);
    r4 = uiMin;
    r6 = uiMax;
    
    uiMin = min(r5, r7);
    uiMax = max(r5, r7);
    r5 = uiMin;
    r7 = uiMax;
    
    uiMin = min(r4, r5);
    uiMax = max(r4, r5);
    r4 = uiMin;
    r5 = uiMax;
    
    uiMin = min(r6, r7);
    uiMax = max(r6, r7);
    r6 = uiMin;
    r7 = uiMax;
    
    uiMin = min(r0, r8);
    uiMax = max(r0, r8);
    r0 = uiMin;
    r8 = uiMax;
    
    r4 = max(r0, r4);
    r5 = max(r1, r5);
    
    r6 = max(r2, r6);
    r7 = max(r3, r7);
    
    r4 = min(r4, r6);
    r5 = min(r5, r7);
    
    //store found median into result
    pDst[0] |= min(r4, r5);
}



__kernel //__attribute__((reqd_work_group_size(8, 8, 1)))
void MedianFilterBitonicAsync(const __global uint* pSrc, __global uint* pDst)
{
    // global id
    const int x = get_global_id(0);
    const int y = get_global_id(1);
    
    // local id (in work items)
    const int lx = get_local_id(0);
    const int ly = get_local_id(1);
    
    // work group id
    const int wx = x - lx;
    const int wy = y - ly;
    
    const int srcwidth = get_global_size(0);
    const int iOffset  = y * srcwidth;
    const int iPrev    = iOffset - srcwidth;
    const int iNext    = iOffset + srcwidth;
    
    
    const int iwidth  = get_local_size(0) + 3 - 1;
    const int iheight = get_local_size(1) + 3 - 1;
    const int istride = iwidth;
    const int owidth  = get_local_size(0);
    const int oheight = get_local_size(1);
    const int ostride = owidth;
    
    // span needs to be 32-bit aligned
    __local uint itmp[(8+2)*(8+2)];
   // __local uint dtmp[8*8];
    //__local uint itmp[(8+8)*(8+2)];
    
    // input 2D transfer
    // create a sequence of 1D transfers from global to local (read)
    if (1)
    {

        event_t ievent = 0;
    
        // Note: iwidth and iheight are padded already
        for (int r = 0; r < (iheight); r++)
        {
                ievent= async_work_group_copy(itmp + (r*istride), pSrc + (wy+r-1)*srcwidth + (wx-1), iwidth, ievent);
                wait_group_events(1, &ievent);   
        }
    }
    
    
    // Processing
    uint uiResult = 0;
    uint uiMask = 0xFF;
    
    const int idxIntmp = (ly) * istride + (lx);
    {
        for(int ch = 0; ch < 3; ch++)
        {
                MedianFilterFuncWGAsync(&(itmp[idxIntmp]), istride, uiMask, &uiResult);
                //update channel mask
                uiMask <<= 8;
        }
    }
    
    //store result into memory
#if 1
    pDst[iOffset + x] = uiResult;
#else
    //const int idxLocal = (ly+1)*istride + (lx+1);
    //itmp[idxLocal] = lx | (ly << 16);
    //pDst[iOffset + x] = itmp[idxLocal];
    dtmp[ly*owidth+lx] = uiResult;
    barrier(CLK_GLOBAL_MEM_FENCE);
    
    //pDst[iOffset + x] = dtmp[ly*owidth+lx];
    if(1)
    {
        event_t oevent;
    
        // Note: iwidth and iheight are padded already
        for (int r = 0; r < (oheight); r++)
        {
                oevent = async_work_group_copy(pDst+(wy+r)*srcwidth + wx, dtmp+r*owidth, owidth, 0);
                wait_group_events(1, &oevent);
        }
    }
#endif

}

