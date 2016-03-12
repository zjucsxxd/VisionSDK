#ifndef _ACF_PROCESS_APU_HISTOGRAM
#define _ACF_PROCESS_APU_HISTOGRAM

#include <acf_process_apu.h>
#include <HISTOGRAM_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HISTOGRAM[] = {{16, 4, 2, 0, 0x0}, {256, 1, 1, 0, 0x0}, {256, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HISTOGRAM[] = {{0}};

static acf_scenario gScenarioArray_HISTOGRAM[] = {
{0, 0, 640, 1024, 0, gScenarioBufferData0_HISTOGRAM, 30, gScenarioKernelData0_HISTOGRAM, 2}
};

static acf_scenario_list gScenarioList_HISTOGRAM = {
1, //number of scenarios
gScenarioArray_HISTOGRAM};
//**************************************************************

class HISTOGRAM : public ACF_Process_APU
{
public:
   HISTOGRAM(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HISTOGRAM");
         SetApuLoadInfo(HISTOGRAM_LOAD_SEGMENTS,
                        HISTOGRAM_LOAD_PMEM, HISTOGRAM_LOAD_PMEM_SIZE,
                        HISTOGRAM_LOAD_DMEM, HISTOGRAM_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_32U, 1, 1, 256, 1, 1, 1, 1, 0, 1, 0, 2);

         CfgScenarios(&gScenarioList_HISTOGRAM);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HISTOGRAM
