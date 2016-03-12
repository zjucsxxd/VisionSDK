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

#ifndef __APU_TEST_UTIL_CORE_H__
#define __APU_TEST_UTIL_CORE_H__

#include <stdint.h>

#define APU_DEBUG    1

// Tile Operations
// Tile Transfer (DMEM -> CMEM)
/*!
   Unsigned 8-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_08(vec08u*  dst, int dstr, const int08u* src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 8-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_08(vec08s*  dst, int dstr, const int08s* src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_08((vec08u*)dst, dstr, (int08u*)src, sstr, tw, th, bw, bh);
}

/*!
   Unsigned 16-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_16(vec16u*  dst, int dstr, const int16u* src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 16-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_16(vec16s*  dst, int dstr, const int16s* src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_16((vec16u*)dst, dstr, (int16u*)src, sstr, tw, th, bw, bh);
}

/*!
   Unsigned 32-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_32(vec32u*  dst, int dstr, const int32u* src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 32-bit Tile Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (DMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_32(vec32s*  dst, int dstr, const int32s* src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_32((vec32u*)dst, dstr, (int32u*)src, sstr, tw, th, bw, bh);
}

// Tile Transfer (CMEM -> DMEM)
/*!
   Unsigned 8-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_08(int08u* dst, int dstr, vec08u*  src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 8-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_08(int08s* dst, int dstr, vec08s*  src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_08((int08u*)dst, dstr, (vec08u*)src, sstr, tw, th, bw, bh);
}

/*!
   Unsigned 16-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_16(int16u* dst, int dstr, vec16u*  src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 16-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_16(int16s* dst, int dstr, vec16s*  src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_16((int16u*)dst, dstr, (vec16u*)src, sstr, tw, th, bw, bh);
}

/*!
   Unsigned 32-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_til_transfer_32(int32u* dst, int dstr, vec32u*  src, int sstr, int tw, int th, int bw, int bh);

/*!
   Signed 32-bit Tile Transfer CMEM to DMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (DMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         (CMEM)
   \param sstr    - [Input]  Source tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
inline void apu_til_transfer_32(int32s* dst, int dstr, vec32s*  src, int sstr, int tw, int th, int bw, int bh) {
   apu_til_transfer_32((int32u*)dst, dstr, (vec32u*)src, sstr, tw, th, bw, bh);
}

/*!
   Unsigned 8-bit Indirect Input Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         
   \param sstr    - [Input]  Source tile stride
   \param offset  - [Input]  Pointer to offset 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_indirect_input_08(      vec08u* dst, int dstr,
                           const int08u* src, int sstr, 
                           const int32s *offset,
                                 int bw, int bh);
                                 
/*!
   Unsigned 16-bit Indirect Input Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         
   \param sstr    - [Input]  Source tile stride
   \param offset  - [Input]  Pointer to offset 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_indirect_input_16(         vec16u* dst, int dstr,
                              const int16u* src, int sstr, 
                              const int32s *offset,
                              int bw, int bh);
/*!
   Unsigned 16-bit Indirect Input Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         
   \param sstr    - [Input]  Source tile stride
   \param offset  - [Input]  Pointer to offset 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_indirect_input_16(         vec16s* dst, int dstr,
                              const int16s* src, int sstr, 
                              const int32s *offset,
                              int bw, int bh);
/*!
   Unsigned 32-bit Indirect Input Transfer DMEM to CMEM (DMA-like operation)

   \param dst     - [Output] Destination block pointer   (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param src     - [Input]  Source tile pointer         
   \param sstr    - [Input]  Source tile stride
   \param offset  - [Input]  Pointer to offset 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_indirect_input_32(         vec32u* dst, int dstr,
                              const int32u* src, int sstr, 
                              const int32s *offset,
                              int bw, int bh);

/*!
   Unsigned 32-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_32(vec32u*  dst, int dstr, int bw, int bh);

/*!
   Signed 32-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_32(vec32s*  dst, int dstr, int bw, int bh);

/*!
   Unsigned 16-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_16(vec16u*  dst, int dstr, int bw, int bh);

/*!
   Signed 16-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_16(vec16s*  dst, int dstr, int bw, int bh);

/*!
   Signed 8-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_08(vec08s*  dst, int dstr, int bw, int bh);

/*!
   Unsigned 8-bit  Mem clear

   \param dst     - [Output] Destination block pointer    (CMEM)
   \param dstr    - [Input]  Destination block stride
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 

 */
void apu_mem_clear_08(vec08u*  dst, int dstr, int bw, int bh);

