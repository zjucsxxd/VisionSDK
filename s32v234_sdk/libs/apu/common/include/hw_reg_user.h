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

#ifndef HW_REGISTERS_USER_HPP__CV230X
#define HW_REGISTERS_USER_HPP__CV230X

typedef enum HW_REG_ID_TAG
{
   HW_REG_SMEM,

   HW_REG_MCDMA,
   HW_REG_MODMA,
   HW_REG_STIO,
   HW_REG_USEQ,
   HW_REG_GLOBAL,
   HW_REG_DEBUG,
   HW_REG_DMEM_FIFO_0,
   HW_REG_DMEM_FIFO_1,
   HW_REG_CMEM_IF,
   HW_REG_HOR_SCALER,

   HW_REG_CMEM_GOC,

   HW_REG_CMEM_SOC_32,
   HW_REG_CMEM_SOC_64,

   HW_REG_CMEM_BOC_31_00,
   HW_REG_CMEM_BOC_63_32,
   HW_REG_CMEM_BOC_63_00,

   HW_REG_NUM //indicate number of enumerations (must always be final enumeration)
} HW_REG_ID;

#ifdef __cplusplus
extern "C"
{
#endif

   int InitVirtualHwPtrArray();
   int UnmapVirtualHwPtrArray();
   void* ReturnVirtualHwPtr(HW_REG_ID lHwRegId);
   void* ReturnPhysicalHwPtr(HW_REG_ID lHwRegId);

#ifdef __cplusplus
}
#endif

#endif //HW_REGISTERS_USER_HPP__CV230X
