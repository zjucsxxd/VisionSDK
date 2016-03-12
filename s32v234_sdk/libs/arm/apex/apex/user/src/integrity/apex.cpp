#include "apex.h"

void ACF_Init()
{
  ResourceManagerInit_APEX(0, global_hal_RetHwVersion(0));
  ResourceManagerInit_APEX(1, global_hal_RetHwVersion(1));
}