/*!
   Signed 32-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_32(const vec32s*  dst, int dstr, const int32s* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   Unsigned 32-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_32(const vec32u*  dst, int dstr, const int32u* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   Signed 16-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_16(const vec16s*  dst, int dstr, const int16s* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   Unsigned 16-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_16(const vec16u*  dst, int dstr, const int16u* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   Signed 8-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_08(const vec08s*  dst, int dstr, const int08s* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   Unsigned 8-bit  Data Comparison (CMEM & DMEM)
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
 */
int apu_til_compare_08(const vec08u*  dst, int dstr, const int08u* ref, int sstr, int tw, int th, int bw, int bh, int errmax);

/*!
   8-bit Image border padding, padding method is border replication  

   \param dst     - [Output] Destination block pointer
   \param src     - [Input]  Source buffer
   \param sw      - [Input]  Source width
   \param sh      - [Input]  Source height 
   \param pw      - [Input]  pad width (left and right)
   \param ph      - [Input]  pad height (top and bottom)

 */
void apu_pad_image_08(int08u* dst, const int08u* src, int sw, int sh, int pw, int ph);
void apu_pad_image_08(int08u* dst, const int08u* src, int sstr, int sw, int sh, int pw, int ph);
inline void apu_pad_image_08(int08s* dst, const int08s* src, int sw, int sh, int pw, int ph) {
   apu_pad_image_08((int08u*)dst, (int08u*)src, sw, sh, pw, ph);
}
inline void apu_pad_image_08(int08s* dst, const int08s* src, int sstr, int sw, int sh, int pw, int ph) {
   apu_pad_image_08((int08u*)dst, (int08u*)src, sstr, sw, sh, pw, ph);
}

/*!
   16-bit Image border padding, padding method is border replication  

   \param dst     - [Output] Destination block pointer
   \param src     - [Input]  Source buffer
   \param sw      - [Input]  Source width
   \param sh      - [Input]  Source height 
   \param pw      - [Input]  pad width (left and right)
   \param ph      - [Input]  pad height (top and bottom)

 */
void apu_pad_image_16(int16u* dst, const int16u* src, int sw, int sh, int pw, int ph);
void apu_pad_image_16(int16u* dst, const int16u* src, int sstr, int sw, int sh, int pw, int ph);
inline void apu_pad_image_16(int16s* dst, const int16s* src, int sw, int sh, int pw, int ph) {
   apu_pad_image_16((int16u*)dst, (int16u*)src, sw, sh, pw, ph);
}
inline void apu_pad_image_16(int16s* dst, const int16s* src, int sstr, int sw, int sh, int pw, int ph) {
   apu_pad_image_16((int16u*)dst, (int16u*)src, sstr, sw, sh, pw, ph);
}

/*!
   32-bit Image border padding, padding method is border replication  

   \param dst     - [Output] Destination block pointer
   \param src     - [Input]  Source buffer
   \param sw      - [Input]  Source width
   \param sh      - [Input]  Source height 
   \param pw      - [Input]  pad width (left and right)
   \param ph      - [Input]  pad height (top and bottom)

 */
void apu_pad_image_32(int32u* dst, const int32u* src, int sw, int sh, int pw, int ph);
void apu_pad_image_32(int32u* dst, const int32u* src, int sstr, int sw, int sh, int pw, int ph);
inline void apu_pad_image_32(int32s* dst, const int32s* src, int sw, int sh, int pw, int ph) {
   apu_pad_image_32((int32u*)dst, (int32u*)src, sw, sh, pw, ph);
}
inline void apu_pad_image_32(int32s* dst, const int32s* src, int sstr, int sw, int sh, int pw, int ph) {
   apu_pad_image_32((int32u*)dst, (int32u*)src, sw, sh, pw, ph);
}

/*!
   Signed 8-bit Vertical padding with pixel replication (in place).

   \param blk  - [Input/Output]  Block pointer
   \param sstr - [Input]         Block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height 
   \param bpx  - [Input]  Border padding size (x-dir)
   \param bpy  - [Input]  Border padding size (y-dir)
*/
void apu_til_padver_08(vec08s* blk, int sstr, int bw, int bh, int bpx, int bpy);

/*!
   Unsigned 8-bit Vertical padding with pixel replication (in place).

   \param blk  - [Input/Output]  Block pointer
   \param sstr - [Input]         Block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height 
   \param bpx  - [Input]  Border padding size (if there is x-dir padding, copy as well with ver padding)
   \param bpy  - [Input]  Border padding size (y-dir)
*/
void apu_til_padver_08(vec08u* blk, int sstr, int bw, int bh, int bpx, int bpy);

