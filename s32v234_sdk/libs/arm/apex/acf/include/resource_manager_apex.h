#ifndef _RESOURCEMANAGER_APEX_H
#define _RESOURCEMANAGER_APEX_H

#include <stdint.h>
#include <global_errors.h>

//resource type enumeration
enum
{  
   //RES__<set type>__<res type>
   RES__APEX__APU = 0,
   RES__APEX__CU_32,
   RES__SMEM_64K
};

//user type enumeration (no association with a set)
enum
{
   USER__ACF = 0
};


LIB_RESULT ResourceManagerInit_APEX(int apexID, uint32_t lHwVersion);

uint32_t InitApexResReq(int apexID, uint32_t lArray[3], uint32_t lResType, uint32_t lNumOrInstance);
uint32_t ApexSetTypeId(int apexID);
uint32_t APEX_ResTypeId(int apexID, int32_t lResEnum);
uint32_t UserTypeId(int apexID, int32_t lUserEnum);

#endif //_RESOURCEMANAGER_APEX_H
