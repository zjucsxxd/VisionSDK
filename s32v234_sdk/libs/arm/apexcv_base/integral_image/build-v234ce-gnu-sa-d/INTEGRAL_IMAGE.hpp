#ifndef _ACF_PROCESS_APU_INTEGRAL_IMAGE
#define _ACF_PROCESS_APU_INTEGRAL_IMAGE

#include <acf_process_apu.h>
#include <INTEGRAL_IMAGE_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_INTEGRAL_IMAGE[] = {{16, 4, 2, 0, 0x0}, {16, 1, 1, 0, 0x0}, {16, 4, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_INTEGRAL_IMAGE[] = {{0}};

static acf_scenario gScenarioArray_INTEGRAL_IMAGE[] = {
{0, 0, 704, 0, 0, gScenarioBufferData0_INTEGRAL_IMAGE, 30, gScenarioKernelData0_INTEGRAL_IMAGE, 2}
};

static acf_scenario_list gScenarioList_INTEGRAL_IMAGE = {
1, //number of scenarios
gScenarioArray_INTEGRAL_IMAGE};
//**************************************************************

class INTEGRAL_IMAGE : public ACF_Process_APU
{
public:
   INTEGRAL_IMAGE(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("INTEGRAL_IMAGE");
         SetApuLoadInfo(INTEGRAL_IMAGE_LOAD_SEGMENTS,
                        INTEGRAL_IMAGE_LOAD_PMEM, INTEGRAL_IMAGE_LOAD_PMEM_SIZE,
                        INTEGRAL_IMAGE_LOAD_DMEM, INTEGRAL_IMAGE_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_32U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 2);

         CfgScenarios(&gScenarioList_INTEGRAL_IMAGE);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_INTEGRAL_IMAGE