/*!
   Signed 16-bit Vertical padding with pixel replication (in place).

   \param blk  - [Input/Output]  Block pointer
   \param sstr - [Input]         Block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height 
   \param bpx  - [Input]  Border padding size (if there is x-dir padding, copy as well with ver padding)
   \param bpy  - [Input]  Border padding size (y-dir)
*/
void apu_til_padver_16(vec16s* blk, int sstr, int bw, int bh, int bpx, int bpy);

/*!
   Unsigned 16-bit Vertical padding with pixel replication (in place).

   \param blk  - [Input/Output]  Block pointer
   \param sstr - [Input]         Block stride
   \param bw   - [Input]  Block width
   \param bh   - [Input]  Block height 
   \param bpx  - [Input]  Border padding size (x-dir)
   \param bpy  - [Input]  Border padding size (y-dir)
*/
void apu_til_padver_16(vec16u* blk, int sstr, int bw, int bh, int bpx, int bpy);

/*!
   Unsigned 8-bit Data Comparison (CMEM & DMEM) using ranges for comparing approximation
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
   \param window  - [Input]  Range window value
 */
int
apu_til_compare_range(
   const vec08u*  dst, int dstr, 
   const uint8_t* ref, int sstr, 
   int tw, int th, 
   int bw, int bh, 
   int errmax, int window);

/*!
   Unsigned 16-bit Data Comparison (CMEM & DMEM) using ranges for comparing approximation
 
   \param dst     - [Input]  Result block pointer     (CMEM)
   \param dstr    - [Input]  Result block stride
   \param ref     - [Input]  Reference tile pointer  (DMEM)
   \param sstr    - [Input]  Reference tile stride
   \param tw      - [Input]  Tile width
   \param th      - [Input]  Tile height 
   \param bw      - [Input]  Block width
   \param bh      - [Input]  Block height 
   \param errmax  - [Input]  Maximum number of errors (display)
   \param window  - [Input]  Range window value
 */
int
apu_til_compare_range(
   const vec16u*  dst, int dstr, 
   const uint16_t* ref, int sstr, 
   int tw, int th, 
   int bw, int bh, 
   int errmax, int window);
   

