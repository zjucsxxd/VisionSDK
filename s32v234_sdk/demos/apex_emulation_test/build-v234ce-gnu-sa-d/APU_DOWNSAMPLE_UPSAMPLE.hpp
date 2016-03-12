#ifndef _ACF_PROCESS_APU_APU_DOWNSAMPLE_UPSAMPLE
#define _ACF_PROCESS_APU_APU_DOWNSAMPLE_UPSAMPLE

#include <acf_process_apu.h>
#include <APU_DOWNSAMPLE_UPSAMPLE_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_DOWNSAMPLE_UPSAMPLE[] = {{8, 8, 4, 0, 0x2211}, {4, 4, 2, 0, 0x0}, {16, 16, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_DOWNSAMPLE_UPSAMPLE[] = {{0}, {1}};

static acf_scenario gScenarioArray_APU_DOWNSAMPLE_UPSAMPLE[] = {
{0, 0, 952, 0, 1, gScenarioBufferData0_APU_DOWNSAMPLE_UPSAMPLE, 30, gScenarioKernelData0_APU_DOWNSAMPLE_UPSAMPLE, 4}
};

static acf_scenario_list gScenarioList_APU_DOWNSAMPLE_UPSAMPLE = {
1, //number of scenarios
gScenarioArray_APU_DOWNSAMPLE_UPSAMPLE};
//**************************************************************

class APU_DOWNSAMPLE_UPSAMPLE : public ACF_Process_APU
{
public:
   APU_DOWNSAMPLE_UPSAMPLE(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_DOWNSAMPLE_UPSAMPLE");
         SetApuLoadInfo(APU_DOWNSAMPLE_UPSAMPLE_LOAD_SEGMENTS,
                        APU_DOWNSAMPLE_UPSAMPLE_LOAD_PMEM, APU_DOWNSAMPLE_UPSAMPLE_LOAD_PMEM_SIZE,
                        APU_DOWNSAMPLE_UPSAMPLE_LOAD_DMEM, APU_DOWNSAMPLE_UPSAMPLE_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT", ICP_DATATYPE_08U, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("OUTPUT_DOWN", ICP_DATATYPE_08U, 1, 1, 4, 4, 1, 0, 0, 0, 0, 0, 1);
         AddPort("OUTPUT_UP", ICP_DATATYPE_08U, 1, 1, 16, 16, 1, 0, 0, 0, 0, 0, 2);

         CfgScenarios(&gScenarioList_APU_DOWNSAMPLE_UPSAMPLE);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_DOWNSAMPLE_UPSAMPLE
