#ifndef _ACF_PROCESS_APU_APU_SAT
#define _ACF_PROCESS_APU_APU_SAT

#include <acf_process_apu.h>
#include <APU_SAT_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_SAT[] = {{8, 8, 2, 0, 0x0}, {8, 8, 4, 0, 0x6565}, {8, 8, 2, 1, 0x0}, {8, 8, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_SAT[] = {{0}, {1}};

static acf_scenario gScenarioArray_APU_SAT[] = {
{0, 0, 3780, 0, 1, gScenarioBufferData0_APU_SAT, 40, gScenarioKernelData0_APU_SAT, 4}
};

static acf_scenario_list gScenarioList_APU_SAT = {
1, //number of scenarios
gScenarioArray_APU_SAT};
//**************************************************************

class APU_SAT : public ACF_Process_APU
{
public:
   APU_SAT(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_SAT");
         SetApuLoadInfo(APU_SAT_LOAD_SEGMENTS,
                        APU_SAT_LOAD_PMEM, APU_SAT_LOAD_PMEM_SIZE,
                        APU_SAT_LOAD_DMEM, APU_SAT_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0x6050506);
         AddPort("OUTPUT_0", ICP_DATATYPE_32U, 1, 1, 8, 8, 1, 0, 0, 0, 0, 0, 1);
         AddPort("OUTPUT_1", ICP_DATATYPE_08U, 1, 1, 8, 8, 1, 0, 0, 0, 0, 0, 2);

         CfgScenarios(&gScenarioList_APU_SAT);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_SAT