/*************************** Horizontal Padding Functions ********************************
 *
 * These will do inter-CU padding, and pixel replication at the image border
 *
 * Choose padding function based on:
 *    1. e0 data type - typecasting from 8-bit or 32-bit to 16-bit functions are not faster
 *                    - EXCEPT for a 32-bit to 16-bit cast when e0.x != 1 
 *    2. Left & Right padding same?
 *    3. Block Height*e0.y is a multiple of two
 *                    - If e0.y is a multiple of two then we do not need any
 *                      run time checks for this
 *
 * Ideally, these can be chosen at offline time with the exception
 * of the block height.
 * Most optimal 1 <---> 8 Least optimal (within e0 data type)
 * The Cycle Count is based on lp&rp=4, 16x16 block, and 16-bit variant
 *    1 -  385cc: [lp & rp same] & [bh*e0.y multiple of 2] & [e0.x is 1]
 *    2 -  518cc: [lp & rp same] & [e0.x is 1]
 *    3 -  547cc: [bh*e0.y multiple of 2] & [e0.x is 1]
 *    4 -  888cc: [e0.x is 1]
 *
 *    For these cases, there are two cc for e0x = 1 and e0x = 2
 *    5 -  796cc,1276cc: [lp & rp same] & [bh*e0.y multiple of 2]
 *    6 - 1065cc,1513cc: [lp & rp same]
 *    7 - 1163cc,1611cc: [bh*e0.y multiple of 2]
 *    8 - 1947cc,2459cc: Most general case
 *****************************************************************************************/

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_08_h2(vec08u* blk, int sstr, int bw, int bh, int padx);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_08(vec08u* blk, int sstr, int bw, int bh, int padx);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_08_h2(vec08u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_08(vec08u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_08_h2_e0x(vec08u* blk, int sstr, int bw, int bh, int e0x, int padx);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_08_e0x(vec08u* blk, int sstr, int bw, int bh, int e0x, int padx);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_08_h2_e0x(vec08u* blk, int sstr, int bw, int bh, int e0x, int leftPadd, int rightPadd);

/*!
   Unsigned 8-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_08_e0x(vec08u* blk, int sstr, int bw, int bh, int e0x, int leftPadd, int rightPadd);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_16_h2(vec16u* blk, int sstr, int bw, int bh, int padx);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_16(vec16u* blk, int sstr, int bw, int bh, int padx);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_16_h2(vec16u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_16(vec16u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_16_h2_e0x(vec16u* blk, int sstr, int bw, int bh, int e0x, int padx);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_16_e0x(vec16u* blk, int sstr, int bw, int bh, int e0x, int padx);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_16_h2_e0x(vec16u* blk, int sstr, int bw, int bh, int e0x, int leftPadd, int rightPadd);

/*!
   Unsigned 16-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_16_e0x(vec16u* blk, int sstr, int bw, int bh, int e0x, int leftPadd, int rightPadd);

/*!
   Unsigned 32-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param e0x       - [Input]         e0.x size
   \param padx      - [Input]         Left & Right Border padding size
 */
void apu_til_padhor_32(vec32u* blk, int sstr, int bw, int bh, int padx);

/*!
   Unsigned 32-bit Horizontal padding with pixel replication (in place).
   _bh_ is required to be a multiple of 2.
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_32_h2(vec32u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);

/*!
   Unsigned 32-bit Horizontal padding with pixel replication (in place).
 
   \param blk       - [Input/Output]  Source block pointer
   \param sstr      - [Input]         Source block stride
   \param bw        - [Input]         Block Width
   \param bh        - [Input]         Block Height * e0.y
   \param leftPadd  - [Input]         Left border padding size
   \param rightPadd - [Input]         Right border padding size
 */
void apu_til_padhor_32(vec32u* blk, int sstr, int bw, int bh, int leftPadd, int rightPadd);


/******************************* Vector Copy Functions **********************************
 *
 * These functions will copy from one vector buffer to another. If the destination height
 * is larger than the source height, the source is duplicated into the destination.
 * The source height has to be a factor of the destination height.
 *
 * Choose copy function based on:
 *    1. 16-bit aligned addresses and if the copy span is multiple of 2
 *    2. If the copy span is a multiple of 2 & height is a multiple of 2
 *    2. If the copy span is a multiple of 2
 *
 * The most optimal function to use will have to be chosen at runtime.
 *
 * Most optimal 1 <---> 6 Least optimal
 * The Cycle Count is based on a 20x16 block of data to copy
 *    1 -  397cc: apu_til_copy_16_w2_h2
 *    2 -  397cc: apu_til_copy_16_w2
 *    3 -  693cc: apu_til_copy_08_w2_h2
 *    4 -  715cc: apu_til_copy_16
 *    5 -  717cc: apu_til_copy_08_w2
 *    6 - 1355cc: apu_til_copy_08
 *****************************************************************************************/
 
/*!
   Copy from one vector buffer to another. This will choose
   the most efficient copy function to use. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.

   \param dst           - [Output]  Destination block pointer
   \param dspan         - [Output]  Destination block span
   \param src           - [Input]   Source block pointer
   \param sspan         - [Input]   Source block span
   \param sh            - [Input]   Source block height
   \param widthInBytes  - [Input]   Copy block width in bytes
   \param height        - [Input]   Copy block height 
 */
void apu_til_copy(
               vec08u* restrict dst, int dspan,
         const vec08u* restrict src, int sspan, int sh,
               int widthInBytes, int height);

/*!
   8-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_08(
               vec08u* restrict dst, int dstr,
         const vec08u* restrict src, int sstr, int sh,
               int bw, int bh);

/*!
   8-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
   
   Block width is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_08_w2(
               vec08u* restrict dst, int dstr,
         const vec08u* restrict src, int sstr, int sh,
               int bw, int bh);

/*!
   8-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
   
   Block width is a multiple of 2.
   Block height is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_08_w2_h2(
               vec08u* restrict dst, int dstr,
         const vec08u* restrict src, int sstr, int sh,
               int bw, int bh);

/*!
   16-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_16(
               vec16u* restrict dst, int dstr,
         const vec16u* restrict src, int sstr, int sh,
               int bw, int bh);

/*!
   16-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
   
   Block width is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_16_w2(
               vec16u* restrict dst, int dstr,
         const vec16u* restrict src, int sstr, int sh,
               int bw, int bh);

/*!
   16-bit copy from one vector buffer to another. If the destination height
   is larger than the source height, the source is duplicated into the destination.
   The source height has to be a factor of the destination height.
   
   Block width is a multiple of 2.
   Block height is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sh   - [Input]   Source block height
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
 */
void apu_til_copy_16_w2_h2(
               vec16u* restrict dst, int dstr,
         const vec16u* restrict src, int sstr, int sh,
               int bw, int bh);

/**************************** Vector Copy Right Functions *********************************
 *
 * These functions will copy from one vector buffer to another. If the block width
 * is larger than the source width, the source is duplicated into the destination.
 * The source width has to be a factor of the block width.
 *
 * Choose copy function based on:
 *    1. 16-bit aligned addresses and if the copy span is multiple of 2
 *    2. If the copy span is a multiple of 2
 *
 * The most optimal function to use will have to be chosen at runtime.
 *
 * Most optimal 1 <---> 4 Least optimal
 * The Cycle Count is based on source width=4, copy width=16, copy height=16
 *    1 -  919cc: apu_til_copy_right_16_w2
 *    2 - 1126cc: apu_til_copy_right_16
 *    3 - 1383cc: apu_til_copy_right_08_w2
 *    4 - 1766cc: apu_til_copy_right_08
 *****************************************************************************************/
 
/*!
   Copy from one vector buffer to another. This will choose
   the most efficient copy function to use.
 
   \param dst           - [Output]  Destination block pointer
   \param dspan         - [Output]  Destination block span
   \param src           - [Input]   Source block pointer
   \param sspan         - [Input]   Source block span
   \param sw            - [Input]   Source block width
   \param widthInBytes  - [Input]   Copy block width
   \param height        - [Input]   Copy block height 
   \param mask          - [Input]   CU Enable mask
 */
void apu_til_copy_right(
               vec08u* restrict dst, int dspan,
         const vec08u* restrict src, int sspan, int sw,
               int widthInBytes, int height,
               vec16u mask);

/*!
   8-bit copy from one vector buffer to another. If the block width
   is larger than the source width, the source is duplicated into the destination.
   The source width has to be a factor of the block width.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sw   - [Input]   Source block width
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
   \param mask - [Input]   CU Enable mask
 */
void apu_til_copy_right_08(
               vec08u* restrict dst, int dspan,
         const vec08u* restrict src, int sspan, int sw,
               int widthInBytes, int height,
               vec16u mask);

/*!
   8-bit copy from one vector buffer to another. If the block width
   is larger than the source width, the source is duplicated into the destination.
   The source width has to be a factor of the block width.

   Block width is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sw   - [Input]   Source block width
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
   \param mask - [Input]   CU Enable mask
 */
void apu_til_copy_right_08_w2(
               vec08u* restrict dst, int dspan,
         const vec08u* restrict src, int sspan, int sw,
               int widthInBytes, int height,
               vec16u mask);

/*!
   16-bit copy from one vector buffer to another. If the block width
   is larger than the source width, the source is duplicated into the destination.
   The source width has to be a factor of the block width.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sw   - [Input]   Source block width
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
   \param mask - [Input]   CU Enable mask
 */
void apu_til_copy_right_16(
               vec16u* restrict dst, int dspan,
         const vec16u* restrict src, int sspan, int sw,
               int widthInBytes, int height,
               vec16u mask);

/*!
   16-bit copy from one vector buffer to another. If the block width
   is larger than the source width, the source is duplicated into the destination.
   The source width has to be a factor of the block width.
   
   Block width is a multiple of 2.
 
   \param dst  - [Output]  Destination block pointer
   \param dstr - [Output]  Destination block stride
   \param src  - [Input]   Source block pointer
   \param sstr - [Input]   Source block stride
   \param sw   - [Input]   Source block width
   \param bw   - [Input]   Copy block width
   \param bh   - [Input]   Copy block height 
   \param mask - [Input]   CU Enable mask
 */
void apu_til_copy_right_16_w2(
               vec16u* restrict dst, int dspan,
         const vec16u* restrict src, int sspan, int sw,
               int widthInBytes, int height,
               vec16u mask);

// [To be consolidated]
void saveImage(char* fn, void *p_src, uint32_t iw, uint32_t ih, uint32_t is, uint8_t bpp);
void readImage(char* fn, uint8_t *p_u8Src, uint32_t iw, uint32_t ih, uint32_t is, uint8_t bpp);

                
// [To be deprecated]               
void apu_til_transfer_08(vec08u*  dst, int dstr, const int08u* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);
void apu_til_transfer_08(vec08s*  dst, int dstr, const int08s* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);
void apu_til_transfer_16(vec16u*  dst, int dstr, const int16u* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);
void apu_til_transfer_16(vec16s*  dst, int dstr, const int16s* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);
void apu_til_transfer_32(vec32s*  dst, int dstr, const int32s* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);
void apu_til_transfer_32(vec32u*  dst, int dstr, const int32u* src, int sstr, int tw, int bw, int bh, int flt_size_x, int flt_size_y);               

#endif /* __APU_TEST_UTIL_CORE_H__ */

