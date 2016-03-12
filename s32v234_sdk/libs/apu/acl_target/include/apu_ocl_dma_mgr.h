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

/* We are operating under the assumption that we are absolute authority
** over the DMA channels we use and nothing else will use them. */

#define NUM_DMA_CHANNELS    2
#define NUM_LL_ENTRY        16

void dma_mgr_init();

                                                
int dma_mgr_new_config(       vec08s*                    dst,     int32_t  dst_stride, 
                        const int8_t chess_storage(XMb)@ src,     int32_t  src_stride, 
                                                uint32_t size_x,  uint32_t size_y,
                                                uint32_t data_size,
                                                uint32_t align, 
                                                uint8_t  chnum,   uint8_t chtype); 
//int dma_mgr_update_config(offset, event.config_idx, chnum);
   
int dma_mgr_get_open_channel();

void dma_mgr_begin_xfer(int chnum, int chtype, int index);

void dma_mgr_wait_xfer(int chnu, int chtype);