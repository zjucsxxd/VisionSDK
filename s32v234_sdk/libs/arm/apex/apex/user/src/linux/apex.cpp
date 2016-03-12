#include "apex.h"
#include <stdio.h>
extern "C"
{
  int InitVirtualHwPtrArray();
}

void ACF_Init()
{
  InitVirtualHwPtrArray();
  printf("Mem init ok\n");
  ResourceManagerInit_APEX(0, global_hal_RetHwVersion(0));
  printf("Res man 0 init ok\n");
  ResourceManagerInit_APEX(1, global_hal_RetHwVersion(1));
  printf("Res man 1 init ok\n");
}