#ifndef _ACF_PROCESS_APU_THRESHOLD_32U
#define _ACF_PROCESS_APU_THRESHOLD_32U

#include <acf_process_apu.h>
#include <THRESHOLD_32U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_THRESHOLD_32U[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_THRESHOLD_32U[] = {{0}};

static acf_scenario gScenarioArray_THRESHOLD_32U[] = {
{0, 0, 640, 8, 0, gScenarioBufferData0_THRESHOLD_32U, 30, gScenarioKernelData0_THRESHOLD_32U, 2}
};

static acf_scenario_list gScenarioList_THRESHOLD_32U = {
1, //number of scenarios
gScenarioArray_THRESHOLD_32U};
//**************************************************************

class THRESHOLD_32U : public ACF_Process_APU
{
public:
   THRESHOLD_32U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("THRESHOLD_32U");
         SetApuLoadInfo(THRESHOLD_32U_LOAD_SEGMENTS,
                        THRESHOLD_32U_LOAD_PMEM, THRESHOLD_32U_LOAD_PMEM_SIZE,
                        THRESHOLD_32U_LOAD_DMEM, THRESHOLD_32U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_32U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("INPUT_1", ICP_DATATYPE_32U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_THRESHOLD_32U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_THRESHOLD_32U
