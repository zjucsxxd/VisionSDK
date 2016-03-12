#ifndef _ACF_PROCESS_APU_HISTORY_MAXIMUM
#define _ACF_PROCESS_APU_HISTORY_MAXIMUM

#include <acf_process_apu.h>
#include <HISTORY_MAXIMUM_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HISTORY_MAXIMUM[] = {{6, 8, 2, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 1, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HISTORY_MAXIMUM[] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

static acf_scenario gScenarioArray_HISTORY_MAXIMUM[] = {
{0, 0, 2160, 0, 0, gScenarioBufferData0_HISTORY_MAXIMUM, 290, gScenarioKernelData0_HISTORY_MAXIMUM, 28}
};

static acf_scenario_list gScenarioList_HISTORY_MAXIMUM = {
1, //number of scenarios
gScenarioArray_HISTORY_MAXIMUM};
//**************************************************************

class HISTORY_MAXIMUM : public ACF_Process_APU
{
public:
   HISTORY_MAXIMUM(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HISTORY_MAXIMUM");
         SetApuLoadInfo(HISTORY_MAXIMUM_LOAD_SEGMENTS,
                        HISTORY_MAXIMUM_LOAD_PMEM, HISTORY_MAXIMUM_LOAD_PMEM_SIZE,
                        HISTORY_MAXIMUM_LOAD_DMEM, HISTORY_MAXIMUM_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("SRC_0", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("SRC_1", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 15, 0x0);
         AddPort("SRC_2", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 16, 0x0);
         AddPort("SRC_3", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 17, 0x0);
         AddPort("SRC_4", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 18, 0x0);
         AddPort("SRC_5", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 19, 0x0);
         AddPort("SRC_6", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 20, 0x0);
         AddPort("SRC_7", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 21, 0x0);
         AddPort("SRC_8", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 22, 0x0);
         AddPort("SRC_9", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 23, 0x0);
         AddPort("SRC_10", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 24, 0x0);
         AddPort("SRC_11", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 25, 0x0);
         AddPort("SRC_12", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 26, 0x0);
         AddPort("SRC_13", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 27, 0x0);
         AddPort("SRC_14", ICP_DATATYPE_08U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 28, 0x0);
         AddPort("DST_IMG", ICP_DATATYPE_08U, 1, 1, 6, 8, 1, 0, 0, 0, 0, 0, 14);

         CfgScenarios(&gScenarioList_HISTORY_MAXIMUM);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HISTORY_MAXIMUM
