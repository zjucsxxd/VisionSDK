#ifndef _ACF_PROCESS_APU_CLZ_08U
#define _ACF_PROCESS_APU_CLZ_08U

#include <acf_process_apu.h>
#include <CLZ_08U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_CLZ_08U[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_CLZ_08U[] = {{0}};

static acf_scenario gScenarioArray_CLZ_08U[] = {
{0, 0, 256, 0, 0, gScenarioBufferData0_CLZ_08U, 20, gScenarioKernelData0_CLZ_08U, 2}
};

static acf_scenario_list gScenarioList_CLZ_08U = {
1, //number of scenarios
gScenarioArray_CLZ_08U};
//**************************************************************

class CLZ_08U : public ACF_Process_APU
{
public:
   CLZ_08U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("CLZ_08U");
         SetApuLoadInfo(CLZ_08U_LOAD_SEGMENTS,
                        CLZ_08U_LOAD_PMEM, CLZ_08U_LOAD_PMEM_SIZE,
                        CLZ_08U_LOAD_DMEM, CLZ_08U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_CLZ_08U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_CLZ_08U
