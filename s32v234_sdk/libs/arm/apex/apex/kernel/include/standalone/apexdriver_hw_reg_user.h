/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2010 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

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
   void* ReturnVirtualHwPtr(int lApexID, HW_REG_ID lHwRegId);
   void* ReturnPhysicalHwPtr(int lApexID, HW_REG_ID lHwRegId);

#ifdef __cplusplus
}
#endif

#endif //HW_REGISTERS_USER_HPP__CV230X
