#ifndef _ACF_PROCESS_APU_INTERP_LINEAR_GRAYSCALE
#define _ACF_PROCESS_APU_INTERP_LINEAR_GRAYSCALE

#include <acf_process_apu.h>
#include <INTERP_LINEAR_GRAYSCALE_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_INTERP_LINEAR_GRAYSCALE[] = {{16, 4, 2, 0, 0x200}, {16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_INTERP_LINEAR_GRAYSCALE[] = {{0}};

static acf_scenario gScenarioArray_INTERP_LINEAR_GRAYSCALE[] = {
{0, 0, 400, 0, 0, gScenarioBufferData0_INTERP_LINEAR_GRAYSCALE, 30, gScenarioKernelData0_INTERP_LINEAR_GRAYSCALE, 2}
};

static acf_scenario_list gScenarioList_INTERP_LINEAR_GRAYSCALE = {
1, //number of scenarios
gScenarioArray_INTERP_LINEAR_GRAYSCALE};
//**************************************************************

class INTERP_LINEAR_GRAYSCALE : public ACF_Process_APU
{
public:
   INTERP_LINEAR_GRAYSCALE(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("INTERP_LINEAR_GRAYSCALE");
         SetApuLoadInfo(INTERP_LINEAR_GRAYSCALE_LOAD_SEGMENTS,
                        INTERP_LINEAR_GRAYSCALE_LOAD_PMEM, INTERP_LINEAR_GRAYSCALE_LOAD_PMEM_SIZE,
                        INTERP_LINEAR_GRAYSCALE_LOAD_DMEM, INTERP_LINEAR_GRAYSCALE_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x100);
         AddPort("DELTA_X", ICP_DATATYPE_08U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 2, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_INTERP_LINEAR_GRAYSCALE);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_INTERP_LINEAR_GRAYSCALE
