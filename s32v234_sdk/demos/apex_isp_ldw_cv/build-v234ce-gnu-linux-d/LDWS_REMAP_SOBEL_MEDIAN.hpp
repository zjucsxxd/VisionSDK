#ifndef _ACF_PROCESS_APU_LDWS_REMAP_SOBEL_MEDIAN
#define _ACF_PROCESS_APU_LDWS_REMAP_SOBEL_MEDIAN

#include <acf_process_apu.h>
#include <LDWS_REMAP_SOBEL_MEDIAN_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_LDWS_REMAP_SOBEL_MEDIAN[] = {{36, 12, 2, 0, 0x0}, {6, 8, 4, 0, 0x2211}, {6, 8, 4, 1, 0x2211}, {6, 8, 2, 2, 0x0}, {6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_LDWS_REMAP_SOBEL_MEDIAN[] = {{0}, {1}, {2}};

static acf_scenario gScenarioArray_LDWS_REMAP_SOBEL_MEDIAN[] = {
{0, 0, 2024, 0, 2, gScenarioBufferData0_LDWS_REMAP_SOBEL_MEDIAN, 60, gScenarioKernelData0_LDWS_REMAP_SOBEL_MEDIAN, 6}
};

static acf_scenario_list gScenarioList_LDWS_REMAP_SOBEL_MEDIAN = {
1, //number of scenarios
gScenarioArray_LDWS_REMAP_SOBEL_MEDIAN};
//**************************************************************

class LDWS_REMAP_SOBEL_MEDIAN : public ACF_Process_APU
{
public:
   LDWS_REMAP_SOBEL_MEDIAN(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("LDWS_REMAP_SOBEL_MEDIAN");
         SetApuLoadInfo(LDWS_REMAP_SOBEL_MEDIAN_LOAD_SEGMENTS,
                        LDWS_REMAP_SOBEL_MEDIAN_LOAD_PMEM, LDWS_REMAP_SOBEL_MEDIAN_LOAD_PMEM_SIZE,
                        LDWS_REMAP_SOBEL_MEDIAN_LOAD_DMEM, LDWS_REMAP_SOBEL_MEDIAN_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("SRC_IMG", ICP_DATATYPE_08U, 1, 1, 36, 12, 0, 0, 0, 1, 1, 0, 0, 0x48481818);
         AddPort("LOCAL_OFFSET", ICP_DATATYPE_16U, 1, 1, 6, 8, 0, 0, 0, 0, 0, 0, 4, 0x2020202);
         AddPort("DELTA", ICP_DATATYPE_08U, 2, 1, 6, 8, 0, 0, 0, 0, 0, 0, 5, 0x2020202);
         AddPort("DST_IMG", ICP_DATATYPE_08U, 1, 1, 6, 8, 1, 0, 0, 0, 0, 0, 3);

         CfgScenarios(&gScenarioList_LDWS_REMAP_SOBEL_MEDIAN);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_LDWS_REMAP_SOBEL_MEDIAN
