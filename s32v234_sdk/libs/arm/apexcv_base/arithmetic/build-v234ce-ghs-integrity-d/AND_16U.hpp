#ifndef _ACF_PROCESS_APU_AND_16U
#define _ACF_PROCESS_APU_AND_16U

#include <acf_process_apu.h>
#include <AND_16U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_AND_16U[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_AND_16U[] = {{0}};

static acf_scenario gScenarioArray_AND_16U[] = {
{0, 0, 768, 0, 0, gScenarioBufferData0_AND_16U, 30, gScenarioKernelData0_AND_16U, 2}
};

static acf_scenario_list gScenarioList_AND_16U = {
1, //number of scenarios
gScenarioArray_AND_16U};
//**************************************************************

class AND_16U : public ACF_Process_APU
{
public:
   AND_16U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("AND_16U");
         SetApuLoadInfo(AND_16U_LOAD_SEGMENTS,
                        AND_16U_LOAD_PMEM, AND_16U_LOAD_PMEM_SIZE,
                        AND_16U_LOAD_DMEM, AND_16U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_16U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("INPUT_1", ICP_DATATYPE_16U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 2, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_16U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_AND_16U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_AND_16U
