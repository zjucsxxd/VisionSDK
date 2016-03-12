#ifndef _ACF_PROCESS_APU_APU_MATCH_DESCRIPTORS
#define _ACF_PROCESS_APU_APU_MATCH_DESCRIPTORS

#include <acf_process_apu.h>
#include <APU_MATCH_DESCRIPTORS_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_MATCH_DESCRIPTORS[] = {{128, 4, 2, 0, 0x0}, {512, 1, 1, 0, 0x0}, {512, 1, 1, 0, 0x0}, {128, 4, 2, 0, 0x0}, {4, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_MATCH_DESCRIPTORS[] = {{0}};

static acf_scenario gScenarioArray_APU_MATCH_DESCRIPTORS[] = {
{0, 0, 2048, 2056, 0, gScenarioBufferData0_APU_MATCH_DESCRIPTORS, 50, gScenarioKernelData0_APU_MATCH_DESCRIPTORS, 2}
};

static acf_scenario_list gScenarioList_APU_MATCH_DESCRIPTORS = {
1, //number of scenarios
gScenarioArray_APU_MATCH_DESCRIPTORS};
//**************************************************************

class APU_MATCH_DESCRIPTORS : public ACF_Process_APU
{
public:
   APU_MATCH_DESCRIPTORS(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_MATCH_DESCRIPTORS");
         SetApuLoadInfo(APU_MATCH_DESCRIPTORS_LOAD_SEGMENTS,
                        APU_MATCH_DESCRIPTORS_LOAD_PMEM, APU_MATCH_DESCRIPTORS_LOAD_PMEM_SIZE,
                        APU_MATCH_DESCRIPTORS_LOAD_DMEM, APU_MATCH_DESCRIPTORS_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 128, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("INPUT_1", ICP_DATATYPE_08U, 1, 1, 128, 4, 0, 0, 0, 0, 0, 0, 3, 0x0);
         AddPort("INPUT_CONFIG", ICP_DATATYPE_16U, 1, 1, 4, 1, 0, 1, 1, 0, 1, 0, 4);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 512, 1, 1, 1, 1, 0, 1, 0, 1);
         AddPort("OUTPUT_1", ICP_DATATYPE_16S, 1, 1, 512, 1, 1, 1, 1, 0, 1, 0, 2);

         CfgScenarios(&gScenarioList_APU_MATCH_DESCRIPTORS);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_MATCH_DESCRIPTORS
