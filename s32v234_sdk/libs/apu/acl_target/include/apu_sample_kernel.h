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

#ifndef _APU_SAMPLE_KERNEL_H_
#define _APU_SAMPLE_KERNEL_H_

//


// standard public kernel APIs
int sample_kernel0(int argc, const char* argv[]);
int sample_kernel1(int argc, const char* argv[]);

// acf kernels
int acf1_testkernel_add(int argc, const char* argv[]);
int acf1_padblock_lr(int argc, const char* argv[]);
int acf1_padblock_tb(int argc, const char* argv[]);
int acf1_copyregion(int argc, const char* argv[]);
int acf1_testkernel_median3x3(int argc, const char* argv[]);
// algo kernels
int remap_bilinear_wrapper(int argc, const char* argv[]);
// debugging
/*
void 
sample_func_set(  vec08u __cmem* dst, int ds,
                  const unsigned char val,
                  int bw, int bh);
                  
void sample_func_dmem_set( unsigned char* dst, int ds, const unsigned char val, int bw, int bh);
*/

int sample_vload();

#endif /* _APU_SAMPLE_KERNEL_H_ */