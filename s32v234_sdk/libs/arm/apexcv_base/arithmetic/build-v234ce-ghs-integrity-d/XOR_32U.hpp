#ifndef _ACF_PROCESS_APU_XOR_32U
#define _ACF_PROCESS_APU_XOR_32U

#include <acf_process_apu.h>
#include <XOR_32U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_XOR_32U[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_XOR_32U[] = {{0}};

static acf_scenario gScenarioArray_XOR_32U[] = {
{0, 0, 1536, 0, 0, gScenarioBufferData0_XOR_32U, 30, gScenarioKernelData0_XOR_32U, 2}
};

static acf_scenario_list gScenarioList_XOR_32U = {
1, //number of scenarios
gScenarioArray_XOR_32U};
//**************************************************************

class XOR_32U : public ACF_Process_APU
{
public:
   XOR_32U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("XOR_32U");
         SetApuLoadInfo(XOR_32U_LOAD_SEGMENTS,
                        XOR_32U_LOAD_PMEM, XOR_32U_LOAD_PMEM_SIZE,
                        XOR_32U_LOAD_DMEM, XOR_32U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_32U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("INPUT_1", ICP_DATATYPE_32U, 1, 1, 16, 4, 0, 0, 0, 0, 0, 0, 2, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_32U, 1, 1, 16, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_XOR_32U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_XOR_32U
