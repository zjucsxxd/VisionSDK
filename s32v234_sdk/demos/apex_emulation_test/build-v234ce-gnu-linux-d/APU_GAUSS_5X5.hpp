#ifndef _ACF_PROCESS_APU_APU_GAUSS_5X5
#define _ACF_PROCESS_APU_APU_GAUSS_5X5

#include <acf_process_apu.h>
#include <APU_GAUSS_5X5_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_GAUSS_5X5[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_GAUSS_5X5[] = {{1}};

static acf_scenario gScenarioArray_APU_GAUSS_5X5[] = {
{0, 0, 560, 0, 1, gScenarioBufferData0_APU_GAUSS_5X5, 20, gScenarioKernelData0_APU_GAUSS_5X5, 2}
};

static acf_scenario_list gScenarioList_APU_GAUSS_5X5 = {
1, //number of scenarios
gScenarioArray_APU_GAUSS_5X5};
//**************************************************************

class APU_GAUSS_5X5 : public ACF_Process_APU
{
public:
   APU_GAUSS_5X5(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_GAUSS_5X5");
         SetApuLoadInfo(APU_GAUSS_5X5_LOAD_SEGMENTS,
                        APU_GAUSS_5X5_LOAD_PMEM, APU_GAUSS_5X5_LOAD_PMEM_SIZE,
                        APU_GAUSS_5X5_LOAD_DMEM, APU_GAUSS_5X5_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("Gauss5x5Graph_Input", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("Gauss5x5Graph_Output", ICP_DATATYPE_08U, 1, 1, 8, 8, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_APU_GAUSS_5X5);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_GAUSS_5X5
