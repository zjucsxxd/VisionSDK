#ifndef _ACF_PROCESS_APU_APU_FAST9_COLOR
#define _ACF_PROCESS_APU_APU_FAST9_COLOR

#include <acf_process_apu.h>
#include <APU_FAST9_COLOR_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_FAST9_COLOR[] = {{8, 8, 6, 0, 0x0}, {8, 8, 4, 0, 0x2211}, {8, 8, 4, 1, 0x4433}, {8, 8, 4, 2, 0x2211}, {8, 8, 4, 3, 0x2222}, {8, 8, 1, 4, 0x0}, {8, 8, 1, 4, 0x0}, {8, 8, 2, 4, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_FAST9_COLOR[] = {{0}, {1}, {2}, {3}, {4}, {4}, {4}};

static acf_scenario gScenarioArray_APU_FAST9_COLOR[] = {
{0, 0, 3520, 16, 4, gScenarioBufferData0_APU_FAST9_COLOR, 100, gScenarioKernelData0_APU_FAST9_COLOR, 14}
};

static acf_scenario_list gScenarioList_APU_FAST9_COLOR = {
1, //number of scenarios
gScenarioArray_APU_FAST9_COLOR};
//**************************************************************

class APU_FAST9_COLOR : public ACF_Process_APU
{
public:
   APU_FAST9_COLOR(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_FAST9_COLOR");
         SetApuLoadInfo(APU_FAST9_COLOR_LOAD_SEGMENTS,
                        APU_FAST9_COLOR_LOAD_PMEM, APU_FAST9_COLOR_LOAD_PMEM_SIZE,
                        APU_FAST9_COLOR_LOAD_DMEM, APU_FAST9_COLOR_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 3, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0x7070707);
         AddPort("THRESHOLD", ICP_DATATYPE_08U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 8);
         AddPort("MARK_COLOR_CHANNEL", ICP_DATATYPE_08U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 9);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 3, 1, 8, 8, 1, 0, 0, 0, 0, 0, 7);

         CfgScenarios(&gScenarioList_APU_FAST9_COLOR);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_FAST9_COLOR
