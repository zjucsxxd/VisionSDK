#ifndef _ACF_PROCESS_APU_APU_ROTATE
#define _ACF_PROCESS_APU_APU_ROTATE

#include <acf_process_apu.h>
#include <APU_ROTATE_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_ROTATE[] = {{8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_ROTATE[] = {{0}};

static acf_scenario gScenarioArray_APU_ROTATE[] = {
{0, 0, 256, 0, 0, gScenarioBufferData0_APU_ROTATE, 20, gScenarioKernelData0_APU_ROTATE, 2}
};

static acf_scenario_list gScenarioList_APU_ROTATE = {
1, //number of scenarios
gScenarioArray_APU_ROTATE};
//**************************************************************

class APU_ROTATE : public ACF_Process_APU
{
public:
   APU_ROTATE(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_ROTATE");
         SetApuLoadInfo(APU_ROTATE_LOAD_SEGMENTS,
                        APU_ROTATE_LOAD_PMEM, APU_ROTATE_LOAD_PMEM_SIZE,
                        APU_ROTATE_LOAD_DMEM, APU_ROTATE_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 1, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 8, 8, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_APU_ROTATE);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_ROTATE
