#ifndef _ACF_PROCESS_APU_APU_ADD
#define _ACF_PROCESS_APU_APU_ADD

#include <acf_process_apu.h>
#include <APU_ADD_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_ADD[] = {{8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_ADD[] = {{0}};

static acf_scenario gScenarioArray_APU_ADD[] = {
{0, 0, 512, 0, 0, gScenarioBufferData0_APU_ADD, 30, gScenarioKernelData0_APU_ADD, 2}
};

static acf_scenario_list gScenarioList_APU_ADD = {
1, //number of scenarios
gScenarioArray_APU_ADD};
//**************************************************************

class APU_ADD : public ACF_Process_APU
{
public:
   APU_ADD(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_ADD");
         SetApuLoadInfo(APU_ADD_LOAD_SEGMENTS,
                        APU_ADD_LOAD_PMEM, APU_ADD_LOAD_PMEM_SIZE,
                        APU_ADD_LOAD_DMEM, APU_ADD_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("Template_Demo_InputA", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("Template_Demo_InputB", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 2, 0x0);
         AddPort("Template_Demo_Output", ICP_DATATYPE_16U, 1, 1, 8, 8, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_APU_ADD);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_ADD
